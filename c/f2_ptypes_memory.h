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

#ifndef F2__PTYPES__MEMORY__H
#define F2__PTYPES__MEMORY__H

// *** Abstraction Barrier Warning: Memory Manager (memory.c) and Primitive Type (ptype.c) Access Only ***
//
// These definitions are only used in the funk memory manager and the ptypes implementations themselves.
// These definitions are not thread safe because they allow unmutexed access to the raw memory objects (which may change locations due to gc in other heavy threads).
// Outside of the memory manager, the safely abstracted f2ptr interfaces provided in ptypes.h should be used.

#include "f2_global.h"
#include "f2_ptypes.h"
#include "f2_memory_protected.h"
//#include "f2_gfunkptr.h"

// memblock

#ifdef MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP
#  define __pure__memblock__creation_microseconds_since_1970(this) (((memblock_t*)(from_ptr(f2ptr_to_ptr(this))))->creation_microseconds_since_1970)
#endif // MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP

#ifdef MEMORY_OPTION__MEMBLOCK__RENDER_DATA
#  define __pure__memblock__render_read_activated(this)              (((memblock_t*)(from_ptr(f2ptr_to_ptr(this))))->render_read_activated)
#  define __pure__memblock__render_read_activated__set(this, value)  (((memblock_t*)(from_ptr(f2ptr_to_ptr(this))))->render_read_activated = (value))
#  define __pure__memblock__render_write_activated(this)             (((memblock_t*)(from_ptr(f2ptr_to_ptr(this))))->render_write_activated)
#  define __pure__memblock__render_write_activated__set(this, value) (((memblock_t*)(from_ptr(f2ptr_to_ptr(this))))->render_write_activated = (value))
#else
#  define __pure__memblock__render_read_activated(this)              0
#  define __pure__memblock__render_read_activated__set(this, value)
#  define __pure__memblock__render_write_activated(this)             0
#  define __pure__memblock__render_write_activated__set(this, value)
#endif // MEMORY_OPTION__MEMBLOCK__RENDER_DATA

// ptype

struct ptype_block_s {
  memblock_t block;
  ptype_t    ptype;
  f2ptr      cause;
} __attribute__((__packed__));
typedef struct ptype_block_s ptype_block_t;

#define __pure__f2ptype__raw(this)               (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->ptype)
#define __pure__f2ptype__cause(this)             (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause)
#define __pure__f2ptype__cause__set(this, value) (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause = (value))

// integer

struct ptype_integer_block_s {
  ptype_block_t ptype;
  s64           i;
} __attribute__((__packed__));
typedef struct ptype_integer_block_s ptype_integer_block_t;

ptype_integer_block_t* ptype_integer_block__new(int pool_index, f2ptr cause, s64 i);

#define __pure__f2integer__new(pool_index, cause, i) ptype_integer__new(pool_index, cause, i)
#define __pure__f2integer__i(this)       (((ptype_integer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->i)

// double

struct ptype_double_block_s {
  ptype_block_t ptype;
  double        d;
} __attribute__((__packed__));
typedef struct ptype_double_block_s ptype_double_block_t;

ptype_double_block_t* ptype_double_block__new(int pool_index, f2ptr cause, double d);

#define __pure__f2double__new(pool_index, cause, d) ptype_double__new(pool_index, cause, d)
#define __pure__f2double__d(this)       (((ptype_double_block_t*)(from_ptr(f2ptr_to_ptr(this))))->d)

// float

struct ptype_float_block_s {
  ptype_block_t ptype;
  float         f;
} __attribute__((__packed__));
typedef struct ptype_float_block_s ptype_float_block_t;

ptype_float_block_t* ptype_float_block__new(int pool_index, f2ptr cause, float f);

#define __pure__f2float__new(pool_index, cause, f) ptype_float__new(pool_index, cause, f)
#define __pure__f2float__f(this)       (((ptype_float_block_t*)(from_ptr(f2ptr_to_ptr(this))))->f)

// pointer

struct ptype_pointer_block_s {
  ptype_block_t ptype;
  ptr           p;
} __attribute__((__packed__));
typedef struct ptype_pointer_block_s ptype_pointer_block_t;

ptype_pointer_block_t* ptype_pointer_block__new(int pool_index, f2ptr cause, ptr p);

#define __pure__f2pointer__new(pool_index, cause, p) ptype_pointer__new(pool_index, cause, p)
#define __pure__f2pointer__p(this)       (((ptype_pointer_block_t*)(from_ptr(f2ptr_to_ptr(this))))->p)

// gfunkptr

struct ptype_gfunkptr_block_s {
  ptype_block_t ptype;
  f2ptr         gfunkptr;
} __attribute__((__packed__));
typedef struct ptype_gfunkptr_block_s ptype_gfunkptr_block_t;

