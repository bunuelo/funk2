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

#include "semantic_frame.h"


// semantic_frame_event

f2ptr raw__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr this = f2__event_stream_event__new(cause, time);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),           new__symbol(cause, "semantic_frame_event"));
  raw__frame__add_var_value(cause, this, new__symbol(cause, "event_type"),     event_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), semantic_frame);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key_type"),       key_type);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "key"),            key);
  raw__frame__add_var_value(cause, this, new__symbol(cause, "value"),          value);
  return this;
}

f2ptr f2__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value) {
  return raw__semantic_frame_event__new(cause, time, event_type, semantic_frame, key_type, key, value);
}
export_cefunk6(semantic_frame_event__new, time, event_type, semantic_frame, key_type, key, value, 0, "Returns a new semantic_frame_event object.");


boolean_t raw__semantic_frame_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_frame_event");
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

f2ptr f2__semantic_frame_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_frame_event__is_type(cause, thing));
}
export_cefunk1(semantic_frame_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_frame_event.");


f2ptr raw__semantic_frame_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_frame_event__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__type(cause, this);
}
export_cefunk1(semantic_frame_event__type, thing, 0, "Returns the specific type of object that this semantic_frame_event is.");


f2ptr raw__semantic_frame_event__event_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "event_type"), nil);
}

f2ptr f2__semantic_frame_event__event_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__event_type(cause, this);
}
export_cefunk1(semantic_frame_event__event_type, thing, 0, "Returns the event_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "event_type"), value);
}

f2ptr f2__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__event_type__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__event_type__set, thing, value, 0, "Sets the event_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__semantic_frame(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "semantic_frame"), nil);
}

f2ptr f2__semantic_frame_event__semantic_frame(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__semantic_frame(cause, this);
}
export_cefunk1(semantic_frame_event__semantic_frame, thing, 0, "Returns the semantic_frame of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_frame"), value);
}

f2ptr f2__semantic_frame_event__semantic_frame__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__semantic_frame__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__semantic_frame__set, thing, value, 0, "Sets the semantic_frame of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key_type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key_type"), nil);
}

f2ptr f2__semantic_frame_event__key_type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__key_type(cause, this);
}
export_cefunk1(semantic_frame_event__key_type, thing, 0, "Returns the key_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key_type"), value);
}

f2ptr f2__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__key_type__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__key_type__set, thing, value, 0, "Sets the key_type of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "key"), nil);
}

f2ptr f2__semantic_frame_event__key(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__key(cause, this);
}
export_cefunk1(semantic_frame_event__key, thing, 0, "Returns the key of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "key"), value);
}

f2ptr f2__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__key__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__key__set, thing, value, 0, "Sets the key of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__value(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "value"), nil);
}

f2ptr f2__semantic_frame_event__value(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__value(cause, this);
}
export_cefunk1(semantic_frame_event__value, thing, 0, "Returns the value of the semantic_frame_event.");


f2ptr raw__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "value"), value);
}

f2ptr f2__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(semantic_frame_event, this);
  return raw__semantic_frame_event__value__set(cause, this, value);
}
export_cefunk2(semantic_frame_event__value__set, thing, value, 0, "Sets the value of the semantic_frame_event.");


f2ptr f2__semantic_frame_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "event_stream_event")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__event_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__event_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__semantic_frame")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "semantic_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__semantic_frame__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key_type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__key_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key_type"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__key_type__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__key")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "key"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__key__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "value"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "value"),          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame_event__value__set")));}
  return this;
}




// semantic_frame

def_ceframe11(semantic_frame, semantic_frame,
	      semantic_realm,
	      trace_add,
	      trace_remove,
	      trace_event_stream,
	      semantic_knowledge_base_set,
	      frame_mutate_cmutex,
	      frame_read_mutate_cmutex,
	      read_count,
	      write_in_progress,
	      frame,
	      reverse_frame);

