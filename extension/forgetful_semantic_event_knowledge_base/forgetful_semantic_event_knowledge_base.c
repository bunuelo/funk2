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

#include "forgetful_semantic_event_knowledge_base.h"


def_ceframe1(forgetful_semantic_event_knowledge_base, remember_token, semantic_time);

f2ptr raw__remember_token__new(f2ptr cause, f2ptr semantic_time) {
  return f2remember_token__new(cause, semantic_time);
}

f2ptr f2__remember_token__new(f2ptr cause, f2ptr semantic_time) {
  assert_argument_type(semantic_time, semantic_time);
  return raw__remember_token__new(cause, semantic_time);
}
export_cefunk1(remember_token__new, semantic_time, 0, "Returns a new remember_token object.");


f2ptr raw__remember_token__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__semantic_time = raw__remember_token__semantic_time(cause, this);
  f2ptr that__semantic_time = raw__remember_token__semantic_time(cause, that);
  return raw__semantic_time__is_less_than(cause, this__semantic_time, that__semantic_time);
}

f2ptr f2__remember_token__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(remember_token, this);
  assert_argument_type(remember_token, that);
  return raw__remember_token__is_less_than(cause, this, that);
}
export_cefunk2(remember_token__is_less_than, this, that, 0, "Returns whether this remember_token refers to a semantic_time that is less than that remember_token's semantic_time.");


f2ptr raw__remember_token__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__semantic_time = raw__remember_token__semantic_time(cause, this);
  f2ptr that__semantic_time = raw__remember_token__semantic_time(cause, that);
  return raw__semantic_time__is_greater_than(cause, this__semantic_time, that__semantic_time);
}

f2ptr f2__remember_token__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(remember_token, this);
  assert_argument_type(remember_token, that);
  return raw__remember_token__is_greater_than(cause, this, that);
}
export_cefunk2(remember_token__is_greater_than, this, that, 0, "Returns whether this remember_token refers to a semantic_time that is greater than that remember_token's semantic_time.");


f2ptr raw__remember_token__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__semantic_time = raw__remember_token__semantic_time(cause, this);
  f2ptr that__semantic_time = raw__remember_token__semantic_time(cause, that);
  return raw__semantic_time__is_numerically_equal_to(cause, this__semantic_time, that__semantic_time);
}

f2ptr f2__remember_token__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(remember_token, this);
  assert_argument_type(remember_token, that);
  return raw__remember_token__is_numerically_equal_to(cause, this, that);
}
export_cefunk2(remember_token__is_numerically_equal_to, this, that, 0, "Returns whether this remember_token refers to a semantic_time that is greater than that remember_token's semantic_time.");


f2ptr f2__remember_token_type__new_aux(f2ptr cause) {
  f2ptr this = f2__remember_token_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_less_than"),            f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "remember_token__is_less_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_greater_than"),         f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "remember_token__is_greater_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_numerically_equal_to"), f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "remember_token__is_numerically_equal_to")));}
  return this;
}



// forgetful_semantic_event_knowledge_base

f2ptr raw__forgetful_semantic_event_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "forgetful_semantic_event_knowledge_base"));
  }
  assert_value(raw__semantic_event_knowledge_base__type_create(cause, this, name, semantic_realm));
  f2ptr value_funk                  = f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "remember_token__semantic_time"));
  f2ptr value_comparison_funk       = f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"),                           new__symbol(cause, "semantic_time__is_less_than"));
  f2ptr remember_token_redblacktree = f2__redblacktree__new(cause, value_funk, value_comparison_funk);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "forget_before_time"),          nil);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "remember_token_redblacktree"), remember_token_redblacktree);
  return this;
}

f2ptr raw__forgetful_semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__forgetful_semantic_event_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__forgetful_semantic_event_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(forgetful_semantic_event_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new forgetful_semantic_event_knowledge_base object.");


boolean_t raw__forgetful_semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "forgetful_semantic_event_knowledge_base");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__forgetful_semantic_event_knowledge_base__is_type(cause, thing));
}
export_cefunk1(forgetful_semantic_event_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type forgetful_semantic_event_knowledge_base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__forgetful_semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  return raw__forgetful_semantic_event_knowledge_base__type(cause, this);
}
export_cefunk1(forgetful_semantic_event_knowledge_base__type, thing, 0, "Returns the specific type of object that this forgetful_semantic_event_knowledge_base is.");


f2ptr raw__forgetful_semantic_event_knowledge_base__forget_before_time(f2ptr cause, f2ptr this) {
  return assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "forget_before_time"), nil));
}

