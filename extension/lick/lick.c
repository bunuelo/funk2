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

#include "lick.h"


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
      (! raw__integer__is_type(cause, lick_note)) ||
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


f2ptr raw__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  f2ptr lick_note = raw__lick_chunk__lick_note(cause, this);
  f2ptr unlicked_object_with_notes = raw__ptypehash__lookup(cause, object_note_hash, lick_note);
  if (unlicked_object_with_notes == nil) {
    f2ptr type_name = raw__lick_chunk__type_name(cause, this);
    f2ptr type      = f2__lookup_type(cause, type_name);
    if (raw__larva__is_type(cause, type)) {
      return type;
    }
    f2ptr lick_chunk__unlick_with_notes__funk = f2__primobject_type__lookup_slot_type_funk(cause, type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"));
    if (raw__larva__is_type(cause, lick_chunk__unlick_with_notes__funk)) {
      return lick_chunk__unlick_with_notes__funk;
    }
    if (! raw__funkable__is_type(cause, lick_chunk__unlick_with_notes__funk)) {
      return f2larva__new(cause, 23444, nil);
    }
    unlicked_object_with_notes = f2__force_funk_apply(cause, f2__this__fiber(cause), lick_chunk__unlick_with_notes__funk, f2list2__new(cause, this, object_note_hash));
    if (raw__larva__is_type(cause, unlicked_object_with_notes)) {
      return unlicked_object_with_notes;
    }
    raw__ptypehash__add(cause, object_note_hash, lick_note, unlicked_object_with_notes);
  }
  return unlicked_object_with_notes;
}

f2ptr f2__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__unlick_with_notes(cause, this, object_note_hash);
}
export_cefunk2(lick_chunk__unlick_with_notes, this, object_note_hash, 0, "Unlicks this lick_chunk as an actual object, but with notes instead of sub-objects.");


f2ptr raw__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  f2ptr lick_note                  = raw__lick_chunk__lick_note(cause, this);
  f2ptr unlicked_object_with_notes = raw__ptypehash__lookup(cause, object_note_hash, lick_note);
  f2ptr type_name                  = raw__lick_chunk__type_name(cause, this);
  f2ptr type                       = f2__lookup_type(cause, type_name);
  if (raw__larva__is_type(cause, type)) {
    return type;
  }
  f2ptr lick_chunk__unlick_replace_notes_with_objects__funk = f2__primobject_type__lookup_slot_type_funk(cause, type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"));
  if (raw__larva__is_type(cause, lick_chunk__unlick_replace_notes_with_objects__funk)) {
    return lick_chunk__unlick_replace_notes_with_objects__funk;
  }
  if (! raw__funkable__is_type(cause, lick_chunk__unlick_replace_notes_with_objects__funk)) {
    return f2larva__new(cause, 23445, nil);
  }
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), lick_chunk__unlick_replace_notes_with_objects__funk, f2list3__new(cause, unlicked_object_with_notes, this, object_note_hash));
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return nil;
}

f2ptr f2__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick_chunk__unlick_replace_notes_with_objects(cause, this, object_note_hash);
}
export_cefunk2(lick_chunk__unlick_replace_notes_with_objects, this, object_note_hash, 0, "Unlicks this lick_chunk as an actual object, but with notes instead of sub-objects.");


f2ptr f2__lick_chunk_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type_name"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type_name")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "type_name"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__type_name__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "lick_note"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__lick_note")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "lick_note"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__lick_note__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__chunk__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__unlick_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick_chunk__unlick_replace_notes_with_objects")));}
  return this;
}


// object_list

f2ptr raw__object_list__lick_first_n_to_chunks(f2ptr cause, f2ptr these, f2ptr note_object_hash, f2ptr chunk_note_hash, f2ptr n) {
  s64   n__i  = f2integer__i(n, cause);
  s64   index = 0;
  f2ptr iter  = these;
  while ((iter != nil) && (index < n__i)) {
    if (! raw__cons__is_type(cause, iter)) {
      return f2larva__new(cause, 1, nil);
    }
    f2ptr object = f2__cons__car(cause, iter);
    {
      f2ptr lick_chunk = f2__object__execute(cause, object, new__symbol(cause, "lick_to_chunk"), f2list1__new(cause, note_object_hash));
      if (raw__larva__is_type(cause, lick_chunk)) {
	return lick_chunk;
      }
      f2ptr lick_chunk__note = f2__lick_chunk__lick_note(cause, lick_chunk);
      if (raw__larva__is_type(cause, lick_chunk__note)) {
	return lick_chunk__note;
      }
      raw__ptypehash__add(cause, chunk_note_hash, lick_chunk__note, lick_chunk);
    }
    index ++;
    iter = f2__cons__cdr(cause, iter);
  }
  return iter;
}

