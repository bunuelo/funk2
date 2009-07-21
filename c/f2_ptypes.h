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

#ifndef F2__PTYPES__H
#define F2__PTYPES__H

#include "f2_print.h"
#include "f2_memory.h"
#include "f2_processor_thread.h"
#include "f2_bytecodes.h"
#include "f2_packet_memaccess.h"

#define SYMBOL_HASH__INITIAL_ARRAY_LENGTH 1024 // must be power of 2
#define PRIME_NUMBER__16_BIT 65521
#define PRIME_NUMBER__32_BIT 3267000013u

// length must be greater than zero.
//#define chararray__hash_value(length, str) ((((uint)((str)[0])) + (((uint)((str)[(length)>>3]))<<8) + (((uint)((str)[(length)>>2]))<<16) + (((uint)((str)[(length)>>1]))<<24)) * PRIME_NUMBER__16_BIT)

#define chararray__hash_value(length, str)    \
  ((*((uint*)(((u8*)(str))+(0))))           * \
   (*((uint*)(((u8*)(str))+(((uint)(length))>>4)))) * \
   (*((uint*)(((u8*)(str))+(((uint)(length))>>3)))) * \
   (*((uint*)(((u8*)(str))+(((uint)(length))>>2)))) * \
   (*((uint*)(((u8*)(str))+(((uint)(length))>>1)))) * \
   ((uint)PRIME_NUMBER__32_BIT))

typedef f2ptr (*cfunkptr_t)(f2ptr cause, f2ptr thread, f2ptr env, f2ptr args);

extern u8 __ptype__str[][128];

// control lockout access (for garbage_collect)

void ptype_access__lockout_access(int pool_index, int max_access);
int  ptype_access__try_lockout_access(int pool_index, int max_access);
void ptype_access__unlockout_access(int pool_index);

// used by global initialization for creation (and other) causes

f2ptr initial_cause();

// cause helper functions

boolean_t raw__cause__is_traced(f2ptr cause, f2ptr this);
boolean_t raw__cause__is_imaginary(f2ptr cause, f2ptr this);

// this.system

f2ptr pfunk2__system__environment(f2ptr cause);

// memblock

u64 pfunk2__memblock__creation_nanoseconds_since_1970(f2ptr this, f2ptr cause);

// ptype

ptype_t pfunk2__f2ptype__raw(f2ptr this, f2ptr cause);
f2ptr   pfunk2__f2ptype__cause(f2ptr this, f2ptr cause);
f2ptr   pfunk2__f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value);


// integer

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i);
s64   pfunk2__f2integer__i(f2ptr this, f2ptr cause);

f2ptr f2integer__primobject_type__new(f2ptr cause);

boolean_t raw__integer__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__integer__is_type(f2ptr cause, f2ptr exp);

// double

f2ptr  pfunk2__f2double__new(f2ptr cause, double d);
double pfunk2__f2double__d(f2ptr this, f2ptr cause);

f2ptr f2double__primobject_type__new(f2ptr cause);

boolean_t raw__double__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__double__is_type(f2ptr cause, f2ptr exp);

// float

f2ptr pfunk2__f2float__new(f2ptr cause, float f);
float pfunk2__f2float__f(f2ptr this, f2ptr cause);

f2ptr f2float__primobject_type__new(f2ptr cause);

boolean_t raw__float__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__float__is_type(f2ptr cause, f2ptr exp);

// pointer

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p);
ptr   pfunk2__f2pointer__p(f2ptr this, f2ptr cause);

f2ptr f2pointer__primobject_type__new(f2ptr cause);

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr exp);

// gfunkptr

f2ptr          pfunk2__f2gfunkptr__new(f2ptr cause, computer_id_t computer_id, pool_index_t pool_index, pool_address_t pool_address);
f2ptr          pfunk2__f2gfunkptr__new_from_f2ptr(f2ptr cause, f2ptr f2p);
f2ptr          pfunk2__f2gfunkptr__gfunkptr(f2ptr this, f2ptr cause);
computer_id_t  pfunk2__f2gfunkptr__computer_id(f2ptr this, f2ptr cause);
pool_index_t   pfunk2__f2gfunkptr__pool_index(f2ptr this, f2ptr cause);
pool_address_t pfunk2__f2gfunkptr__pool_address(f2ptr this, f2ptr cause);

f2ptr f2gfunkptr__primobject_type__new(f2ptr cause);

boolean_t raw__gfunkptr__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__gfunkptr__is_type(f2ptr cause, f2ptr exp);

// mutex

f2ptr            pfunk2__f2mutex__new(f2ptr cause);
void             pfunk2__f2mutex__lock(f2ptr this, f2ptr cause);
void             pfunk2__f2mutex__unlock(f2ptr this, f2ptr cause);
int              pfunk2__f2mutex__trylock(f2ptr this, f2ptr cause);

f2ptr f2mutex__primobject_type__new(f2ptr cause);

