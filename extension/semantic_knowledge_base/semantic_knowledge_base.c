// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#include "../../c/funk2.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"


// semantic_realm

f2ptr raw__semantic_realm__new(f2ptr cause) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),          new__symbol(cause, "semantic_realm"),
					    new__symbol(cause, "semantic_hash"), f2__hash(cause)));
}

f2ptr f2__semantic_realm__new(f2ptr cause) {
  return raw__semantic_realm__new(cause);
}
export_cefunk0(semantic_realm__new, 0, "Returns a new semantic_realm object.");


boolean_t raw__semantic_realm__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_realm");
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

f2ptr f2__semantic_realm__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_realm__is_type(cause, thing));
}
export_cefunk1(semantic_realm__is_type, thing, 0, "Returns whether or not thing is of type semantic_realm.");


f2ptr raw__semantic_realm__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_realm__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__type(cause, this);
}
export_cefunk1(semantic_realm__type, thing, 0, "Returns the specific type of object that this semantic_realm is.");


f2ptr raw__semantic_realm__semantic_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_hash"), nil);
}

f2ptr f2__semantic_realm__semantic_hash(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__semantic_hash(cause, this);
}
export_cefunk1(semantic_realm__semantic_hash, thing, 0, "Returns the semantic_hash of the semantic_realm.");


f2ptr raw__semantic_realm__semantic_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_hash"), value);
}

f2ptr f2__semantic_realm__semantic_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__semantic_hash__set(cause, this, value);
}
export_cefunk2(semantic_realm__semantic_hash__set, thing, value, 0, "Sets the semantic_hash of the semantic_realm.");


f2ptr raw__semantic_realm__lookup_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr hash = raw__semantic_realm__semantic_hash(cause, this);
  return f2__hash__lookup(cause, hash, object);
}

f2ptr f2__semantic_realm__lookup_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__lookup_object_key(cause, this, object);
}
export_cefunk2(semantic_realm__lookup_object_key, this, object, 0, "Returns the an `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__semantic_realm__add_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr hash = raw__semantic_realm__semantic_hash(cause, this);
  f2ptr key  = raw__hash__lookup(cause, hash, object);
  if (key == nil) {
    raw__hash__add(cause, hash, object, object);
  }
  return nil;
}

f2ptr f2__semantic_realm__add_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__add_object_key(cause, this, object);
}
export_cefunk2(semantic_realm__add_object_key, this, object, 0, "Generates an internal `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__semantic_realm__object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr object_key = raw__semantic_realm__lookup_object_key(cause, this, object);
  if (object_key != nil) {
    return object_key;
  }
  raw__semantic_realm__add_object_key(cause, this, object);
  return raw__semantic_realm__lookup_object_key(cause, this, object);
}

f2ptr f2__semantic_realm__object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__object_key(cause, this, object);
}
export_cefunk2(semantic_realm__object_key, this, object, 0, "Returns an `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__semantic_realm__key_count(f2ptr cause, f2ptr this) {
  f2ptr semantic_hash = raw__semantic_realm__semantic_hash(cause, this);
  return f2__hash__key_count(cause, semantic_hash);
}

f2ptr f2__semantic_realm__key_count(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__key_count(cause, this);
}
export_cefunk1(semantic_realm__key_count, this, 0, "Returns the count of how many keys are in this semantic_realm.");


f2ptr raw__semantic_realm__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_realm"),
					       new__symbol(cause, "key_count"),         f2__semantic_realm__key_count(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_realm__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_realm__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_realm_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_object_key"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_object_key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__add_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "object_key"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__terminal_print_with_frame")));}
  return this;
}




// semantic_frame

f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr realm) {
  return f2__frame__new(cause, f2list6__new(cause,
					    new__symbol(cause, "type"),  new__symbol(cause, "semantic_frame"),
					    new__symbol(cause, "realm"), realm,
					    new__symbol(cause, "frame"), f2__frame__new(cause, nil)));
}

f2ptr f2__semantic_frame__new(f2ptr cause, f2ptr realm) {
  if (! raw__semantic_realm__is_type(cause, realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__new(cause, realm);
}
export_cefunk1(semantic_frame__new, realm, 0, "Returns a new semantic_frame object.");


boolean_t raw__semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_frame");
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

f2ptr f2__semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_frame__is_type(cause, thing));
}
export_cefunk1(semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type semantic_frame.");


f2ptr raw__semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__type(cause, this);
}
export_cefunk1(semantic_frame__type, thing, 0, "Returns the specific type of object that this semantic_frame is.");


f2ptr raw__semantic_frame__realm(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "realm"), nil);
}

f2ptr f2__semantic_frame__realm(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__realm(cause, this);
}
export_cefunk1(semantic_frame__realm, thing, 0, "Returns the realm of the semantic_frame.");


f2ptr raw__semantic_frame__realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "realm"), value);
}

f2ptr f2__semantic_frame__realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__realm__set(cause, this, value);
}
export_cefunk2(semantic_frame__realm__set, thing, value, 0, "Sets the realm of the semantic_frame.");


f2ptr raw__semantic_frame__frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "frame"), nil);
}

