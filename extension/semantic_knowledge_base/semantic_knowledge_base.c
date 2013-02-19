// 
// Copyright (c) 2007-2013 Bo Morgan.
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

#include "semantic_knowledge_base.h"


// semantic_knowledge_base_event

f2ptr raw__semantic_knowledge_base_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame) {
  f2ptr this = f2__event_stream_event__new(cause, time);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),           new__symbol(cause, "semantic_knowledge_base_event"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "event_type"),     event_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
  return this;
}

f2ptr f2__semantic_knowledge_base_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame) {
  return raw__semantic_knowledge_base_event__new(cause, time, event_type, semantic_frame);
}
export_cefunk3(semantic_knowledge_base_event__new, time, event_type, semantic_frame, 0, "Returns a new semantic_knowledge_base_event object.");


boolean_t raw__semantic_knowledge_base_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_knowledge_base_event");
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

f2ptr f2__semantic_knowledge_base_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_knowledge_base_event__is_type(cause, thing));
}
export_cefunk1(semantic_knowledge_base_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_knowledge_base_event__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base_event, this);
  return raw__semantic_knowledge_base_event__type(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__type, thing, 0, "Returns the specific type of object that this semantic_knowledge_base_event is.");


f2ptr raw__semantic_knowledge_base_event__event_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "event_type"), nil);
}

f2ptr f2__semantic_knowledge_base_event__event_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base_event, this);
  return raw__semantic_knowledge_base_event__event_type(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__event_type, thing, 0, "Returns the event_type of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "event_type"), value);
}

f2ptr f2__semantic_knowledge_base_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_knowledge_base_event, this);
  return raw__semantic_knowledge_base_event__event_type__set(cause, this, value);
}
export_cefunk2(semantic_knowledge_base_event__event_type__set, thing, value, 0, "Sets the event_type of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frame"), nil);
}

f2ptr f2__semantic_knowledge_base_event__semantic_frame(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base_event, this);
  return raw__semantic_knowledge_base_event__semantic_frame(cause, this);
}
export_cefunk1(semantic_knowledge_base_event__semantic_frame, thing, 0, "Returns the semantic_frame of the semantic_knowledge_base_event.");


f2ptr raw__semantic_knowledge_base_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
}

f2ptr f2__semantic_knowledge_base_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  assert_argument_type(semantic_knowledge_base_event, this);
  return raw__semantic_knowledge_base_event__semantic_frame__set(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base_event__semantic_frame__set, thing, semantic_frame, 0, "Sets the semantic_frame of the semantic_knowledge_base_event.");


f2ptr f2__semantic_knowledge_base_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "event_stream_event")));
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "execute", "new",            "new");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "execute", "is_type",        "is_type");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "get",     "type",           "type");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "get",     "event_type",     "event_type");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "set",     "event_type",     "event_type__set");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "get",     "semantic_frame", "semantic_frame");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base_event", "set",     "semantic_frame", "semantic_frame__set");
  return this;
}




// semantic_knowledge_base

def_ceframe7(semantic_knowledge_base, semantic_knowledge_base,
	     name,
	     semantic_realm,
	     semantic_frame_set,
	     trace_event_stream,
	     trace_add_semantic_frame,
	     trace_remove_semantic_frame,
	     trace_callback_funks_frame);

f2ptr raw__semantic_knowledge_base__type_create_with_details(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_knowledge_base"));
  }
  f2ptr trace_callback_funks_frame = f2__frame__new(cause, nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "name"),                        name);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_realm"),              semantic_realm);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame_set"),          semantic_frame_set);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_event_stream"),          trace_event_stream);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_add_semantic_frame"),    trace_add_semantic_frame);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_remove_semantic_frame"), trace_remove_semantic_frame);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_callback_funks_frame"),  trace_callback_funks_frame);
  assert_value(f2__semantic_realm__add_semantic_knowledge_base(cause, semantic_realm, this));
  return this;
}

f2ptr raw__semantic_knowledge_base__type_create(f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_knowledge_base"));
  }
  f2ptr semantic_frame_set          = f2__set__new(cause, nil);
  f2ptr trace_event_stream          = f2__forgetful_event_stream__new(cause);
  f2ptr trace_add_semantic_frame    = nil;
  f2ptr trace_remove_semantic_frame = nil;
  if (cause != nil) {
    trace_add_semantic_frame    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_add_semantic_frame"));
    trace_remove_semantic_frame = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_knowledge_base-trace_remove_semantic_frame"));
  }
  assert_value(raw__semantic_knowledge_base__type_create_with_details(cause, this, name, semantic_realm, semantic_frame_set, trace_event_stream, trace_add_semantic_frame, trace_remove_semantic_frame));
  return this;
}

f2ptr raw__semantic_knowledge_base__new_with_details(f2ptr cause, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_knowledge_base__type_create_with_details(cause, this, name, semantic_realm, semantic_frame_set, trace_event_stream, trace_add_semantic_frame, trace_remove_semantic_frame));
  return this;
}

