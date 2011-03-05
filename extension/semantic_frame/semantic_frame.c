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

#include "semantic_frame.h"


// object-semantic-lookup, object-semantic-lookup-apply

f2ptr f2__object__semantic__lookup(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-lookup"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-lookup_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__lookup, this, slot, args, 0, "");

f2ptr f2__object__semantic__lookup__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__lookup(cause, this, slot, args);
}
export_cefunk3(object__semantic__lookup__apply, this, slot, args, 0, "");


// object-semantic-add, object-semantic-add-apply

f2ptr f2__object__semantic__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__add__apply, this, slot, args, 0, "");


// object-semantic-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
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
	return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
															new__symbol(cause, "this"),     this,
															new__symbol(cause, "slot"),     slot,
															new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-remove"), slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, 2346, f2__bug__new(cause, f2integer__new(cause, 2346), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_semantic-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
export_cefunk2_and_rest(object__semantic__remove,        this, slot, args, 0, "");

f2ptr f2__object__semantic__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__remove__apply, this, slot, args, 0, "");




// **

f2ptr f2__semantic_frame__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_frame__core_extension__ping, 0, "");

f2ptr f2__semantic_frame__core_extension__initialize(f2ptr cause) {
  status("semantic_frame initialized.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__initialize, 0, "");

f2ptr f2__semantic_frame__core_extension__define_types(f2ptr cause) {
  status("semantic_frame defined types.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__define_types, 0, "");

f2ptr f2__semantic_frame__core_extension__destroy(f2ptr cause) {
  status("semantic_frame destroyed.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__destroy, 0, "");


