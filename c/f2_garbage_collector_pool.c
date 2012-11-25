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

// garbage_collector_mutation_buffer

void funk2_garbage_collector_mutation_buffer__init(funk2_garbage_collector_mutation_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 16ull * 1024 * 1024;
  this->data         = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
}

void funk2_garbage_collector_mutation_buffer__destroy(funk2_garbage_collector_mutation_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_mutation_buffer__know_of_mutation(funk2_garbage_collector_mutation_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64      old_alloc_length = this->alloc_length;
    f2ptr_t* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
    memcpy(this->data, old_data, sizeof(f2ptr_t) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_mutation_buffer__know_of_mutation: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count].data = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_mutation_buffer__flush_mutation_knowledge_to_gc_pool(funk2_garbage_collector_mutation_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_mutation(pool, this->data[i].data);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}

s64 funk2_garbage_collector_mutation_buffer__calculate_save_size(funk2_garbage_collector_mutation_buffer_t* this) {
  s64 save_size = 0;
  {
    u64 count = this->count;
    save_size += sizeof(count);
    save_size += (sizeof(f2ptr_t) * count);
  }
  return save_size;
}

void funk2_garbage_collector_mutation_buffer__save_to_stream(funk2_garbage_collector_mutation_buffer_t* this, int fd) {
  u64 count = this->count;
  safe_write(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp; exp.data = this->data[index].data;
    safe_write(fd, to_ptr(&exp), sizeof(exp));
  }
}

u64 funk2_garbage_collector_mutation_buffer__save_to_buffer(funk2_garbage_collector_mutation_buffer_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  {
    u64 count = this->count;
    memcpy(buffer, &count, sizeof(count)); buffer += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp; exp.data = this->data[index].data;
      memcpy(buffer, &exp, sizeof(exp)); buffer += sizeof(exp);
    }
  }
  return (buffer - initial_buffer);
}

void funk2_garbage_collector_mutation_buffer__load_from_stream(funk2_garbage_collector_mutation_buffer_t* this, int fd) {
  u64 count;
  safe_read(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp;
    safe_read(fd, to_ptr(&exp), sizeof(exp));
    funk2_garbage_collector_mutation_buffer__know_of_mutation(this, exp.data);
  }
}

s64 funk2_garbage_collector_mutation_buffer__load_from_buffer(funk2_garbage_collector_mutation_buffer_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 count;
    memcpy(&count, buffer_iter, sizeof(count)); buffer_iter += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp;
      memcpy(&exp, buffer_iter, sizeof(exp)); buffer_iter += sizeof(exp);
      funk2_garbage_collector_mutation_buffer__know_of_mutation(this, exp.data);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector_mutation_buffer__defragment__fix_pointers(funk2_garbage_collector_mutation_buffer_t* this) {
  u64 count = this->count;
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr exp = this->data[index].data;
    defragment__fix_pointer(exp);
    this->data[index].data = exp;
  }
}


// garbage_collector_no_more_references_buffer

void funk2_garbage_collector_no_more_references_buffer__init(funk2_garbage_collector_no_more_references_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 1024 * 1024;
  this->data         = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
}

void funk2_garbage_collector_no_more_references_buffer__destroy(funk2_garbage_collector_no_more_references_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(funk2_garbage_collector_no_more_references_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64      old_alloc_length = this->alloc_length;
    f2ptr_t* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
    memcpy(this->data, old_data, sizeof(f2ptr_t) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count].data = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_no_more_references_buffer__flush_no_more_references_knowledge_to_gc_pool(funk2_garbage_collector_no_more_references_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(pool, this->data[i].data);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}

s64 funk2_garbage_collector_no_more_references_buffer__calculate_save_size(funk2_garbage_collector_no_more_references_buffer_t* this) {
  s64 save_size = 0;
  {
    u64 count = this->count;
    save_size += sizeof(count);
    save_size += (sizeof(f2ptr_t) * count);
  }
  return save_size;
}

void funk2_garbage_collector_no_more_references_buffer__save_to_stream(funk2_garbage_collector_no_more_references_buffer_t* this, int fd) {
  u64 count = this->count;
  safe_write(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp; exp.data = this->data[index].data;
    safe_write(fd, to_ptr(&exp), sizeof(exp));
  }
}

u64 funk2_garbage_collector_no_more_references_buffer__save_to_buffer(funk2_garbage_collector_no_more_references_buffer_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  {
    u64 count = this->count;
    //safe_write(fd, to_ptr(&count), sizeof(count));
    memcpy(buffer, &count, sizeof(count)); buffer += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp; exp.data = this->data[index].data;
      //safe_write(fd, to_ptr(&exp), sizeof(exp));
      memcpy(buffer, &exp, sizeof(exp)); buffer += sizeof(exp);
    }
  }
  return (buffer - initial_buffer);
}

void funk2_garbage_collector_no_more_references_buffer__load_from_stream(funk2_garbage_collector_no_more_references_buffer_t* this, int fd) {
  u64 count;
  safe_read(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp;
    safe_read(fd, to_ptr(&exp), sizeof(exp));
    funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(this, exp.data);
  }
}

s64 funk2_garbage_collector_no_more_references_buffer__load_from_buffer(funk2_garbage_collector_no_more_references_buffer_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 count;
    memcpy(&count, buffer_iter, sizeof(count)); buffer_iter += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp;
      memcpy(&exp, buffer_iter, sizeof(exp)); buffer_iter += sizeof(exp);
      funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(this, exp.data);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector_no_more_references_buffer__defragment__fix_pointers(funk2_garbage_collector_no_more_references_buffer_t* this) {
  u64 count = this->count;
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr exp = this->data[index].data;
    defragment__fix_pointer(exp);
    this->data[index].data = exp;
  }
}


// garbage_collector_protected_f2ptr_buffer

void funk2_garbage_collector_protected_f2ptr_buffer__init(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 1024 * 1024;
  this->data         = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
}

void funk2_garbage_collector_protected_f2ptr_buffer__destroy(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr(funk2_garbage_collector_protected_f2ptr_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64      old_alloc_length = this->alloc_length;
    f2ptr_t* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
    memcpy(this->data, old_data, sizeof(f2ptr_t) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count].data = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_protected_f2ptr_buffer__flush_protected_f2ptr_knowledge_to_gc_pool(funk2_garbage_collector_protected_f2ptr_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_protected_f2ptr(pool, this->data[i].data);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}

s64 funk2_garbage_collector_protected_f2ptr_buffer__calculate_save_size(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  s64 save_size = 0;
  {
    u64 count = this->count;
    save_size += sizeof(count);
    save_size += (sizeof(f2ptr_t) * count);
  }
  return save_size;
}

void funk2_garbage_collector_protected_f2ptr_buffer__save_to_stream(funk2_garbage_collector_protected_f2ptr_buffer_t* this, int fd) {
  u64 count = this->count;
  safe_write(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp; exp.data = this->data[index].data;
    safe_write(fd, to_ptr(&exp), sizeof(exp));
  }
}

u64 funk2_garbage_collector_protected_f2ptr_buffer__save_to_buffer(funk2_garbage_collector_protected_f2ptr_buffer_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  {
    u64 count = this->count;
    //safe_write(fd, to_ptr(&count), sizeof(count));
    memcpy(buffer, &count, sizeof(count)); buffer += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp; exp.data = this->data[index].data;
      //safe_write(fd, to_ptr(&exp), sizeof(exp));
      memcpy(buffer, &exp, sizeof(exp)); buffer += sizeof(exp);
    }
  }
  return (buffer - initial_buffer);
}

void funk2_garbage_collector_protected_f2ptr_buffer__load_from_stream(funk2_garbage_collector_protected_f2ptr_buffer_t* this, int fd) {
  u64 count;
  safe_read(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp;
    safe_read(fd, to_ptr(&exp), sizeof(exp));
    funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr(this, exp.data);
  }
}

s64 funk2_garbage_collector_protected_f2ptr_buffer__load_from_buffer(funk2_garbage_collector_protected_f2ptr_buffer_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 count;
    memcpy(&count, buffer_iter, sizeof(count)); buffer_iter += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp;
      memcpy(&exp, buffer_iter, sizeof(exp)); buffer_iter += sizeof(exp);
      funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr(this, exp.data);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector_protected_f2ptr_buffer__defragment__fix_pointers(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  u64 count = this->count;
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr exp = this->data[index].data;
    defragment__fix_pointer(exp);
    this->data[index].data = exp;
  }
}


// garbage_collector_other_grey_buffer

void funk2_garbage_collector_other_grey_buffer__init(funk2_garbage_collector_other_grey_buffer_t* this) {
  this->count        = 0;
  this->alloc_length = 1024 * 1024;
  this->data         = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
}

void funk2_garbage_collector_other_grey_buffer__destroy(funk2_garbage_collector_other_grey_buffer_t* this) {
  free(this->data);
}

void funk2_garbage_collector_other_grey_buffer__know_of_other_grey(funk2_garbage_collector_other_grey_buffer_t* this, f2ptr exp) {
  if (this->count == this->alloc_length) {
    u64      old_alloc_length = this->alloc_length;
    f2ptr_t* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * this->alloc_length));
    memcpy(this->data, old_data, sizeof(f2ptr_t) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_other_grey_buffer__know_of_protected_f2ptr: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count].data = exp;
  this->count ++;
}

void funk2_garbage_collector_other_grey_buffer__flush_other_greys(funk2_garbage_collector_other_grey_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  int pool_index = this_processor_thread__pool_index();
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__grey_element(pool, pool_index, this->data[i].data);
  }
  this->count = 0;
}

s64 funk2_garbage_collector_other_grey_buffer__calculate_save_size(funk2_garbage_collector_other_grey_buffer_t* this) {
  s64 save_size = 0;
  {
    u64 count = this->count;
    save_size += sizeof(count);
    save_size += (sizeof(f2ptr_t) * count);
  }
  return save_size;
}

void funk2_garbage_collector_other_grey_buffer__save_to_stream(funk2_garbage_collector_other_grey_buffer_t* this, int fd) {
  u64 count = this->count;
  safe_write(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp; exp.data = this->data[index].data;
    safe_write(fd, to_ptr(&exp), sizeof(exp));
  }
}

u64 funk2_garbage_collector_other_grey_buffer__save_to_buffer(funk2_garbage_collector_other_grey_buffer_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  {
    u64 count = this->count;
    //safe_write(fd, to_ptr(&count), sizeof(count));
    memcpy(buffer, &count, sizeof(count)); buffer += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp; exp.data = this->data[index].data;
      //safe_write(fd, to_ptr(&exp), sizeof(exp));
      memcpy(buffer, &exp, sizeof(exp)); buffer += sizeof(exp);
    }
  }
  return (buffer - initial_buffer);
}

