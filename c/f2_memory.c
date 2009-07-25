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

void assert_failed(f2ptr thread, char* filename, int line_num, char* str) {
  status("*** %s:%d> assertion failed, '%s' ***", filename, line_num, str);
  fprintf(stderr, "\n*** %s:%d> assertion failed, '%s' ***\n", filename, line_num, str);
  exit(-1);
}

ptr malloc_executable(size_t required_bytes) {
  size_t page_size   = getpagesize();
  size_t alloc_bytes = (((required_bytes - 1) / page_size) + 1) * page_size;
  void* p = malloc(alloc_bytes);
  if (! p) {
    perror("malloc_executable() malloc");
    error(nil, "malloc_executable malloc failed.");
  }
  return to_ptr(p);
}

void free_executable(ptr p) {
  munmap(from_ptr(p), 1);
}

// funk2_memory

void funk2_memory__init(funk2_memory_t* this) {
  this->global_environment_ptr   = to_ptr(NULL);
  this->global_environment_f2ptr = nil;
  
  this->memblock__last_x       =  0.0;
  this->memblock__last_y       =  0.0;
  this->memblock__last_z       =  0.0;
  this->memblock__render_on    =  1;
  this->memblock__render_noise =  2.5;
  
  this->memory_handling_thread = pthread_self();
  this->bootstrapping_mode     = boolean__true;
}

void funk2_memory__destroy(funk2_memory_t* this) {
}



// only used once to get initial memory block
ptr f2__malloc(f2size_t byte_num) {
  ptr this = malloc_executable(byte_num);
  if (! this) {error(nil, "f2__malloc error: out of memory.");}
  return this;
}

void f2__free(ptr this) {
  free_executable(this);
}

ptr f2__new_alloc(ptr this, f2size_t old_byte_num, f2size_t new_byte_num) {
  //printf ("\nf2__new_alloc: this         = %x", (uint)this);
  //printf ("\nf2__new_alloc: old_byte_num = %d", (int)old_byte_num);
  //printf ("\nf2__new_alloc: new_byte_num = %d", (int)new_byte_num);
  //fflush(stdout);
  ptr new_mem = f2__malloc(new_byte_num);
  memcpy(from_ptr(new_mem), from_ptr(this), (old_byte_num < new_byte_num) ? old_byte_num : new_byte_num);
  f2__free(this);
  return new_mem;
}

void memblock__init(memblock_t* block, f2size_t byte_num, int used, int gc_touch) {
  memblock__byte_num(block)               = byte_num;
  block->used                             = used;
  block->gc_touch                         = gc_touch;
  block->generation_num                   = 0;
}

void funk2_memorypool__init(funk2_memorypool_t* pool) {
  funk2_processor_mutex__init(&(pool->global_memory_allocate_mutex));
  pool->disable_gc                           = 0;
  pool->should_run_gc                        = boolean__false;
  pool->should_enlarge_memory_now            = boolean__false;
  pool->total_allocated_memory_since_last_gc = 0;
  pool->next_unique_block_id                 = 0;
  pool->total_global_memory = sizeof(memblock_t) + F2__INITIAL_MEMORY;
  f2dynamicmemory__init_and_alloc(&(pool->dynamic_memory), sizeof(memblock_t) + F2__INITIAL_MEMORY);
  
  pool->total_free_memory = pool->total_global_memory;
  
  pool->global_f2ptr_offset = to_ptr(funk2_memorypool__memory__ptr(pool) - 1);
  memblock_t* block = (memblock_t*)from_ptr(funk2_memorypool__memory__ptr(pool));
  memblock__init(block, pool->total_global_memory, 0, 0);
  
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

void funk2_memorypool__signal_enter_bytecode(funk2_memorypool_t* this) {
  this->protected_alloc_array__reentrance_count ++;
}

void funk2_memorypool__signal_exit_bytecode(funk2_memorypool_t* this) {
  if (this->protected_alloc_array__reentrance_count == 0) {
    error(nil, "funk2_memorypool__signal_exit_bytecode error: bytecode reentrance underflow.");
  }
  this->protected_alloc_array__reentrance_count --;
  if (this->protected_alloc_array__reentrance_count == 0) {
    // bytecode stack is done
    this->protected_alloc_array__used_num = 0;
  }
}

// memory handling thread should never call this function
void funk2_memory__signal_enter_bytecode(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__signal_enter_bytecode(&(this->pool[pool_index]));
}

// memory handling thread should never call this function
void funk2_memory__signal_exit_bytecode(funk2_memory_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__signal_exit_bytecode(&(this->pool[pool_index]));
}

boolean_t valid_memblock_ptr(ptr p) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memblock_t* iter = (memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))));
    memblock_t* end_of_blocks = (memblock_t*)(((u8*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))))) + __funk2.memory.pool[pool_index].total_global_memory);
    int byte_num;
    while(iter < end_of_blocks) {
      if ((to_ptr(iter)) == p) {return 1;}
      byte_num = memblock__byte_num(iter);
      if (byte_num <= 0) {
	char str[1024];
	sprintf(str, "valid_memblock_ptr error: byte_num <= 0 (%d).", byte_num);
	error(nil, str);
      }
      iter = (memblock_t*)(((u8*)iter) + byte_num);
    }
  }
  return 0;
}

ptr debug__f2ptr_to_ptr(f2ptr f2p) {
  computer_id_t  computer_id  = __f2ptr__computer_id(f2p);
  pool_index_t   pool_index   = __f2ptr__pool_index(f2p);
  pool_address_t pool_address = __f2ptr__pool_address(f2p);
  debug__assert(computer_id == 0, nil, "computer_id != 0");
  if (computer_id != 0 || pool_address < 0 || pool_address >= __funk2.memory.pool[pool_index].total_global_memory) {
    printf("\ncomputer_id  = " computer_id__fstr,  computer_id);
    printf("\npool_index   = " pool_index__fstr,   pool_index);
    printf("\npool_address = " pool_address__fstr, pool_address);
    fflush(stdout);
    error(nil, "debug__f2ptr_to_ptr error: received invalid pointer.");
  }
  ptr p = __f2ptr_to_ptr(f2p);
#ifdef DEBUG_MEMORY_VALID_PTRS
  if (p && (! valid_memblock_ptr(p))) {
    char str[1024];
    sprintf(str, "debug__f2ptr_to_ptr error: invalid memblock f2ptr (%d).", (int)f2p);
    error(nil, str);
  }
#endif
  return p;
}

ptr debug__used_f2ptr_to_ptr(f2ptr f2p) {
  computer_id_t  computer_id  = __f2ptr__computer_id(f2p);
  pool_index_t   pool_index   = __f2ptr__pool_index(f2p);
  pool_address_t pool_address = __f2ptr__pool_address(f2p);
  if (computer_id != 0 || pool_address < 0 || pool_address >= __funk2.memory.pool[pool_index].total_global_memory) {
    printf("\ncomputer_id  = " computer_id__fstr,  computer_id);
    printf("\npool_index   = " pool_index__fstr,   pool_index);
    printf("\npool_address = " pool_address__fstr, pool_address);
    fflush(stdout);
    error(nil, "debug__used_f2ptr_to_ptr error: received invalid pointer.");
  }
  ptr p = __f2ptr_to_ptr(f2p);
#ifdef DEBUG_MEMORY_VALID_PTRS
  if (p && (! valid_memblock_ptr(p))) {
    char str[1024];
    sprintf(str, "debug__ptr_to_f2ptr error: invalid memblock f2ptr (%d).", (int)f2p);
    error(nil, str);
  }
#endif
  if (p) {
    memblock_t* block = (memblock_t*)from_ptr(p);
    if(! block->used) {
      error(nil, "debug__used_f2ptr_to_ptr error: referenced unused memory block.");
    }
  }
  return p;
}

