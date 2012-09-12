// 
// Copyright (c) 2007-2012 Bo Morgan.
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
  if (corner_radius > (dx / 2)) {
    corner_radius = dx / 2;
  }
  if (corner_radius > (dy / 2)) {
    corner_radius = dy / 2;
  }
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
  if (corner_radius > (dx / 2)) {
    corner_radius = dx / 2;
  }
  if (corner_radius > (dy / 2)) {
    corner_radius = dy / 2;
  }
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
  if (corner_radius > (dx / 2)) {
    corner_radius = dx / 2;
  }
  if (corner_radius > (dy / 2)) {
    corner_radius = dy / 2;
  }
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

void raw__cairo_context__render_text(f2ptr cause, f2ptr this, double x0, double y0, double font_size, char* text, double red, double green, double blue, double alpha) {
  raw__cairo_context__move_to(        cause, this, x0, y0 + (font_size * 0.75));
  raw__cairo_context__set_font_size(  cause, this, font_size);
  raw__cairo_context__text_path(      cause, this, text);
  raw__cairo_context__set_source_rgba(cause, this, red, green, blue, alpha);
  raw__cairo_context__fill(           cause, this);
}

void raw__cairo_context__render_text_scaled(f2ptr cause, f2ptr this, double x0, double y0, double font_size, double x_scale, double y_scale, char* text, double red, double green, double blue, double alpha) {
  boolean_t need_scale = ((x_scale != 1.0) ||
			  (y_scale != 1.0));
  raw__cairo_context__move_to(      cause, this, x0, y0 + (font_size * 0.75));
  raw__cairo_context__set_font_size(cause, this, font_size);
  if (need_scale) {
    raw__cairo_context__save( cause, this);
    raw__cairo_context__scale(cause, this, x_scale, y_scale);
  }
  raw__cairo_context__text_path(      cause, this, text);
  raw__cairo_context__set_source_rgba(cause, this, red, green, blue, alpha);
  raw__cairo_context__fill(           cause, this);
  if (need_scale) {
    raw__cairo_context__restore(cause, this);
  }
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

f2ptr raw__cairo_context__render_centered_text(f2ptr cause, f2ptr this, double cx, double cy, double font_size, char* text, double red, double green, double blue, double alpha) {
  raw__cairo_context__set_font_size(cause, this, font_size);
  f2ptr text_extents = raw__cairo_context__text_extents(cause, this, text);
  if (raw__larva__is_type(cause, text_extents)) {
    return text_extents;
  }
  f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
  double text_extents__width__d = f2double__d(text_extents__width, cause);
  double x0 = cx - (text_extents__width__d / 2);
  double y0 = cy - (font_size              / 2);
  raw__cairo_context__render_text(cause, this, x0, y0, font_size, text, red, green, blue, alpha);
  return nil;
}

f2ptr raw__cairo_context__render_centered_outlined_frame(f2ptr cause, f2ptr this, double cx, double cy, double font_size, f2ptr frame, double outline_width, double maximum_width,
							 double red, double green, double blue, double alpha,
							 double outline_red, double outline_green, double outline_blue, double outline_alpha) {
  s64 frame__key_count = 0;
  frame__var__iteration(cause, frame, key, value,
			key   = nil;
			value = nil;
			frame__key_count ++;
			);
  boolean_t has_cairo_type          = boolean__false;
  s64       cairo_type_index        = 0;
  u8**      key_utf8_string_array   = (u8**)from_ptr(f2__malloc(sizeof(u8*) * frame__key_count));
  s64*      key_utf8_length_array   = (s64*)from_ptr(f2__malloc(sizeof(s64) * frame__key_count));
  u8**      value_utf8_string_array = (u8**)from_ptr(f2__malloc(sizeof(u8*) * frame__key_count));
  s64*      value_utf8_length_array = (s64*)from_ptr(f2__malloc(sizeof(s64) * frame__key_count));
  {
    s64 index = 0;
    frame__var__iteration(cause, frame, key, value,
			  if (index < frame__key_count) {
			    if (raw__eq(cause, key, new__symbol(cause, "cairo_render_type"))) {
			      has_cairo_type   = boolean__true;
			      cairo_type_index = index;
			    }
			    {
			      f2ptr key__string = assert_value(f2__exp__as__string(cause, key));
			      key_utf8_length_array[index] = raw__string__utf8_length(cause, key__string);
			      key_utf8_string_array[index] = (u8*)from_ptr(f2__malloc((key_utf8_length_array[index] + 1) * sizeof(u8)));
			      raw__string__utf8_str_copy(cause, key__string, key_utf8_string_array[index]);
			      key_utf8_string_array[index][key_utf8_length_array[index]] = 0;
			    }
			    {
			      f2ptr value__string = assert_value(f2__exp__as__string(cause, value));
			      value_utf8_length_array[index] = raw__string__utf8_length(cause, value__string);
			      value_utf8_string_array[index] = (u8*)from_ptr(f2__malloc((value_utf8_length_array[index] + 1) * sizeof(u8)));
			      raw__string__utf8_str_copy(cause, value__string, value_utf8_string_array[index]);
			      value_utf8_string_array[index][value_utf8_length_array[index]] = 0;
			    }
			  }
			  index ++;
			  );
  }
  
  {
    double max_key_text_width   = 0;
    double max_value_text_width = 0;
    {
      s64 index;
      for (index = 0; index < frame__key_count; index ++) {
	if ((! has_cairo_type) || (index != cairo_type_index)) {
	  {
	    raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "bold"));
	    raw__cairo_context__set_font_size(cause, this, font_size);
	    f2ptr text_extents = assert_value(raw__cairo_context__text_extents(cause, this, (char*)key_utf8_string_array[index]));
	    f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
	    double text_extents__width__d = f2double__d(text_extents__width, cause);
	    if (text_extents__width__d > max_key_text_width) {
	      max_key_text_width = text_extents__width__d;
	    }
	  }
	  {
	    raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "normal"));
	    raw__cairo_context__set_font_size(cause, this, font_size);
	    f2ptr text_extents = assert_value(raw__cairo_context__text_extents(cause, this, (char*)value_utf8_string_array[index]));
	    f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
	    double text_extents__width__d = f2double__d(text_extents__width, cause);
	    if (text_extents__width__d > max_value_text_width) {
	      max_value_text_width = text_extents__width__d;
	    }
	  }
	}
      }
    }
    if (has_cairo_type) {
      double title_font_size = font_size * 1.05;
      raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "bold"));
      raw__cairo_context__set_font_size(cause, this, title_font_size);
      f2ptr text_extents = assert_value(raw__cairo_context__text_extents(cause, this, (char*)value_utf8_string_array[cairo_type_index]));
      f2ptr  text_extents__width    = raw__cairo_text_extents__width(cause, text_extents);
      double text_extents__width__d = f2double__d(text_extents__width, cause);
      double squish_factor          = 1.0;
      if (text_extents__width__d > maximum_width) {
	squish_factor = (maximum_width / text_extents__width__d);
      }
      if (squish_factor > 0.25) {
	double y0 = cy - (title_font_size * frame__key_count / 2);
	double x0 = cx - ((text_extents__width__d / 2) * squish_factor);
	raw__cairo_context__render_text_scaled(cause, this, x0, y0, title_font_size, squish_factor, 1.0, (char*)value_utf8_string_array[cairo_type_index], red, green, blue, alpha);
      }
    }
    double space_between_key_and_value = 1.0;
    {
      raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "normal"));
      raw__cairo_context__set_font_size(cause, this, font_size);
      double squish_factor = 1.0;
      if ((max_key_text_width + space_between_key_and_value + max_value_text_width) > maximum_width) {
	squish_factor = (maximum_width / (max_key_text_width + space_between_key_and_value + max_value_text_width));
      }
      if (squish_factor > 0.25) {
	s64 y_index = 0;
	if (has_cairo_type) {
	  y_index ++;
	}
	s64 index;
	for (index = 0; index < frame__key_count; index ++) {
	  if ((! has_cairo_type) || (index != cairo_type_index)) {
	    double y0 = cy - (font_size * frame__key_count / 2) + (y_index * font_size);
	    {
	      raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "bold"));
	      raw__cairo_context__set_font_size(cause, this, font_size);
	      double x0 = cx + ((-(max_key_text_width + space_between_key_and_value + max_value_text_width) / 2) * squish_factor);
	      raw__cairo_context__render_text_scaled(cause, this, x0, y0, font_size, squish_factor, 1.0, (char*)key_utf8_string_array[index], red, green, blue, alpha);
	    }
	    {
	      raw__cairo_context__select_font_face(cause, this, "serif", new__symbol(cause, "normal"), new__symbol(cause, "normal"));
	      raw__cairo_context__set_font_size(cause, this, font_size);
	      double x0 = cx + ((-((max_key_text_width + space_between_key_and_value + max_value_text_width) / 2) + max_key_text_width + space_between_key_and_value) * squish_factor);
	      raw__cairo_context__render_text_scaled(cause, this, x0, y0, font_size, squish_factor, 1.0, (char*)value_utf8_string_array[index], red, green, blue, alpha);
	    }
	    y_index ++;
	  }
	}
      }
    }
  }
  {
    s64 index;
    for (index = 0; index < frame__key_count; index ++) {
      f2__free(to_ptr(key_utf8_string_array[index]));
      f2__free(to_ptr(value_utf8_string_array[index]));
    }
  }
  f2__free(to_ptr(key_utf8_string_array));
  f2__free(to_ptr(value_utf8_string_array));
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
  double maximum_width = dx - (outline_width * 2);
  if (maximum_width > 0.0) {
    assert_value(raw__cairo_context__render_centered_outlined_frame(cause, this, x0 + (dx / 2), y0 + (dy / 2), font_size, frame, outline_width, maximum_width,  text_red, text_green, text_blue, text_alpha,  text_outline_red, text_outline_green, text_outline_blue, text_outline_alpha));
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
  assert_value(raw__cairo_context__render_centered_outlined_text(cause, this, x0 + (dx / 2), y0 + (dy / 2), font_size, text, outline_width,  text_red, text_green, text_blue, text_alpha,  text_outline_red, text_outline_green, text_outline_blue, text_outline_alpha));
  return nil;
}



