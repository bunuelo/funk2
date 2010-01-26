// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#include "funk2.h"

// u64

u64 u64__bitshift_left(u64 this, s64 bit_distance) {
  if ((bit_distance >= 64) ||
      (bit_distance <= -64)) {
    return 0;
  }
  return (this << bit_distance);
}

u64 u64__bitshift_right(u64 this, s64 bit_distance) {
  if ((bit_distance >= 64) ||
      (bit_distance <= -64)) {
    return 0;
  }
  return (this >> bit_distance);
}

u64 u64__multiply(u64 this, u64 that, u64* overflow) {
  u64 temp__00 = ((u64)(this & 0xffffffff)) * ((u64)(that & 0xffffffff));
  u64 temp__01 = ((u64)(this & 0xffffffff)) * ((u64)(that >> 32));
  u64 temp__10 = ((u64)(this >> 32))        * ((u64)(that & 0xffffffff));
  u64 temp__11 = ((u64)(this >> 32))        * ((u64)(that >> 32));
  u64 result = temp__00 + ((temp__01 + temp__10) << 32);
  *overflow = ((temp__01 + temp__10) >> 32) + temp__11;
  return result;
}


// largeinteger__unsigned_array  (not a real type, just an array filled with integers)

f2ptr raw__largeinteger__unsigned_array__new(f2ptr cause, u64 value) {
  if (value == 0) {
    return raw__array__new(cause, 0);
  }
  f2ptr integer_array = raw__array__new(cause, 1);
  raw__array__elt__set(cause, integer_array, 0, f2integer__new(cause, value));
  return integer_array;
}

boolean_t raw__largeinteger__unsigned_array__less_than(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  if (this__length < that__length) {
    return boolean__true;
  }
  if (this__length > that__length) {
    return boolean__false;
  }
  // assert(this__length == that__length)
  s64 index;
  for (index = this__length - 1; index >= 0; index --) {
    f2ptr this__elt = raw__array__elt(cause, this, index);
    f2ptr that__elt = raw__array__elt(cause, that, index);
    u64 this__value = f2integer__i(this__elt, cause);
    u64 that__value = f2integer__i(that__elt, cause);
    if (this__value < that__value) {
      return boolean__true;
    }
    if (this__value > that__value) {
      return boolean__false;
    }
  }
  return boolean__false;
}

boolean_t raw__largeinteger__unsigned_array__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  if (this__length > that__length) {
    return boolean__true;
  }
  if (this__length < that__length) {
    return boolean__false;
  }
  // assert(this__length == that__length)
  s64 index;
  for (index = this__length - 1; index >= 0; index --) {
    f2ptr this__elt = raw__array__elt(cause, this, index);
    f2ptr that__elt = raw__array__elt(cause, that, index);
    u64 this__value = f2integer__i(this__elt, cause);
    u64 that__value = f2integer__i(that__elt, cause);
    if (this__value > that__value) {
      return boolean__true;
    }
    if (this__value < that__value) {
      return boolean__false;
    }
  }
  return boolean__false;
}

f2ptr raw__largeinteger__unsigned_array__add(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  f2ptr small;
  f2ptr large;
  u64   small__length;
  u64   large__length;
  if (this__length < that__length) {
    small = this;
    large = that;
    small__length = this__length;
    large__length = that__length;
  } else {
    small = that;
    large = this;
    small__length = that__length;
    large__length = this__length;
  }
  u64  result_array__length = large__length + 1;
  u64* result_array         = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  u64 last_nonzero_index = -1;
  u64 result__carry      = 0;
  u64 index;
  for (index = 0; index < result_array__length; index ++) {
    u64 small__value;
    if (index < small__length) {
      f2ptr small__elt = raw__array__elt(cause, small, index);
      small__value = (u64)f2integer__i(small__elt, cause);
    } else {
      small__value = 0;
    }
    u64 large__value;
    if (index < large__length) {
      f2ptr large__elt = raw__array__elt(cause, large, index);
      large__value = (u64)f2integer__i(large__elt, cause);
    } else {
      large__value = 0;
    }
    u64   result__value_without_carry = small__value                + large__value;
    u64   result__value               = result__value_without_carry + result__carry;
    if ((result__value_without_carry < small__value) ||
	(result__value_without_carry < large__value)) {
      result__carry = 1;
    } else {
      if ((result__value < result__value_without_carry) ||
	  (result__value < result__carry)) {
	result__carry = 1;
      } else {
	result__carry = 0;
      }
    }
    result_array[index] = result__value;
    if (result__value != 0) {
      last_nonzero_index = index;
    }
  }
  u64   new_array__length = last_nonzero_index + 1;
  f2ptr new_array         = raw__array__new(cause, new_array__length);
  for (index = 0; index < new_array__length; index ++) {
    raw__array__elt__set(cause, new_array, index, f2integer__new(cause, result_array[index]));
  }
  return new_array;
}

