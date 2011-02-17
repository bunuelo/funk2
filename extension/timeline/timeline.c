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


void raw__cairo_context__render_box(f2ptr cause,
				    f2ptr cairo_context,
				    double x0,
				    double y0,
				    double dx,
				    double dy,
				    double foreground_red,
				    double foreground_green,
				    double foreground_blue,
				    double foreground_alpha,
				    double background_red,
				    double background_green,
				    double background_blue,
				    double background_alpha) {
  raw__cairo_context__set_source_rgba(cause, cairo_context, background_red, background_green, background_blue, background_alpha);
  raw__cairo_context__move_to(        cause, cairo_context,  x0,  y0);
  raw__cairo_context__rel_line_to(    cause, cairo_context,  dx,   0);
  raw__cairo_context__rel_line_to(    cause, cairo_context,   0,  dy);
  raw__cairo_context__rel_line_to(    cause, cairo_context, -dx,   0);
  raw__cairo_context__rel_line_to(    cause, cairo_context,   0, -dy);
  raw__cairo_context__fill_preserve(  cause, cairo_context);
  raw__cairo_context__set_source_rgba(cause, cairo_context, foreground_red, foreground_green, foreground_blue, foreground_alpha);
  raw__cairo_context__stroke(         cause, cairo_context);
}

void raw__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__set_line_width(cause, cairo_context, 0.001);
  
  // box
  raw__cairo_context__render_box(     cause, cairo_context, 0, 0,  4, 2,  0, 0, 0, 1,  0.5, 0.875, 1.0, 1);
  
  // text
  raw__cairo_context__set_source_rgba(cause, cairo_context, 0, 0, 0, 1);
  raw__cairo_context__move_to(        cause, cairo_context, 0.5, 0.5 + 0.75);
  raw__cairo_context__set_font_size(  cause, cairo_context, 1.0);
  raw__cairo_context__text_path(      cause, cairo_context, "Event");
  raw__cairo_context__fill(           cause, cairo_context);
  
  raw__cairo_context__restore(        cause, cairo_context);
}

f2ptr f2__timeline_event__cairo_render(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  if ((! raw__timeline_event__is_type(cause, this)) ||
      (! raw__cairo_context__is_type(cause, cairo_context))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__timeline_event__cairo_render(cause, this, cairo_context);
  return nil;
}
export_cefunk2(timeline_event__cairo_render, this, cairo_context, 0, "Renders this timeline_event in the given cairo_context.");


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
  f2__primobject_type__parents__set(cause, this, f2list1__new(cause, new__symbol(cause, "semantic_knowledge_base")));
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
  {
    s64   timeline_event_index = 0;
    f2ptr timeline_event_set   = raw__timeline__timeline_event_set(cause, this);
    set__iteration(cause, timeline_event_set, timeline_event,
		   raw__cairo_context__save(         cause, cairo_context);
		   raw__cairo_context__scale(        cause, cairo_context, (1.0 / 64.0), (1.0 / 64.0));
		   raw__cairo_context__translate(    cause, cairo_context, 4 + timeline_event_index, 4 + timeline_event_index);
		   raw__timeline_event__cairo_render(cause, timeline_event, cairo_context);
		   raw__cairo_context__restore(      cause, cairo_context);
		   timeline_event_index ++;
		   );
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


