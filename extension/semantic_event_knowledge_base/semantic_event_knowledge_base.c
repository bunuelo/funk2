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

#include "semantic_event_knowledge_base.h"


f2ptr raw__semantic_event_knowledge_base__know_of_remove__before_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_event__is_type(cause, semantic_frame)) {
    f2ptr semantic_event = semantic_frame;
    if (raw__eq(cause, new__symbol(cause, "property"), key_type) && (raw__eq(cause, new__symbol(cause, "absolute_start_time"), key) ||
								     raw__eq(cause, new__symbol(cause, "absolute_end_time"),   key))) {
      f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
      f2ptr contains_event      = assert_value(f2__semantic_event_tree__contains(cause, semantic_event_tree, semantic_event));
      if (contains_event != nil) {
	assert_value(f2__semantic_event_tree__remove(cause, semantic_event_tree, semantic_event));
      }
    }
  }
  return nil;
}

f2ptr f2__semantic_event_knowledge_base__know_of_remove__before_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_frame,                semantic_frame);
  return raw__semantic_event_knowledge_base__know_of_remove__before_callback(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_event_knowledge_base__know_of_remove__before_callback, this, semantic_frame, key_type, key, value, 0, "Callback for semantic_event_knowledge_base to update internal semantic_event_tree.");


f2ptr raw__semantic_event_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_event__is_type(cause, semantic_frame)) {
    f2ptr semantic_event = semantic_frame;
    if (raw__eq(cause, new__symbol(cause, "property"), key_type) && (raw__eq(cause, new__symbol(cause, "absolute_start_time"), key) ||
								     raw__eq(cause, new__symbol(cause, "absolute_end_time"),   key))) {
      f2ptr semantic_event_tree    = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
      f2ptr already_contains_event = assert_value(f2__semantic_event_tree__contains(cause, semantic_event_tree, semantic_event));
      if (already_contains_event == nil) {
	assert_value(f2__semantic_event_tree__insert(cause, semantic_event_tree, semantic_event));
      }
    }
  }
  return nil;
}

f2ptr f2__semantic_event_knowledge_base__know_of_add__after_callback(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_frame,                semantic_frame);
  return raw__semantic_event_knowledge_base__know_of_add__after_callback(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_event_knowledge_base__know_of_add__after_callback, this, semantic_frame, key_type, key, value, 0, "Callback for semantic_event_knowledge_base to update internal semantic_event_tree.");


// semantic_event_knowledge_base

f2ptr raw__semantic_event_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_event_knowledge_base"));
  }
  assert_value(raw__meta_semantic_knowledge_base__type_create(cause, this, name, semantic_realm));
  f2ptr semantic_event_tree = f2__semantic_event_tree__new(cause);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_event_tree"), semantic_event_tree);
  assert_value(raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(cause, this, f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__know_of_remove__before_callback"))));
  assert_value(raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(    cause, this, f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__know_of_add__after_callback"))));
  return this;
}

f2ptr raw__semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_event_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__semantic_event_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_event_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_event_knowledge_base__new, name, semantic_realm, 0, "Given a name and a semantic_realm, returns a new semantic_event_knowledge_base object.");


boolean_t raw__semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_event_knowledge_base");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__semantic_event_knowledge_base__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_event_knowledge_base__is_type(cause, thing));
}
export_cefunk1(semantic_event_knowledge_base__is_type, thing, 0, "Returns whether or not thing is of type semantic_event_knowledge_base.");


f2ptr raw__semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_event_knowledge_base__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event_knowledge_base, this);
  return raw__semantic_event_knowledge_base__type(cause, this);
}
export_cefunk1(semantic_event_knowledge_base__type, thing, 0, "Returns the specific type of object that this semantic_event_knowledge_base is.");


f2ptr raw__semantic_event_knowledge_base__semantic_event_tree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_event_tree"), nil);
}

