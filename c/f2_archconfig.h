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

#ifndef F2__ARCHCONFIG__H
#define F2__ARCHCONFIG__H

#include "f2_os.h"

#include <sys/types.h>
#include <stdint.h>

#include "../config.h"
#include "../config_bit_num.h"
#include "../config_compile_time_id.h"

typedef uint64_t ptr; //                        0 to 18.446744073709551615e18
typedef uint64_t u64; //                        0 to 18.446744073709551615e18
typedef  int64_t s64; // -9.223372036854775808e18 to 9.223372036854775807e18
typedef uint64_t u48;
typedef  int64_t s48;
typedef uint32_t u32; //                        0 to 4.294967295e9
typedef  int32_t s32; //           -2.147483648e9 to 2.147483647e9
typedef uint16_t u16; //                        0 to 65535
typedef  int16_t s16; //                   -32768 to 32767
typedef  uint8_t  u8; //                        0 to 255
typedef     char  s8; //                     -128 to 127

#if int__bit_num == pointer__bit_num
#  define   to_ptr(value)        ((ptr)(unsigned int)(value))
#  define from_ptr(value) ((void*)(unsigned int)(ptr)(value))
#elif long__bit_num == pointer__bit_num
#  define   to_ptr(value)        ((ptr)(unsigned long)(value))
#  define from_ptr(value) ((void*)(long)(ptr)(value))
#elif long_long__bit_num == pointer__bit_num
#  define   to_ptr(value)        ((ptr)(unsigned long long)(value))
#  define from_ptr(value) ((void*)(unsigned long long)(ptr)(value))
#else
#  error "can't find same sized integer for pointer conversion to integer."
#endif

typedef u8 byte;

typedef u64 f2size_t;

#ifdef F2__APPLE
#  if long_long__bit_num == 64
#    define s64__fstr                   "%lld"
#    define u64__fstr_without_percent    "llu"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr_without_percent   "llx"
#    define x64__fstr                   "%" x64__fstr_without_percent
#    define X64__fstr_without_percent   "llX"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09lld"
#  elif long__bit_num == 64
#    define s64__fstr                   "%ld"
#    define u64__fstr_without_percent    "lu"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr_without_percent   "lx"
#    define x64__fstr                   "%" x64__fstr_without_percent
#    define X64__fstr_without_percent   "lX"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09ld"
#  elif int__bit_num == 64
#    define s64__fstr                   "%d"
#    define u64__fstr_without_percent    "u"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr                   "%X"
#    define X64__fstr_without_percent   "x"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09d"
#  else
#    error configuration not defined.  try: make clean; make configure; make
#  endif
#else
#  if int__bit_num == 64
#    define s64__fstr                   "%d"
#    define u64__fstr_without_percent    "u"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr_without_percent   "X"
#    define x64__fstr                   "%" x64__fstr_without_percent
#    define X64__fstr_without_percent   "x"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09d"
#  elif long__bit_num == 64
#    define s64__fstr                   "%ld"
#    define u64__fstr_without_percent    "lu"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr_without_percent   "lx"
#    define x64__fstr                   "%" x64__fstr_without_percent
#    define X64__fstr_without_percent   "lX"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09ld"
#  elif long_long__bit_num == 64
#    define s64__fstr                   "%lld"
#    define u64__fstr_without_percent    "llu"
#    define u64__fstr                   "%" u64__fstr_without_percent
#    define x64__fstr_without_percent   "llx"
#    define x64__fstr                   "%" x64__fstr_without_percent
#    define X64__fstr_without_percent   "llX"
#    define X64__fstr                   "%" X64__fstr_without_percent
#    define nano_decimal_fraction__fstr "%09lld"
#  else
#    error configuration not defined.  try: make clean; make configure; make
#  endif
#endif // F2__APPLE

#if int__bit_num == 32
#  define s32__fstr "%d"
#  define u32__fstr "%u"
#  define x32__fstr "%x"
#  define X32__fstr "%X"
#elif long__bit_num == 32
#  define s32__fstr "%ld"
#  define u32__fstr "%lu"
#  define x32__fstr "%lx"
#  define X32__fstr "%lX"
#elif long_long__bit_num == 32
#  define s32__fstr "%lld"
#  define u32__fstr "%llu"
#  define x32__fstr "%llx"
#  define X32__fstr "%llX"
#else
#  error configuration not defined.  try: make clean; make configure; make
#endif

#define ptr__fstr X64__fstr

#define s16__fstr s32__fstr
#define u16__fstr u32__fstr
#define X16__fstr X32__fstr
#define s8__fstr  s16__fstr
#define u8__fstr  u16__fstr
#define X8__fstr  X16__fstr

#define f2size_t__fstr u64__fstr

#define double__fstr "%f"
#define float__fstr  "%f"
#define pointer__fstr "#x" X64__fstr

// function mappings
#define f2__mmap  mmap
#define f2__lseek lseek

//#define MEMORY_OPTION__MEMBLOCK__RENDER_DATA
#define MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP
#define DYNAMIC_MEMORY
#define GMODULE_PRIMFUNKS



// **********************************************
// *********** F2__ARCH_SENSOR_NODE *************
// **********************************************
#ifdef F2__ARCH_SENSOR_NODE

#  define F2__ARCH_DEFINED
#
#  ifdef MEMORY_OPTION__MEMBLOCK__RENDER_DATA
#    error MEMORY_OPTION__MEMBLOCK__RENDER_DATA should not be defined.
#  endif
#
#  ifdef MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP
#    error MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP should not be defined.
#  endif

#define STATIC_MEMORY
#define STATIC_MEMORY__BYTE_NUM F2__TOTAL_INITIAL_MEMORY

#endif // F2__ARCH_SENSOR_NODE


#endif // F2__ARCHCONFIG__H
