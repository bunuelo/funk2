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

#ifndef F2__PRIMOBJECT__LARGEINTEGER__TYPES__H
#define F2__PRIMOBJECT__LARGEINTEGER__TYPES__H

// largeinteger

typedef struct funk2_object_type__largeinteger__slot_s funk2_object_type__largeinteger__slot_t;
declare_object_type_2_slot(largeinteger, is_negative, integer_array,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__LARGEINTEGER__TYPES__H

#ifndef F2__PRIMOBJECT__LARGEINTEGER__H
#define F2__PRIMOBJECT__LARGEINTEGER__H

#include "f2_primobjects.h"

// u64

u64 u64__bitshift_left(u64 this, s64 bit_distance);
u64 u64__bitshift_right(u64 this, s64 bit_distance);
u64 u64__multiply(u64 this, u64 that, u64* overflow);

// s64

boolean_t s64__multiply_overflows(s64 this, s64 that);


// largeinteger__unsigned_array  (not a real type, just an array filled with integers)

f2ptr     raw__largeinteger__unsigned_array__new(f2ptr cause, u64 value);
boolean_t raw__largeinteger__unsigned_array__less_than(f2ptr cause, f2ptr this, f2ptr that);
boolean_t raw__largeinteger__unsigned_array__greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__unsigned_array__add(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__unsigned_array__subtract_smaller(f2ptr cause, f2ptr this, f2ptr smaller);
f2ptr     raw__largeinteger__unsigned_array__bitshift_left_only(f2ptr cause, f2ptr this, u64 bit_distance);
f2ptr     raw__largeinteger__unsigned_array__bitshift_right_only(f2ptr cause, f2ptr this, u64 bit_distance);
f2ptr     raw__largeinteger__unsigned_array__bitshift_left(f2ptr cause, f2ptr this, s64 bit_distance);
f2ptr     raw__largeinteger__unsigned_array__bitshift_right(f2ptr cause, f2ptr this, s64 bit_distance);
f2ptr     raw__largeinteger__unsigned_array__multiply(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__unsigned_array__divide_n_plus_one_by_n__that_high_bit_assumed(f2ptr cause, f2ptr this, f2ptr that, f2ptr* remainder);
f2ptr     raw__largeinteger__unsigned_array__divide(f2ptr cause, f2ptr this, f2ptr that, f2ptr* remainder);


// largeinteger

declare_primobject_2_slot(largeinteger, is_negative, integer_array);

f2ptr     raw__largeinteger__new_from_s64(f2ptr cause, s64 value);
f2ptr      f2__largeinteger__new(f2ptr cause, f2ptr value);
boolean_t raw__largeinteger__less_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__less_than(f2ptr cause, f2ptr this, f2ptr that);
boolean_t raw__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__negative(f2ptr cause, f2ptr this);
f2ptr      f2__largeinteger__negative(f2ptr cause, f2ptr this);
f2ptr     raw__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__bitshift_left(f2ptr cause, f2ptr this, s64 bit_distance);
f2ptr      f2__largeinteger__bitshift_left(f2ptr cause, f2ptr this, f2ptr bit_distance);
f2ptr     raw__largeinteger__bitshift_right(f2ptr cause, f2ptr this, f2ptr bit_distance);
f2ptr      f2__largeinteger__bitshift_right(f2ptr cause, f2ptr this, f2ptr bit_distance);
f2ptr     raw__largeinteger__multiply_largeinteger(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__multiply_largeinteger(f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__print(f2ptr cause, f2ptr this);
double    raw__largeinteger__as__double(f2ptr cause, f2ptr this);
boolean_t raw__largeinteger__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__largeinteger__equals(f2ptr cause, f2ptr this, f2ptr that);
u64       raw__largeinteger__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__largeinteger__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr     raw__largeinteger__square_root(f2ptr cause, f2ptr this);
f2ptr      f2__largeinteger__square_root(f2ptr cause, f2ptr this);
f2ptr      f2__largeinteger__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__divided_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__plus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__minus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__is_greater_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__is_less_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr      f2__largeinteger__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);

f2ptr f2largeinteger__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject_largeinteger__reinitialize_globalvars();
void f2__primobject_largeinteger__initialize();

#endif // F2__PRIMOBJECT__LARGEINTEGER__H

