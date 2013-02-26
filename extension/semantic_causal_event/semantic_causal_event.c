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

#include "semantic_causal_event.h"


// semantic_causal_event

f2ptr raw__semantic_causal_event__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr action_name) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_causal_event"));
  }
  assert_value(raw__semantic_event__type_create(cause, this, semantic_realm, action_name));
  assert_value(raw__semantic_causal_object__type_create(cause, this, semantic_realm));
  return this;
}

f2ptr raw__semantic_causal_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_causal_event__type_create(cause, this, semantic_realm, action_name));
  return this;
}

f2ptr f2__semantic_causal_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_causal_event__new(cause, semantic_realm, action_name);
}
export_cefunk2(semantic_causal_event__new, semantic_realm, action_name, 0, "Returns a new semantic_causal_event object.");


boolean_t raw__semantic_causal_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_causal_event");
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

f2ptr f2__semantic_causal_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_causal_event__is_type(cause, thing));
}
export_cefunk1(semantic_causal_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_causal_event.");


f2ptr raw__semantic_causal_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_causal_event__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_causal_event, this);
  return raw__semantic_causal_event__type(cause, this);
}
export_cefunk1(semantic_causal_event__type, thing, 0, "Returns the specific type of object that this semantic_causal_event is.");



f2ptr raw__semantic_causal_event__causes__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_causal_object__causal__causes__lookup_set(cause, this, new__symbol(cause, "event"));
}

f2ptr f2__semantic_causal_event__causes__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_causal_event, this);
  return raw__semantic_causal_event__causes__lookup_set(cause, this);
}
export_cefunk1(semantic_causal_event__causes__lookup_set, this, 0, "Returns the set of causal_events that cause this causal_event, returns nil if no such set exists.");


f2ptr raw__semantic_causal_event__causes__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  printf("\nraw__semantic_causal_event__causes__add: here."); fflush(stdout);
  return raw__semantic_causal_object__causal__causes__add(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__causes__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  assert_argument_type(semantic_causal_event, this);
  assert_argument_type(semantic_causal_event, causal_event);
  return raw__semantic_causal_event__causes__add(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__causes__add, this, causal_object, 0, "Adds the given causal_event to the causes of this causal_event.");


f2ptr raw__semantic_causal_event__causes__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_object__causal__causes__remove(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__causes__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  assert_argument_type(semantic_causal_event, this);
  assert_argument_type(semantic_causal_event, causal_event);
  return raw__semantic_causal_event__causes__remove(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__causes__remove, this, causal_event, 0, "Removes the given causal_event from the set of causes for this causal_event.");


f2ptr raw__semantic_causal_event__is_caused_by__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_causal_object__causal__is_caused_by__lookup_set(cause, this, new__symbol(cause, "event"));
}

f2ptr f2__semantic_causal_event__is_caused_by__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_causal_event, this);
  return raw__semantic_causal_event__is_caused_by__lookup_set(cause, this);
}
export_cefunk1(semantic_causal_event__is_caused_by__lookup_set, this, 0, "Returns the set of causal_events that have caused this causal_event, returns nil if no such set exists.");


f2ptr raw__semantic_causal_event__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_object__causal__is_caused_by__add(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  assert_argument_type(semantic_causal_event, this);
  assert_argument_type(semantic_causal_event, causal_event);
  return raw__semantic_causal_event__is_caused_by__add(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__is_caused_by__add, this, causal_event, 0, "Adds the given causal_event to the set of objects that have caused this causal_event.");


f2ptr raw__semantic_causal_event__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_object__causal__is_caused_by__remove(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  assert_argument_type(semantic_causal_event, this);
  assert_argument_type(semantic_causal_event, causal_event);
  return raw__semantic_causal_event__is_caused_by__remove(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__is_caused_by__remove, this, causal_event, 0, "Removes the given causal_event from the set of causal_events that have caused this causal_event.");


f2ptr f2__semantic_causal_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list2__new(cause,
							    new__symbol(cause, "semantic_event"),
							    new__symbol(cause, "semantic_causal_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__remove")));}
  return this;
}




