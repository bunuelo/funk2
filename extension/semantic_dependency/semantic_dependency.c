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

#include "semantic_dependency.h"


// semantic_dependency

f2ptr raw__semantic_dependency__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),                  new__symbol(cause, "semantic_dependency"));
    raw__frame__add_var_value(cause, this, new__symbol(cause, "invalidated_callbacks"), nil);
    raw__frame__add_var_value(cause, this, new__symbol(cause, "unsupported_callbacks"), nil);
  }
  assert_value(raw__semantic_object__type_create(cause, this, semantic_realm));
  // avoids redefining in cases of multiple inheritance.
  if (raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "property"), new__symbol(cause, "precondition_time")) == nil) {
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "precondition_time"),   nil);
    raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "resource_activation"), nil);
  }
  return this;
}

f2ptr raw__semantic_dependency__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_dependency__type_create(cause, this, semantic_realm));
  return this;
}

f2ptr f2__semantic_dependency__new(f2ptr cause, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_dependency__new(cause, semantic_realm);
}
export_cefunk1(semantic_dependency__new, semantic_realm, 0, "Returns a new semantic_dependency object.");


boolean_t raw__semantic_dependency__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_dependency");
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

f2ptr f2__semantic_dependency__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_dependency__is_type(cause, thing));
}
export_cefunk1(semantic_dependency__is_type, thing, 0, "Returns whether or not thing is of type semantic_dependency.");


f2ptr raw__semantic_dependency__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_dependency__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__type(cause, this);
}
export_cefunk1(semantic_dependency__type, thing, 0, "Returns the specific type of object that this semantic_dependency is.");


f2ptr raw__semantic_dependency__resource_activation(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "resource_activation"));
}

f2ptr f2__semantic_dependency__resource_activation(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__resource_activation(cause, this);
}
export_cefunk1(semantic_dependency__resource_activation, this, 0, "");


f2ptr raw__semantic_dependency__resource_activation__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "resource_activation"), that);
}

f2ptr f2__semantic_dependency__resource_activation__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__resource_activation__set(cause, this, that);
}
export_cefunk2(semantic_dependency__resource_activation__set, this, that, 0, "");


f2ptr raw__semantic_dependency__precondition_time(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "precondition_time"));
}

f2ptr f2__semantic_dependency__precondition_time(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__precondition_time(cause, this);
}
export_cefunk1(semantic_dependency__precondition_time, this, 0, "");


f2ptr raw__semantic_dependency__precondition_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "precondition_time"), that);
}

f2ptr f2__semantic_dependency__precondition_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__precondition_time__set(cause, this, that);
}
export_cefunk2(semantic_dependency__precondition_time__set, this, that, 0, "");


f2ptr raw__semantic_dependency__precondition_event__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "precondition_event"));
}

f2ptr f2__semantic_dependency__precondition_event__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__precondition_event__lookup_set(cause, this);
}
export_cefunk1(semantic_dependency__precondition_event__lookup_set, this, 0, "Returns the set of precondition_events.");


f2ptr raw__semantic_dependency__precondition_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "precondition_event"), that);
}

f2ptr f2__semantic_dependency__precondition_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__precondition_event__add(cause, this, that);
}
export_cefunk2(semantic_dependency__precondition_event__add, this, that, 0, "");


f2ptr raw__semantic_dependency__precondition_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "precondition_event"), that);
}

f2ptr f2__semantic_dependency__precondition_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__precondition_event__remove(cause, this, that);
}
export_cefunk2(semantic_dependency__precondition_event__remove, this, that, 0, "");


f2ptr raw__semantic_dependency__change_hypothesis__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "change_hypothesis"));
}

f2ptr f2__semantic_dependency__change_hypothesis__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__change_hypothesis__lookup_set(cause, this);
}
export_cefunk1(semantic_dependency__change_hypothesis__lookup_set, this, 0, "Returns the set of change_hypothesiss.");


f2ptr raw__semantic_dependency__change_hypothesis__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "change_hypothesis"), that);
}

f2ptr f2__semantic_dependency__change_hypothesis__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__change_hypothesis__add(cause, this, that);
}
export_cefunk2(semantic_dependency__change_hypothesis__add, this, that, 0, "");


f2ptr raw__semantic_dependency__change_hypothesis__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "change_hypothesis"), that);
}

f2ptr f2__semantic_dependency__change_hypothesis__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_dependency, this);
  return raw__semantic_dependency__change_hypothesis__remove(cause, this, that);
}
export_cefunk2(semantic_dependency__change_hypothesis__remove, this, that, 0, "");


f2ptr raw__semantic_dependency__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"),   f2__object__type(cause, this),
						new__symbol(cause, "precondition_time"),   raw__semantic_dependency__precondition_time(cause, this),
						new__symbol(cause, "resource_activation"), raw__semantic_dependency__resource_activation(cause, this),
						new__symbol(cause, "precondition_event"),  raw__semantic_dependency__precondition_event__lookup_set(cause, this),
						new__symbol(cause, "change_hypothesis"),   raw__semantic_dependency__change_hypothesis__lookup_set(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_dependency__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(semantic_dependency,  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__semantic_dependency__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_dependency__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_dependency__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "resource_activation"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__resource_activation")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "resource_activation"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__resource_activation__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "precondition_time"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__precondition_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "precondition_time"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__precondition_time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "precondition_event"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__precondition_event__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "precondition_event"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__precondition_event__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "precondition_event"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__precondition_event__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "change_hypothesis"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__change_hypothesis__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "change_hypothesis"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__change_hypothesis__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "change_hypothesis"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__change_hypothesis__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_dependency"), new__symbol(cause, "semantic_dependency__terminal_print_with_frame")));}
  return this;
}





// **

f2ptr f2__semantic_dependency__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_dependency__core_extension__ping, 0, "");


f2ptr f2__semantic_dependency__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_dependency, semantic_object);
  status("semantic_dependency initialized.");
  return nil;
}
export_cefunk0(semantic_dependency__core_extension__initialize, 0, "");


f2ptr f2__semantic_dependency__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_dependency"), f2__semantic_dependency__primobject_type__new(cause));
  status("semantic_dependency define types.");
  return nil;
}
export_cefunk0(semantic_dependency__core_extension__define_types, 0, "");


f2ptr f2__semantic_dependency__core_extension__destroy(f2ptr cause) {
  status("semantic_dependency destroyed.");
  return nil;
}
export_cefunk0(semantic_dependency__core_extension__destroy, 0, "");