// for some reason a raw #define screws things up with GC enabled... [or at least used to...  8-( ]
ptr fast__f2ptr_to_ptr(f2ptr f2p) {
  return (__f2ptr_to_ptr(f2p));
}

f2size_t total_used_memory(int pool_index) {
  f2size_t used_memory_count = 0;
  rbt_node_t* node = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
  while(node) {
    used_memory_count += memblock__byte_num((memblock_t*)node);
    node = rbt_node__next(node);
  }
  //printf("\ntotal used memory = %d", used_memory_count); fflush(stdout);
  return used_memory_count;
}

f2size_t total_free_memory(int pool_index) {
  f2size_t free_memory_count = 0;
  rbt_node_t* node = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].free_memory_tree));
  while(node) {
    free_memory_count += memblock__byte_num((memblock_t*)node);
    node = rbt_node__next(node);
  }
  //printf("\ntotal free memory = %d", free_memory_count); fflush(stdout);
  return free_memory_count;
}

void memory_test__dynamic_memory(int pool_index) {
  release__assert(__funk2.memory.pool[pool_index].dynamic_memory.byte_num == __funk2.memory.pool[pool_index].total_global_memory, nil, "memory_test: (__funk2.memory.pool[pool_index].dynamic_memory.byte_num == __funk2.memory.pool[pool_index].total_global_memory) failed.");
}

void memory_test__byte_num_zero(int pool_index) {
  memblock_t* iter = (memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))));
  memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
  while(iter < end_of_blocks) {
    release__assert(memblock__byte_num(iter) > 0, nil, "memory_test__byte_num_zero failed.");
    iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
}

void memory_test__all_known_types(int pool_index) {
  memblock_t* iter = (memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))));
  memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
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
	  sprintf(str, "unknown type (%ld) of block (%ld) in debugging pool[%ld] memory test.", (long)(ptype_block->ptype), (long)ptype_block, (long)pool_index);
	  release__assert(0, nil, str);
	}
      }
    }
    iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
  }
}

void memory_test(int pool_index) {
  status("testing memory in pool[%d]...", pool_index);
  status("__funk2.memory.pool[%d].total_free_memory = " f2size_t__fstr, pool_index, __funk2.memory.pool[pool_index].total_free_memory); fflush(stdout);
  status("total_free_memory(%d) = " f2size_t__fstr, pool_index, total_free_memory(pool_index)); fflush(stdout);
  release__assert(total_free_memory(pool_index) == __funk2.memory.pool[pool_index].total_free_memory, nil, "memory_test (total_free_memory() == __funk2.memory.pool[].total_free_memory) failure.");
  release__assert_and_on_failure((int)(total_used_memory(pool_index) + total_free_memory(pool_index)) == (int)__funk2.memory.pool[pool_index].total_global_memory, nil, "memory_test (total_used_memory() + total_free_memory() != __funk2.memory.pool[].total_global_memory) failure.",
				 int used_memory_num = total_used_memory(pool_index);
				 int free_memory_num = total_free_memory(pool_index);
				 printf("\ntotal_used_memory(%d)                       = %d", pool_index, (int)used_memory_num);
				 printf("\ntotal_free_memory(%d)                       = %d", pool_index, (int)free_memory_num);
				 printf("\ntotal_used_memory(%d) + total_free_memory() = %d", pool_index, (int)free_memory_num + used_memory_num);
				 printf("\n__funk2.memory.pool[%d].total_global_memory              = %d", pool_index, (int)__funk2.memory.pool[pool_index].total_global_memory);
				 fflush(stdout));
  memory_test__dynamic_memory(pool_index);
  memory_test__byte_num_zero(pool_index);
  memory_test__all_known_types(pool_index);
  {
    rbt_node_t* free_iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].free_memory_tree));
    // this should lock up if there is a loop in free list.
    while (free_iter) {
      free_iter = rbt_node__next(free_iter);
    }
  }
}

void pool__change_total_memory_available(int pool_index, f2size_t byte_num) {
  if(((u64)byte_num) > ((u64)f2ptr__pool_address__max_value)) {
    status("pool__change_total_memory_available error: tried to allocate more memory than is able to be addressed ((u64)byte_num) > ((u64)f2ptr__pool_address__max_value), ((u64)" u64__fstr ") > ((u64)" u64__fstr ").",
	   ((u64)byte_num), ((u64)f2ptr__pool_address__max_value));
    error(nil, "pool__change_total_memory_available error: tried to allocate more memory than is able to be addressed (are you using a 32 bit version still?).");
  }
  status("pool__change_total_memory_available(%d, " f2size_t__fstr ")", pool_index, byte_num); fflush(stdout);
  if (byte_num == __funk2.memory.pool[pool_index].total_global_memory) {return;}
  f2size_t         old_total_global_memory      = __funk2.memory.pool[pool_index].total_global_memory;
  f2dynamicmemory_t old_dynamic_memory; memcpy(&old_dynamic_memory, &(__funk2.memory.pool[pool_index].dynamic_memory), sizeof(f2dynamicmemory_t));
  f2dynamicmemory__realloc(&(__funk2.memory.pool[pool_index].dynamic_memory), &old_dynamic_memory, byte_num);
  __funk2.memory.pool[pool_index].global_f2ptr_offset = __funk2.memory.pool[pool_index].dynamic_memory.ptr - 1;
  __funk2.memory.pool[pool_index].total_global_memory = byte_num;
  if (__funk2.memory.pool[pool_index].dynamic_memory.ptr != old_dynamic_memory.ptr) {
    // need to fix pointers (globals, memblock__next(block))
    s64 byte_diff = (s64)(__funk2.memory.pool[pool_index].dynamic_memory.ptr - old_dynamic_memory.ptr);
    if (__funk2.memory.pool[pool_index].used_memory_tree.head)  {__funk2.memory.pool[pool_index].used_memory_tree.head = (rbt_node_t*)(((u8*)__funk2.memory.pool[pool_index].used_memory_tree.head) + byte_diff);}
    if (__funk2.memory.pool[pool_index].free_memory_tree.head)  {__funk2.memory.pool[pool_index].free_memory_tree.head = (rbt_node_t*)(((u8*)__funk2.memory.pool[pool_index].free_memory_tree.head) + byte_diff);}
    if (__funk2.memory.global_environment_ptr >= old_dynamic_memory.ptr &&
	__funk2.memory.global_environment_ptr <  old_dynamic_memory.ptr + old_total_global_memory) {
      if (__funk2.memory.global_environment_ptr) {__funk2.memory.global_environment_ptr = __funk2.memory.global_environment_ptr + byte_diff;}
    }
    memblock_t* iter = from_ptr(__funk2.memory.pool[pool_index].dynamic_memory.ptr);
    memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(__funk2.memory.pool[pool_index].dynamic_memory.ptr)) + old_total_global_memory);
    memblock_t* last = NULL;
    while(iter < end_of_blocks) {
      if (iter->rbt_node.parent) {iter->rbt_node.parent = (rbt_node_t*)(((u8*)(iter->rbt_node.parent) + byte_diff));}
      if (iter->rbt_node.left)   {iter->rbt_node.left   = (rbt_node_t*)(((u8*)(iter->rbt_node.left)   + byte_diff));}
      if (iter->rbt_node.right)  {iter->rbt_node.right  = (rbt_node_t*)(((u8*)(iter->rbt_node.right)  + byte_diff));}
      last = iter;
      iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
    }
    if (last->used) {
      release__assert(byte_num > old_total_global_memory, nil, "(byte_num > old_total_global_memory) because defragment was just called and there is still used memory at end.");
      memblock__byte_num(iter) = (byte_num - old_total_global_memory);
      iter->used     = 0;
      iter->gc_touch = 0;
      status("pool__change_total_memory_available: created new block with size memblock__byte_num(last) = " f2size_t__fstr, memblock__byte_num(iter));
      rbt_tree__insert(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)iter);
      release__assert(memblock__byte_num(iter) > 0, nil, "(memblock__byte_num(iter) >= 0) should be enough free space to reduce memory block.");
    } else {
      rbt_tree__remove(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)last);
      memblock__byte_num(last) += (byte_num - old_total_global_memory);
      rbt_tree__insert(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)last);
      status("pool__change_total_memory_available: increased last block size to memblock__byte_num(last) = " f2size_t__fstr, memblock__byte_num(last));
      release__assert(memblock__byte_num(last) > 0, nil, "(memblock__byte_num(last) >= 0) should be enough free space to reduce memory block.");
    }
  } else {
    if (byte_num > old_total_global_memory) {
      memblock_t* block = (memblock_t*)(((u8*)from_ptr(__funk2.memory.pool[pool_index].dynamic_memory.ptr)) + old_total_global_memory);
      memblock__byte_num(block) = (byte_num - old_total_global_memory);
      block->used     = 0;
      block->gc_touch = 0;
      rbt_tree__insert(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)block);
      release__assert(memblock__byte_num(block) > 0, nil, "(memblock__byte_num(block) > 0) should be enough free space to reduce memory block.");
    } else {
      release__assert(0, nil, "pool__change_total_memory_available error: not implemented yet.");
    }
  }
  __funk2.memory.pool[pool_index].total_free_memory += (byte_num - old_total_global_memory);
  debug_memory_test(pool_index, 1);
}

