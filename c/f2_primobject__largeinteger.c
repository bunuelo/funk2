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

// largeinteger

def_primobject_2_slot(largeinteger, is_negative, integer_array);

f2ptr f2__largeinteger__new(f2ptr cause, f2ptr value) {
  if (raw__integer__is_type(cause, value)) {
    s64 value__i = f2integer__i(value, cause);
    if (value__i == 0) {
      return f2largeinteger__new(cause, f2bool__new(boolean__false), raw__array__new(cause, 0));
    } else {
      f2ptr integer_array = raw__array__new(cause, 1);
      f2ptr is_negative;
      if (value__i < 0) {
	is_negative = f2bool__new(boolean__true);
	u64 unsigned_value__i = (u64)((s64)(-value__i));
	raw__array__elt__set(cause, integer_array, 0, f2integer__new(cause, unsigned_value__i));
      } else {
	is_negative = f2bool__new(boolean__false);
	raw__array__elt__set(cause, integer_array, 0, value);
      }
      return f2largeinteger__new(cause, is_negative, integer_array);
    }
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk1(largeinteger__new, value, return f2__largeinteger__new(this_cause, value));

boolean_t raw__largeinteger__unsigned_array__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  if (this__length > that__length) {
    return boolean__true;
  }
  if (this__length < that__length) {
    return boolean__false;
  }
  // assert(this__length == that__length)
  s64 index;
  for (index = this__length - 1; index >= 0; index --) {
    f2ptr this__elt = raw__array__elt(cause, this, index);
    f2ptr that__elt = raw__array__elt(cause, that, index);
    u64 this__value = f2integer__i(this__elt, cause);
    u64 that__value = f2integer__i(that__elt, cause);
    if (this__value > that__value) {
      return boolean__true;
    }
    if (this__value < that__value) {
      return boolean__false;
    }
  }
  return boolean__false;
}

boolean_t raw__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(cause, that);
  if (this__is_negative) {
    if (that__is_negative) {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return (! raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array));
    } else {
      return boolean__false;
    }
  } else {
    if (that__is_negative) {
      return boolean__true;
    } else {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array);
    }
  }
}

f2ptr f2__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__largeinteger__greater_than(cause, this, that));
}
def_pcfunk2(largeinteger__greater_than, this, that, return f2__largeinteger__greater_than(this_cause, this, that));

f2ptr f2__largeinteger__unsigned_array__add(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  f2ptr small;
  f2ptr large;
  u64   small__length;
  u64   large__length;
  if (this__length < that__length) {
    small = this;
    large = that;
    small__length = this__length;
    large__length = that__length;
  } else {
    small = that;
    large = this;
    small__length = that__length;
    large__length = this__length;
  }
  u64 temp__length = small__length + large__length;
  u64* temp_array = (u64*)alloca(sizeof(u64) * temp__length);
  memset(temp_array, 0, sizeof(u64) * temp__length);
  u64 last_nonzero_index = -1;
  u64 result__carry      = 0;
  u64 index;
  for (index = 0; index < large__length; index ++) {
    u64 small__value;
    if (index < small__length) {
      f2ptr small__elt = raw__array__elt(cause, small, index);
      small__value = (u64)f2integer__i(small__elt, cause);
    } else {
      small__value = 0;
    }
    f2ptr large__elt = raw__array__elt(cause, large, index);
    u64   large__value = (u64)f2integer__i(large__elt, cause);
    u64   result__value = small__value + large__value + result__carry;
    if (result__value < small__value) {
      result__carry = 1;
    } else {
      result__carry = 0;
    }
    temp_array[index] = result__value;
    if (result__value != 0) {
      last_nonzero_index = index;
    }
  }
  u64   new_array__length = last_nonzero_index + 1;
  f2ptr new_array         = raw__array__new(cause, new_array__length);
  for (index = 0; index < new_array__length; index ++) {
    raw__array__elt__set(cause, new_array, index, f2integer__new(cause, temp_array[index]));
  }
  return new_array;
}