f2ptr raw__largeinteger__unsigned_array__subtract_smaller(f2ptr cause, f2ptr this, f2ptr smaller) {
  f2ptr large              = this;
  f2ptr small              = smaller;
  u64   large__length      = raw__array__length(cause, large);
  u64   small__length      = raw__array__length(cause, small);
  u64   borrow__value      = 0;
  u64   last_nonzero_index = -1;
  u64*  result_array       = alloca(sizeof(u64) * large__length);
  u64   index;
  for (index = 0; index < large__length; index ++) {
    u64 small__value = 0;
    if (index < small__length) {
      f2ptr small__elt = raw__array__elt(cause, small, index);
      small__value = (u64)f2integer__i(small__elt, cause);
    }
    f2ptr large__elt    = raw__array__elt(cause, large, index);
    u64   large__value  = f2integer__i(large__elt, cause);
    u64   result__value_without_borrow = large__value - small__value;
    u64   result__value                = result__value_without_borrow - borrow__value;
    if (result__value_without_borrow > large__value) {
      borrow__value = 1;
    } else {
      if (result__value > result__value_without_borrow) {
	borrow__value = 1;
      } else {
	borrow__value = 0;
      }
    }
    if (result__value != 0) {
      last_nonzero_index = index;
    }
    result_array[index] = result__value;
  }
  u64   new_array__length = last_nonzero_index + 1;
  f2ptr new_array         = raw__array__new(cause, new_array__length);
  for (index = 0; index < new_array__length; index ++) {
    raw__array__elt__set(cause, new_array, index, f2integer__new(cause, result_array[index]));
  }
  return new_array;
}

f2ptr raw__largeinteger__unsigned_array__bitshift_left_only(f2ptr cause, f2ptr this, u64 bit_distance) {
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return this;
  }
  u64  array__distance      = (bit_distance >> 6);
  u64  array__bit_distance  = bit_distance - (array__distance << 6);
  u64  result_array__length = this__length + array__distance + 1;
  u64* result_array         = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr elt         = raw__array__elt(cause, this, index);
      u64   value       = f2integer__i(elt, cause);
      u64   value_left  = u64__bitshift_right(value, 64 - array__bit_distance);
      u64   value_right = u64__bitshift_left( value, array__bit_distance);
      result_array[array__distance + index]     += value_right;
      result_array[array__distance + index + 1] += value_left;
    }
  }
  u64 max_nonzero_index;
  for (max_nonzero_index = result_array__length - 1; max_nonzero_index >= 0 && result_array[max_nonzero_index] == 0; max_nonzero_index --);
  u64   result__length = max_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__unsigned_array__bitshift_right_only(f2ptr cause, f2ptr this, u64 bit_distance) {
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return this;
  }
  u64  array__distance      = (bit_distance >> 6);
  u64  array__bit_distance  = bit_distance - (array__distance << 6);
  u64  result_array__length = this__length - array__distance;
  u64* result_array         = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  {
    u64 index;
    for (index = array__distance; index < this__length; index ++) {
      f2ptr elt         = raw__array__elt(cause, this, index);
      u64   value       = f2integer__i(elt, cause);
      u64   value_right = u64__bitshift_left( value, 64 - array__bit_distance);
      u64   value_left  = u64__bitshift_right(value, array__bit_distance);
      if (index - array__distance - 1 >= 0) {
	result_array[index - array__distance - 1] += value_right;
      }
      result_array[index - array__distance] += value_left;
    }
  }
  u64 max_nonzero_index;
  for (max_nonzero_index = result_array__length - 1; max_nonzero_index >= 0 && result_array[max_nonzero_index] == 0; max_nonzero_index --);
  u64   result__length = max_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__unsigned_array__bitshift_left(f2ptr cause, f2ptr this, s64 bit_distance) {
  if (bit_distance == 0) {
    return this;
  }
  if (bit_distance > 0) {
    return raw__largeinteger__unsigned_array__bitshift_left_only(cause, this, bit_distance);
  } else {
    return raw__largeinteger__unsigned_array__bitshift_right_only(cause, this, -bit_distance);
  }
}

f2ptr raw__largeinteger__unsigned_array__bitshift_right(f2ptr cause, f2ptr this, s64 bit_distance) {
  if (bit_distance == 0) {
    return this;
  }
  if (bit_distance > 0) {
    return raw__largeinteger__unsigned_array__bitshift_right_only(cause, this, bit_distance);
  } else {
    return raw__largeinteger__unsigned_array__bitshift_left_only(cause, this, -bit_distance);
  }
}