f2ptr f2__object_list__lick_first_n_to_chunks(f2ptr cause, f2ptr these, f2ptr note_object_hash, f2ptr chunk_note_hash, f2ptr n) {
  if ((! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__ptypehash__is_type(cause, chunk_note_hash)) ||
      (! raw__integer__is_type(cause, n))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__object_list__lick_first_n_to_chunks(cause, these, note_object_hash, chunk_note_hash, n);
}
export_cefunk4(object_list__lick_first_n_to_chunks, these, note_object_hash, chunk_note_hash, n, 0, "Helper funktion for quickly licking objects to lick_chunks.");


// lick

f2ptr raw__lick__new(f2ptr cause, f2ptr root_note, f2ptr chunk_note_hash, f2ptr current_size) {
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),            new__symbol(cause, "lick"),
					    new__symbol(cause, "root_note"),       root_note,
					    new__symbol(cause, "chunk_note_hash"), chunk_note_hash,
					    new__symbol(cause, "current_size"),    current_size));
}

f2ptr raw__lick__new_from_object(f2ptr cause, f2ptr root_object) {
  f2ptr chunk_note_hash = f2__ptypehash__new(cause);
  f2ptr current_size    = f2integer__new(cause, 0);
  f2ptr root_note       = f2integer__new(cause, (s64)root_object);
  f2ptr this            = raw__lick__new(cause, root_note, chunk_note_hash, current_size);
  return this;
}

f2ptr f2__lick__new_from_object(f2ptr cause, f2ptr root_object) {
  return raw__lick__new_from_object(cause, root_object);
}

f2ptr f2__lick__new(f2ptr cause, f2ptr root_object) {
  return f2__lick__new_from_object(cause, root_object);
}
export_cefunk1(lick__new, root_object, 0, "Returns a new lick object.");


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


f2ptr raw__lick__current_size(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "current_size"), nil);
}

f2ptr f2__lick__current_size(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__current_size(cause, this);
}
export_cefunk1(lick__current_size, thing, 0, "Returns the current_size of the lick.");


f2ptr raw__lick__current_size__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "current_size"), value);
}

f2ptr f2__lick__current_size__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__current_size__set(cause, this, value);
}
export_cefunk2(lick__current_size__set, thing, value, 0, "Sets the current_size of the lick.");


f2ptr raw__lick__object__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr object, f2ptr note_object_hash, f2ptr max_size) {
  if (raw__eq(cause, object, global_environment())) {
    printf("\nlick__object__gather_lick_notes larva for finding global_environment type: ");
    f2__print(cause, f2__object__type(cause, object));
    fflush(stdout);
    return f2larva__new(cause, 234411, nil);
  }
  f2ptr current_size    = raw__lick__current_size(cause, this);
  s64   current_size__i = f2integer__i(current_size, cause);
  s64   max_size__i     = f2integer__i(max_size,     cause);
  if (current_size__i >= max_size__i) {
    return f2larva__new(cause, 244510, nil);
  }
  raw__lick__current_size__set(cause, this, f2integer__new(cause, current_size__i + 1));
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, object);
  if (lick_note == nil) {
    lick_note = f2integer__new(cause, (s64)object);
    raw__ptypehash__add(cause, note_object_hash, object, lick_note);
    f2ptr result = f2__object__execute(cause, object, new__symbol(cause, "gather_lick_notes"), f2list3__new(cause, this, note_object_hash, max_size));
    if (raw__larva__is_type(cause, result)) {
      printf("\nlick__object__gather_lick_notes larva in stack for object type: ");
      f2__print(cause, f2__object__type(cause, object));
      fflush(stdout);
      return result;
    }
  }
  return nil;
}

f2ptr f2__lick__object__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr object, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__lick__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__object__gather_lick_notes(cause, this, object, note_object_hash, max_size);
}
export_cefunk4(lick__object__gather_lick_notes, this, object, note_object_hash, max_size, 0, "Gather this lick's object's notes.");


f2ptr raw__lick__unlick(f2ptr cause, f2ptr this) {
  f2ptr chunk_note_hash  = raw__lick__chunk_note_hash(cause, this);
  f2ptr object_note_hash = f2__ptypehash__new(cause);
  ptypehash__iteration(cause, chunk_note_hash, note, lick_chunk,
		       f2ptr object = raw__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
		       if (raw__larva__is_type(cause, object)) {
			 return object;
		       }
		       raw__ptypehash__add(cause, object_note_hash, note, object);
		       );
  ptypehash__value__iteration(cause, chunk_note_hash, lick_chunk,
			      f2ptr result = raw__lick_chunk__unlick_replace_notes_with_objects(cause, lick_chunk, object_note_hash);
			      if (raw__larva__is_type(cause, result)) {
				return result;
			      }
			      );
  f2ptr root_note = raw__lick__root_note(cause, this);
  return raw__ptypehash__lookup(cause, object_note_hash, root_note);
}

f2ptr f2__lick__unlick(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__unlick(cause, this);
}
export_cefunk1(lick__unlick, this, 0, "Unlick this lick.");


