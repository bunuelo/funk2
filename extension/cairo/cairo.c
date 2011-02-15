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



// cairo_object

f2ptr f2cairo_object__new(f2ptr cause, f2ptr cairo_object_pointer) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),                 new__symbol(cause, "cairo_object"),
					    new__symbol(cause, "cairo_object_pointer"), cairo_object_pointer));
}

boolean_t raw__cairo_object__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_object");
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

f2ptr f2__cairo_object__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_object__is_type(cause, thing));
}
export_cefunk1(cairo_object__is_type, thing, 0, "Returns whether or not thing is of type cairo_object.");


f2ptr raw__cairo_object__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_object__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_object__type(cause, this);
}
export_cefunk1(cairo_object__type, thing, 0, "Returns the specific type of object that this cairo_object is.");


f2ptr raw__cairo_object__cairo_object_pointer(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cairo_object_pointer"), nil);
}

f2ptr f2__cairo_object__cairo_object_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_object__cairo_object_pointer(cause, this);
}
export_cefunk1(cairo_object__cairo_object_pointer, thing, 0, "Returns the cairo_object_pointer of the cairo_object.");


#if defined(F2__CAIRO_SUPPORTED)
void* raw__cairo_object__as__void(f2ptr cause, f2ptr this) {
  f2ptr cairo_object_pointer = raw__cairo_object__cairo_object_pointer(cause, this);
  void* cairo_object         = from_ptr(f2pointer__p(cairo_object_pointer, cause));
  return cairo_object;
}
#endif // F2__CAIRO_SUPPORTED

f2ptr raw__cairo_object__cairo_object_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "cairo_object_pointer"), value);
}

f2ptr f2__cairo_object__cairo_object_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_object__cairo_object_pointer__set(cause, this, value);
}
export_cefunk2(cairo_object__cairo_object_pointer__set, thing, value, 0, "Sets the cairo_object_pointer of the cairo_object.");


f2ptr f2__cairo_object_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_object__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_object__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_object_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_object__cairo_object_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_object_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_object__cairo_object_pointer__set")));}
  return this;
}



// cairo_context

f2ptr f2cairo_context__new(f2ptr cause, f2ptr cairo_context_pointer) {
  f2ptr this = f2cairo_object__new(cause, cairo_context_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_context"));
  return this;
}

f2ptr raw__cairo_context__new(f2ptr cause, f2ptr target) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface = raw__cairo_surface__as__cairo_surface_t(cause, target);
  cairo_t*         cairo_context         = cairo_create(cairo_surface);
  cairo_status_t   status        = cairo_status(cairo_context);
  if (status == CAIRO_STATUS_NO_MEMORY) {
    cairo_destroy(cairo_context);
    return f2larva__new(cause, 2351, nil);
  }
  return f2cairo_context__new(cause, f2pointer__new(cause, to_ptr(cairo_context)));
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // f2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_context__new(f2ptr cause, f2ptr target) {
  if (! raw__cairo_surface__is_type(cause, target)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__new(cause, target);
}
export_cefunk1(cairo_context__new, target, 0, "Returns a new cairo_context object for drawing to the given target cairo_surface.");


boolean_t raw__cairo_context__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_context");
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

f2ptr f2__cairo_context__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_context__is_type(cause, thing));
}
export_cefunk1(cairo_context__is_type, thing, 0, "Returns whether or not thing is of type cairo_context.");


f2ptr raw__cairo_context__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_context__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__type(cause, this);
}
export_cefunk1(cairo_context__type, thing, 0, "Returns the specific type of object that this cairo_context is.");


f2ptr raw__cairo_context__cairo_context_pointer(f2ptr cause, f2ptr this) {
  return raw__cairo_object__cairo_object_pointer(cause, this);
}

f2ptr f2__cairo_context__cairo_context_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__cairo_context_pointer(cause, this);
}
export_cefunk1(cairo_context__cairo_context_pointer, thing, 0, "Returns the cairo_context_pointer of the cairo_context.");


#if defined(F2__CAIRO_SUPPORTED)
cairo_t* raw__cairo_context__as__cairo_t(f2ptr cause, f2ptr this) {
  f2ptr    cairo_context_pointer = raw__cairo_context__cairo_context_pointer(cause, this);
  cairo_t* cairo_context         = from_ptr(f2pointer__p(cairo_context_pointer, cause));
  return cairo_context;
}
#endif // F2__CAIRO_SUPPORTED