f2ptr raw__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_knowledge_base__type_create(cause, this, name, semantic_realm));
  return this;
}

f2ptr f2__semantic_knowledge_base__new(f2ptr cause, f2ptr name, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_knowledge_base__new(cause, name, semantic_realm);
}
export_cefunk2(semantic_knowledge_base__new, name, semantic_realm, 0, "Takes a name and a semantic_realm and returns a new semantic_knowledge_base object.");





f2ptr raw__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  f2ptr node_ptypehash     = f2__ptypehash__new(cause);
  f2ptr graph              = f2__graph__new(cause);
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  set__iteration(cause, semantic_frame_set, root_frame,
		 raw__frame__add_recursively_to_graph_with_ptypehash(cause, root_frame, graph, node_ptypehash);
		 );
  return graph;
}

f2ptr f2__semantic_knowledge_base__as__graph(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__as__graph(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__graph, this, 0, "Converts the semantic_knowledge_base to a graph.");


f2ptr raw__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  // tell the semantic frame that it belongs to this semantic_knowledge_base (so we can receive change events)
  raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(cause, semantic_frame, this);
  {
    // check for semantic_realm match.
    f2ptr semantic_realm                 = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr semantic_frame__semantic_realm = raw__semantic_frame__semantic_realm(cause, semantic_frame);
    if (! raw__eq(cause, semantic_frame__semantic_realm, semantic_realm)) {
      return f2larva__new(cause, 8924, f2__bug__new(cause, f2integer__new(cause, 8924), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),                               new__symbol(cause, "semantic_frame_semantic_realm_does_not_match_semantic_knowledge_base_semantic_realm"),
															   new__symbol(cause, "funk_name"),                              new__symbol(cause, "semantic_knowledge_base-add_semantic_frame"),
															   new__symbol(cause, "semantic_frame"),                         semantic_frame,
															   new__symbol(cause, "semantic_knowledge_base-semantic_realm"), semantic_realm))));
    }
  }
  semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			    assert_value(raw__semantic_knowledge_base__know_before_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value));
			    );
  // add the semantic frame to this knowledge base
  {
    f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    raw__set__add(cause, semantic_frame_set, semantic_frame);
  }
  // call trace callbacks
  if (raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this) != nil) {
    f2ptr trace_event_stream            = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "add_semantic_frame"), semantic_frame);
    raw__forgetful_event_stream__add(cause, trace_event_stream, semantic_knowledge_base_event);
    {
      f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
      f2ptr add_semantic_frame_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame"), nil);
      {
	f2ptr iter = add_semantic_frame_callbacks;
	while (iter != nil) {
	  f2ptr add_semantic_frame_callback = f2__cons__car(cause, iter);
	  {
	    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_callback, f2list2__new(cause, this, semantic_frame));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			    assert_value(raw__semantic_knowledge_base__know_after_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value));
			    f2ptr semantic_frame_event = raw__semantic_frame__add_event__new(cause, semantic_frame, key_type, key, value);
			    assert_value(raw__semantic_knowledge_base__add_trace_event(cause, this, semantic_frame_event));
			    );
  if (cause != nil) {
    raw__cause__increment_counters_if_exist(cause, cause, new__symbol(cause, "semantic_knowledge_base-semantic_frame"), 1);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  return raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__add_semantic_frame, this, semantic_frame, 0, "Adds a semantic_frame to this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__remove_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  if (! raw__set__contains(cause, semantic_frame_set, semantic_frame)) {
    return f2larva__new(cause, 8923, f2__bug__new(cause, f2integer__new(cause, 8923), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"),       new__symbol(cause, "tried_to_remove_semantic_frame_that_does_not_exist_in_knowledge_base"),
															 new__symbol(cause, "funk_name"),      new__symbol(cause, "semantic_knowledge_base-remove_semantic_frame"),
															 new__symbol(cause, "semantic_frame"), semantic_frame,
															 new__symbol(cause, "this"),           this))));
  }
  semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			    assert_value(raw__semantic_knowledge_base__know_before_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value));
			    );
  // tell the semantic frame that it does not belong to this semantic_knowledge_base anymore (so we do not continue to receive change events)
  raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(cause, semantic_frame, this);
  // remove the semantic frame from this knowledge base
  raw__set__remove(cause, semantic_frame_set, semantic_frame);
  // call trace callbacks
  if (raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this) != nil) {
    f2ptr trace_event_stream            = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr semantic_knowledge_base_event = raw__semantic_knowledge_base_event__new(cause, f2__time(cause), new__symbol(cause, "remove_semantic_frame"), semantic_frame);
    raw__forgetful_event_stream__add(cause, trace_event_stream, semantic_knowledge_base_event);
    {
      f2ptr trace_callback_funks_frame   = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
      f2ptr remove_semantic_frame_callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "remove_semantic_frame"), nil);
      {
	f2ptr iter = remove_semantic_frame_callbacks;
	while (iter != nil) {
	  f2ptr remove_semantic_frame_callback = f2__cons__car(cause, iter);
	  {
	    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), remove_semantic_frame_callback, f2list2__new(cause, this, semantic_frame));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
			    assert_value(raw__semantic_knowledge_base__know_after_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value));
			    f2ptr semantic_frame_event = raw__semantic_frame__remove_event__new(cause, semantic_frame, key_type, key, value);
			    assert_value(raw__semantic_knowledge_base__add_trace_event(cause, this, semantic_frame_event));
			    );
  if (cause != nil) {
    raw__cause__increment_counters_if_exist(cause, cause, new__symbol(cause, "semantic_knowledge_base-semantic_frame"), -1);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__remove_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  return raw__semantic_knowledge_base__remove_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__remove_semantic_frame, this, semantic_frame, 0, "Removes a semantic_frame from this semantic_knowledge_base.");


