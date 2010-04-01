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
  this->should_enlarge_memory_now            = boolean__false;
  this->total_allocated_memory_since_last_gc = 0;
  this->next_unique_block_id                 = 0;
  this->total_global_memory = sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY;
  f2dynamicmemory__init_and_alloc(&(this->dynamic_memory), sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY);
  
  this->total_free_memory = this->total_global_memory;
  
  this->global_f2ptr_offset = to_ptr(this->dynamic_memory.ptr - 1);
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(this->dynamic_memory.ptr);
  funk2_memblock__init(block, this->total_global_memory, 0);
  
  rbt_tree__init(&(this->free_memory_tree), NULL);
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
  rbt_tree__init(&(this->used_memory_tree), NULL);
  //funk2_gc_touch_circle_buffer__init(&(this->gc_touch_circle_buffer));
  
  funk2_memorypool__debug_memory_test(this, 1);
}

void funk2_memorypool__destroy(funk2_memorypool_t* this) {
  //funk2_gc_touch_circle_buffer__destroy(&(this->gc_touch_circle_buffer));
  f2dynamicmemory__destroy_and_free(&(this->dynamic_memory));
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
  funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(this->dynamic_memory.ptr));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
  while(iter < end_of_blocks) {
    release__assert(funk2_memblock__byte_num(iter) > 0, nil, "memory_test__byte_num_zero failed.");
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
}

void funk2_memorypool__memory_test__all_known_types(funk2_memorypool_t* this) {
  funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(this->dynamic_memory.ptr));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (! funk2_memblock__is_self_consistently_valid(iter)) {
      error(nil, "found self-inconsistent memblock ptype.");
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

void funk2_memorypool__memory_test(funk2_memorypool_t* this) {
  status("testing memory in pool...");
  status("  pool.total_free_memory                    = " f2size_t__fstr, this->total_free_memory);
  status("  funk2_memorypool__total_free_memory(this) = " f2size_t__fstr, funk2_memorypool__total_free_memory(this));
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
  status("funk2_memorypool__change_total_memory_available(" f2size_t__fstr ")", byte_num);
  if (byte_num == this->total_global_memory) {return;}
  f2size_t          old_total_global_memory = this->total_global_memory;
  f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
  status("funk2_memorypool__change_total_memory_available: old->ptr=0x" X64__fstr " " u64__fstr, old_dynamic_memory.ptr, old_dynamic_memory.ptr);
  f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, byte_num);
  status("funk2_memorypool__change_total_memory_available: new->ptr=0x" X64__fstr " " u64__fstr, this->dynamic_memory.ptr, this->dynamic_memory.ptr);
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
      //iter->gc_touch = 0;
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
      //block->gc_touch = 0;
      rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
      release__assert(funk2_memblock__byte_num(block) > 0, nil, "(funk2_memblock__byte_num(block) > 0) should be enough free space to reduce memory block.");
    } else {
      release__assert(0, nil, "funk2_memorypool__change_total_memory_available error: not implemented yet.");
    }
  }
  this->total_free_memory += (byte_num - old_total_global_memory);
  funk2_memorypool__debug_memory_test(this, 2);
}

void funk2_memorypool__link_funk2_memblock_to_freelist(funk2_memorypool_t* this, funk2_memblock_t* block) {
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
}

