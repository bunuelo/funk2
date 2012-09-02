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


// concept_version_space_hypothesis_callback

def_ceframe2(concept_version_space, concept_version_space_hypothesis_callback,
	     funk,
	     args);

f2ptr raw__concept_version_space_hypothesis_callback__new(f2ptr cause, f2ptr funk, f2ptr args) {
  return f2concept_version_space_hypothesis_callback__new(cause, funk, args);
}

f2ptr f2__concept_version_space_hypothesis_callback__new(f2ptr cause, f2ptr funk, f2ptr args) {
  assert_argument_type(funkable, funk);
  assert_argument_type(conslist, args);
  return raw__concept_version_space_hypothesis_callback__new(cause, funk, args);
}
export_cefunk2(concept_version_space_hypothesis_callback__new, funk, args, 0, "Returns a new concept_version_space_hypothesis_callback object.");

f2ptr raw__concept_version_space_hypothesis_callback__call(f2ptr cause, f2ptr this) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = raw__concept_version_space_hypothesis_callback__funk(cause, this);
  f2ptr args  = raw__concept_version_space_hypothesis_callback__args(cause, this);
  return catch_value(f2__force_funk_apply(cause, fiber, funk, args),
		     f2list4__new(cause,
				  new__symbol(cause, "description"), new__string(cause, "Bug encountered while executing callback funk for concept_version_space_hypothesis_callback."),
				  new__symbol(cause, "this"),        this));
}

f2ptr f2__concept_version_space_hypothesis_callback__call(f2ptr cause, f2ptr this) {
  assert_argument_type(concept_version_space_hypothesis_callback, this);
  return raw__concept_version_space_hypothesis_callback__call(cause, this);
}
export_cefunk1(concept_version_space_hypothesis_callback__call, this, 0, "Calls this hypothesis_version_space_hypothesis_callback.");


f2ptr f2__concept_version_space_hypothesis_callback_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_hypothesis_callback_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "call"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis_callback__call")));}
  return this;
}


// concept_version_space_hypothesis

def_ceframe4(concept_version_space, concept_version_space_hypothesis,
	     value_variable_name_ptypehash,
	     removal_callbacks_cmutex,
	     removal_callbacks,
	     is_removed);

f2ptr raw__concept_version_space_hypothesis__new(f2ptr cause) {
  f2ptr value_variable_name_ptypehash = f2__ptypehash__new(cause);
  f2ptr removal_callbacks_cmutex      = f2cmutex__new(cause);
  f2ptr removal_callbacks             = nil;
  f2ptr is_removed                    = nil;
  return f2concept_version_space_hypothesis__new(cause,
						 value_variable_name_ptypehash,
						 removal_callbacks_cmutex,
						 removal_callbacks,
						 is_removed);
}

f2ptr f2__concept_version_space_hypothesis__new(f2ptr cause) {
  return raw__concept_version_space_hypothesis__new(cause);
}
export_cefunk0(concept_version_space_hypothesis__new, 0, "Returns a new concept_version_space_hypothesis object.");


f2ptr raw__concept_version_space_hypothesis__new_copy(f2ptr cause, f2ptr this) {
  f2ptr value_variable_name_ptypehash             = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  f2ptr hypothesis                                = f2__concept_version_space_hypothesis__new(cause);
  f2ptr hypothesis__value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, hypothesis);
  ptypehash__iteration(cause, value_variable_name_ptypehash, variable_name, value,
		       raw__ptypehash__add(cause, hypothesis__value_variable_name_ptypehash, variable_name, value);
		       );
  return hypothesis;
}

f2ptr f2__concept_version_space_hypothesis__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(concept_version_space_hypothesis, this);
  return raw__concept_version_space_hypothesis__new_copy(cause, this);
}
export_cefunk1(concept_version_space_hypothesis__new_copy, this, 0, "Returns a new copy of this concept_version_space_hypothesis object.");


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
  if (! raw__ptypehash__contains(cause, value_variable_name_ptypehash, variable_name)) {
    return f2larva__new(cause, 245126, nil);
  } else {
    return raw__ptypehash__lookup(cause, value_variable_name_ptypehash, variable_name);
  }
}

f2ptr f2__concept_version_space_hypothesis__lookup_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  return raw__concept_version_space_hypothesis__lookup_variable_value(cause, this, variable_name);
}
export_cefunk2(concept_version_space_hypothesis__lookup_variable_value, this, variable_name, 0, "Lookup a variable value from this concept_version_space_hypothesis.");