f2ptr raw__lick__chunk_length(f2ptr cause, f2ptr this) {
  s64   chunk_length    = 8; // root_note
  f2ptr chunk_note_hash = raw__lick__chunk_note_hash(cause, this);
  ptypehash__value__iteration(cause, chunk_note_hash, lick_chunk,
			      chunk_length += 8; // lick_note
			      f2ptr type_name = raw__lick_chunk__type_name(cause, lick_chunk);
			      chunk_length += 8; // type_name__length 
			      if (type_name == nil) {
				chunk_length += 0; // type_name__str
			      } else if (raw__symbol__is_type(cause, type_name)) {
				chunk_length += (raw__symbol__length(cause, type_name) * 4);
			      } else {
				return f2larva__new(cause, 13251, nil);
			      }
			      chunk_length += 8; // chunk__length
			      f2ptr chunk = raw__lick_chunk__chunk(cause, lick_chunk);
			      chunk_length += raw__chunk__length(cause, chunk);
			      );
  return f2integer__new(cause, chunk_length);
}

f2ptr f2__lick__chunk_length(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__chunk_length(cause, this);
}
export_cefunk1(lick__chunk_length, this, 0, "Returns the length of this lick as a chunk.");


f2ptr raw__lick__as__chunk(f2ptr cause, f2ptr this) {
  f2ptr chunk_length = raw__lick__chunk_length(cause, this);
  if (raw__larva__is_type(cause, chunk_length)) {
    return chunk_length;
  }
  s64 chunk_length__i = f2integer__i(chunk_length, cause);
  f2ptr chunk = raw__chunk__new(cause, chunk_length__i);
  s64   chunk_index = 0;
  {
    f2ptr root_note = raw__lick__root_note(cause, this);
    s64   root_note__i = f2integer__i(root_note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, root_note__i);
    chunk_index += 8;
  }
  f2ptr chunk_note_hash = raw__lick__chunk_note_hash(cause, this);
  ptypehash__value__iteration(cause, chunk_note_hash, lick_chunk,
			      {
				f2ptr lick_note = raw__lick_chunk__lick_note(cause, lick_chunk);
				s64   lick_note__i = f2integer__i(lick_note, cause);
				raw__chunk__bit64__elt__set(cause, chunk, chunk_index, lick_note__i);
				chunk_index += 8;
			      }
			      f2ptr type_name = raw__lick_chunk__type_name(cause, lick_chunk);
			      {
				s64 type_name__length;
				if (type_name == nil) {
				  type_name__length = 0;
				} else if (raw__symbol__is_type(cause, type_name)) {
				  type_name__length = raw__symbol__length(cause, type_name);
				} else {
				  return f2larva__new(cause, 13250, nil);
				}
				raw__chunk__bit64__elt__set(cause, chunk, chunk_index, type_name__length);
				chunk_index += 8;
			      }
			      if (raw__symbol__is_type(cause, type_name)) {
				s64                type_name__length = raw__symbol__length(cause, type_name);
				funk2_character_t* type_name__str    = (funk2_character_t*)from_ptr(f2__malloc(type_name__length * sizeof(funk2_character_t)));
				raw__symbol__str_copy(cause, type_name, type_name__str);
				{
				  s64 index;
				  for (index = 0; index < type_name__length; index ++) {
				    raw__chunk__bit32__elt__set(cause, chunk, chunk_index, type_name__str[index]); chunk_index += 4;
				  }
				}
				f2__free(to_ptr(type_name__str));
			      }
			      {
				f2ptr lick_chunk__chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
				s64   lick_chunk__chunk__length = raw__chunk__length(cause, lick_chunk__chunk);
				raw__chunk__bit64__elt__set(cause, chunk, chunk_index, lick_chunk__chunk__length);
				chunk_index += 8;
				{
				  u8* lick_chunk__chunk__str = (u8*)from_ptr(f2__malloc(lick_chunk__chunk__length));
				  raw__chunk__str_copy(cause, lick_chunk__chunk, lick_chunk__chunk__str);
				  {
				    s64 index;
				    for (index = 0; index < lick_chunk__chunk__length; index ++) {
				      raw__chunk__bit8__elt__set(cause, chunk, chunk_index, lick_chunk__chunk__str[index]); chunk_index ++;
				    }
				  }
				  f2__free(to_ptr(lick_chunk__chunk__str));
				}
			      }
			      );
  return chunk;
}

f2ptr f2__lick__as__chunk(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__as__chunk(cause, this);
}
export_cefunk1(lick__as__chunk, this, 0, "Returns this lick as a chunk.");