void funk2_garbage_collector_other_grey_buffer__load_from_stream(funk2_garbage_collector_other_grey_buffer_t* this, int fd) {
  u64 count;
  safe_read(fd, to_ptr(&count), sizeof(count));
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr_t exp;
    safe_read(fd, to_ptr(&exp), sizeof(exp));
    funk2_garbage_collector_other_grey_buffer__know_of_other_grey(this, exp.data);
  }
}

s64 funk2_garbage_collector_other_grey_buffer__load_from_buffer(funk2_garbage_collector_other_grey_buffer_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 count;
    memcpy(&count, buffer_iter, sizeof(count)); buffer_iter += sizeof(count);
    u64 index;
    for (index = 0; index < count; index ++) {
      f2ptr_t exp;
      memcpy(&exp, buffer_iter, sizeof(exp)); buffer_iter += sizeof(exp);
      funk2_garbage_collector_other_grey_buffer__know_of_other_grey(this, exp.data);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector_other_grey_buffer__defragment__fix_pointers(funk2_garbage_collector_other_grey_buffer_t* this) {
  u64 count = this->count;
  u64 index;
  for (index = 0; index < count; index ++) {
    f2ptr exp = this->data[index].data;
    defragment__fix_pointer(exp);
    this->data[index].data = exp;
  }
}

// garbage_collector_pool

void funk2_garbage_collector_pool__init(funk2_garbage_collector_pool_t* this, u64 this__pool_index) {
  status("initializing garbage collector pool.");
  
  this->pool_index = this__pool_index;
  funk2_tricolor_set__init(&(this->tricolor_set));
  funk2_garbage_collector_mutation_buffer__init(&(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__init(&(this->other_no_more_references));
  funk2_garbage_collector_protected_f2ptr_buffer__init(&(this->other_protected_f2ptr));
  funk2_protected_alloc_array_fiber_hash__init(&(this->protected_alloc_array_fiber_hash));
  this->should_run_gc = boolean__false;
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_other_grey_buffer__init(&(this->other_grey_buffer[pool_index]));
    }
  }
}

void funk2_garbage_collector_pool__destroy(funk2_garbage_collector_pool_t* this) {
  status("destroying garbage collector pool.");
  
  funk2_tricolor_set__destroy(&(this->tricolor_set));
  funk2_garbage_collector_mutation_buffer__destroy(&(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__destroy(&(this->other_no_more_references));
  funk2_garbage_collector_protected_f2ptr_buffer__destroy(&(this->other_protected_f2ptr));
  funk2_protected_alloc_array_fiber_hash__destroy(&(this->protected_alloc_array_fiber_hash));
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_other_grey_buffer__destroy(&(this->other_grey_buffer[pool_index]));
    }
  }
}

void funk2_garbage_collector_pool__add_used_exp(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  debug__assert(block->used, nil, "funk2_garbage_collector_pool__add_memblock error: block is not used.");
  funk2_tricolor_set__add_element(&(this->tricolor_set), exp, block->gc.tricolor);
}

void funk2_garbage_collector_pool__remove_unused_exp(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  debug__assert(! block->used, nil, "funk2_garbage_collector_pool__remove_memblock error: block is used.");
  funk2_tricolor_set__remove_element(&(this->tricolor_set), exp, block->gc.tricolor);
}

void funk2_garbage_collector_pool__change_used_exp_color(funk2_garbage_collector_pool_t* this, f2ptr exp, funk2_tricolor_t to_tricolor) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (! block->used) {
    status("funk2_garbage_collector_pool__change_used_exp_color fatal error: found reference to unused element (" f2ptr__fstr ") (" u64__fstr ").", exp, (u64)exp);
    error(nil, "funk2_garbage_collector_pool__change_used_exp_color fatal error: found reference to unused element.");
  }
  funk2_tricolor_t from_tricolor = block->gc.tricolor;
  // not processor_thread safe, but don't need to mutex because this is only ever done by the one processor thread that owns this pool.
  funk2_tricolor_set__change_element_color(&(this->tricolor_set), exp, from_tricolor, to_tricolor);
  block->gc.tricolor = to_tricolor;
}

void funk2_garbage_collector_pool__init_sets_from_memorypool(funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool, u64 pool_index) {
  funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(pool->dynamic_memory.ptr));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(pool->dynamic_memory.ptr)) + pool->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used) {
      f2ptr exp = ptr_to_f2ptr(pool_index, to_ptr(iter));
      funk2_garbage_collector_pool__add_used_exp(this, exp);
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

boolean_t funk2_garbage_collector_pool__still_have_grey_nodes(funk2_garbage_collector_pool_t* this) {
  return (funk2_tricolor_set__grey_set__element_count(&(this->tricolor_set)) != 0);
}

void funk2_garbage_collector_pool__add_protected_alloc_f2ptr(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  if (exp) {
    f2ptr fiber = nil;
    {
      s64 try_pool_index = this_processor_thread__try_get_pool_index();
      if (try_pool_index != -1) {
	fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(try_pool_index);
      }
    }
    funk2_protected_alloc_array_fiber_hash__add_protected_alloc_f2ptr(&(this->protected_alloc_array_fiber_hash), fiber, exp);
  }
}

void funk2_garbage_collector_pool__signal_enter_protected_region(funk2_garbage_collector_pool_t* this, char* source_filename, int source_line_num) {
  f2ptr fiber = nil;
  {
    s64 try_pool_index = this_processor_thread__try_get_pool_index();
    if (try_pool_index != -1) {
      fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(try_pool_index);
    }
  }
  funk2_protected_alloc_array_fiber_hash__signal_enter_protected_region(&(this->protected_alloc_array_fiber_hash), fiber, source_filename, source_line_num);
}

void funk2_garbage_collector_pool__signal_exit_protected_region(funk2_garbage_collector_pool_t* this, char* source_filename, int source_line_num) {
  f2ptr fiber = nil;
  {
    s64 try_pool_index = this_processor_thread__try_get_pool_index();
    if (try_pool_index != -1) {
      fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(try_pool_index);
    }
  }
  funk2_protected_alloc_array_fiber_hash__signal_exit_protected_region(&(this->protected_alloc_array_fiber_hash), fiber, source_filename, source_line_num);
}

boolean_t funk2_garbage_collector_pool__in_protected_region(funk2_garbage_collector_pool_t* this) {
  f2ptr fiber = nil;
  {
    s64 try_pool_index = this_processor_thread__try_get_pool_index();
    if (try_pool_index != -1) {
      fiber = raw__global_scheduler__try_get_processor_thread_current_fiber(try_pool_index);
    }
  }
  return funk2_protected_alloc_array_fiber_hash__in_protected_region(&(this->protected_alloc_array_fiber_hash), fiber);
}

void funk2_garbage_collector_pool__touch_f2ptr(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_tricolor__white) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__touch_all_protected_alloc_arrays(funk2_garbage_collector_pool_t* this) {
  funk2_protected_alloc_array_fiber_hash__touch_all(&(this->protected_alloc_array_fiber_hash), this);
}

void funk2_garbage_collector_pool__know_of_used_exp_self_mutation(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_tricolor__black) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__know_of_used_exp_other_mutation(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_mutation_buffer__know_of_mutation(&(this->other_mutations), exp);
}

void debug__tried_to_free_with_references() {
  status(  "warning: tried to free block with references.");
  //printf("\nwarning: tried to free block with references.");
}

void funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  //if (atomic_read(&(block->reference_count)) == 0) { // double check...
  if (block->gc.tricolor == funk2_tricolor__black) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_tricolor__grey);
  }
  //} else {
  //  debug__tried_to_free_with_references();
  //}
}

