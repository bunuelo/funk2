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


// memblock


// ptype

struct ptype_block_s {
  funk2_memblock_t block;
  f2ptr            cause : f2ptr__bit_num;
} __attribute__((__packed__));
typedef struct ptype_block_s ptype_block_t;

#define __pure__f2ptype__raw(this)                             (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->block.ptype)
#define __pure__f2ptype__cause(this)                           (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause)
#define __pure__f2ptype__cause__set(this, value)               (((ptype_block_t*)(from_ptr(f2ptr_to_ptr(this))))->cause = (value))


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


// scheduler_cmutex

struct ptype_scheduler_cmutex_block_s {
  ptype_block_t           ptype;
  boolean_t               locked_state; // this state is persistent between boots.
  funk2_processor_mutex_t m[1];         // this state is reinitialized at each boot.
} __attribute__((__packed__));
typedef struct ptype_scheduler_cmutex_block_s ptype_scheduler_cmutex_block_t;

ptype_scheduler_cmutex_block_t* ptype_scheduler_cmutex_block__new(int pool_index, f2ptr cause);
funk2_processor_mutex_t*       ptype_scheduler_cmutex__m(f2ptr this, f2ptr cause);

#define __pure__f2scheduler_cmutex__new(pool_index, cause)         ptype_scheduler_cmutex__new(pool_index, cause)
#define __pure__f2scheduler_cmutex__locked_state(this)             (((ptype_scheduler_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state)
#define __pure__f2scheduler_cmutex__locked_state__set(this, value) (((ptype_scheduler_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state = (value))
#define __pure__f2scheduler_cmutex__m(this)                        (((ptype_scheduler_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->m)


// cmutex

struct ptype_cmutex_block_s {
  ptype_block_t           ptype;
  boolean_t               locked_state; // this state is persistent between boots.
  funk2_processor_mutex_t m[1];         // this state is reinitialized at each boot.
} __attribute__((__packed__));
typedef struct ptype_cmutex_block_s ptype_cmutex_block_t;

ptype_cmutex_block_t*     ptype_cmutex_block__new(int pool_index, f2ptr cause);
funk2_processor_mutex_t* ptype_cmutex__m(f2ptr this, f2ptr cause);

#define __pure__f2cmutex__new(pool_index, cause)         ptype_cmutex__new(pool_index, cause)
#define __pure__f2cmutex__locked_state(this)             (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state)
#define __pure__f2cmutex__locked_state__set(this, value) (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->locked_state = (value))
#define __pure__f2cmutex__m(this)                        (((ptype_cmutex_block_t*)(from_ptr(f2ptr_to_ptr(this))))->m)


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
} __attribute__((__packed__));;
typedef struct ptype_chunk_block_s ptype_chunk_block_t;

ptype_chunk_block_t* ptype_chunk_block__new(int pool_index, f2ptr cause, uint len, byte* bytes);
u8*                  ptype_chunk__bytes(f2ptr this, f2ptr cause);

#define __pure__f2chunk__new(pool_index, cause, len, bytes)      ptype_chunk__new(pool_index, cause, len, bytes)
#define __pure__f2chunk__new_copy(pool_index, cause, init_chunk) ptype_chunk__new_copy(pool_index, cause, init_chunk)
#define __pure__f2chunk__length(this)                            (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2chunk__bytes(this)                             (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes)

#define __pure__f2chunk__bit8__elt(this, index)                          (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])
#define __pure__f2chunk__bit8__elt__set(this, index, value)              (((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index] = (u8)(value))
#define __pure__f2chunk__bit16__elt(this, index)              (*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit16__elt__set(this, index, value) ((*((u16*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u16)(value))
#define __pure__f2chunk__bit32__elt(this, index)              (*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit32__elt__set(this, index, value) ((*((u32*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u32)(value))
#define __pure__f2chunk__bit64__elt(this, index)              (*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index]))))
#define __pure__f2chunk__bit64__elt__set(this, index, value) ((*((u64*)(&(((ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(this))))->bytes[index])))) = (u64)(value))


// simple_array

struct ptype_simple_array_block_s {
  ptype_block_t ptype;
  u8            immutable : 1;
  u64           length : (f2ptr__bit_num - 2);
  f2ptr_t       slot[0];
} __attribute__((__packed__));
typedef struct ptype_simple_array_block_s ptype_simple_array_block_t;

ptype_simple_array_block_t* ptype_simple_array_block__new(int pool_index, f2ptr cause, u64 len, ptr f2ptr_ptr);

#define __pure__f2simple_array__new(pool_index, cause, len, f2ptr_ptr) ptype_simple_array__new(pool_index, cause, len, f2ptr_ptr)
#define __pure__f2simple_array__immutable(this)                        (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->immutable)
#define __pure__f2simple_array__immutable__set(this, value)            (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->immutable = (value))
#define __pure__f2simple_array__length(this)                           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2simple_array__elt(this, index)                       (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->slot[index].data)
#define __pure__f2simple_array__elt__set(this, index, value)           (((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->slot[index].data = (value))


// traced_array

struct ptype_traced_array_block_s {
  ptype_block_t ptype;
  u8            immutable;
  u64           length;
  funk2_dptr_t  dptr_data[0];
} __attribute__((__packed__));
typedef struct ptype_traced_array_block_s ptype_traced_array_block_t;

ptype_traced_array_block_t* ptype_traced_array_block__new(int pool_index, f2ptr cause, uint len, ptr dptr_ptr);

#define __pure__f2traced_array__new(pool_index, cause, len, dptr_ptr)              ptype_traced_array__new(pool_index, cause, len, dptr_ptr)
#define __pure__f2traced_array__new_from_f2ptrs(pool_index, cause, len, f2ptr_ptr) ptype_traced_array__new_from_f2ptrs(pool_index, cause, len, f2ptr_ptr)
#define __pure__f2traced_array__immutable(this)                                    (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->immutable)
#define __pure__f2traced_array__immutable__set(this, value)                        (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->immutable = (value))
#define __pure__f2traced_array__length(this)                                       (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->length)
#define __pure__f2traced_array__elt_dptr(this, index)                              (((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(this))))->dptr_data[index])
#define __pure__f2traced_array__elt(this, index)                                   funk2_dptr__p(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__set(this, index, value)                       funk2_dptr__p__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__tracing_on(this, index)                       funk2_dptr__tracing_on(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__tracing_on__set(this, index, value)           funk2_dptr__tracing_on__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__trace(this, index)                            funk2_dptr__trace(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__trace__set(this, index, value)                funk2_dptr__trace__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__imagination_frame(this, index)                funk2_dptr__imagination_frame(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__imagination_frame__set(this, index, value)    funk2_dptr__imagination_frame__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__mutate_funks(this, index)                     funk2_dptr__mutate_funks(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__mutate_funks__set(this, index, value)         funk2_dptr__mutate_funks__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)
#define __pure__f2traced_array__elt__read_funks(this, index)                       funk2_dptr__read_funks(&(__pure__f2traced_array__elt_dptr(this, index)))
#define __pure__f2traced_array__elt__read_funks__set(this, index, value)           funk2_dptr__read_funks__set(&(__pure__f2traced_array__elt_dptr(this, index)), value)


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

#endif // F2__PTYPES__MEMORY__H

