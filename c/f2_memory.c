// 
// Copyright (c) 2007-2008 Bo Morgan.
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

void safe_write(int fd, void* ptr, size_t object_size) {
  size_t result = write(fd, ptr, object_size);
  if (result != object_size) {
    error(nil, "safe_write error.");
  }
}

void safe_read(int fd, void* ptr, size_t object_size) {
  size_t result = read(fd, ptr, object_size);
  if (result != object_size) {
    error(nil, "safe_read error.");
  }
}


// funk2_memory

void funk2_memory__init(funk2_memory_t* this) {
  this->global_environment_ptr   = to_ptr(NULL);
  this->global_environment_f2ptr = nil;
  
  this->memory_handling_thread = pthread_self();
  this->bootstrapping_mode     = boolean__true;
  
  funk2_user_thread_controller__init(&(this->user_thread_controller));
  funk2_never_delete_list__init(&(this->never_delete_list));
}

void funk2_memory__destroy(funk2_memory_t* this) {
  funk2_user_thread_controller__destroy(&(this->user_thread_controller));
  funk2_never_delete_list__destroy(&(this->never_delete_list));
}

// memory handling thread should never call this function
void funk2_memory__signal_enter_protected_region(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__signal_enter_protected_region(&(this->pool[pool_index]));
}

// memory handling thread should never call this function
void funk2_memory__signal_exit_protected_region(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__signal_exit_protected_region(&(this->pool[pool_index]));
}

void funk2_memory__handle(funk2_memory_t* this) {
  boolean_t should_collect_garbage    = boolean__false;
  boolean_t should_enlarge_memory_now = boolean__false;
  int index;
  for (index = 0; index < memory_pool_num; index ++) {
    if (this->pool[index].should_enlarge_memory_now) {
      should_enlarge_memory_now = boolean__true;
    }
    if (this->pool[index].should_run_gc) {
      should_collect_garbage = boolean__true;
    }
  }
  if (should_enlarge_memory_now) {
    funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(this->user_thread_controller));
    for (index = 0; index < memory_pool_num; index ++) {
      if (this->pool[index].should_enlarge_memory_now) {
	funk2_memorypool__change_total_memory_available(&(this->pool[index]), this->pool[index].total_global_memory + (this->pool[index].total_global_memory >> 3) + this->pool[index].should_enlarge_memory_now__need_at_least_byte_num);
	this->pool[index].should_enlarge_memory_now__need_at_least_byte_num = 0;
	this->pool[index].should_enlarge_memory_now                         = boolean__false;
      }
    }
    this->user_thread_controller.please_wait = boolean__false;
  }
  if (should_collect_garbage && (raw__nanoseconds_since_1970() - this->last_garbage_collect_nanoseconds_since_1970) > 10 * 1000000000ull) {
    status("funk2_memory__handle asking all user threads to wait_politely so that we can begin collecting garbage.");
    this->user_thread_controller.please_wait = boolean__true;
    funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(this->user_thread_controller));
    status ("");
    status ("**********************************");
    status ("**** DOING GARBAGE COLLECTION ****");
    status ("**********************************");
    status ("");
    for (index = 0; index < memory_pool_num; index ++) {
      if (this->pool[index].should_run_gc) {
	status ("this->pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(this->pool[index].total_global_memory));
      }
    }
    boolean_t did_something = funk2_memory__garbage_collect_generations_until_did_something(this);
    if (did_something) {
      status ("garbage collection did something.");
    } else {
      status ("garbage collection did nothing.");
    }
    for (index = 0; index < memory_pool_num; index ++) {
      if (this->pool[index].should_run_gc) {
	this->pool[index].should_run_gc = boolean__false;
	status ("this->pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(this->pool[index].total_global_memory));
      }
    }
    this->last_garbage_collect_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    this->user_thread_controller.please_wait = boolean__false;
  }
}

