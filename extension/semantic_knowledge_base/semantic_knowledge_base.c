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
#include "semantic_knowledge_base.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"


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
	return f2larva__new(cause, 1, nil);
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

f2ptr raw__semantic_relationship_key__new(f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  return f2__frame__new(cause, f2list10__new(cause,
					     new__symbol(cause, "type"),     new__symbol(cause, "semantic_relationship_key"),
					     new__symbol(cause, "source"),   source,
					     new__symbol(cause, "key_type"), key_type,
					     new__symbol(cause, "key"),      key,
					     new__symbol(cause, "target"),   target));
}

f2ptr f2__semantic_relationship_key__new(f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  return raw__semantic_relationship_key__new(cause, source, key_type, key, target);
}
export_cefunk4(semantic_relationship_key__new, source, key_type, key, target, 0, "Returns a new semantic_relationship_key object.");


boolean_t raw__semantic_relationship_key__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_relationship_key");
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

f2ptr f2__semantic_relationship_key__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_relationship_key__is_type(cause, thing));
}
export_cefunk1(semantic_relationship_key__is_type, thing, 0, "Returns whether or not thing is of type semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_relationship_key__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__type(cause, this);
}
export_cefunk1(semantic_relationship_key__type, thing, 0, "Returns the specific type of object that this semantic_relationship_key is.");


f2ptr raw__semantic_relationship_key__source(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "source"), nil);
}

f2ptr f2__semantic_relationship_key__source(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__source(cause, this);
}
export_cefunk1(semantic_relationship_key__source, thing, 0, "Returns the source of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__source__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "source"), value);
}

f2ptr f2__semantic_relationship_key__source__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__source__set(cause, this, value);
}
export_cefunk2(semantic_relationship_key__source__set, thing, value, 0, "Sets the source of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__key_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key_type"), nil);
}

f2ptr f2__semantic_relationship_key__key_type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__key_type(cause, this);
}
export_cefunk1(semantic_relationship_key__key_type, thing, 0, "Returns the key_type of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key_type"), value);
}

f2ptr f2__semantic_relationship_key__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__key_type__set(cause, this, value);
}
export_cefunk2(semantic_relationship_key__key_type__set, thing, value, 0, "Sets the key_type of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__key(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key"), nil);
}

f2ptr f2__semantic_relationship_key__key(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__key(cause, this);
}
export_cefunk1(semantic_relationship_key__key, thing, 0, "Returns the key of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key"), value);
}

f2ptr f2__semantic_relationship_key__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__key__set(cause, this, value);
}
export_cefunk2(semantic_relationship_key__key__set, thing, value, 0, "Sets the key of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__target(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "target"), nil);
}

f2ptr f2__semantic_relationship_key__target(f2ptr cause, f2ptr this) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__target(cause, this);
}
export_cefunk1(semantic_relationship_key__target, thing, 0, "Returns the target of the semantic_relationship_key.");


f2ptr raw__semantic_relationship_key__target__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "target"), value);
}

f2ptr f2__semantic_relationship_key__target__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_relationship_key__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_relationship_key__target__set(cause, this, value);
}
export_cefunk2(semantic_relationship_key__target__set, thing, value, 0, "Sets the target of the semantic_relationship_key.");


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


f2ptr f2__semantic_relationship_key_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "source"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__source")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "source"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__source__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key_type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "target"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__target")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "target"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__target__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value-loop_free"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals_hash_value__loop_free")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals_hash_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__equals")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_relationship_key__terminal_print_with_frame")));}
  return this;
}


// semantic_realm

f2ptr raw__semantic_realm__new(f2ptr cause) {
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),                          new__symbol(cause, "semantic_realm"),
					    new__symbol(cause, "semantic_hash"),                 f2__hash(cause),
					    new__symbol(cause, "meta_relationship_hash"),        f2__hash(cause),
					    new__symbol(cause, "semantic_knowledge_base_frame"), f2__frame__new(cause, nil)));
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


f2ptr raw__semantic_realm__meta_relationship_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "meta_relationship_hash"), nil);
}

f2ptr f2__semantic_realm__meta_relationship_hash(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__meta_relationship_hash(cause, this);
}
export_cefunk1(semantic_realm__meta_relationship_hash, thing, 0, "Returns the meta_relationship_hash of the semantic_realm.");


