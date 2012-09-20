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

// funk2_memorypool

void funk2_memorypool__init(funk2_memorypool_t* this, u64 pool_index) {
  funk2_processor_mutex__init(&(this->global_memory_allocate_mutex));
  this->pool_index                           = pool_index;
  this->should_enlarge_memory_now            = boolean__false;
  this->total_allocated_memory_since_last_gc = 0;
  this->bytes_allocated_count                = 0;
  this->next_unique_block_id                 = 0;
  this->total_global_memory                  = ((((sizeof(funk2_memblock_t) + F2__INITIAL_MEMORY) - 1) >> f2ptr_block__bit_num) + 1) << f2ptr_block__bit_num;
  f2dynamicmemory__init_and_alloc(&(this->dynamic_memory), this->total_global_memory);
  
  this->end_of_blocks = funk2_memorypool__end_of_blocks(this);
  
  this->total_free_memory = this->total_global_memory;
  
  this->global_f2ptr_offset = to_ptr(this->dynamic_memory.ptr - 1);
  funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(this->dynamic_memory.ptr);
  funk2_memblock__init(block, this->total_global_memory, 0);
  funk2_memblock__previous_byte_num(block) = 0; // we shouldn't ever use this.
  
  this->last_block_byte_num = this->total_global_memory;
  
  funk2_heap__init(&(this->free_memory_heap));
  funk2_heap__insert(&(this->free_memory_heap), (funk2_heap_node_t*)block);
  
  this->free_memory_heap__load_buffer__length = 0;
  this->free_memory_heap__load_buffer         = NULL;
  
  funk2_hash__init(&(this->temporary_bytes_freed_count_fiber_hash), 10);
  
  funk2_memorypool__debug_memory_test(this, 1);
}

void funk2_memorypool__destroy(funk2_memorypool_t* this) {
  f2dynamicmemory__destroy_and_free(&(this->dynamic_memory));
  funk2_hash__destroy(&(this->temporary_bytes_freed_count_fiber_hash));
  funk2_heap__destroy(&(this->free_memory_heap));
}

f2size_t funk2_memorypool__total_used_memory(funk2_memorypool_t* this) {
  f2size_t used_memory_count = 0;
  {
    funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(this->dynamic_memory.ptr));
    funk2_memblock_t* end_of_blocks = funk2_memorypool__end_of_blocks(this);
    //funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
    while(iter < end_of_blocks) {
      if (iter->used) {
	used_memory_count += funk2_memblock__byte_num(iter);
      }
      iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
    }
    release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
  }
  //printf("\ntotal used memory = %d", used_memory_count); fflush(stdout);
  return used_memory_count;
}

f2size_t funk2_memorypool__total_free_memory(funk2_memorypool_t* this) {
  f2size_t free_memory_count = 0;
  funk2_heap__iteration(&(this->free_memory_heap), node,
			funk2_memblock_t* block = (funk2_memblock_t*)node;
			free_memory_count += funk2_memblock__byte_num(block);
			);
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
}

f2ptr raw__memorypool__assert_valid(f2ptr cause, s64 pool_index) {
  if (pool_index < 0 || pool_index >= memory_pool_num) {
    return f2larva__new(cause, 2, nil);
  }
  
  // This may not work anymore if GC occurs during our check...
  //
  
  f2ptr return_value = nil;
  status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") beginning.", pool_index);
  {
    funk2_user_thread_controller__need_wait__set(&(__funk2.user_thread_controller), boolean__true);
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
    funk2_user_thread_controller__need_wait__set(&(__funk2.user_thread_controller), boolean__false);
  }
  if (return_value == nil) {
    status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") memorypool is valid.", pool_index);
  } else {
    status("raw__memorypool__assert_valid(pool_index=" s64__fstr ") memorypool is invalid.", pool_index);
  }
  return return_value;
}