void clear_all_gc_touch_flags(int pool_index) {
  debug_memory_test(pool_index, 3);
  rbt_node_t* iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
  while (iter) {
    ((memblock_t*)iter)->gc_touch = 0;
    iter = rbt_node__next(iter);
  }
  debug_memory_test(pool_index, 3);
}

void clear_all_gc_touch_flags_before_generation(int pool_index, int generation_num) {
  debug_memory_test(pool_index, 3);
  rbt_node_t* iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
  while (iter) {
    if(((memblock_t*)iter)->generation_num < generation_num) {
      ((memblock_t*)iter)->gc_touch = 0;
    }
    iter = rbt_node__next(iter);
  }
  debug_memory_test(pool_index, 3);
}

void pool__link_memblock_to_freelist(int pool_index, memblock_t* block) {
  rbt_tree__insert(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)block);
}

u8 defragment_free_memory_blocks_in_place(int pool_index) {
  debug_memory_test(pool_index, 1);
  status("defragmenting __funk2.memory.pool[%d]", pool_index);
  u8 did_something = 0;
  memblock_t* iter = (memblock_t*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])));
  memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
  memblock_t* segment_first_free_block = NULL;
  rbt_tree__init(&(__funk2.memory.pool[pool_index].free_memory_tree), NULL);
  while(iter < end_of_blocks) {
    if (segment_first_free_block) {
      // we are currently in a segment of free blocks
      if (iter->used) {
	// we are no longer in a segment of free blocks
	segment_first_free_block = NULL;
      } else {
	// we should combine this free block with the others in this segment
	rbt_tree__remove(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)segment_first_free_block);
	memblock__byte_num(segment_first_free_block) += memblock__byte_num(iter);
	rbt_tree__insert(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)segment_first_free_block);
	iter = segment_first_free_block;
	// set did_something flag
	did_something = 1;
      }
    } else {
      if (! iter->used) {
	segment_first_free_block = iter;
	pool__link_memblock_to_freelist(pool_index, iter);
	//memblock__next(iter) = __funk2.memory.pool[pool_index].free_memory_blocks;
	//__funk2.memory.pool[pool_index].free_memory_blocks = iter;
      }
    }
    iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "failed.");
  debug_memory_test(pool_index, 1);
  return did_something;
}

void exp__gc_touch_all_referenced(ptr block_ptr);

void f2__gc_touch_all_referenced(f2ptr exp) {
  if(!exp) {return;}
  ptype_block_t* exp_block = (ptype_block_t*)from_ptr(__f2ptr_to_ptr(exp));
  if (exp_block->block.gc_touch) {return;}
  exp__gc_touch_all_referenced(to_ptr(exp_block));
}

#define GC_TOUCH_CIRCLE_BUF_START_SIZE (2)

typedef struct gc_touch_circle_buffer_s {
  int          num;
  memblock_t** start;
  memblock_t** end;
} gc_touch_circle_buffer_t;

boolean_t                __gc_touch_circle_buffer__initialized = 0;
gc_touch_circle_buffer_t __gc_touch_circle_buffer;

void gc_touch_circle_buffer__init() {
  __gc_touch_circle_buffer__initialized = 1;
  __gc_touch_circle_buffer.num   = GC_TOUCH_CIRCLE_BUF_START_SIZE;
  __gc_touch_circle_buffer.start = (memblock_t**)from_ptr(f2__malloc(GC_TOUCH_CIRCLE_BUF_START_SIZE * sizeof(memblock_t*)));
  __gc_touch_circle_buffer.end   = __gc_touch_circle_buffer.start + GC_TOUCH_CIRCLE_BUF_START_SIZE;  
}

memblock_t** __circle_buf_start_index;
memblock_t** __circle_buf_end_index;

void gc_touch_print_array(char* message) {
  ptr* iter = (ptr*)__gc_touch_circle_buffer.start;
  printf("\n%16s: {", message);
  for(; iter < (ptr*)__gc_touch_circle_buffer.end; iter++) {
    if (iter == (ptr*)__circle_buf_start_index) {
      printf(" *S*");
    }
    if (iter == (ptr*)__circle_buf_end_index) {
      printf(" *E*");
    }
    printf(" %lx", (long)*iter);
    fflush(stdout);
  }
  printf("}\n");
  fflush(stdout);
}

void gc_touch_circle_buffer__advance_end() {
  __circle_buf_end_index ++;
  if (__circle_buf_end_index == __gc_touch_circle_buffer.end) {
    __circle_buf_end_index = __gc_touch_circle_buffer.start;
  }
  if (__circle_buf_end_index == __circle_buf_start_index) {
    //gc_touch_print_array("buffer");
    //printf("\nincreasing buffer."); fflush(stdout);
    //printf("\n  start = %lx.", (int)(__circle_buf_start_index - __gc_touch_circle_buffer.start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(__circle_buf_end_index   - __gc_touch_circle_buffer.start)); fflush(stdout);
    //gc_touch_print_array("debug 0");
    // increasing size by two makes a lot of these memory moves conveniently easy.
    int old_num = __gc_touch_circle_buffer.num;
    __gc_touch_circle_buffer.num = old_num << 1;
    //printf("\n__gc_touch_circle_buffer.start = %x", (int)__gc_touch_circle_buffer.start);
    memblock_t** new_location = (memblock_t**)from_ptr(f2__new_alloc(to_ptr(__gc_touch_circle_buffer.start), sizeof(memblock_t*) * old_num, sizeof(memblock_t*) * __gc_touch_circle_buffer.num));
    //printf("\nnew_location = %lx", (int)new_location); fflush(stdout);
    int location_diff = new_location - __gc_touch_circle_buffer.start;
    __gc_touch_circle_buffer.start = new_location;
    
    __circle_buf_start_index += location_diff;
    __circle_buf_end_index   += location_diff;
    
    __gc_touch_circle_buffer.end = __gc_touch_circle_buffer.start + __gc_touch_circle_buffer.num;
    //printf("\n  copying %d bytes ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start).", ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start));
    //printf("\n  sizeof(memblock_t**) = %d bytes.", sizeof(memblock_t**));
    //printf("\n  old_num = %d", old_num);
    //gc_touch_print_array("just before copy");
    memcpy(__gc_touch_circle_buffer.start + old_num, __gc_touch_circle_buffer.start, ((u8*)__circle_buf_end_index) - ((u8*)__gc_touch_circle_buffer.start));
    //gc_touch_print_array("just after copy");
    __circle_buf_end_index += old_num;
    //printf("\ncircle_buffer size increased to %d.", __gc_touch_circle_buffer.num); fflush(stdout);
    //printf("\n  start = %lx.", (int)(__circle_buf_start_index - __gc_touch_circle_buffer.start)); fflush(stdout);
    //printf("\n  end   = %lx.", (int)(__circle_buf_end_index   - __gc_touch_circle_buffer.start)); fflush(stdout);
    //gc_touch_print_array("after all");
  }
}

