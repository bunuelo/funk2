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

#ifndef F2__EXTENSION__IMAGE_SEQUENCE__H
#define F2__EXTENSION__IMAGE_SEQUENCE__H

f2ptr     raw__image_sequence__new(                  f2ptr cause, f2ptr images);
f2ptr      f2__image_sequence__new(                  f2ptr cause, f2ptr images);
boolean_t raw__image_sequence__is_type(              f2ptr cause, f2ptr thing);
f2ptr      f2__image_sequence__is_type(              f2ptr cause, f2ptr thing);
f2ptr     raw__image_sequence__type(                 f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__type(                 f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__first_image_link(     f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__first_image_link(     f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image_sequence__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__image_sequence__last_image_link(      f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__last_image_link(      f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__last_image_link__set( f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image_sequence__last_image_link__set( f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__image_sequence__images(               f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__images(               f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__images__set(          f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__image_sequence__images__set(          f2ptr cause, f2ptr this, f2ptr value);
s64       raw__image_sequence__length(               f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__length(               f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__width(                f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__width(                f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__height(               f2ptr cause, f2ptr this);
f2ptr      f2__image_sequence__height(               f2ptr cause, f2ptr this);
f2ptr     raw__image_sequence__add_image_to_end(     f2ptr cause, f2ptr this, f2ptr image);
f2ptr      f2__image_sequence__add_image_to_end(     f2ptr cause, f2ptr this, f2ptr image);
f2ptr     raw__image_sequence__elt(                  f2ptr cause, f2ptr this, s64 index);
f2ptr      f2__image_sequence__elt(                  f2ptr cause, f2ptr this, f2ptr index);
f2ptr      f2__image_sequence_type__new(             f2ptr cause);

// **

f2ptr f2__image_sequence__core_extension__ping(      f2ptr cause);
f2ptr f2__image_sequence__core_extension__initialize(f2ptr cause);
f2ptr f2__image_sequence__core_extension__destroy(   f2ptr cause);

#endif // F2__EXTENSION__IMAGE_SEQUENCE__H
