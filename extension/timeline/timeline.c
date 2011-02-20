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

#include "timeline.h"

void raw__cairo_context__render_outlined_box(f2ptr cause,
					     f2ptr this,
					     double x0,
					     double y0,
					     double dx,
					     double dy,
					     double outline_width,
					     double foreground_red,
					     double foreground_green,
					     double foreground_blue,
					     double foreground_alpha,
					     double background_red,
					     double background_green,
					     double background_blue,
					     double background_alpha) {
  raw__cairo_context__move_to(        cause, this,  x0,  y0);
  raw__cairo_context__rel_line_to(    cause, this,  dx,   0);
  raw__cairo_context__rel_line_to(    cause, this,   0,  dy);
  raw__cairo_context__rel_line_to(    cause, this, -dx,   0);
  raw__cairo_context__rel_line_to(    cause, this,   0, -dy);
  raw__cairo_context__set_line_width( cause, this, outline_width);
  raw__cairo_context__set_source_rgba(cause, this, foreground_red, foreground_green, foreground_blue, foreground_alpha);
  raw__cairo_context__stroke_preserve(cause, this);
  raw__cairo_context__set_source_rgba(cause, this, background_red, background_green, background_blue, background_alpha);
  raw__cairo_context__fill(           cause, this);
}

void raw__cairo_context__render_outlined_rounded_box(f2ptr cause,
						     f2ptr this,
						     double x0,
						     double y0,
						     double dx,
						     double dy,
						     double maximum_corner_radius,
						     double outline_width,
						     double foreground_red,
						     double foreground_green,
						     double foreground_blue,
						     double foreground_alpha,
						     double background_red,
						     double background_green,
						     double background_blue,
						     double background_alpha) {
  double corner_radius = maximum_corner_radius;
  raw__cairo_context__move_to(        cause, this, x0 + corner_radius, y0);
  raw__cairo_context__arc(            cause, this, x0 + corner_radius, y0 + corner_radius, corner_radius, M_PI, 3 * M_PI / 2);
  raw__cairo_context__rel_line_to(    cause, this, dx - (corner_radius * 2), 0);
  raw__cairo_context__arc(            cause, this, x0 + dx - corner_radius, y0 + corner_radius, corner_radius, 3 * M_PI / 2, 2 * M_PI);
  raw__cairo_context__rel_line_to(    cause, this, 0, dy - (corner_radius * 2));
  raw__cairo_context__arc(            cause, this, x0 + dx - corner_radius, y0 + dy - corner_radius, corner_radius, 0, M_PI / 2);
  raw__cairo_context__rel_line_to(    cause, this, -(dx - (corner_radius * 2)), 0);
  raw__cairo_context__arc(            cause, this, x0 + corner_radius, y0 + dy - corner_radius, corner_radius, M_PI / 2, M_PI);
  raw__cairo_context__rel_line_to(    cause, this, 0, -(dy - (corner_radius * 2)));
  raw__cairo_context__close_path(     cause, this);
  
  raw__cairo_context__set_line_width( cause, this, outline_width);
  raw__cairo_context__set_source_rgba(cause, this, foreground_red, foreground_green, foreground_blue, foreground_alpha);
  raw__cairo_context__stroke_preserve(cause, this);
  raw__cairo_context__set_source_rgba(cause, this, background_red, background_green, background_blue, background_alpha);
  raw__cairo_context__fill(           cause, this);
}

void raw__cairo_context__render_outlined_text(f2ptr cause, f2ptr this, double x0, double y0, double font_size, char* text, double outline_width, double red, double green, double blue, double alpha, double outline_red, double outline_green, double outline_blue, double outline_alpha) {
  raw__cairo_context__move_to(        cause, this, x0, y0 + (font_size * 0.75));
  raw__cairo_context__set_font_size(  cause, this, font_size);
  raw__cairo_context__text_path(      cause, this, text);
  raw__cairo_context__set_source_rgba(cause, this, outline_red, outline_green, outline_blue, outline_alpha);
  raw__cairo_context__set_line_width( cause, this, outline_width);
  raw__cairo_context__stroke_preserve(cause, this);
  raw__cairo_context__set_source_rgba(cause, this, red, green, blue, alpha);
  raw__cairo_context__fill(           cause, this);
}