f2ptr raw__cairo_context__cairo_context_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_object__cairo_object_pointer__set(cause, this, value);
}

f2ptr f2__cairo_context__cairo_context_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__cairo_context_pointer__set(cause, this, value);
}
export_cefunk2(cairo_context__cairo_context_pointer__set, thing, value, 0, "Sets the cairo_context_pointer of the cairo_context.");


f2ptr raw__cairo_context__destroy(f2ptr cause, f2ptr this) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_t* cairo_context = raw__cairo_context__as__cairo_t(cause, this);
  cairo_destroy(cairo_context);
  return nil;
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_context__destroy(f2ptr cause, f2ptr this) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__destroy(cause, this);
}
export_cefunk1(cairo_context__destroy, this, 0, "Destroys the cairo_context.");



f2ptr raw__cairo_context__new_path(f2ptr cause, f2ptr this) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_t* cairo_context = raw__cairo_context__as__cairo_t(cause, this);
  cairo_new_path(cairo_context);
  return nil;
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_context__new_path(f2ptr cause, f2ptr this) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__new_path(cause, this);
}
export_cefunk1(cairo_context__new_path, this, 0, "Clears the current path.  After this call there will be no path and no current point.");



f2ptr raw__cairo_context__close_path(f2ptr cause, f2ptr this) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_t* cairo_context = raw__cairo_context__as__cairo_t(cause, this);
  cairo_close_path(cairo_context);
  return nil;
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_context__close_path(f2ptr cause, f2ptr this) {
  if (! raw__cairo_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__close_path(cause, this);
}
export_cefunk1(cairo_context__close_path, this, 0, "Adds a line segment to the path from the current point to the beginning of the current sub-path, (the most recent point passed to cairo_move_to()), and closes this sub-path. After this call the current point will be at the joined endpoint of the sub-path.

The behavior of cairo_close_path() is distinct from simply calling cairo_line_to() with the equivalent coordinate in the case of stroking. When a closed sub-path is stroked, there are no caps on the ends of the sub-path. Instead, there is a line join connecting the final and initial segments of the sub-path.

If there is no current point before the call to cairo_close_path, this function will have no effect.

Note: As of cairo version 1.2.4 any call to cairo_close_path will place an explicit MOVE_TO element into the path immediately after the CLOSE_PATH element, (which can be seen in cairo_copy_path() for example). This can simplify path processing in some cases as it may not be necessary to save the \"last move_to point\" during processing as the MOVE_TO immediately after the CLOSE_PATH will provide that point.");



f2ptr raw__cairo_context__arc(f2ptr cause, f2ptr this, f2ptr cr, f2ptr xc, f2ptr yc, f2ptr radius, f2ptr angle1, f2ptr angle2) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_t* cairo_context = raw__cairo_context__as__cairo_t(cause, this);
  double   cr__d         = f2double__d(cr, cause);
  double   xc__d         = f2double__d(xc, cause);
  double   yc__d         = f2double__d(yc, cause);
  double   radius__d     = f2double__d(radius, cause);
  double   angle1__d     = f2double__d(angle1, cause);
  double   angle2__d     = f2double__d(angle2, cause);
  cairo_arc(cairo_context, cr__d, xc__d, yc__d, radius__d, angle1__d, angle2__d);
  return nil;
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_context__arc(f2ptr cause, f2ptr this, f2ptr cr, f2ptr xc, f2ptr yc, f2ptr radius, f2ptr angle1, f2ptr angle2) {
  if ((! raw__cairo_context__is_type(cause, this)) ||
      (! raw__double__is_type(cause, cr)) ||
      (! raw__double__is_type(cause, xc)) ||
      (! raw__double__is_type(cause, yc)) ||
      (! raw__double__is_type(cause, radius)) ||
      (! raw__double__is_type(cause, angle1)) ||
      (! raw__double__is_type(cause, angle2))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_context__arc(cause, this, cr, xc, yc, radius, angle1, angle2);
}
export_cefunk7(cairo_context__arc, this, cr, xc, yc, radius, angle1, angle2, 0, "Adds a circular arc of the given radius to the current path. The arc is centered at (xc, yc), begins at angle1 and proceeds in the direction of increasing angles to end at angle2. If angle2 is less than angle1 it will be progressively increased by 2*M_PI until it is greater than angle1.

If there is a current point, an initial line segment will be added to the path to connect the current point to the beginning of the arc.

Angles are measured in radians. An angle of 0.0 is in the direction of the positive X axis (in user space). An angle of M_PI/2.0 radians (90 degrees) is in the direction of the positive Y axis (in user space). Angles increase in the direction from the positive X axis toward the positive Y axis. So with the default transformation matrix, angles increase in a clockwise direction.

(To convert from degrees to radians, use degrees * (M_PI / 180.).)

This function gives the arc in the direction of increasing angles; see cairo_arc_negative() to get the arc in the direction of decreasing angles.

The arc is circular in user space. To achieve an elliptical arc, you can scale the current transformation matrix by different amounts in the X and Y directions. For example, to draw an ellipse in the box given by x, y, width, height:

cairo_save (cr);
cairo_translate (cr, x + width / 2., y + height / 2.);
cairo_scale (cr, width / 2., height / 2.);
cairo_arc (cr, 0., 0., 1., 0., 2 * M_PI);
cairo_restore (cr);

cr : 	a cairo context
xc : 	X position of the center of the arc
yc : 	Y position of the center of the arc
radius : 	the radius of the arc
angle1 : 	the start angle, in radians
angle2 : 	the end angle, in radians");



f2ptr f2__cairo_context_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),               f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_context_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__cairo_context_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_context_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__cairo_context_pointer__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "destroy"),               f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__destroy")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new_path"),              f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__new_path")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "close_path"),            f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__close_path")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "arc"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_context__arc")));}
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
  error(nil, "raw__cairo_format__as__cairo_format_t used incorrectly.");
}