f2ptr raw__concept_version_space_hypothesis__include_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  if (! raw__ptypehash__contains(cause, value_variable_name_ptypehash, variable_name)) {
    return f2larva__new(cause, 24612616, nil);
  } else {
    f2ptr current_value = raw__ptypehash__lookup(cause, value_variable_name_ptypehash, variable_name);
    if (raw__eq(cause, current_value, new__symbol(cause, "-"))) {
      raw__ptypehash__add(cause, value_variable_name_ptypehash, variable_name, value);
    } else if (! raw__eq(cause, current_value, value)) {
      raw__ptypehash__add(cause, value_variable_name_ptypehash, variable_name, new__symbol(cause, "?"));
    }
  }
  return nil;
}

f2ptr f2__concept_version_space_hypothesis__include_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value) {
  assert_argument_type(concept_version_space_hypothesis, this);
  return raw__concept_version_space_hypothesis__include_variable_value(cause, this, variable_name, value);
}
export_cefunk3(concept_version_space_hypothesis__include_variable_value, this, variable_name, value, 0, "Include a variable value in being consistent with this concept_version_space_hypothesis by generalizing the hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr example__positive = raw__concept_version_space_example__positive(cause, example);
  if (example__positive != nil) {
    f2ptr example__value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, example);
    ptypehash__iteration(cause, example__value_variable_name_ptypehash, example__variable_name, example__value,
			 f2ptr hypothesis__value = raw__concept_version_space_hypothesis__lookup_variable_value(cause, this, example__variable_name);
			 if (! raw__eq(cause, hypothesis__value, new__symbol(cause, "?"))) {
			   if (raw__eq(cause, hypothesis__value, new__symbol(cause, "-")) ||
			       (! raw__eq(cause, hypothesis__value, example__value))) {
			     return f2bool__new(boolean__false);
			   }
			 }
			 );
    return f2bool__new(boolean__true);
  } else { // (example__positive == nil)
    f2ptr example__value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, example);
    ptypehash__iteration(cause, example__value_variable_name_ptypehash, example__variable_name, example__value,
			 f2ptr hypothesis__value = raw__concept_version_space_hypothesis__lookup_variable_value(cause, this, example__variable_name);
			 if (! raw__eq(cause, hypothesis__value, new__symbol(cause, "-"))) {
			   if (raw__eq(cause, hypothesis__value, new__symbol(cause, "?")) ||
			       (raw__eq(cause, hypothesis__value, example__value))) {
			     return f2bool__new(boolean__false);
			   }
			 }
			 );
    return f2bool__new(boolean__true);
  }
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_example,    example);
  return raw__concept_version_space_hypothesis__is_consistent_with_example(cause, this, example);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_example, this, example, 0, "Returns whether or not this hypothesis is consistent with the given example.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  f2ptr value_variable_name_ptypehash = raw__concept_version_space_hypothesis__value_variable_name_ptypehash(cause, this);
  ptypehash__iteration(cause, value_variable_name_ptypehash, variable_name, value,
		       if (! raw__eq(cause, value, new__symbol(cause, "?"))) {
			 f2ptr hypothesis__value = raw__concept_version_space_hypothesis__lookup_variable_value(cause, hypothesis, variable_name);
			 if (raw__eq(cause, value, new__symbol(cause, "-"))) {
			   if (! raw__eq(cause, hypothesis__value, new__symbol(cause, "-"))) {
			     return f2bool__new(boolean__false);
			   }
			 } else {
			   if ((! raw__eq(cause, hypothesis__value, new__symbol(cause, "-"))) &&
			       (! raw__eq(cause, value, hypothesis__value))) {
			     return f2bool__new(boolean__false);
			   }
			 }
		       }
		       );
  return f2bool__new(boolean__true);
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis, this, hypothesis, 0, "Returns true if this hypothesis is consistent with or more general than the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  return ((raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(cause, this, hypothesis) != nil) &&
	  (raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(cause, hypothesis, this) != nil));
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_hypothesis, this, hypothesis, 0, "Returns whether or not this hypothesis is consistent with the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_more_general_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  return (raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(cause, this, hypothesis) &&
	  (raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(cause, this, hypothesis) == nil));
}