f2ptr raw__chunk__as__lick(f2ptr cause, f2ptr this) {
  s64 chunk__length = raw__chunk__length(cause, this);
  s64 chunk_index   = 0;
  if (chunk_index + 8 > chunk__length) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				   new__symbol(cause, "this"),     this));
  }
  s64   root_note__i = raw__chunk__bit64__elt(cause, this, chunk_index); chunk_index += 8;
  f2ptr root_note    = f2integer__new(cause, root_note__i);
  f2ptr chunk_note_hash = f2__ptypehash__new(cause);
  while (chunk_index < chunk__length) {
    if (chunk_index + 8 > chunk__length) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				     new__symbol(cause, "this"),     this));
    }
    s64   lick_note__i = raw__chunk__bit64__elt(cause, this, chunk_index); chunk_index += 8;
    f2ptr lick_note    = f2integer__new(cause, lick_note__i);
    
    if (chunk_index + 8 > chunk__length) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				     new__symbol(cause, "this"),     this));
    }
    s64   type_name__length = raw__chunk__bit64__elt(cause, this, chunk_index); chunk_index += 8;
    f2ptr type_name;
    if (type_name__length == 0) {
      type_name = nil;
    } else {
      if (chunk_index + (type_name__length * 4) > chunk__length) {
	return new__error(f2list4__new(cause,
				       new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				       new__symbol(cause, "this"),     this));
      }
      funk2_character_t* type_name__str = (funk2_character_t*)from_ptr(f2__malloc(type_name__length * sizeof(funk2_character_t)));
      {
	s64 index;
	for (index = 0; index < type_name__length; index ++) {
	  type_name__str[index] = raw__chunk__bit32__elt(cause, this, chunk_index); chunk_index += 4;
	}
      }
      type_name = f2symbol__new(cause, type_name__length, type_name__str);
      f2__free(to_ptr(type_name__str));
    }
    
    if (chunk_index + 8 > chunk__length) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				     new__symbol(cause, "this"),     this));
    }
    s64 lick_chunk__chunk__length = raw__chunk__bit64__elt(cause, this, chunk_index); chunk_index += 8;
    if (chunk_index + lick_chunk__chunk__length > chunk__length) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "chunk_index_overran_lick_chunk"),
				     new__symbol(cause, "this"),     this));
    }
    f2ptr lick_chunk__chunk = raw__chunk__new(cause, lick_chunk__chunk__length);
    {
      s64 index;
      for (index = 0; index < lick_chunk__chunk__length; index ++) {
	raw__chunk__bit8__elt__set(cause, lick_chunk__chunk, index, raw__chunk__bit8__elt(cause, this, chunk_index)); chunk_index ++;
      }
    }
    f2ptr lick_chunk = raw__lick_chunk__new(cause, type_name, lick_note, lick_chunk__chunk);
    raw__ptypehash__add(cause, chunk_note_hash, lick_note, lick_chunk);
  }
  if (chunk_index != chunk__length) {
    return f2larva__new(cause, 3, nil);
  }
  return raw__lick__new(cause, root_note, chunk_note_hash, nil);
}

f2ptr f2__chunk__as__lick(f2ptr cause, f2ptr this) {
  if (! raw__chunk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__as__lick(cause, this);
}
export_cefunk1(chunk__as__lick, this, 0, "Returns this chunk as a lick.");



f2ptr f2__lick_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "root_note"),                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__root_note")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "root_note"),                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__root_note__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk_note_hash"),          f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk_note_hash"),          f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "current_size"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__current_size")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "current_size"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__current_size__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "object-gather_lick_notes"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__object__gather_lick_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "unlick"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__unlick")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk_length"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_length")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-chunk"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__as__chunk")));}
  return this;
}


///////////////////////
// ptypes lick funks //
///////////////////////

// nil lick funks

f2ptr raw__nil__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__nil__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((this != nil) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(nil__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick_note from this nil.");


f2ptr raw__nil__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk = raw__chunk__new(cause, 0);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, nil, lick_note, chunk);
}

f2ptr f2__nil__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((this != nil) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(nil__lick_to_chunk, this, note_object_hash, 0, "Licks this nil.");


f2ptr raw__nil__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__nil__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(nil__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this nil lick_chunk with notes.");


f2ptr raw__nil__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__nil__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((this != nil) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__nil__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(nil__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this nil with notes.");


// integer lick funks

f2ptr raw__integer__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__integer__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(integer__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this integer.");


f2ptr raw__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 8);
  s64   this__i = f2integer__i(this, cause);
  raw__chunk__bit64__elt__set(cause, chunk, 0, this__i);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "integer"), lick_note, chunk);
}

f2ptr f2__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(integer__lick_to_chunk, this, note_object_hash, 0, "Licks this integer.");


f2ptr raw__integer__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk   = raw__lick_chunk__chunk(cause, lick_chunk);
  f2ptr integer = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  return integer;
}