f2ptr f2__semantic_event_knowledge_base__semantic_event_tree(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event_knowledge_base, this);
  return raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
}
export_cefunk1(semantic_event_knowledge_base__semantic_event_tree, thing, 0, "Returns this semantic_event_knowledge_base's semantic_event_tree.");


f2ptr raw__semantic_event_knowledge_base__events_containing_time(f2ptr cause, f2ptr this, f2ptr semantic_time) {
  f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
  return assert_value(f2__semantic_event_tree__events_containing_time(cause, semantic_event_tree, semantic_time));
}

f2ptr f2__semantic_event_knowledge_base__events_containing_time(f2ptr cause, f2ptr this, f2ptr semantic_time) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_time,                 semantic_time);
  return raw__semantic_event_knowledge_base__events_containing_time(cause, this, semantic_time);
}
export_cefunk2(semantic_event_knowledge_base__events_containing_time, this, semantic_time, 0,
	       "Returns the semantic_events from this semantic_event_knowledge_base that contain the given time.");


f2ptr raw__semantic_event_knowledge_base__events_overlapping_range(f2ptr cause, f2ptr this, f2ptr semantic_left_time, f2ptr semantic_right_time) {
  f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
  return assert_value(f2__semantic_event_tree__events_overlapping_range(cause, semantic_event_tree, semantic_left_time, semantic_right_time));
}

f2ptr f2__semantic_event_knowledge_base__events_overlapping_range(f2ptr cause, f2ptr this, f2ptr semantic_left_time, f2ptr semantic_right_time) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_time,                 semantic_left_time);
  assert_argument_type(semantic_time,                 semantic_right_time);
  return raw__semantic_event_knowledge_base__events_overlapping_range(cause, this, semantic_left_time, semantic_right_time);
}
export_cefunk3(semantic_event_knowledge_base__events_overlapping_range, this, semantic_left_time, semantic_right_time, 0,
	       "Returns a new set of events in this semantic_event_knowledge_base that overlap the given range specified by semantic_left_time and semantic_right_time.");


f2ptr raw__semantic_event_knowledge_base__events_overlapping_event(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
  return assert_value(f2__semantic_event_tree__events_overlapping_event(cause, semantic_event_tree, semantic_event));
}

f2ptr f2__semantic_event_knowledge_base__events_overlapping_event(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_event,      semantic_event);
  return raw__semantic_event_knowledge_base__events_overlapping_event(cause, this, semantic_event);
}
export_cefunk2(semantic_event_knowledge_base__events_overlapping_event, this, semantic_event, 0,
	       "Returns a new set of events in this semantic_event_knowledge_base that overlap the given event.");


f2ptr raw__semantic_event_knowledge_base__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time) {
  f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
  return assert_value(f2__semantic_event_tree__most_recent_filtered_events(cause, semantic_event_tree, filter_funk, user_filter_data, semantic_time));
}

f2ptr f2__semantic_event_knowledge_base__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(funkable,                      filter_funk);
  assert_argument_type(semantic_time,                 semantic_time);
  return raw__semantic_event_knowledge_base__most_recent_filtered_events(cause, this, filter_funk, user_filter_data, semantic_time);
}
export_cefunk4(semantic_event_knowledge_base__most_recent_filtered_events, this, filter_funk, user_filter_data, semantic_time, 0,
	       "Returns the most recent semantic_events that occur at or before the given semantic_time and also for which the filter_funk returns true.");


