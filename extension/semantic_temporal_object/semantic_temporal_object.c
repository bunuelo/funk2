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

#include "semantic_temporal_object.h"


// semantic_temporal_object

f2ptr raw__semantic_temporal_object__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__semantic_frame__new(cause, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_temporal_object"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "type"), new__symbol(cause, "name"), new__symbol(cause, "semantic_temporal_object"));
  return this;
}

f2ptr f2__semantic_temporal_object__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__new(cause, semantic_realm);
}
export_cefunk1(semantic_temporal_object__new, semantic_realm, 0, "Returns a new semantic_temporal_object object.");


boolean_t raw__semantic_temporal_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_temporal_object");
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

f2ptr f2__semantic_temporal_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_temporal_object__is_type(cause, thing));
}
export_cefunk1(semantic_temporal_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_temporal_object.");


f2ptr raw__semantic_temporal_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_temporal_object__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_temporal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__type(cause, this);
}
export_cefunk1(semantic_temporal_object__type, thing, 0, "Returns the specific type of object that this semantic_temporal_object is.");


f2ptr raw__semantic_temporal_object__temporal__next__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_ordered_object__ordered__next__lookup(cause, this, new__symbol(cause, "temporal"));
}

f2ptr f2__semantic_temporal_object__temporal__next__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_temporal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__next__lookup(cause, this);
}
export_cefunk1(semantic_temporal_object__temporal__next__lookup, this, 0, "Returns the set of ordered_objects that happen after this ordered_object, returns nil if no such set exists.");


f2ptr raw__semantic_temporal_object__temporal__next__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__ordered__next__add(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__next__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__next__add(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__next__add, this, temporal_object, 0, "Adds the given temporal_object to happen after this ordered_object.");


f2ptr raw__semantic_temporal_object__temporal__next__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__ordered__next__remove(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__next__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__next__remove(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__next__remove, this, temporal_object, 0, "Removes the given temporal_object to no longer happen after this temporal_object.");




f2ptr raw__semantic_temporal_object__temporal__previous__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_ordered_object__ordered__previous__lookup(cause, this, new__symbol(cause, "temporal"));
}

f2ptr f2__semantic_temporal_object__temporal__previous__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_temporal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__previous__lookup(cause, this);
}
export_cefunk1(semantic_temporal_object__temporal__previous__lookup, this, 0, "Returns the set of ordered_objects that happen after this ordered_object, returns nil if no such set exists.");


f2ptr raw__semantic_temporal_object__temporal__previous__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__ordered__previous__add(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__previous__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__previous__add(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__previous__add, this, temporal_object, 0, "Adds the given temporal_object to happen after this ordered_object.");


f2ptr raw__semantic_temporal_object__temporal__previous__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__ordered__previous__remove(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__previous__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__previous__remove(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__previous__remove, this, temporal_object, 0, "Removes the given temporal_object to no longer happen after this temporal_object.");




f2ptr raw__semantic_temporal_object__temporal__contains__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_containment_object__containment_relationship__contains__lookup(cause, this, new__symbol(cause, "temporal"));
}

f2ptr f2__semantic_temporal_object__temporal__contains__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_temporal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__contains__lookup(cause, this);
}
export_cefunk1(semantic_temporal_object__temporal__contains__lookup, this, 0, "Returns the set of containment_objects that happen after this containment_object, returns nil if no such set exists.");


f2ptr raw__semantic_temporal_object__temporal__contains__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_containment_object__containment_relationship__contains__add(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__contains__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__contains__add(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__contains__add, this, temporal_object, 0, "Adds the given temporal_object to happen after this containment_object.");


f2ptr raw__semantic_temporal_object__temporal__contains__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_containment_object__containment__contains__remove(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__contains__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__contains__remove(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__contains__remove, this, temporal_object, 0, "Removes the given temporal_object to no longer happen after this temporal_object.");




f2ptr raw__semantic_temporal_object__temporal__is_contained_by__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_ordered_object__containment__is_contained_by__lookup(cause, this, new__symbol(cause, "temporal"));
}

f2ptr f2__semantic_temporal_object__temporal__is_contained_by__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_temporal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__is_contained_by__lookup(cause, this);
}
export_cefunk1(semantic_temporal_object__temporal__is_contained_by__lookup, this, 0, "Returns the set of ordered_objects that happen after this ordered_object, returns nil if no such set exists.");


f2ptr raw__semantic_temporal_object__temporal__is_contained_by__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__containment__is_contained_by__add(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__is_contained_by__add(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__is_contained_by__add(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__is_contained_by__add, this, temporal_object, 0, "Adds the given temporal_object to happen after this ordered_object.");


f2ptr raw__semantic_temporal_object__temporal__is_contained_by__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  return raw__semantic_ordered_object__containment__is_contained_by__remove(cause, this, new__symbol(cause, "temporal"), temporal_object);
}

f2ptr f2__semantic_temporal_object__temporal__is_contained_by__remove(f2ptr cause, f2ptr this, f2ptr temporal_object) {
  if ((! raw__semantic_temporal_object__is_type(cause, this)) ||
      (! raw__semantic_temporal_object__is_type(cause, temporal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_temporal_object__temporal__is_contained_by__remove(cause, this, temporal_object);
}
export_cefunk2(semantic_temporal_object__temporal__is_contained_by__remove, this, temporal_object, 0, "Removes the given temporal_object to no longer happen after this temporal_object.");




f2ptr f2__semantic_temporal_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_packable_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "execute"),         new__symbol(cause, "new"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "execute"),         new__symbol(cause, "is_type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "get"),             new__symbol(cause, "type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-lookup"), new__symbol(cause, "next"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__next__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-add"),    new__symbol(cause, "next"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__next__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-remove"), new__symbol(cause, "next"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__next__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-lookup"), new__symbol(cause, "previous"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__previous__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-add"),    new__symbol(cause, "previous"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__previous__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-remove"), new__symbol(cause, "previous"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__previous__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-lookup"), new__symbol(cause, "contains"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__contains__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-add"),    new__symbol(cause, "contains"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__contains__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-remove"), new__symbol(cause, "contains"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__contains__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-lookup"), new__symbol(cause, "is_contained_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__is_contained_by__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-add"),    new__symbol(cause, "is_contained_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__is_contained_by__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(causee, "semantic-remove"), new__symbol(cause, "is_contained_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_temporal_object"), new__symbol(cause, "semantic_temporal_object__temporal__is_contained_by__remove")));}
  return this;
}





// **

f2ptr f2__semantic_temporal_object__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_temporal_object__core_extension_ping, 0, "");

f2ptr f2__semantic_temporal_object__core_extension_initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_packable_object"), new__symbol(cause, "semantic_packable_object__core_extension_ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "semantic_temporal_object"), f2__semantic_temporal_object_type__new(cause));
  status("semantic_temporal_object initialized.");
  return nil;
}
export_cefunk0(semantic_temporal_object__core_extension_initialize, 0, "");

f2ptr f2__semantic_temporal_object__core_extension_destroy(f2ptr cause) {
  status("semantic_temporal_object destroyed.");
  return nil;
}
export_cefunk0(semantic_temporal_object__core_extension_destroy, 0, "");


