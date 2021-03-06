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

#include "semantic_reflective_object_type_event.h"


// semantic_reflective_object_type_event

f2ptr raw__semantic_reflective_object_type_event__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr object_phenomenal_name) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_reflective_object_type_event"));
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "is_negative_knowledge"),            nil);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks_cmutex"), f2cmutex__new(cause));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks"),        nil);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "has_lost_dependency"),              nil);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"),  nil);
  assert_value(raw__semantic_object_type_event__type_create(cause, this, semantic_realm, phenomenal_name, object_phenomenal_name));
  return this;
}

f2ptr raw__semantic_reflective_object_type_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr object_phenomenal_name) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  assert_value(raw__semantic_reflective_object_type_event__type_create(cause, this, semantic_realm, phenomenal_name, object_phenomenal_name));
  return this;
}

f2ptr f2__semantic_reflective_object_type_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr object_phenomenal_name) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_reflective_object_type_event__new(cause, semantic_realm, phenomenal_name, object_phenomenal_name);
}
export_cefunk3(semantic_reflective_object_type_event__new, semantic_realm, phenomenal_name, object_phenomenal_name, 0, "Returns a new semantic_reflective_object_type_event object.");


boolean_t raw__semantic_reflective_object_type_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_reflective_object_type_event");
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

f2ptr f2__semantic_reflective_object_type_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_reflective_object_type_event__is_type(cause, thing));
}
export_cefunk1(semantic_reflective_object_type_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_reflective_object_type_event.");


f2ptr raw__semantic_reflective_object_type_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_reflective_object_type_event__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__type(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__type, thing, 0, "Returns the specific type of object that this semantic_reflective_object_type_event is.");


f2ptr raw__semantic_reflective_object_type_event__is_negative_knowledge(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "is_negative_knowledge"), nil);
}

f2ptr f2__semantic_reflective_object_type_event__is_negative_knowledge(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__is_negative_knowledge(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__is_negative_knowledge, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__is_negative_knowledge__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__frame__add_var_value(cause, this, new__symbol(cause, "is_negative_knowledge"), that);
}

f2ptr f2__semantic_reflective_object_type_event__is_negative_knowledge__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__is_negative_knowledge__set(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__is_negative_knowledge__set, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks_cmutex"), nil);
}

f2ptr f2__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__frame__add_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks_cmutex"), that);
}

