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


// funk2_memblock

void funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, int used, int gc_touch) {
  funk2_memblock__byte_num(block) = byte_num;
  block->used                     = used;
  block->gc_touch                 = gc_touch;
  block->generation_num           = 0;
}


// funk2_memorypool

void funk2_memorypool__init(funk2_memorypool_t* pool) {
  funk2_processor_mutex__init(&(pool->global_memory_allocate_mutex));
  pool->should_run_gc                        = boolean__false;
  pool->should_enlarge_memory_now            = boolean__false;
  pool->total_allocated_memory_since_last_gc = 0;
  pool->next_unique_block_id                 = 0;
  pool->total_global_memory = sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY;
  f2dynamicmemory__init_and_alloc(&(pool->dynamic_memory), sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY);
  
  pool->total_free_memory = pool->total_global_memory;
  
  pool->global_f2ptr_offset = to_ptr(funk2_memorypool__memory__ptr(pool) - 1);
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(funk2_memorypool__memory__ptr(pool));
  funk2_memblock__init(block, pool->total_global_memory, 0, 0);
  
  rbt_tree__init(&(pool->free_memory_tree), NULL);
  rbt_tree__insert(&(pool->free_memory_tree), (rbt_node_t*)block);
  rbt_tree__init(&(pool->used_memory_tree), NULL);
  
  pool->protected_alloc_array__used_num = 0;
  pool->protected_alloc_array__length   = 1024;
  u64 i;
  pool->protected_alloc_array = (f2ptr*)f2__malloc(sizeof(f2ptr) * pool->protected_alloc_array__length);
  for (i = 0; i < pool->protected_alloc_array__length; i ++) {
    pool->protected_alloc_array[i] = nil;
  }
  pool->protected_alloc_array__reentrance_count = 0;
}

void funk2_memorypool__destroy(funk2_memorypool_t* this) {
  f2dynamicmemory__destroy_and_free(&(this->dynamic_memory));
}

void funk2_memorypool__add_protected_alloc_f2ptr(funk2_memorypool_t* this, f2ptr exp) {
  this->protected_alloc_array[this->protected_alloc_array__used_num] = exp;
  this->protected_alloc_array__used_num ++;
  if (this->protected_alloc_array__used_num >= this->protected_alloc_array__length) {
    u64 old_length = this->protected_alloc_array__length;
    this->protected_alloc_array__length <<= 1;
    status("funk2_memorypool__add_protected_alloc_f2ptr: doubling size of protected_alloc_array from " u64__fstr " to " u64__fstr " f2ptrs.", old_length, this->protected_alloc_array__length);
    this->protected_alloc_array = from_ptr(f2__new_alloc(to_ptr(this->protected_alloc_array), sizeof(f2ptr) * old_length, sizeof(f2ptr) * this->protected_alloc_array__length));
  }
}

void funk2_memorypool__signal_enter_protected_region(funk2_memorypool_t* this) {
  this->protected_alloc_array__reentrance_count ++;
}

void funk2_memorypool__signal_exit_protected_region(funk2_memorypool_t* this) {
  if (this->protected_alloc_array__reentrance_count == 0) {
    error(nil, "funk2_memorypool__signal_exit_protected_region error: bytecode reentrance underflow.");
  }
  this->protected_alloc_array__reentrance_count --;
  if (this->protected_alloc_array__reentrance_count == 0) {
    // protected counter is back to zero so reset array__used_num to zero.
    this->protected_alloc_array__used_num = 0;
  }
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
	fflush(stdout)
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
  funk2_memorypool__debug_memory_test(this, 1);
}

void funk2_memorypool__clear_all_gc_touch_flags_before_generation(funk2_memorypool_t* this, int generation_num) {
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
  funk2_memorypool__debug_memory_test(this, 1);
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
  funk2_memorypool__debug_memory_test(this, 1);
  return did_something;
}

u8 funk2_memorypool__free_all_gc_untouched_blocks_from_generation(funk2_memorypool_t* this, int generation_num) {
  status("freeing all untouched blocks for pool generation %d.", generation_num);
  funk2_memorypool__debug_memory_test(this, 1);
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
  funk2_memorypool__debug_memory_test(this, 1);
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
  funk2_memorypool__debug_memory_test(this, 3);
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
  // debug_memory_test(pool_index, 3); // memory assumption violation here (block is taken out of free list and not added to used list, yet).
  return max_size_block;
}



// funk2_gc_touch_circle_buffer

