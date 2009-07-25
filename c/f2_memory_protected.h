// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__MEMORY__PROTECTED__H
#define F2__MEMORY__PROTECTED__H

//#define DEBUG_MEMORY 3

#include "f2_global.h"
#include "f2_redblacktree.h"
#include "f2_memory.h"
#include "f2_dynamic_memory.h"

#define maximum_generation_num 7

struct funk2_memblock_s {
  rbt_node_t rbt_node;
  u8         used           : 1;
  u8         gc_touch       : 1;
  u8         generation_num : 3;
  u8         ptype          : ptype__min_bits;
  u8         raw_mem[0];
} __attribute__((__packed__));
typedef struct funk2_memblock_s funk2_memblock_t;

#define funk2_memblock__byte_num(this)         ((this)->rbt_node.key)

typedef struct funk2_memorypool_s {
  funk2_processor_mutex_t global_memory_allocate_mutex;
  uint                    disable_gc; // incremented/decremented by pause_gc/resume_gc
  boolean_t               should_run_gc; // if disabled when needed more memory (and allocated more) then True
  boolean_t               should_enlarge_memory_now;
  f2size_t                should_enlarge_memory_now__need_at_least_byte_num;
  f2size_t                total_global_memory;
  f2size_t                total_free_memory;
#if defined(STATIC_MEMORY)
  f2staticmemory_t*       static_memory;
#elif defined(DYNAMIC_MEMORY)
  f2dynamicmemory_t       dynamic_memory;
#endif 
  rbt_tree_t              used_memory_tree;
  rbt_tree_t              free_memory_tree; // free memory does grow on trees!
  ptr                     global_f2ptr_offset; // one byte less than __global_memory_block_data (to preserve [NULL -> 0] for [ptr -> f2ptr])
  f2size_t                total_allocated_memory_since_last_gc;
  uint                    next_unique_block_id;
  u64                     protected_alloc_array__used_num;
  u64                     protected_alloc_array__length;
  f2ptr*                  protected_alloc_array;
  u64                     protected_alloc_array__reentrance_count;
} funk2_memorypool_t;

#if defined(DYNAMIC_MEMORY)
#  define funk2_memorypool__memory__ptr(this) ((this)->dynamic_memory.ptr)
#elif defined(STATIC_MEMORY)
#  define funk2_memorypool__memory__ptr(this) ((this)->static_memory->ptr)
#else
#  error DYNAMIC_MEMORY or STATIC_MEMORY must be defined.
#endif

#include "f2_ptypes_memory.h"
#include "f2_memory.h"

f2ptr             pool__funk2_memblock_f2ptr__try_new(int pool_index, f2size_t byte_num);
f2ptr             pool__funk2_memblock_f2ptr__new(int pool_index, f2size_t byte_num);
f2ptr             funk2_memblock_f2ptr__new(f2size_t byte_num);
funk2_memblock_t* pool__funk2_memblock__new(int pool_index, f2size_t byte_num);
funk2_memblock_t* funk2_memblock__new(f2size_t byte_num);

#define funk2_memorypool__memory_mutex__lock(this)     funk2_processor_mutex__lock(&((this)->global_memory_allocate_mutex))
#define funk2_memorypool__memory_mutex__try_lock(this) funk2_processor_mutex__trylock(&((this)->global_memory_allocate_mutex))
#define funk2_memorypool__memory_mutex__unlock(this)   funk2_processor_mutex__unlock(&((this)->global_memory_allocate_mutex))

#define f2ptr__computer_id__bit_num  computer_id__bit_num
#define f2ptr__pool_index__bit_num   pool_index__bit_num
#define f2ptr__pool_address__bit_num pool_address__bit_num

#define f2ptr__computer_id__max_value  ((((u64)1)<<(f2ptr__computer_id__bit_num))  - 1)
#define f2ptr__pool_index__max_value   ((((u64)1)<<(f2ptr__pool_index__bit_num))   - 1)
#define f2ptr__pool_address__max_value ((((u64)1)<<(f2ptr__pool_address__bit_num)) - 1)

#define f2ptr__new(computer_id, pool_index, pool_address)  ((((u64)(computer_id)) << (f2ptr__pool_address__bit_num + f2ptr__pool_index__bit_num)) | \
							    (((u64)(pool_index))  <<  f2ptr__pool_address__bit_num) | \
							    ( (u64)(pool_address)))

#if (computer_id__bit_num == 0)
#  define __f2ptr__computer_id(f2p)                        0
#else
#  define __f2ptr__computer_id(f2p)                        (((u64)(f2p)) >> (f2ptr__pool_address__bit_num + f2ptr__pool_index__bit_num))
#endif
#define __f2ptr__pool_index(f2p)                          ((((u64)(f2p)) >> f2ptr__pool_address__bit_num) & f2ptr__pool_index__max_value)
#define __f2ptr__pool_address(f2p)                         (((u64)(f2p)) & f2ptr__pool_address__max_value)

