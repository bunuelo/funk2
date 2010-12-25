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

#include "lick.h"


// lick_note

f2ptr raw__lick_note__new(f2ptr cause, f2ptr unique_identifier) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),              new__symbol(cause, "lick_note"),
					    new__symbol(cause, "unique_identifier"), unique_identifier));
}

f2ptr f2__lick_note__new(f2ptr cause, f2ptr unique_identifier) {
  return raw__lick_note__new(cause, unique_identifier);
}
export_cefunk1(lick_note__new, unique_identifier, 0, "Given a unique_identifier, returns a unique lick_note object identifier.");


boolean_t raw__lick_note__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "lick_note");
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

f2ptr f2__lick_note__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__lick_note__is_type(cause, thing));
}
export_cefunk1(lick_note__is_type, thing, 0, "Returns whether or not thing is of type lick_note.");


f2ptr raw__lick_note__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__lick_note__type(f2ptr cause, f2ptr this) {
  if (! raw__lick_note__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_note__type(cause, this);
}
export_cefunk1(lick_note__type, thing, 0, "Returns the specific type of object that this lick_note is.");


f2ptr raw__lick_note__unique_identifier(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "unique_identifier"), nil);
}

f2ptr f2__lick_note__unique_identifier(f2ptr cause, f2ptr this) {
  if (! raw__lick_note__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_note__unique_identifier(cause, this);
}
export_cefunk1(lick_note__unique_identifier, thing, 0, "Returns the unique_identifier of the lick_note.");


f2ptr raw__lick_note__unique_identifier__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "unique_identifier"), value);
}

f2ptr f2__lick_note__unique_identifier__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick_note__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_note__unique_identifier__set(cause, this, value);
}
export_cefunk2(lick_note__unique_identifier__set, thing, value, 0, "Sets the unique_identifier of the lick_note.");


f2ptr f2__lick_note_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),               f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_note__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_note__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_note__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "unique_identifier"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_note__unique_identifier")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "unique_identifier"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_note__unique_identifier__set")));}
  return this;
}


// lick_chunk

f2ptr raw__lick_chunk__new(f2ptr cause, f2ptr type_name, f2ptr lick_note, f2ptr chunk) {
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),      new__symbol(cause, "lick_chunk"),
					    new__symbol(cause, "type_name"), type_name,
					    new__symbol(cause, "lick_note"), lick_note,
					    new__symbol(cause, "chunk"),     chunk));
}

f2ptr f2__lick_chunk__new(f2ptr cause, f2ptr type_name, f2ptr lick_note, f2ptr chunk) {
  if (((type_name != nil) && (! raw__symbol__is_type(cause, type_name))) ||
      (! raw__lick_note__is_type(cause, lick_note)) ||
      (! raw__chunk__is_type(cause, chunk))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__new(cause, type_name, lick_note, chunk);
}
export_cefunk3(lick_chunk__new, type_name, lick_note, chunk, 0, "Given a type_name, lick_note, and a chunk, returns a unique lick_chunk object.");


boolean_t raw__lick_chunk__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "lick_chunk");
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

f2ptr f2__lick_chunk__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__lick_chunk__is_type(cause, thing));
}
export_cefunk1(lick_chunk__is_type, thing, 0, "Returns whether or not thing is of type lick_chunk.");


f2ptr raw__lick_chunk__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__lick_chunk__type(f2ptr cause, f2ptr this) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__type(cause, this);
}
export_cefunk1(lick_chunk__type, thing, 0, "Returns the specific type of object that this lick_chunk is.");


f2ptr raw__lick_chunk__type_name(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "type_name"), nil);
}

f2ptr f2__lick_chunk__type_name(f2ptr cause, f2ptr this) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__type_name(cause, this);
}
export_cefunk1(lick_chunk__type_name, thing, 0, "Returns the type_name of the lick_chunk.");


f2ptr raw__lick_chunk__type_name__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "type_name"), value);
}

f2ptr f2__lick_chunk__type_name__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__type_name__set(cause, this, value);
}
export_cefunk2(lick_chunk__type_name__set, thing, value, 0, "Sets the type_name of the lick_chunk.");


f2ptr raw__lick_chunk__lick_note(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "lick_note"), nil);
}

f2ptr f2__lick_chunk__lick_note(f2ptr cause, f2ptr this) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__lick_note(cause, this);
}
export_cefunk1(lick_chunk__lick_note, thing, 0, "Returns the lick_note of the lick_chunk.");


f2ptr raw__lick_chunk__lick_note__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "lick_note"), value);
}

