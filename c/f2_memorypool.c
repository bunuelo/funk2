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

// funk2_memorypool

void funk2_memorypool__init(funk2_memorypool_t* this) {
  funk2_processor_mutex__init(&(this->global_memory_allocate_mutex));
  this->should_run_gc                        = boolean__false;
  this->should_enlarge_memory_now            = boolean__false;
  this->total_allocated_memory_since_last_gc = 0;
  this->next_unique_block_id                 = 0;
  this->total_global_memory = sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY;
  f2dynamicmemory__init_and_alloc(&(this->dynamic_memory), sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY);
  
  this->total_free_memory = this->total_global_memory;
  
  this->global_f2ptr_offset = to_ptr(funk2_memorypool__memory__ptr(this) - 1);
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(funk2_memorypool__memory__ptr(this));
  funk2_memblock__init(block, this->total_global_memory, 0, 0);
  
  rbt_tree__init(&(this->free_memory_tree), NULL);
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
  rbt_tree__init(&(this->used_memory_tree), NULL);
  funk2_protected_alloc_array__init(&(this->protected_alloc_array));
  funk2_gc_touch_circle_buffer__init(&(this->gc_touch_circle_buffer));
}

void funk2_memorypool__destroy(funk2_memorypool_t* this) {
  funk2_gc_touch_circle_buffer__destroy(&(this->gc_touch_circle_buffer));
  funk2_protected_alloc_array__destroy(&(this->protected_alloc_array));
  f2dynamicmemory__destroy_and_free(&(this->dynamic_memory));
}

void funk2_memorypool__add_protected_alloc_f2ptr(funk2_memorypool_t* this, f2ptr exp) {
  funk2_protected_alloc_array__add_protected_alloc_f2ptr(&(this->protected_alloc_array), exp);
}

void funk2_memorypool__signal_enter_protected_region(funk2_memorypool_t* this) {
  funk2_protected_alloc_array__signal_enter_protected_region(&(this->protected_alloc_array));
}

void funk2_memorypool__signal_exit_protected_region(funk2_memorypool_t* this) {
  funk2_protected_alloc_array__signal_exit_protected_region(&(this->protected_alloc_array));
}

boolean_t funk2_memorypool__in_protected_region(funk2_memorypool_t* this) {
  return funk2_protected_alloc_array__in_protected_region(&(this->protected_alloc_array));
}

f2size_t funk2_memorypool__total_used_memory(funk2_memorypool_t* this) {
  f2size_t used_memory_count = 0;
  rbt_node_t* node = rbt_tree__minimum(&(this->used_memory_tree));
  while(node) {
    used_memory_count += funk2_memblock__byte_num((funk2_memblock_t*)node);
    node = rbt_node__next(node);
  }
  //printf("\ntotal used memory = %d", used_memory_count); fflush(stdout);
  return used_memory_count;
}

f2size_t funk2_memorypool__total_free_memory(funk2_memorypool_t* this) {
  f2size_t free_memory_count = 0;
  rbt_node_t* node = rbt_tree__minimum(&(this->free_memory_tree));
  while(node) {
    free_memory_count += funk2_memblock__byte_num((funk2_memblock_t*)node);
    node = rbt_node__next(node);
  }
  //printf("\ntotal free memory = %d", free_memory_count); fflush(stdout);
  return free_memory_count;
}

void funk2_memorypool__memory_test__dynamic_memory(funk2_memorypool_t* this) {
  release__assert(this->dynamic_memory.byte_num == this->total_global_memory, nil, "funk2_memorypool__memory_test__dynamic_memory: (this->dynamic_memory.byte_num == this->total_global_memory) failed.");
}

void funk2_memorypool__memory_test__byte_num_zero(funk2_memorypool_t* this) {
  funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(this)));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(this))) + this->total_global_memory);
  while(iter < end_of_blocks) {
    release__assert(funk2_memblock__byte_num(iter) > 0, nil, "memory_test__byte_num_zero failed.");
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
}

