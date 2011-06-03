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

#include "semantic_event_knowledge_base.h"


f2ptr raw__semantic_event_knowledge_base__know_of_remove__before_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_event__is_type(cause, semantic_frame)) {
    f2ptr semantic_event = semantic_frame;
    if (raw__eq(cause, new__symbol(cause, "property"), key_type) && (raw__eq(cause, new__symbol(cause, "absolute_start_time"), key) ||
								     raw__eq(cause, new__symbol(cause, "absolute_end_time"),   key))) {
      f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
      assert_value(f2__semantic_event_tree__remove(cause, semantic_event_tree, semantic_event));
      printf("-"); fflush(stdout);
    }
  }
  return nil;
}

f2ptr f2__semantic_event_knowledge_base__know_of_remove__before_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_frame,                semantic_frame);
  return raw__semantic_event_knowledge_base__know_of_remove__before_callback(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_event_knowledge_base__know_of_remove__before_callback, this, semantic_frame, key_type, key, value, 0, "Callback for semantic_event_knowledge_base to update internal semantic_event_tree.");


f2ptr raw__semantic_event_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_event__is_type(cause, semantic_frame)) {
    f2ptr semantic_event = semantic_frame;
    if (raw__eq(cause, new__symbol(cause, "property"), key_type) && (raw__eq(cause, new__symbol(cause, "absolute_start_time"), key) ||
								     raw__eq(cause, new__symbol(cause, "absolute_end_time"),   key))) {
      printf("+"); fflush(stdout);
      f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
      assert_value(f2__semantic_event_tree__insert(cause, semantic_event_tree, semantic_event));
    }
  }
  return nil;
}

f2ptr f2__semantic_event_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_frame,                semantic_frame);
  return raw__semantic_event_knowledge_base__know_of_add__after_callback(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_event_knowledge_base__know_of_add__after_callback, this, semantic_frame, key_type, key, value, 0, "Callback for semantic_event_knowledge_base to update internal semantic_event_tree.");


// semantic_event_knowledge_base

f2ptr raw__semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = f2__meta_semantic_knowledge_base__new(cause, name, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),                new__symbol(cause, "semantic_event_knowledge_base"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_event_tree"), f2__semantic_event_tree__new(cause));
  assert_value(raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(cause, this, f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__know_of_remove__before_callback"))));
  assert_value(raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(    cause, this, f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__know_of_add__after_callback"))));
  return this;
}

f2ptr f2__semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_event_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_event_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new semantic_event_knowledge_base object.");


boolean_t raw__semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_event_knowledge_base");
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

f2ptr f2__semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_event_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_event_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_event_knowledge_base.");


f2ptr raw__semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event_knowledge_base, this);
  return raw__semantic_event_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_event_knowledge_base__type, thing, 0, "Returns the specific type of object that this semantic_event_knowledge_base is.");


f2ptr raw__semantic_event_knowledge_base__semantic_event_tree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_event_tree"), nil);
}

f2ptr f2__semantic_event_knowledge_base__semantic_event_tree(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event_knowledge_base, this);
  return raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
}
export_cefunk1(semantic_event_knowledge_base__semantic_event_tree, thing, 0, "Returns this semantic_event_knowledge_base's semantic_event_tree.");


f2ptr f2__semantic_event_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "meta_semantic_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_event_tree"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__semantic_event_tree")));}
  return this;
}



// **

f2ptr f2__semantic_event_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__ping, 0, "");


f2ptr f2__semantic_event_knowledge_base__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_event_knowledge_base, meta_semantic_knowledge_base);
  core_extension__ping(semantic_event_knowledge_base, semantic_event);
  core_extension__ping(semantic_event_knowledge_base, semantic_event_tree);
  f2__add_type(cause, new__symbol(cause, "semantic_event_knowledge_base"), f2__semantic_event_knowledge_base_type__new(cause));
  status("semantic_event_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__initialize, 0, "");


f2ptr f2__semantic_event_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_event_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__destroy, 0, "");