f2ptr f2__lick_chunk__lick_note__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__lick_note__set(cause, this, value);
}
export_cefunk2(lick_chunk__lick_note__set, thing, value, 0, "Sets the lick_note of the lick_chunk.");


f2ptr raw__lick_chunk__chunk(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "chunk"), nil);
}

f2ptr f2__lick_chunk__chunk(f2ptr cause, f2ptr this) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__chunk(cause, this);
}
export_cefunk1(lick_chunk__chunk, thing, 0, "Returns the chunk of the lick_chunk.");


f2ptr raw__lick_chunk__chunk__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "chunk"), value);
}

f2ptr f2__lick_chunk__chunk__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick_chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__chunk__set(cause, this, value);
}
export_cefunk2(lick_chunk__chunk__set, thing, value, 0, "Sets the chunk of the lick_chunk.");


f2ptr raw__lick_chunk__remember_with_notes(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  f2ptr lick_note                    = raw__lick_chunk__lick_note(cause, this);
  f2ptr lick_note__unique_identifier = raw__lick_note__unique_identifier(cause, lick_note);
  f2ptr remembered_object_with_notes = raw__ptypehash__lookup(cause, object_note_hash, lick_note__unique_identifier);
  if (remembered_object_with_notes == nil) {
    f2ptr type_name = raw__lick_chunk__type_name(cause, this);
    f2ptr type      = f2__lookup_type(cause, type_name);
    if (raw__larva__is_type(cause, type)) {
      return type;
    }
    f2ptr lick_chunk__remember_with_notes__funk = f2__primobject_type__lookup_slot_type_funk(cause, type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"));
    if (raw__larva__is_type(cause, lick_chunk__remember_with_notes__funk)) {
      return lick_chunk__remember_with_notes__funk;
    }
    if (! raw__funkable__is_type(cause, lick_chunk__remember_with_notes__funk)) {
      return f2larva__new(cause, 23444, nil);
    }
    remembered_object_with_notes = f2__force_funk_apply(cause, f2__this__fiber(cause), lick_chunk__remember_with_notes__funk, f2list2__new(cause, this, object_note_hash));
    if (raw__larva__is_type(cause, remembered_object_with_notes)) {
      return remembered_object_with_notes;
    }
    raw__ptypehash__add(cause, object_note_hash, lick_note__unique_identifier, remembered_object_with_notes);
  }
  return remembered_object_with_notes;
}

f2ptr f2__lick_chunk__remember_with_notes(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__remember_with_notes(cause, this, object_note_hash);
}
export_cefunk2(lick_chunk__remember_with_notes, this, object_note_hash, 0, "Remembers this lick_chunk as an actual object, but with notes instead of sub-objects.");


f2ptr raw__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  f2ptr lick_note                    = raw__lick_chunk__lick_note(cause, this);
  f2ptr lick_note__unique_identifier = raw__lick_note__unique_identifier(cause, lick_note);
  f2ptr remembered_object_with_notes = raw__ptypehash__lookup(cause, object_note_hash, lick_note__unique_identifier);
  f2ptr type_name                    = raw__lick_chunk__type_name(cause, this);
  f2ptr type                         = f2__lookup_type(cause, type_name);
  if (raw__larva__is_type(cause, type)) {
    return type;
  }
  f2ptr lick_chunk__remember_replace_notes_with_objects__funk = f2__primobject_type__lookup_slot_type_funk(cause, type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"));
  if (raw__larva__is_type(cause, lick_chunk__remember_replace_notes_with_objects__funk)) {
    return lick_chunk__remember_replace_notes_with_objects__funk;
  }
  if (! raw__funkable__is_type(cause, lick_chunk__remember_replace_notes_with_objects__funk)) {
    return f2larva__new(cause, 23445, nil);
  }
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), lick_chunk__remember_replace_notes_with_objects__funk, f2list2__new(cause, remembered_object_with_notes, object_note_hash));
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return nil;
}

f2ptr f2__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this lick_chunk as an actual object, but with notes instead of sub-objects.");


f2ptr f2__lick_chunk_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type_name"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type_name")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "type_name"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type_name__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__chunk__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remember_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__remember_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__remember_replace_notes_with_objects")));}
  return this;
}


// lick

f2ptr raw__lick__new(f2ptr cause, f2ptr root_object) {
  f2ptr chunk_note_hash = f2__ptypehash__new(cause);
  f2ptr this = f2__frame__new(cause, f2list6__new(cause,
						  new__symbol(cause, "type"),            new__symbol(cause, "lick"),
						  new__symbol(cause, "root_note"),       nil,
						  new__symbol(cause, "chunk_note_hash"), chunk_note_hash));
  f2ptr note_object_hash = f2__ptypehash__new(cause);
  f2ptr root_note        = raw__lick__object__as__note(cause, this, root_object, note_object_hash);
  if (raw__larva__is_type(cause, root_note)) {
    return root_note;
  }
  raw__lick__root_note__set(cause, this, root_note);
  return this;
}