void funk2_garbage_collector_pool__know_of_used_exp_other_no_more_references(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(&(this->other_no_more_references), exp);
}

void funk2_garbage_collector_pool__know_of_used_exp_self_protected_f2ptr( funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_pool__add_protected_alloc_f2ptr(this, exp);
}

void funk2_garbage_collector_pool__know_of_used_exp_other_protected_f2ptr(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr(&(this->other_protected_f2ptr), exp);
}

void funk2_garbage_collector_pool__flush_other_knowledge(funk2_garbage_collector_pool_t* this) {
  funk2_garbage_collector_mutation_buffer__flush_mutation_knowledge_to_gc_pool(&(this->other_mutations), this);
  funk2_garbage_collector_no_more_references_buffer__flush_no_more_references_knowledge_to_gc_pool(&(this->other_no_more_references), this);
  funk2_garbage_collector_protected_f2ptr_buffer__flush_protected_f2ptr_knowledge_to_gc_pool(&(this->other_protected_f2ptr), this);
}

void funk2_garbage_collector_pool__grey_element(funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_tricolor__white) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__grey_maybe_other_element(funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp) {
  if (exp) {
    int exp__pool_index = __f2ptr__pool_index(exp);
    if (exp__pool_index == pool_index) {
      funk2_garbage_collector_pool__grey_element(this, pool_index, exp);
    } else {
      funk2_garbage_collector_other_grey_buffer__know_of_other_grey(&(__funk2.garbage_collector.gc_pool[exp__pool_index].other_grey_buffer[pool_index]), exp);
    }
  }
}

