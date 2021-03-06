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

#include "semantic_planner.h"


// semantic_planner

f2ptr raw__semantic_planner__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_planner"));
  }
  assert_value(raw__semantic_reflective_object__type_create(cause, this, semantic_realm));
  raw__semantic_reflective_object__reflective_object_type__set(cause, this, new__symbol(cause, "planner"));
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "planner_type"),        nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "execute_plan"),        nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "imagine_plan"),        nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "focus_register"),      nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "return_register"),     nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_a"),          nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_b"),          nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_c"),          nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_d"),          nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_positive_goal"), nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_negative_goal"), nil);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_plan"),          nil);
  return this;
}

f2ptr raw__semantic_planner__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_planner__type_create(cause, this, semantic_realm));
  return this;
}

f2ptr f2__semantic_planner__new(f2ptr cause, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_planner__new(cause, semantic_realm);
}
export_cefunk1(semantic_planner__new, semantic_realm, 0, "Returns a new semantic_planner object.");


boolean_t raw__semantic_planner__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_planner");
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

f2ptr f2__semantic_planner__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_planner__is_type(cause, thing));
}
export_cefunk1(semantic_planner__is_type, thing, 0, "Returns whether or not thing is of type semantic_planner.");


f2ptr raw__semantic_planner__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_planner__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__type(cause, this);
}
export_cefunk1(semantic_planner__type, thing, 0, "Returns the specific type of object that this semantic_planner is.");


f2ptr raw__semantic_planner__planner_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "planner_type"));
}

f2ptr f2__semantic_planner__planner_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__planner_type(cause, this);
}
export_cefunk1(semantic_planner__planner_type, this, 0, "");


f2ptr raw__semantic_planner__planner_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "planner_type"), that);
}

f2ptr f2__semantic_planner__planner_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__planner_type__set(cause, this, that);
}
export_cefunk2(semantic_planner__planner_type__set, this, that, 0, "");


f2ptr raw__semantic_planner__execute_plan(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "execute_plan"));
}

f2ptr f2__semantic_planner__execute_plan(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__execute_plan(cause, this);
}
export_cefunk1(semantic_planner__execute_plan, this, 0, "");


f2ptr raw__semantic_planner__execute_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "execute_plan"), that);
}

f2ptr f2__semantic_planner__execute_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__execute_plan__set(cause, this, that);
}
export_cefunk2(semantic_planner__execute_plan__set, this, that, 0, "");


f2ptr raw__semantic_planner__imagine_plan(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "imagine_plan"));
}

f2ptr f2__semantic_planner__imagine_plan(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__imagine_plan(cause, this);
}
export_cefunk1(semantic_planner__imagine_plan, this, 0, "");


f2ptr raw__semantic_planner__imagine_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "imagine_plan"), that);
}

f2ptr f2__semantic_planner__imagine_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__imagine_plan__set(cause, this, that);
}
export_cefunk2(semantic_planner__imagine_plan__set, this, that, 0, "");


f2ptr raw__semantic_planner__focus_register(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "focus_register"));
}

f2ptr f2__semantic_planner__focus_register(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__focus_register(cause, this);
}
export_cefunk1(semantic_planner__focus_register, this, 0, "");


f2ptr raw__semantic_planner__focus_register__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "focus_register"), that);
}

f2ptr f2__semantic_planner__focus_register__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__focus_register__set(cause, this, that);
}
export_cefunk2(semantic_planner__focus_register__set, this, that, 0, "");


f2ptr raw__semantic_planner__return_register(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "return_register"));
}

f2ptr f2__semantic_planner__return_register(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__return_register(cause, this);
}
export_cefunk1(semantic_planner__return_register, this, 0, "");


f2ptr raw__semantic_planner__return_register__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "return_register"), that);
}

f2ptr f2__semantic_planner__return_register__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__return_register__set(cause, this, that);
}
export_cefunk2(semantic_planner__return_register__set, this, that, 0, "");


f2ptr raw__semantic_planner__register_a(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_a"));
}

f2ptr f2__semantic_planner__register_a(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_a(cause, this);
}
export_cefunk1(semantic_planner__register_a, this, 0, "");


f2ptr raw__semantic_planner__register_a__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_a"), that);
}