f2ptr raw__semantic_realm__meta_relationship_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "meta_relationship_hash"), value);
}

f2ptr f2__semantic_realm__meta_relationship_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__meta_relationship_hash__set(cause, this, value);
}
export_cefunk2(semantic_realm__meta_relationship_hash__set, thing, value, 0, "Sets the meta_relationship_hash of the semantic_realm.");


f2ptr raw__semantic_realm__semantic_knowledge_base_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_knowledge_base_frame"), nil);
}

f2ptr f2__semantic_realm__semantic_knowledge_base_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__semantic_knowledge_base_frame(cause, this);
}
export_cefunk1(semantic_realm__semantic_knowledge_base_frame, thing, 0, "Returns the semantic_knowledge_base_frame of the semantic_realm.");


f2ptr raw__semantic_realm__semantic_knowledge_base_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_knowledge_base_frame"), value);
}

f2ptr f2__semantic_realm__semantic_knowledge_base_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_realm__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_realm__semantic_knowledge_base_frame__set(cause, this, value);
}
export_cefunk2(semantic_realm__semantic_knowledge_base_frame__set, thing, value, 0, "Sets the semantic_knowledge_base_frame of the semantic_realm.");


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


f2ptr raw__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr relationship_equals_key         = raw__semantic_relationship_key__new(cause, semantic_frame, key_type, key, value);
  f2ptr meta_relationship_hash          = raw__semantic_realm__meta_relationship_hash(cause, this);
  f2ptr previously_created_relationship = f2__hash__lookup(cause, meta_relationship_hash, relationship_equals_key);
  if (previously_created_relationship != nil) {
    return previously_created_relationship;
  }
  f2ptr relationship = f2__relationship_meta_semantic_object__new(cause, this, semantic_frame, key_type, key, value);
  f2__hash__add(cause, meta_relationship_hash, relationship_equals_key, relationship);
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
    return f2larva__new(cause, 65826, f2__bug__new(cause, f2integer__new(cause, 65826), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),                new__symbol(cause, "tried_to_add_semantic_knowledge_base_to_different_semantic_realm"),
															    new__symbol(cause, "funk_name"),               new__symbol(cause, "semantic_realm-add_semantic_knowledge_base"),
															    new__symbol(cause, "this"),                    this,
															    new__symbol(cause, "semantic_knowledge_base"), semantic_knowledge_base))));
  }
  f2ptr semantic_knowledge_base_frame = raw__semantic_realm__semantic_knowledge_base_frame(cause, this);
  if (raw__frame__contains_var_value(cause, semantic_knowledge_base_frame, name)) {
    return f2larva__new(cause, 65827, f2__bug__new(cause, f2integer__new(cause, 65827), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),                new__symbol(cause, "knowledge_base_already_in_realm_with_same_name"),
															    new__symbol(cause, "funk_name"),               new__symbol(cause, "semantic_realm-add_semantic_knowledge_base"),
															    new__symbol(cause, "this"),                    this,
															    new__symbol(cause, "semantic_knowledge_base"), semantic_knowledge_base))));
  }
  f2ptr name = f2__semantic_knowledge_base__name(cause, semantic_knowledge_base);
  f2__frame__add_var_value(cause, semantic_knowledge_base_frame, name, semantic_knowledge_base);
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
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_hash"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_hash"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "meta_relationship_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__meta_relationship_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "meta_relationship_hash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__meta_relationship_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_knowledge_base_frame"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_knowledge_base_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_knowledge_base_frame"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__semantic_knowledge_base_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_object_key"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_object_key"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__add_object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "object_key"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__object_key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_or_create_meta_relationship"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__lookup_or_create_meta_relationship")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_realm__terminal_print_with_frame")));}
  return this;
}


// semantic_frame_event

f2ptr raw__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr key_type, f2ptr key, f2ptr value) {
  return f2__frame__new(cause, f2list12__new(cause,
					     new__symbol(cause, "type"),       new__symbol(cause, "semantic_frame_event"),
					     new__symbol(cause, "time"),       time,
					     new__symbol(cause, "event_type"), event_type,
					     new__symbol(cause, "key_type"),   key_type,
					     new__symbol(cause, "key"),        key,
					     new__symbol(cause, "value"),      value));
}