void funk2_memory__print_gc_stats(funk2_memory_t* this) {
  int pool_index;
  for(pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
    status("pool[%d].total_global_memory  = " f2size_t__fstr, pool_index, this->pool[pool_index].total_global_memory);
    status("pool[%d].total_free_memory()  = " f2size_t__fstr, pool_index, funk2_memorypool__total_free_memory(&(__funk2.memory.pool[pool_index])));
    status("pool[%d].total_used_memory()  = " f2size_t__fstr, pool_index, funk2_memorypool__total_used_memory(&(__funk2.memory.pool[pool_index])));
    status("pool[%d].next_unique_block_id = %u", pool_index, this->pool[pool_index].next_unique_block_id);
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
}

boolean_t funk2_memory__is_valid_funk2_memblock_ptr(funk2_memory_t* this, ptr p) {
  if (! p) {
    return boolean__true;
  }
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))));
    funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)(from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))))) + (this->pool[pool_index].total_global_memory));
    if (p >= to_ptr(iter) && p < to_ptr(end_of_blocks)) {
      int byte_num;
      while(iter < end_of_blocks) {
	if ((to_ptr(iter)) == p) {return boolean__true;}
	byte_num = funk2_memblock__byte_num(iter);
	//if (byte_num <= 0) {
	//  char str[1024];
	//  sprintf(str, "funk2_memory__is_valid_funk2_memblock_ptr error: byte_num <= 0 (%d).", byte_num);
	//  error(nil, str);
	//}
	iter = (funk2_memblock_t*)(((u8*)iter) + byte_num);
      }
    }
  }
  return boolean__false;
}

ptr funk2_memory__f2ptr_to_ptr__debug(funk2_memory_t* this, f2ptr f2p) {
  computer_id_t  computer_id  = __f2ptr__computer_id(f2p);
  pool_index_t   pool_index   = __f2ptr__pool_index(f2p);
  pool_address_t pool_address = __f2ptr__pool_address(f2p);
  debug__assert(computer_id == 0, nil, "computer_id != 0");
  if (computer_id != 0 || pool_address < 0 || pool_address >= this->pool[pool_index].total_global_memory) {
    printf("\ncomputer_id  = " computer_id__fstr,  computer_id);
    printf("\npool_index   = " pool_index__fstr,   pool_index);
    printf("\npool_address = " pool_address__fstr, pool_address);
    fflush(stdout);
    error(nil, "f2ptr_to_ptr__debug error: received invalid pointer.");
  }
  ptr p = __f2ptr_to_ptr(f2p);
#ifdef DEBUG_MEMORY_VALID_PTRS
  if (p && (! funk2_memory__is_valid_funk2_memblock_ptr(this, p))) {
    char str[1024];
    sprintf(str, "f2ptr_to_ptr__debug error: invalid memblock f2ptr (%d).", (int)f2p);
    error(nil, str);
  }
#endif
  return p;
}

ptr funk2_memory__used_f2ptr_to_ptr__debug(funk2_memory_t* this, f2ptr f2p) {
  computer_id_t  computer_id  = __f2ptr__computer_id(f2p);
  pool_index_t   pool_index   = __f2ptr__pool_index(f2p);
  pool_address_t pool_address = __f2ptr__pool_address(f2p);
  if (computer_id != 0 || pool_address < 0 || pool_address >= this->pool[pool_index].total_global_memory) {
    printf("\ncomputer_id  = " computer_id__fstr,  computer_id);
    printf("\npool_index   = " pool_index__fstr,   pool_index);
    printf("\npool_address = " pool_address__fstr, pool_address);
    fflush(stdout);
    error(nil, "used_f2ptr_to_ptr__debug error: received invalid pointer.");
  }
  ptr p = __f2ptr_to_ptr(f2p);
#ifdef DEBUG_MEMORY_VALID_PTRS
  if (p && (! funk2_memory__is_valid_funk2_memblock_ptr(this, p))) {
    char str[1024];
    sprintf(str, "ptr_to_f2ptr__debug error: invalid memblock f2ptr (%d).", (int)f2p);
    error(nil, str);
  }
#endif
  if (p) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(p);
    if(! block->used) {
      error(nil, "used_f2ptr_to_ptr__debug error: referenced unused memory block.");
    }
  }
  return p;
}

void funk2_memory__touch_never_delete_list(funk2_memory_t* this) {
  u64 i;
  for (i = 0; i < this->never_delete_list.used_num; i++) {
    funk2_memory__touch_all_referenced_from_f2ptr(this, this->never_delete_list.data[i]);
  }
}

f2ptr funk2_memory__add_f2ptr_to_never_delete_list(funk2_memory_t* this, f2ptr exp) {
  funk2_never_delete_list__add_f2ptr(&(this->never_delete_list), exp);
  return exp;
}