f2ptr f2__integer__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(integer__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this integer lick_chunk with notes.");


f2ptr raw__integer__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__integer__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(integer__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this integer with notes.");


// float lick funks

f2ptr raw__float__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__float__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(float__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this float.");


f2ptr raw__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 4);
  float this__f = f2float__f(this, cause);
  u32*  data    = (u32*)(&this__f);
  raw__chunk__bit32__elt__set(cause, chunk, 0, *data);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "float"), lick_note, chunk);
}

f2ptr f2__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(float__lick_to_chunk, this, note_object_hash, 0, "Licks this float.");


f2ptr raw__float__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr  chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u32    data  = raw__chunk__bit32__elt(cause, chunk, 0);
  float* f_ptr = (float*)(&data);
  return f2float__new(cause, *f_ptr);
}

f2ptr f2__float__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(float__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this float lick_chunk with notes.");


f2ptr raw__float__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__float__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(float__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this float with notes.");


// double lick funks

f2ptr raw__double__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__double__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(double__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this double.");


f2ptr raw__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr  chunk    = raw__chunk__new(cause, 8);
  double this__d  = f2double__d(this, cause);
  u64    data;
  memcpy(&data, &this__d, sizeof(u64));
  raw__chunk__bit64__elt__set(cause, chunk, 0, data);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "double"), lick_note, chunk);
}

f2ptr f2__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(double__lick_to_chunk, this, note_object_hash, 0, "Licks this double.");


f2ptr raw__double__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr   chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u64     data  = raw__chunk__bit64__elt(cause, chunk, 0);
  double* d_ptr = (double*)(&data);
  return f2double__new(cause, *d_ptr);
}

f2ptr f2__double__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(double__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this double lick_chunk with notes.");


f2ptr raw__double__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__double__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(double__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this double with notes.");


// pointer lick funks

f2ptr raw__pointer__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__pointer__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(pointer__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this pointer.");


f2ptr raw__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk   = raw__chunk__new(cause, 8);
  u64   this__p = f2pointer__p(this, cause);
  raw__chunk__bit64__elt__set(cause, chunk, 0, this__p);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "pointer"), lick_note, chunk);
}

f2ptr f2__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(pointer__lick_to_chunk, this, note_object_hash, 0, "Licks this pointer.");


f2ptr raw__pointer__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk = raw__lick_chunk__chunk(cause, lick_chunk);
  u64   data  = raw__chunk__bit64__elt(cause, chunk, 0);
  return f2pointer__new(cause, *((u64*)(&data)));
}

f2ptr f2__pointer__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(pointer__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this pointer lick_chunk with notes.");


f2ptr raw__pointer__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__pointer__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(pointer__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this pointer with notes.");


// cmutex lick funks

f2ptr raw__cmutex__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__cmutex__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__cmutex__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cmutex__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(cmutex__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this cmutex.");


f2ptr raw__cmutex__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr     chunk           = raw__chunk__new(cause, 1);
  boolean_t this__is_locked = raw__cmutex__is_locked(cause, this);
  raw__chunk__bit8__elt__set(cause, chunk, 0, this__is_locked ? 0x01 : 0x00);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "cmutex"), lick_note, chunk);
}

f2ptr f2__cmutex__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__cmutex__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cmutex__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(cmutex__lick_to_chunk, this, note_object_hash, 0, "Licks this cmutex.");


f2ptr raw__cmutex__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr     chunk           = raw__lick_chunk__chunk(cause, lick_chunk);
  boolean_t this__is_locked = (raw__chunk__bit8__elt(cause, chunk, 0) & 0x01) ? boolean__true : boolean__false;
  f2ptr     this            = f2cmutex__new(cause);
  if (this__is_locked) {
    raw__cmutex__lock(cause, this);
  }
  return this;
}

f2ptr f2__cmutex__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cmutex__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(cmutex__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this cmutex lick_chunk with notes.");


f2ptr raw__cmutex__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__cmutex__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__cmutex__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cmutex__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(cmutex__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this cmutex with notes.");


// char lick funks

f2ptr raw__char__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__char__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__char__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__char__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(char__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this char.");


f2ptr raw__char__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk    = raw__chunk__new(cause, 8);
  u64   this__ch = raw__char__ch(cause, this);
  raw__chunk__bit64__elt__set(cause, chunk, 0, this__ch);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "char"), lick_note, chunk);
}

f2ptr f2__char__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__char__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__char__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(char__lick_to_chunk, this, note_object_hash, 0, "Licks this char.");


f2ptr raw__char__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk    = raw__lick_chunk__chunk(cause, lick_chunk);
  u64   this__ch = raw__chunk__bit64__elt(cause, chunk, 0);
  f2ptr this     = f2char__new(cause, this__ch);
  return this;
}