void funk2_garbage_collector_pool__grey_referenced_elements_from_dptr(funk2_garbage_collector_pool_t* this, int pool_index, funk2_dptr_t* dptr) {
  funk2_dptr__grey_referenced_elements(dptr, this, pool_index);
}

void funk2_garbage_collector_pool__grey_referenced_elements(funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp) {
  ptype_block_t* block = (ptype_block_t*)from_ptr(__f2ptr_to_ptr(exp));
  {
    f2ptr cause = block->cause;
    if (cause != nil) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, cause);
    }
  }
  {
    f2ptr creation_fiber = block->creation_fiber;
    if (creation_fiber != nil) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, creation_fiber);
    }
  }
  switch(block->block.ptype) {
  case ptype_free_memory: error(nil, "block of type free_memory in garbage collector.");
  case ptype_integer:                  return;
  case ptype_double:                   return;
  case ptype_float:                    return;
  case ptype_pointer:                  return;
  case ptype_cmutex:                   return;
  case ptype_creadwritelock:           return;
  case ptype_char:                     return;
  case ptype_string:                   return;
  case ptype_symbol:                   return;
  case ptype_chunk:                    return;
  case ptype_simple_array: {
    s64 i;
    f2ptr_t* iter = ((ptype_simple_array_block_t*)block)->slot;
    for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, iter->data);
      iter ++;
    }
  } return;
  case ptype_traced_array: {
    s64 i;
    funk2_dptr_t* iter = (funk2_dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
    for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
      funk2_garbage_collector_pool__grey_referenced_elements_from_dptr(this, pool_index, iter);
      iter ++;
    }
  } return;
  case ptype_larva: {
    f2ptr bug = ((ptype_larva_block_t*)block)->bug;
    if (bug) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, bug);
    }
  } return;
  case ptype_mutable_array_pointer: {
    f2ptr array = ((ptype_mutable_array_pointer_block_t*)block)->array;
    if (array) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, array);
    }
  } return;
  default:
    {
      char str[1024];
      sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(block->block.ptype));
      error(nil, str);
    }
  }
}

