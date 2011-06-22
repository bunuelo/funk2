// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#include "concept_version_space.h"

// concept_version_space_variable

def_ceframe2(concept_version_space, concept_version_space_variable, name, value_set);

f2ptr raw__concept_version_space_variable__new(f2ptr cause, f2ptr name) {
  f2ptr value_set = f2__set__new(cause);
  return f2concept_version_space_variable__new(cause, name, value_set);
}

f2ptr f2__concept_version_space_variable__new(f2ptr cause, f2ptr name) {
  return raw__concept_version_space_variable__new(cause, name);
}
export_cefunk1(concept_version_space_variable__new, name, 0, "Returns a new concept_version_space_variable object.");


f2ptr raw__concept_version_space_variable__add_value(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr value_set = raw__concept_version_space_variable__value_set(cause, this);
  raw__set__add(cause, value_set, value);
  return nil;
}

f2ptr f2__concept_version_space_variable__add_value(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__concept_version_space_variable__add_value(cause, this, value);
}
export_cefunk2(concept_version_space_variable__add_value, this, value, 0, "Adds a value to this concept_version_space_variable.");


f2ptr f2__concept_version_space_variable_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_variable_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_value"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_variable__add_value")));}
  return this;
}


// concept_version_space_example

def_ceframe2(concept_version_space, concept_version_space_example, positive, value_variable_name_ptypehash);

f2ptr raw__concept_version_space_example__new(f2ptr cause, f2ptr positive) {
  f2ptr value_variable_name_ptypehash = f2__ptypehash__new(cause);
  return f2concept_version_space_example__new(cause, positive, value_variable_name_ptypehash);
}

f2ptr f2__concept_version_space_example__new(f2ptr cause, f2ptr positive) {
  return raw__concept_version_space_example__new(cause, positive);
}
export_cefunk1(concept_version_space_example__new, positive, 0, "Returns a new concept_version_space_example object.");


f2ptr raw__concept_version_space_example__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, this);
  raw__ptypehash__add(cause, value_variable_name_ptypehash, variable_name, value);
  return nil;
}

f2ptr f2__concept_version_space_example__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  return raw__concept_version_space_example__add_variable_value(cause, this, variable_name, value);
}
export_cefunk3(concept_version_space_example__add_variable_value, this, variable_name, value, 0, "Adds a variable value to this concept_version_space_example.");


f2ptr raw__concept_version_space_example__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this)));
    f2ptr value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, this);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "positive"), f2__concept_version_space_example__positive(cause, this));
    ptypehash__iteration(cause, value_variable_name_ptypehash, key, value,
			 f2__frame__add_var_value(cause, frame, key, value);
			 );
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__concept_version_space_example__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(concept_version_space_example,       this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__concept_version_space_example__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(concept_version_space_example__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__concept_version_space_example_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_example_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable_value"),        f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_example__add_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_example__terminal_print_with_frame")));}
  return this;
}


// concept_version_space_hypothesis

def_ceframe1(concept_version_space, concept_version_space_hypothesis, value_variable_name_ptypehash);

f2ptr raw__concept_version_space_hypothesis__new(f2ptr cause) {
  f2ptr value_variable_name_ptypehash = f2__ptypehash__new(cause);
  return f2concept_version_space_hypothesis__new(cause, value_variable_name_ptypehash);
}

f2ptr f2__concept_version_space_hypothesis__new(f2ptr cause) {
  return raw__concept_version_space_hypothesis__new(cause);
}
export_cefunk0(concept_version_space_hypothesis__new, 0, "Returns a new concept_version_space_hypothesis object.");


f2ptr raw__concept_version_space_hypothesis__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  raw__ptypehash__add(cause, value_variable_name_ptypehash, variable_name, value);
  return nil;
}

f2ptr f2__concept_version_space_hypothesis__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  return raw__concept_version_space_hypothesis__add_variable_value(cause, this, variable_name, value);
}
export_cefunk3(concept_version_space_hypothesis__add_variable_value, this, variable_name, value, 0, "Adds a variable value to this concept_version_space_hypothesis.");


/*
f2ptr raw__concept_version_space_hypothesis__is_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  ptypehash__iteration(cause, value_variable_name_ptypehash, variable_name, value,
		       
		       );
}
*/

f2ptr raw__concept_version_space_hypothesis__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this)));
    f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
    ptypehash__iteration(cause, value_variable_name_ptypehash, key, value,
			 f2__frame__add_var_value(cause, frame, key, value);
			 );
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__concept_version_space_hypothesis__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(terminal_print_frame,             terminal_print_frame);
  return raw__concept_version_space_hypothesis__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(concept_version_space_hypothesis__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__concept_version_space_hypothesis_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_hypothesis_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable_value"),        f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__add_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__terminal_print_with_frame")));}
  return this;
}


// concept_version_space

def_ceframe1(concept_version_space, concept_version_space, variable_ptypehash);

f2ptr raw__concept_version_space__new(f2ptr cause) {
  f2ptr variable_ptypehash = f2__ptypehash__new(cause);
  return f2concept_version_space__new(cause, variable_ptypehash);
}

f2ptr f2__concept_version_space__new(f2ptr cause) {
  return raw__concept_version_space__new(cause);
}
export_cefunk0(concept_version_space__new, 0, "Returns a new concept_version_space object.");


f2ptr raw__concept_version_space__add_variable(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr variable_ptypehash             = raw__concept_version_space__variable_ptypehash(cause, this);
  f2ptr concept_version_space_variable = f2__concept_version_space_variable__new(cause, name);
  raw__ptypehash__add(cause, variable_ptypehash, name, concept_version_space_variable);
  return nil;
}

f2ptr f2__concept_version_space__add_variable(f2ptr cause, f2ptr this, f2ptr name) {
  return raw__concept_version_space__add_variable(cause, this, name);
}
export_cefunk2(concept_version_space__add_variable, this, name, 0, "Adds a new variable key to this concept_version_space.");


f2ptr f2__concept_version_space_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space__add_variable")));}
  return this;
}




// **

f2ptr f2__concept_version_space__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(concept_version_space__core_extension__ping, 0, "");

f2ptr f2__concept_version_space__core_extension__initialize(f2ptr cause) {
  status("concept_version_space initialized.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__initialize, 0, "");

f2ptr f2__concept_version_space__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "concept_version_space_variable"),   f2__concept_version_space_variable_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space_example"),    f2__concept_version_space_example_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space_hypothesis"), f2__concept_version_space_hypothesis_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space"),            f2__concept_version_space_type__new_aux(cause));
  status("concept_version_space types defined.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__define_types, 0, "");

f2ptr f2__concept_version_space__core_extension__destroy(f2ptr cause) {
  status("concept_version_space destroyed.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__destroy, 0, "");