f2ptr f2__char__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__char__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(char__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this char lick_chunk with notes.");


f2ptr raw__char__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__char__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__char__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__char__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(char__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this char with notes.");


// string lick funks

f2ptr raw__string__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__string__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(string__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this string.");


f2ptr raw__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  s64                this__length = raw__string__length(cause, this);
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, this__str);
  f2ptr              chunk        = raw__chunk__new(cause, this__length * sizeof(funk2_character_t));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      raw__chunk__bit32__elt__set(cause, chunk, index * sizeof(funk2_character_t), this__str[index]);
    }
  }
  f2__free(to_ptr(this__str));
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "string"), lick_note, chunk);
}

f2ptr f2__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(string__lick_to_chunk, this, note_object_hash, 0, "Licks this string.");


f2ptr raw__string__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr              chunk        = raw__lick_chunk__chunk(cause, lick_chunk);
  s64                this__length = raw__chunk__length(cause, chunk) / sizeof(funk2_character_t);
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      this__str[index] = raw__chunk__bit32__elt(cause, chunk, index * sizeof(funk2_character_t));
    }
  }
  f2ptr this = f2string__new(cause, this__length, this__str);
  f2__free(to_ptr(this__str));
  return this;
}

f2ptr f2__string__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(string__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this string lick_chunk with notes.");


f2ptr raw__string__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__string__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(string__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this string with notes.");


// symbol lick funks

f2ptr raw__symbol__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__symbol__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(symbol__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this symbol.");


f2ptr raw__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  s64                this__length = raw__symbol__length(cause, this);
  f2ptr              chunk        = raw__chunk__new(cause, this__length * sizeof(funk2_character_t));
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__symbol__str_copy(cause, this, this__str);
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      raw__chunk__bit32__elt__set(cause, chunk, index * sizeof(funk2_character_t), this__str[index]);
    }
  }
  f2__free(to_ptr(this__str));
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "symbol"), lick_note, chunk);
}

f2ptr f2__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(symbol__lick_to_chunk, this, note_object_hash, 0, "Licks this symbol.");


f2ptr raw__symbol__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr              chunk        = raw__lick_chunk__chunk(cause, lick_chunk);
  s64                this__length = raw__chunk__length(cause, chunk) / sizeof(funk2_character_t);
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      this__str[index] = raw__chunk__bit32__elt(cause, chunk, index * sizeof(funk2_character_t));
    }
  }
  f2ptr this = f2symbol__new(cause, this__length, this__str);
  f2__free(to_ptr(this__str));
  return this;
}

f2ptr f2__symbol__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(symbol__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this symbol lick_chunk with notes.");


f2ptr raw__symbol__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__symbol__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(symbol__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this symbol with notes.");


// chunk lick funks

f2ptr raw__chunk__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  return nil;
}

f2ptr f2__chunk__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(chunk__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this chunk.");


f2ptr raw__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  s64   this__length = raw__chunk__length(cause, this);
  f2ptr chunk   = raw__chunk__new(cause, this__length);
  u8*   this__str = (u8*)from_ptr(f2__malloc(this__length));
  raw__chunk__str_copy(cause, this, this__str);
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      raw__chunk__bit8__elt__set(cause, chunk, index, this__str[index]);
    }
  }
  f2__free(to_ptr(this__str));
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, new__symbol(cause, "chunk"), lick_note, chunk);
}

f2ptr f2__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(chunk__lick_to_chunk, this, note_object_hash, 0, "Licks this chunk.");


f2ptr raw__chunk__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk        = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   this__length = raw__chunk__length(cause, chunk);
  u8*   this__str    = (u8*)from_ptr(f2__malloc(this__length));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      this__str[index] = raw__chunk__bit8__elt(cause, chunk, index);
    }
  }
  f2ptr this = f2chunk__new(cause, this__length, this__str);
  f2__free(to_ptr(this__str));
  return this;
}

f2ptr f2__chunk__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(chunk__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this chunk lick_chunk with notes.");


f2ptr raw__chunk__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  return nil;
}

f2ptr f2__chunk__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(chunk__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this chunk with notes.");


// cons lick funks

f2ptr raw__cons__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  {
    f2ptr element = raw__cons__car(cause, this);
    f2ptr result  = raw__lick__object__gather_lick_notes(cause, lick, element, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr element = raw__cons__cdr(cause, this);
    f2ptr result  = raw__lick__object__gather_lick_notes(cause, lick, element, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__cons__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  assert_argument_type(cons,      this);
  assert_argument_type(lick,      lick);
  assert_argument_type(ptypehash, node_object_hash);
  assert_argument_type(integer,   max_size);
  return raw__cons__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(cons__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this cons.");


f2ptr raw__cons__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk = raw__chunk__new(cause, 2 * 8);
  {
    f2ptr element       = raw__cons__car(cause, this, index);
    f2ptr element__note = raw__ptypehash__lookup(cause, note_object_hash, element);
    if (element__note == nil) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
				     new__symbol(cause, "element"),  element,
				     new__symbol(cause, "this"),     this));
    }
    s64 element__note__i = f2integer__i(element__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, index * 8, (s64)element__note__i);
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__cons__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  assert_argument_type(cons,      this);
  assert_argument_type(ptypehash, note_object_hash);
  return raw__cons__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(cons__lick_to_chunk, this, note_object_hash, 0, "Licks this cons.");


f2ptr raw__cons__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != (2 * 8)) {
    return f2larva__new(cause, 32555, nil);
  }
  
  f2ptr car = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0 << 3));
  f2ptr cdr = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 1 << 3));
  return raw__cons__new(cause, car, cdr);
}

