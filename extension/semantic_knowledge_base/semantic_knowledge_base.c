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

#include "../../c/funk2.h"
#include "semantic_knowledge_base.h"
#include "../equals_hash/equals_hash.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"
#include "../event_stream/event_stream.h"
#include "../lick/lick.h"


// object-semantic-lookup, object-semantic-lookup-apply

f2ptr f2__object__semantic__lookup(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-lookup"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-lookup_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__lookup, this, slot, args, 0, "");

f2ptr f2__object__semantic__lookup__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__lookup(cause, this, slot, args);
}
export_cefunk3(object__semantic__lookup__apply, this, slot, args, 0, "");


// object-semantic-add, object-semantic-add-apply

f2ptr f2__object__semantic__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__add__apply, this, slot, args, 0, "");


// object-semantic-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-remove"), slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, 2346, f2__bug__new(cause, f2integer__new(cause, 2346), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
export_cefunk2_and_rest(object__semantic__remove,        this, slot, args, 0, "");

f2ptr f2__object__semantic__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__remove__apply, this, slot, args, 0, "");



// semantic_relationship_key

def_ceframe4(semantic_knowledge_base, semantic_relationship_key,
	     source,
	     key_type,
	     key,
	     target);

f2ptr raw__semantic_relationship_key__new(f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  return f2semantic_relationship_key__new(cause, source, key_type, key, target);
}

f2ptr f2__semantic_relationship_key__new(f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  return raw__semantic_relationship_key__new(cause, source, key_type, key, target);
}
export_cefunk4(semantic_relationship_key__new, source, key_type, key, target, 0, "Returns a new semantic_relationship_key object.");


u64 raw__semantic_relationship_key__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  f2ptr source   = raw__semantic_relationship_key__source(  cause, this);
  f2ptr key_type = raw__semantic_relationship_key__key_type(cause, this);
  f2ptr key      = raw__semantic_relationship_key__key(     cause, this);
  f2ptr target   = raw__semantic_relationship_key__target(  cause, this);
  f2ptr source__eq_hash_value = f2__object__eq_hash_value(cause, source);
  if (raw__larva__is_type(cause, source__eq_hash_value)) {
    return source__eq_hash_value;
  }
  u64 source__eq_hash_value__i = f2integer__i(source__eq_hash_value, cause);
  if (source__eq_hash_value__i == 0) {
    source__eq_hash_value__i = 1;
  }
  f2ptr target__eq_hash_value = f2__object__eq_hash_value(cause, target);
  if (raw__larva__is_type(cause, target__eq_hash_value)) {
    return target__eq_hash_value;
  }
  u64 target__eq_hash_value__i = f2integer__i(target__eq_hash_value, cause);
  if (target__eq_hash_value__i == 0) {
    target__eq_hash_value__i = 1;
  }
  f2ptr key_type__equals_hash_value = f2__object__equals_hash_value__loop_free(cause, key_type, node_ptypehash);
  if (raw__larva__is_type(cause, key_type__equals_hash_value)) {
    return key_type__equals_hash_value;
  }
  u64 key_type__equals_hash_value__i = f2integer__i(key_type__equals_hash_value, cause);
  if (key_type__equals_hash_value__i == 0) {
    key_type__equals_hash_value__i = 1;
  }
  f2ptr key__equals_hash_value = f2__object__equals_hash_value__loop_free(cause, key, node_ptypehash);
  if (raw__larva__is_type(cause, key__equals_hash_value)) {
    return key__equals_hash_value;
  }
  u64 key__equals_hash_value__i = f2integer__i(key__equals_hash_value, cause);
  if (key__equals_hash_value__i == 0) {
    key__equals_hash_value__i = 1;
  }
  return (source__eq_hash_value__i       *
	  key_type__equals_hash_value__i *
	  key__equals_hash_value__i      *
	  target__eq_hash_value__i);
}

f2ptr f2__semantic_relationship_key__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2integer__new(cause, raw__semantic_relationship_key__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
export_cefunk2(semantic_relationship_key__equals_hash_value__loop_free, this, node_ptypehash, 0, "");


u64 raw__semantic_relationship_key__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__semantic_relationship_key__equals_hash_value__loop_free(cause, this, f2__ptypehash__new(cause));
}

f2ptr f2__semantic_relationship_key__equals_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2integer__new(cause, raw__semantic_relationship_key__equals_hash_value(cause, this));
}
export_cefunk1(semantic_relationship_key__equals_hash_value, this, 0, "");


boolean_t raw__semantic_relationship_key__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__semantic_relationship_key__is_type(cause, that)) {
    return boolean__false;
  }
  f2ptr this__source   = raw__semantic_relationship_key__source(  cause, this);
  f2ptr this__key_type = raw__semantic_relationship_key__key_type(cause, this);
  f2ptr this__key      = raw__semantic_relationship_key__key(     cause, this);
  f2ptr this__target   = raw__semantic_relationship_key__target(  cause, this);
  f2ptr that__source   = raw__semantic_relationship_key__source(  cause, that);
  f2ptr that__key_type = raw__semantic_relationship_key__key_type(cause, that);
  f2ptr that__key      = raw__semantic_relationship_key__key(     cause, that);
  f2ptr that__target   = raw__semantic_relationship_key__target(  cause, that);
  return (raw__eq(    cause, this__source,   that__source)   &&
	  raw__eq(    cause, this__target,   that__target)   &&
	  raw__equals(cause, this__key_type, that__key_type) &&
	  raw__equals(cause, this__key,      that__key));
}

f2ptr f2__semantic_relationship_key__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__semantic_relationship_key__equals(cause, this, that));
}
export_cefunk2(semantic_relationship_key__equals, this, that, 0, "");