#if (computer_id__bit_num == 0)
#  define __f2ptr__computer_id__set(f2p, computer_id) (f2p)
#else
#  define __f2ptr__computer_id__set(f2p, computer_id) f2ptr__new(         computer_id,      __f2ptr__pool_index(f2p), __f2ptr__pool_address(f2p))
#endif
#define __f2ptr__pool_index__set(f2p, pool_index)     f2ptr__new(__f2ptr__computer_id(f2p),          pool_index,      __f2ptr__pool_address(f2p))
#define __f2ptr__pool_address__set(f2p, pool_address) f2ptr__new(__f2ptr__computer_id(f2p), __f2ptr__pool_index(f2p),          pool_address)

#define   __ptr__pool_address(pool_index, p) ((((u64)p) != (u64)0) ? ((u64)(((u64)(p)) - (u64)(__funk2.memory.pool[pool_index].global_f2ptr_offset))) : (u64)0)
					      
#define __f2ptr_to_ptr(f2p)             ((((u64)(f2p)) !=       ((u64)0)) ? ((to_ptr((__f2ptr__pool_address(f2p))        + __funk2.memory.pool[__f2ptr__pool_index(f2p)].global_f2ptr_offset))) : (to_ptr(NULL)))
#define   __ptr_to_f2ptr(pool_index, p) (((to_ptr(p))  != (to_ptr(NULL))) ?    ((u64)(f2ptr__new(0, pool_index, __ptr__pool_address(pool_index, p))))                                           : ((u64)0))

#ifdef DEBUG_MEMORY_POINTERS
#  define      f2ptr_to_ptr(f2p) used_f2ptr_to_ptr__debug(f2p)
//#  define        ptr_to_f2ptr(p) used_ptr_to_f2ptr__debug(p)
#  define raw__f2ptr_to_ptr(f2p) f2ptr_to_ptr__debug(f2p)
//#  define   raw__ptr_to_f2ptr(p) ptr_to_f2ptr__debug(p)
#else
//#  define      f2ptr_to_ptr(f2p) fast__f2ptr_to_ptr(f2p)
//#  define        ptr_to_f2ptr(p) fast__ptr_to_f2ptr(p)
//#  define raw__f2ptr_to_ptr(f2p) fast__f2ptr_to_ptr(f2p)
//#  define   raw__ptr_to_f2ptr(p) fast__ptr_to_f2ptr(p)
// inlining these definitions sometimes causes run-time errors (why?), so use raw__* above in that case.
#  define      f2ptr_to_ptr(f2p) __f2ptr_to_ptr(f2p)
//#  define        ptr_to_f2ptr(pool_index, p) __ptr_to_f2ptr(pool_index, p)
#  define raw__f2ptr_to_ptr(f2p) __f2ptr_to_ptr(f2p)
//#  define   raw__ptr_to_f2ptr(pool_index, p) __ptr_to_f2ptr(pool_index, p)
#endif

#define ptr_to_f2ptr(pool_index, p) __ptr_to_f2ptr(pool_index, p)

void memory_test();

#ifdef DEBUG_MEMORY
#  if (DEBUG_MEMORY > 0)
#    define debug_memory_test(pool_index, level) {if (DEBUG_MEMORY >= level) {memory_test(pool_index);}}
#  else
#    define debug_memory_test(pool_index, level)
#  endif
#else
#  define debug_memory_test(pool_index, level)
#endif

u8 garbage_collect();

ptr   f2ptr_to_ptr__debug(f2ptr f2p);
f2ptr ptr_to_f2ptr__debug(ptr   p);

ptr   used_f2ptr_to_ptr__debug(f2ptr f2p);
f2ptr used_ptr_to_f2ptr__debug(ptr   p);

//ptr   fast__f2ptr_to_ptr(f2ptr f2p);
f2ptr fast__ptr_to_f2ptr(ptr   p);

#define fast__f2ptr_to_ptr(f2p) __f2ptr_to_ptr(f2p)

typedef struct funk2_memory_s {
  funk2_memorypool_t pool[memory_pool_num];
  ptr                global_environment_ptr;
  f2ptr              global_environment_f2ptr;
  u64                last_garbage_collect_nanoseconds_since_1970;
  pthread_t          memory_handling_thread;
  boolean_t          bootstrapping_mode;
} funk2_memory_t;

void      funk2_memory__init(funk2_memory_t* this); // only called by memory management thread
void      funk2_memory__destroy(funk2_memory_t* this); // only called by memory management thread
void      funk2_memory__signal_enter_bytecode(funk2_memory_t* this); // memory handling thread should never call this function
void      funk2_memory__signal_exit_bytecode(funk2_memory_t* this); // memory handling thread should never call this function
void      funk2_memory__handle(funk2_memory_t* memory); // only called by memory management thread
void      funk2_memory__print_gc_stats(funk2_memory_t* this);
boolean_t funk2_memory__is_valid_funk2_memblock_ptr(funk2_memory_t* this, ptr p);

#endif // F2__MEMORY__PROTECTED__H
