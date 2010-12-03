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


f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr realm) {
  f2ptr trace_event_redblacktree = nil;
  f2ptr trace_add    = nil;
  f2ptr trace_remove = nil;
  if (cause != nil) {
    trace_add    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_add"));
    trace_remove = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_remove"));
  }
  return f2__frame__new(cause, f2list12__new(cause,
					     new__symbol(cause, "type"),                     new__symbol(cause, "semantic_frame"),
					     new__symbol(cause, "realm"),                    realm,
					     new__symbol(cause, "trace_add"),                trace_add,
					     new__symbol(cause, "trace_remove"),             trace_remove,
					     new__symbol(cause, "trace_event_redblacktree"), trace_event_redblacktree,
					     new__symbol(cause, "frame"),                    f2__frame__new(cause, nil)));
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
export_cefunk4(semantic_frame__add, this, key_type, key, value, 0, "Adds the value to the key_type and key set of values.");


f2ptr raw__semantic_frame__remove(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_remove(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_redblacktree = raw__semantic_frame__trace_event_redblacktree(cause, this);
    f2ptr semantic_frame_event = raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "remove"), key_type, key, value);
    raw__semantic_frame_event_redblacktree__add(cause, trace_event_redblacktree, semantic_frame_event);
  }
  f2ptr realm                = raw__semantic_frame__realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, realm, key_type);
  f2ptr key__object_key      = raw__semantic_realm__object_key(cause, realm, key);
  f2ptr value_set            = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (value_set == nil) {
    return f2larva__new(cause, 53, nil);
  }
  if (! raw__set__remove(cause, value_set, value)) {
    return f2larva__new(cause, 53, nil);
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
  return f2__exp__as__string(cause, f2__object__type(cause, this));
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
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "realm"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__realm")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "realm"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__realm__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_add"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_add"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_add__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_remove"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_remove"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_remove__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_event_redblacktree"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_event_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_event_redblacktree"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__trace_event_redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "frame"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "frame"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_single_value"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__lookup_single_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_to_set"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__recursively_add_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_frame__as__graphviz_label")));}
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


f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  f2ptr trace_event_redblacktree = nil;
  f2ptr trace_add_semantic_frame = nil;
  if (cause != nil) {
    trace_add_semantic_frame = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_add_semantic_frame"));
  }
  return f2__frame__new(cause, f2list10__new(cause,
					     new__symbol(cause, "type"),                       new__symbol(cause, "semantic_knowledge_base"),
					     new__symbol(cause, "semantic_frames"),            semantic_frames,
					     new__symbol(cause, "trace_event_redblacktree"),   trace_event_redblacktree,
					     new__symbol(cause, "trace_add_semantic_frame"),   trace_add_semantic_frame,
					     new__symbol(cause, "trace_callback_funks_frame"), f2__frame__new(cause, nil)));
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


void raw__semantic_knowledge_base__initialize_tracing(f2ptr cause, f2ptr this) {
  if (raw__semantic_knowledge_base__trace_event_redblacktree(cause, this) == nil) {
    f2ptr trace_event_redblacktree = f2__semantic_knowledge_base_event_redblacktree__new(cause);
    raw__semantic_knowledge_base__trace_event_redblacktree__set(cause, this, trace_event_redblacktree);
  }
}


f2ptr raw__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frames = raw__semantic_knowledge_base__semantic_frames(cause, this);
  raw__semantic_knowledge_base__semantic_frames__set(cause, this, f2cons__new(cause, semantic_frame, semantic_frames));
  // trace
  if (raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this) != nil) {
    raw__semantic_knowledge_base__initialize_tracing(cause, this);
    f2ptr trace_event_redblacktree = raw__semantic_knowledge_base__trace_event_redblacktree(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "add_semantic_frame"), semantic_frame);
    raw__semantic_knowledge_base_event_redblacktree__add(cause, trace_event_redblacktree, semantic_knowledge_base_event);
    {
      f2ptr trace_callback_funks_frame        = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
      f2ptr add_semantic_frame_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame"), nil);
      {
	f2ptr iter = add_semantic_frame_callbacks;
	while (iter != nil) {
	  f2ptr add_semantic_frame_callback = f2__cons__car(cause, iter);
	  {
	    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_callback, f2list1__new(cause, semantic_knowledge_base_event));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
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


f2ptr raw__semantic_knowledge_base__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base__semantic_frames = raw__semantic_knowledge_base__semantic_frames(cause, semantic_knowledge_base);
  {
    f2ptr iter = semantic_knowledge_base__semantic_frames;
    while (iter != nil) {
      f2ptr semantic_frame = f2__cons__car(cause, iter);
      {
	raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
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


f2ptr raw__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  f2ptr trace_callback_funks_frame = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr trace_callback_funks       = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, callback_name, nil);
  f2__frame__add_var_value(cause, trace_callback_funks_frame, callback_name, f2cons__new(cause, trace_callback_funk, trace_callback_funks));
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  if ((! raw__semantic_knowledge_base__is_type(cause, this)) ||
      (! raw__funkable__is_type(cause, trace_callback_funk))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, trace_callback_name, trace_callback_funk);
}
export_cefunk3(semantic_knowledge_base__add_trace_callback_funk, this, trace_callback_name, trace_callback_funk, 0, "Adds the trace_callback_funk to the trace_callback_funks_frame under the appropriate trace_callback_name.");


boolean_t raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size) {
  s64 this_size = 0;
  {
    f2ptr iter = raw__semantic_knowledge_base__semantic_frames(cause, this);
    while (iter != nil) {
      f2ptr semantic_frame = f2__cons__car(cause, iter);
      {
	s64 semantic_frame__exact_size = 0;
	if (raw__semantic_frame__recursively_add_to_set(cause, semantic_frame, set, maximum_size - this_size, &semantic_frame__exact_size)) {
	  this_size += semantic_frame__exact_size;
	  if (this_size > maximum_size) {
	    return boolean__false;
	  }
	} else {
	  return boolean__false;
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
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



f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frames"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frames"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__semantic_frames__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_event_redblacktree"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_event_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_event_redblacktree"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_event_redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_add_semantic_frame"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_add_semantic_frame"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_add_semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "trace_callback_funks_frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_callback_funks_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "trace_callback_funks_frame"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__trace_callback_funks_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graph"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__as__graph")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_semantic_frame"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_semantic_knowledge_base"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_trace_callback_funk"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_trace_callback_funk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_semantic_frames_to_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__recursively_add_semantic_frames_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__add_to_graph_with_node_ptypehash")));}
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
  f2__add_type(cause, new__symbol(cause, "semantic_realm"),                             f2__semantic_realm_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event"),                       f2__semantic_frame_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event_redblacktree"),          f2__semantic_frame_event_redblacktree_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),                             f2__semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event"),              f2__semantic_knowledge_base_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event_redblacktree"), f2__semantic_knowledge_base_event_redblacktree_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"),                    f2__semantic_knowledge_base_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "noun_semantic_frame"),                        f2__noun_semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "visual_object_semantic_frame"),               f2__visual_object_semantic_frame_type__new(cause));
  status("semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  status("semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension_destroy, 0, "");


