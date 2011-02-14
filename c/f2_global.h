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

#ifndef F2__GLOBAL__H
#define F2__GLOBAL__H

#include <stdio.h>
#include <stdlib.h>

#include "f2_archconfig.h"
#include "f2_debug_macros.h"
#include "f2_system_headers.h"

typedef unsigned int  uint;

#ifndef F2__APPLE
typedef unsigned char boolean_t;
#endif // F2__APPLE

#define int_bit_num    (sizeof(int)*8)
#define max_uint_value ((unsigned int)-1)

#define F2__INITIAL_MEMORY (10 * 1024 * 1024ull)

#ifdef F2__ASSERTIONS__DEBUG
#  define debug__assert(cond, fiber, desc)                            {if(! (cond)) {assert_failed(fiber, __FILE__, __LINE__, desc);}}
#  define debug__assert_and_on_failure(cond, fiber, desc, on_failure) {if(! (cond)) {{on_failure;} assert_failed(fiber, __FILE__, __LINE__, desc);}}
#else
#  define debug__assert(cond, fiber, desc)
#  define debug__assert_and_on_failure(cond, fiber, desc, on_failure)
#endif

#define F2__ASSERTIONS__RELEASE

#ifdef F2__ASSERTIONS__RELEASE
#  define release__assert(cond, fiber, desc)                            {if(! (cond)) {assert_failed(fiber, __FILE__, __LINE__, desc);}}
#  define release__assert_and_on_failure(cond, fiber, desc, on_failure) {if(! (cond)) {{on_failure;} assert_failed(fiber, __FILE__, __LINE__, desc);}}
#else
#  define release__assert(cond, fiber, desc)
#  define release__assert_and_on_failure(cond, fiber, desc, on_failure)
#endif

#define boolean__false ((boolean_t)0)
#define boolean__true  (! boolean__false)

#define max_equals_hash_value_recursion_depth 1024

#define error(fiber, str) {fputs("\n*** ", stderr); fputs(str, stderr); fputs(" ***\n", stderr); assert_failed(fiber, __FILE__, __LINE__, str); exit(-1);}

// Single user 32 bit mode is only used for very old computers or those with very little (less than 1 gigabyte of usable disk space for a demo of the language).
#ifdef F2__SINGLE_USER_32BIT_VERSION
    typedef                      u32 f2ptr;
#   define f2ptr__fstr           X32__fstr
#   define f2ptr__bit_num         32
    typedef                       u8 computer_id_t;
#   define computer_id__fstr      X8__fstr
#   define computer_id__bit_num    1
    typedef                       u8 pool_index_t;
#   define pool_index__fstr       X8__fstr
#   define pool_index__bit_num     1
    typedef                      u32 pool_address_t;
#   define pool_address__fstr    X32__fstr
#   define pool_address__bit_num  30
#else
    typedef                      u64 f2ptr;
#   define f2ptr__fstr           X64__fstr
#   define f2ptr__bit_num         64
    typedef                      u32 computer_id_t;
#   define computer_id__fstr     X32__fstr
#   define computer_id__bit_num   17
    typedef                       u8 pool_index_t;
#   define pool_index__fstr       X8__fstr
#   define pool_index__bit_num     5
    typedef                      u64 pool_address_t;
#   define pool_address__fstr    X64__fstr
#   define pool_address__bit_num  42
#endif


//#define scheduler_processor_num 1
#if (processor_num_power <= 2)
#  define ideal_scheduler_processor_num (4)
#else
#  define ideal_scheduler_processor_num (1<<(processor_num_power))
#endif

#if (ideal_scheduler_processor_num > (1<<(pool_index__bit_num)))
#  define scheduler_processor_num (1<<(pool_index__bit_num))
#else
#  define scheduler_processor_num ideal_scheduler_processor_num
#endif
     
#define memory_pool_num scheduler_processor_num





typedef u64 event_id_t;
#define event_id__fstr "#x" X64__fstr

#if (f2ptr__bit_num != (computer_id__bit_num + pool_index__bit_num + pool_address__bit_num))
#  error (f2ptr__bit_num != (computer_id__bit_num + pool_index__bit_num + pool_address__bit_num))
#endif

#endif // F2__GLOBAL__H

