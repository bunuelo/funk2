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

// funk2_memblock

void funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, boolean_t used) {
  funk2_memblock__byte_num(block) = byte_num;
  funk2_garbage_collector_block_header__init(&(block->gc));
  atomic_set(&(block->reference_count), 0);
  block->used                     = used;
}


boolean_t funk2_memblock__check_all_memory_pointers_valid_in_memory(funk2_memblock_t* this, funk2_memory_t* memory) {
  if (! this) {
    return boolean__false;
  }
  
  if (this->used) {
    ptype_block_t* block = (ptype_block_t*)this;
    switch(block->block.ptype) {
    case ptype_free_memory:              error(nil, "block of type free_memory in garbage collector.");
    case ptype_integer:                  return boolean__false;
    case ptype_double:                   return boolean__false;
    case ptype_float:                    return boolean__false;
    case ptype_pointer:                  return boolean__false;
    case ptype_cmutex:                   return boolean__false;
    case ptype_creadwritelock:           return boolean__false;
    case ptype_char:                     return boolean__false;
    case ptype_string:                   return boolean__false;
    case ptype_symbol:                   return boolean__false;
    case ptype_chunk:                    return boolean__false;
    case ptype_simple_array: {
      boolean_t found_invalid = boolean__false;
      s64 i;
      f2ptr_t* iter = ((ptype_simple_array_block_t*)block)->slot;
      for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
	if (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(iter->data))) {
	  found_invalid = boolean__true;
	  error(nil, "found invalid f2ptr in simple_array.");
	}
	iter ++;
      }
      return found_invalid;
    }
    case ptype_larva:
      // should check bug is reasonably valid.
      return boolean__false;
    case ptype_mutable_array_pointer:
      // should check array is reasonably valid.
      return boolean__false;
    default:
      {
	char str[1024];
	sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(block->block.ptype));
	error(nil, str);
      }
    }
  }
  return boolean__false;
}

boolean_t funk2_memblock__is_self_consistently_valid(funk2_memblock_t* this) {
  if (! this) {
    return boolean__true;
  }
  if (this->used) {
    ptype_block_t* ptype_block = (ptype_block_t*)this;
    switch(ptype_block->block.ptype) {
    case ptype_free_memory:
    case ptype_newly_allocated:
    case ptype_integer:
    case ptype_double:
    case ptype_float:
    case ptype_pointer:
    case ptype_cmutex:
    case ptype_creadwritelock:
    case ptype_char:
    case ptype_string:
    case ptype_symbol:
    case ptype_chunk:
    case ptype_simple_array:
    case ptype_larva:
    case ptype_mutable_array_pointer:
      break;
    default: {
      status("unknown type (%ld) of block (%ld) in debugging funk2_memorypool memory test.", (long)(ptype_block->block.ptype), (long)ptype_block);
      return boolean__false;
    } break;
    }
  }
  return boolean__true;
}

void funk2_memblock__decrement_reference_count(funk2_memblock_t* this, f2ptr this_f2ptr, funk2_garbage_collector_t* garbage_collector) {
  if (this_f2ptr != nil) {
    boolean_t no_more_references = atomic_dec_and_test(&(this->reference_count));
    if (no_more_references) {
      // notify garbage collector to whiten old value if it is not already because it has no references (because of no references it doesn't upset the no black references white invariant).
      funk2_garbage_collector__know_of_no_more_references(garbage_collector, this_f2ptr);
    }
  } else {
    debug__assert(! this, nil, "funk2_memblock__decrement_reference_count error: this should be NULL if this_f2ptr is nil.");
  }
}

