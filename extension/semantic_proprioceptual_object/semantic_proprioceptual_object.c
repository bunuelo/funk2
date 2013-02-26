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

#include "semantic_proprioceptual_object.h"


// semantic_proprioceptual_object

f2ptr raw__semantic_proprioceptual_object__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr physical_object_type, f2ptr position, f2ptr orientation) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_proprioceptual_object"));
  }
  {
    f2ptr result = raw__semantic_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"),     new__symbol(cause, "physical_object_type"), physical_object_type);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "position"),             position);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "orientation"),          orientation);
  return this;
}

f2ptr raw__semantic_proprioceptual_object__new(f2ptr cause, f2ptr semantic_realm, f2ptr physical_object_type, f2ptr position, f2ptr orientation) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_proprioceptual_object__type_create(cause, this, semantic_realm, physical_object_type, position, orientation);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_proprioceptual_object__new(f2ptr cause, f2ptr semantic_realm, f2ptr physical_object_type, f2ptr position, f2ptr orientation) {
  assert_argument_type(semantic_realm,                      semantic_realm);
  assert_argument_type(symbol,                              physical_object_type);
  assert_argument_type(semantic_proprioceptual_position,    position);
  assert_argument_type(semantic_proprioceptual_orientation, orientation);
  return raw__semantic_proprioceptual_object__new(cause, semantic_realm, physical_object_type, position, orientation);
}
export_cefunk4(semantic_proprioceptual_object__new, semantic_realm, physical_object_type, position, orientation, 0, "Returns a new semantic_proprioceptual_object object.");


boolean_t raw__semantic_proprioceptual_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_proprioceptual_object");
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

f2ptr f2__semantic_proprioceptual_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_proprioceptual_object__is_type(cause, thing));
}
export_cefunk1(semantic_proprioceptual_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_proprioceptual_object.");


f2ptr raw__semantic_proprioceptual_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_proprioceptual_object__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__type(cause, this);
}
export_cefunk1(semantic_proprioceptual_object__type, thing, 0, "Returns the specific type of object that this semantic_proprioceptual_object is.");


f2ptr raw__semantic_proprioceptual_object__physical_object_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "physical_object_type"));
}

f2ptr f2__semantic_proprioceptual_object__physical_object_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__physical_object_type(cause, this);
}
export_cefunk1(semantic_proprioceptual_object__physical_object_type, this, 0, "");


f2ptr raw__semantic_proprioceptual_object__physical_object_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "physical_object_type"), that);
}

f2ptr f2__semantic_proprioceptual_object__physical_object_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__physical_object_type__set(cause, this, that);
}
export_cefunk2(semantic_proprioceptual_object__physical_object_type__set, this, that, 0, "");


f2ptr raw__semantic_proprioceptual_object__position(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "position"));
}

f2ptr f2__semantic_proprioceptual_object__position(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__position(cause, this);
}
export_cefunk1(semantic_proprioceptual_object__position, this, 0, "");


f2ptr raw__semantic_proprioceptual_object__position__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "position"), that);
}

f2ptr f2__semantic_proprioceptual_object__position__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__position__set(cause, this, that);
}
export_cefunk2(semantic_proprioceptual_object__position__set, this, that, 0, "");


f2ptr raw__semantic_proprioceptual_object__orientation(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "orientation"));
}

f2ptr f2__semantic_proprioceptual_object__orientation(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__orientation(cause, this);
}
export_cefunk1(semantic_proprioceptual_object__orientation, this, 0, "");


f2ptr raw__semantic_proprioceptual_object__orientation__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "orientation"), that);
}

f2ptr f2__semantic_proprioceptual_object__orientation__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioceptual_object, this);
  return raw__semantic_proprioceptual_object__orientation__set(cause, this, that);
}
export_cefunk2(semantic_proprioceptual_object__orientation__set, this, that, 0, "");


f2ptr f2__semantic_proprioceptual_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "physical_object_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__physical_object_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "physical_object_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__physical_object_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "position"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__position")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "position"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__position__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "orientation"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__orientation")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "orientation"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioceptual_object"), new__symbol(cause, "semantic_proprioceptual_object__orientation__set")));}
  return this;
}



// **

f2ptr f2__semantic_proprioceptual_object__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_proprioceptual_object__core_extension__ping, 0, "");

f2ptr f2__semantic_proprioceptual_object__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_proprioceptual_object, semantic_object);
  core_extension__ping(semantic_proprioceptual_object, semantic_proprioceptual_position);
  core_extension__ping(semantic_proprioceptual_object, semantic_proprioceptual_orientation);
  status("semantic_proprioceptual_object initialized.");
  return nil;
}
export_cefunk0(semantic_proprioceptual_object__core_extension__initialize, 0, "");

f2ptr f2__semantic_proprioceptual_object__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_proprioceptual_object"), f2__semantic_proprioceptual_object_type__new(cause));
  status("semantic_proprioceptual_object define types.");
  return nil;
}
export_cefunk0(semantic_proprioceptual_object__core_extension__define_types, 0, "");

f2ptr f2__semantic_proprioceptual_object__core_extension__destroy(f2ptr cause) {
  status("semantic_proprioceptual_object destroyed.");
  return nil;
}
export_cefunk0(semantic_proprioceptual_object__core_extension__destroy, 0, "");


