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

#include "semantic_partial_state_property.h"


//[semantic_object_property_type_event-phenomenal_name [object_type_event-phenomenal_name [semantic_object_property_type_event-phenomenal_name source_type
//											                                                       `property source_property source_property_value]]
//						       `property property property_value]]]

f2ptr raw__semantic_partial_state_property__phenomenal_name(f2ptr cause, 
							    f2ptr source_type,
							    f2ptr source_key_type,
							    f2ptr source_key,
							    f2ptr source_value,
							    f2ptr key_type,
							    f2ptr key,
							    f2ptr target_type) {
  return raw__semantic_object_property_type_event__phenomenal_name(cause,
								   raw__object_type_event__phenomenal_name(cause, raw__semantic_object_property_type_event__phenomenal_name(cause,
																					    source_type,
																					    source_key_type,
																					    source_key,
																					    source_value)),
								   key_type,
								   key,
								   target_type);
}

f2ptr f2__semantic_partial_state_property__phenomenal_name(f2ptr cause, 
							   f2ptr source_type,
							   f2ptr source_key_type,
							   f2ptr source_key,
							   f2ptr source_value,
							   f2ptr key_type,
							   f2ptr key,
							   f2ptr target_type) {
  return raw__semantic_partial_state_property__phenomenal_name(cause, 
							       source_type,
							       source_key_type,
							       source_key,
							       source_value,
							       key_type,
							       key,
							       target_type);
}
export_cefunk7(semantic_partial_state_property__phenomenal_name,
	       source_type,
	       source_key_type,
	       source_key,
	       source_value,
	       key_type,
	       key,
	       target_type, 0, "");


// semantic_partial_state_property

f2ptr raw__semantic_partial_state_property__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm,
							f2ptr source_type,
							f2ptr source_key_type,
							f2ptr source_key,
							f2ptr source_value,
							f2ptr key_type,
							f2ptr key,
							f2ptr target_type) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_partial_state_property"));
  }
  assert_value(raw__semantic_partial_state__type_create(cause, this, semantic_realm));
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_type"),     source_type);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key_type"), source_key_type);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key"),      source_key);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_value"),    source_value);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key_type"),        key_type);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key"),             key);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "target_type"),     target_type);
  {
    f2ptr phenomenal_name = f2__semantic_partial_state_property__phenomenal_name(cause, 
										 source_type,
										 source_key_type,
										 source_key,
										 source_value,
										 key_type,
										 key,
										 target_type);
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "phenomenal_name"), phenomenal_name);
  }
  return this;
}

f2ptr raw__semantic_partial_state_property__new(f2ptr cause, f2ptr semantic_realm,
						f2ptr source_type,
						f2ptr source_key_type,
						f2ptr source_key,
						f2ptr source_value,
						f2ptr key_type,
						f2ptr key,
						f2ptr target_type) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_partial_state_property__type_create(cause, this, semantic_realm,
								 source_type,
								 source_key_type,
								 source_key,
								 source_value,
								 key_type,
								 key,
								 target_type));
  return this;
}

f2ptr f2__semantic_partial_state_property__new(f2ptr cause, f2ptr semantic_realm,
					       f2ptr source_type,
					       f2ptr source_key_type,
					       f2ptr source_key,
					       f2ptr source_value,
					       f2ptr key_type,
					       f2ptr key,
					       f2ptr target_type) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_partial_state_property__new(cause, semantic_realm,
						   source_type,
						   source_key_type,
						   source_key,
						   source_value,
						   key_type,
						   key,
						   target_type);
}
export_cefunk8(semantic_partial_state_property__new, semantic_realm,
	       source_type,
	       source_key_type,
	       source_key,
	       source_value,
	       key_type,
	       key,
	       target_type, 0, "Returns a new semantic_partial_state_property object.");


boolean_t raw__semantic_partial_state_property__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_partial_state_property");
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

f2ptr f2__semantic_partial_state_property__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_partial_state_property__is_type(cause, thing));
}
export_cefunk1(semantic_partial_state_property__is_type, thing, 0, "Returns whether or not thing is of type semantic_partial_state_property.");


f2ptr raw__semantic_partial_state_property__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_partial_state_property__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__type(cause, this);
}
export_cefunk1(semantic_partial_state_property__type, thing, 0, "Returns the specific type of object that this semantic_partial_state_property is.");


