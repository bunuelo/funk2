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

#ifndef F2__EXTENSION__CAIRO__H
#define F2__EXTENSION__CAIRO__H

#include "../../c/funk2.h"
#include "../image/image.h"

f2ptr        f2cairo__new(               f2ptr cause, f2ptr cairo_pointer);
f2ptr     raw__cairo__new(               f2ptr cause, f2ptr target);
f2ptr      f2__cairo__new(               f2ptr cause, f2ptr target);
boolean_t raw__cairo__is_type(           f2ptr cause, f2ptr thing);
f2ptr      f2__cairo__is_type(           f2ptr cause, f2ptr thing);
f2ptr     raw__cairo__type(              f2ptr cause, f2ptr this);
f2ptr      f2__cairo__type(              f2ptr cause, f2ptr this);
f2ptr     raw__cairo__cairo_pointer(     f2ptr cause, f2ptr this);
f2ptr      f2__cairo__cairo_pointer(     f2ptr cause, f2ptr this);
f2ptr     raw__cairo__cairo_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo__cairo_pointer__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__cairo_type__new(f2ptr cause);


// cairo_image_surface

f2ptr        f2cairo_image_surface__new                             (f2ptr cause, f2ptr cairo_image_surface_pointer);
f2ptr     raw__cairo_image_surface__new                             (f2ptr cause, f2ptr format, f2ptr width, f2ptr height);
f2ptr      f2__cairo_image_surface__new                             (f2ptr cause, f2ptr format, f2ptr width, f2ptr height);
boolean_t raw__cairo_image_surface__is_type                         (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_image_surface__is_type                         (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_image_surface__type                            (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__type                            (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_image_surface__cairo_image_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__cairo_image_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_image_surface__cairo_image_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__cairo_image_surface__destroy                         (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__destroy                         (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_image_surface__format                          (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__format                          (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_image_surface__as__image                       (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__as__image                       (f2ptr cause, f2ptr this);

f2ptr f2__cairo_image_surface_type__new(f2ptr cause);

// **

f2ptr f2__cairo__core_extension__ping(f2ptr cause);
f2ptr f2__cairo__core_extension__initialize(f2ptr cause);
f2ptr f2__cairo__core_extension__destroy(f2ptr cause);

#endif // F2__EXTENSION__CAIRO__H