boolean_t raw__semantic_knowledge_base__contains_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  return raw__set__contains(cause, semantic_frame_set, semantic_frame);
}

f2ptr f2__semantic_knowledge_base__contains_semantic_frame(f2ptr cause, f2ptr this, f2ptr semantic_frame) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  return raw__semantic_knowledge_base__contains_semantic_frame(cause, this, semantic_frame);
}
export_cefunk2(semantic_knowledge_base__contains_semantic_frame, this, semantic_frame, 0, "Returns true if this semantic_knowledge_base contains the given semantic_frame.");


f2ptr raw__semantic_knowledge_base__remove_all(f2ptr cause, f2ptr this) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  f2ptr semantic_frames    = nil;
  set__iteration(cause, semantic_frame_set, semantic_frame,
		 semantic_frames = raw__cons__new(cause, semantic_frame, semantic_frames));
  {
    f2ptr iter = semantic_frames;
    while (iter != nil) {
      f2ptr semantic_frame = f2__cons__car(cause, iter);
      assert_value(raw__semantic_knowledge_base__remove_semantic_frame(cause, this, semantic_frame));
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__remove_all(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__remove_all(cause, this);
}
export_cefunk1(semantic_knowledge_base__remove_all, this, 0, "Removes all semantic_frames from this knowledge_base.");


f2ptr raw__semantic_knowledge_base__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base__semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, semantic_knowledge_base);
  set__iteration(cause, semantic_knowledge_base__semantic_frame_set, semantic_frame,
		 raw__semantic_knowledge_base__add_semantic_frame(cause, this, semantic_frame);
		 );
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_knowledge_base, semantic_knowledge_base);
  return raw__semantic_knowledge_base__add_semantic_knowledge_base(cause, this, semantic_knowledge_base);
}
export_cefunk2(semantic_knowledge_base__add_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Adds the semantic frames from semantic_knowledge_base to this semantic_knowledge_base.");


void raw__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  f2ptr trace_callback_funks_frame = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr trace_callback_funks       = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, trace_callback_name, nil);
  f2__frame__add_var_value(cause, trace_callback_funks_frame, trace_callback_name, raw__cons__new(cause, trace_callback_funk, trace_callback_funks));
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk(f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(funkable,                trace_callback_funk);
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, trace_callback_name, trace_callback_funk);
  return nil;
}
export_cefunk3(semantic_knowledge_base__add_trace_callback_funk, this, trace_callback_name, trace_callback_funk, 0, "Adds the trace_callback_funk to the trace_callback_funks_frame under the appropriate trace_callback_name.");


f2ptr raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk) {
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, new__symbol(cause, "add_semantic_frame_value-before"), funk);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(funkable,                funk);
  return raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before(cause, this, funk);
}
export_cefunk2(semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before, this, funk, 0, "Adds the funk to the trace_callback_funks_frame under the add_semantic_frame_value-before slot.");


f2ptr raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(f2ptr cause, f2ptr this, f2ptr funk) {
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, new__symbol(cause, "add_semantic_frame_value-after"), funk);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(f2ptr cause, f2ptr this, f2ptr funk) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(funkable,                funk);
  return raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after(cause, this, funk);
}
export_cefunk2(semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after, this, funk, 0, "Adds the funk to the trace_callback_funks_frame under the add_semantic_frame_value-after slot.");


f2ptr raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk) {
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, new__symbol(cause, "remove_semantic_frame_value-before"), funk);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(funkable,                funk);
  return raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(cause, this, funk);
}
export_cefunk2(semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before, this, funk, 0, "Adds the funk to the trace_callback_funks_frame under the remove_semantic_frame_value-before slot.");