void funk2_gc_touch_circle_buffer__init(funk2_gc_touch_circle_buffer_t* this) {
  this->num         = GC_TOUCH_CIRCLE_BUF_START_SIZE;
  this->start       = (funk2_memblock_t**)from_ptr(f2__malloc(GC_TOUCH_CIRCLE_BUF_START_SIZE * sizeof(funk2_memblock_t*)));
  this->end         = this->start + GC_TOUCH_CIRCLE_BUF_START_SIZE;  
  this->start_index = NULL;
  this->end_index   = NULL;
}

void funk2_gc_touch_circle_buffer__print(funk2_gc_touch_circle_buffer_t* this, char* message) {
  ptr* iter = (ptr*)this->start;
  printf("\n%16s: {", message);
  for(; iter < (ptr*)this->end; iter++) {
    if (iter == (ptr*)this->start_index) {
      printf(" *S*");
    }
    if (iter == (ptr*)this->end_index) {
      printf(" *E*");
    }
    printf(" %lx", (long)*iter);
    fflush(stdout);
  }
  printf("}\n");
  fflush(stdout);
}

void funk2_gc_touch_circle_buffer__advance_end(funk2_gc_touch_circle_buffer_t* this) {
  this->end_index ++;
  if (this->end_index == this->end) {
    this->end_index = this->start;
  }
  if (this->end_index == this->start_index) {
    //funk2_gc_touch_circle_buffer__print(this, "buffer");
    //printf("\nincreasing buffer."); fflush(stdout);
    //printf("\n  start = %lx.", (int)(this->start_index - this->start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(this->end_index   - this->start)); fflush(stdout);
    //funk2_gc_touch_circle_buffer__print(this, "debug 0");
    // increasing size by two makes a lot of these memory moves conveniently easy.
    int old_num = this->num;
    this->num = old_num << 1;
    //printf("\n__gc_touch_circle_buffer.start = %x", (int)this->start);
    funk2_memblock_t** new_location = (funk2_memblock_t**)from_ptr(f2__new_alloc(to_ptr(this->start), sizeof(funk2_memblock_t*) * old_num, sizeof(funk2_memblock_t*) * this->num));
    //printf("\nnew_location = %lx", (int)new_location); fflush(stdout);
    int location_diff = new_location - this->start;
    this->start = new_location;
    
    this->start_index += location_diff;
    this->end_index   += location_diff;
    
    this->end = this->start + this->num;
    //printf("\n  copying %d bytes ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start).", ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start));
    //printf("\n  sizeof(funk2_memblock_t**) = %d bytes.", sizeof(funk2_memblock_t**));
    //printf("\n  old_num = %d", old_num);
    //funk2_gc_touch_circle_buffer__print(this, "just before copy");
    memcpy(this->start + old_num, this->start, ((u8*)this->end_index) - ((u8*)this->start));
    //funk2_gc_touch_circle_buffer__print(this, "just after copy");
    this->end_index += old_num;
    //printf("\ncircle_buffer size increased to %d.", this->num); fflush(stdout);
    //printf("\n  start = %lx.", (int)(this->circle_buf_start_index - this->start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(this->circle_buf_end_index   - this->start)); fflush(stdout);
    //funk2_gc_touch_circle_buffer__print(this, "after all");
  }
}

void funk2_gc_touch_circle_buffer__advance_start_index(funk2_gc_touch_circle_buffer_t* this) {
  //printf("\nadvance start."); fflush(stdout);
  //printf("\n  start = %x.", (int)(this->circle_buf_start_index - this->start)); fflush(stdout);
  //printf("\n  end   = %x.", (int)(this->circle_buf_end_index   - this->start)); fflush(stdout);
  this->start_index ++;
  if (this->start_index == this->end) {
    this->start_index = this->start;
  }
}

void funk2_gc_touch_circle_buffer__touch_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr block_f2ptr) {
  if (block_f2ptr) {
    ptr block_ptr = __f2ptr_to_ptr(block_f2ptr);
    (this)->end_index[0] = (funk2_memblock_t*)from_ptr(block_ptr);
    funk2_gc_touch_circle_buffer__advance_end(this);
  }
}

void funk2_gc_touch_circle_buffer__touch_dptr(funk2_gc_touch_circle_buffer_t* this, dptr_t* dptr) {
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->p);
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->tracing_on);
  funk2_gc_touch_circle_buffer__touch_f2ptr(this, dptr->trace);
}

void funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(funk2_gc_touch_circle_buffer_t* this, ptr start_block_ptr) {
  
  release__assert(start_block_ptr, nil, "exp__gc_touch_all_referenced assertion failed: got null value.");
  
  ptype_block_t* start_block = (ptype_block_t*)from_ptr(start_block_ptr);
  this->start_index    = this->start;
  this->end_index      = this->start_index + 1;
  this->start_index[0] = (funk2_memblock_t*)start_block;
  ptype_block_t* block;
  while (this->end_index != this->start_index) {
    block = (ptype_block_t*)(this->start_index[0]);
    if (block && (! block->block.gc_touch)) {
      funk2_gc_touch_circle_buffer__touch_f2ptr(this, block->cause);
      switch(block->ptype) {
      case ptype_free_memory:
	{
	  char str[1024];
	  sprintf(str,
		  "\nblock of type free_memory (%lu bytes) in garbage collector."
		  "\n  FYI:"
		  "\n    sizeof(integer_block)      = %lu"
		  "\n    sizeof(double_block)       = %lu"
		  "\n    sizeof(float_block)        = %lu"
		  "\n    sizeof(pointer_block)      = %lu"
		  "\n    sizeof(gfunkptr_block)     = %lu"
		  "\n    sizeof(mutex_block)        = %lu"
		  "\n    sizeof(char_block)         = %lu"
		  "\n    sizeof(string_block)       = %lu"
		  "\n    sizeof(symbol_block)       = %lu"
		  "\n    sizeof(chunk_block)        = %lu"
		  "\n    sizeof(simple_array_block) = %lu"
		  "\n    sizeof(array_block)        = %lu"
		  "\n    sizeof(larva_block)        = %lu",
		  (unsigned long)funk2_memblock__byte_num((funk2_memblock_t*)block),
		  (unsigned long)sizeof(ptype_integer_block_t),
		  (unsigned long)sizeof(ptype_double_block_t),
		  (unsigned long)sizeof(ptype_float_block_t),
		  (unsigned long)sizeof(ptype_pointer_block_t),
		  (unsigned long)sizeof(ptype_gfunkptr_block_t),
		  (unsigned long)sizeof(ptype_mutex_block_t),
		  (unsigned long)sizeof(ptype_char_block_t),
		  (unsigned long)sizeof(ptype_string_block_t),
		  (unsigned long)sizeof(ptype_symbol_block_t),
		  (unsigned long)sizeof(ptype_chunk_block_t),
		  (unsigned long)sizeof(ptype_simple_array_block_t),
		  (unsigned long)sizeof(ptype_traced_array_block_t),
		  (unsigned long)sizeof(ptype_larva_block_t));
	  error(nil, str);
	}
	break;
      case ptype_integer:      block->block.gc_touch = 1; break;
      case ptype_double:       block->block.gc_touch = 1; break;
      case ptype_float:        block->block.gc_touch = 1; break;
      case ptype_pointer:      block->block.gc_touch = 1; break;
      case ptype_gfunkptr:     block->block.gc_touch = 1; break;
      case ptype_mutex:        block->block.gc_touch = 1; break;
      case ptype_char:         block->block.gc_touch = 1; break;
      case ptype_string:       block->block.gc_touch = 1; break;
      case ptype_symbol:       block->block.gc_touch = 1; break;
      case ptype_chunk:        block->block.gc_touch = 1; break;
      case ptype_simple_array: block->block.gc_touch = 1; {
	int i;
	f2ptr* iter = (f2ptr*)((ptype_simple_array_block_t*)block)->f2ptr_data;
	for (i = ((ptype_simple_array_block_t*)block)->length; i > 0; i --) {
	  funk2_gc_touch_circle_buffer__touch_f2ptr(this, *iter);
	  iter ++;
	}
      } break;
      case ptype_traced_array: block->block.gc_touch = 1; {
	int i;
	dptr_t* iter = (dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
	for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
	  funk2_gc_touch_circle_buffer__touch_dptr(this, (dptr_t*)iter);
	  iter ++;
	}
      } break;
      case ptype_larva:        block->block.gc_touch = 1; break;
      default:
	{
	  char str[1024];
	  sprintf(str, "unknown type (%d) of block in garbage collector.", (int)(block->ptype));
	  error(nil, str);
	}
      }
    }
    funk2_gc_touch_circle_buffer__advance_start_index(this);
  }
}

void funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(funk2_gc_touch_circle_buffer_t* this, f2ptr exp) {
  if(!exp) {return;}
  ptype_block_t* exp_block = (ptype_block_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (exp_block->block.gc_touch) {return;}
  funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(this, to_ptr(exp_block));
}






int raw__memory_image__load(char* filename) {
  int retval = 0; // success
  status("loading memory image.");
  
  f2__global_scheduler__execute_mutex__lock(initial_cause());
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(__funk2.memory.pool[pool_index]));
  }
  
  
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    status("load_image_from_disk failure: could not open file \"%s\".", filename);
    retval = -1;
  } else {
    while(1) {
      int      i;
      f2ptr    f2_i;
      f2size_t size_i;
      safe_read(fd, &i, sizeof(int));
      if (i != 0xfaded) {
	status("load_image_from_disk failure: file is not a funk memory image.");
	retval = -1;
	break;
      }
      
      safe_read(fd, &i, sizeof(int));
      if (i != F2__COMPILE_TIME_ID) {
	status("load_image_from_disk failure: file is saved from a different version of funk2.");
	retval = -1;
	break;
      }
      
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	safe_read(fd, &size_i, sizeof(f2size_t));
	__funk2.memory.pool[pool_index].total_global_memory = size_i;
	
	safe_read(fd, &size_i, sizeof(f2size_t));
	__funk2.memory.pool[pool_index].next_unique_block_id = size_i;
	
	f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(__funk2.memory.pool[pool_index].dynamic_memory), sizeof(f2dynamicmemory_t));
	f2dynamicmemory__realloc(&(__funk2.memory.pool[pool_index].dynamic_memory), &old_dynamic_memory, __funk2.memory.pool[pool_index].total_global_memory);
	safe_read(fd, from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))), __funk2.memory.pool[pool_index].total_global_memory);
      }
      
      safe_read(fd, &f2_i, sizeof(f2ptr));
      f2ptr global_environment_f2ptr = f2_i;
      
      status("done loading memory image."); fflush(stdout);
      
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	__funk2.memory.pool[pool_index].global_f2ptr_offset = to_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))) - 1;
      }
      
      __funk2.memory.global_environment_f2ptr = global_environment_f2ptr;
      __funk2.memory.global_environment_ptr   = raw__f2ptr_to_ptr(global_environment_f2ptr);
      
      funk2_memory__rebuild_memory_info_from_image(&(__funk2.memory));
      
      status("loaded memory image successfully.");
      break;
    }
    close(fd);      
  }
  
  f2__global_scheduler__execute_mutex__unlock(initial_cause());
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__unlock(&(__funk2.memory.pool[pool_index]));
  }
  
  funk2_memory__print_gc_stats(&(__funk2.memory));
  return retval;
}



// funk2_memory

void funk2_memory__init(funk2_memory_t* this) {
  this->global_environment_ptr   = to_ptr(NULL);
  this->global_environment_f2ptr = nil;
  
  this->memory_handling_thread = pthread_self();
  this->bootstrapping_mode     = boolean__true;
  
  funk2_gc_touch_circle_buffer__init(&(this->gc_touch_circle_buffer));
}

void funk2_memory__destroy(funk2_memory_t* this) {
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
    while (__ptypes_waiting_count < memory_pool_num) {
      sched_yield();
    }
    for (index = 0; index < memory_pool_num; index ++) {
      if (this->pool[index].should_enlarge_memory_now) {
	funk2_memorypool__change_total_memory_available(&(this->pool[index]), this->pool[index].total_global_memory + (this->pool[index].total_global_memory >> 3) + this->pool[index].should_enlarge_memory_now__need_at_least_byte_num);
	this->pool[index].should_enlarge_memory_now__need_at_least_byte_num = 0;
	this->pool[index].should_enlarge_memory_now                         = boolean__false;
      }
    }
    __ptypes_please_wait_for_gc_to_take_place = boolean__false;
  }
  if (should_collect_garbage && (raw__nanoseconds_since_1970() - this->last_garbage_collect_nanoseconds_since_1970) > 10 * 1000000000ull) {
    status("funk2_memory__handle asking all user threads to wait_politely so that we can begin collecting garbage.");
    __ptypes_please_wait_for_gc_to_take_place = boolean__true;
    while (__ptypes_waiting_count < memory_pool_num) {
      sched_yield();
    }
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
    __ptypes_please_wait_for_gc_to_take_place = boolean__false;
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
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memblock_t* iter = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))));
    funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)(from_ptr(funk2_memorypool__memory__ptr(&(this->pool[pool_index]))))) + (this->pool[pool_index].total_global_memory));
    int byte_num;
    while(iter < end_of_blocks) {
      if ((to_ptr(iter)) == p) {return boolean__true;}
      byte_num = funk2_memblock__byte_num(iter);
      if (byte_num <= 0) {
	char str[1024];
	sprintf(str, "funk2_memory__is_valid_funk2_memblock_ptr error: byte_num <= 0 (%d).", byte_num);
	error(nil, str);
      }
      iter = (funk2_memblock_t*)(((u8*)iter) + byte_num);
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

void funk2_memory__touch_all_protected_alloc_arrays(funk2_memory_t* this) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    u64 i;
    for (i = 0; i < this->pool[pool_index].protected_alloc_array__used_num; i ++) {
      funk2_gc_touch_circle_buffer__touch_all_referenced_from_f2ptr(&(this->gc_touch_circle_buffer), this->pool[pool_index].protected_alloc_array[i]);
    }
  }
}

