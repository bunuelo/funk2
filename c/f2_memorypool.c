// 
// Copyright (c) 2007-2011 Bo Morgan.
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
  
  rbt_tree__init(&(this->free_memory_tree), NULL, this->global_f2ptr_offset);
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
  rbt_tree__init(&(this->used_memory_tree), NULL, this->global_f2ptr_offset);
  
  funk2_memorypool__debug_memory_test(this, 1);
}

void funk2_memorypool__destroy(funk2_memorypool_t* this) {
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
  release__assert_and_on_failure((s64)(funk2_memorypool__total_used_memory(this) + funk2_memorypool__total_free_memory(this)) == (s64)this->total_global_memory,
				 nil,
				 "funk2_memorypool__memory_test (funk2_memorypool__total_used_memory(this) + funk2_memorypool__total_free_memory(this) != this->total_global_memory) failure.",
      {
	s64 used_memory_num = funk2_memorypool__total_used_memory(this);
	s64 free_memory_num = funk2_memorypool__total_free_memory(this);
	printf("\ntotal_used_memory                       = " s64__fstr, (s64)used_memory_num);
	printf("\ntotal_free_memory                       = " s64__fstr, (s64)free_memory_num);
	printf("\ntotal_used_memory + total_free_memory() = " s64__fstr, (s64)free_memory_num + used_memory_num);
	printf("\nthis->total_global_memory               = " s64__fstr, (s64)this->total_global_memory);
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

f2ptr raw__memorypool__assert_valid(f2ptr cause, s64 pool_index) {
  if (pool_index < 0 || pool_index >= memory_pool_num) {
    return f2larva__new(cause, 2, nil);
  }
  
  pause_gc();
  f2ptr return_value = nil;
  status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") beginning.", pool_index);
  {
    __funk2.user_thread_controller.please_wait = boolean__true;
    funk2_user_thread_controller__signal_user_waiting_politely(&(__funk2.user_thread_controller));
    funk2_user_thread_controller__wait_for_all_user_threads_to_wait(&(__funk2.user_thread_controller));
  }
  {
    funk2_memorypool_t* memorypool = &(__funk2.memory.pool[pool_index]);
    if (funk2_memorypool__total_free_memory(memorypool) != memorypool->total_free_memory) {
      status("memorypool_assertion_failed");
      status("  funk2_memorypool__total_free_memory(memorypool) == memorypool->total_free_memory");
      status("  funk2_memorypool__total_free_memory(memorypool): " s64__fstr, (s64)(funk2_memorypool__total_free_memory(memorypool)));
      status("  memorypool->total_free_memory..................: " s64__fstr, (s64)(memorypool->total_free_memory));
      return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list8__new(cause,
															     new__symbol(cause, "bug_type"),                                        new__symbol(cause, "memorypool_assertion_failed"),
															     new__symbol(cause, "assertion_description"),                           new__string(cause, "funk2_memorypool__total_free_memory(memorypool) == memorypool->total_free_memory"),
															     new__symbol(cause, "funk2_memorypool__total_free_memory(memorypool)"), f2integer__new(cause, funk2_memorypool__total_free_memory(memorypool)),
															     new__symbol(cause, "memorypool->total_free_memory"),                   f2integer__new(cause, memorypool->total_free_memory)))));
      goto raw__memorypool__assert_valid__return_label;
    }
    if ((s64)(funk2_memorypool__total_used_memory(memorypool) + funk2_memorypool__total_free_memory(memorypool)) != (s64)memorypool->total_global_memory) {
      status("memorypool_assertion_failed");
      status("  total_used_memory(memorypool) + total_free_memory(memorypool) == memorypool->total_global_memory");
      status("  memorypool->total_global_memory..............................: " s64__fstr, (s64)memorypool->total_global_memory);
      status("  total_used_memory(memorypool)................................: " s64__fstr, (s64)funk2_memorypool__total_used_memory(memorypool));
      status("  total_free_memory(memorypool)................................: " s64__fstr, (s64)funk2_memorypool__total_free_memory(memorypool));
      status("  total_used_memory(memorypool) + total_free_memory(memorypool): " s64__fstr, (s64)(funk2_memorypool__total_used_memory(memorypool) + funk2_memorypool__total_free_memory(memorypool)));
      return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list12__new(cause,
															      new__symbol(cause, "bug_type"),                                                      new__symbol(cause, "memorypool_assertion_failed"),
															      new__symbol(cause, "assertion_description"),                                         new__string(cause, "total_used_memory(memorypool) + total_free_memory(memorypool) == memorypool->total_global_memory"),
															      new__symbol(cause, "memorypool->total_global_memory"),                               f2integer__new(cause, (s64)memorypool->total_global_memory),
															      new__symbol(cause, "total_used_memory(memorypool)"),                                 f2integer__new(cause, funk2_memorypool__total_used_memory(memorypool)),
															      new__symbol(cause, "total_free_memory(memorypool)"),                                 f2integer__new(cause, funk2_memorypool__total_free_memory(memorypool)),
															      new__symbol(cause, "total_used_memory(memorypool) + total_free_memory(memorypool)"), f2integer__new(cause, funk2_memorypool__total_used_memory(memorypool) + funk2_memorypool__total_free_memory(memorypool))))));
      goto raw__memorypool__assert_valid__return_label;
    }
    if (memorypool->dynamic_memory.byte_num != memorypool->total_global_memory) {
      status("memorypool_assertion_failed");
      status("  memorypool->dynamic_memory.byte_num == memorypool->total_global_memory");
      status("  memorypool->dynamic_memory.byte_num: " s64__fstr, (s64)(memorypool->dynamic_memory.byte_num));
      status("  memorypool->total_global_memory....: " s64__fstr, (s64)(memorypool->total_global_memory));
      return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list8__new(cause,
															     new__symbol(cause, "bug_type"),                            new__symbol(cause, "memorypool_assertion_failed"),
															     new__symbol(cause, "assertion_description"),               new__string(cause, "memorypool->dynamic_memory.byte_num == memorypool->total_global_memory"),
															     new__symbol(cause, "memorypool->dynamic_memory.byte_num"), f2integer__new(cause, memorypool->dynamic_memory.byte_num),
															     new__symbol(cause, "memorypool->total_global_memory"),     f2integer__new(cause, memorypool->total_global_memory)))));
      goto raw__memorypool__assert_valid__return_label;
    }
    {
      funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(memorypool->dynamic_memory.ptr));
      funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(memorypool->dynamic_memory.ptr)) + memorypool->total_global_memory);
      while(iter < end_of_blocks) {
	if (funk2_memblock__byte_num(iter) == 0) {
	  status("memorypool_assertion_failed");
	  status("  funk2_memblock__byte_num(iter) != 0");
	  status("  iter: " s64__fstr, (s64)to_ptr(iter));
	  return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list6__new(cause,
																 new__symbol(cause, "bug_type"),              new__symbol(cause, "memorypool_assertion_failed"),
																 new__symbol(cause, "assertion_description"), new__string(cause, "funk2_memblock__byte_num(iter) != 0"),
																 new__symbol(cause, "iter"),                  f2integer__new(cause, (s64)to_ptr(iter))))));
	  goto raw__memorypool__assert_valid__return_label;
	}
	iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
      }
      if (iter != end_of_blocks) {
	status("memorypool_assertion_failed");
	status("  iter == end_of_blocks");
	status("  iter.........: " s64__fstr, (s64)to_ptr(iter));
	status("  end_of_blocks: " s64__fstr, (s64)to_ptr(end_of_blocks));
	return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list8__new(cause,
															       new__symbol(cause, "bug_type"),              new__symbol(cause, "memorypool_assertion_failed"),
															       new__symbol(cause, "assertion_description"), new__string(cause, "iter == end_of_blocks"),
															       new__symbol(cause, "iter"),                  f2integer__new(cause, (s64)to_ptr(iter)),
															       new__symbol(cause, "end_of_blocks"),         f2integer__new(cause, (s64)to_ptr(end_of_blocks))))));
	goto raw__memorypool__assert_valid__return_label;
      }
    }
    {
      funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(memorypool->dynamic_memory.ptr));
      funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(memorypool->dynamic_memory.ptr)) + memorypool->total_global_memory);
      while(iter < end_of_blocks) {
	if (! funk2_memblock__is_self_consistently_valid(iter)) {
	  status("memorypool_assertion_failed");
	  status("  funk2_memblock__is_self_consistently_valid(iter)");
	  status("  iter: " s64__fstr, (s64)to_ptr(iter));
	  return_value = f2larva__new(cause, 5, f2__bug__new(cause, f2integer__new(cause, 5), f2__frame__new(cause, f2list6__new(cause,
																 new__symbol(cause, "bug_type"),              new__symbol(cause, "memorypool_assertion_failed"),
																 new__symbol(cause, "assertion_description"), new__string(cause, "funk2_memblock__is_self_consistently_valid(iter)"),
																 new__symbol(cause, "iter"),                  f2integer__new(cause, (s64)to_ptr(iter))))));
	  goto raw__memorypool__assert_valid__return_label;
	}
	iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
      }
    }
  }
 raw__memorypool__assert_valid__return_label:
  {
    funk2_user_thread_controller__signal_user_done_waiting_politely(&(__funk2.user_thread_controller));
    __funk2.user_thread_controller.please_wait = boolean__false;
  }
  if (return_value == nil) {
    status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") memorypool is valid.", pool_index);
  } else {
    status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") memorypool is invalid.", pool_index);
  }
  resume_gc();
  return return_value;
}



