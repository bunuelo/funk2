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

#include "semantic_causal_event.h"


// semantic_causal_event

f2ptr raw__semantic_causal_event__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr action_name) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_causal_event"));
  }
  {
    f2ptr result = raw__semantic_event__type_create(cause, this, semantic_realm, action_name);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__semantic_causal_object__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr raw__semantic_causal_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  f2ptr this = f2__frame__new(cause, nil);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  {
    f2ptr result = raw__semantic_causal_event__type_create(cause, this, semantic_realm, action_name);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}

f2ptr f2__semantic_causal_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
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
  if (! raw__semantic_causal_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__type(cause, this);
}
export_cefunk1(semantic_causal_event__type, thing, 0, "Returns the specific type of object that this semantic_causal_event is.");



f2ptr raw__semantic_causal_event__causes__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_causal_event__causal__causes__lookup(cause, this, new__symbol(cause, "event"));
}

f2ptr f2__semantic_causal_event__causes__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_causal_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__causes__lookup(cause, this);
}
export_cefunk1(semantic_causal_event__causes__lookup, this, 0, "Returns the set of causal_events that cause this causal_event, returns nil if no such set exists.");


f2ptr raw__semantic_causal_event__causes__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_event__causal__causes__add(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__causes__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  if ((! raw__semantic_causal_event__is_type(cause, this)) ||
      (! raw__semantic_causal_event__is_type(cause, causal_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__causes__add(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__causes__add, this, causal_object, 0, "Adds the given causal_event to the causes of this causal_event.");


f2ptr raw__semantic_causal_event__causes__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_event__causal__causes__remove(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__causes__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  if ((! raw__semantic_causal_event__is_type(cause, this)) ||
      (! raw__semantic_causal_event__is_type(cause, causal_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__causes__remove(cause, this, causal_object);
}
export_cefunk2(semantic_causal_event__causes__remove, this, causal_object, 0, "Removes the given causal_event from the set of causes for this causal_event.");


f2ptr raw__semantic_causal_event__is_caused_by__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_causal_event__causal__is_caused_by__lookup(cause, this, new__symbol(cause, "event"));
}

f2ptr f2__semantic_causal_event__is_caused_by__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_causal_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__is_caused_by__lookup(cause, this);
}
export_cefunk1(semantic_causal_event__is_caused_by__lookup, this, 0, "Returns the set of causal_events that have caused this causal_event, returns nil if no such set exists.");


f2ptr raw__semantic_causal_event__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_event__causal__is_caused_by__add(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__is_caused_by__add(f2ptr cause, f2ptr this, f2ptr causal_event) {
  if ((! raw__semantic_causal_event__is_type(cause, this)) ||
      (! raw__semantic_causal_event__is_type(cause, causal_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__is_caused_by__add(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__is_caused_by__add, this, causal_event, 0, "Adds the given causal_event to the set of objects that have caused this causal_event.");


f2ptr raw__semantic_causal_event__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  return raw__semantic_causal_event__causal__is_caused_by__remove(cause, this, new__symbol(cause, "event"), causal_event);
}

f2ptr f2__semantic_causal_event__is_caused_by__remove(f2ptr cause, f2ptr this, f2ptr causal_event) {
  if ((! raw__semantic_causal_event__is_type(cause, this)) ||
      (! raw__semantic_causal_event__is_type(cause, causal_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_causal_event__is_caused_by__remove(cause, this, causal_event);
}
export_cefunk2(semantic_causal_event__is_caused_by__remove, this, causal_event, 0, "Removes the given causal_event from the set of causal_events that have caused this causal_event.");


f2ptr f2__semantic_causal_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list2__new(cause,
							    new__symbol(cause, "semantic_event"),
							    new__symbol(cause, "semantic_causal_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "new"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "is_type"),      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),             new__symbol(cause, "type"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup"), new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "causes"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__causes__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup"), new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "is_caused_by"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_event"), new__symbol(cause, "semantic_causal_event__is_caused_by__remove")));}
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
	      f2ptr render_frame        = f2__object__get(cause, semantic_event, new__symbol(cause, "cairo_render_frame"), nil);
	      f2ptr absolute_start_time = f2__object__semantic__get(cause, semantic_event, new__symbol(cause, "absolute_start_time"), nil);
	      if (raw__larva__is_type(cause, absolute_start_time)) {
		return absolute_start_time;
	      }
	      f2ptr absolute_end_time = f2__object__semantic__get(cause, semantic_event, new__symbol(cause, "absolute_end_time"),   nil);
	      if (raw__larva__is_type(cause, absolute_end_time)) {
		return absolute_end_time;
	      }
	      f2ptr timeline_event = f2__timeline_event__new(cause, render_frame, absolute_start_time, absolute_end_time);
	      if (raw__larva__is_type(cause, timeline_event)) {
		return timeline_event;
	      }
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
			   f2ptr next_set = f2__object__semantic__lookup(cause, semantic_event, new__symbol(cause, "next"), nil);
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
			   f2ptr contains_set = f2__object__semantic__lookup(cause, semantic_event, new__symbol(cause, "contains"), nil);
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
			   
			   f2ptr causes_set = f2__object__semantic__lookup(cause, semantic_event, new__symbol(cause, "causes"), nil);
			   if (causes_set != nil) {
			     set__iteration(cause, causes_set, causes_semantic_event,
					    if (raw__ptypehash__contains(cause, timeline_event_semantic_event_hash, causes_semantic_event)) {
					      f2ptr causes_timeline_event = raw__ptypehash__lookup(cause, timeline_event_semantic_event_hash, causes_semantic_event);
					      raw__timeline_event__add_causes(cause, timeline_event, causes_timeline_event);
					    }
					    );
			   }
			 }
			 );
  }
  return timeline;
}

f2ptr f2__semantic_knowledge_base__as__timeline(f2ptr cause, f2ptr this) {
  if (! raw__semantic_knowledge_base__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
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
    {
      f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__core_extension__ping")), nil);
      if (raw__larva__is_type(cause, result)) {
	status("semantic_causal_event: failed to ping semantic_event.");
	return result;
      }
    }
    {
      f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_causal_object"), new__symbol(cause, "semantic_causal_object__core_extension__ping")), nil);
      if (raw__larva__is_type(cause, result)) {
	status("semantic_causal_event: failed to ping semantic_causal_object.");
	return result;
      }
    }
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