f2ptr f2__lick__new(f2ptr cause, f2ptr chunk_note_hash) {
  return raw__lick__new(cause, chunk_note_hash);
}
export_cefunk1(lick__new, chunk_note_hash, 0, "Returns a new lick object.");


boolean_t raw__lick__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "lick");
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

f2ptr f2__lick__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__lick__is_type(cause, thing));
}
export_cefunk1(lick__is_type, thing, 0, "Returns whether or not thing is of type lick.");


f2ptr raw__lick__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__lick__type(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__type(cause, this);
}
export_cefunk1(lick__type, thing, 0, "Returns the specific type of object that this lick is.");


f2ptr raw__lick__root_note(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "root_note"), nil);
}

f2ptr f2__lick__root_note(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__root_note(cause, this);
}
export_cefunk1(lick__root_note, thing, 0, "Returns the root_note of the lick.");


f2ptr raw__lick__root_note__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "root_note"), value);
}

f2ptr f2__lick__root_note__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__root_note__set(cause, this, value);
}
export_cefunk2(lick__root_note__set, thing, value, 0, "Sets the root_note of the lick.");


f2ptr raw__lick__chunk_note_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "chunk_note_hash"), nil);
}

f2ptr f2__lick__chunk_note_hash(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__chunk_note_hash(cause, this);
}
export_cefunk1(lick__chunk_note_hash, thing, 0, "Returns the chunk_note_hash of the lick.");


f2ptr raw__lick__chunk_note_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "chunk_note_hash"), value);
}

f2ptr f2__lick__chunk_note_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__chunk_note_hash__set(cause, this, value);
}
export_cefunk2(lick__chunk_note_hash__set, thing, value, 0, "Sets the chunk_note_hash of the lick.");


f2ptr raw__lick__object__as__note(f2ptr cause, f2ptr this, f2ptr object, f2ptr note_object_hash) {
  f2ptr note = raw__ptypehash__lookup(cause, note_object_hash, object);
  if (note == nil) {
    f2ptr unique_identifier = f2integer__new(cause, (s64)object);
    note = f2__lick_note__new(cause, unique_identifier);
    if (raw__larva__is_type(cause, note)) {
      return note;
    }
    raw__ptypehash__add(cause, note_object_hash, object, note);
    f2ptr chunk = f2__object__execute(cause, object, new__symbol(cause, "lick_to_chunk"), f2list2__new(cause, this, note_object_hash));
    if (raw__larva__is_type(cause, chunk)) {
      return chunk;
    }
    f2ptr chunk_note_hash = raw__lick__chunk_note_hash(cause, this);
    raw__ptypehash__add(cause, chunk_note_hash, unique_identifier, chunk);
  }
  return note;
}

f2ptr f2__lick__object__as__note(f2ptr cause, f2ptr this, f2ptr object, f2ptr note_object_hash) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__object__as__note(cause, this, object, note_object_hash);
}
export_cefunk3(lick__object__as__note, this, object, note_object_hash, 0, "Get this lick's object as note.");


f2ptr raw__lick__remember(f2ptr cause, f2ptr this) {
  f2ptr chunk_note_hash  = raw__lick__chunk_note_hash(cause, this);
  f2ptr object_note_hash = f2__ptypehash__new(cause);
  ptypehash__value__iteration(cause, chunk_note_hash, lick_chunk,
			      raw__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
			      );
  ptypehash__value__iteration(cause, chunk_note_hash, lick_chunk,
			      f2ptr result = raw__lick_chunk__remember_replace_notes_with_objects(cause, lick_chunk, object_note_hash);
			      if (raw__larva__is_type(cause, result)) {
				return result;
			      }
			      );
  f2ptr root_note                    = raw__lick__root_note(cause, this);
  f2ptr root_note__unique_identifier = raw__lick_note__unique_identifier(cause, root_note);
  return raw__ptypehash__lookup(cause, object_note_hash, root_note__unique_identifier);
}

f2ptr f2__lick__remember(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__remember(cause, this);
}
export_cefunk1(lick__remember, this, 0, "Remember this lick.");


f2ptr f2__lick_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "root_note"),       f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__root_note")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "root_note"),       f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__root_note__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk_note_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk_note_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "object-as-note"),  f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__object__as__note")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remember"),        f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__remember")));}
  return this;
}


