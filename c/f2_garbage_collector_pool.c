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


// garbage_collector_protected_f2ptr_buffer

void funk2_garbage_collector_protected_f2ptr_buffer__init(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->count        = 0;
  this->alloc_length = 1;
  this->data         = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
}

void funk2_garbage_collector_protected_f2ptr_buffer__destroy(funk2_garbage_collector_protected_f2ptr_buffer_t* this) {
  funk2_processor_mutex__destroy(&(this->mutex));
  free(this->data);
}

void funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr(funk2_garbage_collector_protected_f2ptr_buffer_t* this, f2ptr exp) {
  funk2_processor_mutex__user_lock(&(this->mutex));
  if (this->count == this->alloc_length) {
    u64    old_alloc_length = this->alloc_length;
    f2ptr* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
    memcpy(this->data, old_data, sizeof(f2ptr) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_protected_f2ptr_buffer__know_of_protected_f2ptr: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count] = exp;
  this->count ++;
  funk2_processor_mutex__unlock(&(this->mutex));
}

void funk2_garbage_collector_protected_f2ptr_buffer__flush_protected_f2ptr_knowledge_to_gc_pool(funk2_garbage_collector_protected_f2ptr_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  funk2_processor_mutex__lock(&(this->mutex));
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__know_of_used_exp_self_protected_f2ptr(pool, this->data[i]);
  }
  this->count = 0;
  funk2_processor_mutex__unlock(&(this->mutex));
}


// garbage_collector_other_grey_buffer

void funk2_garbage_collector_other_grey_buffer__init(funk2_garbage_collector_other_grey_buffer_t* this) {
  this->count        = 0;
  this->alloc_length = 1;
  this->data         = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
}

void funk2_garbage_collector_other_grey_buffer__destroy(funk2_garbage_collector_other_grey_buffer_t* this) {
  free(this->data);
}

void funk2_garbage_collector_other_grey_buffer__know_of_other_grey(funk2_garbage_collector_other_grey_buffer_t* this, f2ptr exp) {
  if (this->count == this->alloc_length) {
    u64    old_alloc_length = this->alloc_length;
    f2ptr* old_data         = this->data;
    this->alloc_length = 2 * old_alloc_length;
    this->data = (f2ptr*)f2__malloc(sizeof(f2ptr) * this->alloc_length);
    memcpy(this->data, old_data, sizeof(f2ptr) * old_alloc_length);
    free(old_data);
    status("funk2_garbage_collector_other_grey_buffer__know_of_protected_f2ptr: doubled buffer size from " u64__fstr " to " u64__fstr ".", old_alloc_length, this->alloc_length);
  }
  this->data[this->count] = exp;
  this->count ++;
}

void funk2_garbage_collector_other_grey_buffer__flush_other_greys(funk2_garbage_collector_other_grey_buffer_t* this, funk2_garbage_collector_pool_t* pool) {
  int pool_index = this_processor_thread__pool_index();
  u64 i;
  for (i = 0; i < this->count; i ++) {
    funk2_garbage_collector_pool__grey_element(pool, pool_index, this->data[i]);
  }
  this->count = 0;
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
  funk2_garbage_collector_protected_f2ptr_buffer__init(&(this->other_protected_f2ptr));
  funk2_protected_alloc_array__init(&(this->protected_alloc_array));
  this->should_run_gc = boolean__false;
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_other_grey_buffer__init(&(this->other_grey_buffer[pool_index]));
    }
  }
  funk2_garbage_collector_pool__init_sets_from_memorypool(this, pool, pool_index);
}

void funk2_garbage_collector_pool__destroy(funk2_garbage_collector_pool_t* this) {
  status("destroying garbage collector pool.");
  
  funk2_garbage_collector_set__destroy(&(this->black_set));
  funk2_garbage_collector_set__destroy(&(this->grey_set));
  funk2_garbage_collector_set__destroy(&(this->white_set));
  funk2_garbage_collector_mutation_buffer__destroy(&(this->other_mutations));
  funk2_garbage_collector_no_more_references_buffer__destroy(&(this->other_no_more_references));
  funk2_garbage_collector_protected_f2ptr_buffer__destroy(&(this->other_protected_f2ptr));
  funk2_protected_alloc_array__destroy(&(this->protected_alloc_array));
  {
    int pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_garbage_collector_other_grey_buffer__destroy(&(this->other_grey_buffer[pool_index]));
    }
  }
}

