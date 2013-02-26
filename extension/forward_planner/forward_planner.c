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

#include "../../c/funk2.h"


// forward_planner_action

f2ptr raw__forward_planner_action__new(f2ptr cause, f2ptr precondition_funk, f2ptr transition_funk) {
  return f2__frame__new(cause, f2list6__new(cause,
					    new__symbol(cause, "type"),              new__symbol(cause, "forward_planner_action"),
					    new__symbol(cause, "transition_funk"),   transition_funk,
					    new__symbol(cause, "precondition_funk"), precondition_funk));
}

f2ptr f2__forward_planner_action__new(f2ptr cause, f2ptr precondition_funk, f2ptr transition_funk) {
  if ((! raw__funkable__is_type(cause, precondition_funk)) ||
      (! raw__funkable__is_type(cause, transition_funk))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__new(cause, precondition_funk, transition_funk);
}
export_cefunk2(forward_planner_action__new, precondition_funk, transition_funk, 0, "Returns a new forward_planner_action object.");


boolean_t raw__forward_planner_action__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "forward_planner_action");
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

f2ptr f2__forward_planner_action__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__forward_planner_action__is_type(cause, thing));
}
export_cefunk1(forward_planner_action__is_type, thing, 0, "Returns whether or not thing is of type forward_planner_action.");


f2ptr raw__forward_planner_action__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__forward_planner_action__type(f2ptr cause, f2ptr this) {
  if (! raw__forward_planner_action__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__type(cause, this);
}
export_cefunk1(forward_planner_action__type, thing, 0, "Returns the specific type of object that this forward_planner_action is.");


f2ptr raw__forward_planner_action__precondition_funk(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "precondition_funk"), nil);
}

f2ptr f2__forward_planner_action__precondition_funk(f2ptr cause, f2ptr this) {
  if (! raw__forward_planner_action__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__precondition_funk(cause, this);
}
export_cefunk1(forward_planner_action__precondition_funk, thing, 0, "Returns the precondition_funk of the forward_planner_action.");


f2ptr raw__forward_planner_action__precondition_funk__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "precondition_funk"), value);
}

f2ptr f2__forward_planner_action__precondition_funk__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__forward_planner_action__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__precondition_funk__set(cause, this, value);
}
export_cefunk2(forward_planner_action__precondition_funk__set, thing, value, 0, "Sets the precondition_funk of the forward_planner_action.");


f2ptr raw__forward_planner_action__transition_funk(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "transition_funk"), nil);
}

f2ptr f2__forward_planner_action__transition_funk(f2ptr cause, f2ptr this) {
  if (! raw__forward_planner_action__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__transition_funk(cause, this);
}
export_cefunk1(forward_planner_action__transition_funk, thing, 0, "Returns the transition_funk of the forward_planner_action.");


f2ptr raw__forward_planner_action__transition_funk__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "transition_funk"), value);
}

f2ptr f2__forward_planner_action__transition_funk__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__forward_planner_action__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner_action__transition_funk__set(cause, this, value);
}
export_cefunk2(forward_planner_action__transition_funk__set, thing, value, 0, "Sets the transition_funk of the forward_planner_action.");


f2ptr f2__forward_planner_action_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),               f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "precondition_funk"), f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__precondition_funk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "precondition_funk"), f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__precondition_funk__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "transition_funk"),   f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__transition_funk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "transition_funk"),   f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner_action__transition_funk__set")));}
  return this;
}


// forward_planner

f2ptr raw__forward_planner__new(f2ptr cause, f2ptr action_set) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),       new__symbol(cause, "forward_planner"),
					    new__symbol(cause, "action_set"), action_set));
}

f2ptr f2__forward_planner__new(f2ptr cause, f2ptr action_set) {
  if (! raw__set__is_type(cause, action_set)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner__new(cause, action_set);
}
export_cefunk1(forward_planner__new, images, 0, "Returns a new forward_planner object.");


boolean_t raw__forward_planner__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "forward_planner");
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

f2ptr f2__forward_planner__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__forward_planner__is_type(cause, thing));
}
export_cefunk1(forward_planner__is_type, thing, 0, "Returns whether or not thing is of type forward_planner.");


f2ptr raw__forward_planner__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__forward_planner__type(f2ptr cause, f2ptr this) {
  if (! raw__forward_planner__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner__type(cause, this);
}
export_cefunk1(forward_planner__type, thing, 0, "Returns the specific type of object that this forward_planner is.");


f2ptr raw__forward_planner__action_set(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "action_set"), nil);
}

f2ptr f2__forward_planner__action_set(f2ptr cause, f2ptr this) {
  if (! raw__forward_planner__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner__action_set(cause, this);
}
export_cefunk1(forward_planner__action_set, thing, 0, "Returns the action_set of the forward_planner.");


f2ptr raw__forward_planner__action_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "action_set"), value);
}

f2ptr f2__forward_planner__action_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__forward_planner__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__forward_planner__action_set__set(cause, this, value);
}
export_cefunk2(forward_planner__action_set__set, thing, value, 0, "Sets the action_set of the forward_planner.");


f2ptr f2__forward_planner_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),        f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "action_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner__action_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "action_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "forward_planner"), new__symbol(cause, "forward_planner__action_set__set")));}
  return this;
}


// **

f2ptr f2__forward_planner__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(forward_planner__core_extension__ping, 0, "");

f2ptr f2__forward_planner__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "forward_planner_action"), f2__forward_planner_action_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "forward_planner"),        f2__forward_planner_type__new(cause));
  printf("\nforward_planner initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(forward_planner__core_extension__initialize, 0, "");

f2ptr f2__forward_planner__core_extension__destroy(f2ptr cause) {
  printf("\nforward_planner destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(forward_planner__core_extension__destroy, 0, "");