void funk2_garbage_collector_pool__blacken_grey_nodes__helper(f2ptr element, void** user_data, boolean_t* stop, void** return_value) {
  f2ptr_t*                        grey_array = (f2ptr_t*)(user_data[0]);
  u64*                            grey_index = (u64*)(user_data[1]);
  f2ptr                           exp        = (f2ptr)element;
  grey_array[*grey_index].data = exp;
  (*grey_index) ++;
}

void funk2_garbage_collector_pool__blacken_grey_nodes(funk2_garbage_collector_pool_t* this) {
  //status("funk2_garbage_collector_pool: blacken_grey_nodes.");
  while (funk2_garbage_collector_pool__still_have_grey_nodes(this)) {
    int      pool_index = this_processor_thread__pool_index();
    u64      grey_count = funk2_tricolor_set__grey_set__element_count(&(this->tricolor_set));
    f2ptr_t* grey_array = (f2ptr_t*)from_ptr(f2__malloc(sizeof(f2ptr_t) * grey_count));
    u64      grey_index = 0;
    {
      void** user_data = (void**)alloca(sizeof(void*) * 2);
      user_data[0] = (void*)grey_array;
      user_data[1] = (void*)(&grey_index);
      funk2_tricolor_set__grey_set__mapc(&(this->tricolor_set), &funk2_garbage_collector_pool__blacken_grey_nodes__helper, user_data);
      debug__assert(grey_index == grey_count, nil, "error grey_index should equal grey_count.");
    }
    for (grey_index = 0; grey_index < grey_count; grey_index ++) {
      f2ptr exp = grey_array[grey_index].data;
      funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_tricolor__black);
      funk2_garbage_collector_pool__grey_referenced_elements(this, pool_index, exp);
    }
    free(grey_array);
  }
}