f2ptr f2__forgetful_semantic_event_knowledge_base__forget_before_time(f2ptr cause, f2ptr this) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  return raw__forgetful_semantic_event_knowledge_base__forget_before_time(cause, this);
}
export_cefunk1(forgetful_semantic_event_knowledge_base__forget_before_time, thing, 0, "Returns the time before which events will be forgotten in this knowledge base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(f2ptr cause, f2ptr this, f2ptr forget_before_time) {
  f2ptr result                    = assert_value(raw__frame__add_var_value(cause, this, new__symbol(cause, "forget_before_time"), forget_before_time));
  f2ptr usable_forget_before_time = forget_before_time;
  if (usable_forget_before_time == nil) {
    usable_forget_before_time = f2__semantic_time__new(cause, f2__time(cause));
  }
  f2ptr     semantic_left_time     = assert_value(f2__semantic_time__new(cause, new__symbol(cause, "before")));
  f2ptr     semantic_right_time    = usable_forget_before_time;
  s64       remove_tries           = 0;
  boolean_t making_progress        = boolean__true;
  boolean_t removing_events_failed = boolean__true;
  while (removing_events_failed && making_progress) {
    making_progress        = boolean__false;
    removing_events_failed = boolean__false;
    f2ptr possible_forget_events = assert_value(raw__semantic_event_knowledge_base__events_overlapping_range(cause, this, semantic_left_time, semantic_right_time));
    list__iteration(cause, possible_forget_events, possible_forget_event,
		    f2ptr absolute_end_time = assert_value(f2__semantic_event__absolute_end_time(  cause, possible_forget_event));
		    if (assert_value(f2__is_less_than(cause, absolute_end_time, usable_forget_before_time)) != nil) {
		      f2ptr forget_event  = possible_forget_event;
		      f2ptr remove_result = f2__semantic_knowledge_base__remove_semantic_frame(cause, this, forget_event);
		      if (! raw__larva__is_type(cause, remove_result)) {
			// we successfully removed forget_event
			making_progress        = boolean__true;
		      } else {
			// condition: error removing event
			// causes:    two possibilities at this point
			//              1. good: maybe someone else removed it between the time we created the possible_remove_events list and now.
			//              2. bad:  maybe the event is in the knowledge base, but is failing to be removed for some other reason.
			// solution:  two part solution to correctly handle possible causes
			//              1. we look for progress on each loop
			//              2. only loop a short finite number of times before reporting an error
			removing_events_failed = boolean__true;
		      }
		    }
		    );
    if (removing_events_failed && making_progress) {
      remove_tries ++;
      if (remove_tries > 1000) {
	return new__error(f2list10__new(cause,
					new__symbol(cause, "bug_name"),                  new__symbol(cause, "forgetful_semantic_event_knowledge_base-forget_before_time-set-tried_removing_too_many_times"),
					new__symbol(cause, "this"),                      this,
					new__symbol(cause, "forget_before_time"),        forget_before_time,
					new__symbol(cause, "usable_forget_before_time"), usable_forget_before_time,
					new__symbol(cause, "remove_tries"),              f2integer__new(cause, remove_tries)));
      }
    }
  }
  return result;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__forget_before_time__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(       forgetful_semantic_event_knowledge_base, this);
  assert_argument_type_or_nil(semantic_time,                           value);
  return raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(cause, this, value);
}
export_cefunk2(forgetful_semantic_event_knowledge_base__forget_before_time__set, thing, value, 0, "Sets the time before which events will be forgotten in this knowledge base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr result = nil;
  if (raw__semantic_event__is_type(cause, semantic_frame)) {
    f2ptr semantic_event = semantic_frame;
    {
      f2ptr forget_before_time        = raw__forgetful_semantic_event_knowledge_base__forget_before_time(cause, this);
      f2ptr usable_forget_before_time = forget_before_time;
      if (usable_forget_before_time == nil) {
	usable_forget_before_time = f2__semantic_time__new(cause, f2__time(cause));
      }
      f2ptr absolute_end_time = assert_value(f2__semantic_event__absolute_end_time(cause, semantic_event));
      if (assert_value(f2__is_less_than(cause, absolute_end_time, usable_forget_before_time)) == nil) {
	result = assert_value(f2__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_event));
      }
    }
  } else {
    result = assert_value(raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame));
  }
  return result;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  assert_argument_type(semantic_frame,                          semantic_frame);
  return raw__forgetful_semantic_event_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(forgetful_semantic_event_knowledge_base__add_semantic_frame, this, semantic_frame, 0, "Adds the given semantic_frame to this forgetful_semantic_event_knowledge_base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__remember_token_redblacktree(f2ptr cause, f2ptr this) {
  return assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "remember_token_redblacktree"), nil));
}

