// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__MEMORY__TYPES__H
#define F2__MEMORY__TYPES__H

typedef struct funk2_memory_s funk2_memory_t;

#endif // F2__MEMORY__TYPES__H

#ifndef F2__MEMORY__H
#define F2__MEMORY__H

#include "f2_memorypool.h"
#include "f2_processor_mutex.h"
#include "f2_user_thread_controller.h"
#include "f2_never_delete_list.h"

//#define DEBUG_MEMORY 1

struct funk2_memory_s {
  funk2_memorypool_t pool[memory_pool_num];
  ptr                global_environment_ptr;
  f2ptr              global_environment_f2ptr;
  pthread_t          memory_handling_thread;
  boolean_t          bootstrapping_mode;
};

#define nil ((f2ptr)0)

#define maximum_generation_num 7

#define f2ptr__computer_id__bit_num        computer_id__bit_num
#define f2ptr__pool_index__bit_num         pool_index__bit_num
#define f2ptr__pool_block_address__bit_num pool_block_address__bit_num

#define f2ptr__computer_id__max_value        ((((u64)1)<<(f2ptr__computer_id__bit_num))        - 1)
#define f2ptr__pool_index__max_value         ((((u64)1)<<(f2ptr__pool_index__bit_num))         - 1)
#define f2ptr__pool_block_address__max_value ((((u64)1)<<(f2ptr__pool_block_address__bit_num)) - 1)

#define f2ptr__new(computer_id, pool_index, pool_block_address) ((f2ptr)((u64)(((u64)(computer_id)) << (f2ptr__pool_block_address__bit_num + f2ptr__pool_index__bit_num)) | \
									 (u64)(((u64)(pool_index))  <<  f2ptr__pool_block_address__bit_num) | \
									 (u64)( (u64)(pool_block_address))))

#if (computer_id__bit_num == 0)
#  define __f2ptr__computer_id(f2p)                        0
#else
#  define __f2ptr__computer_id(f2p)                        (((u64)(f2p)) >> (f2ptr__pool_block_address__bit_num + f2ptr__pool_index__bit_num))
#endif
#define __f2ptr__pool_index(f2p)                          ((((u64)(f2p)) >> f2ptr__pool_block_address__bit_num) & f2ptr__pool_index__max_value)
#define __f2ptr__pool_block_address(f2p)                  (((u64)(f2p)) & f2ptr__pool_block_address__max_value)

#if (computer_id__bit_num == 0)
#  define __f2ptr__computer_id__set(f2p, computer_id) (f2p)
#else
#  define __f2ptr__computer_id__set(f2p, computer_id) f2ptr__new(         computer_id,      __f2ptr__pool_index(f2p), __f2ptr__pool_block_address(f2p))
#endif
#define __f2ptr__pool_index__set(f2p, pool_index)     f2ptr__new(__f2ptr__computer_id(f2p),          pool_index,      __f2ptr__pool_block_address(f2p))
#define __f2ptr__pool_block_address__set(f2p, pool_block_address) f2ptr__new(__f2ptr__computer_id(f2p), __f2ptr__pool_index(f2p),          pool_block_address)

#define __f2ptr__pool_address(f2p) ((((u64)(__f2ptr__pool_block_address(f2p)) - 1) << f2ptr_block__bit_num) + 1)

#define   __ptr__pool_block_address(pool_index, p)			\
  ((((u64)p) != (u64)0) ? ({						\
      u64 return_value = ((u64)(((u64)(p)) - (u64)(__funk2.memory.pool[pool_index].global_f2ptr_offset))); \
      return_value --;							\
      if (return_value & f2ptr_block__max_value) {			\
	error(nil, "__ptr__pool_block_address error: not aligned.");	\
      }									\
      return_value >>= f2ptr_block__bit_num;				\
      return_value ++;							\
      return_value;							\
    }) : (u64)0)