ptype_gfunkptr_block_t* ptype_gfunkptr_block__new(int pool_index, f2ptr cause, computer_id_t gf2_computer_id, pool_index_t gf2_pool_indx, pool_address_t gf2_pool_address);

#define __pure__f2gfunkptr__new(pool_index, cause, gf2_computer_id, gf2_pool_index, gf2_pool_address) ptype_gfunkptr__new(pool_index, cause, gf2_computer_id, gf2_pool_index, gf2_pool_address)
#define __pure__f2gfunkptr__gfunkptr(this)                                                            (((ptype_gfunkptr_block_t*)(from_ptr(f2ptr_to_ptr(this))))->gfunkptr)
#define __pure__f2gfunkptr__computer_id(this)                                                         __f2ptr__computer_id(__pure__f2gfunkptr__gfunkptr(this))
#define __pure__f2gfunkptr__pool_index(this)                                                          __f2ptr__pool_index(__pure__f2gfunkptr__gfunkptr(this))
#define __pure__f2gfunkptr__pool_address(this)                                                        __f2ptr__pool_address(__pure__f2gfunkptr__gfunkptr(this))

// mutex

struct ptype_mutex_block_s {
  ptype_block_t   ptype;
  pthread_mutex_t m[1];
} __attribute__((__packed__));
typedef struct ptype_mutex_block_s ptype_mutex_block_t;

ptype_mutex_block_t* ptype_mutex_block__new(int pool_index, f2ptr cause);
pthread_mutex_t*     ptype_mutex__m(f2ptr this, f2ptr cause);

#define __pure__f2mutex__new(pool_index, cause) ptype_mutex__new(pool_index, cause)
#define __pure__f2mutex__m(this)    (((ptype_mutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->m)

// character

struct ptype_char_block_s {
  ptype_block_t ptype;
  u64           ch;
} __attribute__((__packed__));;
typedef struct ptype_char_block_s ptype_char_block_t;

ptype_char_block_t* ptype_char_block__new(int pool_index, f2ptr cause, u64 ch);

#define __pure__f2char__new(pool_index, cause, ch) ptype_char__new(pool_index, cause, ch)
#define __pure__f2char__ch(this)       (((ptype_char_block_t*)(from_ptr(f2ptr_to_ptr(this))))->ch)

// string

struct ptype_string_block_s {
  ptype_block_t ptype;
  u64           length;
  u8            str[0];
} __attribute__((__packed__));
typedef struct ptype_string_block_s ptype_string_block_t;

ptype_string_block_t* ptype_string_block__new(int pool_index, f2ptr cause, uint len, u8* data);

#define __pure__f2string__new(pool_index, cause, len, init) ptype_string__new(pool_index, cause, len, init)
#define __pure__f2string__length(this)          (((ptype_string_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2string__str(this)             (((ptype_string_block_t*)(from_ptr(f2ptr_to_ptr(this))))->str)

// symbol

struct ptype_symbol_block_s {
  ptype_block_t ptype;
  u64           length;
  u64           hash_value;
  u8            str[0];
} __attribute__((__packed__));
typedef struct ptype_symbol_block_s ptype_symbol_block_t;

ptype_symbol_block_t* ptype_symbol_block__new(int pool_index, f2ptr cause, uint len, u8* data);

#define __pure__f2symbol__new(pool_index, cause, len, init) ptype_symbol__new(pool_index, cause, len, init)
#define __pure__f2symbol__length(this)          (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2symbol__hash_value(this)      (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->hash_value)
#define __pure__f2symbol__str(this)             (((ptype_symbol_block_t*)(from_ptr(f2ptr_to_ptr(this))))->str)

void symbol_hash__reinitialize();
void symbol_hash__add_symbol(f2ptr symbol_f2ptr);

// chunk

struct ptype_chunk_block_s {
  ptype_block_t ptype;
  u64           length;
  u8            bytes[0];
} __attribute__((__packed__));;
typedef struct ptype_chunk_block_s ptype_chunk_block_t;

ptype_chunk_block_t* ptype_chunk_block__new(int pool_index, f2ptr cause, uint len, byte* bytes);
u8*                  ptype_chunk__bytes(f2ptr this, f2ptr cause);

#define __pure__f2chunk__new(pool_index, cause, len, bytes)              ptype_chunk__new(pool_index, cause, len, bytes)
#define __pure__f2chunk__new_copy(pool_index, cause, init_chunk)         ptype_chunk__new_copy(pool_index, cause, init_chunk)
#define __pure__f2chunk__length(this)                        (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2chunk__bytes(this)                         (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes)