boolean_t funk2_memory__garbage_collect_generation(funk2_memory_t* this, int generation_num) {
  status("collecting garbage...");
  funk2_memory__debug_memory_test(this, 1);
  // parallelized
  funk2_user_thread_controller__clear_all_gc_touch_flags_before_generation(&(this->user_thread_controller), generation_num);
  
  // this is where we touch everything we want to keep!
  {
    // parallelized
    funk2_user_thread_controller__touch_all_referenced_from_pool_generation(&(this->user_thread_controller), generation_num);
    // parallelized
    funk2_user_thread_controller__touch_all_protected_alloc_arrays(&(this->user_thread_controller));
    // serial
    funk2_memory__touch_all_symbols(this);
    // serial
    funk2_memory__touch_never_delete_list(this);
  }
  
  // parallelized
  boolean_t did_something = funk2_user_thread_controller__free_all_gc_untouched_blocks_from_generation(&(this->user_thread_controller), generation_num);
#ifdef DEBUG_MEMORY
  {
    funk2_memory__debug_memory_test(this, 1);
  }
#endif // DEBUG_MEMORY
  status("...done collecting garbage.");
  return did_something;
}

boolean_t funk2_memory__garbage_collect_generations_until_did_something(funk2_memory_t* this) {
  boolean_t did_something      = boolean__false;
  int       try_generation_num = 1;
  while (try_generation_num <= maximum_generation_num && (! did_something)) {
    status("funk2_memory__garbage_collect_generations_until_did_something try_generation_num=%d, maximum_generation_num=%d", try_generation_num, maximum_generation_num);
    if (funk2_memory__garbage_collect_generation(&(__funk2.memory), try_generation_num)) {
      did_something = boolean__true;
    }
    try_generation_num ++;
  }
  int index;
  for (index = 0; index < memory_pool_num; index ++) {
    funk2_memorypool__increment_generation(&(__funk2.memory.pool[index]));
  }
  return did_something;
}

ptr funk2_memory__find_or_create_free_splittable_funk2_memblock_and_unfree(funk2_memory_t* this, int pool_index, f2size_t byte_num) {
  ptr block = to_ptr(funk2_memorypool__find_splittable_free_block_and_unfree(&(this->pool[pool_index]), byte_num));
  if (block) {return block;}  
  // If we get here then we failed to allocate enough memory from pool.
  funk2_memory__debug_memory_test(this, 3);
  if (funk2_memorypool__defragment_free_memory_blocks_in_place(&(this->pool[pool_index]))) {
    block = to_ptr(funk2_memorypool__find_splittable_free_block_and_unfree(&(this->pool[pool_index]), byte_num));
    if (block) {return block;}
  }
  this->pool[pool_index].should_run_gc = boolean__true;
  status ("this->pool[%d].total_global_memory = " f2size_t__fstr, pool_index, (f2size_t)(this->pool[pool_index].total_global_memory));
  status ("pool %d new size = " f2size_t__fstr, pool_index, (f2size_t)(this->pool[pool_index].total_global_memory + (this->pool[pool_index].total_global_memory >> 3) + byte_num));
  do {
    this->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num = byte_num;
    this->pool[pool_index].should_enlarge_memory_now                         = boolean__true;
    this->user_thread_controller.please_wait                                 = boolean__true;
    if (pthread_self() == this->memory_handling_thread) {
      if (! this->bootstrapping_mode) {
	funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(this->user_thread_controller));
      }
      funk2_memorypool__change_total_memory_available(&(this->pool[pool_index]), this->pool[pool_index].total_global_memory + (this->pool[pool_index].total_global_memory >> 3) + this->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num);
      this->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num = 0;
      this->pool[pool_index].should_enlarge_memory_now                         = boolean__false;
      this->user_thread_controller.please_wait                                 = boolean__false;
    } else {
      funk2_user_thread_controller__user_wait_politely(&(this->user_thread_controller));
    }
    block = to_ptr(funk2_memorypool__find_splittable_free_block_and_unfree(&(this->pool[pool_index]), byte_num));
    if (block) {return block;}  
    // might need to loop more than once if two requests for memory from memory handling process occur at the same time.
  } while (1);
  // shouldn't get here if we have DYNAMIC_MEMORY defined.  if we are *only* using static_memory then this fails.  however, in distributed systems external memory systems could be asked for memory at this point (REMOTE_MEMORY?).
  printf(  "\nfind_free_memory_for_new_memblock error: shouldn't get here.  byte_num = %u\n", (unsigned int)byte_num);
  error(nil, "find_free_memory_for_new_memblock error: shouldn't get here.\n");
  return to_ptr(NULL);
}