void funk2_memorypool__memory_test__all_known_types(funk2_memorypool_t* this) {
  funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(this)));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(this))) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used) {
      ptype_block_t* ptype_block = (ptype_block_t*)iter;
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
      default:
	{
	  char str[1024];
	  sprintf(str, "unknown type (%ld) of block (%ld) in debugging funk2_memorypool memory test.", (long)(ptype_block->ptype), (long)ptype_block);
	  release__assert(0, nil, str);
	}
      }
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

void funk2_memorypool__memory_test(funk2_memorypool_t* this) {
  status("testing memory in pool...");
  status("  pool.total_free_memory = " f2size_t__fstr, this->total_free_memory); fflush(stdout);
  status("  total_free_memory(%d) = " f2size_t__fstr, funk2_memorypool__total_free_memory(this)); fflush(stdout);
  release__assert(funk2_memorypool__total_free_memory(this) == this->total_free_memory, nil, "funk2_memorypool__memory_test (funk2_memorypool__total_free_memory(this) == this->total_free_memory) failure.");
  release__assert_and_on_failure((int)(funk2_memorypool__total_used_memory(this) + funk2_memorypool__total_free_memory(this)) == (int)this->total_global_memory,
				 nil,
				 "funk2_memorypool__memory_test (funk2_memorypool__total_used_memory(this) + funk2_memorypool__total_free_memory(this) != this->total_global_memory) failure.",
      {
	int used_memory_num = funk2_memorypool__total_used_memory(this);
	int free_memory_num = funk2_memorypool__total_free_memory(this);
	printf("\ntotal_used_memory                       = %d", (int)used_memory_num);
	printf("\ntotal_free_memory                       = %d", (int)free_memory_num);
	printf("\ntotal_used_memory + total_free_memory() = %d", (int)free_memory_num + used_memory_num);
	printf("\nthis->total_global_memory               = %d", (int)this->total_global_memory);
	fflush(stdout);
      });
  funk2_memorypool__memory_test__dynamic_memory(this);
  funk2_memorypool__memory_test__byte_num_zero(this);
  funk2_memorypool__memory_test__all_known_types(this);
  {
    rbt_node_t* free_iter = rbt_tree__minimum(&(this->free_memory_tree));
    // this should lock up if there is a loop in free list.
    while (free_iter) {
      free_iter = rbt_node__next(free_iter);
    }
  }
}

