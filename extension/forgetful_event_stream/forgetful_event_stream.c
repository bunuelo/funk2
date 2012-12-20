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

#include "forgetful_event_stream.h"

def_ceframe1(forgetful_event_stream, forgetful_event_stream, important_iterator_set);

f2ptr raw__forgetful_event_stream__new(f2ptr cause) {
  f2ptr this = f2__event_stream__new(cause);
  f2ptr important_iterator_set = f2__set__new(cause, nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),                   new__symbol(cause, "forgetful_event_stream"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "important_iterator_set"), important_iterator_set);
  return this;
}

f2ptr f2__forgetful_event_stream__new(f2ptr cause) {
  return raw__forgetful_event_stream__new(cause);
}
export_cefunk0(forgetful_event_stream__new, 0, "Returns a new forgetful_event_stream object.");


f2ptr raw__forgetful_event_stream__add(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  {
    f2ptr result = f2__event_stream__add(cause, this, event_stream_event);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  boolean_t keep_all_events                                   = boolean__false;
  f2ptr     important_iterator_set                            = raw__forgetful_event_stream__important_iterator_set(cause, this);
  f2ptr     minimum_important_index_time                      = nil;
  s64       minimum_important_index_nanoseconds_since_1970__i = 0;
  set__iteration(cause, important_iterator_set, important_iterator,
		 f2ptr index_time = f2__event_stream_iterator__index_time(cause, important_iterator);
		 if (raw__larva__is_type(cause, index_time)) {
		   return index_time;
		 }
		 if (index_time == nil) {
		   keep_all_events = boolean__true;
		 } else {
		   if (! raw__time__is_type(cause, index_time)) {
		     return f2larva__new(cause, 1355151, nil);
		   }
		   f2ptr index_time__nanoseconds_since_1970    = f2time__nanoseconds_since_1970(index_time, cause);
		   s64   index_time__nanoseconds_since_1970__i = f2integer__i(index_time__nanoseconds_since_1970, cause);
		   if ((minimum_important_index_time == nil) ||
		       (index_time__nanoseconds_since_1970__i < minimum_important_index_nanoseconds_since_1970__i)) {
		     minimum_important_index_time                      = index_time;
		     minimum_important_index_nanoseconds_since_1970__i = index_time__nanoseconds_since_1970__i;
		   }
		 }
		 );
  if (! keep_all_events) {
    if (minimum_important_index_time != nil) {
      f2ptr result = f2__event_stream__remove_all_before_time(cause, this, minimum_important_index_time);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else {
      f2ptr result = f2__event_stream__remove_all(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}

f2ptr f2__forgetful_event_stream__add(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  assert_argument_type(forgetful_event_stream, this);
  assert_argument_type(event_stream_event,     event_stream_event);
  return raw__forgetful_event_stream__add(cause, this, event_stream_event);
}
export_cefunk2(forgetful_event_stream__add, this, event_stream_event, 0,
	       "Adds an event_stream_event to a forgetful_event_stream iterator.\n"
	       "Warning: The event will be forgotten if there is not an important iterator that still has to iterate through this event.");


f2ptr raw__forgetful_event_stream__remove(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  return raw__event_stream__remove(cause, this, event_stream_event);
}

f2ptr f2__forgetful_event_stream__remove(f2ptr cause, f2ptr this, f2ptr event_stream_event) {
  assert_argument_type(forgetful_event_stream, this);
  assert_argument_type(event_stream_event,     event_stream_event);
  return raw__forgetful_event_stream__remove(cause, this, event_stream_event);
}
export_cefunk2(forgetful_event_stream__remove, this, event_stream_event, 0,
	       "Removes an event_stream_event from a forgetful_event_stream iterator.");


void raw__forgetful_event_stream__add_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator) {
  f2ptr important_iterator_set = raw__forgetful_event_stream__important_iterator_set(cause, this);
  raw__set__add(cause, important_iterator_set, iterator);
}

f2ptr f2__forgetful_event_stream__add_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator) {
  assert_argument_type(forgetful_event_stream, this);
  assert_argument_type(event_stream_iterator,  iterator);
  raw__forgetful_event_stream__add_important_iterator(cause, this, iterator);
  return nil;
}
export_cefunk2(forgetful_event_stream__add_important_iterator, this, iterator, 0,
	       "Adds an important event_stream_iterator to this forgetful_event_stream.");


void raw__forgetful_event_stream__remove_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator) {
  f2ptr important_iterator_set = raw__forgetful_event_stream__important_iterator_set(cause, this);
  raw__set__remove(cause, important_iterator_set, iterator);
}

f2ptr f2__forgetful_event_stream__remove_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator) {
  assert_argument_type(forgetful_event_stream, this);
  assert_argument_type(event_stream_iterator,  iterator);
  raw__forgetful_event_stream__remove_important_iterator(cause, this, iterator);
  return nil;
}
export_cefunk2(forgetful_event_stream__remove_important_iterator, this, iterator, 0,
	       "Removes an important event_stream_iterator from this forgetful_event_stream.");


f2ptr f2__forgetful_event_stream_type__new_aux(f2ptr cause) {
  f2ptr this = f2__forgetful_event_stream_type__new(cause);
  f2__primobject_type__parents__set(cause, this, f2list1__new(cause, new__symbol(cause, "event_stream")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_event_stream"), new__symbol(cause, "forgetful_event_stream__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove"),                    f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_event_stream"), new__symbol(cause, "forgetful_event_stream__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_important_iterator"),    f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_event_stream"), new__symbol(cause, "forgetful_event_stream__add_important_iterator")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_important_iterator"), f2__core_extension_funk__new(cause, new__symbol(cause, "forgetful_event_stream"), new__symbol(cause, "forgetful_event_stream__remove_important_iterator")));}
  return this;
}



// **

f2ptr f2__forgetful_event_stream__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__ping, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("forgetful_event_stream initialized.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__initialize, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "forgetful_event_stream"), f2__forgetful_event_stream_type__new_aux(cause));
  status("forgetful_event_stream types defined.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__define_types, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__destroy(f2ptr cause) {
  status("forgetful_event_stream destroyed.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__destroy, 0, "");