f2ptr raw__semantic_frame__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_frame"));
  }
  // avoid multiply defining the variables in the case of multiple inheritance.
  // this must be checked in all types that are multiply inherited.
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "semantic_realm"))) {
    f2ptr trace_event_stream          = nil;
    f2ptr trace_add                   = f2bool__new(boolean__true);
    f2ptr trace_remove                = f2bool__new(boolean__true);
    f2ptr semantic_knowledge_base_set = f2__set__new(cause);
    f2ptr frame                       = f2__frame__new(cause, nil);
    f2ptr reverse_frame               = f2__frame__new(cause, nil);
    if (cause != nil) {
      trace_add    = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_add"));
      trace_remove = f2__cause__lookup(cause, cause, new__symbol(cause, "semantic_frame-trace_remove"));
    }
    f2ptr frame_read_mutate_cmutex = f2__cmutex__new(cause);
    f2ptr read_count          = f2integer__new(cause, 0);
    f2ptr write_in_progress   = nil;
    f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_realm"),              semantic_realm);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_add"),                   trace_add);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_remove"),                trace_remove);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "trace_event_stream"),          trace_event_stream);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "semantic_knowledge_base_set"), semantic_knowledge_base_set);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "frame_read_mutate_cmutex"),    frame_read_mutate_cmutex);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "read_count"),                  read_count);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "write_in_progress"),           write_in_progress);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "frame"),                       frame);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "reverse_frame"),               reverse_frame);
  }
  return this;
}

f2ptr raw__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__frame__new(cause, nil);
  {
    f2ptr result = raw__semantic_frame__type_create(cause, this, semantic_realm);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return this;
}


f2ptr f2__semantic_frame__new(f2ptr cause, f2ptr semantic_realm) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_frame__new(cause, semantic_realm);
}
export_cefunk1(semantic_frame__new, semantic_realm, 0, "Returns a new semantic_frame object.");


void raw__semantic_frame__initialize_tracing(f2ptr cause, f2ptr this) {
  if (raw__semantic_frame__trace_event_stream(cause, this) == nil) {
    f2ptr trace_event_stream = f2__event_stream__new(cause);
    raw__semantic_frame__trace_event_stream__set(cause, this, trace_event_stream);
  }
}


f2ptr raw__semantic_frame__add_event__new(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  return raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "add"), this, key_type, key, value);
}

f2ptr raw__semantic_frame__add__handle_before_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_add(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_stream   = raw__semantic_frame__trace_event_stream(cause, this);
    f2ptr semantic_frame_event = raw__semantic_frame__add_event__new(cause, this, key_type, key, value);
    raw__event_stream__add(cause, trace_event_stream, semantic_frame_event);
    {
      f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
      set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		     assert_value(raw__semantic_knowledge_base__know_before_semantic_frame_value_addition(cause, semantic_knowledge_base, this, key_type, key, value));
		     assert_value(f2__semantic_knowledge_base__add_trace_event(cause, semantic_knowledge_base, semantic_frame_event));
		     );
    }
  }
  return nil;
}

f2ptr raw__semantic_frame__add__without_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr key_type__object_key = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key_type));
  f2ptr key__object_key      = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key));
  {
    f2ptr frame     = raw__semantic_frame__frame(cause, this);
    f2ptr value_set = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
    if (value_set == nil) {
      value_set = f2__set__new(cause);
      raw__frame__add_type_var_value(cause, frame, key_type__object_key, key__object_key, value_set);
    }
    raw__set__add(cause, value_set, value);
  }
  if (raw__semantic_frame__is_type(cause, value)) {
    f2ptr reverse_frame     = raw__semantic_frame__reverse_frame(cause, value);
    f2ptr reverse_value_set = raw__frame__lookup_type_var_value(cause, reverse_frame, key_type__object_key, key__object_key, nil);
    if (reverse_value_set == nil) {
      reverse_value_set = f2__set__new(cause);
      raw__frame__add_type_var_value(cause, reverse_frame, key_type__object_key, key__object_key, reverse_value_set);
    }
    raw__set__add(cause, reverse_value_set, this);
  }
  return nil;
}

f2ptr raw__semantic_frame__add__handle_after_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_add(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    {
      f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
      set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		     assert_value(raw__semantic_knowledge_base__know_after_semantic_frame_value_addition(cause, semantic_knowledge_base, this, key_type, key, value));
		     );
    }
  }
  return nil;
}

f2ptr raw__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_value(raw__semantic_frame__add__handle_before_callbacks(cause, this, key_type, key, value));
  assert_value(raw__semantic_frame__add__without_callbacks(      cause, this, key_type, key, value));
  assert_value(raw__semantic_frame__add__handle_after_callbacks( cause, this, key_type, key, value));
  return nil;
}