double raw__cairo_context__text_width(f2ptr cause, f2ptr this, double font_size, char* text) {
  raw__cairo_context__set_font_size(cause, this, font_size);
  f2ptr text_extents = raw__cairo_context__text_extents(cause, this, text);
  if (raw__larva__is_type(cause, text_extents)) {
    return 0.0;
  }
  f2ptr text_extents__width     = raw__cairo_text_extents__width(cause, text_extents);
  double text_extents__width__d = f2double__d(text_extents__width, cause);
  return text_extents__width__d;
}

f2ptr raw__cairo_context__render_centered_outlined_text(f2ptr cause, f2ptr this, double cx, double cy, double font_size, char* text, double outline_width, double red, double green, double blue, double alpha, double outline_red, double outline_green, double outline_blue, double outline_alpha) {
  raw__cairo_context__set_font_size(cause, this, font_size);
  f2ptr text_extents = raw__cairo_context__text_extents(cause, this, text);
  if (raw__larva__is_type(cause, text_extents)) {
    return text_extents;
  }
  f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
  double text_extents__width__d = f2double__d(text_extents__width, cause);
  double x0 = cx - (text_extents__width__d / 2);
  double y0 = cy - (font_size              / 2);
  raw__cairo_context__render_outlined_text(cause, this, x0, y0, font_size, text, outline_width, red, green, blue, alpha, outline_red, outline_green, outline_blue, outline_alpha);
  return nil;
}

f2ptr raw__cairo_context__render_rounded_text_box(f2ptr cause, f2ptr this, double x0, double y0, double dx, double dy, double font_size, char* text,
						 double maximum_corner_radius,
						 double background_red, double background_green, double background_blue, double background_alpha,
						 double outline_width,
						 double text_red, double text_green, double text_blue, double text_alpha,
						 double outline_red, double outline_green, double outline_blue, double outline_alpha) {
  raw__cairo_context__render_outlined_rounded_box(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, outline_red, outline_green, outline_blue, outline_alpha,  background_red, background_green, background_blue, background_alpha);
  {
    f2ptr result = raw__cairo_context__render_centered_outlined_text(cause, this, x0 + (dx / 2), y0 + (dy / 2), font_size, text, outline_width,  text_red, text_green, text_blue, text_alpha,  outline_red, outline_green, outline_blue, outline_alpha);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}



// timeline_event

def_ceframe7(timeline, timeline_event, name, start_time, end_time, contains_set, is_contained_by_set, next_set, previous_set);


f2ptr raw__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  f2ptr contains_set        = f2__set__new(cause);
  f2ptr is_contained_by_set = f2__set__new(cause);
  f2ptr next_set            = f2__set__new(cause);
  f2ptr previous_set        = f2__set__new(cause);
  return f2timeline_event__new(cause, name, start_time, end_time, contains_set, is_contained_by_set, next_set, previous_set);
}

f2ptr f2__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  if ((! raw__time__is_type(cause, start_time)) ||
      (! raw__time__is_type(cause, end_time))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr is_less_than = f2__is_less_than(cause, start_time, end_time);
  if (raw__larva__is_type(cause, is_less_than)) {
    return is_less_than;
  }
  if (is_less_than == nil) {
    return f2larva__new(cause, 1351, nil);
  }
  return raw__timeline_event__new(cause, name, start_time, end_time);
}
export_cefunk3(timeline_event__new, name, start_time, end_time, 0, "Returns a new timeline_event object.");


f2ptr raw__timeline_event__cairo_action_name(f2ptr cause, f2ptr this) {
  f2ptr name = raw__timeline_event__name(cause, this);
  f2ptr name_as_string;
  if (name != nil) {
    if (raw__string__is_type(cause, name)) {
      name_as_string = name;
    } else {
      name_as_string = f2__exp__as__string(cause, name);
      if (raw__larva__is_type(cause, name_as_string)) {
	return name_as_string;
      }
    }
  } else {
    name_as_string = new__string(cause, "Event");
  }
  return name_as_string;
}