f2ptr f2__concept_version_space_hypothesis__is_more_general_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_more_general_than_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_more_general_than_hypothesis, this, hypothesis, 0, "Returns true if this hypothesis is more general than the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  return (raw__concept_version_space_hypothesis__is_more_general_than_hypothesis(cause, hypothesis, this) != nil);
}

f2ptr f2__concept_version_space_hypothesis__is_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_more_specific_than_hypothesis, this, hypothesis, 0, "Returns true if this hypothesis is more specific than the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  return ((raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis(cause, this, hypothesis) != nil) ||
	  (raw__concept_version_space_hypothesis__is_consistent_with_hypothesis(cause, this, hypothesis) != nil));
}

f2ptr f2__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_hypothesis, hypothesis);
  return raw__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(cause, this, hypothesis);
}
export_cefunk2(concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis, this, hypothesis, 0, "Returns true if this hypothesis is consistent with or more specific than the given hypothesis.");


f2ptr raw__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr example__positive = raw__concept_version_space_example__positive(cause, example);
  if (example__positive == nil) {
    // example must be positive in order to generalize based on it.
    return f2larva__new(cause, 232464, nil);
  }
  f2ptr new_hypotheses = nil;
  {
    f2ptr hypothesis                             = raw__concept_version_space_hypothesis__new_copy(cause, this);
    f2ptr example__value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, example);
    ptypehash__iteration(cause, example__value_variable_name_ptypehash, example__variable_name, example__value,
			 raw__concept_version_space_hypothesis__include_variable_value(cause, hypothesis, example__variable_name, example__value);
			 );
    new_hypotheses = f2cons__new(cause, hypothesis, new_hypotheses);
  }
  return new_hypotheses;
}

f2ptr f2__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_example,    example);
  return raw__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example(cause, this, example);
}
export_cefunk2(concept_version_space_hypothesis__minimal_generalizations_consistent_with_example, this, example, 0, "Returns the minimal generalizations of this hypothesis that is also consistent with the given positive example.");


f2ptr raw__concept_version_space_hypothesis__minimal_specializations_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example, f2ptr concept_version_space) {
  f2ptr example__positive = raw__concept_version_space_example__positive(cause, example);
  if (example__positive != nil) {
    // example must be negative in order to specialize based on it.
    return f2larva__new(cause, 232465, nil);
  }
  f2ptr variable_value_set_name_ptypehash = raw__concept_version_space__variable_value_set_name_ptypehash(cause, concept_version_space);
  f2ptr new_hypotheses                    = nil;
  {
    f2ptr example__value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, example);
    ptypehash__iteration(cause, example__value_variable_name_ptypehash, example__variable_name, example__value,
			 // add all *other* variables from concept version space that wouldn't match this one (no negative concepts in conjunctive hypothesis language...).
			 f2ptr possible_variable_value_set = raw__ptypehash__lookup(cause, variable_value_set_name_ptypehash, example__variable_name);
			 set__iteration(cause, possible_variable_value_set, possible__value,
					if (! raw__eq(cause, example__value, possible__value)) {
					  f2ptr hypothesis = raw__concept_version_space_hypothesis__new_copy(cause, this);
					  assert_value(raw__concept_version_space_hypothesis__add_variable_value(cause, hypothesis, example__variable_name, possible__value));
					  new_hypotheses = f2cons__new(cause, hypothesis, new_hypotheses);
					}
					);
			 );
  }
  return new_hypotheses;
}

f2ptr f2__concept_version_space_hypothesis__minimal_specializations_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example, f2ptr concept_version_space) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(concept_version_space_example,    example);
  assert_argument_type(concept_version_space,            concept_version_space);
  return raw__concept_version_space_hypothesis__minimal_specializations_consistent_with_example(cause, this, example, concept_version_space);
}
export_cefunk3(concept_version_space_hypothesis__minimal_specializations_consistent_with_example, this, example, concept_version_space, 0,
	       "Returns the minimal specializations of this hypothesis that is also consistent with the given negative example"
	       "and given other variable values already known in concept_version_space.");


