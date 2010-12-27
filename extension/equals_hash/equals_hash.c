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
#include "equals_hash.h"
#include "../lick/lick.h"

f2ptr raw__equals_hash__new(f2ptr cause, f2ptr hash) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"), new__symbol(cause, "equals_hash"),
					    new__symbol(cause, "hash"), hash));
}

f2ptr raw__equals_hash__equals_hash_value_funk(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter);
  return f2__object__equals_hash_value(cause, this);
}

f2ptr raw__equals_hash__equals_funk(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr that = f2__cons__car(cause, args_iter);
  return f2__object__equals(cause, this, that);
}

f2ptr f2__equals_hash__new(f2ptr cause) {
  f2ptr equals_hash__equals_hash_value_cfunk = f2cfunk__new(cause, new__symbol(cause, "object-equals_hash_value"), 
							    f2list1__new(cause, new__symbol(cause, "this")),
							    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__equals_hash__equals_hash_value_funk)), global_environment(), nil, nil);
  f2ptr equals_hash__equals_cfunk            = f2cfunk__new(cause, new__symbol(cause, "object-equals"), 
							    f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
							    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__equals_hash__equals_funk)), global_environment(), nil, nil);
  f2ptr hash = f2__hash__new(cause, equals_hash__equals_hash_value_cfunk, equals_hash__equals_cfunk);
  return raw__equals_hash__new(cause, hash);
}
export_cefunk0(equals_hash__new, 0, "Returns a new equals_hash object.");


boolean_t raw__equals_hash__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "equals_hash");
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

f2ptr f2__equals_hash__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__equals_hash__is_type(cause, thing));
}
export_cefunk1(equals_hash__is_type, thing, 0, "Returns whether or not thing is of type equals_hash.");


f2ptr raw__equals_hash__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__equals_hash__type(f2ptr cause, f2ptr this) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__type(cause, this);
}
export_cefunk1(equals_hash__type, thing, 0, "Returns the specific type of object that this equals_hash is.");


f2ptr raw__equals_hash__hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "hash"), nil);
}

f2ptr f2__equals_hash__hash(f2ptr cause, f2ptr this) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__hash(cause, this);
}
export_cefunk1(equals_hash__hash, thing, 0, "Returns the hash of the equals_hash.");


f2ptr raw__equals_hash__hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "hash"), value);
}

f2ptr f2__equals_hash__hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__hash__set(cause, this, value);
}
export_cefunk2(equals_hash__hash__set, thing, value, 0, "Sets the hash of the equals_hash.");


f2ptr raw__equals_hash__key_count(f2ptr cause, f2ptr this) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return f2__hash__key_count(cause, hash);
}

f2ptr f2__equals_hash__key_count(f2ptr cause, f2ptr this) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__key_count(cause, this);
}
export_cefunk1(equals_hash__key_count, this, 0, "Returns the key_count of this equals_hash.");


f2ptr raw__equals_hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__add(cause, hash, key, value);
}

f2ptr f2__equals_hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__add(cause, this, key, value);
}
export_cefunk3(equals_hash__add, this, key, value, 0, "Adds a key/value pair to this equals_hash.");


f2ptr raw__equals_hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__lookup(cause, hash, key);
}

f2ptr f2__equals_hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__lookup(cause, this, key);
}
export_cefunk2(equals_hash__lookup, this, key, 0, "Looks up the given key's value in this equals hash.");


f2ptr raw__equals_hash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "equals_hash")));
    f2ptr hash = raw__equals_hash__hash(cause, this);
    hash__iteration(cause, hash, key, value,
		    raw__frame__add_var_value(cause, frame, key, value);
		    );
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__equals_hash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__equals_hash__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(equals_hash__terminal_print_with_frame, this, terminal_print_frame, 0, "");



// equals_hash lick funks

