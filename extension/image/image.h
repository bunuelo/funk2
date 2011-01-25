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

#ifndef F2__EXTENSION__IMAGE__H
#define F2__EXTENSION__IMAGE__H

f2ptr     raw__image__new(                       f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data);
f2ptr      f2__image__new(                       f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data);
f2ptr     raw__image__new_from_rgb_data(         f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data);
f2ptr      f2__image__new_from_rgb_data(         f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data);
boolean_t raw__image__is_type(                   f2ptr cause, f2ptr thing);
f2ptr      f2__image__is_type(                   f2ptr cause, f2ptr thing);
f2ptr     raw__image__type(                      f2ptr cause, f2ptr this);
f2ptr      f2__image__type(                      f2ptr cause, f2ptr this);
f2ptr     raw__image__width(                     f2ptr cause, f2ptr this);
f2ptr      f2__image__width(                     f2ptr cause, f2ptr this);
f2ptr     raw__image__width__set(                f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image__width__set(                f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__image__height(                    f2ptr cause, f2ptr this);
f2ptr      f2__image__height(                    f2ptr cause, f2ptr this);
f2ptr     raw__image__height__set(               f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image__height__set(               f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__image__rgba_data(                 f2ptr cause, f2ptr this);
f2ptr      f2__image__rgba_data(                 f2ptr cause, f2ptr this);
f2ptr     raw__image__rgba_data__set(            f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image__rgba_data__set(            f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__image__write_reduction_image_part(f2ptr cause, f2ptr this, f2ptr reduced_image, f2ptr reduction_factor, f2ptr x_offset, f2ptr y_offset);
f2ptr      f2__image__write_reduction_image_part(f2ptr cause, f2ptr this, f2ptr reduced_image, f2ptr reduction_factor, f2ptr x_offset, f2ptr y_offset);

f2ptr f2__image_type__new(f2ptr cause);

// **

f2ptr f2__image__core_extension_ping(f2ptr cause);
f2ptr f2__image__core_extension_initialize(f2ptr cause);
f2ptr f2__image__core_extension_destroy(f2ptr cause);

#endif // F2__EXTENSION__IMAGE__H