boolean_t funk2_garbage_collector_pool__still_have_grey_nodes(funk2_garbage_collector_pool_t* this) {
  return ((this->grey_set.set.element_count) != 0);
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

void funk2_garbage_collector_pool__touch_f2ptr(funk2_garbage_collector_pool_t* this, f2ptr exp) {
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (block->gc.tricolor == funk2_garbage_collector_tricolor__white) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_garbage_collector_tricolor__grey);
  }
}

void funk2_garbage_collector_pool__touch_all_protected_alloc_arrays(funk2_garbage_collector_pool_t* this) {
  status("funk2_garbage_collector_pool: touch_all_protected_alloc_arrays.");
  u64 i;
  for (i = 0; i < this->protected_alloc_array.used_num; i ++) {
    funk2_garbage_collector_pool__touch_f2ptr(this, this->protected_alloc_array.data[i]);
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
  if (block->gc.tricolor == funk2_garbage_collector_tricolor__white) {
    funk2_garbage_collector_pool__change_used_exp_color(this, exp, funk2_garbage_collector_tricolor__grey);
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
  funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, dptr->p);
  funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, dptr->tracing_on);
  funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, dptr->trace);
  funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, dptr->imagination_frame);
}

void funk2_garbage_collector_pool__grey_referenced_elements(funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp) {
  ptype_block_t* block = (ptype_block_t*)from_ptr(__f2ptr_to_ptr(exp));
  switch(block->ptype) {
  case ptype_free_memory:  error(nil, "block of type free_memory in garbage collector.");
  case ptype_integer:      return;
  case ptype_double:       return;
  case ptype_float:        return;
  case ptype_pointer:      return;
  case ptype_gfunkptr:     return;
  case ptype_mutex:        return;
  case ptype_char:         return;
  case ptype_string:       return;
  case ptype_symbol:       return;
  case ptype_chunk:        return;
  case ptype_simple_array: {
    s64 i;
    f2ptr* iter = (f2ptr*)((ptype_simple_array_block_t*)block)->f2ptr_data;
    for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
      funk2_garbage_collector_pool__grey_maybe_other_element(this, pool_index, *iter);
      iter ++;
    }
  } return;
  case ptype_traced_array: {
    s64 i;
    funk2_dptr_t* iter = (funk2_dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
    for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
      funk2_garbage_collector_pool__grey_referenced_element_from_dptr(this, pool_index, iter);
      iter ++;
    }
  } return;
  case ptype_larva:        return;
  default:
    {
      char str[1024];
      sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(block->ptype));
      error(nil, str);
    }
  }
}

void funk2_garbage_collector_pool__blacken_grey_nodes(funk2_garbage_collector_pool_t* this) {
  int pool_index = this_processor_thread__pool_index();
  u64                bin_num = 1ull << this->grey_set.set.bin_power;
  funk2_set_node_t** bin     = this->grey_set.set.bin;
  u64 i;
  for (i = 0; i < bin_num; i ++) {
    funk2_set_node_t* iter = bin[i];
    while (iter) {
      funk2_garbage_collector_pool__change_used_exp_color(this, (f2ptr)(iter->element), funk2_garbage_collector_tricolor__black);
      funk2_garbage_collector_pool__grey_referenced_elements(this, pool_index, );
    }
  }
}

void funk2_garbage_collector_pool__grey_from_other_nodes(funk2_garbage_collector_pool_t* this) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index) {
    funk2_garbage_collector_other_grey_buffer__flush_other_greys(&(this->other_grey_buffer[pool_index]), this);
  }
}