f2ptr f2__cons__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(lick_chunk, lick_chunk);
  assert_argument_type(ptypehash,  object_note_hash);
  return raw__cons__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(cons__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this cons lick_chunk with notes.");


f2ptr raw__cons__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  {
    f2ptr lick_note = raw__cons__car(cause, this);
    f2ptr object    = raw__ptypehash__lookup(cause, object_note_hash, lick_note);
    raw__cons__car__set(cause, this, index, object);
  }
  {
    f2ptr lick_note = raw__cons__cdr(cause, this);
    f2ptr object    = raw__ptypehash__lookup(cause, object_note_hash, lick_note);
    raw__cons__cdr__set(cause, this, index, object);
  }
  return nil;
}

f2ptr f2__cons__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(cons,       this);
  assert_argument_type(lick_chunk, lick_chunk);
  assert_argument_type(ptypehash,  object_note_hash);
  return raw__cons__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(cons__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this cons with notes.");


// array lick funks

f2ptr raw__array__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  s64 this__length = raw__array__length(cause, this);
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr element = raw__array__elt(cause, this, index);
      f2ptr result  = raw__lick__object__gather_lick_notes(cause, lick, element, note_object_hash, max_size);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}

f2ptr f2__array__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(array__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this array.");


f2ptr raw__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  s64   this__length = raw__array__length(cause, this);
  f2ptr chunk        = raw__chunk__new(cause, this__length * 8);
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr element       = raw__array__elt(cause, this, index);
      f2ptr element__note = raw__ptypehash__lookup(cause, note_object_hash, element);
      if (element__note == nil) {
	return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															       new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															       new__symbol(cause, "element"),  element,
															       new__symbol(cause, "this"),     this))));
      }
      s64 element__note__i = f2integer__i(element__note, cause);
      raw__chunk__bit64__elt__set(cause, chunk, index * 8, (s64)element__note__i);
    }
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(array__lick_to_chunk, this, note_object_hash, 0, "Licks this array.");


f2ptr raw__array__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
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
      f2ptr lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, index << 3));
      raw__array__elt__set(cause, array, index, lick_note);
    }
  }
  return array;
}

f2ptr f2__array__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(array__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this array lick_chunk with notes.");


f2ptr raw__array__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  s64 array__length = raw__array__length(cause, this);
  {
    s64 index;
    for (index = 0; index < array__length; index ++) {
      f2ptr lick_note = raw__array__elt(cause, this, index);
      f2ptr object    = raw__ptypehash__lookup(cause, object_note_hash, lick_note);
      raw__array__elt__set(cause, this, index, object);
    }
  }
  return nil;
}

f2ptr f2__array__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(array__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this array with notes.");


// ptypehash lick funks

f2ptr raw__ptypehash__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  {
    f2ptr key_count = f2__ptypehash__key_count(cause, this);
    f2ptr result    = raw__lick__object__gather_lick_notes(cause, lick, key_count, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr bin_num_power = f2__ptypehash__bin_num_power(cause, this);
    f2ptr result        = raw__lick__object__gather_lick_notes(cause, lick, bin_num_power, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr bin_array = f2__ptypehash__bin_array(cause, this);
    f2ptr result    = raw__lick__object__gather_lick_notes(cause, lick, bin_array, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__ptypehash__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__ptypehash__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__ptypehash__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(ptypehash__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Gathers the lick note from this ptypehash.");


f2ptr raw__ptypehash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk = raw__chunk__new(cause, 8 * 3);
  {
    f2ptr key_count          = f2__ptypehash__key_count(cause, this);
    f2ptr key_count__note    = raw__ptypehash__lookup(cause, note_object_hash, key_count);
    if (key_count__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),  new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "key_count"), key_count,
															     new__symbol(cause, "this"),      this))));
    }
    s64   key_count__note__i = f2integer__i(key_count__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 0, (s64)key_count__note__i);
  }
  {
    f2ptr bin_num_power          = f2__ptypehash__bin_num_power(cause, this);
    f2ptr bin_num_power__note    = raw__ptypehash__lookup(cause, note_object_hash, bin_num_power);
    if (bin_num_power__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),      new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "bin_num_power"), bin_num_power,
															     new__symbol(cause, "this"),          this))));
    }
    s64   bin_num_power__note__i = f2integer__i(bin_num_power__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 8, (s64)bin_num_power__note__i);
  }
  {
    f2ptr bin_array          = f2__ptypehash__bin_array(cause, this);
    f2ptr bin_array__note    = raw__ptypehash__lookup(cause, note_object_hash, bin_array);
    if (bin_array__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),  new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "bin_array"), bin_array,
															     new__symbol(cause, "this"),      this))));
    }
    s64   bin_array__note__i = f2integer__i(bin_array__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, 16, (s64)bin_array__note__i);
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__ptypehash__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  if ((! raw__ptypehash__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__ptypehash__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(ptypehash__lick_to_chunk, this, note_object_hash, 0, "Licks this ptypehash.");


f2ptr raw__ptypehash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != (8 * 3)) {
    return f2larva__new(cause, 32555, nil);
  }
  f2ptr key_count__lick_note     = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  f2ptr bin_num_power__lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 8));
  f2ptr bin_array__lick_note     = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 16));
  f2ptr ptypehash = f2ptypehash__new(cause, f2__cmutex__new(cause), key_count__lick_note, bin_num_power__lick_note, bin_array__lick_note);
  return ptypehash;
}

