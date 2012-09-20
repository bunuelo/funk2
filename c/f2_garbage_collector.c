// 
// Copyright (c) 2007-2012 Bo Morgan.
// All rights reserved.
// 
// Author: Bo Morgan
// 
// Permission to use, copy, modify and distribute this software and its
// documentation is hereby granted, provided that both the copyright
// notice and this permission notice appear in all copies of the
// software, derivative works or modified versions, and any portions
// thereof, and that both notices appear in supporting documentation.
// 
// BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
// BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
// WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
// 
// Bo Morgan requests users of this software to return to bo@mit.edu any
// improvements or extensions that they make and grant Bo Morgan the
// rights to redistribute these changes.
// 

#include "funk2.h"

// garbage_collector

void funk2_garbage_collector__init(funk2_garbage_collector_t* this) {
  status("initializing garbage collector.");
  
  funk2_processor_mutex__init(&(this->do_collection_mutex));
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__init(&(this->gc_pool[pool_index]), pool_index);
  }
  
  funk2_never_delete_list__init(&(this->never_delete_list));
  
  funk2_processor_mutex__init(&(this->total_garbage_collection_count__mutex));
  this->total_garbage_collection_count = 0;
  
  status("initializing garbage collector done.");
}

void funk2_garbage_collector__destroy(funk2_garbage_collector_t* this) {
  status("destroying garbage collector.");
  
  funk2_processor_mutex__destroy(&(this->do_collection_mutex));
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__destroy(&(this->gc_pool[pool_index]));
  }

  funk2_never_delete_list__destroy(&(this->never_delete_list));
  funk2_processor_mutex__destroy(&(this->total_garbage_collection_count__mutex));
}

void funk2_garbage_collector__init_sets_from_memory(funk2_garbage_collector_t* this, funk2_memory_t* memory) {
  status("initializing garbage collector from memory.");
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__init_sets_from_memorypool(&(this->gc_pool[pool_index]), &(memory->pool[pool_index]), pool_index);
  }
  
  status("initializing garbage collector from memory done.");
}

void funk2_garbage_collector__know_of_used_exp_mutation(funk2_garbage_collector_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_tricolor__black) {
    int pool_index = this_processor_thread__pool_index();
    int exp__pool_index = __f2ptr__pool_index(exp);
    if (pool_index == exp__pool_index) {
      funk2_garbage_collector_pool__know_of_used_exp_self_mutation(&(this->gc_pool[exp__pool_index]), exp);
    } else {
      funk2_garbage_collector_pool__know_of_used_exp_other_mutation(&(this->gc_pool[exp__pool_index]), exp);
    }
  }
}

void funk2_garbage_collector__know_of_no_more_references(funk2_garbage_collector_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor != funk2_tricolor__white) {
    int pool_index = this_processor_thread__pool_index();
    int exp__pool_index = __f2ptr__pool_index(exp);
    if (pool_index == exp__pool_index) {
      funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(&(this->gc_pool[exp__pool_index]), exp);
    } else {
      funk2_garbage_collector_pool__know_of_used_exp_other_no_more_references(&(this->gc_pool[exp__pool_index]), exp);
    }
  }
}

void funk2_garbage_collector__know_of_protected_f2ptr(funk2_garbage_collector_t* this, f2ptr exp) {
  int pool_index = this_processor_thread__pool_index();
  int exp__pool_index = __f2ptr__pool_index(exp);
  if (pool_index == exp__pool_index) {
    funk2_garbage_collector_pool__know_of_used_exp_self_protected_f2ptr(&(this->gc_pool[exp__pool_index]), exp);
  } else {
    funk2_garbage_collector_pool__know_of_used_exp_other_protected_f2ptr(&(this->gc_pool[exp__pool_index]), exp);
  }
}

void funk2_garbage_collector__touch_f2ptr(funk2_garbage_collector_t* this, f2ptr exp) {
  int pool_index = __f2ptr__pool_index(exp);
  funk2_garbage_collector_pool__touch_f2ptr(&(this->gc_pool[pool_index]), exp);
}

void funk2_garbage_collector__touch_all_roots(funk2_garbage_collector_t* this) {
  garbage_collector_status("funk2_garbage_collector: touch_all_roots.");
  // this is where we touch everything we want to keep!
  {
    // parallelized
    funk2_user_thread_controller__touch_all_protected_alloc_arrays(&(__funk2.user_thread_controller));
    // serial
    funk2_symbol_hash__touch_all_symbols(&(__funk2.ptypes.symbol_hash), this);
    // serial
    funk2_garbage_collector__touch_never_delete_list(this);
    funk2_garbage_collector__touch_f2ptr(this, funk2_memory__global_environment(&(__funk2.memory))); // touch root environment
  }
}

