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


// cairo_object

f2ptr        f2cairo_object__new                      (f2ptr cause, f2ptr cairo_object_pointer);
boolean_t raw__cairo_object__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_object__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_object__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_object__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_object__cairo_object_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_object__cairo_object_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_object__cairo_object_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_object__cairo_object_pointer__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__cairo_object_type__new(f2ptr cause);


// cairo_line_cap

boolean_t raw__cairo_line_cap__is_type(f2ptr cause, f2ptr object);


// cairo_font_slant

boolean_t raw__cairo_font_slant__is_type(f2ptr cause, f2ptr object);


// cairo_font_weight

boolean_t raw__cairo_font_weight__is_type(f2ptr cause, f2ptr object);


// cairo_context

f2ptr      f2cairo_context__new                         (f2ptr cause, f2ptr cairo_context_pointer);
f2ptr     raw__cairo_context__new                       (f2ptr cause, f2ptr target);
f2ptr      f2__cairo_context__new                       (f2ptr cause, f2ptr target);
boolean_t raw__cairo_context__is_type                   (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_context__is_type                   (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_context__type                      (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__type                      (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__cairo_context_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__cairo_context_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__cairo_context_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_context__cairo_context_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__cairo_context__destroy                   (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__destroy                   (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__save                      (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__save                      (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__restore                   (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__restore                   (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__new_path                  (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__new_path                  (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__close_path                (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__close_path                (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__arc                       (f2ptr cause, f2ptr this, f2ptr xc, f2ptr yc, f2ptr radius, f2ptr angle1, f2ptr angle2);
f2ptr      f2__cairo_context__arc                       (f2ptr cause, f2ptr this, f2ptr xc, f2ptr yc, f2ptr radius, f2ptr angle1, f2ptr angle2);
f2ptr     raw__cairo_context__set_source_rgba           (f2ptr cause, f2ptr this, f2ptr red, f2ptr green, f2ptr blue, f2ptr alpha);
f2ptr      f2__cairo_context__set_source_rgba           (f2ptr cause, f2ptr this, f2ptr red, f2ptr green, f2ptr blue, f2ptr alpha);
f2ptr     raw__cairo_context__move_to                   (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr      f2__cairo_context__move_to                   (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr     raw__cairo_context__line_to                   (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr      f2__cairo_context__line_to                   (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr     raw__cairo_context__rel_move_to               (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr      f2__cairo_context__rel_move_to               (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr     raw__cairo_context__rel_line_to               (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr      f2__cairo_context__rel_line_to               (f2ptr cause, f2ptr this, f2ptr x, f2ptr y);
f2ptr     raw__cairo_context__text_path                 (f2ptr cause, f2ptr this, f2ptr text);
f2ptr      f2__cairo_context__text_path                 (f2ptr cause, f2ptr this, f2ptr text);
f2ptr     raw__cairo_context__set_line_cap              (f2ptr cause, f2ptr this, f2ptr line_cap);
f2ptr      f2__cairo_context__set_line_cap              (f2ptr cause, f2ptr this, f2ptr line_cap);
f2ptr     raw__cairo_context__fill                      (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__fill                      (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__fill_preserve             (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__fill_preserve             (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__paint                     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__paint                     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__stroke                    (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__stroke                    (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__stroke_preserve           (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_context__stroke_preserve           (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_context__select_font_face          (f2ptr cause, f2ptr this, f2ptr family, f2ptr slant, f2ptr weight);
f2ptr      f2__cairo_context__select_font_face          (f2ptr cause, f2ptr this, f2ptr family, f2ptr slant, f2ptr weight);
f2ptr     raw__cairo_context__set_font_size             (f2ptr cause, f2ptr this, f2ptr size);
f2ptr      f2__cairo_context__set_font_size             (f2ptr cause, f2ptr this, f2ptr size);

f2ptr f2__cairo_context_type__new(f2ptr cause);



// cairo_format

boolean_t raw__cairo_format__is_type(f2ptr cause, f2ptr object);


// cairo_surface

f2ptr      f2cairo_surface__new                         (f2ptr cause, f2ptr cairo_surface_pointer);
boolean_t raw__cairo_surface__is_type                   (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_surface__is_type                   (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_surface__type                      (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_surface__type                      (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_surface__cairo_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_surface__cairo_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_surface__cairo_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_surface__cairo_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__cairo_surface__destroy                   (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_surface__destroy                   (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_surface__write_to_png              (f2ptr cause, f2ptr this, f2ptr filename);
f2ptr      f2__cairo_surface__write_to_png              (f2ptr cause, f2ptr this, f2ptr filename);

f2ptr f2__cairo_surface_type__new(f2ptr cause);



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
f2ptr     raw__cairo_image_surface__format                          (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__format                          (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_image_surface__as__image                       (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_image_surface__as__image                       (f2ptr cause, f2ptr this);

f2ptr f2__cairo_image_surface_type__new(f2ptr cause);



// cairo_svg_surface

f2ptr        f2cairo_svg_surface__new                           (f2ptr cause, f2ptr cairo_svg_surface_pointer);
f2ptr     raw__cairo_svg_surface__new                           (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
f2ptr      f2__cairo_svg_surface__new                           (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
boolean_t raw__cairo_svg_surface__is_type                       (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_svg_surface__is_type                       (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_svg_surface__type                          (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_svg_surface__type                          (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_svg_surface__cairo_svg_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_svg_surface__cairo_svg_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_svg_surface__cairo_svg_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_svg_surface__cairo_svg_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__cairo_svg_surface_type__new(f2ptr cause);



// cairo_pdf_surface

f2ptr        f2cairo_pdf_surface__new                           (f2ptr cause, f2ptr cairo_pdf_surface_pointer);
f2ptr     raw__cairo_pdf_surface__new                           (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
f2ptr      f2__cairo_pdf_surface__new                           (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
boolean_t raw__cairo_pdf_surface__is_type                       (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_pdf_surface__is_type                       (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_pdf_surface__type                          (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_pdf_surface__type                          (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_pdf_surface__cairo_pdf_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_pdf_surface__cairo_pdf_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_pdf_surface__cairo_pdf_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_pdf_surface__cairo_pdf_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__cairo_pdf_surface_type__new(f2ptr cause);



// cairo_ps_surface

f2ptr        f2cairo_ps_surface__new                          (f2ptr cause, f2ptr cairo_ps_surface_pointer);
f2ptr     raw__cairo_ps_surface__new                          (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
f2ptr      f2__cairo_ps_surface__new                          (f2ptr cause, f2ptr filename, f2ptr width, f2ptr height);
boolean_t raw__cairo_ps_surface__is_type                      (f2ptr cause, f2ptr thing);
f2ptr      f2__cairo_ps_surface__is_type                      (f2ptr cause, f2ptr thing);
f2ptr     raw__cairo_ps_surface__type                         (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_ps_surface__type                         (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_ps_surface__cairo_ps_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr      f2__cairo_ps_surface__cairo_ps_surface_pointer     (f2ptr cause, f2ptr this);
f2ptr     raw__cairo_ps_surface__cairo_ps_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__cairo_ps_surface__cairo_ps_surface_pointer__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__cairo_ps_surface_type__new(f2ptr cause);

// **

f2ptr f2__cairo__core_extension__ping(f2ptr cause);
f2ptr f2__cairo__core_extension__initialize(f2ptr cause);
f2ptr f2__cairo__core_extension__destroy(f2ptr cause);

#endif // F2__EXTENSION__CAIRO__H

