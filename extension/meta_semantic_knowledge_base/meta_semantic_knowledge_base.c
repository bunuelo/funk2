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
#include "meta_semantic_knowledge_base.h"


// meta_semantic_knowledge_base

f2ptr raw__meta_semantic_knowledge_base__new(f2ptr cause) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),          new__symbol(cause, "meta_semantic_knowledge_base"),
					    new__symbol(cause, "semantic_hash"), f2__hash(cause)));
}

f2ptr f2__meta_semantic_knowledge_base__new(f2ptr cause) {
  return raw__meta_semantic_knowledge_base__new(cause);
}
export_cefunk0(meta_semantic_knowledge_base__new, 0, "Returns a new meta_semantic_knowledge_base object.");


boolean_t raw__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_knowledge_base");
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

f2ptr f2__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_knowledge_base__is_type(cause, thing));
}
export_cefunk1(meta_semantic_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__type(cause, this);
}
export_cefunk1(meta_semantic_knowledge_base__type, thing, 0, "Returns the specific type of object that this meta_semantic_knowledge_base is.");


f2ptr raw__meta_semantic_knowledge_base__semantic_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_hash"), nil);
}

f2ptr f2__meta_semantic_knowledge_base__semantic_hash(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__semantic_hash(cause, this);
}
export_cefunk1(meta_semantic_knowledge_base__semantic_hash, thing, 0, "Returns the semantic_hash of the meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__semantic_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_hash"), value);
}

f2ptr f2__meta_semantic_knowledge_base__semantic_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__semantic_hash__set(cause, this, value);
}
export_cefunk2(meta_semantic_knowledge_base__semantic_hash__set, thing, value, 0, "Sets the semantic_hash of the meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__lookup_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr hash = raw__meta_semantic_knowledge_base__semantic_hash(cause, this);
  return f2__hash__lookup(cause, hash, object);
}

f2ptr f2__meta_semantic_knowledge_base__lookup_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__lookup_object_key(cause, this, object);
}
export_cefunk2(meta_semantic_knowledge_base__lookup_object_key, this, object, 0, "Returns the an `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__meta_semantic_knowledge_base__add_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr hash = raw__meta_semantic_knowledge_base__semantic_hash(cause, this);
  f2ptr key  = raw__hash__lookup(cause, hash, object);
  if (key == nil) {
    raw__hash__add(cause, hash, object, object);
  }
  return nil;
}

f2ptr f2__meta_semantic_knowledge_base__add_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__add_object_key(cause, this, object);
}
export_cefunk2(meta_semantic_knowledge_base__add_object_key, this, object, 0, "Generates an internal `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__meta_semantic_knowledge_base__object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr object_key = raw__meta_semantic_knowledge_base__lookup_object_key(cause, this, object);
  if (object_key != nil) {
    return object_key;
  }
  raw__meta_semantic_knowledge_base__add_object_key(cause, this, object);
  return raw__meta_semantic_knowledge_base__lookup_object_key(cause, this, object);
}

f2ptr f2__meta_semantic_knowledge_base__object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__object_key(cause, this, object);
}
export_cefunk2(meta_semantic_knowledge_base__object_key, this, object, 0, "Returns an `equals key mapping for this object for use within this semantic realm.");


f2ptr raw__meta_semantic_knowledge_base__key_count(f2ptr cause, f2ptr this) {
  f2ptr semantic_hash = raw__meta_semantic_knowledge_base__semantic_hash(cause, this);
  return f2__hash__key_count(cause, semantic_hash);
}

f2ptr f2__meta_semantic_knowledge_base__key_count(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__key_count(cause, this);
}
export_cefunk1(meta_semantic_knowledge_base__key_count, this, 0, "Returns the count of how many keys are in this meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "meta_semantic_knowledge_base"),
					       new__symbol(cause, "key_count"),         f2__meta_semantic_knowledge_base__key_count(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__meta_semantic_knowledge_base__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(meta_semantic_knowledge_base__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__meta_semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__semantic_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__semantic_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_object_key"),         f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__lookup_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_object_key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__add_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "object_key"),                f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__terminal_print_with_frame")));}
  return this;
}


// **

f2ptr f2__meta_semantic_knowledge_base__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_ping, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension_initialize(f2ptr cause) {
  f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__core_extension_ping")), nil);
  f2__add_type(cause, new__symbol(cause, "meta_semantic_knowledge_base"), f2__meta_semantic_knowledge_base_type__new(cause));
  status("meta_semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  status("\nmeta_semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_destroy, 0, "");


