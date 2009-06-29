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

#include "f2_global.h"
#include "f2_redblacktree.h"
#include "f2_memory.h"

#ifdef F2__ARCH_SENSOR_NODE
#  include "f2_staticmemory.h"
#endif // F2__ARCH_SENSOR_NODE

#include "f2_dynamic_memory.h"
#include <pthread.h>

//#include "f2_gfunkptr.h"

#define maximum_generation_num 7

struct memblock_s {
  rbt_node_t rbt_node;
  u8         used           : 1;
  u8         gc_touch       : 1;
  u8         generation_num : 3;
  u8         ptype          : ptype__min_bits;
#ifdef MEMORY_OPTION__MEMBLOCK__RENDER_DATA
  float      render_position[3];
  u8         render_create_activated : 1;
  u8         render_read_activated   : 1;
  u8         render_write_activated  : 1;
  u8         render_on               : 1;
#endif // MEMORY_OPTION__MEMBLOCK__RENDER_DATA
  u8         raw_mem[0];
} __attribute__((__packed__));
typedef struct memblock_s memblock_t;

#define memblock__byte_num(this)         ((this)->rbt_node.key)

//#define memblock__next(this)             ((memblock_t*)((this)->rbt_node.right))
//#define memblock__next__set(this, value) (((this)->rbt_node.right) = (rbt_node_t*)(value))

typedef struct memorypool_s {
  funk2_processor_mutex_t global_memory_allocate_mutex;
  uint                    disable_gc; // incremented/decremented by pause_gc/resume_gc
  u8                      should_run_gc; // if disabled when needed more memory (and allocated more) then True
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
} memorypool_t;

#if defined(DYNAMIC_MEMORY)
#  define memorypool__memory__ptr(this) ((this)->dynamic_memory.ptr)
#elif defined(STATIC_MEMORY)
#  define memorypool__memory__ptr(this) ((this)->static_memory->ptr)
#else
#  error DYNAMIC_MEMORY or STATIC_MEMORY must be defined.
#endif

#include "f2_ptypes_memory.h"
#include "f2_memory.h"

#define memblock__lock(this)                   {if(pthread_mutex_lock(&(((memblock_t*)f2ptr_to_ptr(this))->mutex)))   {error(nil, "memblock_lock failed.");}}
#define memblock__unlock(this)                 {if(pthread_mutex_unlock(&(((memblock_t*)f2ptr_to_ptr(this))->mutex))) {error(nil, "memblock_unlock failed.");}}

f2ptr       pool__memblock_f2ptr__try_new(int pool_index, f2size_t byte_num);
f2ptr       pool__memblock_f2ptr__new(int pool_index, f2size_t byte_num);
f2ptr       memblock_f2ptr__new(f2size_t byte_num);
memblock_t* pool__memblock__new(int pool_index, f2size_t byte_num);
memblock_t* memblock__new(f2size_t byte_num);

boolean_t valid_memblock_ptr(ptr p);

#define memory_mutex__lock(pool_index)     funk2_processor_mutex__lock(&__funk2.memory.pool[pool_index].global_memory_allocate_mutex)
#define memory_mutex__try_lock(pool_index) funk2_processor_mutex__trylock(&__funk2.memory.pool[pool_index].global_memory_allocate_mutex)
#define memory_mutex__unlock(pool_index)   funk2_processor_mutex__unlock(&__funk2.memory.pool[pool_index].global_memory_allocate_mutex)

//void memory_mutex__lock(int pool_index);
//int  memory_mutex__try_lock(int pool_index);
//void memory_mutex__unlock(int pool_index);

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
#  define      f2ptr_to_ptr(f2p) debug__used_f2ptr_to_ptr(f2p)
//#  define        ptr_to_f2ptr(p) debug__used_ptr_to_f2ptr(p)
#  define raw__f2ptr_to_ptr(f2p) debug__f2ptr_to_ptr(f2p)
//#  define   raw__ptr_to_f2ptr(p) debug__ptr_to_f2ptr(p)
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

extern void memory_test();

#ifdef DEBUG_MEMORY
#  if (DEBUG_MEMORY > 0)
#    define debug_memory_test(pool_index, level) {if (DEBUG_MEMORY >= level) {memory_test(pool_index);}}
#  else
#    define debug_memory_test(pool_index, level)
#  endif
#else
#  define debug_memory_test(pool_index, level)
#endif

extern u8 garbage_collect();

extern ptr   debug__f2ptr_to_ptr(f2ptr f2p);
extern f2ptr debug__ptr_to_f2ptr(ptr   p);

extern ptr   debug__used_f2ptr_to_ptr(f2ptr f2p);
extern f2ptr debug__used_ptr_to_f2ptr(ptr   p);

extern ptr   fast__f2ptr_to_ptr(f2ptr f2p);
extern f2ptr fast__ptr_to_f2ptr(ptr   p);

typedef struct funk2_memory_s {
  memorypool_t pool[memory_pool_num];
  ptr          global_environment_ptr;
  f2ptr        global_environment_f2ptr;
  float        memblock__last_x;
  float        memblock__last_y;
  float        memblock__last_z;
  u8           memblock__render_on;
  float        memblock__render_noise;
} funk2_memory_t;

void funk2_memory__init(funk2_memory_t* this);
void funk2_memory__destroy(funk2_memory_t* this);

#endif // F2__MEMORY__PROTECTED__H
