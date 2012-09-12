// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "semantic_ordered_object.h"


// object-semantic-next-lookup_set, object-semantic-lookup_set-apply

f2ptr f2__object__semantic__ordered__next__lookup_set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-next-lookup_set"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-next-lookup_set_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-next-lookup_set"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__next__lookup_set, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__next__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__next__lookup_set(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__next__lookup_set__apply, this, slot, args, 0, "");


// object-semantic-next-add, object-semantic-add-apply

f2ptr f2__object__semantic__ordered__next__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-next-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-next-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-next-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__next__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__next__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__next__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__next__add__apply, this, slot, args, 0, "");


// object-semantic-next-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__ordered__next__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-next-remove"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-next-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-next-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__next__remove, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__next__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__next__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__next__remove__apply, this, slot, args, 0, "");



// object-semantic-previous-lookup_set, object-semantic-lookup_set-apply

f2ptr f2__object__semantic__ordered__previous__lookup_set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-previous-lookup_set"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-previous-lookup_set_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-previous-lookup_set"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__previous__lookup_set, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__previous__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__previous__lookup_set(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__previous__lookup_set__apply, this, slot, args, 0, "");


// object-semantic-previous-add, object-semantic-add-apply

f2ptr f2__object__semantic__ordered__previous__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-previous-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-previous-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-previous-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__previous__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__previous__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__previous__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__previous__add__apply, this, slot, args, 0, "");


// object-semantic-previous-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__ordered__previous__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-ordered-previous-remove"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-ordered-previous-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-ordered-previous-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__ordered__previous__remove, this, slot, args, 0, "");

f2ptr f2__object__semantic__ordered__previous__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__ordered__previous__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__ordered__previous__remove__apply, this, slot, args, 0, "");





// semantic_ordered_object

f2ptr raw__semantic_ordered_object__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_ordered_object"));
  }
  {
    f2ptr result = raw__semantic_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__semantic_ordered_object__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_ordered_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_ordered_object__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__new(cause, semantic_realm);
}
export_cefunk1(semantic_ordered_object__new, semantic_realm, 0, "Returns a new semantic_ordered_object object.");


boolean_t raw__semantic_ordered_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_ordered_object");
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

f2ptr f2__semantic_ordered_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_ordered_object__is_type(cause, thing));
}
export_cefunk1(semantic_ordered_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_ordered_object.");


f2ptr raw__semantic_ordered_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_ordered_object__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_ordered_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__type(cause, this);
}
export_cefunk1(semantic_ordered_object__type, thing, 0, "Returns the specific type of object that this semantic_ordered_object is.");


f2ptr raw__semantic_ordered_object__ordered__next__lookup_set(f2ptr cause, f2ptr this, f2ptr ordered__type_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "ordered-next"), ordered__type_name);
}