f2ptr f2__semantic_frame__add(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__add(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__add, this, key_type, key, value, 0, "Adds the value to the key_type and key set of values.");


f2ptr raw__semantic_frame__remove_event__new(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  return raw__semantic_frame_event__new(cause, f2__time(cause), new__symbol(cause, "remove"), this, key_type, key, value);
}

f2ptr raw__semantic_frame__remove__handle_before_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_remove(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    f2ptr trace_event_stream   = raw__semantic_frame__trace_event_stream(cause, this);
    f2ptr semantic_frame_event = raw__semantic_frame__remove_event__new(cause, this, key_type, key, value);
    raw__event_stream__add(cause, trace_event_stream, semantic_frame_event);
    {
      f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
      set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		     assert_value(raw__semantic_knowledge_base__know_before_semantic_frame_value_removal(cause, semantic_knowledge_base, this, key_type, key, value));
		     assert_value(raw__semantic_knowledge_base__add_trace_event(cause, semantic_knowledge_base, semantic_frame_event));
		     );
    }
  }
  return nil;
}

f2ptr raw__semantic_frame__remove__without_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr key_type__object_key = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key_type));
  f2ptr key__object_key      = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key));
  {
    f2ptr frame     = raw__semantic_frame__frame(cause, this);
    f2ptr value_set = raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
    if ((value_set == nil) || (! raw__set__remove(cause, value_set, value))) {
      return new__error(f2list12__new(cause,
				      new__symbol(cause, "bug_name"),      new__symbol(cause, "value_does_not_exist_in_semantic_frame"),
				      new__symbol(cause, "funktion_name"), new__symbol(cause, "semantic_frame-remove"),
				      new__symbol(cause, "this"),          this,
				      new__symbol(cause, "key_type"),      key_type,
				      new__symbol(cause, "key"),           key,
				      new__symbol(cause, "value"),         value));
    }
  }
  if (raw__semantic_frame__is_type(cause, value)) {
    f2ptr reverse_frame     = raw__semantic_frame__reverse_frame(cause, value);
    f2ptr reverse_value_set = raw__frame__lookup_type_var_value(cause, reverse_frame, key_type__object_key, key__object_key, nil);
    if ((reverse_value_set == nil) || (! raw__set__remove(cause, reverse_value_set, this))) {
      return new__error(f2list12__new(cause,
				      new__symbol(cause, "bug_name"),      new__symbol(cause, "value_does_not_exist_in_semantic_frame_reverse_frame"),
				      new__symbol(cause, "funktion_name"), new__symbol(cause, "semantic_frame-remove"),
				      new__symbol(cause, "this"),          this,
				      new__symbol(cause, "key_type"),      key_type,
				      new__symbol(cause, "key"),           key,
				      new__symbol(cause, "value"),         value));
    }
  }
  return nil;
}

f2ptr raw__semantic_frame__remove__handle_after_callbacks(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  if (raw__semantic_frame__trace_remove(cause, this) != nil) {
    raw__semantic_frame__initialize_tracing(cause, this);
    {
      f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
      set__iteration(cause, semantic_knowledge_base_set, semantic_knowledge_base,
		     assert_value(raw__semantic_knowledge_base__know_after_semantic_frame_value_removal(cause, semantic_knowledge_base, this, key_type, key, value));
		     );
    }
  }
  return nil;
}

f2ptr raw__semantic_frame__remove(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_value(raw__semantic_frame__remove__handle_before_callbacks(cause, this, key_type, key, value));
  assert_value(raw__semantic_frame__remove__without_callbacks(      cause, this, key_type, key, value));
  assert_value(raw__semantic_frame__remove__handle_after_callbacks( cause, this, key_type, key, value));
  return nil;
}

f2ptr f2__semantic_frame__remove(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__remove(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__remove, this, key_type, key, value, 0, "Removes the value from the key_type and key set of values.");


f2ptr raw__semantic_frame__lookup_set(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key_type));
  f2ptr key__object_key      = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key));
  return raw__frame__lookup_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
}

f2ptr f2__semantic_frame__lookup_set(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__lookup_set(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup_set, this, key_type, key, 0, "Returns the set of values associated with the key_type and key.");


f2ptr raw__semantic_frame__lookup_reverse_set(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr reverse_frame        = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key_type));
  f2ptr key__object_key      = assert_value(raw__semantic_realm__object_key(cause, semantic_realm, key));
  return raw__frame__lookup_type_var_value(cause, reverse_frame, key_type__object_key, key__object_key, nil);
}