f2ptr raw__semantic_relationship_key__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_relationship_key"),
						new__symbol(cause, "source"),            f2__semantic_relationship_key__source(  cause, this),
						new__symbol(cause, "key_type"),          f2__semantic_relationship_key__key_type(cause, this),
						new__symbol(cause, "key"),               f2__semantic_relationship_key__key(     cause, this),
						new__symbol(cause, "target"),            f2__semantic_relationship_key__target(  cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_relationship_key__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_relationship_key__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_relationship_key_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_relationship_key_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value-loop_free"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals_hash_value__loop_free")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals_hash_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__terminal_print_with_frame")));}
  return this;
}


// semantic_realm

def_ceframe4(semantic_knowledge_base, semantic_realm, semantic_hash, meta_relationship_hash, semantic_knowledge_base_frame, semantic_frame_phenomenon_hash);

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
  f2ptr relationship_equals_key         = raw__semantic_relationship_key__new(cause, semantic_frame, key_type, key, value);
  f2ptr meta_relationship_hash          = raw__semantic_realm__meta_relationship_hash(cause, this);
  f2ptr previously_created_relationship = f2__equals_hash__lookup(cause, meta_relationship_hash, relationship_equals_key);
  if (previously_created_relationship != nil) {
    return previously_created_relationship;
  }
  f2ptr relationship = f2__relationship_meta_semantic_object__new(cause, this, semantic_frame, key_type, key, value);
  f2__equals_hash__add(cause, meta_relationship_hash, relationship_equals_key, relationship);
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
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_object_key"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_object_key"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__add_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "object_key"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_or_create_meta_relationship"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_or_create_meta_relationship")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_semantic_knowledge_base"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_phenomenon_semantic_frame"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__add_phenomenon_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_phenomenon_semantic_frame"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_phenomenon_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__terminal_print_with_frame")));}
  return this;
}


// semantic_frame_event

f2ptr raw__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr this = f2__event_stream_event__new(cause, time);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),           new__symbol(cause, "semantic_frame_event"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "event_type"),     event_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key_type"),       key_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key"),            key);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "value"),          value);
  return this;
}

f2ptr f2__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  return raw__semantic_frame_event__new(cause, time, event_type, semantic_frame, key_type, key, value);
}
export_cefunk6(semantic_frame_event__new, time, event_type, semantic_frame, key_type, key, value, 0, "Returns a new semantic_frame_event object.");


boolean_t raw__semantic_frame_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_frame_event");
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

f2ptr f2__semantic_frame_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_frame_event__is_type(cause, thing));
}
export_cefunk1(semantic_frame_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_frame_event.");


f2ptr raw__semantic_frame_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_frame_event__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__type(cause, this);
}
export_cefunk1(semantic_frame_event__type, thing, 0, "Returns the specific type of object that this semantic_frame_event is.");


f2ptr raw__semantic_frame_event__event_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "event_type"), nil);
}

f2ptr f2__semantic_frame_event__event_type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__event_type(cause, this);
}
export_cefunk1(semantic_frame_event__event_type, thing, 0, "Returns the event_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "event_type"), value);
}

f2ptr f2__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__event_type__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__event_type__set, thing, value, 0, "Sets the event_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frame"), nil);
}

f2ptr f2__semantic_frame_event__semantic_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__semantic_frame(cause, this);
}
export_cefunk1(semantic_frame_event__semantic_frame, thing, 0, "Returns the semantic_frame of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), value);
}

f2ptr f2__semantic_frame_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__semantic_frame__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__semantic_frame__set, thing, value, 0, "Sets the semantic_frame of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key_type"), nil);
}

f2ptr f2__semantic_frame_event__key_type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__key_type(cause, this);
}
export_cefunk1(semantic_frame_event__key_type, thing, 0, "Returns the key_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key_type"), value);
}

f2ptr f2__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__key_type__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__key_type__set, thing, value, 0, "Sets the key_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key"), nil);
}

f2ptr f2__semantic_frame_event__key(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__key(cause, this);
}
export_cefunk1(semantic_frame_event__key, thing, 0, "Returns the key of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key"), value);
}

f2ptr f2__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__key__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__key__set, thing, value, 0, "Sets the key of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__value(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "value"), nil);
}

f2ptr f2__semantic_frame_event__value(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__value(cause, this);
}
export_cefunk1(semantic_frame_event__value, thing, 0, "Returns the value of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "value"), value);
}

f2ptr f2__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__value__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__value__set, thing, value, 0, "Sets the value of the semantic_frame_event.");


f2ptr f2__semantic_frame_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__event_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__event_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key_type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "value"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "value"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__value__set")));}
  return this;
}




// semantic_frame

def_ceframe6(semantic_knowledge_base, semantic_frame, semantic_realm, trace_add, trace_remove, trace_event_stream, semantic_knowledge_base_set, frame);

f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr trace_event_stream          = nil;
  f2ptr trace_add                   = nil;
  f2ptr trace_remove                = nil;
  f2ptr semantic_knowledge_base_set = f2__set__new(cause);
  f2ptr frame                       = f2__frame__new(cause, nil);
  if (cause != nil) {
    trace_add    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_add"));
    trace_remove = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_remove"));
  }
  return f2semantic_frame__new(cause, semantic_realm, trace_add, trace_remove, trace_event_stream, semantic_knowledge_base_set, frame);
}


f2ptr f2__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__new(cause, semantic_realm);
}
export_cefunk1(semantic_frame__new, semantic_realm, 0, "Returns a new semantic_frame object.");


void raw__semantic_frame__initialize_tracing(f2ptr cause, f2ptr this) {
  if (raw__semantic_frame__trace_event_stream(cause, this) == nil) {
    f2ptr trace_event_stream = f2__event_stream__new(cause);
    raw__semantic_frame__trace_event_stream__set(cause, this, trace_event_stream);
  }
}


