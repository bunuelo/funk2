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
    iter = f2__doublelink__next(cause, this);
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


f2ptr f2__image_sequence_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),              f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),          f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "first_image_link"), f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__first_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "first_image_link"), f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__first_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "last_image_link"),  f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__last_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "last_image_link"),  f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__last_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "images"),           f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__images")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "images"),           f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__images__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "length"),           f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__length")));}
  return this;
}



// **

f2ptr f2__image_sequence__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(image_sequence__core_extension_ping, 0, "");

f2ptr f2__image_sequence__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "image_sequence"), f2__image_sequence_type__new(cause));
  printf("\nimage_sequence initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(image_sequence__core_extension_initialize, 0, "");

f2ptr f2__image_sequence__core_extension_destroy(f2ptr cause) {
  printf("\nimage_sequence destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(image_sequence__core_extension_destroy, 0, "");


