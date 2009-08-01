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

// garbage_collector_block_header

void funk2_garbage_collector_block_header__init(funk2_garbage_collector_block_header_t* this) {
  this->tricolor = funk2_garbage_collector_tricolor__grey;
}

void funk2_garbage_collector_block_header__destroy(funk2_garbage_collector_block_header_t* this) {
}


// garbage_collector_set

void funk2_garbage_collector_set__init(funk2_garbage_collector_set_t* this) {
  funk2_set__init(&(this->set));
}

void funk2_garbage_collector_set__destroy(funk2_garbage_collector_set_t* this) {
  funk2_set__destroy(&(this->set));
}

void funk2_garbage_collector_set__add_exp(funk2_garbage_collector_set_t* this, f2ptr exp) {
  funk2_set__add(&(this->set), (funk2_set_element_t)exp);
}

void funk2_garbage_collector_set__remove_exp(funk2_garbage_collector_set_t* this, f2ptr exp) {
  funk2_set__remove(&(this->set), (funk2_set_element_t)exp);
}

void funk2_garbage_collector_set__remove_exp_and_add_to(funk2_garbage_collector_set_t* this, f2ptr exp, funk2_garbage_collector_set_t* to_set) {
  funk2_set__remove_and_add_to(&(this->set), (funk2_set_element_t)exp, &(to_set->set));
}

// garbage_collector_mutation_buffer

void funk2_garbage_collector_mutation_buffer__init(funk2_garbage_collector_mutation_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 1;
  this->data         = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
}