f2ptr raw__semantic_event_knowledge_base__event_transframe(f2ptr cause, f2ptr this, f2ptr start_semantic_time, f2ptr end_semantic_time) {
  f2ptr semantic_realm            = assert_value(f2__semantic_knowledge_base__semantic_realm(cause, this));
  f2ptr semantic_event_transframe = assert_value(f2__semantic_event_transframe__new(cause, semantic_realm));
  {
    f2ptr start_events    = assert_value(raw__semantic_event_knowledge_base__events_containing_time(cause, this, start_semantic_time));
    f2ptr start_event_set = f2__set__new(cause, nil);
    {
      f2ptr iter = start_events;
      while (iter != nil) {
	f2ptr event = f2__cons__car(cause, iter);
	raw__set__add(cause, start_event_set, event);
	iter = f2__cons__cdr(cause, iter);
      }
    }
    f2ptr end_events    = assert_value(raw__semantic_event_knowledge_base__events_containing_time(cause, this, end_semantic_time));
    f2ptr end_event_set = f2__set__new(cause, nil);
    {
      f2ptr iter = end_events;
      while (iter != nil) {
	f2ptr event = f2__cons__car(cause, iter);
	raw__set__add(cause, end_event_set, event);
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = start_events;
      while (iter != nil) {
	f2ptr start_event = f2__cons__car(cause, iter);
	if (! raw__set__contains(cause, end_event_set, start_event)) {
	  assert_value(raw__semantic_event_transframe__remove__add(cause, semantic_event_transframe, start_event));
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = end_events;
      while (iter != nil) {
	f2ptr end_event = f2__cons__car(cause, iter);
	if (! raw__set__contains(cause, start_event_set, end_event)) {
	  assert_value(raw__semantic_event_transframe__add__add(cause, semantic_event_transframe, end_event));
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return semantic_event_transframe;
}

f2ptr f2__semantic_event_knowledge_base__event_transframe(f2ptr cause, f2ptr this, f2ptr start_semantic_time, f2ptr end_semantic_time) {
  assert_argument_type(semantic_event_knowledge_base, this);
  assert_argument_type(semantic_time,                 start_semantic_time);
  assert_argument_type(semantic_time,                 end_semantic_time);
  return raw__semantic_event_knowledge_base__event_transframe(cause, this, start_semantic_time, end_semantic_time);
}
export_cefunk3(semantic_event_knowledge_base__event_transframe, this, start_semantic_time, end_semantic_time, 0,
	       "Returns a new semantic_event_transframe derived from this semantic_event_knowledge_base that represents the change in events between start_semantic_time and end_semantic_time.");

f2ptr raw__semantic_event_knowledge_base__events(f2ptr cause, f2ptr this) {
  f2ptr semantic_event_tree = raw__semantic_event_knowledge_base__semantic_event_tree(cause, this);
  return raw__semantic_event_tree__events(cause, semantic_event_tree);
}

f2ptr f2__semantic_event_knowledge_base__events(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event_knowledge_base, this);
  return raw__semantic_event_knowledge_base__events(cause, this);
}
export_cefunk1(semantic_event_knowledge_base__events, this, 0,
	       "Returns all events within this semantic_event_knowledge_base.");



f2ptr f2__semantic_event_knowledge_base_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "meta_semantic_knowledge_base")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "semantic_event_tree"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__semantic_event_tree")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events_containing_time"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__events_containing_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events_overlapping_range"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__events_overlapping_range")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events_overlapping_event"),    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__events_overlapping_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "most_recent_filtered_events"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__most_recent_filtered_events")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "event_transframe"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__event_transframe")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_knowledge_base"), new__symbol(cause, "semantic_event_knowledge_base__events")));}
  return this;
}



// **

f2ptr f2__semantic_event_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__ping, 0, "");


f2ptr f2__semantic_event_knowledge_base__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_event_knowledge_base, meta_semantic_knowledge_base);
  core_extension__ping(semantic_event_knowledge_base, semantic_event);
  core_extension__ping(semantic_event_knowledge_base, semantic_event_tree);
  core_extension__ping(semantic_event_knowledge_base, semantic_event_transframe);
  f2__add_type(cause, new__symbol(cause, "semantic_event_knowledge_base"), f2__semantic_event_knowledge_base_type__new(cause));
  status("semantic_event_knowledge_base initialized.");
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__initialize, 0, "");


f2ptr f2__semantic_event_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_event_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_event_knowledge_base__core_extension__destroy, 0, "");


