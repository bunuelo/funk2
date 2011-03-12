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

#include "funk2.h"

void raw__serialize_ptype_to_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index, ptype_t ptype) {
  if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, (u8)ptype);} index += 1;
  if (new_index) {*new_index = index;}
}

ptype_t raw__deserialize_ptype_from_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index) {
  ptype_t ptype = (ptype_t)f2chunk__bit8__elt(chunk, index, cause); index += 1;
  if (new_index) {*new_index = index;}
  return ptype;
}

void raw__serialize_to_chunk_index(f2ptr cause, f2ptr chunk, int index, int *new_index, f2ptr exp) {
  if (exp) {
    ptype_t ptype = f2ptype__raw(exp, cause);
    raw__serialize_ptype_to_chunk_index( cause, chunk, index, &index, (u8)ptype);
    switch(ptype) {
    case ptype_integer:
      printf("\nserialize integer"); fflush(stdout);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, f2integer__i(exp, cause));} index += 8;
      break;
    case ptype_double: {
      printf("\nserialize double"); fflush(stdout);
      union {
	double d;
	u64    i; // these must be the same size
      } convert;
      debug__assert(sizeof(double) == sizeof(u64), nil, "sizeof(double) == sizeof(u64)");
      convert.d = f2double__d(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, convert.i);} index += 8;
    } break;
    case ptype_float: {
      printf("\nserialize float"); fflush(stdout);
      union {
      	float f;
      	u32   i; // these must be the same size
      } convert;
      debug__assert(sizeof(float) == sizeof(u32), nil, "sizeof(float) == sizeof(u32)");
      convert.f = f2float__f(exp, cause);
      if (chunk) {f2chunk__bit32__elt__set(chunk, index, cause, convert.i);} 
      index += 4;
    } break;
    case ptype_pointer: {
      printf("\nserialize pointer"); fflush(stdout);
      u64 i = (u64)f2pointer__p(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, i);} index += 8;
    } break;
    case ptype_gfunkptr: {
      printf("\nserialize gfunkptr"); fflush(stdout);
      union {
	f2ptr g;
	u64   i;
      } u;
      u.g = f2gfunkptr__gfunkptr(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, u.i);} index += 8;
    } break;
    case ptype_scheduler_cmutex: {
      printf("\nserialize scheduler_cmutex"); fflush(stdout);
      u8 temp_buffer[128];
      memset(temp_buffer, 0, 128);
      funk2_processor_mutex_t* scheduler_cmutex = ptype_scheduler_cmutex__m(exp, cause);
      memcpy(temp_buffer, scheduler_cmutex, sizeof(funk2_processor_mutex_t));
      u64 i;
      for (i = 0; i < 128; i++) {
      	if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, temp_buffer[i]);} index ++;
      }
    } break;
    case ptype_cmutex: {
      printf("\nserialize cmutex"); fflush(stdout);
      u8 temp_buffer[128];
      memset(temp_buffer, 0, 128);
      funk2_processor_mutex_t* cmutex = ptype_cmutex__m(exp, cause);
      memcpy(temp_buffer, cmutex, sizeof(funk2_processor_mutex_t));
      u64 i;
      for (i = 0; i < 128; i++) {
      	if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, temp_buffer[i]);} index ++;
      }
    } break;
    case ptype_char:
      printf("\nserialize char"); fflush(stdout);
      if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, (u8)f2char__ch(exp, cause));} index ++;
      break;
    case ptype_string: {
      printf("\nserialize string"); fflush(stdout);
      u64 length = f2string__length(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, length);} index += 8;
      u64 i;
      for (i = 0; i < length; i++) {
	u8 ch = (u8)f2string__elt(exp, i, cause);
	if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, ch);} index ++;
      }
    } break;
    case ptype_symbol: {
      printf("\nserialize symbol"); fflush(stdout);
      u64 length = f2symbol__length(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, length);} index += 8;
      u64 i;
      for (i = 0; i < length; i++) {
	u8 ch = (u8)f2symbol__elt(exp, i, cause);
	if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, ch);} index ++;
      }
    } break;
    case ptype_simple_array:
    case ptype_traced_array: {
      printf("\nserialize array"); fflush(stdout);
      u64 length = raw__array__length(cause, exp);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, length);} index += 8;
      u64 i;
      for (i = 0; i < length; i++) {
	union {
	  f2ptr g;
	  u64   u;
	} convert;
	debug__assert(sizeof(f2ptr) == sizeof(u64), nil, "sizeof(f2ptr) == sizeof(u64)");
	convert.g = raw__array__elt(cause, exp, i);
	if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, convert.u);} index += 8;
      }
    } break;
    case ptype_chunk: {
      printf("\nserialize chunk"); fflush(stdout);
      u64 length = f2chunk__length(exp, cause);
      if (chunk) {f2chunk__bit64__elt__set(chunk, index, cause, length);} index += 8;
      u64 i;
      for (i = 0; i < length; i++) {
	u8 b = f2chunk__bit8__elt(exp, i, cause);
	if (chunk) {f2chunk__bit8__elt__set(chunk, index, cause, b);} index ++;
      }
    } break;
    default:
      error(nil, "f2__serialize error: unknown ptype.");
      break;
    }
  }
  printf("\ndone with a serialization (index = %d)", index); fflush(stdout);
  if (new_index) {*new_index = index;}
}

