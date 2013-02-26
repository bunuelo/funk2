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

#ifndef F2__ARRAY__H
#define F2__ARRAY__H

// array

boolean_t raw__cause_is_traced(f2ptr cause);
f2ptr     raw__array__new(f2ptr cause, u64 length);
f2ptr     raw__array__new_copy(f2ptr cause, u64 length, f2ptr init);
f2ptr      f2__array__new(f2ptr cause, f2ptr lengths);
f2ptr     raw__array__new_multidimensional(f2ptr cause, f2ptr lengths);
f2ptr      f2__array__new_multidimensional(f2ptr cause, f2ptr lengths);
boolean_t raw__array__is_type(f2ptr cause, f2ptr x);
f2ptr      f2__array__is_type(f2ptr cause, f2ptr x);
u64       raw__array__length(f2ptr cause, f2ptr x);
f2ptr      f2__array__length(f2ptr cause, f2ptr x);
f2ptr     raw__array__elt__trace_depth(f2ptr cause, f2ptr this, u64 index, int trace_depth);
f2ptr     raw__array__elt(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr      f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr     raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
f2ptr     raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr      f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr     raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr      f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr     raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr      f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr     raw__array__elt__mutate_funks(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt__mutate_funks(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr      f2__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr     raw__array__elt__read_funks(f2ptr cause, f2ptr this, u64 index);
f2ptr      f2__array__elt__read_funks(f2ptr cause, f2ptr this, f2ptr index);
f2ptr     raw__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr      f2__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);

boolean_t raw__array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr      f2__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr     raw__array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr     raw__array__as__conslist(f2ptr cause, f2ptr this);
f2ptr      f2__array__as__conslist(f2ptr cause, f2ptr this);
f2ptr     raw__array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2array__primobject_type__new(f2ptr cause);

// array

typedef struct funk2_object_type__array__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr elt__set__symbol;
  f2ptr elt__set__funk;
  f2ptr elt__tracing_on__symbol;
  f2ptr elt__tracing_on__funk;
  f2ptr elt__tracing_on__set__symbol;
  f2ptr elt__tracing_on__set__funk;
  f2ptr elt__trace__symbol;
  f2ptr elt__trace__funk;
  f2ptr elt__trace__set__symbol;
  f2ptr elt__trace__set__funk;
  f2ptr elt__imagination_frame__symbol;
  f2ptr elt__imagination_frame__funk;
  f2ptr elt__imagination_frame__set__symbol;
  f2ptr elt__imagination_frame__set__funk;
  f2ptr elt__mutate_funks__symbol;
  f2ptr elt__mutate_funks__funk;
  f2ptr elt__mutate_funks__set__symbol;
  f2ptr elt__mutate_funks__set__funk;
  f2ptr elt__read_funks__symbol;
  f2ptr elt__read_funks__funk;
  f2ptr elt__read_funks__set__symbol;
  f2ptr elt__read_funks__set__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__array__slot_t;

// **

void f2__array__initialize();

#endif // F2__ARRAY__H