f2ptr f2__forgetful_semantic_event_knowledge_base__remember_token_redblacktree(f2ptr cause, f2ptr this) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  return raw__forgetful_semantic_event_knowledge_base__remember_token_redblacktree(cause, this);
}
export_cefunk1(forgetful_semantic_event_knowledge_base__remember_token_redblacktree, thing, 0, "Returns the time before which events will be forgotten in this knowledge base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__add_remember_token(f2ptr cause, f2ptr this, f2ptr remember_token) {
  f2ptr remember_token_redblacktree = raw__forgetful_semantic_event_knowledge_base__remember_token_redblacktree(cause, this);
  assert_value(raw__redblacktree__insert(cause, remember_token_redblacktree, remember_token));
  f2ptr minimum_remember_token = assert_value(raw__redblacktree__minimum(cause, remember_token_redblacktree));
  if (minimum_remember_token == nil) {
    assert_value(raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(cause, this, nil));
  } else {
    f2ptr minimum_remember_token__semantic_time = raw__remember_token__semantic_time(cause, minimum_remember_token);
    assert_value(raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(cause, this, minimum_remember_token__semantic_time));
  }
  return nil;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__add_remember_token(f2ptr cause, f2ptr this, f2ptr remember_token) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  assert_argument_type(remember_token,                          remember_token);
  return raw__forgetful_semantic_event_knowledge_base__add_remember_token(cause, this, remember_token);
}
export_cefunk2(forgetful_semantic_event_knowledge_base__add_remember_token, this, remember_token, 0, "Add the given remember_token to this forgetful_semantic_event_knowledge_base.");


f2ptr raw__forgetful_semantic_event_knowledge_base__remove_remember_token(f2ptr cause, f2ptr this, f2ptr remember_token) {
  f2ptr remember_token_redblacktree = raw__forgetful_semantic_event_knowledge_base__remember_token_redblacktree(cause, this);
  assert_value(raw__redblacktree__remove(cause, remember_token_redblacktree, remember_token));
  f2ptr minimum_remember_token = assert_value(raw__redblacktree__minimum(cause, remember_token_redblacktree));
  if (minimum_remember_token == nil) {
    assert_value(raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(cause, this, nil));
  } else {
    f2ptr minimum_remember_token__semantic_time = raw__remember_token__semantic_time(cause, minimum_remember_token);
    assert_value(raw__forgetful_semantic_event_knowledge_base__forget_before_time__set(cause, this, minimum_remember_token__semantic_time));
  }
  return nil;
}

f2ptr f2__forgetful_semantic_event_knowledge_base__remove_remember_token(f2ptr cause, f2ptr this, f2ptr remember_token) {
  assert_argument_type(forgetful_semantic_event_knowledge_base, this);
  assert_argument_type(remember_token,                          remember_token);
  return raw__forgetful_semantic_event_knowledge_base__remove_remember_token(cause, this, remember_token);
}
export_cefunk2(forgetful_semantic_event_knowledge_base__remove_remember_token, this, remember_token, 0, "Remove the given remember_token from this forgetful_semantic_event_knowledge_base.");


f2ptr f2__forgetful_semantic_event_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_event_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "forget_before_time"),          f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__forget_before_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "forget_before_time"),          f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__forget_before_time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_semantic_frame"),          f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "remember_token_redblacktree"), f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__remember_token_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_remember_token"),          f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__add_remember_token")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_remember_token"),       f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), new__symbol(cause, "forgetful_semantic_event_knowledge_base__remove_remember_token")));}
  return this;
}



// **

f2ptr f2__forgetful_semantic_event_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(forgetful_semantic_event_knowledge_base__core_extension__ping, 0, "");


f2ptr f2__forgetful_semantic_event_knowledge_base__core_extension__initialize(f2ptr cause) {
  core_extension__ping(forgetful_semantic_event_knowledge_base, semantic_event_knowledge_base);
  f2__add_type(cause, new__symbol(cause, "forgetful_semantic_event_knowledge_base"), f2__forgetful_semantic_event_knowledge_base_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "remember_token"),                          f2__remember_token_type__new_aux(cause));
  status("forgetful_semantic_event_knowledge_base initialized.");
  return nil;
}
export_cefunk0(forgetful_semantic_event_knowledge_base__core_extension__initialize, 0, "");


f2ptr f2__forgetful_semantic_event_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("forgetful_semantic_event_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(forgetful_semantic_event_knowledge_base__core_extension__destroy, 0, "");


