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
#include "f2_set.h"
#include "f2_zlib.h"

struct funk2_memorypool_s {
  u64                     pool_index;
  funk2_processor_mutex_t global_memory_allocate_mutex;
  boolean_t               should_enlarge_memory_now;
  f2size_t                should_enlarge_memory_now__need_at_least_byte_num;
  f2size_t                total_global_memory;
  f2size_t                total_free_memory;
  f2dynamicmemory_t       dynamic_memory;
  funk2_memblock_t*       end_of_blocks;
  u64                     last_block_byte_num;
  
  funk2_heap_t            free_memory_heap; // free memory piles in heaps!
  u64                     free_memory_heap__load_buffer__length;
  funk2_heap_node_t**     free_memory_heap__load_buffer;
  s64                     free_memory_heap__load_buffer__global_f2ptr_offset;
  
  ptr                     global_f2ptr_offset; // one byte less than __global_memory_block_data (to preserve [NULL -> 0] for [ptr -> f2ptr])
  f2size_t                total_allocated_memory_since_last_gc;
  u64                     next_unique_block_id;
  s64                     temporary_compressed_data_for_loading__length;
  u8*                     temporary_compressed_data_for_loading;
  s64                     temporary_compressed_data_for_saving__length;
  u8*                     temporary_compressed_data_for_saving;
};

#define funk2_memorypool__end_of_blocks(this) ({			\
      funk2_memorypool_t* funk2_memorypool__end_of_blocks__memorypool = (this);	\
      (funk2_memblock_t*)(((u8*)from_ptr(funk2_memorypool__end_of_blocks__memorypool->dynamic_memory.ptr)) + funk2_memorypool__end_of_blocks__memorypool->total_global_memory); \
    })

#define funk2_memorypool__beginning_of_blocks(this) ({			\
      funk2_memorypool_t* funk2_memorypool__end_of_blocks__memorypool = (this);	\
      (funk2_memblock_t*)(from_ptr(funk2_memorypool__end_of_blocks__memorypool->dynamic_memory.ptr)); \
    })

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

void              funk2_memorypool__init                                           (funk2_memorypool_t* pool, u64 pool_index);
void              funk2_memorypool__destroy                                        (funk2_memorypool_t* this);
f2size_t          funk2_memorypool__total_used_memory                              (funk2_memorypool_t* this);
f2size_t          funk2_memorypool__total_free_memory                              (funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__dynamic_memory                    (funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__byte_num_zero                     (funk2_memorypool_t* this);
void              funk2_memorypool__memory_test__all_known_types                   (funk2_memorypool_t* this);
void              funk2_memorypool__memory_test                                    (funk2_memorypool_t* this);
f2ptr              raw__memorypool__assert_valid                                   (f2ptr cause, s64 pool_index);
void              funk2_memorypool__change_total_memory_available                  (funk2_memorypool_t* this, f2size_t byte_num);
void              funk2_memorypool__shrink_last_free_block                         (funk2_memorypool_t* this, f2size_t byte_num);
void              funk2_memorypool__free_memory_heap__insert                       (funk2_memorypool_t* this, funk2_memblock_t* block);
u8                funk2_memorypool__defragment_free_memory_blocks_in_place         (funk2_memorypool_t* this);
void              funk2_memorypool__free_used_block                                (funk2_memorypool_t* this, funk2_memblock_t* block);
funk2_memblock_t* funk2_memorypool__find_splittable_free_block_and_unfree          (funk2_memorypool_t* this, f2size_t byte_num);
u64               funk2_memorypool__maximum_block__byte_num                        (funk2_memorypool_t* this);
boolean_t         funk2_memorypool__check_all_memory_pointers_valid_in_memory      (funk2_memorypool_t* this, funk2_memory_t* memory);
boolean_t         funk2_memorypool__check_all_gc_colors_valid                      (funk2_memorypool_t* this, funk2_memory_t* memory, funk2_garbage_collector_pool_t* garbage_collector_pool);
void              funk2_memorypool__compress_for_saving                            (funk2_memorypool_t* this);
void              funk2_memorypool__write_compressed_to_stream                     (funk2_memorypool_t* this, int fd);
void              funk2_memorypool__decompress_and_free_compressed_data_for_loading(funk2_memorypool_t* this);
void              funk2_memorypool__rebuild_memory_from_image                      (funk2_memorypool_t* this);
void              funk2_memorypool__load_from_stream                               (funk2_memorypool_t* this, int fd);

#endif // F2__MEMORYPOOL__H

