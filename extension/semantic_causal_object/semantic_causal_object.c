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

#include "semantic_causal_object.h"


// object-semantic-causes-lookup_set, object-semantic-causes-lookup_set-apply

f2ptr f2__object__semantic__causal__causes__lookup_set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-causes-lookup_set"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-causes-lookup_set_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-causes-lookup_set"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__causes__lookup_set, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__causes__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__causes__lookup_set(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__causes__lookup_set__apply, this, slot, args, 0, "");


// object-semantic-causes-add, object-semantic-add-apply

f2ptr f2__object__semantic__causal__causes__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-causes-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-causes-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-causes-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__causes__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__causes__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__causes__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__causes__add__apply, this, slot, args, 0, "");


// object-semantic-causes-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__causal__causes__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-causes-remove"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-causes-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-causes-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__causes__remove, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__causes__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__causes__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__causes__remove__apply, this, slot, args, 0, "");



// object-semantic-is_caused_by-lookup_set, object-semantic-is_caused_by-lookup_set-apply

f2ptr f2__object__semantic__causal__is_caused_by__lookup_set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-is_caused_by-lookup_set"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-is_caused_by-lookup_set_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-is_caused_by-lookup_set"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__is_caused_by__lookup_set, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__is_caused_by__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__is_caused_by__lookup_set(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__is_caused_by__lookup_set__apply, this, slot, args, 0, "");


// object-semantic-is_caused_by-add, object-semantic-is_caused_by-add-apply

f2ptr f2__object__semantic__causal__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-is_caused_by-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-is_caused_by-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-is_caused_by-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__is_caused_by__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__is_caused_by__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__is_caused_by__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__is_caused_by__add__apply, this, slot, args, 0, "");


// object-semantic-is_caused_by-remove, object-semantic-is_caused_by-remove-apply

f2ptr f2__object__semantic__causal__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-causal-is_caused_by-remove"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-causal-is_caused_by-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-causal-is_caused_by-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__causal__is_caused_by__remove, this, slot, args, 0, "");

f2ptr f2__object__semantic__causal__is_caused_by__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__causal__is_caused_by__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__causal__is_caused_by__remove__apply, this, slot, args, 0, "");





// semantic_causal_object

f2ptr raw__semantic_causal_object__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_causal_object"));
  }
  {
    f2ptr result = raw__semantic_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__semantic_causal_object__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_causal_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_causal_object__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__new(cause, semantic_realm);
}
export_cefunk1(semantic_causal_object__new, semantic_realm, 0, "Returns a new semantic_causal_object object.");


boolean_t raw__semantic_causal_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_causal_object");
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

f2ptr f2__semantic_causal_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_causal_object__is_type(cause, thing));
}
export_cefunk1(semantic_causal_object__is_type, thing, 0, "Returns whether or not thing is of type semantic_causal_object.");


f2ptr raw__semantic_causal_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_causal_object__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_causal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__type(cause, this);
}
export_cefunk1(semantic_causal_object__type, thing, 0, "Returns the specific type of object that this semantic_causal_object is.");


f2ptr raw__semantic_causal_object__causal__causes__lookup_set(f2ptr cause, f2ptr this, f2ptr causal__type_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "causal-causes"), causal__type_name);
}

