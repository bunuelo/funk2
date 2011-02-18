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

def_ceframe0(timeline, timeline_event);


f2ptr raw__timeline_event__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__semantic_event__new(cause, semantic_realm);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "timeline_event"));
  return this;
}

f2ptr f2__timeline_event__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline_event__new(cause, semantic_realm);
}
export_cefunk1(timeline_event__new, semantic_realm, 0, "Returns a new timeline_event object.");


f2ptr raw__timeline_event__cairo_action_name(f2ptr cause, f2ptr this) {
  f2ptr action_name_set = raw__semantic_event__action_name__lookup(cause, this);
  s64   action_name__length;
  u8*   action_name__str;
  if (action_name_set != nil) {
    action_name__length = 0;
    f2ptr action_name_as_strings = nil;
    set__iteration(cause, action_name_set, action_name,
		   f2ptr action_name_as_string = f2__exp__as__string(cause, action_name);
		   if (raw__larva__is_type(cause, action_name_as_string)) {
		     return action_name_as_string;
		   }
		   action_name__length += raw__string__length(cause, action_name_as_string);
		   action_name__length += 2;
		   action_name_as_strings = f2cons__new(cause, action_name_as_string, action_name_as_strings));
    action_name__length -= 2;
    action_name__str = (u8*)from_ptr(f2__malloc(action_name__length + 1));
    {
      s64   action_name__index = 0;
      f2ptr iter               = action_name_as_strings;
      while (iter != nil) {
	f2ptr action_name_as_string = f2cons__car(iter, cause);
	{
	  raw__string__str_copy(cause, action_name_as_string, action_name__str + action_name__index);
	  action_name__index += raw__string__length(cause, action_name_as_string);
	  memcpy(action_name__str + action_name__index, ", ", 2);
	  action_name__index += 2;
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
    action_name__str[action_name__length] = 0;
  } else {
    char* default_name = "Event";
    action_name__length = strlen(default_name);
    action_name__str = (u8*)from_ptr(f2__malloc(action_name__length + 1));
    memcpy(action_name__str, default_name, action_name__length);
    action_name__str[action_name__length] = 0;
  }
  f2ptr action_name = new__string(cause, (char*)action_name__str);
  f2__free(to_ptr(action_name__str));
  return action_name;
}

f2ptr raw__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  f2ptr action_name         = raw__timeline_event__cairo_action_name(cause, this);
  s64   action_name__length = raw__string__length(cause, action_name);
  u8*   action_name__str    = (u8*)from_ptr(f2__malloc(action_name__length));
  raw__string__str_copy(cause, action_name, action_name__str);
  action_name__str[action_name__length] = 0;
  raw__cairo_context__save(cause, cairo_context);
  {
    double text_width  = raw__cairo_context__text_width(cause, cairo_context, 1, (char*)action_name__str);
    double event_width = (double)((int)(text_width + 1.5));
    f2ptr  result      = raw__cairo_context__render_rounded_text_box(cause, cairo_context,
								     0, 0,                                    // x0, y0
								     event_width, 1.5,                        // dx, dy
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

f2ptr f2__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__cairo_context__is_type(cause, cairo_context))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline_event__cairo_render(cause, this, cairo_context);
}
export_cefunk2(timeline_event__cairo_render, this, cairo_context, 0, "Renders this timeline_event in the given cairo_context.");


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
  f2__primobject_type__parents__set(cause, this, f2list1__new(cause, new__symbol(cause, "semantic_event")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "cairo_render"),              f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__cairo_render")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "timeline"), new__symbol(cause, "timeline_event__terminal_print_with_frame")));}
  return this;
}







// timeline

def_ceframe1(timeline, timeline,
	     timeline_event_set);


f2ptr raw__timeline__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr timeline_event_set = f2__set__new(cause);
  f2ptr this               = f2__semantic_knowledge_base__new(cause, name, semantic_realm);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),               new__symbol(cause, "timeline"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "timeline_event_set"), timeline_event_set);
  return this;
}

