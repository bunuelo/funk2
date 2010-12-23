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

f2ptr raw__lick_note__new(f2ptr cause, f2ptr object) {
  f2ptr unique_identifier = f2integer__new(cause, (s64)object);
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),              new__symbol(cause, "lick_note"),
					    new__symbol(cause, "unique_identifier"), unique_identifier));
}

f2ptr f2__lick_note__new(f2ptr cause, f2ptr object) {
  return raw__lick_note__new(cause, object);
}
export_cefunk1(lick_note__new, object, 0, "Given any object, returns a unique lick_note object identifier.");


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


// lick

f2ptr raw__lick__new(f2ptr cause, f2ptr root_object) {
  f2ptr note_object_hash = f2__ptypehash__new(cause);
  f2ptr chunk_note_hash  = f2__ptypehash__new(cause);
  f2ptr this = f2__frame__new(cause, f2list8__new(cause,
						  new__symbol(cause, "type"),             new__symbol(cause, "lick"),
						  new__symbol(cause, "root_note"),        nil,
						  new__symbol(cause, "note_object_hash"), note_object_hash,
						  new__symbol(cause, "chunk_note_hash"),  chunk_note_hash));
  f2ptr root_note = raw__lick__object__as__note(cause, this, root_object);
  if (raw__larva__is_type(cause, root_note)) {
    return result;
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


f2ptr raw__lick__note_object_hash(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "note_object_hash"), nil);
}

f2ptr f2__lick__note_object_hash(f2ptr cause, f2ptr this) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__note_object_hash(cause, this);
}
export_cefunk1(lick__note_object_hash, thing, 0, "Returns the note_object_hash of the lick.");


f2ptr raw__lick__note_object_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "note_object_hash"), value);
}

f2ptr f2__lick__note_object_hash__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__note_object_hash__set(cause, this, value);
}
export_cefunk2(lick__note_object_hash__set, thing, value, 0, "Sets the note_object_hash of the lick.");


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


f2ptr raw__lick__object__as__note(f2ptr cause, f2ptr this, f2ptr object) {
  f2ptr note_object_hash = raw__lick__note_object_hash(cause, this);
  f2ptr note             = raw__ptypehash__lookup(cause, note_object_hash, object);
  if (note == nil) {
    note = f2__lick_note__new(cause, object);
    if (raw__larva__is_type(cause, note)) {
      return note;
    }
    raw__ptypehash__add(cause, note_object_hash, object, note);
    f2ptr chunk = f2__object__execute(cause, root_object, new__symbol(cause, "lick_to_chunk"), f2list1__new(cause, this));
    if (raw__larva__is_type(cause, chunk)) {
      return chunk;
    }
    f2ptr chunk_note_hash = raw__lick__chunk_note_hash(cause, this);
    f2ptr unique_indentifier = raw__lick_note__unique_identifier(cause, note);
    raw__ptypehash__add(cause, chunk_note_hash, unique_identifier, chunk);
  }
  return note;
}

f2ptr f2__lick__object__as__note(f2ptr cause, f2ptr this, f2ptr object) {
  if (! raw__lick__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__lick__object__as__note(cause, this, object);
}
export_cefunk2(lick__object__as__note, this, object, 0, "Get this lick's object as note.");



f2ptr f2__lick_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),              f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),          f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "note_object_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__note_object_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "note_object_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__note_object_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk_note_hash"),  f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk_note_hash"),  f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "object__as__note"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__object__as__note")));}
  return this;
}


// ptype lick_to_chunk funks

//   integer lick_to_chunk

f2ptr raw__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__integer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__integer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__integer__lick_to_chunk(cause, this, lick);
}
export_cefunk2(integer__lick_to_chunk, this, lick, 0, "Licks this integer.");


//   float lick_to_chunk

f2ptr raw__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__float__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__float__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__float__lick_to_chunk(cause, this, lick);
}
export_cefunk2(float__lick_to_chunk, this, lick, 0, "Licks this float.");


//   double lick_to_chunk

f2ptr raw__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__double__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__double__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__double__lick_to_chunk(cause, this, lick);
}
export_cefunk2(double__lick_to_chunk, this, lick, 0, "Licks this double.");


//   pointer lick_to_chunk

f2ptr raw__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__pointer__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__pointer__lick_to_chunk(cause, this, lick);
}
export_cefunk2(pointer__lick_to_chunk, this, lick, 0, "Licks this pointer.");


//   string lick_to_chunk

f2ptr raw__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__string__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__lick_to_chunk(cause, this, lick);
}
export_cefunk2(string__lick_to_chunk, this, lick, 0, "Licks this string.");


//   symbol lick_to_chunk

f2ptr raw__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__symbol__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__symbol__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__symbol__lick_to_chunk(cause, this, lick);
}
export_cefunk2(symbol__lick_to_chunk, this, lick, 0, "Licks this symbol.");


//   chunk lick_to_chunk

f2ptr raw__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__chunk__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__lick_to_chunk(cause, this, lick);
}
export_cefunk2(chunk__lick_to_chunk, this, lick, 0, "Licks this chunk.");


//   array lick_to_chunk

f2ptr raw__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  return nil;
}

f2ptr f2__array__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__lick_to_chunk(cause, this, lick);
}
export_cefunk2(array__lick_to_chunk, this, lick, 0, "Licks this array.");


f2ptr raw__add_all_lick_to_chunk_to_ptypes(f2ptr cause) {
  {
    f2ptr integer_type = f2__lookup_type(cause, new__symbol(cause, "integer"));
    if (raw__larva__is_type(cause, integer_type)) {
      return integer_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, integer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "integer__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr float_type = f2__lookup_type(cause, new__symbol(cause, "float"));
    if (raw__larva__is_type(cause, float_type)) {
      return float_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, float_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "float__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr double_type = f2__lookup_type(cause, new__symbol(cause, "double"));
    if (raw__larva__is_type(cause, double_type)) {
      return double_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, double_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "double__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr pointer_type = f2__lookup_type(cause, new__symbol(cause, "pointer"));
    if (raw__larva__is_type(cause, pointer_type)) {
      return pointer_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, pointer_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "pointer__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr string_type = f2__lookup_type(cause, new__symbol(cause, "string"));
    if (raw__larva__is_type(cause, string_type)) {
      return string_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, string_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "string__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr symbol_type = f2__lookup_type(cause, new__symbol(cause, "symbol"));
    if (raw__larva__is_type(cause, symbol_type)) {
      return symbol_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, symbol_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "symbol__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr chunk_type = f2__lookup_type(cause, new__symbol(cause, "chunk"));
    if (raw__larva__is_type(cause, chunk_type)) {
      return chunk_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, chunk_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "chunk__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr simple_array_type = f2__lookup_type(cause, new__symbol(cause, "simple_array"));
    if (raw__larva__is_type(cause, simple_array_type)) {
      return simple_array_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, simple_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr traced_array_type = f2__lookup_type(cause, new__symbol(cause, "traced_array"));
    if (raw__larva__is_type(cause, traced_array_type)) {
      return traced_array_type;
    }
    f2ptr result = f2__primobject_type__add_slot_type(cause, traced_array_type, new__symbol(cause, "execute"), new__symbol(cause, "lick_to_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "array__lick_to_chunk")));
    if (raw__larva__is_type(cause, result)) {
      return result;
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
  f2__add_type(cause, new__symbol(cause, "lick_note"), f2__lick_note_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "lick"),      f2__lick_type__new(cause));
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