f2ptr raw__largeinteger__unsigned_array__mask_bitrange(f2ptr cause, f2ptr this, u64 low_bit_num, u64 high_bit_num) {
  u64   mask__length = ((high_bit_num - 1) >> 6) + 1;
  u64   this__length = raw__array__length(cause, this);
  u64   result_array__length;
  if (this__length < mask__length) {
    result_array__length = this__length;
  } else {
    result_array__length = mask__length;
  }
  u64* result_array = (u64*)alloca(sizeof(u64) * result_array__length);
  u64  zero_count   = (low_bit_num >> 6);
  {
    u64 index;
    for (index = 0; index < result_array__length; index ++) {
      f2ptr this__elt        = raw__array__elt(cause, this, index);
      u64   this__elt__value = f2integer__i(this__elt, cause);
      u64   value;
      if (index < zero_count) {
	value = 0;
      } else {
	value = this__elt__value;
	if (index == zero_count) {
	  value = value & u64__bitshift_left(0xffffffffffffffff, (low_bit_num - (zero_count << 6)));
	}
	if (index == mask__length - 1) {
	  value = value & u64__bitshift_right(0xffffffffffffffff, 63 - (high_bit_num - ((mask__length - 1) << 6)));
	}
      }
      result_array[index] = value;
    }
  }
  s64 last_nonzero_index;
  for (last_nonzero_index = result_array__length - 1; (last_nonzero_index >= 0) && (result_array[last_nonzero_index] == 0); last_nonzero_index --);
  u64   result__length = last_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

f2ptr raw__largeinteger__unsigned_array__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  u64  result_array__length = this__length + that__length;
  u64* result_array = (u64*)alloca(sizeof(u64) * result_array__length);
  memset(result_array, 0, sizeof(u64) * result_array__length);
  u64* this_array = (u64*)alloca(sizeof(u64) * this__length);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr elt = raw__array__elt(cause, this, index);
      this_array[index] = f2integer__i(elt, cause);
    }
  }
  u64* that_array = (u64*)alloca(sizeof(u64) * that__length);
  {
    u64 index;
    for (index = 0; index < that__length; index ++) {
      f2ptr elt = raw__array__elt(cause, that, index);
      that_array[index] = f2integer__i(elt, cause);
    }
  }
  {
    u64 this_index;
    u64 that_index;
    for (that_index = 0; that_index < that__length; that_index ++) {
      u64 that__value = that_array[that_index];
      for (this_index = 0; this_index < this__length; this_index ++) {
	u64 this__value = this_array[this_index];
	u64 overflow_value;
	u64 result_value = u64__multiply(this__value, that__value, &overflow_value);
	result_array[this_index + that_index]     += result_value;
	result_array[this_index + that_index + 1] += overflow_value;
      }
    }
  }
  s64 last_nonzero_index;
  for (last_nonzero_index = result_array__length - 1; last_nonzero_index >= 0 && result_array[last_nonzero_index] == 0; last_nonzero_index --);
  u64   result__length = last_nonzero_index + 1;
  f2ptr result         = raw__array__new(cause, result__length);
  {
    u64 index;
    for (index = 0; index < result__length; index ++) {
      raw__array__elt__set(cause, result, index, f2integer__new(cause, result_array[index]));
    }
  }
  return result;
}

u64 raw__largeinteger__unsigned_array__u32_digit_length(f2ptr cause, f2ptr this) {
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return 0;
  }
  f2ptr high_u64_value    = raw__array__elt(cause, this, this__length - 1);
  u64   high_u64_value__i = f2integer__i(high_u64_value, cause);
  if (high_u64_value__i & 0xffffffff00000000) {
    return (this__length << 1);
  } else {
    return (this__length << 1) - 1;
  }
}

u64 raw__largeinteger__unsigned_array__top_two_most_significant_u32_digits(f2ptr cause, f2ptr this) {
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return 0;
    //error(nil, "raw__largeinteger__unsigned_array__top_two_most_significant_u32_digits_as_u64 fatal error: no digits available.");
  }
  f2ptr high_u64_value    = raw__array__elt(cause, this, this__length - 1);
  u64   high_u64_value__i = f2integer__i(high_u64_value, cause);
  if (high_u64_value__i & 0xffffffff00000000) {
    return high_u64_value__i;
  } else {
    if (this__length == 1) {
      return high_u64_value__i;
      //error(nil, "raw__largeinteger__unsigned_array__top_two_most_significant_u32_digits_as_u64 fatal error: not enough digits available.");
    }
    f2ptr second_high_u64_value    = raw__array__elt(cause, this, this__length - 2);
    u64   second_high_u64_value__i = f2integer__i(second_high_u64_value, cause);
    return (high_u64_value__i << 32) + (second_high_u64_value__i >> 32);
  }
}

u64 raw__largeinteger__unsigned_array__top_most_significant_u32_digits(f2ptr cause, f2ptr this) {
  u64 this__length = raw__array__length(cause, this);
  if (this__length == 0) {
    return 0;
    //error(nil, "raw__largeinteger__unsigned_array__top_most_significant_u32_digits fatal error: no digits available.");
  }
  f2ptr high_u64_value    = raw__array__elt(cause, this, this__length - 1);
  u64   high_u64_value__i = f2integer__i(high_u64_value, cause);
  if (high_u64_value__i & 0xffffffff00000000) {
    return (high_u64_value__i >> 32);
  } else {
    return (high_u64_value__i & 0x00000000ffffffff);
  }
}