f2ptr f2__timeline__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__new(cause, name, semantic_realm);
}
export_cefunk2(timeline__new, name, semantic_realm, 0, "Returns a new timeline object.");


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
  return raw__semantic_knowledge_base__add_semantic_frame(cause, this, timeline_event);
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
  raw__set__add(cause, timeline_event_set, timeline_event);
  return raw__semantic_knowledge_base__remove_semantic_frame(cause, this, timeline_event);
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
  f2ptr timeline_events    = raw__set__elements(cause, timeline_event_set);
  return timeline_events;
}

f2ptr f2__timeline__timeline_events(f2ptr cause, f2ptr this) {
  if (! raw__timeline__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__timeline_events(cause, this);
}
export_cefunk1(timeline__timeline_events, this, 0, "Returns a new list of the timeline_events contained within this timeline.");


f2ptr raw__timeline_event_extents__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr minimum_width, f2ptr minimum_height) {
  return f2__frame__new(cause, f2list12__new(cause,
					     new__symbol(cause, "x"),              x,
					     new__symbol(cause, "y"),              y,
					     new__symbol(cause, "width"),          width,
					     new__symbol(cause, "height"),         height,
					     new__symbol(cause, "minimum_width"),  minimum_width,
					     new__symbol(cause, "minimum_height"), minimum_height));
}

f2ptr raw__timeline_event_extents__x(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"), nil);
}

f2ptr raw__timeline_event_extents__x__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "x"), value);
}

f2ptr raw__timeline_event_extents__y(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"), nil);
}

f2ptr raw__timeline_event_extents__y__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "y"), value);
}

f2ptr raw__timeline_event_extents__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr raw__timeline_event_extents__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr raw__timeline_event_extents__height(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil);
}

f2ptr raw__timeline_event_extents__height__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "height"), value);
}

f2ptr raw__timeline_event_extents__minimum_width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "minimum_width"), nil);
}

f2ptr raw__timeline_event_extents__minimum_width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "minimum_width"), value);
}

f2ptr raw__timeline_event_extents__minimum_height(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "minimum_height"), nil);
}

f2ptr raw__timeline_event_extents__minimum_height__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "minimum_height"), value);
}