f2ptr f2__semantic_planner__register_a__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_a__set(cause, this, that);
}
export_cefunk2(semantic_planner__register_a__set, this, that, 0, "");


f2ptr raw__semantic_planner__register_b(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_b"));
}

f2ptr f2__semantic_planner__register_b(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_b(cause, this);
}
export_cefunk1(semantic_planner__register_b, this, 0, "");


f2ptr raw__semantic_planner__register_b__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_b"), that);
}

f2ptr f2__semantic_planner__register_b__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_b__set(cause, this, that);
}
export_cefunk2(semantic_planner__register_b__set, this, that, 0, "");


f2ptr raw__semantic_planner__register_c(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_c"));
}

f2ptr f2__semantic_planner__register_c(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_c(cause, this);
}
export_cefunk1(semantic_planner__register_c, this, 0, "");


f2ptr raw__semantic_planner__register_c__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_c"), that);
}

f2ptr f2__semantic_planner__register_c__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_c__set(cause, this, that);
}
export_cefunk2(semantic_planner__register_c__set, this, that, 0, "");


f2ptr raw__semantic_planner__register_d(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_d"));
}

f2ptr f2__semantic_planner__register_d(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_d(cause, this);
}
export_cefunk1(semantic_planner__register_d, this, 0, "");


f2ptr raw__semantic_planner__register_d__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "register_d"), that);
}

f2ptr f2__semantic_planner__register_d__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__register_d__set(cause, this, that);
}
export_cefunk2(semantic_planner__register_d__set, this, that, 0, "");


f2ptr raw__semantic_planner__first_positive_goal(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_positive_goal"));
}

f2ptr f2__semantic_planner__first_positive_goal(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_positive_goal(cause, this);
}
export_cefunk1(semantic_planner__first_positive_goal, this, 0, "");


f2ptr raw__semantic_planner__first_positive_goal__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_positive_goal"), that);
}

f2ptr f2__semantic_planner__first_positive_goal__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_positive_goal__set(cause, this, that);
}
export_cefunk2(semantic_planner__first_positive_goal__set, this, that, 0, "");


f2ptr raw__semantic_planner__first_negative_goal(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_negative_goal"));
}

f2ptr f2__semantic_planner__first_negative_goal(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_negative_goal(cause, this);
}
export_cefunk1(semantic_planner__first_negative_goal, this, 0, "");


f2ptr raw__semantic_planner__first_negative_goal__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_negative_goal"), that);
}

f2ptr f2__semantic_planner__first_negative_goal__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_negative_goal__set(cause, this, that);
}
export_cefunk2(semantic_planner__first_negative_goal__set, this, that, 0, "");


f2ptr raw__semantic_planner__first_plan(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_plan"));
}

f2ptr f2__semantic_planner__first_plan(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_plan(cause, this);
}
export_cefunk1(semantic_planner__first_plan, this, 0, "");


f2ptr raw__semantic_planner__first_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "first_plan"), that);
}

f2ptr f2__semantic_planner__first_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__first_plan__set(cause, this, that);
}
export_cefunk2(semantic_planner__first_plan__set, this, that, 0, "");


f2ptr raw__semantic_planner__positive_goal__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "positive_goal"));
}

f2ptr f2__semantic_planner__positive_goal__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__positive_goal__lookup_set(cause, this);
}
export_cefunk1(semantic_planner__positive_goal__lookup_set, this, 0, "Returns the set of relation-ons.");


f2ptr raw__semantic_planner__positive_goal__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "positive_goal"), that);
}

f2ptr f2__semantic_planner__positive_goal__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__positive_goal__add(cause, this, that);
}
export_cefunk2(semantic_planner__positive_goal__add, this, that, 0, "");


f2ptr raw__semantic_planner__positive_goal__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "positive_goal"), that);
}

f2ptr f2__semantic_planner__positive_goal__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__positive_goal__remove(cause, this, that);
}
export_cefunk2(semantic_planner__positive_goal__remove, this, that, 0, "");


f2ptr raw__semantic_planner__negative_goal__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "negative_goal"));
}

f2ptr f2__semantic_planner__negative_goal__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__negative_goal__lookup_set(cause, this);
}
export_cefunk1(semantic_planner__negative_goal__lookup_set, this, 0, "Returns the set of relation-ons.");


