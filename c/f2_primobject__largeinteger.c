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

def_primobject_3_slot(largeinteger, access_mutex, negative, integer_array);

f2ptr f2__largeinteger__new(f2ptr cause, f2ptr value) {
  if (raw__integer__is_type(cause, value)) {
    f2ptr integer_array = raw__array__new(cause, 1);
    s64 value__i = f2integer__i(value, cause);
    f2ptr negative;
    if (value__i < 0) {
      negative = f2bool__new(boolean__true);
      u64 unsigned_value__i = (u64)((s64)(-value__i));
      raw__array__elt__set(cause, integer_array, 0, f2integer__new(cause, unsigned_value__i));
    } else {
      negative = f2bool__new(boolean__false);
      raw__array__elt__set(cause, integer_array, 0, value);
    }
    return f2largeinteger__new(cause, f2mutex__new(cause), negative, integer_array);
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

boolean_t raw__largeinteger__greater_than__thread_unsafe(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__negative = f2__largeinteger__negative(cause, this);
  f2ptr that__negative = f2__largeinteger__negative(cause, that);
  if (this__negative) {
    if (that__negative) {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return (! raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array));
    } else {
      return boolean__false;
    }
  } else {
    if (that__negative) {
      return boolean__true;
    } else {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array);
    }
  }
}

boolean_t raw__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__mutex    = f2__largeinteger__access_mutex( cause, this);
  f2ptr that__mutex    = f2__largeinteger__access_mutex( cause, that);
  raw__mutex__lock_both(cause, this__mutex, that__mutex);
  boolean_t result = raw__largeinteger__greater_than__thread_unsafe(cause, this, that);
  f2mutex__unlock(this__mutex, cause);
  f2mutex__unlock(that__mutex, cause);
  return result;
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
  u64*  result_array       = alloca(sizeof(f2ptr) * large__length);
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

f2ptr f2__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__mutex    = f2__largeinteger__access_mutex( cause, this);
  f2ptr that__mutex    = f2__largeinteger__access_mutex( cause, that);
  raw__mutex__lock_both(cause, this__mutex, that__mutex);
  f2ptr this__negative = f2__largeinteger__negative(     cause, this);
  f2ptr that__negative = f2__largeinteger__negative(     cause, that);
  f2ptr this__array    = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array    = f2__largeinteger__integer_array(cause, that);
  f2ptr result__array;
  f2ptr result__negative;
  if (this__negative) {
    if (that__negative) {
      result__negative = f2bool__new(boolean__true);
      result__array    = f2__largeinteger__unsigned_array__add(cause, this__array, that__array);
    } else {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__negative = f2bool__new(boolean__true);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__negative = f2bool__new(boolean__false);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = f2__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    }
  } else {
    if (that__negative) {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__negative = f2bool__new(boolean__false);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__negative = f2bool__new(boolean__true);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = f2__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    } else {
      result__negative = f2bool__new(boolean__false);
      result__array    = f2__largeinteger__unsigned_array__add(cause, this__array, that__array);
    }
  }
  f2mutex__unlock(this__mutex, cause);
  f2mutex__unlock(that__mutex, cause);
  return f2largeinteger__new(cause, f2mutex__new(cause), result__negative, result__array);
}
def_pcfunk2(largeinteger__add, this, that, return f2__largeinteger__add(this_cause, this, that));

// **

void f2__primobject_largeinteger__reinitialize_globalvars() {
  __largeinteger__symbol = f2symbol__new(initial_cause(), strlen("largeinteger"), (u8*)"largeinteger");
}

void f2__primobject_largeinteger__initialize() {
  f2__primobject_largeinteger__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __largeinteger__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // largeinteger
  
  initialize_primobject_3_slot(largeinteger, access_mutex, negative, integer_array);
  
  f2__primcfunk__init__2(largeinteger__greater_than, this, that, "compare two largeintegers for which is greater and return a boolean value as the result.");
  f2__primcfunk__init__2(largeinteger__add, this, that, "add two largeintegers and return a new largeinteger as the result.");
  
}

