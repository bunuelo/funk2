// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#include "semantic_resource.h"


// semantic_resource

f2ptr raw__semantic_resource__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__semantic_frame__new(cause, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_resource"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "type"), new__symbol(cause, "name"), new__symbol(cause, "semantic_resource"));
  raw__semantic_resource__current_action_sequence__add(cause, this, nil);
  return this;
}

f2ptr f2__semantic_resource__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__new(cause, semantic_realm);
}
export_cefunk1(semantic_resource__new, semantic_realm, 0, "Returns a new semantic_resource object.");


boolean_t raw__semantic_resource__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_resource");
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

f2ptr f2__semantic_resource__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_resource__is_type(cause, thing));
}
export_cefunk1(semantic_resource__is_type, thing, 0, "Returns whether or not thing is of type semantic_resource.");


f2ptr raw__semantic_resource__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_resource__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_resource__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__type(cause, this);
}
export_cefunk1(semantic_resource__type, thing, 0, "Returns the specific type of object that this semantic_resource is.");


f2ptr raw__semantic_resource__name__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup(cause, this, new__symbol(cause, "property"), new__symbol(cause, "name"));
}

f2ptr f2__semantic_resource__name__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_resource__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__name__lookup(cause, this);
}
export_cefunk1(semantic_resource__name__lookup, this, 0, "");


f2ptr raw__semantic_resource__name__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "name"), that);
}

f2ptr f2__semantic_resource__name__add(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__semantic_resource__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__name__add(cause, this, that);
}
export_cefunk2(semantic_resource__name__add, this, that, 0, "");


f2ptr raw__semantic_resource__name__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "property"), new__symbol(cause, "name"), that);
}

f2ptr f2__semantic_resource__name__remove(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__semantic_resource__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__name__remove(cause, this, that);
}
export_cefunk2(semantic_resource__name__remove, this, that, 0, "");


f2ptr raw__semantic_resource__current_action_sequence__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "current_action_sequence"));
}

f2ptr f2__semantic_resource__current_action_sequence__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_resource__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__current_action_sequence__lookup(cause, this);
}
export_cefunk1(semantic_resource__current_action_sequence__lookup, this, 0, "");


f2ptr raw__semantic_resource__current_action_sequence__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "current_action_sequence"), that);
}

f2ptr f2__semantic_resource__current_action_sequence__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_resource__is_type(cause, this)) ||
      ((that != nil) && (! raw__semantic_event_sequence__is_type(cause, that)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__current_action_sequence__add(cause, this, that);
}
export_cefunk2(semantic_resource__current_action_sequence__add, this, that, 0, "");


f2ptr raw__semantic_resource__current_action_sequence__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "current_action_sequence"), that);
}

f2ptr f2__semantic_resource__current_action_sequence__remove(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_resource__is_type(cause, this)) ||
      ((that != nil) && (! raw__semantic_event_sequence__is_type(cause, that)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource__current_action_sequence__remove(cause, this, that);
}
export_cefunk2(semantic_resource__current_action_sequence__remove, this, that, 0, "");


f2ptr f2__semantic_resource_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol,     new__symbol(cause, "new"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol,     new__symbol(cause, "is_type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,         new__symbol(cause, "type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup"), new__symbol(cause, "name"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__name__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "name"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__name__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "name"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__name__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup"), new__symbol(cause, "current_action_sequence"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__current_action_sequence__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "current_action_sequence"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__current_action_sequence__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "current_action_sequence"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource"), new__symbol(cause, "semantic_resource__current_action_sequence__remove")));}
  return this;
}


// **

f2ptr f2__semantic_resource__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_resource__core_extension_ping, 0, "");

f2ptr f2__semantic_resource__core_extension_initialize(f2ptr cause) {
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__core_extension_ping")), nil);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2__add_type(cause, new__symbol(cause, "semantic_resource"), f2__semantic_resource_type__new(cause));
  status("semantic_resource initialized.");
  return nil;
}
export_cefunk0(semantic_resource__core_extension_initialize, 0, "");

f2ptr f2__semantic_resource__core_extension_destroy(f2ptr cause) {
  status("semantic_resource destroyed.");
  return nil;
}
export_cefunk0(semantic_resource__core_extension_destroy, 0, "");


