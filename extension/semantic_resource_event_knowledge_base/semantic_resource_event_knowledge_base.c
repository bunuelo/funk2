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

#include "semantic_resource_event_knowledge_base.h"


// semantic_resource_event_knowledge_base

f2ptr raw__semantic_resource_event_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_resource_event_knowledge_base"));
  }
  assert_value(raw__semantic_event_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr raw__semantic_resource_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_resource_event_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__semantic_resource_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_resource_event_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_resource_event_knowledge_base__new, name, semantic_realm, 0, "Returns a new semantic_resource_event_knowledge_base object.");


boolean_t raw__semantic_resource_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_resource_event_knowledge_base");
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

f2ptr f2__semantic_resource_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_resource_event_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_resource_event_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_resource_event_knowledge_base.");


f2ptr raw__semantic_resource_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_resource_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_resource_event_knowledge_base, this);
  return raw__semantic_resource_event_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_resource_event_knowledge_base__type, thing, 0,
	       "Returns the specific type of object that this semantic_resource_event_knowledge_base is.");


f2ptr raw__semantic_resource_event_knowledge_base__resource_targeting_events_containing_time(f2ptr cause, f2ptr this, f2ptr semantic_resource, f2ptr semantic_time) {
  f2ptr events_containing_time    = assert_value(f2__semantic_event_knowledge_base__events_containing_time(cause, this, semantic_time));
  f2ptr resource_targeting_events = nil;
  status("semantic_resource_event_knowledge_base__resource_targeting_events_containing_time debug.");
  {
    f2ptr iter = events_containing_time;
    while (iter != nil) {
      status("semantic_resource_event_knowledge_base__resource_targeting_events_containing_time debug.");
      f2ptr event_containing_time = assert_value(f2__cons__car(cause, iter));
      {
	if (raw__semantic_know_of_relationship_event__is_type(cause, event_containing_time)) {
	  f2ptr meta_relationship = f2__semantic_know_of_relationship_event__meta_relationship(cause, event_containing_time);
	  if (raw__relationship_meta_semantic_object__is_type(cause, meta_relationship)) {
	    f2ptr target = f2__relationship_meta_semantic_object__target(cause, meta_relationship);
	    if (raw__eq(cause, target, semantic_resource)) {
	      resource_targeting_events = f2cons__new(cause, event_containing_time, resource_targeting_events);
	    }
	  }
	}
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  return resource_targeting_events;
}

f2ptr f2__semantic_resource_event_knowledge_base__resource_targeting_events_containing_time(f2ptr cause, f2ptr this, f2ptr semantic_resource, f2ptr semantic_time) {
  assert_argument_type(semantic_resource_event_knowledge_base, this);
  assert_argument_type(semantic_resource,                      semantic_resource);
  assert_argument_type(semantic_time,                          semantic_time);
  return raw__semantic_resource_event_knowledge_base__resource_targeting_events_containing_time(cause, this, semantic_resource, semantic_time);
}
export_cefunk3(semantic_resource_event_knowledge_base__resource_targeting_events_containing_time, this, semantic_resource, semantic_time, 0,
	       "Returns all of semantic_know_of_relationship_events containing the given semantic_time and targeting the given semantic_resource.");


f2ptr f2__semantic_resource_event_knowledge_base__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_event_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_event_knowledge_base"), new__symbol(cause, "semantic_resource_event_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_event_knowledge_base"), new__symbol(cause, "semantic_resource_event_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_event_knowledge_base"), new__symbol(cause, "semantic_resource_event_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "resource_targeting_events_containing_time"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_event_knowledge_base"), new__symbol(cause, "semantic_resource_event_knowledge_base__resource_targeting_events_containing_time")));}
  return this;
}





// **

f2ptr f2__semantic_resource_event_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_resource_event_knowledge_base__core_extension__ping, 0, "");

f2ptr f2__semantic_resource_event_knowledge_base__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_resource_event_knowledge_base, semantic_event_knowledge_base);
  core_extension__ping(semantic_resource_event_knowledge_base, semantic_know_of_relationship_event);
  core_extension__ping(semantic_resource_event_knowledge_base, semantic_resource);
  return nil;
}
export_cefunk0(semantic_resource_event_knowledge_base__core_extension__initialize, 0, "");

f2ptr f2__semantic_resource_event_knowledge_base__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_resource_event_knowledge_base"), f2__semantic_resource_event_knowledge_base__primobject_type__new(cause));
  status("semantic_resource_event_knowledge_base defined types.");
  return nil;
}
export_cefunk0(semantic_resource_event_knowledge_base__core_extension__define_types, 0, "");

f2ptr f2__semantic_resource_event_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_resource_event_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_resource_event_knowledge_base__core_extension__destroy, 0, "");