f2ptr f2__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr key_type, f2ptr key, f2ptr value) {
  return raw__semantic_frame_event__new(cause, time, event_type, key_type, key, value);
}
export_cefunk5(semantic_frame_event__new, time, event_type, key_type, key, value, 0, "Returns a new semantic_frame_event object.");


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


f2ptr raw__semantic_frame_event__time(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "time"), nil);
}

f2ptr f2__semantic_frame_event__time(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__time(cause, this);
}
export_cefunk1(semantic_frame_event__time, thing, 0, "Returns the time of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "time"), value);
}

f2ptr f2__semantic_frame_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__time__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__time__set, thing, value, 0, "Sets the time of the semantic_frame_event.");


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


f2ptr raw__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_frame_event"),
						new__symbol(cause, "time"),              raw__semantic_frame_event__time(cause, this),
						new__symbol(cause, "event_type"),        raw__semantic_frame_event__event_type(cause, this),
						new__symbol(cause, "key_type"),          raw__semantic_frame_event__key_type(cause, this),
						new__symbol(cause, "key"),               raw__semantic_frame_event__key(cause, this),
						new__symbol(cause, "value"),             raw__semantic_frame_event__value(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_frame_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_frame_event__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_frame_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__time")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__event_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__event_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key_type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "value"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "value"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__value__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event__terminal_print_with_frame")));}
  return this;
}




// semantic_frame_event_redblacktree

f2ptr raw__semantic_frame_event_redblacktree__new(f2ptr cause) {
  f2ptr value_event_cfunk   = f2cfunk__new(cause, nil, 
					   f2list1__new(cause, new__symbol(cause, "this")),
					   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__semantic_frame_event__time_value)), global_environment(), nil, nil);
  f2ptr compare_event_cfunk = f2cfunk__new(cause, nil, 
					   f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
					   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__semantic_frame_event__compare_value)), global_environment(), nil, nil);
  f2ptr redblacktree        = f2__redblacktree__new(cause, value_event_cfunk, compare_event_cfunk);
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),         new__symbol(cause, "semantic_frame_event_redblacktree"),
					    new__symbol(cause, "redblacktree"), redblacktree));
}

f2ptr f2__semantic_frame_event_redblacktree__new(f2ptr cause) {
  return raw__semantic_frame_event_redblacktree__new(cause);
}
export_cefunk0(semantic_frame_event_redblacktree__new, 0, "Returns a new semantic_frame_event_redblacktree object.");


boolean_t raw__semantic_frame_event_redblacktree__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_frame_event_redblacktree");
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

f2ptr f2__semantic_frame_event_redblacktree__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_frame_event_redblacktree__is_type(cause, thing));
}
export_cefunk1(semantic_frame_event_redblacktree__is_type, thing, 0, "Returns whether or not thing is of type semantic_frame_event_redblacktree.");


f2ptr raw__semantic_frame_event_redblacktree__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_frame_event_redblacktree__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__type(cause, this);
}
export_cefunk1(semantic_frame_event_redblacktree__type, thing, 0, "Returns the specific type of object that this semantic_frame_event_redblacktree is.");


f2ptr raw__semantic_frame_event_redblacktree__redblacktree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "redblacktree"), nil);
}

f2ptr f2__semantic_frame_event_redblacktree__redblacktree(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__redblacktree(cause, this);
}
export_cefunk1(semantic_frame_event_redblacktree__redblacktree, thing, 0, "Returns the redblacktree of the semantic_frame_event_redblacktree.");


f2ptr raw__semantic_frame_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "redblacktree"), value);
}

f2ptr f2__semantic_frame_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__redblacktree__set(cause, this, value);
}
export_cefunk2(semantic_frame_event_redblacktree__redblacktree__set, thing, value, 0, "Sets the redblacktree of the semantic_frame_event_redblacktree.");


f2ptr raw__semantic_frame_event_redblacktree__events(f2ptr cause, f2ptr this) {
  f2ptr redblacktree = raw__semantic_frame_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__leaves(cause, redblacktree);
}

f2ptr f2__semantic_frame_event_redblacktree__events(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__events(cause, this);
}
export_cefunk1(semantic_frame_event_redblacktree__events, this, 0, "Returns the events within this semantic_frame_event_redblacktree, ordered in time.");


