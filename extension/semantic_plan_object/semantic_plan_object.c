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

#include "semantic_plan_object.h"


// semantic_plan_object

f2ptr raw__semantic_plan_object__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr deliberative_plan) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_plan_object"));
  }
  assert_value(raw__semantic_object__type_create(cause, this, semantic_realm));
  raw__semantic_object__phenomenal_name__set(cause, this, phenomenal_name);
  // avoids redefining in cases of multiple inheritance.
  if (raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "property"), new__symbol(cause, "plan_object_type")) == nil) {
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "plan_object_type"),    nil);
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "deliberative_plan"),   deliberative_plan);
    raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "start_plan_operator"), nil);
  }
  return this;
}

f2ptr raw__semantic_plan_object__new(f2ptr cause, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr deliberative_plan) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_plan_object__type_create(cause, this, semantic_realm, phenomenal_name, deliberative_plan));
  return this;
}

f2ptr f2__semantic_plan_object__new(f2ptr cause, f2ptr semantic_realm, f2ptr phenomenal_name, f2ptr deliberative_plan) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_plan_object__new(cause, semantic_realm, phenomenal_name, deliberative_plan);
}
export_cefunk3(semantic_plan_object__new, semantic_realm, phenomenal_name, deliberative_plan, 0, "Returns a new semantic_plan_object object.");


boolean_t raw__semantic_plan_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_plan_object");
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

f2ptr f2__semantic_plan_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_plan_object__is_type(cause, thing));
}
export_cefunk1(semantic_plan_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_plan_object.");


f2ptr raw__semantic_plan_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_plan_object__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__type(cause, this);
}
export_cefunk1(semantic_plan_object__type, thing, 0, "Returns the specific type of object that this semantic_plan_object is.");


f2ptr raw__semantic_plan_object__plan_object_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "plan_object_type"));
}

f2ptr f2__semantic_plan_object__plan_object_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__plan_object_type(cause, this);
}
export_cefunk1(semantic_plan_object__plan_object_type, this, 0, "");


f2ptr raw__semantic_plan_object__plan_object_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "plan_object_type"), that);
}

f2ptr f2__semantic_plan_object__plan_object_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__plan_object_type__set(cause, this, that);
}
export_cefunk2(semantic_plan_object__plan_object_type__set, this, that, 0, "");


f2ptr raw__semantic_plan_object__deliberative_plan(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "deliberative_plan"));
}

f2ptr f2__semantic_plan_object__deliberative_plan(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__deliberative_plan(cause, this);
}
export_cefunk1(semantic_plan_object__deliberative_plan, this, 0, "");


f2ptr raw__semantic_plan_object__deliberative_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "deliberative_plan"), that);
}

f2ptr f2__semantic_plan_object__deliberative_plan__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__deliberative_plan__set(cause, this, that);
}
export_cefunk2(semantic_plan_object__deliberative_plan__set, this, that, 0, "");



f2ptr raw__semantic_plan_object__start_plan_operator(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "start_plan_operator"));
}

f2ptr f2__semantic_plan_object__start_plan_operator(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__start_plan_operator(cause, this);
}
export_cefunk1(semantic_plan_object__start_plan_operator, this, 0, "");


f2ptr raw__semantic_plan_object__start_plan_operator__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "start_plan_operator"), that);
}

f2ptr f2__semantic_plan_object__start_plan_operator__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__start_plan_operator__set(cause, this, that);
}
export_cefunk2(semantic_plan_object__start_plan_operator__set, this, that, 0, "");



f2ptr raw__semantic_plan_object__hypothesis__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "hypothesis"));
}

f2ptr f2__semantic_plan_object__hypothesis__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__hypothesis__lookup_set(cause, this);
}
export_cefunk1(semantic_plan_object__hypothesis__lookup_set, this, 0, "Returns the set of ordered_objects that happen after this ordered_object, returns nil if no such set exists.");


f2ptr raw__semantic_plan_object__hypothesis__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "hypothesis"), that);
}

f2ptr f2__semantic_plan_object__hypothesis__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__hypothesis__add(cause, this, that);
}
export_cefunk2(semantic_plan_object__hypothesis__add, this, that, 0, "Adds the given that to happen after this ordered_object.");


f2ptr raw__semantic_plan_object__hypothesis__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "hypothesis"), that);
}

f2ptr f2__semantic_plan_object__hypothesis__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_object, this);
  return raw__semantic_plan_object__hypothesis__remove(cause, this, that);
}
export_cefunk2(semantic_plan_object__hypothesis__remove, this, that, 0, "Removes the given that to no longer happen after this that.");



f2ptr f2__semantic_plan_object__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "plan_object_type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__plan_object_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "plan_object_type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__plan_object_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "deliberative_plan"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__deliberative_plan")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "deliberative_plan"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__deliberative_plan__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "start_plan_operator"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__start_plan_operator")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "start_plan_operator"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__start_plan_operator__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "hypothesis"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__hypothesis__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "hypothesis"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__hypothesis__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "hypothesis"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_object"), new__symbol(cause, "semantic_plan_object__hypothesis__remove")));}
  return this;
}





// **

f2ptr f2__semantic_plan_object__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_plan_object__core_extension__ping, 0, "");

f2ptr f2__semantic_plan_object__core_extension__initialize(f2ptr cause) {
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_object"), new__symbol(cause, "semantic_object__core_extension__ping")), nil);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2__add_type(cause, new__symbol(cause, "semantic_plan_object"), f2__semantic_plan_object__primobject_type__new(cause));
  status("semantic_plan_object initialized.");
  return nil;
}
export_cefunk0(semantic_plan_object__core_extension__initialize, 0, "");

f2ptr f2__semantic_plan_object__core_extension__destroy(f2ptr cause) {
  status("semantic_plan_object destroyed.");
  return nil;
}
export_cefunk0(semantic_plan_object__core_extension__destroy, 0, "");


