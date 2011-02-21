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
						  double box_outline_red, double box_outline_green, double box_outline_blue, double box_outline_alpha,
						  double text_outline_red, double text_outline_green, double text_outline_blue, double text_outline_alpha) {
  raw__cairo_context__render_outlined_rounded_box(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, box_outline_red, box_outline_green, box_outline_blue, box_outline_alpha,  background_red, background_green, background_blue, background_alpha);
  {
    f2ptr result = raw__cairo_context__render_centered_outlined_text(cause, this, x0 + (dx / 2), y0 + (dy / 2), font_size, text, outline_width,  text_red, text_green, text_blue, text_alpha,  text_outline_red, text_outline_green, text_outline_blue, text_outline_alpha);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}



// timeline_event

def_ceframe8(timeline, timeline_event,
	     name,
	     start_time,
	     end_time,
	     contains_set,
	     is_contained_by_set,
	     next_set,
	     previous_set,
	     y_index);


f2ptr raw__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  f2ptr contains_set        = f2__set__new(cause);
  f2ptr is_contained_by_set = f2__set__new(cause);
  f2ptr next_set            = f2__set__new(cause);
  f2ptr previous_set        = f2__set__new(cause);
  return f2timeline_event__new(cause, name, start_time, end_time, contains_set, is_contained_by_set, next_set, previous_set, nil);
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
  f2ptr  maximum_time                            = raw__timeline__maximum_time(cause, timeline);
  f2ptr  maximum_time__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, maximum_time);
  s64    maximum_time__nanoseconds_since_1970__i = f2integer__i(maximum_time__nanoseconds_since_1970, cause);
  f2ptr  start_time                              = raw__timeline_event__start_time(cause, this);
  f2ptr  start_time__nanoseconds_since_1970      = f2__time__nanoseconds_since_1970(cause, start_time);
  s64    start_time__nanoseconds_since_1970__i   = f2integer__i(start_time__nanoseconds_since_1970, cause);
  f2ptr  end_time                                = raw__timeline_event__end_time(cause, this);
  f2ptr  end_time__nanoseconds_since_1970        = f2__time__nanoseconds_since_1970(cause, end_time);
  s64    end_time__nanoseconds_since_1970__i     = f2integer__i(end_time__nanoseconds_since_1970, cause);
  s64    total_nanoseconds                       = maximum_time__nanoseconds_since_1970__i - minimum_time__nanoseconds_since_1970__i;
  s64    start_nanoseconds                       = start_time__nanoseconds_since_1970__i   - minimum_time__nanoseconds_since_1970__i;
  s64    end_nanoseconds                         = end_time__nanoseconds_since_1970__i     - minimum_time__nanoseconds_since_1970__i;
  if (total_nanoseconds == 0) {
    return f2larva__new(cause, 4444, nil);
  }
  double start_position                          = ((double)(start_nanoseconds * 56000ull / total_nanoseconds)) / 1000.0;
  double end_position                            = ((double)(end_nanoseconds   * 56000ull / total_nanoseconds)) / 1000.0;
  f2ptr  action_name                             = raw__timeline_event__cairo_action_name(cause, this);
  s64    action_name__length                     = raw__string__length(cause, action_name);
  u8*    action_name__str                        = (u8*)from_ptr(f2__malloc(action_name__length));
  raw__string__str_copy(cause, action_name, action_name__str);
  action_name__str[action_name__length] = 0;
  f2ptr y_index    = raw__timeline_event__y_index(cause, this);
  s64   y_index__i = f2integer__i(y_index, cause);
  
  raw__cairo_context__save(cause, cairo_context);
  {
    //double text_width  = raw__cairo_context__text_width(cause, cairo_context, 1, (char*)action_name__str);
    //double event_width = (double)((int)(text_width + 1.5));
    f2ptr  result      = raw__cairo_context__render_rounded_text_box(cause, cairo_context,
								     start_position, y_index__i * 2.0,          // x0, y0
								     end_position - start_position, 1.5,        // dx, dy
								     1,                                         // font size
								     (char*)action_name__str,                   // text
								     0.5,                                       // maximum corner radius
								     142 / 255.0, 200 / 255.0, 255 / 255.0, 1,  // background rgba
								     0.2,                                       // outline width
								     0, 0, 0, 1,                                // text rgba
								     0, 0, 0, 1,                                // box outline rgba
								     142 / 255.0, 200 / 255.0, 255 / 255.0, 1); // text outline rgba
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


boolean_t raw__timeline_event__overlaps(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr start_time        = raw__timeline_event__start_time(cause, this);
  f2ptr end_time          = raw__timeline_event__end_time(  cause, this);
  f2ptr event__start_time = raw__timeline_event__start_time(cause, event);
  f2ptr event__end_time   = raw__timeline_event__end_time(  cause, event);
  return (((f2__is_greater_than(cause, end_time,          event__start_time) != nil) &&
	   (f2__is_less_than(   cause, start_time,        event__start_time) != nil))   ||
	  ((f2__is_greater_than(cause, end_time,          event__end_time)   != nil) &&
	   (f2__is_less_than(   cause, start_time,        event__end_time)   != nil))   ||
	  ((f2__is_greater_than(cause, event__end_time,   start_time)        != nil) &&
	   (f2__is_less_than(   cause, event__start_time, start_time)        != nil))   ||
	  ((f2__is_greater_than(cause, event__end_time,   end_time)          != nil) &&
	   (f2__is_less_than(   cause, event__start_time, end_time)          != nil)));
}

f2ptr f2__timeline_event__overlaps(f2ptr cause, f2ptr this, f2ptr event) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__timeline_event__overlaps(cause, this, event));
}
export_cefunk2(timeline_event__overlaps, this, event, 0, "");


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
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "overlaps"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__overlaps")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__terminal_print_with_frame")));}
  return this;
}



