#include "funk2.h"

// funk2_memblock

void funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, int used) {
  funk2_memblock__byte_num(block) = byte_num;
  funk2_garbage_collector_block_header__init(&(block->gc));
  block->used                     = used;
  //block->gc_touch                 = gc_touch;
  //block->generation_num           = 0;
}

boolean_t funk2_memblock__check_all_memory_pointers_valid_in_memory(funk2_memblock_t* this, funk2_memory_t* memory) {
  if (! this) {
    return boolean__false;
  }
  
  if (this->used) {
    ptype_block_t* block = (ptype_block_t*)this;
    switch(block->ptype) {
    case ptype_free_memory:  error(nil, "block of type free_memory in garbage collector.");
    case ptype_integer:      return boolean__false;
    case ptype_double:       return boolean__false;
    case ptype_float:        return boolean__false;
    case ptype_pointer:      return boolean__false;
    case ptype_gfunkptr:     return boolean__false;
    case ptype_mutex:        return boolean__false;
    case ptype_char:         return boolean__false;
    case ptype_string:       return boolean__false;
    case ptype_symbol:       return boolean__false;
    case ptype_chunk:        return boolean__false;
    case ptype_simple_array: {
      boolean_t found_invalid = boolean__false;
      s64 i;
      f2ptr* iter = (f2ptr*)((ptype_simple_array_block_t*)block)->f2ptr_data;
      for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
	if (! funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr(memory, __f2ptr_to_ptr(*iter))) {
	  found_invalid = boolean__true;
	  error(nil, "found invalid f2ptr in simple_array.");
	}
	iter ++;
      }
      return found_invalid;
    }
    case ptype_traced_array: {
      boolean_t found_invalid = boolean__false;
      s64 i;
      funk2_dptr_t* iter = (funk2_dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
      for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
	found_invalid |= funk2_dptr__check_all_memory_pointers_valid_in_memory(iter, memory);
	iter ++;
      }
      return found_invalid;
    }
    case ptype_larva:        return boolean__false;
    default:
      {
	char str[1024];
	sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(block->ptype));
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
    switch(ptype_block->ptype) {
    case ptype_free_memory:
    case ptype_newly_allocated:
    case ptype_integer:
    case ptype_double:
    case ptype_float:
    case ptype_pointer:
    case ptype_gfunkptr:
    case ptype_mutex:
    case ptype_char:
    case ptype_string:
    case ptype_symbol:
    case ptype_chunk:
    case ptype_simple_array:
    case ptype_traced_array:
    case ptype_larva:
      break;
    default: {
      status("unknown type (%ld) of block (%ld) in debugging funk2_memorypool memory test.", (long)(ptype_block->ptype), (long)ptype_block);
      return boolean__false;
    } break;
    }
  }
  return boolean__true;
}

void funk2_memblock__decrement_reference_count(funk2_memblock_t* this, f2ptr this_f2ptr, funk2_garbage_collector_t* garbage_collector) {
  boolean_t no_more_references = atomic_dec_and_test(&(this->reference_count));
  if (no_more_references) {
    // notify garbage collector to whiten old value if it is not already because it has no references (because of no references it doesn't upset the no black references white invariant).
    funk2_garbage_collector__know_of_no_more_references(garbage_collector, this_f2ptr);
  }
}