f2ptr raw__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline) {
  f2ptr  minimum_time                            = raw__timeline__minimum_time(cause, timeline);
  f2ptr  minimum_time__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, minimum_time);
  s64    minimum_time__nanoseconds_since_1970__i = f2integer__i(minimum_time__nanoseconds_since_1970, cause);
  printf("\nminimum_time__nanoseconds_since_1970__i=" s64__fstr, minimum_time__nanoseconds_since_1970__i); fflush(stdout);
  f2ptr  maximum_time                            = raw__timeline__maximum_time(cause, timeline);
  f2ptr  maximum_time__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, maximum_time);
  s64    maximum_time__nanoseconds_since_1970__i = f2integer__i(maximum_time__nanoseconds_since_1970, cause);
  printf("\nmaximum_time__nanoseconds_since_1970__i=" s64__fstr, maximum_time__nanoseconds_since_1970__i); fflush(stdout);
  f2ptr  start_time                              = raw__timeline_event__start_time(cause, this);
  f2ptr  start_time__nanoseconds_since_1970      = f2__time__nanoseconds_since_1970(cause, start_time);
  s64    start_time__nanoseconds_since_1970__i   = f2integer__i(start_time__nanoseconds_since_1970, cause);
  printf("\nstart_time__nanoseconds_since_1970__i=" s64__fstr, start_time__nanoseconds_since_1970__i); fflush(stdout);
  f2ptr  end_time                                = raw__timeline_event__end_time(cause, this);
  f2ptr  end_time__nanoseconds_since_1970        = f2__time__nanoseconds_since_1970(cause, end_time);
  s64    end_time__nanoseconds_since_1970__i     = f2integer__i(end_time__nanoseconds_since_1970, cause);
  printf("\nend_time__nanoseconds_since_1970__i=" s64__fstr, end_time__nanoseconds_since_1970__i); fflush(stdout);
  s64    total_nanoseconds                       = maximum_time__nanoseconds_since_1970__i - minimum_time__nanoseconds_since_1970__i;
  printf("\ntotal_nanoseconds=" s64__fstr, total_nanoseconds); fflush(stdout);
  s64    start_nanoseconds                       = start_time__nanoseconds_since_1970__i   - minimum_time__nanoseconds_since_1970__i;
  printf("\nstart_nanoseconds=" s64__fstr, start_nanoseconds); fflush(stdout);
  s64    end_nanoseconds                         = end_time__nanoseconds_since_1970__i     - minimum_time__nanoseconds_since_1970__i;
  printf("\nend_nanoseconds=" s64__fstr, end_nanoseconds); fflush(stdout);
  if (total_nanoseconds == 0) {
    return f2larva__new(cause, 4444, nil);
  }
  double start_position                          = ((double)(start_nanoseconds * 56000ull / total_nanoseconds)) / 1000.0;
  double end_position                            = ((double)(end_nanoseconds   * 56000ull / total_nanoseconds)) / 1000.0;
  printf("\nstart_position=%f", start_position); fflush(stdout);
  printf("\nend_position=%f",   end_position);   fflush(stdout);
  f2ptr  action_name                             = raw__timeline_event__cairo_action_name(cause, this);
  s64    action_name__length                     = raw__string__length(cause, action_name);
  u8*    action_name__str                        = (u8*)from_ptr(f2__malloc(action_name__length));
  raw__string__str_copy(cause, action_name, action_name__str);
  action_name__str[action_name__length] = 0;
  raw__cairo_context__save(cause, cairo_context);
  {
    double text_width  = raw__cairo_context__text_width(cause, cairo_context, 1, (char*)action_name__str);
    double event_width = (double)((int)(text_width + 1.5));
    f2ptr  result      = raw__cairo_context__render_rounded_text_box(cause, cairo_context,
								     start_position, 0,                       // x0, y0
								     end_position - start_position, 1.5,      // dx, dy
								     1,                                       // font size
								     (char*)action_name__str,                 // text
								     0.5,                                     // maximum corner radius
								     30 / 255.0, 144 / 255.0, 255 / 255.0, 1, // background rgba
								     0.1,                                     // outline width
								     1, 1, 1, 1,                              // text rgba
								     0, 0, 0, 1);                             // outline rgba
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__free(to_ptr(action_name__str));
  raw__cairo_context__restore(cause, cairo_context);
  return nil;
}

