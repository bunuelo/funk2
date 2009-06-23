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

#include "funk2.h"

f2ptr __argument_type_check_failure__exception__tag;
f2ptr __argument_type_check_failure__exception;
f2ptr __argument_number_check_failure__exception__tag;
f2ptr __argument_number_check_failure__exception;

f2ptr f2__argument_type_check_failure__exception__new(f2ptr cause, f2ptr value)                                      {return f2exception__new(cause, __argument_type_check_failure__exception__tag,   value);}
f2ptr f2__argument_number_check_failure__exception__new(f2ptr cause, f2ptr funk_symbol, int min_arg_num, f2ptr args) {return f2exception__new(cause, __argument_number_check_failure__exception__tag, f2list3__new(cause, funk_symbol, f2integer__new(cause, min_arg_num), args));}

// nil

boolean_t raw__null(f2ptr x) {return !x;}

f2ptr f2__null(f2ptr cause, f2ptr x) {return f2bool__new(raw__null(x));}
def_pcfunk1(null, x, return f2__null(this_cause, x));

// logic

boolean_t raw__not(f2ptr x) {return !x;}

f2ptr f2__not(f2ptr cause, f2ptr x) {return f2bool__new(raw__not(x));}
def_pcfunk1(not, x, return f2__not(this_cause, x));

// system

f2ptr f2__system__node_id(f2ptr cause) {
  return f2pointer__new(cause, __funk2.node_id);
}
def_pcfunk0(system__node_id, return f2__system__node_id(this_cause));

f2ptr f2__system__environment(f2ptr cause, f2ptr node_id) {
  node_id_t raw_node_id;
  if (raw__pointerp(node_id, cause)) {
    raw_node_id = f2pointer__p(node_id, cause);
  } else if (raw__integerp(node_id, cause)) {
    raw_node_id = f2integer__i(node_id, cause);
  } else {
    printf("\nsystem-environment error: node_id must be integer or pointer.");
    return nil;
  }
  return f2system__environment(cause, raw_node_id);
}
def_pcfunk1(system__environment, node_id, return f2__system__environment(this_cause, node_id));

// funk2 pointer (f2ptr)

f2ptr f2__pointer(f2ptr cause, f2ptr x) {return f2pointer__new(cause, (ptr)(long)x);}
def_pcfunk1(pointer, x, return f2__pointer(this_cause, x));

f2ptr f2__deref_pointer(f2ptr cause, f2ptr x) {return (f2ptr)(long)f2pointer__p(x, cause);}
def_pcfunk1(deref_pointer, x, return f2__deref_pointer(this_cause, x));

// memblock

f2ptr f2__memblock__set_init_render_xyz(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {
  memblock__set_init_render_xyz(f2float__f(x, cause), f2float__f(y, cause), f2float__f(z, cause));
  return nil;
}
def_pcfunk3(memblock__set_init_render_xyz, x, y, z, return f2__memblock__set_init_render_xyz(this_cause, x, y, z));

f2ptr f2__memblock__set_init_render_on(f2ptr cause, f2ptr render_on) {
  memblock__set_init_render_on(f2integer__i(render_on, cause));
  return nil;
}
def_pcfunk1(memblock__set_init_render_on, render_on, return f2__memblock__set_init_render_on(this_cause, render_on));

f2ptr f2__memblock__set_init_render_noise(f2ptr cause, f2ptr render_noise) {
  memblock__set_init_render_noise(f2float__f(render_noise, cause));
  return nil;
}
def_pcfunk1(memblock__set_init_render_noise, render_noise, return f2__memblock__set_init_render_noise(this_cause, render_noise));

// ptype

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2ptype__raw(x, cause));}
def_pcfunk1(ptype__raw, x, return f2__ptype__raw(this_cause, x));

f2ptr f2__ptype__cause(f2ptr cause, f2ptr x) {return f2ptype__cause(x, cause);}
def_pcfunk1(ptype__cause, x, return f2__ptype__cause(this_cause, x));

f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value) {f2ptype__cause__set(x, cause, value); return nil;}
def_pcfunk2(ptype__cause__set, x, value, return f2__ptype__cause__set(this_cause, x, value));

// integer

boolean_t raw__integerp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_integer);}

f2ptr f2__integerp(f2ptr cause, f2ptr x) {return f2bool__new(raw__integerp(x, cause));}
def_pcfunk1(integerp, x, return f2__integerp(this_cause, x));

f2ptr f2__integer__to_double(f2ptr cause, f2ptr x) {return f2double__new(cause, f2integer__i(x, cause));}
def_pcfunk1(integer__to_double, x, return f2__integer__to_double(this_cause, x));

f2ptr f2__integer__to_float(f2ptr cause, f2ptr x) {return f2float__new(cause, f2integer__i(x, cause));}
def_pcfunk1(integer__to_float,  x, return f2__integer__to_float(this_cause, x));

f2ptr f2__integer__greater_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) >  f2integer__i(y, cause));}
def_pcfunk2(integer__greater_than, x, y, return f2__integer__greater_than(this_cause, x, y));

f2ptr f2__integer__less_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) <  f2integer__i(y, cause));}
def_pcfunk2(integer__less_than, x, y, return f2__integer__less_than(this_cause, x, y));

f2ptr f2__integer__equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) == f2integer__i(y, cause));}
def_pcfunk2(integer__equal_sign, x, y, return f2__integer__equal_sign(this_cause, x, y));

f2ptr f2__integer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) != f2integer__i(y, cause));}
def_pcfunk2(integer__not_equal_sign, x, y, return f2__integer__not_equal_sign(this_cause, x, y));

f2ptr f2__integer__bitshift_left(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) << f2integer__i(y, cause));}
def_pcfunk2(integer__bitshift_left, x, y, return f2__integer__bitshift_left(this_cause, x, y));

f2ptr f2__integer__bitshift_right(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) >> f2integer__i(y, cause));}
def_pcfunk2(integer__bitshift_right, x, y, return f2__integer__bitshift_right(this_cause, x, y));

f2ptr f2__integer__bit_and(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) &  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_and, x, y, return f2__integer__bit_and(this_cause, x, y));

f2ptr f2__integer__bit_or(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) |  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_or, x, y, return f2__integer__bit_or(this_cause, x, y));

f2ptr f2__integer__bit_xor(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) ^  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_xor, x, y, return f2__integer__bit_xor(this_cause, x, y));

f2ptr f2__integer__bit_not(f2ptr cause, f2ptr x) {return f2integer__new(cause, ~f2integer__i(x, cause));}
def_pcfunk1(integer__bit_not, x, return f2__integer__bit_not(this_cause, x));

f2ptr f2__integer__add(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) +  f2integer__i(y, cause));}
def_pcfunk2(integer__add, x, y, return f2__integer__add(this_cause, x, y));

f2ptr f2__integer__subtract(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) -  f2integer__i(y, cause));}
def_pcfunk2(integer__subtract, x, y, return f2__integer__subtract(this_cause, x, y));

f2ptr f2__integer__multiply(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) *  f2integer__i(y, cause));}
def_pcfunk2(integer__multiply, x, y, return f2__integer__multiply(this_cause, x, y));

f2ptr f2__integer__add_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  f2integer__i(x, cause) +   f2double__d(y, cause));}
def_pcfunk2(integer__add_double, x, y, return f2__integer__add_double(this_cause, x, y));

f2ptr f2__integer__subtract_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  f2integer__i(x, cause) -   f2double__d(y, cause));}
def_pcfunk2(integer__subtract_double, x, y, return f2__integer__subtract_double(this_cause, x, y));

f2ptr f2__integer__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) /  f2integer__i(y, cause));}
def_pcfunk2(integer__divide_by_integer, x, y, return f2__integer__divide_by_integer(this_cause, x, y));

f2ptr f2__integer__divide_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  (double)f2integer__i(x, cause) / f2double__d(y, cause));}
def_pcfunk2(integer__divide_by_double, x, y, return f2__integer__divide_by_double(this_cause, x, y));

// double

boolean_t raw__doublep(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_double);}

f2ptr f2__doublep(f2ptr cause, f2ptr x) {return f2bool__new(raw__doublep(x, cause));}
def_pcfunk1(doublep, x, return f2__doublep(this_cause, x));

f2ptr f2__double__to_integer(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2double__d(x, cause));}
def_pcfunk1(double__to_integer, x, return f2__double__to_integer(this_cause, x));

f2ptr f2__double__to_float(f2ptr cause, f2ptr x) {return f2float__new(cause, f2double__d(x, cause));}
def_pcfunk1(double__to_float, x, return f2__double__to_float(this_cause, x));

f2ptr f2__double__add_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) + f2double__d(y, cause));}
def_pcfunk2(double__add_double, x, y, return f2__double__add_double(this_cause, x, y));

f2ptr f2__double__subtract_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) - f2double__d(y, cause));}
def_pcfunk2(double__subtract_double, x, y, return f2__double__subtract_double(this_cause, x, y));

f2ptr f2__double__multiply_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) * f2double__d(y, cause));}
def_pcfunk2(double__multiply_by_double, x, y, return f2__double__multiply_by_double(this_cause, x, y));

f2ptr f2__double__divide_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) / f2double__d(y, cause));}
def_pcfunk2(double__divide_by_double, x, y, return f2__double__divide_by_double(this_cause, x, y));

f2ptr f2__double__add_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) + f2integer__i(y, cause));}
def_pcfunk2(double__add_integer, x, y, return f2__double__add_integer(this_cause, x, y));

f2ptr f2__double__subtract_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) - f2integer__i(y, cause));}
def_pcfunk2(double__subtract_integer, x, y, return f2__double__subtract_integer(this_cause, x, y));

f2ptr f2__double__multiply_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) * f2integer__i(y, cause));}
def_pcfunk2(double__multiply_by_integer, x, y, return f2__double__multiply_by_integer(this_cause, x, y));

f2ptr f2__double__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) / f2integer__i(y, cause));}
def_pcfunk2(double__divide_by_integer, x, y, return f2__double__divide_by_integer(this_cause, x, y));

// float

boolean_t raw__floatp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_float);}

f2ptr f2__floatp(f2ptr cause, f2ptr x) {return f2bool__new(raw__floatp(x, cause));}
def_pcfunk1(floatp, x, return f2__floatp(this_cause, x));

f2ptr f2__float__to_integer(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2float__f(x, cause));}
def_pcfunk1(float__to_integer, x, return f2__float__to_integer(this_cause, x));

f2ptr f2__float__to_double(f2ptr cause, f2ptr x) {return f2double__new(cause, f2float__f(x, cause));}
def_pcfunk1(float__to_double, x, return f2__float__to_double(this_cause, x));

// pointer

boolean_t raw__pointerp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_pointer);}

f2ptr f2__pointerp(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointerp(x, cause));}
def_pcfunk1(pointerp, x, return f2__pointerp(this_cause, x));

f2ptr f2__pointer__greater_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) >  f2pointer__p(y, cause));}
def_pcfunk2(pointer__greater_than, x, y, return f2__pointer__greater_than(this_cause, x, y));

f2ptr f2__pointer__less_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) <  f2pointer__p(y, cause));}
def_pcfunk2(pointer__less_than, x, y, return f2__pointer__less_than(this_cause, x, y));

f2ptr f2__pointer__equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) == f2pointer__p(y, cause));}
def_pcfunk2(pointer__equal_sign, x, y, return f2__pointer__equal_sign(this_cause, x, y));

f2ptr f2__pointer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) != f2pointer__p(y, cause));}
def_pcfunk2(pointer__not_equal_sign, x, y, return f2__pointer__not_equal_sign(this_cause, x, y));

f2ptr f2__pointer__add_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2pointer__new(cause, f2pointer__p(x, cause) +  f2integer__i(y, cause));}
def_pcfunk2(pointer__add_integer, x, y, return f2__pointer__add_integer(this_cause, x, y));

f2ptr f2__pointer__subtract(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2pointer__p(x, cause) -  f2pointer__p(y, cause));}
def_pcfunk2(pointer__subtract, x, y, return f2__pointer__subtract(this_cause, x, y));

// gfunkptr

boolean_t raw__gfunkptrp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_gfunkptr);}

f2ptr f2__gfunkptr(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2gfunkptr__new(cause, f2integer__i(x, cause), f2integer__i(y, cause), f2integer__i(z, cause));}
def_pcfunk3(gfunkptr, x, y, z, return f2__gfunkptr(this_cause, x, y, z));

f2ptr f2__gfunkptr__new_from_pointer(f2ptr cause, f2ptr x) {f2ptr f2p = (f2ptr)((unsigned long)f2pointer__p(x, cause)); return f2gfunkptr__new(cause, __f2ptr__computer_id(f2p), __f2ptr__pool_index(f2p), __f2ptr__pool_address(f2p));}
def_pcfunk1(gfunkptr__new_from_pointer, x, return f2__gfunkptr__new_from_pointer(this_cause, x));

f2ptr f2__gfunkptrp(f2ptr cause, f2ptr x) {return f2bool__new(raw__gfunkptrp(x, cause));}
def_pcfunk1(gfunkptrp, x, return f2__gfunkptrp(this_cause, x));