f2ptr raw__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr semantic_frame_event = nil;
  if (raw__semantic_frame__trace_add(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_stream = raw__semantic_frame__trace_event_stream(cause, this);
    semantic_frame_event = raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "add"), this, key_type, key, value);
    raw__event_stream__add(cause, trace_event_stream, semantic_frame_event);
  }
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key_type);
  if (raw__larva__is_type(cause, key_type__object_key)) {
    return key_type__object_key;
  }
  f2ptr key__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key);
  if (raw__larva__is_type(cause, key__object_key)) {
    return key__object_key;
  }
  f2ptr value_set = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (value_set == nil) {
    value_set = f2__set__new(cause);
    raw__frame__add_type_var_value(cause, frame, key_type__object_key, key__object_key, value_set);
  }
  raw__set__add(cause, value_set, value);
  {
    f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
    set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		   f2ptr result = raw__semantic_knowledge_base__know_of_semantic_frame_value_addition(cause, semantic_knowledge_base, this, key_type, key, value);
		   if (raw__larva__is_type(cause, result)) {
		     return result;
		   }
		   if (semantic_frame_event != nil) {
		     raw__semantic_knowledge_base__add_trace_event(cause, semantic_knowledge_base, semantic_frame_event);
		   }
		   );
  }
  return nil;
}

f2ptr f2__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__add(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__add, this, key_type, key, value, 0, "Adds the value to the key_type and key set of values.");


f2ptr raw__semantic_frame__remove(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr semantic_frame_event = nil;
  if (raw__semantic_frame__trace_remove(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_stream = raw__semantic_frame__trace_event_stream(cause, this);
    semantic_frame_event = raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "remove"), this, key_type, key, value);
    raw__event_stream__add(cause, trace_event_stream, semantic_frame_event);
  }
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key_type);
  if (raw__larva__is_type(cause, key_type__object_key)) {
    return key_type__object_key;
  }
  f2ptr key__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key);
  if (raw__larva__is_type(cause, key__object_key)) {
    return key__object_key;
  }
  f2ptr value_set = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (value_set == nil) {
    return f2larva__new(cause, 53, nil);
  }
  if (! raw__set__remove(cause, value_set, value)) {
    return f2larva__new(cause, 53, nil);
  }
  {
    f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
    set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		   f2ptr result = raw__semantic_knowledge_base__know_of_semantic_frame_value_removal(cause, semantic_knowledge_base, this, key_type, key, value);
		   if (raw__larva__is_type(cause, result)) {
		     return result;
		   }
		   if (semantic_frame_event != nil) {
		     raw__semantic_knowledge_base__add_trace_event(cause, semantic_knowledge_base, semantic_frame_event);
		   }
		   );
  }
  return nil;
}

f2ptr f2__semantic_frame__remove(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__remove(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__remove, this, key_type, key, value, 0, "Removes the value from the key_type and key set of values.");


f2ptr raw__semantic_frame__lookup(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key_type);
  if (raw__larva__is_type(cause, key_type__object_key)) {
    return key_type__object_key;
  }
  f2ptr key__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key);
  if (raw__larva__is_type(cause, key__object_key)) {
    return key__object_key;
  }
  return raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
}

f2ptr f2__semantic_frame__lookup(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__lookup(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup, this, key_type, key, 0, "Returns the values associated with the key_type and key.");


boolean_t raw__semantic_frame__lookup_contains(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr set = raw__semantic_frame__lookup(cause, this, key_type, key);
  if (set == nil) {
    return boolean__false;
  }
  return raw__set__contains(cause, set, value);
}

f2ptr f2__semantic_frame__lookup_contains(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__lookup_contains(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__lookup_contains, this, key_type, key, value, 0, "Returns the values associated with the key_type and key.");


f2ptr raw__semantic_frame__assure_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__lookup_contains(cause, this, key_type, key, value)) {
    f2ptr result = raw__semantic_frame__add(cause, this, key_type, key, value);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}

f2ptr f2__semantic_frame__assure_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__assure_exists(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__assure_exists, this, key_type, key, value, 0, "Adds the semantic relationship if it does not already exist in this semantic_frame.");


f2ptr raw__semantic_frame__lookup_single_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr source_set = raw__semantic_frame__lookup(cause, this, key_type, key);
  if (source_set == nil) {
    return nil;
  }
  f2ptr return_source = nil;
  s64   source_count  = 0;
  set__iteration(cause, source_set, source,
		 source_count ++;
		 return_source = source);
  if (source_count > 1) {
    return f2larva__new(cause, 415, nil);
  }
  return return_source;
}

f2ptr f2__semantic_frame__lookup_single_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__lookup_single_value(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup_single_value, this, key_type, key, 0, "Returns the single value associated with the key_type and key.  If there is no value associated, nil is returned.  It is a bug if more than one value is associated.");


f2ptr raw__semantic_frame__remove_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key_type);
  if (raw__larva__is_type(cause, key_type__object_key)) {
    return key_type__object_key;
  }
  f2ptr key__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key);
  if (raw__larva__is_type(cause, key__object_key)) {
    return key__object_key;
  }
  f2ptr set = raw__frame__add_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (set != nil) {
    f2ptr elements = raw__set__elements(cause, set);
    {
      f2ptr iter = elements;
      while (iter != nil) {
	f2ptr element = f2__cons__car(cause, iter);
	raw__semantic_frame__remove(cause, this, key_type, key, element);
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return nil;
}

f2ptr f2__semantic_frame__remove_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__remove_all(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__remove_all, this, key_type, key, 0, "Removes all associated values from this key_type and key.");


f2ptr raw__semantic_frame__replace_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  raw__semantic_frame__remove_all(cause, this, key_type, key);
  return raw__semantic_frame__add(cause, this, key_type, key, value);
}

f2ptr f2__semantic_frame__replace_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__replace_all(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__replace_all, this, key_type, key, value, 0, "Removes all associated values from this key_type and key, and adds the given value.");


void raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
  f2__set__add(cause, semantic_knowledge_base_set, semantic_knowledge_base);
}