// timeline_event

def_ceframe11(timeline, timeline_event,
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


f2ptr raw__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  f2ptr contains_set        = f2__set__new(cause);
  f2ptr is_contained_by_set = f2__set__new(cause);
  f2ptr next_set            = f2__set__new(cause);
  f2ptr previous_set        = f2__set__new(cause);
  f2ptr causes_set          = f2__set__new(cause);
  f2ptr is_caused_by_set    = f2__set__new(cause);
  f2ptr height              = nil;
  return f2timeline_event__new(cause, name, height, start_time, end_time, contains_set, is_contained_by_set, next_set, previous_set, causes_set, is_caused_by_set, nil);
}

f2ptr f2__timeline_event__new(f2ptr cause, f2ptr name, f2ptr start_time, f2ptr end_time) {
  assert_argument_type_or_nil(time, start_time);
  assert_argument_type_or_nil(time, end_time);
  if ((start_time != nil) && (end_time != nil)) {
    f2ptr is_greater_than = assert_value(f2__is_greater_than(cause, start_time, end_time));
    if (is_greater_than != nil) {
      return f2larva__new(cause, 1351, nil);
    }
  }
  return raw__timeline_event__new(cause, name, start_time, end_time);
}
export_cefunk3(timeline_event__new, name, start_time, end_time, 0, "Returns a new timeline_event object.");


