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
#include "../lick/lick.h"


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


def_ceframe1(event_stream, event_stream_event, time);

f2ptr raw__event_stream_event__new(f2ptr cause, f2ptr time) {
  return f2event_stream_event__new(cause, time);
}

f2ptr f2__event_stream_event__new(f2ptr cause, f2ptr time) {
  if (! raw__time__is_type(cause, time)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_event__new(cause, time);
}
export_cefunk1(event_stream_event__new, time, 0, "Returns a new event_stream_event object.");


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


f2ptr f2__event_stream_event_type__new_aux(f2ptr cause) {
  f2ptr this = f2__event_stream_event_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_event__terminal_print_with_frame")));}
  return this;
}


// event_stream

def_ceframe1(event_stream, event_stream, event_time_redblacktree);

f2ptr raw__event_stream__new(f2ptr cause) {
  f2ptr event_time_redblacktree__value_event_cfunk   = f2cfunk__new(cause, nil, 
								    f2list1__new(cause, new__symbol(cause, "this")),
								    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__event_stream_event__time_value)), global_environment(), nil, nil);
  f2ptr event_time_redblacktree__compare_event_cfunk = f2cfunk__new(cause, nil, 
								    f2list2__new(cause, new__symbol(cause, "this"), new__symbol(cause, "that")),
								    f2pointer__new(cause, raw_executable__to__relative_ptr(raw__event_stream_event__compare_value)), global_environment(), nil, nil);
  f2ptr event_time_redblacktree = f2__redblacktree__new(cause, event_time_redblacktree__value_event_cfunk, event_time_redblacktree__compare_event_cfunk);
  return f2event_stream__new(cause, event_time_redblacktree);
}

f2ptr f2__event_stream__new(f2ptr cause) {
  return raw__event_stream__new(cause);
}
export_cefunk0(event_stream__new, 0, "Returns a new event_stream object.");


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


f2ptr raw__event_stream__size(f2ptr cause, f2ptr this) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  return f2__redblacktree__size(cause, event_time_redblacktree);
}

f2ptr f2__event_stream__size(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__size(cause, this);
}
export_cefunk1(event_stream__size, this, 0, "Returns the number of events in the event_stream.");


f2ptr raw__event_stream__first(f2ptr cause, f2ptr this) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr event                   = raw__redblacktree__minimum(cause, event_time_redblacktree);
  return event;
}

f2ptr f2__event_stream__first(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__first(cause, this);
}
export_cefunk1(event_stream__first, this, 0, "Returns the first event in the event_stream.");


f2ptr raw__event_stream__last(f2ptr cause, f2ptr this) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr event                   = raw__redblacktree__maximum(cause, event_time_redblacktree);
  return event;
}

f2ptr f2__event_stream__last(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__last(cause, this);
}
export_cefunk1(event_stream__last, this, 0, "Returns the last event in the event_stream.");


f2ptr raw__event_stream__first_not_before(f2ptr cause, f2ptr this, f2ptr time) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr event                   = raw__redblacktree__minimum_not_less_than(cause, event_time_redblacktree, time);
  return event;
}

f2ptr f2__event_stream__first_not_before(f2ptr cause, f2ptr this, f2ptr time) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__time__is_type(cause, time))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__first_not_before(cause, this, time);
}
export_cefunk2(event_stream__first_not_before, this, time, 0, "Returns the first event that is not before the given time in the event_stream.");


f2ptr raw__event_stream__last_not_after_or_at(f2ptr cause, f2ptr this, f2ptr time) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr event                   = raw__redblacktree__maximum_not_greater_than_or_equal_to(cause, event_time_redblacktree, time);
  return event;
}

f2ptr f2__event_stream__last_not_after_or_at(f2ptr cause, f2ptr this, f2ptr time) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__time__is_type(cause, time))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__last_not_after_or_at(cause, this, time);
}
export_cefunk2(event_stream__last_not_after_or_at, this, time, 0, "Returns the first event that is not before the given time in the event_stream.");


f2ptr raw__event_stream__new__iterator(f2ptr cause, f2ptr this) {
  f2ptr first_event       = raw__event_stream__first(cause, this);
  f2ptr first_event__time;
  if (first_event != nil) {
    first_event__time = raw__event_stream_event__time(cause, first_event);
  } else {
    first_event__time = nil;
  }
  f2ptr iterator = f2__event_stream_iterator__new(cause, this, first_event__time);
  return iterator;
}

f2ptr f2__event_stream__new__iterator(f2ptr cause, f2ptr this) {
  if (! raw__event_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__new__iterator(cause, this);
}
export_cefunk1(event_stream__new__iterator, this, 0, "Returns a new event_stream_iterator set to point to the first event in the stream.");



// event_stream lick funks

f2ptr raw__event_stream__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr head                    = f2__redblacktree__head(cause, event_time_redblacktree);
  f2ptr result                  = raw__lick__object__gather_lick_notes(cause, lick, head, note_object_hash, max_size);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return nil;
}