// mutex

boolean_t raw__mutexp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_mutex);}

f2ptr f2__mutex(f2ptr cause) {return f2mutex__new(cause);}
def_pcfunk0(mutex, return f2__mutex(this_cause));

f2ptr f2__mutexp(f2ptr cause, f2ptr x) {return f2bool__new(raw__mutexp(x, cause));}
def_pcfunk1(mutexp, x, return f2__mutexp(this_cause, x));

f2ptr f2__mutex__lock(f2ptr cause, f2ptr x) {f2mutex__lock(x, cause); return nil;}
def_pcfunk1(mutex__lock, x, return f2__mutex__lock(this_cause, x));

f2ptr f2__mutex__unlock(f2ptr cause, f2ptr x) {f2mutex__unlock(x, cause); return nil;}
def_pcfunk1(mutex__unlock, x, return f2__mutex__unlock(this_cause, x));

f2ptr f2__mutex__trylock(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2mutex__trylock(x, cause));}
def_pcfunk1(mutex__trylock, x, return f2__mutex__trylock(this_cause, x));

// char

boolean_t raw__charp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_char);}

// string

boolean_t raw__stringp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_string);}

f2ptr f2__stringp(f2ptr cause, f2ptr x) {return f2bool__new(raw__stringp(x, cause));}
def_pcfunk1(stringp, x, return f2__stringp(this_cause, x));

f2ptr f2__string__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2string__length(x, cause));}
def_pcfunk1(string__length, x, return f2__string__length(this_cause, x));

f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if ((! raw__stringp(this, cause)) ||
      (! raw__integerp(index, cause))) {
    return f2larva__new(cause, 1);
  }
  u64 raw_index = f2integer__i(index, cause);
  return f2char__new(cause, f2string__elt(this, raw_index, cause));
}
def_pcfunk2(string__elt, x, y, return f2__string__elt(this_cause, x, y));

f2ptr f2__string__eq(f2ptr cause, f2ptr x, f2ptr y) {
  u64 x_len = f2string__length(x, cause);
  u64 y_len = f2string__length(y, cause);
  if (x_len != y_len) {
    return nil;
  }
  char* x_str = alloca(x_len);
  char* y_str = alloca(x_len);
  f2string__str_copy(x, cause, (u8*)x_str);
  f2string__str_copy(y, cause, (u8*)y_str);
  return f2bool__new(memcmp(x_str, y_str, x_len) == 0);
}
def_pcfunk2(string__equals, x, y, return f2__string__eq(this_cause, x, y));

f2ptr f2__string__new_raw_c_string(f2ptr cause, f2ptr x) {
  int length = f2string__length(x, cause);
  char* str = (char*)from_ptr(f2__malloc(length + 1));
  f2string__str_copy(x, cause, (u8*)str);
  str[length] = 0;
  return f2pointer__new(cause, to_ptr(str));
}
def_pcfunk1(string__new_raw_c_string, x, return f2__string__new_raw_c_string(this_cause, x));

f2ptr f2__string__new_from_raw_c_string(f2ptr cause, f2ptr x) {
  if (!raw__pointerp(x, cause)) {return f2larva__new(cause, 1);}
  char* str = (char*)from_ptr(f2pointer__p(x, cause));
  return f2string__new(cause, strlen(str), (u8*)str);
}
def_pcfunk1(string__new_from_raw_c_string, x, return f2__string__new_from_raw_c_string(this_cause, x));

// symbol

boolean_t raw__symbolp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_symbol);}

f2ptr f2__symbolp(f2ptr cause, f2ptr x) {return f2bool__new(raw__symbolp(x, cause));}
def_pcfunk1(symbolp, x, return f2__symbolp(this_cause, x));

f2ptr f2__symbol__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2symbol__length(x, cause));}
def_pcfunk1(symbol__length, x, return f2__symbol__length(this_cause, x));

f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2symbol__elt(x, f2integer__i(y, cause), cause));}
def_pcfunk2(symbol__elt, x, y, return f2__symbol__elt(this_cause, x, y));

//boolean_t  pfunk2__f2symbol__equals(f2ptr this, f2ptr cause, f2ptr that) {
//  int pool_index = __f2ptr__pool_index(this);
//  ptype_access_num__incr(pool_index);
//  __pure__memblock__render_read_activated__set(this, 1);
//  __pure__memblock__render_read_activated__set(that, 1);
//  int this_length = __pure__f2symbol__length(this);
//  if (this_length != __pure__f2symbol__length(that)) {
//    ptype_access_num__decr(pool_index);
//    return 0;
//  }
//  boolean_t retval = (! memcmp(__pure__f2symbol__str(this), __pure__f2symbol__str(that), this_length));
//  ptype_access_num__decr(pool_index);
//  return retval;
//}

boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__symbolp(this, cause)) || (! raw__symbolp(that, cause))) {return boolean__false;}
  u64 this__length = f2symbol__length(this, cause);
  u64 that__length = f2symbol__length(that, cause);
  if (this__length != that__length) {
    return boolean__false;
  }
  char* this__str = (char*)alloca(this__length + 1);
  char* that__str = (char*)alloca(that__length + 1);
  f2symbol__str_copy(this, cause, (u8*)this__str);
  f2symbol__str_copy(that, cause, (u8*)that__str);
  if (memcmp(this__str, that__str, this__length) != 0) {
    return boolean__false;
  }
  return boolean__true;
}

f2ptr f2__symbol__eq(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(raw__symbol__eq(cause, x, y));}
def_pcfunk2(symbol__eq, x, y, return f2__symbol__eq(this_cause, x, y));

// simple_array

boolean_t raw__simple_arrayp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_simple_array);}

f2ptr f2__simple_arrayp(f2ptr cause, f2ptr x) {return f2bool__new(raw__simple_arrayp(x, cause));}
def_pcfunk1(simple_arrayp, x, return f2__simple_arrayp(this_cause, x));

f2ptr f2__simple_array__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2simple_array__length(x, cause));}
def_pcfunk1(simple_array__length, x, return f2__simple_array__length(this_cause, x));

f2ptr f2__simple_array__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2simple_array__elt(x, f2integer__i(y, cause), cause);}
def_pcfunk2(simple_array__elt, x, y, return f2__simple_array__elt(this_cause, x, y));

f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2simple_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
def_pcfunk3(simple_array__elt__set, x, y, z, return f2__simple_array__elt__set(this_cause, x, y, z));


// traced_array

boolean_t raw__traced_arrayp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_traced_array);}

f2ptr f2__traced_arrayp(f2ptr cause, f2ptr x) {return f2bool__new(raw__traced_arrayp(x, cause));}
def_pcfunk1(traced_arrayp, x, return f2__traced_arrayp(this_cause, x));

f2ptr f2__traced_array__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2traced_array__length(x, cause));}
def_pcfunk1(traced_array__length, x, return f2__traced_array__length(this_cause, x));

f2ptr f2__traced_array__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt(x, f2integer__i(y, cause), cause);}
def_pcfunk2(traced_array__elt, x, y, return f2__traced_array__elt(this_cause, x, y));

f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
def_pcfunk3(traced_array__elt__set, x, y, z, return f2__traced_array__elt__set(this_cause, x, y, z));

f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__tracing_on(x, f2integer__i(y, cause), cause);}
def_pcfunk2(traced_array__elt__tracing_on, x, y, return f2__traced_array__elt__tracing_on(this_cause, x, y));

f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__tracing_on__set(x, f2integer__i(y, cause), cause, z); return nil;}
def_pcfunk3(traced_array__elt__tracing_on__set, x, y, z, return f2__traced_array__elt__tracing_on__set(this_cause, x, y, z));

f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__trace(x, f2integer__i(y, cause), cause);}
def_pcfunk2(traced_array__elt__trace, x, y, return f2__traced_array__elt__trace(this_cause, x, y));

f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__trace__set(x, f2integer__i(y, cause), cause, z); return nil;}
def_pcfunk3(traced_array__elt__trace__set, x, y, z, return f2__traced_array__elt__trace__set(this_cause, x, y, z));

f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__imagination_frame(x, f2integer__i(y, cause), cause);}
def_pcfunk2(traced_array__elt__imagination_frame, x, y, return f2__traced_array__elt__imagination_frame(this_cause, x, y));

f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__imagination_frame__set(x, f2integer__i(y, cause), cause, z); return nil;}
def_pcfunk3(traced_array__elt__imagination_frame__set, x, y, z, return f2__traced_array__elt__imagination_frame__set(this_cause, x, y, z));

// array interface

f2ptr raw__array__new(f2ptr cause, u64 length) {
  if (raw__cause__is_traced(cause, cause)) {
    return f2traced_array__new(cause, length, to_ptr(NULL));
  } else {
    return f2simple_array__new(cause, length, to_ptr(NULL));
  }
}

f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init) {
  if (raw__cause__is_traced(cause, cause)) {
    return f2traced_array__new_copy(cause, length, init);
  } else {
    return f2simple_array__new_copy(cause, length, init);
  }
}

boolean_t raw__arrayp(f2ptr x, f2ptr cause) {return (raw__simple_arrayp(x, cause) || raw__traced_arrayp(x, cause));}

f2ptr f2__arrayp(f2ptr cause, f2ptr x) {return f2bool__new(raw__arrayp(x, cause));}
def_pcfunk1(arrayp, x, return f2__arrayp(this_cause, x));

u64 raw__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_arrayp(x, cause)) {return f2simple_array__length(x, cause);}
  else if (raw__traced_arrayp(x, cause)) {return f2traced_array__length(x, cause);}
  else {error(nil, "raw__array__length: invalid type"); return 0;}
}
f2ptr f2__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_arrayp(x, cause)) {return f2integer__new(cause, f2simple_array__length(x, cause));}
  else if (raw__traced_arrayp(x, cause)) {return f2integer__new(cause, f2traced_array__length(x, cause));}
  else {return f2larva__new(cause, 1);}
}
def_pcfunk1(array__length, x, return f2__array__length(this_cause, x));

f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_arrayp(this, cause)) {return f2simple_array__elt(this, index, cause);}
  else if (raw__traced_arrayp(this, cause)) {return f2traced_array__elt(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt, x, y, return f2__array__elt(this_cause, x, y));

f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_arrayp(this, cause)) {f2simple_array__elt__set(this, index, cause, value); return nil;}
  else if (raw__traced_arrayp(this, cause)) {f2traced_array__elt__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__set, x, y, z, return f2__array__elt__set(this_cause, x, y, z));

f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth) {
  if      (raw__simple_arrayp(this, cause)) {f2simple_array__elt__set(             this, index, cause, value             ); return nil;}
  else if (raw__traced_arrayp(this, cause)) {f2traced_array__elt__set__trace_depth(this, index, cause, value, trace_depth); return nil;}
  else {
    error(nil, "raw__array__elt__set__trace_depth: should be a type of array.");
    return nil;
  }
}

f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_arrayp(this, cause)) {return nil;}
  else if (raw__traced_arrayp(this, cause)) {return f2traced_array__elt__tracing_on(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__tracing_on, x, y, return f2__array__elt__tracing_on(this_cause, x, y));

f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_arrayp(this, cause)) {return f2larva__new(cause, 1);}
  else if (raw__traced_arrayp(this, cause)) {f2traced_array__elt__tracing_on__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__tracing_on__set, x, y, z, return f2__array__elt__tracing_on__set(this_cause, x, y, z));

f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_arrayp(this, cause)) {return nil;}
  else if (raw__traced_arrayp(this, cause)) {return f2traced_array__elt__trace(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__trace, x, y, return f2__array__elt__trace(this_cause, x, y));

f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_arrayp(this, cause)) {return f2larva__new(cause, 1);}
  else if (raw__traced_arrayp(this, cause)) {f2traced_array__elt__trace__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__trace__set, x, y, z, return f2__array__elt__trace__set(this_cause, x, y, z));

f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_arrayp(this, cause)) {return nil;}
  else if (raw__traced_arrayp(this, cause)) {return f2traced_array__elt__imagination_frame(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__imagination_frame, x, y, return f2__array__elt__imagination_frame(this_cause, x, y));

f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_arrayp(this, cause)) {return f2larva__new(cause, 1);}
  else if (raw__traced_arrayp(this, cause)) {f2traced_array__elt__imagination_frame__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integerp(index, cause)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__imagination_frame__set, x, y, z, return f2__array__elt__imagination_frame__set(this_cause, x, y, z));



// larva

boolean_t raw__larvap(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_larva);}

// place

boolean_t raw__placep(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_place(x, cause));}

f2ptr f2__place(f2ptr cause, f2ptr x) {return f2place__new(cause, x);}
def_pcfunk1(place, x, return f2__place(this_cause, x));

f2ptr f2__placep(f2ptr cause, f2ptr x) {return f2bool__new(raw__placep(x, cause));}
def_pcfunk1(placep, x, return f2__placep(this_cause, x));

f2ptr f2__place__thing(f2ptr cause, f2ptr x) {return f2place__thing(x, cause);}
def_pcfunk1(place__thing, x, return f2__place__thing(this_cause, x));