f2ptr raw__timeline_event__cairo_render_frame(f2ptr cause, f2ptr this) {
  f2ptr render_frame = nil;
  {
    f2ptr user_render_frame = raw__timeline_event__render_frame(cause, this);
    if (raw__frame__is_type(cause, user_render_frame)) {
      render_frame = user_render_frame;
    } else {
      render_frame = f2__frame__new(cause, f2list4__new(cause,
							new__string(cause, "cairo_render_type"), new__symbol(cause, "Event"),
							new__string(cause, "value"),             user_render_frame));
    }
  }
  return render_frame;
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
    double timeline__left_border   = f2double__d(raw__timeline__left_border( cause, timeline), cause);
    double timeline__right_border  = f2double__d(raw__timeline__right_border(cause, timeline), cause);
    double timeline__x_width       = f2double__d(raw__timeline__x_width(     cause, timeline), cause);
    double content_width           = timeline__x_width - timeline__left_border - timeline__right_border;
    if (start_position != NULL) {
      *start_position                              = start_nanoseconds * content_width / total_nanoseconds;
    }
    if (end_position != NULL) {
      *end_position                                = end_nanoseconds   * content_width / total_nanoseconds;
    }
  }
  if ((top_position != NULL) || (bottom_position != NULL)) {
    f2ptr  y_start    = raw__timeline_event__y_start(cause, this);
    double y_start__d = f2double__d(y_start, cause);
    f2ptr  height     = raw__timeline_event__height(cause, this);
    double height__d  = f2double__d(height, cause);
    if (top_position != NULL) {
      *top_position = y_start__d;
    }
    if (bottom_position != NULL) {
      *bottom_position = y_start__d + height__d;
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
  assert_value(raw__timeline_event__render_extents(cause, this, timeline, &start_position, &end_position, &top_position, &bottom_position));
  f2ptr render_frame = raw__timeline_event__cairo_render_frame(cause, this);
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
    assert_value(raw__cairo_context__render_frame_text_box(cause, cairo_context, left_edge_type, right_edge_type,
							   start_position, top_position,                                  // x0, y0
							   end_position - start_position, bottom_position - top_position, // dx, dy
							   1,                                                             // font size
							   render_frame,                                                  // frame
							   0.5,                                                           // maximum corner radius
							   142 / 255.0, 200 / 255.0, 255 / 255.0, 1,                      // background rgba
							   0.2,                                                           // outline width
							   0, 0, 0, 1,                                                    // text rgba
							   0, 0, 0, 1,                                                    // box outline rgba
							   142 / 255.0, 200 / 255.0, 255 / 255.0, 1));                     // text outline rgba
  }
  raw__cairo_context__restore(cause, cairo_context);
  return nil;
}