// note that byte_num must be at least sizeof(u8) for ptype! because of type checking in garbage collection
f2ptr funk2_memory__funk2_memblock_f2ptr__try_new(funk2_memory_t* this, int pool_index, f2size_t byte_num) {
#ifdef DEBUG_MEMORY
  if ((! funk2_memorypool__in_protected_region(&(this->pool[pool_index]))) && (! this->bootstrapping_mode)) {
    error(nil, "funk2_memory__funk2_memblock_f2ptr__try_new used without protection outside of bootstrapping mode.");
  }
#endif
  funk2_memory__debug_memory_test(this, 3);
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(funk2_memory__find_or_create_free_splittable_funk2_memblock_and_unfree(this, pool_index, byte_num));
#ifdef DEBUG_MEMORY
  if (block == NULL) {
    status("shouldn't ever get a NULL pointer here.");
    error(nil, "shouldn't ever get a NULL pointer here.");
  }
#endif
  if (funk2_memblock__byte_num(block) > byte_num + sizeof(funk2_memblock_t)) {
    funk2_memblock_t* new_block           = (funk2_memblock_t*)(((u8*)(block)) + byte_num);
    int               new_block__byte_num = funk2_memblock__byte_num(block) - byte_num;
    funk2_memblock__init(new_block, new_block__byte_num, 0, 0);
    
    funk2_memorypool__link_funk2_memblock_to_freelist(&(this->pool[pool_index]), new_block);
    
    funk2_memblock__byte_num(block) = byte_num;
  }
  
  this->pool[pool_index].total_free_memory                    -= funk2_memblock__byte_num(block);
  this->pool[pool_index].total_allocated_memory_since_last_gc += funk2_memblock__byte_num(block);
  if (__funk2.memory.pool[pool_index].total_allocated_memory_since_last_gc >= __funk2.memory.pool[pool_index].total_free_memory) {
    __funk2.memory.pool[pool_index].should_run_gc = boolean__true;
  }
  rbt_tree__insert(&(this->pool[pool_index].used_memory_tree), (rbt_node_t*)block);
  block->used = 1;
  ((ptype_block_t*)block)->ptype = ptype_newly_allocated;
  funk2_memory__debug_memory_test(this, 3);
#ifdef DEBUG_MEMORY
  {
    ptr block_ptr = to_ptr(block);
    s64 check_pool_address = __ptr__pool_address(pool_index, to_ptr(block_ptr));
    if (check_pool_address < 0 || check_pool_address > f2ptr__pool_address__max_value) {
      status("pool_address is out of range, (0 <= " s64__fstr " <= " u64__fstr ").", check_pool_address, f2ptr__pool_address__max_value);
      status("  pool_index = " pool_index__fstr, (pool_index_t)pool_index);
      status("  block_ptr  = " ptr__fstr,        (ptr)block_ptr);
      funk2_memory__print_gc_stats(this);
      error(nil, "pool_address is out of range.");
    }
  }
#endif
  f2ptr block_f2ptr = ptr_to_f2ptr(pool_index, to_ptr(block)); // this should be the only use of ptr_to_f2ptr in the whole program...
#ifdef DEBUG_MEMORY
  {
    u64 check_computer_id  = __f2ptr__computer_id(block_f2ptr);
    if (check_computer_id != 0) {
      status("[ERROR] computer_id must be zero for a local memory allocation.");
      funk2_memory__print_gc_stats(this);
      error(nil, "computer_id must be zero for a local memory allocation.");
    }
    u64 check_pool_index   = __f2ptr__pool_index(block_f2ptr);
    if (check_pool_index > f2ptr__pool_index__max_value) {
      status("[ERROR] pool_index is out of range, (0 <= " u64__fstr " <= " u64__fstr ").", check_pool_index, f2ptr__pool_index__max_value);
      funk2_memory__print_gc_stats(this);
      error(nil, "pool_index is out of range.");
    }
    u64 check_pool_address = __f2ptr__pool_address(block_f2ptr);
    if (check_pool_address > f2ptr__pool_address__max_value) {
      status("[ERROR] pool_address is out of range, (0 <= " u64__fstr " <= " u64__fstr ").", check_pool_address, f2ptr__pool_address__max_value);
      funk2_memory__print_gc_stats(this);
      error(nil, "pool_address is out of range.");
    }
  }
#endif
  if (block_f2ptr) {
    funk2_memorypool__add_protected_alloc_f2ptr(&(this->pool[pool_index]), block_f2ptr);
  }
  return block_f2ptr;
}

