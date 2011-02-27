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
  raw__cairo_context__move_to(        cause, this, x0, y0 + corner_radius);
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

void raw__cairo_context__render_outlined_rounded_box_with_broken_right(f2ptr cause,
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
  raw__cairo_context__move_to(        cause, this, x0, y0 + corner_radius);
  raw__cairo_context__arc(            cause, this, x0 + corner_radius, y0 + corner_radius, corner_radius, M_PI, 3 * M_PI / 2);
  raw__cairo_context__rel_line_to(    cause, this, dx - corner_radius - (dy / 3), 0);
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this, -(dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this, -(dx - corner_radius), 0);
  raw__cairo_context__arc(            cause, this, x0 + corner_radius, y0 + dy - corner_radius, corner_radius, M_PI / 2, M_PI);
  raw__cairo_context__rel_line_to(    cause, this, 0, -(dy - (corner_radius * 2)));
  raw__cairo_context__close_path(     cause, this);
  
  raw__cairo_context__set_line_width( cause, this, outline_width);
  raw__cairo_context__set_source_rgba(cause, this, foreground_red, foreground_green, foreground_blue, foreground_alpha);
  raw__cairo_context__stroke_preserve(cause, this);
  raw__cairo_context__set_source_rgba(cause, this, background_red, background_green, background_blue, background_alpha);
  raw__cairo_context__fill(           cause, this);
}

void raw__cairo_context__render_outlined_rounded_box_with_broken_left(f2ptr cause,
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
  raw__cairo_context__move_to(        cause, this, x0, y0);
  raw__cairo_context__rel_line_to(    cause, this, dx - corner_radius, 0);
  raw__cairo_context__arc(            cause, this, x0 + dx - corner_radius, y0 + corner_radius, corner_radius, 3 * M_PI / 2, 2 * M_PI);
  raw__cairo_context__rel_line_to(    cause, this, 0, dy - (corner_radius * 2));
  raw__cairo_context__arc(            cause, this, x0 + dx - corner_radius, y0 + dy - corner_radius, corner_radius, 0, M_PI / 2);
  raw__cairo_context__rel_line_to(    cause, this, -(dx - corner_radius - (dy / 3)), 0);
  raw__cairo_context__rel_line_to(    cause, this, -(dy / 3), -(dy / 3));
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), -(dy / 3));
  raw__cairo_context__close_path(     cause, this);
  
  raw__cairo_context__set_line_width( cause, this, outline_width);
  raw__cairo_context__set_source_rgba(cause, this, foreground_red, foreground_green, foreground_blue, foreground_alpha);
  raw__cairo_context__stroke_preserve(cause, this);
  raw__cairo_context__set_source_rgba(cause, this, background_red, background_green, background_blue, background_alpha);
  raw__cairo_context__fill(           cause, this);
}

void raw__cairo_context__render_outlined_box_with_broken_left_and_right(f2ptr cause,
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
  //double corner_radius = maximum_corner_radius;
  raw__cairo_context__move_to(        cause, this, x0, y0);
  raw__cairo_context__rel_line_to(    cause, this, dx - (dy / 3), 0);
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this, -(dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), (dy / 3));
  raw__cairo_context__rel_line_to(    cause, this, -(dx - (dy / 3)), 0);
  raw__cairo_context__rel_line_to(    cause, this, -(dy / 3), -(dy / 3));
  raw__cairo_context__rel_line_to(    cause, this,  (dy / 3), -(dy / 3));
  raw__cairo_context__rel_line_to(    cause, this, -(dy / 3), -(dy / 3));
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

f2ptr raw__cairo_context__render_centered_outlined_frame(f2ptr cause, f2ptr this, double cx, double cy, double font_size, f2ptr frame, double outline_width, double red, double green, double blue, double alpha, double outline_red, double outline_green, double outline_blue, double outline_alpha) {
  s64 frame__key_count = f2integer__i(f2__frame__key_count(cause, frame), cause);
  s64 frame__y_index   = 0;
  {
    f2ptr frame__title = f2__frame__lookup_var_value(cause, frame, new__symbol(cause, "title"), nil);
    f2ptr frame__title__string = f2__exp__as__string(cause, frame__title);
    if (raw__larva__is_type(cause, frame__title__string)) {
      return frame__title__string;
    }
    s64 frame__title__string__length = raw__string__length(cause, frame__title__string);
    u8* frame__title__string__str    = (u8*)from_ptr(f2__malloc(frame__title__string__length));
    raw__string__str_copy(cause, frame__title__string, frame__title__string__str);
    frame__title__string__str[frame__title__string__length] = 0;
    
    raw__cairo_context__set_font_size(cause, this, font_size);
    f2ptr text_extents = raw__cairo_context__text_extents(cause, this, (char*)frame__title__string__str);
    if (raw__larva__is_type(cause, text_extents)) {
      return text_extents;
    }
    f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
    double text_extents__width__d = f2double__d(text_extents__width, cause);
    double x0 = cx - (text_extents__width__d / 2);
    double y0 = cy - (font_size * frame__key_count / 2) + (frame__y_index * font_size);
    raw__cairo_context__render_outlined_text(cause, this, x0, y0, font_size, (char*)frame__title__string__str, outline_width, red, green, blue, alpha, outline_red, outline_green, outline_blue, outline_alpha);
    f2__free(to_ptr(frame__title__string__str));
  }
  return nil;
}