void gc_touch__advance_start_index() {
  //printf("\nadvance start."); fflush(stdout);
  //printf("\n  start = %x.", (int)(__circle_buf_start_index - __gc_touch_circle_buffer.start)); fflush(stdout);
  //printf("\n  end   = %x.", (int)(__circle_buf_end_index   - __gc_touch_circle_buffer.start)); fflush(stdout);
  __circle_buf_start_index ++;
  if (__circle_buf_start_index == __gc_touch_circle_buffer.end) {
    __circle_buf_start_index = __gc_touch_circle_buffer.start;
  }
}

#define gc_touch__f2ptr(block_f2ptr)       {if (block_f2ptr) {ptr block_ptr = __f2ptr_to_ptr(block_f2ptr); debug__assert(!block_ptr || valid_memblock_ptr(block_ptr), nil, "valid_memblock_ptr(block_ptr) failed"); __circle_buf_end_index[0] = (memblock_t*)from_ptr(block_ptr); gc_touch_circle_buffer__advance_end();}}

void gc_touch__dptr(dptr_t* dptr) {
  gc_touch__f2ptr(dptr->p);
  gc_touch__f2ptr(dptr->tracing_on);
  gc_touch__f2ptr(dptr->trace);
}

void exp__gc_touch_all_referenced(ptr start_block_ptr) {
  
  release__assert(start_block_ptr, nil, "exp__gc_touch_all_referenced assertion failed: got null value.");
  
  ptype_block_t* start_block = (ptype_block_t*)from_ptr(start_block_ptr);
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    debug_memory_test(pool_index, 3);
  }
  if (! __gc_touch_circle_buffer__initialized) {gc_touch_circle_buffer__init();}
  __circle_buf_start_index    = __gc_touch_circle_buffer.start;
  __circle_buf_end_index      = __circle_buf_start_index + 1;
  __circle_buf_start_index[0] = (memblock_t*)start_block;
  ptype_block_t* block;
  while (__circle_buf_end_index != __circle_buf_start_index) {
    block = (ptype_block_t*)(__circle_buf_start_index[0]);
    if (block && (! block->block.gc_touch)) {
      gc_touch__f2ptr(block->cause);
      switch(block->ptype) {
      case ptype_free_memory:
	{
	  char str[1024];
	  sprintf(str,
		  "\nblock (valid=%lu) of type free_memory (%lu bytes) in garbage collector."
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
		  (unsigned long)valid_memblock_ptr(to_ptr(block)),
		  (unsigned long)memblock__byte_num((memblock_t*)block),
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
	  gc_touch__f2ptr(*iter);
	  iter ++;
	}
      } break;
      case ptype_traced_array: block->block.gc_touch = 1; {
	int i;
	dptr_t* iter = (dptr_t*)((ptype_traced_array_block_t*)block)->dptr_data;
	for (i = ((ptype_traced_array_block_t*)block)->length; i > 0; i --) {
	  gc_touch__dptr((dptr_t*)iter);
	  iter ++;
	}
      } break;
      case ptype_larva:        block->block.gc_touch = 1; break;
      default:
	{
	  char str[1024];
	  sprintf(str, "unknown type (%d) of block (valid=%d) in garbage collector.",
		  (int)(block->ptype), (int)valid_memblock_ptr(to_ptr(block)));
	  error(nil, str);
	}
      }
    }
    gc_touch__advance_start_index();
  }
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    debug_memory_test(pool_index, 3);
  }
}

u8 pool__free_all_gc_untouched_blocks(int pool_index) {
  debug_memory_test(pool_index, 1);
  u8 did_something = 0;
  rbt_node_t* iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
  rbt_node_t* next;
  while (iter) {
    next = rbt_node__next(iter);
    if (! ((memblock_t*)iter)->gc_touch) {
      // remove from used list
      rbt_tree__remove(&(__funk2.memory.pool[pool_index].used_memory_tree), iter);
      // set to free
      ((memblock_t*)iter)->used = 0;
      __funk2.memory.pool[pool_index].total_free_memory += memblock__byte_num((memblock_t*)iter);
      // add to free list
      pool__link_memblock_to_freelist(pool_index, (memblock_t*)iter);
      // set did_something flag
      did_something = 1;
    }
    iter = next;
  }
  debug_memory_test(pool_index, 1);
  return did_something;
}

u8 pool__free_all_gc_untouched_blocks_from_generation(int pool_index, int generation_num) {
  status("freeing all untouched blocks for pool %d, generation %d.", pool_index, generation_num);
  debug_memory_test(pool_index, 1);
  u8 did_something = 0;
  rbt_node_t* iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
  rbt_node_t* next;
  while (iter) {
    next = rbt_node__next(iter);
    if (((memblock_t*)iter)->generation_num <= generation_num && (! ((memblock_t*)iter)->gc_touch)) {
      // remove from used list
      rbt_tree__remove(&(__funk2.memory.pool[pool_index].used_memory_tree), iter);
      // set to free
      ((memblock_t*)iter)->used = 0;
      __funk2.memory.pool[pool_index].total_free_memory += memblock__byte_num((memblock_t*)iter);
      // add to free list
      pool__link_memblock_to_freelist(pool_index, (memblock_t*)iter);
      // set did_something flag
      did_something = 1;
    }
    iter = next;
  }
  debug_memory_test(pool_index, 1);
  return did_something;
}

void pool__touch_all_referenced_from_generation(int pool_index, int touch_generation_num) {
  memblock_t* iter = (memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))));
  memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used && iter->generation_num == touch_generation_num) {
      exp__gc_touch_all_referenced(to_ptr(iter));
    }
    iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
  }
}

void pool__increment_generation(int pool_index) {
  memblock_t* iter = (memblock_t*)(from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))));
  memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
  while(iter < end_of_blocks) {
    if (iter->used) {
      if (iter->generation_num < maximum_generation_num) {
	iter->generation_num ++;
      }
    }
    iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
  }
}

void gc_touch_all_protected_alloc_arrays() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    u64 i;
    for (i = 0; i < __funk2.memory.pool[pool_index].protected_alloc_array__used_num; i ++) {
      f2__gc_touch_all_referenced(__funk2.memory.pool[pool_index].protected_alloc_array[i]);
    }
  }
}

void garbage_collect__touch_everything(int generation_num) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    pool__touch_all_referenced_from_generation(pool_index, generation_num);
  }
  gc_touch_all_symbols();
  gc_touch_all_protected_alloc_arrays();
}

u8 garbage_collect_generation(int generation_num) {
  status("collecting garbage...");
  int pool_index;
#ifdef DEBUG_MEMORY
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    debug_memory_test(pool_index, 1);
  }