f2ptr raw__concept_version_space_hypothesis__add_removal_callback(f2ptr cause, f2ptr this, f2ptr funk, f2ptr args) {
  f2ptr     callback                 = raw__concept_version_space_hypothesis_callback__new(cause, funk, args);
  f2ptr     removal_callbacks_cmutex = raw__concept_version_space_hypothesis__removal_callbacks_cmutex(cause, this);
  boolean_t already_removed          = boolean__false;
  {
    raw__cmutex__lock(cause, removal_callbacks_cmutex);
    {
      f2ptr is_removed = raw__concept_version_space_hypothesis__is_removed(cause, this);
      if (is_removed != nil) {
	already_removed = boolean__true;
      } else {
	f2ptr removal_callbacks = raw__concept_version_space_hypothesis__removal_callbacks(cause, this);
	removal_callbacks = f2cons__new(cause, callback, removal_callbacks);
	raw__concept_version_space_hypothesis__removal_callbacks__set(cause, this, removal_callbacks);
      }
    }
    raw__cmutex__unlock(cause, removal_callbacks_cmutex);
  }
  if (already_removed) {
    // call immediately
    raw__concept_version_space_hypothesis_callback__call(cause, callback);
  }
  return nil;
}

f2ptr f2__concept_version_space_hypothesis__add_removal_callback(f2ptr cause, f2ptr this, f2ptr funk, f2ptr args) {
  assert_argument_type(concept_version_space_hypothesis, this);
  assert_argument_type(funkable,                         funk);
  assert_argument_type(conslist,                         args);
  return raw__concept_version_space_hypothesis__add_removal_callback(cause, this, funk, args);
}
export_cefunk3(concept_version_space_hypothesis__add_removal_callback, this, funk, args, 0, "Adds removal callback to this hypothesis.");


f2ptr raw__concept_version_space_hypothesis__know_of_removal(f2ptr cause, f2ptr this) {
  f2ptr removal_callbacks_cmutex = raw__concept_version_space_hypothesis__removal_callbacks_cmutex(cause, this);
  f2ptr old_removal_callbacks = nil;
  {
    raw__cmutex__lock(cause, removal_callbacks_cmutex);
    {
      old_removal_callbacks = raw__concept_version_space_hypothesis__removal_callbacks(cause, this);
      raw__concept_version_space_hypothesis__removal_callbacks__set(cause, this, nil);
      raw__concept_version_space_hypothesis__is_removed__set(       cause, this, f2bool__new(boolean__true));
    }
    raw__cmutex__unlock(cause, removal_callbacks_cmutex);
  }
  {
    f2ptr iter = old_removal_callbacks;
    while (iter != nil) {
      f2ptr removal_callback = assert_value(f2__cons__car(cause, iter));
      catch_value(raw__concept_version_space_hypothesis_callback__call(cause, removal_callback),
		  f2list4__new(cause,
			       new__symbol(cause, "description"), new__string(cause, "Bug encountered while calling removal callbacks for concept_version_space_hypothesis."),
			       new__symbol(cause, "this"),        this));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  return nil;
}

f2ptr f2__concept_version_space_hypothesis__know_of_removal(f2ptr cause, f2ptr this) {
  assert_argument_type(concept_version_space_hypothesis, this);
  return raw__concept_version_space_hypothesis__know_of_removal(cause, this);
}
export_cefunk1(concept_version_space_hypothesis__know_of_removal, this, 0, "Informs this hypothesis of its removal from a version space lattice.");


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
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "new_copy"),                                            f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__new_copy")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable_value"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__add_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lookup_variable_value"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__lookup_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "include_variable_value"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__include_variable_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_example"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_example")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_or_more_general_than_hypothesis"),  f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_hypothesis"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_more_general_than_hypothesis"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_more_general_than_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_more_specific_than_hypothesis"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_more_specific_than_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "is_consistent_with_or_more_specific_than_hypothesis"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "minimal_generalizations_consistent_with_example"),     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__minimal_generalizations_consistent_with_example")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "minimal_specializations_consistent_with_example"),     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__minimal_specializations_consistent_with_example")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "know_of_removal"),                                     f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__know_of_removal")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_removal_callback"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__add_removal_callback")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space_hypothesis__terminal_print_with_frame")));}
  return this;
}


// concept_version_space

def_ceframe3(concept_version_space, concept_version_space, variable_value_set_name_ptypehash, specific_hypotheses, general_hypotheses);

f2ptr raw__concept_version_space__new(f2ptr cause) {
  f2ptr variable_value_set_name_ptypehash = f2__ptypehash__new(cause);
  f2ptr specific_hypotheses               = f2list1__new(cause, f2__concept_version_space_hypothesis__new(cause));
  f2ptr general_hypotheses                = f2list1__new(cause, f2__concept_version_space_hypothesis__new(cause));
  return f2concept_version_space__new(cause, variable_value_set_name_ptypehash, specific_hypotheses, general_hypotheses);
}