// assumes: B^n/2 <= that < B^n
f2ptr raw__largeinteger__unsigned_array__divide_n_plus_one_by_n__that_high_bit_assumed(f2ptr cause, f2ptr this, f2ptr that, f2ptr* remainder) {
  // A    = this
  // B    = that
  // beta = 2^32  (we need to do 2 by 1 division (2*32=64 [our max possible division])
  f2ptr quotient = nil;
  f2ptr that_times_beta = raw__largeinteger__unsigned_array__bitshift_left(cause, that, 32);
  if (! raw__largeinteger__unsigned_array__less_than(cause, this, that_times_beta)) {
    f2ptr recurse__this      = raw__largeinteger__unsigned_array__subtract_smaller(cause, this, that_times_beta);
    f2ptr beta               = raw__largeinteger__unsigned_array__bitshift_left(cause, raw__largeinteger__unsigned_array__new(cause, 1), 32);
    f2ptr recurse__remainder = nil;
    f2ptr recurse__quotient  = raw__largeinteger__unsigned_array__divide_n_plus_one_by_n__that_high_bit_assumed(cause, recurse__this, that, &recurse__remainder);
    quotient                 = raw__largeinteger__unsigned_array__add(cause, recurse__quotient, beta);
    *remainder               = recurse__remainder;
  } else {
    u64   two_digit_numerator   = raw__largeinteger__unsigned_array__top_two_most_significant_u32_digits(cause, this);
    u64   one_digit_denomenator = raw__largeinteger__unsigned_array__top_most_significant_u32_digits(cause, that);
    u64   test_quotient         = two_digit_numerator / one_digit_denomenator;
    if (test_quotient > 0x00000000ffffffff) {
      test_quotient = 0x00000000ffffffff;
    }
    quotient = raw__largeinteger__unsigned_array__new(cause, test_quotient);
    f2ptr test_result = raw__largeinteger__unsigned_array__multiply(cause, that, quotient);
    if (raw__largeinteger__unsigned_array__greater_than(cause, test_result, this)) {
      f2ptr one   = raw__largeinteger__unsigned_array__new(cause, 1);
      quotient    = raw__largeinteger__unsigned_array__subtract_smaller(cause, quotient, one);
      test_result = raw__largeinteger__unsigned_array__subtract_smaller(cause, test_result, that);
      if (raw__largeinteger__unsigned_array__greater_than(cause, test_result, this)) {
	quotient    = raw__largeinteger__unsigned_array__subtract_smaller(cause, quotient, one);
	test_result = raw__largeinteger__unsigned_array__subtract_smaller(cause, test_result, that);
      }
    }
    *remainder = raw__largeinteger__unsigned_array__subtract_smaller(cause, this, test_result);
  }
  return quotient;
}

f2ptr raw__largeinteger__unsigned_array__divide__that_high_bit_assumed(f2ptr cause, f2ptr this, f2ptr that, f2ptr* remainder) {
  if (raw__largeinteger__unsigned_array__greater_than(cause, that, this)) {
    *remainder = this;
    return raw__array__new(cause, 0);
  }
  u64 that__length = raw__array__length(cause, that);
  if (that__length == 0) {
    return f2larva__new(cause, 53); // divide by zero
  }
  u64 this__u32_length = raw__largeinteger__unsigned_array__u32_digit_length(cause, this);
  u64 that__u32_length = raw__largeinteger__unsigned_array__u32_digit_length(cause, that);
  if (this__u32_length < that__u32_length) {
    *remainder = that;
    return raw__largeinteger__unsigned_array__new(cause, 0);
  }
  if (this__u32_length == that__u32_length) {
    if (raw__largeinteger__unsigned_array__less_than(cause, this, that)) {
      *remainder = that;
      return raw__largeinteger__unsigned_array__new(cause, 0);
    } else {
      *remainder = raw__largeinteger__unsigned_array__subtract_smaller(cause, this, that);
      return raw__largeinteger__unsigned_array__new(cause, 1);
    }
  }
  if (this__u32_length == that__u32_length + 1) {
    return raw__largeinteger__unsigned_array__divide_n_plus_one_by_n__that_high_bit_assumed(cause, this, that, remainder);
  }
  f2ptr this_right_shifted = raw__largeinteger__unsigned_array__bitshift_right(cause, this, (this__u32_length - that__u32_length - 1) * 32);
  s64   high_bit_num       = ((this__u32_length - that__u32_length - 1) * 32) - 1;
  f2ptr this_right_shifted_leftover;
  if (high_bit_num >= 0) {
    this_right_shifted_leftover = raw__largeinteger__unsigned_array__mask_bitrange(cause, this, 0, high_bit_num);
  } else {
    this_right_shifted_leftover = raw__largeinteger__unsigned_array__new(cause, 0);
  }
  f2ptr this_right_shifted__remainder = nil;
  f2ptr this_right_shifted__quotient  = raw__largeinteger__unsigned_array__divide_n_plus_one_by_n__that_high_bit_assumed(cause, this_right_shifted, that, &this_right_shifted__remainder);
  f2ptr recursive__left_shifted_remainder = raw__largeinteger__unsigned_array__bitshift_left(cause, this_right_shifted__remainder, (this__u32_length - that__u32_length - 1) * 32);
  f2ptr recursive__numerator = raw__largeinteger__unsigned_array__add(cause, recursive__left_shifted_remainder, this_right_shifted_leftover);
  f2ptr recursive__remainder = nil;
  f2ptr recursive__quotient  = raw__largeinteger__unsigned_array__divide__that_high_bit_assumed(cause, recursive__numerator, that, &recursive__remainder);
  f2ptr this_right_shifted__quotient__left_shifted = raw__largeinteger__unsigned_array__bitshift_left(cause, this_right_shifted__quotient, (this__u32_length - that__u32_length - 1) * 32);
  *remainder = recursive__remainder;
  return raw__largeinteger__unsigned_array__add(cause, this_right_shifted__quotient__left_shifted, recursive__quotient);
}