f2ptr raw__cairo_context__render_frame_text_box(f2ptr cause, f2ptr this, f2ptr left_edge_type, f2ptr right_edge_type,
						double x0, double y0, double dx, double dy, double font_size,
						f2ptr frame,
						double maximum_corner_radius,
						double background_red, double background_green, double background_blue, double background_alpha,
						double outline_width,
						double text_red, double text_green, double text_blue, double text_alpha,
						double box_outline_red, double box_outline_green, double box_outline_blue, double box_outline_alpha,
						double text_outline_red, double text_outline_green, double text_outline_blue, double text_outline_alpha) {
  if (raw__eq(cause, left_edge_type, new__symbol(cause, "rounded"))) {
    if (raw__eq(cause, right_edge_type, new__symbol(cause, "rounded"))) {
      raw__cairo_context__render_outlined_rounded_box(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, box_outline_red, box_outline_green, box_outline_blue, box_outline_alpha,  background_red, background_green, background_blue, background_alpha);
    } else {
      raw__cairo_context__render_outlined_rounded_box_with_broken_right(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, box_outline_red, box_outline_green, box_outline_blue, box_outline_alpha,  background_red, background_green, background_blue, background_alpha);
    }
  } else {
    if (raw__eq(cause, right_edge_type, new__symbol(cause, "rounded"))) {
      raw__cairo_context__render_outlined_rounded_box_with_broken_left(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, box_outline_red, box_outline_green, box_outline_blue, box_outline_alpha,  background_red, background_green, background_blue, background_alpha);
    } else {
      raw__cairo_context__render_outlined_box_with_broken_left_and_right(cause, this, x0, y0, dx, dy, maximum_corner_radius, outline_width, box_outline_red, box_outline_green, box_outline_blue, box_outline_alpha,  background_red, background_green, background_blue, background_alpha);
    }
  }
  {
    f2ptr result = raw__cairo_context__render_centered_outlined_frame(cause, this, x0 + (dx / 2), y0 + (dy / 2), font_size, frame, outline_width,  text_red, text_green, text_blue, text_alpha,  text_outline_red, text_outline_green, text_outline_blue, text_outline_alpha);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}


f2ptr raw__cairo_context__render_rounded_text_box(f2ptr cause, f2ptr this,
						  double x0, double y0, double dx, double dy, double font_size,
						  char* text,
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

def_ceframe9(timeline, timeline_event,
	     name,
	     height,
	     start_time,
	     end_time,
	     contains_set,
	     is_contained_by_set,
	     next_set,
	     previous_set,
	     y_index);


f2ptr raw__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  f2ptr height              = f2integer__new(cause, 2);
  f2ptr contains_set        = f2__set__new(cause);
  f2ptr is_contained_by_set = f2__set__new(cause);
  f2ptr next_set            = f2__set__new(cause);
  f2ptr previous_set        = f2__set__new(cause);
  return f2timeline_event__new(cause, name, height, start_time, end_time, contains_set, is_contained_by_set, next_set, previous_set, nil);
}

f2ptr f2__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  if (((start_time != nil) && (! raw__time__is_type(cause, start_time))) ||
      ((end_time  != nil)  && (! raw__time__is_type(cause, end_time)))) {
    return f2larva__new(cause, 1, nil);
  }
  if ((start_time != nil) && (end_time != nil)) {
    f2ptr is_less_than = f2__is_less_than(cause, start_time, end_time);
    if (raw__larva__is_type(cause, is_less_than)) {
      return is_less_than;
    }
    if (is_less_than == nil) {
      return f2larva__new(cause, 1351, nil);
    }
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

f2ptr raw__timeline_event__render_extents(f2ptr cause, f2ptr this, f2ptr timeline, double* start_position, double* end_position, double* top_position, double* bottom_position) {
  if ((start_position != NULL) || (end_position != NULL)) {
    f2ptr  minimum_time                            = raw__timeline__minimum_time(cause, timeline);
    f2ptr  minimum_time__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, minimum_time);
    s64    minimum_time__nanoseconds_since_1970__i = f2integer__i(minimum_time__nanoseconds_since_1970, cause);
    f2ptr  maximum_time                            = raw__timeline__maximum_time(cause, timeline);
    f2ptr  maximum_time__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, maximum_time);
    s64    maximum_time__nanoseconds_since_1970__i = f2integer__i(maximum_time__nanoseconds_since_1970, cause);
    f2ptr  start_time                              = raw__timeline_event__start_time(cause, this);
    if (start_time == nil) {
      start_time = minimum_time;
    }
    f2ptr  start_time__nanoseconds_since_1970      = f2__time__nanoseconds_since_1970(cause, start_time);
    s64    start_time__nanoseconds_since_1970__i   = f2integer__i(start_time__nanoseconds_since_1970, cause);
    f2ptr  end_time                                = raw__timeline_event__end_time(cause, this);
    if (end_time == nil) {
      end_time = maximum_time;
    }
    f2ptr  end_time__nanoseconds_since_1970        = f2__time__nanoseconds_since_1970(cause, end_time);
    s64    end_time__nanoseconds_since_1970__i     = f2integer__i(end_time__nanoseconds_since_1970, cause);
    s64    total_nanoseconds                       = maximum_time__nanoseconds_since_1970__i - minimum_time__nanoseconds_since_1970__i;
    s64    start_nanoseconds                       = start_time__nanoseconds_since_1970__i   - minimum_time__nanoseconds_since_1970__i;
    s64    end_nanoseconds                         = end_time__nanoseconds_since_1970__i     - minimum_time__nanoseconds_since_1970__i;
    if (total_nanoseconds == 0) {
      return f2larva__new(cause, 4444, nil);
    }
    double timeline__left_border   = f2double__d(raw__timeline__left_border(  cause, timeline), cause);
    double timeline__right_border  = f2double__d(raw__timeline__right_border( cause, timeline), cause);
    double timeline__x_width       = f2double__d(raw__timeline__x_width(      cause, timeline), cause);
    double content_width           = timeline__x_width - timeline__left_border - timeline__right_border;
    if (start_position != NULL) {
      *start_position                              = start_nanoseconds * content_width / total_nanoseconds;
    }
    if (end_position != NULL) {
      *end_position                                = end_nanoseconds   * content_width / total_nanoseconds;
    }
  }
  if ((top_position != NULL) || (bottom_position != NULL)) {
    f2ptr  y_index          = raw__timeline_event__y_index(cause, this);
    s64    y_index__i       = f2integer__i(y_index, cause);
    f2ptr  height           = raw__timeline_event__height(cause, this);
    s64    height__i        = f2integer__i(height, cause);
    double y_event_distance = f2double__d(raw__timeline__y_event_distance(cause, timeline), cause);
    if (top_position != NULL) {
      printf("\ny_index__i=" s64__fstr, y_index__i); fflush(stdout);
      *top_position = y_index__i * y_event_distance;
    }
    if (bottom_position != NULL) {
      *bottom_position = (y_index__i * y_event_distance) + height__i + 1.5;
    }
  }
  return nil;
}