f2ptr f2__largeinteger__unsigned_array__subtract_smaller(f2ptr cause, f2ptr this, f2ptr smaller) {
  f2ptr large              = this;
  f2ptr small              = smaller;
  u64   large__length      = raw__array__length(cause, large);
  u64   small__length      = raw__array__length(cause, small);
  u64   borrow__value      = 0;
  u64   last_nonzero_index = -1;
  u64*  result_array       = alloca(sizeof(u64) * large__length);
  u64   index;
  for (index = 0; index < large__length; index ++) {
    u64 small__value = 0;
    if (index < small__length) {
      f2ptr small__elt = raw__array__elt(cause, small, index);
      small__value = (u64)f2integer__i(small__elt, cause);
    }
    f2ptr large__elt    = raw__array__elt(cause, large, index);
    u64   large__value  = f2integer__i(large__elt, cause);
    u64   result__value = large__value - small__value - borrow__value;
    if (result__value > large__value) {
      borrow__value = 1;
    } else {
      borrow__value = 0;
    }
    if (result__value != 0) {
      last_nonzero_index = index;
    }
    result_array[index] = result__value;
  }
  u64   new_array__length = last_nonzero_index + 1;
  f2ptr new_array         = raw__array__new(cause, new_array__length);
  for (index = 0; index < new_array__length; index ++) {
    raw__array__elt__set(cause, new_array, index, f2integer__new(cause, result_array[index]));
  }
  return new_array;
}

f2ptr raw__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative = f2__largeinteger__is_negative(     cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(     cause, that);
  f2ptr this__array    = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array    = f2__largeinteger__integer_array(cause, that);
  f2ptr result__array;
  f2ptr result__is_negative;
  if (this__is_negative) {
    if (that__is_negative) {
      result__is_negative = f2bool__new(boolean__true);
      result__array    = f2__largeinteger__unsigned_array__add(cause, this__array, that__array);
    } else {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__is_negative = f2bool__new(boolean__true);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__is_negative = f2bool__new(boolean__false);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = f2__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    }
  } else {
    if (that__is_negative) {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__is_negative = f2bool__new(boolean__false);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__is_negative = f2bool__new(boolean__true);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = f2__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    } else {
      result__is_negative = f2bool__new(boolean__false);
      result__array    = f2__largeinteger__unsigned_array__add(cause, this__array, that__array);
    }
  }
  return f2largeinteger__new(cause, result__is_negative, result__array);
}

f2ptr f2__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__add(cause, this, that);
}
def_pcfunk2(largeinteger__add, this, that, return f2__largeinteger__add(this_cause, this, that));

f2ptr raw__largeinteger__negative(f2ptr cause, f2ptr this) {
  return f2largeinteger__new(cause, f2bool__new(f2largeinteger__is_negative(this, cause) == nil), f2largeinteger__integer_array(this, cause));
}

f2ptr f2__largeinteger__negative(f2ptr cause, f2ptr this) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__negative(cause, this);
}
def_pcfunk1(largeinteger__negative, this, return f2__largeinteger__negative(this_cause, this));

f2ptr raw__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__largeinteger__add(cause, this, raw__largeinteger__negative(cause, that));
}

f2ptr f2__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__subtract(cause, this, that);
}
def_pcfunk2(largeinteger__subtract, this, that, return f2__largeinteger__subtract(this_cause, this, that));

u64 u64__multiply(u64 this, u64 that, u64* overflow) {
  u64 temp__00 = ((u64)(this & 0xffffffff)) * ((u64)(that & 0xffffffff));
  u64 temp__01 = ((u64)(this & 0xffffffff)) * ((u64)(that >> 32));
  u64 temp__10 = ((u64)(this >> 32))        * ((u64)(that & 0xffffffff));
  u64 temp__11 = ((u64)(this >> 32))        * ((u64)(that >> 32));
  u64 result = temp__00 + ((temp__01 + temp__10) << 32);
  *overflow = ((temp__01 + temp__10) >> 32) + temp__11;
  return result;
}

