// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#include "semantic_directed_action_event.h"


// semantic_directed_action_event

f2ptr raw__semantic_directed_action_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name, f2ptr agent, f2ptr target) {
  f2ptr this = f2__semantic_action_event__new(cause, semantic_realm, action_name, agent);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_directed_action_event"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "target"), target);
  return this;
}

f2ptr f2__semantic_directed_action_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name, f2ptr agent, f2ptr target) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_directed_action_event__new(cause, semantic_realm, action_name, agent, target);
}
export_cefunk4(semantic_directed_action_event__new, semantic_realm, action_name, agent, target, 0, "Returns a new semantic_directed_action_event object.");


boolean_t raw__semantic_directed_action_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_directed_action_event");
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

f2ptr f2__semantic_directed_action_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_directed_action_event__is_type(cause, thing));
}
export_cefunk1(semantic_directed_action_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_directed_action_event.");


f2ptr raw__semantic_directed_action_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_directed_action_event__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_directed_action_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_directed_action_event__type(cause, this);
}
export_cefunk1(semantic_directed_action_event__type, thing, 0, "Returns the specific type of object that this semantic_directed_action_event is.");


f2ptr raw__semantic_directed_action_event__target(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "target"));
}

f2ptr f2__semantic_directed_action_event__target(f2ptr cause, f2ptr this) {
  if (! raw__semantic_directed_action_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_directed_action_event__target(cause, this);
}
export_cefunk1(semantic_directed_action_event__target, this, 0, "");


f2ptr raw__semantic_directed_action_event__target__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "target"), that);
}

f2ptr f2__semantic_directed_action_event__target__set(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_directed_action_event__is_type(cause, this)) ||
      (! raw__semantic_frame__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_directed_action_event__target__set(cause, this, that);
}
export_cefunk2(semantic_directed_action_event__target__set, this, that, 0, "");


f2ptr f2__semantic_directed_action_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_action_event")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_directed_action_event"), new__symbol(cause, "semantic_directed_action_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_directed_action_event"), new__symbol(cause, "semantic_directed_action_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_directed_action_event"), new__symbol(cause, "semantic_directed_action_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "target"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_directed_action_event"), new__symbol(cause, "semantic_directed_action_event__target")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "target"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_directed_action_event"), new__symbol(cause, "semantic_directed_action_event__target__set")));}
  return this;
}



// **

f2ptr f2__semantic_directed_action_event__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_directed_action_event__core_extension__ping, 0, "");

f2ptr f2__semantic_directed_action_event__core_extension__initialize(f2ptr cause) {
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_action_event"), new__symbol(cause, "semantic_action_event__core_extension__ping")), nil);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2__add_type(cause, new__symbol(cause, "semantic_directed_action_event"), f2__semantic_directed_action_event_type__new(cause));
  status("semantic_directed_action_event initialized.");
  return nil;
}
export_cefunk0(semantic_directed_action_event__core_extension__initialize, 0, "");

f2ptr f2__semantic_directed_action_event__core_extension__destroy(f2ptr cause) {
  status("semantic_directed_action_event destroyed.");
  return nil;
}
export_cefunk0(semantic_directed_action_event__core_extension__destroy, 0, "");


