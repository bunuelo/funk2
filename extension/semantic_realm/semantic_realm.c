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

#include "semantic_realm.h"


// semantic_realm

def_ceframe4(semantic_realm, semantic_realm, semantic_hash, meta_relationship_hash, semantic_knowledge_base_frame, semantic_frame_phenomenon_hash);

f2ptr raw__semantic_realm__new(f2ptr cause) {
  f2ptr semantic_hash                  = f2__equals_hash__new(cause);
  f2ptr meta_relationship_hash         = f2__equals_hash__new(cause);
  f2ptr semantic_knowledge_base_frame  = f2__frame__new(cause, nil);
  f2ptr semantic_frame_phenomenon_hash = f2__equals_hash__new(cause);
  return f2semantic_realm__new(cause, semantic_hash, meta_relationship_hash, semantic_knowledge_base_frame, semantic_frame_phenomenon_hash);
}

f2ptr f2__semantic_realm__new(f2ptr cause) {
  return raw__semantic_realm__new(cause);
}
export_cefunk0(semantic_realm__new, 0, "Returns a new semantic_realm object.");


f2ptr raw__semantic_realm__lookup_object_key(f2ptr cause, f2ptr this, f2ptr object) {
  if (object == nil) {
    return nil;
  }
  f2ptr hash = raw__semantic_realm__semantic_hash(cause, this);
  return f2__equals_hash__lookup(cause, hash, object);
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
  f2ptr key  = raw__equals_hash__lookup(cause, hash, object);
  if (key == nil) {
    raw__equals_hash__add(cause, hash, object, object);
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
  return f2__equals_hash__key_count(cause, semantic_hash);
}

f2ptr f2__semantic_realm__key_count(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__key_count(cause, this);
}
export_cefunk1(semantic_realm__key_count, this, 0, "Returns the count of how many keys are in this semantic_realm.");


f2ptr raw__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  //f2ptr relationship_equals_key         = raw__semantic_relationship_key__new(cause, semantic_frame, key_type, key, value);
  //f2ptr meta_relationship_hash          = raw__semantic_realm__meta_relationship_hash(cause, this);
  //f2ptr previously_created_relationship = f2__equals_hash__lookup(cause, meta_relationship_hash, relationship_equals_key);
  //if (previously_created_relationship != nil) {
  //  return previously_created_relationship;
  //}
  f2ptr relationship = f2__relationship_meta_semantic_object__new(cause, this, semantic_frame, key_type, key, value);
  //f2__equals_hash__add(cause, meta_relationship_hash, relationship_equals_key, relationship);
  return relationship;
}

f2ptr f2__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if ((! raw__semantic_realm__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__lookup_or_create_meta_relationship(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_realm__lookup_or_create_meta_relationship, this, semantic_frame, key_type, key, value, 0, "Returns an eq representative relationship_meta_semantic_object for the given meta relationship by hash lookup, or creation and hashing.");


f2ptr raw__semantic_realm__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base__semantic_realm = raw__semantic_knowledge_base__semantic_realm(cause, semantic_knowledge_base);
  if (! raw__eq(cause, this, semantic_knowledge_base__semantic_realm)) {
    return f2larva__new(cause, 65826, f2__bug__new(cause, f2integer__new(cause, 65826), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),                new__symbol(cause, "tried_to_add_semantic_knowledge_base_to_different_semantic_realm"),
															   new__symbol(cause, "funk_name"),               new__symbol(cause, "semantic_realm-add_semantic_knowledge_base"),
															   new__symbol(cause, "this"),                    this,
															   new__symbol(cause, "semantic_knowledge_base"), semantic_knowledge_base))));
  }
  f2ptr semantic_knowledge_base_frame = raw__semantic_realm__semantic_knowledge_base_frame(cause, this);
  f2ptr semantic_knowledge_base__name = raw__semantic_knowledge_base__name(cause, semantic_knowledge_base);
  if (raw__frame__contains_var(cause, semantic_knowledge_base_frame, semantic_knowledge_base__name)) {
    return f2larva__new(cause, 65827, f2__bug__new(cause, f2integer__new(cause, 65827), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),                new__symbol(cause, "knowledge_base_already_in_realm_with_same_name"),
															   new__symbol(cause, "funk_name"),               new__symbol(cause, "semantic_realm-add_semantic_knowledge_base"),
															   new__symbol(cause, "this"),                    this,
															   new__symbol(cause, "semantic_knowledge_base"), semantic_knowledge_base))));
  }
  f2__frame__add_var_value(cause, semantic_knowledge_base_frame, semantic_knowledge_base__name, semantic_knowledge_base);
  return nil;
}