f2ptr f2__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr timeline) {
  assert_argument_type(timeline_event, this);
  assert_argument_type(cairo_context,  cairo_context);
  assert_argument_type(timeline,       timeline);
  return raw__timeline_event__cairo_render(cause, this, cairo_context, timeline);
}
export_cefunk3(timeline_event__cairo_render, this, cairo_context, timeline, 0, "Renders this timeline_event in the given cairo_context.");


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
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
  raw__timeline_event__add_contains(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_contains, this, event, 0, "");


void raw__timeline_event__add_is_contained_by(f2ptr cause, f2ptr this, f2ptr event) {
  raw__timeline_event__add_contains(cause, event, this);
}

f2ptr f2__timeline_event__add_is_contained_by(f2ptr cause, f2ptr this, f2ptr event) {
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
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
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
  raw__timeline_event__add_next(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_next, this, event, 0, "");


void raw__timeline_event__add_previous(f2ptr cause, f2ptr this, f2ptr event) {
  raw__timeline_event__add_next(cause, event, this);
}

f2ptr f2__timeline_event__add_previous(f2ptr cause, f2ptr this, f2ptr event) {
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
  raw__timeline_event__add_previous(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_previous, this, event, 0, "");


void raw__timeline_event__add_causes(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr causes_set = raw__timeline_event__causes_set(cause, this);
  raw__set__add(cause, causes_set, event);
  f2ptr event__is_caused_by_set = raw__timeline_event__is_caused_by_set(cause, event);
  raw__set__add(cause, event__is_caused_by_set, this);
}

f2ptr f2__timeline_event__add_causes(f2ptr cause, f2ptr this, f2ptr event) {
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
  raw__timeline_event__add_causes(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_causes, this, event, 0, "");


void raw__timeline_event__add_is_caused_by(f2ptr cause, f2ptr this, f2ptr event) {
  raw__timeline_event__add_causes(cause, event, this);
}

f2ptr f2__timeline_event__add_is_caused_by(f2ptr cause, f2ptr this, f2ptr event) {
  assert_argument_type(timeline_event, this);
  assert_argument_type(timeline_event, event);
  raw__timeline_event__add_is_caused_by(cause, this, event);
  return nil;
}
export_cefunk2(timeline_event__add_is_caused_by, this, event, 0, "");


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
  assert_argument_type(timeline_event, this);
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
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_causes"),                f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_causes")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_is_caused_by"),          f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__add_is_caused_by")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__terminal_print_with_frame")));}
  return this;
}



// timeline_connected_part

def_ceframe5(timeline, timeline_connected_part,
	     event_set,
	     sorted_event_array,
	     maximum_y,
	     y_position,
	     minimum_x);

f2ptr raw__timeline_connected_part__new(f2ptr cause) {
  f2ptr event_set          = f2__set__new(cause);
  f2ptr sorted_event_array = nil;
  f2ptr maximum_y          = nil;
  f2ptr y_position         = nil;
  f2ptr minimum_x          = nil;
  return f2timeline_connected_part__new(cause, event_set, sorted_event_array, maximum_y, y_position, minimum_x);
}

f2ptr f2__timeline_connected_part__new(f2ptr cause) {
  return raw__timeline_connected_part__new(cause);
}
export_cefunk0(timeline_connected_part__new, 0, "");



// timeline

