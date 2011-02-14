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

#include "cairo.h"


f2ptr f2__cairo_not_supported_larva__new(f2ptr cause) {
  return f2larva__new(cause, 1243, f2__bug__new(cause, f2integer__new(cause, 1243), f2__frame__new(cause, f2list2__new(cause, new__symbol(cause, "bug_type"), new__symbol(cause, "cairo_not_supported")))));
}



// cairo

f2ptr raw__cairo__new(f2ptr cause, f2ptr cairo_pointer) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),          new__symbol(cause, "cairo"),
					    new__symbol(cause, "cairo_pointer"), cairo_pointer));
}

f2ptr f2__cairo__new(f2ptr cause) {
  f2ptr cairo_pointer = nil;
  return raw__cairo__new(cause, cairo_pointer);
}
export_cefunk0(cairo__new, 0, "Returns a new cairo object.");


boolean_t raw__cairo__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo");
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

f2ptr f2__cairo__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo__is_type(cause, thing));
}
export_cefunk1(cairo__is_type, thing, 0, "Returns whether or not thing is of type cairo.");


f2ptr raw__cairo__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo__type(cause, this);
}
export_cefunk1(cairo__type, thing, 0, "Returns the specific type of object that this cairo is.");


f2ptr raw__cairo__cairo_pointer(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cairo_pointer"), nil);
}

f2ptr f2__cairo__cairo_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo__cairo_pointer(cause, this);
}
export_cefunk1(cairo__cairo_pointer, thing, 0, "Returns the cairo_pointer of the cairo.");


f2ptr raw__cairo__cairo_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "cairo_pointer"), value);
}

f2ptr f2__cairo__cairo_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo__cairo_pointer__set(cause, this, value);
}
export_cefunk2(cairo__cairo_pointer__set, thing, value, 0, "Sets the cairo_pointer of the cairo.");


f2ptr f2__cairo_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),           f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),          f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "cairo_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__cairo_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "cairo_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__cairo_pointer__set")));}
  return this;
}



#if defined(F2__CAIRO_SUPPORTED)
// cairo_format

boolean_t raw__cairo_format__is_type(f2ptr cause, f2ptr object) {
  return (raw__eq(cause, object, new__symbol(cause, "ARGB32")) ||
	  raw__eq(cause, object, new__symbol(cause, "RGB24")) ||
	  raw__eq(cause, object, new__symbol(cause, "A8")) ||
	  raw__eq(cause, object, new__symbol(cause, "A1")) ||
	  raw__eq(cause, object, new__symbol(cause, "RGB16_565")));
}

cairo_format_t raw__cairo_format__as__cairo_format_t(f2ptr cause, f2ptr this) {
  if        (raw__eq(cause, this, new__symbol(cause, "ARGB32"))) {
    return CAIRO_FORMAT_ARGB32;
  } else if (raw__eq(cause, this, new__symbol(cause, "RGB24"))) {
    return CAIRO_FORMAT_RGB24;
  } else if (raw__eq(cause, this, new__symbol(cause, "A8"))) {
    return CAIRO_FORMAT_A8;
  } else if (raw__eq(cause, this, new__symbol(cause, "A1"))) {
    return CAIRO_FORMAT_A1;
  } else if (raw__eq(cause, this, new__symbol(cause, "RGB16_565"))) {
    return CAIRO_FORMAT_RGB16_565;
  }
  return CAIRO_FORMAT_INVALID;
}
#endif // F2__CAIRO_SUPPORTED

// cairo_image_surface

f2ptr f2cairo_image_surface__new(f2ptr cause, f2ptr cairo_image_surface_pointer) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),          new__symbol(cause, "cairo_image_surface"),
					    new__symbol(cause, "cairo_image_surface_pointer"), cairo_image_surface_pointer));
}