void funk2_memorypool__change_total_memory_available(funk2_memorypool_t* this, f2size_t byte_num) {
  if(((u64)byte_num) > ((u64)f2ptr__pool_address__max_value)) {
    status("funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed ((u64)byte_num) > ((u64)f2ptr__pool_address__max_value), ((u64)" u64__fstr ") > ((u64)" u64__fstr ").",
	   ((u64)byte_num), ((u64)f2ptr__pool_address__max_value));
    error(nil, "funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed (are you using a 32 bit version still?).");
  }
  status("funk2_memorypool__change_total_memory_available(" f2size_t__fstr ")", byte_num); fflush(stdout);
  if (byte_num == this->total_global_memory) {return;}
  f2size_t         old_total_global_memory      = this->total_global_memory;
  f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
  f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, byte_num);
  this->global_f2ptr_offset = this->dynamic_memory.ptr - 1;
  this->total_global_memory = byte_num;
  if (this->dynamic_memory.ptr != old_dynamic_memory.ptr) {
    // need to fix pointers (globals, funk2_memblock__next(block))
    s64 byte_diff = (s64)(this->dynamic_memory.ptr - old_dynamic_memory.ptr);
    if (this->used_memory_tree.head)  {this->used_memory_tree.head = (rbt_node_t*)(((u8*)this->used_memory_tree.head) + byte_diff);}
    if (this->free_memory_tree.head)  {this->free_memory_tree.head = (rbt_node_t*)(((u8*)this->free_memory_tree.head) + byte_diff);}
    if (__funk2.memory.global_environment_ptr >= old_dynamic_memory.ptr &&
	__funk2.memory.global_environment_ptr <  old_dynamic_memory.ptr + old_total_global_memory) {
      if (__funk2.memory.global_environment_ptr) {__funk2.memory.global_environment_ptr = __funk2.memory.global_environment_ptr + byte_diff;}
    }
    funk2_memblock_t* iter = from_ptr(this->dynamic_memory.ptr);
    funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + old_total_global_memory);
    funk2_memblock_t* last = NULL;
    while(iter < end_of_blocks) {
      if (iter->rbt_node.parent) {iter->rbt_node.parent = (rbt_node_t*)(((u8*)(iter->rbt_node.parent) + byte_diff));}
      if (iter->rbt_node.left)   {iter->rbt_node.left   = (rbt_node_t*)(((u8*)(iter->rbt_node.left)   + byte_diff));}
      if (iter->rbt_node.right)  {iter->rbt_node.right  = (rbt_node_t*)(((u8*)(iter->rbt_node.right)  + byte_diff));}
      last = iter;
      iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
    }
    if (last->used) {
      release__assert(byte_num > old_total_global_memory, nil, "(byte_num > old_total_global_memory) because defragment was just called and there is still used memory at end.");
      funk2_memblock__byte_num(iter) = (byte_num - old_total_global_memory);
      iter->used     = 0;
      iter->gc_touch = 0;
      status("funk2_memorypool__change_total_memory_available: created new block with size funk2_memblock__byte_num(last) = " f2size_t__fstr, funk2_memblock__byte_num(iter));
      rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)iter);
      release__assert(funk2_memblock__byte_num(iter) > 0, nil, "(funk2_memblock__byte_num(iter) >= 0) should be enough free space to reduce memory block.");
    } else {
      rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)last);
      funk2_memblock__byte_num(last) += (byte_num - old_total_global_memory);
      rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)last);
      status("funk2_memorypool__change_total_memory_available: increased last block size to funk2_memblock__byte_num(last) = " f2size_t__fstr, funk2_memblock__byte_num(last));
      release__assert(funk2_memblock__byte_num(last) > 0, nil, "(funk2_memblock__byte_num(last) >= 0) should be enough free space to reduce memory block.");
    }
  } else {
    if (byte_num > old_total_global_memory) {
      funk2_memblock_t* block = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + old_total_global_memory);
      funk2_memblock__byte_num(block) = (byte_num - old_total_global_memory);
      block->used     = 0;
      block->gc_touch = 0;
      rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
      release__assert(funk2_memblock__byte_num(block) > 0, nil, "(funk2_memblock__byte_num(block) > 0) should be enough free space to reduce memory block.");
    } else {
      release__assert(0, nil, "funk2_memorypool__change_total_memory_available error: not implemented yet.");
    }
  }
  this->total_free_memory += (byte_num - old_total_global_memory);
  funk2_memorypool__debug_memory_test(this, 2);
}

void funk2_memorypool__clear_all_gc_touch_flags_before_generation(funk2_memorypool_t* this, int generation_num) {
  //status("funk2_memorypool__clear_all_gc_touch_flags_before_generation: generation_num=%d.", generation_num);
  funk2_memorypool__debug_memory_test(this, 3);
  rbt_node_t* iter = rbt_tree__minimum(&(this->used_memory_tree));
  while (iter) {
    if(((funk2_memblock_t*)iter)->generation_num < generation_num) {
      ((funk2_memblock_t*)iter)->gc_touch = 0;
    }
    iter = rbt_node__next(iter);
  }
  funk2_memorypool__debug_memory_test(this, 3);
}

void funk2_memorypool__link_funk2_memblock_to_freelist(funk2_memorypool_t* this, funk2_memblock_t* block) {
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
}

u8 funk2_memorypool__defragment_free_memory_blocks_in_place(funk2_memorypool_t* this) {
  funk2_memorypool__debug_memory_test(this, 2);
  status("defragmenting funk2_memorypool");
  u8 did_something = 0;
  funk2_memblock_t* iter = (funk2_memblock_t*)from_ptr(funk2_memorypool__memory__ptr(this));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(this))) + this->total_global_memory);
  funk2_memblock_t* segment_first_free_block = NULL;
  rbt_tree__init(&(this->free_memory_tree), NULL);
  while(iter < end_of_blocks) {
    if (segment_first_free_block) {
      // we are currently in a segment of free blocks
      if (iter->used) {
	// we are no longer in a segment of free blocks
	segment_first_free_block = NULL;
      } else {
	// we should combine this free block with the others in this segment
	rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)segment_first_free_block);
	funk2_memblock__byte_num(segment_first_free_block) += funk2_memblock__byte_num(iter);
	rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)segment_first_free_block);
	iter = segment_first_free_block;
	// set did_something flag
	did_something = 1;
      }
    } else {
      if (! iter->used) {
	segment_first_free_block = iter;
	funk2_memorypool__link_funk2_memblock_to_freelist(this, iter);
      }
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "failed.");
  funk2_memorypool__debug_memory_test(this, 2);
  return did_something;
}