def_ceframe14(timeline, timeline,
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

f2ptr raw__timeline__new(f2ptr cause) {
  f2ptr timeline_event_set             = f2__set__new(cause);
  f2ptr left_border                    = f2double__new(cause, 2.0);
  f2ptr right_border                   = f2double__new(cause, 2.0);
  f2ptr top_border                     = f2double__new(cause, 2.0);
  f2ptr bottom_border                  = f2double__new(cause, 2.0);
  f2ptr x_width                        = f2double__new(cause, 100.0);
  f2ptr y_event_distance               = f2double__new(cause, 3.5);
  f2ptr y_connected_part_distance      = f2double__new(cause, 4.5);
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
			 y_connected_part_distance,
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
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),       new__symbol(cause, "timeline_already_contains_timeline_event"),
				   new__symbol(cause, "funkname"),       new__symbol(cause, "timeline-add_timeline_event"),
				   new__symbol(cause, "this"),           this,
				   new__symbol(cause, "timeline_event"), timeline_event));
  }
  raw__set__add(cause, timeline_event_set, timeline_event);
  return nil;
}

f2ptr f2__timeline__add_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  assert_argument_type(timeline,       this);
  assert_argument_type(timeline_event, timeline_event);
  return raw__timeline__add_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__add_timeline_event, this, timeline_event, 0, "Adds a timeline_event to a timeline.");


f2ptr raw__timeline__remove_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  if (! raw__set__contains(cause, timeline_event_set, timeline_event)) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),       new__symbol(cause, "timeline_does_not_contain_timeline_event"),
				   new__symbol(cause, "funkname"),       new__symbol(cause, "timeline-remove_timeline_event"),
				   new__symbol(cause, "this"),           this,
				   new__symbol(cause, "timeline_event"), timeline_event));
  }
  raw__set__remove(cause, timeline_event_set, timeline_event);
  return nil;
}

f2ptr f2__timeline__remove_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  assert_argument_type(timeline,       this);
  assert_argument_type(timeline_event, timeline_event);
  return raw__timeline__remove_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__remove_timeline_event, this, timeline_event, 0, "Removes a timeline_event from a timeline.");


boolean_t raw__timeline__contains_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  return raw__set__contains(cause, timeline_event_set, timeline_event);
}

f2ptr f2__timeline__contains_timeline_event(f2ptr cause, f2ptr this, f2ptr timeline_event) {
  assert_argument_type(timeline,       this);
  assert_argument_type(timeline_event, timeline_event);
  return raw__timeline__contains_timeline_event(cause, this, timeline_event);
}
export_cefunk2(timeline__contains_timeline_event, this, timeline_event, 0, "Returns whether or not a timeline contains a timeline_event.");


f2ptr raw__timeline__timeline_events(f2ptr cause, f2ptr this) {
  f2ptr timeline_event_set = raw__timeline__timeline_event_set(cause, this);
  return raw__set__elements(cause, timeline_event_set);
}