f2ptr f2__place__thing__set(f2ptr cause, f2ptr x, f2ptr y) {f2place__thing__set(x, cause, y); return nil;}
def_pcfunk2(place__thing__set, x, y, return f2__place__thing__set(this_cause, x, y));

// cons

boolean_t raw__consp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_cons(x, cause));}

f2ptr f2__cons(f2ptr cause, f2ptr x, f2ptr y) {return f2cons__new(cause, x, y);}
def_pcfunk2(cons, x, y, return f2__cons(this_cause, x, y));

f2ptr f2__consp(f2ptr cause, f2ptr x) {return f2bool__new(raw__consp(x, cause));}
def_pcfunk1(consp, x, return f2__consp(this_cause, x));

f2ptr f2__cons__car(f2ptr cause, f2ptr x) {return f2cons__car(x, cause);}
def_pcfunk1(cons__car, x, return f2__cons__car(this_cause, x));

f2ptr f2__cons__car__set(f2ptr cause, f2ptr x, f2ptr y) {f2cons__car__set(x, cause, y); return nil;}
def_pcfunk2(cons__car__set, x, y, return f2__cons__car__set(this_cause, x, y));

f2ptr f2__cons__cdr(f2ptr cause, f2ptr x) {return f2cons__cdr(x, cause);}
def_pcfunk1(cons__cdr, x, return f2__cons__cdr(this_cause, x));

f2ptr f2__cons__cdr__set(f2ptr cause, f2ptr x, f2ptr y) {f2cons__cdr__set(x, cause, y); return nil;}
def_pcfunk2(cons__cdr__set, x, y, return f2__cons__cdr__set(this_cause, x, y));

// doublelink

boolean_t raw__doublelinkp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_doublelink(x, cause));}

f2ptr f2__doublelink(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2doublelink__new(cause, x, y, z);}
def_pcfunk3(doublelink, x, y, z, return f2__doublelink(this_cause, x, y, z));

f2ptr f2__doublelinkp(f2ptr cause, f2ptr x) {return f2bool__new(raw__doublelinkp(x, cause));}
def_pcfunk1(doublelinkp, x, return f2__doublelinkp(this_cause, x));

f2ptr f2__doublelink__prev(f2ptr cause, f2ptr x) {return f2doublelink__prev(x, cause);}
def_pcfunk1(doublelink__prev, x, return f2__doublelink__prev(this_cause, x));

f2ptr f2__doublelink__prev__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__prev__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__prev__set, x, y, return f2__doublelink__prev__set(this_cause, x, y));

f2ptr f2__doublelink__next(f2ptr cause, f2ptr x) {return f2doublelink__next(x, cause);}
def_pcfunk1(doublelink__next, x, return f2__doublelink__next(this_cause, x));

f2ptr f2__doublelink__next__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__next__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__next__set, x, y, return f2__doublelink__next__set(this_cause, x, y));

f2ptr f2__doublelink__value(f2ptr cause, f2ptr x) {return f2doublelink__value(x, cause);}
def_pcfunk1(doublelink__value, x, return f2__doublelink__value(this_cause, x));

f2ptr f2__doublelink__value__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__value__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__value__set, x, y, return f2__doublelink__value__set(this_cause, x, y));

// chunk

f2ptr f2__chunk(f2ptr cause, f2ptr length) {
  if ((! length) || (! raw__integerp(length, cause))) {
    printf("\n[chunk length] error: length must be integer.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, nil);
  }
  int raw_length = f2integer__i(length, cause);
  return f2chunk__new(cause, raw_length, NULL);
}
def_pcfunk1(chunk, length, return f2__chunk(this_cause, length));

boolean_t raw__chunkp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_chunk);}

f2ptr f2__chunkp(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunkp(x, cause));}
def_pcfunk1(chunkp, x, return f2__chunkp(this_cause, x));

f2ptr f2__chunk__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2chunk__length(x, cause));}
def_pcfunk1(chunk__length, x, return f2__chunk__length(this_cause, x));

//f2ptr f2__chunk__bytes(f2ptr cause, f2ptr x) {return f2pointer__new(cause, f2chunk__bytes(x, cause));}
//def_pcfunk1(chunk__bytes, x, return f2__chunk__bytes(this_cause, x));

f2ptr f2__chunk__new_compiled_from_funk(f2ptr cause, f2ptr x) {return f2chunk__new_compiled_from_funk(cause, x);}
def_pcfunk1(chunk__new_compiled_from_funk, x, return f2__chunk__new_compiled_from_funk(this_cause, x));

// primobject hashtable

def_pcfunk3(hashtable__add_keyvalue_pair,    this, key, value,        f2__hashtable__add_keyvalue_pair(   simple_cause, this, key, value); return nil);
def_pcfunk2(hashtable__lookup_keyvalue_pair, this, key,        return f2__hashtable__lookup_keyvalue_pair(this,   this_cause, key));
def_pcfunk2(hashtable__lookup_value,         this, key,        return f2__hashtable__lookup_value(        this,   this_cause, key));

// primobject thread

void f2thread__force_funk(f2ptr thread, f2ptr cause, f2ptr cfunkable, f2ptr args) {
  pause_gc();
  f2ptr env;
  if      (raw__funkp(cfunkable, cause))       {env = f2funk__env(cfunkable, cause);}
  else if (raw__metrop(cfunkable, cause))      {env = f2metro__env(cfunkable, cause);}
  else if (raw__cfunkp(cfunkable, cause))      {env = f2thread__env(thread, cause);}
  else if (raw__metrocfunkp(cfunkable, cause)) {env = f2thread__env(thread, cause);}
  else                                         {error(nil, "f2thread__force_funk error: cfunkable must be funk or metro.");}
  
  f2thread__env__set(thread, cause, env);
  f2thread__args__set(thread, cause, args);
  f2thread__value__set(thread, cause, cfunkable);
  //f2thread__program_counter__set(thread, cause, f2__compile__funk_bc(cause, nil));
  
  f2__thread__bytecode_helper__funk__no_increment_pc_reg(thread, cause);
  //f2__global_scheduler__add_thread(cause, thread);
  resume_gc();
}

boolean_t raw__funkablep(f2ptr exp, f2ptr cause) {
  return (exp && (raw__funkp(      exp, cause) ||
		  raw__metrop(     exp, cause) ||
		  raw__cfunkp(     exp, cause) ||
		  raw__metrocfunkp(exp, cause)));
}

// returns larva on error
f2ptr raw__funkable__env(f2ptr cause, f2ptr funkable) {
  if      (raw__funkp(funkable, cause))       {return f2funk__env( funkable, cause);}
  else if (raw__metrop(funkable, cause))      {return f2metro__env(funkable, cause);}
  else if (raw__cfunkp(funkable, cause))      {return nil;}
  else if (raw__metrocfunkp(funkable, cause)) {return nil;}
  return f2larva__new(cause, 1);
}

void debug__f2thread__funk__unfunkable_error() {
  status("debug__f2thread__funk__unfunkable_error here.");
}

void f2thread__funk(f2ptr thread, f2ptr cause, f2ptr cfunkable, f2ptr args) {
  pause_gc();
  
  f2thread__args__set(           thread, cause, args);
  f2thread__value__set(          thread, cause, cfunkable);
  f2thread__program_counter__set(thread, cause, f2__compile__funk_bc(cause));
  
  if (raw__funkablep(cfunkable, cause)) {
    f2ptr env = raw__funkable__env(cause, cfunkable);
    if (env) {
      f2thread__env__set(thread, cause, env);
    }
  } else {
    status(  "[ERROR] f2thread__force_funk error: cfunkable must be funk or metro.");
    printf("\n[ERROR] f2thread__force_funk error: cfunkable must be funk or metro.\n"); fflush(stdout);
    printf("\n[ERROR] cfunkable="); fflush(stdout); f2__print(cause, cfunkable); fflush(stdout); printf("\n"); fflush(stdout);
    f2thread__value__set(thread, cause, f2larva__new(cause, 24));
    debug__f2thread__funk__unfunkable_error();
  }
  
  resume_gc();
}

f2ptr f2__thread(f2ptr cause, f2ptr parent_thread, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  pause_gc();
  f2ptr new_thread = f2thread__new(cause,
				   nil,
				   nil,
				   nil,
				   parent_env,
				   nil,
				   nil,
				   nil,
				   nil,
				   nil,
				   cause,
				   __funk2.globalenv.true__symbol,
				   nil,
				   parent_thread,
				   parent_env,
				   f2mutex__new(cause),
				   nil,
				   nil);
  
  f2thread__keep_undead__set(new_thread, cause, __funk2.globalenv.true__symbol);
  f2thread__funk(new_thread, cause, cfunkable, args);
  
  f2__global_scheduler__add_thread_parallel(cause, new_thread);
  resume_gc();
  return new_thread;
}
def_pcfunk2(thread, funk, args, return f2__thread(this_cause, simple_thread, simple_env, funk, args));

f2ptr f2__thread_serial(f2ptr cause, f2ptr parent_thread, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  pause_gc();
  f2ptr new_thread = f2thread__new(cause,
				   nil,
				   nil,
				   nil,
				   parent_env,
				   nil,
				   nil,
				   nil,
				   nil,
				   nil,
				   cause,
				   __funk2.globalenv.true__symbol,
				   nil,
				   parent_thread,
				   parent_env,
				   f2mutex__new(cause),
				   nil,
				   nil);
  
  f2thread__keep_undead__set(new_thread, cause, __funk2.globalenv.true__symbol);
  f2thread__funk(new_thread, cause, cfunkable, args);
  
  f2__global_scheduler__add_thread_serial(cause, new_thread);
  resume_gc();
  return new_thread;
}

// sequence (array, list, doublelist, etc.)

u64 raw__length(f2ptr cause, f2ptr seq) {
  if (!seq) {return 0;}
  switch (f2ptype__raw(seq, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__consp(seq, cause)) {
      u64 count = 0;
      f2ptr iter = seq;
      while(iter) {
	count ++;
	iter = f2cons__cdr(iter, cause);
      }
      return count;
    } else {
      return raw__array__length(cause, seq);
    }
  case ptype_chunk:  return f2chunk__length( seq, cause);
  case ptype_symbol: return f2symbol__length(seq, cause);
  case ptype_string: return f2string__length(seq, cause);
  default:
    error(nil, "raw__length error: invalid type");
    break;
  }
}

f2ptr f2__length(f2ptr cause, f2ptr seq) {
  if (!seq) {return f2integer__new(cause, 0);}
  switch (f2ptype__raw(seq, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__consp(seq, cause)) {
      u64 count = 0;
      f2ptr iter = seq;
      while(iter && raw__consp(iter, cause)) {
	count ++;
	iter = f2cons__cdr(iter, cause);
      }
      if (iter) {
	count += f2__length(cause, iter);
      }
      return f2integer__new(cause, count);
    } else if (raw__doublelinkp(seq, cause)) {
      u64 count = 0;
      if (seq) {
	{
	  f2ptr iter = seq;
	  while (iter && raw__doublelinkp(iter, cause)) {
	    count ++;
	    iter = f2doublelink__prev(iter, cause);
	  }
	  if (iter) {
	    count += f2__length(cause, iter);
	  }
	}
	{
	  f2ptr iter = f2doublelink__next(seq, cause);
	  while (iter && raw__doublelinkp(iter, cause)) {
	    count ++;
	    iter = f2doublelink__next(iter, cause);
	  }
	  if (iter) {
	    count += f2__length(cause, iter);
	  }
	}
      }
      return f2integer__new(cause, count);
    } else {
      return f2__array__length(cause, seq);
    }
  case ptype_chunk:  return f2integer__new(cause, f2chunk__length(seq, cause));
  case ptype_string: return f2integer__new(cause, f2string__length(seq, cause));
  case ptype_symbol: return f2integer__new(cause, f2symbol__length(seq, cause));
  default:
    return f2integer__new(cause, 1);
  }
}
def_pcfunk1(length, seq, return f2__length(this_cause, seq));

f2ptr raw__seq_elt(f2ptr this, f2ptr index, f2ptr cause) {
  if (! this) {
    printf ("\nseq_elt error: this argument is nil (must be cons, array, or chunk)."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, this);
  }
  if ((! index) || (! raw__integerp(index, cause))) {
    printf ("\nseq_elt error: index argument must be integer."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, index);
  }
  int raw_index = f2integer__i(index, cause);
  if (raw_index < 0) {
    printf("\nseq_elt error: index less than zero."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, index);
  }
  switch (f2ptype__raw(this, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__consp(this, cause)) {
      int count = f2integer__i(index, cause);
      f2ptr iter = this;
      while(count > 0) {
	count --;
	iter = f2cons__cdr(iter, cause);
	if (!iter || !raw__consp(iter, cause)) {
	  printf ("\nseq_elt error: list index out of range."); fflush(stdout);
	  return f2larva__new(cause, 1);
	  //return f2__argument_type_check_failure__exception__new(cause, index);
	}
      }
      return f2cons__car(iter, cause);
    } else {
      if (raw_index >= raw__array__length(cause, this)) {
	printf("\nseq_elt error: array index out of range."); fflush(stdout);
	return f2larva__new(cause, 1);
	//return f2__argument_type_check_failure__exception__new(cause, index);
      }
    }
    return raw__array__elt(cause, this, raw_index);
  case ptype_chunk:
    if (raw_index >= f2chunk__length(this, cause)) {
      printf("\nseq_elt error: chunk index out of range."); fflush(stdout);
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    return f2integer__new(cause, f2chunk__bit8__elt(this, raw_index, cause));
  default:
    printf("\nseq_elt error: sequence must be cons, array, or chunk."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, this); // should return exception (once exceptions are defined)
    break;
  }
}

// primobject cfunk

boolean_t raw__cfunkp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_cfunk(x, cause));}