f2ptr f2__semantic_frame__frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__frame(cause, this);
}
export_cefunk1(semantic_frame__frame, thing, 0, "Returns the frame of the semantic_frame.");


f2ptr raw__semantic_frame__frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "frame"), value);
}

f2ptr f2__semantic_frame__frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__frame__set(cause, this, value);
}
export_cefunk2(semantic_frame__frame__set, thing, value, 0, "Sets the frame of the semantic_frame.");


f2ptr raw__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr realm                = raw__semantic_frame__realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, realm, key_type);
  f2ptr key__object_key      = raw__semantic_realm__object_key(cause, realm, key);
  f2ptr value_set            = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (value_set == nil) {
    value_set = f2__set__new(cause);
    raw__frame__add_type_var_value(cause, frame, key_type__object_key, key__object_key, value_set);
  }
  raw__set__add(cause, value_set, value);
  return nil;
}

f2ptr f2__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__add(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__add, this, key_type, key, value, 0, "Adds the value to the key_type and key list of values.");


f2ptr raw__semantic_frame__lookup(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr realm                = raw__semantic_frame__realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, realm, key_type);
  f2ptr key__object_key      = raw__semantic_realm__object_key(cause, realm, key);
  return raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
}

f2ptr f2__semantic_frame__lookup(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__lookup(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup, this, key_type, key, 0, "Returns the values associated with the key_type and key.");


// this function is dangerous.  make sure that you are sure of the size of the recursive structure you are asking it to iterate over.
// this is function is safely used from the semantic_frame_ball core_extension.  it is recommended that you use that interface unless you know what you are doing.
f2ptr raw__semantic_frame__add_recursively_to_graph_with_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
    f2__graph__add_node(cause, graph, this_node);
    semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value,
			      f2ptr key_type_node   = f2__graph_node__new(cause, key_type_name);
			      f2ptr key_node        = f2__graph_node__new(cause, key_name);
			      f2ptr slot_value_node;
			      if (raw__semantic_frame__is_type(cause, slot_value)) {
				slot_value_node = raw__semantic_frame__add_recursively_to_graph_with_ptypehash(cause, slot_value, graph, node_ptypehash);
			      } else {
				slot_value_node = f2__graph_node__new(cause, slot_value);
			      }
			      f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key_type"), this_node,     key_type_node);
			      f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key"),      key_type_node, key_node);
			      f2__graph__add_new_edge(cause, graph, new__symbol(cause, "value"),    key_node,      slot_value_node);
			      );
  }
  return this_node;
}


f2ptr raw__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  return new__string(cause, "semantic_frame");
}

f2ptr f2__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__as__graphviz_label(cause, this);
}
export_cefunk1(semantic_frame__as__graphviz_label, this, 0, "Simply returns the string 'semantic_frame' for rendering semantic frames in graphviz.");


f2ptr f2__semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "realm"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__realm")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "realm"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__realm__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__as__graphviz_label")));}
  return this;
}


// semantic_knowledge_base

f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),            new__symbol(cause, "semantic_knowledge_base"),
					    new__symbol(cause, "semantic_frames"), semantic_frames));
}

f2ptr f2__semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  if ((semantic_frames != nil) && (! raw__cons__is_type(cause, semantic_frames))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__new(cause, semantic_frames);
}
export_cefunk0_and_rest(semantic_knowledge_base__new, user_semantic_frames, 0, "Takes frames and returns a new semantic_knowledge_base object.");


boolean_t raw__semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_knowledge_base");
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

f2ptr f2__semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_knowledge_base__type, thing, 0, "Returns the specific type of object that this semantic_knowledge_base is.");


f2ptr raw__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frames"), nil);
}

f2ptr f2__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frames(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_frames, thing, 0, "Returns the semantic_frames of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frames"), value);
}

f2ptr f2__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frames__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__semantic_frames__set, thing, value, 0, "Sets the semantic_frames of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  f2ptr node_ptypehash = f2__ptypehash__new(cause);
  f2ptr graph          = f2__graph__new(cause);
  f2ptr iter = raw__semantic_knowledge_base__semantic_frames(cause, this);
  while (iter != nil) {
    f2ptr root_frame = f2__cons__car(cause, iter);
    raw__frame__add_recursively_to_graph_with_ptypehash(cause, root_frame, graph, node_ptypehash);
    iter = f2__cons__cdr(cause, iter);
  }
  return graph;
}

f2ptr f2__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__as__graph(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__graph, this, 0, "Converts the semantic_knowledge_base to a graph.");


f2ptr raw__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frames = raw__semantic_knowledge_base__semantic_frames(cause, this);
  raw__semantic_knowledge_base__semantic_frames__set(cause, this, f2cons__new(cause, semantic_frame, semantic_frames));
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__add_semantic_frame, this, semantic_frame, 0, "Adds a semantic_frame to this semantic_knowledge_base.");


f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frames"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frames"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graph"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__graph")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_frame")));}
  return this;
}


// noun_semantic_frame

f2ptr raw__noun_semantic_frame__new(f2ptr cause, f2ptr realm) {
  f2ptr this = f2__semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "noun_semantic_frame"));
  return this;
}

