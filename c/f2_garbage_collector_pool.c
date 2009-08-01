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
  this->tricolor = funk2_garbage_collector_tricolor__white;
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

void funk2_garbage_collector_set__add_block(funk2_garbage_collector_set_t* this, funk2_memblock_t* block) {
  funk2_set__add(&(this->set), (funk2_set_element_t)to_ptr(block));
}

void funk2_garbage_collector_set__remove_block(funk2_garbage_collector_set_t* this, funk2_memblock_t* block) {
  funk2_set__remove(&(this->set), (funk2_set_element_t)to_ptr(block));
}

// garbage_collector_pool

void funk2_garbage_collector_pool__init_sets_from_memblock(funk2_garbage_collector_pool_t* this, funk2_memblock_t* block) {
  if (block->used) {
    switch(block->gc.tricolor) {
    case funk2_garbage_collector_tricolor__black: funk2_garbage_collector_set__add_block(&(this->black_set), block); break;
    case funk2_garbage_collector_tricolor__grey:  funk2_garbage_collector_set__add_block(&(this->grey_set),  block); break;
    case funk2_garbage_collector_tricolor__white: funk2_garbage_collector_set__add_block(&(this->white_set), block); break;
    }
  }
}

void funk2_garbage_collector_pool__init_sets_from_memorypool(funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool) {
  funk2_memblock_t*   iter          = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(pool)));
  funk2_memblock_t*   end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(pool))) + pool->total_global_memory);
  while(iter < end_of_blocks) {
    funk2_garbage_collector__init_sets_from_memblock(this, iter);
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

void funk2_garbage_collector_pool__init(funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool) {
  status("initializing garbage collector pool.");
  
  funk2_garbage_collector_set__init(&(this->black_set));
  funk2_garbage_collector_set__init(&(this->grey_set));
  funk2_garbage_collector_set__init(&(this->white_set));
  
  funk2_garbage_collector__init_sets_from_memorypool(this, pool);
}

void funk2_garbage_collector_pool__destroy(funk2_garbage_collector_pool_t* this) {
  status("destroying garbage collector pool.");
  
  funk2_garbage_collector_set__destroy(&(this->black_set));
  funk2_garbage_collector_set__destroy(&(this->grey_set));
  funk2_garbage_collector_set__destroy(&(this->white_set));
}