f2ptr raw__semantic_frame_event_redblacktree__add(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr redblacktree = raw__semantic_frame_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__insert(cause, redblacktree, event);
}

f2ptr f2__semantic_frame_event_redblacktree__add(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__semantic_frame_event_redblacktree__is_type(cause, this)) ||
      (! raw__semantic_frame_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__add(cause, this, event);
}
export_cefunk2(semantic_frame_event_redblacktree__add, this, event, 0, "Adds a semantic_frame_event to this semantic_frame_event_redblacktree.");


f2ptr raw__semantic_frame_event_redblacktree__remove(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr redblacktree = raw__semantic_frame_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__remove(cause, redblacktree, event);
}

f2ptr f2__semantic_frame_event_redblacktree__remove(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__semantic_frame_event_redblacktree__is_type(cause, this)) ||
      (! raw__semantic_frame_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__remove(cause, this, event);
}
export_cefunk2(semantic_frame_event_redblacktree__remove, this, event, 0, "Removes a semantic_frame_event from this semantic_frame_event_redblacktree.");


f2ptr raw__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_frame_event_redblacktree"),
					       new__symbol(cause, "events"),            f2__semantic_frame_event_redblacktree__events(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_frame_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame_event_redblacktree__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_frame_event_redblacktree__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_frame_event_redblacktree_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "redblacktree"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "redblacktree"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "events"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__events")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame_event_redblacktree__terminal_print_with_frame")));}
  return this;
}




// semantic_frame

f2ptr raw__semantic_frame_event__time_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter);
  return raw__semantic_frame_event__time(cause, this);
}

f2ptr raw__semantic_frame_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this__time = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr that__time = f2__cons__car(cause, args_iter);
  {
    f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this__time);
    f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that__time);
    s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
    s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
    return (this__nanoseconds_since_1970__i < that__nanoseconds_since_1970__i);
  }
}


f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr trace_event_redblacktree = nil;
  f2ptr trace_add    = nil;
  f2ptr trace_remove = nil;
  if (cause != nil) {
    trace_add    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_add"));
    trace_remove = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_remove"));
  }
  return f2__frame__new(cause, f2list14__new(cause,
					     new__symbol(cause, "type"),                        new__symbol(cause, "semantic_frame"),
					     new__symbol(cause, "semantic_realm"),              semantic_realm,
					     new__symbol(cause, "trace_add"),                   trace_add,
					     new__symbol(cause, "trace_remove"),                trace_remove,
					     new__symbol(cause, "trace_event_redblacktree"),    trace_event_redblacktree,
					     new__symbol(cause, "semantic_knowledge_base_set"), f2__set__new(cause),
					     new__symbol(cause, "frame"),                       f2__frame__new(cause, nil)));
}


f2ptr f2__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__new(cause, semantic_realm);
}
export_cefunk1(semantic_frame__new, semantic_realm, 0, "Returns a new semantic_frame object.");


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


f2ptr raw__semantic_frame__semantic_realm(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_realm"), nil);
}

f2ptr f2__semantic_frame__semantic_realm(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_realm(cause, this);
}
export_cefunk1(semantic_frame__semantic_realm, thing, 0, "Returns the semantic_realm of the semantic_frame.");


f2ptr raw__semantic_frame__semantic_realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_realm"), value);
}

f2ptr f2__semantic_frame__semantic_realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_realm__set(cause, this, value);
}
export_cefunk2(semantic_frame__semantic_realm__set, thing, value, 0, "Sets the semantic_realm of the semantic_frame.");


f2ptr raw__semantic_frame__trace_add(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_add"), nil);
}

f2ptr f2__semantic_frame__trace_add(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_add(cause, this);
}
export_cefunk1(semantic_frame__trace_add, thing, 0, "Returns the trace_add of the semantic_frame.");


f2ptr raw__semantic_frame__trace_add__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_add"), value);
}

f2ptr f2__semantic_frame__trace_add__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_add__set(cause, this, value);
}
export_cefunk2(semantic_frame__trace_add__set, thing, value, 0, "Sets the trace_add of the semantic_frame.");


f2ptr raw__semantic_frame__trace_remove(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_remove"), nil);
}