f2ptr f2__semantic_causal_object__causal__causes__lookup_set(f2ptr cause, f2ptr this, f2ptr causal__type_name) {
  if (! raw__semantic_causal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__causes__lookup_set(cause, this, causal__type_name);
}
export_cefunk2(semantic_causal_object__causal__causes__lookup_set, this, causal__type_name, 0, "Returns the set of causal_objects that are related to this causal_object in the given causal__type_name-way, returns nil if no such set exists.");


f2ptr raw__semantic_causal_object__causal__causes__add(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  {
    f2ptr result = raw__semantic_frame__add(cause, this, new__symbol(cause, "causal-causes"), causal__type_name, causal_object);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__semantic_frame__add(cause, causal_object, new__symbol(cause, "causal-is_caused_by"), causal__type_name, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_causal_object__causal__causes__add(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  if ((! raw__semantic_causal_object__is_type(cause, this)) ||
      (! raw__semantic_causal_object__is_type(cause, causal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__causes__add(cause, this, causal__type_name, causal_object);
}
export_cefunk3(semantic_causal_object__causal__causes__add, this, causal__type_name, causal_object, 0, "Adds the given causal_object to relate to this causal_object in the given causal__type_name-way.");


f2ptr raw__semantic_causal_object__causal__causes__remove(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  {
    f2ptr result = raw__semantic_frame__remove(cause, this, new__symbol(cause, "causal-causes"), causal__type_name, causal_object);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__semantic_frame__remove(cause, causal_object, new__symbol(cause, "causal-is_caused_by"), causal__type_name, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_causal_object__causal__causes__remove(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  if ((! raw__semantic_causal_object__is_type(cause, this)) ||
      (! raw__semantic_causal_object__is_type(cause, causal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__causes__remove(cause, this, causal__type_name, causal_object);
}
export_cefunk3(semantic_causal_object__causal__causes__remove, this, causal__type_name, causal_object, 0, "Removes the given causal_object to no longer relate to this causal_object in the given causal__type_name-way.");


f2ptr raw__semantic_causal_object__causal__is_caused_by__lookup_set(f2ptr cause, f2ptr this, f2ptr causal__type_name) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "causal-is_caused_by"), causal__type_name);
}

f2ptr f2__semantic_causal_object__causal__is_caused_by__lookup_set(f2ptr cause, f2ptr this, f2ptr causal__type_name) {
  if (! raw__semantic_causal_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__is_caused_by__lookup_set(cause, this, causal__type_name);
}
export_cefunk2(semantic_causal_object__causal__is_caused_by__lookup_set, this, causal__type_name, 0, "Returns the set of causal_objects that are related to this causal_object in the given causal-type_name-way, returns nil if no such set exists.");


f2ptr raw__semantic_causal_object__causal__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  return raw__semantic_causal_object__causal__causes__add(cause, causal_object, causal__type_name, this);
}

f2ptr f2__semantic_causal_object__causal__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  if ((! raw__semantic_causal_object__is_type(cause, this)) ||
      (! raw__semantic_causal_object__is_type(cause, causal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__is_caused_by__add(cause, this, causal__type_name, causal_object);
}
export_cefunk3(semantic_causal_object__causal__is_caused_by__add, this, causal__type_name, causal_object, 0, "Adds the given causal_object to relate to this causal_object in the given causal-type_name-way.");


f2ptr raw__semantic_causal_object__causal__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  return raw__semantic_causal_object__causal__causes__remove(cause, causal_object, causal__type_name, this);
}

f2ptr f2__semantic_causal_object__causal__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal__type_name, f2ptr causal_object) {
  if ((! raw__semantic_causal_object__is_type(cause, this)) ||
      (! raw__semantic_causal_object__is_type(cause, causal_object))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_object__causal__is_caused_by__remove(cause, this, causal__type_name, causal_object);
}
export_cefunk3(semantic_causal_object__causal__is_caused_by__remove, this, causal__type_name, causal_object, 0, "Removes the given causal_object to no longer relate to this causal_object in the given causal__is_caused_by_name-way.");




f2ptr f2__semantic_causal_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "causal-causes-lookup_set"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__causes__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "causal-causes-add"),              f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__causes__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "causal-causes-remove"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__causes__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "causal-is_caused_by-lookup_set"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__is_caused_by__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "causal-is_caused_by-add"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__is_caused_by__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "causal-is_caused_by-remove"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__causal__is_caused_by__remove")));}
  return this;
}





// **

f2ptr f2__semantic_causal_object__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_causal_object__core_extension__ping, 0, "");

f2ptr f2__semantic_causal_object__core_extension__initialize(f2ptr cause) {
  { 
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_object"), new__symbol(cause, "semantic_object__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      status("semantic_causal_object: failed to ping semantic_object.");
      return result;
    }
  }
  status("semantic_causal_object initialized.");
  return nil;
}
export_cefunk0(semantic_causal_object__core_extension__initialize, 0, "");

f2ptr f2__semantic_causal_object__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_causal_object"), f2__semantic_causal_object_type__new(cause));
  status("semantic_causal_object defined types.");
  return nil;
}
export_cefunk0(semantic_causal_object__core_extension__define_types, 0, "");

f2ptr f2__semantic_causal_object__core_extension__destroy(f2ptr cause) {
  status("semantic_causal_object destroyed.");
  return nil;
}
export_cefunk0(semantic_causal_object__core_extension__destroy, 0, "");