boolean_t funk2_garbage_collector__still_have_grey_nodes(funk2_garbage_collector_t* this) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    if (funk2_garbage_collector_pool__still_have_grey_nodes(&(this->gc_pool[pool_index]))) {
      return boolean__true;
    }
  }
  return boolean__false;
}

void funk2_garbage_collector__spread_all_blackness(funk2_garbage_collector_t* this) {
  garbage_collector_status("funk2_garbage_collector: spread_all_blackness.");
  u64 cycle_count    = 0;
  while (funk2_garbage_collector__still_have_grey_nodes(this)) {
    garbage_collector_status("funk2_garbage_collector: blackening all grey nodes.  cycle_count=" u64__fstr, cycle_count);
    // parallelized
    funk2_user_thread_controller__blacken_grey_nodes(&(__funk2.user_thread_controller));
    garbage_collector_status("funk2_garbage_collector: greying from other nodes.  cycle_count=" u64__fstr, cycle_count);
    // parallelized
    funk2_user_thread_controller__grey_from_other_nodes(&(__funk2.user_thread_controller));
    cycle_count ++;
  }
  garbage_collector_status("funk2_garbage_collector: done with spread_all_blackness.  cycle_count=" u64__fstr, cycle_count);
}

void funk2_garbage_collector__collect_garbage(funk2_garbage_collector_t* this) {
  garbage_collector_status("funk2_garbage_collector: collect_garbage.");
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_pool__flush_other_knowledge(&(this->gc_pool[pool_index]));
  }
  funk2_garbage_collector__touch_all_roots(this);
  funk2_garbage_collector__spread_all_blackness(this);
  funk2_user_thread_controller__free_white_exps(&(__funk2.user_thread_controller));
  funk2_user_thread_controller__remove_freed_fibers(&(__funk2.user_thread_controller));
  funk2_processor_mutex__lock(&(this->total_garbage_collection_count__mutex));
  this->total_garbage_collection_count ++;
  funk2_processor_mutex__unlock(&(this->total_garbage_collection_count__mutex));
}

u64 funk2_garbage_collector__total_garbage_collection_count(funk2_garbage_collector_t* this) {
  u64 total_count = 0;
  funk2_processor_mutex__lock(&(this->total_garbage_collection_count__mutex));
  total_count = this->total_garbage_collection_count;
  funk2_processor_mutex__unlock(&(this->total_garbage_collection_count__mutex));
  return total_count;
}

f2ptr f2__garbage_collector__total_garbage_collection_count(f2ptr cause) {
  return f2integer__new(cause, funk2_garbage_collector__total_garbage_collection_count(&(__funk2.garbage_collector)));
}
def_pcfunk0(garbage_collector__total_garbage_collection_count,
	    "Returns to total number of times that the garbage collector has collected garbage.",
	    return f2__garbage_collector__total_garbage_collection_count(this_cause));

void funk2_garbage_collector__user_signal_garbage_collect_now(funk2_garbage_collector_t* this) {
  this->user_signal_garbage_collect_now = boolean__true;
}

f2ptr f2__garbage_collector__user_signal_garbage_collect_now(f2ptr cause) {
  funk2_garbage_collector__user_signal_garbage_collect_now(&(__funk2.garbage_collector));
  return nil;
}
def_pcfunk0(garbage_collector__user_signal_garbage_collect_now,
	    "Tells the garbage collector to collect garbage as soon as possible.",
	    return f2__garbage_collector__user_signal_garbage_collect_now(this_cause));

// memory handling thread should never call this function
void funk2_garbage_collector__signal_enter_protected_region(funk2_garbage_collector_t* this, char* source_filename, int source_line_num) {
  int   pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__signal_enter_protected_region(&(this->gc_pool[pool_index]), source_filename, source_line_num);
}

// memory handling thread should never call this function
void funk2_garbage_collector__signal_exit_protected_region(funk2_garbage_collector_t* this, char* source_filename, int source_line_num) {
  int   pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__signal_exit_protected_region(&(this->gc_pool[pool_index]), source_filename, source_line_num);
}

void funk2_garbage_collector__touch_never_delete_list(funk2_garbage_collector_t* this) {
  garbage_collector_status("funk2_garbage_collector: touch_never_delete_list length=" u64__fstr ".", this->never_delete_list.used_num);
  u64 i;
  for (i = 0; i < this->never_delete_list.used_num; i++) {
    funk2_garbage_collector__touch_f2ptr(this, this->never_delete_list.data[i]);
  }
}

f2ptr funk2_garbage_collector__add_f2ptr_to_never_delete_list(funk2_garbage_collector_t* this, f2ptr exp, char* source_filename, int source_line_num) {
  funk2_never_delete_list__add_f2ptr(&(this->never_delete_list), exp);
  return exp;
}