f2ptr f2__event_stream__gather_lick_notes(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__gather_lick_notes(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(event_stream__gather_lick_notes, this, lick, note_object_hash, max_size, 0, "Licks this event_stream.");


f2ptr raw__event_stream__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr chunk                   = raw__chunk__new(cause, 8);
  f2ptr head                    = f2__redblacktree__head(cause, event_time_redblacktree);
  f2ptr head__note              = raw__ptypehash__lookup(cause, note_object_hash, head);
  s64   head__note__i           = f2integer__i(head__note, cause);
  raw__chunk__bit64__elt__set(cause, chunk, 0, (s64)head__note__i);
  f2ptr lick_note = raw__ptypehash__lookup(cause, note_object_hash, this);
  return raw__lick_chunk__new(cause, f2__object__type(cause, this), lick_note, chunk);
}

f2ptr f2__event_stream__lick_to_chunk(f2ptr cause, f2ptr this, f2ptr lick, f2ptr note_object_hash, f2ptr max_size) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__lick__is_type(cause, lick)) ||
      (! raw__ptypehash__is_type(cause, note_object_hash)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__lick_to_chunk(cause, this, lick, note_object_hash, max_size);
}
export_cefunk4(event_stream__lick_to_chunk, this, lick, note_object_hash, max_size, 0, "Licks this event_stream.");


f2ptr raw__event_stream__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr chunk         = raw__lick_chunk__chunk(cause, lick_chunk);
  s64   chunk__length = raw__chunk__length(cause, chunk);
  if (chunk__length != 8) {
    return f2larva__new(cause, 32558, nil);
  }
  f2ptr event_stream            = f2__event_stream__new(cause);
  f2ptr head__lick_note         = f2integer__new(cause, raw__chunk__bit64__elt(cause, chunk, 0));
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, event_stream);
  f2__redblacktree__head__set(cause, event_time_redblacktree, head__lick_note);
  return event_stream;
}

f2ptr f2__event_stream__lick_chunk__unlick_with_notes(f2ptr cause, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__lick_chunk__unlick_with_notes(cause, lick_chunk, object_note_hash);
}
export_cefunk2(event_stream__lick_chunk__unlick_with_notes, lick_chunk, object_note_hash, 0, "Unlicks this event_stream lick_chunk with notes.");


f2ptr raw__event_stream__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  f2ptr event_time_redblacktree = raw__event_stream__event_time_redblacktree(cause, this);
  f2ptr head__lick_note         = f2__redblacktree__head(cause, event_time_redblacktree);
  f2ptr head__object            = raw__ptypehash__lookup(cause, object_note_hash, head__lick_note);
  f2__redblacktree__head__set(cause, event_time_redblacktree, head__object);
  return nil;
}

f2ptr f2__event_stream__lick_chunk__unlick_replace_notes_with_objects(f2ptr cause, f2ptr this, f2ptr lick_chunk, f2ptr object_note_hash) {
  if ((! raw__event_stream__is_type(cause, this)) ||
      (! raw__lick_chunk__is_type(cause, lick_chunk)) ||
      (! raw__ptypehash__is_type(cause, object_note_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream__lick_chunk__unlick_replace_notes_with_objects(cause, this, lick_chunk, object_note_hash);
}
export_cefunk3(event_stream__lick_chunk__unlick_replace_notes_with_objects, this, lick_chunk, object_note_hash, 0, "Unlicks this event_stream with notes.");


f2ptr f2__event_stream_type__new_aux(f2ptr cause) {
  f2ptr this = f2__event_stream_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__add")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "remove"),                                       f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "size"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__size")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "first"),                                        f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__first")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "last"),                                         f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__last")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "first_not_before"),                             f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__first_not_before")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "last_not_after_or_at"),                         f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__last_not_after_or_at")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "new-iterator"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__new__iterator")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lick_to_chunk"),                                f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__lick_to_chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lick_chunk-unlick_with_notes"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__lick_chunk__unlick_with_notes")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "lick_chunk-unlick_replace_notes_with_objects"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__lick_chunk__unlick_replace_notes_with_objects")));}
  return this;
}



// event_stream_iterator

def_ceframe2(event_stream, event_stream_iterator, event_stream, index_time);

f2ptr raw__event_stream_iterator__new(f2ptr cause, f2ptr event_stream, f2ptr index_time) {
  return f2event_stream_iterator__new(cause, event_stream, index_time);
}

