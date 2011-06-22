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

#include "concept_version_space.h"

def_ceframe1(concept_version_space, concept_version_space, variable_set);

f2ptr raw__concept_version_space__new(f2ptr cause) {
  f2ptr variable_set = f2__set__new(cause);
  return f2concept_version_space__new(cause, variable_set);
}

f2ptr f2__concept_version_space__new(f2ptr cause) {
  return raw__concept_version_space__new(cause);
}
export_cefunk0(concept_version_space__new, 0, "Returns a new concept_version_space object.");


f2ptr raw__concept_version_space__add_variable(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr variable_set = raw__concept_version_space__variable_set(cause, this);
  raw__set__add(cause, variable_set, key);
  return nil;
}

f2ptr f2__concept_version_space__add_variable(f2ptr cause, f2ptr this, f2ptr key) {
  return raw__concept_version_space__add_variable(cause, this, key);
}
export_cefunk2(concept_version_space__add_variable, this, key, 0, "Adds a new variable key to this concept_version_space.");


f2ptr f2__concept_version_space_type__new_aux(f2ptr cause) {
  f2ptr this = f2__concept_version_space_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_variable"), f2__core_extension_funk__new(cause, new__symbol(cause, "concept_version_space"), new__symbol(cause, "concept_version_space__add_variable")));}
  return this;
}



// **

f2ptr f2__concept_version_space__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(concept_version_space__core_extension__ping, 0, "");

f2ptr f2__concept_version_space__core_extension__initialize(f2ptr cause) {
  status("concept_version_space initialized.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__initialize, 0, "");

f2ptr f2__concept_version_space__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "concept_version_space"), f2__concept_version_space_type__new_aux(cause));
  status("concept_version_space types defined.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__define_types, 0, "");

f2ptr f2__concept_version_space__core_extension__destroy(f2ptr cause) {
  status("concept_version_space destroyed.");
  return nil;
}
export_cefunk0(concept_version_space__core_extension__destroy, 0, "");