f2ptr raw__cairo_format_t__as__cairo_format(f2ptr cause, cairo_format_t cairo_format) {
  switch(cairo_format) {
  case CAIRO_FORMAT_ARGB32:
    return new__symbol(cause, "ARGB32");
  case CAIRO_FORMAT_RGB24:
    return new__symbol(cause, "RGB24");
  case CAIRO_FORMAT_A8:
    return new__symbol(cause, "A8");
  case CAIRO_FORMAT_A1:
    return new__symbol(cause, "A1");
    //case CAIRO_FORMAT_RGB16_565:
    //return new__symbol(cause, "RGB16_565");
  }
  return new__symbol(cause, "unknown_cairo_format");
}
#endif // F2__CAIRO_SUPPORTED


// cairo_surface

f2ptr f2cairo_surface__new(f2ptr cause, f2ptr cairo_surface_pointer) {
  f2ptr this = f2cairo_object__new(cause, cairo_surface_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_surface"));
  return this;
}

boolean_t raw__cairo_surface__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_surface");
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

f2ptr f2__cairo_surface__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_surface__is_type(cause, thing));
}
export_cefunk1(cairo_surface__is_type, thing, 0, "Returns whether or not thing is of type cairo_surface.");


f2ptr raw__cairo_surface__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_surface__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_surface__type(cause, this);
}
export_cefunk1(cairo_surface__type, thing, 0, "Returns the specific type of object that this cairo_surface is.");


f2ptr raw__cairo_surface__cairo_surface_pointer(f2ptr cause, f2ptr this) {
  return raw__cairo_object__cairo_object_pointer(cause, this);
}

f2ptr f2__cairo_surface__cairo_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_surface__cairo_surface_pointer(cause, this);
}
export_cefunk1(cairo_surface__cairo_surface_pointer, thing, 0, "Returns the cairo_surface_pointer of the cairo_surface.");


#if defined(F2__CAIRO_SUPPORTED)
cairo_surface_t* raw__cairo_surface__as__cairo_surface_t(f2ptr cause, f2ptr this) {
  f2ptr            cairo_surface_pointer = raw__cairo_surface__cairo_surface_pointer(cause, this);
  cairo_surface_t* cairo_surface         = from_ptr(f2pointer__p(cairo_surface_pointer, cause));
  return cairo_surface;
}
#endif // F2__CAIRO_SUPPORTED

f2ptr raw__cairo_surface__cairo_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_object__cairo_object_pointer__set(cause, this, value);
}

f2ptr f2__cairo_surface__cairo_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_surface__cairo_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_surface__cairo_surface_pointer__set, thing, value, 0, "Sets the cairo_surface_pointer of the cairo_surface.");