#endif
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    clear_all_gc_touch_flags_before_generation(pool_index, generation_num);
  }
  
  // this is where we touch everything we want to keep!
  garbage_collect__touch_everything(generation_num);
  
  u8 did_something = 0;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    did_something |= pool__free_all_gc_untouched_blocks_from_generation(pool_index, generation_num);
    __funk2.memory.pool[pool_index].total_allocated_memory_since_last_gc = 0;
  }
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    debug_memory_test(pool_index, 1);
  }
  status("...done collecting garbage."); fflush(stdout);
  return did_something;
}

u8 garbage_collect(int pool_index, f2size_t goal_free_block_byte_num) {
  //printf("\ngarbage_collect(%d, " f2size_t__fstr ") note: running.", pool_index, goal_free_block_byte_num); fflush(stdout);
  u8  did_something      = 0;
  int try_generation_num = 1;
  while (try_generation_num <= maximum_generation_num && (! did_something)) {
    status("garbage_collect try_generation_num=%d, maximum_generation_num=%d", try_generation_num, maximum_generation_num);
    //memblock_t* max_size_block = (memblock_t*)rbt_tree__maximum(&(__funk2.memory.pool[pool_index].free_memory_tree));
    //if (max_size_block && memblock__byte_num(max_size_block) >= goal_free_block_byte_num) {
    //  break;
    //}
    if (garbage_collect_generation(try_generation_num)) {
      did_something = 1;
    }
    try_generation_num ++;
  }
  int index;
  for (index = 0; index < memory_pool_num; index ++) {
    pool__increment_generation(index);
  }
  return did_something;
}

// look for memory block that is not used and is big enough for us to split up
memblock_t* find_splittable_free_block_and_unfree(int pool_index, f2size_t byte_num) {
  debug_memory_test(pool_index, 3);
  memblock_t* max_size_block = (memblock_t*)rbt_tree__maximum(&(__funk2.memory.pool[pool_index].free_memory_tree));
  if (max_size_block && memblock__byte_num(max_size_block) >= byte_num) {
    rbt_tree__remove(&(__funk2.memory.pool[pool_index].free_memory_tree), (rbt_node_t*)max_size_block);
    max_size_block->used = 1;
  } else {
    if (!max_size_block) {
      status("there are no free memory blocks left.");
    } else {
      status("largest memory block is too small (need " f2size_t__fstr " bytes, have " f2size_t__fstr " bytes).", byte_num, memblock__byte_num(max_size_block));
    }
    max_size_block = NULL; // largest free memory block is not large enough.  fail.
  }
  // debug_memory_test(pool_index, 3); // memory assumption violation here (block is taken out of free list and not added to used list, yet).
  return max_size_block;
}

ptr find_or_create_free_splittable_memblock_and_unfree(int pool_index, f2size_t byte_num) {
  ptr block = to_ptr(find_splittable_free_block_and_unfree(pool_index, byte_num));
  if (block) {return block;}  
  // If we get here then we failed to allocate enough memory from pool.
  debug_memory_test(pool_index, 3);
  if (defragment_free_memory_blocks_in_place(pool_index)) {
    block = to_ptr(find_splittable_free_block_and_unfree(pool_index, byte_num));
    if (block) {return block;}
  }
  __funk2.memory.pool[pool_index].should_run_gc = boolean__true;
  status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, pool_index, (f2size_t)(__funk2.memory.pool[pool_index].total_global_memory));
  status ("pool %d new size = " f2size_t__fstr, pool_index, (f2size_t)(__funk2.memory.pool[pool_index].total_global_memory + (__funk2.memory.pool[pool_index].total_global_memory >> 3) + byte_num));
  do {
    __funk2.memory.pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num = byte_num;
    __funk2.memory.pool[pool_index].should_enlarge_memory_now                         = boolean__true;
    __ptypes_please_wait_for_gc_to_take_place                                         = boolean__true;
    if (pthread_self() == __funk2.memory.memory_handling_thread) {
      funk2_memory_t* memory = (&__funk2.memory);
      if (! memory->bootstrapping_mode) {
	while (__ptypes_waiting_count < memory_pool_num) {
	  sched_yield();
	}
      }
      pool__change_total_memory_available(pool_index, memory->pool[pool_index].total_global_memory + (memory->pool[pool_index].total_global_memory >> 3) + memory->pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num);
      __funk2.memory.pool[pool_index].should_enlarge_memory_now__need_at_least_byte_num = 0;
      __funk2.memory.pool[pool_index].should_enlarge_memory_now                         = boolean__false;
      __ptypes_please_wait_for_gc_to_take_place                                         = boolean__false;
    } else {
      wait_politely();
    }
    block = to_ptr(find_splittable_free_block_and_unfree(pool_index, byte_num));
    if (block) {return block;}  
    // might need to loop more than once if two requests for memory from memory handling process occur at the same time.
  } while (1);
  // shouldn't get here if we have DYNAMIC_MEMORY defined.  if we are *only* using static_memory then this fails.  however, in distributed systems external memory systems could be asked for memory at this point (REMOTE_MEMORY?).
  printf("\nfind_free_memory_for_new_memblock error: shouldn't get here.  byte_num = %u\n", (unsigned int)byte_num);
  error(nil, "find_free_memory_for_new_memblock error: shouldn't get here.\n");
  return to_ptr(NULL);
}

// note that byte_num must be at least sizeof(u8) for ptype! because of type checking in garbage collection
f2ptr pool__memblock_f2ptr__try_new(int pool_index, f2size_t byte_num) {
  //if ((! __funk2.memory.bootstrapping_mode) && (pthread_self() == __funk2.memory.memory_handling_thread)) {
  //  status("warning: memory handling thread trying to allocate %d bytes from pool %d.", byte_num, pool_index);
  //}
  debug_memory_test(pool_index, 3);
  memblock_t* block = (memblock_t*)from_ptr(find_or_create_free_splittable_memblock_and_unfree(pool_index, byte_num));
#ifdef DEBUG_MEMORY
  if (block == NULL) {
    status("shouldn't ever get a NULL pointer here.");
    error(nil, "shouldn't ever get a NULL pointer here.");
  }
#endif
  if (memblock__byte_num(block) > byte_num + sizeof(memblock_t)) {
    memblock_t* new_block           = (memblock_t*)(((u8*)(block)) + byte_num);
    int         new_block__byte_num = memblock__byte_num(block) - byte_num;
    memblock__init(new_block, new_block__byte_num, 0, 0);
    
    pool__link_memblock_to_freelist(pool_index, new_block);
    
    memblock__byte_num(block) = byte_num;
  }
  
  __funk2.memory.pool[pool_index].total_free_memory                    -= memblock__byte_num(block);
  __funk2.memory.pool[pool_index].total_allocated_memory_since_last_gc += memblock__byte_num(block);
  //if (__funk2.memory.pool[pool_index].total_allocated_memory_since_last_gc >= __funk2.memory.pool[pool_index].total_free_memory) {
  //  __funk2.memory.pool[pool_index].should_run_gc = boolean__true;
  //}
  rbt_tree__insert(&(__funk2.memory.pool[pool_index].used_memory_tree), (rbt_node_t*)block);
  block->used        = 1;
  ((ptype_block_t*)block)->ptype = ptype_newly_allocated;
  debug_memory_test(pool_index, 3);
#ifdef DEBUG_MEMORY
  {
    ptr block_ptr = to_ptr(block);
    s64 check_pool_address = __ptr__pool_address(pool_index, to_ptr(block_ptr));
    if (check_pool_address < 0 || check_pool_address > f2ptr__pool_address__max_value) {
      status("pool_address is out of range, (0 <= " s64__fstr " <= " u64__fstr ").", check_pool_address, f2ptr__pool_address__max_value);
      status("  pool_index = " pool_index__fstr, (pool_index_t)pool_index);
      status("  block_ptr  = " ptr__fstr,        (ptr)block_ptr);
      print_gc_stats();
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
      print_gc_stats();
      error(nil, "computer_id must be zero for a local memory allocation.");
    }
    u64 check_pool_index   = __f2ptr__pool_index(block_f2ptr);
    if (check_pool_index > f2ptr__pool_index__max_value) {
      status("[ERROR] pool_index is out of range, (0 <= " u64__fstr " <= " u64__fstr ").", check_pool_index, f2ptr__pool_index__max_value);
      print_gc_stats();
      error(nil, "pool_index is out of range.");
    }
    u64 check_pool_address = __f2ptr__pool_address(block_f2ptr);
    if (check_pool_address > f2ptr__pool_address__max_value) {
      status("[ERROR] pool_address is out of range, (0 <= " u64__fstr " <= " u64__fstr ").", check_pool_address, f2ptr__pool_address__max_value);
      print_gc_stats();
      error(nil, "pool_address is out of range.");
    }
  }
#endif
  if (block_f2ptr) {
    funk2_memorypool__add_protected_alloc_f2ptr(&(__funk2.memory.pool[pool_index]), block_f2ptr);
  }
  return block_f2ptr;
}