f2ptr raw__largeinteger__unsigned_array__divide(f2ptr cause, f2ptr this, f2ptr that, f2ptr* remainder) {
  u64 that__most_significant = raw__largeinteger__unsigned_array__top_most_significant_u32_digits(cause, that);
  u64 need_left_shift;
  if      (that__most_significant & 0x80000000) {need_left_shift =  0;}
  else if (that__most_significant & 0x40000000) {need_left_shift =  1;}
  else if (that__most_significant & 0x20000000) {need_left_shift =  2;}
  else if (that__most_significant & 0x10000000) {need_left_shift =  3;}
  else if (that__most_significant & 0x08000000) {need_left_shift =  4;}
  else if (that__most_significant & 0x04000000) {need_left_shift =  5;}
  else if (that__most_significant & 0x02000000) {need_left_shift =  6;}
  else if (that__most_significant & 0x01000000) {need_left_shift =  7;}
  else if (that__most_significant & 0x00800000) {need_left_shift =  8;}
  else if (that__most_significant & 0x00400000) {need_left_shift =  9;}
  else if (that__most_significant & 0x00200000) {need_left_shift = 10;}
  else if (that__most_significant & 0x00100000) {need_left_shift = 11;}
  else if (that__most_significant & 0x00080000) {need_left_shift = 12;}
  else if (that__most_significant & 0x00040000) {need_left_shift = 13;}
  else if (that__most_significant & 0x00020000) {need_left_shift = 14;}
  else if (that__most_significant & 0x00010000) {need_left_shift = 15;}
  else if (that__most_significant & 0x00008000) {need_left_shift = 16;}
  else if (that__most_significant & 0x00004000) {need_left_shift = 17;}
  else if (that__most_significant & 0x00002000) {need_left_shift = 18;}
  else if (that__most_significant & 0x00001000) {need_left_shift = 19;}
  else if (that__most_significant & 0x00000800) {need_left_shift = 20;}
  else if (that__most_significant & 0x00000400) {need_left_shift = 21;}
  else if (that__most_significant & 0x00000200) {need_left_shift = 22;}
  else if (that__most_significant & 0x00000100) {need_left_shift = 23;}
  else if (that__most_significant & 0x00000080) {need_left_shift = 24;}
  else if (that__most_significant & 0x00000040) {need_left_shift = 25;}
  else if (that__most_significant & 0x00000020) {need_left_shift = 26;}
  else if (that__most_significant & 0x00000010) {need_left_shift = 27;}
  else if (that__most_significant & 0x00000008) {need_left_shift = 28;}
  else if (that__most_significant & 0x00000004) {need_left_shift = 29;}
  else if (that__most_significant & 0x00000002) {need_left_shift = 30;}
  else if (that__most_significant & 0x00000001) {need_left_shift = 31;}
  else {error(nil, "expected most significant digit to contain at least one nonzero bit.");}
  f2ptr this__left_shifted = raw__largeinteger__unsigned_array__bitshift_left(cause, this, need_left_shift);
  f2ptr that__left_shifted = raw__largeinteger__unsigned_array__bitshift_left(cause, that, need_left_shift);
  f2ptr remainder__left_shifted = nil;
  f2ptr quotient = raw__largeinteger__unsigned_array__divide__that_high_bit_assumed(cause, this__left_shifted, that__left_shifted, &remainder__left_shifted);
  *remainder = raw__largeinteger__unsigned_array__bitshift_right(cause, remainder__left_shifted, need_left_shift);
  return quotient;
}

