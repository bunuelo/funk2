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

#include "semantic_environment.h"


// semantic_environment

f2ptr raw__semantic_environment__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_environment"));
  }
  assert_value(raw__semantic_object__type_create(cause, this, semantic_realm));
  return this;
}

f2ptr raw__semantic_environment__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_environment__type_create(cause, this, semantic_realm));
  return this;
}

f2ptr f2__semantic_environment__new(f2ptr cause, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_environment__new(cause, semantic_realm);
}
export_cefunk1(semantic_environment__new, semantic_realm, 0, "Returns a new semantic_environment object.");


boolean_t raw__semantic_environment__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_environment");
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

f2ptr f2__semantic_environment__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_environment__is_type(cause, thing));
}
export_cefunk1(semantic_environment__is_type, thing, 0, "Returns whether or not thing is of type semantic_environment.");


f2ptr raw__semantic_environment__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_environment__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__type(cause, this);
}
export_cefunk1(semantic_environment__type, thing, 0, "Returns the specific type of object that this semantic_environment is.");


f2ptr raw__semantic_environment__parent__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "parent"));
}

f2ptr f2__semantic_environment__parent__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__parent__lookup_set(cause, this);
}
export_cefunk1(semantic_environment__parent__lookup_set, this, 0, "Returns the set of parents.");


f2ptr raw__semantic_environment__parent__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "parent"), that);
}

f2ptr f2__semantic_environment__parent__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_environment, this);
  assert_argument_type(semantic_environment, that);
  return raw__semantic_environment__parent__add(cause, this, that);
}
export_cefunk2(semantic_environment__parent__add, this, that, 0, "");


f2ptr raw__semantic_environment__parent__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "parent"), that);
}

f2ptr f2__semantic_environment__parent__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_environment, this);
  assert_argument_type(semantic_environment, that);
  return raw__semantic_environment__parent__remove(cause, this, that);
}
export_cefunk2(semantic_environment__parent__remove, this, that, 0, "");


f2ptr raw__semantic_environment__variable__lookup_set(f2ptr cause, f2ptr this, f2ptr variable_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "variable"), variable_name);
}

f2ptr f2__semantic_environment__variable__lookup_set(f2ptr cause, f2ptr this, f2ptr variable_name) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__variable__lookup_set(cause, this, variable_name);
}
export_cefunk2(semantic_environment__variable__lookup_set, this, variable_name, 0, "Returns the set of variable bindings for this semantic_environment's default frame variable, returns nil if no such set exists.");


f2ptr raw__semantic_environment__variable__add(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "variable"), variable_name, that);
}

f2ptr f2__semantic_environment__variable__add(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__variable__add(cause, this, variable_name, that);
}
export_cefunk3(semantic_environment__variable__add, this, variable_name, that, 0, "Adds the given value to this semantic_environment's default frame variable bindings.");


f2ptr raw__semantic_environment__variable__remove(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "variable"), variable_name, that);
}

f2ptr f2__semantic_environment__variable__remove(f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr that) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__variable__remove(cause, this, variable_name, that);
}
export_cefunk3(semantic_environment__variable__remove, this, variable_name, that, 0, "Removes the given value from this semantic_environment's default frame variable bindings.");


f2ptr raw__semantic_environment__lookup_a_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  f2ptr variable_value_set = raw__semantic_environment__variable__lookup_set(cause, this, variable_name);
  if (variable_value_set == nil) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "funk_name"),            new__symbol(cause, "semantic_environment-lookup_a_variable_value"),
				   new__symbol(cause, "bug_name"),             new__symbol(cause, "variable_value_set-is-nil"),
				   new__symbol(cause, "semantic_environment"), this,
				   new__symbol(cause, "variable_name"),        variable_name));
  }
  return assert_value(f2__set__an_arbitrary_element(cause, variable_value_set));
}

f2ptr f2__semantic_environment__lookup_a_variable_value(f2ptr cause, f2ptr this, f2ptr variable_name) {
  assert_argument_type(semantic_environment, this);
  return raw__semantic_environment__lookup_a_variable_value(cause, this, variable_name);
}
export_cefunk2(semantic_environment__lookup_a_variable_value, this, variable_name, 0, "");



f2ptr f2__semantic_environment__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "parent"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__parent__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "parent"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__parent__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "parent"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__parent__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "variable"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__variable__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "variable"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__variable__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "variable"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__variable__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "lookup_a_variable_value"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_environment"), new__symbol(cause, "semantic_environment__lookup_a_variable_value")));}
  return this;
}





// **

f2ptr f2__semantic_environment__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_environment__core_extension__ping, 0, "");


f2ptr f2__semantic_environment__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_environment, semantic_object);
  status("semantic_environment initialized.");
  return nil;
}
export_cefunk0(semantic_environment__core_extension__initialize, 0, "");


f2ptr f2__semantic_environment__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_environment"), f2__semantic_environment__primobject_type__new(cause));
  status("semantic_environment define types.");
  return nil;
}
export_cefunk0(semantic_environment__core_extension__define_types, 0, "");


f2ptr f2__semantic_environment__core_extension__destroy(f2ptr cause) {
  status("semantic_environment destroyed.");
  return nil;
}
export_cefunk0(semantic_environment__core_extension__destroy, 0, "");