f2ptr f2__ptypehash__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__ptypehash__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(ptypehash__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this ptypehash lick_chunk with notes.");


f2ptr raw__ptypehash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  {
    f2ptr key_count__lick_note = f2__ptypehash__key_count(cause, this);
    f2ptr key_count__object    = raw__ptypehash__lookup(cause, object_note_hash, key_count__lick_note);
    f2__ptypehash__key_count__set(cause, this, key_count__object);
  }
  {
    f2ptr bin_num_power__lick_note = f2__ptypehash__bin_num_power(cause, this);
    f2ptr bin_num_power__object    = raw__ptypehash__lookup(cause, object_note_hash, bin_num_power__lick_note);
    f2__ptypehash__bin_num_power__set(cause, this, bin_num_power__object);
  }
  {
    f2ptr bin_array__lick_note = f2__ptypehash__bin_array(cause, this);
    f2ptr bin_array__object    = raw__ptypehash__lookup(cause, object_note_hash, bin_array__lick_note);
    f2__ptypehash__bin_array__set(cause, this, bin_array__object);
  }
  return nil;
}

f2ptr f2__ptypehash__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__ptypehash__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__ptypehash__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(ptypehash__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this ptypehash with notes.");


// end of type lick funks

f2ptr raw__add_all_lick_to_chunk_to_ptypes(f2ptr cause) {
  {
    f2ptr nil_type = assert_value(f2__lookup_type(cause, nil));
    assert_value(f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, nil_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "nil__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr integer_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "integer")));
    assert_value(f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr float_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "float")));
    assert_value(f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr double_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "double")));
    assert_value(f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr pointer_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "pointer")));
    assert_value(f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr cmutex_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "cmutex")));
    assert_value(f2__primobject_type__add_slot_type(cause, cmutex_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cmutex__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cmutex_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cmutex__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cmutex_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cmutex__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cmutex_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cmutex__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr char_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "char")));
    assert_value(f2__primobject_type__add_slot_type(cause, char_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "char__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, char_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "char__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, char_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "char__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, char_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "char__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr string_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "string")));
    assert_value(f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr symbol_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "symbol")));
    assert_value(f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr chunk_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "chunk")));
    assert_value(f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_chunk__unlick_replace_notes_with_objects"))));
    assert_value(f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "get"),     new__symbol(cause, "as-lick"),                                      f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__as__lick"))));
  }
  {
    f2ptr cons_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "cons")));
    assert_value(f2__primobject_type__add_slot_type(cause, cons_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cons__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cons_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cons__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cons_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cons__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, cons_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "cons__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr simple_array_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "simple_array")));
    assert_value(f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr array_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "array")));
    assert_value(f2__primobject_type__add_slot_type(cause, array_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  {
    f2ptr ptypehash_type = assert_value(f2__lookup_type(cause, new__symbol(cause, "ptypehash")));
    assert_value(f2__primobject_type__add_slot_type(cause, ptypehash_type, new__symbol(cause, "execute"), new__symbol(cause, "gather_lick_notes"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "ptypehash__gather_lick_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, ptypehash_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "ptypehash__lick_to_chunk"))));
    assert_value(f2__primobject_type__add_slot_type(cause, ptypehash_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "ptypehash__lick_chunk__unlick_with_notes"))));
    assert_value(f2__primobject_type__add_slot_type(cause, ptypehash_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "ptypehash__lick_chunk__unlick_replace_notes_with_objects"))));
  }
  return nil;
}


// **

f2ptr f2__lick__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(lick__core_extension__ping, 0, "");

f2ptr f2__lick__core_extension__initialize(f2ptr cause) {
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
export_cefunk0(lick__core_extension__initialize, 0, "");

f2ptr f2__lick__core_extension__destroy(f2ptr cause) {
  status("lick destroyed.");
  return nil;
}
export_cefunk0(lick__core_extension__destroy, 0, "");