void funk2_memorypool__change_total_memory_available(funk2_memorypool_t* this, f2size_t byte_num) {
  if(((u64)byte_num) > ((u64)f2ptr__pool_address__max_value)) {
    status("funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed ((u64)byte_num) > ((u64)f2ptr__pool_address__max_value), ((u64)" u64__fstr ") > ((u64)" u64__fstr ").",
	   ((u64)byte_num), ((u64)f2ptr__pool_address__max_value));
    error(nil, "funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed (are you using a 32 bit version still?).");
  }
  status("funk2_memorypool__change_total_memory_available(" f2size_t__fstr ")", byte_num);
  if (byte_num == this->total_global_memory) {
    return;
  }
  
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
    if (this->used_memory_tree.head) {this->used_memory_tree.head = (rbt_node_t*)(((u8*)this->used_memory_tree.head) + byte_diff);}
    if (this->free_memory_tree.head) {this->free_memory_tree.head = (rbt_node_t*)(((u8*)this->free_memory_tree.head) + byte_diff);}
    if (__funk2.memory.global_environment_ptr >= old_dynamic_memory.ptr &&
	__funk2.memory.global_environment_ptr <  old_dynamic_memory.ptr + old_total_global_memory) {
      if (__funk2.memory.global_environment_ptr) {__funk2.memory.global_environment_ptr = __funk2.memory.global_environment_ptr + byte_diff;}
    }
    funk2_memblock_t* iter          = from_ptr(this->dynamic_memory.ptr);
    funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + old_total_global_memory);
    funk2_memblock_t* last          = NULL;
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
      iter->used = 0;
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
      block->used = 0;
      rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
      release__assert(funk2_memblock__byte_num(block) > 0, nil, "(funk2_memblock__byte_num(block) > 0) should be enough free space to reduce memory block.");
    } else {
      release__assert(0, nil, "funk2_memorypool__change_total_memory_available error: not implemented yet.");
    }
  }
  this->total_free_memory += (byte_num - old_total_global_memory);
  funk2_memorypool__debug_memory_test(this, 2);
}

