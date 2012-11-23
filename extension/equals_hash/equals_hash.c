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

#include "../../c/funk2.h"
#include "equals_hash.h"
#include "../lick/lick.h"

f2ptr raw__equals_hash__new(f2ptr cause, f2ptr hash) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"), new__symbol(cause, "equals_hash"),
					    new__symbol(cause, "hash"), hash));
}

f2ptr raw__equals_hash__equals_hash_value_cfunk(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter);
  return f2__object__equals_hash_value(cause, this);
}

f2ptr raw__equals_hash__equals_cfunk(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr that = f2__cons__car(cause, args_iter);
  return f2__object__equals(cause, this, that);
}

f2ptr raw__equals_hash__hash_value_funk(f2ptr cause) {
  return f2cfunk__new(cause, new__symbol(cause, "object-equals_hash_value"), 
		      f2list1__new(cause, new__symbol(cause, "this")),
		      f2pointer__new(cause, raw_executable__to__relative_ptr(raw__equals_hash__equals_hash_value_cfunk)), global_environment(), nil, nil);
}

f2ptr raw__equals_hash__equals_funk(f2ptr cause) {
  return f2cfunk__new(cause, new__symbol(cause, "object-equals"), 
		      f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
		      f2pointer__new(cause, raw_executable__to__relative_ptr(raw__equals_hash__equals_cfunk)), global_environment(), nil, nil);
}

f2ptr f2__equals_hash__new(f2ptr cause) {
  f2ptr hash = f2__hash__new(cause, raw__equals_hash__hash_value_funk(cause), raw__equals_hash__equals_funk(cause));
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
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__type(cause, this);
}
export_cefunk1(equals_hash__type, thing, 0, "Returns the specific type of object that this equals_hash is.");


f2ptr raw__equals_hash__hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "hash"), nil);
}

f2ptr f2__equals_hash__hash(f2ptr cause, f2ptr this) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__hash(cause, this);
}
export_cefunk1(equals_hash__hash, thing, 0, "Returns the hash of the equals_hash.");


f2ptr raw__equals_hash__hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "hash"), value);
}

f2ptr f2__equals_hash__hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__hash__set(cause, this, value);
}
export_cefunk2(equals_hash__hash__set, thing, value, 0, "Sets the hash of the equals_hash.");


f2ptr raw__equals_hash__key_count(f2ptr cause, f2ptr this) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return f2__hash__key_count(cause, hash);
}

f2ptr f2__equals_hash__key_count(f2ptr cause, f2ptr this) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__key_count(cause, this);
}
export_cefunk1(equals_hash__key_count, this, 0, "Returns the key_count of this equals_hash.");


f2ptr raw__equals_hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__add(cause, hash, key, value);
}

f2ptr f2__equals_hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__add(cause, this, key, value);
}
export_cefunk3(equals_hash__add, this, key, value, 0, "Adds a key/value pair to this equals_hash.");


f2ptr raw__equals_hash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__remove(cause, hash, key);
}

f2ptr f2__equals_hash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__remove(cause, this, key);
}
export_cefunk2(equals_hash__remove, this, key, 0, "Looks up the given key's value in this equals hash.");


f2ptr raw__equals_hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__lookup(cause, hash, key);
}

f2ptr f2__equals_hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__lookup(cause, this, key);
}
export_cefunk2(equals_hash__lookup, this, key, 0, "Looks up the given key's value in this equals hash.");


f2ptr raw__equals_hash__keys(f2ptr cause, f2ptr this) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__keys(cause, hash);
}

f2ptr f2__equals_hash__keys(f2ptr cause, f2ptr this) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__keys(cause, this);
}
export_cefunk1(equals_hash__keys, this, 0, "Returns a new conslist of the keys in this equals_hash.");


f2ptr raw__equals_hash__values(f2ptr cause, f2ptr this) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  return raw__hash__values(cause, hash);
}

f2ptr f2__equals_hash__values(f2ptr cause, f2ptr this) {
  assert_argument_type(equals_hash, this);
  return raw__equals_hash__values(cause, this);
}
export_cefunk1(equals_hash__values, this, 0, "Returns a new conslist of the values in this equals_hash.");


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
  assert_argument_type(equals_hash, this); 
  return raw__equals_hash__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(equals_hash__terminal_print_with_frame, this, terminal_print_frame, 0, "");



// equals_hash lick funks

f2ptr raw__equals_hash__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  {
    f2ptr key_count = f2__hash__key_count(cause, hash);
    assert_value(raw__lick__object__gather_lick_notes(cause, lick, key_count, note_object_hash, max_size));
  }
  {
    f2ptr bin_num_power = f2__hash__bin_num_power(cause, hash);
    assert_value(raw__lick__object__gather_lick_notes(cause, lick, bin_num_power, note_object_hash, max_size));
  }
  {
    f2ptr bin_array = f2__hash__bin_array(cause, hash);
    assert_value(raw__lick__object__gather_lick_notes(cause, lick, bin_array, note_object_hash, max_size));
  }
  return nil;
}

