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

#ifndef F2__PTYPES__H
#define F2__PTYPES__H

#include "f2_dptr.h"
#include "f2_print.h"
#include "f2_memory.h"
#include "f2_processor_thread.h"
#include "f2_bytecodes.h"

#define SYMBOL_HASH__INITIAL_ARRAY_LENGTH 1024 // must be power of 2
#define PRIME_NUMBER__16_BIT 65521
#define PRIME_NUMBER__32_BIT 3267000013u

#define chararray__hash_value(length, str)                \
  (((u64)(*((u8*)(((u8*)(str))+(0)))))                  * \
   ((u64)(*((u8*)(((u8*)(str))+(((u64)(length))>>4))))) * \
   ((u64)(*((u8*)(((u8*)(str))+(((u64)(length))>>3))))) * \
   ((u64)(*((u8*)(((u8*)(str))+(((u64)(length))>>2))))) * \
   ((u64)(*((u8*)(((u8*)(str))+(((u64)(length))>>1))))) * \
   ((u64)PRIME_NUMBER__32_BIT))

#define character_array__hash_value(length, str) \
  (((u64)(*((funk2_character_t*)(((funk2_character_t*)(str))+(0)))))                  * \
   ((u64)(*((funk2_character_t*)(((funk2_character_t*)(str))+(((u64)(length))>>4))))) * \
   ((u64)(*((funk2_character_t*)(((funk2_character_t*)(str))+(((u64)(length))>>3))))) * \
   ((u64)(*((funk2_character_t*)(((funk2_character_t*)(str))+(((u64)(length))>>2))))) * \
   ((u64)(*((funk2_character_t*)(((funk2_character_t*)(str))+(((u64)(length))>>1))))) * \
   ((u64)PRIME_NUMBER__32_BIT))

typedef f2ptr (*cfunkptr_t)(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args);

void wait_politely();

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

// ptype

boolean_t    raw__ptype__is_type(f2ptr cause, f2ptr thing);
f2ptr         f2__ptype__is_type(f2ptr cause, f2ptr thing);
f2ptr         f2__ptype__type(   f2ptr cause, f2ptr this);

ptype_t pfunk2__f2ptype__raw                (f2ptr this, f2ptr cause);
f2ptr   pfunk2__f2ptype__cause              (f2ptr this, f2ptr cause);
f2ptr   pfunk2__f2ptype__cause__set         (f2ptr this, f2ptr cause, f2ptr value);
f2ptr   pfunk2__f2ptype__creation_fiber     (f2ptr this, f2ptr cause);
f2ptr   pfunk2__f2ptype__creation_fiber__set(f2ptr this, f2ptr cause, f2ptr value);

// integer

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i);
s64   pfunk2__f2integer__i(f2ptr this, f2ptr cause);

boolean_t raw__integer__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__integer__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__integer__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__integer__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__integer__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__integer__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__integer__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__integer__equals(f2ptr cause, f2ptr this, f2ptr that);

double raw__integer__as__double(f2ptr cause, f2ptr this);
f2ptr   f2__integer__as__double(f2ptr cause, f2ptr this);

