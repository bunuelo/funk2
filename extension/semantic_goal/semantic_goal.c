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

#include "semantic_goal.h"


f2ptr f2__semantic_goal__new_phenomenal_name(f2ptr cause, f2ptr positive, f2ptr partial_state_phenomenal_name) {
  f2ptr positive_string = (positive != nil) ? new__string(cause, "positive") : new__string(cause, "negative");
  return assert_value(f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list4__new(cause,
											       new__string(cause, "goal_"),
											       positive_string,
											       new__string(cause, "_"),
											       assert_value(f2__exp__as__string(cause, partial_state_phenomenal_name))))));
}
export_cefunk2(semantic_goal__new_phenomenal_name, positive, partial_state_phenomenal_name, 0, "Returns a new semantic_goal-phenomenal_name symbol.");


// semantic_goal

f2ptr raw__semantic_goal__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr positive, f2ptr partial_state_phenomenal_name, f2ptr partial_state) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_goal"));
  }
  assert_value(raw__semantic_reflective_object__type_create(cause, this, semantic_realm));
  f2ptr phenomenal_name = assert_value(f2__semantic_goal__new_phenomenal_name(cause, positive, partial_state_phenomenal_name));
  raw__semantic_object__phenomenal_name__set(cause, this, phenomenal_name);
  raw__semantic_reflective_object__reflective_object_type__set(cause, this, new__symbol(cause, "goal"));
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "positive"),                      positive);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "partial_state_phenomenal_name"), partial_state_phenomenal_name);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "partial_state"),                 partial_state);
  return this;
}

f2ptr raw__semantic_goal__new(f2ptr cause, f2ptr semantic_realm, f2ptr positive, f2ptr partial_state_phenomenal_name, f2ptr partial_state) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_goal__type_create(cause, this, semantic_realm, positive, partial_state_phenomenal_name, partial_state));
  return this;
}

f2ptr f2__semantic_goal__new(f2ptr cause, f2ptr semantic_realm, f2ptr positive, f2ptr partial_state_phenomenal_name, f2ptr partial_state) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_goal__new(cause, semantic_realm, positive, partial_state_phenomenal_name, partial_state);
}
export_cefunk4(semantic_goal__new, semantic_realm, positive, partial_state_phenomenal_name, partial_state, 0, "Returns a new semantic_goal object.");


boolean_t raw__semantic_goal__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_goal");
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

f2ptr f2__semantic_goal__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_goal__is_type(cause, thing));
}
export_cefunk1(semantic_goal__is_type, thing, 0, "Returns whether or not thing is of type semantic_goal.");


f2ptr raw__semantic_goal__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_goal__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__type(cause, this);
}
export_cefunk1(semantic_goal__type, thing, 0, "Returns the specific type of object that this semantic_goal is.");


f2ptr raw__semantic_goal__positive(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "positive"));
}

f2ptr f2__semantic_goal__positive(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__positive(cause, this);
}
export_cefunk1(semantic_goal__positive, this, 0, "");


f2ptr raw__semantic_goal__positive__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "positive"), that);
}

f2ptr f2__semantic_goal__positive__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__positive__set(cause, this, that);
}
export_cefunk2(semantic_goal__positive__set, this, that, 0, "");


f2ptr raw__semantic_goal__partial_state_phenomenal_name(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "partial_state_phenomenal_name"));
}

f2ptr f2__semantic_goal__partial_state_phenomenal_name(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__partial_state_phenomenal_name(cause, this);
}
export_cefunk1(semantic_goal__partial_state_phenomenal_name, this, 0, "");


f2ptr raw__semantic_goal__partial_state_phenomenal_name__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "partial_state_phenomenal_name"), that);
}

f2ptr f2__semantic_goal__partial_state_phenomenal_name__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__partial_state_phenomenal_name__set(cause, this, that);
}
export_cefunk2(semantic_goal__partial_state_phenomenal_name__set, this, that, 0, "");


f2ptr raw__semantic_goal__partial_state(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "partial_state"));
}

f2ptr f2__semantic_goal__partial_state(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__partial_state(cause, this);
}
export_cefunk1(semantic_goal__partial_state, this, 0, "");


f2ptr raw__semantic_goal__partial_state__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "partial_state"), that);
}

f2ptr f2__semantic_goal__partial_state__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_goal, this);
  return raw__semantic_goal__partial_state__set(cause, this, that);
}
export_cefunk2(semantic_goal__partial_state__set, this, that, 0, "");



f2ptr f2__semantic_goal_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_reflective_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "positive"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__positive")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "positive"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__positive__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "partial_state_phenomenal_name"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__partial_state_phenomenal_name")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "partial_state_phenomenal_name"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__partial_state_phenomenal_name__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "partial_state"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__partial_state")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "partial_state"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_goal"), new__symbol(cause, "semantic_goal__partial_state__set")));}
  return this;
}



// **

f2ptr f2__semantic_goal__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_goal__core_extension__ping, 0, "");

f2ptr f2__semantic_goal__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_goal, semantic_reflective_object);
  core_extension__ping(semantic_goal, semantic_event);
  status("semantic_goal initialized.");
  return nil;
}
export_cefunk0(semantic_goal__core_extension__initialize, 0, "");

f2ptr f2__semantic_goal__core_extension__define_types(f2ptr cause) {
  assert_value(f2__add_type(cause, new__symbol(cause, "semantic_goal"), f2__semantic_goal_type__new(cause)));
  status("semantic_goal define types.");
  return nil;
}
export_cefunk0(semantic_goal__core_extension__define_types, 0, "");

f2ptr f2__semantic_goal__core_extension__destroy(f2ptr cause) {
  status("semantic_goal destroyed.");
  return nil;
}
export_cefunk0(semantic_goal__core_extension__destroy, 0, "");