boolean_t raw__mutex__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__mutex__is_type(f2ptr cause, f2ptr exp);

// char

f2ptr pfunk2__f2char__new(f2ptr cause, u64 ch);
u64   pfunk2__f2char__ch(f2ptr this, f2ptr cause);

f2ptr f2char__primobject_type__new(f2ptr cause);

boolean_t raw__char__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__char__is_type(f2ptr cause, f2ptr exp);

// string

f2ptr pfunk2__f2string__new(f2ptr cause, u64 length, u8* init);
u64   pfunk2__f2string__length(f2ptr this, f2ptr cause);
u8    pfunk2__f2string__elt(f2ptr this, int index, f2ptr cause);
void  pfunk2__f2string__str_copy(f2ptr this, f2ptr cause, u8* str);
int   pfunk2__f2string__hash_value(f2ptr this, f2ptr cause);

f2ptr f2string__primobject_type__new(f2ptr cause);

boolean_t raw__string__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__string__is_type(f2ptr cause, f2ptr exp);

// symbol

void gc_touch_all_symbols();


f2ptr pfunk2__f2symbol__new(f2ptr cause, u64 length, u8* init);
u64   pfunk2__f2symbol__length(f2ptr this, f2ptr cause);
u8    pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause);
u64   pfunk2__f2symbol__hash_value(f2ptr this, f2ptr cause);
void  pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, u8* str);

f2ptr f2symbol__primobject_type__new(f2ptr cause);

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x);
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x);
f2ptr f2__symbol__length(f2ptr cause, f2ptr x);
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__symbol__hash_value(f2ptr cause, f2ptr x);
f2ptr f2__symbol__new(f2ptr cause, f2ptr str);
boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__symbol__eq(f2ptr cause, f2ptr x, f2ptr y);

// chunk

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes);
f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk);
u64   pfunk2__f2chunk__length(f2ptr this, f2ptr cause);

u8    pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value);
u16   pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value);
u32   pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value);
u64   pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value);
f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr thread, f2ptr env, f2ptr args);
int   pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr thread);
f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags);
f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags);

f2ptr f2chunk__primobject_type__new(f2ptr cause);

boolean_t raw__chunk__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr exp);

// simple_array

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr);
f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array);
u8    pfunk2__f2simple_array__immutable(f2ptr this, f2ptr cause);
void  pfunk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value);
u64   pfunk2__f2simple_array__length(f2ptr this, f2ptr cause);
f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);

f2ptr f2simple_array__primobject_type__new(f2ptr cause);

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__new(f2ptr cause, f2ptr length);
f2ptr f2__simple_array__length(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);

// traced_array

f2ptr pfunk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_ptr);
f2ptr pfunk2__f2traced_array__new_from_f2ptrs(f2ptr cause, u64 length, f2ptr* f2ptr_ptr);
f2ptr pfunk2__f2traced_array__new_copy(f2ptr cause, u64 length, f2ptr init_array);
u8    pfunk2__f2traced_array__immutable(f2ptr this, f2ptr cause);
void  pfunk2__f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value);
u64   pfunk2__f2traced_array__length(f2ptr this, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__trace_depth(f2ptr this, u64 index, f2ptr cause, int trace_depth);
f2ptr pfunk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth);
f2ptr pfunk2__f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);

f2ptr pfunk2__f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);
f2ptr pfunk2__f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);
f2ptr pfunk2__f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);

f2ptr f2traced_array__primobject_type__new(f2ptr cause);

boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__new(f2ptr cause, f2ptr length);
f2ptr f2__traced_array__length(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);

// larva

typedef enum larva_type_e {
  larva_type__array_index_out_of_bounds,
  larva_type__invalid_type,
} larva_type_t;

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 type);
u32   pfunk2__f2larva__type(f2ptr this, f2ptr cause);

f2ptr f2larva__primobject_type__new(f2ptr cause);

boolean_t raw__larva__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__larva__is_type(f2ptr cause, f2ptr exp);




// get, set, and execute slot funk accessors

f2ptr f2__integer__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__integer__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__integer__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__double__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__double__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__float__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__float__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__float__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__pointer__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__pointer__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__pointer__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__gfunkptr__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__gfunkptr__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__gfunkptr__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__mutex__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__mutex__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__mutex__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__char__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__char__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__char__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__string__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__string__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__string__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__symbol__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__symbol__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__symbol__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__chunk__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__chunk__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__chunk__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__simple_array__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__simple_array__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__simple_array__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__traced_array__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__traced_array__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__traced_array__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2__larva__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__larva__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr f2__larva__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);


// **

void f2__ptypes__initialize__object_slots();
void f2__ptypes__initialize();

#endif // F2__PTYPES__H

#ifndef F2__PTYPES__OBJECT_TYPES
#define F2__PTYPES__OBJECT_TYPES

// integer