#define __f2ptr_to_ptr(f2p)             ((((u64)(f2p)) !=       ((u64)0)) ? ((to_ptr(((u64)__f2ptr__pool_address((u64)f2p)) + __funk2.memory.pool[__f2ptr__pool_index((u64)f2p)].global_f2ptr_offset))) : (to_ptr(NULL)))
#define   __ptr_to_f2ptr(pool_index, p) (((to_ptr(p))  != (to_ptr(NULL))) ?    ((u64)(f2ptr__new(0, pool_index, __ptr__pool_block_address(pool_index, p))))                              :   ((u64)0))

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

#define fast__f2ptr_to_ptr(f2p) __f2ptr_to_ptr(f2p)

#define global_environment()       funk2_memory__global_environment(&(__funk2.memory))
#define global_environment__set(x) funk2_memory__global_environment__set(&(__funk2.memory), x)

// misc

void safe_write(int fd, ptr p, f2size_t object_size);
void safe_read(int fd, ptr p, f2size_t object_size);

// funk2_memory

void      funk2_memory__init                                                    (funk2_memory_t* this);
void      funk2_memory__destroy                                                 (funk2_memory_t* this);
void      funk2_memory__handle                                                  (funk2_memory_t* this);
void      funk2_memory__print_gc_stats                                          (funk2_memory_t* this);
boolean_t funk2_memory__is_reasonably_valid_funk2_memblock_ptr                  (funk2_memory_t* this, ptr p);
boolean_t funk2_memory__is_reasonably_valid_used_funk2_memblock_ptr             (funk2_memory_t* this, ptr p);
boolean_t funk2_memory__is_valid_funk2_memblock_ptr                             (funk2_memory_t* this, ptr p);
ptr       funk2_memory__f2ptr_to_ptr__debug                                     (funk2_memory_t* this, f2ptr f2p);
ptr       funk2_memory__used_f2ptr_to_ptr__debug                                (funk2_memory_t* this, f2ptr f2p);
ptr       funk2_memory__find_or_create_free_splittable_funk2_memblock_and_unfree(funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__try_new                           (funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__new_from_pool                     (funk2_memory_t* this, int pool_index, f2size_t byte_num);
f2ptr     funk2_memory__funk2_memblock_f2ptr__new                               (funk2_memory_t* this, f2size_t byte_num);
u64       funk2_memory__pool__maximum_block__byte_num                           (funk2_memory_t* this, s64 pool_index);
u64        raw__memory__pool__maximum_block__byte_num                           (f2ptr cause, s64 pool_index);
f2ptr       f2__memory__pool__maximum_block__byte_num                           (f2ptr cause, f2ptr pool_index);
void      funk2_memory__global_environment__set                                 (funk2_memory_t* this, f2ptr global_environment);
f2ptr     funk2_memory__global_environment                                      (funk2_memory_t* this);
boolean_t funk2_memory__save_image_to_file                                      (funk2_memory_t* this, char* filename);
f2ptr     funk2_memory__ptr_to_f2ptr__slow                                      (funk2_memory_t* this, ptr p);
void      funk2_memory__rebuild_memory_info_from_image                          (funk2_memory_t* this);
boolean_t funk2_memory__load_image_from_file                                    (funk2_memory_t* this, char* filename);
boolean_t funk2_memory__check_all_memory_pointers_valid                         (funk2_memory_t* this);
void      funk2_memory__memory_test                                             (funk2_memory_t* this);
f2ptr       f2__memory__assert_valid                                            (f2ptr cause);

#ifdef DEBUG_MEMORY
#  if (DEBUG_MEMORY > 0)
#    define funk2_memory__debug_memory_test(this, level) {if (DEBUG_MEMORY >= level) {funk2_memory__memory_test(this);}}
#  else
#    define funk2_memory__debug_memory_test(this, level)
#  endif
#else
#  define funk2_memory__debug_memory_test(this, level)
#endif



// **

void f2__memory__preinitialize();
void f2__memory__initialize();
void f2__memory__destroy();

#endif // F2__MEMORY__H