u8 funk2_memorypool__defragment_free_memory_blocks_in_place(funk2_memorypool_t* this) {
  funk2_memorypool__debug_memory_test(this, 2);
  status("defragmenting funk2_memorypool");
  u8 did_something = 0;
  funk2_memblock_t* iter = (funk2_memblock_t*)from_ptr(this->dynamic_memory.ptr);
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
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

void funk2_memorypool__free_used_block(funk2_memorypool_t* this, funk2_memblock_t* block) {
  // remove from used list
  rbt_tree__remove(&(this->used_memory_tree), (rbt_node_t*)block);
  // set to free
  block->used = 0;
  this->total_free_memory += funk2_memblock__byte_num(block);
  // add to free list
  funk2_memorypool__link_funk2_memblock_to_freelist(this, block);
  // remove reference counts
  {  
    ptype_block_t* ptype_block = (ptype_block_t*)block;
    switch(ptype_block->ptype) {
    case ptype_free_memory:  error(nil, "block of type free_memory in garbage collector.");
    case ptype_integer:      break;
    case ptype_double:       break;
    case ptype_float:        break;
    case ptype_pointer:      break;
    case ptype_gfunkptr:     break;
    case ptype_mutex:        break;
    case ptype_char:         break;
    case ptype_string:       break;
    case ptype_symbol:       break;
    case ptype_chunk:        break;
    case ptype_simple_array: {
      s64 i;
      f2ptr* iter = (f2ptr*)((ptype_simple_array_block_t*)ptype_block)->f2ptr_data;
      for (i = ((ptype_simple_array_block_t*)ptype_block)->length; i > 0; i --) {
	funk2_memblock_t* subblock = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(*iter));
	funk2_memblock__decrement_reference_count(subblock, *iter, &(__funk2.garbage_collector));
	iter ++;
      }
    } break;
    case ptype_traced_array: {
      s64 i;
      funk2_dptr_t* iter = (funk2_dptr_t*)((ptype_traced_array_block_t*)ptype_block)->dptr_data;
      for (i = ((ptype_traced_array_block_t*)ptype_block)->length; i > 0; i --) {
	funk2_dptr__decrement_reference_counts(iter, &(__funk2.garbage_collector));
	iter ++;
      }
    } break;
    case ptype_larva: {
      f2ptr             bug       = ((ptype_traced_array_block_t*)ptype_block)->bug;
      ptr               bug_ptr   = f2ptr_to_ptr(bug);
      funk2_memblock_t* bug_block = (funk2_memblock_t*)from_ptr(bug_ptr);
      funk2_memblock__decrement_reference_count(bug_block, bug, &(__funk2.garbage_collector));
    } break;
    default:
      {
	char str[1024];
	sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(ptype_block->ptype));
	error(nil, str);
      }
    }
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

boolean_t funk2_memorypool__check_all_memory_pointers_valid_in_memory(funk2_memorypool_t* this, funk2_memory_t* memory) {
  boolean_t         found_invalid = boolean__false;
  funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(this->dynamic_memory.ptr));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (! funk2_memory__is_reasonably_valid_funk2_memblock_ptr(memory, to_ptr(iter))) {
      status("funk2_memory__check_all_memory_pointers_valid error: found invalid memblock.");
      found_invalid = boolean__true;
      error(nil, "funk2_memory__check_all_memory_pointers_valid error: found invalid memblock.");
    }
    found_invalid |= funk2_memblock__check_all_memory_pointers_valid_in_memory(iter, memory);
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  return found_invalid;
}

void funk2_memorypool__save_to_stream(funk2_memorypool_t* this, int fd) {
  int compressed_length = 0;
  u8* compressed_data;
  {
    u8*       uncompressed_data   = (u8*)from_ptr(this->dynamic_memory.ptr);
    int       uncompressed_length = this->total_global_memory;
    compressed_length             = 0;
    boolean_t failure             = zlib__deflate_length(uncompressed_data, uncompressed_length, &compressed_length);
    if (failure) {
      error(nil, "funk2_memorypool__save_to_stream error: failed to deflate image using zlib.");
    }
    compressed_data               = (u8*)from_ptr(f2__malloc(compressed_length));
    failure                       = zlib__deflate(compressed_data, &compressed_length, uncompressed_data, uncompressed_length);
    if (failure) {
      error(nil, "funk2_memorypool__save_to_stream error: failed to deflate image using zlib.");
    }
  }
  f2size_t size_i;
  size_i = compressed_length;          safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
  size_i = this->total_global_memory;  safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
  size_i = this->next_unique_block_id; safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));

  status("funk2_memorypool__save_to_stream: dynamic_memory.ptr=0x" X64__fstr " " u64__fstr " total_global_memory=" u64__fstr " compressed_length=" u64__fstr,
	 this->dynamic_memory.ptr, this->dynamic_memory.ptr,
	 this->total_global_memory,
	 (u64)compressed_length);
  
  safe_write(fd, to_ptr(compressed_data), compressed_length);
  
  //safe_write(fd, this->dynamic_memory.ptr, this->total_global_memory);
  
  f2__free(to_ptr(compressed_data));
}

void funk2_memorypool__load_from_stream(funk2_memorypool_t* this, int fd) {
  f2size_t size_i;
  
  safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
  int compressed_length = size_i;
  
  safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
  this->total_global_memory = size_i;
  
  safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
  this->next_unique_block_id = size_i;
  
  f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
  f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, this->total_global_memory);
  
  u8* compressed_data = (u8*)from_ptr(f2__malloc(compressed_length));
  
  safe_read(fd, to_ptr(compressed_data), compressed_length);
  
  {
    int dest_length = 0;
    boolean_t failure = zlib__inflate(from_ptr(this->dynamic_memory.ptr), &dest_length, compressed_data, compressed_length);
    if (failure) {
      error(nil, "funk2_memorypool__load_from_stream error: failed to inflate image using zlib.");
    }
  }
  
  //safe_read(fd, this->dynamic_memory.ptr, this->total_global_memory);
  
  f2__free(to_ptr(compressed_data));
}