void funk2_garbage_collector_pool__grey_from_other_nodes(funk2_garbage_collector_pool_t* this) {
  //status("funk2_garbage_collector_pool: grey_from_other_nodes.");
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_other_grey_buffer__flush_other_greys(&(this->other_grey_buffer[pool_index]), this);
  }
}

void funk2_garbage_collector_pool__free_white_exps__helper(f2ptr element, void** user_data, boolean_t* stop, void** return_value) {
  f2ptr                           exp              =   (f2ptr)                          element;
  funk2_garbage_collector_pool_t* this             =   (funk2_garbage_collector_pool_t*)(user_data[0]);
  int                             pool_index       = *((int*)                           (user_data[1]));
  u64*                            freed_byte_count =   (u64*)                           (user_data[2]);
  {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
    (*freed_byte_count) += funk2_memblock__byte_num(block);
    funk2_tricolor_set__remove_element(&(this->tricolor_set), exp, funk2_tricolor__white);
    funk2_memorypool__free_used_block(&(__funk2.memory.pool[pool_index]), block);
  }
}

void funk2_garbage_collector_pool__free_white_exps(funk2_garbage_collector_pool_t* this) {
  int pool_index       = this_processor_thread__pool_index();
  u64 freed_byte_count = 0;
  {
    void** user_data = (void**)alloca(sizeof(void*) * 3);
    user_data[0]     = (void*)this;
    user_data[1]     = (void*)(&pool_index);
    user_data[2]     = (void*)(&freed_byte_count);
    funk2_tricolor_set__white_set__mapc(&(this->tricolor_set), &funk2_garbage_collector_pool__free_white_exps__helper, user_data);
  }
  garbage_collector_status("funk2_garbage_collector_pool: free white blocks pool_index=" u64__fstr " freed_byte_count=" u64__fstr ".", (u64)this_processor_thread__pool_index(), freed_byte_count);
}

