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
  f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  f2ptr that__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  return f2bool__new(this__nanoseconds_since_1970__i == that__nanoseconds_since_1970__i);
}

f2ptr f2__semantic_event_tree__semantic_event__value_equality(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return raw__semantic_event_tree__semantic_event__value_equality(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_equality, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is equal to another semantic_event_tree-semantic_event value.");


f2ptr raw__semantic_event_tree__semantic_event__value_comparison(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  f2ptr that__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  return f2bool__new(this__nanoseconds_since_1970__i < that__nanoseconds_since_1970__i);
}

f2ptr f2__semantic_event_tree__semantic_event__value_comparison(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return raw__semantic_event_tree__semantic_event__value_comparison(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_comparison, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is less than another semantic_event_tree-semantic_event value.");


f2ptr raw__semantic_event_tree__semantic_event__value_center(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this);
  s64   this__nanoseconds_since_1970__i = f2integer__i(this__nanoseconds_since_1970, cause);
  f2ptr that__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that);
  s64   that__nanoseconds_since_1970__i = f2integer__i(that__nanoseconds_since_1970, cause);
  return f2time__new(cause, f2integer__new(cause, (this__nanoseconds_since_1970__i + that__nanoseconds_since_1970__i) >> 1));
}

f2ptr f2__semantic_event_tree__semantic_event__value_center(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(time, this);
  assert_argument_type(time, that);
  return raw__semantic_event_tree__semantic_event__value_center(cause, this, that);
}
export_cefunk2(semantic_event_tree__semantic_event__value_comparison, this, that, 0, "Returns whether a semantic_event_tree-semantic_event value is less than another semantic_event_tree-semantic_event value.");


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


f2ptr f2__semantic_event_tree_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_event_tree_type__new(cause);
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
  f2__add_type(cause, new__symbol(cause, "semantic_event_tree"), f2__semantic_event_tree_type__new(cause));
  status("semantic_event_tree define types.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__define_types, 0, "");

f2ptr f2__semantic_event_tree__core_extension__destroy(f2ptr cause) {
  status("semantic_event_tree destroyed.");
  return nil;
}
export_cefunk0(semantic_event_tree__core_extension__destroy, 0, "");


