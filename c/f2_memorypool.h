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

#ifndef F2__MEMORYPOOL__TYPES__H
#define F2__MEMORYPOOL__TYPES__H

typedef struct funk2_memorypool_s funk2_memorypool_t;

#endif // F2__MEMORYPOOL__TYPES__H

#ifndef F2__MEMORYPOOL__H
#define F2__MEMORYPOOL__H

#include "f2_dptr.h"
#include "f2_global.h"
#include "f2_redblacktree.h"
#include "f2_dynamic_memory.h"
#include "f2_memblock.h"
#include "f2_ptype.h"
#include "f2_zlib.h"

struct funk2_memorypool_s {
  funk2_processor_mutex_t        global_memory_allocate_mutex;
  boolean_t                      should_enlarge_memory_now;
  f2size_t                       should_enlarge_memory_now__need_at_least_byte_num;
  f2size_t                       total_global_memory;
  f2size_t                       total_free_memory;
  f2dynamicmemory_t              dynamic_memory;
  rbt_tree_t                     used_memory_tree;
  rbt_tree_t                     free_memory_tree; // free memory does grow on trees!
  ptr                            global_f2ptr_offset; // one byte less than __global_memory_block_data (to preserve [NULL -> 0] for [ptr -> f2ptr])
  f2size_t                       total_allocated_memory_since_last_gc;
  u64                            next_unique_block_id;
  //funk2_gc_touch_circle_buffer_t gc_touch_circle_buffer;
};

#define funk2_memorypool__memory_mutex__lock(this)     funk2_processor_mutex__lock(&((this)->global_memory_allocate_mutex))
#define funk2_memorypool__memory_mutex__try_lock(this) funk2_processor_mutex__trylock(&((this)->global_memory_allocate_mutex))
#define funk2_memorypool__memory_mutex__unlock(this)   funk2_processor_mutex__unlock(&((this)->global_memory_allocate_mutex))

#ifdef DEBUG_MEMORY
#  if (DEBUG_MEMORY > 0)
#    define funk2_memorypool__debug_memory_test(this, level) {if (DEBUG_MEMORY >= level) {funk2_memorypool__memory_test(this);}}
#  else
#    define funk2_memorypool__debug_memory_test(this, level)
#  endif
#else
#  define funk2_memorypool__debug_memory_test(this, level)
#endif

// funk2_memorypool

void              funk2_memorypool__init(funk2_memorypool_t* pool);
void              funk2_memorypool__destroy(funk2_memorypool_t* this);
f2size_t          funk2_memorypool__total_used_memory(funk2_memorypool_t* this);
f2size_t          funk2_memorypool__total_free_memory(funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__dynamic_memory(funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__byte_num_zero(funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__all_known_types(funk2_memorypool_t* this);
void              funk2_memorypool__memory_test(funk2_memorypool_t* this);
void              funk2_memorypool__change_total_memory_available(funk2_memorypool_t* this, f2size_t byte_num);
void              funk2_memorypool__used_memory_tree__insert(funk2_memorypool_t* this, funk2_memblock_t* block);
void              funk2_memorypool__free_memory_tree__insert(funk2_memorypool_t* this, funk2_memblock_t* block);
u8                funk2_memorypool__defragment_free_memory_blocks_in_place(funk2_memorypool_t* this);
void              funk2_memorypool__free_used_block(funk2_memorypool_t* this, funk2_memblock_t* block);
funk2_memblock_t* funk2_memorypool__find_splittable_free_block_and_unfree(funk2_memorypool_t* this, f2size_t byte_num);
boolean_t         funk2_memorypool__check_all_memory_pointers_valid_in_memory(funk2_memorypool_t* this, funk2_memory_t* memory);
void              funk2_memorypool__save_to_stream(funk2_memorypool_t* this, int fd);
void              funk2_memorypool__load_from_stream(funk2_memorypool_t* this, int fd);

#endif // F2__MEMORYPOOL__H