u8 funk2_memorypool__free_all_gc_untouched_blocks_from_generation(funk2_memorypool_t* this, int generation_num) {
  //status("funk2_memorypool__free_all_gc_untouched_blocks_from_generation: generation_num=%d.", generation_num);
  funk2_memorypool__debug_memory_test(this, 2);
  u8 did_something = 0;
  rbt_node_t* iter = rbt_tree__minimum(&(this->used_memory_tree));
  rbt_node_t* next;
  while (iter) {
    next = rbt_node__next(iter);
    if (((funk2_memblock_t*)iter)->generation_num <= generation_num && (! ((funk2_memblock_t*)iter)->gc_touch)) {
      // remove from used list
      rbt_tree__remove(&(this->used_memory_tree), iter);
      // set to free
      ((funk2_memblock_t*)iter)->used = 0;
      this->total_free_memory += funk2_memblock__byte_num((funk2_memblock_t*)iter);
      // add to free list
      funk2_memorypool__link_funk2_memblock_to_freelist(this, (funk2_memblock_t*)iter);
      // set did_something flag
      did_something = 1;
    }
    iter = next;
  }
  funk2_memorypool__debug_memory_test(this, 2);
  return did_something;
}

void funk2_memorypool__increment_generation(funk2_memorypool_t* this) {
  funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(this)));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(this))) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used) {
      if (iter->generation_num < maximum_generation_num) {
	iter->generation_num ++;
      }
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

// look for memory block that is not used and is big enough for us to split up
funk2_memblock_t* funk2_memorypool__find_splittable_free_block_and_unfree(funk2_memorypool_t* this, f2size_t byte_num) {
  funk2_memorypool__debug_memory_test(this, 4);
  funk2_memblock_t* max_size_block = (funk2_memblock_t*)rbt_tree__maximum(&(this->free_memory_tree));
  if (max_size_block && funk2_memblock__byte_num(max_size_block) >= byte_num) {
    rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)max_size_block);
    max_size_block->used = 1;
  } else {
    if (!max_size_block) {
      status("there are no free memory blocks left.");
    } else {
      status("largest memory block is too small (need " f2size_t__fstr " bytes, have " f2size_t__fstr " bytes).", byte_num, funk2_memblock__byte_num(max_size_block));
    }
    max_size_block = NULL; // largest free memory block is not large enough.  fail.
  }
  funk2_memorypool__debug_memory_test(this, 4); // memory assumption violation here (block is taken out of free list and not added to used list, yet).
  return max_size_block;
}

void funk2_memorypool__touch_all_referenced_from_block(funk2_memorypool_t* this, ptr block) {
  funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(&(this->gc_touch_circle_buffer), (funk2_memblock_t*)(to_ptr(block)));
}

void funk2_memorypool__touch_all_referenced_from_f2ptr(funk2_memorypool_t* this, f2ptr exp) {
  funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(&(this->gc_touch_circle_buffer), exp);
}

void funk2_memorypool__touch_all_referenced_from_pool_generation(funk2_memorypool_t* this, int touch_generation_num) {
  //status("funk2_memorypool__touch_all_referenced_from_pool_generation: generation_num=%d.", touch_generation_num);
  funk2_memblock_t*   iter          = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(this)));
  funk2_memblock_t*   end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(this))) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used && iter->generation_num == touch_generation_num) {
      funk2_memorypool__touch_all_referenced_from_block(this, to_ptr(iter));
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

void funk2_memorypool__touch_all_protected_alloc_arrays(funk2_memorypool_t* this) {
  u64 i;
  for (i = 0; i < this->protected_alloc_array.used_num; i ++) {
    funk2_memorypool__touch_all_referenced_from_f2ptr(this, this->protected_alloc_array.data[i]);
  }
}

