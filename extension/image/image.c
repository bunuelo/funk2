// 
// Copyright (c) 2007-2010 Bo Morgan.
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

f2ptr raw__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  s64 width__i  = f2integer__i(width,  cause);
  s64 height__i = f2integer__i(height, cause);
  if ((width__i < 0) || (height__i < 0)) {
    return f2larva__new(cause, 2, nil);
  }
  if (rgb_data == nil) {
    rgb_data = raw__chunk__new(cause, 3 * width__i * height__i);
  } else {
    s64 rgb_data__length = f2chunk__length(rgb_data, cause);
    if (rgb_data__length != 3 * width__i * height__i) {
      return f2larva__new(cause, 3, nil);
    }
  }
  return f2__frame__new(cause, f2list6__new(cause,
					    new__symbol(cause, "width"),    width,
					    new__symbol(cause, "height"),   height,
					    new__symbol(cause, "rgb_data"), rgb_data));
}

f2ptr f2__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      ((rgb_data != nil) && (! raw__chunk__is_type(cause, rgb_data)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__new(cause, width, height, rgb_data);
}
export_cefunk3(image__new, width, height, rgb_data, 0, "Returns a new image object.  rgb_data can be nil, in which case a black image is returned.");


boolean_t raw__image__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "image");
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

f2ptr f2__image__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__image__is_type(cause, thing));
}
export_cefunk1(image__is_type, thing, 0, "Returns whether or not thing is of type image.");


f2ptr raw__image__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__image__type(f2ptr cause, f2ptr this) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__type(cause, this);
}
export_cefunk1(image__type, thing, 0, "Returns the specific type of object that this image is.");


f2ptr f2__image_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("frame"), (u8*)"frame"), nil)); \
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__type")));}
  return this;
}



f2ptr f2__image__core_extension_initialize(f2ptr cause) {
  printf("\nimage initializing."); fflush(stdout);
  f2__add_type(cause, new__symbol__new(cause, "image"), f2__image_type__new(cause));
  printf("\nimage initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_initialize, 0, "");

f2ptr f2__image__core_extension_destroy(f2ptr cause) {
  printf("\nimage destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_destroy, 0, "");


