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
#include "../semantic_knowledge_base/semantic_knowledge_base.h"
#include "meta_semantic_knowledge_base.h"





// meta_semantic_frame

f2ptr raw__meta_semantic_frame__new(f2ptr cause, f2ptr realm) {
  f2ptr this = f2__semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_frame"));
  return this;
}

f2ptr f2__meta_semantic_frame__new(f2ptr cause, f2ptr realm) {
  return raw__meta_semantic_frame__new(cause, realm);
}
export_cefunk1(meta_semantic_frame__new, realm, 0, "Returns a new meta_semantic_frame object.");


boolean_t raw__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_frame");
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

f2ptr f2__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_frame__is_type(cause, thing));
}
export_cefunk1(meta_semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_frame.");


f2ptr raw__meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_frame__type(cause, this);
}
export_cefunk1(meta_semantic_frame__type, thing, 0, "Returns the specific type of object that this meta_semantic_frame is.");


f2ptr f2__meta_semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_frame__type")));}
  return this;
}



// meta_semantic_knowledge_base

f2ptr raw__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  f2ptr this = f2__semantic_knowledge_base__new(cause, semantic_frames);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "meta_semantic_knowledge_base"));
  return this;
}

f2ptr f2__meta_semantic_knowledge_base__new(f2ptr cause, f2ptr semantic_frames) {
  return raw__meta_semantic_knowledge_base__new(cause, semantic_frames);
}
export_cefunk1(meta_semantic_knowledge_base__new, semantic_frames, 0, "Returns a new meta_semantic_knowledge_base object.");


boolean_t raw__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "meta_semantic_knowledge_base");
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

f2ptr f2__meta_semantic_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__meta_semantic_knowledge_base__is_type(cause, thing));
}
export_cefunk1(meta_semantic_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type meta_semantic_knowledge_base.");


f2ptr raw__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__meta_semantic_knowledge_base__type(f2ptr cause, f2ptr this) {
  if (! raw__meta_semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__meta_semantic_knowledge_base__type(cause, this);
}
export_cefunk1(meta_semantic_knowledge_base__type, thing, 0, "Returns the specific type of object that this meta_semantic_knowledge_base is.");


f2ptr f2__meta_semantic_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "meta_semantic_knowledge_base__type")));}
  return this;
}



// relationship_meta_semantic_frame

f2ptr raw__relationship_meta_semantic_frame__new(f2ptr cause, f2ptr realm, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target) {
  f2ptr this = f2__meta_semantic_frame__new(cause, realm);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "relationship_meta_semantic_frame"));
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "source"),   source);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "key_type"), key_type);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "key"),      key);
  raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "target"),   target);
  return this;
}

f2ptr f2__relationship_meta_semantic_frame__new(f2ptr cause, f2ptr realm, f2ptr relationship__source, f2ptr relationship__key_type, f2ptr relationship__key, f2ptr relationship__target) {
  return raw__relationship_meta_semantic_frame__new(cause, realm, relationship__source, relationship__key_type, relationship__key, relationship__target);
}
export_cefunk5(relationship_meta_semantic_frame__new, realm, relationship__source, relationship__key_type, relationship__key, relationship__target, 0, "Returns a new relationship_meta_semantic_frame object.");


boolean_t raw__relationship_meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "relationship_meta_semantic_frame");
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

f2ptr f2__relationship_meta_semantic_frame__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__relationship_meta_semantic_frame__is_type(cause, thing));
}
export_cefunk1(relationship_meta_semantic_frame__is_type, thing, 0, "Returns whether or not thing is of type relationship_meta_semantic_frame.");


f2ptr raw__relationship_meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__relationship_meta_semantic_frame__type(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_frame__type(cause, this);
}
export_cefunk1(relationship_meta_semantic_frame__type, thing, 0, "Returns the specific type of object that this relationship_meta_semantic_frame is.");



f2ptr raw__relationship_meta_semantic_frame__source(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_single_value(cause, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "source"));
}

f2ptr f2__relationship_meta_semantic_frame__source(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_frame__source(cause, this);
}
export_cefunk1(relationship_meta_semantic_frame__source, this, 0, "Returns the source for this relationship_meta_semantic_frame.");



f2ptr raw__relationship_meta_semantic_frame__key_type(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_single_value(cause, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "key_type"));
}

f2ptr f2__relationship_meta_semantic_frame__key_type(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_frame__key_type(cause, this);
}
export_cefunk1(relationship_meta_semantic_frame__key_type, this, 0, "Returns the key_type for this relationship_meta_semantic_frame.");



f2ptr raw__relationship_meta_semantic_frame__key(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_single_value(cause, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "key"));
}

f2ptr f2__relationship_meta_semantic_frame__key(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_frame__key(cause, this);
}
export_cefunk1(relationship_meta_semantic_frame__key, this, 0, "Returns the key for this relationship_meta_semantic_frame.");



f2ptr raw__relationship_meta_semantic_frame__target(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_single_value(cause, new__symbol(cause, "relationship_meta_semantic_frame"), new__symbol(cause, "target"));
}

f2ptr f2__relationship_meta_semantic_frame__target(f2ptr cause, f2ptr this) {
  if (! raw__relationship_meta_semantic_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__relationship_meta_semantic_frame__target(cause, this);
}
export_cefunk1(relationship_meta_semantic_frame__target, this, 0, "Returns the target for this relationship_meta_semantic_frame.");



f2ptr f2__relationship_meta_semantic_frame_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "meta_semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),      f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),  f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "source"),   f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__source")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),      f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "target"),   f2__core_extension_funk__new(cause, new__symbol(cause, "meta_semantic_knowledge_base"), new__symbol(cause, "relationship_meta_semantic_frame__target")));}
  return this;
}





// **

f2ptr f2__meta_semantic_knowledge_base__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_ping, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension_initialize(f2ptr cause) {
  f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__core_extension_ping")), nil);
  f2__add_type(cause, new__symbol(cause, "meta_semantic_frame"),              f2__meta_semantic_frame_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "meta_semantic_knowledge_base"),     f2__meta_semantic_knowledge_base_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "relationship_meta_semantic_frame"), f2__relationship_meta_semantic_frame_type__new(cause));
  status("meta_semantic_knowledge_base initialized.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_initialize, 0, "");

f2ptr f2__meta_semantic_knowledge_base__core_extension_destroy(f2ptr cause) {
  status("\nmeta_semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(meta_semantic_knowledge_base__core_extension_destroy, 0, "");