// ptype lick_to_chunk funks

//   nil lick_to_chunk

f2ptr raw__nil__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  f2ptr chunk = raw__chunk__new(cause, 0);
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, nil, raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__nil__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((this != nil) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(nil__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this nil.");


f2ptr raw__nil__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__nil__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(nil__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this nil lick_chunk with notes.");


f2ptr raw__nil__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__nil__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((this != nil) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(nil__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this nil with notes.");


//   integer lick_to_chunk

f2ptr raw__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 8);
  s64   this__i = f2integer__i(this, cause);
  raw__chunk__bit64__elt__set(cause, chunk, 0, this__i);
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, new__symbol(cause, "integer"), raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(integer__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this integer.");


f2ptr raw__integer__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk   = raw__lick_chunk__chunk(cause, lick_chunk);
  f2ptr integer = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  return integer;
}

f2ptr f2__integer__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(integer__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this integer lick_chunk with notes.");


f2ptr raw__integer__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__integer__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(integer__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this integer with notes.");


//   float lick_to_chunk

f2ptr raw__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 4);
  float this__f = f2float__f(this, cause);
  u32*  data    = (u32*)(&this__f);
  raw__chunk__bit32__elt__set(cause, chunk, 0, *data);
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, new__symbol(cause, "float"), raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(float__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this float.");


f2ptr raw__float__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr  chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u32    data  = raw__chunk__bit32__elt(cause, chunk, 0);
  float* f_ptr = (float*)(&data);
  return f2float__new(cause, *f_ptr);
}

f2ptr f2__float__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(float__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this float lick_chunk with notes.");


f2ptr raw__float__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__float__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(float__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this float with notes.");


//   double lick_to_chunk

f2ptr raw__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  f2ptr  chunk    = raw__chunk__new(cause, 8);
  double this__d  = f2double__d(this, cause);
  u64    data     = *data_ptr;
  memcpy(&data, &this__d, sizeof(u64));
  raw__chunk__bit64__elt__set(cause, chunk, 0, data);
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, new__symbol(cause, "double"), raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(double__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this double.");


f2ptr raw__double__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr   chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u64     data  = raw__chunk__bit64__elt(cause, chunk, 0);
  double* d_ptr = (double*)(&data);
  return f2double__new(cause, *d_ptr);
}

f2ptr f2__double__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(double__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this double lick_chunk with notes.");


f2ptr raw__double__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__double__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(double__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this double with notes.");


//   pointer lick_to_chunk

f2ptr raw__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 8);
  u64   this__p = f2pointer__p(this, cause);
  raw__chunk__bit64__elt__set(cause, chunk, 0, this__p);
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, new__symbol(cause, "pointer"), raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(pointer__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this pointer.");


f2ptr raw__pointer__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u64   data  = raw__chunk__bit64__elt(cause, chunk, 0);
  return f2pointer__new(cause, *((u64*)(&data)));
}

f2ptr f2__pointer__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(pointer__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this pointer lick_chunk with notes.");


f2ptr raw__pointer__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__pointer__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(pointer__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this pointer with notes.");


//   string lick_to_chunk

f2ptr raw__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  return nil;
}

f2ptr f2__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(string__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this string.");


f2ptr raw__string__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__string__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(string__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this string lick_chunk with notes.");


f2ptr raw__string__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__string__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(string__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this string with notes.");


//   symbol lick_to_chunk

f2ptr raw__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  return nil;
}

f2ptr f2__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(symbol__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this symbol.");


f2ptr raw__symbol__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__symbol__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(symbol__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this symbol lick_chunk with notes.");


f2ptr raw__symbol__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__symbol__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(symbol__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this symbol with notes.");


//   chunk lick_to_chunk

f2ptr raw__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  return nil;
}

f2ptr f2__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(chunk__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this chunk.");


f2ptr raw__chunk__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__chunk__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(chunk__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this chunk lick_chunk with notes.");


f2ptr raw__chunk__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__chunk__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(chunk__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this chunk with notes.");


//   array lick_to_chunk

f2ptr raw__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  s64   this__length = raw__array__length(cause, this);
  f2ptr chunk        = raw__chunk__new(cause, this__length * 8);
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr element       = raw__array__elt(cause, this, index);
      f2ptr element__note = raw__lick__object__as__note(cause, lick, element, note_object_hash);
      if (raw__larva__is_type(cause, element__note)) {
	return element__note;
      }
      f2ptr element__note__unique_identifier    = raw__lick_note__unique_identifier(cause, element__note);
      s64   element__note__unique_identifier__i = f2integer__i(element__note__unique_identifier, cause);
      raw__chunk__bit64__elt__set(cause, chunk, index * 8, (s64)(element__note__unique_identifier__i));
    }
  }
  f2ptr unique_identifier = f2integer__new(cause, (s64)this);
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), raw__lick_note__new(cause, unique_identifier), chunk);
}

f2ptr f2__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_to_chunk(cause, this, lick, note_object_hash);
}
export_cefunk3(array__lick_to_chunk, this, lick, note_object_hash, 0, "Licks this array.");


f2ptr raw__array__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (((chunk__length >> 3) << 3) != chunk__length) {
    return f2larva__new(cause, 32555, nil);
  }
  s64   array__length = chunk__length >> 3;
  f2ptr array         = raw__array__new(cause, array__length);
  {
    s64 index;
    for (index = 0; index < array__length; index ++) {
      f2ptr unique_identifier = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, index << 3));
      f2ptr lick_note         = raw__lick_note__new(cause, unique_identifier);
      raw__array__elt__set(cause, array, index, lick_note);
    }
  }
  return array;
}

f2ptr f2__array__lick_chunk__remember_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_chunk__remember_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(array__lick_chunk__remember_with_notes, lick_chunk, object_note_hash, 0, "Remembers this array lick_chunk with notes.");


f2ptr raw__array__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  s64 array__length = raw__array__length(cause, this);
  {
    s64 index;
    for (index = 0; index < array__length; index ++) {
      f2ptr lick_note                    = raw__array__elt(cause, this, index);
      f2ptr lick_note__unique_identifier = raw__lick_note__unique_identifier(cause, lick_note);
      f2ptr object                       = raw__ptypehash__lookup(cause, object_note_hash, lick_note__unique_identifier);
      raw__array__elt__set(cause, this, index, object);
    }
  }
  return nil;
}

f2ptr f2__array__lick_chunk__remember_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_chunk__remember_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(array__lick_chunk__remember_replace_notes_with_objects, this, object_note_hash, 0, "Remembers this array with notes.");


f2ptr raw__add_all_lick_to_chunk_to_ptypes(f2ptr cause) {
  {
    f2ptr nil_type = f2__lookup_type(cause, nil);
    if (raw__larva__is_type(cause, nil_type)) {
      return nil_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr integer_type = f2__lookup_type(cause, new__symbol(cause, "integer"));
    if (raw__larva__is_type(cause, integer_type)) {
      return integer_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr float_type = f2__lookup_type(cause, new__symbol(cause, "float"));
    if (raw__larva__is_type(cause, float_type)) {
      return float_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr double_type = f2__lookup_type(cause, new__symbol(cause, "double"));
    if (raw__larva__is_type(cause, double_type)) {
      return double_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr pointer_type = f2__lookup_type(cause, new__symbol(cause, "pointer"));
    if (raw__larva__is_type(cause, pointer_type)) {
      return pointer_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr string_type = f2__lookup_type(cause, new__symbol(cause, "string"));
    if (raw__larva__is_type(cause, string_type)) {
      return string_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr symbol_type = f2__lookup_type(cause, new__symbol(cause, "symbol"));
    if (raw__larva__is_type(cause, symbol_type)) {
      return symbol_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr chunk_type = f2__lookup_type(cause, new__symbol(cause, "chunk"));
    if (raw__larva__is_type(cause, chunk_type)) {
      return chunk_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr simple_array_type = f2__lookup_type(cause, new__symbol(cause, "simple_array"));
    if (raw__larva__is_type(cause, simple_array_type)) {
      return simple_array_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr traced_array_type = f2__lookup_type(cause, new__symbol(cause, "traced_array"));
    if (raw__larva__is_type(cause, traced_array_type)) {
      return traced_array_type;
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, traced_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, traced_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_with_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__remember_with_notes")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = f2__primobject_type__add_slot_type(cause, traced_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-remember_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__remember_replace_notes_with_objects")));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}


// **

f2ptr f2__lick__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(lick__core_extension_ping, 0, "");

f2ptr f2__lick__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "lick_note"),  f2__lick_note_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "lick_chunk"), f2__lick_chunk_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "lick"),       f2__lick_type__new(cause));
  {
    f2ptr result = raw__add_all_lick_to_chunk_to_ptypes(cause);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("lick initialized.");
  return nil;
}
export_cefunk0(lick__core_extension_initialize, 0, "");

f2ptr f2__lick__core_extension_destroy(f2ptr cause) {
  status("lick destroyed.");
  return nil;
}
export_cefunk0(lick__core_extension_destroy, 0, "");