f2ptr f2__semantic_ordered_object__ordered__next__lookup_set(f2ptr cause, f2ptr this, f2ptr ordered__type_name) {
  if (! raw__semantic_ordered_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__next__lookup_set(cause, this, ordered__type_name);
}
export_cefunk2(semantic_ordered_object__ordered__next__lookup_set, this, ordered__type_name, 0, "Returns the set of ordered_objects that are related to this ordered_object in the given ordered__type_name-way, returns nil if no such set exists.");


f2ptr raw__semantic_ordered_object__ordered__next__add(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  {
    f2ptr result = raw__semantic_frame__add(cause, this, new__symbol(cause, "ordered-next"), ordered__type_name, ordered_object);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__semantic_frame__add(cause, ordered_object, new__symbol(cause, "ordered-previous"), ordered__type_name, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_ordered_object__ordered__next__add(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  if ((! raw__semantic_ordered_object__is_type(cause, this)) ||
      (! raw__semantic_ordered_object__is_type(cause, ordered_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__next__add(cause, this, ordered__type_name, ordered_object);
}
export_cefunk3(semantic_ordered_object__ordered__next__add, this, ordered__type_name, ordered_object, 0, "Adds the given ordered_object to relate to this ordered_object in the given ordered__type_name-way.");


f2ptr raw__semantic_ordered_object__ordered__next__remove(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  {
    f2ptr result = raw__semantic_frame__remove(cause, this, new__symbol(cause, "ordered-next"), ordered__type_name, ordered_object);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__semantic_frame__remove(cause, ordered_object, new__symbol(cause, "ordered-previous"), ordered__type_name, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_ordered_object__ordered__next__remove(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  if ((! raw__semantic_ordered_object__is_type(cause, this)) ||
      (! raw__semantic_ordered_object__is_type(cause, ordered_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__next__remove(cause, this, ordered__type_name, ordered_object);
}
export_cefunk3(semantic_ordered_object__ordered__next__remove, this, ordered__type_name, ordered_object, 0, "Removes the given ordered_object to no longer relate to this ordered_object in the given ordered__type_name-way.");


f2ptr raw__semantic_ordered_object__ordered__previous__lookup_set(f2ptr cause, f2ptr this, f2ptr ordered__type_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "ordered-previous"), ordered__type_name);
}

f2ptr f2__semantic_ordered_object__ordered__previous__lookup_set(f2ptr cause, f2ptr this, f2ptr ordered__type_name) {
  if (! raw__semantic_ordered_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__previous__lookup_set(cause, this, ordered__type_name);
}
export_cefunk2(semantic_ordered_object__ordered__previous__lookup_set, this, ordered__type_name, 0, "Returns the set of ordered_objects that are related to this ordered_object in the given ordered-type_name-way, returns nil if no such set exists.");


f2ptr raw__semantic_ordered_object__ordered__previous__add(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  return raw__semantic_ordered_object__ordered__next__add(cause, ordered_object, ordered__type_name, this);
}

f2ptr f2__semantic_ordered_object__ordered__previous__add(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  if ((! raw__semantic_ordered_object__is_type(cause, this)) ||
      (! raw__semantic_ordered_object__is_type(cause, ordered_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__previous__add(cause, this, ordered__type_name, ordered_object);
}
export_cefunk3(semantic_ordered_object__ordered__previous__add, this, ordered__type_name, ordered_object, 0, "Adds the given ordered_object to relate to this ordered_object in the given ordered-type_name-way.");


f2ptr raw__semantic_ordered_object__ordered__previous__remove(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  return raw__semantic_ordered_object__ordered__next__remove(cause, ordered_object, ordered__type_name, this);
}

f2ptr f2__semantic_ordered_object__ordered__previous__remove(f2ptr cause, f2ptr this, f2ptr ordered__type_name, f2ptr ordered_object) {
  if ((! raw__semantic_ordered_object__is_type(cause, this)) ||
      (! raw__semantic_ordered_object__is_type(cause, ordered_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_ordered_object__ordered__previous__remove(cause, this, ordered__type_name, ordered_object);
}
export_cefunk3(semantic_ordered_object__ordered__previous__remove, this, ordered__type_name, ordered_object, 0, "Removes the given ordered_object to no longer relate to this ordered_object in the given ordered__previous_name-way.");




f2ptr f2__semantic_ordered_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "ordered-next-lookup_set"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__next__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "ordered-next-add"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__next__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "ordered-next-remove"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__next__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "ordered-previous-lookup_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__previous__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "ordered-previous-add"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__previous__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "ordered-previous-remove"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_ordered_object"), new__symbol(cause, "semantic_ordered_object__ordered__previous__remove")));}
  return this;
}





// **

f2ptr f2__semantic_ordered_object__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_ordered_object__core_extension__ping, 0, "");

f2ptr f2__semantic_ordered_object__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_ordered_object, semantic_object);
  status("semantic_ordered_object initialized.");
  return nil;
}
export_cefunk0(semantic_ordered_object__core_extension__initialize, 0, "");

f2ptr f2__semantic_ordered_object__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_ordered_object"), f2__semantic_ordered_object_type__new(cause));
  status("semantic_ordered_object types defined.");
  return nil;
}
export_cefunk0(semantic_ordered_object__core_extension__define_types, 0, "");

f2ptr f2__semantic_ordered_object__core_extension__destroy(f2ptr cause) {
  status("semantic_ordered_object destroyed.");
  return nil;
}
export_cefunk0(semantic_ordered_object__core_extension__destroy, 0, "");