f2ptr f2__semantic_frame__trace_remove(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_remove(cause, this);
}
export_cefunk1(semantic_frame__trace_remove, thing, 0, "Returns the trace_remove of the semantic_frame.");


f2ptr raw__semantic_frame__trace_remove__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_remove"), value);
}

f2ptr f2__semantic_frame__trace_remove__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_remove__set(cause, this, value);
}
export_cefunk2(semantic_frame__trace_remove__set, thing, value, 0, "Sets the trace_remove of the semantic_frame.");


f2ptr raw__semantic_frame__trace_event_redblacktree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_event_redblacktree"), nil);
}

f2ptr f2__semantic_frame__trace_event_redblacktree(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_event_redblacktree(cause, this);
}
export_cefunk1(semantic_frame__trace_event_redblacktree, thing, 0, "Returns the trace_event_redblacktree of the semantic_frame.");


f2ptr raw__semantic_frame__trace_event_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_event_redblacktree"), value);
}

f2ptr f2__semantic_frame__trace_event_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__trace_event_redblacktree__set(cause, this, value);
}
export_cefunk2(semantic_frame__trace_event_redblacktree__set, thing, value, 0, "Sets the trace_event_redblacktree of the semantic_frame.");


f2ptr raw__semantic_frame__semantic_knowledge_base_set(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_knowledge_base_set"), nil);
}

f2ptr f2__semantic_frame__semantic_knowledge_base_set(f2ptr cause, f2ptr this) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_knowledge_base_set(cause, this);
}
export_cefunk1(semantic_frame__semantic_knowledge_base_set, thing, 0, "Returns the semantic_knowledge_base_set of the semantic_frame.");


f2ptr raw__semantic_frame__semantic_knowledge_base_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_knowledge_base_set"), value);
}

f2ptr f2__semantic_frame__semantic_knowledge_base_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_frame__semantic_knowledge_base_set__set(cause, this, value);
}
export_cefunk2(semantic_frame__semantic_knowledge_base_set__set, thing, value, 0, "Sets the semantic_knowledge_base_set of the semantic_frame.");


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


void raw__semantic_frame__initialize_tracing(f2ptr cause, f2ptr this) {
  if (raw__semantic_frame__trace_event_redblacktree(cause, this) == nil) {
    f2ptr trace_event_redblacktree = f2__semantic_frame_event_redblacktree__new(cause);
    raw__semantic_frame__trace_event_redblacktree__set(cause, this, trace_event_redblacktree);
  }
}


f2ptr raw__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_add(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_redblacktree = raw__semantic_frame__trace_event_redblacktree(cause, this);
    f2ptr semantic_frame_event = raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "add"), key_type, key, value);
    raw__semantic_frame_event_redblacktree__add(cause, trace_event_redblacktree, semantic_frame_event);
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
  if (raw__semantic_frame__trace_remove(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_redblacktree = raw__semantic_frame__trace_event_redblacktree(cause, this);
    f2ptr semantic_frame_event = raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "remove"), key_type, key, value);
    raw__semantic_frame_event_redblacktree__add(cause, trace_event_redblacktree, semantic_frame_event);
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


f2ptr f2__semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_realm"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_realm")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_realm"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_realm__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_add"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_add"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_add__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_remove"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_remove"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_remove__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_event_redblacktree"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_event_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_event_redblacktree"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_event_redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_knowledge_base_set"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_knowledge_base_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_knowledge_base_set"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__semantic_knowledge_base_set__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "frame"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "frame"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_single_value"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup_single_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove_all"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__remove_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "replace_all"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__replace_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_addition_to_semantic_knowledge_base"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__know_of_addition_to_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_to_set"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__recursively_add_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__as__graphviz_label")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__terminal_print_with_frame")));}
  return this;
}




// semantic_knowledge_base_event

f2ptr raw__semantic_knowledge_base_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame) {
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),           new__symbol(cause, "semantic_knowledge_base_event"),
					    new__symbol(cause, "time"),           time,
					    new__symbol(cause, "event_type"),     event_type,
					    new__symbol(cause, "semantic_frame"), semantic_frame));
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


f2ptr raw__semantic_knowledge_base_event__time(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "time"), nil);
}

