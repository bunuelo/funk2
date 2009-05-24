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

#include "f2_gfunktypes.h"

// ptype

u8 gf2__ptype__raw(gfunkptr_t* this) {
  if (gfunkptr__is_local(this)) {
    return ptype__raw(local_gfunkptr__to_f2ptr(this));
  } else {
    error(nil, "f2_funktypes error: not implemented yet.");
  }
}

void gf2__ptype__cause(gfunkptr_t** result, gfunkptr_t* this) {
  if (gfunkptr__is_local(this)) {
    f2ptr result_f2ptr = ptype__cause(local_gfunkptr__to_f2ptr(this));
    *result = &(__pure__ptype__gfunkptr(result_f2ptr));
  } else {
    error(nil, "f2_funktypes error: not implemented yet.");
  }
}

void gf2__ptype__cause__set(gfunkptr_t* this, gfunkptr_t* value) {
  if (gfunkptr__is_local(this) && gfunkptr__is_local(value)) {
  } else {
    error(nil, "f2_funktypes error: not implemented yet.");
  }
}

// integer

void gf2__f2integer__new(gfunkptr_t** result, gfunkptr_t* cause, int i) {
  if (gfunkptr__is_local(cause)) {
  } else {
    error(nil, "f2_funktypes error: not implemented yet.");
  }
}

int  gf2__integer__i(gfunkptr_t* this) {
}

// double

void   gf2__double__new(gfunkptr_t* result, gfunkptr_t* cause, double d) {
}

double gf2__double__d(gfunkptr_t* this) {
}

// float

void  gf2__float__new(gfunkptr_t* result, gfunkptr_t* cause, float f) {
}

float gf2__float__f(gfunkptr_t* this) {
}

// pointer

void gf2__pointer__new(gfunkptr_t* result, gfunkptr_t* cause, ptr p) {
}

ptr  gf2__pointer__p(gfunkptr_t* this) {
}

// mutex

void                     gf2__mutex__new(gfunkptr_t* result, gfunkptr_t* cause) {
}

funk2_processor_mutex_t* gf2__mutex__m(gfunkptr_t* this) {
}

void                     gf2__mutex__lock(gfunkptr_t* this) {
}

void                     gf2__mutex__unlock(gfunkptr_t* this) {
}

int                      gf2__mutex__trylock(gfunkptr_t* this) {
}


// character

void f2char__new(gfunkptr_t* result, gfunkptr_t* cause, char ch) {
}

char gf2__char__ch(gfunkptr_t* this) {
}

// string

void  f2string__new(gfunkptr_t* result, gfunkptr_t* cause, uint length, char* init) {
}

uint  gf2__string__length(gfunkptr_t* this) {
}

s8    gf2__string__elt(gfunkptr_t* this, int index) {
}

boolean_t  gf2__string__equals(gfunkptr_t* this, f2ptr that) {
}

void  gf2__string__str_copy(gfunkptr_t* this, char* str) {
}

int   gf2__string__hash_value(gfunkptr_t* this) {
}


// symbol

void  f2symbol__new(gfunkptr_t* result, gfunkptr_t* cause, uint length, s8* init) {
}

uint  gf2__symbol__length(gfunkptr_t* this) {
}

s8    gf2__symbol__elt(gfunkptr_t* this, int index) {
}

boolean_t  gf2__symbol__equals(gfunkptr_t* this, gfunkptr_t* that) {
}

void  gf2__symbol__str_copy(gfunkptr_t* this, char* str) {
}


// chunk

void gf2__chunk__new(gfunkptr_t* result, gfunkptr_t* cause, uint length, byte* bytes) {
}

uint gf2__chunk__length(gfunkptr_t* this) {
}

u8*  gf2__chunk__bytes(gfunkptr_t* this) {
}


u8    gf2__chunk__8bit__elt(gfunkptr_t* this, uint index) {
}

void  gf2__chunk__8bit__elt__set(gfunkptr_t* this, uint index, u8 value) {
}

u16   gf2__chunk__16bit__elt(gfunkptr_t* this, uint index) {
}

void  gf2__chunk__16bit__elt__set(gfunkptr_t* this, uint index, u16 value) {
}

u32   gf2__chunk__32bit__elt(gfunkptr_t* this, uint index) {
}

void  gf2__chunk__32bit__elt__set(gfunkptr_t* this, uint index, u32 value) {
}

f2ptr gf2__chunk__cfunk_jump(gfunkptr_t* this, f2ptr cause, f2ptr thread, f2ptr env, f2ptr args) {
}

void  gf2__chunk__send(gfunkptr_t* result_dest, gfunkptr_t* this, gfunkptr_t* cause, int start, int length, int fd, int flags) {
}

void  gf2__chunk__recv(gfunkptr_t* result_dest, gfunkptr_t* this, gfunkptr_t* cause, int start, int length, int fd, int flags) {
}


// array

void gf2__array__new(gfunkptr_t* result, gfunkptr_t* cause, uint length, ptr dptr_ptr) {
}

void gf2__array__new_from_f2ptrs(gfunkptr_t* result, gfunkptr_t* cause, uint length, gfunkptr_t** f2ptr_ptr) {
}

void gf2__array__new_copy(gfunkptr_t* result, gfunkptr_t* cause, uint length, gfunkptr_t* init_array) {
}

uint gf2__array__length(gfunkptr_t* this) {
}

void gf2__array__elt(gfunkptr_t* result, gfunkptr_t* this, uint index) {
}

void gf2__array__elt__set(gfunkptr_t* result, gfunkptr_t* this, uint index, gfunkptr_t* cause, gfunkptr_t* value) {
}

void gf2__array__elt__tracing_on(gfunkptr_t* result, gfunkptr_t* this, uint index) {
}

void gf2__array__elt__tracing_on__set(gfunkptr_t* result, gfunkptr_t* this, uint index, gfunkptr_t* value) {
}

void gf2__array__elt__prev(gfunkptr_t* result, gfunkptr_t* this, uint index) {
}

void gf2__array__elt__prev__set(gfunkptr_t* result, gfunkptr_t* this, uint index, gfunkptr_t* value) {
}

void gf2__array__elt__cause(gfunkptr_t* result, gfunkptr_t* this, uint index) {
}

void gf2__array__elt__cause__set(gfunkptr_t* result, gfunkptr_t* this, uint index, gfunkptr_t* value) {
}


void f2__gfunktypes__initialize() {
}