f2ptr f2__semantic_frame__lookup_reverse_set(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__lookup_reverse_set(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup_reverse_set, this, key_type, key, 0, "Returns the set of values that this semantic_frame is associated with by the given key_type and key.");


f2ptr raw__semantic_frame__lookup_type_var_value__thread_unsafe(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr     value_set           = f2__semantic_frame__lookup_set(cause, this, key_type, key);
  boolean_t found_current_value = boolean__false;
  f2ptr     current_value       = nil;
  if (value_set != nil) {
    if (! raw__set__is_type(cause, value_set)) {
      return new__error(f2list10__new(cause,
				      new__symbol(cause, "bug_name"), new__symbol(cause, "semantic_frame_slot_contains_non_set"),
				      new__symbol(cause, "funkname"), new__symbol(cause, "semantic_frame-lookup_type_var_value"),
				      new__symbol(cause, "this"),     this,
				      new__symbol(cause, "key_type"), key_type,
				      new__symbol(cause, "key"),      key));
    }
    set__iteration(cause, value_set, value,
		   if (found_current_value) {
		     return new__error(f2list10__new(cause,
						     new__symbol(cause, "bug_name"), new__symbol(cause, "semantic_frame_has_more_than_one_value_in_slot"),
						     new__symbol(cause, "funkname"), new__symbol(cause, "semantic_frame-lookup_type_var_value"),
						     new__symbol(cause, "this"),     this,
						     new__symbol(cause, "key_type"), key_type,
						     new__symbol(cause, "key"),      key));
		   }
		   current_value = value;
		   found_current_value = boolean__true;
		   );
  }
  if (! found_current_value) {
    return new__error(f2list10__new(cause,
				    new__symbol(cause, "bug_name"), new__symbol(cause, "semantic_frame_does_not_have_slot_value"),
				    new__symbol(cause, "funkname"), new__symbol(cause, "semantic_frame-lookup_type_var_value"),
				    new__symbol(cause, "this"),     this,
				    new__symbol(cause, "key_type"), key_type,
				    new__symbol(cause, "key"),      key));
  }
  return current_value;
}


f2ptr raw__semantic_frame__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr frame_read_mutate_cmutex = raw__semantic_frame__frame_read_mutate_cmutex(cause, this);
  {
    boolean_t keep_looping;
    do {
      f2ptr read_count;
      f2ptr write_in_progress;
      f2__cmutex__lock(cause, frame_read_mutate_cmutex);
      read_count        = raw__semantic_frame__read_count(cause, this);
      write_in_progress = raw__semantic_frame__write_in_progress(cause, this);
      if (write_in_progress != nil) {
	keep_looping = boolean__true;
	f2__this__fiber__yield(cause);
      } else {
	keep_looping = boolean__false;
	read_count = f2integer__new(cause, f2integer__i(read_count, cause) + 1);
	raw__semantic_frame__read_count__set(cause, this, read_count);
      }
      f2__cmutex__unlock(cause, frame_read_mutate_cmutex);
    } while (keep_looping);
  }
  f2ptr result = raw__semantic_frame__lookup_type_var_value__thread_unsafe(cause, this, key_type, key);
  {
    f2__cmutex__lock(cause, frame_read_mutate_cmutex);
    f2ptr read_count = raw__semantic_frame__read_count(cause, this);
    read_count       = f2integer__new(cause, f2integer__i(read_count, cause) - 1);
    raw__semantic_frame__read_count__set(cause, this, read_count);
    f2__cmutex__unlock(cause, frame_read_mutate_cmutex);
  }
  return result;
}

f2ptr f2__semantic_frame__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__lookup_type_var_value(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__lookup_type_var_value, this, key_type, key, 0, "Returns the one value associated with the key_type and key.");