f2ptr raw__cairo_surface__destroy(f2ptr cause, f2ptr this) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface = raw__cairo_surface__as__cairo_surface_t(cause, this);
  cairo_surface_destroy(cairo_surface);
  return nil;
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_surface__destroy(f2ptr cause, f2ptr this) {
  if (! raw__cairo_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_surface__destroy(cause, this);
}
export_cefunk1(cairo_surface__destroy, this, 0, "Destroys the cairo_surface.");


f2ptr raw__cairo_surface__write_to_png(f2ptr cause, f2ptr this, f2ptr filename) {
  s64 filename__length = raw__string__length(cause, filename);
  u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
  raw__string__str_copy(cause, filename, filename__str);
  filename__str[filename__length] = 0;
  cairo_surface_t* cairo_surface = raw__cairo_surface__as__cairo_surface_t(cause, this);
  cairo_surface_write_to_png(cairo_surface, (char*)filename__str);
  cairo_status_t status = cairo_surface_status(cairo_surface);
  f2__free(to_ptr(filename__str));
  if (status != CAIRO_STATUS_SUCCESS) {
    f2ptr cairo_status;
    switch(status) {
    case CAIRO_STATUS_NO_MEMORY:             cairo_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");             break;
    case CAIRO_STATUS_SURFACE_TYPE_MISMATCH: cairo_status = new__symbol(cause, "CAIRO_STATUS_SURFACE_TYPE_MISMATCH"); break;
    case CAIRO_STATUS_WRITE_ERROR:           cairo_status = new__symbol(cause, "CAIRO_STATUS_WRITE_ERROR");           break;
    default:                                 cairo_status = new__symbol(cause, "unknown_cairo_status");               break;
    }
    return f2larva__new(cause, 1351, f2__bug__new(cause, f2integer__new(cause, 1351), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"),     new__symbol(cause, "error_writing_cairo_surface_to_png_file"),
															 new__symbol(cause, "cairo_status"), cairo_status,
															 new__symbol(cause, "this"),         this,
															 new__symbol(cause, "filename"),     filename))));
  }
  return nil;
}

f2ptr f2__cairo_surface__write_to_png(f2ptr cause, f2ptr this, f2ptr filename) {
  if ((! raw__cairo_surface__is_type(cause, this)) ||
      (! raw__string__is_type(cause, filename))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_surface__write_to_png(cause, this, filename);
}
export_cefunk2(cairo_surface__write_to_png, this, filename, 0, "Writes this cairo_surface to the given filename as a png file.");


f2ptr f2__cairo_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),               f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__cairo_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__cairo_surface_pointer__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "destroy"),               f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__destroy")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "write_to_png"),          f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_surface__write_to_png")));}
  return this;
}



// cairo_image_surface

f2ptr f2cairo_image_surface__new(f2ptr cause, f2ptr cairo_image_surface_pointer) {
  f2ptr this = f2cairo_surface__new(cause, cairo_image_surface_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_image_surface"));
  return this;
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
    case CAIRO_STATUS_NULL_POINTER:    cairo_status = new__symbol(cause, "CAIRO_STATUS_NULL_POINTER");    break;
    case CAIRO_STATUS_NO_MEMORY:       cairo_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");       break;
    case CAIRO_STATUS_READ_ERROR:      cairo_status = new__symbol(cause, "CAIRO_STATUS_READ_ERROR");      break;
    case CAIRO_STATUS_INVALID_CONTENT: cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_CONTENT"); break;
    case CAIRO_STATUS_INVALID_FORMAT:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_FORMAT");  break;
    case CAIRO_STATUS_INVALID_VISUAL:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_VISUAL");  break;
    default:                           cairo_status = new__symbol(cause, "unknown");                      break;
    }
    cairo_surface_destroy(cairo_surface);
    return f2larva__new(cause, 44321, f2__bug__new(cause, f2integer__new(cause, 44321), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),     new__symbol(cause, "failure_to_create_cairo_image_surface"),
															    new__symbol(cause, "cairo_status"), cairo_status,
															    new__symbol(cause, "format"),       format,
															    new__symbol(cause, "width"),        width,
															    new__symbol(cause, "height"),       height))));
  }
  f2ptr cairo_image_surface_pointer = f2pointer__new(cause, to_ptr(cairo_surface));
  return f2cairo_image_surface__new(cause, cairo_image_surface_pointer);
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
  return raw__cairo_surface__cairo_surface_pointer(cause, this);
}

f2ptr f2__cairo_image_surface__cairo_image_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__cairo_image_surface_pointer(cause, this);
}
export_cefunk1(cairo_image_surface__cairo_image_surface_pointer, thing, 0, "Returns the cairo_image_surface_pointer of the cairo_image_surface.");


f2ptr raw__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_surface__cairo_surface_pointer__set(cause, this, value);
}