void raw__largeinteger__unsigned_array__print(f2ptr cause, f2ptr this, boolean_t pad_front_with_zeros) {
  f2ptr max_decimals_at_once = raw__largeinteger__unsigned_array__new(cause, 1000000000ull);
  if (raw__largeinteger__unsigned_array__less_than(cause, this, max_decimals_at_once)) {
    u64 this__length = raw__array__length(cause, this);
    u64 this__elt__value;
    if (this__length == 0) {
      this__elt__value = 0;
    } else if (this__length != 1) {
      error(nil, "array should have length of one.");
    } else {
      f2ptr this__elt  = raw__array__elt(cause, this, 0);
      this__elt__value = f2integer__i(this__elt, cause);
    }
    char temp_str[32];
    snprintf(temp_str, 32, pad_front_with_zeros ? ("%09" u64__fstr_without_percent) : u64__fstr, this__elt__value);
    write(1, temp_str, strlen(temp_str));
  } else {
    f2ptr remaining_decimals_to_print;
    f2ptr first_decimals_to_print = raw__largeinteger__unsigned_array__divide(cause, this, max_decimals_at_once, &remaining_decimals_to_print);
    raw__largeinteger__unsigned_array__print(cause, first_decimals_to_print,     boolean__false);
    raw__largeinteger__unsigned_array__print(cause, remaining_decimals_to_print, boolean__true);
  }
}

// largeinteger

def_primobject_2_slot(largeinteger, is_negative, integer_array);

f2ptr raw__largeinteger__new_from_s64(f2ptr cause, s64 value) {
  f2ptr is_negative;
  f2ptr integer_array;
  if (value >= 0) {
    is_negative = f2bool__new(boolean__false);
    integer_array = raw__largeinteger__unsigned_array__new(cause, value);
  } else {
    is_negative = f2bool__new(boolean__true);
    integer_array = raw__largeinteger__unsigned_array__new(cause, -value);
  }
  return f2largeinteger__new(cause, is_negative, integer_array);
}

f2ptr f2__largeinteger__new(f2ptr cause, f2ptr value) {
  if (raw__largeinteger__is_type(cause, value)) {
    return value;
  }
  if (! raw__integer__is_type(cause, value)) {
    return f2larva__new(cause, 1);
  }
  s64 value__i = f2integer__i(value, cause);
  return raw__largeinteger__new_from_s64(cause, value__i);
}
def_pcfunk1(largeinteger__new, value, return f2__largeinteger__new(this_cause, value));

boolean_t raw__largeinteger__less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(cause, that);
  if (this__is_negative) {
    if (that__is_negative) {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array);
    } else {
      return boolean__true;
    }
  } else {
    if (that__is_negative) {
      return boolean__false;
    } else {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__less_than(cause, this__array, that__array);
    }
  }
}

f2ptr f2__largeinteger__less_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__largeinteger__less_than(cause, this, that));
}
def_pcfunk2(largeinteger__less_than, this, that, return f2__largeinteger__less_than(this_cause, this, that));

boolean_t raw__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(cause, that);
  if (this__is_negative) {
    if (that__is_negative) {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__less_than(cause, this__array, that__array);
    } else {
      return boolean__false;
    }
  } else {
    if (that__is_negative) {
      return boolean__true;
    } else {
      f2ptr this__array = f2__largeinteger__integer_array(cause, this);
      f2ptr that__array = f2__largeinteger__integer_array(cause, that);
      return raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array);
    }
  }
}

f2ptr f2__largeinteger__greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__largeinteger__greater_than(cause, this, that));
}
def_pcfunk2(largeinteger__greater_than, this, that, return f2__largeinteger__greater_than(this_cause, this, that));

f2ptr raw__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative = f2__largeinteger__is_negative(     cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(     cause, that);
  f2ptr this__array    = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array    = f2__largeinteger__integer_array(cause, that);
  f2ptr result__array;
  f2ptr result__is_negative;
  if (this__is_negative) {
    if (that__is_negative) {
      result__is_negative = f2bool__new(boolean__true);
      result__array    = raw__largeinteger__unsigned_array__add(cause, this__array, that__array);
    } else {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__is_negative = f2bool__new(boolean__true);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__is_negative = f2bool__new(boolean__false);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = raw__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    }
  } else {
    if (that__is_negative) {
      f2ptr small__array;
      f2ptr large__array;
      if (raw__largeinteger__unsigned_array__greater_than(cause, this__array, that__array)) {
	result__is_negative = f2bool__new(boolean__false);
	small__array     = that__array;
	large__array     = this__array;
      } else {
	result__is_negative = f2bool__new(boolean__true);
	small__array     = this__array;
	large__array     = that__array;
      }
      result__array = raw__largeinteger__unsigned_array__subtract_smaller(cause, large__array, small__array);
    } else {
      result__is_negative = f2bool__new(boolean__false);
      result__array    = raw__largeinteger__unsigned_array__add(cause, this__array, that__array);
    }
  }
  return f2largeinteger__new(cause, result__is_negative, result__array);
}

f2ptr f2__largeinteger__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__add(cause, this, that);
}
def_pcfunk2(largeinteger__add, this, that, return f2__largeinteger__add(this_cause, this, that));

f2ptr raw__largeinteger__negative(f2ptr cause, f2ptr this) {
  return f2largeinteger__new(cause, f2bool__new(f2largeinteger__is_negative(this, cause) == nil), f2largeinteger__integer_array(this, cause));
}

f2ptr f2__largeinteger__negative(f2ptr cause, f2ptr this) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__negative(cause, this);
}
def_pcfunk1(largeinteger__negative, this, return f2__largeinteger__negative(this_cause, this));

