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

#include "semantic_relationship_key.h"


// semantic_relationship_key

def_ceframe4(semantic_relationship_key, semantic_relationship_key,
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
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value-loop_free"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_relationship_key"), new__symbol(cause, "semantic_relationship_key__equals_hash_value__loop_free")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals_hash_value"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_relationship_key"), new__symbol(cause, "semantic_relationship_key__equals_hash_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "equals"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_relationship_key"), new__symbol(cause, "semantic_relationship_key__equals")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_relationship_key"), new__symbol(cause, "semantic_relationship_key__terminal_print_with_frame")));}
  return this;
}



// **

f2ptr f2__semantic_relationship_key__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_relationship_key__core_extension__ping, 0, "");

f2ptr f2__semantic_relationship_key__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_relationship_key, semantic_realm);
  status("semantic_relationship_key initialized.");
  return nil;
}
export_cefunk0(semantic_relationship_key__core_extension__initialize, 0, "");

f2ptr f2__semantic_relationship_key__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_relationship_key"), f2__semantic_relationship_key_type__new_aux(cause));
  status("semantic_relationship_key defined types.");
  return nil;
}
export_cefunk0(semantic_relationship_key__core_extension__define_types, 0, "");

f2ptr f2__semantic_relationship_key__core_extension__destroy(f2ptr cause) {
  status("semantic_relationship_key destroyed.");
  return nil;
}
export_cefunk0(semantic_relationship_key__core_extension__destroy, 0, "");