f2ptr raw__cairo_image_surface__new(f2ptr cause, f2ptr format, f2ptr width, f2ptr height) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_format_t   cairo_format  = raw__cairo_format__as__cairo_format_t(cause, format);
  s64              width__i      = f2integer__i(width,  cause);
  s64              height__i     = f2integer__i(height, cause);
  cairo_surface_t* cairo_surface = cairo_image_surface_create(cairo_format,
							      width__i,
							      height__i);
  cairo_status_t status = cairo_surface_status(cairo_surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    f2ptr cairo_status = nil;
    switch(status) {
    case CAIRO_STATUS_NULL_POINTER:    cauro_status = new__symbol(cause, "CAIRO_STATUS_NULL_POINTER");    break;
    case CAIRO_STATUS_NO_MEMORY:       cauro_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");       break;
    case CAIRO_STATUS_READ_ERROR:      cauro_status = new__symbol(cause, "CAIRO_STATUS_READ_ERROR");      break;
    case CAIRO_STATUS_INVALID_CONTENT: cauro_status = new__symbol(cause, "CAIRO_STATUS_INVALID_CONTENT"); break;
    case CAIRO_STATUS_INVALID_FORMAT:  cauro_status = new__symbol(cause, "CAIRO_STATUS_INVALID_FORMAT");  break;
    case CAIRO_STATUS_INVALID_VISUAL:  cauro_status = new__symbol(cause, "CAIRO_STATUS_INVALID_VISUAL");  break;
    default:                           cauro_status = new__symbol(cause, "unknown");                      break;
    }
    cauro_surface_destroy(cairo_surface);
    return f2larva__new(cause, 44321, f2__bug__new(cause, f2integer__new(cause, 44321), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),     new__symbol(cause, "failure_to_create_cairo_surface"),
															    new__symbol(cause, "cairo_status"), cairo_status,
															    new__symbol(cause, "format"),       format,
															    new__symbol(cause, "width"),        width,
															    new__symbol(cause, "height"),       height))));
  }
  f2ptr cairo_image_surface_pointer = f2pointer__new(cause, to_ptr(cairo_surface));
  return raw__cairo_image_surface__new(cause, cairo_image_surface_pointer);
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_image_surface__new(f2ptr cause, f2ptr format, f2ptr width, f2ptr height) {
  if ((! raw__cairo_format__is_type(cause, format)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__new(cause, format, width, height);
}
export_cefunk3(cairo_image_surface__new, format, width, height, 0, "Returns a new cairo_image_surface object.  Given format must be one of the following symbols: ARGB32, RGB24, A8, A1, RGB16_565.");


boolean_t raw__cairo_image_surface__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_image_surface");
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

f2ptr f2__cairo_image_surface__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_image_surface__is_type(cause, thing));
}
export_cefunk1(cairo_image_surface__is_type, thing, 0, "Returns whether or not thing is of type cairo_image_surface.");


f2ptr raw__cairo_image_surface__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_image_surface__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__type(cause, this);
}
export_cefunk1(cairo_image_surface__type, thing, 0, "Returns the specific type of object that this cairo_image_surface is.");


f2ptr raw__cairo_image_surface__cairo_image_surface_pointer(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cairo_image_surface_pointer"), nil);
}

f2ptr f2__cairo_image_surface__cairo_image_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__cairo_image_surface_pointer(cause, this);
}
export_cefunk1(cairo_image_surface__cairo_image_surface_pointer, thing, 0, "Returns the cairo_image_surface_pointer of the cairo_image_surface.");


f2ptr raw__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "cairo_image_surface_pointer"), value);
}

f2ptr f2__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__cairo_image_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_image_surface__cairo_image_surface_pointer__set, thing, value, 0, "Sets the cairo_image_surface_pointer of the cairo_image_surface.");


f2ptr f2__cairo_image_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_image_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__cairo_image_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_image_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__cairo_image_surface_pointer__set")));}
  return this;
}



// **

f2ptr f2__cairo__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(cairo__core_extension__ping, 0, "");

f2ptr f2__cairo__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "cairo"),               f2__cairo_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_image_surface"), f2__cairo_image_surface_type__new(cause));
  status("cairo initialized.");
  return nil;
}
export_cefunk0(cairo__core_extension__initialize, 0, "");

f2ptr f2__cairo__core_extension__destroy(f2ptr cause) {
  status("cairo destroyed.");
  return nil;
}
export_cefunk0(cairo__core_extension__destroy, 0, "");