void funk2_memory__touch_everything(funk2_memory_t* this, int generation_num) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memory__touch_all_referenced_from_pool_generation(this, pool_index, generation_num);
  }
  funk2_memory__touch_all_symbols(this);
  funk2_memory__touch_all_protected_alloc_arrays(this);
}

void funk2_memory__touch_all_referenced_from_pool_generation(funk2_memory_t* this, int pool_index, int touch_generation_num) {
  if (pool_index < 0 || pool_index >= memory_pool_num) {
    error(nil, "pool_index out of range.");
  }
  funk2_memorypool_t* pool          = &(this->pool[pool_index]);
  funk2_memblock_t*   iter          = (funk2_memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(pool)));
  funk2_memblock_t*   end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(pool))) + pool->total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used && iter->generation_num == touch_generation_num) {
      funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(&(this->gc_touch_circle_buffer), to_ptr(iter));
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
}

boolean_t funk2_memory__garbage_collect_generation(funk2_memory_t* this, int generation_num) {
  status("collecting garbage...");
  int pool_index;
#ifdef DEBUG_MEMORY
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 1);
  }
#endif
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__clear_all_gc_touch_flags_before_generation(&(this->pool[pool_index]), generation_num);
  }
  
  // this is where we touch everything we want to keep!
  funk2_memory__touch_everything(this, generation_num);
  
  boolean_t did_something = 0;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    did_something |= funk2_memorypool__free_all_gc_untouched_blocks_from_generation(&(this->pool[pool_index]), generation_num);
    this->pool[pool_index].total_allocated_memory_since_last_gc = 0;
  }
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 1);
  }
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
  funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 3);
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
    __ptypes_please_wait_for_gc_to_take_place                                = boolean__true;
    if (pthread_self() == this->memory_handling_thread) {
      if (! this->bootstrapping_mode) {
	while (__ptypes_waiting_count < memory_pool_num) {
	  sched_yield();
	}
      }
      funk2_memorypool__change_total_memory_available(&(this->pool[pool_index]), this->pool[pool_index].total_global_memory + (this->pool[pool_index].total_global_memory >> 3) + this->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num);
      this->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num = 0;
      this->pool[pool_index].should_enlarge_memory_now                         = boolean__false;
      __ptypes_please_wait_for_gc_to_take_place                                = boolean__false;
    } else {
      wait_politely();
    }
    block = to_ptr(funk2_memorypool__find_splittable_free_block_and_unfree(&(this->pool[pool_index]), byte_num));
    if (block) {return block;}  
    // might need to loop more than once if two requests for memory from memory handling process occur at the same time.
  } while (1);
  // shouldn't get here if we have DYNAMIC_MEMORY defined.  if we are *only* using static_memory then this fails.  however, in distributed systems external memory systems could be asked for memory at this point (REMOTE_MEMORY?).
  printf("\nfind_free_memory_for_new_memblock error: shouldn't get here.  byte_num = %u\n", (unsigned int)byte_num);
  error(nil, "find_free_memory_for_new_memblock error: shouldn't get here.\n");
  return to_ptr(NULL);
}

// note that byte_num must be at least sizeof(u8) for ptype! because of type checking in garbage collection
f2ptr funk2_memory__funk2_memblock_f2ptr__try_new(funk2_memory_t* this, int pool_index, f2size_t byte_num) {
  funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 3);
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
  funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 3);
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
    
    funk2_module_registration__reinitialize_all_modules(&(__funk2->module_registration));
  }
  // end temporary unlocking of all memory mutexes
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__memory_mutex__lock(&(this->pool[pool_index]));
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_memorypool__debug_memory_test(&(this->pool[pool_index]), 1);
  }
  
  status("done rebuilding memory info from image."); fflush(stdout);
}





// **

void f2__memory__initialize() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__init((&__funk2.memory.pool[pool_index]));
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__debug_memory_test(&(__funk2.memory.pool[pool_index]), 1);
  }
}

void f2__memory__destroy() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__debug_memory_test(&(__funk2.memory.pool[pool_index]), 1);
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__destroy(&(__funk2.memory.pool[pool_index]));
  }
}