f2ptr raw__largeinteger__unsigned_array__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  u64  result_array__length = this__length + that__length;
  u64* result_array = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  u64* this_array = (u64*)alloca(sizeof(u64) * this__length);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr elt = raw__array__elt(cause, this, index);
      this_array[index] = f2integer__i(elt, cause);
    }
  }
  u64* that_array = (u64*)alloca(sizeof(u64) * that__length);
  {
    u64 index;
    for (index = 0; index < that__length; index ++) {
      f2ptr elt = raw__array__elt(cause, that, index);
      that_array[index] = f2integer__i(elt, cause);
    }
  }
  {
    u64 this_index;
    u64 that_index;
    for (that_index = 0; that_index < that__length; that_index ++) {
      u64 that__value = that_array[that_index];
      for (this_index = 0; this_index < this__length; this_index ++) {
	u64 this__value = this_array[this_index];
	u64 overflow_value;
	u64 result_value = u64__multiply(this__value, that__value, &overflow_value);
	result_array[this_index + that_index]     += result_value;
	result_array[this_index + that_index + 1] += overflow_value;
      }
    }
  }
  s64 last_nonzero_index;
  for (last_nonzero_index = result_array__length - 1; last_nonzero_index >= 0 && result_array[last_nonzero_index] == 0; last_nonzero_index --);
  u64   result__length = last_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative   = f2__largeinteger__is_negative(  cause, this);
  f2ptr that__is_negative   = f2__largeinteger__is_negative(  cause, that);
  f2ptr this__array         = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array         = f2__largeinteger__integer_array(cause, that);
  f2ptr result__is_negative = f2bool__new((this__is_negative != nil) != (that__is_negative != nil));
  f2ptr result__array       = raw__largeinteger__unsigned_array__multiply(cause, this__array, that__array);
  return f2largeinteger__new(cause, result__is_negative, result__array);
}

f2ptr f2__largeinteger__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__multiply(cause, this, that);
}
def_pcfunk2(largeinteger__multiply, this, that, return f2__largeinteger__multiply(this_cause, this, that));

f2ptr raw__largeinteger__unsigned_array__divide(f2ptr cause, f2ptr this, f2ptr that) {
  if (raw__largeinteger__unsigned_array__greater_than(cause, that, this)) {
    return raw__array__new(cause, 0);
  }
  u64 that__length = raw__array__length(cause, that);
  if (that__length == 0) {
    return f2larva__new(cause, 53); // divide by zero
  }
  //u64 this__length = raw__array__length(cause, this);
  
  return nil; // not implemented yet...
}

f2ptr raw__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative   = f2__largeinteger__is_negative(  cause, this);
  f2ptr that__is_negative   = f2__largeinteger__is_negative(  cause, that);
  f2ptr this__array         = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array         = f2__largeinteger__integer_array(cause, that);
  f2ptr result__is_negative = f2bool__new((this__is_negative != nil) != (that__is_negative != nil));
  f2ptr result__array       = raw__largeinteger__unsigned_array__divide(cause, this__array, that__array);
  return f2largeinteger__new(cause, result__is_negative, result__array);
}

f2ptr f2__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__divide(cause, this, that);
}
def_pcfunk2(largeinteger__divide, this, that, return f2__largeinteger__divide(this_cause, this, that));

