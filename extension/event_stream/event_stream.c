// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#include "event_stream.h"


// event_stream_event

f2ptr raw__event_stream_event__time_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this = f2__cons__car(cause, args_iter);
  return raw__event_stream_event__time(cause, this);
}

f2ptr raw__event_stream_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr args_iter = args;
  f2ptr this__time = f2__cons__car(cause, args_iter); args_iter = f2__cons__cdr(cause, args_iter);
  f2ptr that__time = f2__cons__car(cause, args_iter);
  {
    f2ptr this__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, this__time);
    f2ptr that__nanoseconds_since_1970 = f2__time__nanoseconds_since_1970(cause, that__time);
    s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
    s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
    return f2bool__new(this__nanoseconds_since_1970__i < that__nanoseconds_since_1970__i);
  }
}


f2ptr raw__event_stream_event__new(f2ptr cause, f2ptr time) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"), new__symbol(cause, "event_stream_event"),
					    new__symbol(cause, "time"), time));
}

f2ptr f2__event_stream_event__new(f2ptr cause, f2ptr time) {
  if (! raw__time__is_type(cause, time)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__new(cause, time);
}
export_cefunk1(event_stream_event__new, time, 0, "Returns a new event_stream_event object.");


boolean_t raw__event_stream_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "event_stream_event");
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

f2ptr f2__event_stream_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__event_stream_event__is_type(cause, thing));
}
export_cefunk1(event_stream_event__is_type, thing, 0, "Returns whether or not thing is of type event_stream_event.");


f2ptr raw__event_stream_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__event_stream_event__type(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__type(cause, this);
}
export_cefunk1(event_stream_event__type, thing, 0, "Returns the specific type of object that this event_stream_event is.");


f2ptr raw__event_stream_event__time(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "time"), nil);
}

f2ptr f2__event_stream_event__time(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__time(cause, this);
}
export_cefunk1(event_stream_event__time, thing, 0, "Returns the time of the event_stream_event.");


f2ptr raw__event_stream_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "time"), value);
}

f2ptr f2__event_stream_event__time__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__event_stream_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__time__set(cause, this, value);
}
export_cefunk2(event_stream_event__time__set, thing, value, 0, "Sets the time of the event_stream_event.");


f2ptr raw__event_stream_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    raw__frame__copy(cause, frame, this);
    raw__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), f2__object__type(cause, this));
    raw__frame__add_var_value(cause, frame, new__symbol(cause, "time"),              raw__event_stream_event__time(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__event_stream_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__event_stream_event__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(event_stream_event__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__event_stream_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__time")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "time"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__terminal_print_with_frame")));}
  return this;
}


// event_stream

f2ptr raw__event_stream__new(f2ptr cause) {
  f2ptr event_time_redblacktree__value_event_cfunk   = f2cfunk__new(cause, nil, 
								    f2list1__new(cause, new__symbol(cause, "this")),
								    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__event_stream_event__time_value)), global_environment(), nil, nil);
  f2ptr event_time_redblacktree__compare_event_cfunk = f2cfunk__new(cause, nil, 
								    f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
								    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__event_stream_event__compare_value)), global_environment(), nil, nil);
  f2ptr event_time_redblacktree = f2__redblacktree__new(cause, event_time_redblacktree__value_event_cfunk, event_time_redblacktree__compare_event_cfunk);
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),                    new__symbol(cause, "event_stream"),
					    new__symbol(cause, "event_time_redblacktree"), event_time_redblacktree));
}

f2ptr f2__event_stream__new(f2ptr cause) {
  return raw__event_stream__new(cause);
}
export_cefunk0(event_stream__new, 0, "Returns a new event_stream object.");


boolean_t raw__event_stream__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "event_stream");
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

f2ptr f2__event_stream__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__event_stream__is_type(cause, thing));
}
export_cefunk1(event_stream__is_type, thing, 0, "Returns whether or not thing is of type event_stream.");


f2ptr raw__event_stream__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__event_stream__type(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__type(cause, this);
}
export_cefunk1(event_stream__type, thing, 0, "Returns the specific type of object that this event_stream is.");


f2ptr raw__event_stream__event_time_redblacktree(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "event_time_redblacktree"), nil);
}

f2ptr f2__event_stream__event_time_redblacktree(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__event_time_redblacktree(cause, this);
}
export_cefunk1(event_stream__event_time_redblacktree, thing, 0, "Returns the event_time_redblacktree of the event_stream.");


f2ptr raw__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "event_time_redblacktree"), value);
}

f2ptr f2__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__event_time_redblacktree__set(cause, this, value);
}
export_cefunk2(event_stream__event_time_redblacktree__set, thing, value, 0, "Sets the event_time_redblacktree of the event_stream.");


f2ptr raw__event_stream__add(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  return raw__redblacktree__insert(cause, event_time_redblacktree, event_stream_event);
}

f2ptr f2__event_stream__add(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__event_stream_event__is_type(cause, event_stream_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__add(cause, this, event_stream_event);
}
export_cefunk2(event_stream__add, this, event_stream_event, 0, "Add an event_stream_event to this event_stream.");


f2ptr raw__event_stream__remove(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  return raw__redblacktree__remove(cause, event_time_redblacktree, event_stream_event);
}

f2ptr f2__event_stream__remove(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__event_stream_event__is_type(cause, event_stream_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__remove(cause, this, event_stream_event);
}
export_cefunk2(event_stream__remove, this, event_stream_event, 0, "Remove an event_stream_event from this event_stream.");


f2ptr f2__event_stream_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "event_time_redblacktree"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__event_time_redblacktree")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "event_time_redblacktree"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__event_time_redblacktree__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__remove")));}
  return this;
}



// **

f2ptr f2__event_stream__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(event_stream__core_extension_ping, 0, "");

f2ptr f2__event_stream__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "event_stream_event"), f2__event_stream_event_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "event_stream"),       f2__event_stream_type__new(cause));
  status("event_stream initialized.");
  return nil;
}
export_cefunk0(event_stream__core_extension_initialize, 0, "");

f2ptr f2__event_stream__core_extension_destroy(f2ptr cause) {
  status("event_stream destroyed.");
  return nil;
}
export_cefunk0(event_stream__core_extension_destroy, 0, "");