// primobject funk

boolean_t raw__funkp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_funk(x, cause));}

// primobject metro

boolean_t raw__metrop(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_metro(x, cause));}

// primobject metrocfunk

boolean_t raw__metrocfunkp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_metrocfunk(x, cause));}

// primobject bytecode

boolean_t raw__bytecodep(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_bytecode(x, cause));}

// primobject cause

boolean_t raw__causep(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_cause(x, cause));}

// primobject hashtable

// primobject thought_process

boolean_t raw__thought_processp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_thought_process(x, cause));}

// primobject thread

boolean_t raw__threadp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_thread(x, cause));}

// primobject exception

boolean_t raw__exceptionp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_exception(x, cause));}

f2ptr f2__exception(f2ptr cause, f2ptr tag, f2ptr value) {return f2exception__new(cause, tag, value);}
def_pcfunk2(exception, tag, value, return f2__exception(this_cause, tag, value));

// primobject circular_buffer

def_pcfunk1(circular_bufferp,        x,    return f2__circular_bufferp(x, this_cause));
f2ptr f2__circular_buffer(f2ptr cause, f2ptr length) {
  if (! raw__integerp(length, cause)) {return f2larva__new(cause, 1);}
  return raw__circular_buffer__new_empty(cause, f2integer__i(length, cause));
}
def_pcfunk1(circular_buffer,         x,    return f2__circular_buffer(this_cause, x));
def_pcfunk2(circular_buffer__add,    x, y, return f2__circular_buffer__add(   this_cause, x, y));
def_pcfunk1(circular_buffer__remove, x,    return f2__circular_buffer__remove(this_cause, x));

def_pcfunk1(exp__print, x, return f2__exp__print(this_cause, x));
def_pcfunk1(write, x, return f2__write(this_cause, x));
def_pcfunk2(fwrite, fptr, x, return f2__fwrite(this_cause, fptr, x));

f2ptr f2__format(f2ptr cause, f2ptr stream, f2ptr exp) {
  if (! raw__streamp(stream, cause)) {
    printf("\nraw__format error: stream must be stream.");
    f2__print(cause, stream);
    return f2larva__new(cause, 1);
    //return nil;
  }
  if (! exp) {
    f2__fwrite__raw_char(cause, stream, '[', NULL, nil);
    f2__fwrite__raw_char(cause, stream, ']', NULL, nil);
  } else {
    switch(f2ptype__raw(exp, cause)) {
    case ptype_string:f2__fwrite__raw_string(cause, stream, exp, nil); break;
    default:          f2__fwrite(            cause, stream, exp     ); break;
    }
  }
  return exp;
}
def_pcfunk2(exp__format, fptr, x, return f2__format(this_cause, fptr, x));

f2ptr f2__format__html(f2ptr cause, f2ptr stream, f2ptr exp) {
  if (! raw__streamp(stream, cause)) {
    printf("\nraw__format error: stream must be stream.");
    f2__print(cause, stream);
    return f2larva__new(cause, 1);
    //return nil;
  }
  if (! exp) {
    f2__fwrite__raw_char(cause, stream, '[', NULL, __funk2.globalenv.true__symbol);
    f2__fwrite__raw_char(cause, stream, ']', NULL, __funk2.globalenv.true__symbol);
  } else {
    switch(f2ptype__raw(exp, cause)) {
    case ptype_string:f2__fwrite__raw_string(cause, stream, exp, __funk2.globalenv.true__symbol); break;
    default:          f2__fwrite_html(       cause, stream, exp                                ); break;
    }
  }
  return exp;
}
def_pcfunk2(exp__format__html, stream, x, return f2__format__html(this_cause, stream, x));

def_pcfunk2(exp__fwrite_html, stream, exp, return f2__fwrite_html(this_cause, stream, exp));

f2ptr f2__list(f2ptr cause, f2ptr seq) {
  //debug_memory_test();
  if (! seq) {return nil;}
  if (! raw__consp(seq, cause)) {
    printf("\nlist error: sequence must be type cons."); fflush(stdout);
    return f2__argument_type_check_failure__exception__new(cause, seq);
  }
  f2ptr new_cons = f2cons__new(cause, f2cons__car(seq, cause), nil);
  f2ptr new_seq  = new_cons;
  f2ptr new_iter = new_cons;
  f2ptr iter     = f2cons__cdr(seq, cause);
  while(iter) {
    release__assert(raw__consp(iter, cause), nil, "args cons type check failure in list.");
    new_cons = f2cons__new(cause, f2cons__car(iter, cause), nil);
    release__assert(raw__consp(new_cons, cause), nil, "new cons type check failure in list.");
    f2cons__cdr__set(new_iter, cause, new_cons);
    iter     = f2cons__cdr(iter, cause);
    new_iter = new_cons;
  }
  //debug_memory_test();
  return new_seq;
}
def_pcfunk0_and_rest(list, seq, return f2__list(this_cause, seq));

void raw__exit(int value) {
  status("funk2: exit.");
#ifdef DEBUG
  print_bytecode_stats(stdout);
  print_gc_stats();
#endif // DEBUG
  f2__destroy();
  status("funk2 exit: exiting.");
  exit(value);
}
f2ptr f2__quit(f2ptr cause, f2ptr value) {
  if (raw__integerp(value, cause)) {
    raw__exit(f2integer__i(cause, value));
  } else {
    raw__exit((int)value);
  }
  printf("\nfunk2 error: shouldn't get here at exit.\n");
  return f2larva__new(cause, 1);
  //exit(-1);
}
def_pcfunk0(quit, f2__quit(this_cause, nil); return nil);

def_pcfunk0(system_microseconds_since_1970, return f2__system_microseconds_since_1970(this_cause));

f2ptr f2__seq_elt__set(f2ptr this, f2ptr index, f2ptr cause, f2ptr value) {
  if (!this || !index || ! raw__integerp(index, cause)) {
    printf("\nseq_elt-set error: argument type check failure."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, this);
  }
  int raw_index = f2integer__i(index, cause);
  if (raw_index < 0) {
    printf("\nseq_elt-set error: index out of range."); fflush(stdout);
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, index);
  }
  switch (f2ptype__raw(this, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__consp(this, cause)) {
      int count = f2integer__i(index, cause);
      f2ptr iter = this;
      while(count > 0) {
	count --;
	iter = f2cons__cdr(iter, cause);
	if (!iter || !raw__consp(iter, cause)) {
	  printf ("\nseq_elt-set error: list index out of range."); fflush(stdout);
	  return f2larva__new(cause, 1);
	  //return f2__argument_type_check_failure__exception__new(cause, index);
	}
      }
      f2cons__car__set(iter, cause, value);
      return nil;
    } else {
      if (raw_index >= raw__array__length(cause, this)) {
	printf("\nseq_elt-set error: array index out of range."); fflush(stdout); 
	return f2larva__new(cause, 1);
	//return f2__argument_type_check_failure__exception__new(cause, index);
      }
    }
    raw__array__elt__set(cause, this, raw_index, value);
    return nil;
  case ptype_chunk:
    if (raw_index >= f2chunk__length(this, cause)) {
      printf("\nseq_elt-set error: chunk index out of range."); fflush(stdout); 
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    if ((! value) || (! raw__integerp(value, cause))) {
      printf("\nseq_elt-set error: chunk value must be integer."); fflush(stdout); 
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    f2chunk__bit8__elt__set(this, raw_index, cause, f2integer__i(value, cause));
    return nil;
  default:
    printf("\nseq_elt-set error: sequence must be list, array, or chunk."); fflush(stdout); 
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, this); // should return exception (once exceptions are defined)
    //break;
  }
}

def_pcfunk4(bytecode, command, arg0, arg1, arg2,
	    printf("\ncreating user bytecode! "); fflush(stdout);
	    return f2bytecode__new(this_cause, command, arg0, arg1, arg2));

def_pcfunk1(debug, value,
	   printf("\ndebug: "); f2__write(nil, value); fflush(stdout);
	   return value);

def_pcfunk1(trace, value,
	   f2thread__trace__set(simple_thread, this_cause, f2cons__new(this_cause, value, f2thread__trace(simple_thread, this_cause)));
	   return value);

boolean_t raw__eq(f2ptr cause, f2ptr x, f2ptr y) {
  if (x == y) {return 1;}
  if (!x || !y) {return 0;}
  if (f2ptype__raw(x, cause) != f2ptype__raw(y, cause)) {return 0;}
  switch(f2ptype__raw(x, cause)) {
  case ptype_symbol:
    return f2__symbol__eq(cause, x, y);
  case ptype_integer:
    return (f2integer__i(x, cause) == f2integer__i(y, cause));
  case ptype_pointer:
    return (f2pointer__p(x, cause) == f2pointer__p(y, cause));
  case ptype_char:
    return (f2char__ch(x, cause) == f2char__ch(y, cause));
  case ptype_string:
    return f2__string__eq(cause, x, y);
  case ptype_simple_array:
    return (x == y);
  case ptype_traced_array:
    return (x == y);
  case ptype_chunk:
    return (x == y);
  default:
    error(nil, "shouldn't ever get here.");
  }
  error(nil, "eq error: argument type check failure."); fflush(stdout); 
  //return f2__argument_type_check_failure__exception__new(nil, x);
}

f2ptr f2__eq(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(raw__eq(cause, x, y));}
def_pcfunk2(eq, x, y, return f2__eq(this_cause, x, y));

f2ptr f2__fopen(f2ptr cause, f2ptr filename, f2ptr mode) {
  if (!raw__stringp(filename, cause) || !raw__stringp(mode, cause)) {
    error(nil, "fopen error: filename and mode must both be strings.");
    return f2larva__new(cause, 1);
    //return nil;
  }
  int filename_length = f2string__length(filename, cause);
  char* filename_str = (char*)from_ptr(f2__malloc(filename_length + 1));
  f2string__str_copy(filename, cause, (u8*)filename_str);
  filename_str[filename_length] = 0;
  int mode_length = f2string__length(mode, cause);
  char* mode_str = (char*)from_ptr(f2__malloc(mode_length + 1));
  f2string__str_copy(mode, cause, (u8*)mode_str);
  mode_str[mode_length] = 0;
  f2ptr fptr = f2pointer__new(cause, to_ptr(fopen(filename_str, mode_str)));
  f2__free(to_ptr(filename_str));
  f2__free(to_ptr(mode_str));
  return fptr;
}
def_pcfunk2(fopen, filename, mode, return f2__fopen(this_cause, filename, mode));

f2ptr f2__fclose(f2ptr cause, f2ptr fptr) {
  if ((! fptr) || (! raw__pointerp(fptr, cause))) {
    printf("\nfclose error: fptr must be pointer.");
    return f2larva__new(cause, 1);
    return nil;
  }
  return f2integer__new(cause, fclose((FILE*)from_ptr(f2pointer__p(fptr, cause))));
}
def_pcfunk1(fclose, fptr, return f2__fclose(this_cause, fptr));