f2ptr raw__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline) {
  f2ptr start_time = raw__timeline_event__start_time(cause, this);
  f2ptr end_time   = raw__timeline_event__end_time(cause, this);
  double start_position  = 0.0;
  double end_position    = 0.0;
  double top_position    = 0.0;
  double bottom_position = 0.0;
  {
    f2ptr result = raw__timeline_event__render_extents(cause, this, timeline, &start_position, &end_position, &top_position, &bottom_position);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2ptr action_name = raw__timeline_event__cairo_action_name(cause, this);
  f2ptr frame       = f2__frame__new(cause, f2list2__new(cause,
							 new__symbol(cause, "title"), action_name));
  raw__cairo_context__save(cause, cairo_context);
  {
    f2ptr left_edge_type = nil;
    if (start_time != nil) {
      left_edge_type = new__symbol(cause, "rounded");
    } else {
      left_edge_type = new__symbol(cause, "broken");
    }
    f2ptr right_edge_type = nil;
    if (end_time != nil) {
      right_edge_type = new__symbol(cause, "rounded");
    } else {
      right_edge_type = new__symbol(cause, "broken");
    }
    {
      f2ptr result = raw__cairo_context__render_frame_text_box(cause, cairo_context, left_edge_type, right_edge_type,
							       start_position, top_position,                                  // x0, y0
							       end_position - start_position, bottom_position - top_position, // dx, dy
							       1,                                                             // font size
							       frame,                                                         // frame
							       0.5,                                                           // maximum corner radius
							       142 / 255.0, 200 / 255.0, 255 / 255.0, 1,                      // background rgba
							       0.2,                                                           // outline width
							       0, 0, 0, 1,                                                    // text rgba
							       0, 0, 0, 1,                                                    // box outline rgba
							       142 / 255.0, 200 / 255.0, 255 / 255.0, 1);                     // text outline rgba
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
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



// timeline_connected_part

def_ceframe4(timeline, timeline_connected_part,
	     event_set,
	     sorted_event_array,
	     maximum_y_index,
	     y_position);

f2ptr raw__timeline_connected_part__new(f2ptr cause) {
  f2ptr event_set          = f2__set__new(cause);
  f2ptr sorted_event_array = nil;
  f2ptr maximum_y_index    = nil;
  f2ptr y_position         = nil;
  return f2timeline_connected_part__new(cause, event_set, sorted_event_array, maximum_y_index, y_position);
}

f2ptr f2__timeline_connected_part__new(f2ptr cause) {
  return raw__timeline_connected_part__new(cause);
}
export_cefunk0(timeline_connected_part__new, 0, "");



// timeline

def_ceframe13(timeline, timeline,
	      timeline_event_set,
	      left_border,
	      right_border,
	      top_border,
	      bottom_border,
	      x_width,
	      y_event_distance,
	      arrow_head_size,
	      positions_have_been_calculated,
	      minimum_time,
	      maximum_time,
	      connected_part_array,
	      y_height);

f2ptr raw__timeline__new(f2ptr cause) {
  f2ptr timeline_event_set             = f2__set__new(cause);
  f2ptr left_border                    = f2double__new(cause, 2.0);
  f2ptr right_border                   = f2double__new(cause, 2.0);
  f2ptr top_border                     = f2double__new(cause, 2.0);
  f2ptr bottom_border                  = f2double__new(cause, 2.0);
  f2ptr x_width                        = f2double__new(cause, 100.0);
  f2ptr y_event_distance               = f2double__new(cause, 4.0);
  f2ptr arrow_head_size                = f2double__new(cause, 0.33);
  f2ptr positions_have_been_calculated = nil;
  f2ptr minimum_time                   = nil;
  f2ptr maximum_time                   = nil;
  f2ptr connected_part_array           = nil;
  f2ptr y_height                       = nil;
  return f2timeline__new(cause,
			 timeline_event_set,
			 left_border,
			 right_border,
			 top_border,
			 bottom_border,
			 x_width,
			 y_event_distance,
			 arrow_head_size,
			 positions_have_been_calculated,
			 minimum_time,
			 maximum_time,
			 connected_part_array,
			 y_height);
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


f2ptr raw__timeline__calculate_positions(f2ptr cause, f2ptr this) {
  {
    f2ptr minimum_time = raw__timeline__minimum_time(cause, this);
    f2ptr maximum_time = raw__timeline__maximum_time(cause, this);
    if ((minimum_time == nil) ||
	(maximum_time == nil)) {
      f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
      set__iteration(cause, timeline_event_set, event,
		     f2ptr start_time = raw__timeline_event__start_time(cause, event);
		     f2ptr end_time   = raw__timeline_event__end_time(  cause, event);
		     if (start_time != nil) {
		       if ((minimum_time == nil) ||
			   (f2__is_less_than(cause, start_time, minimum_time) != nil)) {
			 minimum_time = start_time;
		       }
		     }
		     if (end_time != nil) {
		       if ((maximum_time == nil) ||
			   (f2__is_greater_than(cause, end_time, maximum_time) != nil)) {
			 maximum_time = end_time;
		       }
		     }
		     );
    }
    if (minimum_time == nil) {
      minimum_time = f2__time(cause);
    }
    if (maximum_time == nil) {
      maximum_time = f2__time(cause);
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
    s64 connected_part_count = 0;
    {
      f2ptr connected_part_iter = connected_parts;
      while (connected_part_iter != nil) {
	connected_part_count ++;
	connected_part_iter = f2cons__cdr(connected_part_iter, cause);
      }
    }
    {
      f2ptr connected_part_array = raw__array__new(cause, connected_part_count);
      raw__timeline__connected_part_array__set(cause, this, connected_part_array);
      {
	s64   connected_part_index = 0;
	f2ptr connected_part_iter  = connected_parts;
	while (connected_part_iter != nil) {
	  f2ptr connected_part = f2cons__car(connected_part_iter, cause);
	  if (connected_part_index >= connected_part_count) {
	    return f2larva__new(cause, 2223, nil);
	  }
	  raw__array__elt__set(cause, connected_part_array, connected_part_index, connected_part);
	  connected_part_index ++;
	  connected_part_iter = f2cons__cdr(connected_part_iter, cause);
	}
      }
      double y_position = 0;
      {
	s64 connected_part_index;
	for (connected_part_index = 0; connected_part_index < connected_part_count; connected_part_index ++) {
	  f2ptr connected_part = raw__array__elt(cause, connected_part_array, connected_part_index);
	  f2ptr connected_set  = raw__timeline_connected_part__event_set(cause, connected_part);
	  {
	    s64   event_count = f2integer__i(f2__set__key_count(cause, connected_set), cause);
	    f2ptr event_array = raw__array__new(cause, event_count);
	    raw__timeline_connected_part__sorted_event_array__set(cause, connected_part, event_array);
	    {
	      s64 index = 0;
	      set__iteration(cause, connected_set, event,
			     if (index >= event_count) {
			       return f2larva__new(cause, 222, nil);
			     }
			     raw__array__elt__set(cause, event_array, index, event);
			     index ++;
			     );
	    }
	    { // swap sort
	      s64 i__index;
	      for (i__index = 0; i__index < event_count; i__index ++) {
		f2ptr i = raw__array__elt(cause, event_array, i__index);
		s64 j__index;
		for (j__index = i__index + 1; j__index < event_count; j__index ++) {
		  f2ptr j = raw__array__elt(cause, event_array, j__index);
		  f2ptr j__contains_set = raw__timeline_event__contains_set(cause, j);
		  f2ptr j__next_set     = raw__timeline_event__next_set(    cause, j);
		  if (raw__set__contains(cause, j__contains_set, i) ||
		      raw__set__contains(cause, j__next_set,     i)) {
		    raw__array__elt__set(cause, event_array, i__index, j);
		    raw__array__elt__set(cause, event_array, j__index, i);
		    i__index --;
		    break;
		  }
		}
	      }
	    }
	    {
	      s64 y_index = 0;
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		raw__timeline_event__y_index__set(cause, event, f2integer__new(cause, y_index));
		f2ptr height    = raw__timeline_event__height(cause, event);
		s64   height__i = f2integer__i(height, cause);
		y_index += height__i;
	      }
	    }
	    { // move events up if possible
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		{
		  s64 maximum_overlap_y_index = 0;
		  {
		    s64 o_index;
		    for (o_index = index - 1; o_index >= 0; o_index --) {
		      f2ptr o_event = raw__array__elt(cause, event_array, o_index);
		      if (raw__timeline__timeline_event__overlaps(cause, this, event, o_event)) {
			f2ptr o_y_index    = raw__timeline_event__y_index(cause, o_event);
			s64   o_y_index__i = f2integer__i(o_y_index, cause);
			f2ptr o_height     = raw__timeline_event__height(cause, o_event);
			s64   o_height__i  = f2integer__i(o_height, cause);
			if (o_y_index__i + o_height__i > maximum_overlap_y_index) {
			  maximum_overlap_y_index = o_y_index__i + o_height__i;
			}
		      }
		    }
		  }
		  raw__timeline_event__y_index__set(cause, event, f2integer__new(cause, maximum_overlap_y_index));
		}
	      }
	    }
	    s64 connected_part_max_y = 0;
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event      = raw__array__elt(cause, event_array, index);
		f2ptr y_index    = raw__timeline_event__y_index(cause, event);
		s64   y_index__i = f2integer__i(y_index, cause);
		f2ptr height     = raw__timeline_event__height(cause, event);
		s64   height__i  = f2integer__i(height, cause);
		if (y_index__i + height__i> connected_part_max_y) {
		  connected_part_max_y = y_index__i + height__i;
		}
	      }
	    }
	    raw__timeline_connected_part__maximum_y_index__set(cause, connected_part, f2integer__new(cause, connected_part_max_y));
	    raw__timeline_connected_part__y_position__set(     cause, connected_part, f2double__new(cause, y_position));
	    double y_event_distance = f2double__d(raw__timeline__y_event_distance(cause, this), cause);
	    y_position += (connected_part_max_y * y_event_distance) + 2.0;
	  }
	}
      }
      double bottom_border = f2double__d(raw__timeline__bottom_border(cause, this), cause);
      double y_height      = y_position + bottom_border;
      raw__timeline__y_height__set(cause, this, f2double__new(cause, y_height));
    }
  }
  raw__timeline__positions_have_been_calculated__set(cause, this, f2bool__new(boolean__true));
  return nil;
}

f2ptr f2__timeline__calculate_positions(f2ptr cause, f2ptr this) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__calculate_positions(cause, this);
}
export_cefunk1(timeline__calculate_positions, this, 0, "Prepares the timeline for rendering.");


f2ptr raw__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  {
    f2ptr positions_have_been_calculated = raw__timeline__positions_have_been_calculated(cause, this);
    if (positions_have_been_calculated == nil) {
      f2ptr result = raw__timeline__calculate_positions(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  
  double timeline__left_border   = f2double__d(raw__timeline__left_border(  cause, this), cause);
  double timeline__right_border  = f2double__d(raw__timeline__right_border( cause, this), cause);
  double timeline__top_border    = f2double__d(raw__timeline__top_border(   cause, this), cause);
  double timeline__x_width       = f2double__d(raw__timeline__x_width(      cause, this), cause);
  double timeline__y_height      = f2double__d(raw__timeline__y_height(     cause, this), cause);
  
  {
    raw__cairo_context__save(cause, cairo_context);
    raw__cairo_context__set_source_rgba(cause, cairo_context, 0, 0, 0, 1);
    raw__cairo_context__set_line_width(cause, cairo_context, 0.05);
    raw__cairo_context__scale(cause, cairo_context, (1.0 / timeline__x_width), (1.0 / timeline__y_height));
    {
      boolean_t draw_outline_box = boolean__false;
      if (draw_outline_box) {
	raw__cairo_context__rel_line_to(cause, cairo_context,  timeline__x_width,  0);
	raw__cairo_context__rel_line_to(cause, cairo_context,  0,                  timeline__y_height);
	raw__cairo_context__rel_line_to(cause, cairo_context, -timeline__x_width,  0);
	raw__cairo_context__rel_line_to(cause, cairo_context,  0,                 -timeline__y_height);
	raw__cairo_context__stroke(cause, cairo_context);
      }
    }
    {
      boolean_t draw_dot_grid = boolean__true;
      if (draw_dot_grid) {
	s64 y;
	for (y = 0; y < (((int)(timeline__y_height + 0.5)) - 1); y ++) {
	  s64 x;
	  for (x = 0; x < (((int)(timeline__x_width + 0.5)) - 1); x ++) {
	    raw__cairo_context__arc(cause, cairo_context, x + 1.0, y + 1.0, 0.05, 0, 2 * cairo_pi);
	    raw__cairo_context__fill(cause, cairo_context);
	  }
	}
      }
    }
    raw__cairo_context__move_to(cause, cairo_context, 0, 0);
    { // draw edge lines
      double arrow_head_size      = f2double__d(raw__timeline__arrow_head_size(cause, this), cause);
      f2ptr  connected_part_array = raw__timeline__connected_part_array(cause, this);
      s64    connected_part_count = raw__array__length(cause, connected_part_array);
      {
	s64 connected_part_index;
	for (connected_part_index = 0; connected_part_index < connected_part_count; connected_part_index ++) {
	  f2ptr connected_part = raw__array__elt(cause, connected_part_array, connected_part_index);
	  {
	    double y_position  = f2double__d(raw__timeline_connected_part__y_position(cause, connected_part), cause);
	    raw__cairo_context__save(cause, cairo_context);
	    raw__cairo_context__translate(cause, cairo_context, timeline__left_border, timeline__top_border + y_position);
	    {
	      f2ptr event_array = raw__timeline_connected_part__sorted_event_array(cause, connected_part);
	      s64   event_count = raw__array__length(cause, event_array);
	      {
		s64 index;
		for (index = 0; index < event_count; index ++) {
		  f2ptr event = raw__array__elt(cause, event_array, index);
		  {
		    double start_position;
		    double end_position;
		    double top_position;
		    double bottom_position;
		    {
		      f2ptr result = raw__timeline_event__render_extents(cause, event, this, &start_position, &end_position, &top_position, &bottom_position);
		      if (raw__larva__is_type(cause, result)) {
			return result;
		      }
		    }
		    {
		      f2ptr next_set = raw__timeline_event__next_set(cause, event);
		      if (next_set != nil) {
			set__iteration(cause, next_set, next_event,
				       double next_event__start_position;
				       double next_event__end_position;
				       double next_event__top_position;
				       double next_event__bottom_position;
				       {
					 f2ptr result = raw__timeline_event__render_extents(cause, next_event, this, &next_event__start_position, &next_event__end_position, &next_event__top_position, &next_event__bottom_position);
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       {
					 double x0 = end_position;
					 double y0 = (top_position + bottom_position) / 2.0;
					 double x1 = (end_position + next_event__start_position) / 2.0;
					 double y1 = y0;
					 double x2 = x1;
					 double y2 = (next_event__top_position + next_event__bottom_position) / 2.0;
					 double x3 = next_event__start_position;
					 double y3 = y2;
					 raw__cairo_context__set_source_rgba(cause, cairo_context, 0, 0, 0, 1);
					 raw__cairo_context__set_line_width( cause, cairo_context, 0.1);
					 
					 raw__cairo_context__move_to( cause, cairo_context, x0, y0);
					 raw__cairo_context__curve_to(cause, cairo_context, x1, y1, x2, y2, x3, y3);
					 raw__cairo_context__stroke(cause, cairo_context);
					 
					 raw__cairo_context__move_to(cause, cairo_context, x3, y3);
					 raw__cairo_context__line_to(cause, cairo_context, x3 - arrow_head_size, y3 - arrow_head_size);
					 raw__cairo_context__stroke(cause, cairo_context);
					 
					 raw__cairo_context__move_to(cause, cairo_context, x3, y3);
					 raw__cairo_context__line_to(cause, cairo_context, x3 - arrow_head_size, y3 + arrow_head_size);
					 raw__cairo_context__stroke(cause, cairo_context);
				       }
				       );
		      }
		    }
		    {
		      f2ptr contains_set = raw__timeline_event__contains_set(cause, event);
		      if (contains_set != nil) {
			set__iteration(cause, contains_set, contains_event,
				       double contains_event__start_position;
				       double contains_event__end_position;
				       double contains_event__top_position;
				       double contains_event__bottom_position;
				       {
					 f2ptr result = raw__timeline_event__render_extents(cause, contains_event, this, &contains_event__start_position, &contains_event__end_position, &contains_event__top_position, &contains_event__bottom_position);
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       {
					 double x0 = (start_position + end_position) / 2.0;
					 double y0 = bottom_position;
					 double x1 = x0;
					 double y1 = (bottom_position + contains_event__top_position) / 2.0;
					 double x2 = (contains_event__start_position + contains_event__end_position) / 2.0;
					 double y2 = y1;
					 double x3 = x2;
					 double y3 = contains_event__top_position;
					 raw__cairo_context__move_to( cause, cairo_context, x0, y0);
					 raw__cairo_context__curve_to(cause, cairo_context, x1, y1, x2, y2, x3, y3);
					 
					 raw__cairo_context__set_source_rgba(cause, cairo_context, 0, 0, 0, 1);
					 raw__cairo_context__set_line_width( cause, cairo_context, 0.1);
					 raw__cairo_context__stroke(cause, cairo_context);
					 
					 raw__cairo_context__move_to(cause, cairo_context, x3, y3);
					 raw__cairo_context__line_to(cause, cairo_context, x3 - arrow_head_size, y3 - arrow_head_size);
					 raw__cairo_context__stroke(cause, cairo_context);
					 
					 raw__cairo_context__move_to(cause, cairo_context, x3, y3);
					 raw__cairo_context__line_to(cause, cairo_context, x3 + arrow_head_size, y3 - arrow_head_size);
					 raw__cairo_context__stroke(cause, cairo_context);
				       }
				       );
		      }
		    }
		  }
		}
	      }
	    }
	    raw__cairo_context__restore(cause, cairo_context);
	  }
	}
      }
    }
    { // draw edge labels
      f2ptr connected_part_array = raw__timeline__connected_part_array(cause, this);
      s64   connected_part_count = raw__array__length(cause, connected_part_array);
      {
	s64 connected_part_index;
	for (connected_part_index = 0; connected_part_index < connected_part_count; connected_part_index ++) {
	  f2ptr connected_part = raw__array__elt(cause, connected_part_array, connected_part_index);
	  {
	    double y_position  = f2double__d(raw__timeline_connected_part__y_position(cause, connected_part), cause);
	    raw__cairo_context__save(cause, cairo_context);
	    raw__cairo_context__translate(cause, cairo_context, timeline__left_border, timeline__top_border + y_position);
	    {
	      f2ptr event_array = raw__timeline_connected_part__sorted_event_array(cause, connected_part);
	      s64   event_count = raw__array__length(cause, event_array);
	      {
		s64 index;
		for (index = 0; index < event_count; index ++) {
		  f2ptr event = raw__array__elt(cause, event_array, index);
		  {
		    double start_position;
		    double end_position;
		    double top_position;
		    double bottom_position;
		    {
		      f2ptr result = raw__timeline_event__render_extents(cause, event, this, &start_position, &end_position, &top_position, &bottom_position);
		      if (raw__larva__is_type(cause, result)) {
			return result;
		      }
		    }
		    {
		      f2ptr next_set = raw__timeline_event__next_set(cause, event);
		      if (next_set != nil) {
			set__iteration(cause, next_set, next_event,
				       double next_event__start_position;
				       double next_event__end_position;
				       double next_event__top_position;
				       double next_event__bottom_position;
				       {
					 f2ptr result = raw__timeline_event__render_extents(cause, next_event, this, &next_event__start_position, &next_event__end_position, &next_event__top_position, &next_event__bottom_position);
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       {
					 double font_size  = 0.75;
					 char*  label_str  = "next";
					 double text_width = raw__cairo_context__text_width(cause, cairo_context, font_size, label_str);
					 double width      = text_width + 0.5;
					 double height     = 1.0;
					 double x0         = ((end_position + next_event__start_position - width) / 2.0);
					 double y0         = (((top_position + bottom_position + next_event__top_position + next_event__bottom_position) / 2.0) - height) / 2.0;
					 f2ptr result = raw__cairo_context__render_rounded_text_box(cause, cairo_context, x0, y0, width, height, font_size, label_str,
												    0.5,                 // maximum_corner_radius
												    1.0, 1.0, 1.0, 1.0,  // background_rgba
												    0.1,
												    0.0, 0.0, 0.0, 1.0,  // text_rgba
												    0.0, 0.0, 0.0, 1.0,  // box_outline_rgba
												    1.0, 1.0, 1.0, 1.0); // text_outline_rgba
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       );
		      }
		    }
		    {
		      f2ptr contains_set = raw__timeline_event__contains_set(cause, event);
		      if (contains_set != nil) {
			set__iteration(cause, contains_set, contains_event,
				       double contains_event__start_position;
				       double contains_event__end_position;
				       double contains_event__top_position;
				       double contains_event__bottom_position;
				       {
					 f2ptr result = raw__timeline_event__render_extents(cause, contains_event, this, &contains_event__start_position, &contains_event__end_position, &contains_event__top_position, &contains_event__bottom_position);
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       {
					 double font_size  = 0.75;
					 char*  label_str  = "contains";
					 double text_width = raw__cairo_context__text_width(cause, cairo_context, font_size, label_str);
					 double width      = text_width + 0.5;
					 double height     = 1.0;
					 double x0         = (((start_position + end_position + contains_event__start_position + contains_event__end_position) / 2.0) - width) / 2.0;
					 double y0         = ((bottom_position + contains_event__top_position - height) / 2.0);
					 f2ptr result = raw__cairo_context__render_rounded_text_box(cause, cairo_context, x0, y0, width, height, font_size, label_str,
												    0.5,                 // maximum_corner_radius
												    1.0, 1.0, 1.0, 1.0,  // background_rgba
												    0.1,
												    0.0, 0.0, 0.0, 1.0,  // text_rgba
												    0.0, 0.0, 0.0, 1.0,  // box_outline_rgba
												    1.0, 1.0, 1.0, 1.0); // text_outline_rgba
					 if (raw__larva__is_type(cause, result)) {
					   return result;
					 }
				       }
				       );
		      }
		    }
		  }
		}
	      }
	    }
	    raw__cairo_context__restore(cause, cairo_context);
	  }
	}
      }
    }
    { // draw events
      f2ptr connected_part_array = raw__timeline__connected_part_array(cause, this);
      s64   connected_part_count = raw__array__length(cause, connected_part_array);
      {
	s64 connected_part_index;
	for (connected_part_index = 0; connected_part_index < connected_part_count; connected_part_index ++) {
	  f2ptr connected_part = raw__array__elt(cause, connected_part_array, connected_part_index);
	  {
	    double y_position  = f2double__d(raw__timeline_connected_part__y_position(cause, connected_part), cause);
	    f2ptr  event_array = raw__timeline_connected_part__sorted_event_array(cause, connected_part);
	    s64    event_count = raw__array__length(cause, event_array);
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		raw__cairo_context__save(cause, cairo_context);
		raw__cairo_context__translate(cause, cairo_context, timeline__left_border, timeline__right_border + y_position);
		f2ptr result = raw__timeline_event__cairo_render(cause, event, cairo_context, this);
		if (raw__larva__is_type(cause, result)) {
		  return result;
		}
		raw__cairo_context__restore(cause, cairo_context);
	      }
	    }
	  }
	}
      }
    }
    raw__cairo_context__restore(cause, cairo_context);
  }
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



boolean_t raw__timeline__timeline_event__overlaps(f2ptr cause, f2ptr this, f2ptr event_a, f2ptr event_b) {
  f2ptr minimum_time        = raw__timeline__minimum_time(cause, this);
  f2ptr maximum_time        = raw__timeline__maximum_time(cause, this);
  f2ptr event_a__start_time = raw__timeline_event__start_time(cause, event_a);
  f2ptr event_a__end_time   = raw__timeline_event__end_time(  cause, event_a);
  f2ptr event_b__start_time = raw__timeline_event__start_time(cause, event_b);
  f2ptr event_b__end_time   = raw__timeline_event__end_time(  cause, event_b);
  if (event_a__start_time == nil) {
    event_a__start_time = minimum_time;
  }
  if (event_a__end_time == nil) {
    event_a__end_time = maximum_time;
  }
  if (event_b__start_time == nil) {
    event_b__start_time = minimum_time;
  }
  if (event_b__end_time == nil) {
    event_b__end_time = maximum_time;
  }
  return (((f2__is_greater_than(cause, event_a__end_time,   event_b__start_time) != nil) &&
	   (f2__is_less_than(   cause, event_a__start_time, event_b__start_time) != nil))   ||
	  ((f2__is_greater_than(cause, event_a__end_time,   event_b__end_time)   != nil) &&
	   (f2__is_less_than(   cause, event_a__start_time, event_b__end_time)   != nil))   ||
	  ((f2__is_greater_than(cause, event_b__end_time,   event_a__start_time) != nil) &&
	   (f2__is_less_than(   cause, event_b__start_time, event_a__start_time) != nil))   ||
	  ((f2__is_greater_than(cause, event_b__end_time,   event_a__end_time)   != nil) &&
	   (f2__is_less_than(   cause, event_b__start_time, event_a__end_time)   != nil)));
}

f2ptr f2__timeline__timeline_event__overlaps(f2ptr cause, f2ptr this, f2ptr event_a, f2ptr event_b) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__timeline_event__is_type(cause, event_a)) ||
      (! raw__timeline_event__is_type(cause, event_b))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__timeline__timeline_event__overlaps(cause, this, event_a, event_b));
}
export_cefunk3(timeline__timeline_event__overlaps, this, event_a, event_b, 0, "");


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
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "calculate_positions"),       f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__calculate_positions")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "cairo_render"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__cairo_render")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "timeline_event-overlaps"),   f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline__timeline_event__overlaps")));}
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
  status("timeline initialized.");
  return nil;
}
export_cefunk0(timeline__core_extension__initialize, 0, "");

f2ptr f2__timeline__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "timeline_event"),          f2__timeline_event_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "timeline_connected_part"), f2__timeline_connected_part_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "timeline"),                f2__timeline_type__new_aux(cause));
  status("timeline types defined.");
  return nil;
}
export_cefunk0(timeline__core_extension__define_types, 0, "");

f2ptr f2__timeline__core_extension__destroy(f2ptr cause) {
  status("timeline destroyed.");
  return nil;
}
export_cefunk0(timeline__core_extension__destroy, 0, "");