f2ptr f2__semantic_frame__know_of_addition_to_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  if ((! raw__semantic_frame__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(cause, this, semantic_knowledge_base);
  return nil;
}
export_cefunk2(semantic_frame__know_of_addition_to_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Adds the given semantic_knowledge_base to this semantic_frame's semantic_knowledge_base_set.");


void raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
  f2__set__remove(cause, semantic_knowledge_base_set, semantic_knowledge_base);
}

f2ptr f2__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  if ((! raw__semantic_frame__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(cause, this, semantic_knowledge_base);
  return nil;
}
export_cefunk2(semantic_frame__know_of_removal_from_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Removes the given semantic_knowledge_base from this semantic_frame's semantic_knowledge_base_set.");


boolean_t raw__semantic_frame__recursively_add_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size) {
  if (maximum_size <= 0) {
    return boolean__false;
  }
  boolean_t this_is_in_set = raw__set__contains(cause, set, this);
  if (this_is_in_set) {
    *exact_size = 0;
    return boolean__true;
  }
  f2__set__add(cause, set, this);
  // semantic_frame nodes count as one.
  s64 this_size = 1;
  semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value,
			    key_type_name = nil;
			    key_name      = nil;
			    if (raw__semantic_frame__is_type(cause, slot_value)) {
			      s64 slot_value__exact_size;
			      if (raw__semantic_frame__recursively_add_to_set(cause, slot_value, set, maximum_size - this_size, &slot_value__exact_size)) {
				this_size += slot_value__exact_size;
			      } else {
				return boolean__false;
			      }
			    } else {
			      // non-semantic_frame leaf nodes count as one.
			      this_size ++;
			    }
			    if (this_size >= maximum_size) {
			      return boolean__false;
			    }
			    );
  *exact_size = this_size;
  return boolean__true;
}

f2ptr f2__semantic_frame__recursively_add_to_set(f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place) {
  if ((! raw__semantic_frame__is_type(cause, this)) ||
      (! raw__set__is_type(cause, set)) ||
      (! raw__integer__is_type(cause, maximum_size)) ||
      ((exact_size_place != nil) && (! raw__place__is_type(cause, exact_size_place)))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_frame__recursively_add_to_set(cause, this, set, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 4151, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk4(semantic_frame__recursively_add_to_set, this, set, maximum_size, exact_size_place, 0,
	       "Recursively enumerates all semantic_frames referenced from this semantic frame.\n"
	       "Each semantic_frame is added to the given set.\n"
	       "This function fails if more than maximum_size number of frames is encountered.\n"
	       "A exact_size_place may be given to store the exact_size before returning.");


void raw__semantic_frame__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
  }
  semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value,
			    //f2ptr key_type_node   = f2__graph_node__new(cause, key_type_name);
			    //f2ptr key_node        = f2__graph_node__new(cause, key_name);
			    f2ptr slot_value_node;
			    if (raw__semantic_frame__is_type(cause, slot_value)) {
			      slot_value_node = f2__ptypehash__lookup(cause, node_ptypehash, slot_value);
			      if (slot_value_node == nil) {
				slot_value_node = f2__graph_node__new(cause, slot_value);
				f2__ptypehash__add(cause, node_ptypehash, slot_value, slot_value_node);
			      }
			    } else {
			      slot_value_node = f2__graph_node__new(cause, slot_value);
			    }
			    f2ptr edge_name = f2__stringlist__concat(cause, f2list3__new(cause,
											 f2__exp__as__string(cause, key_type_name),
											 new__string(cause, "-"),
											 f2__exp__as__string(cause, key_name)));
			    f2__graph__add_new_edge(cause, graph, edge_name, this_node, slot_value_node);
			    );
}

f2ptr f2__semantic_frame__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  if ((! raw__semantic_frame__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, graph)) ||
      (! raw__ptypehash__is_type(cause, node_ptypehash))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_frame__add_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash);
  return nil;
}
export_cefunk3(semantic_frame__add_to_graph_with_node_ptypehash, this, graph, node_ptypehash, 0, "Adds this semantic frame and slots to the given graph, using the given node_ptypehash to reuse nodes generated by previous calls to this function.");


f2ptr raw__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  return new__string(cause, "frame");
}

f2ptr f2__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__as__graphviz_label(cause, this);
}
export_cefunk1(semantic_frame__as__graphviz_label, this, 0, "Simply returns the string 'semantic_frame' for rendering semantic frames in graphviz.");


boolean_t raw__semantic_frame__is_semantic_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  return raw__semantic_frame__lookup_contains(cause, this, new__symbol(cause, "type"), new__symbol(cause, "name"), type_name);
}

f2ptr f2__semantic_frame__is_semantic_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__is_semantic_type(cause, this, type_name);
}
export_cefunk2(semantic_frame__is_semantic_type, this, type_name, 0, "Returns true if this semantic_frame is of the given semantic type, false otherwise.");



f2ptr raw__semantic_frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this)));
    f2ptr semantic_frame__frame = raw__semantic_frame__frame(cause, this);
    frame__iteration(cause, semantic_frame__frame, type_slot_name, slot_name, slot_value,
		     f2ptr set           = slot_value;
		     f2ptr set__elements = f2__set__elements(cause, set);
		     raw__frame__add_type_var_value(cause, frame, type_slot_name, slot_name, set__elements);
		     );
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__semantic_frame__is_type(cause, this)) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_frame__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_frame_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_frame_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "lookup_contains"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup_contains")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "assure_exists"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__assure_exists")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_single_value"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup_single_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove_all"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__remove_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "replace_all"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__replace_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_addition_to_semantic_knowledge_base"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__know_of_addition_to_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_removal_from_semantic_knowledge_base"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__know_of_removal_from_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_to_set"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__recursively_add_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__as__graphviz_label")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "is_semantic_type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__is_semantic_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__terminal_print_with_frame")));}
  return this;
}




// semantic_knowledge_base_event

f2ptr raw__semantic_knowledge_base_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame) {
  f2ptr this = f2__event_stream_event__new(cause, time);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),           new__symbol(cause, "semantic_knowledge_base_event"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "event_type"),     event_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
  return this;
}

f2ptr f2__semantic_knowledge_base_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame) {
  return raw__semantic_knowledge_base_event__new(cause, time, event_type, semantic_frame);
}
export_cefunk3(semantic_knowledge_base_event__new, time, event_type, semantic_frame, 0, "Returns a new semantic_knowledge_base_event object.");


