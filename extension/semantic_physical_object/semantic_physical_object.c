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
#include "semantic_physical_object.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"


// semantic_physical_object

f2ptr raw__semantic_physical_object__new(f2ptr cause, f2ptr source) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),   new__symbol(cause, "semantic_physical_object"),
					    new__symbol(cause, "source"), source));
}

f2ptr f2__semantic_physical_object__new(f2ptr cause, f2ptr source) {
  return raw__semantic_physical_object__new(cause, source);
}
export_cefunk1(semantic_physical_object__new, source, 0, "Returns a new semantic_physical_object object.");


boolean_t raw__semantic_physical_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_physical_object");
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

f2ptr f2__semantic_physical_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_physical_object__is_type(cause, thing));
}
export_cefunk1(semantic_physical_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_physical_object.");


f2ptr raw__semantic_physical_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_physical_object__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_physical_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_physical_object__type(cause, this);
}
export_cefunk1(semantic_physical_object__type, thing, 0, "Returns the specific type of object that this semantic_physical_object is.");


f2ptr raw__semantic_physical_object__source(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "source"), nil);
}

f2ptr f2__semantic_physical_object__source(f2ptr cause, f2ptr this) {
  if (! raw__semantic_physical_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_physical_object__source(cause, this);
}
export_cefunk1(semantic_physical_object__source, thing, 0, "Returns the source of the semantic_physical_object.");


f2ptr raw__semantic_physical_object__source__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "source"), value);
}

f2ptr f2__semantic_physical_object__source__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__semantic_physical_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_physical_object__source__set(cause, this, value);
}
export_cefunk2(semantic_physical_object__source__set, thing, value, 0, "Sets the source of the semantic_physical_object.");


f2ptr f2__semantic_physical_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_physical_object"), new__symbol(cause, "semantic_physical_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_physical_object"), new__symbol(cause, "semantic_physical_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_physical_object"), new__symbol(cause, "semantic_physical_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "source"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_physical_object"), new__symbol(cause, "semantic_physical_object__source")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "source"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_physical_object"), new__symbol(cause, "semantic_physical_object__source__set")));}
  return this;
}





// **

f2ptr f2__semantic_physical_object__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_physical_object__core_extension_ping, 0, "");

f2ptr f2__semantic_physical_object__core_extension_initialize(f2ptr cause) {
  status("semantic_physical_object initialized.");
  return nil;
}
export_cefunk0(semantic_physical_object__core_extension_initialize, 0, "");

f2ptr f2__semantic_physical_object__core_extension_destroy(f2ptr cause) {
  status("semantic_physical_object destroyed.");
  return nil;
}
export_cefunk0(semantic_physical_object__core_extension_destroy, 0, "");