f2ptr f2__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__cairo_image_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_image_surface__cairo_image_surface_pointer__set, thing, value, 0, "Sets the cairo_image_surface_pointer of the cairo_image_surface.");


f2ptr raw__cairo_image_surface__format(f2ptr cause, f2ptr this) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface = raw__cairo_surface__as__cairo_surface_t(cause, this);
  cairo_format_t   cairo_format  = cairo_image_surface_get_format(cairo_surface);
  return raw__cairo_format_t__as__cairo_format(cause, cairo_format);
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_image_surface__format(f2ptr cause, f2ptr this) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__format(cause, this);
}
export_cefunk1(cairo_image_surface__format, this, 0, "Returns the format of the cairo_image_surface.");


f2ptr raw__cairo_image_surface__as__image(f2ptr cause, f2ptr this) {
  f2ptr format = raw__cairo_image_surface__format(cause, this);
  if (! raw__eq(cause, format, new__symbol(cause, "ARGB32"))) {
    return f2larva__new(cause, 2132, nil);
  }
  cairo_surface_t* cairo_surface = raw__cairo_surface__as__cairo_surface_t(cause, this);
  unsigned char*   data          = cairo_image_surface_get_data(  cairo_surface);
  s64              width         = cairo_image_surface_get_width( cairo_surface);
  s64              height        = cairo_image_surface_get_height(cairo_surface);
  f2ptr            rgba_data     = raw__chunk__new(cause, 4 * width * height);
  s64              stride        = cairo_image_surface_get_stride(cairo_surface);
  {
    s64 y;
    for (y = 0; y < height; y ++) {
      s64 cairo_y_index = (y * stride);
      s64 y_index       = (y * width);
      s64 x;
      for (x = 0; x < width; x ++) {
	s64 cairo_pixel_index = (cairo_y_index + x) << 2;
	u8  alpha             = *(data + cairo_pixel_index + 0);
	u8  red               = *(data + cairo_pixel_index + 1);
	u8  green             = *(data + cairo_pixel_index + 2);
	u8  blue              = *(data + cairo_pixel_index + 3);
	{
	  s64 pixel_index = (y_index + x) << 2;
	  raw__chunk__bit8__elt__set(cause, rgba_data, pixel_index + 0, red);
	  raw__chunk__bit8__elt__set(cause, rgba_data, pixel_index + 1, green);
	  raw__chunk__bit8__elt__set(cause, rgba_data, pixel_index + 2, blue);
	  raw__chunk__bit8__elt__set(cause, rgba_data, pixel_index + 3, alpha);
	}
      }
    }
  }
  return raw__image__new(cause, f2integer__new(cause, width), f2integer__new(cause, height), rgba_data);
}

f2ptr f2__cairo_image_surface__as__image(f2ptr cause, f2ptr this) {
  if (! raw__cairo_image_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_image_surface__as__image(cause, this);
}
export_cefunk1(cairo_image_surface__as__image, this, 0, "Returns a new image representation of this cairo_image_surface.");


f2ptr f2__cairo_image_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_surface")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_image_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__cairo_image_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_image_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__cairo_image_surface_pointer__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "format"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__format")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "as-image"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_image_surface__as__image")));}
  return this;
}



// cairo_svg_surface

f2ptr f2cairo_svg_surface__new(f2ptr cause, f2ptr cairo_svg_surface_pointer) {
  f2ptr this = f2cairo_surface__new(cause, cairo_svg_surface_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_svg_surface"));
  return this;
}

f2ptr raw__cairo_svg_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface;
  {
    s64 filename__length = raw__string__length(cause, filename);
    u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
    raw__string__str_copy(cause, filename, filename__str);
    filename__str[filename__length] = 0;
    double width__d  = f2double__d(width,  cause);
    double height__d = f2double__d(height, cause);
    cairo_surface = cairo_svg_surface_create((char*)filename__str,
					     width__d,
					     height__d);
    f2__free(to_ptr(filename__str));
  }
  cairo_status_t status = cairo_surface_status(cairo_surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    f2ptr cairo_status = nil;
    switch(status) {
    case CAIRO_STATUS_NULL_POINTER:    cairo_status = new__symbol(cause, "CAIRO_STATUS_NULL_POINTER");    break;
    case CAIRO_STATUS_NO_MEMORY:       cairo_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");       break;
    case CAIRO_STATUS_READ_ERROR:      cairo_status = new__symbol(cause, "CAIRO_STATUS_READ_ERROR");      break;
    case CAIRO_STATUS_INVALID_CONTENT: cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_CONTENT"); break;
    case CAIRO_STATUS_INVALID_FORMAT:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_FORMAT");  break;
    case CAIRO_STATUS_INVALID_VISUAL:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_VISUAL");  break;
    default:                           cairo_status = new__symbol(cause, "unknown");                      break;
    }
    cairo_surface_destroy(cairo_surface);
    return f2larva__new(cause, 44321, f2__bug__new(cause, f2integer__new(cause, 44321), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),     new__symbol(cause, "failure_to_create_cairo_svg_surface"),
															    new__symbol(cause, "cairo_status"), cairo_status,
															    new__symbol(cause, "filename"),     filename,
															    new__symbol(cause, "width"),        width,
															    new__symbol(cause, "height"),       height))));
  }
  f2ptr cairo_svg_surface_pointer = f2pointer__new(cause, to_ptr(cairo_surface));
  return f2cairo_svg_surface__new(cause, cairo_svg_surface_pointer);
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_svg_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__double__is_type(cause, width)) ||
      (! raw__double__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_svg_surface__new(cause, filename, width, height);
}
export_cefunk3(cairo_svg_surface__new, filename, width, height, 0, "Returns a new cairo_svg_surface object.");


