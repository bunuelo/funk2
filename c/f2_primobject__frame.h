// 
// Copyright (c) 2007-2010 Bo Morgan.
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

// frame

typedef struct funk2_object_type__frame__slot_s funk2_object_type__frame__slot_t;
declare_object_type_2_slot(frame, new_type_mutex, type_ptypehash,
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
			   f2ptr equals_hash_value__loop_free__symbol;
			   f2ptr equals_hash_value__loop_free__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   f2ptr part_not_contained_by__symbol;
			   f2ptr part_not_contained_by__funk;
			   f2ptr as__graph__symbol;
			   f2ptr as__graph__funk;
			   );

#endif // F2__PRIMOBJECT__PTYPEHASH__TYPES__H

#ifndef F2__PRIMOBJECT__FRAME__H
#define F2__PRIMOBJECT__FRAME__H

#include "f2_primobjects.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__environment.h"

// typedframe

boolean_t raw__typedframe__is_type(f2ptr cause, f2ptr this);
f2ptr      f2__typedframe__is_type(f2ptr cause, f2ptr this);
f2ptr      f2__typedframe__type(f2ptr cause, f2ptr this);


// frame

declare_primobject_2_slot(frame, new_type_mutex, type_ptypehash);

f2ptr  f2__frame__new                            (f2ptr cause, f2ptr slot_value_pairs);
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
f2ptr raw__frame__type_var__mapc_slot_names      (f2ptr cause, f2ptr this, f2ptr type, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data);
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

f2ptr f2frame__primobject_type__new_aux(f2ptr cause);

#define frame__iteration(cause, this, type_slot_name, slot_name, slot_value, code) \
  ptypehash__iteration(cause, f2frame__type_ptypehash(this, cause), type_slot_name, type_slot_ptypehash, \
                       ptypehash__iteration(cause, type_slot_ptypehash, slot_name, slot_value, \
                       code;))

#define frame__var__iteration(cause, this, slot_name, slot_value, code) \
  ptypehash__iteration(cause, f2__ptypehash__lookup(cause, f2frame__type_ptypehash(this, cause), __funk2.primobject__frame.variable__symbol), slot_name, slot_value, \
                       code;)

// **

void f2__primobject_frame__reinitialize_globalvars();
void f2__primobject_frame__initialize();

#endif // F2__PRIMOBJECT__FRAME__H