f2ptr funk2_memory__funk2_memblock_f2ptr__new_from_pool(funk2_memory_t* this, int pool_index, f2size_t byte_num) {
  while (1) {
    f2ptr funk2_memblock_f2ptr = funk2_memory__funk2_memblock_f2ptr__try_new(this, pool_index, byte_num);
    if (funk2_memblock_f2ptr) {
      return funk2_memblock_f2ptr;
    }
    sched_yield();
    f2__sleep(1);
  }
}

f2ptr funk2_memory__funk2_memblock_f2ptr__new(funk2_memory_t* this, f2size_t byte_num) {
  int pool_index;
  while (1) {
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      f2ptr funk2_memblock_f2ptr = funk2_memory__funk2_memblock_f2ptr__try_new(this, pool_index, byte_num);
      if (funk2_memblock_f2ptr) {
	return funk2_memblock_f2ptr;
      }
    }
    sched_yield();
    f2__sleep(1);
  }
}

void funk2_memory__global_environment__set(funk2_memory_t* this, f2ptr global_environment) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  __funk2.memory.global_environment_f2ptr = global_environment;
  __funk2.memory.global_environment_ptr = raw__f2ptr_to_ptr(global_environment);
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
}

f2ptr funk2_memory__global_environment(funk2_memory_t* this) {
  f2ptr retval;
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  retval = __funk2.memory.global_environment_f2ptr;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
  return retval;
}

boolean_t funk2_memory__save_image_to_file(funk2_memory_t* this, char* filename) {
  status("saving memory image.");
  funk2_memory__print_gc_stats(this);
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  // should collect garbage probably
  int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1) {
    printf("\nsave_image_to_disk error: couldn't open file \"%s\".", filename);
    return boolean__true;
  }
  f2ptr    f2_i;
  f2size_t size_i;
  int      i;
  i = 0xfaded;             safe_write(fd, &i, sizeof(int));
  i = F2__COMPILE_TIME_ID; safe_write(fd, &i, sizeof(int));
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    size_i = this->pool[pool_index].total_global_memory;  safe_write(fd, &size_i, sizeof(f2size_t));
    size_i = this->pool[pool_index].next_unique_block_id; safe_write(fd, &size_i, sizeof(f2size_t));
    safe_write(fd, from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))), this->pool[pool_index].total_global_memory);
  }
  f2_i = this->global_environment_f2ptr; safe_write(fd, &f2_i, sizeof(f2ptr));
  close(fd);
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
  return boolean__false;
}

f2ptr funk2_memory__ptr_to_f2ptr__slow(funk2_memory_t* this, ptr p) {
  if (p == to_ptr(NULL)) {return nil;}
  int i;
  for (i = 0; i < memory_pool_num; i ++) {
    if (p >= funk2_memorypool__memory__ptr(&(this->pool[i])) &&
	p <  funk2_memorypool__memory__ptr(&(this->pool[i])) + this->pool[i].total_global_memory) {
      return f2ptr__new(0, i, ((u8*)from_ptr(p)) - ((u8*)from_ptr(this->pool[i].global_f2ptr_offset)));
    }
  }
  error(nil, "funk2_memory__ptr_to_f2ptr__slow error: p is not in any memory pool.");
}

// precondition: each and every memory pool's global_memory_mutex is locked!
void funk2_memory__rebuild_memory_info_from_image(funk2_memory_t* this) {
  // each and every pool's global_memory_mutex is locked (we need to return that way).
  //
  // note: all memory being locked allows us to assume that we are the
  //       only pthread executing.
  
  int pool_index;
  
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    status("rebuilding memory pool[%d] info from image.", pool_index);
    rbt_tree__init(&(this->pool[pool_index].free_memory_tree), NULL);
    this->pool[pool_index].total_free_memory  = 0;
    rbt_tree__init(&(this->pool[pool_index].used_memory_tree), NULL);
    
    {
      funk2_memblock_t* iter = (funk2_memblock_t*)from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index])));
      funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index])))) + this->pool[pool_index].total_global_memory);
      while(iter < end_of_blocks) {
	debug__assert(funk2_memblock__byte_num(iter) > 0, nil, "memory_test__byte_num_zero failed.");
	if (iter->used) {
	  rbt_tree__insert(&(this->pool[pool_index].used_memory_tree), (rbt_node_t*)iter);
	} else {
	  funk2_memorypool__link_funk2_memblock_to_freelist(&(this->pool[pool_index]), iter);
	  this->pool[pool_index].total_free_memory += funk2_memblock__byte_num(iter);
	}
	iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
      }
      release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
    }
  }
  
  // temporarily unlocks all memory mutexes
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
  // temporary period of all memory mutexes locked
  {
    symbol_hash__reinitialize();
    
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      // add all symbols to symbol_hash in ptypes.c
      rbt_node_t* iter = rbt_tree__minimum(&(this->pool[pool_index].used_memory_tree));
      while(iter) {
	ptype_block_t* block = (ptype_block_t*)iter;
	if(block->ptype == ptype_symbol) {
	  f2ptr block_f2ptr = funk2_memory__ptr_to_f2ptr__slow(this, to_ptr(block));
	  symbol_hash__add_symbol(block_f2ptr);
	}
	iter = rbt_node__next(iter);
      }
    }
    
    funk2_module_registration__reinitialize_all_modules(&(__funk2.module_registration));
  }
  // end temporary unlocking of all memory mutexes
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  
  funk2_memory__debug_memory_test(this, 1);
  
  status("done rebuilding memory info from image."); fflush(stdout);
}