void funk2_garbage_collector__handle(funk2_garbage_collector_t* this) {
  if (funk2_processor_mutex__trylock(&(this->do_collection_mutex)) == 0) {
    boolean_t doing_garbage_collect_now = boolean__false;
    {
      boolean_t should_collect_garbage = boolean__false;
      int index;
      for (index = 0; index < memory_pool_num; index ++) {
	if (this->gc_pool[index].should_run_gc) {
	  should_collect_garbage = boolean__true;
	}
      }
      if (should_collect_garbage && (raw__nanoseconds_since_1970() - this->last_garbage_collect_nanoseconds_since_1970) > (1000000000ull / 8)) {
	doing_garbage_collect_now = boolean__true;
      }
    }
    if (this->user_signal_garbage_collect_now) {
      doing_garbage_collect_now = boolean__true;
    }
    if (doing_garbage_collect_now) {
      garbage_collector_status("funk2_garbage_collector__handle asking all user processor threads to wait_politely so that we can begin collecting garbage.");
      __funk2.user_thread_controller.please_wait = boolean__true;
      funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(__funk2.user_thread_controller));
      garbage_collector_status("");
      garbage_collector_status("**********************************");
      garbage_collector_status("**** DOING GARBAGE COLLECTION ****");
      garbage_collector_status("**********************************");
      garbage_collector_status("");
      {
	int index;
	for (index = 0; index < memory_pool_num; index ++) {
	  garbage_collector_status("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
	}
      }
      funk2_garbage_collector__collect_garbage(this);
      garbage_collector_status("");
      garbage_collector_status("**************************************");
      garbage_collector_status("**** DONE WITH GARBAGE COLLECTION ****");
      garbage_collector_status("**************************************");
      garbage_collector_status("");
      {
	int index;
	for (index = 0; index < memory_pool_num; index ++) {
	  this->gc_pool[index].should_run_gc = boolean__false;
	  garbage_collector_status("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
	}
      }
      this->last_garbage_collect_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
      this->user_signal_garbage_collect_now = boolean__false;
      __funk2.user_thread_controller.please_wait = boolean__false;
    }
    funk2_processor_mutex__unlock(&(this->do_collection_mutex));
  }
}

s64 funk2_garbage_collector__calculate_save_size(funk2_garbage_collector_t* this) {
  s64 save_size = 0;
  save_size += (sizeof(s64) * memory_pool_num);
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      save_size += funk2_garbage_collector_pool__calculate_save_size(&(this->gc_pool[pool_index]));
    }
  }
  save_size += funk2_never_delete_list__calculate_save_size(&(this->never_delete_list));
  return save_size;
}

void* funk2_garbage_collector__save_to_stream__start_thread_create_garbage_collector_pool_buffer(void* garbage_collector_pool_arg) {
  funk2_garbage_collector_pool_t* garbage_collector_pool = (funk2_garbage_collector_pool_t*)garbage_collector_pool_arg;
  {
    funk2_garbage_collector_pool__create_save_buffer(garbage_collector_pool);
    status("done creating garbage collector pool " u64__fstr " save buffer.", garbage_collector_pool->pool_index);
  }
  return NULL;
}


void funk2_garbage_collector__save_to_stream(funk2_garbage_collector_t* this, int fd) {
  status("saving garbage collector to stream %d.", fd);
  {
    s64 garbage_collector_save_size = funk2_garbage_collector__calculate_save_size(this);
    safe_write(fd, to_ptr(&garbage_collector_save_size), sizeof(s64));
    status("garbage collector save size = " s64__fstr ".", garbage_collector_save_size); fflush(stdout);
  }
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      s64 pool_save_size = funk2_garbage_collector_pool__calculate_save_size(&(this->gc_pool[pool_index]));
      safe_write(fd, to_ptr(&pool_save_size), sizeof(s64));
    }
  }
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    }
  }
  status("creating garbage collector save buffers.");
  {
    pthread_t save_gc_pool_thread[memory_pool_num];
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_create(&(save_gc_pool_thread[pool_index]), NULL, &funk2_garbage_collector__save_to_stream__start_thread_create_garbage_collector_pool_buffer, (void*)(&(this->gc_pool[pool_index])));
      }
    }
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_join(save_gc_pool_thread[pool_index], NULL);
      }
    }
  }
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      status("saving garbage collector pool %d buffer to stream %d.", pool_index, fd);
      funk2_garbage_collector_pool__save_buffer_to_stream(&(this->gc_pool[pool_index]), fd);
    }
  }
  status("saving garbage collector never_delete_list to stream %d.", fd);
  funk2_never_delete_list__save_to_stream(&(this->never_delete_list), fd);
  status("saving garbage collector to stream %d done.", fd);
}