f2ptr raw__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__largeinteger__add(cause, this, raw__largeinteger__negative(cause, that));
}

f2ptr f2__largeinteger__subtract(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__subtract(cause, this, that);
}
def_pcfunk2(largeinteger__subtract, this, that, return f2__largeinteger__subtract(this_cause, this, that));

f2ptr raw__largeinteger__bitshift_left(f2ptr cause, f2ptr this, s64 bit_distance) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr this__array       = f2__largeinteger__integer_array(cause, this);
  f2ptr result_array      = raw__largeinteger__unsigned_array__bitshift_left(cause, this__array, bit_distance);
  return f2largeinteger__new(cause, this__is_negative, result_array);
}

f2ptr f2__largeinteger__bitshift_left(f2ptr cause, f2ptr this, f2ptr bit_distance) {
  if (! raw__integer__is_type(cause, bit_distance)) {
    return f2larva__new(cause, 1);
  }
  s64 bit_distance__i = f2integer__i(bit_distance, cause);
  return raw__largeinteger__bitshift_left(cause, this, bit_distance__i);
}
def_pcfunk2(largeinteger__bitshift_left, this, bit_distance, return f2__largeinteger__bitshift_left(this_cause, this, bit_distance));

f2ptr raw__largeinteger__bitshift_right(f2ptr cause, f2ptr this, f2ptr bit_distance) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr this__array       = f2__largeinteger__integer_array(cause, this);
  f2ptr result_array      = raw__largeinteger__unsigned_array__bitshift_right(cause, this__array, bit_distance);
  return f2largeinteger__new(cause, this__is_negative, result_array);
}

f2ptr f2__largeinteger__bitshift_right(f2ptr cause, f2ptr this, f2ptr bit_distance) {
  if (! raw__integer__is_type(cause, bit_distance)) {
    return f2larva__new(cause, 1);
  }
  s64 bit_distance__i = f2integer__i(bit_distance, cause);
  return raw__largeinteger__bitshift_right(cause, this, bit_distance__i);
}
def_pcfunk2(largeinteger__bitshift_right, this, bit_distance, return f2__largeinteger__bitshift_right(this_cause, this, bit_distance));

f2ptr raw__largeinteger__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative   = f2__largeinteger__is_negative(  cause, this);
  f2ptr that__is_negative   = f2__largeinteger__is_negative(  cause, that);
  f2ptr this__array         = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array         = f2__largeinteger__integer_array(cause, that);
  f2ptr result__is_negative = f2bool__new((this__is_negative != nil) != (that__is_negative != nil));
  f2ptr result__array       = raw__largeinteger__unsigned_array__multiply(cause, this__array, that__array);
  return f2largeinteger__new(cause, result__is_negative, result__array);
}

f2ptr f2__largeinteger__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__multiply(cause, this, that);
}
def_pcfunk2(largeinteger__multiply, this, that, return f2__largeinteger__multiply(this_cause, this, that));

f2ptr raw__largeinteger__quotient_and_remainder(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__is_negative       = f2__largeinteger__is_negative(  cause, this);
  f2ptr that__is_negative       = f2__largeinteger__is_negative(  cause, that);
  f2ptr this__array             = f2__largeinteger__integer_array(cause, this);
  f2ptr that__array             = f2__largeinteger__integer_array(cause, that);
  f2ptr result__is_negative     = f2bool__new((this__is_negative != nil) != (that__is_negative != nil));
  f2ptr result__remainder_array = nil;
  f2ptr result__quotient_array  = raw__largeinteger__unsigned_array__divide(cause, this__array, that__array, &result__remainder_array);
  if (raw__larva__is_type(cause, result__quotient_array)) {
    return result__quotient_array; // catch and propagate divide by zero
  }
  f2ptr quotient_and_remainder = f2cons__new(cause, f2largeinteger__new(cause, result__is_negative, result__quotient_array), f2largeinteger__new(cause, result__is_negative, result__remainder_array));
  return quotient_and_remainder;
}

f2ptr f2__largeinteger__quotient_and_remainder(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__quotient_and_remainder(cause, this, that);
}
def_pcfunk2(largeinteger__quotient_and_remainder, this, that, return f2__largeinteger__quotient_and_remainder(this_cause, this, that));

f2ptr raw__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr quotient_and_remainder = raw__largeinteger__quotient_and_remainder(cause, this, that);
  f2ptr quotient = f2__cons__car(cause, quotient_and_remainder);
  return quotient;
}

f2ptr f2__largeinteger__divide(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__divide(cause, this, that);
}
def_pcfunk2(largeinteger__divide, this, that, return f2__largeinteger__divide(this_cause, this, that));

f2ptr raw__largeinteger__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr quotient_and_remainder = raw__largeinteger__quotient_and_remainder(cause, this, that);
  f2ptr remainder = f2__cons__cdr(cause, quotient_and_remainder);
  return remainder;
}