void raw__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
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
		f2ptr next_set = raw__semantic_temporal_object__next__lookup(cause, expand_event);
		if (next_set != nil) {
		  set__iteration(cause, next_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr previous_set = raw__semantic_temporal_object__previous__lookup(cause, expand_event);
		if (previous_set != nil) {
		  set__iteration(cause, previous_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr contains_set = raw__semantic_temporal_object__contains__lookup(cause, expand_event);
		if (contains_set != nil) {
		  set__iteration(cause, contains_set, expansion_event,
				 if (! raw__set__contains(cause, connected_set, expansion_event)) {
				   raw__set__add(cause, expansion_event_set, expansion_event);
				 }
				 );
		}
	      }
	      {
		f2ptr is_contained_by_set = raw__semantic_temporal_object__is_contained_by__lookup(cause, expand_event);
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
	f2ptr extents_event_hash = f2__ptypehash__new(cause);
	set__iteration(cause, connected_set, event,
		       double minimum_width__d  = raw__timeline_event__cairo_minimum_width( cause, event, cairo_context);
		       double minimum_height__d = raw__timeline_event__cairo_minimum_height(cause, event, cairo_context);
		       raw__ptypehash__add(cause, extents_event_hash, event, raw__timeline_event_extents__new(cause, nil, nil, nil, nil,
													      f2double__new(cause, minimum_width__d),
													      f2double__new(cause, minimum_height__d)));
		       );
	// calculate width and height
	{
	  f2ptr expansion_set = connected_set;
	  while (! raw__set__is_empty(cause, expansion_set)) {
	    f2ptr next_expansion_set = f2__set__new(cause);
	    set__iteration(cause, expansion_set, event,
			   f2ptr     contains_set           = raw__semantic_temporal_object__contains__lookup(cause, event);
			   boolean_t not_enough_information = boolean__false;
			   double    width__d  = 0;
			   double    height__d = 0;
			   if (contains_set != nil) {
			     double maximum_path_width = 0;
			     {
			       f2ptr search_forward_path_event_hash  = f2__ptypehash__new(cause);
			       f2ptr search_backward_path_event_hash = f2__ptypehash__new(cause);
			       set__iteration(cause, contains_set, contains_event,
					      f2ptr search_forward_set = f2__set__new(cause);
					      raw__set__add(cause, search_forward_set, contains_event);
					      while (! raw__set__is_empty(cause, search_forward_set)) {
						f2ptr search_forward_event = raw__set__an_arbitrary_element(cause, search_forward_set);
						{
						  f2ptr search_forward_event__extents = raw__ptypehash__lookup(cause, extents_event_hash, search_forward_event);
						  f2ptr search_forward_event__width   = raw__timeline_event_extents__width( cause, search_forward_event__extents);
						  if (search_forward_event__width  != nil) {
						    double search_forward_event__width__d  = f2double__d(search_forward_event__width,  cause);
						    path__width__d += search_forward_event__width__d;
						    f2ptr next_set = raw__semantic_temporal_object__next__lookup(cause, contains_event);
						    
						  } else {
						    not_enough_information = boolean__true;
						    // could break iteration to run faster
						  }
						  
						}
						raw__set__remove(cause, search_forward_set, next_event);
					      }
					      );
			     }
			     set__iteration(cause, contains_set, contains_event,
					    f2ptr contains_event__extents = raw__ptypehash__lookup(cause, extents_event_hash, contains_event);
					    f2ptr contains_event__width   = raw__timeline_event_extents__width( cause, contains_event__extents);
					    f2ptr contains_event__height  = raw__timeline_event_extents__height(cause, contains_event__extents);
					    if ((contains_event__width  != nil) &&
						(contains_event__height != nil)) {
					      double contains_event__width__d  = f2double__d(contains_event__width,  cause);
					      double contains_event__height__d = f2double__d(contains_event__height, cause);
					      width__d  += contains_event__width__d;
					      height__d += contains_event__height__d;
					    } else {
					      not_enough_information = boolean__true;
					      // could break iteration to run faster
					    }
					    );
			   }
			   if (not_enough_information) {
			     raw__set__add(cause, next_expansion_set, event);
			   } else {
			     f2ptr  extents           = raw__ptypehash__lookup(cause, extents_event_hash, event);
			     f2ptr  minimum_width     = raw__timeline_event_extents__minimum_width( cause, extents);
			     f2ptr  minimum_height    = raw__timeline_event_extents__minimum_height(cause, extents);
			     double minimum_width__d  = f2double__d(minimum_width,  cause);
			     double minimum_height__d = f2double__d(minimum_height, cause);
			     if (width__d < minimum_width__d) {
			       width__d = minimum_width__d;
			     }
			     if (height__d < minimum_height__d) {
			       height__d = minimum_height__d;
			     }
			     f2ptr width  = f2double__new(cause, width__d);  raw__timeline_event_extents__width__set( cause, extents, width);
			     f2ptr height = f2double__new(cause, height__d); raw__timeline_event_extents__height__set(cause, extents, height);
			   }
			   );
	    expansion_set = next_expansion_set;
	  }
	}
	set__iteration(cause, connected_set, event,
		       f2ptr extents = raw__ptypehash__lookup(cause, extents_event_hash, event);
		       raw__cairo_context__save(         cause, cairo_context);
		       raw__cairo_context__scale(        cause, cairo_context, (1.0 / 64.0), (1.0 / 64.0));
		       raw__cairo_context__translate(    cause, cairo_context, 4, 4 + y_position);
		       raw__timeline_event__cairo_render(cause, event, cairo_context);
		       raw__cairo_context__restore(      cause, cairo_context);
		       y_position += 2.0;
		       );
	y_position += 1.0;
      }
      connected_set_iter = f2cons__cdr(connected_set_iter, cause);
    }
  }
  raw__cairo_context__restore(cause, cairo_context);
}

f2ptr f2__timeline__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  if ((! raw__timeline__is_type(cause, this)) ||
      (! raw__cairo_context__is_type(cause, cairo_context))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline__cairo_render(cause, this, cairo_context);
  return nil;
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
  f2__primobject_type__parents__set(cause, this, f2list1__new(cause, new__symbol(cause, "semantic_knowledge_base")));
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
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_knowledge_base"), new__symbol(cause, "semantic_knowledge_base__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
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