boolean_t funk2_memory__load_image_from_file(funk2_memory_t* this, char* filename) {
  int retval = boolean__false; // success
  status("loading memory image.");
  
  if (! __funk2.memory.bootstrapping_mode) {
    funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(&(__funk2.scheduler_thread_controller));
  }
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  
  
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    status("load_image_from_disk failure: could not open file \"%s\".", filename);
    retval = boolean__true;
  } else {
    while(1) {
      int      i;
      f2ptr    f2_i;
      f2size_t size_i;
      safe_read(fd, &i, sizeof(int));
      if (i != 0xfaded) {
	status("load_image_from_disk failure: file is not a funk memory image.");
	retval = boolean__true;
	break;
      }
      
      safe_read(fd, &i, sizeof(int));
      if (i != F2__COMPILE_TIME_ID) {
	status("load_image_from_disk failure: file is saved from a different version of funk2.");
	retval = boolean__true;
	break;
      }
      
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	safe_read(fd, &size_i, sizeof(f2size_t));
	this->pool[pool_index].total_global_memory = size_i;
	
	safe_read(fd, &size_i, sizeof(f2size_t));
	this->pool[pool_index].next_unique_block_id = size_i;
	
	f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->pool[pool_index].dynamic_memory), sizeof(f2dynamicmemory_t));
	f2dynamicmemory__realloc(&(this->pool[pool_index].dynamic_memory), &old_dynamic_memory, this->pool[pool_index].total_global_memory);
	safe_read(fd, from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))), this->pool[pool_index].total_global_memory);
      }
      
      safe_read(fd, &f2_i, sizeof(f2ptr));
      f2ptr global_environment_f2ptr = f2_i;
      
      status("done loading memory image."); fflush(stdout);
      
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	this->pool[pool_index].global_f2ptr_offset = to_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))) - 1;
      }
      
      this->global_environment_f2ptr = global_environment_f2ptr;
      this->global_environment_ptr   = raw__f2ptr_to_ptr(global_environment_f2ptr);
      
      funk2_memory__rebuild_memory_info_from_image(this);
      
      status("loaded memory image successfully.");
      break;
    }
    close(fd);      
  }
  
  if (! __funk2.memory.bootstrapping_mode) {
    funk2_scheduler_thread_controller__let_scheduler_threads_continue(&(__funk2.scheduler_thread_controller));  
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(this->pool[pool_index]));
  }
  
  funk2_memory__print_gc_stats(this);
  return retval;
}

void funk2_memory__touch_all_referenced_from_f2ptr(funk2_memory_t* this, f2ptr exp) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__touch_all_referenced_from_f2ptr(&(this->pool[pool_index]), exp);
}

boolean_t funk2_memory__check_all_memory_pointers_valid(funk2_memory_t* this) {
  boolean_t found_invalid = boolean__false;
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    status("scanning pool %d for invalid memory pointers.", pool_index);
    found_invalid |= funk2_memorypool__check_all_memory_pointers_valid_in_memory(&(this->pool[pool_index]), this);
  }
  return found_invalid;
}

void funk2_memory__memory_test(funk2_memory_t* this) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_test(&(this->pool[pool_index]));
  }
  funk2_memory__check_all_memory_pointers_valid(this);
}

// **

void f2__memory__initialize() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__init((&__funk2.memory.pool[pool_index]));
  }
  
  funk2_memory__debug_memory_test(&(__funk2.memory), 1);
}

void f2__memory__destroy() {
  funk2_memory__debug_memory_test(&(__funk2.memory), 1);
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__destroy(&(__funk2.memory.pool[pool_index]));
  }
}