void funk2_garbage_collector_mutation_buffer__destroy(funk2_garbage_collector_mutation_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_mutation_buffer__know_of_mutation(funk2_garbage_collector_mutation_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__user_lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64    old_alloc_length = this->alloc_length;
    f2ptr* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
    memcpy(this->data, old_data, sizeof(f2ptr) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_mutation_buffer__know_of_mutation: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count] = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_mutation_buffer__flush_mutation_knowledge_to_gc_pool(funk2_garbage_collector_mutation_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_mutation(pool, this->data[i]);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}


// garbage_collector_no_more_references_buffer

void funk2_garbage_collector_no_more_references_buffer__init(funk2_garbage_collector_no_more_references_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 1;
  this->data         = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
}

void funk2_garbage_collector_no_more_references_buffer__destroy(funk2_garbage_collector_no_more_references_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(funk2_garbage_collector_no_more_references_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__user_lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64    old_alloc_length = this->alloc_length;
    f2ptr* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
    memcpy(this->data, old_data, sizeof(f2ptr) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count] = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_no_more_references_buffer__flush_no_more_references_knowledge_to_gc_pool(funk2_garbage_collector_no_more_references_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(pool, this->data[i]);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}


// garbage_collector_pool

void funk2_garbage_collector_pool__add_used_exp(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  debug__assert(block->used, nil, "funk2_garbage_collector_pool__add_memblock error: block is not used.");
  switch(block->gc.tricolor) {
  case funk2_garbage_collector_tricolor__black: funk2_garbage_collector_set__add_exp(&(this->black_set), exp); break;
  case funk2_garbage_collector_tricolor__grey:  funk2_garbage_collector_set__add_exp(&(this->grey_set),  exp); break;
  case funk2_garbage_collector_tricolor__white: funk2_garbage_collector_set__add_exp(&(this->white_set), exp); break;
  }
}

void funk2_garbage_collector_pool__remove_unused_exp(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  debug__assert(! block->used, nil, "funk2_garbage_collector_pool__remove_memblock error: block is used.");
  switch(block->gc.tricolor) {
  case funk2_garbage_collector_tricolor__black: funk2_garbage_collector_set__remove_exp(&(this->black_set), exp); break;
  case funk2_garbage_collector_tricolor__grey:  funk2_garbage_collector_set__remove_exp(&(this->grey_set),  exp); break;
  case funk2_garbage_collector_tricolor__white: funk2_garbage_collector_set__remove_exp(&(this->white_set), exp); break;
  }
}

void funk2_garbage_collector_pool__change_used_exp_color(funk2_garbage_collector_pool_t* this, f2ptr exp, funk2_garbage_collector_tricolor_t new_tricolor) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  funk2_garbage_collector_set_t* from_set;
  funk2_garbage_collector_set_t* to_set;
  switch(block->gc.tricolor) {
  case funk2_garbage_collector_tricolor__black: from_set = &(this->black_set); break;
  case funk2_garbage_collector_tricolor__grey:  from_set = &(this->grey_set);  break;
  case funk2_garbage_collector_tricolor__white: from_set = &(this->white_set); break;
  }
  switch(new_tricolor) {
  case funk2_garbage_collector_tricolor__black: to_set = &(this->black_set); break;
  case funk2_garbage_collector_tricolor__grey:  to_set = &(this->grey_set);  break;
  case funk2_garbage_collector_tricolor__white: to_set = &(this->white_set); break;
  }
  { // not thread safe, but don't need to mutex because this is only ever done by the one thread that owns this pool.
    block->gc.tricolor = new_tricolor;
    funk2_garbage_collector_set__remove_exp_and_add_to(from_set, exp, to_set);
  }
}

void funk2_garbage_collector_pool__init_sets_from_memorypool(funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool, u64 pool_index) {
  funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(pool)));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(pool))) + pool->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used) {
      f2ptr exp = ptr_to_f2ptr(pool_index, to_ptr(iter));
      funk2_garbage_collector_pool__add_used_exp(this, exp);
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

void funk2_garbage_collector_pool__init(funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool, u64 pool_index) {
  status("initializing garbage collector pool.");
  
  funk2_garbage_collector_set__init(&(this->black_set));
  funk2_garbage_collector_set__init(&(this->grey_set));
  funk2_garbage_collector_set__init(&(this->white_set));
  funk2_garbage_collector_mutation_buffer__init(&(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__init(&(this->other_no_more_references));
  funk2_protected_alloc_array__init(&(this->protected_alloc_array));
  
  funk2_garbage_collector_pool__init_sets_from_memorypool(this, pool, pool_index);
}

void funk2_garbage_collector_pool__destroy(funk2_garbage_collector_pool_t* this) {
  status("destroying garbage collector pool.");
  
  funk2_garbage_collector_set__destroy(&(this->black_set));
  funk2_garbage_collector_set__destroy(&(this->grey_set));
  funk2_garbage_collector_set__destroy(&(this->white_set));
  funk2_garbage_collector_mutation_buffer__destroy(&(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__destroy(&(this->other_no_more_references));
  funk2_protected_alloc_array__destroy(&(this->protected_alloc_array));
}

void funk2_garbage_collector_pool__add_protected_alloc_f2ptr(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  if (exp) {
    funk2_protected_alloc_array__add_protected_alloc_f2ptr(&(this->protected_alloc_array), exp);
  }
}

void funk2_garbage_collector_pool__signal_enter_protected_region(funk2_garbage_collector_pool_t* this) {
  funk2_protected_alloc_array__signal_enter_protected_region(&(this->protected_alloc_array));
}

void funk2_garbage_collector_pool__signal_exit_protected_region(funk2_garbage_collector_pool_t* this) {
  funk2_protected_alloc_array__signal_exit_protected_region(&(this->protected_alloc_array));
}

boolean_t funk2_garbage_collector_pool__in_protected_region(funk2_garbage_collector_pool_t* this) {
  return funk2_protected_alloc_array__in_protected_region(&(this->protected_alloc_array));
}

void funk2_memorypool__touch_all_protected_alloc_arrays(funk2_garbage_collector_pool_t* this) {
  u64 i;
  for (i = 0; i < this->protected_alloc_array.used_num; i ++) {
    funk2_memorypool__touch_all_referenced_from_f2ptr(this, this->protected_alloc_array.data[i]);
  }
}

void funk2_garbage_collector_pool__know_of_used_exp_self_mutation(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_garbage_collector_tricolor__black) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_garbage_collector_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__know_of_used_exp_other_mutation(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_mutation_buffer__know_of_mutation(&(this->other_mutations), exp);
}

void funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_garbage_collector_tricolor__black) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_garbage_collector_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__know_of_used_exp_other_no_more_references(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references(&(this->other_no_more_references), exp);
}

void funk2_garbage_collector_pool__flush_other_knowledge(funk2_garbage_collector_pool_t* this) {
  funk2_garbage_collector_mutation_buffer__flush_mutation_knowledge_to_gc_pool(&(this->other_mutations), this);
  funk2_garbage_collector_no_more_references_buffer__flush_no_more_references_knowledge_to_gc_pool(&(this->other_no_more_references), this);
}

