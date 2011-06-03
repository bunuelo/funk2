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

#include "semantic_event_tree.h"

// semantic_event_tree__semantic_event

f2ptr raw__semantic_event_tree__semantic_event__left_value(f2ptr cause, f2ptr this) {
  return f2__object__semantic__get(cause, this, new__symbol(cause, "absolute_start_time"), nil);
}

f2ptr f2__semantic_event_tree__semantic_event__left_value(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event_tree__semantic_event__left_value(cause, this);
}
export_cefunk1(semantic_event_tree__semantic_event__left_value, this, 0, "Returns the left_value for this semantic_event_tree-semantic_event.");


f2ptr raw__semantic_event_tree__semantic_event__right_value(f2ptr cause, f2ptr this) {
  return f2__object__semantic__get(cause, this, new__symbol(cause, "absolute_end_time"), nil);
}

f2ptr f2__semantic_event_tree__semantic_event__right_value(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event_tree__semantic_event__right_value(cause, this);
}
export_cefunk1(semantic_event_tree__semantic_event__right_value, this, 0, "Returns the right_value for this semantic_event_tree-semantic_event.");


f2ptr raw__semantic_event_tree__semantic_event__value_equality(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_time__is_numerically_equal_to(cause, this, that);
}

f2ptr f2__semantic_event_tree__semantic_event__value_equality(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_event_tree__semantic_event__value_equality(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_equality, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is equal to another semantic_event_tree-semantic_event value.");


f2ptr raw__semantic_event_tree__semantic_event__value_comparison(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_time__is_less_than(cause, this, that);
}

f2ptr f2__semantic_event_tree__semantic_event__value_comparison(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_event_tree__semantic_event__value_comparison(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_comparison, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is less than another semantic_event_tree-semantic_event value.");


f2ptr raw__semantic_event_tree__semantic_event__value_center(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr     this__value          = f2__semantic_time__value(cause, this);
  f2ptr     that__value          = f2__semantic_time__value(cause, that);
  boolean_t this__value__is__now = raw__eq(cause, new__symbol(cause, "now"), this__value);
  boolean_t that__value__is__now = raw__eq(cause, new__symbol(cause, "now"), that__value);
  if (this__value__is__now && that__value__is__now) {
    return f2__semantic_time__new(cause, f2__time(cause));
  }
  if (this__value__is__now) {
    this__value = f2__time(cause);
  }
  if (that__value__is__now) {
    that__value = f2__time(cause);
  }
  boolean_t this__value__is__time = raw__time__is_type(cause, this__value);
  boolean_t that__value__is__time = raw__time__is_type(cause, that__value);
  if ((! this__value__is__time) && (! this__value__is__time)) {
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
	return f2__semantic_time__new(cause, new__symbol(cause, "before"));
      } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
	return f2__semantic_time__new(cause, f2__time(cause));
      } else {
	return f2larva__new(cause, 24626, nil);
      }
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
	return f2__semantic_time__new(cause, f2__time(cause));
      } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
	return f2__semantic_time__new(cause, new__symbol(cause, "after"));
      } else {
	return f2larva__new(cause, 24626, nil);
      }
    } else {
      return f2larva__new(cause, 24626, nil);
    }
  } else if (! this__value__is__time) {
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      return f2__semantic_time__new(cause, new__symbol(cause, "before"));
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      return f2__semantic_time__new(cause, new__symbol(cause, "after"));
    } else {
      return f2larva__new(cause, 24626, nil);
    }
  } else if (! that__value__is__time) {
    if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
      return f2__semantic_time__new(cause, new__symbol(cause, "before"));
    } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
      return f2__semantic_time__new(cause, new__symbol(cause, "after"));
    } else {
      return f2larva__new(cause, 24626, nil);
    }
  } else {
    f2ptr this__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
    s64   this__value__nanoseconds_since_1970__i = f2integer__i(this__value__nanoseconds_since_1970, cause);
    f2ptr that__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that);
    s64   that__value__nanoseconds_since_1970__i = f2integer__i(that__value__nanoseconds_since_1970, cause);
    return f2__semantic_time__new(cause, f2time__new(cause, f2integer__new(cause, (this__value__nanoseconds_since_1970__i + that__value__nanoseconds_since_1970__i) >> 1)));
  }
}

