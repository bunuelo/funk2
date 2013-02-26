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

#include "../../c/funk2.h"
#include "../image/image.h"
#include "../image_sequence/image_sequence.h"

f2ptr raw__image_sequence__new(f2ptr cause, f2ptr images) {
  f2ptr first_image_link;
  {
    f2ptr next = nil;
    f2ptr iter = images;
    while (iter != nil) {
      next = iter;
      iter = f2__doublelink__prev(cause, iter);
    }
    first_image_link = next;
  }
  f2ptr last_image_link;
  {
    f2ptr prev = nil;
    f2ptr iter = images;
    while (iter != nil) {
      prev = iter;
      iter = f2__doublelink__next(cause, iter);
    }
    last_image_link = prev;
  }
  s64 width  = -1;
  s64 height = -1;
  {
    f2ptr iter = first_image_link;
    while (iter != nil) {
      f2ptr image = f2__doublelink__value(cause, iter);
      if (! raw__image__is_type(cause, image)) {
	return f2larva__new(cause, 1, nil);
      }
      s64 image__width  = raw__image__width( cause, image);
      s64 image__height = raw__image__height(cause, image);
      if (width == -1) {
	width  = image__width;
	height = image__height;
      } else if ((width  != image__width) ||
		 (height != image__height)) {
	return f2larva__new(cause, 13, nil);
      }
      iter = f2__doublelink__next(cause, iter);
    }
  }
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),             new__symbol(cause, "image_sequence"),
					    new__symbol(cause, "first_image_link"), first_image_link,
					    new__symbol(cause, "last_image_link"),  last_image_link,
					    new__symbol(cause, "images"),           images));
}

f2ptr f2__image_sequence__new(f2ptr cause, f2ptr images) {
  if ((images != nil) && (! raw__doublelink__is_type(cause, images))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__new(cause, images);
}
export_cefunk1(image_sequence__new, images, 0, "Returns a new image_sequence object.  images can be nil or a doublelink list.");


boolean_t raw__image_sequence__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "image_sequence");
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

f2ptr f2__image_sequence__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__image_sequence__is_type(cause, thing));
}
export_cefunk1(image_sequence__is_type, thing, 0, "Returns whether or not thing is of type image_sequence.");


f2ptr raw__image_sequence__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__image_sequence__type(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__type(cause, this);
}
export_cefunk1(image_sequence__type, thing, 0, "Returns the specific type of object that this image_sequence is.");


f2ptr raw__image_sequence__first_image_link(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "first_image_link"), nil);
}

f2ptr f2__image_sequence__first_image_link(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__first_image_link(cause, this);
}
export_cefunk1(image_sequence__first_image_link, thing, 0, "Returns the first_image_link of the image_sequence.");


f2ptr raw__image_sequence__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "first_image_link"), value);
}

f2ptr f2__image_sequence__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__first_image_link__set(cause, this, value);
}
export_cefunk2(image_sequence__first_image_link__set, thing, value, 0, "Sets the first_image_link of the image_sequence.");


f2ptr raw__image_sequence__last_image_link(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "last_image_link"), nil);
}

f2ptr f2__image_sequence__last_image_link(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__last_image_link(cause, this);
}
export_cefunk1(image_sequence__last_image_link, thing, 0, "Returns the last_image_link of the image_sequence.");


f2ptr raw__image_sequence__last_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "last_image_link"), value);
}

f2ptr f2__image_sequence__last_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__last_image_link__set(cause, this, value);
}
export_cefunk2(image_sequence__last_image_link__set, thing, value, 0, "Sets the last_image_link of the image_sequence.");


f2ptr raw__image_sequence__images(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "images"), nil);
}

f2ptr f2__image_sequence__images(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__images(cause, this);
}
export_cefunk1(image_sequence__images, thing, 0, "Returns the images of the image_sequence.");


f2ptr raw__image_sequence__images__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "images"), value);
}

f2ptr f2__image_sequence__images__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__images__set(cause, this, value);
}
export_cefunk2(image_sequence__images__set, thing, value, 0, "Sets the images of the image_sequence.");


s64 raw__image_sequence__length(f2ptr cause, f2ptr this) {
  s64 length = 0;
  f2ptr iter = raw__image_sequence__first_image_link(cause, this);
  while (iter != nil) {
    length ++;
    iter = f2__doublelink__next(cause, iter);
  }
  return length;
}

f2ptr f2__image_sequence__length(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2integer__new(cause, raw__image_sequence__length(cause, this));
}
export_cefunk1(image_sequence__length, this, 0, "Returns the number of images in the image sequence.");


f2ptr raw__image_sequence__width(f2ptr cause, f2ptr this) {
  f2ptr width = nil;
  f2ptr iter = raw__image_sequence__first_image_link(cause, this);
  if (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    width = raw__image__width(cause, image);
  }
  return width;
}

f2ptr f2__image_sequence__width(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__width(cause, this);
}
export_cefunk1(image_sequence__width, this, 0, "Returns the width of all of the images in the sequence, or nil if sequence is empty.");


f2ptr raw__image_sequence__height(f2ptr cause, f2ptr this) {
  f2ptr height = nil;
  f2ptr iter = raw__image_sequence__first_image_link(cause, this);
  if (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    height = raw__image__height(cause, image);
  }
  return height;
}