f2ptr f2__concept_version_space__new(f2ptr cause) {
  return raw__concept_version_space__new(cause);
}
export_cefunk0(concept_version_space__new, 0, "Returns a new concept_version_space object.");


f2ptr raw__concept_version_space__add_variable(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr variable_value_set_name_ptypehash = raw__concept_version_space__variable_value_set_name_ptypehash(cause, this);
  if (! raw__ptypehash__contains(cause, variable_value_set_name_ptypehash, variable_name)) {
    f2ptr specific_hypotheses               = raw__concept_version_space__specific_hypotheses(              cause, this);
    f2ptr general_hypotheses                = raw__concept_version_space__general_hypotheses(               cause, this);
    {
      f2ptr iter = specific_hypotheses;
      while (iter != nil) {
	f2ptr hypothesis = f2__cons__car(cause, iter);
	raw__concept_version_space_hypothesis__add_variable_value(cause, hypothesis, variable_name, new__symbol(cause, "-"));
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = general_hypotheses;
      while (iter != nil) {
	f2ptr hypothesis = f2__cons__car(cause, iter);
	raw__concept_version_space_hypothesis__add_variable_value(cause, hypothesis, variable_name, new__symbol(cause, "?"));
	iter = f2__cons__cdr(cause, iter);
      }
    }
    raw__ptypehash__add(cause, variable_value_set_name_ptypehash, variable_name, f2__set__new(cause));
  }
  return nil;
}

f2ptr raw__concept_version_space__add_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr variable_value) {
  assert_value(raw__concept_version_space__add_variable(cause, this, variable_name));
  f2ptr variable_value_set_name_ptypehash = raw__concept_version_space__variable_value_set_name_ptypehash(cause, this);
  f2ptr variable_value_set                = raw__ptypehash__lookup(cause, variable_value_set_name_ptypehash, variable_name);
  raw__set__add(cause, variable_value_set, variable_value);
  return nil;
}

