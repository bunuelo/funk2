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

#ifndef F2_MEMORY_TYPEDEF_STRUCTS
#define F2_MEMORY_TYPEDEF_STRUCTS

#include "f2_dynamic_memory.h"
#include "f2_redblacktree.h"
#include "f2_processor_mutex.h"

#define ptype__total_num 14
#define ptype__min_bits   4

typedef enum ptype_e {
  ptype_free_memory     = 0x40 + 0x0,
  ptype_newly_allocated = 0x40 + 0x1,
  ptype_integer         = 0x40 + 0x2,
  ptype_double          = 0x40 + 0x3,
  ptype_float           = 0x40 + 0x4,
  ptype_pointer         = 0x40 + 0x5,
  ptype_gfunkptr        = 0x40 + 0x6,
  ptype_mutex           = 0x40 + 0x7,
  ptype_char            = 0x40 + 0x8,
  ptype_string          = 0x40 + 0x9,
  ptype_symbol          = 0x40 + 0xA,
  ptype_chunk           = 0x40 + 0xB,
  ptype_simple_array    = 0x40 + 0xC,
  ptype_traced_array    = 0x40 + 0xD,
  ptype_larva           = 0x40 + 0xE,
} ptype_t;

struct funk2_memblock_s {
  rbt_node_t rbt_node;
  u8         used           : 1;
  u8         gc_touch       : 1;
  u8         generation_num : 3;
  u8         ptype          : ptype__min_bits;
  u8         raw_mem[0];
} __attribute__((__packed__));
typedef struct funk2_memblock_s funk2_memblock_t;