f2ptr f2__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__cairo_context__is_type(cause, cairo_context)) ||
      (! raw__timeline__is_type(cause, timeline))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline_event__cairo_render(cause, this, cairo_context, timeline);
}
export_cefunk3(timeline_event__cairo_render, this, cairo_context, timeline, 0, "Renders this timeline_event in the given cairo_context.");


double raw__timeline_event__cairo_minimum_width(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  f2ptr action_name         = raw__timeline_event__cairo_action_name(cause, this);
  s64   action_name__length = raw__string__length(cause, action_name);
  u8*   action_name__str    = (u8*)from_ptr(f2__malloc(action_name__length));
  raw__string__str_copy(cause, action_name, action_name__str);
  action_name__str[action_name__length] = 0;
  raw__cairo_context__save(cause, cairo_context);
  double text_width  = raw__cairo_context__text_width(cause, cairo_context, 1, (char*)action_name__str);
  double event_width = (double)((int)(text_width + 1.5));
  f2__free(to_ptr(action_name__str));
  return event_width;
}


double raw__timeline_event__cairo_minimum_height(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  return 1.5;
}


void raw__timeline_event__add_contains(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr contains_set = raw__timeline_event__contains_set(cause, this);
  raw__set__add(cause, contains_set, event);
  f2ptr event__is_contained_by_set = raw__timeline_event__is_contained_by_set(cause, event);
  raw__set__add(cause, event__is_contained_by_set, this);
}

f2ptr f2__timeline_event__add_contains(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline_event__add_contains(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_contains, this, event, 0, "");


void raw__timeline_event__add_is_contained_by(f2ptr cause, f2ptr this, f2ptr event) {
  raw__timeline_event__add_contains(cause, event, this);
}

f2ptr f2__timeline_event__add_is_contained_by(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline_event__add_is_contained_by(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_is_contained_by, this, event, 0, "");


void raw__timeline_event__add_next(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr next_set = raw__timeline_event__next_set(cause, this);
  raw__set__add(cause, next_set, event);
  f2ptr event__previous_set = raw__timeline_event__previous_set(cause, event);
  raw__set__add(cause, event__previous_set, this);
}

f2ptr f2__timeline_event__add_next(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline_event__add_next(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_next, this, event, 0, "");


void raw__timeline_event__add_previous(f2ptr cause, f2ptr this, f2ptr event) {
  raw__timeline_event__add_next(cause, event, this);
}

f2ptr f2__timeline_event__add_previous(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline_event__add_previous(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_previous, this, event, 0, "");


f2ptr raw__timeline_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "timeline_event")));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__timeline_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__timeline_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline_event__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(timeline_event__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__timeline_event_type__new_aux(f2ptr cause) {
  f2ptr this = f2__timeline_event_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "cairo_render"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__cairo_render")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_contains"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_contains")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_is_contained_by"),       f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_is_contained_by")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_next"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_next")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_previous"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_previous")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__terminal_print_with_frame")));}
  return this;
}







// timeline

def_ceframe3(timeline, timeline,
	     timeline_event_set,
	     minimum_time,
	     maximum_time);


f2ptr raw__timeline__new(f2ptr cause) {
  f2ptr timeline_event_set = f2__set__new(cause);
  f2ptr minimum_time       = nil;
  f2ptr maximum_time       = nil;
  return f2timeline__new(cause, timeline_event_set, minimum_time, maximum_time);
}

f2ptr f2__timeline__new(f2ptr cause) {
  return raw__timeline__new(cause);
}
export_cefunk0(timeline__new, 0, "Returns a new timeline object.");


f2ptr raw__timeline__add_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  if (raw__set__contains(cause, timeline_event_set, timeline_event)) {
    return f2larva__new(cause, 1235, f2__bug__new(cause, f2integer__new(cause, 1235), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"),       new__symbol(cause, "timeline_already_contains_timeline_event"),
															 new__symbol(cause, "funkname"),       new__symbol(cause, "timeline-add_timeline_event"),
															 new__symbol(cause, "this"),           this,
															 new__symbol(cause, "timeline_event"), timeline_event))));
  }
  raw__set__add(cause, timeline_event_set, timeline_event);
  return nil;
}

