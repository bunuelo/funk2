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

#include "transframe.h"

// transframe_change_type

boolean_t raw__transframe_change_type__is_type(f2ptr cause, f2ptr object) {
  return (raw__eq(cause, object, new__symbol(cause, "add")) ||
	  raw__eq(cause, object, new__symbol(cause, "remove")));
}


// transframe_change

def_ceframe5(transframe, transframe_change, change_type, change_object, change_slot_type, change_slot, change_target);

f2ptr raw__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target) {
  return f2transframe_change__new(cause, change_type, change_object, change_slot_type, change_slot, change_target);
}

f2ptr f2__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target) {
  assert_argument_type(transframe_change_type, change_type);
  return raw__transframe_change__new(cause, change_type, change_object, change_slot_type, change_slot, change_target);
}
export_cefunk5(transframe_change__new, change_type, change_object, change_slot_type, change_slot, change_target, 0, "Returns a new transframe_change object.");


f2ptr raw__transframe_change__apply_to_knowledge_base(f2ptr cause, f2ptr this, f2ptr knowledge_base) {
  
  return nil;
}

f2ptr f2__transframe_change__apply_to_knowledge_base(f2ptr cause, f2ptr this, f2ptr knowledge_base) {
  assert_argument_type(transframe_change,       this);
  assert_argument_type(semantic_knowledge_base, knowledge_base);
  return raw__transframe_change__apply_to_knowledge_base(cause, this, knowledge_base);
}
export_cefunk2(transframe_change__apply_to_knowledge_base, this, knowledge_base, 0, "Applies this change to given knowledge_base.");


f2ptr raw__transframe_change__unapply_from_knowledge_base(f2ptr cause, f2ptr this, f2ptr knowledge_base) {
  return nil;
}

f2ptr f2__transframe_change__unapply_from_knowledge_base(f2ptr cause, f2ptr this, f2ptr knowledge_base) {
  assert_argument_type(transframe_change,       this);
  assert_argument_type(semantic_knowledge_base, knowledge_base);
  return raw__transframe_change__unapply_from_knowledge_base(cause, this, knowledge_base);
}
export_cefunk2(transframe_change__unapply_from_knowledge_base, this, knowledge_base, 0, "Unapplies this change from given knowledge_base.");


f2ptr f2__transframe_change_type__new_aux(f2ptr cause) {
  f2ptr this = f2__transframe_change_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "apply_to_knowledge_base"),     f2__core_extension_funk__new(cause, new__symbol(cause, "transframe"), new__symbol(cause, "transframe_change__apply_to_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "unapply_from_knowledge_base"), f2__core_extension_funk__new(cause, new__symbol(cause, "transframe"), new__symbol(cause, "transframe_change__unapply_from_knowledge_base")));}
  return this;
}



// transframe

def_ceframe1(transframe, transframe, change_set);

f2ptr raw__transframe__new(f2ptr cause) {
  f2ptr change_set = f2__set__new(cause, nil);
  return f2transframe__new(cause, change_set);
}

f2ptr f2__transframe__new(f2ptr cause) {
  return raw__transframe__new(cause);
}
export_cefunk0(transframe__new, 0, "Returns a new transframe object.");


f2ptr raw__transframe__apply_to_knowledge_base(f2ptr cause, f2ptr this, f2ptr knowledge_base) {
  f2ptr change_set = f2__transframe__change_set(cause, this);
  set__iteration(cause, change_set, change,
		 raw__transframe_change__apply_to_knowledge_base(cause, change, knowledge_base));
  return nil;
}


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
  core_extension__ping(transframe, semantic_frame);
  core_extension__ping(transframe, semantic_knowledge_base);
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