f2ptr f2__serialize(f2ptr cause, f2ptr exp) {
  int chunk__length;
  raw__serialize_to_chunk_index(cause, nil, 0, &chunk__length, exp);
  printf("\nserialize: chunk__length = %d", chunk__length); fflush(stdout);
  f2ptr chunk = f2chunk__new(cause, chunk__length, NULL);
  raw__serialize_to_chunk_index(cause, chunk, 0, &chunk__length, exp);
  return chunk;
}
def_pcfunk1(f2__serialize, exp, return f2__serialize(this_cause, exp));


f2ptr raw__deserialize_from_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index) {
  ptype_t ptype = raw__deserialize_ptype_from_chunk_index(cause, chunk, index, &index);
  printf("\ndeserialize ptype = %d", (u8)ptype); fflush(stdout);
  f2ptr   exp   = nil;
  switch(ptype) {
  case ptype_integer: {
    u64 i = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    exp = f2integer__new(cause, i);
  } break;
  case ptype_double: {
    union {
      u64    i;
      double d;
    } u;
    u.i = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    exp = f2double__new(cause, u.d);
  } break;
  case ptype_float: {
    union {
      u32   i;
      float f;
    } u;
    u.i = f2chunk__bit32__elt(chunk, index, cause); index += 4;
    exp = f2float__new(cause, u.f);
  } break;
  case ptype_pointer: {
    u64 i = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    void* p = from_ptr((ptr)i);
    exp = f2pointer__new(cause, to_ptr(p));
  } break;
  case ptype_gfunkptr: {
    f2ptr gptr = (f2ptr)f2chunk__bit64__elt(chunk, index, cause); index += 8;
    exp = f2gfunkptr__new(cause, __f2ptr__computer_id(gptr), __f2ptr__pool_index(gptr), __f2ptr__pool_address(gptr));
  } break;
  case ptype_scheduler_cmutex: {
    u8 temp_buffer[128];
    u64 i;
    for (i = 0; i < 128; i++) {
      temp_buffer[i] = f2chunk__bit8__elt(chunk, index, cause); index ++;
    }
    exp = f2scheduler_cmutex__new(cause);
    funk2_processor_mutex_t* scheduler_cmutex = ptype_scheduler_cmutex__m(exp, cause);
    memcpy(scheduler_cmutex, temp_buffer, sizeof(funk2_processor_mutex_t));
  } break;
  case ptype_cmutex: {
    u8 temp_buffer[128];
    u64 i;
    for (i = 0; i < 128; i++) {
      temp_buffer[i] = f2chunk__bit8__elt(chunk, index, cause); index ++;
    }
    exp = f2cmutex__new(cause);
    funk2_processor_mutex_t* cmutex = ptype_cmutex__m(exp, cause);
    memcpy(cmutex, temp_buffer, sizeof(funk2_processor_mutex_t));
  } break;
  case ptype_char: {
    u8 ch = (u8)f2chunk__bit8__elt(chunk, index, cause); index ++;
    exp = f2char__new(cause, ch);
  } break;
  case ptype_string: {
    u64 length = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    s8* str = (s8*)alloca(length + 1); // note: local stack allocation (freed on return)
    u64 i;
    for (i = 0; i < length; i ++) {
      str[i] = (s8)f2chunk__bit8__elt(chunk, index, cause); index ++;
    }
    str[i] = 0;
    exp = f2string__new(cause, length, (u8*)str);
  } break;
  case ptype_symbol: {
    u64 length = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    s8* str = (s8*)alloca(length + 1); // note: local stack allocation (freed on return)
    u64 i;
    for (i = 0; i < length; i ++) {
      str[i] = (s8)f2chunk__bit8__elt(chunk, index, cause); index ++;
    }
    str[i] = 0;
    exp = f2symbol__new(cause, length, (u8*)str);
  } break;
  case ptype_simple_array:
  case ptype_traced_array: {
    u64    length = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    u64 i;
    exp = raw__array__new(cause, length);
    for (i = 0; i < length; i ++) {
      raw__array__elt__set(cause, exp, i, (f2ptr)f2chunk__bit64__elt(chunk, index, cause)); index += 8;
    }
  } break;
  case ptype_chunk: {
    u64 length = f2chunk__bit64__elt(chunk, index, cause); index += 8;
    u8* str = (u8*)alloca(length); // note: local stack allocation (freed on return)
    u64 i;
    for (i = 0; i < length; i ++) {
      str[i] = f2chunk__bit8__elt(chunk, index, cause); index ++;
    }
    exp = f2chunk__new(cause, length, str);
  } break;
  default:
    error(nil, "f2__deserialize error: unknown ptype.");
    break;
  }
  if (new_index) {*new_index = index;}
  return exp;
}

f2ptr f2__deserialize(f2ptr cause, f2ptr chunk, f2ptr index, f2ptr new_index_place) {
  int new_index__i;
  f2ptr exp = raw__deserialize_from_chunk_index(cause, chunk, f2integer__i(index, cause), &new_index__i);
  if (new_index_place) {
    f2place__thing__set(new_index_place, cause, f2integer__new(cause, new_index__i));
  }
  return exp;
}
def_pcfunk3(f2__deserialize, chunk, index, new_index_place, return f2__deserialize(this_cause, chunk, index, new_index_place));

void f2__serialize__reinitialize_globalvars() {
  //f2ptr cause = f2_serialize_c__cause__new(initial_cause(), nil, nil);
  
}

void f2__serialize__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "serialize", "", &f2__serialize__reinitialize_globalvars);
  
  f2__serialize__reinitialize_globalvars();
  
  f2__primcfunk__init(f2__serialize, "");
  f2__primcfunk__init(f2__deserialize, "");
}