void* funk2_garbage_collector__load_from_buffer__start_thread_load_garbage_collector_pool_buffer(void* garbage_collector_pool_arg) {
  funk2_garbage_collector_pool_t* garbage_collector_pool = (funk2_garbage_collector_pool_t*)garbage_collector_pool_arg;
  {
    status("garbage collector buffer_pool_offset=" s64__fstr, (s64)(garbage_collector_pool->temporary_load_buffer_offset));
    s64 pool_load_size = funk2_garbage_collector_pool__load_from_buffer(garbage_collector_pool, (garbage_collector_pool->temporary_load_buffer) + (garbage_collector_pool->temporary_load_buffer_offset));
    if (pool_load_size != (garbage_collector_pool->temporary_load_buffer_size)) {
      status("garbage collector buffer_pool_size mismatch.  pool_load_size=" s64__fstr ", buffer_pool_size=" s64__fstr, (s64)pool_load_size, (s64)(garbage_collector_pool->temporary_load_buffer_size));
      error(nil, "garbage collector pool_load_size mismatch.");
    }
  }
  return NULL;
}

s64 funk2_garbage_collector__load_from_buffer(funk2_garbage_collector_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    s64 offset = 0;
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	s64 pool_save_size;
	memcpy(&pool_save_size, buffer_iter, sizeof(s64)); buffer_iter += sizeof(s64);
	this->gc_pool[pool_index].temporary_load_buffer_size = pool_save_size;
	status("garbage collector buffer_pool_size[" s64__fstr "]=" s64__fstr, (s64)pool_index, (s64)(this->gc_pool[pool_index].temporary_load_buffer_size));
	this->gc_pool[pool_index].temporary_load_buffer_offset = offset;
	offset += pool_save_size;
      }
    }
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	this->gc_pool[pool_index].temporary_load_buffer = buffer_iter;
      }
    }
    {
      pthread_t load_gc_thread[memory_pool_num];
      {
	s64 pool_index;
	for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	  pthread_create(&(load_gc_thread[pool_index]), NULL, &funk2_garbage_collector__load_from_buffer__start_thread_load_garbage_collector_pool_buffer, (void*)(&(this->gc_pool[pool_index])));
	}
      }
      {
	s64 pool_index;
	for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	  pthread_join(load_gc_thread[pool_index], NULL);
	}
      }
    }
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	buffer_iter += (this->gc_pool[pool_index].temporary_load_buffer_size);
      }
    }
  }
  buffer_iter += funk2_never_delete_list__load_from_buffer(&(this->never_delete_list), buffer_iter);
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector__load_from_stream(funk2_garbage_collector_t* this, int fd) {
  s64 garbage_collector_save_size;
  safe_read(fd, to_ptr(&garbage_collector_save_size), sizeof(s64));
  status("garbage collector save size = " s64__fstr ".", garbage_collector_save_size); fflush(stdout);
  this->temporary_load_buffer__length = garbage_collector_save_size;
  this->temporary_load_buffer = (u8*)from_ptr(f2__malloc(this->temporary_load_buffer__length));
  safe_read(fd, to_ptr(this->temporary_load_buffer), this->temporary_load_buffer__length);
  s64 load_length = funk2_garbage_collector__load_from_buffer(this, this->temporary_load_buffer);
  if (load_length != this->temporary_load_buffer__length) {
    status(    "garbage collector load size mismatch: load_length = " s64__fstr ", save_length = " s64__fstr, (s64)load_length, (s64)(this->temporary_load_buffer__length));
    error(nil, "garbage collector load size mismatch.");
  }
  f2__free(to_ptr(this->temporary_load_buffer));
}

void funk2_garbage_collector__defragment__fix_pointers(funk2_garbage_collector_t* this) {
  status("funk2_garbage_collector defragment: fixing pointers.");
  {
    s64 pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_pool__defragment__fix_pointers(&(this->gc_pool[pool_index]));
    }
  }
  funk2_never_delete_list__defragment__fix_pointers(&(this->never_delete_list));
  status("funk2_garbage_collector defragment: fixing pointers done.");
}

// **

void f2__garbage_collector__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_garbage_collector__defragment__fix_pointers(&(__funk2.garbage_collector));
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(garbage_collector__user_signal_garbage_collect_now);
  f2__primcfunk__init__defragment__fix_pointers(garbage_collector__total_garbage_collection_count);
  
}

void f2__garbage_collector__reinitialize_globalvars() {
  f2__primcfunk__init__0(garbage_collector__user_signal_garbage_collect_now);
  f2__primcfunk__init__0(garbage_collector__total_garbage_collection_count);
}

void f2__garbage_collector__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "garbage_collector", "", &f2__garbage_collector__reinitialize_globalvars, &f2__garbage_collector__defragment__fix_pointers);
  
  f2__garbage_collector__reinitialize_globalvars();
}