boolean_t raw__semantic_knowledge_base_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_knowledge_base_event");
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

f2ptr f2__semantic_knowledge_base_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_knowledge_base_event__is_type(cause, thing));
}
export_cefunk1(semantic_knowledge_base_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_knowledge_base_event__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__type(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__type, thing, 0, "Returns the specific type of object that this semantic_knowledge_base_event is.");


f2ptr raw__semantic_knowledge_base_event__event_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "event_type"), nil);
}

f2ptr f2__semantic_knowledge_base_event__event_type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__event_type(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__event_type, thing, 0, "Returns the event_type of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "event_type"), value);
}

f2ptr f2__semantic_knowledge_base_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__event_type__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base_event__event_type__set, thing, value, 0, "Sets the event_type of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frame"), nil);
}

f2ptr f2__semantic_knowledge_base_event__semantic_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__semantic_frame(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__semantic_frame, thing, 0, "Returns the semantic_frame of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
}

f2ptr f2__semantic_knowledge_base_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__semantic_frame__set(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base_event__semantic_frame__set, thing, semantic_frame, 0, "Sets the semantic_frame of the semantic_knowledge_base_event.");


f2ptr f2__semantic_knowledge_base_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__event_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__event_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__semantic_frame__set")));}
  return this;
}




// semantic_knowledge_base

def_ceframe7(semantic_knowledge_base, semantic_knowledge_base, name, semantic_realm, semantic_frame_set, trace_event_stream, trace_add_semantic_frame, trace_remove_semantic_frame, trace_callback_funks_frame);

f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame) {
  f2ptr trace_callback_funks_frame = f2__frame__new(cause, nil);
  return f2semantic_knowledge_base__new(cause, name, semantic_realm, semantic_frame_set, trace_event_stream, trace_add_semantic_frame, trace_remove_semantic_frame, trace_callback_funks_frame);
}

f2ptr f2__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr trace_event_stream          = nil;
  f2ptr trace_add_semantic_frame    = nil;
  f2ptr trace_remove_semantic_frame = nil;
  if (cause != nil) {
    trace_add_semantic_frame    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_add_semantic_frame"));
    trace_remove_semantic_frame = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_remove_semantic_frame"));
  }
  f2ptr semantic_frame_set = f2__set__new(cause);
  f2ptr this = raw__semantic_knowledge_base__new(cause, name, semantic_realm, semantic_frame_set, trace_event_stream, trace_add_semantic_frame, trace_remove_semantic_frame);
  f2__semantic_realm__add_semantic_knowledge_base(cause, semantic_realm, this);
  return this;
}
export_cefunk2(semantic_knowledge_base__new, name, semantic_realm, 0, "Takes a name nad a semantic_realm and returns a new semantic_knowledge_base object.");


f2ptr raw__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  f2ptr node_ptypehash     = f2__ptypehash__new(cause);
  f2ptr graph              = f2__graph__new(cause);
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  set__iteration(cause, semantic_frame_set, root_frame,
		 raw__frame__add_recursively_to_graph_with_ptypehash(cause, root_frame, graph, node_ptypehash);
		 );
  return graph;
}

f2ptr f2__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__as__graph(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__graph, this, 0, "Converts the semantic_knowledge_base to a graph.");


void raw__semantic_knowledge_base__initialize_tracing(f2ptr cause, f2ptr this) {
  if (raw__semantic_knowledge_base__trace_event_stream(cause, this) == nil) {
    f2ptr trace_event_stream = f2__event_stream__new(cause);
    raw__semantic_knowledge_base__trace_event_stream__set(cause, this, trace_event_stream);
  }
}


f2ptr raw__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  // tell the semantic frame that it belongs to this semantic_knowledge_base (so we can receive change events)
  raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(cause, semantic_frame, this);
  {
    // check for semantic_realm match.
    f2ptr semantic_realm                 = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr semantic_frame__semantic_realm = raw__semantic_frame__semantic_realm(cause, semantic_frame);
    if (! raw__eq(cause, semantic_frame__semantic_realm, semantic_realm)) {
      return f2larva__new(cause, 8924, f2__bug__new(cause, f2integer__new(cause, 8924), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),                               new__symbol(cause, "semantic_frame_semantic_realm_does_not_match_semantic_knowledge_base_semantic_realm"),
															   new__symbol(cause, "funk_name"),                              new__symbol(cause, "semantic_knowledge_base-add_semantic_frame"),
															   new__symbol(cause, "semantic_frame"),                         semantic_frame,
															   new__symbol(cause, "semantic_knowledge_base-semantic_realm"), semantic_realm))));
    }
  }
  // add the semantic frame to this knowledge base
  {
    f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    raw__set__add(cause, semantic_frame_set, semantic_frame);
  }
  // call trace callbacks
  if (raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this) != nil) {
    raw__semantic_knowledge_base__initialize_tracing(cause, this);
    f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "add_semantic_frame"), semantic_frame);
    raw__event_stream__add(cause, trace_event_stream, semantic_knowledge_base_event);
    {
      f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
      f2ptr add_semantic_frame_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame"), nil);
      {
	f2ptr iter = add_semantic_frame_callbacks;
	while (iter != nil) {
	  f2ptr add_semantic_frame_callback = f2__cons__car(cause, iter);
	  {
	    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_callback, f2list2__new(cause, this, semantic_frame));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  {
    semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			      f2ptr result = raw__semantic_knowledge_base__know_of_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value);
			      if (raw__larva__is_type(cause, result)) {
				return result;
			      }
			      );
  }
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


f2ptr raw__semantic_knowledge_base__remove_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  if (! raw__set__contains(cause, semantic_frame_set, semantic_frame)) {
    return f2larva__new(cause, 8923, f2__bug__new(cause, f2integer__new(cause, 8923), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"),       new__symbol(cause, "tried_to_remove_semantic_frame_that_does_not_exist_in_knowledge_base"),
															 new__symbol(cause, "funk_name"),      new__symbol(cause, "semantic_knowledge_base-remove_semantic_frame"),
															 new__symbol(cause, "semantic_frame"), semantic_frame,
															 new__symbol(cause, "this"),           this))));
  }
  // tell the semantic frame that it does not belong to this semantic_knowledge_base anymore (so we can do not continue to receive change events)
  raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(cause, semantic_frame, this);
  // remove the semantic frame from this knowledge base
  raw__set__remove(cause, semantic_frame_set, semantic_frame);
  // call trace callbacks
  if (raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this) != nil) {
    raw__semantic_knowledge_base__initialize_tracing(cause, this);
    f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "remove_semantic_frame"), semantic_frame);
    raw__event_stream__add(cause, trace_event_stream, semantic_knowledge_base_event);
    {
      f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
      f2ptr remove_semantic_frame_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "remove_semantic_frame"), nil);
      {
	f2ptr iter = remove_semantic_frame_callbacks;
	while (iter != nil) {
	  f2ptr remove_semantic_frame_callback = f2__cons__car(cause, iter);
	  {
	    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), remove_semantic_frame_callback, f2list2__new(cause, this, semantic_frame));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  {
    semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			      f2ptr result = raw__semantic_knowledge_base__know_of_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value);
			      if (raw__larva__is_type(cause, result)) {
				return result;
			      }
			      );
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__remove_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__remove_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__remove_semantic_frame, this, semantic_frame, 0, "Removes a semantic_frame from this semantic_knowledge_base.");