f2ptr f2__semantic_knowledge_base_event__time(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__time(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__time, thing, 0, "Returns the time of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "time"), value);
}

f2ptr f2__semantic_knowledge_base_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__time__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base_event__time__set, thing, value, 0, "Sets the time of the semantic_knowledge_base_event.");


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


f2ptr raw__semantic_knowledge_base_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_knowledge_base_event"),
					       new__symbol(cause, "time"),              raw__semantic_knowledge_base_event__time(cause, this),
					       new__symbol(cause, "event_type"),        raw__semantic_knowledge_base_event__event_type(cause, this),
					       new__symbol(cause, "semantic_frame"),    raw__semantic_knowledge_base_event__semantic_frame(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_knowledge_base_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_knowledge_base_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_knowledge_base_event__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_knowledge_base_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__time")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__event_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__event_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frame"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frame"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event__terminal_print_with_frame")));}
  return this;
}




// semantic_knowledge_base_event_redblacktree

f2ptr raw__semantic_knowledge_base_event_redblacktree__new(f2ptr cause) {
  f2ptr value_event_cfunk   = f2cfunk__new(cause, nil, 
					   f2list1__new(cause, new__symbol(cause, "this")),
					   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__semantic_knowledge_base_event__time_value)), global_environment(), nil, nil);
  f2ptr compare_event_cfunk = f2cfunk__new(cause, nil, 
					   f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
					   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__semantic_knowledge_base_event__compare_value)), global_environment(), nil, nil);
  f2ptr redblacktree        = f2__redblacktree__new(cause, value_event_cfunk, compare_event_cfunk);
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),         new__symbol(cause, "semantic_knowledge_base_event_redblacktree"),
					    new__symbol(cause, "redblacktree"), redblacktree));
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__new(f2ptr cause) {
  return raw__semantic_knowledge_base_event_redblacktree__new(cause);
}
export_cefunk0(semantic_knowledge_base_event_redblacktree__new, 0, "Returns a new semantic_knowledge_base_event_redblacktree object.");


boolean_t raw__semantic_knowledge_base_event_redblacktree__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_knowledge_base_event_redblacktree");
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

f2ptr f2__semantic_knowledge_base_event_redblacktree__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_knowledge_base_event_redblacktree__is_type(cause, thing));
}
export_cefunk1(semantic_knowledge_base_event_redblacktree__is_type, thing, 0, "Returns whether or not thing is of type semantic_knowledge_base_event_redblacktree.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__type(cause, this);
}
export_cefunk1(semantic_knowledge_base_event_redblacktree__type, thing, 0, "Returns the specific type of object that this semantic_knowledge_base_event_redblacktree is.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__redblacktree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "redblacktree"), nil);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__redblacktree(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__redblacktree(cause, this);
}
export_cefunk1(semantic_knowledge_base_event_redblacktree__redblacktree, thing, 0, "Returns the redblacktree of the semantic_knowledge_base_event_redblacktree.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "redblacktree"), value);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__redblacktree__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base_event_redblacktree__redblacktree__set, thing, value, 0, "Sets the redblacktree of the semantic_knowledge_base_event_redblacktree.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__events(f2ptr cause, f2ptr this) {
  f2ptr redblacktree = raw__semantic_knowledge_base_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__leaves(cause, redblacktree);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__events(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__events(cause, this);
}
export_cefunk1(semantic_knowledge_base_event_redblacktree__events, this, 0, "Returns the events within this semantic_knowledge_base_event_redblacktree, ordered in time.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__add(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr redblacktree = raw__semantic_knowledge_base_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__insert(cause, redblacktree, event);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__add(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__add(cause, this, event);
}
export_cefunk2(semantic_knowledge_base_event_redblacktree__add, this, event, 0, "Adds a semantic_knowledge_base_event to this semantic_knowledge_base_event_redblacktree.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__remove(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr redblacktree = raw__semantic_knowledge_base_event_redblacktree__redblacktree(cause, this);
  return raw__redblacktree__remove(cause, redblacktree, event);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__remove(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) ||
      (! raw__semantic_knowledge_base_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__remove(cause, this, event);
}
export_cefunk2(semantic_knowledge_base_event_redblacktree__remove, this, event, 0, "Removes a semantic_knowledge_base_event from this semantic_knowledge_base_event_redblacktree.");


f2ptr raw__semantic_knowledge_base_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree"),
					       new__symbol(cause, "events"),            f2__semantic_knowledge_base_event_redblacktree__events(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_knowledge_base_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__semantic_knowledge_base_event_redblacktree__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base_event_redblacktree__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_knowledge_base_event_redblacktree__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_knowledge_base_event_redblacktree_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "redblacktree"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "redblacktree"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "events"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__events")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base_event_redblacktree__terminal_print_with_frame")));}
  return this;
}