typedef struct funk2_object_type__integer__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr i__symbol;
  f2ptr i__funk;
} funk2_object_type__integer__slot_t;

// double

typedef struct funk2_object_type__double__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr d__symbol;
  f2ptr d__funk;
} funk2_object_type__double__slot_t;

// float

typedef struct funk2_object_type__float__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr f__symbol;
  f2ptr f__funk;
} funk2_object_type__float__slot_t;

// pointer

typedef struct funk2_object_type__pointer__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr p__symbol;
  f2ptr p__funk;
} funk2_object_type__pointer__slot_t;

// gfunkptr

typedef struct funk2_object_type__gfunkptr__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_from_f2ptr__symbol;
  f2ptr new_from_f2ptr__funk;
  f2ptr gfunkptr__symbol;
  f2ptr gfunkptr__funk;
  f2ptr computer_id__symbol;
  f2ptr computer_id__funk;
  f2ptr pool_index__symbol;
  f2ptr pool_index__funk;
  f2ptr pool_address__symbol;
  f2ptr pool_address__funk;
} funk2_object_type__gfunkptr__slot_t;

// mutex

typedef struct funk2_object_type__mutex__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr lock__symbol;
  f2ptr lock__funk;
  f2ptr unlock__symbol;
  f2ptr unlock__funk;
  f2ptr trylock__symbol;
  f2ptr trylock__funk;
} funk2_object_type__mutex__slot_t;

// char

typedef struct funk2_object_type__char__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr ch__symbol;
  f2ptr ch__funk;
} funk2_object_type__char__slot_t;

// string

typedef struct funk2_object_type__string__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr hash_value__symbol;
  f2ptr hash_value__funk;
} funk2_object_type__string__slot_t;

// symbol

typedef struct funk2_object_type__symbol__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr hash_value__symbol;
  f2ptr hash_value__funk;
} funk2_object_type__symbol__slot_t;

// chunk

typedef struct funk2_object_type__chunk__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr bit8__elt__symbol;
  f2ptr bit8__elt__funk;
  f2ptr bit8__elt__set__symbol;
  f2ptr bit8__elt__set__funk;
  f2ptr bit16__elt__symbol;
  f2ptr bit16__elt__funk;
  f2ptr bit16__elt__set__symbol;
  f2ptr bit16__elt__set__funk;
  f2ptr bit32__elt__symbol;
  f2ptr bit32__elt__funk;
  f2ptr bit32__elt__set__symbol;
  f2ptr bit32__elt__set__funk;
  f2ptr bit64__elt__symbol;
  f2ptr bit64__elt__funk;
  f2ptr bit64__elt__set__symbol;
  f2ptr bit64__elt__set__funk;
  f2ptr cfunk_jump__symbol;
  f2ptr cfunk_jump__funk;
  f2ptr bytecode_jump__symbol;
  f2ptr bytecode_jump__funk;
} funk2_object_type__chunk__slot_t;

// simple_array

typedef struct funk2_object_type__simple_array__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr elt__set__symbol;
  f2ptr elt__set__funk;
} funk2_object_type__simple_array__slot_t;

// traced_array

typedef struct funk2_object_type__traced_array__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr elt__set__symbol;
  f2ptr elt__set__funk;
  f2ptr elt__tracing_on__symbol;
  f2ptr elt__tracing_on__funk;
  f2ptr elt__tracing_on__set__symbol;
  f2ptr elt__tracing_on__set__funk;
  f2ptr elt__trace__symbol;
  f2ptr elt__trace__funk;
  f2ptr elt__trace__set__symbol;
  f2ptr elt__trace__set__funk;
  f2ptr elt__imagination_frame__symbol;
  f2ptr elt__imagination_frame__funk;
  f2ptr elt__imagination_frame__set__symbol;
  f2ptr elt__imagination_frame__set__funk;
} funk2_object_type__traced_array__slot_t;

// larva

typedef struct funk2_object_type__larva__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
} funk2_object_type__larva__slot_t;



typedef struct funk2_ptype_object_types_s {
  funk2_object_type__integer__slot_t      ptype_integer;
  funk2_object_type__double__slot_t       ptype_double;
  funk2_object_type__float__slot_t        ptype_float;
  funk2_object_type__pointer__slot_t      ptype_pointer;
  funk2_object_type__gfunkptr__slot_t     ptype_gfunkptr;
  funk2_object_type__mutex__slot_t        ptype_mutex;
  funk2_object_type__char__slot_t         ptype_char;
  funk2_object_type__string__slot_t       ptype_string;
  funk2_object_type__symbol__slot_t       ptype_symbol;
  funk2_object_type__chunk__slot_t        ptype_chunk;
  funk2_object_type__simple_array__slot_t ptype_simple_array;
  funk2_object_type__traced_array__slot_t ptype_traced_array;
  funk2_object_type__larva__slot_t        ptype_larva;
} funk2_ptype_object_types_t;

#endif // F2__PTYPES__OBJECT_TYPES
