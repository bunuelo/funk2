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

#include "funk2.h"

// tensor primobject definition

defprimobject__static_slot(tensor__dimensions, 0);
defprimobject__static_slot(tensor__data,       1);

f2ptr __tensor__symbol = -1;

f2ptr f2tensor__new(f2ptr cause, f2ptr dimensions, f2ptr data) {
  release__assert(__tensor__symbol != -1, nil, "f2tensor__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __tensor__symbol, 2, nil);
  f2tensor__dimensions__set(this, cause, dimensions);
  f2tensor__data__set(      this, cause, data);
  return this;
}

// hardcoded functions

f2ptr f2__tensor__new_from_array_of_integer_dimensions(f2ptr cause, f2ptr dimensions, f2ptr fill_element) {
  int   dimensions__length = raw__array__length(cause, dimensions);
  f2ptr new_dimensions     = raw__array__new(cause, dimensions__length);
  int   data__length       = 1;
  int   i;
  for (i = dimensions__length - 1; i >= 0; i --) {
    f2ptr element = raw__array__elt(cause, dimensions, i);
    raw__array__elt__set(cause, new_dimensions, i, element);
    data__length *= f2integer__i(element, cause);
  }
  f2ptr data = raw__array__new(cause, data__length);
  for (i = data__length - 1; i >= 0; i --) {
    raw__array__elt__set(cause, data, i, fill_element);
  }
  f2ptr this = f2tensor__new(cause, new_dimensions, data);
  return this;
}

f2ptr f2tensor__elt_from_array_of_integer_indices(f2ptr this, f2ptr indices, f2ptr cause) {
  f2ptr dimensions         = f2tensor__dimensions(this, cause);
  int   dimensions__length = raw__array__length(cause, dimensions);
  f2ptr data               = f2tensor__data(this, cause);
  int   data__length       = raw__array__length(cause, data);
  int   indices__length    = raw__array__length(cause, indices);
  if (indices__length != dimensions__length) {
    status("f2tensor__elt_from_array_of_integer_indices release assertion failed: [= indices__length dimensions__length].");
    error(nil, "f2tensor__elt_from_array_of_integer_indices release assertion failed: [= indices__length dimensions__length].");
  }
  int i;
  int data_index            = 0;
  int data_index_multiplier = 1;
  for (i = indices__length - 1; i >= 0; i --) {
    f2ptr index         = raw__array__elt(cause, indices, i);
    int   raw_index     = f2integer__i(index, cause);
    f2ptr dimension     = raw__array__elt(cause, dimensions, i);
    int   raw_dimension = f2integer__i(dimension, cause);
    data_index            += (data_index_multiplier * raw_index);
    data_index_multiplier *= raw_dimension;
  }
  if (data_index >= data__length) {
    status("f2tensor__elt_from_array_of_integer_indices release assertion failed: [< data_index data__length]");
    error(nil, "f2tensor__elt_from_array_of_integer_indices release assertion failed: [< data_index data__length]");
  }
  f2ptr element = raw__array__elt(cause, data, data_index);
  return element;
}



// end of object

void f2__primobject_tensor__reinitialize_globalvars() {
  __tensor__symbol = new__symbol(initial_cause(), "tensor");
}

void f2__primobject_tensor__defragment__fix_pointers() {
  // -- reinitialize --
  
  defragment__fix_pointer(__tensor__symbol);
  
  
  // -- initialize --
  
}

void f2__primobject_tensor__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_tensor", "", &f2__primobject_tensor__reinitialize_globalvars, &f2__primobject_tensor__defragment__fix_pointers);
  
  f2__primobject_tensor__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __tensor__symbol, nil);
}