#define __pure__f2chunk__bit8__elt(this, index)              (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])
#define __pure__f2chunk__bit8__elt__set(this, index, value)  (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index] = (u8)(value))
#define __pure__f2chunk__bit16__elt(this, index)              (*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit16__elt__set(this, index, value) ((*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u16)(value))
#define __pure__f2chunk__bit32__elt(this, index)              (*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit32__elt__set(this, index, value) ((*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u32)(value))
#define __pure__f2chunk__bit64__elt(this, index)              (*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit64__elt__set(this, index, value) ((*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u64)(value))

// dptr struct

struct dptr_s {
  f2ptr p;
  f2ptr tracing_on;
  f2ptr trace;
  f2ptr imagination_frame;
} __attribute__((__packed__));
typedef struct dptr_s dptr_t;

void dptr__init(dptr_t* dptr, f2ptr p, f2ptr tracing_on, f2ptr prev, f2ptr imagination_frame);

#define dptr__gf2_p(this)                 ((this)->p)
#define dptr__gf2_tracing_on(this)        ((this)->tracing_on)
#define dptr__gf2_trace(this)             ((this)->trace)
#define dptr__gf2_imagination_frame(this) ((this)->imagination_frame)

#define dptr__p(this)                              dptr__gf2_p(this)
#define dptr__p__set(this, value)                 (dptr__gf2_p(this) = (value))
#define dptr__tracing_on(this)                     dptr__gf2_tracing_on(this)
#define dptr__tracing_on__set(this, value)        (dptr__gf2_tracing_on(this) = (value))
#define dptr__trace(this)                          dptr__gf2_trace(this)
#define dptr__trace__set(this, value)             (dptr__gf2_trace(this) = (value))
#define dptr__imagination_frame(this)              dptr__gf2_imagination_frame(this)
#define dptr__imagination_frame__set(this, value) (dptr__gf2_imagination_frame(this) = (value))

// simple_array

struct ptype_simple_array_block_s {
  ptype_block_t ptype;
  u64           length;
  f2ptr         f2ptr_data[0];
} __attribute__((__packed__));
typedef struct ptype_simple_array_block_s ptype_simple_array_block_t;

ptype_simple_array_block_t* ptype_simple_array_block__new(int pool_index, f2ptr cause, u64 len, ptr f2ptr_ptr);

#define __pure__f2simple_array__new(pool_index, cause, len, f2ptr_ptr) ptype_simple_array__new(pool_index, cause, len, f2ptr_ptr)
#define __pure__f2simple_array__length(this)                           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2simple_array__elt(this, index)                       (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->f2ptr_data[index])
#define __pure__f2simple_array__elt__set(this, index, value)           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->f2ptr_data[index] = (value))

// traced_array

struct ptype_traced_array_block_s {
  ptype_block_t ptype;
  u64           length;
  dptr_t        dptr_data[0];
} __attribute__((__packed__));
typedef struct ptype_traced_array_block_s ptype_traced_array_block_t;

ptype_traced_array_block_t* ptype_traced_array_block__new(int pool_index, f2ptr cause, uint len, ptr dptr_ptr);

#define __pure__f2traced_array__new(pool_index, cause, len, dptr_ptr)              ptype_traced_array__new(pool_index, cause, len, dptr_ptr)
#define __pure__f2traced_array__new_from_f2ptrs(pool_index, cause, len, f2ptr_ptr) ptype_traced_array__new_from_f2ptrs(pool_index, cause, len, f2ptr_ptr)
#define __pure__f2traced_array__length(this)                                       (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2traced_array__elt_dptr(this, index)                              (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->dptr_data[index])
#define __pure__f2traced_array__elt(this, index)                                   dptr__p(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__set(this, index, value)                       dptr__p__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__tracing_on(this, index)                       dptr__tracing_on(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__tracing_on__set(this, index, value)           dptr__tracing_on__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__trace(this, index)                            dptr__trace(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__trace__set(this, index, value)                dptr__trace__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__imagination_frame(this, index)                dptr__imagination_frame(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__imagination_frame__set(this, index, value)    dptr__imagination_frame__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)

// larva

struct ptype_larva_block_s {
  ptype_block_t ptype;
  u32           type;
} __attribute__((__packed__));
typedef struct ptype_larva_block_s ptype_larva_block_t;

ptype_larva_block_t* ptype_larva_block__new(int pool_index, f2ptr cause, u32 type);

#define __pure__f2larva__new(pool_index, cause, type) ptype_larva__new(pool_index, cause, type)
#define __pure__f2larva__type(this)                   (((ptype_larva_block_t*)(from_ptr(f2ptr_to_ptr(this))))->type)

#endif // F2__PTYPES__MEMORY__H