f2ptr f2__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex__set(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex__set, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__lost_dependency_callbacks(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks"), nil);
}

f2ptr f2__semantic_reflective_object_type_event__lost_dependency_callbacks(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__lost_dependency_callbacks(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__lost_dependency_callbacks, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__lost_dependency_callbacks__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__frame__add_var_value(cause, this, new__symbol(cause, "lost_dependency_callbacks"), that);
}

f2ptr f2__semantic_reflective_object_type_event__lost_dependency_callbacks__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__lost_dependency_callbacks__set(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__lost_dependency_callbacks__set, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__has_lost_dependency(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "has_lost_dependency"), nil);
}

f2ptr f2__semantic_reflective_object_type_event__has_lost_dependency(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__has_lost_dependency(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__has_lost_dependency, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__has_lost_dependency__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__frame__add_var_value(cause, this, new__symbol(cause, "has_lost_dependency"), that);
}

f2ptr f2__semantic_reflective_object_type_event__has_lost_dependency__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__has_lost_dependency__set(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__has_lost_dependency__set, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__nonsemantic_plan_execution_node(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"), nil);
}

f2ptr f2__semantic_reflective_object_type_event__nonsemantic_plan_execution_node(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__nonsemantic_plan_execution_node(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__nonsemantic_plan_execution_node, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__nonsemantic_plan_execution_node__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__frame__add_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"), that);
}

f2ptr f2__semantic_reflective_object_type_event__nonsemantic_plan_execution_node__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__nonsemantic_plan_execution_node__set(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__nonsemantic_plan_execution_node__set, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__add_lost_dependency_callback(f2ptr cause, f2ptr this, f2ptr dependency_callback) {
  f2ptr     lost_dependency_callbacks_cmutex = raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex(cause, this);
  boolean_t already_lost_dependency          = boolean__false;
  {
    raw__cmutex__lock(cause, lost_dependency_callbacks_cmutex);
    {
      f2ptr has_lost_dependency = raw__semantic_reflective_object_type_event__has_lost_dependency(cause, this);
      if (has_lost_dependency != nil) {
	already_lost_dependency = boolean__true;
      } else {
	f2ptr lost_dependency_callbacks = raw__semantic_reflective_object_type_event__lost_dependency_callbacks(cause, this);
	lost_dependency_callbacks = raw__cons__new(cause, dependency_callback, lost_dependency_callbacks);
	raw__semantic_reflective_object_type_event__lost_dependency_callbacks__set(cause, this, lost_dependency_callbacks);
      }
    }
    raw__cmutex__unlock(cause, lost_dependency_callbacks_cmutex);
  }
  if (already_lost_dependency) {
    raw__dependency_callback__call(cause, dependency_callback);
  }
  return nil;
}

f2ptr f2__semantic_reflective_object_type_event__add_lost_dependency_callback(f2ptr cause, f2ptr this, f2ptr dependency_callback) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  assert_argument_type(dependency_callback, dependency_callback);
  return raw__semantic_reflective_object_type_event__add_lost_dependency_callback(cause, this, dependency_callback);
}
export_cefunk2(semantic_reflective_object_type_event__add_lost_dependency_callback, this, dependency_callback, 0, "");


f2ptr raw__semantic_reflective_object_type_event__know_has_lost_dependency(f2ptr cause, f2ptr this) {
  f2ptr lost_dependency_callbacks_cmutex = raw__semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex(cause, this);
  f2ptr old_lost_dependency_callbacks = nil;
  {
    raw__cmutex__lock(cause, lost_dependency_callbacks_cmutex);
    {
      f2ptr has_lost_dependency = raw__semantic_reflective_object_type_event__has_lost_dependency(cause, this);
      if (has_lost_dependency == nil) {
	has_lost_dependency = f2bool__new(boolean__true);
	raw__semantic_reflective_object_type_event__has_lost_dependency__set(cause, this, has_lost_dependency);
	f2ptr lost_dependency_callbacks = raw__semantic_reflective_object_type_event__lost_dependency_callbacks(cause, this);
	old_lost_dependency_callbacks = lost_dependency_callbacks;
	lost_dependency_callbacks     = nil;
	raw__semantic_reflective_object_type_event__lost_dependency_callbacks__set(cause, this, lost_dependency_callbacks);
      }
    }
    raw__cmutex__unlock(cause, lost_dependency_callbacks_cmutex);
  }
  {
    f2ptr iter = old_lost_dependency_callbacks;
    while (iter != nil) {
      f2ptr dependency_callback = f2cons__car(iter, cause);
      {
	raw__dependency_callback__call(cause, dependency_callback);
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return nil;
}

f2ptr f2__semantic_reflective_object_type_event__know_has_lost_dependency(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__know_has_lost_dependency(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__know_has_lost_dependency, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__in__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-in"));
}

f2ptr f2__semantic_reflective_object_type_event__preposition__in__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__preposition__in__lookup_set(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__preposition__in__lookup_set, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__in__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-in"), that);
}

f2ptr f2__semantic_reflective_object_type_event__preposition__in__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event,          this);
  assert_argument_type(semantic_reflective_object_type_relation_event, that);
  return raw__semantic_reflective_object_type_event__preposition__in__add(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__preposition__in__add, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__in__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-in"), that);
}

f2ptr f2__semantic_reflective_object_type_event__preposition__in__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event,          this);
  assert_argument_type(semantic_reflective_object_type_relation_event, that);
  return raw__semantic_reflective_object_type_event__preposition__in__remove(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__preposition__in__remove, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__on__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-on"));
}

f2ptr f2__semantic_reflective_object_type_event__preposition__on__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__preposition__on__lookup_set(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__preposition__on__lookup_set, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__on__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-on"), that);
}

f2ptr f2__semantic_reflective_object_type_event__preposition__on__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event,          this);
  assert_argument_type(semantic_reflective_object_type_relation_event, that);
  return raw__semantic_reflective_object_type_event__preposition__on__add(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__preposition__on__add, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__preposition__on__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "preposition-on"), that);
}

f2ptr f2__semantic_reflective_object_type_event__preposition__on__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event,          this);
  assert_argument_type(semantic_reflective_object_type_relation_event, that);
  return raw__semantic_reflective_object_type_event__preposition__on__remove(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__preposition__on__remove, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__dependency__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "dependency"));
}