f2ptr  f2__integer__multiplied_by(          f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__integer__divided_by(             f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__integer__plus(                   f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__integer__minus(                  f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__integer__is_greater_than(        f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__integer__is_less_than(           f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__integer__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__integer__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__integer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);

// double

f2ptr  pfunk2__f2double__new(f2ptr cause, double d);
double pfunk2__f2double__d(f2ptr this, f2ptr cause);

boolean_t raw__double__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__double__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__double__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__double__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__double__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__double__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__double__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__double__equals(f2ptr cause, f2ptr this, f2ptr that);

double raw__double__as__double(f2ptr cause, f2ptr this);
f2ptr   f2__double__as__double(f2ptr cause, f2ptr this);

f2ptr f2__double__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);

f2ptr  f2__double__multiplied_by(          f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__double__divided_by(             f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__double__plus(                   f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__double__minus(                  f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__double__is_greater_than(        f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__double__is_less_than(           f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__double__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__double__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__double__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);

// float

f2ptr pfunk2__f2float__new(f2ptr cause, float f);
float pfunk2__f2float__f(f2ptr this, f2ptr cause);

boolean_t raw__float__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__float__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__float__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__float__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__float__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__float__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__float__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__float__equals(f2ptr cause, f2ptr this, f2ptr that);

double raw__float__as__double(f2ptr cause, f2ptr this);
f2ptr   f2__float__as__double(f2ptr cause, f2ptr this);

f2ptr f2__float__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);

f2ptr  f2__float__multiplied_by(          f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__float__divided_by(             f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__float__plus(                   f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__float__minus(                  f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__float__is_greater_than(        f2ptr cause, f2ptr this, f2ptr number);
f2ptr  f2__float__is_less_than(           f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__float__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__float__square_root(            f2ptr cause, f2ptr this);
f2ptr  f2__float__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);

// pointer

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p);
ptr   pfunk2__f2pointer__p(f2ptr this, f2ptr cause);

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr exp);
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__pointer__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__pointer__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__pointer__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__pointer__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__pointer__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__pointer__equals(f2ptr cause, f2ptr this, f2ptr that);

f2ptr f2__pointer__plus(                   f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__pointer__minus(                  f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__pointer__is_greater_than(        f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__pointer__is_less_than(           f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__pointer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);

// scheduler_cmutex

f2ptr            pfunk2__f2scheduler_cmutex__new(f2ptr cause);
boolean_t        pfunk2__f2scheduler_cmutex__is_locked(f2ptr this, f2ptr cause);
void             pfunk2__f2scheduler_cmutex__lock(f2ptr this, f2ptr cause);
void             pfunk2__f2scheduler_cmutex__unlock(f2ptr this, f2ptr cause);
int              pfunk2__f2scheduler_cmutex__trylock(f2ptr this, f2ptr cause);

f2ptr      f2__scheduler_cmutex__new(f2ptr cause);

boolean_t raw__scheduler_cmutex__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__scheduler_cmutex__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);


// cmutex

f2ptr     pfunk2__f2cmutex__new(f2ptr cause);
boolean_t pfunk2__f2cmutex__is_locked(f2ptr this, f2ptr cause);
void      pfunk2__f2cmutex__lock(f2ptr this, f2ptr cause);
void      pfunk2__f2cmutex__unlock(f2ptr this, f2ptr cause);
int       pfunk2__f2cmutex__trylock(f2ptr this, f2ptr cause);

f2ptr      f2__cmutex__new(f2ptr cause);
boolean_t raw__cmutex__is_locked(f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__is_locked(f2ptr cause, f2ptr this);
void      raw__cmutex__lock(f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__lock(f2ptr cause, f2ptr this);
void      raw__cmutex__unlock(f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__unlock(f2ptr cause, f2ptr this);
boolean_t raw__cmutex__trylock(f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__trylock(f2ptr cause, f2ptr this);

boolean_t raw__cmutex__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__cmutex__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__cmutex__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__cmutex__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);


// scheduler_creadwritelock

f2ptr     pfunk2__f2scheduler_creadwritelock__new           (f2ptr cause);
boolean_t pfunk2__f2scheduler_creadwritelock__is_writelocked(f2ptr this, f2ptr cause);
boolean_t pfunk2__f2scheduler_creadwritelock__is_readlocked (f2ptr this, f2ptr cause);
void      pfunk2__f2scheduler_creadwritelock__writelock     (f2ptr this, f2ptr cause);
void      pfunk2__f2scheduler_creadwritelock__readlock      (f2ptr this, f2ptr cause);
void      pfunk2__f2scheduler_creadwritelock__unlock        (f2ptr this, f2ptr cause);
int       pfunk2__f2scheduler_creadwritelock__trywritelock  (f2ptr this, f2ptr cause);
int       pfunk2__f2scheduler_creadwritelock__tryreadlock   (f2ptr this, f2ptr cause);

f2ptr      f2__scheduler_creadwritelock__new           (f2ptr cause);
boolean_t raw__scheduler_creadwritelock__is_writelocked(f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__is_writelocked(f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__writelock     (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__writelock     (f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__readlock      (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__readlock      (f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__unlock        (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__unlock        (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__trywritelock  (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__trywritelock  (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__tryreadlock   (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__tryreadlock   (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__is_type       (f2ptr cause, f2ptr exp);
f2ptr      f2__scheduler_creadwritelock__is_type       (f2ptr cause, f2ptr exp);
boolean_t raw__scheduler_creadwritelock__eq            (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_creadwritelock__eq            (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__scheduler_creadwritelock__eq_hash_value (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__eq_hash_value (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__equals        (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_creadwritelock__equals        (f2ptr cause, f2ptr this, f2ptr that);


// creadwritelock

f2ptr     pfunk2__f2creadwritelock__new           (f2ptr cause);
boolean_t pfunk2__f2creadwritelock__is_writelocked(f2ptr this, f2ptr cause);
boolean_t pfunk2__f2creadwritelock__is_readlocked (f2ptr this, f2ptr cause);
void      pfunk2__f2creadwritelock__writelock     (f2ptr this, f2ptr cause);
void      pfunk2__f2creadwritelock__readlock      (f2ptr this, f2ptr cause);
void      pfunk2__f2creadwritelock__unlock        (f2ptr this, f2ptr cause);
int       pfunk2__f2creadwritelock__trywritelock  (f2ptr this, f2ptr cause);
int       pfunk2__f2creadwritelock__tryreadlock   (f2ptr this, f2ptr cause);

f2ptr      f2__creadwritelock__new           (f2ptr cause);
boolean_t raw__creadwritelock__is_writelocked(f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__is_writelocked(f2ptr cause, f2ptr this);
void      raw__creadwritelock__writelock     (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__writelock     (f2ptr cause, f2ptr this);
void      raw__creadwritelock__readlock      (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__readlock      (f2ptr cause, f2ptr this);
void      raw__creadwritelock__unlock        (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__unlock        (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__trywritelock  (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__trywritelock  (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__tryreadlock   (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__tryreadlock   (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__is_type       (f2ptr cause, f2ptr exp);
f2ptr      f2__creadwritelock__is_type       (f2ptr cause, f2ptr exp);
boolean_t raw__creadwritelock__eq            (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__creadwritelock__eq            (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__creadwritelock__eq_hash_value (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__eq_hash_value (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__equals        (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__creadwritelock__equals        (f2ptr cause, f2ptr this, f2ptr that);


// char

f2ptr             pfunk2__f2char__new(f2ptr cause, funk2_character_t ch);
funk2_character_t pfunk2__f2char__ch(f2ptr this, f2ptr cause);

boolean_t         raw__char__is_type      (f2ptr cause, f2ptr exp);
f2ptr              f2__char__is_type      (f2ptr cause, f2ptr exp);
funk2_character_t raw__char__ch           (f2ptr cause, f2ptr this);
f2ptr              f2__char__ch           (f2ptr cause, f2ptr this);
boolean_t         raw__char__eq           (f2ptr cause, f2ptr this, f2ptr that);
f2ptr              f2__char__eq           (f2ptr cause, f2ptr this, f2ptr that);
u64               raw__char__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr              f2__char__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t         raw__char__equals       (f2ptr cause, f2ptr this, f2ptr that);
f2ptr              f2__char__equals       (f2ptr cause, f2ptr this, f2ptr that);
f2ptr             raw__char__string       (f2ptr cause, f2ptr this);
f2ptr              f2__char__string       (f2ptr cause, f2ptr this);

// string

f2ptr             pfunk2__f2string__new          (f2ptr cause, u64 length, funk2_character_t* init);
u64               pfunk2__f2string__length       (f2ptr this, f2ptr cause);
funk2_character_t pfunk2__f2string__elt          (f2ptr this, int index, f2ptr cause);
void              pfunk2__f2string__str_copy     (f2ptr this, f2ptr cause, funk2_character_t* str);
u64               pfunk2__f2string__eq_hash_value(f2ptr this, f2ptr cause);

boolean_t         raw__string__is_type (f2ptr cause, f2ptr exp);
f2ptr              f2__string__is_type (f2ptr cause, f2ptr exp);
void              raw__string__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str);
u64               raw__string__length  (f2ptr cause, f2ptr this);
f2ptr              f2__string__length  (f2ptr cause, f2ptr this);
funk2_character_t raw__string__elt     (f2ptr cause, f2ptr this, s64   index);
f2ptr              f2__string__elt     (f2ptr cause, f2ptr this, f2ptr index);

boolean_t raw__string__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__string__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__string__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__string__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__string__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__string__equals(f2ptr cause, f2ptr this, f2ptr that);

u64  raw__string__utf8_length  (f2ptr cause, f2ptr this);
void raw__string__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str);

u64  raw__utf8_string__length  (char* utf8_string);
void raw__utf8_string__str_copy(char* utf8_string, funk2_character_t* str);

f2ptr raw__string__new_from_utf8(f2ptr cause, char* utf8_string);


// symbol

f2ptr             pfunk2__f2symbol__new(f2ptr cause, u64 length, funk2_character_t* init);
u64               pfunk2__f2symbol__length(f2ptr this, f2ptr cause);
funk2_character_t pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause);
u64               pfunk2__f2symbol__eq_hash_value(f2ptr this, f2ptr cause);
void              pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str);

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x);
f2ptr      f2__symbol__is_type(f2ptr cause, f2ptr x);
u64       raw__symbol__length(f2ptr cause, f2ptr this);
f2ptr      f2__symbol__length(f2ptr cause, f2ptr x);
f2ptr      f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y);
u64       raw__symbol__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__symbol__eq_hash_value(f2ptr cause, f2ptr this);
void      raw__symbol__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str);
f2ptr      f2__symbol__new(f2ptr cause, f2ptr str);
boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__symbol__eq(f2ptr cause, f2ptr x, f2ptr y);

boolean_t raw__symbol__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__symbol__equals(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__symbol__utf8_length  (f2ptr cause, f2ptr this);
void  raw__symbol__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str);
f2ptr raw__symbol__new_from_utf8(f2ptr cause, char* utf8_string);

f2ptr raw__key_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr raw__type_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

// chunk

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes);
f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk);
u64   pfunk2__f2chunk__length(f2ptr this, f2ptr cause);
void  pfunk2__f2chunk__str_copy(f2ptr this, f2ptr cause, u8* str);
u64   pfunk2__f2chunk__eq_hash_value(f2ptr this, f2ptr cause);
u64   pfunk2__f2chunk__equals_hash_value(f2ptr this, f2ptr cause);

u8    pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value);
u16   pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value);
u32   pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value);
u64   pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause);
void  pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value);
f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args);
int   pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr fiber);
f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags);
f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags);

f2ptr     raw__chunk__new              (f2ptr cause, u64 length);
f2ptr      f2__chunk__new              (f2ptr cause, f2ptr length);
boolean_t raw__chunk__is_type          (f2ptr cause, f2ptr exp);
f2ptr      f2__chunk__is_type          (f2ptr cause, f2ptr exp);
void      raw__chunk__str_copy         (f2ptr cause, f2ptr this, u8* str);
u64       raw__chunk__length           (f2ptr cause, f2ptr this);
f2ptr      f2__chunk__length           (f2ptr cause, f2ptr this);
boolean_t raw__chunk__eq               (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__chunk__eq               (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__chunk__eq_hash_value    (f2ptr cause, f2ptr this);
f2ptr      f2__chunk__eq_hash_value    (f2ptr cause, f2ptr this);
u64       raw__chunk__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__chunk__equals_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__chunk__equals           (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__chunk__equals           (f2ptr cause, f2ptr this, f2ptr that);

u8    raw__chunk__bit8__elt(      f2ptr cause, f2ptr this, s64   index);
f2ptr  f2__chunk__bit8__elt(      f2ptr cause, f2ptr this, f2ptr index);
void  raw__chunk__bit8__elt__set( f2ptr cause, f2ptr this, s64   index, u64   value);
f2ptr  f2__chunk__bit8__elt__set( f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u16   raw__chunk__bit16__elt(     f2ptr cause, f2ptr this, s64   index);
f2ptr  f2__chunk__bit16__elt(     f2ptr cause, f2ptr this, f2ptr index);
void  raw__chunk__bit16__elt__set(f2ptr cause, f2ptr this, s64   index, u64   value);
f2ptr  f2__chunk__bit16__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u32   raw__chunk__bit32__elt(     f2ptr cause, f2ptr this, s64   index);
f2ptr  f2__chunk__bit32__elt(     f2ptr cause, f2ptr this, f2ptr index);
void  raw__chunk__bit32__elt__set(f2ptr cause, f2ptr this, s64   index, u64   value);
f2ptr  f2__chunk__bit32__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u64   raw__chunk__bit64__elt(     f2ptr cause, f2ptr this, s64   index);
f2ptr  f2__chunk__bit64__elt(     f2ptr cause, f2ptr this, f2ptr index);
void  raw__chunk__bit64__elt__set(f2ptr cause, f2ptr this, s64   index, u64   value);
f2ptr  f2__chunk__bit64__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);

// simple_array

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr);
f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array);
u8    pfunk2__f2simple_array__immutable(f2ptr this, f2ptr cause);
void  pfunk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value);
u64   pfunk2__f2simple_array__length(f2ptr this, f2ptr cause);
f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr      f2__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr      f2__simple_array__new(f2ptr cause, f2ptr length);
f2ptr      f2__simple_array__length(f2ptr cause, f2ptr x);
u64       raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__simple_array__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr      f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);

boolean_t raw__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that);

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
f2ptr pfunk2__f2traced_array__elt__mutate_funks(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__mutate_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);
f2ptr pfunk2__f2traced_array__elt__read_funks(f2ptr this, u64 index, f2ptr cause);
f2ptr pfunk2__f2traced_array__elt__read_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value);

boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__new(f2ptr cause, f2ptr length);
f2ptr f2__traced_array__length(f2ptr cause, f2ptr x);
u64  raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__traced_array__elt(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__mutate_funks(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__mutate_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__read_funks(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__read_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);

boolean_t raw__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that);

// larva

typedef enum larva_type_e {
  larva_type__array_index_out_of_bounds,
  larva_type__invalid_type,
} larva_type_t;

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 larva_type, f2ptr bug);
u32   pfunk2__f2larva__larva_type(f2ptr this, f2ptr cause);
f2ptr pfunk2__f2larva__bug(f2ptr this, f2ptr cause);

u32   raw__larva__larva_type(f2ptr cause, f2ptr this);
f2ptr  f2__larva__larva_type(f2ptr cause, f2ptr this);

f2ptr raw__larva__bug(f2ptr cause, f2ptr this);
f2ptr  f2__larva__bug(f2ptr cause, f2ptr this);

boolean_t raw__larva__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__larva__is_type(f2ptr cause, f2ptr exp);

boolean_t raw__larva__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__larva__eq(f2ptr cause, f2ptr this, f2ptr that);

u64   raw__larva__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__larva__eq_hash_value(f2ptr cause, f2ptr this);

boolean_t raw__larva__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__larva__equals(f2ptr cause, f2ptr this, f2ptr that);


f2ptr raw__gensym(f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string);
f2ptr  f2__gensym(f2ptr cause, f2ptr initial_string);

f2ptr raw__gensym__new_from_utf8(f2ptr cause, char* initial_utf8_string);

#define gensym(cause, str) raw__gensym__new_from_utf8(cause, str)

// **

void f2__ptypes__initialize__object_slots();
void f2__ptypes__initialize();
void f2__ptypes__destroy();

#endif // F2__PTYPES__H

#ifndef F2__PTYPES__OBJECT_TYPES
#define F2__PTYPES__OBJECT_TYPES

typedef struct funk2_symbol_hash_node_s funk2_symbol_hash_node_t;
typedef struct funk2_symbol_hash_s      funk2_symbol_hash_t;
typedef struct funk2_ptypes_s           funk2_ptypes_t;

// symbol_hash_node

struct funk2_symbol_hash_node_s {
  f2ptr                     symbol;
  funk2_symbol_hash_node_t* next;
};

// symbol_hash

struct funk2_symbol_hash_s {
  funk2_processor_mutex_t    cmutex;
  funk2_symbol_hash_node_t** array;
  u64                        eq_hash_value_bit_mask;
  int                        total_symbol_num;
  int                        array_length;
};

void  funk2_symbol_hash__init                                  (funk2_symbol_hash_t* this);
void  funk2_symbol_hash__destroy                               (funk2_symbol_hash_t* this);
void  funk2_symbol_hash__reinit                                (funk2_symbol_hash_t* this);
void  funk2_symbol_hash__add_symbol                            (funk2_symbol_hash_t* this, f2ptr symbol_f2ptr);
f2ptr funk2_symbol_hash__lookup_symbol__thread_unsafe          (funk2_symbol_hash_t* this, u64 length, funk2_character_t* str);
f2ptr funk2_symbol_hash__lookup_symbol                         (funk2_symbol_hash_t* this, u64 length, funk2_character_t* str);
f2ptr funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str);
f2ptr funk2_symbol_hash__lookup_or_create_symbol               (funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str);
void  funk2_symbol_hash__touch_all_symbols                     (funk2_symbol_hash_t* this, funk2_garbage_collector_t* garbage_collector);
f2ptr funk2_symbol_hash__generate_new_random_symbol            (funk2_symbol_hash_t* this, int pool_index, f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string);

// ptypes

struct funk2_ptypes_s {
  boolean_t           read_write_reflective_tracing_enabled;
  funk2_symbol_hash_t symbol_hash;
};

void funk2_ptypes__init(funk2_ptypes_t* this);
void funk2_ptypes__destroy(funk2_ptypes_t* this);




#endif // F2__PTYPES__OBJECT_TYPES