void funk2_memorypool__used_memory_tree__insert(funk2_memorypool_t* this, funk2_memblock_t* block) {
  rbt_tree__insert(&(this->used_memory_tree), (rbt_node_t*)block);
}

void funk2_memorypool__free_memory_tree__insert(funk2_memorypool_t* this, funk2_memblock_t* block) {
  rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)block);
}

u64 u64__log2(u64 this) {
  s64 power = 63;
  u64 mask  = 0x8000000000000000ull;
  while ((this & mask) == 0) {
    mask >>= 1;
    power --;
    if (power == 0) {
      return 0;
    }
  }
  return power;
}

u8 funk2_memorypool__defragment_free_memory_blocks_in_place(funk2_memorypool_t* this) {
  u8 did_something = 0;
  status("skipping defragmentation of funk2_memorypool.");
  return did_something;
  {// this block is (not --^) skipped because there is a bug that occurs with a zero byte_num block of memory.
    funk2_memorypool__debug_memory_test(this, 2);
    status("defragmenting funk2_memorypool");
    u64               largest_free_block_size       = 0;
    funk2_memblock_t* end_of_blocks                 = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
    u64               free_memory_tree__size        = rbt_tree__size(&(this->free_memory_tree));
    u64               free_memory_tree__size__power = u64__log2(free_memory_tree__size);
    funk2_hash_t      blocks_to_defragment;
    funk2_hash__init(&blocks_to_defragment, free_memory_tree__size__power + 1);
    status("  free_memory_tree__size=" u64__fstr, free_memory_tree__size);
    {
      rbt_node_t* node = rbt_tree__minimum(&(this->free_memory_tree));
      while(node) {
	u64               byte_num   = funk2_memblock__byte_num(((funk2_memblock_t*)node));
	if (largest_free_block_size < byte_num) {
	  largest_free_block_size = byte_num;
	}
	funk2_memblock_t* next_block = (funk2_memblock_t*)(((u8*)node) + byte_num);
	if ((next_block < end_of_blocks) && (! (next_block->used))) {
	  funk2_hash__add(&blocks_to_defragment, (u64)to_ptr(node), (u64)0);
	}
	node = rbt_node__next(node);
      }
    }
    status("  blocks_to_defragment.key_count=" u64__fstr, (u64)(blocks_to_defragment.key_count));
    status("  before defragment largest_free_block_size=" u64__fstr, (u64)(largest_free_block_size));
    u64 bin_count = funk2_hash__bin_count(&blocks_to_defragment);
    {
      u64 index;
      for (index = 0; index < bin_count; index ++) {
	funk2_hash_bin_node_t* bin_node = blocks_to_defragment.bin_array[index];
	while (bin_node) {
	  funk2_memblock_t* segment_first_free_block = (funk2_memblock_t*)(from_ptr(bin_node->keyvalue_pair.key));
	  funk2_memblock_t* iter                     = (funk2_memblock_t*)(((u8*)segment_first_free_block) + funk2_memblock__byte_num(((funk2_memblock_t*)segment_first_free_block)));
	  while ((iter < end_of_blocks) && (! (iter->used))) {
	    if (funk2_memblock__byte_num(iter) == 0) {
	      status(nil, "funk2_memorypool__defragment_free_memory_blocks_in_place MEMORY BUG: memblock__byte_num = 0.");
	      printf( "\n\nfunk2_memorypool__defragment_free_memory_blocks_in_place MEMORY BUG: memblock__byte_num = 0.\n\n");
	      break;
	    }
	    funk2_memblock_t* next = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
	    if (funk2_hash__contains(&blocks_to_defragment, (u64)to_ptr(iter))) {
	      funk2_hash__remove(&blocks_to_defragment, (u64)to_ptr(iter));
	    }
	    rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)iter);
	    rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)segment_first_free_block);
	    u64 byte_num = funk2_memblock__byte_num(segment_first_free_block) + funk2_memblock__byte_num(iter);
	    if (largest_free_block_size < byte_num) {
	      largest_free_block_size = byte_num;
	    }
	    funk2_memblock__byte_num(segment_first_free_block) = byte_num;
	    rbt_tree__insert(&(this->free_memory_tree), (rbt_node_t*)segment_first_free_block);
	    iter = next;
	    did_something = 1;
	  }
	  funk2_hash__remove(&blocks_to_defragment, (u64)to_ptr(segment_first_free_block));
	  bin_node = blocks_to_defragment.bin_array[index];
	}
      }
    }
    funk2_hash__destroy(&blocks_to_defragment);
    status("  after defragment largest_free_block_size=" u64__fstr, (u64)(largest_free_block_size));
    funk2_memorypool__debug_memory_test(this, 2);
    return did_something;
  }
}


