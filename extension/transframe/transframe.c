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

#include "transframe.h"

def_ceframe5(transframe, transframe_change, change_type, change_object, change_slot_type, change_slot, change_target);

f2ptr raw__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target) {
  return f2transframe_change__new(cause, change_type, change_object, change_slot_type, change_slot, change_target);
}

f2ptr f2__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target) {
  return raw__transframe_change__new(cause, change_type, change_object, change_slot_type, change_slot, change_target);
}
export_cefunk5(transframe_change__new, change_type, change_object, change_slot_type, change_slot, change_target, 0, "Returns a new transframe_change object.");


f2ptr f2__transframe_change_type__new_aux(f2ptr cause) {
  f2ptr this = f2__transframe_change_type__new(cause);
  return this;
}



def_ceframe1(transframe, transframe, change_set);

f2ptr raw__transframe__new(f2ptr cause) {
  f2ptr change_set = f2__set__new(cause);
  return f2transframe__new(cause, change_set);
}

f2ptr f2__transframe__new(f2ptr cause) {
  return raw__transframe__new(cause);
}
export_cefunk0(transframe__new, 0, "Returns a new transframe object.");


f2ptr f2__transframe_type__new_aux(f2ptr cause) {
  f2ptr this = f2__transframe_type__new(cause);
  return this;
}



// **

f2ptr f2__transframe__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(transframe__core_extension__ping, 0, "");

f2ptr f2__transframe__core_extension__initialize(f2ptr cause) {
  status("transframe initialized.");
  return nil;
}
export_cefunk0(transframe__core_extension__initialize, 0, "");

f2ptr f2__transframe__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "transframe_change"), f2__transframe_change_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "transframe"),        f2__transframe_type__new_aux(cause));
  status("transframe types defined.");
  return nil;
}
export_cefunk0(transframe__core_extension__define_types, 0, "");

f2ptr f2__transframe__core_extension__destroy(f2ptr cause) {
  status("transframe destroyed.");
  return nil;
}
export_cefunk0(transframe__core_extension__destroy, 0, "");


