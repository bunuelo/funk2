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

#include "semantic_self.h"


// semantic_self

f2ptr raw__semantic_self__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_self"));
  }
  {
    f2ptr result = raw__semantic_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr raw__semantic_self__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_self__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_self__new(f2ptr cause, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_self__new(cause, semantic_realm);
}
export_cefunk1(semantic_self__new, semantic_realm, 0, "Returns a new semantic_self object.");


boolean_t raw__semantic_self__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_self");
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

f2ptr f2__semantic_self__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_self__is_type(cause, thing));
}
export_cefunk1(semantic_self__is_type, thing, 0, "Returns whether or not thing is of type semantic_self.");


f2ptr raw__semantic_self__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_self__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_self, this);
  return raw__semantic_self__type(cause, this);
}
export_cefunk1(semantic_self__type, thing, 0, "Returns the specific type of object that this semantic_self is.");


f2ptr raw__semantic_self__event__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "event"));
}

f2ptr f2__semantic_self__event__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_self, this);
  return raw__semantic_self__event__lookup_set(cause, this);
}
export_cefunk1(semantic_self__event__lookup_set, this, 0, "");


f2ptr raw__semantic_self__event__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "event"), that);
}

f2ptr f2__semantic_self__event__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_self, this);
  assert_argument_type(semantic_event,     that);
  return raw__semantic_self__event__add(cause, this, that);
}
export_cefunk2(semantic_self__event__add, this, that, 0, "");


f2ptr raw__semantic_self__event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "event"), that);
}

f2ptr f2__semantic_self__event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_self, this);
  assert_argument_type(semantic_event,     that);
  return raw__semantic_self__event__remove(cause, this, that);
}
export_cefunk2(semantic_self__event__remove, this, that, 0, "");


f2ptr f2__semantic_self_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "event"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__event__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "event"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__event__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "event"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_self"), new__symbol(cause, "semantic_self__event__remove")));}
  return this;
}



// **

f2ptr f2__semantic_self__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_self__core_extension__ping, 0, "");

f2ptr f2__semantic_self__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_self, semantic_object);
  core_extension__ping(semantic_self, semantic_event);
  status("semantic_self initialized.");
  return nil;
}
export_cefunk0(semantic_self__core_extension__initialize, 0, "");

f2ptr f2__semantic_self__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_self"), f2__semantic_self_type__new(cause));
  status("semantic_self define types.");
  return nil;
}
export_cefunk0(semantic_self__core_extension__define_types, 0, "");

f2ptr f2__semantic_self__core_extension__destroy(f2ptr cause) {
  status("semantic_self destroyed.");
  return nil;
}
export_cefunk0(semantic_self__core_extension__destroy, 0, "");