f2ptr f2__image_sequence__height(f2ptr cause, f2ptr this) {
  if (! raw__image_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__height(cause, this);
}
export_cefunk1(image_sequence__height, this, 0, "Returns the height of all of the images in the sequence, or nil if sequence is empty.");


f2ptr raw__image_sequence__add_image_to_end(f2ptr cause, f2ptr this, f2ptr image) {
  f2ptr width  = raw__image_sequence__width(cause, this);
  f2ptr height = raw__image_sequence__height(cause, this);
  s64   width__i;
  s64   height__i;
  if (width != nil) {
    width__i  = f2integer__i(width,  cause);
    height__i = f2integer__i(height, cause);
    f2ptr image__width     = raw__image__width( cause, image);
    f2ptr image__height    = raw__image__height(cause, image);
    s64   image__width__i  = f2integer__i(image__width,  cause);
    s64   image__height__i = f2integer__i(image__height, cause);
    if ((width__i  != image__width__i) ||
	(height__i != image__height__i)) {
      return f2larva__new(cause, 3, nil);
    }
  }
  f2ptr last_image_link = raw__image_sequence__last_image_link(cause, this);
  f2ptr link = f2__doublelink__new(cause, last_image_link, nil, image);
  if (last_image_link == nil) {
    f2__image_sequence__images__set(          cause, this, link);
    f2__image_sequence__first_image_link__set(cause, this, link);
  } else {
    f2__doublelink__next__set(cause, last_image_link, link);
  }
  f2__image_sequence__last_image_link__set(cause, this, link);
  return nil;
}

f2ptr f2__image_sequence__add_image_to_end(f2ptr cause, f2ptr this, f2ptr image) {
  if ((! raw__image_sequence__is_type(cause, this)) ||
      (! raw__image__is_type(cause, image))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image_sequence__add_image_to_end(cause, this, image);
}
export_cefunk2(image_sequence__add_image_to_end, this, image, 0, "Adds an image to the end of the image sequence.  The image must be the same dimensions as the other images in the sequence.");


f2ptr raw__image_sequence__elt(f2ptr cause, f2ptr this, s64 index) {
  if (index < 0) {
    return f2larva__new(cause, 2, nil);
  }
  s64   count = 0;
  f2ptr iter  = f2__image_sequence__first_image_link(cause, this);
  while (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    if (count == index) {
      return image;
    }
    count ++;
    iter = f2__doublelink__next(cause, iter);
  }
  return f2larva__new(cause, 2, nil);
}

f2ptr f2__image_sequence__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if ((! raw__image_sequence__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, index))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 index__i = f2integer__i(index, cause);
  return raw__image_sequence__elt(cause, this, index__i);
}
export_cefunk2(image_sequence__elt, this, index, 0, "Returns an image from the sequence.  Indices start at zero.");


f2ptr raw__image_sequence__new_by_time_stretch(f2ptr cause, f2ptr this, double stretch_factor) {
  f2ptr image_sequence = f2__image_sequence__new(cause, nil);
  s64 length     = raw__image_sequence__length(cause, this);
  s64 new_length = ((double)length) * stretch_factor;
  s64 index;
  for (index = 0; index < new_length; index ++) {
    double old_index         = ((double)index) / stretch_factor;
    s64    rounded_old_index = ((s64)(old_index + 0.5));
    if (rounded_old_index >= length) {
      rounded_old_index = length - 1;
    }
    f2ptr image = raw__image_sequence__elt(cause, this, rounded_old_index);
    raw__image_sequence__add_image_to_end(cause, image_sequence, image);
  }
  return image_sequence;
}

f2ptr f2__image_sequence__new_by_time_stretch(f2ptr cause, f2ptr this, f2ptr stretch_factor) {
  if ((! raw__image_sequence__is_type(cause, this)) ||
      (! raw__double__is_type(cause, stretch_factor))) {
    return f2larva__new(cause, 1, nil);
  }
  double stretch_factor__d = f2double__d(stretch_factor, cause);
  return raw__image_sequence__new_by_time_stretch(cause, this, stretch_factor__d);
}
export_cefunk2(image_sequence__new_by_time_stretch, this, stretch_factor, 0, "Returns a new image sequence, which is longer by the given stretch factor..");


f2ptr f2__image_sequence_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "first_image_link"),    f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__first_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "first_image_link"),    f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__first_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "last_image_link"),     f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__last_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "last_image_link"),     f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__last_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "images"),              f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__images")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "images"),              f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__images__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "length"),              f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__length")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),               f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "height"),              f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__height")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_image_to_end"),    f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__add_image_to_end")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "elt"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__elt")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "new_by_time_stretch"), f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__new_by_time_stretch")));}
  return this;
}



// **

f2ptr f2__image_sequence__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(image_sequence__core_extension__ping, 0, "");

f2ptr f2__image_sequence__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "image_sequence"), f2__image_sequence_type__new(cause));
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("image_sequence initialized.");
  return nil;
}
export_cefunk0(image_sequence__core_extension__initialize, 0, "");

f2ptr f2__image_sequence__core_extension__destroy(f2ptr cause) {
  status("image_sequence destroyed.");
  return nil;
}
export_cefunk0(image_sequence__core_extension__destroy, 0, "");