typedef struct funk2_memorypool_s {
  funk2_processor_mutex_t global_memory_allocate_mutex;
  boolean_t               should_run_gc; // if disabled when needed more memory (and allocated more) then True
  boolean_t               should_enlarge_memory_now;
  f2size_t                should_enlarge_memory_now__need_at_least_byte_num;
  f2size_t                total_global_memory;
  f2size_t                total_free_memory;
  f2dynamicmemory_t       dynamic_memory;
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

typedef struct funk2_gc_touch_circle_buffer_s {
  int                num;
  funk2_memblock_t** start;
  funk2_memblock_t** end;
  funk2_memblock_t** start_index;
  funk2_memblock_t** end_index;
} funk2_gc_touch_circle_buffer_t;

typedef struct funk2_memory_s {
  funk2_memorypool_t             pool[memory_pool_num];
  ptr                            global_environment_ptr;
  f2ptr                          global_environment_f2ptr;
  u64                            last_garbage_collect_nanoseconds_since_1970;
  pthread_t                      memory_handling_thread;
  boolean_t                      bootstrapping_mode;
  boolean_t                      gc_touch_circle_buffer__initialized;
  funk2_gc_touch_circle_buffer_t gc_touch_circle_buffer;
} funk2_memory_t;

#endif // F2_MEMORY_TYPEDEF_STRUCTS

#ifndef F2__MEMORY__H
#define F2__MEMORY__H

#include "f2_global.h"

#define nil ((f2ptr)0)

#ifdef F2__PTYPE__C__COMPILING
u8 __ptype__str[][128] = {
  "free_memory",
  "newly_allocated",
  "integer",
  "double",
  "float",
  "pointer",
  "gfunkptr",
  "mutex",
  "char",
  "string",
  "symbol",
  "chunk",
  "simple_array",
  "traced_array",
  "larva",
};
#endif // F2__PTYPE__C__COMPILING

ptr  f2__malloc(f2size_t byte_num);
void f2__free(ptr this);
ptr  f2__new_alloc(ptr this, f2size_t old_byte_num, f2size_t new_byte_num);

void assert_failed(f2ptr thread, char* filename, int line_num, char* str);

void exp__gc_touch_all_referenced(ptr start_block_ptr);
void f2__gc_touch_all_referenced(f2ptr exp);

boolean_t pool__should_run_gc(int pool_index);

#define pause_gc()  funk2_memory__signal_enter_protected_region(&(__funk2.memory))
#define resume_gc() funk2_memory__signal_exit_protected_region(&(__funk2.memory))

boolean_t should_run_gc();
int       gc__is_disabled();

int raw__memory_image__save(char* filename);
int raw__memory_image__load(char* filename);

void f2__memory__initialize();
void f2__memory__destroy();

//#define DEBUG_MEMORY 3

#include "f2_global.h"
#include "f2_redblacktree.h"
#include "f2_memory.h"
#include "f2_dynamic_memory.h"

#define maximum_generation_num 7

#define funk2_memblock__byte_num(this)         ((this)->rbt_node.key)

#define funk2_memorypool__memory__ptr(this) ((this)->dynamic_memory.ptr)

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
#  define      f2ptr_to_ptr(f2p) funk2_memory__used_f2ptr_to_ptr__debug(&(__funk2.memory), f2p)
//#  define        ptr_to_f2ptr(p) used_ptr_to_f2ptr__debug(p)
#  define raw__f2ptr_to_ptr(f2p) funk2_memory__f2ptr_to_ptr__debug(&(__funk2.memory), f2p)
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

#ifdef DEBUG_MEMORY
#  if (DEBUG_MEMORY > 0)
#    define funk2_memorypool__debug_memory_test(this, level) {if (DEBUG_MEMORY >= level) {funk2_memorypool__memory_test(this);}}
#  else
#    define funk2_memorypool__debug_memory_test(this, level)
#  endif
#else
#  define funk2_memorypool__debug_memory_test(this, level)
#endif

u8 garbage_collect();

ptr   f2ptr_to_ptr__debug(f2ptr f2p);
f2ptr ptr_to_f2ptr__debug(ptr   p);

ptr   used_f2ptr_to_ptr__debug(f2ptr f2p);
f2ptr used_ptr_to_f2ptr__debug(ptr   p);

//ptr   fast__f2ptr_to_ptr(f2ptr f2p);
f2ptr fast__ptr_to_f2ptr(ptr   p);

#define fast__f2ptr_to_ptr(f2p) __f2ptr_to_ptr(f2p)

#define GC_TOUCH_CIRCLE_BUF_START_SIZE (2)

// funk2_gc_touch_circle_buffer

void funk2_gc_touch_circle_buffer__touch_all_referenced_from_block(funk2_gc_touch_circle_buffer_t* this, ptr start_block_ptr);

// funk2_memory

void      funk2_memory__init(funk2_memory_t* this); // only called by memory management thread
void      funk2_memory__destroy(funk2_memory_t* this); // only called by memory management thread
void      funk2_memory__signal_enter_protected_region(funk2_memory_t* this); // memory handling thread should never call this function
void      funk2_memory__signal_exit_protected_region(funk2_memory_t* this); // memory handling thread should never call this function
void      funk2_memory__handle(funk2_memory_t* memory); // only called by memory management thread
void      funk2_memory__print_gc_stats(funk2_memory_t* this);
boolean_t funk2_memory__is_valid_funk2_memblock_ptr(funk2_memory_t* this, ptr p);
void      funk2_memory__touch_all_referenced_from_pool_generation(funk2_memory_t* this, int pool_index, int touch_generation_num);
boolean_t funk2_memory__garbage_collect_generation(funk2_memory_t* this, int generation_num);
boolean_t funk2_memory__garbage_collect_generations_until_did_something(funk2_memory_t* this);
ptr       funk2_memory__find_or_create_free_splittable_funk2_memblock_and_unfree(funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__try_new(funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__new_from_pool(funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__new(funk2_memory_t* this, f2size_t byte_num);
void      funk2_memory__signal_enter_protected_region(funk2_memory_t* this);
void      funk2_memory__signal_exit_protected_region(funk2_memory_t* this);
f2ptr     funk2_memory__funk2_memblock_f2ptr__new(funk2_memory_t* this, f2size_t byte_num);
void      funk2_memory__global_environment__set(funk2_memory_t* this, f2ptr global_environment);
f2ptr     funk2_memory__global_environment(funk2_memory_t* this);

#define global_environment()       funk2_memory__global_environment(&(__funk2.memory))
#define global_environment__set(x) funk2_memory__global_environment(&(__funk2.memory), x)

#endif // F2__MEMORY__H