f2ptr pool__memblock_f2ptr__new(int pool_index, f2size_t byte_num) {
  while (1) {
    f2ptr memblock_f2ptr = pool__memblock_f2ptr__try_new(pool_index, byte_num);
    if (memblock_f2ptr) {
      return memblock_f2ptr;
    }
    sched_yield();
  }
}

f2ptr memblock_f2ptr__new(f2size_t byte_num) {
  int pool_index;
  while (1) {
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      f2ptr memblock_f2ptr = pool__memblock_f2ptr__try_new(pool_index, byte_num);
      if (memblock_f2ptr) {
	return memblock_f2ptr;
      }
    }
    sched_yield();
  }
}

memblock_t* pool__memblock__new(int pool_index, f2size_t byte_num) {
  return (memblock_t*)from_ptr(f2ptr_to_ptr(pool__memblock_f2ptr__new(pool_index, byte_num)));
}

memblock_t* memblock__new(f2size_t byte_num) {
  return (memblock_t*)from_ptr(f2ptr_to_ptr(memblock_f2ptr__new(byte_num)));
}

// UNPROTECTED-USE MEMORY FUNCTIONS

void debug__begin_pause_gc(int pool_index) {
  fprintf(stderr, "\ndebug__begin_pause_gc note: __funk2.memory.pool[%d].disable_gc = %d", pool_index, (int)__funk2.memory.pool[pool_index].disable_gc);
}

void debug__end_pause_gc(int pool_index) {
  fprintf(stderr, "\ndebug__end_pause_gc note: __funk2.memory.pool[%d].disable_gc = %d", pool_index, (int)__funk2.memory.pool[pool_index].disable_gc);
}

void pool__pause_gc (int pool_index) {
  memory_mutex__lock(pool_index);
#ifdef DEBUG
  //if (! __funk2.memory.pool[pool_index].disable_gc) {
  //  debug__begin_pause_gc(pool_index);
  //}
#endif // DEBUG
  funk2_memorypool__signal_enter_bytecode(&(__funk2.memory.pool[pool_index]));
  //__funk2.memory.pool[pool_index].disable_gc ++;
  memory_mutex__unlock(pool_index);
}

int pool__try_pause_gc (int pool_index) {
  int lock_failed = memory_mutex__try_lock(pool_index);
  if (lock_failed == 0) {
#ifdef DEBUG
    //if (! __funk2.memory.pool[pool_index].disable_gc) {
    //  debug__begin_pause_gc(pool_index);
    //}
#endif // DEBUG
    funk2_memorypool__signal_enter_bytecode(&(__funk2.memory.pool[pool_index]));
    //__funk2.memory.pool[pool_index].disable_gc ++;
    memory_mutex__unlock(pool_index);
  }
  return lock_failed;
}

void raw_pause_gc() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    pool__pause_gc(pool_index);
  }
}

int raw_try_pause_gc() {
  int pool_index;
  int lock_failed = 0;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    lock_failed = pool__try_pause_gc(pool_index);
    if (lock_failed) {
      break;
    }
  }
  if (lock_failed) {
    int resume_pool_index;
    for (resume_pool_index = 0; resume_pool_index < pool_index; resume_pool_index ++) {
      pool__resume_gc(resume_pool_index);
    }
  }
  return lock_failed;
}

void pool__resume_gc (int pool_index) {
  memory_mutex__lock(pool_index);
  release__assert(__funk2.memory.pool[pool_index].disable_gc != 0, nil, "__funk2.memory.pool[].disable_gc == 0 before decrement... too many calls to resume_gc.");
  funk2_memorypool__signal_exit_bytecode(&(__funk2.memory.pool[pool_index]));
  //__funk2.memory.pool[pool_index].disable_gc --;
#ifdef DEBUG
  //if (! __funk2.memory.pool[pool_index].disable_gc) {
  //  debug__end_pause_gc(pool_index);
  //}
#endif // DEBUG
  memory_mutex__unlock(pool_index);
}

void raw_resume_gc() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    pool__resume_gc(pool_index);
  }
}

int gc__is_disabled() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    if(__funk2.memory.pool[pool_index].disable_gc) {
      return 1;
    }
  }
  return 0;
}

// use this after pausing and resuming garbage collection
//
// bug: pool__try_gc has thread lock conditions with find_or_create_free_splittable_memblock_and_unfree.
//
boolean_t pool__try_gc(int pool_index) {
  u8 result = 0;
  return result;
}

boolean_t try_gc() {
  boolean_t did_something = 0;
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    did_something |= pool__try_gc(pool_index);
  }
  return did_something;
}

void funk2_memory__handle(funk2_memory_t* memory) {
  boolean_t should_collect_garbage    = boolean__false;
  boolean_t should_enlarge_memory_now = boolean__false;
  int index;
  for (index = 0; index < memory_pool_num; index ++) {
    if (memory->pool[index].should_enlarge_memory_now) {
      should_enlarge_memory_now = boolean__true;
    }
    if (memory->pool[index].should_run_gc) {
      should_collect_garbage = boolean__true;
    }
  }
  if (should_enlarge_memory_now) {
    while (__ptypes_waiting_count < memory_pool_num) {
      sched_yield();
    }
    for (index = 0; index < memory_pool_num; index ++) {
      if (memory->pool[index].should_enlarge_memory_now) {
	pool__change_total_memory_available(index, memory->pool[index].total_global_memory + (memory->pool[index].total_global_memory >> 3) + memory->pool[index].should_enlarge_memory_now__need_at_least_byte_num);
	memory->pool[index].should_enlarge_memory_now__need_at_least_byte_num = 0;
	memory->pool[index].should_enlarge_memory_now                         = boolean__false;
      }
    }
    __ptypes_please_wait_for_gc_to_take_place = boolean__false;
  }
  if (should_collect_garbage && (raw__nanoseconds_since_1970() - memory->last_garbage_collect_nanoseconds_since_1970) > 10 * 1000000000ull) {
    status("funk2_memory__handle asking all user threads to wait_politely so that we can begin collecting garbage.");
    __ptypes_please_wait_for_gc_to_take_place = boolean__true;
    while (__ptypes_waiting_count < memory_pool_num) {
      sched_yield();
    }
    if (! gc__is_disabled()) {
      status ("");
      status ("**********************************");
      status ("**** DOING GARBAGE COLLECTION ****");
      status ("**********************************");
      status ("");
      for (index = 0; index < memory_pool_num; index ++) {
	if (memory->pool[index].should_run_gc) {
	  status ("memory->pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(memory->pool[index].total_global_memory));
	  int did_something = garbage_collect(index, 0);
	  if (did_something) {
	    status ("garbage collection did something.");
	  } else {
	    status ("garbage collection did nothing.");
	  }
	  memory->pool[index].should_run_gc = boolean__false;
	  status ("memory->pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(memory->pool[index].total_global_memory));
	}
      }
    } else {
      status ("");
      status ("***********************************************************");
      status ("**** should do garbage collection, but gc is disabled. ****");
      status ("***********************************************************");
      status ("");
    }
    memory->last_garbage_collect_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    __ptypes_please_wait_for_gc_to_take_place = boolean__false;
  }
}

boolean_t pool__should_run_gc(int pool_index) {
  memory_mutex__lock(pool_index);
  boolean_t should_gc = __funk2.memory.pool[pool_index].should_run_gc;
  memory_mutex__unlock(pool_index);
  return should_gc;
}

boolean_t should_run_gc() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    if (pool__should_run_gc(pool_index)) {
      return 1;
    }
  }
  return 0;
}

