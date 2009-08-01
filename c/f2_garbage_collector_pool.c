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
  
  funk2_garbage_collector_pool__init_sets_from_memorypool(this, pool, pool_index);
}

void funk2_garbage_collector_pool__destroy(funk2_garbage_collector_pool_t* this) {
  status("destroying garbage collector pool.");
  
  funk2_garbage_collector_set__destroy(&(this->black_set));
  funk2_garbage_collector_set__destroy(&(this->grey_set));
  funk2_garbage_collector_set__destroy(&(this->white_set));
}