void funk2_memorypool__change_total_memory_available(funk2_memorypool_t* this, f2size_t byte_num) {
  if (((u64)byte_num) > ((u64)pool_address__max_byte_num)) {
    status("funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed ((u64)byte_num) > ((u64)pool_address__max_byte_num), ((u64)" u64__fstr ") > ((u64)" u64__fstr ").",
	   ((u64)byte_num), ((u64)pool_address__max_byte_num));
    error(nil, "funk2_memorypool__change_total_memory_available error: tried to allocate more memory than is able to be addressed (are you using a 32 bit version still?).");
  }
  status("funk2_memorypool__change_total_memory_available(" f2size_t__fstr ")", byte_num);
  if (byte_num == this->total_global_memory) {
    return;
  }
  
  f2size_t old_total_global_memory = this->total_global_memory;
  if (byte_num <= old_total_global_memory) {
    error(nil, "funk2_memorypool__change_total_memory_available error: reducing memory pool size not yet implemented.");
  } else {
    f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
    status("funk2_memorypool__change_total_memory_available: old->ptr=0x" X64__fstr " " u64__fstr, old_dynamic_memory.ptr, old_dynamic_memory.ptr);
    f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, byte_num);
    status("funk2_memorypool__change_total_memory_available: new->ptr=0x" X64__fstr " " u64__fstr, this->dynamic_memory.ptr, this->dynamic_memory.ptr);
    this->global_f2ptr_offset = this->dynamic_memory.ptr - 1;
    this->total_global_memory = byte_num;
    // update all absolute pointers by a constant offset, if memory has moved
    if (this->dynamic_memory.ptr != old_dynamic_memory.ptr) {
      s64 byte_diff = (s64)(this->dynamic_memory.ptr - old_dynamic_memory.ptr);
      // fix global environment pointer, if it is in this pool
      if (__funk2.memory.global_environment_ptr >= old_dynamic_memory.ptr &&
	  __funk2.memory.global_environment_ptr <  old_dynamic_memory.ptr + old_total_global_memory) {
	if (__funk2.memory.global_environment_ptr) {
	  __funk2.memory.global_environment_ptr = __funk2.memory.global_environment_ptr + byte_diff;
	}
      }
      // fix pointers in heap
      {
	s64 index;
	for (index = 1; index <= this->free_memory_heap.node_array_used_num; index ++) {
	  this->free_memory_heap.node_array[index] = (funk2_heap_node_t*)(((u8*)this->free_memory_heap.node_array[index]) + byte_diff);
	}
      }
    }
    // make new free block at the old end of blocks
    {
      funk2_memblock_t* old_end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + old_total_global_memory);
      funk2_memblock__byte_num(old_end_of_blocks) = (byte_num - old_total_global_memory);
      {
	funk2_memblock_t* old_last_block = (funk2_memblock_t*)(((u8*)old_end_of_blocks) - this->last_block_byte_num);
	funk2_memblock__previous_byte_num(old_end_of_blocks) = funk2_memblock__byte_num(old_last_block);
      }
      this->last_block_byte_num = funk2_memblock__byte_num(old_end_of_blocks);
      old_end_of_blocks->used = 0;
      funk2_heap__insert(&(this->free_memory_heap), (funk2_heap_node_t*)old_end_of_blocks);
      status("funk2_memorypool__change_total_memory_available: created new block with size funk2_memblock__byte_num(last) = " f2size_t__fstr, funk2_memblock__byte_num(old_end_of_blocks));
      release__assert(funk2_memblock__byte_num(old_end_of_blocks) > 0, nil, "(funk2_memblock__byte_num(old_end_of_blocks) >= 0) should be enough free space to reduce memory block.");
    }
    this->total_free_memory += (byte_num - old_total_global_memory);
    this->end_of_blocks = funk2_memorypool__end_of_blocks(this);
  }
  funk2_memorypool__debug_memory_test(this, 2);
}

void funk2_memorypool__shrink_last_free_block(funk2_memorypool_t* this, f2size_t byte_num) {
  if (byte_num < memblock__minimum_size) {
    error(nil, "funk2_memorypool__shrink_last_free_block fatal error: cannot attempt to resize block to size smmaller than memblock__minimum_size.");
  }
  funk2_memblock_t* old_end_of_blocks       = funk2_memorypool__end_of_blocks(this);
  u64               old_last_block_byte_num = this->last_block_byte_num; 
  if (old_last_block_byte_num > byte_num) {
    funk2_memblock_t* last_block = (funk2_memblock_t*)(((u8*)old_end_of_blocks) - old_last_block_byte_num);
    if (! last_block->used) {
      funk2_heap__remove(&(this->free_memory_heap), (funk2_heap_node_t*)last_block); 
      {
	u64 byte_num_diff = (old_last_block_byte_num - byte_num);
	funk2_memblock__byte_num(last_block) = byte_num;
	this->total_free_memory       -= byte_num_diff;
      	this->total_global_memory     -= byte_num_diff;
	this->dynamic_memory.byte_num -= byte_num_diff;
	this->last_block_byte_num      = byte_num;
	this->end_of_blocks            = funk2_memorypool__end_of_blocks(this);
      }
      funk2_heap__insert(&(this->free_memory_heap), (funk2_heap_node_t*)last_block);
    }
  }
}