f2ptr f2__semantic_reflective_object_type_event__dependency__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__dependency__lookup_set(cause, this);
}
export_cefunk1(semantic_reflective_object_type_event__dependency__lookup_set, this, 0, "");


f2ptr raw__semantic_reflective_object_type_event__dependency__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "dependency"), that);
}

f2ptr f2__semantic_reflective_object_type_event__dependency__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__dependency__add(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__dependency__add, this, that, 0, "");


f2ptr raw__semantic_reflective_object_type_event__dependency__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "dependency"), that);
}

f2ptr f2__semantic_reflective_object_type_event__dependency__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_reflective_object_type_event, this);
  return raw__semantic_reflective_object_type_event__dependency__remove(cause, this, that);
}
export_cefunk2(semantic_reflective_object_type_event__dependency__remove, this, that, 0, "");


f2ptr f2__semantic_reflective_object_type_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object_type_event")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "is_negative_knowledge"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__is_negative_knowledge")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "is_negative_knowledge"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__is_negative_knowledge__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "lost_dependency_callbacks_cmutex"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "lost_dependency_callbacks_cmutex"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__lost_dependency_callbacks_cmutex__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "lost_dependency_callbacks"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__lost_dependency_callbacks")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "lost_dependency_callbacks"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__lost_dependency_callbacks__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "has_lost_dependency"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__has_lost_dependency")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "has_lost_dependency"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__has_lost_dependency__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "nonsemantic_plan_execution_node"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__nonsemantic_plan_execution_node")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "nonsemantic_plan_execution_node"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__nonsemantic_plan_execution_node__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "add_lost_dependency_callback"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__add_lost_dependency_callback")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "know_has_lost_dependency"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__know_has_lost_dependency")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "preposition-in"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__in__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "preposition-in"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__in__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "preposition-in"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__in__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "preposition-on"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__on__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "preposition-on"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__on__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "preposition-on"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__preposition__on__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "dependency"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__dependency__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "dependency"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__dependency__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "dependency"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_reflective_object_type_event"), new__symbol(cause, "semantic_reflective_object_type_event__dependency__remove")));}
  return this;
}



// **

f2ptr f2__semantic_reflective_object_type_event__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_reflective_object_type_event__core_extension__ping, 0, "");

f2ptr f2__semantic_reflective_object_type_event__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_reflective_object_type_event, semantic_object_type_event);
  core_extension__ping(semantic_dependency,                   semantic_dependency);
  status("semantic_reflective_object_type_event initialized.");
  return nil;
}
export_cefunk0(semantic_reflective_object_type_event__core_extension__initialize, 0, "");

f2ptr f2__semantic_reflective_object_type_event__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_reflective_object_type_event"), f2__semantic_reflective_object_type_event_type__new(cause));
  status("semantic_reflective_object_type_event define types.");
  return nil;
}
export_cefunk0(semantic_reflective_object_type_event__core_extension__define_types, 0, "");

f2ptr f2__semantic_reflective_object_type_event__core_extension__destroy(f2ptr cause) {
  status("semantic_reflective_object_type_event destroyed.");
  return nil;
}
export_cefunk0(semantic_reflective_object_type_event__core_extension__destroy, 0, "");