f2ptr raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after(f2ptr cause, f2ptr this, f2ptr funk) {
  raw__semantic_knowledge_base__add_trace_callback_funk(cause, this, new__symbol(cause, "remove_semantic_frame_value-after"), funk);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after(f2ptr cause, f2ptr this, f2ptr funk) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(funkable,                funk);
  return raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after(cause, this, funk);
}
export_cefunk2(semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after, this, funk, 0, "Adds the funk to the trace_callback_funks_frame under the remove_semantic_frame_value-after slot.");


f2ptr raw__semantic_knowledge_base__add_trace_event(f2ptr cause, f2ptr this, f2ptr event) {
  f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
  raw__forgetful_event_stream__add(cause, trace_event_stream, event);
  return nil;
}

f2ptr f2__semantic_knowledge_base__add_trace_event(f2ptr cause, f2ptr this, f2ptr event) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(event_stream_event,      event);
  raw__semantic_knowledge_base__add_trace_event(cause, this, event);
  return nil;
}
export_cefunk2(semantic_knowledge_base__add_trace_event, this, event, 0, "Adds an event to this semantic_knowledge_base's trace event stream.");


f2ptr raw__semantic_knowledge_base__know_before_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame                  = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr add_semantic_frame_value__before__callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame_value-before"), nil);
  {
    f2ptr iter = add_semantic_frame_value__before__callbacks;
    while (iter != nil) {
      f2ptr add_semantic_frame_value__before__callback = f2__cons__car(cause, iter);
      assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_value__before__callback, f2list5__new(cause, this, semantic_frame, key_type, key, value)));
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_before_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  raw__semantic_knowledge_base__know_before_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value);
  return nil;
}
export_cefunk5(semantic_knowledge_base__know_before_semantic_frame_value_addition, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is added to the frame.");


f2ptr raw__semantic_knowledge_base__know_after_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame                 = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr add_semantic_frame_value__after__callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "add_semantic_frame_value-after"), nil);
  {
    f2ptr iter = add_semantic_frame_value__after__callbacks;
    while (iter != nil) {
      f2ptr add_semantic_frame_value__after__callback = f2__cons__car(cause, iter);
      assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), add_semantic_frame_value__after__callback, f2list5__new(cause, this, semantic_frame, key_type, key, value)));
      iter = f2__cons__cdr(cause, iter);
    }
  }
  if (cause != nil) {
    raw__cause__increment_counters_if_exist(cause, cause, new__symbol(cause, "semantic_knowledge_base-semantic_frame_value"), 1);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_after_semantic_frame_value_addition(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  raw__semantic_knowledge_base__know_after_semantic_frame_value_addition(cause, this, semantic_frame, key_type, key, value);
  return nil;
}
export_cefunk5(semantic_knowledge_base__know_after_semantic_frame_value_addition, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is added to the frame.");


f2ptr raw__semantic_knowledge_base__know_before_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame                     = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr remove_semantic_frame_value__before__callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "remove_semantic_frame_value-before"), nil);
  {
    f2ptr iter = remove_semantic_frame_value__before__callbacks;
    while (iter != nil) {
      f2ptr remove_semantic_frame_value__before__callback = f2__cons__car(cause, iter);
      assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), remove_semantic_frame_value__before__callback, f2list5__new(cause, this, semantic_frame, key_type, key, value)));
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_before_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  return raw__semantic_knowledge_base__know_before_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value);
}
export_cefunk5(semantic_knowledge_base__know_before_semantic_frame_value_removal, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is removed from the frame.");


f2ptr raw__semantic_knowledge_base__know_after_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr trace_callback_funks_frame                    = raw__semantic_knowledge_base__trace_callback_funks_frame(cause, this);
  f2ptr remove_semantic_frame_value__after__callbacks = f2__frame__lookup_var_value(cause, trace_callback_funks_frame, new__symbol(cause, "remove_semantic_frame_value-after"), nil);
  {
    f2ptr iter = remove_semantic_frame_value__after__callbacks;
    while (iter != nil) {
      f2ptr remove_semantic_frame_value__after__callback = f2__cons__car(cause, iter);
      assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), remove_semantic_frame_value__after__callback, f2list5__new(cause, this, semantic_frame, key_type, key, value)));
      iter = f2__cons__cdr(cause, iter);
    }
  }
  if (cause != nil) {
    raw__cause__increment_counters_if_exist(cause, cause, new__symbol(cause, "semantic_knowledge_base-semantic_frame_value"), -1);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__know_after_semantic_frame_value_removal(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_frame,          semantic_frame);
  raw__semantic_knowledge_base__know_after_semantic_frame_value_removal(cause, this, semantic_frame, key_type, key, value);
  return nil;
}
export_cefunk5(semantic_knowledge_base__know_after_semantic_frame_value_removal, this, semantic_frame, key_type, key, value, 0, "Usually called by a semantic_frame that belongs to this knowledge base when a value is removed from the frame.");