f2ptr f2__timeline__timeline_events(f2ptr cause, f2ptr this) {
  assert_argument_type(timeline, this);
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
    {
      s64 minimum_time__nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(minimum_time, cause), cause);
      s64 maximum_time__nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(maximum_time, cause), cause);
      if (minimum_time__nanoseconds_since_1970 == maximum_time__nanoseconds_since_1970) {
	maximum_time__nanoseconds_since_1970 += 8;
      }
      s64 left_right_border_nanoseconds = (maximum_time__nanoseconds_since_1970 - minimum_time__nanoseconds_since_1970) / 8;
      minimum_time__nanoseconds_since_1970 -= left_right_border_nanoseconds;
      maximum_time__nanoseconds_since_1970 += left_right_border_nanoseconds;
      minimum_time = f2__time__new(cause, f2integer__new(cause, minimum_time__nanoseconds_since_1970));
      maximum_time = f2__time__new(cause, f2integer__new(cause, maximum_time__nanoseconds_since_1970));
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
	    connected_parts = raw__cons__new(cause, connected_part, connected_parts);
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
	      {
		f2ptr causes_set = raw__timeline_event__causes_set(cause, expand_event);
		if (causes_set != nil) {
		  set__iteration(cause, causes_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr is_caused_by_set = raw__timeline_event__is_caused_by_set(cause, expand_event);
		if (is_caused_by_set != nil) {
		  set__iteration(cause, is_caused_by_set, expansion_event,
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
  // calculate minimum_x for each connected part
  {
    f2ptr connected_part_iter = connected_parts;
    while (connected_part_iter != nil) {
      f2ptr connected_part = f2__cons__car(cause, connected_part_iter);
      {
  	f2ptr minimum_x     = nil;
  	f2ptr connected_set = raw__timeline_connected_part__event_set(cause, connected_part);
  	set__iteration(cause, connected_set, connected_event,
  		       f2ptr start_time = assert_value(f2__timeline_event__start_time(cause, connected_event));
  		       if ((minimum_x == nil) ||
  			   (assert_value(f2__is_less_than(cause, start_time, minimum_x)) != nil)) {
  			 minimum_x = start_time;
  		       }
  		       );
  	f2__timeline_connected_part__minimum_x__set(cause, connected_part, minimum_x);
      }
      connected_part_iter = assert_value(f2__cons__cdr(cause, connected_part_iter));
    }
  }
  // sort connected parts by minimum_x
  {
    
  }
  // 
  double y_event_distance = f2double__d(raw__timeline__y_event_distance(cause, this), cause);
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
		  f2ptr j__causes_set   = raw__timeline_event__causes_set(  cause, j);
		  if (raw__set__contains(cause, j__contains_set, i) ||
		      raw__set__contains(cause, j__next_set,     i) ||
		      raw__set__contains(cause, j__causes_set,   i)) {
		    raw__array__elt__set(cause, event_array, i__index, j);
		    raw__array__elt__set(cause, event_array, j__index, i);
		    i__index --;
		    break;
		  }
		}
	      }
	    }
	    { // calculate event heights
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		f2ptr cairo_render_frame = raw__timeline_event__cairo_render_frame(cause, event);
		s64 key_count = 0;
		frame__var__iteration(cause, cairo_render_frame, key, value,
				      key   = nil;
				      value = nil;
				      key_count ++;
				      );
		double height = key_count + 1.5;
		raw__timeline_event__height__set(cause, event, f2double__new(cause, height));
	      }
	    }
	    {
	      double y_start = 0;
	      s64    index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		raw__timeline_event__y_start__set(cause, event, f2double__new(cause, y_start));
		f2ptr  height    = raw__timeline_event__height(cause, event);
		double height__d = f2double__d(height, cause);
		y_start += (height__d + y_event_distance);
	      }
	    }
	    { // move events up if possible
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr event = raw__array__elt(cause, event_array, index);
		{
		  double maximum_overlap_y = 0;
		  {
		    s64 o_index;
		    for (o_index = index - 1; o_index >= 0; o_index --) {
		      f2ptr o_event = raw__array__elt(cause, event_array, o_index);
		      f2ptr o_event__contains_set = raw__timeline_event__contains_set(cause, o_event);
		      f2ptr o_event__causes_set   = raw__timeline_event__causes_set(  cause, o_event);
		      if (raw__set__contains(cause, o_event__contains_set, event) ||
		          raw__set__contains(cause, o_event__causes_set,   event) ||
		          raw__timeline__timeline_event__overlaps(cause, this, event, o_event)) {
			f2ptr  o_y_start    = raw__timeline_event__y_start(cause, o_event);
			double o_y_start__d = f2double__d(o_y_start, cause);
			f2ptr  o_height     = raw__timeline_event__height(cause, o_event);
			double o_height__d  = f2double__d(o_height, cause);
			if (o_y_start__d + o_height__d + y_event_distance > maximum_overlap_y) {
			  maximum_overlap_y = o_y_start__d + o_height__d + y_event_distance;
			}
		      }
		    }
		  }
		  raw__timeline_event__y_start__set(cause, event, f2double__new(cause, maximum_overlap_y));
		}
	      }
	    }
	    double connected_part_max_y = 0;
	    {
	      s64 index;
	      for (index = 0; index < event_count; index ++) {
		f2ptr  event      = raw__array__elt(cause, event_array, index);
		f2ptr  y_start    = raw__timeline_event__y_start(cause, event);
		double y_start__d = f2double__d(y_start, cause);
		f2ptr  height     = raw__timeline_event__height(cause, event);
		double height__d  = f2double__d(height, cause);
		if (y_start__d + height__d > connected_part_max_y) {
		  connected_part_max_y = y_start__d + height__d;
		}
	      }
	    }
	    raw__timeline_connected_part__maximum_y__set(cause, connected_part, f2double__new(cause, connected_part_max_y));
	    raw__timeline_connected_part__y_position__set(cause, connected_part, f2double__new(cause, y_position));
	    double y_connected_part_distance = f2double__d(raw__timeline__y_connected_part_distance(cause, this), cause);
	    y_position += connected_part_max_y + y_connected_part_distance;
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
  assert_argument_type(timeline, this);
  return raw__timeline__calculate_positions(cause, this);
}
export_cefunk1(timeline__calculate_positions, this, 0, "Prepares the timeline for rendering.");