f2ptr raw__semantic_knowledge_base__as__timeline(f2ptr cause, f2ptr this) {
  f2ptr timeline = f2__timeline__new(cause);
  {
    f2ptr semantic_frames                    = raw__semantic_knowledge_base__semantic_frames(cause, this);
    f2ptr timeline_event_semantic_event_hash = f2__ptypehash__new(cause);
    {
      f2ptr iter = semantic_frames;
      while (iter != nil) {
	f2ptr semantic_frame = f2cons__car(iter, cause);
	{
	  if (raw__semantic_event__is_type(cause, semantic_frame)) {
	    f2ptr semantic_event = semantic_frame;
	    {
	      f2ptr render_frame               = f2__object__get(cause, semantic_event, new__symbol(cause, "cairo_render_frame"), nil);
	      f2ptr absolute_start_time        = assert_value(f2__semantic_event__absolute_start_time(cause, semantic_event));
	      f2ptr absolute_start_time__value = f2__semantic_time__value(cause, absolute_start_time);
	      if (! raw__time__is_type(cause, absolute_start_time__value)) {
		absolute_start_time__value = nil;
	      }
	      f2ptr absolute_end_time        = assert_value(f2__semantic_event__absolute_end_time(cause, semantic_event));
	      f2ptr absolute_end_time__value = f2__semantic_time__value(cause, absolute_end_time);
	      if (! raw__time__is_type(cause, absolute_end_time__value)) {
		absolute_end_time__value = nil;
	      }
	      f2ptr timeline_event = assert_value(f2__timeline_event__new(cause, render_frame, absolute_start_time__value, absolute_end_time__value));
	      raw__timeline__add_timeline_event(cause, timeline, timeline_event);
	      raw__ptypehash__add(cause, timeline_event_semantic_event_hash, semantic_event, timeline_event);
	    }
	  }
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
    ptypehash__iteration(cause, timeline_event_semantic_event_hash, semantic_event, timeline_event,
			 {
			   f2ptr next_set = f2__object__semantic__lookup_set(cause, semantic_event, new__symbol(cause, "next"), nil);
			   if (next_set != nil) {
			     set__iteration(cause, next_set, next_semantic_event,
					    if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, next_semantic_event)) {
					      f2ptr next_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, next_semantic_event);
					      raw__timeline_event__add_next(cause, timeline_event, next_timeline_event);
					    }
					    );
			   }
			 }
			 {
			   f2ptr contains_set = f2__object__semantic__lookup_set(cause, semantic_event, new__symbol(cause, "contains"), nil);
			   if (contains_set != nil) {
			     set__iteration(cause, contains_set, contains_semantic_event,
					    if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, contains_semantic_event)) {
					      f2ptr contains_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, contains_semantic_event);
					      raw__timeline_event__add_contains(cause, timeline_event, contains_timeline_event);
					    }
					    );
			   }
			 }
			 if (raw__semantic_causal_event__is_type(cause, semantic_event)) {
			   f2ptr semantic_causal_event = semantic_event;
			   
			   f2ptr causes_set = assert_value(f2__object__semantic__lookup_set(cause, semantic_causal_event, new__symbol(cause, "causes"), nil));
			   if (causes_set != nil) {
			     set__iteration(cause, causes_set, causes_semantic_event,
					    if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, causes_semantic_event)) {
					      f2ptr causes_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, causes_semantic_event);
					      raw__timeline_event__add_causes(cause, timeline_event, causes_timeline_event);
					    }
					    );
			   }
			 }
			 // if event has no start or end times, try to use parent info to place correctly.
			 if ((raw__timeline_event__start_time(cause, timeline_event) == nil) &&
			     (raw__timeline_event__end_time(  cause, timeline_event) == nil)) {
			   s64 nanoseconds__example_count = 0;
			   s64 nanoseconds__sum = 0;
			   {
			     f2ptr is_contained_by_set = f2__object__semantic__lookup_set(cause, semantic_event, new__symbol(cause, "is_contained_by"), nil);
			     if (is_contained_by_set != nil) {
			       set__iteration(cause, is_contained_by_set, is_contained_by_semantic_event,
					      if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, is_contained_by_semantic_event)) {
						f2ptr is_contained_by_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, is_contained_by_semantic_event);
						f2ptr is_contained_by_timeline_event__start_time = raw__timeline_event__start_time(cause, is_contained_by_timeline_event);
						f2ptr is_contained_by_timeline_event__end_time   = raw__timeline_event__end_time(cause, is_contained_by_timeline_event);
						if (is_contained_by_timeline_event__start_time != nil) {
						  nanoseconds__example_count ++;
						  nanoseconds__sum           += f2integer__i(f2time__nanoseconds_since_1970(is_contained_by_timeline_event__start_time, cause), cause);
						}
						if (is_contained_by_timeline_event__end_time != nil) {
						  nanoseconds__example_count ++;
						  nanoseconds__sum           += f2integer__i(f2time__nanoseconds_since_1970(is_contained_by_timeline_event__end_time, cause), cause);
						}
					      }
					      );
			     }
			   }
			   if (raw__semantic_causal_event__is_type(cause, semantic_event)) {
			     f2ptr semantic_causal_event = semantic_event;
			     
			     f2ptr is_caused_by_set = assert_value(f2__object__semantic__lookup_set(cause, semantic_causal_event, new__symbol(cause, "is_caused_by"), nil));
			     if (is_caused_by_set != nil) {
			       set__iteration(cause, is_caused_by_set, is_caused_by_semantic_event,
					      if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, is_caused_by_semantic_event)) {
						f2ptr is_caused_by_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, is_caused_by_semantic_event);
						
						f2ptr is_caused_by_timeline_event__start_time = raw__timeline_event__start_time(cause, is_caused_by_timeline_event);
						f2ptr is_caused_by_timeline_event__end_time   = raw__timeline_event__end_time(cause, is_caused_by_timeline_event);
						if (is_caused_by_timeline_event__start_time != nil) {
						  nanoseconds__example_count ++;
						  nanoseconds__sum           += f2integer__i(f2time__nanoseconds_since_1970(is_caused_by_timeline_event__start_time, cause), cause);
						}
						if (is_caused_by_timeline_event__end_time != nil) {
						  nanoseconds__example_count ++;
						  nanoseconds__sum           += f2integer__i(f2time__nanoseconds_since_1970(is_caused_by_timeline_event__end_time, cause), cause);
						}
					      }
					      );
			     }
			   }
			   if (nanoseconds__example_count != 0) {
			     s64 average_nanoseconds_since_1970 = nanoseconds__sum / nanoseconds__example_count;
			     raw__timeline_event__start_time__set(cause, timeline_event, f2__time__new(cause, f2integer__new(cause, average_nanoseconds_since_1970)));
			     raw__timeline_event__end_time__set(  cause, timeline_event, f2__time__new(cause, f2integer__new(cause, average_nanoseconds_since_1970 + 1)));
			   }
			 }
			 );
  }
  return timeline;
}