// semantic_knowledge_base

f2ptr raw__semantic_knowledge_base_event__time_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter);
  return raw__semantic_knowledge_base_event__time(cause, this);
}

f2ptr raw__semantic_knowledge_base_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this__time = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr that__time = f2__cons__car(cause, args_iter);
  {
    f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this__time);
    f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that__time);
    s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
    s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
    return (this__nanoseconds_since_1970__i < that__nanoseconds_since_1970__i);
  }
}


f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr trace_event_redblacktree    = nil;
  f2ptr trace_add_semantic_frame    = nil;
  f2ptr trace_remove_semantic_frame = nil;
  if (cause != nil) {
    trace_add_semantic_frame = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_add_semantic_frame"));
  }
  f2ptr this = f2__frame__new(cause, f2list14__new(cause,
						   new__symbol(cause, "type"),                        new__symbol(cause, "semantic_knowledge_base"),
						   new__symbol(cause, "name"),                        name,
						   new__symbol(cause, "semantic_realm"),              semantic_realm,
						   new__symbol(cause, "semantic_frame_set"),          f2__set__new(cause),
						   new__symbol(cause, "trace_event_redblacktree"),    trace_event_redblacktree,
						   new__symbol(cause, "trace_add_semantic_frame"),    trace_add_semantic_frame,
						   new__symbol(cause, "trace_remove_semantic_frame"), trace_remove_semantic_frame,
						   new__symbol(cause, "trace_callback_funks_frame"),  f2__frame__new(cause, nil)));
  f2__semantic_realm__add_semantic_knowledge_base(cause, semantic_realm, this);
  return this;
}

f2ptr f2__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_knowledge_base__new, name, semantic_realm, 0, "Takes a name nad a semantic_realm and returns a new semantic_knowledge_base object.");


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


f2ptr raw__semantic_knowledge_base__semantic_realm(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_realm"), nil);
}

f2ptr f2__semantic_knowledge_base__semantic_realm(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_realm(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_realm, thing, 0, "Returns the semantic_realm of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__semantic_realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_realm"), value);
}

f2ptr f2__semantic_knowledge_base__semantic_realm__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_realm__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__semantic_realm__set, thing, value, 0, "Sets the semantic_realm of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__semantic_frame_set(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frame_set"), nil);
}

f2ptr f2__semantic_knowledge_base__semantic_frame_set(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frame_set(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_frame_set, thing, 0, "Returns the semantic_frame_set of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__semantic_frame_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame_set"), value);
}

f2ptr f2__semantic_knowledge_base__semantic_frame_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__semantic_frame_set__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__semantic_frame_set__set, thing, value, 0, "Sets the semantic_frame_set of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_event_redblacktree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_event_redblacktree"), nil);
}

f2ptr f2__semantic_knowledge_base__trace_event_redblacktree(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_event_redblacktree(cause, this);
}
export_cefunk1(semantic_knowledge_base__trace_event_redblacktree, thing, 0, "Returns the trace_event_redblacktree of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_event_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_event_redblacktree"), value);
}

f2ptr f2__semantic_knowledge_base__trace_event_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_event_redblacktree__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__trace_event_redblacktree__set, thing, value, 0, "Sets the trace_event_redblacktree of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_add_semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_add_semantic_frame"), nil);
}

f2ptr f2__semantic_knowledge_base__trace_add_semantic_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this);
}
export_cefunk1(semantic_knowledge_base__trace_add_semantic_frame, thing, 0, "Returns the trace_add_semantic_frame of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_add_semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_add_semantic_frame"), value);
}