f2ptr raw__semantic_frame__replace_type_var_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  f2ptr result              = nil;
  f2ptr frame_mutate_cmutex = raw__semantic_frame__frame_mutate_cmutex(cause, this);
  f2__cmutex__lock(cause, frame_mutate_cmutex);
  {
    f2ptr current_value = raw__semantic_frame__lookup_type_var_value__thread_unsafe(cause, this, key_type, key);
    if (raw__larva__is_type(cause, current_value)) {
      result = new__error(f2list10__new(cause,
					new__symbol(cause, "bug_name"), new__symbol(cause, "error_encountered_while_getting_current_value"),
					new__symbol(cause, "this"),     this,
					new__symbol(cause, "key_type"), key_type,
					new__symbol(cause, "key"),      key,
					new__symbol(cause, "subbug"),   f2__bug__new_from_larva(cause, current_value)));
    } else {
      if (raw__eq(cause, current_value, value)) {
	result = nil;
      } else {
	assert_value(raw__semantic_frame__remove__handle_before_callbacks(cause, this, key_type, key, current_value));
	assert_value(raw__semantic_frame__add__handle_before_callbacks(   cause, this, key_type, key, value));
	{
	  f2ptr frame_read_mutate_cmutex = raw__semantic_frame__frame_read_mutate_cmutex(cause, this);
	  {
	    boolean_t keep_looping;
	    do {
	      f2ptr read_count;
	      f2ptr write_in_progress;
	      f2__cmutex__lock(cause, frame_read_mutate_cmutex);
	      read_count        = raw__semantic_frame__read_count(cause, this);
	      write_in_progress = raw__semantic_frame__write_in_progress(cause, this);
	      if ((f2integer__i(read_count, cause) != 0) ||
		  (write_in_progress != nil)) {
		keep_looping = boolean__true;
		f2__this__fiber__yield(cause);
	      } else {
		keep_looping = boolean__false;
		write_in_progress = f2bool__new(boolean__true);
		raw__semantic_frame__write_in_progress__set(cause, this, write_in_progress);
	      }
	      f2__cmutex__unlock(cause, frame_read_mutate_cmutex);
	    } while (keep_looping);
	  }
	  {
	    result = raw__semantic_frame__remove__without_callbacks(cause, this, key_type, key, current_value);
	    if (! raw__larva__is_type(cause, result)) {
	      result = raw__semantic_frame__add__without_callbacks(cause, this, key_type, key, value);
	    }
	  }
	  {
	    f2__cmutex__lock(cause, frame_read_mutate_cmutex);
	    raw__semantic_frame__write_in_progress__set(cause, this, nil);
	    f2__cmutex__unlock(cause, frame_read_mutate_cmutex);
	  }
	}
	assert_value(raw__semantic_frame__remove__handle_after_callbacks(cause, this, key_type, key, current_value));
	assert_value(raw__semantic_frame__add__handle_after_callbacks(   cause, this, key_type, key, value));
      }
    }
  }
  f2__cmutex__unlock(cause, frame_mutate_cmutex);
  return result;
}