f2ptr raw__largeinteger__unsigned_array__bitshift_left_only(f2ptr cause, f2ptr this, u64 bit_distance) {
  u64  this__length         = raw__array__length(cause, this);
  u64  array__distance      = (bit_distance >> 6);
  u64  array__bit_distance  = bit_distance - (array__distance << 6);
  u64  result_array__length = this__length + array__distance + 1;
  u64* result_array         = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr elt         = raw__array__elt(cause, this, index);
      u64   value       = f2integer__i(elt, cause);
      u64   value_left  = (value >> (64 - array__bit_distance));
      u64   value_right = (value << array__bit_distance);
      result_array[array__distance + index]     += value_right;
      result_array[array__distance + index + 1] += value_left;
    }
  }
  u64 max_nonzero_index;
  for (max_nonzero_index = result_array__length - 1; max_nonzero_index >= 0 && result_array[max_nonzero_index] == 0; max_nonzero_index --);
  u64   result__length = max_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__unsigned_array__bitshift_right_only(f2ptr cause, f2ptr this, u64 bit_distance) {
  u64  this__length         = raw__array__length(cause, this);
  u64  array__distance      = (bit_distance >> 6);
  u64  array__bit_distance  = bit_distance - (array__distance << 6);
  u64  result_array__length = this__length - array__distance;
  u64* result_array         = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  {
    u64 index;
    for (index = array__distance; index < this__length; index ++) {
      f2ptr elt         = raw__array__elt(cause, this, index);
      u64   value       = f2integer__i(elt, cause);
      u64   value_right = (value << (64 - array__bit_distance));
      u64   value_left  = (value >> array__bit_distance);
      if (index - array__distance - 1 >= 0) {
	result_array[index - array__distance - 1] += value_right;
      }
      result_array[index - array__distance]     += value_left;
    }
  }
  u64 max_nonzero_index;
  for (max_nonzero_index = result_array__length - 1; max_nonzero_index >= 0 && result_array[max_nonzero_index] == 0; max_nonzero_index --);
  u64   result__length = max_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__unsigned_array__bitshift_left(f2ptr cause, f2ptr this, s64 bit_distance) {
  if (bit_distance == 0) {
    return this;
  }
  if (bit_distance > 0) {
    return raw__largeinteger__unsigned_array__bitshift_left_only(cause, this, bit_distance);
  } else {
    return raw__largeinteger__unsigned_array__bitshift_right_only(cause, this, -bit_distance);
  }
}

f2ptr raw__largeinteger__unsigned_array__bitshift_right(f2ptr cause, f2ptr this, s64 bit_distance) {
  if (bit_distance == 0) {
    return this;
  }
  if (bit_distance > 0) {
    return raw__largeinteger__unsigned_array__bitshift_right_only(cause, this, bit_distance);
  } else {
    return raw__largeinteger__unsigned_array__bitshift_left_only(cause, this, -bit_distance);
  }
}

f2ptr f2__largeinteger__bitshift_left(f2ptr cause, f2ptr this, f2ptr bit_distance) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, bit_distance))) {
    return f2larva__new(cause, 1);
  }
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr this__array       = f2__largeinteger__integer_array(cause, this);
  s64   bit_distance__i   = f2integer__i(bit_distance, cause);
  f2ptr result_array      = raw__largeinteger__unsigned_array__bitshift_left(cause, this__array, bit_distance__i);
  return f2largeinteger__new(cause, this__is_negative, result_array);
}
def_pcfunk2(largeinteger__bitshift_left, this, bit_distance, return f2__largeinteger__bitshift_left(this_cause, this, bit_distance));

f2ptr f2__largeinteger__bitshift_right(f2ptr cause, f2ptr this, f2ptr bit_distance) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, bit_distance))) {
    return f2larva__new(cause, 1);
  }
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr this__array       = f2__largeinteger__integer_array(cause, this);
  s64   bit_distance__i   = f2integer__i(bit_distance, cause);
  f2ptr result_array      = raw__largeinteger__unsigned_array__bitshift_right(cause, this__array, bit_distance__i);
  return f2largeinteger__new(cause, this__is_negative, result_array);
}
def_pcfunk2(largeinteger__bitshift_right, this, bit_distance, return f2__largeinteger__bitshift_right(this_cause, this, bit_distance));

// **

void f2__primobject_largeinteger__reinitialize_globalvars() {
  __largeinteger__symbol = f2symbol__new(initial_cause(), strlen("largeinteger"), (u8*)"largeinteger");
}

void f2__primobject_largeinteger__initialize() {
  f2__primobject_largeinteger__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __largeinteger__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // largeinteger
  
  initialize_primobject_2_slot(largeinteger, is_negative, integer_array);
  
  f2__primcfunk__init__2(largeinteger__greater_than, this, that, "compare two largeintegers for which is greater and return a boolean value as the result.");
  f2__primcfunk__init__2(largeinteger__add, this, that, "add two largeintegers and return a new largeinteger as the result.");
  f2__primcfunk__init__1(largeinteger__negative, this, "returns the negative of a largeinteger.");
  f2__primcfunk__init__2(largeinteger__subtract, this, that, "returns the result of subtracting two largeintegers.");
  f2__primcfunk__init__2(largeinteger__multiply, this, that, "returns the result of multiplying two largeintegers.");
  f2__primcfunk__init__2(largeinteger__divide, this, that, "returns the result of dividing two largeintegers.");
  f2__primcfunk__init__2(largeinteger__bitshift_left, this, bit_distance, "returns the result of bitshifting one largeinteger to the left by an integer bit distance.");
  f2__primcfunk__init__2(largeinteger__bitshift_right, this, bit_distance, "returns the result of bitshifting one largeinteger to the right by an integer bit distance.");
  
}