f2ptr f2__semantic_knowledge_base__trace_add_semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_add_semantic_frame__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__trace_add_semantic_frame__set, thing, value, 0, "Sets the trace_add_semantic_frame of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_remove_semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_remove_semantic_frame"), nil);
}

f2ptr f2__semantic_knowledge_base__trace_remove_semantic_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
}
export_cefunk1(semantic_knowledge_base__trace_remove_semantic_frame, thing, 0, "Returns the trace_remove_semantic_frame of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_remove_semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_remove_semantic_frame"), value);
}

f2ptr f2__semantic_knowledge_base__trace_remove_semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_remove_semantic_frame__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__trace_remove_semantic_frame__set, thing, value, 0, "Sets the trace_remove_semantic_frame of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_callback_funks_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "trace_callback_funks_frame"), nil);
}

f2ptr f2__semantic_knowledge_base__trace_callback_funks_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
}
export_cefunk1(semantic_knowledge_base__trace_callback_funks_frame, thing, 0, "Returns the trace_callback_funks_frame of the semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__trace_callback_funks_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_callback_funks_frame"), value);
}

f2ptr f2__semantic_knowledge_base__trace_callback_funks_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__trace_callback_funks_frame__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base__trace_callback_funks_frame__set, thing, value, 0, "Sets the trace_callback_funks_frame of the semantic_knowledge_base.");


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
  if (raw__semantic_knowledge_base__trace_event_redblacktree(cause, this) == nil) {
    f2ptr trace_event_redblacktree = f2__semantic_knowledge_base_event_redblacktree__new(cause);
    raw__semantic_knowledge_base__trace_event_redblacktree__set(cause, this, trace_event_redblacktree);
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
    f2ptr trace_event_redblacktree = raw__semantic_knowledge_base__trace_event_redblacktree(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "add_semantic_frame"), semantic_frame);
    raw__semantic_knowledge_base_event_redblacktree__add(cause, trace_event_redblacktree, semantic_knowledge_base_event);
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
  // tell the semantic frame that it belongs to this semantic_knowledge_base (so we can receive change events)
  raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(cause, semantic_frame, this);
  // remove the semantic frame from this knowledge base
  raw__set__remove(cause, semantic_frame_set, semantic_frame);
  // call trace callbacks
  if (raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this) != nil) {
    raw__semantic_knowledge_base__initialize_tracing(cause, this);
    f2ptr trace_event_redblacktree = raw__semantic_knowledge_base__trace_event_redblacktree(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "remove_semantic_frame"), semantic_frame);
    raw__semantic_knowledge_base_event_redblacktree__add(cause, trace_event_redblacktree, semantic_knowledge_base_event);
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
  return raw__semantic_knowledge_base__remove_all(cause, this);
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


f2ptr raw__semantic_knowledge_base__know_of_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
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
  f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
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


f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_realm"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_realm")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_realm"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_realm__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frame_set"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frame_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frame_set"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frame_set__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_event_redblacktree"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_event_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_event_redblacktree"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_event_redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_add_semantic_frame"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_add_semantic_frame"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_add_semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_remove_semantic_frame"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_remove_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_remove_semantic_frame"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_remove_semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_callback_funks_frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_callback_funks_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_callback_funks_frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_callback_funks_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graph"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__graph")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_semantic_frame"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove_semantic_frame"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__remove_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove_all"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__remove_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_semantic_knowledge_base"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_trace_callback_funk"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_trace_callback_funk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_semantic_frame_value_addition"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__know_of_semantic_frame_value_addition")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_semantic_frame_value_removal"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__know_of_semantic_frame_value_removal")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_semantic_frames_to_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__recursively_add_semantic_frames_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-digraph_dot_code"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__digraph_dot_code")));}
  return this;
}


// **

f2ptr f2__semantic_knowledge_base__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_ping, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_relationship_key"),                  f2__semantic_relationship_key_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_realm"),                             f2__semantic_realm_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event"),                       f2__semantic_frame_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event_redblacktree"),          f2__semantic_frame_event_redblacktree_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),                             f2__semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event"),              f2__semantic_knowledge_base_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event_redblacktree"), f2__semantic_knowledge_base_event_redblacktree_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"),                    f2__semantic_knowledge_base_type__new(cause));
  status("semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  status("semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_destroy, 0, "");