f2ptr raw__semantic_partial_state_property__source_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_type"));
}

f2ptr f2__semantic_partial_state_property__source_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_type(cause, this);
}
export_cefunk1(semantic_partial_state_property__source_type, this, 0, "");


f2ptr raw__semantic_partial_state_property__source_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_type"), that);
}

f2ptr f2__semantic_partial_state_property__source_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_type__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__source_type__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__source_key_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key_type"));
}

f2ptr f2__semantic_partial_state_property__source_key_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_key_type(cause, this);
}
export_cefunk1(semantic_partial_state_property__source_key_type, this, 0, "");


f2ptr raw__semantic_partial_state_property__source_key_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key_type"), that);
}

f2ptr f2__semantic_partial_state_property__source_key_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_key_type__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__source_key_type__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__source_key(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key"));
}

f2ptr f2__semantic_partial_state_property__source_key(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_key(cause, this);
}
export_cefunk1(semantic_partial_state_property__source_key, this, 0, "");


f2ptr raw__semantic_partial_state_property__source_key__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_key"), that);
}

f2ptr f2__semantic_partial_state_property__source_key__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_key__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__source_key__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__source_value(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_value"));
}

f2ptr f2__semantic_partial_state_property__source_value(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_value(cause, this);
}
export_cefunk1(semantic_partial_state_property__source_value, this, 0, "");


f2ptr raw__semantic_partial_state_property__source_value__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "source_value"), that);
}

f2ptr f2__semantic_partial_state_property__source_value__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__source_value__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__source_value__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__key_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key_type"));
}

f2ptr f2__semantic_partial_state_property__key_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__key_type(cause, this);
}
export_cefunk1(semantic_partial_state_property__key_type, this, 0, "");


f2ptr raw__semantic_partial_state_property__key_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key_type"), that);
}

f2ptr f2__semantic_partial_state_property__key_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__key_type__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__key_type__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__key(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key"));
}

f2ptr f2__semantic_partial_state_property__key(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__key(cause, this);
}
export_cefunk1(semantic_partial_state_property__key, this, 0, "");


f2ptr raw__semantic_partial_state_property__key__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "key"), that);
}

f2ptr f2__semantic_partial_state_property__key__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__key__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__key__set, this, that, 0, "");


f2ptr raw__semantic_partial_state_property__target_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "target_type"));
}

f2ptr f2__semantic_partial_state_property__target_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__target_type(cause, this);
}
export_cefunk1(semantic_partial_state_property__target_type, this, 0, "");


f2ptr raw__semantic_partial_state_property__target_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "target_type"), that);
}

f2ptr f2__semantic_partial_state_property__target_type__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_partial_state_property, this);
  return raw__semantic_partial_state_property__target_type__set(cause, this, that);
}
export_cefunk2(semantic_partial_state_property__target_type__set, this, that, 0, "");


f2ptr f2__semantic_partial_state_property__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_partial_state")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "source_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "source_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "source_key_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "source_key_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "source_key"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_key")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "source_key"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "source_value"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_value")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "source_value"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__source_value__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "key_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "key_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "key"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__key")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "key"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "target_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__target_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "target_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_partial_state_property"), new__symbol(cause, "semantic_partial_state_property__target_type__set")));}
  return this;
}





// **

f2ptr f2__semantic_partial_state_property__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_partial_state_property__core_extension__ping, 0, "");


f2ptr f2__semantic_partial_state_property__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_partial_state_property, semantic_partial_state);
  status("semantic_partial_state_property initialized.");
  return nil;
}
export_cefunk0(semantic_partial_state_property__core_extension__initialize, 0, "");


f2ptr f2__semantic_partial_state_property__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_partial_state_property"), f2__semantic_partial_state_property__primobject_type__new(cause));
  status("semantic_partial_state_property define types.");
  return nil;
}
export_cefunk0(semantic_partial_state_property__core_extension__define_types, 0, "");


f2ptr f2__semantic_partial_state_property__core_extension__destroy(f2ptr cause) {
  status("semantic_partial_state_property destroyed.");
  return nil;
}
export_cefunk0(semantic_partial_state_property__core_extension__destroy, 0, "");