f2ptr f2__semantic_frame__replace_type_var_value(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__replace_type_var_value(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__replace_type_var_value, this, key_type, key, value, 0, "");


f2ptr raw__semantic_frame__lookup_set_contains(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr set = assert_value(raw__semantic_frame__lookup_set(cause, this, key_type, key));
  if (set == nil) {
    return f2bool__new(boolean__false);
  }
  return f2bool__new(raw__set__contains(cause, set, value));
}

f2ptr f2__semantic_frame__lookup_set_contains(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__lookup_set_contains(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__lookup_set_contains, this, key_type, key, value, 0, "Returns the values associated with the key_type and key.");


f2ptr raw__semantic_frame__assure_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr contains = assert_value(raw__semantic_frame__lookup_set_contains(cause, this, key_type, key, value));
  if (contains == nil) {
    f2ptr result = raw__semantic_frame__add(cause, this, key_type, key, value);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}

f2ptr f2__semantic_frame__assure_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__assure_exists(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__assure_exists, this, key_type, key, value, 0, "Adds the semantic relationship if it does not already exist in this semantic_frame.");


f2ptr raw__semantic_frame__assure_not_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  f2ptr contains = assert_value(raw__semantic_frame__lookup_set_contains(cause, this, key_type, key, value));
  if (contains != nil) {
    f2ptr result = raw__semantic_frame__remove(cause, this, key_type, key, value);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}

f2ptr f2__semantic_frame__assure_not_exists(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__assure_not_exists(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__assure_not_exists, this, key_type, key, value, 0, "Adds the semantic relationship if it does not already exist in this semantic_frame.");


f2ptr raw__semantic_frame__remove_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  f2ptr semantic_realm       = raw__semantic_frame__semantic_realm(cause, this);
  f2ptr frame                = raw__semantic_frame__frame(cause, this);
  f2ptr key_type__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key_type);
  if (raw__larva__is_type(cause, key_type__object_key)) {
    return key_type__object_key;
  }
  f2ptr key__object_key = raw__semantic_realm__object_key(cause, semantic_realm, key);
  if (raw__larva__is_type(cause, key__object_key)) {
    return key__object_key;
  }
  f2ptr set = raw__frame__add_type_var_value(cause, frame, key_type__object_key, key__object_key, nil);
  if (set != nil) {
    f2ptr elements = raw__set__elements(cause, set);
    {
      f2ptr iter = elements;
      while (iter != nil) {
	f2ptr element = f2__cons__car(cause, iter);
	raw__semantic_frame__remove(cause, this, key_type, key, element);
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return nil;
}

f2ptr f2__semantic_frame__remove_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__remove_all(cause, this, key_type, key);
}
export_cefunk3(semantic_frame__remove_all, this, key_type, key, 0, "Removes all associated values from this key_type and key.");


f2ptr raw__semantic_frame__replace_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  raw__semantic_frame__remove_all(cause, this, key_type, key);
  return raw__semantic_frame__add(cause, this, key_type, key, value);
}

f2ptr f2__semantic_frame__replace_all(f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__replace_all(cause, this, key_type, key, value);
}
export_cefunk4(semantic_frame__replace_all, this, key_type, key, value, 0, "Removes all associated values from this key_type and key, and adds the given value.");


void raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
  f2__set__add(cause, semantic_knowledge_base_set, semantic_knowledge_base);
}

f2ptr f2__semantic_frame__know_of_addition_to_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  assert_argument_type(semantic_frame,          this);
  assert_argument_type(semantic_knowledge_base, semantic_knowledge_base);
  raw__semantic_frame__know_of_addition_to_semantic_knowledge_base(cause, this, semantic_knowledge_base);
  return nil;
}
export_cefunk2(semantic_frame__know_of_addition_to_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Adds the given semantic_knowledge_base to this semantic_frame's semantic_knowledge_base_set.");


void raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  f2ptr semantic_knowledge_base_set = raw__semantic_frame__semantic_knowledge_base_set(cause, this);
  f2__set__remove(cause, semantic_knowledge_base_set, semantic_knowledge_base);
}

f2ptr f2__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base) {
  assert_argument_type(semantic_frame,          this);
  assert_argument_type(semantic_knowledge_base, semantic_knowledge_base);
  raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(cause, this, semantic_knowledge_base);
  return nil;
}
export_cefunk2(semantic_frame__know_of_removal_from_semantic_knowledge_base, this, semantic_knowledge_base, 0, "Removes the given semantic_knowledge_base from this semantic_frame's semantic_knowledge_base_set.");


boolean_t raw__semantic_frame__recursively_add_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size) {
  if (maximum_size <= 0) {
    return boolean__false;
  }
  boolean_t this_is_in_set = raw__set__contains(cause, set, this);
  if (this_is_in_set) {
    *exact_size = 0;
    return boolean__true;
  }
  f2__set__add(cause, set, this);
  // semantic_frame nodes count as one.
  s64 this_size = 1;
  semantic_frame__value__iteration(cause, this, slot_value,
				   if (raw__semantic_frame__is_type(cause, slot_value)) {
				     s64 slot_value__exact_size;
				     if (raw__semantic_frame__recursively_add_to_set(cause, slot_value, set, maximum_size - this_size, &slot_value__exact_size)) {
				       this_size += slot_value__exact_size;
				     } else {
				       return boolean__false;
				     }
				   } else {
				     // non-semantic_frame leaf nodes count as one.
				     this_size ++;
				   }
				   if (this_size >= maximum_size) {
				     return boolean__false;
				   }
				   );
  *exact_size = this_size;
  return boolean__true;
}

f2ptr f2__semantic_frame__recursively_add_to_set(f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place) {
  assert_argument_type(       semantic_frame, this);
  assert_argument_type(       set,            set);
  assert_argument_type(       integer,        maximum_size);
  assert_argument_type_or_nil(place,          exact_size_place);
  s64 maximum_size__i = f2integer__i(maximum_size, cause);
  s64 exact_size__i   = 0;
  if (! raw__semantic_frame__recursively_add_to_set(cause, this, set, maximum_size__i, &exact_size__i)) {
    return f2larva__new(cause, 4151, nil);
  }
  if (raw__place__is_type(cause, exact_size_place)) {
    f2__place__thing__set(cause, exact_size_place, f2integer__new(cause, exact_size__i));
  }
  return nil;
}
export_cefunk4(semantic_frame__recursively_add_to_set, this, set, maximum_size, exact_size_place, 0,
	       "Recursively enumerates all semantic_frames referenced from this semantic frame.\n"
	       "Each semantic_frame is added to the given set.\n"
	       "This function fails if more than maximum_size number of frames is encountered.\n"
	       "A exact_size_place may be given to store the exact_size before returning.");


