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

f2ptr raw__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data) {
  s64 width__i  = f2integer__i(width,  cause);
  s64 height__i = f2integer__i(height, cause);
  if ((width__i < 0) || (height__i < 0)) {
    return f2larva__new(cause, 2, nil);
  }
  if (rgba_data == nil) {
    rgba_data = raw__chunk__new(cause, 4 * width__i * height__i);
  } else {
    s64 rgba_data__length = f2chunk__length(rgba_data, cause);
    if (rgba_data__length != 4 * width__i * height__i) {
      return f2larva__new(cause, 3, nil);
    }
  }
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),      new__symbol(cause, "image"),
					    new__symbol(cause, "width"),     width,
					    new__symbol(cause, "height"),    height,
					    new__symbol(cause, "rgba_data"), rgba_data));
}

f2ptr f2__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      ((rgba_data != nil) && (! raw__chunk__is_type(cause, rgba_data)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__new(cause, width, height, rgba_data);
}
export_cefunk3(image__new, width, height, rgba_data, 0, "Returns a new image object.  rgba_data can be nil, in which case a black image is returned.");


f2ptr raw__image__new_from_rgb_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  s64 width__i  = f2integer__i(width,  cause);
  s64 height__i = f2integer__i(height, cause);
  if ((width__i < 0) || (height__i < 0)) {
    return f2larva__new(cause, 2, nil);
  }
  s64 rgb_data__length = f2chunk__length(rgb_data, cause);
  if (rgb_data__length != 3 * width__i * height__i) {
    return f2larva__new(cause, 3, nil);
  }
  f2ptr rgba_data = raw__chunk__new(cause, 4 * width__i * height__i);
  {
    s64 y;
    for (y = 0; y < height__i; y ++) {
      s64 x;
      for (x = 0; x < width__i; x ++) {
	s64 rgb_pixel = (3 * ((y * width__i) + x));
	u8 red   = raw__chunk__bit8__elt(cause, rgb_data, rgb_pixel + 0);
	u8 green = raw__chunk__bit8__elt(cause, rgb_data, rgb_pixel + 1);
	u8 blue  = raw__chunk__bit8__elt(cause, rgb_data, rgb_pixel + 2);
	u8 alpha = 255;
	s64 rgba_pixel = (4 * ((y * width__i) + x));
	raw__chunk__bit8__elt__set(cause, rgba_data, rgba_pixel + 0, red);
	raw__chunk__bit8__elt__set(cause, rgba_data, rgba_pixel + 1, green);
	raw__chunk__bit8__elt__set(cause, rgba_data, rgba_pixel + 2, blue);
	raw__chunk__bit8__elt__set(cause, rgba_data, rgba_pixel + 3, alpha);
      }
    }
  }
  return f2__image__new(cause, width, height, rgba_data);
}

f2ptr f2__image__new_from_rgb_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      (! raw__chunk__is_type(  cause, rgb_data))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__new_from_rgb_data(cause, width, height, rgb_data);
}
export_cefunk3(image__new_from_rgb_data, width, height, rgb_data, 0, "Returns a new image object from rgb_data.");



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


f2ptr raw__image__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr f2__image__width(f2ptr cause, f2ptr this) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__width(cause, this);
}
export_cefunk1(image__width, thing, 0, "Returns the width of the image.");


f2ptr raw__image__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr f2__image__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__width__set(cause, this, value);
}
export_cefunk2(image__width__set, thing, value, 0, "Sets the width of the image.");


f2ptr raw__image__height(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil);
}

f2ptr f2__image__height(f2ptr cause, f2ptr this) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__height(cause, this);
}
export_cefunk1(image__height, thing, 0, "Returns the height of the image.");


f2ptr raw__image__height__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "height"), value);
}

f2ptr f2__image__height__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__height__set(cause, this, value);
}
export_cefunk2(image__height__set, thing, value, 0, "Sets the height of the image.");


f2ptr raw__image__rgba_data(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "rgba_data"), nil);
}

