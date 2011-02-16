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

#include "../../c/funk2.h"
#include "timeline.h"

f2ptr raw__timeline__new(f2ptr cause, f2ptr width) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),  new__symbol(cause, "timeline"),
					    new__symbol(cause, "width"), width));
}

f2ptr f2__timeline__new(f2ptr cause, f2ptr width) {
  if (! raw__integer__is_type(cause, width)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__new(cause, width);
}
export_cefunk1(timeline__new, width, 0, "Returns a new timeline object.");


boolean_t raw__timeline__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "timeline");
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

f2ptr f2__timeline__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__timeline__is_type(cause, thing));
}
export_cefunk1(timeline__is_type, thing, 0, "Returns whether or not thing is of type timeline.");


f2ptr raw__timeline__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__timeline__type(f2ptr cause, f2ptr this) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__type(cause, this);
}
export_cefunk1(timeline__type, thing, 0, "Returns the specific type of object that this timeline is.");


f2ptr raw__timeline__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr f2__timeline__width(f2ptr cause, f2ptr this) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__width(cause, this);
}
export_cefunk1(timeline__width, thing, 0, "Returns the width of the timeline.");


f2ptr raw__timeline__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr f2__timeline__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__width__set(cause, this, value);
}
export_cefunk2(timeline__width__set, thing, value, 0, "Sets the width of the timeline.");


f2ptr f2__timeline_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__width__set")));}
  return this;
}



// **

f2ptr f2__timeline__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(timeline__core_extension__ping, 0, "");

f2ptr f2__timeline__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "timeline"), f2__timeline_type__new(cause));
  status("timeline initialized.");
  return nil;
}
export_cefunk0(timeline__core_extension__initialize, 0, "");

f2ptr f2__timeline__core_extension__destroy(f2ptr cause) {
  status("timeline destroyed.");
  return nil;
}
export_cefunk0(timeline__core_extension__destroy, 0, "");