void funk2_memorypool__free_used_block(funk2_memorypool_t* this, funk2_memblock_t* block) {
  // remove from used list
  rbt_tree__remove(&(this->used_memory_tree), (rbt_node_t*)block);
  // set to free
  debug__assert(block->used, nil, "attempting to free a block that is already free.");
  block->used = 0;
  this->total_free_memory += funk2_memblock__byte_num(block);
  // add to free list
  funk2_memorypool__free_memory_tree__insert(this, block);
  // remove reference counts
  {
    ptype_block_t* ptype_block = (ptype_block_t*)block;
    {
      f2ptr             cause       = ptype_block->cause;
      f2ptr             cause_ptr   = __f2ptr_to_ptr(cause);
      funk2_memblock_t* cause_block = (funk2_memblock_t*)from_ptr(cause_ptr);
      funk2_memblock__decrement_reference_count(cause_block, cause, &(__funk2.garbage_collector));
    }
    switch(ptype_block->ptype) {
    case ptype_free_memory:     error(nil, "block of type free_memory in garbage collector.");
    case ptype_integer:          break;
    case ptype_double:           break;
    case ptype_float:            break;
    case ptype_pointer:          break;
    case ptype_gfunkptr:         break;
    case ptype_scheduler_cmutex: break;
    case ptype_cmutex:           break;
    case ptype_char:             break;
    case ptype_string:           break;
    case ptype_symbol:           break;
    case ptype_chunk:            break;
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
      f2ptr             bug       = ((ptype_larva_block_t*)ptype_block)->bug;
      ptr               bug_ptr   = __f2ptr_to_ptr(bug);
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
  //funk2_memblock_t* max_size_block = (funk2_memblock_t*)rbt_tree__maximum(&(this->free_memory_tree));
  funk2_memblock_t* perfect_size_block = (funk2_memblock_t*)rbt_tree__minimum_not_less_than(&(this->free_memory_tree), byte_num);
  if (perfect_size_block && funk2_memblock__byte_num(perfect_size_block) >= byte_num) {
    rbt_tree__remove(&(this->free_memory_tree), (rbt_node_t*)perfect_size_block);
    perfect_size_block->used = 1;
  } else {
    if (! perfect_size_block) {
      status("there are no free memory blocks left that are at least " u64__fstr " bytes.", (u64)byte_num);
    } else {
      status("largest memory block is too small (need " f2size_t__fstr " bytes, have " f2size_t__fstr " bytes).", byte_num, funk2_memblock__byte_num(perfect_size_block));
    }
    perfect_size_block = NULL; // largest free memory block is not large enough.  fail.
  }
  funk2_memorypool__debug_memory_test(this, 4); // memory assumption violation here (block is taken out of free list and not added to used list, yet).
  return perfect_size_block;
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
  // save compressed memory image
  {
    status("funk2_memorypool__save_to_stream: compressing memorypool.");
    u64 compressed_length = 0;
    u8* compressed_data;
    {
      u8*       uncompressed_data   = (u8*)from_ptr(this->dynamic_memory.ptr);
      u64       uncompressed_length = this->total_global_memory;
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
    
    status("funk2_memorypool__save_to_stream: dynamic_memory.ptr=0x" X64__fstr " " u64__fstr " total_global_memory=" u64__fstr " compressed_length=" u64__fstr "  (writing compressed image to disk now)",
	   this->dynamic_memory.ptr, this->dynamic_memory.ptr,
	   this->total_global_memory,
	   (u64)compressed_length);
    
    safe_write(fd, to_ptr(compressed_data), compressed_length);
    
    status("funk2_memorypool__save_to_stream: done writing memorypool image to disk.");
    
    f2__free(to_ptr(compressed_data));
  }
  {
    this->used_memory_tree.memorypool_beginning = this->global_f2ptr_offset;
    rbt_tree__save_to_stream(&(this->used_memory_tree), fd);
  }
  {
    this->free_memory_tree.memorypool_beginning = this->global_f2ptr_offset;
    rbt_tree__save_to_stream(&(this->free_memory_tree), fd);
  }
}

void funk2_memorypool__decompress_and_free_compressed_data_for_loading(funk2_memorypool_t* this) {
  status("funk2_memorypool__load_from_stream: decompressing memorypool image.");
  {
    u64 dest_length = 0;
    boolean_t failure = zlib__inflate(from_ptr(this->dynamic_memory.ptr), &dest_length, this->temporary_compressed_data_for_loading, this->temporary_compressed_data_for_loading__length);
    if (failure) {
      error(nil, "funk2_memorypool__load_from_stream error: failed to inflate image using zlib.");
    }
    status("funk2_memorypool__load_from_stream: decompressed memory image.  dest_length=" u64__fstr "  total_global_memory=" u64__fstr, dest_length, (u64)(this->total_global_memory));
    if (dest_length != this->total_global_memory) {
      error(nil, "funk2_memorypool__load_from_stream error: decompressed memory image is not the correct size.");
    }
  }
  status("funk2_memorypool__load_from_stream: done decompressing memorypool image.");
  
  f2__free(to_ptr(this->temporary_compressed_data_for_loading));
  this->temporary_compressed_data_for_loading = NULL;
}

void funk2_memorypool__load_from_stream(funk2_memorypool_t* this, int fd) {
  // load compressed memory image
  {
    f2size_t size_i;
    
    safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    this->temporary_compressed_data_for_loading__length = size_i;
    
    safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    this->total_global_memory = size_i;
    status("funk2_memorypool__load_from_stream: total_global_memory=" u64__fstr ".", (u64)(this->total_global_memory));
    
    safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    this->next_unique_block_id = size_i;
    
    f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
    f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, this->total_global_memory);
    
    this->temporary_compressed_data_for_loading = (u8*)from_ptr(f2__malloc(this->temporary_compressed_data_for_loading__length));
    
    status("funk2_memorypool__load_from_stream: loading compressed memorypool image from disk.");
    safe_read(fd, to_ptr(this->temporary_compressed_data_for_loading), this->temporary_compressed_data_for_loading__length);
    status("funk2_memorypool__load_from_stream: done loading compressed memorypool image from disk.");
    
    funk2_memorypool__decompress_and_free_compressed_data_for_loading(this);
  }
  rbt_tree__load_from_stream(&(this->used_memory_tree), fd);
  rbt_tree__load_from_stream(&(this->free_memory_tree), fd);
}