// timeline_connected_part

def_ceframe2(timeline, timeline_connected_part,
	     event_set,
	     maximum_y_index);

f2ptr raw__timeline_connected_part__new(f2ptr cause) {
  f2ptr event_set       = f2__set__new(cause);
  f2ptr maximum_y_index = nil;
  return f2timeline_connected_part__new(cause, event_set, maximum_y_index);
}

f2ptr f2__timeline_connected_part__new(f2ptr cause) {
  return raw__timeline_connected_part__new(cause);
}
export_cefunk0(timeline_connected_part__new, 0, "");



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
      f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
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
  f2ptr connected_parts = nil;
  // find connected sets of timeline_events
  {
    f2ptr timeline_event_set        = raw__timeline__timeline_event_set(cause, this);
    f2ptr connected_part_event_hash = f2__ptypehash__new(cause);
    {
      f2ptr event_set_elements = raw__set__elements(cause, timeline_event_set);
      {
	f2ptr iter = event_set_elements;
	while (iter != nil) {
	  f2ptr event = f2cons__car(iter, cause);
	  f2ptr connected_part = raw__ptypehash__lookup(cause, connected_part_event_hash, event);
	  if (connected_part == nil) {
	    connected_part  = f2__timeline_connected_part__new(cause);
	    connected_parts = f2cons__new(cause, connected_part, connected_parts);
	    f2ptr connected_set = raw__timeline_connected_part__event_set(cause, connected_part);
	    f2ptr expansion_event_set = f2__set__new(cause);
	    raw__set__add(cause, expansion_event_set, event);
	    while (! raw__set__is_empty(cause, expansion_event_set)) {
	      f2ptr expand_event = raw__set__an_arbitrary_element(cause, expansion_event_set);
	      raw__ptypehash__add(cause, connected_part_event_hash, expand_event, connected_part);
	      raw__set__add(      cause, connected_set, expand_event);
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
    s64 connected_part_count = 0;
    {
      f2ptr connected_part_iter = connected_parts;
      while (connected_part_iter != nil) {
	connected_part_count ++;
	connected_part_iter = f2cons__cdr(connected_part_iter, cause);
      }
    }
    {
      f2ptr* connected_part_array       = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * connected_part_count));
      s64*   connected_part_max_y_array = (s64*)  from_ptr(f2__malloc(sizeof(s64)   * connected_part_count));
      {
	s64   connected_part_index = 0;
	f2ptr connected_part_iter  = connected_parts;
	while (connected_part_iter != nil) {
	  f2ptr connected_part = f2cons__car(connected_part_iter, cause);
	  if (connected_part_index >= connected_part_count) {
	    return f2larva__new(cause, 2223, nil);
	  }
	  connected_part_array[connected_part_index] = connected_part;
	  connected_part_index ++;
	  connected_part_iter = f2cons__cdr(connected_part_iter, cause);
	}
      }
      {
	s64 connected_part_index;
	for (connected_part_index = 0; connected_part_index < connected_part_count; connected_part_index ++) {
	  f2ptr connected_part = connected_part_array[connected_part_index];
	  f2ptr connected_set  = raw__timeline_connected_part__event_set(cause, connected_part);
	  {
	    s64    event_count   = f2integer__i(f2__set__key_count(cause, connected_set), cause);
	    f2ptr* event_array   = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * event_count));
	    {
	      s64 index = 0;
	      set__iteration(cause, connected_set, event,
			     if (index >= event_count) {
			       return f2larva__new(cause, 222, nil);
			     }
			     event_array[index] = event;
			     index ++;
			     );
	    }
	    { // swap sort
	      s64 i__index;
	      for (i__index = 0; i__index < event_count; i__index ++) {
		f2ptr i = event_array[i__index];
		s64 j__index;
		for (j__index = i__index + 1; j__index < event_count; j__index ++) {
		  f2ptr j = event_array[j__index];
		  f2ptr j__contains_set = raw__timeline_event__contains_set(cause, j);
		  f2ptr j__next_set     = raw__timeline_event__next_set(    cause, j);
		  if (raw__set__contains(cause, j__contains_set, i) ||
		      raw__set__contains(cause, j__next_set,     i)) {
		    event_array[i__index] = j;
		    event_array[j__index] = i;
		    i__index --;
		    break;
		  }
		}
	      }
	    }
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = event_array[index];
		raw__timeline_event__y_index__set(cause, event, f2integer__new(cause, index));
	      }
	    }
	    { // move events up if possible
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = event_array[index];
		{
		  s64 maximum_overlap_y_index = -1;
		  {
		    s64 o_index;
		    for (o_index = index - 1; o_index >= 0; o_index --) {
		      f2ptr o_event = event_array[o_index];
		      if (raw__timeline_event__overlaps(cause, event, o_event)) {
			f2ptr o_y_index    = raw__timeline_event__y_index(cause, o_event);
			s64   o_y_index__i = f2integer__i(o_y_index, cause);
			if (o_y_index__i > maximum_overlap_y_index) {
			  maximum_overlap_y_index = o_y_index__i;
			}
		      }
		    }
		  }
		  raw__timeline_event__y_index__set(cause, event, f2integer__new(cause, maximum_overlap_y_index + 1));
		}
	      }
	    }
	    connected_part_max_y_array[connected_part_index] = 0;
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event      = event_array[index];
		f2ptr y_index    = raw__timeline_event__y_index(cause, event);
		s64   y_index__i = f2integer__i(y_index, cause);
		if (y_index__i > connected_part_max_y_array[connected_part_index]) {
		  connected_part_max_y_array[connected_part_index] = y_index__i;
		}
	      }
	    }
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = event_array[index];
		//f2ptr extents = raw__ptypehash__lookup(cause, extents_event_hash, event);
		raw__cairo_context__save(cause, cairo_context);
		raw__cairo_context__scale(cause, cairo_context, (1.0 / 64.0), (1.0 / 64.0));
		raw__cairo_context__translate(cause, cairo_context, 4, 4 + y_position);
		f2ptr result = raw__timeline_event__cairo_render(cause, event, cairo_context, this);
		if (raw__larva__is_type(cause, result)) {
		  return result;
		}
		raw__cairo_context__restore(cause, cairo_context);
	      }
	      y_position += ((connected_part_max_y_array[connected_part_index] + 1) * 2.0) + 1.0;
	    }
	    f2__free(to_ptr(event_array));
	  }
	}
      }
      f2__free(to_ptr(connected_part_array));
      f2__free(to_ptr(connected_part_max_y_array));
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
  f2__add_type(cause, new__symbol(cause, "timeline_event"),               f2__timeline_event_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "timeline_connected_event_set"), f2__timeline_connected_event_set_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "timeline"),                     f2__timeline_type__new_aux(cause));
  status("timeline initialized.");
  return nil;
}
export_cefunk0(timeline__core_extension__initialize, 0, "");

f2ptr f2__timeline__core_extension__destroy(f2ptr cause) {
  status("timeline destroyed.");
  return nil;
}
export_cefunk0(timeline__core_extension__destroy, 0, "");