void raw__semantic_frame__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
  }
  semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value,
			    //f2ptr key_type_node   = f2__graph_node__new(cause, key_type_name);
			    //f2ptr key_node        = f2__graph_node__new(cause, key_name);
			    f2ptr slot_value_node;
			    if (raw__semantic_frame__is_type(cause, slot_value)) {
			      slot_value_node = f2__ptypehash__lookup(cause, node_ptypehash, slot_value);
			      if (slot_value_node == nil) {
				slot_value_node = f2__graph_node__new(cause, slot_value);
				f2__ptypehash__add(cause, node_ptypehash, slot_value, slot_value_node);
			      }
			    } else {
			      slot_value_node = f2__graph_node__new(cause, slot_value);
			    }
			    f2ptr edge_name = f2__stringlist__concat(cause, f2list3__new(cause,
											 f2__exp__as__string(cause, key_type_name),
											 new__string(cause, "-"),
											 f2__exp__as__string(cause, key_name)));
			    f2__graph__add_new_edge(cause, graph, edge_name, this_node, slot_value_node);
			    );
}

f2ptr f2__semantic_frame__add_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  assert_argument_type(semantic_frame, this);
  assert_argument_type(graph,          graph);
  assert_argument_type(ptypehash,      node_ptypehash);
  raw__semantic_frame__add_to_graph_with_node_ptypehash(cause, this, graph, node_ptypehash);
  return nil;
}
export_cefunk3(semantic_frame__add_to_graph_with_node_ptypehash, this, graph, node_ptypehash, 0, "Adds this semantic frame and slots to the given graph, using the given node_ptypehash to reuse nodes generated by previous calls to this function.");


f2ptr raw__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  return f2__exp__as__string(cause, f2__object__type(cause, this));
}

f2ptr f2__semantic_frame__as__graphviz_label(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__as__graphviz_label(cause, this);
}
export_cefunk1(semantic_frame__as__graphviz_label, this, 0, "Returns a string representing the specific type of this semantic_frame for rendering semantic_frame objects in graphviz.");


boolean_t raw__semantic_frame__is_semantic_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  return raw__semantic_frame__lookup_set_contains(cause, this, new__symbol(cause, "type"), new__symbol(cause, "name"), type_name);
}

f2ptr f2__semantic_frame__is_semantic_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  assert_argument_type(semantic_frame, this);
  return raw__semantic_frame__is_semantic_type(cause, this, type_name);
}
export_cefunk2(semantic_frame__is_semantic_type, this, type_name, 0, "Returns true if this semantic_frame is of the given semantic type, false otherwise.");



f2ptr raw__semantic_frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this)));
    f2ptr semantic_frame__frame = raw__semantic_frame__frame(cause, this);
    frame__iteration(cause, semantic_frame__frame, type_slot_name, slot_name, slot_value,
		     f2ptr set           = slot_value;
		     f2ptr set__elements = f2__set__elements(cause, set);
		     raw__frame__add_type_var_value(cause, frame, type_slot_name, slot_name, set__elements);
		     );
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__semantic_frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(semantic_frame,       this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__semantic_frame__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(semantic_frame__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__semantic_frame_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_frame_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_set"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lookup_type_var_value"),                        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__lookup_type_var_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "replace_type_var_value"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__replace_type_var_value")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "lookup_set_contains"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__lookup_set_contains")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "assure_exists"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__assure_exists")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "assure_not_exists"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__assure_not_exists")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove_all"),                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__remove_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "replace_all"),                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__replace_all")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_addition_to_semantic_knowledge_base"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__know_of_addition_to_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "know_of_removal_from_semantic_knowledge_base"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__know_of_removal_from_semantic_knowledge_base")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "recursively_add_to_set"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__recursively_add_to_set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_to_graph_with_node_ptypehash"),             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__add_to_graph_with_node_ptypehash")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "as-graphviz_label"),                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__as__graphviz_label")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "is_semantic_type"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__is_semantic_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_frame"), new__symbol(cause, "semantic_frame__terminal_print_with_frame")));}
  return this;
}



