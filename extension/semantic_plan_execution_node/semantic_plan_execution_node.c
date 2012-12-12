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

#include "semantic_plan_execution_node.h"


// semantic_plan_execution_node

f2ptr raw__semantic_plan_execution_node__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr node_type, f2ptr nonsemantic_plan_execution_node) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_plan_execution_node"));
  }
  assert_value(raw__semantic_object__type_create(cause, this, semantic_realm));
  raw__semantic_object__phenomenal_name__set(cause, this, phenomenal_name);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"), nonsemantic_plan_execution_node);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "node_type"), node_type);
  return this;
}

f2ptr raw__semantic_plan_execution_node__new(f2ptr cause, f2ptr semantic_realm, f2ptr node_type, f2ptr nonsemantic_plan_execution_node) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_plan_execution_node__type_create(cause, this, semantic_realm, node_type, nonsemantic_plan_execution_node));
  return this;
}

f2ptr f2__semantic_plan_execution_node__new(f2ptr cause, f2ptr semantic_realm, f2ptr node_type, f2ptr nonsemantic_plan_execution_node) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_plan_execution_node__new(cause, semantic_realm, node_type, nonsemantic_plan_execution_node);
}
export_cefunk3(semantic_plan_execution_node__new, semantic_realm, node_type, nonsemantic_plan_execution_node, 0, "Returns a new semantic_plan_execution_node object.");


boolean_t raw__semantic_plan_execution_node__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_plan_execution_node");
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

f2ptr f2__semantic_plan_execution_node__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_plan_execution_node__is_type(cause, thing));
}
export_cefunk1(semantic_plan_execution_node__is_type, thing, 0, "Returns whether or not thing is of type semantic_plan_execution_node.");


f2ptr raw__semantic_plan_execution_node__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_plan_execution_node__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__type(cause, this);
}
export_cefunk1(semantic_plan_execution_node__type, thing, 0, "Returns the specific type of object that this semantic_plan_execution_node is.");


f2ptr raw__semantic_plan_execution_node__node_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "node_type"));
}

f2ptr f2__semantic_plan_execution_node__node_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__node_type(cause, this);
}
export_cefunk1(semantic_plan_execution_node__node_type, this, 0, "");


f2ptr raw__semantic_plan_execution_node__node_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "node_type"), that);
}

f2ptr f2__semantic_plan_execution_node__node_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__node_type__set(cause, this, that);
}
export_cefunk2(semantic_plan_execution_node__node_type__set, this, that, 0, "");



f2ptr raw__semantic_plan_execution_node__nonsemantic_plan_execution_node(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"), nil);
}

f2ptr f2__semantic_plan_execution_node__nonsemantic_plan_execution_node(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__nonsemantic_plan_execution_node(cause, this);
}
export_cefunk1(semantic_plan_execution_node__nonsemantic_plan_execution_node, this, 0, "");


f2ptr raw__semantic_plan_execution_node__nonsemantic_plan_execution_node__set(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "nonsemantic_plan_execution_node"), that);
}

f2ptr f2__semantic_plan_execution_node__nonsemantic_plan_execution_node__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__nonsemantic_plan_execution_node__set(cause, this, that);
}
export_cefunk2(semantic_plan_execution_node__nonsemantic_plan_execution_node__set, this, that, 0, "");


f2ptr raw__semantic_plan_execution_node__subnode__lookup_set(f2ptr cause, f2ptr this, f2ptr variable_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "subnode"), variable_name);
}

f2ptr f2__semantic_plan_execution_node__subnode__lookup_set(f2ptr cause, f2ptr this, f2ptr variable_name) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__subnode__lookup_set(cause, this, variable_name);
}
export_cefunk2(semantic_plan_execution_node__subnode__lookup_set, this, variable_name, 0, "Returns the set of variable bindings for this semantic_plan_execution_node's default frame variable, returns nil if no such set exists.");


f2ptr raw__semantic_plan_execution_node__subnode__add(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "subnode"), variable_name, that);
}

f2ptr f2__semantic_plan_execution_node__subnode__add(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__subnode__add(cause, this, variable_name, that);
}
export_cefunk3(semantic_plan_execution_node__subnode__add, this, variable_name, that, 0, "Adds the given value to this semantic_plan_execution_node's default frame variable bindings.");


f2ptr raw__semantic_plan_execution_node__subnode__remove(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "subnode"), variable_name, that);
}

f2ptr f2__semantic_plan_execution_node__subnode__remove(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  assert_argument_type(semantic_plan_execution_node, this);
  return raw__semantic_plan_execution_node__subnode__remove(cause, this, variable_name, that);
}
export_cefunk3(semantic_plan_execution_node__subnode__remove, this, variable_name, that, 0, "Removes the given value from this semantic_plan_execution_node's default frame variable bindings.");


f2ptr f2__semantic_plan_execution_node__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "plan_object_type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__plan_object_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "plan_object_type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__plan_object_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "node_type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__node_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "node_type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__node_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "nonsemantic_plan_execution_node"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__nonsemantic_plan_execution_node")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "nonsemantic_plan_execution_node"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__nonsemantic_plan_execution_node__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "subnode"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__subnode__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "subnode"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__subnode__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "subnode"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_plan_execution_node"), new__symbol(cause, "semantic_plan_execution_node__subnode__remove")));}
  return this;
}


// **

f2ptr f2__semantic_plan_execution_node__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_plan_execution_node__core_extension__ping, 0, "");

f2ptr f2__semantic_plan_execution_node__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_plan_execution_node, semantic_object);
  core_extension__ping(semantic_plan_execution_node, semantic_environment);
  f2__add_type(cause, new__symbol(cause, "semantic_plan_execution_node"), f2__semantic_plan_execution_node__primobject_type__new(cause));
  status("semantic_plan_execution_node initialized.");
  return nil;
}
export_cefunk0(semantic_plan_execution_node__core_extension__initialize, 0, "");

f2ptr f2__semantic_plan_execution_node__core_extension__destroy(f2ptr cause) {
  status("semantic_plan_execution_node destroyed.");
  return nil;
}
export_cefunk0(semantic_plan_execution_node__core_extension__destroy, 0, "");