f2ptr f2__equals_hash__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  assert_argument_type(equals_hash, this);
  assert_argument_type(lick,        lick);
  assert_argument_type(ptypehash,   note_object_hash);
  assert_argument_type(integer,     max_size);
  return raw__equals_hash__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(equals_hash__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Licks this equals_hash.");


f2ptr raw__equals_hash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk = raw__chunk__new(cause, 8 * 3);
  f2ptr hash  = raw__equals_hash__hash(cause, this);
  {
    f2ptr key_count          = f2__hash__key_count(cause, hash);
    f2ptr key_count__note    = raw__ptypehash__lookup(cause, note_object_hash, key_count);
    if (key_count__note == nil) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),  new__symbol(cause, "note_changed_while_licking_to_chunk"),
				     new__symbol(cause, "key_count"), key_count,
				     new__symbol(cause, "this"),      this));
    }
    s64   key_count__note__i = f2integer__i(key_count__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 0, (s64)key_count__note__i);
  }
  {
    f2ptr bin_num_power = f2__hash__bin_num_power(cause, hash);
    f2ptr bin_num_power__note    = raw__ptypehash__lookup(cause, note_object_hash, bin_num_power);
    if (bin_num_power__note == nil) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),      new__symbol(cause, "note_changed_while_licking_to_chunk"),
				     new__symbol(cause, "bin_num_power"), bin_num_power,
				     new__symbol(cause, "this"),          this));
    }
    s64   bin_num_power__note__i = f2integer__i(bin_num_power__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 8, (s64)bin_num_power__note__i);
  }
  {
    f2ptr bin_array          = f2__hash__bin_array(cause, hash);
    f2ptr bin_array__note    = raw__ptypehash__lookup(cause, note_object_hash, bin_array);
    if (bin_array__note == nil) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),  new__symbol(cause, "note_changed_while_licking_to_chunk"),
				     new__symbol(cause, "bin_array"), bin_array,
				     new__symbol(cause, "this"),      this));
    }
    s64   bin_array__note__i = f2integer__i(bin_array__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 16, (s64)bin_array__note__i);
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),  new__symbol(cause, "note_changed_while_licking_to_chunk"),
				   new__symbol(cause, "this"),      this));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__equals_hash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  assert_argument_type(equals_hash, this);
  assert_argument_type(ptypehash,   note_object_hash);
  return raw__equals_hash__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(equals_hash__lick_to_chunk, this, note_object_hash, 0, "Licks this equals_hash.");


f2ptr raw__equals_hash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != (8 * 3)) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),         new__symbol(cause, "equals_hash-lick_chunk-unlick_with_nodes-chunk_length_incorrect"),
				   new__symbol(cause, "this"),             this,
				   new__symbol(cause, "lick_chunk"),       lick_chunk,
				   new__symbol(cause, "object_note_hash"), object_note_hash));
  }
  f2ptr key_count__lick_note     = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  f2ptr bin_num_power__lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 8));
  f2ptr bin_array__lick_note     = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 16));
  f2ptr hash                     = f2hash__new(cause, f2__cmutex__new(cause), key_count__lick_note, bin_num_power__lick_note, bin_array__lick_note, raw__equals_hash__hash_value_funk(cause), raw__equals_hash__equals_funk(cause));
  f2ptr equals_hash              = raw__equals_hash__new(cause, hash);
  return equals_hash;
}

f2ptr f2__equals_hash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(lick_chunk, lick_chunk);
  assert_argument_type(ptypehash,  object_note_hash);
  return raw__equals_hash__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(equals_hash__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this equals_hash lick_chunk with notes.");


f2ptr raw__equals_hash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr hash = raw__equals_hash__hash(cause, this);
  {
    f2ptr key_count__lick_note = f2__hash__key_count(cause, hash);
    f2ptr key_count__object    = raw__ptypehash__lookup(cause, object_note_hash, key_count__lick_note);
    f2__hash__key_count__set(cause, hash, key_count__object);
  }
  {
    f2ptr bin_num_power__lick_note = f2__hash__bin_num_power(cause, hash);
    f2ptr bin_num_power__object    = raw__ptypehash__lookup(cause, object_note_hash, bin_num_power__lick_note);
    f2__hash__bin_num_power__set(cause, hash, bin_num_power__object);
  }
  {
    f2ptr bin_array__lick_note = f2__hash__bin_array(cause, hash);
    f2ptr bin_array__object    = raw__ptypehash__lookup(cause, object_note_hash, bin_array__lick_note);
    f2__hash__bin_array__set(cause, hash, bin_array__object);
  }
  return nil;
}

f2ptr f2__equals_hash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(equals_hash, this);
  assert_argument_type(lick_chunk,  lick_chunk);
  assert_argument_type(ptypehash,   object_note_hash);
  return raw__equals_hash__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(equals_hash__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this equals_hash with notes.");


f2ptr f2__equals_hash_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "hash"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__hash")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "hash"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "key_count"),                                    f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__key_count")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lookup"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "keys"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__keys")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "values"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__values")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__terminal_print_with_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__gather_lick_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lick_to_chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lick_chunk__unlick_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "equals_hash"), new__symbol(cause, "equals_hash__lick_chunk__unlick_replace_notes_with_objects")));}
  return this;
}



// **

f2ptr f2__equals_hash__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(equals_hash__core_extension__ping, 0, "");

f2ptr f2__equals_hash__core_extension__initialize(f2ptr cause) {
  assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__core_extension__ping")), nil));
  f2__add_type(cause, new__symbol(cause, "equals_hash"), f2__equals_hash_type__new(cause));
  status("equals_hash initialized.");
  return nil;
}
export_cefunk0(equals_hash__core_extension__initialize, 0, "");

f2ptr f2__equals_hash__core_extension__destroy(f2ptr cause) {
  status("equals_hash destroyed.");
  return nil;
}
export_cefunk0(equals_hash__core_extension__destroy, 0, "");


