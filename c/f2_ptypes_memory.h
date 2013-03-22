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

#ifndef F2__PTYPES__MEMORY__H
#define F2__PTYPES__MEMORY__H

// *** Abstraction Barrier Warning: Memory Manager (memory.c) and Primitive Type (ptype.c) Access Only ***
//
// These definitions are only used in the funk memory manager and the ptypes implementations themselves.
// These definitions are not thread safe because they allow uncmutexed access to the raw memory objects (which may change locations due to gc in other processor threads).
// Outside of the memory manager, the safely abstracted f2ptr interfaces provided in ptypes.h should be used.

#include "f2_global.h"
#include "f2_ptypes.h"
#include "f2_memory.h"
#include "f2_processor_mutex.h"
#include "f2_processor_readwritelock.h"
#include "f2_processor_spinlock.h"

// memblock


// ptype

struct ptype_block_s {
  funk2_memblock_t block;
  f2ptr            cause          : f2ptr__bit_num;
  f2ptr            creation_fiber : f2ptr__bit_num;
} __attribute__((__packed__));
typedef struct ptype_block_s ptype_block_t;

#define __pure__f2ptype__raw(this)                        (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->block.ptype)
#define __pure__f2ptype__cause(this)                      (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause)
#define __pure__f2ptype__cause__set(this, value)          (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause = (value))
#define __pure__f2ptype__creation_fiber(this)             (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->creation_fiber)
#define __pure__f2ptype__creation_fiber__set(this, value) (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->creation_fiber = (value))


// integer

struct ptype_integer_block_s {
  ptype_block_t ptype;
  s64           i;
} __attribute__((__packed__));
typedef struct ptype_integer_block_s ptype_integer_block_t;

ptype_integer_block_t* ptype_integer_block__new(int pool_index, f2ptr cause, s64 i);

#define __pure__f2integer__new(pool_index, cause, i) ptype_integer__new(pool_index, cause, i)
#define __pure__f2integer__i(this)                   (((ptype_integer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->i)


// double

struct ptype_double_block_s {
  ptype_block_t ptype;
  double        d;
} __attribute__((__packed__));
typedef struct ptype_double_block_s ptype_double_block_t;

ptype_double_block_t* ptype_double_block__new(int pool_index, f2ptr cause, double d);

#define __pure__f2double__new(pool_index, cause, d) ptype_double__new(pool_index, cause, d)
#define __pure__f2double__d(this)                   (((ptype_double_block_t*)(from_ptr(f2ptr_to_ptr(this))))->d)


// float

struct ptype_float_block_s {
  ptype_block_t ptype;
  float         f;
} __attribute__((__packed__));
typedef struct ptype_float_block_s ptype_float_block_t;

ptype_float_block_t* ptype_float_block__new(int pool_index, f2ptr cause, float f);

#define __pure__f2float__new(pool_index, cause, f) ptype_float__new(pool_index, cause, f)
#define __pure__f2float__f(this)                   (((ptype_float_block_t*)(from_ptr(f2ptr_to_ptr(this))))->f)


// pointer

struct ptype_pointer_block_s {
  ptype_block_t ptype;
  ptr           p;
} __attribute__((__packed__));
typedef struct ptype_pointer_block_s ptype_pointer_block_t;

ptype_pointer_block_t* ptype_pointer_block__new(int pool_index, f2ptr cause, ptr p);

#define __pure__f2pointer__new(pool_index, cause, p) ptype_pointer__new(pool_index, cause, p)
#define __pure__f2pointer__p(this)                   (((ptype_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->p)


// cmutex

struct ptype_cmutex_block_s {
  ptype_block_t           ptype;
  boolean_t               locked_state; // this state is persistent between boots.
  funk2_processor_mutex_t m[1];         // this state is reinitialized at each boot.
} __attribute__((__packed__));
typedef struct ptype_cmutex_block_s ptype_cmutex_block_t;

ptype_cmutex_block_t*    ptype_cmutex_block__new(int pool_index, f2ptr cause);
funk2_processor_mutex_t* ptype_cmutex__m(f2ptr this, f2ptr cause);

#define __pure__f2cmutex__new(pool_index, cause)         ptype_cmutex__new(pool_index, cause)
#define __pure__f2cmutex__locked_state(this)             (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state)
#define __pure__f2cmutex__locked_state__set(this, value) (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state = (value))
#define __pure__f2cmutex__m(this)                        (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->m)


// creadwritelock

struct ptype_creadwritelock_block_s {
  ptype_block_t                   ptype;
  funk2_processor_readwritelock_t rwlock[1];
} __attribute__((__packed__));
typedef struct ptype_creadwritelock_block_s ptype_creadwritelock_block_t;