boolean_t raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size) {
  s64 this_size = 0;
  {
    f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    set__iteration(cause, semantic_frame_set, semantic_frame,
		   s64 semantic_frame__exact_size = 0;
		   if (raw__semantic_frame__recursively_add_to_set(cause, semantic_frame, set, maximum_size - this_size, &semantic_frame__exact_size)) {
		     this_size += semantic_frame__exact_size;
		     if (this_size > maximum_size) {
		       return boolean__false;
		     }
		   } else {
		     return boolean__false;
		   }
		   );
  }
  *exact_size = this_size;
  return boolean__true;
}

f2ptr f2__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place) {
  assert_argument_type(       semantic_knowledge_base, this);
  assert_argument_type(       set,                     set);
  assert_argument_type(       integer,                 maximum_size);
  assert_argument_type_or_nil(place,                   exact_size_place);
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(cause, this, set, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 24511, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk4(semantic_knowledge_base__recursively_add_semantic_frames_to_set, this, set, maximum_size, exact_size_place, 0, "Recursively adds all semantic_frames referenced from the semantic_frames within this knowledge base.");


boolean_t raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64 *exact_size) {
  f2ptr semantic_frame_set = f2__set__new(cause, nil);
  if (! raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(cause, this, semantic_frame_set, maximum_size, exact_size)) {
    return boolean__false;
  }
  set__iteration(cause, semantic_frame_set, semantic_frame,
		 raw__semantic_frame__add_to_graph_with_node_ptypehash(cause, semantic_frame, graph, node_ptypehash));
  return boolean__true;
}

f2ptr f2__semantic_knowledge_base__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place) {
  assert_argument_type(       semantic_knowledge_base, this);
  assert_argument_type(       graph,                   graph);
  assert_argument_type(       ptypehash,               node_ptypehash);
  assert_argument_type(       integer,                 maximum_size);
  assert_argument_type_or_nil(place,                   exact_size_place);
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 23521, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk5(semantic_knowledge_base__add_to_graph_with_node_ptypehash, this, graph, node_ptypehash, maximum_size, exact_size_place, 0, "Add all semantic frames from this knowledge base as well as all semantic frames referenced from those frames.");


f2ptr raw__semantic_knowledge_base__as__digraph_dot_code(f2ptr cause, f2ptr this) {
  f2ptr code;
  {
    f2ptr node_code_ptypehash = f2__ptypehash__new(cause);
    f2ptr edge_code_ptypehash = f2__ptypehash__new(cause);
    {
      f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
      set__iteration(cause, semantic_frame_set, semantic_frame,
		     if (! raw__ptypehash__contains(cause, node_code_ptypehash, semantic_frame)) {
		       if (! raw__relationship_meta_semantic_object__is_type(cause, semantic_frame)) {
			 f2ptr color = f2__graphviz__exp__as__color(cause, semantic_frame);
			 if (raw__larva__is_type(cause, color)) {
			   return color;
			 }
			 if (color == nil) {
			   color = new__string(cause, "#7f7fff");
			 }
			 f2ptr semantic_frame_name = f2__graphviz__exp__as__name(cause, semantic_frame);
			 if (raw__larva__is_type(cause, semantic_frame_name)) {
			   return semantic_frame_name;
			 }
			 f2ptr semantic_frame_label = f2__graphviz__exp__as__label(cause, semantic_frame);
			 if (raw__larva__is_type(cause, semantic_frame_label)) {
			   return semantic_frame_label;
			 }
			 f2ptr node_code = f2__graphviz__node(cause, semantic_frame_name, semantic_frame_label, color);
			 if (raw__larva__is_type(cause, node_code)) {
			   return node_code;
			 }
			 raw__ptypehash__add(cause, node_code_ptypehash, semantic_frame, node_code);
		       }
		     }
		     {
		       f2ptr semantic_realm = raw__semantic_frame__semantic_realm(cause, semantic_frame);
		       semantic_frame__iteration(cause, semantic_frame, key_type, key, value,
						 if (! raw__ptypehash__contains(cause, node_code_ptypehash, value)) {
						   if (! raw__relationship_meta_semantic_object__is_type(cause, value)) {
						     f2ptr value_color = f2__graphviz__exp__as__color(cause, value);
						     if (raw__larva__is_type(cause, value_color)) {
						       return value_color;
						     }
						     if (value_color == nil) {
						       value_color = new__string(cause, "#3f3fff");
						     }
						     f2ptr value_name = f2__graphviz__exp__as__name(cause, value);
						     if (raw__larva__is_type(cause, value_name)) {
						       return value_name;
						     }
						     f2ptr value_label = f2__graphviz__exp__as__label(cause, value);
						     if (raw__larva__is_type(cause, value_label)) {
						       return value_label;
						     }
						     f2ptr value_node_code = f2__graphviz__node(cause, value_name, value_label, value_color);
						     if (raw__larva__is_type(cause, value_node_code)) {
						       return value_node_code;
						     }
						     raw__ptypehash__add(cause, node_code_ptypehash, value, value_node_code);
						   }
						 }
						 {
						   f2ptr relationship = raw__semantic_realm__lookup_or_create_meta_relationship(cause, semantic_realm, semantic_frame, key_type, key, value);
						   if (raw__larva__is_type(cause, relationship)) {
						     return relationship;
						   }
						   if (! raw__ptypehash__contains(cause, edge_code_ptypehash, relationship)) {
						     f2ptr edge_code = f2__relationship_meta_semantic_object__as__graphviz_edge_code(cause, relationship);
						     if (raw__larva__is_type(cause, edge_code)) {
						       return edge_code;
						     }
						     raw__ptypehash__add(cause, edge_code_ptypehash, relationship, edge_code);
						   }
						 }
						 );
		     }
		     );
    }
    {
      f2ptr nodes_code;
      {
	f2ptr node_codes = nil;
	ptypehash__value__iteration(cause, node_code_ptypehash, node_code,
				    node_codes = raw__cons__new(cause, node_code, node_codes));
	nodes_code = f2__stringlist__intersperse(cause, node_codes, new__string(cause, "\n"));
      }
      f2ptr edges_code;
      {
	f2ptr edge_codes = nil;
	ptypehash__value__iteration(cause, edge_code_ptypehash, edge_code,
				    edge_codes = raw__cons__new(cause, edge_code, edge_codes));
	edges_code = f2__stringlist__intersperse(cause, edge_codes, new__string(cause, "\n"));
      }
      code = f2__stringlist__intersperse(cause, f2list2__new(cause, nodes_code, edges_code), new__string(cause, "\n"));
    }
  }
  return code;
}

f2ptr f2__semantic_knowledge_base__as__digraph_dot_code(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__as__digraph_dot_code(cause, this);
}
export_cefunk1(semantic_knowledge_base__as__digraph_dot_code, this, 0, "Compile this semantic_knowledge base as digraph dot code (needs a digraph dot wrapper to be fully compiled).");


f2ptr raw__semantic_knowledge_base__new__event_stream_iterator(f2ptr cause, f2ptr this) {
  f2ptr trace_event_stream = raw__semantic_knowledge_base__trace_event_stream(cause, this);
  f2ptr iterator = raw__event_stream__new__iterator(cause, trace_event_stream);
  raw__forgetful_event_stream__add_important_iterator(cause, trace_event_stream, iterator);
  return iterator;
}

f2ptr f2__semantic_knowledge_base__new__event_stream_iterator(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__new__event_stream_iterator(cause, this);
}
export_cefunk1(semantic_knowledge_base__new__event_stream_iterator, this, 0, "Returns a new event_stream_iterator for this semantic_knowledge_base's trace_event_stream.");


f2ptr raw__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  return raw__set__elements(cause, semantic_frame_set);
}

