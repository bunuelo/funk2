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

#ifndef F2__PRIMOBJECT__FRAME__TYPES__H
#define F2__PRIMOBJECT__FRAME__TYPES__H

typedef struct funk2_object_type__frame__slot_s funk2_object_type__frame__slot_t;

// frame

struct funk2_object_type__frame__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_type_mutex__symbol;
  f2ptr new_type_mutex__funk;
  f2ptr new_type_mutex__set__symbol;
  f2ptr new_type_mutex__set__funk;
  f2ptr type_ptypehash__symbol;
  f2ptr type_ptypehash__funk;
  f2ptr type_ptypehash__set__symbol;
  f2ptr type_ptypehash__set__funk;
  f2ptr add_type_var_value__symbol;
  f2ptr add_type_var_value__funk;
  f2ptr lookup_type_var_assignment_cons__symbol;
  f2ptr lookup_type_var_assignment_cons__funk;
  f2ptr lookup_type_var_value__symbol;
  f2ptr lookup_type_var_value__funk;
  f2ptr type_var_value__set__symbol;
  f2ptr type_var_value__set__funk;
  f2ptr type_var__slot_names__symbol;
  f2ptr type_var__slot_names__funk;
  f2ptr copy__symbol;
  f2ptr copy__funk;
  f2ptr copy_slots__symbol;
  f2ptr copy_slots__funk;
  f2ptr check_has_type_slot__symbol;
  f2ptr check_has_type_slot__funk;
};

#endif // F2__PRIMOBJECT__PTYPEHASH__TYPES__H

#ifndef F2__PRIMOBJECT__FRAME__H
#define F2__PRIMOBJECT__FRAME__H

#include "f2_primobjects.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__environment.h"

// typedframe

boolean_t raw__typedframe__is_type(f2ptr cause, f2ptr this);
f2ptr f2__typedframe__is_type(f2ptr cause, f2ptr this);
f2ptr f2__typedframe__type(f2ptr cause, f2ptr this);


// frame

boolean_t raw__frame__is_type(f2ptr cause, f2ptr x);
f2ptr f2__frame__is_type(f2ptr cause, f2ptr x);
f2ptr f2frame__new(f2ptr cause);
#define f2primobject__is_frame(this, cause) raw__eq(cause, f2primobject__type(this, cause), __funk2.primobject__frame.frame__symbol)

defprimobject__static_slot__prototype(frame__new_type_mutex);
#define f2frame__new_type_mutex(            this, cause)        primobject__static_slot__accessor(  this, frame__new_type_mutex, cause)
#define f2frame__new_type_mutex__set(       this, cause, value) primobject__static_slot__set(       this, frame__new_type_mutex, cause, value)
#define f2frame__new_type_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, frame__new_type_mutex, cause)
#define f2frame__new_type_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, frame__new_type_mutex, cause)
#define f2frame__new_type_mutex__cause(     this, cause)        primobject__static_slot__cause(     this, frame__new_type_mutex, cause)

defprimobject__static_slot__prototype(frame__type_ptypehash);
#define f2frame__type_ptypehash(            this, cause)        primobject__static_slot__accessor(  this, frame__type_ptypehash, cause)
#define f2frame__type_ptypehash__set(       this, cause, value) primobject__static_slot__set(       this, frame__type_ptypehash, cause, value)
#define f2frame__type_ptypehash__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, frame__type_ptypehash, cause)
#define f2frame__type_ptypehash__trace(     this, cause)        primobject__static_slot__trace(     this, frame__type_ptypehash, cause)
#define f2frame__type_ptypehash__cause(     this, cause)        primobject__static_slot__cause(     this, frame__type_ptypehash, cause)

f2ptr  f2__frame__new                            (f2ptr cause);
f2ptr  f2__frame__add_type_var_value             (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr  f2__frame__var_ptypehash                  (f2ptr cause, f2ptr this);
f2ptr  f2__frame__funkvar_ptypehash              (f2ptr cause, f2ptr this);
f2ptr  f2__frame__add_var_value                  (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
f2ptr  f2__frame__add_funkvar_value              (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
f2ptr  f2__frame__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value);
f2ptr  f2__frame__lookup_type_var_value          (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value);              // *
f2ptr  f2__frame__type_var_value__set            (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value, f2ptr not_defined_value); // *
f2ptr  f2__frame__lookup_var_assignment_cons     (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);
f2ptr  f2__frame__lookup_var_value               (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);                          // *
f2ptr  f2__frame__var_value__set                 (f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value);             // *
f2ptr  f2__frame__lookup_funkvar_assignment_cons (f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value);
f2ptr  f2__frame__lookup_funkvar_value           (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr not_defined_value);                      // *
f2ptr  f2__frame__funkvar_value__set             (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value, f2ptr not_defined_value);         // *
f2ptr raw__frame__type_var__mapc_slot_names(f2ptr cause, f2ptr this, f2ptr type, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data);
f2ptr  f2__frame__type_var__slot_names           (f2ptr cause, f2ptr this, f2ptr type);

boolean_t raw__frame__check_has_type_slot(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr slot_name);
f2ptr      f2__frame__check_has_type_slot(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr slot_name);

typedef struct funk2_primobject__frame_s {
  f2ptr frame__symbol;
  f2ptr variable__symbol;
  f2ptr funk_variable__symbol;
  f2ptr type_variable_not_defined__larva;
  f2ptr type_variable_not_defined__symbol;
} funk2_primobject__frame_t;

void funk2_primobject__frame__init(   funk2_primobject__frame_t* this);
void funk2_primobject__frame__reinit( funk2_primobject__frame_t* this);
void funk2_primobject__frame__destroy(funk2_primobject__frame_t* this);

f2ptr f2frame__primobject_type__new(f2ptr cause);

#define frame__iteration(cause, this, type_slot_name, slot_name, slot_value, code) \
  ptypehash__iteration(cause, f2frame__type_ptypehash(this, cause), type_slot_name, type_slot_ptypehash, \
                       ptypehash__iteration(cause, type_slot_ptypehash, slot_name, slot_value, \
                       code;))

// **

void f2__primobject_frame__reinitialize_globalvars();
void f2__primobject_frame__initialize();

#endif // F2__PRIMOBJECT__FRAME__H