ptype_creadwritelock_block_t*    ptype_creadwritelock_block__new(int pool_index, f2ptr cause);
funk2_processor_readwritelock_t* ptype_creadwritelock__rwlock   (f2ptr this, f2ptr cause);

#define __pure__f2creadwritelock__new(pool_index, cause) ptype_creadwritelock__new(pool_index, cause)
#define __pure__f2creadwritelock__rwlock(this)           (((ptype_creadwritelock_block_t*)(from_ptr(f2ptr_to_ptr(this))))->rwlock)


// character

struct ptype_char_block_s {
  ptype_block_t     ptype;
  funk2_character_t ch;
} __attribute__((__packed__));;
typedef struct ptype_char_block_s ptype_char_block_t;

ptype_char_block_t* ptype_char_block__new(int pool_index, f2ptr cause, funk2_character_t ch);

#define __pure__f2char__new(pool_index, cause, ch) ptype_char__new(pool_index, cause, ch)
#define __pure__f2char__ch(this)                   (((ptype_char_block_t*)(from_ptr(f2ptr_to_ptr(this))))->ch)


// string

struct ptype_string_block_s {
  ptype_block_t     ptype;
  u64               length;
  funk2_character_t str[0];
} __attribute__((__packed__));
typedef struct ptype_string_block_s ptype_string_block_t;

ptype_string_block_t* ptype_string_block__new(int pool_index, f2ptr cause, uint len, funk2_character_t* data);

#define __pure__f2string__new(pool_index, cause, len, init) ptype_string__new(pool_index, cause, len, init)
#define __pure__f2string__length(this)                      (((ptype_string_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2string__str(this)                         (((ptype_string_block_t*)(from_ptr(f2ptr_to_ptr(this))))->str)


// symbol

struct ptype_symbol_block_s {
  ptype_block_t     ptype;
  u64               length;
  u64               eq_hash_value;
  funk2_character_t str[0];
} __attribute__((__packed__));
typedef struct ptype_symbol_block_s ptype_symbol_block_t;

ptype_symbol_block_t* ptype_symbol_block__new(int pool_index, f2ptr cause, uint len, funk2_character_t* data);

#define __pure__f2symbol__new(pool_index, cause, len, init) ptype_symbol__new(pool_index, cause, len, init)
#define __pure__f2symbol__length(this)                      (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2symbol__eq_hash_value(this)               (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->eq_hash_value)
#define __pure__f2symbol__str(this)                         (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->str)


// chunk

struct ptype_chunk_block_s {
  ptype_block_t ptype;
  u64           length;
  u8            bytes[0];
} __attribute__((__packed__));
typedef struct ptype_chunk_block_s ptype_chunk_block_t;

ptype_chunk_block_t* ptype_chunk_block__new(int pool_index, f2ptr cause, uint len, u8* bytes);
u8*                  ptype_chunk__bytes(f2ptr this, f2ptr cause);

#define __pure__f2chunk__new(pool_index, cause, len, bytes)      ptype_chunk__new(pool_index, cause, len, bytes)
#define __pure__f2chunk__new_copy(pool_index, cause, init_chunk) ptype_chunk__new_copy(pool_index, cause, init_chunk)
#define __pure__f2chunk__length(this)                            (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2chunk__bytes(this)                             (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes)

#define __pure__f2chunk__bit8__elt(this, index) \
  ({									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u8*   temp_u8_ptr   = (u8*)temp_void_ptr;				\
    *temp_u8_ptr;							\
  })
#define __pure__f2chunk__bit8__elt__set(this, index, value)		\
  {									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u8*   temp_u8_ptr   = (u8*)temp_void_ptr;				\
    *temp_u8_ptr = value;						\
  }
#define __pure__f2chunk__bit16__elt(this, index)			\
  ({									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u16*  temp_u16_ptr  = (u16*)temp_void_ptr;				\
    *temp_u16_ptr;							\
  })
#define __pure__f2chunk__bit16__elt__set(this, index, value)		\
  {									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u16*  temp_u16_ptr  = (u16*)temp_void_ptr;				\
    *temp_u16_ptr = value;						\
  }
#define __pure__f2chunk__bit32__elt(this, index)			\
  ({									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u32*  temp_u32_ptr  = (u32*)temp_void_ptr;				\
    *temp_u32_ptr;							\
  })
#define __pure__f2chunk__bit32__elt__set(this, index, value)		\
  {									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u32*  temp_u32_ptr  = (u32*)temp_void_ptr;				\
    *temp_u32_ptr = value;						\
  }
#define __pure__f2chunk__bit64__elt(this, index)			\
  ({									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u64*  temp_u64_ptr  = (u64*)temp_void_ptr;				\
    *temp_u64_ptr;							\
  })