void funk2_memorypool__free_memory_heap__insert(funk2_memorypool_t* this, funk2_memblock_t* block) {
  funk2_heap__insert(&(this->free_memory_heap), (funk2_heap_node_t*)block);
}

void funk2_memorypool__free_memory_heap__remove(funk2_memorypool_t* this, funk2_memblock_t* block) {
  funk2_heap__remove(&(this->free_memory_heap), (funk2_heap_node_t*)block);
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
  status("defragmentation of funk2_memorypool not yet implemented.");
  return did_something;
}


void funk2_memorypool__increment_creation_fibers_bytes_freed_count(funk2_memorypool_t* this) {
  funk2_hash__iteration(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber, relative_bytes_freed_count,
			raw__fiber__increment_bytes_freed_count(nil, creation_fiber, relative_bytes_freed_count);
			);
  funk2_hash__remove_all(&(this->temporary_bytes_freed_count_fiber_hash));
}


void funk2_memorypool__remove_freed_fiber_bytes_freed_counts(funk2_memorypool_t* this) {
  {
    funk2_set_t remove_creation_fiber_set;
    funk2_set__init(&remove_creation_fiber_set);
    funk2_hash__key__iteration(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber,
			       funk2_memblock_t* creation_fiber_memblock = ((funk2_memblock_t*)(__f2ptr_to_ptr(creation_fiber)));
			       if (! creation_fiber_memblock->used) {
				 funk2_set__add(&remove_creation_fiber_set, creation_fiber);
			       }
			       );
    funk2_set__iteration(&remove_creation_fiber_set, creation_fiber,
			 funk2_hash__remove(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber);
			 );
    funk2_set__destroy(&remove_creation_fiber_set);
  }
}

void funk2_memorypool__user_flush_creation_fiber_bytes_freed_counts(f2ptr cause, funk2_memorypool_t* this) {
  if (this->temporary_bytes_freed_count_fiber_hash.key_count != 0) {
    funk2_hash__iteration(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber, relative_bytes_freed_count,
			  raw__fiber__increment_bytes_freed_count(cause, creation_fiber, relative_bytes_freed_count);
			  );
    funk2_hash__remove_all(&(this->temporary_bytes_freed_count_fiber_hash));
  }
}

