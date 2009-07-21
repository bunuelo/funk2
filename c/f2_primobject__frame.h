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

#ifndef F2__PRIMOBJECT__FRAME__H
#define F2__PRIMOBJECT__FRAME__H

#include "f2_primobjects.h"
#include "f2_primobject__hashtable.h"
#include "f2_primobject__environment.h"

// default variable types

extern f2ptr __frame__variable_type__symbol;
extern f2ptr __frame__funk_variable_type__symbol;

// frame

extern f2ptr __frame__symbol;
boolean_t raw__frame__is_type(f2ptr cause, f2ptr x);
f2ptr f2__frame__is_type(f2ptr cause, f2ptr x);
f2ptr f2frame__new(f2ptr cause, f2ptr var_hashtable, f2ptr funkvar_hashtable);
#define f2primobject__is_frame(this, cause) raw__eq(cause, f2primobject__type(this, cause), __frame__symbol)

defprimobject__static_slot__prototype(frame__type_hashtable);
#define f2frame__type_hashtable(            this, cause)        primobject__static_slot__accessor(  this, frame__type_hashtable, cause)
#define f2frame__type_hashtable__set(       this, cause, value) primobject__static_slot__set(       this, frame__type_hashtable, cause, value)
#define f2frame__type_hashtable__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, frame__type_hashtable, cause)
#define f2frame__type_hashtable__trace(     this, cause)        primobject__static_slot__trace(     this, frame__type_hashtable, cause)
#define f2frame__type_hashtable__cause(     this, cause)        primobject__static_slot__cause(     this, frame__type_hashtable, cause)

extern f2ptr __type_variable_not_defined__exception;

void  frame__add_type_var_value             (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr frame__var_hashtable                  (f2ptr cause, f2ptr this);
f2ptr frame__funkvar_hashtable              (f2ptr cause, f2ptr this);
void  frame__add_var_value                  (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
void  frame__add_funkvar_value              (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
f2ptr frame__new_empty                      (f2ptr cause);
f2ptr frame__new_empty_globalsize           (f2ptr cause);
f2ptr frame__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value);
f2ptr frame__lookup_type_var_value          (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value);              // *
f2ptr frame__type_var_value__set            (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value, f2ptr not_defined_value); // *
f2ptr frame__lookup_var_assignment_cons     (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);
f2ptr frame__lookup_var_value               (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);                          // *
f2ptr frame__var_value__set                 (f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value);             // *
f2ptr frame__lookup_funkvar_assignment_cons (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);
f2ptr frame__lookup_funkvar_value           (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr not_defined_value);                      // *
f2ptr frame__funkvar_value__set             (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value, f2ptr not_defined_value);         // *
f2ptr frame__type_var__slot_names           (f2ptr cause, f2ptr this, f2ptr type);

void f2__primobject_frame__reinitialize_globalvar__symbols();
void f2__primobject_frame__reinitialize_globalvar__exceptions();
void f2__primobject_frame__reinitialize_globalvars();
void f2__primobject_frame__initialize();

#endif // F2__PRIMOBJECT__FRAME__H

