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

#ifndef F2__EXTENSION__TIMELINE__H
#define F2__EXTENSION__TIMELINE__H

#include "../../c/funk2.h"
#include "../cairo/cairo.h"

// timeline_event

def_header_ceframe11(timeline_event,
		     render_frame,
		     height,
		     start_time,
		     end_time,
		     contains_set,
		     is_contained_by_set,
		     next_set,
		     previous_set,
		     causes_set,
		     is_caused_by_set,
		     y_start);

f2ptr     raw__timeline_event__new                      (f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time);
f2ptr      f2__timeline_event__new                      (f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time);
f2ptr     raw__timeline_event__cairo_action_name        (f2ptr cause, f2ptr this);
f2ptr     raw__timeline_event__render_extents           (f2ptr cause, f2ptr this, f2ptr timeline, double* start_position, double* end_position, double* top_position, double* bottom_position);
f2ptr     raw__timeline_event__cairo_render             (f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline);
f2ptr      f2__timeline_event__cairo_render             (f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline);
double    raw__timeline_event__cairo_minimum_width      (f2ptr cause, f2ptr this, f2ptr cairo_context);
double    raw__timeline_event__cairo_minimum_height     (f2ptr cause, f2ptr this, f2ptr cairo_context);
void      raw__timeline_event__add_contains             (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_contains             (f2ptr cause, f2ptr this, f2ptr event);
void      raw__timeline_event__add_is_contained_by      (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_is_contained_by      (f2ptr cause, f2ptr this, f2ptr event);
void      raw__timeline_event__add_next                 (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_next                 (f2ptr cause, f2ptr this, f2ptr event);
void      raw__timeline_event__add_previous             (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_previous             (f2ptr cause, f2ptr this, f2ptr event);
void      raw__timeline_event__add_causes               (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_causes               (f2ptr cause, f2ptr this, f2ptr event);
void      raw__timeline_event__add_is_caused_by         (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__timeline_event__add_is_caused_by         (f2ptr cause, f2ptr this, f2ptr event);
f2ptr     raw__timeline_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__timeline_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__timeline_event_type__new_aux(f2ptr cause);


// timeline

def_header_ceframe14(timeline,
		     timeline_event_set,
		     left_border,
		     right_border,
		     top_border,
		     bottom_border,
		     x_width,
		     y_event_distance,
		     y_connected_part_distance,
		     arrow_head_size,
		     positions_have_been_calculated,
		     minimum_time,
		     maximum_time,
		     connected_part_array,
		     y_height);

f2ptr     raw__timeline__new                      (f2ptr cause);
f2ptr      f2__timeline__new                      (f2ptr cause);
f2ptr     raw__timeline__add_timeline_event       (f2ptr cause, f2ptr this, f2ptr timeline_event);
f2ptr      f2__timeline__add_timeline_event       (f2ptr cause, f2ptr this, f2ptr timeline_event);
f2ptr     raw__timeline__remove_timeline_event    (f2ptr cause, f2ptr this, f2ptr timeline_event);
f2ptr      f2__timeline__remove_timeline_event    (f2ptr cause, f2ptr this, f2ptr timeline_event);
boolean_t raw__timeline__contains_timeline_event  (f2ptr cause, f2ptr this, f2ptr timeline_event);
f2ptr      f2__timeline__contains_timeline_event  (f2ptr cause, f2ptr this, f2ptr timeline_event);
f2ptr     raw__timeline__timeline_events          (f2ptr cause, f2ptr this);
f2ptr      f2__timeline__timeline_events          (f2ptr cause, f2ptr this);
f2ptr     raw__timeline__calculate_positions      (f2ptr cause, f2ptr this);
f2ptr      f2__timeline__calculate_positions      (f2ptr cause, f2ptr this);
f2ptr     raw__timeline__cairo_render             (f2ptr cause, f2ptr this, f2ptr cairo_context);
f2ptr      f2__timeline__cairo_render             (f2ptr cause, f2ptr this, f2ptr cairo_context);
boolean_t raw__timeline__timeline_event__overlaps (f2ptr cause, f2ptr this, f2ptr event_a, f2ptr event_b);
f2ptr      f2__timeline__timeline_event__overlaps (f2ptr cause, f2ptr this, f2ptr event_a, f2ptr event_b);
f2ptr     raw__timeline__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__timeline__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__timeline_type__new_aux(f2ptr cause);

// **

f2ptr f2__timeline__core_extension__ping      (f2ptr cause);
f2ptr f2__timeline__core_extension__initialize(f2ptr cause);
f2ptr f2__timeline__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__TIMELINE__H