s64 funk2_garbage_collector_pool__calculate_save_size(funk2_garbage_collector_pool_t* this) {
  s64 save_size = 0;
  {
    save_size += funk2_tricolor_set__calculate_save_size(&(this->tricolor_set));
    save_size += funk2_garbage_collector_mutation_buffer__calculate_save_size(&(this->other_mutations));
    save_size += funk2_garbage_collector_no_more_references_buffer__calculate_save_size(&(this->other_no_more_references));
    save_size += funk2_garbage_collector_protected_f2ptr_buffer__calculate_save_size(&(this->other_protected_f2ptr));
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      save_size += funk2_garbage_collector_other_grey_buffer__calculate_save_size(&(this->other_grey_buffer[pool_index]));
    }
  }
  return save_size;
}

void funk2_garbage_collector_pool__save_to_stream(funk2_garbage_collector_pool_t* this, int fd) {
  funk2_tricolor_set__save_to_stream(&(this->tricolor_set), fd);
  funk2_garbage_collector_mutation_buffer__save_to_stream(&(this->other_mutations), fd);
  funk2_garbage_collector_no_more_references_buffer__save_to_stream(&(this->other_no_more_references), fd);
  funk2_garbage_collector_protected_f2ptr_buffer__save_to_stream(&(this->other_protected_f2ptr), fd);
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_other_grey_buffer__save_to_stream(&(this->other_grey_buffer[pool_index]), fd);
  }
}

u64 funk2_garbage_collector_pool__save_to_buffer(funk2_garbage_collector_pool_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  buffer += funk2_tricolor_set__save_to_buffer(&(this->tricolor_set), buffer);
  buffer += funk2_garbage_collector_mutation_buffer__save_to_buffer(&(this->other_mutations), buffer);
  buffer += funk2_garbage_collector_no_more_references_buffer__save_to_buffer(&(this->other_no_more_references), buffer);
  buffer += funk2_garbage_collector_protected_f2ptr_buffer__save_to_buffer(&(this->other_protected_f2ptr), buffer);
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    buffer += funk2_garbage_collector_other_grey_buffer__save_to_buffer(&(this->other_grey_buffer[pool_index]), buffer);
  }
  return (buffer - initial_buffer);
}

void funk2_garbage_collector_pool__create_save_buffer(funk2_garbage_collector_pool_t* this) {
  this->temporary_save_buffer_size = funk2_garbage_collector_pool__calculate_save_size(this);
  this->temporary_save_buffer = (u8*)from_ptr(f2__malloc(this->temporary_save_buffer_size));
  u64 bytes_used = funk2_garbage_collector_pool__save_to_buffer(this, this->temporary_save_buffer);
  if (bytes_used != this->temporary_save_buffer_size) {
    error(nil, "funk2_garbage_collector_pool__create_save_buffer: (bytes_used != this->temporary_save_buffer_size)");
  }
}

