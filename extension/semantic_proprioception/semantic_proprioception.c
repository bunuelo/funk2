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

#include "semantic_proprioception.h"


// semantic_proprioception

f2ptr raw__semantic_proprioception__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr body, f2ptr neck, f2ptr left_hand, f2ptr right_hand) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_proprioception"));
  }
  {
    f2ptr result = raw__semantic_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "body"),       body);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "neck"),       neck);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "left_hand"),  left_hand);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "right_hand"), right_hand);
  return this;
}

f2ptr raw__semantic_proprioception__new(f2ptr cause, f2ptr semantic_realm, f2ptr body, f2ptr neck, f2ptr left_hand, f2ptr right_hand) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_proprioception__type_create(cause, this, semantic_realm, body, neck, left_hand, right_hand);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_proprioception__new(f2ptr cause, f2ptr semantic_realm, f2ptr body, f2ptr neck, f2ptr left_hand, f2ptr right_hand) {
  assert_argument_type(semantic_realm,                 semantic_realm);
  assert_argument_type(semantic_proprioceptual_object, body);
  assert_argument_type(semantic_proprioceptual_object, neck);
  assert_argument_type(semantic_proprioceptual_object, left_hand);
  assert_argument_type(semantic_proprioceptual_object, right_hand);
  return raw__semantic_proprioception__new(cause, semantic_realm, body, neck, left_hand, right_hand);
}
export_cefunk5(semantic_proprioception__new, semantic_realm, body, neck, left_hand, right_hand, 0, "Returns a new semantic_proprioception object.");


boolean_t raw__semantic_proprioception__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_proprioception");
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

f2ptr f2__semantic_proprioception__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_proprioception__is_type(cause, thing));
}
export_cefunk1(semantic_proprioception__is_type, thing, 0, "Returns whether or not thing is of type semantic_proprioception.");


f2ptr raw__semantic_proprioception__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_proprioception__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__type(cause, this);
}
export_cefunk1(semantic_proprioception__type, thing, 0, "Returns the specific type of object that this semantic_proprioception is.");


f2ptr raw__semantic_proprioception__body(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "body"));
}

f2ptr f2__semantic_proprioception__body(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__body(cause, this);
}
export_cefunk1(semantic_proprioception__body, this, 0, "");


f2ptr raw__semantic_proprioception__body__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "body"), that);
}

f2ptr f2__semantic_proprioception__body__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__body__set(cause, this, that);
}
export_cefunk2(semantic_proprioception__body__set, this, that, 0, "");


f2ptr raw__semantic_proprioception__neck(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "neck"));
}

f2ptr f2__semantic_proprioception__neck(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__neck(cause, this);
}
export_cefunk1(semantic_proprioception__neck, this, 0, "");


f2ptr raw__semantic_proprioception__neck__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "neck"), that);
}

f2ptr f2__semantic_proprioception__neck__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__neck__set(cause, this, that);
}
export_cefunk2(semantic_proprioception__neck__set, this, that, 0, "");


f2ptr raw__semantic_proprioception__left_hand(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "left_hand"));
}

f2ptr f2__semantic_proprioception__left_hand(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__left_hand(cause, this);
}
export_cefunk1(semantic_proprioception__left_hand, this, 0, "");


f2ptr raw__semantic_proprioception__left_hand__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "left_hand"), that);
}

f2ptr f2__semantic_proprioception__left_hand__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__left_hand__set(cause, this, that);
}
export_cefunk2(semantic_proprioception__left_hand__set, this, that, 0, "");


f2ptr raw__semantic_proprioception__right_hand(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "right_hand"));
}

f2ptr f2__semantic_proprioception__right_hand(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__right_hand(cause, this);
}
export_cefunk1(semantic_proprioception__right_hand, this, 0, "");


f2ptr raw__semantic_proprioception__right_hand__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "right_hand"), that);
}

f2ptr f2__semantic_proprioception__right_hand__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_proprioception, this);
  return raw__semantic_proprioception__right_hand__set(cause, this, that);
}
export_cefunk2(semantic_proprioception__right_hand__set, this, that, 0, "");


f2ptr f2__semantic_proprioception_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "body"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__body")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "body"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__body__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "neck"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__neck")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "neck"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__neck__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "left_hand"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__left_hand")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "left_hand"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__left_hand__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "right_hand"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__right_hand")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "right_hand"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_proprioception"), new__symbol(cause, "semantic_proprioception__right_hand__set")));}
  return this;
}



// **

f2ptr f2__semantic_proprioception__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_proprioception__core_extension__ping, 0, "");

f2ptr f2__semantic_proprioception__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_proprioception, semantic_object);
  core_extension__ping(semantic_proprioception, semantic_proprioceptual_object);
  status("semantic_proprioception initialized.");
  return nil;
}
export_cefunk0(semantic_proprioception__core_extension__initialize, 0, "");

f2ptr f2__semantic_proprioception__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_proprioception"), f2__semantic_proprioception_type__new(cause));
  status("semantic_proprioception define types.");
  return nil;
}
export_cefunk0(semantic_proprioception__core_extension__define_types, 0, "");

f2ptr f2__semantic_proprioception__core_extension__destroy(f2ptr cause) {
  status("semantic_proprioception destroyed.");
  return nil;
}
export_cefunk0(semantic_proprioception__core_extension__destroy, 0, "");


