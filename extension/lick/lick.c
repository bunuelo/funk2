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
  f2ptr root_note = f2__lick_note__new(cause, root_object);
  if (raw__larva__is_type(cause, root_note)) {
    return root_note;
  }
  f2ptr chunk_note_hash = f2__ptypehash__new(cause);
  f2ptr this = f2__frame__new(cause, f2list6__new(cause,
						  new__symbol(cause, "type"),            new__symbol(cause, "lick"),
						  new__symbol(cause, "root_note"),       root_note,
						  new__symbol(cause, "chunk_note_hash"), chunk_note_hash));
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


f2ptr f2__lick_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "chunk_note_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "chunk_note_hash"), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__chunk_note_hash__set")));}
  return this;
}



// **

f2ptr f2__lick__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(lick__core_extension_ping, 0, "");

f2ptr f2__lick__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "lick_note"), f2__lick_note_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "lick"),      f2__lick_type__new(cause));
  status("lick initialized.");
  return nil;
}
export_cefunk0(lick__core_extension_initialize, 0, "");

f2ptr f2__lick__core_extension_destroy(f2ptr cause) {
  status("lick destroyed.");
  return nil;
}
export_cefunk0(lick__core_extension_destroy, 0, "");


