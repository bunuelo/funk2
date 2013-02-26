// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

// object_type primobject definition

defprimobject__static_slot(object_type__types, 0);
defprimobject__static_slot(object_type__frame, 1);

f2ptr __object_type__symbol = -1;

f2ptr f2__object_type__new(f2ptr cause, f2ptr types, f2ptr frame) {
  release__assert(__object_type__symbol != -1, nil, "f2object_type__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __object_type__symbol, 2, nil);
  f2object_type__types__set(this, cause, types);
  f2object_type__frame__set(this, cause, frame);
  return this;
}

boolean_t raw__object_type__is_type(f2ptr cause, f2ptr this) {return raw__array__is_type(cause, this) && f2primobject__is_object_type(this, cause);}
f2ptr f2__object_type__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__object_type__is_type(cause, this));}

f2ptr object_type__new(f2ptr cause) {
  return f2__object_type__new(cause, nil, f2__frame__new(cause, nil));
}

def_pcfunk0(object_type__new,
	    "",
	    return object_type__new(this_cause));

// this lookup fails if binding is not strictly in local frame of object
f2ptr object_type__lookup_local_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  return f2__frame__lookup_type_var_assignment_cons(cause, f2object_type__frame(this, cause), type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
}

// this lookup first attempts to find a local binding, but also checks all inherited type frames for type bindings.
f2ptr object_type__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr assignment_cons = object_type__lookup_local_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __funk2.primobject__frame.type_variable_not_defined__larva) {
    return assignment_cons;
  }
  // cycle through type bindings here if there is no local binding.
  f2ptr type_iter = f2object_type__types(this, cause);
  while (type_iter) {
    f2ptr parent_type = f2cons__car(type_iter, cause);
    assignment_cons = object_type__lookup_type_var_assignment_cons(cause, parent_type, type, var);
    if (assignment_cons != __funk2.primobject__frame.type_variable_not_defined__larva) {
      return assignment_cons;
    }
    type_iter = f2cons__cdr(type_iter, cause);
  }
  // return exception
  return assignment_cons;
}

// this add only modifies the local object frame
void object_type__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2__frame__add_type_var_value(cause, f2object_type__frame(this, cause), type, var, value);
}

// this lookup first attempts the local object frame and then tries to find a type frame binding
f2ptr object_type__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr assignment_cons = object_type__lookup_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __funk2.primobject__frame.type_variable_not_defined__larva) {
    f2ptr value = f2cons__cdr(assignment_cons, cause);
    return value;
  }
  // return exception
  return assignment_cons;
}

f2ptr object_type__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr assignment_cons = object_type__lookup_local_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __funk2.primobject__frame.type_variable_not_defined__larva) {
    f2cons__cdr__set(assignment_cons, cause, value);
    // success
    return nil;
  }
  // return exception
  return assignment_cons;
}

// end of object_type

void f2__primobject_object_type__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __object_type__symbol = new__symbol(cause, "object_type");
  
  f2__primcfunk__init(object_type__new);
}

void f2__primobject_object_type__defragment__fix_pointers() {
  // -- reinitialize --
  
  defragment__fix_pointer(__object_type__symbol);
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(object_type__new);
}

void f2__primobject_object_type__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_object_type", "", &f2__primobject_object_type__reinitialize_globalvars, &f2__primobject_object_type__defragment__fix_pointers);
  
  f2__primobject_object_type__reinitialize_globalvars();
}

