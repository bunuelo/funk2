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
  
}