f2ptr raw__concept_version_space__train_on_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr variable_value_set_name_ptypehash = raw__concept_version_space__variable_value_set_name_ptypehash(cause, this);
  f2ptr general_hypotheses                = raw__concept_version_space__general_hypotheses(cause, this);
  f2ptr specific_hypotheses               = raw__concept_version_space__specific_hypotheses(cause, this);
  f2ptr example__positive                 = raw__concept_version_space_example__positive(cause, example);
  f2ptr all_removed_hypothesis_set        = f2__set__new(cause);
  {
    f2ptr example__value_variable_name_ptypehash = raw__concept_version_space_example__value_variable_name_ptypehash(cause, example);
    ptypehash__iteration(cause, example__value_variable_name_ptypehash, example__variable_name, example_variable_value,
			 if (! raw__ptypehash__contains(cause, variable_value_set_name_ptypehash, example__variable_name)) {
			   assert_value(raw__concept_version_space__add_variable_value(cause, this, example__variable_name, example__value));
			 }
			 );
  }
  if (example__positive != nil) {
    {
      // remove all general_hypotheses that are not consistent with example.
      f2ptr new_general_hypotheses = nil;
      {
	f2ptr iter = general_hypotheses;
	while (iter != nil) {
	  f2ptr general_hypothesis = f2__cons__car(cause, iter);
	  {
	    if (raw__concept_version_space_hypothesis__is_consistent_with_example(cause, general_hypothesis, example) != nil) {
	      new_general_hypotheses = f2cons__new(cause, general_hypothesis, new_general_hypotheses);
	    } else {
	      f2__set__add(cause, all_removed_hypothesis_set, general_hypothesis);
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      general_hypotheses = new_general_hypotheses;
      raw__concept_version_space__general_hypotheses__set(cause, this, general_hypotheses);
    }
    {
      f2ptr removed_specific_hypotheses = nil;
      {
	// remove all specific_hypotheses that are not consistent with example.
	f2ptr new_specific_hypotheses = nil;
	{
	  f2ptr iter = specific_hypotheses;
	  while (iter != nil) {
	    f2ptr specific_hypothesis = f2__cons__car(cause, iter);
	    {
	      if (raw__concept_version_space_hypothesis__is_consistent_with_example(cause, specific_hypothesis, example) != nil) {
		new_specific_hypotheses     = f2cons__new(cause, specific_hypothesis, new_specific_hypotheses);
	      } else {
		removed_specific_hypotheses = f2cons__new(cause, specific_hypothesis, removed_specific_hypotheses);
		f2__set__add(cause, all_removed_hypothesis_set, specific_hypothesis);
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	specific_hypotheses = new_specific_hypotheses;
	raw__concept_version_space__specific_hypotheses__set(cause, this, specific_hypotheses);
      }
      // for each removed specific_hypothesis, add all minimal generalizations that are consistent with example AND are more general than at least one general_hypothesis.
      {
	f2ptr new_specific_hypotheses = specific_hypotheses;
	{
	  f2ptr iter = removed_specific_hypotheses;
	  while (iter != nil) {
	    f2ptr removed_specific_hypothesis = f2__cons__car(cause, iter);
	    {
	      f2ptr removed_specific_hypothesis__minimal_generalizations_consistent_with_example = assert_value(raw__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example(cause, removed_specific_hypothesis, example));
	      {
		f2ptr removed_specific_hypothesis__minimal_generalizations_consistent_with_example__iter = removed_specific_hypothesis__minimal_generalizations_consistent_with_example;
		while (removed_specific_hypothesis__minimal_generalizations_consistent_with_example__iter != nil) {
		  f2ptr removed_specific_hypothesis__minimal_generalization_consistent_with_example = f2__cons__car(cause, removed_specific_hypothesis__minimal_generalizations_consistent_with_example__iter);
		  {
		    {
		      boolean_t is_consistent_or_more_general_than_at_least_one_general_hypothesis = boolean__false;
		      {
			f2ptr general_iter = general_hypotheses;
			while (general_iter != nil) {
			  f2ptr general_hypothesis = f2__cons__car(cause, general_iter);
			  {
			    if (raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis(cause, general_hypothesis, removed_specific_hypothesis__minimal_generalization_consistent_with_example)) {
			      is_consistent_or_more_general_than_at_least_one_general_hypothesis = boolean__true;
			      goto raw__concept_version_space__train_on_example__is_consistent_or_more_general_than_at_least_one_general_hypothesis__done;
			    }
			  }
			  general_iter = f2__cons__cdr(cause, general_iter);
			}
		      }
		    raw__concept_version_space__train_on_example__is_consistent_or_more_general_than_at_least_one_general_hypothesis__done:
		      if (is_consistent_or_more_general_than_at_least_one_general_hypothesis) {
			new_specific_hypotheses = f2cons__new(cause, removed_specific_hypothesis__minimal_generalization_consistent_with_example, new_specific_hypotheses);
		      }
		    }
		  }
		  removed_specific_hypothesis__minimal_generalizations_consistent_with_example__iter = f2__cons__cdr(cause, removed_specific_hypothesis__minimal_generalizations_consistent_with_example__iter);
		}
	      }	
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	specific_hypotheses = new_specific_hypotheses;
	raw__concept_version_space__specific_hypotheses__set(cause, this, specific_hypotheses);
      }
      // remove any specific_hypothesis that is more general than any other specific hypothesis.
      {
	f2ptr new_specific_hypotheses = nil;
	{
	  f2ptr iter = specific_hypotheses;
	  while (iter != nil) {
	    f2ptr specific_hypothesis = f2__cons__car(cause, iter);
	    {
	      boolean_t specific_hypothesis_is_more_general_than_another = boolean__false;
	      {
		f2ptr iter_compare = specific_hypotheses;
		while (iter_compare != nil) {
		  f2ptr specific_hypothesis_compare = f2__cons__car(cause, iter_compare);
		  if (! raw__eq(cause, specific_hypothesis, specific_hypothesis_compare)) {
		    if (raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis(cause, specific_hypothesis, specific_hypothesis_compare)) {
		      specific_hypothesis_is_more_general_than_another = boolean__true;
		      goto raw__concept_version_space__train_on_example__specific_hypothesis_is_more_general_than_another__done;
		    }
		  }
		  iter_compare = f2__cons__cdr(cause, iter_compare);
		}
	      }
	    raw__concept_version_space__train_on_example__specific_hypothesis_is_more_general_than_another__done:
	      if (! specific_hypothesis_is_more_general_than_another) {
		new_specific_hypotheses = f2cons__new(cause, specific_hypothesis, new_specific_hypotheses);
	      } else {
		f2__set__add(cause, all_removed_hypothesis_set, specific_hypothesis);
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	specific_hypotheses = new_specific_hypotheses;
	raw__concept_version_space__specific_hypotheses__set(cause, this, specific_hypotheses);
      }
    }
  } else { // (example__positive == nil)
    {
      // remove all specific_hypotheses that are not consistent with example.
      f2ptr new_specific_hypotheses = nil;
      {
	f2ptr iter = specific_hypotheses;
	while (iter != nil) {
	  f2ptr specific_hypothesis = f2__cons__car(cause, iter);
	  {
	    if (raw__concept_version_space_hypothesis__is_consistent_with_example(cause, specific_hypothesis, example) != nil) {
	      new_specific_hypotheses = f2cons__new(cause, specific_hypothesis, new_specific_hypotheses);
	    } else {
	      f2__set__add(cause, all_removed_hypothesis_set, specific_hypothesis);
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      specific_hypotheses = new_specific_hypotheses;
      raw__concept_version_space__specific_hypotheses__set(cause, this, specific_hypotheses);
    }
    {
      f2ptr removed_general_hypotheses = nil;
      {
	// remove all general_hypotheses that are not consistent with example.
	f2ptr new_general_hypotheses = nil;
	{
	  f2ptr iter = general_hypotheses;
	  while (iter != nil) {
	    f2ptr general_hypothesis = f2__cons__car(cause, iter);
	    {
	      if (raw__concept_version_space_hypothesis__is_consistent_with_example(cause, general_hypothesis, example) != nil) {
		new_general_hypotheses     = f2cons__new(cause, general_hypothesis, new_general_hypotheses);
	      } else {
		removed_general_hypotheses = f2cons__new(cause, general_hypothesis, removed_general_hypotheses);
		f2__set__add(cause, all_removed_hypothesis_set, general_hypothesis);
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	general_hypotheses = new_general_hypotheses;
	raw__concept_version_space__general_hypotheses__set(cause, this, general_hypotheses);
      }
      // for each removed general_hypothesis, add all minimal specializations that are consistent with example AND are more specific than at least one specific_hypothesis.
      {
	f2ptr new_general_hypotheses = general_hypotheses;
	{
	  f2ptr iter = removed_general_hypotheses;
	  while (iter != nil) {
	    f2ptr removed_general_hypothesis = f2__cons__car(cause, iter);
	    {
	      f2ptr removed_general_hypothesis__minimal_specializations_consistent_with_example = assert_value(raw__concept_version_space_hypothesis__minimal_specializations_consistent_with_example(cause, removed_general_hypothesis, example, this));
	      {
		f2ptr removed_general_hypothesis__minimal_specializations_consistent_with_example__iter = removed_general_hypothesis__minimal_specializations_consistent_with_example;
		while (removed_general_hypothesis__minimal_specializations_consistent_with_example__iter != nil) {
		  f2ptr removed_general_hypothesis__minimal_specialization_consistent_with_example = f2__cons__car(cause, removed_general_hypothesis__minimal_specializations_consistent_with_example__iter);
		  {
		    boolean_t is_consistent_or_more_specific_than_at_least_one_specific_hypothesis = boolean__false;
		    {
		      f2ptr specific_iter = specific_hypotheses;
		      while (specific_iter != nil) {
			f2ptr specific_hypothesis = f2__cons__car(cause, specific_iter);
			{
			  if (raw__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(cause, specific_hypothesis, removed_general_hypothesis__minimal_specialization_consistent_with_example)) {
			    is_consistent_or_more_specific_than_at_least_one_specific_hypothesis = boolean__true;
			    goto raw__concept_version_space__train_on_example__is_consistent_or_more_specific_than_at_least_one_specific_hypothesis__done;
			  }
			}
			specific_iter = f2__cons__cdr(cause, specific_iter);
		      }
		    }
		  raw__concept_version_space__train_on_example__is_consistent_or_more_specific_than_at_least_one_specific_hypothesis__done:
		    if (is_consistent_or_more_specific_than_at_least_one_specific_hypothesis) {
		      new_general_hypotheses = f2cons__new(cause, removed_general_hypothesis__minimal_specialization_consistent_with_example, new_general_hypotheses);
		    } else {
		      f2__set__add(cause, all_removed_hypothesis_set, removed_general_hypothesis__minimal_specialization_consistent_with_example);
		    }
		  }
		  removed_general_hypothesis__minimal_specializations_consistent_with_example__iter = f2__cons__cdr(cause, removed_general_hypothesis__minimal_specializations_consistent_with_example__iter);
		}
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	general_hypotheses = new_general_hypotheses;
	raw__concept_version_space__general_hypotheses__set(cause, this, general_hypotheses);
      }
      // remove any general_hypothesis that is more specific than any other general hypothesis.
      {
	f2ptr new_general_hypotheses = nil;
	{
	  f2ptr iter = general_hypotheses;
	  while (iter != nil) {
	    f2ptr general_hypothesis = f2__cons__car(cause, iter);
	    {
	      boolean_t general_hypothesis_is_more_specific_than_another = boolean__false;
	      {
		f2ptr iter_compare = general_hypotheses;
		while (iter_compare != nil) {
		  f2ptr general_hypothesis_compare = f2__cons__car(cause, iter_compare);
		  if (! raw__eq(cause, general_hypothesis, general_hypothesis_compare)) {
		    if (raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis(cause, general_hypothesis, general_hypothesis_compare)) {
		      general_hypothesis_is_more_specific_than_another = boolean__true;
		      goto raw__concept_version_space__train_on_example__general_hypothesis_is_more_specific_than_another__done;
		    }
		  }
		  iter_compare = f2__cons__cdr(cause, iter_compare);
		}
	      }
	    raw__concept_version_space__train_on_example__general_hypothesis_is_more_specific_than_another__done:
	      if (! general_hypothesis_is_more_specific_than_another) {
		new_general_hypotheses = f2cons__new(cause, general_hypothesis, new_general_hypotheses);
	      } else {
		f2__set__add(cause, all_removed_hypothesis_set, general_hypothesis);
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	general_hypotheses = new_general_hypotheses;
	raw__concept_version_space__general_hypotheses__set(cause, this, general_hypotheses);
      }
    }
  }
  // inform each removed hypothesis of its removal
  {
    set__iteration(cause, all_removed_hypothesis_set, removed_hypothesis,
		   catch_value(raw__concept_version_space_hypothesis__know_of_removal(cause, removed_hypothesis),
			       f2list6__new(cause,
					    new__symbol(cause, "description"), new__string(cause, "Bug encountered while informing removed concept_version_space_hypotheses of its removal during training on example."),
					    new__symbol(cause, "this"),        this,
					    new__symbol(cause, "example"),     example));
  		   );
  }
  return nil;
}

f2ptr f2__concept_version_space__train_on_example(f2ptr cause, f2ptr this, f2ptr example) {
  assert_argument_type(concept_version_space,         this);
  assert_argument_type(concept_version_space_example, example);
  return raw__concept_version_space__train_on_example(cause, this, example);
}
export_cefunk2(concept_version_space__train_on_example, this, example, 0, "Trains this concept_version_space on the given example.");


f2ptr raw__concept_version_space__specific_hypotheses_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  f2ptr consistent_hypotheses = nil;
  f2ptr specific_hypotheses = raw__concept_version_space__specific_hypotheses(cause, this);
  {
    f2ptr iter = specific_hypotheses;
    while (iter != nil) {
      f2ptr hypothesis = f2__cons__car(cause, iter);
      if (assert_value(raw__concept_version_space_hypothesis__is_consistent_with_example(cause, hypothesis, example)) != nil) {
	consistent_hypotheses = f2cons__new(cause, hypothesis, consistent_hypotheses);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return consistent_hypotheses;
}

f2ptr f2__concept_version_space__specific_hypotheses_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example) {
  assert_argument_type(concept_version_space,         this);
  assert_argument_type(concept_version_space_example, example);
  return raw__concept_version_space__specific_hypotheses_consistent_with_example(cause, this, example);
}
export_cefunk2(concept_version_space__specific_hypotheses_consistent_with_example, this, example, 0, "Returns all specific hypotheses that are consistent with the given example.");


f2ptr f2__concept_version_space_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "train_on_example"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space__train_on_example")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "specific_hypotheses_consistent_with_example"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space__specific_hypotheses_consistent_with_example")));}
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
  f2__add_type(cause, new__symbol(cause, "concept_version_space_example"),             f2__concept_version_space_example_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space_hypothesis_callback"), f2__concept_version_space_hypothesis_callback_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space_hypothesis"),          f2__concept_version_space_hypothesis_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "concept_version_space"),                     f2__concept_version_space_type__new_aux(cause));
  status("concept_version_space types defined.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__define_types, 0, "");

f2ptr f2__concept_version_space__core_extension__destroy(f2ptr cause) {
  status("concept_version_space destroyed.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__destroy, 0, "");


