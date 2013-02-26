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

#ifndef F2__GLOBAL__H
#define F2__GLOBAL__H

#include <stdio.h>
#include <stdlib.h>

#include "f2_archconfig.h"
#include "f2_debug_macros.h"
#include "f2_system_headers.h"

typedef unsigned int uint;


// funk2_character

typedef u32 funk2_character_t;

#define funk2_character__utf8_length(this) ({				\
      funk2_character_t funk2_character__utf8_length__this = (this);	\
      u64 utf8_length = 1;						\
      if (funk2_character__utf8_length__this <= 0x7f) {			\
	utf8_length = 1;						\
      } else if (funk2_character__utf8_length__this <= 0x07ff) {	\
	utf8_length = 2;						\
      } else if (funk2_character__utf8_length__this <= 0xffff) {	\
	utf8_length = 3;						\
      } else if (funk2_character__utf8_length__this <= 0x1fffff) {	\
	utf8_length = 4;						\
      } else if (funk2_character__utf8_length__this <= 0x3ffffff) {	\
	utf8_length = 5;						\
      } else if (funk2_character__utf8_length__this <= 0x7fffffff) {	\
	utf8_length = 6;						\
      }									\
      utf8_length;							\
    })

#define funk2_character__utf8_str_copy(this, utf8_str) {		\
    funk2_character_t funk2_character__utf8_str_copy__this     = (this); \
    u8*               funk2_character__utf8_str_copy__utf8_str = (utf8_str); \
    if (funk2_character__utf8_str_copy__this <= 0x7f) {			\
      funk2_character__utf8_str_copy__utf8_str[0] = funk2_character__utf8_str_copy__this; \
    } else if (funk2_character__utf8_str_copy__this <= 0x07ff) {	\
      funk2_character__utf8_str_copy__utf8_str[0] = 0xc0 + (0x1f & (funk2_character__utf8_str_copy__this >> 6)); \
      funk2_character__utf8_str_copy__utf8_str[1] = 0x80 + (0x3f & funk2_character__utf8_str_copy__this); \
    } else if (funk2_character__utf8_str_copy__this <= 0xffff) {	\
      funk2_character__utf8_str_copy__utf8_str[0] = 0xe0 + (0x0f & (funk2_character__utf8_str_copy__this >> 12)); \
      funk2_character__utf8_str_copy__utf8_str[1] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 6)); \
      funk2_character__utf8_str_copy__utf8_str[2] = 0x80 + (0x3f & funk2_character__utf8_str_copy__this); \
    } else if (funk2_character__utf8_str_copy__this <= 0x1fffff) {	\
      funk2_character__utf8_str_copy__utf8_str[0] = 0xf0 + (0x07 & (funk2_character__utf8_str_copy__this >> 18)); \
      funk2_character__utf8_str_copy__utf8_str[1] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 12)); \
      funk2_character__utf8_str_copy__utf8_str[2] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 6)); \
      funk2_character__utf8_str_copy__utf8_str[3] = 0x80 + (0x3f & funk2_character__utf8_str_copy__this); \
    } else if (funk2_character__utf8_str_copy__this <= 0x3ffffff) {	\
      funk2_character__utf8_str_copy__utf8_str[0] = 0xf7 + (0x03 & (funk2_character__utf8_str_copy__this >> 24)); \
      funk2_character__utf8_str_copy__utf8_str[1] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 18)); \
      funk2_character__utf8_str_copy__utf8_str[2] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 12)); \
      funk2_character__utf8_str_copy__utf8_str[3] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 6)); \
      funk2_character__utf8_str_copy__utf8_str[4] = 0x80 + (0x3f & funk2_character__utf8_str_copy__this); \
    } else if (funk2_character__utf8_str_copy__this <= 0x7fffffff) {	\
      funk2_character__utf8_str_copy__utf8_str[0] = 0xfc + (0x01 & (funk2_character__utf8_str_copy__this >> 30)); \
      funk2_character__utf8_str_copy__utf8_str[1] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 24)); \
      funk2_character__utf8_str_copy__utf8_str[2] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 18)); \
      funk2_character__utf8_str_copy__utf8_str[3] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 12)); \
      funk2_character__utf8_str_copy__utf8_str[4] = 0x80 + (0x3f & (funk2_character__utf8_str_copy__this >> 6)); \
      funk2_character__utf8_str_copy__utf8_str[5] = 0x80 + (0x3f & funk2_character__utf8_str_copy__this); \
    } else {								\
      funk2_character__utf8_str_copy__utf8_str[0] = (u8)'?';						\
    }									\
  }


#ifndef F2__APPLE
typedef unsigned char boolean_t;
#endif // F2__APPLE

#if defined(__INTEL_COMPILER)
// remark #383: value copied to temporary, reference to temporary used
//#  pragma warning(disable: 383)
// remark #271: trailing comma is nonstandard
#  pragma warning(disable: 271)
// remark #424: extra ";" ignored
#  pragma warning(disable: 424)
// remark #981: operands are evaluated in unspecified order
#  pragma warning(disable: 981)
// remark #869: parameter "cause" was never referenced
#  pragma warning(disable: 869)
// remark #1418: external function definition with no prior declaration
#  pragma warning(disable: 1418)
// remark #2259: non-pointer conversion may lose significant bits
#  pragma warning(disable: 2259)
// remark #1599: declaration hides variable
#  pragma warning(disable: 1599)
#endif	// __INTEL_COMPILER

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

// pool_address can be larger than pool_block_address.
// the difference ends up being the f2ptr_block__bit_num
// computer_id__bit_num can be zero.

typedef                             u64       pool_address_t;
#define pool_address__fstr          X64__fstr
#define pool_address__bit_num        38
#define pool_address__max_byte_num     ((1ull << pool_address__bit_num) - 1)

typedef                             u64       f2ptr;
#define f2ptr__fstr                 X64__fstr
#define f2ptr__bit_num               48
typedef                              u8       computer_id_t;
#define computer_id__fstr            X8__fstr
#define computer_id__bit_num          0
typedef                              u8       pool_index_t;
#define pool_index__fstr             X8__fstr
#define pool_index__bit_num          10
typedef                             u64       pool_block_address_t;
#define pool_block_address__fstr    X64__fstr
#define pool_block_address__bit_num  38


#define f2ptr_block__bit_num   (pool_address__bit_num - pool_block_address__bit_num)
#define f2ptr_block__size      (1ull << f2ptr_block__bit_num)
#define f2ptr_block__max_value ((1ull << f2ptr_block__bit_num) - 1)


typedef struct f2ptr_s f2ptr_t;
struct f2ptr_s {
  f2ptr data : f2ptr__bit_num;
} __attribute__((__packed__));

#define ideal_scheduler_processor_num processor_num

#if (ideal_scheduler_processor_num > (1<<(pool_index__bit_num)))
#  define scheduler_processor_num (1<<(pool_index__bit_num))
#else
#  define scheduler_processor_num ideal_scheduler_processor_num
#endif
     
#define memory_pool_num scheduler_processor_num





typedef u64 event_id_t;
#define event_id__fstr "#x" X64__fstr

#if (f2ptr__bit_num != (computer_id__bit_num + pool_index__bit_num + pool_block_address__bit_num))
#  error (f2ptr__bit_num != (computer_id__bit_num + pool_index__bit_num + pool_block_address__bit_num))
#endif

#endif // F2__GLOBAL__H