f2ptr f2__noun_semantic_frame__new(f2ptr cause, f2ptr realm) {
  if (! raw__semantic_realm__is_type(cause, realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__new(cause, realm);
}
export_cefunk1(noun_semantic_frame__new, realm, 0, "Returns a new noun_semantic_frame object.");


boolean_t raw__noun_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "noun_semantic_frame");
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

f2ptr f2__noun_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__noun_semantic_frame__is_type(cause, thing));
}
export_cefunk1(noun_semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type noun_semantic_frame.");


f2ptr raw__noun_semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__noun_semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__noun_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__type(cause, this);
}
export_cefunk1(noun_semantic_frame__type, thing, 0, "Returns the specific type of object that this noun_semantic_frame is.");


f2ptr raw__noun_semantic_frame__add_noun(f2ptr cause, f2ptr this, f2ptr noun) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "noun"), noun, f2bool__new(boolean__true));
}

f2ptr f2__noun_semantic_frame__add_noun(f2ptr cause, f2ptr this, f2ptr noun) {
  if (! raw__noun_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__add_noun(cause, this, noun);
}
export_cefunk2(noun_semantic_frame__add_noun, this, noun, 0, "Adds a noun to this noun_semantic_frame.");


f2ptr raw__noun_semantic_frame__add_classifier(f2ptr cause, f2ptr this, f2ptr classifier) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "classifier"), classifier, f2bool__new(boolean__true));
}

f2ptr f2__noun_semantic_frame__add_classifier(f2ptr cause, f2ptr this, f2ptr classifier) {
  if (! raw__noun_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__add_classifier(cause, this, classifier);
}
export_cefunk2(noun_semantic_frame__add_classifier, this, classifier, 0, "Adds a classifier to this noun_semantic_frame.");


f2ptr raw__noun_semantic_frame__add_adjective(f2ptr cause, f2ptr this, f2ptr adjective) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "adjective"), adjective, f2bool__new(boolean__true));
}

f2ptr f2__noun_semantic_frame__add_adjective(f2ptr cause, f2ptr this, f2ptr adjective) {
  if (! raw__noun_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__add_adjective(cause, this, adjective);
}
export_cefunk2(noun_semantic_frame__add_adjective, this, adjective, 0, "Adds a adjective to this noun_semantic_frame.");


f2ptr raw__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "preposition"), preposition, semantic_object);
}

f2ptr f2__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object) {
  if (! raw__noun_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__noun_semantic_frame__add_preposition(cause, this, preposition, semantic_object);
}
export_cefunk3(noun_semantic_frame__add_preposition, this, preposition, semantic_object, 0, "Adds a preposition and object to this noun_semantic_frame.");


f2ptr f2__noun_semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_noun"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__add_noun")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_classifier"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__add_classifier")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_adjective"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__add_adjective")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_preposition"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "noun_semantic_frame__add_preposition")));}
  return this;
}


// visual_object_semantic_frame

f2ptr raw__visual_object_semantic_frame__new(f2ptr cause, f2ptr realm) {
  f2ptr this = f2__noun_semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "visual_object_semantic_frame"));
  return this;
}

f2ptr f2__visual_object_semantic_frame__new(f2ptr cause, f2ptr realm) {
  if (! raw__semantic_realm__is_type(cause, realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__visual_object_semantic_frame__new(cause, realm);
}
export_cefunk1(visual_object_semantic_frame__new, realm, 0, "Returns a new visual_object_semantic_frame object.");


boolean_t raw__visual_object_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "visual_object_semantic_frame");
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

f2ptr f2__visual_object_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__visual_object_semantic_frame__is_type(cause, thing));
}
export_cefunk1(visual_object_semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type visual_object_semantic_frame.");


f2ptr raw__visual_object_semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__visual_object_semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__visual_object_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__visual_object_semantic_frame__type(cause, this);
}
export_cefunk1(visual_object_semantic_frame__type, thing, 0, "Returns the specific type of object that this visual_object_semantic_frame is.");


f2ptr raw__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "visual_object_name"), visual_object_name, f2bool__new(boolean__true));
}

f2ptr f2__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name) {
  if (! raw__visual_object_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__visual_object_semantic_frame__add_visual_object_name(cause, this, visual_object_name);
}
export_cefunk2(visual_object_semantic_frame__add_visual_object_name, this, visual_object_name, 0, "Adds a visual_object_name to this visual_object_semantic_frame.");


f2ptr f2__visual_object_semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "noun_semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "visual_object_semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "visual_object_semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "visual_object_semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_visual_object_name"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "visual_object_semantic_frame__add_visual_object_name")));}
  return this;
}


// **

f2ptr f2__semantic_knowledge_base__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_ping, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_realm"),               f2__semantic_realm_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),               f2__semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"),      f2__semantic_knowledge_base_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "noun_semantic_frame"),          f2__noun_semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "visual_object_semantic_frame"), f2__visual_object_semantic_frame_type__new(cause));
  printf("\nsemantic_knowledge_base initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  printf("\nsemantic_knowledge_base destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_destroy, 0, "");