#define __pure__f2chunk__bit64__elt__set(this, index, value)		\
  {									\
    void* temp_void_ptr = (void*)(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes + index); \
    u64*  temp_u64_ptr  = (u64*)temp_void_ptr;				\
    *temp_u64_ptr = value;						\
  }

//#define __pure__f2chunk__bit8__elt(this, index)                          (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])
//#define __pure__f2chunk__bit8__elt__set(this, index, value)              (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index] = (u8)(value))
//#define __pure__f2chunk__bit16__elt(this, index)              (*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
//#define __pure__f2chunk__bit16__elt__set(this, index, value) ((*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u16)(value))
//#define __pure__f2chunk__bit32__elt(this, index)              (*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
//#define __pure__f2chunk__bit32__elt__set(this, index, value) ((*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u32)(value))
//#define __pure__f2chunk__bit64__elt(this, index)              (*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
//#define __pure__f2chunk__bit64__elt__set(this, index, value) ((*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u64)(value))


// cons

struct ptype_cons_block_s {
  ptype_block_t ptype;
  f2ptr_t       car;
  f2ptr_t       cdr;
} __attribute__((__packed__));
typedef struct ptype_cons_block_s ptype_cons_block_t;

ptype_cons_block_t* ptype_cons_block__new(int pool_index, f2ptr cause, u64 len, ptr f2ptr_ptr);

#define __pure__f2cons__new(pool_index, cause, car, cdr) ptype_cons__new(pool_index, cause, car, cdr)
#define __pure__f2cons__car(this)                        (((ptype_cons_block_t*)(from_ptr(f2ptr_to_ptr(this))))->car.data)
#define __pure__f2cons__car__set(this, value)            (((ptype_cons_block_t*)(from_ptr(f2ptr_to_ptr(this))))->car.data = (value))
#define __pure__f2cons__cdr(this)                        (((ptype_cons_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cdr.data)
#define __pure__f2cons__cdr__set(this, value)            (((ptype_cons_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cdr.data = (value))


// simple_array

struct ptype_simple_array_block_s {
  ptype_block_t ptype;
  u64           length : (f2ptr__bit_num - 2);
  f2ptr_t       slot[0];
} __attribute__((__packed__));
typedef struct ptype_simple_array_block_s ptype_simple_array_block_t;

ptype_simple_array_block_t* ptype_simple_array_block__new(int pool_index, f2ptr cause, u64 len, ptr f2ptr_ptr);

#define __pure__f2simple_array__new(pool_index, cause, len, f2ptr_ptr) ptype_simple_array__new(pool_index, cause, len, f2ptr_ptr)
#define __pure__f2simple_array__length(this)                           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2simple_array__elt(this, index)                       (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->slot[index].data)
#define __pure__f2simple_array__elt__set(this, index, value)           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->slot[index].data = (value))


// larva

struct ptype_larva_block_s {
  ptype_block_t ptype;
  u32           larva_type;
  f2ptr         bug : f2ptr__bit_num;
} __attribute__((__packed__));
typedef struct ptype_larva_block_s ptype_larva_block_t;

ptype_larva_block_t* ptype_larva_block__new(int pool_index, f2ptr cause, u32 larva_type, f2ptr bug);

#define __pure__f2larva__new(pool_index, cause, larva_type, bug) ptype_larva__new(pool_index, cause, larva_type, bug)
#define __pure__f2larva__larva_type(this)                        (((ptype_larva_block_t*)(from_ptr(f2ptr_to_ptr(this))))->larva_type)
#define __pure__f2larva__bug(this)                               (((ptype_larva_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bug)


// mutable_array_pointer

struct ptype_mutable_array_pointer_block_s {
  ptype_block_t ptype;
  f2ptr         array : f2ptr__bit_num;
  u64           index;
} __attribute__((__packed__));
typedef struct ptype_mutable_array_pointer_block_s ptype_mutable_array_pointer_block_t;

ptype_mutable_array_pointer_block_t* ptype_mutable_array_pointer_block__new(int pool_index, f2ptr cause, u64 index, f2ptr array);

#define __pure__f2mutable_array_pointer__new(pool_index, cause, array, index) ptype_mutable_array_pointer__new(pool_index, cause, array, index)
#define __pure__f2mutable_array_pointer__array(this)                          (((ptype_mutable_array_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->array)
#define __pure__f2mutable_array_pointer__array__set(this, value)              (((ptype_mutable_array_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->array = (value))
#define __pure__f2mutable_array_pointer__index(this)                          (((ptype_mutable_array_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->index)
#define __pure__f2mutable_array_pointer__index__set(this, value)              (((ptype_mutable_array_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->index = (value))

#endif // F2__PTYPES__MEMORY__H