f2ptr raw__equals_hash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  f2ptr key_count    = f2__equals_hash__key_count(cause, this);
  s64   key_count__i = f2integer__i(key_count, cause);
  f2ptr chunk        = raw__chunk__new(cause, key_count__i * 8 * 2);
  {
    s64 index = 0;
    equals_hash__iteration(cause, this, key, value,
			   {
			     f2ptr key__note = raw__lick__object__as__note(cause, lick, key, note_object_hash, max_size);
			     if (raw__larva__is_type(cause, key__note)) {
			       return key__note;
			     }
			     s64 key__note__i = f2integer__i(key__note, cause);
			     raw__chunk__bit64__elt__set(cause, chunk, ((index * 2) + 0) * 8, (s64)(key__note__i));
			   }
			   {
			     f2ptr value__note = raw__lick__object__as__note(cause, lick, value, note_object_hash, max_size);
			     if (raw__larva__is_type(cause, value__note)) {
			       return value__note;
			     }
			     s64 value__note__i = f2integer__i(value__note, cause);
			     raw__chunk__bit64__elt__set(cause, chunk, ((index * 2) + 1) * 8, (s64)(value__note__i));
			   }
			   index ++;
			   );
    if (index != key_count__i) {
      return f2larva__new(cause, 23445, nil);
    }
  }
  f2ptr lick_note = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__equals_hash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__equals_hash__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__lick_to_chunk(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(equals_hash__lick_to_chunk, this, lick, note_object_hash, max_size, 0, "Licks this equals_hash.");


f2ptr raw__equals_hash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (((chunk__length >> 4) << 4) != chunk__length) {
    return f2larva__new(cause, 32555, nil);
  }
  s64   equals_hash__key_count = chunk__length >> 4;
  f2ptr equals_hash            = f2__equals_hash__new(cause);
  {
    s64 index;
    for (index = 0; index < equals_hash__key_count; index ++) {
      f2ptr key__lick_note   = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, ((index * 2) + 0) * 8));
      f2ptr value__lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, ((index * 2) + 1) * 8));
      raw__equals_hash__add(cause, equals_hash, key__lick_note, value__lick_note);
    }
  }
  return equals_hash;
}

f2ptr f2__equals_hash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__equals_hash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(equals_hash__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this equals_hash lick_chunk with notes.");


f2ptr raw__equals_hash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  f2ptr key_notes   = nil;
  f2ptr value_notes = nil;
  equals_hash__iteration(cause, this, key_note, value_note,
			 key_notes   = f2cons__new(cause, key_note,   key_notes);
			 value_notes = f2cons__new(cause, value_note, value_notes);
			 );
  f2ptr key_objects   = nil;
  f2ptr value_objects = nil;
  {
    f2ptr key_note_iter   = key_notes;
    f2ptr value_note_iter = value_notes;
    while (key_note_iter != nil) {
      f2ptr key_note   = f2__cons__car(cause, key_note_iter);
      f2ptr value_note = f2__cons__car(cause, value_note_iter);
      {
	f2ptr key_object   = raw__ptypehash__lookup(cause, object_note_hash, key_note);
	f2ptr value_object = raw__ptypehash__lookup(cause, object_note_hash, value_note);
	key_objects   = f2cons__new(cause, key_object,   key_objects);
	value_objects = f2cons__new(cause, value_object, value_objects);
	raw__equals_hash__remove(cause, this, key_note);
      }
      key_note_iter   = f2__cons__cdr(cause, key_note_iter);
      value_note_iter = f2__cons__cdr(cause, value_note_iter);
    }
  }
  {
    f2ptr key_object_iter   = key_objects;
    f2ptr value_object_iter = value_objects;
    while (key_object_iter != nil) {
      f2ptr key_object   = f2__cons__car(cause, key_object_iter);
      f2ptr value_object = f2__cons__car(cause, value_object_iter);
      {
	raw__equals_hash__add(cause, this, key_object, value_object);
      }
      key_object_iter   = f2__cons__cdr(cause, key_object_iter);
      value_object_iter = f2__cons__cdr(cause, value_object_iter);
    }
  }
  return nil;
}

f2ptr f2__equals_hash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__equals_hash__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__equals_hash__lick_chunk__unlick_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(equals_hash__lick_chunk__unlick_replace_notes_with_objects, this, object_note_hash, 0, "Unlicks this equals_hash with notes.");


f2ptr f2__equals_hash_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "hash"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "hash"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_count"),                                    f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__terminal_print_with_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lick_chunk__unlick_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lick_chunk__unlick_replace_notes_with_objects")));}
  return this;
}



// **

f2ptr f2__equals_hash__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(equals_hash__core_extension_ping, 0, "");

f2ptr f2__equals_hash__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "equals_hash"), f2__equals_hash_type__new(cause));
  status("equals_hash initialized.");
  return nil;
}
export_cefunk0(equals_hash__core_extension_initialize, 0, "");

f2ptr f2__equals_hash__core_extension_destroy(f2ptr cause) {
  status("equals_hash destroyed.");
  return nil;
}
export_cefunk0(equals_hash__core_extension_destroy, 0, "");