f2ptr f2__timeline__add_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, timeline_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__add_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__add_timeline_event, this, timeline_event, 0, "Adds a timeline_event to a timeline.");


f2ptr raw__timeline__remove_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  if (! raw__set__contains(cause, timeline_event_set, timeline_event)) {
    return f2larva__new(cause, 1236, f2__bug__new(cause, f2integer__new(cause, 1236), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"),       new__symbol(cause, "timeline_does_not_contain_timeline_event"),
															 new__symbol(cause, "funkname"),       new__symbol(cause, "timeline-remove_timeline_event"),
															 new__symbol(cause, "this"),           this,
															 new__symbol(cause, "timeline_event"), timeline_event))));
  }
  raw__set__remove(cause, timeline_event_set, timeline_event);
  return nil;
}

f2ptr f2__timeline__remove_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, timeline_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__remove_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__remove_timeline_event, this, timeline_event, 0, "Removes a timeline_event from a timeline.");


boolean_t raw__timeline__contains_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  return raw__set__contains(cause, timeline_event_set, timeline_event);
}

f2ptr f2__timeline__contains_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, timeline_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__contains_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__contains_timeline_event, this, timeline_event, 0, "Returns whether or not a timeline contains a timeline_event.");


f2ptr raw__timeline__timeline_events(f2ptr cause, f2ptr this) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  return raw__set__elements(cause, timeline_event_set);
}

f2ptr f2__timeline__timeline_events(f2ptr cause, f2ptr this) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__timeline_events(cause, this);
}
export_cefunk1(timeline__timeline_events, this, 0, "Returns a new list of the timeline_events contained within this timeline.");