f2ptr f2__semantic_knowledge_base__semantic_frames(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_knowledge_base, this);
  return raw__semantic_knowledge_base__semantic_frames(cause, this);
}
export_cefunk1(semantic_knowledge_base__semantic_frames, this, 0, "Returns a new conslist of semantic_frames in this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__copy_differences_to(f2ptr cause, f2ptr this, f2ptr target) {
  {
    f2ptr target_semantic_frames = raw__semantic_knowledge_base__semantic_frames(cause, target);
    {
      f2ptr iter = target_semantic_frames;
      while (iter != nil) {
	f2ptr target__semantic_frame = f2cons__car(iter, cause);
	if (! raw__semantic_knowledge_base__contains_semantic_frame(cause, this, target__semantic_frame)) {
	  assert_value(raw__semantic_knowledge_base__remove_semantic_frame(cause, target, target__semantic_frame));
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
  }
  f2ptr semantic_frame_set = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
  set__iteration(cause, semantic_frame_set, semantic_frame,
		 if (! raw__semantic_knowledge_base__contains_semantic_frame(cause, target, semantic_frame)) {
		   raw__semantic_knowledge_base__add_semantic_frame(cause, target, semantic_frame);
		 }
		 );
  return nil;
}

f2ptr f2__semantic_knowledge_base__copy_differences_to(f2ptr cause, f2ptr this, f2ptr target) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(semantic_knowledge_base, target);
  return raw__semantic_knowledge_base__copy_differences_to(cause, this, target);
}
export_cefunk2(semantic_knowledge_base__copy_differences_to, this, target, 0, "Makes the minimal number of changes to the target semantic_knowledge_base in order to make it a copy of this semantic_knowledge_base.");


// semantic_knowledge_base lick funks

f2ptr raw__semantic_knowledge_base__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  {
    f2ptr name   = raw__semantic_knowledge_base__name(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, name, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr semantic_realm   = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, semantic_realm, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr semantic_frame_set   = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, semantic_frame_set, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_event_stream   = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_event_stream, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_add_semantic_frame   = raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_add_semantic_frame, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr trace_remove_semantic_frame   = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
    f2ptr result = raw__lick__object__gather_lick_notes(cause, lick, trace_remove_semantic_frame, note_object_hash, max_size);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(lick,                    lick);
  assert_argument_type(ptypehash,               note_object_hash);
  assert_argument_type(integer,                 max_size);
  return raw__semantic_knowledge_base__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(semantic_knowledge_base__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Licks this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  f2ptr chunk                       = raw__chunk__new(cause, 8 * 6);
  f2ptr name                        = raw__semantic_knowledge_base__name(                       cause, this);
  f2ptr semantic_realm              = raw__semantic_knowledge_base__semantic_realm(             cause, this);
  f2ptr semantic_frame_set          = raw__semantic_knowledge_base__semantic_frame_set(         cause, this);
  f2ptr trace_event_stream          = raw__semantic_knowledge_base__trace_event_stream(         cause, this);
  f2ptr trace_add_semantic_frame    = raw__semantic_knowledge_base__trace_add_semantic_frame(   cause, this);
  f2ptr trace_remove_semantic_frame = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
  s64 chunk_index = 0;
  {
    f2ptr data          = name;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "name"),     name,
															     new__symbol(cause, "this"),     this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = semantic_realm;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),       new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "semantic_realm"), semantic_realm,
															     new__symbol(cause, "this"),           this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = semantic_frame_set;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),           new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "semantic_frame_set"), semantic_frame_set,
															     new__symbol(cause, "this"),               this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_event_stream;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),           new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_event_stream"), trace_event_stream,
															     new__symbol(cause, "this"),               this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_add_semantic_frame;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),                 new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_add_semantic_frame"), trace_add_semantic_frame,
															     new__symbol(cause, "this"),                     this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  {
    f2ptr data          = trace_remove_semantic_frame;
    f2ptr data__note    = raw__ptypehash__lookup(cause, note_object_hash, data);
    if (data__note == nil) {
      return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"),                    new__symbol(cause, "note_changed_while_licking_to_chunk"),
															     new__symbol(cause, "trace_remove_semantic_frame"), trace_remove_semantic_frame,
															     new__symbol(cause, "this"),                        this))));
    }
    s64   data__note__i = f2integer__i(data__note, cause);
    raw__chunk__bit64__elt__set(cause, chunk, chunk_index, (s64)data__note__i);
    chunk_index += 8;
  }
  if (chunk_index != (8 * 6)) {
    return f2larva__new(cause, 23551, nil);
  }
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  if (lick_note == nil) {
    return f2larva__new(cause, 13579, f2__bug__new(cause, f2integer__new(cause, 13579), f2__frame__new(cause, f2list4__new(cause,
															   new__symbol(cause, "bug_type"), new__symbol(cause, "note_changed_while_licking_to_chunk"),
															   new__symbol(cause, "this"),     this))));
  }
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__semantic_knowledge_base__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr note_object_hash) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(ptypehash,               note_object_hash);
  return raw__semantic_knowledge_base__lick_to_chunk(cause, this, note_object_hash);
}
export_cefunk2(semantic_knowledge_base__lick_to_chunk, this, note_object_hash, 0, "Licks this semantic_knowledge_base.");