boolean_t raw__cairo_svg_surface__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_svg_surface");
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

f2ptr f2__cairo_svg_surface__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_svg_surface__is_type(cause, thing));
}
export_cefunk1(cairo_svg_surface__is_type, thing, 0, "Returns whether or not thing is of type cairo_svg_surface.");


f2ptr raw__cairo_svg_surface__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_svg_surface__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_svg_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_svg_surface__type(cause, this);
}
export_cefunk1(cairo_svg_surface__type, thing, 0, "Returns the specific type of object that this cairo_svg_surface is.");


f2ptr raw__cairo_svg_surface__cairo_svg_surface_pointer(f2ptr cause, f2ptr this) {
  return raw__cairo_surface__cairo_surface_pointer(cause, this);
}

f2ptr f2__cairo_svg_surface__cairo_svg_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_svg_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_svg_surface__cairo_svg_surface_pointer(cause, this);
}
export_cefunk1(cairo_svg_surface__cairo_svg_surface_pointer, thing, 0, "Returns the cairo_svg_surface_pointer of the cairo_svg_surface.");


f2ptr raw__cairo_svg_surface__cairo_svg_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_surface__cairo_surface_pointer__set(cause, this, value);
}

f2ptr f2__cairo_svg_surface__cairo_svg_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_svg_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_svg_surface__cairo_svg_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_svg_surface__cairo_svg_surface_pointer__set, thing, value, 0, "Sets the cairo_svg_surface_pointer of the cairo_svg_surface.");


f2ptr f2__cairo_svg_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_surface")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_svg_surface__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_svg_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_svg_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_svg_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_svg_surface__cairo_svg_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_svg_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_svg_surface__cairo_svg_surface_pointer__set")));}
  return this;
}



// cairo_pdf_surface

f2ptr f2cairo_pdf_surface__new(f2ptr cause, f2ptr cairo_pdf_surface_pointer) {
  f2ptr this = f2cairo_surface__new(cause, cairo_pdf_surface_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_pdf_surface"));
  return this;
}

f2ptr raw__cairo_pdf_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface;
  {
    s64 filename__length = raw__string__length(cause, filename);
    u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
    raw__string__str_copy(cause, filename, filename__str);
    filename__str[filename__length] = 0;
    double width__d  = f2double__d(width,  cause);
    double height__d = f2double__d(height, cause);
    cairo_surface = cairo_pdf_surface_create((char*)filename__str,
					     width__d,
					     height__d);
    f2__free(to_ptr(filename__str));
  }
  cairo_status_t status = cairo_surface_status(cairo_surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    f2ptr cairo_status = nil;
    switch(status) {
    case CAIRO_STATUS_NULL_POINTER:    cairo_status = new__symbol(cause, "CAIRO_STATUS_NULL_POINTER");    break;
    case CAIRO_STATUS_NO_MEMORY:       cairo_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");       break;
    case CAIRO_STATUS_READ_ERROR:      cairo_status = new__symbol(cause, "CAIRO_STATUS_READ_ERROR");      break;
    case CAIRO_STATUS_INVALID_CONTENT: cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_CONTENT"); break;
    case CAIRO_STATUS_INVALID_FORMAT:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_FORMAT");  break;
    case CAIRO_STATUS_INVALID_VISUAL:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_VISUAL");  break;
    default:                           cairo_status = new__symbol(cause, "unknown");                      break;
    }
    cairo_surface_destroy(cairo_surface);
    return f2larva__new(cause, 44321, f2__bug__new(cause, f2integer__new(cause, 44321), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),     new__symbol(cause, "failure_to_create_cairo_pdf_surface"),
															    new__symbol(cause, "cairo_status"), cairo_status,
															    new__symbol(cause, "filename"),     filename,
															    new__symbol(cause, "width"),        width,
															    new__symbol(cause, "height"),       height))));
  }
  f2ptr cairo_pdf_surface_pointer = f2pointer__new(cause, to_ptr(cairo_surface));
  return f2cairo_pdf_surface__new(cause, cairo_pdf_surface_pointer);
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_pdf_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__double__is_type(cause, width)) ||
      (! raw__double__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_pdf_surface__new(cause, filename, width, height);
}
export_cefunk3(cairo_pdf_surface__new, filename, width, height, 0, "Returns a new cairo_pdf_surface object.");