boolean_t raw__semantic_knowledge_base__contains_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  return raw__set__contains(cause, semantic_frame_set, semantic_frame);
}

f2ptr f2__semantic_knowledge_base__contains_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__contains_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__contains_semantic_frame, this, semantic_frame, 0, "Returns true if this semantic_knowledge_base contains the given semantic_frame.");


void raw__semantic_knowledge_base__remove_all(f2ptr cause, f2ptr this) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  f2ptr semantic_frames    = nil;
  set__iteration(cause, semantic_frame_set, semantic_frame,
		 semantic_frames = f2cons__new(cause, semantic_frame, semantic_frames));
  {
    f2ptr iter = semantic_frames;
    while (iter != nil) {
      f2ptr semantic_frame = f2__cons__car(cause, iter);
      raw__semantic_knowledge_base__remove_semantic_frame(cause, this, semantic_frame);
      iter = f2__cons__cdr(cause, iter);
    }
  }
}

f2ptr f2__semantic_knowledge_base__remove_all(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_knowledge_base__remove_all(cause, this);
  return nil;
}
export_cefunk1(semantic_knowledge_base__remove_all, this, 0, "Removes all semantic_frames from this knowledge_base.");


f2ptr raw__semantic_knowledge_base__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base__semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, semantic_knowledge_base);
  set__iteration(cause, semantic_knowledge_base__semantic_frame_set, semantic_frame,
		 raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
		 );
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base__is_type(cause, semantic_knowledge_base))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__add_semantic_knowledge_base(cause, this, semantic_knowledge_base);
}
export_cefunk2(semantic_knowledge_base__add_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Adds the semantic frames from semantic_knowledge_base to this semantic_knowledge_base.");


void raw__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  f2ptr trace_callback_funks_frame = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr trace_callback_funks       = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, trace_callback_name, nil);
  f2__frame__add_var_value(cause, trace_callback_funks_frame, trace_callback_name, f2cons__new(cause, trace_callback_funk, trace_callback_funks));
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__funkable__is_type(cause, trace_callback_funk))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, trace_callback_name, trace_callback_funk);
  return nil;
}
export_cefunk3(semantic_knowledge_base__add_trace_callback_funk, this, trace_callback_name, trace_callback_funk, 0, "Adds the trace_callback_funk to the trace_callback_funks_frame under the appropriate trace_callback_name.");


f2ptr raw__semantic_knowledge_base__add_trace_event(f2ptr cause, f2ptr this, f2ptr event) {
  raw__semantic_knowledge_base__initialize_tracing(cause, this);
  f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
  raw__event_stream__add(cause, trace_event_stream, event);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_event(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__event_stream_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_knowledge_base__add_trace_event(cause, this, event);
  return nil;
}
export_cefunk2(semantic_knowledge_base__add_trace_event, this, event, 0, "Adds an event to this semantic_knowledge_base's trace event stream.");


f2ptr raw__semantic_knowledge_base__know_of_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame         = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr add_semantic_frame_value_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame_value"), nil);
  {
    f2ptr iter = add_semantic_frame_value_callbacks;
    while (iter != nil) {
      f2ptr add_semantic_frame_value_callback = f2__cons__car(cause, iter);
      {
	f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_value_callback, f2list5__new(cause, this, semantic_frame, key_type, key, value));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_of_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_knowledge_base__know_of_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value);
  return nil;
}
export_cefunk5(semantic_knowledge_base__know_of_semantic_frame_value_addition, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is added to the frame.");


f2ptr raw__semantic_knowledge_base__know_of_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame            = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr remove_semantic_frame_value_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "remove_semantic_frame_value"), nil);
  {
    f2ptr iter = remove_semantic_frame_value_callbacks;
    while (iter != nil) {
      f2ptr remove_semantic_frame_value_callback = f2__cons__car(cause, iter);
      {
	f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), remove_semantic_frame_value_callback, f2list5__new(cause, this, semantic_frame, key_type, key, value));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_of_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, semantic_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__semantic_knowledge_base__know_of_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value);
  return nil;
}
export_cefunk5(semantic_knowledge_base__know_of_semantic_frame_value_removal, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is removed from the frame.");


boolean_t raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size) {
  s64 this_size = 0;
  {
    f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    set__iteration(cause, semantic_frame_set, semantic_frame,
		   s64 semantic_frame__exact_size = 0;
		   if (raw__semantic_frame__recursively_add_to_set(cause, semantic_frame, set, maximum_size - this_size, &semantic_frame__exact_size)) {
		     this_size += semantic_frame__exact_size;
		     if (this_size > maximum_size) {
		       return boolean__false;
		     }
		   } else {
		     return boolean__false;
		   }
		   );
  }
  *exact_size = this_size;
  return boolean__true;
}