f2ptr raw__semantic_knowledge_base__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != (8 * 6)) {
    return f2larva__new(cause, 32555, nil);
  }
  f2ptr name__lick_note                        = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  f2ptr semantic_realm__lick_note              = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 8));
  f2ptr semantic_frame_set__lick_note          = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 16));
  f2ptr trace_event_stream__lick_note          = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 24));
  f2ptr trace_add_semantic_frame__lick_note    = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 32));
  f2ptr trace_remove_semantic_frame__lick_note = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 40));
  f2ptr semantic_knowledge_base = raw__semantic_knowledge_base__new_with_details(cause,
										 name__lick_note,
										 semantic_realm__lick_note,
										 semantic_frame_set__lick_note,
										 trace_event_stream__lick_note,
										 trace_add_semantic_frame__lick_note,
										 trace_remove_semantic_frame__lick_note);
  return semantic_knowledge_base;
}

f2ptr f2__semantic_knowledge_base__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(lick_chunk, lick_chunk);
  assert_argument_type(ptypehash,  object_note_hash);
  return raw__semantic_knowledge_base__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(semantic_knowledge_base__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this semantic_knowledge_base lick_chunk with notes.");


f2ptr raw__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__name(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__name__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__semantic_realm(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__semantic_realm__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__semantic_frame_set(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__semantic_frame_set__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_event_stream(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_event_stream__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_add_semantic_frame(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_add_semantic_frame__set(cause, this, data__object);
  }
  {
    f2ptr data__lick_note = raw__semantic_knowledge_base__trace_remove_semantic_frame(cause, this);
    f2ptr data__object    = raw__ptypehash__lookup(cause, object_note_hash, data__lick_note);
    raw__semantic_knowledge_base__trace_remove_semantic_frame__set(cause, this, data__object);
  }
  return nil;
}

f2ptr f2__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  assert_argument_type(semantic_knowledge_base, this);
  assert_argument_type(lick_chunk,              lick_chunk);
  assert_argument_type(ptypehash,               object_note_hash);
  return raw__semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(semantic_knowledge_base__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this semantic_knowledge_base with notes.");


// semantic_knowledge_base

f2ptr f2__semantic_knowledge_base_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_knowledge_base_type__new(cause);
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "get",     "as-graph",                                                   "as__graph");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_semantic_frame",                                         "add_semantic_frame");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "remove_semantic_frame",                                      "remove_semantic_frame");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "get",     "contains_semantic_frame",                                    "contains_semantic_frame");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "remove_all",                                                 "remove_all");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_semantic_knowledge_base",                                "add_semantic_knowledge_base");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_callback_funk",                                    "add_trace_callback_funk");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_callback_funk-add_semantic_frame_value-before",    "add_trace_callback_funk-add_semantic_frame_value-before");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_callback_funk-add_semantic_frame_value-after",     "add_trace_callback_funk-add_semantic_frame_value-after");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_callback_funk-remove_semantic_frame_value-before", "add_trace_callback_funk-remove_semantic_frame_value-before");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_callback_funk-remove_semantic_frame_value-after",  "add_trace_callback_funk-remove_semantic_frame_value-after");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_trace_event",                                            "add_trace_event");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "know_before_semantic_frame_value_addition",                  "know_before_semantic_frame_value_addition");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "know_after_semantic_frame_value_addition",                   "know_after_semantic_frame_value_addition");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "know_before_semantic_frame_value_removal",                   "know_before_semantic_frame_value_removal");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "know_after_semantic_frame_value_removal",                    "know_after_semantic_frame_value_removal");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "recursively_add_semantic_frames_to_set",                     "recursively_add_semantic_frames_to_set");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "add_to_graph_with_node_ptypehash",                           "add_to_graph_with_node_ptypehash");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "get",     "as-digraph_dot_code",                                        "as__digraph_dot_code");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "get",     "new-event_stream_iterator",                                  "new__event_stream_iterator");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "get",     "semantic_frames",                                            "semantic_frames");
  core_extension__primobject_type__add_funk("semantic_causal_event",   "semantic_knowledge_base", "get",     "as-timeline",                                                "as__timeline");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "copy_differences_to",                                        "copy_differences_to");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "gather_lick_notes",                                          "gather_lick_notes");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "lick_to_chunk",                                              "lick_to_chunk");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "lick_chunk-unlick_with_notes",                               "lick_chunk__unlick_with_notes");
  core_extension__primobject_type__add_funk("semantic_knowledge_base", "semantic_knowledge_base", "execute", "lick_chunk-unlick_replace_notes_with_objects",               "lick_chunk__unlick_replace_notes_with_objects");
  return this;
}