f2ptr f2__semantic_event_tree__semantic_event__value_center(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_event_tree__semantic_event__value_center(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_center, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is less than another semantic_event_tree-semantic_event value.");


// semantic_event_tree

def_ceframe1(semantic_event_tree, semantic_event_tree, interval_tree);

f2ptr raw__semantic_event_tree__new(f2ptr cause) {
  f2ptr interval_tree = f2__interval_tree__new(cause,
					       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__semantic_event__left_value")),
					       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__semantic_event__right_value")),
					       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__semantic_event__value_equality")),
					       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__semantic_event__value_comparison")),
					       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__semantic_event__value_center")));
  return f2semantic_event_tree__new(cause, interval_tree);
}

f2ptr f2__semantic_event_tree__new(f2ptr cause) {
  return raw__semantic_event_tree__new(cause);
}
export_cefunk0(semantic_event_tree__new, 0, "Returns a new semantic_event_tree object.");


f2ptr raw__semantic_event_tree__insert(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr interval_tree = f2__semantic_event_tree__interval_tree(cause, this);
  return f2__interval_tree__insert(cause, interval_tree, semantic_event);
}

f2ptr f2__semantic_event_tree__insert(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  assert_argument_type(semantic_event, semantic_event);
  return raw__semantic_event_tree__insert(cause, this, semantic_event);
}
export_cefunk2(semantic_event_tree__insert, this, semantic_event, 0, "Inserts a semantic_event into this semantic_event_tree.");


f2ptr raw__semantic_event_tree__remove(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr interval_tree = f2__semantic_event_tree__interval_tree(cause, this);
  return f2__interval_tree__remove(cause, interval_tree, semantic_event);
}

f2ptr f2__semantic_event_tree__remove(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  assert_argument_type(semantic_event, semantic_event);
  return raw__semantic_event_tree__remove(cause, this, semantic_event);
}
export_cefunk2(semantic_event_tree__remove, this, semantic_event, 0, "Removes a semantic_event from this semantic_event_tree.");


f2ptr raw__semantic_event_tree__events_containing_time(f2ptr cause, f2ptr this, f2ptr time) {
  f2ptr interval_tree = f2__semantic_event_tree__interval_tree(cause, this);
  return f2__interval_tree__intervals_containing_value(cause, interval_tree, time);
}

f2ptr f2__semantic_event_tree__events_containing_time(f2ptr cause, f2ptr this, f2ptr time) {
  assert_argument_type(semantic_time, time);
  return raw__semantic_event_tree__events_containing_time(cause, this, time);
}
export_cefunk2(semantic_event_tree__events_containing_time, this, time, 0, "Returns a new set of events in this semantic_event_tree that contain the given time.");


f2ptr raw__semantic_event_tree__events_overlapping_event(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr interval_tree = f2__semantic_event_tree__interval_tree(cause, this);
  return f2__interval_tree__intervals_overlapping_interval(cause, interval_tree, semantic_event);
}

f2ptr f2__semantic_event_tree__events_overlapping_event(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  assert_argument_type(semantic_event, semantic_event);
  return raw__semantic_event_tree__events_overlapping_event(cause, this, semantic_event);
}
export_cefunk2(semantic_event_tree__events_overlapping_event, this, semantic_event, 0, "Returns a new set of events in this semantic_event_tree that overlap the given event.");


f2ptr f2__semantic_event_tree_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_event_tree_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__insert")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events_containing_time"),   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__events_containing_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "events_overlapping_event"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_tree"), new__symbol(cause, "semantic_event_tree__events_overlapping_event")));}
  return this;
}



// **

f2ptr f2__semantic_event_tree__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__ping, 0, "");

f2ptr f2__semantic_event_tree__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_event_tree, semantic_event);
  status("semantic_event_tree initialized.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__initialize, 0, "");

f2ptr f2__semantic_event_tree__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_event_tree"), f2__semantic_event_tree_type__new_aux(cause));
  status("semantic_event_tree define types.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__define_types, 0, "");

f2ptr f2__semantic_event_tree__core_extension__destroy(f2ptr cause) {
  status("semantic_event_tree destroyed.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__destroy, 0, "");