f2ptr f2__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__set__is_type(cause, set)) ||
      (! raw__integer__is_type(cause, maximum_size)) ||
      ((exact_size_place != nil) && (! raw__place__is_type(cause, exact_size_place)))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(cause, this, set, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 24511, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk4(semantic_knowledge_base__recursively_add_semantic_frames_to_set, this, set, maximum_size, exact_size_place, 0, "Recursively adds all semantic_frames referenced from the semantic_frames within this knowledge base.");


boolean_t raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64 *exact_size) {
  f2ptr semantic_frame_set = f2__set__new(cause);
  if (! raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(cause, this, semantic_frame_set, maximum_size, exact_size)) {
    return boolean__false;
  }
  set__iteration(cause, semantic_frame_set, semantic_frame,
		 raw__semantic_frame__add_to_graph_with_node_ptypehash(cause, semantic_frame, graph, node_ptypehash));
  return boolean__true;
}

f2ptr f2__semantic_knowledge_base__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, graph)) ||
      (! raw__ptypehash__is_type(cause, node_ptypehash)) ||
      (! raw__integer__is_type(cause, maximum_size)) ||
      ((exact_size_place != nil) && (raw__place__is_type(cause, exact_size_place)))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 23521, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk5(semantic_knowledge_base__add_to_graph_with_node_ptypehash, this, graph, node_ptypehash, maximum_size, exact_size_place, 0, "Add all semantic frames from this knowledge base as well as all semantic frames referenced from those frames.");


f2ptr raw__semantic_knowledge_base__as__digraph_dot_code(f2ptr cause, f2ptr this) {
  f2ptr code;
  {
    f2ptr node_code_ptypehash = f2__ptypehash__new(cause);
    f2ptr edge_code_ptypehash = f2__ptypehash__new(cause);
    {
      f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
      set__iteration(cause, semantic_frame_set, semantic_frame,
		     if (! raw__ptypehash__contains(cause, node_code_ptypehash, semantic_frame)) {
		       if (! raw__relationship_meta_semantic_object__is_type(cause, semantic_frame)) {
			 f2ptr color = f2__graphviz__exp__as__color(cause, semantic_frame);
			 if (raw__larva__is_type(cause, color)) {
			   return color;
			 }
			 if (color == nil) {
			   color = new__string(cause, "#7f7fff");
			 }
			 f2ptr semantic_frame_name = f2__graphviz__exp__as__name(cause, semantic_frame);
			 if (raw__larva__is_type(cause, semantic_frame_name)) {
			   return semantic_frame_name;
			 }
			 f2ptr semantic_frame_label = f2__graphviz__exp__as__label(cause, semantic_frame);
			 if (raw__larva__is_type(cause, semantic_frame_label)) {
			   return semantic_frame_label;
			 }
			 f2ptr node_code = f2__graphviz__node(cause, semantic_frame_name, semantic_frame_label, color);
			 if (raw__larva__is_type(cause, node_code)) {
			   return node_code;
			 }
			 raw__ptypehash__add(cause, node_code_ptypehash, semantic_frame, node_code);
		       }
		     }
		     {
		       f2ptr semantic_realm = raw__semantic_frame__semantic_realm(cause, semantic_frame);
		       semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
						 if (! raw__ptypehash__contains(cause, node_code_ptypehash, value)) {
						   if (! raw__relationship_meta_semantic_object__is_type(cause, value)) {
						     f2ptr value_color = f2__graphviz__exp__as__color(cause, value);
						     if (raw__larva__is_type(cause, value_color)) {
						       return value_color;
						     }
						     if (value_color == nil) {
						       value_color = new__string(cause, "#3f3fff");
						     }
						     f2ptr value_name = f2__graphviz__exp__as__name(cause, value);
						     if (raw__larva__is_type(cause, value_name)) {
						       return value_name;
						     }
						     f2ptr value_label = f2__graphviz__exp__as__label(cause, value);
						     if (raw__larva__is_type(cause, value_label)) {
						       return value_label;
						     }
						     f2ptr value_node_code = f2__graphviz__node(cause, value_name, value_label, value_color);
						     if (raw__larva__is_type(cause, value_node_code)) {
						       return value_node_code;
						     }
						     raw__ptypehash__add(cause, node_code_ptypehash, value, value_node_code);
						   }
						 }
						 {
						   f2ptr relationship = raw__semantic_realm__lookup_or_create_meta_relationship(cause, semantic_realm, semantic_frame, key_type, key, value);
						   if (raw__larva__is_type(cause, relationship)) {
						     return relationship;
						   }
						   if (! raw__ptypehash__contains(cause, edge_code_ptypehash, relationship)) {
						     f2ptr edge_code = f2__relationship_meta_semantic_object__as__graphviz_edge_code(cause, relationship);
						     if (raw__larva__is_type(cause, edge_code)) {
						       return edge_code;
						     }
						     raw__ptypehash__add(cause, edge_code_ptypehash, relationship, edge_code);
						   }
						 }
						 );
		     }
		     );
    }
    {
      f2ptr nodes_code;
      {
	f2ptr node_codes = nil;
	ptypehash__value__iteration(cause, node_code_ptypehash, node_code,
				    node_codes = f2cons__new(cause, node_code, node_codes));
	nodes_code = f2__stringlist__intersperse(cause, node_codes, new__string(cause, "\n"));
      }
      f2ptr edges_code;
      {
	f2ptr edge_codes = nil;
	ptypehash__value__iteration(cause, edge_code_ptypehash, edge_code,
				    edge_codes = f2cons__new(cause, edge_code, edge_codes));
	edges_code = f2__stringlist__intersperse(cause, edge_codes, new__string(cause, "\n"));
      }
      code = f2__stringlist__intersperse(cause, f2list2__new(cause, nodes_code, edges_code), new__string(cause, "\n"));
    }
  }
  return code;
}