f2ptr raw__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__set_source_rgba(cause, cairo_context, 0, 0, 0, 1);
  raw__cairo_context__set_line_width(cause, cairo_context, 0.001);
  // box
  raw__cairo_context__rel_line_to(cause, cairo_context,  1,  0);
  raw__cairo_context__rel_line_to(cause, cairo_context,  0,  1);
  raw__cairo_context__rel_line_to(cause, cairo_context, -1,  0);
  raw__cairo_context__rel_line_to(cause, cairo_context,  0, -1);
  raw__cairo_context__stroke(cause, cairo_context);
  {
    s64 y;
    for (y = 0; y < (64 - 1); y ++) {
      s64 x;
      for (x = 0; x < (64 - 1); x ++) {
	raw__cairo_context__arc(cause, cairo_context, (x + 1.0) / 64.0, (y + 1.0) / 64.0, 0.001, 0, 2 * cairo_pi);
	raw__cairo_context__fill(cause, cairo_context);
      }
    }
  }
  raw__cairo_context__move_to(cause, cairo_context, 0, 0);
  {
    f2ptr minimum_time = raw__timeline__minimum_time(cause, this);
    f2ptr maximum_time = raw__timeline__maximum_time(cause, this);
    if ((minimum_time == nil) ||
	(maximum_time == nil)) {
      f2ptr timeline_event_set   = raw__timeline__timeline_event_set(cause, this);
      set__iteration(cause, timeline_event_set, event,
		     f2ptr start_time = raw__timeline_event__start_time(cause, event);
		     f2ptr end_time   = raw__timeline_event__end_time(  cause, event);
		     if ((minimum_time == nil) ||
			 (f2__is_less_than(cause, start_time, minimum_time) != nil)) {
		       minimum_time = start_time;
		     }
		     if ((maximum_time == nil) ||
			 (f2__is_greater_than(cause, end_time, maximum_time) != nil)) {
		       maximum_time = end_time;
		     }
		     );
    }
    raw__timeline__minimum_time__set(cause, this, minimum_time);
    raw__timeline__maximum_time__set(cause, this, maximum_time);
  }
  f2ptr connected_sets = nil;
  // find connected sets of timeline_events
  {
    f2ptr timeline_event_set   = raw__timeline__timeline_event_set(cause, this);
    f2ptr connected_set_event_hash = f2__ptypehash__new(cause);
    {
      f2ptr event_set_elements = raw__set__elements(cause, timeline_event_set);
      {
	f2ptr iter = event_set_elements;
	while (iter != nil) {
	  f2ptr event = f2cons__car(iter, cause);
	  f2ptr connected_set = raw__ptypehash__lookup(cause, connected_set_event_hash, event);
	  if (connected_set == nil) {
	    connected_set  = f2__set__new(cause);
	    connected_sets = f2cons__new(cause, connected_set, connected_sets);
	    f2ptr expansion_event_set = f2__set__new(cause);
	    raw__set__add(cause, expansion_event_set, event);
	    while (! raw__set__is_empty(cause, expansion_event_set)) {
	      f2ptr expand_event = raw__set__an_arbitrary_element(cause, expansion_event_set);
	      raw__ptypehash__add(cause, connected_set_event_hash, expand_event, connected_set);
	      raw__set__add(      cause, connected_set,            expand_event);
	      {
		f2ptr next_set = raw__timeline_event__next_set(cause, expand_event);
		if (next_set != nil) {
		  set__iteration(cause, next_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr previous_set = raw__timeline_event__previous_set(cause, expand_event);
		if (previous_set != nil) {
		  set__iteration(cause, previous_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr contains_set = raw__timeline_event__contains_set(cause, expand_event);
		if (contains_set != nil) {
		  set__iteration(cause, contains_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr is_contained_by_set = raw__timeline_event__is_contained_by_set(cause, expand_event);
		if (is_contained_by_set != nil) {
		  set__iteration(cause, is_contained_by_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      raw__set__remove(cause, expansion_event_set, expand_event);
	    }
	  }
	  iter = f2cons__cdr(iter, cause);
	}
      }
    }
  }
  {
    double y_position         = 0;
    f2ptr  connected_set_iter = connected_sets;
    while (connected_set_iter != nil) {
      f2ptr connected_set = f2cons__car(connected_set_iter, cause);
      {
	set__iteration(cause, connected_set, event,
		       //f2ptr extents = raw__ptypehash__lookup(cause, extents_event_hash, event);
		       raw__cairo_context__save(         cause, cairo_context);
		       raw__cairo_context__scale(        cause, cairo_context, (1.0 / 64.0), (1.0 / 64.0));
		       raw__cairo_context__translate(    cause, cairo_context, 4, 4 + y_position);
		       f2ptr result = raw__timeline_event__cairo_render(cause, event, cairo_context, this);
		       if (raw__larva__is_type(cause, result)) {
			 return result;
		       }
		       raw__cairo_context__restore(      cause, cairo_context);
		       y_position += 2.0;
		       );
	y_position += 1.0;
      }
      connected_set_iter = f2cons__cdr(connected_set_iter, cause);
    }
  }
  raw__cairo_context__restore(cause, cairo_context);
  return nil;
}

f2ptr f2__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__cairo_context__is_type(cause, cairo_context))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__cairo_render(cause, this, cairo_context);
}
export_cefunk2(timeline__cairo_render, this, cairo_context, 0, "Renders this timeline within the given cairo_context.");



f2ptr raw__timeline__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"),  new__symbol(cause, "timeline"),
					       new__symbol(cause, "timeline_events"),    raw__timeline__timeline_events(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__timeline__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(timeline__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__timeline_type__new_aux(f2ptr cause) {
  f2ptr this = f2__timeline_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_timeline_event"),        f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__add_timeline_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_timeline_event"),     f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__remove_timeline_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "contains_timeline_event"),   f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__contains_timeline_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "timeline_events"),           f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__timeline_events")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "cairo_render"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__cairo_render")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__terminal_print_with_frame")));}
  return this;
}



// **

f2ptr f2__timeline__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(timeline__core_extension__ping, 0, "");

f2ptr f2__timeline__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "timeline_event"), f2__timeline_event_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "timeline"),       f2__timeline_type__new_aux(cause));
  status("timeline initialized.");
  return nil;
}
export_cefunk0(timeline__core_extension__initialize, 0, "");

f2ptr f2__timeline__core_extension__destroy(f2ptr cause) {
  status("timeline destroyed.");
  return nil;
}
export_cefunk0(timeline__core_extension__destroy, 0, "");


