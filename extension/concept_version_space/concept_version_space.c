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


f2ptr raw__concept_version_space_example__lookup_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, this);
  return raw__ptypehash__lookup(cause, value_variable_name_ptypehash, variable_name);
}

f2ptr f2__concept_version_space_example__lookup_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  return raw__concept_version_space_example__lookup_variable_value(cause, this, variable_name);
}
export_cefunk2(concept_version_space_example__lookup_variable_value, this, variable_name, 0, "Lookup a variable value from this concept_version_space_example.");


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
  assert_argument_type(concept_version_space_example, this);
  assert_argument_type(terminal_print_frame,          terminal_print_frame);
  return raw__concept_version_space_example__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(concept_version_space_example__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__concept_version_space_example_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_example_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable_value"),        f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_example__add_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lookup_variable_value"),     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_example__lookup_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_example__terminal_print_with_frame")));}
  return this;
}


// concept_version_space_hypothesis

def_ceframe2(concept_version_space, concept_version_space_hypothesis, positive, value_variable_name_ptypehash);

f2ptr raw__concept_version_space_hypothesis__new(f2ptr cause, f2ptr positive) {
  f2ptr value_variable_name_ptypehash = f2__ptypehash__new(cause);
  return f2concept_version_space_hypothesis__new(cause, positive, value_variable_name_ptypehash);
}

f2ptr f2__concept_version_space_hypothesis__new(f2ptr cause, f2ptr positive) {
  return raw__concept_version_space_hypothesis__new(cause, positive);
}
export_cefunk1(concept_version_space_hypothesis__new, positive, 0, "Returns a new concept_version_space_hypothesis object.");


f2ptr raw__concept_version_space_hypothesis__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  raw__ptypehash__add(cause, value_variable_name_ptypehash, variable_name, value);
  return nil;
}

f2ptr f2__concept_version_space_hypothesis__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  return raw__concept_version_space_hypothesis__add_variable_value(cause, this, variable_name, value);
}
export_cefunk3(concept_version_space_hypothesis__add_variable_value, this, variable_name, value, 0, "Adds a variable value to this concept_version_space_hypothesis.");


f2ptr raw__concept_version_space_hypothesis__lookup_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  return raw__ptypehash__lookup(cause, value_variable_name_ptypehash, variable_name);
}

f2ptr f2__concept_version_space_hypothesis__lookup_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  return raw__concept_version_space_hypothesis__lookup_variable_value(cause, this, variable_name);
}
export_cefunk2(concept_version_space_hypothesis__lookup_variable_value, this, variable_name, 0, "Lookup a variable value from this concept_version_space_hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr positive                      = raw__concept_version_space_hypothesis__positive(                     cause, this);
  f2ptr example__positive             = raw__concept_version_space_example__positive(                        cause, example);
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  ptypehash__iteration(cause, value_variable_name_ptypehash, variable_name, value,
		       if (! raw__eq(cause, value, new__symbol(cause, "?"))) {
			 if (raw__eq(cause, value, new__symbol(cause, "-"))) {
			   return f2bool__new(! ((positive != nil) == (example__positive != nil)));
			 }
			 f2ptr example_value = raw__concept_version_space_example__lookup_variable_value(cause, example, variable_name);
			 if (! raw__eq(cause, value, example_value)) {
			   return f2bool__new(! ((positive != nil) == (example__positive != nil)));
			 }
		       }
		       );
  return f2bool__new((positive != nil) == (example__positive != nil));
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_example,    example);
  return raw__concept_version_space_hypothesis__is_consistent_with_example(cause, this, example);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_example, this, example, 0, "Returns whether or not this hypothesis is consistent with the given example.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_hypothesis__helper(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  f2ptr positive                      = raw__concept_version_space_hypothesis__positive(                     cause, this);
  f2ptr hypothesis__positive          = raw__concept_version_space_hypothesis__positive(                     cause, hypothesis);
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  ptypehash__iteration(cause, value_variable_name_ptypehash, variable_name, value,
		       if (! raw__eq(cause, value, new__symbol(cause, "?"))) {
			 if (raw__eq(cause, value, new__symbol(cause, "-"))) {
			   return f2bool__new(! ((positive != nil) == (hypothesis__positive != nil)));
			 }
			 f2ptr hypothesis_value = raw__concept_version_space_hypothesis__lookup_variable_value(cause, hypothesis, variable_name);
			 if (! raw__eq(cause, value, hypothesis_value)) {
			   return f2bool__new(! ((positive != nil) == (hypothesis__positive != nil)));
			 }
		       }
		       );
  return f2bool__new((positive != nil) == (hypothesis__positive != nil));
}

f2ptr raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  return ((raw__concept_version_space_hypothesis__is_consistent_with_hypothesis__helper(cause, this, hypothesis) != nil) &&
	  (raw__concept_version_space_hypothesis__is_consistent_with_hypothesis__helper(cause, hypothesis, this) != nil));
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_hypothesis, this, hypothesis, 0, "Returns whether or not this hypothesis is consistent with the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this)));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "positive"), f2__concept_version_space_hypothesis__positive(cause, this));
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
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable_value"),            f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__add_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lookup_variable_value"),         f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__lookup_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_example"),    f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_example")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_hypothesis"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__terminal_print_with_frame")));}
  return this;
}


// concept_version_space

def_ceframe2(concept_version_space, concept_version_space, specific_hypotheses, general_hypotheses);

f2ptr raw__concept_version_space__new(f2ptr cause) {
  f2ptr specific_hypotheses = f2list1__new(cause, f2__concept_version_space_hypothesis__new(cause, f2bool__new(boolean__false)));
  f2ptr general_hypotheses  = f2list1__new(cause, f2__concept_version_space_hypothesis__new(cause, f2bool__new(boolean__true)));
  return f2concept_version_space__new(cause, specific_hypotheses, general_hypotheses);
}

f2ptr f2__concept_version_space__new(f2ptr cause) {
  return raw__concept_version_space__new(cause);
}
export_cefunk0(concept_version_space__new, 0, "Returns a new concept_version_space object.");


f2ptr raw__concept_version_space__train_on_example(f2ptr cause, f2ptr this, f2ptr example) {
  
  return nil;
}

f2ptr f2__concept_version_space__train_on_example(f2ptr cause, f2ptr this, f2ptr example) {
  return raw__concept_version_space__train_on_example(cause, this, example);
}
export_cefunk2(concept_version_space__train_on_example, this, example, 0, "Trains this concept_version_space on the given example.");


f2ptr f2__concept_version_space_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "train_on_example"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space__train_on_example")));}
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