f2ptr f2__semantic_knowledge_base__as__digraph_dot_code(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__as__digraph_dot_code(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__digraph_dot_code, this, 0, "Compile this semantic_knowledge base as digraph dot code (needs a digraph dot wrapper to be fully compiled).");


f2ptr raw__semantic_knowledge_base__new__event_stream_iterator(f2ptr cause, f2ptr this) {
  raw__semantic_knowledge_base__initialize_tracing(cause, this);
  f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
  return raw__event_stream__new__iterator(cause, trace_event_stream);
}

f2ptr f2__semantic_knowledge_base__new__event_stream_iterator(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__new__event_stream_iterator(cause, this);
}
export_cefunk1(semantic_knowledge_base__new__event_stream_iterator, this, 0, "Returns a new event_stream_iterator for this semantic_knowledge_base's trace_event_stream.");


f2ptr raw__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  return raw__set__elements(cause, semantic_frame_set);
}

f2ptr f2__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frames(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_frames, this, 0, "Returns a new conslist of semantic_frames in this semantic_knowledge_base.");


// semantic_knowledge_base lick funks

f2ptr raw__semantic_knowledge_base__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  {
    f2ptr name   = raw__semantic_knowledge_base__name(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, name, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr semantic_realm   = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, semantic_realm, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr semantic_frame_set   = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, semantic_frame_set, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_event_stream   = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_event_stream, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_add_semantic_frame   = raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_add_semantic_frame, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_remove_semantic_frame   = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_remove_semantic_frame, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(semantic_knowledge_base__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Licks this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk                       = raw__chunk__new(cause, 8 * 6);
  f2ptr name                        = raw__semantic_knowledge_base__name(                       cause, this);
  f2ptr semantic_realm              = raw__semantic_knowledge_base__semantic_realm(             cause, this);
  f2ptr semantic_frame_set          = raw__semantic_knowledge_base__semantic_frame_set(         cause, this);
  f2ptr trace_event_stream          = raw__semantic_knowledge_base__trace_event_stream(         cause, this);
  f2ptr trace_add_semantic_frame    = raw__semantic_knowledge_base__trace_add_semantic_frame(   cause, this);
  f2ptr trace_remove_semantic_frame = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
  s64 chunk_index = 0;
  {
    f2ptr data          = name;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "name"),     name,
															     new__symbol(cause, "this"),     this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = semantic_realm;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),       new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "semantic_realm"), semantic_realm,
															     new__symbol(cause, "this"),           this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = semantic_frame_set;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),           new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "semantic_frame_set"), semantic_frame_set,
															     new__symbol(cause, "this"),               this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_event_stream;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),           new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_event_stream"), trace_event_stream,
															     new__symbol(cause, "this"),               this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_add_semantic_frame;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),                 new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_add_semantic_frame"), trace_add_semantic_frame,
															     new__symbol(cause, "this"),                     this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_remove_semantic_frame;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),                    new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_remove_semantic_frame"), trace_remove_semantic_frame,
															     new__symbol(cause, "this"),                        this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  if (chunk_index != (8 * 6)) {
    return f2larva__new(cause, 23551, nil);
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__semantic_knowledge_base__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(semantic_knowledge_base__lick_to_chunk, this, note_object_hash, 0, "Licks this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != (8 * 6)) {
    return f2larva__new(cause, 32555, nil);
  }
  f2ptr name__lick_note                        = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  f2ptr semantic_realm__lick_note              = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 8));
  f2ptr semantic_frame_set__lick_note          = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 16));
  f2ptr trace_event_stream__lick_note          = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 24));
  f2ptr trace_add_semantic_frame__lick_note    = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 32));
  f2ptr trace_remove_semantic_frame__lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 40));
  f2ptr semantic_knowledge_base = raw__semantic_knowledge_base__new(cause,
								    name__lick_note,
								    semantic_realm__lick_note,
								    semantic_frame_set__lick_note,
								    trace_event_stream__lick_note,
								    trace_add_semantic_frame__lick_note,
								    trace_remove_semantic_frame__lick_note);
  return semantic_knowledge_base;
}

f2ptr f2__semantic_knowledge_base__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(semantic_knowledge_base__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this semantic_knowledge_base lick_chunk with notes.");


f2ptr raw__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__name(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__name__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__semantic_realm__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__semantic_frame_set__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_event_stream__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_add_semantic_frame__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_remove_semantic_frame__set(cause, this, data__object);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this semantic_knowledge_base with notes.");



f2ptr f2__semantic_knowledge_base_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_knowledge_base_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "as-graph"),                                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__graph")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_semantic_frame"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_semantic_frame"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__remove_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "contains_semantic_frame"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__contains_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_all"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__remove_all")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_semantic_knowledge_base"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_trace_callback_funk"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_trace_callback_funk")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_trace_event"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_trace_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "know_of_semantic_frame_value_addition"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__know_of_semantic_frame_value_addition")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "know_of_semantic_frame_value_removal"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__know_of_semantic_frame_value_removal")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "recursively_add_semantic_frames_to_set"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__recursively_add_semantic_frames_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_to_graph_with_node_ptypehash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "as-digraph_dot_code"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__digraph_dot_code")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "new-event_stream_iterator"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__new__event_stream_iterator")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "semantic_frames"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "as-timeline"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"),          new__symbol(cause, "semantic_knowledge_base__as__timeline")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__gather_lick_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__lick_to_chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__lick_chunk__unlick_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects")));}
  return this;
}


// **

f2ptr f2__semantic_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__ping, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "semantic_relationship_key"),     f2__semantic_relationship_key_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_realm"),                f2__semantic_realm_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event"),          f2__semantic_frame_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),                f2__semantic_frame_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event"), f2__semantic_knowledge_base_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"),       f2__semantic_knowledge_base_type__new_aux(cause));
  status("semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__destroy, 0, "");