f2ptr f2__largeinteger__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__largeinteger__modulo(cause, this, that);
}
def_pcfunk2(largeinteger__modulo, this, that, return f2__largeinteger__modulo(this_cause, this, that));

f2ptr f2__largeinteger__print(f2ptr cause, f2ptr this) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr is_negative   = f2__largeinteger__is_negative(cause, this);
  f2ptr integer_array = f2__largeinteger__integer_array(cause, this);
  if (is_negative) {
    char* negative_sign = "-";
    write(1, negative_sign, 1);
  }
  raw__largeinteger__unsigned_array__print(cause, integer_array, boolean__false);
  return nil;
}
def_pcfunk1(largeinteger__print, this, return f2__largeinteger__print(this_cause, this));

boolean_t raw__largeinteger__unsigned_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__array__length(cause, this);
  u64 that__length = raw__array__length(cause, that);
  if (this__length != that__length) {
    return boolean__false;
  }
  u64 index;
  for (index = 0; index < this__length; index ++) {
    f2ptr this__elt   = raw__array__elt(cause, this, index);
    f2ptr that__elt   = raw__array__elt(cause, that, index);
    u64   this__value = f2integer__i(this__elt, cause);
    u64   that__value = f2integer__i(that__elt, cause);
    if (this__value != that__value) {
      return boolean__false;
    }
  }
  return boolean__true;
}

boolean_t raw__largeinteger__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__largeinteger__is_type(cause, this)) ||
      (! raw__largeinteger__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  f2ptr this__is_negative = f2__largeinteger__is_negative(cause, this);
  f2ptr that__is_negative = f2__largeinteger__is_negative(cause, that);
  if ((! this__is_negative) != (! that__is_negative)) {
    return boolean__false;
  }
  f2ptr this__integer_array = f2__largeinteger__integer_array(cause, this);
  f2ptr that__integer_array = f2__largeinteger__integer_array(cause, that);
  return raw__largeinteger__unsigned_array__equals(cause, this__integer_array, that__integer_array);
}

f2ptr f2__largeinteger__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__largeinteger__equals(cause, this, that));
}

double raw__largeinteger__unsigned_array__to_double(f2ptr cause, f2ptr this) {
  u64 this__length = raw__array__length(cause, this);
  double result      = 0.0;
  double digit_power = 1.0;
  u64 index;
  for (index = 0; index < this__length; index ++) {
    f2ptr  elt        = raw__array__elt(cause, this, index);
    u64    elt__value = (u64)f2integer__i(elt, cause);
    double d          = (double)elt__value;
    double addend     = d * digit_power;
    result += addend;
    digit_power *= 18446744073709551616.0;
  }
  return result;
}

double raw__largeinteger__to_double(f2ptr cause, f2ptr this) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr is_negative   = f2__largeinteger__is_negative(cause, this);
  f2ptr integer_array = f2__largeinteger__integer_array(cause, this);
  double value = raw__largeinteger__unsigned_array__to_double(cause, integer_array);
  if (is_negative) {
    value = -value;
  }
  return value;
}

// **

void f2__primobject_largeinteger__reinitialize_globalvars() {
  __largeinteger__symbol = f2symbol__new(initial_cause(), strlen("largeinteger"), (u8*)"largeinteger");
}

void f2__primobject_largeinteger__initialize() {
  f2__primobject_largeinteger__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __largeinteger__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // largeinteger
  
  initialize_primobject_2_slot(largeinteger, is_negative, integer_array);
  
  f2__primcfunk__init__2(largeinteger__less_than, this, that, "compare two largeintegers for which is less and return a boolean value as the result.");
  f2__primcfunk__init__2(largeinteger__greater_than, this, that, "compare two largeintegers for which is greater and return a boolean value as the result.");
  f2__primcfunk__init__2(largeinteger__add, this, that, "add two largeintegers and return a new largeinteger as the result.");
  f2__primcfunk__init__1(largeinteger__negative, this, "returns the negative of a largeinteger.");
  f2__primcfunk__init__2(largeinteger__subtract, this, that, "returns the result of subtracting two largeintegers.");
  f2__primcfunk__init__2(largeinteger__bitshift_left, this, bit_distance, "returns the result of bitshifting one largeinteger to the left by an integer bit distance.");
  f2__primcfunk__init__2(largeinteger__bitshift_right, this, bit_distance, "returns the result of bitshifting one largeinteger to the right by an integer bit distance.");
  f2__primcfunk__init__2(largeinteger__multiply, this, that, "returns the result of multiplying two largeintegers.");
  f2__primcfunk__init__2(largeinteger__quotient_and_remainder, this, that, "returns the quotient and remainder of a largeinteger division in a cons cell.");
  f2__primcfunk__init__2(largeinteger__divide, this, that, "returns the result of dividing two largeintegers.");
  f2__primcfunk__init__2(largeinteger__modulo, this, that, "returns the result of the modulo of two largeintegers.");
  f2__primcfunk__init__1(largeinteger__print, this, "prints a large integer in decimal format to the standard output.");
  
}