// semantic_frame object accessors

// object-semantic-lookup_set, object-semantic-lookup_set-apply

f2ptr f2__object__semantic__lookup_set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 1421, f2__bug__new(cause, f2integer__new(cause, 1421), f2__frame__new(cause, f2list10__new(cause,
															      new__symbol(cause, "bug_name"), new__symbol(cause, "argument_list_is_not_a_conslist"),
															      new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup_set"),
															      new__symbol(cause, "this"),     this,
															      new__symbol(cause, "slot"),     slot,
															      new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-lookup_set"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_name"), new__symbol(cause, "object_does_not_have_semantic-lookup_set_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-lookup_set"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__lookup_set, this, slot, args, 0, "");

f2ptr f2__object__semantic__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__lookup_set(cause, this, slot, args);
}
export_cefunk3(object__semantic__lookup_set__apply, this, slot, args, 0, "");


// object-semantic-add, object-semantic-add-apply

f2ptr f2__object__semantic__add(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 143222, f2__bug__new(cause, f2integer__new(cause, 143222), f2__frame__new(cause, f2list10__new(cause,
																  new__symbol(cause, "bug_name"), new__symbol(cause, "argument_list_is_not_a_conslist"),
																  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
																  new__symbol(cause, "this"),     this,
																  new__symbol(cause, "slot"),     slot,
																  new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-add"), slot);
  if (raw__larva__is_type(cause, funk)) {
    return funk;
  }
  if (! raw__funkable__is_type(cause, funk)) {
    return f2larva__new(cause, 2345, f2__bug__new(cause, f2integer__new(cause, 2345), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_name"), new__symbol(cause, "object_does_not_have_semantic-add_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-add"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  return result;
}
export_cefunk2_and_rest(object__semantic__add, this, slot, args, 0, "");

f2ptr f2__object__semantic__add__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__add(cause, this, slot, args);
}
export_cefunk3(object__semantic__add__apply, this, slot, args, 0, "");


// object-semantic-remove, object-semantic-remove-apply

f2ptr f2__object__semantic__remove(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  if (raw__larva__is_type(cause, slot)) {
    return slot;
  }
  {
    f2ptr iter = args;
    while (iter != nil) {
      if (! raw__cons__is_type(cause, iter)) {
	return f2larva__new(cause, 234234, f2__bug__new(cause, f2integer__new(cause, 234234), f2__frame__new(cause, f2list10__new(cause,
																  new__symbol(cause, "bug_name"), new__symbol(cause, "argument_list_is_not_a_conslist"),
																  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
																  new__symbol(cause, "this"),     this,
																  new__symbol(cause, "slot"),     slot,
																  new__symbol(cause, "args"),     args))));
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, new__symbol(cause, "semantic-remove"), slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, 2346, f2__bug__new(cause, f2integer__new(cause, 2346), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_name"), new__symbol(cause, "object_does_not_have_semantic-remove_funk"),
															  new__symbol(cause, "funkname"), new__symbol(cause, "object-semantic-remove"),
															  new__symbol(cause, "this"),     this,
															  new__symbol(cause, "slot"),     slot,
															  new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, raw__cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
export_cefunk2_and_rest(object__semantic__remove,        this, slot, args, 0, "");

f2ptr f2__object__semantic__remove__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  return f2__object__semantic__remove(cause, this, slot, args);
}
export_cefunk3(object__semantic__remove__apply, this, slot, args, 0, "");





// **

f2ptr f2__semantic_frame__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_frame__core_extension__ping, 0, "");

f2ptr f2__semantic_frame__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_frame, semantic_realm);
  core_extension__ping(semantic_frame, semantic_relationship_key);
  status("semantic_frame initialized.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__initialize, 0, "");

f2ptr f2__semantic_frame__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_frame_event"), f2__semantic_frame_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_frame"),       f2__semantic_frame_type__new_aux(cause));
  status("semantic_frame defined types.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__define_types, 0, "");

f2ptr f2__semantic_frame__core_extension__destroy(f2ptr cause) {
  status("semantic_frame destroyed.");
  return nil;
}
export_cefunk0(semantic_frame__core_extension__destroy, 0, "");