void global_environment__set(f2ptr global_environment) {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__lock(pool_index);
  }
  __funk2.memory.global_environment_f2ptr = global_environment;
  __funk2.memory.global_environment_ptr = raw__f2ptr_to_ptr(global_environment);
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__unlock(pool_index);
  }
}

f2ptr global_environment() {
  f2ptr retval;
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__lock(pool_index);
  }
  retval = __funk2.memory.global_environment_f2ptr;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__unlock(pool_index);
  }
  return retval;
}

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

int raw__memory_image__save(char* filename) {
  status("saving memory image.");
  print_gc_stats();
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__lock(pool_index);
  }
  // should collect garbage probably
  int fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1) {
    printf("\nsave_image_to_disk error: couldn't open file \"%s\".", filename);
    return -1;
  }
  f2ptr    f2_i;
  f2size_t size_i;
  int      i;
  i = 0xfaded;             safe_write(fd, &i, sizeof(int));
  i = F2__COMPILE_TIME_ID; safe_write(fd, &i, sizeof(int));
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    size_i = __funk2.memory.pool[pool_index].total_global_memory;      safe_write(fd, &size_i, sizeof(f2size_t));
    size_i = __funk2.memory.pool[pool_index].next_unique_block_id;     safe_write(fd, &size_i, sizeof(f2size_t));
    safe_write(fd, from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index]))), __funk2.memory.pool[pool_index].total_global_memory);
  }
  f2_i = __funk2.memory.global_environment_f2ptr; safe_write(fd, &f2_i, sizeof(f2ptr));
  close(fd);
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__unlock(pool_index);
  }
  return 0;
}

void f2__thought_process__reinitialize_globalvars();             // defined in f2_thought_process.c
void f2__env__reinitialize_globalvars();                         // defined in f2_env.c
void f2__funk2_node__reinitialize_globalvars();                  // defined in f2_funk2_node.c
void f2__globalenv__reinitialize_globalvars();                   // defined in f2_globalenv.c
void f2__peer_command_server__reinitialize_globalvars();         // defined in f2_peer_command_server.c
void f2__primobjects__reinitialize_globalvars();                 // defined in f2_primobjects.c
void f2__primobject__action__reinitialize_globalvars();          // defined in f2_primobject__action.c
void f2__primobject_tensor__reinitialize_globalvars();           // defined in f2_primobject__tensor.c
void f2__primobject_object__reinitialize_globalvars();           // defined in f2_primobject__object.c
void f2__primobject_object_type__reinitialize_globalvars();      // defined in f2_primobject__object_type.c
void f2__primobject_circular_buffer__reinitialize_globalvars();  // defined in f2_primobject__circular_buffer.c
void f2__primobject__semantic_graph__reinitialize_globalvars();  // defined in f2_primobject__semantic_graph.c
void f2__primobject__stream__reinitialize_globalvars();          // defined in f2_primobject__stream.c
void f2__primobject__text_buffer__reinitialize_globalvars();     // defined in f2_primobject__text_buffer.c
void f2__primcfunks__reinitialize_globalvars();                  // defined in f2_primfunks.c
void f2__reader__reinitialize_globalvars();                      // defined in f2_reader.c
void f2__compile__reinitialize_globalvars();                     // defined in f2_compile.c
void f2__thread__reinitialize_globalvars();                      // defined in f2_thread.c
void f2__bytecodes__reinitialize_globalvars();                   // defined in f2_bytecodes.c
void f2__signal__reinitialize_globalvars();                      // defined in f2_signal.c
void f2__scheduler__reinitialize_globalvars();                   // defined in f2_scheduler.c
void f2__socket__reinitialize_globalvars();                      // defined in f2_socket.c
void f2__trace__reinitialize_globalvars();                       // defined in f2_trace.c
void f2__serialize__reinitialize_globalvars();                   // defined in f2_serialize.c
void f2__primfunks__errno__reinitialize_globalvars();            // defined in f2_primfunks__errno.c
void f2__primfunks__fcntl__reinitialize_globalvars();            // defined in f2_primfunks__fcntl.c
void f2__primfunks__ioctl__reinitialize_globalvars();            // defined in f2_primfunks__ioctl.c
void f2__primfunks__locale__reinitialize_globalvars();           // defined in f2_primfunks__locale.c
void f2__ansi__reinitialize_globalvars();                        // defined in f2_ansi.c
void f2__termios__reinitialize_globalvars();                     // defined in f2_termios.c
void f2__blocks_world__reinitialize_globalvars();                // defined in f2_blocks_world.c
void f2__primobject__dynamic_library__reinitialize_globalvars(); // defined in f2_primobject__dynamic_library.c
void f2__dlfcn__reinitialize_globalvars();                       // defined in f2_dlfcn.c
void f2__gmodule__reinitialize_globalvars();                     // defined in f2_gmodule.c
void f2__string__reinitialize_globalvars();                      // defined in f2_string.c
void f2__child_handler__reinitialize_globalvars();               // defined in f2_child_handler.c
void f2__apropos__reinitialize_globalvars();                     // defined in f2_apropos.c
void f2__object__reinitialize_globalvars();                      // defined in f2_object.c
void f2__primobject_type_handler__reinitialize_globalvars();     // defined in f2_primobject_type_handler.c
void f2__primobject_type__reinitialize_globalvars();             // defined in f2_primobject_type.c
void f2__sort__reinitialize_globalvars();                        // defined in f2_sort.c
void f2__search__reinitialize_globalvars();                      // defined in f2_search.c

f2ptr ptr_to_f2ptr__slow(ptr p) {
  if (p == to_ptr(NULL)) {return nil;}
  int i;
  for (i = 0; i < memory_pool_num; i ++) {
    if (p >= funk2_memorypool__memory__ptr(&(__funk2.memory.pool[i])) &&
	p <  funk2_memorypool__memory__ptr(&(__funk2.memory.pool[i])) + __funk2.memory.pool[i].total_global_memory) {
      return f2ptr__new(0, i, ((u8*)from_ptr(p)) - ((u8*)from_ptr(__funk2.memory.pool[i].global_f2ptr_offset)));
    }
  }
  error(nil, "ptr_to_f2ptr__slow error: p is not in any memory pool.");
}