f2ptr raw__semantic_planner__negative_goal__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "negative_goal"), that);
}

f2ptr f2__semantic_planner__negative_goal__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__negative_goal__add(cause, this, that);
}
export_cefunk2(semantic_planner__negative_goal__add, this, that, 0, "");


f2ptr raw__semantic_planner__negative_goal__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "negative_goal"), that);
}

f2ptr f2__semantic_planner__negative_goal__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__negative_goal__remove(cause, this, that);
}
export_cefunk2(semantic_planner__negative_goal__remove, this, that, 0, "");


f2ptr raw__semantic_planner__bug_plan__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "bug_plan"));
}

f2ptr f2__semantic_planner__bug_plan__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__bug_plan__lookup_set(cause, this);
}
export_cefunk1(semantic_planner__bug_plan__lookup_set, this, 0, "Returns the set of relation-ons.");


f2ptr raw__semantic_planner__bug_plan__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "bug_plan"), that);
}

f2ptr f2__semantic_planner__bug_plan__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__bug_plan__add(cause, this, that);
}
export_cefunk2(semantic_planner__bug_plan__add, this, that, 0, "");


f2ptr raw__semantic_planner__bug_plan__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "bug_plan"), that);
}

f2ptr f2__semantic_planner__bug_plan__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__bug_plan__remove(cause, this, that);
}
export_cefunk2(semantic_planner__bug_plan__remove, this, that, 0, "");


f2ptr raw__semantic_planner__thought__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "thought"));
}

f2ptr f2__semantic_planner__thought__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__thought__lookup_set(cause, this);
}
export_cefunk1(semantic_planner__thought__lookup_set, this, 0, "Returns the set of relation-ons.");


f2ptr raw__semantic_planner__thought__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "thought"), that);
}

f2ptr f2__semantic_planner__thought__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__thought__add(cause, this, that);
}
export_cefunk2(semantic_planner__thought__add, this, that, 0, "");


f2ptr raw__semantic_planner__thought__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "thought"), that);
}

f2ptr f2__semantic_planner__thought__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_planner, this);
  return raw__semantic_planner__thought__remove(cause, this, that);
}
export_cefunk2(semantic_planner__thought__remove, this, that, 0, "");


f2ptr f2__semantic_planner__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_reflective_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "planner_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__planner_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "planner_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__planner_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "execute_plan"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__execute_plan")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "execute_plan"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__execute_plan__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "imagine_plan"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__imagine_plan")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "imagine_plan"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__imagine_plan__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "focus_register"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__focus_register")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "focus_register"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__focus_register__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "return_register"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__return_register")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "return_register"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__return_register__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "register_a"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_a")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "register_a"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_a__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "register_b"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_b")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "register_b"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_b__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "register_c"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_c")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "register_c"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_c__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "register_d"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_d")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "register_d"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__register_d__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "first_positive_goal"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_positive_goal")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "first_positive_goal"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_positive_goal__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "first_negative_goal"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_negative_goal")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "first_negative_goal"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_negative_goal__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "first_plan"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_plan")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "first_plan"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__first_plan__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "positive_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__positive_goal__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "positive_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__positive_goal__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "positive_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__positive_goal__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "negative_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__negative_goal__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "negative_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__negative_goal__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "negative_goal"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__negative_goal__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "bug_plan"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__bug_plan__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "bug_plan"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__bug_plan__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "bug_plan"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__bug_plan__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "thought"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__thought__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "thought"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__thought__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "thought"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_planner"), new__symbol(cause, "semantic_planner__thought__remove")));}
  return this;
}


// **

f2ptr f2__semantic_planner__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_planner__core_extension__ping, 0, "");

f2ptr f2__semantic_planner__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_planner, semantic_reflective_object);
  f2__add_type(cause, new__symbol(cause, "semantic_planner"), f2__semantic_planner__primobject_type__new(cause));
  status("semantic_planner initialized.");
  return nil;
}
export_cefunk0(semantic_planner__core_extension__initialize, 0, "");

f2ptr f2__semantic_planner__core_extension__destroy(f2ptr cause) {
  status("semantic_planner destroyed.");
  return nil;
}
export_cefunk0(semantic_planner__core_extension__destroy, 0, "");