boolean_t raw__cairo_pdf_surface__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_pdf_surface");
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

f2ptr f2__cairo_pdf_surface__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_pdf_surface__is_type(cause, thing));
}
export_cefunk1(cairo_pdf_surface__is_type, thing, 0, "Returns whether or not thing is of type cairo_pdf_surface.");


f2ptr raw__cairo_pdf_surface__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_pdf_surface__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_pdf_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_pdf_surface__type(cause, this);
}
export_cefunk1(cairo_pdf_surface__type, thing, 0, "Returns the specific type of object that this cairo_pdf_surface is.");


f2ptr raw__cairo_pdf_surface__cairo_pdf_surface_pointer(f2ptr cause, f2ptr this) {
  return raw__cairo_surface__cairo_surface_pointer(cause, this);
}

f2ptr f2__cairo_pdf_surface__cairo_pdf_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_pdf_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_pdf_surface__cairo_pdf_surface_pointer(cause, this);
}
export_cefunk1(cairo_pdf_surface__cairo_pdf_surface_pointer, thing, 0, "Returns the cairo_pdf_surface_pointer of the cairo_pdf_surface.");


f2ptr raw__cairo_pdf_surface__cairo_pdf_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_surface__cairo_surface_pointer__set(cause, this, value);
}

f2ptr f2__cairo_pdf_surface__cairo_pdf_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_pdf_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_pdf_surface__cairo_pdf_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_pdf_surface__cairo_pdf_surface_pointer__set, thing, value, 0, "Sets the cairo_pdf_surface_pointer of the cairo_pdf_surface.");


f2ptr f2__cairo_pdf_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_surface")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_pdf_surface__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_pdf_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_pdf_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_pdf_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_pdf_surface__cairo_pdf_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_pdf_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_pdf_surface__cairo_pdf_surface_pointer__set")));}
  return this;
}



// cairo_ps_surface

f2ptr f2cairo_ps_surface__new(f2ptr cause, f2ptr cairo_ps_surface_pointer) {
  f2ptr this = f2cairo_surface__new(cause, cairo_ps_surface_pointer);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "cairo_ps_surface"));
  return this;
}

f2ptr raw__cairo_ps_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
#if defined(F2__CAIRO_SUPPORTED)
  cairo_surface_t* cairo_surface;
  {
    s64 filename__length = raw__string__length(cause, filename);
    u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
    raw__string__str_copy(cause, filename, filename__str);
    filename__str[filename__length] = 0;
    double width__d  = f2double__d(width,  cause);
    double height__d = f2double__d(height, cause);
    cairo_surface = cairo_ps_surface_create((char*)filename__str,
					     width__d,
					     height__d);
    f2__free(to_ptr(filename__str));
  }
  cairo_status_t status = cairo_surface_status(cairo_surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    f2ptr cairo_status = nil;
    switch(status) {
    case CAIRO_STATUS_NULL_POINTER:    cairo_status = new__symbol(cause, "CAIRO_STATUS_NULL_POINTER");    break;
    case CAIRO_STATUS_NO_MEMORY:       cairo_status = new__symbol(cause, "CAIRO_STATUS_NO_MEMORY");       break;
    case CAIRO_STATUS_READ_ERROR:      cairo_status = new__symbol(cause, "CAIRO_STATUS_READ_ERROR");      break;
    case CAIRO_STATUS_INVALID_CONTENT: cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_CONTENT"); break;
    case CAIRO_STATUS_INVALID_FORMAT:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_FORMAT");  break;
    case CAIRO_STATUS_INVALID_VISUAL:  cairo_status = new__symbol(cause, "CAIRO_STATUS_INVALID_VISUAL");  break;
    default:                           cairo_status = new__symbol(cause, "unknown");                      break;
    }
    cairo_surface_destroy(cairo_surface);
    return f2larva__new(cause, 44321, f2__bug__new(cause, f2integer__new(cause, 44321), f2__frame__new(cause, f2list10__new(cause,
															    new__symbol(cause, "bug_type"),     new__symbol(cause, "failure_to_create_cairo_ps_surface"),
															    new__symbol(cause, "cairo_status"), cairo_status,
															    new__symbol(cause, "filename"),     filename,
															    new__symbol(cause, "width"),        width,
															    new__symbol(cause, "height"),       height))));
  }
  f2ptr cairo_ps_surface_pointer = f2pointer__new(cause, to_ptr(cairo_surface));
  return f2cairo_ps_surface__new(cause, cairo_ps_surface_pointer);