// precondition: each and every memory pool's global_memory_mutex is locked!
void rebuild_memory_info_from_image() {
  // each and every pool's global_memory_mutex is locked (we need to return that way).
  //
  // note: all memory being locked allows us to assume that we are the
  //       only pthread executing.
  
  int pool_index;
  
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    //#ifdef DEBUG_MEMORY
    status("rebuilding memory pool[%d] info from image.", pool_index); fflush(stdout);
    //#endif // DEBUG_MEMORY
    rbt_tree__init(&(__funk2.memory.pool[pool_index].free_memory_tree), NULL);
    __funk2.memory.pool[pool_index].total_free_memory  = 0;
    rbt_tree__init(&(__funk2.memory.pool[pool_index].used_memory_tree), NULL);
    
    {
      memblock_t* iter = (memblock_t*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])));
      memblock_t* end_of_blocks = (memblock_t*)(((u8*)from_ptr(funk2_memorypool__memory__ptr(&(__funk2.memory.pool[pool_index])))) + __funk2.memory.pool[pool_index].total_global_memory);
      while(iter < end_of_blocks) {
	debug__assert(memblock__byte_num(iter) > 0, nil, "memory_test__byte_num_zero failed.");
	if (iter->used) {
	  rbt_tree__insert(&(__funk2.memory.pool[pool_index].used_memory_tree), (rbt_node_t*)iter);
	} else {
	  pool__link_memblock_to_freelist(pool_index, iter);
	  __funk2.memory.pool[pool_index].total_free_memory += memblock__byte_num(iter);
	}
	iter = (memblock_t*)(((u8*)iter) + memblock__byte_num(iter));
      }
      release__assert(iter == end_of_blocks, nil, "memory_test: (end_of_blocks != iter) failure.");
    }
  }
  
  // temporarily unlocks all memory mutexes
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__unlock(pool_index);
  }
  // temporary period of all memory mutexes locked
  {
    symbol_hash__reinitialize();
    
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      // add all symbols to symbol_hash in ptypes.c
      rbt_node_t* iter = rbt_tree__minimum(&(__funk2.memory.pool[pool_index].used_memory_tree));
      while(iter) {
	ptype_block_t* block = (ptype_block_t*)iter;
	if(block->ptype == ptype_symbol) {
	  f2ptr block_f2ptr = ptr_to_f2ptr__slow(to_ptr(block));
	  symbol_hash__add_symbol(block_f2ptr);
	}
	iter = rbt_node__next(iter);
      }
    }
    
    f2__primobjects__reinitialize_globalvars();
    f2__primobject_hashtable__reinitialize_globalvars();
    f2__primobject_frame__reinitialize_globalvars();
    f2__primobject_environment__reinitialize_globalvars();
    f2__primobject__action__reinitialize_globalvars();
    f2__primobject_tensor__reinitialize_globalvars();
    f2__primobject_object__reinitialize_globalvars();
    f2__primobject_object_type__reinitialize_globalvars();
    f2__primobject_circular_buffer__reinitialize_globalvars();
    f2__primobject__semantic_graph__reinitialize_globalvars();
    f2__primobject__stream__reinitialize_globalvars();
    f2__primobject__text_buffer__reinitialize_globalvars();
    f2__globalenv__reinitialize_globalvars();
    f2__primcfunks__reinitialize_globalvars();
    f2__reader__reinitialize_globalvars();
    f2__compile__reinitialize_globalvars();
    f2__thread__reinitialize_globalvars();
    f2__bytecodes__reinitialize_globalvars();
    f2__signal__reinitialize_globalvars();
    f2__scheduler__reinitialize_globalvars();
    f2__socket__reinitialize_globalvars();
    f2__trace__reinitialize_globalvars();
    f2__serialize__reinitialize_globalvars();
    f2__thought_process__reinitialize_globalvars();
    f2__primfunks__errno__reinitialize_globalvars();
    f2__primfunks__fcntl__reinitialize_globalvars();
    f2__primfunks__ioctl__reinitialize_globalvars();
    f2__primfunks__locale__reinitialize_globalvars();
    f2__funk2_node__reinitialize_globalvars();
    f2__peer_command_server__reinitialize_globalvars();
    f2__ansi__reinitialize_globalvars();
    f2__termios__reinitialize_globalvars();
    f2__blocks_world__reinitialize_globalvars();
    f2__dlfcn__reinitialize_globalvars();
    f2__gmodule__reinitialize_globalvars();
    f2__string__reinitialize_globalvars();
    f2__child_handler__reinitialize_globalvars();
    f2__apropos__reinitialize_globalvars();
    f2__object__reinitialize_globalvars();
    f2__primobject_type_handler__reinitialize_globalvars();
    f2__primobject_type__reinitialize_globalvars();
    f2__sort__reinitialize_globalvars();
    f2__search__reinitialize_globalvars();
  }
  // end temporary unlocking of all memory mutexes
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__lock(pool_index);
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    debug_memory_test(pool_index, 1);
  }
  
  //#ifdef DEBUG_MEMORY
  status("done rebuilding memory info from image."); fflush(stdout);
  //#endif // DEBUG_MEMORY
}

void f2__global_scheduler__execute_mutex__lock(f2ptr cause);
void f2__global_scheduler__execute_mutex__unlock(f2ptr cause);

int raw__memory_image__load(char* filename) {
  int retval = 0; // success
  //#ifdef DEBUG_MEMORY
  status("loading memory image.");
  //#endif // DEBUG_MEMORY
  
  f2__global_scheduler__execute_mutex__lock(initial_cause());
  
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__lock(pool_index);
  }
  
  
  int fd = open(filename, O_RDONLY);
  if (fd == -1) {
    //#ifdef DEBUG_MEMORY
    status("load_image_from_disk failure: could not open file \"%s\".", filename);
    //#endif // DEBUG_MEMORY
    retval = -1;
  } else {
    while(1) {
      int      i;
      f2ptr    f2_i;
      f2size_t size_i;
      safe_read(fd, &i, sizeof(int));
      if (i != 0xfaded) {
	//#ifdef DEBUG_MEMORY
	status("load_image_from_disk failure: file is not a funk memory image.");
	//#endif // DEBUG_MEMORY
	retval = -1;
	break;
      }
      
      safe_read(fd, &i, sizeof(int));
      if (i != F2__COMPILE_TIME_ID) {
	//#ifdef DEBUG_MEMORY
	status("load_image_from_disk failure: file is saved from a different version of funk2.");
	//#endif // DEBUG_MEMORY
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
      
      rebuild_memory_info_from_image();
      
      status("loaded memory image successfully.");
      break;
    }
    close(fd);      
  }
  
  f2__global_scheduler__execute_mutex__unlock(initial_cause());
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    memory_mutex__unlock(pool_index);
  }
  
  print_gc_stats();
  return retval;
}

void print_gc_stats() {
  int pool_index;
  for(pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    memory_mutex__lock(pool_index);
    status("__funk2.memory.pool[%d].total_global_memory  = " f2size_t__fstr, pool_index, __funk2.memory.pool[pool_index].total_global_memory);
    status("__funk2.memory.pool[%d].total_free_memory()  = " f2size_t__fstr, pool_index, total_free_memory(pool_index));
    status("__funk2.memory.pool[%d].total_used_memory()  = " f2size_t__fstr, pool_index, total_used_memory(pool_index));
    status("__funk2.memory.pool[%d].next_unique_block_id = %u", pool_index, __funk2.memory.pool[pool_index].next_unique_block_id);
    memory_mutex__unlock(pool_index);
  }
}

// END UNPROTECTED-USE MEMORY FUNCTIONS

void f2__memory__initialize() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__init((&__funk2.memory.pool[pool_index]));
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    debug_memory_test(pool_index, 1);
  }
}

void f2__memory__destroy() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    debug_memory_test(pool_index, 1);
  }
  
  for (pool_index = 0; pool_index < memory_pool_num; pool_index++) {
    funk2_memorypool__destroy(&(__funk2.memory.pool[pool_index]));
  }
}