void funk2_memorypool__free_used_block(funk2_memorypool_t* this, funk2_memblock_t* block) {
  // remove block from used list and set to free
  debug__assert(block->used, nil, "attempting to free a block that is already free.");
  block->used = 0;
  this->total_free_memory += funk2_memblock__byte_num(block);
  {
    f2ptr creation_fiber = ((ptype_block_t*)block)->creation_fiber;
    if (creation_fiber != nil) {
      u64 old_value = 0;
      if (funk2_hash__contains(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber)) {
	old_value = funk2_hash__lookup(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber);
      }
      u64 new_value = old_value + funk2_memblock__byte_num(block);
      funk2_hash__add(&(this->temporary_bytes_freed_count_fiber_hash), creation_fiber, new_value);
    }
  }
  
  // remove reference counts
  {
    ptype_block_t* ptype_block = (ptype_block_t*)block;
    {
      f2ptr             cause       = ptype_block->cause;
      ptr               cause_ptr   = __f2ptr_to_ptr(cause);
      funk2_memblock_t* cause_block = (funk2_memblock_t*)from_ptr(cause_ptr);
      funk2_memblock__decrement_reference_count(cause_block, cause, &(__funk2.garbage_collector));
    }
    {
      f2ptr             creation_fiber       = ptype_block->creation_fiber;
      ptr               creation_fiber_ptr   = __f2ptr_to_ptr(creation_fiber);
      funk2_memblock_t* creation_fiber_block = (funk2_memblock_t*)from_ptr(creation_fiber_ptr);
      funk2_memblock__decrement_reference_count(creation_fiber_block, creation_fiber, &(__funk2.garbage_collector));
    }
    switch(ptype_block->block.ptype) {
    case ptype_free_memory:              error(nil, "block of type free_memory in garbage collector.");
    case ptype_integer:                  break;
    case ptype_double:                   break;
    case ptype_float:                    break;
    case ptype_pointer:                  break;
    case ptype_scheduler_cmutex:         break;
    case ptype_cmutex:                   break;
    case ptype_scheduler_creadwritelock: break;
    case ptype_creadwritelock:           break;
    case ptype_char:                     break;
    case ptype_string:                   break;
    case ptype_symbol:                   break;
    case ptype_chunk:                    break;
    case ptype_simple_array: {
      s64 i;
      f2ptr_t* iter = ((ptype_simple_array_block_t*)ptype_block)->slot;
      for (i = ((ptype_simple_array_block_t*)ptype_block)->length; i > 0; i --) {
	funk2_memblock_t* subblock = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(iter->data));
	funk2_memblock__decrement_reference_count(subblock, iter->data, &(__funk2.garbage_collector));
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
	sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(ptype_block->block.ptype));
	error(nil, str);
      }
    }
  }
  
  funk2_memblock_t* end_of_blocks = this->end_of_blocks;
  
  // try to join block with next block if next block is also free
  {
    funk2_memblock_t* next_block = (funk2_memblock_t*)(((u8*)block) + funk2_memblock__byte_num(block));
    if ((next_block < end_of_blocks) &&
	(! next_block->used)) {
      // remove next block from free memory heap
      funk2_memorypool__free_memory_heap__remove(this, next_block);
      // increase the size of this block to include next block
      u64 block__byte_num = funk2_memblock__byte_num(block) + funk2_memblock__byte_num(next_block);
      funk2_memblock__byte_num(block) = block__byte_num;
      {
	funk2_memblock_t* block_after = (funk2_memblock_t*)(((u8*)block) + block__byte_num);
	if (block_after < end_of_blocks) {
	  funk2_memblock__previous_byte_num(block_after) = block__byte_num;
	} else {
	  this->last_block_byte_num = block__byte_num;
	}
      }
    }
  }
  
  // try to join block with previous block if next block is also free
  {
    funk2_memblock_t* beginning_of_blocks = funk2_memorypool__beginning_of_blocks(this);
    if (block != beginning_of_blocks) {
      funk2_memblock_t* previous_block = (funk2_memblock_t*)(((u8*)block) - funk2_memblock__previous_byte_num(block));
      if (! previous_block->used) {
	// remove previous block from free memory heap
	funk2_memorypool__free_memory_heap__remove(this, previous_block);
	// increase the size of previous block to include this block
	u64 previous_block__byte_num = funk2_memblock__byte_num(previous_block) + funk2_memblock__byte_num(block);
	funk2_memblock__byte_num(previous_block) = previous_block__byte_num;
	{
	  funk2_memblock_t* block_after = (funk2_memblock_t*)(((u8*)previous_block) + previous_block__byte_num);
	  if (block_after < end_of_blocks) {
	    funk2_memblock__previous_byte_num(block_after) = previous_block__byte_num;
	  } else {
	    this->last_block_byte_num = previous_block__byte_num;
	  }
	}
	// swap block to be previous block
	block = previous_block;
      }
    }
  }
  
  // add block to free list
  funk2_memorypool__free_memory_heap__insert(this, block);
}

// look for memory block that is not used and is big enough for us to split up
funk2_memblock_t* funk2_memorypool__find_splittable_free_block_and_unfree(funk2_memorypool_t* this, f2size_t byte_num) {
  funk2_memorypool__debug_memory_test(this, 4);
  funk2_memblock_t* maximum_block = NULL;
  if (! funk2_heap__is_empty(&(this->free_memory_heap))) {
    maximum_block = (funk2_memblock_t*)funk2_heap__remove_maximum(&(this->free_memory_heap));
    if (maximum_block && funk2_memblock__byte_num(maximum_block) >= byte_num) {
      maximum_block->used = 1;
    } else {
      funk2_heap__insert(&(this->free_memory_heap), (funk2_heap_node_t*)maximum_block);
      if (! maximum_block) {
	status("there are no free memory blocks left that are at least " u64__fstr " bytes.", (u64)byte_num);
      } else {
	status("largest memory block is too small (need " f2size_t__fstr " bytes, have " f2size_t__fstr " bytes).", byte_num, funk2_memblock__byte_num(maximum_block));
      }
      maximum_block = NULL; // largest free memory block is not large enough.  fail.
    }
  }
  funk2_memorypool__debug_memory_test(this, 4); // memory assumption violation here (block is taken out of free list and not added to used list, yet).
  return maximum_block;
}