#else
  return f2__cairo_not_supported_larva__new(cause);
#endif // F2__CAIRO_SUPPORTED
}

f2ptr f2__cairo_ps_surface__new(f2ptr cause, f2ptr filename, f2ptr width, f2ptr height) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__double__is_type(cause, width)) ||
      (! raw__double__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_ps_surface__new(cause, filename, width, height);
}
export_cefunk3(cairo_ps_surface__new, filename, width, height, 0, "Returns a new cairo_ps_surface object.");


boolean_t raw__cairo_ps_surface__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "cairo_ps_surface");
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

f2ptr f2__cairo_ps_surface__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__cairo_ps_surface__is_type(cause, thing));
}
export_cefunk1(cairo_ps_surface__is_type, thing, 0, "Returns whether or not thing is of type cairo_ps_surface.");


f2ptr raw__cairo_ps_surface__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__cairo_ps_surface__type(f2ptr cause, f2ptr this) {
  if (! raw__cairo_ps_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_ps_surface__type(cause, this);
}
export_cefunk1(cairo_ps_surface__type, thing, 0, "Returns the specific type of object that this cairo_ps_surface is.");


f2ptr raw__cairo_ps_surface__cairo_ps_surface_pointer(f2ptr cause, f2ptr this) {
  return raw__cairo_surface__cairo_surface_pointer(cause, this);
}

f2ptr f2__cairo_ps_surface__cairo_ps_surface_pointer(f2ptr cause, f2ptr this) {
  if (! raw__cairo_ps_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_ps_surface__cairo_ps_surface_pointer(cause, this);
}
export_cefunk1(cairo_ps_surface__cairo_ps_surface_pointer, thing, 0, "Returns the cairo_ps_surface_pointer of the cairo_ps_surface.");


f2ptr raw__cairo_ps_surface__cairo_ps_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return raw__cairo_surface__cairo_surface_pointer__set(cause, this, value);
}

f2ptr f2__cairo_ps_surface__cairo_ps_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__cairo_ps_surface__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__cairo_ps_surface__cairo_ps_surface_pointer__set(cause, this, value);
}
export_cefunk2(cairo_ps_surface__cairo_ps_surface_pointer__set, thing, value, 0, "Sets the cairo_ps_surface_pointer of the cairo_ps_surface.");


f2ptr f2__cairo_ps_surface_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "cairo_surface")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_ps_surface__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_ps_surface__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_ps_surface__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_ps_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_ps_surface__cairo_ps_surface_pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, "cairo_ps_surface_pointer"), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo_ps_surface__cairo_ps_surface_pointer__set")));}
  return this;
}


// **

f2ptr f2__cairo__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(cairo__core_extension__ping, 0, "");

f2ptr f2__cairo__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "cairo_object"),        f2__cairo_object_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_context"),       f2__cairo_context_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_surface"),       f2__cairo_surface_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_image_surface"), f2__cairo_image_surface_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_svg_surface"),   f2__cairo_svg_surface_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_pdf_surface"),   f2__cairo_pdf_surface_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "cairo_ps_surface"),    f2__cairo_ps_surface_type__new(cause));
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("cairo initialized.");
  return nil;
}
export_cefunk0(cairo__core_extension__initialize, 0, "");

f2ptr f2__cairo__core_extension__destroy(f2ptr cause) {
  status("cairo destroyed.");
  return nil;
}
export_cefunk0(cairo__core_extension__destroy, 0, "");