f2ptr f2__event_stream_iterator__new(f2ptr cause, f2ptr event_stream, f2ptr index_time) {
  if ((! raw__event_stream__is_type(cause, event_stream)) ||
      ((index_time != nil) && (! raw__time__is_type(cause, index_time)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__new(cause, event_stream, index_time);
}
export_cefunk2(event_stream_iterator__new, event_stream, index_time, 0, "Returns a new event_stream_iterator object.");


f2ptr raw__event_stream_iterator__current(f2ptr cause, f2ptr this) {
  f2ptr event_stream = raw__event_stream_iterator__event_stream(cause, this);
  f2ptr index_time   = raw__event_stream_iterator__index_time(cause, this);
  return raw__event_stream__first_not_before(cause, event_stream, index_time);
}

f2ptr f2__event_stream_iterator__current(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_iterator__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__current(cause, this);
}
export_cefunk1(event_stream_iterator__current, event_stream, 0, "Returns the current event referenced by the event_stream_iterator.");


f2ptr raw__event_stream_iterator__next(f2ptr cause, f2ptr this) {
  f2ptr event_stream              = raw__event_stream_iterator__event_stream(cause, this);
  f2ptr index_time                = raw__event_stream_iterator__index_time(cause, this);
  f2ptr nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, index_time);
  f2ptr nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
  f2ptr slightly_greater_time     = f2__time__new(cause, f2integer__new(cause, nanoseconds_since_1970__i + 1));
  f2ptr next_event                = raw__event_stream__first_not_before(cause, event_stream, slightly_greater_time);
  return next_event;
}

f2ptr f2__event_stream_iterator__next(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_iterator__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__next(cause, this);
}
export_cefunk1(event_stream_iterator__next, event_stream, 0, "Returns the next event from this event_stream_iterator if one exists, nil otherwise.");


f2ptr raw__event_stream_iterator__has__next(f2ptr cause, f2ptr this) {
  f2ptr event_stream              = raw__event_stream_iterator__event_stream(cause, this);
  f2ptr index_time                = raw__event_stream_iterator__index_time(cause, this);
  f2ptr nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, index_time);
  f2ptr nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
  f2ptr slightly_greater_time     = f2__time__new(cause, f2integer__new(cause, nanoseconds_since_1970__i + 1));
  f2ptr next_event                = raw__event_stream__first_not_before(cause, event_stream, slightly_greater_time);
  return f2bool__new(next_event != nil);
}

f2ptr f2__event_stream_iterator__has__next(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_iterator__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__has__next(cause, this);
}
export_cefunk1(event_stream_iterator__has__next, event_stream, 0, "Returns true if this event_stream_iterator has a next event, false otherwise.");


f2ptr raw__event_stream_iterator__increment(f2ptr cause, f2ptr this) {
  f2ptr current_event = raw__event_stream_iterator__current(cause, this);
  if (current_event == nil) {
    return f2bool__new(boolean__false);
  }
  f2ptr time                      = raw__event_stream_event__time(cause, current_event);
  f2ptr nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, time);
  f2ptr nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
  f2ptr slightly_greater_time     = f2__time__new(cause, f2integer__new(cause, nanoseconds_since_1970__i + 1));
  raw__event_stream_iterator__index_time__set(cause, this, slightly_greater_time);
  return f2bool__new(boolean__true);
}

f2ptr f2__event_stream_iterator__increment(f2ptr cause, f2ptr this) {
  if (! raw__event_stream_iterator__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__increment(cause, this);
}
export_cefunk1(event_stream_iterator__increment, event_stream, 0, "Increments the event_stream_iterator, and returns true if successful, otherwise returns false.");


f2ptr raw__event_stream_iterator__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    raw__frame__copy(cause, frame, this);
    raw__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), f2__object__type(cause, this));
    raw__frame__add_var_value(cause, frame, new__symbol(cause, "event_stream"),      raw__event_stream_iterator__event_stream(cause, this));
    raw__frame__add_var_value(cause, frame, new__symbol(cause, "index_time"),        raw__event_stream_iterator__index_time(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__event_stream_iterator__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__event_stream_iterator__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__event_stream_iterator__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(event_stream_iterator__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__event_stream_iterator_type__new_aux(f2ptr cause) {
  f2ptr this = f2__event_stream_iterator_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "current"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_iterator__current")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "increment"),                 f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_iterator__increment")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "next"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_iterator__next")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "has-next"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_iterator__has__next")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream_iterator__terminal_print_with_frame")));}
  return this;
}



// **

f2ptr f2__event_stream__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(event_stream__core_extension_ping, 0, "");

f2ptr f2__event_stream__core_extension_initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "lick"), new__symbol(cause, "lick__core_extension_ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "event_stream_event"),    f2__event_stream_event_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "event_stream"),          f2__event_stream_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "event_stream_iterator"), f2__event_stream_iterator_type__new_aux(cause));
  status("event_stream initialized.");
  return nil;
}
export_cefunk0(event_stream__core_extension_initialize, 0, "");

f2ptr f2__event_stream__core_extension_destroy(f2ptr cause) {
  status("event_stream destroyed.");
  return nil;
}
export_cefunk0(event_stream__core_extension_destroy, 0, "");