f2ptr f2__semantic_knowledge_base__as__timeline(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__as__timeline(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__timeline, this, 0, "Returns a new timeline object representing this semantic_knowledge_base.");



// **

f2ptr f2__semantic_causal_event__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_causal_event__core_extension__ping, 0, "");

boolean_t __semantic_causal_event__core_extension__is_initialized = boolean__false;
f2ptr f2__semantic_causal_event__core_extension__initialize(f2ptr cause) {
  if (! __semantic_causal_event__core_extension__is_initialized) {
    __semantic_causal_event__core_extension__is_initialized = boolean__true;
    core_extension__ping(semantic_causal_event, semantic_event);
    core_extension__ping(semantic_causal_event, semantic_causal_object);
    core_extension__ping(semantic_causal_event, timeline);
    status("semantic_causal_event initialized.");
  } else {
    status("semantic_causal_event already initialized.");
  }
  return nil;
}
export_cefunk0(semantic_causal_event__core_extension__initialize, 0, "");

f2ptr f2__semantic_causal_event__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_causal_event"), f2__semantic_causal_event_type__new(cause));
  status("semantic_causal_event initialized.");
  return nil;
}
export_cefunk0(semantic_causal_event__core_extension__define_types, 0, "");

f2ptr f2__semantic_causal_event__core_extension__destroy(f2ptr cause) {
  status("semantic_causal_event destroyed.");
  return nil;
}
export_cefunk0(semantic_causal_event__core_extension__destroy, 0, "");


