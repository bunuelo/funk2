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

#include "semantic_action_knowledge_base.h"


f2ptr raw__semantic_action_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_action__is_type(cause, semantic_frame)) {
    f2ptr semantic_action = semantic_frame;
    if (raw__eq(cause, new__symbol(cause, "relationship"), key_type) && raw__eq(cause, new__symbol(cause, "example_event"), key)) {
      f2ptr example_event = value;
      {
	f2ptr transframe_set = assert_value(f2__semantic_event__transframe__lookup_set(cause, example_event));
	set__iteration(cause, transframe_set, transframe,
		       //f2ptr removal_set  = assert_value(f2__semantic_event_transframe__removal__lookup_set(cause, transframe));
		       //f2ptr addition_set = assert_value(f2__semantic_event_transframe__addition__lookup_set(cause, transframe));
		       //set__iteration(cause, removal_set, removal,
		       //		      
		       //		      );
		       //set__iteration(cause, addition_set, addition,
		       //		      
		       //		      );
		       );
      }
    }
  }
  return nil;
}

f2ptr f2__semantic_action_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_action_knowledge_base, this);
  assert_argument_type(semantic_frame,                semantic_frame);
  return raw__semantic_action_knowledge_base__know_of_add__after_callback(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_action_knowledge_base__know_of_add__after_callback, this, semantic_frame, key_type, key, value, 0, "Callback for semantic_action_knowledge_base.");


// semantic_action_knowledge_base

f2ptr raw__semantic_action_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_action_knowledge_base"));
  }
  assert_value(raw__meta_semantic_knowledge_base__type_create(cause, this, name, semantic_realm));
  assert_value(raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(    cause, this, f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_action_knowledge_base"), new__symbol(cause, "semantic_action_knowledge_base__know_of_add__after_callback"))));
  return this;
}

f2ptr raw__semantic_action_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_action_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__semantic_action_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_action_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_action_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new semantic_action_knowledge_base object.");


boolean_t raw__semantic_action_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_action_knowledge_base");
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

f2ptr f2__semantic_action_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_action_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_action_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_action_knowledge_base.");


f2ptr raw__semantic_action_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_action_knowledge_base__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_action_knowledge_base, this);
  return raw__semantic_action_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_action_knowledge_base__type, thing, 0, "Returns the specific type of object that this semantic_action_knowledge_base is.");







f2ptr f2__semantic_action_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "meta_semantic_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_action_knowledge_base"), new__symbol(cause, "semantic_action_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_action_knowledge_base"), new__symbol(cause, "semantic_action_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_action_knowledge_base"), new__symbol(cause, "semantic_action_knowledge_base__type")));}
  return this;
}



// **

f2ptr f2__semantic_action_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_action_knowledge_base__core_extension__ping, 0, "");


f2ptr f2__semantic_action_knowledge_base__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_action_knowledge_base, meta_semantic_knowledge_base);
  core_extension__ping(semantic_action_knowledge_base, semantic_action);
  f2__add_type(cause, new__symbol(cause, "semantic_action_knowledge_base"), f2__semantic_action_knowledge_base_type__new(cause));
  status("semantic_action_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_action_knowledge_base__core_extension__initialize, 0, "");


f2ptr f2__semantic_action_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_action_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_action_knowledge_base__core_extension__destroy, 0, "");