u64 funk2_memorypool__maximum_block__byte_num(funk2_memorypool_t* this) {
  if (funk2_heap__is_empty(&(this->free_memory_heap))) {
    return 0;
  }
  funk2_memblock_t* maximum_block = (funk2_memblock_t*)funk2_heap__maximum(&(this->free_memory_heap));
  if (! maximum_block) {
    return 0;
  }
  return funk2_memblock__byte_num(maximum_block);
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

boolean_t funk2_memorypool__check_all_gc_colors_valid(funk2_memorypool_t* this, funk2_memory_t* memory, funk2_garbage_collector_pool_t* garbage_collector_pool) {
  boolean_t         found_invalid = boolean__false;
  funk2_memblock_t* iter          = (funk2_memblock_t*)(from_ptr(this->dynamic_memory.ptr));
  funk2_memblock_t* end_of_blocks = (funk2_memblock_t*)(((u8*)from_ptr(this->dynamic_memory.ptr)) + this->total_global_memory);
  while(iter < end_of_blocks) {
    if (! funk2_garbage_collector_pool__memblock_color_is_valid(garbage_collector_pool, iter)) {
      status("funk2_memory__check_all_gc_colors_valid error: found color inconsistency for memblock.");
      found_invalid = boolean__true;
      error(nil, "funk2_memory__check_all_gc_colors_valid error: found color inconsistency for memblock.");
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  return found_invalid;
}

void funk2_memorypool__compress_for_saving(funk2_memorypool_t* this) {
  status("funk2_memorypool__save_to_stream: compressing memorypool.");
  u64 compressed_length = 0;
  u8* compressed_data;
  {
    u8* uncompressed_data   = (u8*)from_ptr(this->dynamic_memory.ptr);
    u64 uncompressed_length = this->total_global_memory;
    compressed_length       = 0;
    boolean_t failure       = zlib__deflate_length(uncompressed_data, uncompressed_length, &compressed_length);
    if (failure) {
      error(nil, "funk2_memorypool__save_to_stream error: failed to deflate image using zlib.");
    }
    compressed_data = (u8*)from_ptr(f2__malloc(compressed_length));
    failure         = zlib__deflate(compressed_data, &compressed_length, uncompressed_data, uncompressed_length);
    if (failure) {
      error(nil, "funk2_memorypool__save_to_stream error: failed to deflate image using zlib.");
    }
  }
  this->temporary_compressed_data_for_saving__length = compressed_length;
  this->temporary_compressed_data_for_saving         = compressed_data;
}

void funk2_memorypool__write_compressed_to_stream(funk2_memorypool_t* this, int fd) {
  u64 compressed_length = this->temporary_compressed_data_for_saving__length;
  u8* compressed_data   = this->temporary_compressed_data_for_saving;
  this->temporary_compressed_data_for_saving__length = 0;
  this->temporary_compressed_data_for_saving         = NULL;
  {
    f2size_t size_i;
    size_i = compressed_length;           safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    size_i = this->total_global_memory;   safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    size_i = this->total_free_memory;     safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    size_i = this->next_unique_block_id;  safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    size_i = this->bytes_allocated_count; safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    
    status("funk2_memorypool__save_to_stream: dynamic_memory.ptr=0x" X64__fstr " " u64__fstr " total_global_memory=" u64__fstr " compressed_length=" u64__fstr "  (writing compressed image to disk now)",
	   this->dynamic_memory.ptr, this->dynamic_memory.ptr,
	   this->total_global_memory,
	   (u64)compressed_length);
    
    safe_write(fd, to_ptr(compressed_data), compressed_length);
    
    status("funk2_memorypool__save_to_stream: done writing memorypool image to disk.");
    
    f2__free(to_ptr(compressed_data));
  }
  {
    f2size_t size_i = this->global_f2ptr_offset;
    safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
  }
  
  //
  {
    u64                 save_buffer__length = funk2_heap__size(&(this->free_memory_heap));
    funk2_heap_node_t** save_buffer         = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * save_buffer__length));
    {
      f2size_t size_i = save_buffer__length;
      safe_write(fd, to_ptr(&size_i), sizeof(f2size_t));
    }
    {
      u64 index = 0;
      funk2_heap__iteration(&(this->free_memory_heap), node,
			    save_buffer[index] = node;
			    index ++;
			    );
    }
    safe_write(fd, to_ptr(save_buffer), sizeof(funk2_heap_node_t*) * save_buffer__length);
    f2__free(to_ptr(save_buffer));
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

  this->end_of_blocks = funk2_memorypool__end_of_blocks(this);
}

void funk2_memorypool__rebuild_memory_from_image(funk2_memorypool_t* this) {
  
  status("funk2_memorypool__rebuild_memory_from_image: here.");
  
  status("funk2_memorypool__rebuild_memory_from_image: rebuilding free_memory_heap from load buffer.");
  funk2_heap__destroy(&(this->free_memory_heap));
  funk2_heap__init(&(this->free_memory_heap));
  {
    s64 global_f2ptr_difference = (((s64)this->global_f2ptr_offset) - ((s64)this->free_memory_heap__load_buffer__global_f2ptr_offset));
    
    // chonk
    {
      u64 index;
      for (index = 0; index < this->free_memory_heap__load_buffer__length; index ++) {
	funk2_heap_node_t* node = this->free_memory_heap__load_buffer[index];
	node = ((funk2_heap_node_t*)(((u8*)node) + global_f2ptr_difference));
	//status("funk2_memorypool__rebuild_memory_from_image: compiling free_memory_heap from load buffer (index = " u64__fstr ").", index);
	funk2_heap__insert(&(this->free_memory_heap), node);
      }
    }
    
    f2__free(to_ptr(this->free_memory_heap__load_buffer));
    this->free_memory_heap__load_buffer__length = 0;
    this->free_memory_heap__load_buffer         = NULL;
  }
  status("funk2_memorypool__rebuild_memory_from_image: done.");
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
    this->total_free_memory = size_i;
    status("funk2_memorypool__load_from_stream: total_free_memory=" u64__fstr ".", (u64)(this->total_free_memory));
    
    safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    this->next_unique_block_id = size_i;
    
    safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    this->bytes_allocated_count = size_i;
    
    f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(this->dynamic_memory), sizeof(f2dynamicmemory_t));
    f2dynamicmemory__realloc(&(this->dynamic_memory), &old_dynamic_memory, this->total_global_memory);
    
    this->temporary_compressed_data_for_loading = (u8*)from_ptr(f2__malloc(this->temporary_compressed_data_for_loading__length));
    
    status("funk2_memorypool__load_from_stream: loading compressed memorypool image from disk.");
    safe_read(fd, to_ptr(this->temporary_compressed_data_for_loading), this->temporary_compressed_data_for_loading__length);
    status("funk2_memorypool__load_from_stream: done loading compressed memorypool image from disk.");
    
    //funk2_memorypool__decompress_and_free_compressed_data_for_loading(this);
  }
  
  ptr old_global_f2ptr_offset; {
    f2size_t size_i; safe_read(fd, to_ptr(&size_i), sizeof(f2size_t));
    old_global_f2ptr_offset = size_i;
  }
  this->free_memory_heap__load_buffer__global_f2ptr_offset = old_global_f2ptr_offset;
  
  status("funk2_memorypool__load_from_stream: loading free_memory_heap from disk.");
  {
    u64 node_count; {f2size_t size_i; safe_read(fd, to_ptr(&size_i), sizeof(f2size_t)); node_count = size_i;}
    status("funk2_memorypool__load_from_stream: loading free_memory_heap from disk (node_count = " u64__fstr ").", node_count);
    
    this->free_memory_heap__load_buffer__length = node_count;
    this->free_memory_heap__load_buffer         = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * this->free_memory_heap__load_buffer__length));
    
    safe_read(fd, to_ptr(this->free_memory_heap__load_buffer), sizeof(funk2_heap_node_t*) * this->free_memory_heap__load_buffer__length);
  }
  
  status("funk2_memorypool__load_from_stream: done.");
}