f2ptr raw__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  {
    f2ptr positions_have_been_calculated = raw__timeline__positions_have_been_calculated(cause, this);
    if (positions_have_been_calculated == nil) {
      assert_value(raw__timeline__calculate_positions(cause, this));
    }
  }
  
  double timeline__left_border  = f2double__d(raw__timeline__left_border( cause, this), cause);
  double timeline__right_border = f2double__d(raw__timeline__right_border(cause, this), cause);
  double timeline__top_border   = f2double__d(raw__timeline__top_border(  cause, this), cause);
  double timeline__x_width      = f2double__d(raw__timeline__x_width(     cause, this), cause);
  double timeline__y_height     = f2double__d(raw__timeline__y_height(    cause, this), cause);
  
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
      boolean_t draw_dot_grid = boolean__false;
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
		    assert_value(raw__timeline_event__render_extents(cause, event, this, &start_position, &end_position, &top_position, &bottom_position));
		    {
		      f2ptr next_set = raw__timeline_event__next_set(cause, event);
		      if (next_set != nil) {
			set__iteration(cause, next_set, next_event,
				       double next_event__start_position;
				       double next_event__end_position;
				       double next_event__top_position;
				       double next_event__bottom_position;
				       assert_value(raw__timeline_event__render_extents(cause, next_event, this, &next_event__start_position, &next_event__end_position, &next_event__top_position, &next_event__bottom_position));
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
				       assert_value(raw__timeline_event__render_extents(cause, contains_event, this, &contains_event__start_position, &contains_event__end_position, &contains_event__top_position, &contains_event__bottom_position));
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
		    {
		      f2ptr causes_set = raw__timeline_event__causes_set(cause, event);
		      if (causes_set != nil) {
			set__iteration(cause, causes_set, causes_event,
				       double causes_event__start_position;
				       double causes_event__end_position;
				       double causes_event__top_position;
				       double causes_event__bottom_position;
				       assert_value(raw__timeline_event__render_extents(cause, causes_event, this, &causes_event__start_position, &causes_event__end_position, &causes_event__top_position, &causes_event__bottom_position));
				       {
					 double x0 = (start_position + end_position) / 2.0;
					 double y0 = bottom_position;
					 double x1 = x0;
					 double y1 = (bottom_position + causes_event__top_position) / 2.0;
					 double x2 = (causes_event__start_position + causes_event__end_position) / 2.0;
					 double y2 = y1;
					 double x3 = x2;
					 double y3 = causes_event__top_position;
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
		    assert_value(raw__timeline_event__render_extents(cause, event, this, &start_position, &end_position, &top_position, &bottom_position));
		    {
		      f2ptr next_set = raw__timeline_event__next_set(cause, event);
		      if (next_set != nil) {
			set__iteration(cause, next_set, next_event,
				       double next_event__start_position;
				       double next_event__end_position;
				       double next_event__top_position;
				       double next_event__bottom_position;
				       assert_value(raw__timeline_event__render_extents(cause, next_event, this, &next_event__start_position, &next_event__end_position, &next_event__top_position, &next_event__bottom_position));
				       {
					 double font_size  = 0.75;
					 char*  label_str  = "next";
					 double text_width = raw__cairo_context__text_width(cause, cairo_context, font_size, label_str);
					 double width      = text_width + 0.5;
					 double height     = 1.0;
					 double x0         = ((end_position + next_event__start_position - width) / 2.0);
					 double y0         = (((top_position + bottom_position + next_event__top_position + next_event__bottom_position) / 2.0) - height) / 2.0;
					 assert_value(raw__cairo_context__render_rounded_text_box(cause, cairo_context, x0, y0, width, height, font_size, label_str,
												  0.5,                 // maximum_corner_radius
												  1.0, 1.0, 1.0, 1.0,  // background_rgba
												  0.1,
												  0.0, 0.0, 0.0, 1.0,  // text_rgba
												  0.0, 0.0, 0.0, 1.0,  // box_outline_rgba
												  1.0, 1.0, 1.0, 1.0)); // text_outline_rgba
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
				       assert_value(raw__timeline_event__render_extents(cause, contains_event, this, &contains_event__start_position, &contains_event__end_position, &contains_event__top_position, &contains_event__bottom_position));
				       {
					 double font_size  = 0.75;
					 char*  label_str  = "contains";
					 double text_width = raw__cairo_context__text_width(cause, cairo_context, font_size, label_str);
					 double width      = text_width + 0.5;
					 double height     = 1.0;
					 double x0         = (((start_position + end_position + contains_event__start_position + contains_event__end_position) / 2.0) - width) / 2.0;
					 double y0         = ((bottom_position + contains_event__top_position - height) / 2.0);
					 assert_value(raw__cairo_context__render_rounded_text_box(cause, cairo_context, x0, y0, width, height, font_size, label_str,
												  0.5,                 // maximum_corner_radius
												  1.0, 1.0, 1.0, 1.0,  // background_rgba
												  0.1,
												  0.0, 0.0, 0.0, 1.0,  // text_rgba
												  0.0, 0.0, 0.0, 1.0,  // box_outline_rgba
												  1.0, 1.0, 1.0, 1.0)); // text_outline_rgba
				       }
				       );
		      }
		    }
		    {
		      f2ptr causes_set = raw__timeline_event__causes_set(cause, event);
		      if (causes_set != nil) {
			set__iteration(cause, causes_set, causes_event,
				       double causes_event__start_position;
				       double causes_event__end_position;
				       double causes_event__top_position;
				       double causes_event__bottom_position;
				       assert_value(raw__timeline_event__render_extents(cause, causes_event, this, &causes_event__start_position, &causes_event__end_position, &causes_event__top_position, &causes_event__bottom_position));
				       {
					 double font_size  = 0.75;
					 char*  label_str  = "causes";
					 double text_width = raw__cairo_context__text_width(cause, cairo_context, font_size, label_str);
					 double width      = text_width + 0.5;
					 double height     = 1.0;
					 double x0         = (((start_position + end_position + causes_event__start_position + causes_event__end_position) / 2.0) - width) / 2.0;
					 double y0         = ((bottom_position + causes_event__top_position - height) / 2.0);
					 assert_value(raw__cairo_context__render_rounded_text_box(cause, cairo_context, x0, y0, width, height, font_size, label_str,
												  0.5,                 // maximum_corner_radius
												  1.0, 1.0, 1.0, 1.0,  // background_rgba
												  0.1,
												  0.0, 0.0, 0.0, 1.0,  // text_rgba
												  0.0, 0.0, 0.0, 1.0,  // box_outline_rgba
												  1.0, 1.0, 1.0, 1.0)); // text_outline_rgba
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
		assert_value(raw__timeline_event__cairo_render(cause, event, cairo_context, this));
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
  assert_argument_type(timeline,      this);
  assert_argument_type(cairo_context, cairo_context);
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
  s64 event_a__start_time__nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(event_a__start_time, cause), cause);
  s64 event_a__end_time__nanoseconds_since_1970   = f2integer__i(f2time__nanoseconds_since_1970(event_a__end_time,   cause), cause);
  s64 event_b__start_time__nanoseconds_since_1970 = f2integer__i(f2time__nanoseconds_since_1970(event_b__start_time, cause), cause);
  s64 event_b__end_time__nanoseconds_since_1970   = f2integer__i(f2time__nanoseconds_since_1970(event_b__end_time,   cause), cause);
  return ((event_a__start_time__nanoseconds_since_1970 == event_b__start_time__nanoseconds_since_1970)    ||
	  (event_a__end_time__nanoseconds_since_1970   == event_b__end_time__nanoseconds_since_1970)      ||
	  ((event_a__end_time__nanoseconds_since_1970   > event_b__start_time__nanoseconds_since_1970) &&
	   (event_a__start_time__nanoseconds_since_1970 < event_b__start_time__nanoseconds_since_1970))   ||
	  ((event_a__end_time__nanoseconds_since_1970   > event_b__end_time__nanoseconds_since_1970) &&
	   (event_a__start_time__nanoseconds_since_1970 < event_b__end_time__nanoseconds_since_1970))   ||
	  ((event_b__end_time__nanoseconds_since_1970   > event_a__start_time__nanoseconds_since_1970) &&
	   (event_b__start_time__nanoseconds_since_1970 < event_a__start_time__nanoseconds_since_1970))   ||
	  ((event_b__end_time__nanoseconds_since_1970   > event_a__end_time__nanoseconds_since_1970) &&
	   (event_b__start_time__nanoseconds_since_1970 < event_a__end_time__nanoseconds_since_1970)));
}

f2ptr f2__timeline__timeline_event__overlaps(f2ptr cause, f2ptr this, f2ptr event_a, f2ptr event_b) {
  assert_argument_type(timeline,       this);
  assert_argument_type(timeline_event, event_a);
  assert_argument_type(timeline_event, event_b);
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
  assert_argument_type(timeline, this);
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
  core_extension__ping(timeline, cairo);
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