f2ptr f2__image__rgba_data(f2ptr cause, f2ptr this) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__rgba_data(cause, this);
}
export_cefunk1(image__rgba_data, thing, 0, "Returns the rgba_data of the image.");


f2ptr raw__image__rgba_data__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "rgba_data"), value);
}

f2ptr f2__image__rgba_data__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__rgba_data__set(cause, this, value);
}
export_cefunk2(image__rgba_data__set, thing, value, 0, "Sets the rgba_data of the image.");


f2ptr raw__image__write_reduction_image_part(f2ptr cause, f2ptr this, f2ptr reduced_image, f2ptr reduction_factor, f2ptr x_offset, f2ptr y_offset) {
  f2ptr this__rgba_data          = raw__image__rgba_data(cause, this);
  f2ptr this__width              = raw__image__width(    cause, this);
  s64   this__width__i           = f2integer__i(this__width, cause);
  f2ptr this__height             = raw__image__width(    cause, this);
  s64   this__height__i          = f2integer__i(this__height, cause);
  f2ptr reduced_image__rgba_data = raw__image__rgba_data(cause, reduced_image);
  f2ptr reduced_image__width     = raw__image__width(    cause, reduced_image);
  s64   reduced_image__width__i  = f2integer__i(reduced_image__width, cause);
  f2ptr reduced_image__height    = raw__image__width(    cause, reduced_image);
  s64   reduced_image__height__i = f2integer__i(reduced_image__height, cause);
  s64   reduction_factor__i      = f2integer__i(reduction_factor, cause);
  s64   x_offset__i              = f2integer__i(x_offset, cause);
  s64   y_offset__i              = f2integer__i(y_offset, cause);
  {
    s64 reduced_image__y;
    for (reduced_image__y = 0; reduced_image__y < reduced_image__height__i; reduced_image__y ++) {
      s64 this__y = (reduced_image__y * reduction_factor__i) + y_offset__i;
      {
	if ((this__y >= 0) && (this__y < this__height__i)) {
	  s64 reduced_image__x;
	  for (reduced_image__x = 0; reduced_image__x < reduced_image__width__i; reduced_image__x ++) {
	    s64 this__x = (reduced_image__x * reduction_factor__i) + x_offset__i;
	    if ((this__x >= 0) && (this__x < this__width__i)) {
	      s64 reduced_image__pixel_index = (reduced_image__y * reduced_image__width__i) + reduced_image__x;
	      s64 this__pixel_index          = (this__y          * this__width__i)          + this__x;
	      u64 rgba_pixel                 = raw__chunk__bit8__elt(cause, reduced_image__rgba_data, reduced_image__pixel_index);
	      raw__chunk__bit64__elt__set(cause, this__rgba_data, this__pixel_index, rgba_pixel);
	    }
	  }
	}
      }
    }
  }
  return nil;
}

f2ptr f2__image__write_reduction_image_part(f2ptr cause, f2ptr this, f2ptr reduced_image, f2ptr reduction_factor, f2ptr x_offset, f2ptr y_offset) {
  if ((! raw__image__is_type(cause, this)) ||
      (! raw__image__is_type(cause, reduced_image)) ||
      (! raw__integer__is_type(cause, reduction_factor)) ||
      (! raw__integer__is_type(cause, x_offset)) ||
      (! raw__integer__is_type(cause, y_offset))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__write_reduction_image_part(cause, this, reduced_image, reduction_factor, x_offset, y_offset);
}
export_cefunk5(image__write_reduction_image_part, this, reduced_image, reduction_factor, x_offset, y_offset, 0, "");


f2ptr f2__image_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "width"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__width__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "height"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__height")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "height"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__height__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "rgba_data"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__rgba_data")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "rgba_data"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__rgba_data__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "write_reduction_image_part"), f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__write_reduction_image_part")));}
  return this;
}



// **

f2ptr f2__image__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(image__core_extension_ping, 0, "");

f2ptr f2__image__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "image"), f2__image_type__new(cause));
  printf("\nimage initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_initialize, 0, "");

f2ptr f2__image__core_extension_destroy(f2ptr cause) {
  printf("\nimage destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_destroy, 0, "");


