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

// tensor primobject definition

defprimobject__static_slot(object__types, 0);
defprimobject__static_slot(object__frame, 1);

f2ptr __object__symbol = -1;

f2ptr f2__object__new(f2ptr cause, f2ptr types, f2ptr frame) {
  release__assert(__object__symbol != -1, nil, "f2object__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __object__symbol, 2, nil);
  f2object__types__set(this, cause, types);
  f2object__frame__set(this, cause, frame);
  return this;
}

boolean_t raw__objectp(f2ptr this, f2ptr cause) {return raw__arrayp(this, cause) && f2primobject__is_object(this, cause);}
f2ptr f2__objectp(f2ptr this, f2ptr cause) {return f2bool__new(raw__objectp(this, cause));}

f2ptr object__new(f2ptr cause) {
  return f2__object__new(cause, nil, frame__new_empty(cause));
}

def_pcfunk0(object__new, return object__new(this_cause));

// this lookup fails if binding is not strictly in local frame of object
f2ptr object__lookup_local_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  return frame__lookup_type_var_assignment_cons(cause, f2object__frame(this, cause), type, var, __type_variable_not_defined__symbol);
}

// this lookup first attempts to find a local binding, but also checks all inherited type frames for type bindings.
f2ptr object__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  pause_gc();
  f2ptr assignment_cons = object__lookup_local_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __type_variable_not_defined__symbol) {
    resume_gc(); return assignment_cons;
  }
  // cycle through type bindings here if there is no local binding.
  f2ptr type_iter = f2object__types(this, cause);
  while (type_iter) {
    f2ptr parent_type = f2cons__car(type_iter, cause);
    assignment_cons = object_type__lookup_type_var_assignment_cons(cause, parent_type, type, var);
    if (assignment_cons != __type_variable_not_defined__symbol) {
      resume_gc(); return assignment_cons;
    }
    type_iter = f2cons__cdr(type_iter, cause);
  }
  // return exception
  resume_gc(); return assignment_cons;
}

// this add only modifies the local object frame
void object__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  frame__add_type_var_value(cause, f2object__frame(this, cause), type, var, value);
}

// this lookup first attempts the local object frame and then tries to find a type frame binding
f2ptr object__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  pause_gc();
  f2ptr assignment_cons = object__lookup_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __type_variable_not_defined__symbol) {
    f2ptr value = f2cons__cdr(assignment_cons, cause);
    resume_gc(); return value;
  }
  // return exception
  resume_gc(); return assignment_cons;
}

f2ptr object__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  pause_gc();
  f2ptr assignment_cons = object__lookup_local_type_var_assignment_cons(cause, this, type, var);
  if (assignment_cons != __type_variable_not_defined__symbol) {
    f2cons__cdr__set(assignment_cons, cause, value);
    // success
    resume_gc(); return nil;
  }
  // return exception
  resume_gc(); return assignment_cons;
}

// end of object

void f2__primobject_object__reinitialize_globalvars() {
  __object__symbol = f2symbol__new(initial_cause(), strlen("object"), (u8*)"object");
}

void f2__primobject_object__initialize() {
  pause_gc();
  f2__primobject_object__reinitialize_globalvars();
  
  f2__primcfunk__init(object__new);
  
  environment__add_var_value(initial_cause(), global_environment(), __object__symbol, nil);
  
  resume_gc();
  try_gc();
}