// **

f2ptr f2__semantic_knowledge_base__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__ping, 0, "");

boolean_t __semantic_knowledge_base__core_extension__is_initialized = boolean__false;

f2ptr f2__semantic_knowledge_base__core_extension__initialize(f2ptr cause) {
  if (! __semantic_knowledge_base__core_extension__is_initialized) {
    __semantic_knowledge_base__core_extension__is_initialized = boolean__true;
    core_extension__ping(semantic_knowledge_base, equals_hash);
    core_extension__ping(semantic_knowledge_base, forgetful_event_stream);
    core_extension__ping(semantic_knowledge_base, lick);
    core_extension__ping(semantic_knowledge_base, semantic_realm);
    core_extension__ping(semantic_knowledge_base, semantic_causal_event);
    core_extension__ping(semantic_knowledge_base, semantic_relationship_key);
    core_extension__ping(semantic_knowledge_base, semantic_frame);
    // used to be backward:
    core_extension__ping(semantic_knowledge_base, semantic_object);
    core_extension__ping(semantic_knowledge_base, semantic_event);
    status("semantic_knowledge_base initialized.");
  } else {
    status("semantic_knowledge_base already initialized.");
  }
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__initialize, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base_event"), f2__semantic_knowledge_base_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_knowledge_base"),       f2__semantic_knowledge_base_type__new_aux(cause));
  status("semantic_knowledge_base defined types.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__define_types, 0, "");

f2ptr f2__semantic_knowledge_base__core_extension__destroy(f2ptr cause) {
  status("semantic_knowledge_base destroyed.");
  return nil;
}
export_cefunk0(semantic_knowledge_base__core_extension__destroy, 0, "");