void funk2_garbage_collector_pool__save_buffer_to_stream(funk2_garbage_collector_pool_t* this, int fd) {
  safe_write(fd, to_ptr(this->temporary_save_buffer), this->temporary_save_buffer_size);
  f2__free(to_ptr(this->temporary_save_buffer));
  this->temporary_save_buffer_size = 0;
  this->temporary_save_buffer      = NULL;
}

void funk2_garbage_collector_pool__load_from_stream(funk2_garbage_collector_pool_t* this, int fd) {
  funk2_tricolor_set__load_from_stream(&(this->tricolor_set), fd);
  funk2_garbage_collector_mutation_buffer__load_from_stream(&(this->other_mutations), fd);
  funk2_garbage_collector_no_more_references_buffer__load_from_stream(&(this->other_no_more_references), fd);
  funk2_garbage_collector_protected_f2ptr_buffer__load_from_stream(&(this->other_protected_f2ptr), fd);
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_garbage_collector_other_grey_buffer__load_from_stream(&(this->other_grey_buffer[pool_index]), fd);
  }
}

s64 funk2_garbage_collector_pool__load_from_buffer(funk2_garbage_collector_pool_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    buffer_iter += funk2_tricolor_set__load_from_buffer(                               &(this->tricolor_set),             buffer_iter);
    buffer_iter += funk2_garbage_collector_mutation_buffer__load_from_buffer(          &(this->other_mutations),          buffer_iter);
    buffer_iter += funk2_garbage_collector_no_more_references_buffer__load_from_buffer(&(this->other_no_more_references), buffer_iter);
    buffer_iter += funk2_garbage_collector_protected_f2ptr_buffer__load_from_buffer(   &(this->other_protected_f2ptr),    buffer_iter);
    {
      int pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	buffer_iter += funk2_garbage_collector_other_grey_buffer__load_from_buffer(&(this->other_grey_buffer[pool_index]), buffer_iter);
      }
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_garbage_collector_pool__defragment__fix_pointers(funk2_garbage_collector_pool_t* this) {
  status("funk2_garbage_collector_pool[" u64__fstr "] defragment: fixing pointers.", this->pool_index);
  funk2_tricolor_set__defragment__fix_pointers(                               &(this->tricolor_set));
  funk2_garbage_collector_mutation_buffer__defragment__fix_pointers(          &(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__defragment__fix_pointers(&(this->other_no_more_references));
  funk2_garbage_collector_protected_f2ptr_buffer__defragment__fix_pointers(   &(this->other_protected_f2ptr));
  funk2_protected_alloc_array_fiber_hash__defragment__fix_pointers(           &(this->protected_alloc_array_fiber_hash));
  {
    u64 pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_other_grey_buffer__defragment__fix_pointers(&(this->other_grey_buffer[pool_index]));
    }
  }
  status("funk2_garbage_collector_pool[" u64__fstr "] defragment: fixing pointers done.", this->pool_index);
}

boolean_t funk2_garbage_collector_pool__memblock_color_is_valid(funk2_garbage_collector_pool_t* this, funk2_memblock_t* memblock) {
  if (memblock->used) {
    f2ptr            memblock_f2ptr    = __ptr_to_f2ptr(this->pool_index, to_ptr(memblock));
    funk2_tricolor_t memblock_tricolor = memblock->gc.tricolor;
    funk2_tricolor_t gc_tricolor       = funk2_tricolor_set__element_color(&(this->tricolor_set), memblock_f2ptr);
    if (memblock_tricolor != gc_tricolor) {
      status("funk2_garbage_collector_pool__memblock_color_is_valid assertion invalid: memblock_tricolor (" u64__fstr ") != gc_tricolor (" u64__fstr ").", (u64)memblock_tricolor, (u64)gc_tricolor);
      error(nil, "funk2_garbage_collector_pool__memblock_color_is_valid assertion invalid: memblock_tricolor != gc_tricolor.");
      return boolean__false;
    }
  }
  return boolean__true;
}