f2ptr f2__compile(f2ptr cause, f2ptr thread, f2ptr exp, f2ptr protect_environment) {
  boolean_t is_funktional = boolean__true;
  return raw__compile(cause, thread, exp, (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL);
}
def_pcfunk2(compile, exp, protect_environment, return f2__compile(this_cause, simple_thread, exp, protect_environment));

f2ptr f2__identity(f2ptr cause, f2ptr exp) {return exp;}
def_pcfunk1(identity, exp, return f2__identity(this_cause, exp));

f2ptr f2__make_funk(f2ptr cause, f2ptr thread, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional) {
  //f2__print_prompt("make-funk args: ", args);
  //f2__print_prompt("  body        : ", body);
  //f2__print_prompt("  env         : ", f2thread__env(simple_thread));
  //f2__print_prompt("  tracewrap   : ", tracewrap);
  f2ptr funk = f2funk__new(cause, name, bytecodes, args, demetropolized_body, body, f2thread__env(thread, cause), nil, is_funktional);
  f2ptr result = f2__compile__funk(cause, thread, funk);
  if (raw__larvap(result, cause)) {
    return result;
  }
  //f2funk__machine_code__set(funk, this_cause, f2chunk__new_compiled_from_funk(this_cause, funk));
  return funk;
}
def_pcfunk6(make_funk, name, args, demetropolized_body, body, bytecodes, is_funktional, return f2__make_funk(this_cause, simple_thread, name, args, demetropolized_body, body, bytecodes, is_funktional));

f2ptr f2__make_metro(f2ptr cause, f2ptr thread, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional) {
  //f2__print_prompt("make-metro args: ", args);
  //f2__print_prompt("  body         : ", body);
  //f2__print_prompt("  env          : ", f2thread__env(simple_thread));
  //f2__print_prompt("  tracewrap    : ", tracewrap);
  f2ptr metro = f2metro__new(cause, name, bytecodes, args, demetropolized_body, body, f2thread__env(thread, cause), nil, is_funktional);
  f2ptr result = f2__compile__metro(cause, thread, metro);
  if (raw__larvap(result, cause)) {
    return result;
  }
  
  // metro machine code compiling bug...  temporarily disabled.
  //f2metro__machine_code__set(metro, this_cause, f2chunk__new_compiled_from_metro(this_cause, metro));
  
  return metro;
}
def_pcfunk6(make_metro, name, args, demetropolized_body, body, bytecodes, is_funktional, return f2__make_metro(this_cause, simple_thread, name, args, demetropolized_body, body, bytecodes, is_funktional));

f2ptr f2__cfunk__apply(f2ptr cause, f2ptr cfunk, f2ptr thread, f2ptr args) {
  release__assert(raw__cfunkp(cfunk, cause),        nil, "cfunk failed type assertion.");
  release__assert(raw__threadp(thread, cause),      nil, "thread failed type assertion.");
  release__assert(!args || raw__consp(args, cause), nil, "args failed type assertion.");
  if (!f2cfunk__cfunkptr(cfunk, cause)) {
    printf("\ncfunk-apply error: cfunkptr object was null for cfunk.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, cfunk);
  }
  ptr cfunk_ptr = f2pointer__p(f2cfunk__cfunkptr(cfunk, cause), cause);
  if (!cfunk_ptr) {
    printf("\ncfunk-apply error: cfunk_ptr was null for cfunk.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, cfunk);
  }
  return ((cfunkptr_t)(from_ptr(cfunk_ptr)))(cause, thread, f2cfunk__env(cfunk, cause), args);
}
def_pcfunk3(cfunk__apply, x, y, z, return f2__cfunk__apply(this_cause, x, y, z));

f2ptr f2__metrocfunk__apply(f2ptr cause, f2ptr metrocfunk, f2ptr thread, f2ptr args) {
  release__assert(raw__metrocfunkp(metrocfunk, cause), nil, "metrocfunk failed type assertion.");
  release__assert(raw__threadp(thread, cause),         nil, "thread failed type assertion.");
  release__assert(raw__consp(args, cause),             nil, "args failed type assertion.");
  return ((cfunkptr_t)from_ptr(f2pointer__p(f2metrocfunk__cfunkptr(metrocfunk, cause), cause)))(cause, thread, f2metrocfunk__env(metrocfunk, cause), args);
}
def_pcfunk3(metrocfunk__apply, x, y, z, return f2__metrocfunk__apply(this_cause, x, y, z));

#define PRIME_NUMBER__16_BIT 65521

f2ptr f2__random(f2ptr cause, f2ptr max_value) {
  if ((! max_value) || (! raw__integerp(max_value, cause))) {
    printf("\n[random max_value] error: max_value must be integer.");
    return f2larva__new(cause, 1);
  }
  int raw_max_value = f2integer__i(max_value, cause);
  int random_value = (uint)(rand() * PRIME_NUMBER__16_BIT) % raw_max_value;
  random_value = (random_value < 0) ? (-random_value) : random_value;
  return f2integer__new(cause, random_value % max_value);
}
def_pcfunk1(random, max_value, return f2__random(this_cause, max_value));

f2ptr f2__array__new_1d(f2ptr cause, f2ptr length, f2ptr and_rest) {
  if ((! length) || (! raw__integerp(length, cause))) {
    printf("\n[array_1d length &opt init] error: length must be integer.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, nil);
  }
  int raw_length = f2integer__i(length, cause);
  f2ptr init = nil;
  //printf ("\nand_rest: "); fflush(stdout); f2__print(simple_thread, and_rest); fflush(stdout);
  if (and_rest) {
    init = f2cons__car(and_rest, cause);
    if (!init || !raw__arrayp(init, cause)) {
      printf("\n[array length :rest init] error: init must be array (or not included)."); fflush(stdout);
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
    if (raw__array__length(init, cause) < raw_length) {
      printf("\n[array length :rest init] error: init must be longer or equal in length to length."); fflush(stdout);
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
  }
  if (init) {return raw__array__new_copy(cause, raw_length, init);}
  else      {return raw__array__new(cause, raw_length);}
}
def_pcfunk1_and_rest(array__new_1d, length, and_rest, return f2__array__new_1d(this_cause, length, and_rest));

f2ptr f2__array(f2ptr cause, f2ptr and_rest) {
  f2ptr iter = and_rest;
  int rest_length = 0;
  while (iter) {
    rest_length ++;
    iter = f2cons__cdr(iter, cause);
  }
  f2ptr this = raw__array__new(cause, rest_length);
  int i = 0;
  iter = and_rest;
  while (iter) {
    f2ptr car = f2cons__car(iter, cause);
    raw__array__elt__set(cause, this, i, car);
    i ++;
    iter = f2cons__cdr(iter, cause);
  }
  return this;
}
def_pcfunk0_and_rest(array, and_rest, return f2__array(this_cause, and_rest));

f2ptr f2__chunk_copy(f2ptr cause, f2ptr init) {
  if ((! init) || (! raw__chunkp(init, cause))) {
    printf("\n[chunk-copy init] error: init must be chunk.");
    return f2larva__new(cause, 1);
  }
  return f2chunk__new_copy(cause, init);
}
def_pcfunk1(chunk__copy, init, return f2__chunk_copy(this_cause, init));

f2ptr f2__chunk__read_bit8(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((u8)f2chunk__bit8__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit8, chunk, offset, return f2__chunk__read_bit8(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit8_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit8__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit8_integer, chunk, offset, value, return f2__chunk__write_bit8_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit8_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((char)f2chunk__bit8__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit8_signed, chunk, offset, return f2__chunk__read_bit8_signed(this_cause, chunk, offset));

f2ptr f2__chunk__read_bit16(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, f2chunk__bit16__elt(chunk, f2integer__i(offset, cause), cause));}
def_pcfunk2(chunk__read_bit16, chunk, offset, return f2__chunk__read_bit16(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit16_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit16__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit16_integer, chunk, offset, value, return f2__chunk__write_bit16_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit16_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((s16)f2chunk__bit16__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit16_signed, chunk, offset, return f2__chunk__read_bit16_signed(this_cause, chunk, offset));

f2ptr f2__chunk__read_bit32(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((u32)f2chunk__bit32__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit32, chunk, offset, return f2__chunk__read_bit32(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit32_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit32__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit32_integer, chunk, offset, value, return f2__chunk__write_bit32_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit32_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((short)f2chunk__bit32__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit32_signed, chunk, offset, return f2__chunk__read_bit32_signed(this_cause, chunk, offset));

def_pcfunk1(demetropolize_once, exp, return f2__demetropolize_once(this_cause, simple_thread, simple_env, exp));

f2ptr f2__demetropolize_full(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp) {return f2cons__cdr(f2__demetropolize_full__with_status(cause, thread, env, exp), cause);}
def_pcfunk1(demetropolize_full, exp, return f2__demetropolize_full(this_cause, simple_thread, simple_env, exp));

def_pcfunk0(this__cause,  return this_cause);
def_pcfunk0(this__thread, return simple_thread);
def_pcfunk0(this__env,    return simple_env);
def_pcfunk0(this__args,   return simple_args);

f2ptr f2__exps_demetropolize_full(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp) {
  if (!exp) {return nil;}
  if (!raw__consp(exp, cause)) {
    printf("\nexps-demetropolize_full error: exp type must be list.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
  return f2cons__new(cause,
		     f2cons__cdr(f2__demetropolize_full__with_status(cause, thread, env, f2cons__car(exp, cause)), cause),
		     f2__exps_demetropolize_full(cause, thread, env, f2cons__cdr(exp, cause)));
}

def_pcfunk1(exps_demetropolize_full, exp,
	    return f2__exps_demetropolize_full(this_cause, simple_thread, simple_env, exp));

def_pcfunk2(compile__special_symbol_exp, exp, protect_environment,
	    return f2__compile__special_symbol_exp(this_cause, simple_thread, exp, (protect_environment != nil), (protect_environment == nil), NULL, NULL, nil, NULL));

f2ptr f2__lookup_funkvar(f2ptr cause, f2ptr env, f2ptr funkvar, f2ptr undefined_value) {
  f2ptr value = environment__lookup_funkvar_value(cause, env, funkvar);
  if (raw__larvap(value, cause)) {return undefined_value;}
  return value;
}
def_pcfunk2(lookup_funkvar, funkvar, undefined_value, return f2__lookup_funkvar(this_cause, simple_env, funkvar, undefined_value));

extern f2ptr __wrong_argument_number__bcs; // this is like an interrupt pointer (defined in compile.c)

f2ptr f2__wrong_argument_number_error__set(f2ptr cause, f2ptr error_bcs) {
  __wrong_argument_number__bcs = error_bcs;
  return nil;
}
def_pcfunk1(wrong_argument_number_error__set, error_bcs, return f2__wrong_argument_number_error__set(this_cause, error_bcs));

f2ptr f2__jump_to_chunk(f2ptr cause, f2ptr thread, f2ptr env, f2ptr exp, f2ptr args) {
  if((! exp)) {
    printf("\njump-to-pointer error: exp is nil."); 
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
  switch(f2ptype__raw(exp, cause)) {
  case ptype_pointer: {
    cfunkptr_t jump = (cfunkptr_t)from_ptr(f2pointer__p(exp, cause));
    return jump(cause, thread, env, args);
  }
  case ptype_chunk:
    return f2chunk__cfunk_jump(exp, cause, thread, env, args);
  default:
    printf("\njump-to-pointer error: exp must be pointer or chunk.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
}
def_pcfunk2(jump_to_chunk, p, args, return f2__jump_to_chunk(this_cause, simple_thread, simple_env, p, args));

f2ptr f2__coerce_to_int(f2ptr cause, f2ptr exp) {
  if(! exp) {
    printf("\ncoerce-to-int error: exp is nil.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
  switch(f2ptype__raw(exp, cause)) {
  case ptype_integer: return exp;
  case ptype_pointer: return f2integer__new(cause, (long)f2pointer__p(exp, cause));
  default:
    printf("\ncoerce-to-int error: exp must be integer or pointer.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
}
def_pcfunk1(coerce_to_int, exp, return f2__coerce_to_int(this_cause, exp));

f2ptr f2__memory_image__save(f2ptr cause, f2ptr filename) {
  char* str = (char*)from_ptr(f2__malloc(f2string__length(filename, cause)));
  f2string__str_copy(filename, cause, (u8*)str);
  f2ptr retval = f2bool__new(raw__memory_image__save(str));
  f2__free(to_ptr(str));
  return retval;
}
def_pcfunk1(memory_image__save, filename, return f2__memory_image__save(this_cause, filename));

f2ptr f2__memory_image__load(f2ptr cause, f2ptr filename) {
  char* str = (char*)from_ptr(f2__malloc(f2string__length(filename, cause)));
  f2string__str_copy(filename, cause, (u8*)str);
  f2ptr retval = f2bool__new(raw__memory_image__load(str));
  f2__free(to_ptr(str));
  return retval;
}
def_pcfunk1(memory_image__load, filename, return f2__memory_image__load(this_cause, filename));

def_pcfunk1(funkall__raw_c_funk__v__v,      cfunk_ptr,                                                                  (* (void   (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(); return nil);
def_pcfunk2(funkall__raw_c_funk__v__i,      cfunk_ptr, a0,                                                              (* (void   (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ii,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__iid,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(int,    int,    double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2double__d(a2, this_cause));  return nil);
def_pcfunk4(funkall__raw_c_funk__v__iii,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iiii,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iiip,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(int,    int,    int,    ptr))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2pointer__p(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__iiiip,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(int,    int,    int,    int,    ptr))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2pointer__p(a4, this_cause)); return nil);
def_pcfunk7(funkall__raw_c_funk__v__iiiiip, cfunk_ptr, a0, a1, a2, a3, a4, a5,                                          (* (void   (*)(int,    int,    int,    int,    int,    ptr))  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause), f2pointer__p(a5, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__id,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(int,    double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__idd,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(int,    double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iddd,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(int,    double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__idddd,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(int,    double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ip,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause))); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ipp,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))); return nil);
def_pcfunk5(funkall__raw_c_funk__v__ippp,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(int,    void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ipppp,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(int,    void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause))); return nil);
def_pcfunk2(funkall__raw_c_funk__v__p,      cfunk_ptr, a0,                                                              (* (void   (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause))); return nil);
def_pcfunk3(funkall__raw_c_funk__v__pi,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(void*,  int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), f2integer__i(a1, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__pp,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause))); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ppp,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))); return nil);
def_pcfunk5(funkall__raw_c_funk__v__pppp,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ppppp,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(void*,  void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause))); return nil);
def_pcfunk2(funkall__raw_c_funk__v__d,      cfunk_ptr, a0,                                                              (* (void   (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__dd,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ddd,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__dddd,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause)); return nil);
def_pcfunk2(funkall__raw_c_funk__v__f,      cfunk_ptr, a0,                                                              (* (void   (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ff,     cfunk_ptr, a0, a1,                                                          (* (void   (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__fff,    cfunk_ptr, a0, a1, a2,                                                      (* (void   (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__ffff,   cfunk_ptr, a0, a1, a2, a3,                                                  (* (void   (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__fffff,  cfunk_ptr, a0, a1, a2, a3, a4,                                              (* (void   (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause)); return nil);
def_pcfunk1(funkall__raw_c_funk__i__v,      cfunk_ptr,                         return f2integer__new(this_cause,        (* (int    (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__i__i,      cfunk_ptr, a0,                     return f2integer__new(this_cause,        (* (int    (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__ii,     cfunk_ptr, a0, a1,                 return f2integer__new(this_cause,        (* (int    (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__iii,    cfunk_ptr, a0, a1, a2,             return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__iiii,   cfunk_ptr, a0, a1, a2, a3,         return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk7(funkall__raw_c_funk__i__iiiiip, cfunk_ptr, a0, a1, a2, a3, a4, a5, return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int,    int,    void*))from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause), from_ptr(f2pointer__p(a5, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__i__ip,     cfunk_ptr, a0, a1,                 return f2integer__new(this_cause,        (* (int    (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)))));
def_pcfunk4(funkall__raw_c_funk__i__ipp,    cfunk_ptr, a0, a1, a2,             return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)))));
def_pcfunk5(funkall__raw_c_funk__i__ippp,   cfunk_ptr, a0, a1, a2, a3,         return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)))));
def_pcfunk6(funkall__raw_c_funk__i__ipppp,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause)))));
def_pcfunk2(funkall__raw_c_funk__i__p,      cfunk_ptr, a0,                     return f2integer__new(this_cause,        (* (int    (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__i__pp,     cfunk_ptr, a0, a1,                 return f2integer__new(this_cause,        (* (int    (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)))));
def_pcfunk4(funkall__raw_c_funk__i__ppp,    cfunk_ptr, a0, a1, a2,             return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)))));
def_pcfunk5(funkall__raw_c_funk__i__pppp,   cfunk_ptr, a0, a1, a2, a3,         return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)))));
def_pcfunk6(funkall__raw_c_funk__i__ppppp,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause)))));
def_pcfunk2(funkall__raw_c_funk__i__d,      cfunk_ptr, a0,                     return f2integer__new(this_cause,        (* (int    (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__dd,     cfunk_ptr, a0, a1,                 return f2integer__new(this_cause,        (* (int    (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__ddd,    cfunk_ptr, a0, a1, a2,             return f2integer__new(this_cause,        (* (int    (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__dddd,   cfunk_ptr, a0, a1, a2, a3,         return f2integer__new(this_cause,        (* (int    (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2integer__new(this_cause,        (* (int    (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__i__f,      cfunk_ptr, a0,                     return f2integer__new(this_cause,        (* (int    (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__ff,     cfunk_ptr, a0, a1,                 return f2integer__new(this_cause,        (* (int    (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__fff,    cfunk_ptr, a0, a1, a2,             return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__ffff,   cfunk_ptr, a0, a1, a2, a3,         return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__fffff,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__d__v,      cfunk_ptr,                         return f2double__new(this_cause,         (* (double (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__d__i,      cfunk_ptr, a0,                     return f2double__new(this_cause,         (* (double (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__ii,     cfunk_ptr, a0, a1,                 return f2double__new(this_cause,         (* (double (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__iii,    cfunk_ptr, a0, a1, a2,             return f2double__new(this_cause,         (* (double (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__iiii,   cfunk_ptr, a0, a1, a2, a3,         return f2double__new(this_cause,         (* (double (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2double__new(this_cause,         (* (double (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__d__d,      cfunk_ptr, a0,                     return f2double__new(this_cause,         (* (double (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__dd,     cfunk_ptr, a0, a1,                 return f2double__new(this_cause,         (* (double (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__ddd,    cfunk_ptr, a0, a1, a2,             return f2double__new(this_cause,         (* (double (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__dddd,   cfunk_ptr, a0, a1, a2, a3,         return f2double__new(this_cause,         (* (double (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2double__new(this_cause,         (* (double (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__d__f,      cfunk_ptr, a0,                     return f2double__new(this_cause,         (* (double (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__ff,     cfunk_ptr, a0, a1,                 return f2double__new(this_cause,         (* (double (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__fff,    cfunk_ptr, a0, a1, a2,             return f2double__new(this_cause,         (* (double (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__ffff,   cfunk_ptr, a0, a1, a2, a3,         return f2double__new(this_cause,         (* (double (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__fffff,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2double__new(this_cause,         (* (double (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__f__v,      cfunk_ptr,                         return f2float__new(this_cause,          (* (float  (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__f__i,      cfunk_ptr, a0,                     return f2float__new(this_cause,          (* (float  (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__ii,     cfunk_ptr, a0, a1,                 return f2float__new(this_cause,          (* (float  (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__iii,    cfunk_ptr, a0, a1, a2,             return f2float__new(this_cause,          (* (float  (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__iiii,   cfunk_ptr, a0, a1, a2, a3,         return f2float__new(this_cause,          (* (float  (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2float__new(this_cause,          (* (float  (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__f__d,      cfunk_ptr, a0,                     return f2float__new(this_cause,          (* (float  (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__dd,     cfunk_ptr, a0, a1,                 return f2float__new(this_cause,          (* (float  (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__ddd,    cfunk_ptr, a0, a1, a2,             return f2float__new(this_cause,          (* (float  (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__dddd,   cfunk_ptr, a0, a1, a2, a3,         return f2float__new(this_cause,          (* (float  (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2float__new(this_cause,          (* (float  (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__f__f,      cfunk_ptr, a0,                     return f2float__new(this_cause,          (* (float  (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__ff,     cfunk_ptr, a0, a1,                 return f2float__new(this_cause,          (* (float  (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__fff,    cfunk_ptr, a0, a1, a2,             return f2float__new(this_cause,          (* (float  (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__ffff,   cfunk_ptr, a0, a1, a2, a3,         return f2float__new(this_cause,          (* (float  (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__fffff,  cfunk_ptr, a0, a1, a2, a3, a4,     return f2float__new(this_cause,          (* (float  (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__p__v,      cfunk_ptr,                         return f2pointer__new(this_cause, to_ptr((* (void*  (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )())));
def_pcfunk2(funkall__raw_c_funk__p__i,      cfunk_ptr, a0,                     return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__p__ip,     cfunk_ptr, a0, a1,                 return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause))))));
def_pcfunk4(funkall__raw_c_funk__p__ipp,    cfunk_ptr, a0, a1, a2,             return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))))));
def_pcfunk2(funkall__raw_c_funk__p__p,      cfunk_ptr, a0,                     return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause))))));
def_pcfunk3(funkall__raw_c_funk__p__pp,     cfunk_ptr, a0, a1,                 return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause))))));
def_pcfunk4(funkall__raw_c_funk__p__ppp,    cfunk_ptr, a0, a1, a2,             return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))))));
def_pcfunk5(funkall__raw_c_funk__p__pppp,   cfunk_ptr, a0, a1, a2, a3,         return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))))));

def_pcfunk0(repl, return f2integer__new(this_cause, f2__repl(this_cause, simple_thread)));

def_pcfunk2(tensor__new_from_array_of_integer_dimensions, dimensions, fill_element, return f2__tensor__new_from_array_of_integer_dimensions(this_cause, dimensions, fill_element));
def_pcfunk2(tensor__elt_from_array_of_integer_indices,    this, indices,            return f2tensor__elt_from_array_of_integer_indices(this, indices, this_cause));

// f2_trace.c funktions

def_pcfunk3(trace__remember__microseconds_since_1970, this, microseconds_since_1970, remember_value__place,
	    f2ptr remember_value;
	    f2ptr trace_iter = raw__trace__remember__microseconds_since_1970( this_cause, this, f2integer__i(microseconds_since_1970, this_cause), &remember_value);
	    f2place__thing__set(remember_value__place, this_cause, remember_value);
	    return trace_iter);

def_pcfunk3(array__elt__remember__microseconds_since_1970, this, index, microseconds_since_1970,
	    return raw__array__elt__remember__microseconds_since_1970( this_cause, this, f2integer__i(index, this_cause), f2integer__i(microseconds_since_1970, this_cause)));

def_pcfunk2(exp__remember__microseconds_since_1970, exp, microseconds_since_1970,
	    return raw__exp__remember__microseconds_since_1970( this_cause, exp, f2integer__i(microseconds_since_1970, this_cause)));

def_pcfunk3(exp__remember__trans__microseconds_since_1970, exp, initial_microseconds, final_microseconds,
	    return raw__exp__remember__trans__microseconds_since_1970( this_cause, exp, f2integer__i(initial_microseconds, this_cause), f2integer__i(final_microseconds, this_cause)));

def_pcfunk2(array__tracing_on__set, this, tracing_on,
	    raw__array__tracing_on__set(this_cause, this, tracing_on != nil);
	    return nil);

def_pcfunk0(system__peer_command_server__port_num,
	    return f2integer__new(this_cause, __funk2.command_line.peer_command_server__port_num));

def_pcfunk0(system__gethostname,
	    char hostname[1024];
	    if (gethostname(hostname, 1023) != 0) {
	      return nil;
	    }
	    return f2string__new(this_cause, strlen(hostname), (u8*)hostname));

// funk2_node_handler

f2ptr f2__funk2_node_handler__know_of_node(f2ptr cause, f2ptr hostname, f2ptr port_num) {
  // note that this is not mutexed!
  if (! raw__stringp(hostname, cause)) {
    status("funk2_node_handler__know_of_node error: hostname must be a string.");
    return -1;
  }
  if (! raw__integerp(port_num, cause)) {
    status("funk2_node_handler__know_of_node error: port_num must be an integer.");
    return -2;
  }
  client_id_t client_id;
  int hostname__length = f2string__length(hostname, cause);
  char* hostname__str = alloca(hostname__length + 1);
  f2string__str_copy(hostname, cause, (u8*)hostname__str);
  hostname__str[hostname__length] = 0;
  struct hostent* host_entity = gethostbyname(hostname__str);
  if (host_entity == NULL) {
    status("couldn't lookup funk2 node with gethostbyname: '%s'\n", hostname__str);
    return -3;
  }
  u32 netorder_ip_addr = *((u32*)(host_entity->h_addr_list[0]));
  u32 hostorder_ip_addr = ntohl(netorder_ip_addr);
  u8 ip_addr[4];
  ip_addr[0] = ((u8*)(&hostorder_ip_addr))[3];
  ip_addr[1] = ((u8*)(&hostorder_ip_addr))[2];
  ip_addr[2] = ((u8*)(&hostorder_ip_addr))[1];
  ip_addr[3] = ((u8*)(&hostorder_ip_addr))[0];
  u16 port_num__i = f2integer__i(port_num, cause);
  client_id__init(&client_id, (u8*)"", ip_addr, port_num__i);
  computer_id_t computer_id = funk2_node_handler__add_node(&(__funk2.node_handler), 0, &client_id);
  status("added knowledge of funk2 node: '%s' %d.%d.%d.%d:%d", hostname__str, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port_num__i);
  return f2integer__new(cause, computer_id);
}

def_pcfunk2(funk2_node_handler__know_of_node, hostname, port_num, return f2__funk2_node_handler__know_of_node(this_cause, hostname, port_num));

void raw__send_request_register_peer(f2ptr cause, computer_id_t computer_id, node_id_t node_id, u8* ip_addr, u16 port_num) {
  funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
  status("sending request register peer packet [to computer_id=" u64__fstr "]: node_id=" u64__fstr " %d.%d.%d.%d:%d", (u64)computer_id, (u64)node_id, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port_num);
  send_packet__request__register_peer(cause, funk2_node, node_id, ip_addr, port_num);
}

f2ptr f2__send_request_register_peer(f2ptr cause, f2ptr computer_id, f2ptr node_id, f2ptr ip_addr, f2ptr port_num) {
  if (! raw__integerp(computer_id, cause)) {printf("\nf2__send_request_register_peer error: computer_id must be integer."); return f2larva__new(cause, 1);}
  if (! raw__pointerp(node_id,     cause)) {printf("\nf2__send_request_register_peer error: node_id must be pointer.");     return f2larva__new(cause, 1);}
  if (! raw__arrayp(ip_addr,       cause)) {printf("\nf2__send_request_register_peer error: ip_addr must be array.");       return f2larva__new(cause, 1);}
  if (! raw__integerp(port_num,    cause)) {printf("\nf2__send_request_register_peer error: port_num must be integer.");    return f2larva__new(cause, 1);}
  u8 u8_ip_addr[4];
  u8_ip_addr[0] = f2integer__i(raw__array__elt(cause, ip_addr, 0), cause);
  u8_ip_addr[1] = f2integer__i(raw__array__elt(cause, ip_addr, 1), cause);
  u8_ip_addr[2] = f2integer__i(raw__array__elt(cause, ip_addr, 2), cause);
  u8_ip_addr[3] = f2integer__i(raw__array__elt(cause, ip_addr, 3), cause);
  raw__send_request_register_peer(cause, f2integer__i(computer_id, cause), f2pointer__p(node_id, cause), u8_ip_addr, f2integer__i(port_num, cause));
  return nil;
}
def_pcfunk4(send_request_register_peer, computer_id, node_id, ip_addr, port_num, return f2__send_request_register_peer(this_cause, computer_id, node_id, ip_addr, port_num););

f2ptr f2__larva(f2ptr cause, f2ptr type) {
  if (! raw__integerp(type, cause)) {
    return f2larva__new(cause, 1);
  }
  u32 raw_type = f2integer__i(type, cause);
  return f2larva__new(cause, raw_type);
}

def_pcfunk1(larva, type, return f2__larva(this_cause, type));

// events

f2ptr f2__publish_event(f2ptr cause, f2ptr type, f2ptr data) {
  pthread_mutex_lock(&(__funk2.event_id_mutex));
  event_id_t event_id = __funk2.event_id;
  __funk2.event_id ++;
  pthread_mutex_unlock(&(__funk2.event_id_mutex));
  circular_buffer__write_result_t result = funk2_event_router__know_of_event(&(__funk2.event_router), cause, __funk2.node_id, event_id, type, data);
  if (result != circular_buffer__write_result__success) {
    return f2larva__new(cause, 13);
  }
  return nil;
}
def_pcfunk2(publish_event, type, data, return f2__publish_event(this_cause, type, data));

f2ptr f2__funkable__parent_env(f2ptr cause, f2ptr funkable) {
  if (raw__cfunkp(funkable, cause)) {
    return f2cfunk__env(funkable, cause);
  } else if (raw__funkp(funkable, cause)) {
    return f2funk__env(funkable, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}

f2ptr f2__event_subscriber(f2ptr cause, f2ptr parent_thread, f2ptr event_type, f2ptr funkable) {
  f2ptr parent_env         = f2__funkable__parent_env(cause, funkable);
  f2ptr thread             = f2thread__new(cause,
					   nil,
					   nil,
					   nil,
					   parent_env,
					   nil,
					   nil,
					   nil,
					   nil,
					   nil,
					   cause,
					   __funk2.globalenv.true__symbol,
					   nil,
					   parent_thread,
					   parent_env,
					   f2mutex__new(cause),
					   nil,
					   nil);
  f2ptr event_buffer       = raw__circular_buffer__new_empty(cause, 1024);
  f2ptr event_buffer_mutex = f2mutex__new(cause);
  f2ptr subscriber         = f2event_subscriber__new(cause, event_type, thread, funkable, event_buffer, event_buffer_mutex);
  return subscriber;
}
def_pcfunk2(event_subscriber, event_type, funkable, return f2__event_subscriber(this_cause, simple_thread, event_type, funkable));

f2ptr f2__subscribe(f2ptr cause, f2ptr thread, f2ptr event_types, f2ptr funkable) {
  if (! raw__consp(event_types, cause)) {
    event_types = f2cons__new(cause, event_types, nil);
  }
  f2ptr event_subscriber = f2__event_subscriber(cause, thread, event_types, funkable);
  if (cause && (! raw__causep(cause, cause))) {
    return f2larva__new(cause, 1);
  }
  {
    f2ptr subscribers_mutex = f2cause__subscribers_mutex(cause, cause);
    f2mutex__lock(subscribers_mutex, cause);
    f2ptr subscribers = f2cause__subscribers(cause, cause);
    f2ptr new_cons = f2cons__new(cause, event_subscriber, subscribers);
    f2cause__subscribers__set(cause, cause, new_cons);
    f2mutex__unlock(subscribers_mutex, cause);
  }
  {
    f2ptr subscribers_mutex = f2scheduler__event_subscribers_mutex(__funk2.operating_system.scheduler, cause);
    f2mutex__lock(subscribers_mutex, cause);
    f2ptr subscribers = f2scheduler__event_subscribers(__funk2.operating_system.scheduler, cause);
    f2ptr new_cons = f2cons__new(cause, event_subscriber, subscribers);
    f2scheduler__event_subscribers__set(__funk2.operating_system.scheduler, cause, new_cons);
    f2mutex__unlock(subscribers_mutex, cause);
  }
  //f2__print(cause, cause);
  return nil;
}
def_pcfunk2(subscribe, event_type, funkable, return f2__subscribe(this_cause, simple_thread, event_type, funkable));

f2ptr f2__thread__subversion_cause(f2ptr cause, f2ptr thread, f2ptr name) {
  f2ptr bytecode_tracing_on   = nil;
  f2ptr memory_tracing_on     = nil;
  f2ptr subscribers           = nil;
  f2ptr old_imagination_stack = nil;
  if (cause) {
    bytecode_tracing_on   = f2cause__bytecode_tracing_on(cause, cause);
    memory_tracing_on     = f2cause__memory_tracing_on(cause, cause);
    subscribers           = f2cause__subscribers(cause, cause);
    old_imagination_stack = f2cause__imagination_stack(cause, cause);
  }
  f2ptr new_cause = f2__cause__new(cause, bytecode_tracing_on, memory_tracing_on, subscribers, f2cons__new(cause, name, old_imagination_stack), nil, nil);
  f2thread__cause_reg__set(thread, cause, new_cause);
  return new_cause;
}
def_pcfunk2(thread__subversion_cause, thread, name, return f2__thread__subversion_cause(this_cause, thread, name));

f2ptr f2__first(f2ptr cause, f2ptr exp) {
  if (raw__consp(exp, cause)) {
    return f2cons__car(exp, cause);
  } else if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__value(exp, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk1(first, exp, return f2__first(this_cause, exp));

f2ptr f2__first__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__consp(exp, cause)) {
    return f2cons__car__set(exp, cause, value);
  } else if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__value__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk2(first__set, exp, value, return f2__first__set(this_cause, exp, value));

f2ptr f2__next(f2ptr cause, f2ptr exp) {
  if (raw__consp(exp, cause)) {
    return f2cons__cdr(exp, cause);
  } else if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__next(exp, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk1(next, exp, return f2__next(this_cause, exp));

f2ptr f2__next__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__consp(exp, cause)) {
    return f2cons__cdr__set(exp, cause, value);
  } else if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__next__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk2(next__set, exp, value, return f2__next__set(this_cause, exp, value));

f2ptr f2__prev(f2ptr cause, f2ptr exp) {
  if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__prev(exp, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk1(prev, exp, return f2__prev(this_cause, exp));

f2ptr f2__prev__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__doublelinkp(exp, cause)) {
    return f2doublelink__prev__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk2(prev__set, exp, value, return f2__prev__set(this_cause, exp, value));

f2ptr raw__str_copy(f2ptr cause, f2ptr object, u8* str) {
  if (raw__stringp(object, cause)) {
    f2string__str_copy(object, cause, str);
    return nil;
  } else if (raw__symbolp(object, cause)) {
    f2symbol__str_copy(object, cause, str);
    return nil;
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__colonize(f2ptr cause, f2ptr exp) {
  if ((! raw__stringp(exp, cause)) &&
      (! raw__symbolp(exp, cause))) {
    return f2larva__new(cause, 1);
  }
  u64 length = raw__length(cause, exp);
  u8* str = alloca(length + 2);
  str[0] = (u8)':';
  raw__str_copy(cause, exp, str + 1);
  str[length + 1] = 0;
  f2ptr colonized = f2symbol__new(cause, length + 1, str);
  return colonized;
}
def_pcfunk1(colonize, exp, return f2__colonize(this_cause, exp));

f2ptr f2__funktionalp(f2ptr cause, f2ptr thread, f2ptr exp) {
  boolean_t exp__is_funktional = boolean__true;
  raw__compile(cause, thread, exp, boolean__false, boolean__false, NULL, &exp__is_funktional, nil, NULL);
  return f2bool__new(exp__is_funktional);
}
def_pcfunk1(funktionalp, exp, return f2__funktionalp(this_cause, simple_thread, exp));

void f2__primcfunks__reinitialize_globalvars() {
  f2ptr cause = f2_primfunks_c__cause__new(initial_cause());
  
  __argument_type_check_failure__exception__tag   = f2symbol__new(cause, strlen("primcfunks:argument-type-check-failure"),   (u8*)"primcfunks:argument-type-check-failure");
  __argument_number_check_failure__exception__tag = f2symbol__new(cause, strlen("primcfunks:argument-number-check-failure"), (u8*)"primcfunks:argument-number-check-failure");
  
  __argument_type_check_failure__exception   = f2exception__new(cause, __argument_type_check_failure__exception__tag,   nil);  
  __argument_number_check_failure__exception = f2exception__new(cause, __argument_number_check_failure__exception__tag, nil);
}

void f2__primcfunks__initialize() {
  pause_gc();
  
  f2ptr cause = f2_primfunks_c__cause__new(initial_cause());
  
  f2__primcfunks__reinitialize_globalvars();
  
  // system
  
  f2__funktional_primcfunk__init__0(system__node_id);
  f2__funktional_primcfunk__init__0(system__environment);
  
  // funk2 pointer (f2ptr)
  
  f2__funktional_primcfunk__init__1(pointer, exp);
  f2__funktional_primcfunk__init__1(deref_pointer, pointer);
  
  // ptype
  
  f2__primcfunk__init__4(           memblock__set_init_render_xyz,              this, x, y, z);
  f2__primcfunk__init__2(           memblock__set_init_render_on,               this, value);
  f2__primcfunk__init__2(           memblock__set_init_render_noise,            this, value);
  
  // ptype
  
  f2__funktional_primcfunk__init__1(ptype__raw,        this);
  f2__primcfunk__init__1(           ptype__cause,      this);
  f2__primcfunk__init__2(           ptype__cause__set, this, value);
  
  // integer
  
  f2__funktional_primcfunk__init__1(integerp, exp);
  
  // double
  
  f2__funktional_primcfunk__init__1(doublep, exp);
  
  // float
  
  f2__funktional_primcfunk__init__1(floatp, exp);
  
  // pointer
  
  f2__funktional_primcfunk__init__1(pointerp, exp);
  
  // gfunkptr
  
  f2__primcfunk__init__3(           gfunkptr,                   computer_id, pool_index, pool_address);
  f2__primcfunk__init__1(           gfunkptr__new_from_pointer, pointer);
  f2__funktional_primcfunk__init__1(gfunkptrp,                  exp);
  
  // mutex
  
  f2__funktional_primcfunk__init__1(mutexp,         exp);
  f2__primcfunk__init__0(           mutex);
  f2__primcfunk__init__1(           mutex__lock,    this);
  f2__primcfunk__init__1(           mutex__unlock,  this);
  f2__primcfunk__init__1(           mutex__trylock, this);
  
  // string
  
  f2__funktional_primcfunk__init__1(stringp,                       exp);
  f2__funktional_primcfunk__init__1(string__length,                this);
  f2__funktional_primcfunk__init__2(string__elt,                   this, index);
  f2__funktional_primcfunk__init__2(string__equals,                this, that);
  f2__primcfunk__init__1(           string__new_raw_c_string,      this);
  f2__primcfunk__init__1(           string__new_from_raw_c_string, c_string);
  
  // symbol
  
  f2__funktional_primcfunk__init__1(symbolp,        exp);
  f2__funktional_primcfunk__init__1(symbol__length, this);
  f2__funktional_primcfunk__init__2(symbol__elt,    this, index);
  f2__funktional_primcfunk__init__2(symbol__eq,     this, that);
  
  // chunk
  
  f2__funktional_primcfunk__init__1(chunkp,        exp);
  f2__primcfunk__init__1(           chunk,         length);
  f2__funktional_primcfunk__init__1(chunk__length, this);
  f2__primcfunk__init(chunk__copy);
  f2__primcfunk__init(chunk__read_bit8);
  f2__primcfunk__init(chunk__write_bit8_integer);
  f2__primcfunk__init(chunk__read_bit8_signed);
  f2__primcfunk__init(chunk__read_bit16);
  f2__primcfunk__init(chunk__write_bit16_integer);
  f2__primcfunk__init(chunk__read_bit16_signed);
  f2__primcfunk__init(chunk__read_bit32);
  f2__primcfunk__init(chunk__write_bit32_integer);
  f2__primcfunk__init(chunk__read_bit32_signed);
  f2__primcfunk__init(chunk__new_compiled_from_funk);
  
  // simple_array
  
  f2__funktional_primcfunk__init__1(simple_arrayp,          exp);
  f2__funktional_primcfunk__init__1(simple_array__length,   this);
  f2__primcfunk__init__2(           simple_array__elt,      this, index);
  f2__primcfunk__init__3(           simple_array__elt__set, this, index, value);
  
  // traced_array
  
  f2__funktional_primcfunk__init__1(traced_arrayp,                             exp);
  f2__funktional_primcfunk__init__1(traced_array__length,                      this);
  f2__primcfunk__init__2(           traced_array__elt,                         this, index);
  f2__primcfunk__init__3(           traced_array__elt__set,                    this, index, value);
  f2__primcfunk__init__2(           traced_array__elt__tracing_on,             this, index);
  f2__primcfunk__init__3(           traced_array__elt__tracing_on__set,        this, index, value);
  f2__primcfunk__init__2(           traced_array__elt__trace,                  this, index);
  f2__primcfunk__init__3(           traced_array__elt__trace__set,             this, index, value);
  f2__primcfunk__init__2(           traced_array__elt__imagination_frame,      this, index);
  f2__primcfunk__init__3(           traced_array__elt__imagination_frame__set, this, index, value);
  
  // array
  
  f2__funktional_primcfunk__init__1(arrayp,                             exp);
  f2__primcfunk__init__1(           array__new_1d,                      length);
  f2__primcfunk__init__0_and_rest(  array,                              elts);
  f2__funktional_primcfunk__init__1(array__length,                      this);
  f2__primcfunk__init__2(           array__elt,                         this, index);
  f2__primcfunk__init__3(           array__elt__set,                    this, index, value);
  f2__primcfunk__init__2(           array__elt__tracing_on,             this, index);
  f2__primcfunk__init__3(           array__elt__tracing_on__set,        this, index, value);
  f2__primcfunk__init__2(           array__elt__trace,                  this, index);
  f2__primcfunk__init__3(           array__elt__trace__set,             this, index, value);
  f2__primcfunk__init__2(           array__elt__imagination_frame,      this, index);
  f2__primcfunk__init__3(           array__elt__imagination_frame__set, this, index, value);
  
  // place
  
  f2__primcfunk__init(place);
  f2__funktional_primcfunk__init(placep);
  f2__primcfunk__init(place__thing);
  f2__primcfunk__init(place__thing__set);
  
  // cons
  
  f2__funktional_primcfunk__init(consp);
  f2__primcfunk__init(cons);
  f2__primcfunk__init(cons__car);
  f2__primcfunk__init(cons__car__set);
  f2__primcfunk__init(cons__cdr);
  f2__primcfunk__init(cons__cdr__set);
  
  // doublelink
  
  f2__primcfunk__init(doublelink);
  f2__funktional_primcfunk__init(doublelinkp);
  f2__primcfunk__init(doublelink__prev);
  f2__primcfunk__init(doublelink__prev__set);
  f2__primcfunk__init(doublelink__next);
  f2__primcfunk__init(doublelink__next__set);
  f2__primcfunk__init(doublelink__value);
  f2__primcfunk__init(doublelink__value__set);
  
  // circular_buffer
  
  f2__funktional_primcfunk__init(circular_bufferp);
  f2__primcfunk__init(circular_buffer);
  f2__primcfunk__init(circular_buffer__add);
  f2__primcfunk__init(circular_buffer__remove);
  
  // other complex functions
  
  f2__primcfunk__init(make_funk);
  f2__primcfunk__init(make_metro);
  f2__primcfunk__init(thread);
  
  f2__primcfunk__init__1(           length,                     seq);
  f2__funktional_primcfunk__init__2(integer__greater_than,      x, y);
  f2__funktional_primcfunk__init__2(integer__less_than,         x, y);
  f2__funktional_primcfunk__init__2(integer__add,               x, y);
  f2__funktional_primcfunk__init__2(integer__subtract,          x, y);
  f2__funktional_primcfunk__init__2(integer__multiply,          x, y);
  f2__funktional_primcfunk__init__2(integer__add_double,        x, y);
  f2__funktional_primcfunk__init__2(integer__subtract_double,   x, y);
  f2__funktional_primcfunk__init__2(integer__divide_by_integer, x, y);
  f2__funktional_primcfunk__init__2(integer__divide_by_double,  x, y);
  f2__funktional_primcfunk__init__2(integer__equal_sign,        x, y);
  f2__funktional_primcfunk__init__2(integer__not_equal_sign,    x, y);
  f2__funktional_primcfunk__init__2(integer__bitshift_left,     x, y);
  f2__funktional_primcfunk__init__2(integer__bitshift_right,    x, y);
  f2__funktional_primcfunk__init__2(integer__bit_and,           x, y);
  f2__funktional_primcfunk__init__2(integer__bit_or,            x, y);
  f2__funktional_primcfunk__init__2(integer__bit_xor,           x, y);
  f2__funktional_primcfunk__init__1(integer__bit_not,           x);
  f2__funktional_primcfunk__init__2(pointer__greater_than,      x, y);
  f2__funktional_primcfunk__init__2(pointer__less_than,         x, y);
  f2__funktional_primcfunk__init__2(pointer__add_integer,       x, y);
  f2__funktional_primcfunk__init__2(pointer__subtract,          x, y);
  f2__funktional_primcfunk__init__2(pointer__equal_sign,        x, y);
  f2__funktional_primcfunk__init__2(pointer__not_equal_sign,    x, y);
  f2__funktional_primcfunk__init__1(null,                       x);
  f2__funktional_primcfunk__init__1(not,                        x);
  
  f2__funktional_primcfunk__init__2(eq,                         x, y);
  
  f2__primcfunk__init__0(quit);
  
  f2__primcfunk__init__1(exp__print, exp);
  f2__primcfunk__init(write);
  f2__primcfunk__init(fwrite);
  f2__primcfunk__init(exp__format);
  f2__primcfunk__init(exp__format__html);
  f2__primcfunk__init(exp__fwrite_html);
  
  f2__primcfunk__init(debug);
  f2__primcfunk__init(trace);
  f2__primcfunk__init(compile);
  
  f2__primcfunk__init(fopen);
  f2__primcfunk__init(fclose);
  
  f2__primcfunk__init__0(this__cause);
  f2__primcfunk__init__0(this__thread);
  f2__primcfunk__init__0(this__env);
  f2__primcfunk__init__0(this__args);
  
  f2__primcfunk__init(random);
  
  f2__primcfunk__init(system_microseconds_since_1970);
  
  f2__funktional_primcfunk__init(identity);
  
  f2__primcfunk__init(demetropolize_once);
  f2__primcfunk__init(demetropolize_full);
  f2__primcfunk__init(exps_demetropolize_full);
  f2__primcfunk__init(compile__special_symbol_exp);
  f2__primcfunk__init(lookup_funkvar);  
  f2__primcfunk__init(jump_to_chunk);
  f2__funktional_primcfunk__init(coerce_to_int);
  
  f2__primcfunk__init(wrong_argument_number_error__set);
  
  f2__primcfunk__init(memory_image__save);
  f2__primcfunk__init(memory_image__load);
  
  f2__primcfunk__init(funkall__raw_c_funk__v__v);
  f2__primcfunk__init(funkall__raw_c_funk__v__i);
  f2__primcfunk__init(funkall__raw_c_funk__v__id);
  f2__primcfunk__init(funkall__raw_c_funk__v__idd);
  f2__primcfunk__init(funkall__raw_c_funk__v__iddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__idddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ip);
  f2__primcfunk__init(funkall__raw_c_funk__v__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ippp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ipppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iid);
  f2__primcfunk__init(funkall__raw_c_funk__v__iii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__p);
  f2__primcfunk__init(funkall__raw_c_funk__v__pi);
  f2__primcfunk__init(funkall__raw_c_funk__v__pp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__pppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ppppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__d);
  f2__primcfunk__init(funkall__raw_c_funk__v__dd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__f);
  f2__primcfunk__init(funkall__raw_c_funk__v__ff);
  f2__primcfunk__init(funkall__raw_c_funk__v__fff);
  f2__primcfunk__init(funkall__raw_c_funk__v__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__v__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__i__v);
  f2__primcfunk__init(funkall__raw_c_funk__i__i);
  f2__primcfunk__init(funkall__raw_c_funk__i__ii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiiiip);
  f2__primcfunk__init(funkall__raw_c_funk__i__ip);
  f2__primcfunk__init(funkall__raw_c_funk__i__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ippp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ipppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__p);
  f2__primcfunk__init(funkall__raw_c_funk__i__pp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__pppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ppppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__d);
  f2__primcfunk__init(funkall__raw_c_funk__i__dd);
  f2__primcfunk__init(funkall__raw_c_funk__i__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__f);
  f2__primcfunk__init(funkall__raw_c_funk__i__ff);
  f2__primcfunk__init(funkall__raw_c_funk__i__fff);
  f2__primcfunk__init(funkall__raw_c_funk__i__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__i__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__d__v);
  f2__primcfunk__init(funkall__raw_c_funk__d__i);
  f2__primcfunk__init(funkall__raw_c_funk__d__ii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__d__d);
  f2__primcfunk__init(funkall__raw_c_funk__d__dd);
  f2__primcfunk__init(funkall__raw_c_funk__d__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__f);
  f2__primcfunk__init(funkall__raw_c_funk__d__ff);
  f2__primcfunk__init(funkall__raw_c_funk__d__fff);
  f2__primcfunk__init(funkall__raw_c_funk__d__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__d__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__f__v);
  f2__primcfunk__init(funkall__raw_c_funk__f__i);
  f2__primcfunk__init(funkall__raw_c_funk__f__ii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__f__d);
  f2__primcfunk__init(funkall__raw_c_funk__f__dd);
  f2__primcfunk__init(funkall__raw_c_funk__f__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__f);
  f2__primcfunk__init(funkall__raw_c_funk__f__ff);
  f2__primcfunk__init(funkall__raw_c_funk__f__fff);
  f2__primcfunk__init(funkall__raw_c_funk__f__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__f__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__p__v);
  f2__primcfunk__init(funkall__raw_c_funk__p__i);
  f2__primcfunk__init(funkall__raw_c_funk__p__ip);
  f2__primcfunk__init(funkall__raw_c_funk__p__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__p__p);
  f2__primcfunk__init(funkall__raw_c_funk__p__pp);
  f2__primcfunk__init(funkall__raw_c_funk__p__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__p__pppp);
  
  f2__funktional_primcfunk__init(integer__to_float);
  f2__funktional_primcfunk__init(integer__to_double);
  f2__funktional_primcfunk__init(double__to_integer);
  f2__funktional_primcfunk__init(double__to_float);
  f2__funktional_primcfunk__init(double__add_double);
  f2__funktional_primcfunk__init(double__subtract_double);
  f2__funktional_primcfunk__init(double__multiply_by_double);
  f2__funktional_primcfunk__init(double__divide_by_double);
  f2__funktional_primcfunk__init(double__add_integer);
  f2__funktional_primcfunk__init(double__subtract_integer);
  f2__funktional_primcfunk__init(double__multiply_by_integer);
  f2__funktional_primcfunk__init(double__divide_by_integer);
  f2__funktional_primcfunk__init(float__to_integer);
  f2__funktional_primcfunk__init(float__to_double);
  
  f2__primcfunk__init(repl);
  
  f2__primcfunk__init(hashtable__add_keyvalue_pair);
  f2__primcfunk__init(hashtable__lookup_keyvalue_pair);
  f2__primcfunk__init(hashtable__lookup_value);
  
  f2__primcfunk__init(tensor__new_from_array_of_integer_dimensions);
  f2__primcfunk__init(tensor__elt_from_array_of_integer_indices);
  
  // f2_trace.c funktions
  f2__primcfunk__init(trace__remember__microseconds_since_1970);
  f2__primcfunk__init(array__elt__remember__microseconds_since_1970);
  f2__primcfunk__init(exp__remember__microseconds_since_1970);
  f2__primcfunk__init(exp__remember__trans__microseconds_since_1970);
  f2__primcfunk__init(array__tracing_on__set);
  
  f2__primcfunk__init(funk2_node_handler__know_of_node);
  f2__primcfunk__init__4(send_request_register_peer, computer_id, node_id, ip_addr, port_num);
  
  f2__primcfunk__init(system__peer_command_server__port_num);
  f2__primcfunk__init(system__gethostname);
  
  f2__funktional_primcfunk__init(larva);
  
  f2__primcfunk__init(publish_event);
  f2__primcfunk__init(event_subscriber);
  f2__primcfunk__init(subscribe);
  
  f2__primcfunk__init(thread__subversion_cause);
  
  f2__funktional_primcfunk__init(first);
  f2__funktional_primcfunk__init(first__set);
  f2__funktional_primcfunk__init(next);
  f2__funktional_primcfunk__init(next__set);
  f2__funktional_primcfunk__init(prev);
  f2__funktional_primcfunk__init(prev__set);
  
  f2__funktional_primcfunk__init__1(colonize, exp);
  f2__funktional_primcfunk__init__1(funktionalp, exp);
  
  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen("argument_type_check_failure-exception"),   (u8*)"argument_type_check_failure-exception"),   __argument_type_check_failure__exception);
  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen("argument_number_check_failure-exception"), (u8*)"argument_number_check_failure-exception"), __argument_number_check_failure__exception);
  
  resume_gc();
  try_gc();
}