f2ptr f2__semantic_realm__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  if ((! raw__semantic_realm__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base__is_type(cause, semantic_knowledge_base))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__add_semantic_knowledge_base(cause, this, semantic_knowledge_base);
}
export_cefunk2(semantic_realm__add_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Adds a semantic knowledge base to this mental realm.");


f2ptr raw__semantic_realm__lookup_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr semantic_knowledge_base_frame = raw__semantic_realm__semantic_knowledge_base_frame(cause, this);
  return f2__frame__lookup_var_value(cause, semantic_knowledge_base_frame, name, nil);
}

f2ptr f2__semantic_realm__lookup_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr name) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__lookup_semantic_knowledge_base(cause, this, name);
}
export_cefunk2(semantic_realm__lookup_semantic_knowledge_base, this, name, 0, "Given a name, looks up a semantic knowledge base from this mental realm.");


f2ptr raw__semantic_realm__add_phenomenon_semantic_frame(f2ptr cause, f2ptr this, f2ptr phenomenon, f2ptr semantic_frame) {
  f2ptr semantic_frame_phenomenon_hash = raw__semantic_realm__semantic_frame_phenomenon_hash(cause, this);
  return raw__equals_hash__add(cause, semantic_frame_phenomenon_hash, phenomenon, semantic_frame);
}

f2ptr f2__semantic_realm__add_phenomenon_semantic_frame(f2ptr cause, f2ptr this, f2ptr phenomenon, f2ptr semantic_frame) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__add_phenomenon_semantic_frame(cause, this, phenomenon, semantic_frame);
}
export_cefunk3(semantic_realm__add_phenomenon_semantic_frame, this, phenomenon, semantic_frame, 0, "Adds a phenomenon semantic_frame mapping to this semantic realm.");


f2ptr raw__semantic_realm__lookup_phenomenon_semantic_frame(f2ptr cause, f2ptr this, f2ptr phenomenon) {
  f2ptr semantic_frame_phenomenon_hash = raw__semantic_realm__semantic_frame_phenomenon_hash(cause, this);
  return raw__equals_hash__lookup(cause, semantic_frame_phenomenon_hash, phenomenon);
}

f2ptr f2__semantic_realm__lookup_phenomenon_semantic_frame(f2ptr cause, f2ptr this, f2ptr phenomenon) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__lookup_phenomenon_semantic_frame(cause, this, phenomenon);
}
export_cefunk2(semantic_realm__lookup_phenomenon_semantic_frame, this, phenomenon, 0, "Looks up a phenomenon's semantic_frame from this semantic realm.");


f2ptr raw__semantic_realm__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"),             new__symbol(cause, "semantic_realm"),
					       new__symbol(cause, "key_count"),                     f2__semantic_realm__key_count(cause, this),
					       new__symbol(cause, "semantic_knowledge_base_frame"), f2__semantic_realm__semantic_knowledge_base_frame(cause, this)));
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



f2ptr f2__semantic_realm_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_realm_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_object_key"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__lookup_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_object_key"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__add_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "object_key"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_or_create_meta_relationship"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__lookup_or_create_meta_relationship")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_semantic_knowledge_base"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__lookup_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_phenomenon_semantic_frame"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__add_phenomenon_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_phenomenon_semantic_frame"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__lookup_phenomenon_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_realm"), new__symbol(cause, "semantic_realm__terminal_print_with_frame")));}
  return this;
}



// **

f2ptr f2__semantic_realm__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_realm__core_extension__ping, 0, "");

f2ptr f2__semantic_realm__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_realm, equals_hash);
  core_extension__ping(semantic_realm, forgetful_event_stream);
  core_extension__ping(semantic_realm, lick);
  status("semantic_realm initialized.");
  return nil;
}
export_cefunk0(semantic_realm__core_extension__initialize, 0, "");

f2ptr f2__semantic_realm__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_realm"), f2__semantic_realm_type__new_aux(cause));
  status("semantic_realm defined types.");
  return nil;
}
export_cefunk0(semantic_realm__core_extension__define_types, 0, "");

f2ptr f2__semantic_realm__core_extension__destroy(f2ptr cause) {
  status("semantic_realm destroyed.");
  return nil;
}
export_cefunk0(semantic_realm__core_extension__destroy, 0, "");


