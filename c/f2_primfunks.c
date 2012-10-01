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

#include "funk2.h"

f2ptr f2__argument_type_check_failure__larva__new(f2ptr cause, f2ptr value) {
  return f2larva__new(cause, 1235222, nil);
}

f2ptr f2__argument_number_check_failure__larva__new(f2ptr cause, f2ptr funk_symbol, int correct_arg_num, f2ptr args) {
  f2ptr bug_frame = f2__frame__new(cause, nil);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),        new__symbol(cause, "argument_number_check_failure"));
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_symbol"),     funk_symbol);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "correct_arg_num"), f2integer__new(cause, correct_arg_num));
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "args"),            args);
  return f2larva__new(cause, 33, f2__bug__new(cause, f2integer__new(cause, 33), bug_frame));
}

// nil

boolean_t raw__null(f2ptr x) {return !x;}

f2ptr f2__null(f2ptr cause, f2ptr x) {return f2bool__new(raw__null(x));}
def_pcfunk1(null, x,
	    "",
	    return f2__null(this_cause, x));

// s64

boolean_t s64__add_overflows(s64 this, s64 that) {
  if (that == 0) {
    return boolean__false;
  }
  s64 result = this + that;
  if (that > 0) {
    return (result < this);
  } else {
    return (result > this);
  }
}


// u64

u64 u64__sqrt(u64 this) {
  register u64 root      = 0;
  register u64 remainder = this;
  register u64 place     = 0x4000000000000000ull;
  
  while (place > remainder) {
    place = place >> 2;
  }
  
  while (place) {
    if (remainder >= root + place) {
      remainder = remainder - root - place;
      root = root + (place << 1);
    }
    root = root >> 1;
    place = place >> 2;
  }
  return root;
}

/*
  1 << (((64__bit_num(this) * 3) / 2) + 1)
  (2 ^ (log2(this) * (3 / 2))  + 2
 */

u64 u64__bit_num(u64 this) {
  register u64 remainder = this;
  register u64 bit_num   = 1;
  if (remainder & 0xffffffff00000000) {
    bit_num += 32;
    remainder >>= 32;
  }
  if (remainder & 0xffff0000) {
    bit_num += 16;
    remainder >>= 16;
  }
  if (remainder & 0xff00) {
    bit_num += 8;
    remainder >>= 8;
  }
  if (remainder & 0xf0) {
    bit_num += 4;
    remainder >>= 4;
  }
  if (remainder & 0xC) {
    bit_num += 2;
    remainder >>= 2;
  }
  if (remainder & 0x2) {
    bit_num ++;
    remainder >>= 1;
  }
  return bit_num;
}

// logic

boolean_t raw__not(f2ptr x) {return !x;}

f2ptr f2__not(f2ptr cause, f2ptr x) {return f2bool__new(raw__not(x));}
def_pcfunk1(not, x,
	    "",
	    return f2__not(this_cause, x));

f2ptr f2__and(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2bool__new((x0 != nil) && (x1 != nil));
}

f2ptr f2__or(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2bool__new((x0 != nil) || (x1 != nil));
}

// math

f2ptr f2__add(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__plus(cause, x1, x0);
}

f2ptr f2__negative(f2ptr cause, f2ptr x) {
  return f2__number__minus(cause, f2integer__new(cause, 0), x);
}

f2ptr f2__subtract(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__minus(cause, x1, x0);
}

f2ptr f2__multiply(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__multiplied_by(cause, x1, x0);
}

f2ptr f2__inverse(f2ptr cause, f2ptr x) {
  return f2__number__divided_by(cause, f2integer__new(cause, 1), x);
}

f2ptr f2__divide(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__divided_by(cause, x1, x0);
}

f2ptr f2__modulo(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__modulo(cause, x1, x0);
}

f2ptr f2__increment(f2ptr cause, f2ptr x) {
  return f2__number__plus(cause, x, f2integer__new(cause, 1));
}

f2ptr f2__decrement(f2ptr cause, f2ptr x) {
  return f2__number__minus(cause, x, f2integer__new(cause, 1));
}

f2ptr f2__numerically_equals(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__is_numerically_equal_to(cause, x1, x0);
}

f2ptr f2__less_than(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__is_less_than(cause, x1, x0);
}

f2ptr f2__greater_than(f2ptr cause, f2ptr x0, f2ptr x1) {
  return f2__number__is_greater_than(cause, x1, x0);
}

// system

f2ptr f2__system__node_id(f2ptr cause) {
  return f2pointer__new(cause, __funk2.node_id);
}
def_pcfunk0(system__node_id,
	    "",
	    return f2__system__node_id(this_cause));

f2ptr f2__system__environment(f2ptr cause, f2ptr node_id) {
  node_id_t raw_node_id;
  if (raw__pointer__is_type(cause, node_id)) {
    raw_node_id = f2pointer__p(node_id, cause);
  } else if (raw__integer__is_type(cause, node_id)) {
    raw_node_id = f2integer__i(node_id, cause);
  } else {
    printf("\nsystem-environment error: node_id must be integer or pointer.");
    return nil;
  }
  return f2system__environment(cause, raw_node_id);
}
def_pcfunk1(system__environment, node_id,
	    "",
	    return f2__system__environment(this_cause, node_id));

f2ptr raw__system__memorypool__total_global_memory(f2ptr cause, s64 index) {
  if (index < 0 || index > 7) {
    return f2larva__new(cause, 2, nil);
  }
  return f2integer__new(cause, __funk2.memory.pool[index].total_global_memory);
}

f2ptr f2__system__memorypool__total_global_memory(f2ptr cause, f2ptr index) {
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  return raw__system__memorypool__total_global_memory(cause, index__i);
}
def_pcfunk1(system__memorypool__total_global_memory, index,
	    "Returns the total_global_memory of the memorypool index (0-7).",
	    return f2__system__memorypool__total_global_memory(this_cause, index));


f2ptr raw__system__memorypool__total_free_memory(f2ptr cause, s64 index) {
  if (index < 0 || index > 7) {
    return f2larva__new(cause, 2, nil);
  }
  return f2integer__new(cause, __funk2.memory.pool[index].total_free_memory);
}

f2ptr f2__system__memorypool__total_free_memory(f2ptr cause, f2ptr index) {
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  return raw__system__memorypool__total_free_memory(cause, index__i);
}
def_pcfunk1(system__memorypool__total_free_memory, index,
	    "Returns the total_free_memory of the memorypool index (0-7).",
	    return f2__system__memorypool__total_free_memory(this_cause, index));


// funk2 pointer (f2ptr)

f2ptr f2__pointer(f2ptr cause, f2ptr x) {return f2pointer__new(cause, (ptr)(long)x);}
def_pcfunk1(pointer, x,
	    "",
	    return f2__pointer(this_cause, x));

f2ptr f2__deref_pointer(f2ptr cause, f2ptr x) {return (f2ptr)(long)f2pointer__p(x, cause);}
def_pcfunk1(deref_pointer, x,
	    "",
	    return f2__deref_pointer(this_cause, x));

// memblock

// ptype


// integer

f2ptr f2__integer__to_double(f2ptr cause, f2ptr x) {return f2double__new(cause, f2integer__i(x, cause));}
def_pcfunk1(integer__to_double, x,
	    "",
	    return f2__integer__to_double(this_cause, x));

f2ptr f2__integer__to_float(f2ptr cause, f2ptr x) {return f2float__new(cause, f2integer__i(x, cause));}
def_pcfunk1(integer__to_float,  x,
	    "",
	    return f2__integer__to_float(this_cause, x));

f2ptr f2__integer__greater_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) >  f2integer__i(y, cause));}
def_pcfunk2(integer__greater_than, x, y,
	    "",
	    return f2__integer__greater_than(this_cause, x, y));

f2ptr f2__integer__less_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) <  f2integer__i(y, cause));}
def_pcfunk2(integer__less_than, x, y,
	    "",
	    return f2__integer__less_than(this_cause, x, y));

f2ptr f2__integer__equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) == f2integer__i(y, cause));}
def_pcfunk2(integer__equal_sign, x, y,
	    "",
	    return f2__integer__equal_sign(this_cause, x, y));

f2ptr f2__integer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2integer__i(x, cause) != f2integer__i(y, cause));}
def_pcfunk2(integer__not_equal_sign, x, y,
	    "",
	    return f2__integer__not_equal_sign(this_cause, x, y));

f2ptr f2__integer__bitshift_left(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) << f2integer__i(y, cause));}
def_pcfunk2(integer__bitshift_left, x, y,
	    "",
	    return f2__integer__bitshift_left(this_cause, x, y));

f2ptr f2__integer__bitshift_right(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) >> f2integer__i(y, cause));}
def_pcfunk2(integer__bitshift_right, x, y,
	    "",
	    return f2__integer__bitshift_right(this_cause, x, y));

f2ptr f2__integer__bit_and(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) &  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_and, x, y,
	    "",
	    return f2__integer__bit_and(this_cause, x, y));

f2ptr f2__integer__bit_or(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) |  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_or, x, y,
	    "",
	    return f2__integer__bit_or(this_cause, x, y));

f2ptr f2__integer__bit_xor(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) ^  f2integer__i(y, cause));}
def_pcfunk2(integer__bit_xor, x, y,
	    "",
	    return f2__integer__bit_xor(this_cause, x, y));

f2ptr f2__integer__bit_not(f2ptr cause, f2ptr x) {return f2integer__new(cause, ~f2integer__i(x, cause));}
def_pcfunk1(integer__bit_not, x,
	    "",
	    return f2__integer__bit_not(this_cause, x));

f2ptr f2__integer__add(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) +  f2integer__i(y, cause));}
def_pcfunk2(integer__add, x, y,
	    "",
	    return f2__integer__add(this_cause, x, y));

f2ptr f2__integer__subtract(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) -  f2integer__i(y, cause));}
def_pcfunk2(integer__subtract, x, y,
	    "",
	    return f2__integer__subtract(this_cause, x, y));

f2ptr f2__integer__multiply(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) *  f2integer__i(y, cause));}
def_pcfunk2(integer__multiply, x, y,
	    "",
	    return f2__integer__multiply(this_cause, x, y));

f2ptr f2__integer__add_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  f2integer__i(x, cause) +   f2double__d(y, cause));}
def_pcfunk2(integer__add_double, x, y,
	    "",
	    return f2__integer__add_double(this_cause, x, y));

f2ptr f2__integer__subtract_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  f2integer__i(x, cause) -   f2double__d(y, cause));}
def_pcfunk2(integer__subtract_double, x, y,
	    "",
	    return f2__integer__subtract_double(this_cause, x, y));

f2ptr f2__integer__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause,  f2integer__i(x, cause) /  f2integer__i(y, cause));}
def_pcfunk2(integer__divide_by_integer, x, y,
	    "",
	    return f2__integer__divide_by_integer(this_cause, x, y));

f2ptr f2__integer__divide_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause,  (double)f2integer__i(x, cause) / f2double__d(y, cause));}
def_pcfunk2(integer__divide_by_double, x, y,
	    "",
	    return f2__integer__divide_by_double(this_cause, x, y));

// double

f2ptr f2__double__to_integer(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2double__d(x, cause));}
def_pcfunk1(double__to_integer, x,
	    "",
	    return f2__double__to_integer(this_cause, x));

f2ptr f2__double__to_float(f2ptr cause, f2ptr x) {return f2float__new(cause, f2double__d(x, cause));}
def_pcfunk1(double__to_float, x,
	    "",
	    return f2__double__to_float(this_cause, x));

f2ptr f2__double__add_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) + f2double__d(y, cause));}
def_pcfunk2(double__add_double, x, y,
	    "",
	    return f2__double__add_double(this_cause, x, y));

f2ptr f2__double__subtract_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) - f2double__d(y, cause));}
def_pcfunk2(double__subtract_double, x, y,
	    "",
	    return f2__double__subtract_double(this_cause, x, y));

f2ptr f2__double__multiply_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) * f2double__d(y, cause));}
def_pcfunk2(double__multiply_by_double, x, y,
	    "",
	    return f2__double__multiply_by_double(this_cause, x, y));

f2ptr f2__double__divide_by_double(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) / f2double__d(y, cause));}
def_pcfunk2(double__divide_by_double, x, y,
	    "",
	    return f2__double__divide_by_double(this_cause, x, y));

f2ptr f2__double__add_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) + f2integer__i(y, cause));}
def_pcfunk2(double__add_integer, x, y,
	    "",
	    return f2__double__add_integer(this_cause, x, y));

f2ptr f2__double__subtract_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) - f2integer__i(y, cause));}
def_pcfunk2(double__subtract_integer, x, y,
	    "",
	    return f2__double__subtract_integer(this_cause, x, y));

f2ptr f2__double__multiply_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) * f2integer__i(y, cause));}
def_pcfunk2(double__multiply_by_integer, x, y,
	    "",
	    return f2__double__multiply_by_integer(this_cause, x, y));

f2ptr f2__double__divide_by_integer(f2ptr cause, f2ptr x, f2ptr y) {return f2double__new(cause, f2double__d(x, cause) / f2integer__i(y, cause));}
def_pcfunk2(double__divide_by_integer, x, y,
	    "",
	    return f2__double__divide_by_integer(this_cause, x, y));

// float

f2ptr f2__float__to_integer(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2float__f(x, cause));}
def_pcfunk1(float__to_integer, x,
	    "",
	    return f2__float__to_integer(this_cause, x));

f2ptr f2__float__to_double(f2ptr cause, f2ptr x) {return f2double__new(cause, f2float__f(x, cause));}
def_pcfunk1(float__to_double, x,
	    "",
	    return f2__float__to_double(this_cause, x));

// pointer

f2ptr f2__pointer__greater_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) >  f2pointer__p(y, cause));}
def_pcfunk2(pointer__greater_than, x, y,
	    "",
	    return f2__pointer__greater_than(this_cause, x, y));

f2ptr f2__pointer__less_than(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) <  f2pointer__p(y, cause));}
def_pcfunk2(pointer__less_than, x, y,
	    "",
	    return f2__pointer__less_than(this_cause, x, y));

f2ptr f2__pointer__equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) == f2pointer__p(y, cause));}
def_pcfunk2(pointer__equal_sign, x, y,
	    "",
	    return f2__pointer__equal_sign(this_cause, x, y));

f2ptr f2__pointer__not_equal_sign(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(f2pointer__p(x, cause) != f2pointer__p(y, cause));}
def_pcfunk2(pointer__not_equal_sign, x, y,
	    "",
	    return f2__pointer__not_equal_sign(this_cause, x, y));

f2ptr f2__pointer__subtract(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2pointer__p(x, cause) -  f2pointer__p(y, cause));}
def_pcfunk2(pointer__subtract, x, y,
	    "",
	    return f2__pointer__subtract(this_cause, x, y));

// cmutex

// avoids race conditions
void raw__cmutex__lock_both(f2ptr cause, f2ptr this, f2ptr that) {
  boolean_t both_locked = boolean__false;
  while (! both_locked) {
    if (f2cmutex__trylock(this, cause) == 0) {
      if (f2cmutex__trylock(that, cause) == 0) {
	both_locked = boolean__true;
      } else {
	f2cmutex__unlock(this, cause);
      }
    }
    if (! both_locked) {
      raw__fast_spin_sleep_yield();
    }
  }
}

// avoids race conditions
f2ptr f2__cmutex__lock_both(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(cmutex, this);
  assert_argument_type(cmutex, that);
  raw__cmutex__lock_both(cause, this, that);
  return nil;
}

// char


// string

f2ptr new__string(f2ptr cause, char* str) {
  return raw__string__new_from_utf8(cause, str);
}

f2ptr new__funk2_string(f2ptr cause, funk2_character_t* str) {
  u64 length;
  for (length = 0; str[length] != 0; length ++);
  return f2string__new(cause, length, str);
}

//def_pcfunk2(string__equals, x, y, return f2__string__eq(this_cause, x, y));

f2ptr f2__string__new_raw_c_string(f2ptr cause, f2ptr x) {
  int   utf8_length = raw__string__utf8_length(cause, x);
  char* utf8_str    = (char*)from_ptr(f2__malloc(utf8_length + 1));
  raw__string__utf8_str_copy(cause, x, (u8*)utf8_str);
  utf8_str[utf8_length] = 0;
  return f2pointer__new(cause, to_ptr(utf8_str));
}
def_pcfunk1(string__new_raw_c_string, x,
	    "",
	    return f2__string__new_raw_c_string(this_cause, x));

f2ptr f2__string__new_from_raw_c_string(f2ptr cause, f2ptr x) {
  assert_argument_type(pointer, x);
  char* str = (char*)from_ptr(f2pointer__p(x, cause));
  return new__string(cause, str);
}
def_pcfunk1(string__new_from_raw_c_string, x,
	    "",
	    return f2__string__new_from_raw_c_string(this_cause, x));

// symbol

f2ptr new__symbol(f2ptr cause, char* str) {
  return raw__symbol__new_from_utf8(cause, str);
}

// simple_array


// traced_array


// cons

boolean_t raw__conslist__is_type(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return boolean__true;
  }
  if (! raw__cons__is_type(cause, this)) {
    return boolean__false;
  }
  f2ptr this__cdr = f2__cons__cdr(cause, this);
  return raw__conslist__is_type(cause, this__cdr);
}

f2ptr f2__conslist__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__conslist__is_type(cause, this));
}

f2ptr raw__conslist__new(f2ptr cause, f2ptr conslist) {
  if (conslist == nil) {
    return nil;
  }
  f2ptr car = f2cons__car(conslist, cause);
  f2ptr cdr = f2cons__cdr(conslist, cause);
  return raw__cons__new(cause, car, raw__conslist__new(cause, cdr));
}

f2ptr f2__conslist__new(f2ptr cause, f2ptr conslist) {
  assert_argument_type(conslist, conslist);
  return raw__conslist__new(cause, conslist);
}
def_pcfunk0_and_rest(conslist, conslist,
		     "returns a new conslist.",
		     return f2__conslist__new(this_cause, conslist));

def_pcfunk0_and_rest(immutable_conslist, seq,
		     "returns a new conslist that we will agree to not mutate.",
		     return f2__conslist__new(this_cause, seq));

f2ptr raw__conslist__as__array(f2ptr cause, f2ptr this) {
  u64 length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      length ++;
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr new_array = raw__array__new(cause, length);
  {
    f2ptr iter = this;
    u64 index = 0;
    while (iter) {
      f2ptr car = f2cons__car(iter, cause);
      raw__array__elt__set(cause, new_array, index, car);
      index ++;
      iter = f2cons__cdr(iter, cause);
    }
  }
  return new_array;
}

f2ptr f2__conslist__as__array(f2ptr cause, f2ptr this) {
  assert_argument_type(conslist, this);
  return raw__conslist__as__array(cause, this);
}
def_pcfunk1(conslist__as__array, this,
	    "returns a conslist represented as a new array.",
	    return f2__conslist__as__array(this_cause, this));

f2ptr f2__conslist__first_n(f2ptr cause, f2ptr this, f2ptr n) {
  assert_argument_type(conslist, this);
  assert_argument_type(integer,  n);
  s64 raw_n = f2integer__i(n, cause);
  s64 index = 0;
  f2ptr new_seq  = nil;
  f2ptr new_iter = nil;
  f2ptr iter = this;
  while (iter && index < raw_n) {
    f2ptr car = f2cons__car(iter, cause);
    f2ptr new_cons = raw__cons__new(cause, car, nil);
    if (! new_seq) {
      new_seq = new_cons;
    }
    if (new_iter) {
      f2cons__cdr__set(new_iter, cause, new_cons);
    }
    new_iter = new_cons;
    index ++;
    iter = f2cons__cdr(iter, cause);
  }
  return new_seq;
}
def_pcfunk2(conslist__first_n, this, n,
	    "returns a new representation of the first n elements of the list, this.",
	    return f2__conslist__first_n(this_cause, this, n));

f2ptr f2__conslistlist__append(f2ptr cause, f2ptr this) {
  f2ptr new_list      = nil;
  f2ptr new_list_iter = nil;
  f2ptr conslist_iter = this;
  while (conslist_iter) {
    f2ptr conslist = f2__cons__car(cause, conslist_iter);
    {
      f2ptr iter = conslist;
      while (iter) {
	f2ptr elt = f2__cons__car(cause, iter);
	f2ptr new_cons = raw__cons__new(cause, elt, nil);
	if (new_list_iter) {
	  f2__cons__cdr__set(cause, new_list_iter, new_cons);
	} else {
	  new_list = new_cons;
	}
	new_list_iter = new_cons;
	iter = f2__cons__cdr(cause, iter);
      }
    }
    conslist_iter = f2__cons__cdr(cause, conslist_iter);
  }
  return new_list;
}
def_pcfunk1(conslistlist__append, this,
	    "append a list of lists.",
	    return f2__conslistlist__append(this_cause, this));

// time

f2ptr f2__time(f2ptr cause) {
  return f2time__new(cause, f2__nanoseconds_since_1970(cause));
}
def_pcfunk0(time,
	    "returns the current time.",
	    return f2__time(this_cause));

// fiber

f2ptr f2__sleep_for_nanoseconds_without_yield(f2ptr fiber, f2ptr cause, f2ptr nanoseconds) {
  return f2__fiber__sleep_for_nanoseconds(cause, fiber, nanoseconds);
}
def_pcfunk1(sleep_for_nanoseconds_without_yield, nanoseconds,
	    "tells current executing fiber to sleep for given number of nanoseconds.  [yield] should immediately follow.",
	    return f2__sleep_for_nanoseconds_without_yield(simple_fiber, this_cause, nanoseconds));

// larva

//boolean_t raw__larvap(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_larva);}

// chunk

f2ptr f2__chunk(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  int raw_length = f2integer__i(length, cause);
  return f2chunk__new(cause, raw_length, NULL);
}
def_pcfunk1(chunk, length,
	    "",
	    return f2__chunk(this_cause, length));

//boolean_t raw__chunkp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_chunk);}

//f2ptr f2__chunkp(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunkp(x, cause));}
//def_pcfunk1(chunkp, x, return f2__chunkp(this_cause, x));

//f2ptr f2__chunk__bytes(f2ptr cause, f2ptr x) {return f2pointer__new(cause, f2chunk__bytes(x, cause));}
//def_pcfunk1(chunk__bytes, x, return f2__chunk__bytes(this_cause, x));

f2ptr f2__chunk__new_compiled_from_funk(f2ptr cause, f2ptr x) {return f2chunk__new_compiled_from_funk(cause, x);}
def_pcfunk1(chunk__new_compiled_from_funk, x,
	    "",
	    return f2__chunk__new_compiled_from_funk(this_cause, x));



// primobject ptypehash

// primobject fiber

f2ptr f2__force_funk_apply(f2ptr cause, f2ptr fiber, f2ptr funkable, f2ptr args) {
  if (raw__cfunk__is_type(cause, funkable)) {
    return f2__cfunk__apply(cause, funkable, fiber, args);
  } else if (raw__core_extension_funk__is_type(cause, funkable)) {
    return raw__core_extension_funk__apply(cause, funkable, args);
  } else if (raw__funkable__is_type(cause, funkable)) {
    f2ptr new_fiber = f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), funkable, args);
    f2__global_scheduler__complete_fiber(cause, new_fiber);
    f2ptr value = f2fiber__value(new_fiber, cause);
    f2fiber__keep_undead__set(new_fiber, cause, nil);
    if ((f2__fiber__paused(cause, new_fiber) != nil) &&
	raw__bug__is_type(cause, value)) {
      f2ptr bug_type    = f2__bug__bug_type(cause, value);
      s64   bug_type__i;
      if (raw__integer__is_type(cause, bug_type)) {
	bug_type__i = f2integer__i(bug_type, cause);
      } else {
	bug_type__i = 753;
      }
      return f2larva__new(cause, bug_type__i, value);
      //return f2larva__new(cause, 753, f2__bug__new(cause, f2integer__new(cause, 753), f2__frame__new(cause, f2list10__new(cause,
      //															  new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_in_fiber"),
      //															  new__symbol(cause, "funkname"),  new__symbol(cause, "f2__force_funk_apply"),
      //															  new__symbol(cause, "funkable"),  funkable,
      //															  new__symbol(cause, "args"),      args,
      //															  new__symbol(cause, "bug_found"), value))));
    }
    return value;
  } else {
    return f2larva__new(cause, 752, f2__bug__new(cause, f2integer__new(cause, 752), f2__frame__new(cause, f2list8__new(cause,
														       new__symbol(cause, "bug_type"),  new__symbol(cause, "tried_to_funk_unfunkable_funktion"),
														       new__symbol(cause, "funkname"),  new__symbol(cause, "f2__force_funk_apply"),
														       new__symbol(cause, "funkable"),  funkable,
														       new__symbol(cause, "args"),      args))));
  }
}

f2ptr f2__parallel_funk_apply(f2ptr cause, f2ptr fiber, f2ptr funkable, f2ptr args) {
  f2ptr new_fiber = f2__fiber_parallel(cause, cause, fiber, f2fiber__env(fiber, cause), funkable, args);
  f2fiber__keep_undead__set(new_fiber, cause, nil);
  return nil;
}

void f2fiber__force_funk(f2ptr fiber, f2ptr cause, f2ptr cfunkable, f2ptr args) {
  f2ptr env;
  if      (raw__funk__is_type(               cause, cfunkable)) {env = f2funk__env(    cfunkable, cause);}
  else if (raw__metro__is_type(              cause, cfunkable)) {env = raw__metro__env(cause, cfunkable);}
  else if (raw__cfunk__is_type(              cause, cfunkable)) {env = f2fiber__env(   fiber, cause);}
  else if (raw__metrocfunk__is_type(         cause, cfunkable)) {env = f2fiber__env(   fiber, cause);}
  else if (raw__core_extension_funk__is_type(cause, cfunkable)) {env = f2fiber__env(   fiber, cause);}
  else                                                          {error(nil, "f2fiber__force_funk error: cfunkable must be funk or metro.");}
  
  f2fiber__env__set(fiber, cause, env);
  f2fiber__args__set(fiber, cause, args);
  f2fiber__value__set(fiber, cause, cfunkable);
  //f2fiber__program_counter__set(fiber, cause, f2__compile__funk_bc(cause, nil));
  
  f2__fiber__bytecode_helper__funk__no_increment_pc_reg(fiber, cause, nil);
  //f2__global_scheduler__add_fiber(cause, fiber);
}

boolean_t raw__funkable__is_type(f2ptr cause, f2ptr exp) {
  return (exp && (raw__funk__is_type(               cause, exp) ||
		  raw__metro__is_type(              cause, exp) ||
		  raw__cfunk__is_type(              cause, exp) ||
		  raw__metrocfunk__is_type(         cause, exp) ||
		  raw__core_extension_funk__is_type(cause, exp)));
}

void debug__f2fiber__funk__unfunkable_error() {
  status("debug__f2fiber__funk__unfunkable_error here.");
}

void f2fiber__funk(f2ptr fiber, f2ptr cause, f2ptr cfunkable, f2ptr args) {
  f2fiber__args__set(           fiber, cause, args);
  f2fiber__value__set(          fiber, cause, cfunkable);
  {
    f2ptr body_bcs       = f2__compile__funk_bc(cause);
    f2ptr bytecode_array = raw__bytecodes__as__array(cause, body_bcs);
    f2fiber__program_counter__set(fiber, cause, raw__mutable_array_pointer__new(cause, bytecode_array, 0));
  }
  if (raw__funkable__is_type(cause, cfunkable)) {
    f2ptr env = raw__funkable__env(cause, cfunkable);
    if (env) {
      f2fiber__env__set(fiber, cause, env);
    }
  } else {
    status(  "[ERROR] f2fiber__funk error: cfunkable must be funk or metro.");
    printf("\n[ERROR] f2fiber__funk error: cfunkable must be funk or metro.\n"); fflush(stdout);
    printf("\n[ERROR] cfunkable="); fflush(stdout); f2__print(cause, cfunkable); fflush(stdout); printf("\n"); fflush(stdout);
    error(nil, "[ERROR] f2fiber__funk error: cfunkable must be funk or metro.");
    f2fiber__value__set(fiber, cause, f2larva__new(cause, 24, nil));
    debug__f2fiber__funk__unfunkable_error();
  }
}

f2ptr f2__simple_paused_fiber(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  return raw__fiber__new(cause, parent_fiber, parent_env, cfunkable, args);
}
def_pcfunk2(simple_paused_fiber, funk, args,
	    "Creates a fiber.  Does not branch cause.",
	    return f2__simple_paused_fiber(this_cause, this_cause, simple_fiber, simple_env, funk, args));

f2ptr f2__fiber_parallel(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  f2ptr new_fiber = f2__simple_paused_fiber(cause, execution_cause, parent_fiber, parent_env, cfunkable, args);
  f2__global_scheduler__add_fiber_parallel(cause, new_fiber);
  f2fiber__keep_undead__set(new_fiber, cause, nil);
  return new_fiber;
}
def_pcfunk2(fiber_parallel, funk, args,
	    "Starts a fiber that executes in parallel with the current fiber.  Does not branch cause.",
	    return f2__fiber_parallel(this_cause, this_cause, simple_fiber, simple_env, funk, args));

f2ptr f2__fiber_serial(f2ptr cause, f2ptr execution_cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  f2ptr new_fiber = f2__simple_paused_fiber(cause, execution_cause, parent_fiber, parent_env, cfunkable, args);
  f2__global_scheduler__add_fiber_serial(cause, new_fiber);
  return new_fiber;
}

f2ptr f2__fiber__imagine(f2ptr cause, f2ptr imagination_name, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr args) {
  f2ptr imaginary_cause = f2__cause__new_imaginary(cause, imagination_name);
  f2ptr new_fiber = f2__fiber_parallel(cause, imaginary_cause, parent_fiber, parent_env, cfunkable, args);
  return new_fiber;
}
def_pcfunk3(fiber__imagine, imagination_name, funk, args,
	    "",
	    return f2__fiber__imagine(this_cause, imagination_name, simple_fiber, simple_env, funk, args));

f2ptr f2__test_imagine(f2ptr cause, f2ptr imagination_name) {
  f2ptr i_cause = f2__cause__new_imaginary(cause, imagination_name);
  f2ptr test_array = raw__array__new(i_cause, 10);
  raw__array__elt__set(cause,   test_array, 0, f2integer__new(cause, 0));
  raw__array__elt__set(i_cause, test_array, 1, f2integer__new(cause, 1));
  f2__print(cause,   cause);
  f2__print(cause,   test_array);
  f2__print(cause,   raw__array__elt(cause,   test_array, 0));
  f2__print(cause,   i_cause);
  f2__print(i_cause, test_array);
  f2__print(cause,   raw__array__elt(i_cause, test_array, 1));
  return test_array;
}
def_pcfunk1(test_imagine, imagination_name,
	    "",
	    return f2__test_imagine(this_cause, imagination_name));

// sequence (array, list, doublelist, etc.)

u64 raw__simple_length(f2ptr cause, f2ptr seq) {
  if (!seq) {return 0;}
  switch (f2ptype__raw(seq, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__cons__is_type(cause, seq)) {
      return 1 + raw__simple_length(cause, f2cons__cdr(seq, cause));
    } else {
      return raw__array__length(cause, seq);
    }
  case ptype_chunk:  return f2chunk__length( seq, cause);
  case ptype_symbol: return f2symbol__length(seq, cause);
  case ptype_string: return f2string__length(seq, cause);
  default:
    return 0;
  }
}

f2ptr f2__simple_length(f2ptr cause, f2ptr seq) {
  if (!seq) {return f2integer__new(cause, 0);}
  switch (f2ptype__raw(seq, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__cons__is_type(cause, seq)) {
      u64 count = 0;
      f2ptr iter = seq;
      while(iter && raw__cons__is_type(cause, iter)) {
	count ++;
	iter = f2cons__cdr(iter, cause);
      }
      if (iter) {
	count += f2__simple_length(cause, iter);
      }
      return f2integer__new(cause, count);
    } else if (raw__doublelink__is_type(cause, seq)) {
      u64 count = 0;
      if (seq) {
	{
	  f2ptr iter = seq;
	  while (iter && raw__doublelink__is_type(cause, iter)) {
	    count ++;
	    iter = f2doublelink__prev(iter, cause);
	  }
	  if (iter) {
	    count += f2__simple_length(cause, iter);
	  }
	}
	{
	  f2ptr iter = f2doublelink__next(seq, cause);
	  while (iter && raw__doublelink__is_type(cause, iter)) {
	    count ++;
	    iter = f2doublelink__next(iter, cause);
	  }
	  if (iter) {
	    count += f2__simple_length(cause, iter);
	  }
	}
      }
      return f2integer__new(cause, count);
    } else {
      return f2__array__length(cause, seq);
    }
  case ptype_chunk:  return f2integer__new(cause, f2chunk__length(seq, cause));
  case ptype_string: return f2integer__new(cause, f2string__length(seq, cause));
  case ptype_symbol: return f2integer__new(cause, f2symbol__length(seq, cause));
  default:
    return f2integer__new(cause, 1);
  }
}
def_pcfunk1(simple_length, seq,
	    "",
	    return f2__simple_length(this_cause, seq));


// this funktion is deprecated; use object-get accessors at this point.
boolean_t raw__eltable_object__is_type(f2ptr cause, f2ptr this) {
  return (raw__array__is_type(cause, this) ||
	  raw__chunk__is_type(cause, this) ||
	  raw__conslist__is_type(cause, this));
}

// this funktion is deprecated; use object-get accessors at this point.
f2ptr raw__elt(f2ptr cause, f2ptr this, int raw_index) {
  if (! this) {
    printf ("\nseq_elt error: this argument is nil (must be cons, array, or chunk)."); fflush(stdout);
    return f2larva__new(cause, 1, nil);
    //return f2__argument_type_check_failure__exception__new(cause, this);
  }
  if (raw_index < 0) {
    printf("\nseq_elt error: index less than zero."); fflush(stdout);
    return f2larva__new(cause, 1, nil);
    //return f2__argument_type_check_failure__exception__new(cause, index);
  }
  switch (f2ptype__raw(this, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__cons__is_type(cause, this)) {
      int count = raw_index;
      f2ptr iter = this;
      while(count > 0) {
	count --;
	iter = f2cons__cdr(iter, cause);
	if (!iter || !raw__cons__is_type(cause, iter)) {
	  printf ("\nseq_elt error: list index out of range."); fflush(stdout);
	  return f2larva__new(cause, 1, nil);
	  //return f2__argument_type_check_failure__exception__new(cause, index);
	}
      }
      return f2cons__car(iter, cause);
    } else {
      if (raw_index >= raw__array__length(cause, this)) {
	printf("\nseq_elt error: array index out of range."); fflush(stdout);
	return f2larva__new(cause, 1, nil);
	//return f2__argument_type_check_failure__exception__new(cause, index);
      }
    }
    return raw__array__elt(cause, this, raw_index);
  case ptype_chunk:
    if (raw_index >= f2chunk__length(this, cause)) {
      printf("\nseq_elt error: chunk index out of range."); fflush(stdout);
      return f2larva__new(cause, 1, nil);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    return f2integer__new(cause, f2chunk__bit8__elt(this, raw_index, cause));
  default:
    printf("\nseq_elt error: sequence must be cons, array, or chunk."); fflush(stdout);
    return f2larva__new(cause, 1, nil);
    //return f2__argument_type_check_failure__exception__new(cause, this); // should return exception (once exceptions are defined)
    break;
  }
}

// this funktion is deprecated; use object-get accessors at this point.
f2ptr f2__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(eltable_object, this);
  assert_argument_type(integer,        index);
  int raw_index = f2integer__i(index, cause);
  return raw__elt(cause, this, raw_index);
}

f2ptr raw__conslist__reverse(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return this;
  }
  f2ptr new_seq = nil;
  f2ptr iter    = this;
  while (iter != nil) {
    f2ptr exp = f2cons__car(iter, cause);
    new_seq   = raw__cons__new(cause, exp, new_seq);
    iter      = f2cons__cdr(iter, cause);
  }
  return new_seq;
}

f2ptr f2__conslist__reverse(f2ptr cause, f2ptr this) {
  assert_argument_type(conslist, this);
  return raw__conslist__reverse(cause, this);
}

// this funktion is deprecated; use conslist__reverse or object-get accessors instead.
f2ptr f2__reverse(f2ptr cause, f2ptr this) {
  return f2__conslist__reverse(cause, this);
}
def_pcfunk1(reverse, this,
	    "reverses elements in a list.",
	    return f2__reverse(this_cause, this));

// deprecated and should be removed
f2ptr raw__seq_elt(f2ptr this, f2ptr index, f2ptr cause) {
  return f2__elt(cause, this, index);
}

// primobject thought_process

// primobject fiber

//boolean_t raw__fiberp(f2ptr x, f2ptr cause) {return (raw__primobjectp(x, cause) && f2primobject__is_fiber(x, cause));}

def_pcfunk1(exp__print, x,
	    "",
	    return f2__exp__print(this_cause, simple_fiber, x));
def_pcfunk1(write, x,
	    "",
	    return f2__write(this_cause, simple_fiber, x));
def_pcfunk2(fwrite, fptr, x,
	    "",
	    return f2__fwrite(this_cause, simple_fiber, fptr, x));

f2ptr f2__format(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp) {
  assert_argument_type(stream, stream);
  if (! exp) {
    f2__fwrite__raw_char(cause, stream, '[', NULL, nil);
    f2__fwrite__raw_char(cause, stream, ']', NULL, nil);
  } else {
    switch(f2ptype__raw(exp, cause)) {
    case ptype_string:f2__fwrite__raw_string(cause,        stream, exp, nil); break;
    default:          f2__fwrite(            cause, fiber, stream, exp     ); break;
    }
  }
  return exp;
}
def_pcfunk2(exp__format, fptr, x,
	    "",
	    return f2__format(this_cause, simple_fiber, fptr, x));

f2ptr f2__format__html(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp) {
  assert_argument_type(stream, stream);
  if (! exp) {
    f2__fwrite__raw_char(cause, stream, '[', NULL, __funk2.globalenv.true__symbol);
    f2__fwrite__raw_char(cause, stream, ']', NULL, __funk2.globalenv.true__symbol);
  } else {
    switch(f2ptype__raw(exp, cause)) {
    case ptype_string:f2__fwrite__raw_string(cause,        stream, exp, __funk2.globalenv.true__symbol); break;
    default:          f2__fwrite_html(       cause, fiber, stream, exp                                ); break;
    }
  }
  return exp;
}
def_pcfunk2(exp__format__html, stream, x,
	    "",
	    return f2__format__html(this_cause, simple_fiber, stream, x));

def_pcfunk2(exp__fwrite_html, stream, exp,
	    "",
	    return f2__fwrite_html(this_cause, simple_fiber, stream, exp));


f2ptr raw__mkdir(f2ptr cause, f2ptr directory_name) {
  u64 directory_name__utf8_length = raw__string__utf8_length(cause, directory_name);
  u8* directory_name__utf8_str    = (u8*)alloca(directory_name__utf8_length + 1);
  raw__string__utf8_str_copy(cause, directory_name, directory_name__utf8_str);
  directory_name__utf8_str[directory_name__utf8_length] = 0;
  int failure = mkdir((char*)directory_name__utf8_str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  if (failure) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),       new__symbol(cause, "could_not_create_directory"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "directory_name"), directory_name);
    f2ptr error_description;
    switch(errno) {
    case EACCES:       error_description = new__string(cause, "Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be created."); break;
    case EEXIST:       error_description = new__string(cause, "The named file exists."); break;
    case ELOOP:        error_description = new__string(cause, "A loop exists in symbolic links encountered during resolution of the path argument."); break;
    case EMLINK:       error_description = new__string(cause, "The link count of the parent directory would exceed {LINK_MAX}."); break;
    case ENAMETOOLONG: error_description = new__string(cause, "The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}."); break;
    case ENOENT:       error_description = new__string(cause, "A component of the path prefix specified by path does not name an existing directory or path is an empty string."); break;
    case ENOSPC:       error_description = new__string(cause, "The file system does not contain enough space to hold the contents of the new directory or to extend the parent directory of the new directory."); break;
    case ENOTDIR:      error_description = new__string(cause, "A component of the path prefix is not a directory."); break;
    case EROFS:        error_description = new__string(cause, "The parent directory resides on a read-only file system."); break;
      //case ELOOP:        error_description = new__string(cause, "More than {SYMLOOP_MAX} symbolic links were encountered during resolution of the path argument."); break;
      //case ENAMETOOLONG: error_description = new__string(cause, "As a result of encountering a symbolic link in resolution of the path argument, the length of the substituted pathname string exceeded {PATH_MAX}."); break;
    default:           error_description = new__string(cause, "unknown mkdir error."); break;
    }
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "description"), error_description);
    return f2larva__new(cause, 345, f2__bug__new(cause, f2integer__new(cause, 345), bug_frame));
  }
  return nil;
}

f2ptr f2__mkdir(f2ptr cause, f2ptr directory_name) {
  assert_argument_type(string, directory_name);
  return raw__mkdir(cause, directory_name);
}
def_pcfunk1(mkdir, directory_name,
	    "makes a directory.",
	    return f2__mkdir(this_cause, directory_name));

// this funktion is deprecated; use object-set mutators instead.
f2ptr f2__seq_elt__set(f2ptr this, f2ptr index, f2ptr cause, f2ptr value) {
  assert_argument_type(eltable_object, this);
  assert_argument_type(integer,        index);
  int raw_index = f2integer__i(index, cause);
  if (raw_index < 0) {
    printf("\nseq_elt-set error: index out of range."); fflush(stdout);
    return f2larva__new(cause, 2, nil);
    //return f2__argument_type_check_failure__exception__new(cause, index);
  }
  switch (f2ptype__raw(this, cause)) {
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__cons__is_type(cause, this)) {
      int count = f2integer__i(index, cause);
      f2ptr iter = this;
      while(count > 0) {
	count --;
	iter = f2cons__cdr(iter, cause);
	if (!iter || !raw__cons__is_type(cause, iter)) {
	  printf ("\nseq_elt-set error: list index out of range."); fflush(stdout);
	  return f2larva__new(cause, 1, nil);
	  //return f2__argument_type_check_failure__exception__new(cause, index);
	}
      }
      f2cons__car__set(iter, cause, value);
      return nil;
    } else {
      if (raw_index >= raw__array__length(cause, this)) {
	printf("\nseq_elt-set error: array index out of range."); fflush(stdout); 
	return f2larva__new(cause, 1, nil);
	//return f2__argument_type_check_failure__exception__new(cause, index);
      }
    }
    raw__array__elt__set(cause, this, raw_index, value);
    return nil;
  case ptype_chunk:
    if (raw_index >= f2chunk__length(this, cause)) {
      printf("\nseq_elt-set error: chunk index out of range."); fflush(stdout); 
      return f2larva__new(cause, 1, nil);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    if ((! value) || (! raw__integer__is_type(cause, value))) {
      printf("\nseq_elt-set error: chunk value must be integer."); fflush(stdout); 
      return f2larva__new(cause, 1, nil);
      //return f2__argument_type_check_failure__exception__new(cause, index);
    }
    f2chunk__bit8__elt__set(this, raw_index, cause, f2integer__i(value, cause));
    return nil;
  default:
    printf("\nseq_elt-set error: sequence must be list, array, or chunk."); fflush(stdout); 
    return f2larva__new(cause, 1, nil);
    //return f2__argument_type_check_failure__exception__new(cause, this); // should return exception (once exceptions are defined)
    //break;
  }
}

//def_pcfunk4(bytecode, command, arg0, arg1, arg2,
//	    printf("\ncreating user bytecode! "); fflush(stdout);
//	    return f2bytecode__new(this_cause, command, arg0, arg1, arg2));

def_pcfunk1(debug, value,
	    "",
	    printf("\ndebug: "); f2__write(this_cause, simple_fiber, value); fflush(stdout);
	    return value);

def_pcfunk1(trace, value,
	    "",
	    f2fiber__trace__set(simple_fiber, this_cause, raw__cons__new(this_cause, value, f2fiber__trace(simple_fiber, this_cause)));
	    return value);

boolean_t raw__scheduler_eq(f2ptr cause, f2ptr x, f2ptr y) {
  return (x == y);
}

u64 raw__scheduler_eq_hash_value(f2ptr cause, f2ptr x) {
  return (u64)(x);
}

boolean_t raw__eq(f2ptr cause, f2ptr x, f2ptr y) {
  if (x == y) {return boolean__true;}
  if (!x || !y) {return boolean__false;}
  if (f2ptype__raw(x, cause) != f2ptype__raw(y, cause)) {return boolean__false;}
  switch(f2ptype__raw(x, cause)) {
  case ptype_symbol:
    return f2__symbol__eq(cause, x, y);
  case ptype_integer:
    return (f2integer__i(x, cause) == f2integer__i(y, cause));
  case ptype_pointer:
    return (f2pointer__p(x, cause) == f2pointer__p(y, cause));
  case ptype_char:
    return (f2char__ch(x, cause) == f2char__ch(y, cause));
  case ptype_double:
    return (f2double__d(x, cause) == f2double__d(y, cause));
  case ptype_float:
    return (f2float__f(x, cause) == f2float__f(y, cause));
  case ptype_string:
    return f2__string__eq(cause, x, y);
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, x) &&
	raw__primobject__is_type(cause, y)) {
      if (f2primobject__is__cause_group(x, cause) &&
	  f2primobject__is__cause_group(y, cause)) {
	return (x == y);
      } else if (f2primobject__is__largeinteger(x, cause) &&
		 f2primobject__is__largeinteger(y, cause)) {
	return raw__largeinteger__equals(cause, x, y);
      }
    }
    return f2__object__eq(cause, x, y);
  case ptype_chunk:
    return (x == y);
  case ptype_free_memory:
    return boolean__false;
  case ptype_newly_allocated:
    return boolean__false;
  case ptype_scheduler_cmutex:
    return boolean__false;
  case ptype_cmutex:
    return boolean__false;
  case ptype_scheduler_creadwritelock:
    return boolean__false;
  case ptype_creadwritelock:
    return boolean__false;
  case ptype_mutable_array_pointer:
    return (x == y);
  case ptype_larva:
    return (f2larva__larva_type(x, cause) == f2larva__larva_type(y, cause));
  }
  error(nil, "eq error: argument type check failure."); fflush(stdout); 
  //return f2__argument_type_check_failure__exception__new(nil, x);
}

f2ptr f2__eq(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(raw__eq(cause, x, y));}
def_pcfunk2(eq, x, y,
	    "",
	    return f2__eq(this_cause, x, y));

boolean_t raw__contains(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr iter = this;
  while (iter) {
    f2ptr first = f2__first(cause, iter);
    if (raw__eq(cause, first, element)) {
      return boolean__true;
    }
    iter = f2__next(cause, iter);
  }
  return boolean__false;
}

f2ptr f2__contains(f2ptr cause, f2ptr this, f2ptr element) {
  return f2bool__new(raw__contains(cause, this, element));
}
def_pcfunk2(contains, this, element,
	    "",
	    return f2__contains(this_cause, this, element));

f2ptr f2__fopen(f2ptr cause, f2ptr filename, f2ptr mode) {
  assert_argument_type(string, filename);
  assert_argument_type(string, mode);
  u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
  u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
  raw__string__utf8_str_copy(cause, filename, (u8*)filename__utf8_str);
  filename__utf8_str[filename__utf8_length] = 0;
  u64 mode__utf8_length = raw__string__utf8_length(cause, mode);
  u8* mode__utf8_str    = (u8*)from_ptr(f2__malloc(mode__utf8_length + 1));
  raw__string__utf8_str_copy(cause, mode, mode__utf8_str);
  mode__utf8_str[mode__utf8_length] = 0;
  f2ptr fptr = f2pointer__new(cause, to_ptr(fopen((char*)filename__utf8_str, (char*)mode__utf8_str)));
  f2__free(to_ptr(filename__utf8_str));
  f2__free(to_ptr(mode__utf8_str));
  return fptr;
}
def_pcfunk2(fopen, filename, mode,
	    "",
	    return f2__fopen(this_cause, filename, mode));

f2ptr f2__fclose(f2ptr cause, f2ptr fptr) {
  assert_argument_type(pointer, fptr);
  return f2integer__new(cause, fclose((FILE*)from_ptr(f2pointer__p(fptr, cause))));
}
def_pcfunk1(fclose, fptr,
	    "",
	    return f2__fclose(this_cause, fptr));

f2ptr f2__compile(f2ptr cause, f2ptr fiber, f2ptr exp, f2ptr protect_environment) {
  boolean_t is_funktional = boolean__true;
  return raw__compile(cause, fiber, exp, (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL);
}
def_pcfunk2(compile, exp, protect_environment,
	    "",
	    return f2__compile(this_cause, simple_fiber, exp, protect_environment));

f2ptr f2__identity(f2ptr cause, f2ptr exp) {return exp;}
def_pcfunk1(identity, exp,
	    "",
	    return f2__identity(this_cause, exp));

#define PRIME_NUMBER__16_BIT 65521

u64 raw__random(u64 max_value) {
  int random_value = (uint)(rand() * PRIME_NUMBER__16_BIT) % max_value;
  random_value = (random_value < 0) ? (-random_value) : random_value;
  return random_value;
}

f2ptr f2__random(f2ptr cause, f2ptr max_value) {
  assert_argument_type(integer, max_value);
  int raw_max_value = f2integer__i(max_value, cause);
  return f2integer__new(cause, raw__random(raw_max_value));
}
def_pcfunk1(random, max_value,
	    "generate a random integer between 0 and sup_integer - 1.",
	    return f2__random(this_cause, max_value));

f2ptr f2__chunk_copy(f2ptr cause, f2ptr init) {
  assert_argument_type(chunk, init);
  return f2chunk__new_copy(cause, init);
}
def_pcfunk1(chunk__copy, init,
	    "",
	    return f2__chunk_copy(this_cause, init));

f2ptr f2__chunk__read_bit8(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((u8)f2chunk__bit8__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit8, chunk, offset,
	    "",
	    return f2__chunk__read_bit8(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit8_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit8__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit8_integer, chunk, offset, value,
	    "",
	    return f2__chunk__write_bit8_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit8_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((char)f2chunk__bit8__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit8_signed, chunk, offset,
	    "",
	    return f2__chunk__read_bit8_signed(this_cause, chunk, offset));

f2ptr f2__chunk__read_bit16(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, f2chunk__bit16__elt(chunk, f2integer__i(offset, cause), cause));}
def_pcfunk2(chunk__read_bit16, chunk, offset,
	    "",
	    return f2__chunk__read_bit16(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit16_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit16__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit16_integer, chunk, offset, value,
	    "",
	    return f2__chunk__write_bit16_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit16_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((s16)f2chunk__bit16__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit16_signed, chunk, offset,
	    "",
	    return f2__chunk__read_bit16_signed(this_cause, chunk, offset));

f2ptr f2__chunk__read_bit32(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((u32)f2chunk__bit32__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit32, chunk, offset,
	    "",
	    return f2__chunk__read_bit32(this_cause, chunk, offset));

f2ptr f2__chunk__write_bit32_integer(f2ptr cause, f2ptr chunk, f2ptr offset, f2ptr value) {f2chunk__bit32__elt__set(chunk, f2integer__i(offset, cause), cause, f2integer__i(value, cause)); return nil;}
def_pcfunk3(chunk__write_bit32_integer, chunk, offset, value,
	    "",
	    return f2__chunk__write_bit32_integer(this_cause, chunk, offset, value));

f2ptr f2__chunk__read_bit32_signed(f2ptr cause, f2ptr chunk, f2ptr offset) {return f2integer__new(cause, ((short)f2chunk__bit32__elt(chunk, f2integer__i(offset, cause), cause)));}
def_pcfunk2(chunk__read_bit32_signed, chunk, offset,
	    "",
	    return f2__chunk__read_bit32_signed(this_cause, chunk, offset));

def_pcfunk1(demetropolize_once, exp,
	    "",
	    return f2__demetropolize_once(this_cause, simple_fiber, simple_env, exp));

f2ptr f2__demetropolize_full(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  f2ptr demetropolize_result = f2__demetropolize_full__with_status(cause, fiber, env, exp);
  if (raw__larva__is_type(cause, demetropolize_result)) {
    return demetropolize_result;
  }
  return f2cons__cdr(demetropolize_result, cause);
}
def_pcfunk1(demetropolize_full, exp,
	    "",
	    return f2__demetropolize_full(this_cause, simple_fiber, simple_env, exp));

def_pcfunk0(this__cause,
	    "",
	    return this_cause);
def_pcfunk0(this__env,
	    "",
	    return f2fiber__env(simple_fiber, this_cause));
def_pcfunk0(this__args,
	    "",
	    return simple_args);

f2ptr f2__exps_demetropolize_full(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  assert_argument_type_or_nil(cons, exp);
  if (exp == nil) {
    return nil;
  }
  f2ptr demetropolize_result = f2__demetropolize_full__with_status(cause, fiber, env, f2cons__car(exp, cause));
  if (raw__larva__is_type(cause, demetropolize_result)) {
    return demetropolize_result;
  }
  f2ptr demetropolize_exps_result = f2__exps_demetropolize_full(cause, fiber, env, f2cons__cdr(exp, cause));
  if (raw__larva__is_type(cause, demetropolize_exps_result)) {
    return demetropolize_exps_result;
  }
  return raw__cons__new(cause,
			f2cons__cdr(demetropolize_result, cause),
			demetropolize_exps_result);
}

def_pcfunk1(exps_demetropolize_full, exp,
	    "",
	    return f2__exps_demetropolize_full(this_cause, simple_fiber, simple_env, exp));

def_pcfunk2(compile__special_symbol_exp, exp, protect_environment,
	    "",
	    return f2__compile__special_symbol_exp(this_cause, simple_fiber, exp, (protect_environment != nil), (protect_environment == nil), NULL, NULL, nil, NULL));

f2ptr f2__lookup_funkvar(f2ptr cause, f2ptr env, f2ptr funkvar, f2ptr undefined_value) {
  f2ptr value = environment__lookup_funkvar_value(cause, env, funkvar);
  if (raw__larva__is_type(cause, value)) {return undefined_value;}
  return value;
}
def_pcfunk2(lookup_funkvar, funkvar, undefined_value,
	    "",
	    return f2__lookup_funkvar(this_cause, simple_env, funkvar, undefined_value));

f2ptr f2__jump_to_chunk(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp, f2ptr args) {
  if(exp == nil) {
    printf("\njump-to-pointer error: exp is nil."); 
    return f2larva__new(cause, 12356, nil);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
  switch(f2ptype__raw(exp, cause)) {
  case ptype_pointer: {
    cfunkptr_t jump = (cfunkptr_t)from_ptr(f2pointer__p(exp, cause));
    return jump(cause, fiber, env, args);
  }
  case ptype_chunk:
    return f2chunk__cfunk_jump(exp, cause, fiber, env, args);
  default:
    printf("\njump-to-pointer error: exp must be pointer or chunk.");
    return f2larva__new(cause, 1135, nil);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
}
def_pcfunk2(jump_to_chunk, p, args,
	    "",
	    return f2__jump_to_chunk(this_cause, simple_fiber, simple_env, p, args));

f2ptr f2__coerce_to_int(f2ptr cause, f2ptr exp) {
  if(! exp) {
    printf("\ncoerce-to-int error: exp is nil.");
    return f2larva__new(cause, 151515, nil);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
  switch(f2ptype__raw(exp, cause)) {
  case ptype_integer: return exp;
  case ptype_pointer: return f2integer__new(cause, (long)f2pointer__p(exp, cause));
  default:
    printf("\ncoerce-to-int error: exp must be integer or pointer.");
    return f2larva__new(cause, 13512, nil);
    //return f2__argument_type_check_failure__exception__new(cause, exp);
  }
}
def_pcfunk1(coerce_to_int, exp,
	    "",
	    return f2__coerce_to_int(this_cause, exp));

def_pcfunk1(funkall__raw_c_funk__v__v,      cfunk_ptr, "",                                                                  (* (void   (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(); return nil);
def_pcfunk2(funkall__raw_c_funk__v__i,      cfunk_ptr, a0, "",                                                              (* (void   (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ii,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__iid,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(int,    int,    double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2double__d(a2, this_cause));  return nil);
def_pcfunk4(funkall__raw_c_funk__v__iii,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iiii,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iiip,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(int,    int,    int,    ptr))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2pointer__p(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__iiiip,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(int,    int,    int,    int,    ptr))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2pointer__p(a4, this_cause)); return nil);
def_pcfunk7(funkall__raw_c_funk__v__iiiiip, cfunk_ptr, a0, a1, a2, a3, a4, a5, "",                                          (* (void   (*)(int,    int,    int,    int,    int,    ptr))  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause), f2pointer__p(a5, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__id,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(int,    double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__idd,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(int,    double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__iddd,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(int,    double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__idddd,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(int,    double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ip,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause))); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ipp,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))); return nil);
def_pcfunk5(funkall__raw_c_funk__v__ippp,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(int,    void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ipppp,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(int,    void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause))); return nil);
def_pcfunk2(funkall__raw_c_funk__v__p,      cfunk_ptr, a0, "",                                                              (* (void   (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause))); return nil);
def_pcfunk3(funkall__raw_c_funk__v__pi,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(void*,  int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), f2integer__i(a1, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__pp,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause))); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ppp,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))); return nil);
def_pcfunk5(funkall__raw_c_funk__v__pppp,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ppppp,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(void*,  void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause))); return nil);
def_pcfunk2(funkall__raw_c_funk__v__d,      cfunk_ptr, a0, "",                                                              (* (void   (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__dd,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__ddd,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__dddd,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause)); return nil);
def_pcfunk2(funkall__raw_c_funk__v__f,      cfunk_ptr, a0, "",                                                              (* (void   (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause)); return nil);
def_pcfunk3(funkall__raw_c_funk__v__ff,     cfunk_ptr, a0, a1, "",                                                          (* (void   (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause)); return nil);
def_pcfunk4(funkall__raw_c_funk__v__fff,    cfunk_ptr, a0, a1, a2, "",                                                      (* (void   (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause)); return nil);
def_pcfunk5(funkall__raw_c_funk__v__ffff,   cfunk_ptr, a0, a1, a2, a3, "",                                                  (* (void   (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause)); return nil);
def_pcfunk6(funkall__raw_c_funk__v__fffff,  cfunk_ptr, a0, a1, a2, a3, a4, "",                                              (* (void   (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause)); return nil);
def_pcfunk1(funkall__raw_c_funk__i__v,      cfunk_ptr, "",                         return f2integer__new(this_cause,        (* (int    (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__i__i,      cfunk_ptr, a0, "",                     return f2integer__new(this_cause,        (* (int    (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__ii,     cfunk_ptr, a0, a1, "",                 return f2integer__new(this_cause,        (* (int    (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__iii,    cfunk_ptr, a0, a1, a2, "",             return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__iiii,   cfunk_ptr, a0, a1, a2, a3, "",         return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk7(funkall__raw_c_funk__i__iiiiip, cfunk_ptr, a0, a1, a2, a3, a4, a5, "", return f2integer__new(this_cause,        (* (int    (*)(int,    int,    int,    int,    int,    void*))from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause), from_ptr(f2pointer__p(a5, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__i__ip,     cfunk_ptr, a0, a1, "",                 return f2integer__new(this_cause,        (* (int    (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)))));
def_pcfunk4(funkall__raw_c_funk__i__ipp,    cfunk_ptr, a0, a1, a2, "",             return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)))));
def_pcfunk5(funkall__raw_c_funk__i__ippp,   cfunk_ptr, a0, a1, a2, a3, "",         return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)))));
def_pcfunk6(funkall__raw_c_funk__i__ipppp,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2integer__new(this_cause,        (* (int    (*)(int,    void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause)))));
def_pcfunk2(funkall__raw_c_funk__i__p,      cfunk_ptr, a0, "",                     return f2integer__new(this_cause,        (* (int    (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__i__pp,     cfunk_ptr, a0, a1, "",                 return f2integer__new(this_cause,        (* (int    (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)))));
def_pcfunk4(funkall__raw_c_funk__i__ppp,    cfunk_ptr, a0, a1, a2, "",             return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)))));
def_pcfunk5(funkall__raw_c_funk__i__pppp,   cfunk_ptr, a0, a1, a2, a3, "",         return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)))));
def_pcfunk6(funkall__raw_c_funk__i__ppppp,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2integer__new(this_cause,        (* (int    (*)(void*,  void*,  void*,  void*,  void*))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause)), from_ptr(f2pointer__p(a4, this_cause)))));
def_pcfunk2(funkall__raw_c_funk__i__d,      cfunk_ptr, a0, "",                     return f2integer__new(this_cause,        (* (int    (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__dd,     cfunk_ptr, a0, a1, "",                 return f2integer__new(this_cause,        (* (int    (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__ddd,    cfunk_ptr, a0, a1, a2, "",             return f2integer__new(this_cause,        (* (int    (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__dddd,   cfunk_ptr, a0, a1, a2, a3, "",         return f2integer__new(this_cause,        (* (int    (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2integer__new(this_cause,        (* (int    (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__i__f,      cfunk_ptr, a0, "",                     return f2integer__new(this_cause,        (* (int    (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__i__ff,     cfunk_ptr, a0, a1, "",                 return f2integer__new(this_cause,        (* (int    (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__i__fff,    cfunk_ptr, a0, a1, a2, "",             return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__i__ffff,   cfunk_ptr, a0, a1, a2, a3, "",         return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__i__fffff,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2integer__new(this_cause,        (* (int    (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__d__v,      cfunk_ptr, "",                         return f2double__new(this_cause,         (* (double (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__d__i,      cfunk_ptr, a0, "",                     return f2double__new(this_cause,         (* (double (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__ii,     cfunk_ptr, a0, a1, "",                 return f2double__new(this_cause,         (* (double (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__iii,    cfunk_ptr, a0, a1, a2, "",             return f2double__new(this_cause,         (* (double (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__iiii,   cfunk_ptr, a0, a1, a2, a3, "",         return f2double__new(this_cause,         (* (double (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2double__new(this_cause,         (* (double (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__d__d,      cfunk_ptr, a0, "",                     return f2double__new(this_cause,         (* (double (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__dd,     cfunk_ptr, a0, a1, "",                 return f2double__new(this_cause,         (* (double (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__ddd,    cfunk_ptr, a0, a1, a2, "",             return f2double__new(this_cause,         (* (double (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__dddd,   cfunk_ptr, a0, a1, a2, a3, "",         return f2double__new(this_cause,         (* (double (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2double__new(this_cause,         (* (double (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__d__f,      cfunk_ptr, a0, "",                     return f2double__new(this_cause,         (* (double (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__d__ff,     cfunk_ptr, a0, a1, "",                 return f2double__new(this_cause,         (* (double (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__d__fff,    cfunk_ptr, a0, a1, a2, "",             return f2double__new(this_cause,         (* (double (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__d__ffff,   cfunk_ptr, a0, a1, a2, a3, "",         return f2double__new(this_cause,         (* (double (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__d__fffff,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2double__new(this_cause,         (* (double (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__f__v,      cfunk_ptr, "",                         return f2float__new(this_cause,          (* (float  (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )()));
def_pcfunk2(funkall__raw_c_funk__f__i,      cfunk_ptr, a0, "",                     return f2float__new(this_cause,          (* (float  (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__ii,     cfunk_ptr, a0, a1, "",                 return f2float__new(this_cause,          (* (float  (*)(int,    int))                                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__iii,    cfunk_ptr, a0, a1, a2, "",             return f2float__new(this_cause,          (* (float  (*)(int,    int,    int))                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__iiii,   cfunk_ptr, a0, a1, a2, a3, "",         return f2float__new(this_cause,          (* (float  (*)(int,    int,    int,    int))                  from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__iiiii,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2float__new(this_cause,          (* (float  (*)(int,    int,    int,    int,    int))          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), f2integer__i(a1, this_cause), f2integer__i(a2, this_cause), f2integer__i(a3, this_cause), f2integer__i(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__f__d,      cfunk_ptr, a0, "",                     return f2float__new(this_cause,          (* (float  (*)(double))                                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__dd,     cfunk_ptr, a0, a1, "",                 return f2float__new(this_cause,          (* (float  (*)(double, double))                               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__ddd,    cfunk_ptr, a0, a1, a2, "",             return f2float__new(this_cause,          (* (float  (*)(double, double, double))                       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__dddd,   cfunk_ptr, a0, a1, a2, a3, "",         return f2float__new(this_cause,          (* (float  (*)(double, double, double, double))               from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__ddddd,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2float__new(this_cause,          (* (float  (*)(double, double, double, double, double))       from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2double__d(a0, this_cause),  f2double__d(a1, this_cause),  f2double__d(a2, this_cause),  f2double__d(a3, this_cause),  f2double__d(a4, this_cause))));
def_pcfunk2(funkall__raw_c_funk__f__f,      cfunk_ptr, a0, "",                     return f2float__new(this_cause,          (* (float  (*)(float))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause))));
def_pcfunk3(funkall__raw_c_funk__f__ff,     cfunk_ptr, a0, a1, "",                 return f2float__new(this_cause,          (* (float  (*)(float,  float))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause))));
def_pcfunk4(funkall__raw_c_funk__f__fff,    cfunk_ptr, a0, a1, a2, "",             return f2float__new(this_cause,          (* (float  (*)(float,  float,  float))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause))));
def_pcfunk5(funkall__raw_c_funk__f__ffff,   cfunk_ptr, a0, a1, a2, a3, "",         return f2float__new(this_cause,          (* (float  (*)(float,  float,  float,  float))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause))));
def_pcfunk6(funkall__raw_c_funk__f__fffff,  cfunk_ptr, a0, a1, a2, a3, a4, "",     return f2float__new(this_cause,          (* (float  (*)(float,  float,  float,  float,  float))        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2float__f(a0, this_cause),   f2float__f(a1, this_cause),   f2float__f(a2, this_cause),   f2float__f(a3, this_cause),   f2float__f(a4, this_cause))));
def_pcfunk1(funkall__raw_c_funk__p__v,      cfunk_ptr, "",                         return f2pointer__new(this_cause, to_ptr((* (void*  (*)())                                             from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )())));
def_pcfunk2(funkall__raw_c_funk__p__i,      cfunk_ptr, a0, "",                     return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int))                                          from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause)))));
def_pcfunk3(funkall__raw_c_funk__p__ip,     cfunk_ptr, a0, a1, "",                 return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int,    void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause))))));
def_pcfunk4(funkall__raw_c_funk__p__ipp,    cfunk_ptr, a0, a1, a2, "",             return f2pointer__new(this_cause, to_ptr((* (void*  (*)(int,    void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(f2integer__i(a0, this_cause), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))))));
def_pcfunk2(funkall__raw_c_funk__p__p,      cfunk_ptr, a0, "",                     return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*))                                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause))))));
def_pcfunk3(funkall__raw_c_funk__p__pp,     cfunk_ptr, a0, a1, "",                 return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*))                                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause))))));
def_pcfunk4(funkall__raw_c_funk__p__ppp,    cfunk_ptr, a0, a1, a2, "",             return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*,  void*))                        from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause))))));
def_pcfunk5(funkall__raw_c_funk__p__pppp,   cfunk_ptr, a0, a1, a2, a3, "",         return f2pointer__new(this_cause, to_ptr((* (void*  (*)(void*,  void*,  void*,  void*))                from_ptr(f2pointer__p(cfunk_ptr, this_cause)) )(from_ptr(f2pointer__p(a0, this_cause)), from_ptr(f2pointer__p(a1, this_cause)), from_ptr(f2pointer__p(a2, this_cause)), from_ptr(f2pointer__p(a3, this_cause))))));

def_pcfunk2(tensor__new_from_array_of_integer_dimensions, dimensions, fill_element, "", return f2__tensor__new_from_array_of_integer_dimensions(this_cause, dimensions, fill_element));
def_pcfunk2(tensor__elt_from_array_of_integer_indices,    this, indices, "",            return f2tensor__elt_from_array_of_integer_indices(this, indices, this_cause));

def_pcfunk0(system__peer_command_server__port_num,
	    "",
	    return f2integer__new(this_cause, __funk2.command_line.peer_command_server__port_num));

def_pcfunk0(system__gethostname,
	    "",
	    char hostname[1024];
	    if (gethostname(hostname, 1023) != 0) {
	      return nil;
	    }
	    return new__string(this_cause, hostname));

// funk2_node_handler

f2ptr f2__funk2_node_handler__know_of_node(f2ptr cause, f2ptr hostname, f2ptr port_num) {
  // note that this is not cmutexed!
  if (! raw__string__is_type(cause, hostname)) {
    status("funk2_node_handler__know_of_node error: hostname must be a string.");
    return -1;
  }
  if (! raw__integer__is_type(cause, port_num)) {
    status("funk2_node_handler__know_of_node error: port_num must be an integer.");
    return -2;
  }
  client_id_t client_id;
  u64 hostname__utf8_length = raw__string__utf8_length(cause, hostname);
  u8* hostname__utf8_str = alloca(hostname__utf8_length + 1);
  raw__string__utf8_str_copy(hostname, cause, (u8*)hostname__utf8_str);
  hostname__utf8_str[hostname__utf8_length] = 0;
  struct hostent* host_entity = gethostbyname((char*)hostname__utf8_str);
  if (host_entity == NULL) {
    status("couldn't lookup funk2 node with gethostbyname: '%s'\n", hostname__utf8_str);
    return -3;
  }
  u32 netorder_ip_addr = *((u32*)(host_entity->h_addr_list[0]));
  u32 hostorder_ip_addr = ntohl(netorder_ip_addr);
  u8 ip_addr[4];
  ip_addr[0] = ((u8*)(&hostorder_ip_addr))[3];
  ip_addr[1] = ((u8*)(&hostorder_ip_addr))[2];
  ip_addr[2] = ((u8*)(&hostorder_ip_addr))[1];
  ip_addr[3] = ((u8*)(&hostorder_ip_addr))[0];
  u16 port_num__i = f2integer__i(port_num, cause);
  client_id__init(&client_id, (u8*)"", ip_addr, port_num__i);
  computer_id_t computer_id = funk2_node_handler__add_node(&(__funk2.node_handler), 0, &client_id);
  status("added knowledge of funk2 node: '%s' %d.%d.%d.%d:%d", hostname__utf8_str, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port_num__i);
  return f2integer__new(cause, computer_id);
}

def_pcfunk2(funk2_node_handler__know_of_node, hostname, port_num,
	    "",
	    return f2__funk2_node_handler__know_of_node(this_cause, hostname, port_num));

void raw__send_request_register_peer(f2ptr cause, computer_id_t computer_id, node_id_t node_id, u8* ip_addr, u16 port_num) {
  funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
  status("sending request register peer packet [to computer_id=" u64__fstr "]: node_id=" u64__fstr " %d.%d.%d.%d:%d", (u64)computer_id, (u64)node_id, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3], port_num);
  send_packet__request__register_peer(cause, funk2_node, node_id, ip_addr, port_num);
}

f2ptr f2__send_request_register_peer(f2ptr cause, f2ptr computer_id, f2ptr node_id, f2ptr ip_addr, f2ptr port_num) {
  assert_argument_type(integer, computer_id);
  assert_argument_type(pointer, node_id);
  assert_argument_type(array,   ip_addr);
  assert_argument_type(integer, port_num);
  u8 u8_ip_addr[4];
  u8_ip_addr[0] = f2integer__i(raw__array__elt(cause, ip_addr, 0), cause);
  u8_ip_addr[1] = f2integer__i(raw__array__elt(cause, ip_addr, 1), cause);
  u8_ip_addr[2] = f2integer__i(raw__array__elt(cause, ip_addr, 2), cause);
  u8_ip_addr[3] = f2integer__i(raw__array__elt(cause, ip_addr, 3), cause);
  raw__send_request_register_peer(cause, f2integer__i(computer_id, cause), f2pointer__p(node_id, cause), u8_ip_addr, f2integer__i(port_num, cause));
  return nil;
}
def_pcfunk4(send_request_register_peer, computer_id, node_id, ip_addr, port_num,
	    "",
	    return f2__send_request_register_peer(this_cause, computer_id, node_id, ip_addr, port_num););

f2ptr f2__larva(f2ptr cause, f2ptr type, f2ptr bug) {
  assert_argument_type(       integer, type);
  assert_argument_type_or_nil(bug, bug);
  u32 raw_type = f2integer__i(type, cause);
  return f2larva__new(cause, raw_type, bug);
}
def_pcfunk2(larva, type, bug,
	    "",
	    return f2__larva(this_cause, type, bug));

f2ptr raw__funkable__env(f2ptr cause, f2ptr funkable) {
  if      (raw__funk__is_type(               cause, funkable)) {return f2funk__env(    funkable, cause);}
  else if (raw__metro__is_type(              cause, funkable)) {return raw__metro__env(cause, funkable);}
  else if (raw__cfunk__is_type(              cause, funkable)) {return nil;}
  else if (raw__metrocfunk__is_type(         cause, funkable)) {return nil;}
  else if (raw__core_extension_funk__is_type(cause, funkable)) {return nil;}
  error(nil, "raw__funkable__env error: funkable is invalid type.");
  // we should never get here.
  return nil;
}

f2ptr f2__funkable__env(f2ptr cause, f2ptr this) {
  assert_argument_type(funkable, this);
  return raw__funkable__env(cause, this);
}


f2ptr raw__funkable__name(f2ptr cause, f2ptr this) {
  if (raw__cfunk__is_type(cause, this)) {
    return f2cfunk__name(this, cause);
  } else if (raw__funk__is_type(cause, this)) {
    return f2funk__name(this, cause);
  } else if (raw__metro__is_type(cause, this)) {
    return raw__metro__name(cause, this);
  } else if (raw__core_extension_funk__is_type(cause, this)) {
    return raw__core_extension_funk__name(cause, this);
  }
  error(nil, "raw__funkable__name error: this is invalid type.");
}

f2ptr f2__funkable__name(f2ptr cause, f2ptr this) {
  assert_argument_type(funkable, this);
  return raw__funkable__name(cause, this);
}


f2ptr raw__funkable__args(f2ptr cause, f2ptr this) {
  if (raw__cfunk__is_type(cause, this)) {
    return f2cfunk__args(this, cause);
  } else if (raw__funk__is_type(cause, this)) {
    return f2funk__args(this, cause);
  } else if (raw__metro__is_type(cause, this)) {
    return raw__metro__args(cause, this);
  } else if (raw__core_extension_funk__is_type(cause, this)) {
    return raw__core_extension_funk__args(cause, this);
  }
  error(nil, "raw__funkable__args error: this is invalid type.");
}

f2ptr f2__funkable__args(f2ptr cause, f2ptr this) {
  assert_argument_type(funkable, this);
  return raw__funkable__args(cause, this);
}


// this interface is deprecated.
// abstract sequence getters and setters (first, next, prev)

f2ptr f2__first(f2ptr cause, f2ptr exp) {
  if (raw__cons__is_type(cause, exp)) {
    return f2cons__car(exp, cause);
  } else if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__value(exp, cause);
  } else if (raw__list__is_type(cause, exp)) {
    return f2__list__car(cause, exp);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk1(first, exp,
	    "",
	    return f2__first(this_cause, exp));

f2ptr f2__first__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__cons__is_type(cause, exp)) {
    return f2cons__car__set(exp, cause, value);
  } else if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__value__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk2(first__set, exp, value,
	    "",
	    return f2__first__set(this_cause, exp, value));

f2ptr f2__next(f2ptr cause, f2ptr exp) {
  if (raw__cons__is_type(cause, exp)) {
    return f2cons__cdr(exp, cause);
  } else if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__next(exp, cause);
  } else if (raw__list__is_type(cause, exp)) {
    return f2__list__cdr(cause, exp);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk1(next, exp,
	    "",
	    return f2__next(this_cause, exp));

f2ptr f2__next__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__cons__is_type(cause, exp)) {
    return f2cons__cdr__set(exp, cause, value);
  } else if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__next__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk2(next__set, exp, value,
	    "",
	    return f2__next__set(this_cause, exp, value));

f2ptr f2__prev(f2ptr cause, f2ptr exp) {
  if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__prev(exp, cause);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk1(prev, exp,
	    "",
	    return f2__prev(this_cause, exp));

f2ptr f2__prev__set(f2ptr cause, f2ptr exp, f2ptr value) {
  if (raw__doublelink__is_type(cause, exp)) {
    return f2doublelink__prev__set(exp, cause, value);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
def_pcfunk2(prev__set, exp, value,
	    "",
	    return f2__prev__set(this_cause, exp, value));

u64 raw__eq_hash_value(f2ptr cause, f2ptr exp) {
  if (! exp) {
    return 0;
  }
  ptype_t ptype = f2ptype__raw(exp, cause);
  switch(ptype) {
  case ptype_integer:                  return raw__integer__eq_hash_value(         cause, exp);
  case ptype_double:                   return raw__double__eq_hash_value(          cause, exp);
  case ptype_float:                    return raw__float__eq_hash_value(           cause, exp);
  case ptype_pointer:                  return raw__pointer__eq_hash_value(         cause, exp);
  case ptype_scheduler_cmutex:         return raw__scheduler_cmutex__eq_hash_value(cause, exp);
  case ptype_cmutex:                   return raw__cmutex__eq_hash_value(          cause, exp);
  case ptype_scheduler_creadwritelock: return raw__scheduler_creadwritelock__eq_hash_value(          cause, exp);
  case ptype_creadwritelock:           return raw__creadwritelock__eq_hash_value(          cause, exp);
  case ptype_char:                     return raw__char__eq_hash_value(            cause, exp);
  case ptype_string:                   return raw__string__eq_hash_value(          cause, exp);
  case ptype_symbol:                   return raw__symbol__eq_hash_value(          cause, exp);
  case ptype_chunk:                    return raw__chunk__eq_hash_value(           cause, exp);
  case ptype_simple_array:
  case ptype_traced_array: {
    if (raw__primobject__is_type(cause, exp)) {
      if (f2primobject__is__cause_group(exp, cause)) {
	return (u64)exp;
      } else if (f2primobject__is__largeinteger(exp, cause)) {
	return raw__largeinteger__equals_hash_value(cause, exp);
      }
    }
    f2ptr hash_value = f2__object__eq_hash_value(cause, exp);
    u64 hash_value__i = 0;
    if (raw__integer__is_type(cause, hash_value)) {
      hash_value__i = f2integer__i(hash_value, cause);
    }
    return hash_value__i;
  }
  case ptype_larva:                 return raw__larva__eq_hash_value(                cause, exp);
  case ptype_mutable_array_pointer: return raw__mutable_array_pointer__eq_hash_value(cause, exp);
  case ptype_free_memory:
  case ptype_newly_allocated: 
  default:
    status("raw__eq_hash_value error: found invalid ptype (" u64__fstr ")", (u64)ptype);
    error(nil, "raw__eq_hash_value error: found invalid ptype.");
    break;
  }
  return 0; // should never get here.
}

f2ptr f2__eq_hash_value(f2ptr cause, f2ptr exp) {
  return f2integer__new(cause, raw__eq_hash_value(cause, exp));
}
def_pcfunk1(eq_hash_value, exp,
	    "",
	    return f2__eq_hash_value(this_cause, exp));

boolean_t raw__equals(f2ptr cause, f2ptr x, f2ptr y) {
  if (x == y) {
    return boolean__true;
  }
  if ((! x) || (! y)) {
    return boolean__false;
  }
  ptype_t x_ptype = f2ptype__raw(x, cause);
  ptype_t y_ptype = f2ptype__raw(y, cause);
  if (x_ptype != y_ptype) {
    return boolean__false;
  }
  switch(x_ptype) {
  case ptype_integer:                  return raw__integer__equals(                 cause, x, y);
  case ptype_double:                   return raw__double__equals(                  cause, x, y);
  case ptype_float:                    return raw__float__equals(                   cause, x, y);
  case ptype_pointer:                  return raw__pointer__equals(                 cause, x, y);
  case ptype_scheduler_cmutex:         return raw__scheduler_cmutex__equals(        cause, x, y);
  case ptype_cmutex:                   return raw__cmutex__equals(                  cause, x, y);
  case ptype_scheduler_creadwritelock: return raw__scheduler_creadwritelock__equals(cause, x, y);
  case ptype_creadwritelock:           return raw__creadwritelock__equals(          cause, x, y);
  case ptype_char:                     return raw__char__equals(                    cause, x, y);
  case ptype_string:                   return raw__string__equals(                  cause, x, y);
  case ptype_symbol:                   return raw__symbol__equals(                  cause, x, y);
  case ptype_chunk:                    return raw__chunk__equals(                   cause, x, y);
  case ptype_simple_array:
  case ptype_traced_array:             return f2__object__equals(                   cause, x, y);
  case ptype_larva:                    return raw__larva__equals(                   cause, x, y);
  case ptype_mutable_array_pointer:    return raw__mutable_array_pointer__equals(   cause, x, y);
  default:                             return boolean__false;
  }
}

f2ptr f2__equals(f2ptr cause, f2ptr x, f2ptr y) {
  return f2bool__new(raw__equals(cause, x, y));
}
def_pcfunk2(equals, x, y,
	    "",
	    return f2__equals(this_cause, x, y));

f2ptr f2__is_funktional(f2ptr cause, f2ptr fiber, f2ptr exp) {
  boolean_t exp__is_funktional = boolean__true;
  f2ptr result = raw__compile(cause, fiber, exp, boolean__false, boolean__false, NULL, &exp__is_funktional, nil, NULL);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return f2bool__new(exp__is_funktional);
}
def_pcfunk1(is_funktional, exp,
	    "",
	    return f2__is_funktional(this_cause, simple_fiber, exp));


f2ptr raw__string__read(f2ptr cause, f2ptr this) {
  f2ptr stream = f2__string_stream(cause, this);
  return f2__stream__try_read(cause, stream);
}

f2ptr f2__string__read(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string__read(cause, this);
}

void raw__memory__test(f2ptr cause) {
  funk2_memory__memory_test(&(__funk2.memory));
}

f2ptr f2__memory__test(f2ptr cause) {
  funk2_memory__memory_test(&(__funk2.memory));
  return nil;
}
def_pcfunk0(memory__test,
	    "Asserts that memory tests pass, otherwise logs debugging information regarding the bug and stops Funk2 with fatal error.",
	    return f2__memory__test(this_cause));


def_pcfunk0(memory__assert_valid,
	    "Asserts that memory tests pass, otherwise returns a larva with low-level memory system debugging information.",
	    return f2__memory__assert_valid(this_cause));


// **

void f2__primcfunks__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  // system
  
  f2__primcfunk__init__defragment__fix_pointers(system__node_id);
  f2__primcfunk__init__defragment__fix_pointers(system__environment);
  
  // funk2 pointer (f2ptr)
  
  f2__primcfunk__init__defragment__fix_pointers(pointer);
  f2__primcfunk__init__defragment__fix_pointers(deref_pointer);
  
  // ptype
  
  // integer
  
  // double
  
  // float
  
  // pointer
  
  // cmutex
  
  // string
  
  //f2__funktional_primcfunk__init__2(string__equals,                this, that);
  f2__primcfunk__init__defragment__fix_pointers(string__new_raw_c_string);
  f2__primcfunk__init__defragment__fix_pointers(string__new_from_raw_c_string);
  
  // symbol
  
  //f2__funktional_primcfunk__init__2(symbol__eq,     this, that);
  
  // chunk
  
  f2__primcfunk__init__defragment__fix_pointers(chunk__copy);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit8);
  f2__primcfunk__init__defragment__fix_pointers(chunk__write_bit8_integer);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit8_signed);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit16);
  f2__primcfunk__init__defragment__fix_pointers(chunk__write_bit16_integer);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit16_signed);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit32);
  f2__primcfunk__init__defragment__fix_pointers(chunk__write_bit32_integer);
  f2__primcfunk__init__defragment__fix_pointers(chunk__read_bit32_signed);
  f2__primcfunk__init__defragment__fix_pointers(chunk__new_compiled_from_funk);
  
  // simple_array
  
  
  // traced_array
  
  
  f2__primcfunk__init__defragment__fix_pointers(mkdir);
  
  // cons
  
  f2__primcfunk__init__defragment__fix_pointers(conslist);
  f2__primcfunk__init__defragment__fix_pointers(conslist__as__array);
  f2__primcfunk__init__defragment__fix_pointers(conslist__first_n);
  f2__primcfunk__init__defragment__fix_pointers(conslistlist__append);
  
  f2__primcfunk__init__defragment__fix_pointers(immutable_conslist);
  
  // cause
  
  // fiber
  
  f2__primcfunk__init__defragment__fix_pointers(sleep_for_nanoseconds_without_yield);
  
  // time
  
  f2__primcfunk__init__defragment__fix_pointers(time);

  
  
  // other complex functions
  
  f2__primcfunk__init__defragment__fix_pointers(simple_paused_fiber);
  f2__primcfunk__init__defragment__fix_pointers(fiber_parallel);
  f2__primcfunk__init__defragment__fix_pointers(fiber__imagine);
  f2__primcfunk__init__defragment__fix_pointers(test_imagine);
  
  f2__primcfunk__init__defragment__fix_pointers(simple_length);
  
  f2__primcfunk__init__defragment__fix_pointers(integer__greater_than);
  f2__primcfunk__init__defragment__fix_pointers(integer__less_than);
  f2__primcfunk__init__defragment__fix_pointers(integer__add);
  f2__primcfunk__init__defragment__fix_pointers(integer__subtract);
  f2__primcfunk__init__defragment__fix_pointers(integer__multiply);
  f2__primcfunk__init__defragment__fix_pointers(integer__add_double);
  f2__primcfunk__init__defragment__fix_pointers(integer__subtract_double);
  f2__primcfunk__init__defragment__fix_pointers(integer__divide_by_integer);
  f2__primcfunk__init__defragment__fix_pointers(integer__divide_by_double);
  f2__primcfunk__init__defragment__fix_pointers(integer__equal_sign);
  f2__primcfunk__init__defragment__fix_pointers(integer__not_equal_sign);
  f2__primcfunk__init__defragment__fix_pointers(integer__bitshift_left);
  f2__primcfunk__init__defragment__fix_pointers(integer__bitshift_right);
  f2__primcfunk__init__defragment__fix_pointers(integer__bit_and);
  f2__primcfunk__init__defragment__fix_pointers(integer__bit_or);
  f2__primcfunk__init__defragment__fix_pointers(integer__bit_xor);
  f2__primcfunk__init__defragment__fix_pointers(integer__bit_not);
  f2__primcfunk__init__defragment__fix_pointers(pointer__greater_than);
  f2__primcfunk__init__defragment__fix_pointers(pointer__less_than);
  f2__primcfunk__init__defragment__fix_pointers(pointer__subtract);
  f2__primcfunk__init__defragment__fix_pointers(pointer__equal_sign);
  f2__primcfunk__init__defragment__fix_pointers(pointer__not_equal_sign);
  f2__primcfunk__init__defragment__fix_pointers(null);
  f2__primcfunk__init__defragment__fix_pointers(not);
  
  f2__primcfunk__init__defragment__fix_pointers(eq);
  f2__primcfunk__init__defragment__fix_pointers(contains);
  
  f2__primcfunk__init__defragment__fix_pointers(reverse);
  
  f2__primcfunk__init__defragment__fix_pointers(exp__print);
  f2__primcfunk__init__defragment__fix_pointers(write);
  f2__primcfunk__init__defragment__fix_pointers(fwrite);
  f2__primcfunk__init__defragment__fix_pointers(exp__format);
  f2__primcfunk__init__defragment__fix_pointers(exp__format__html);
  f2__primcfunk__init__defragment__fix_pointers(exp__fwrite_html);
  
  f2__primcfunk__init__defragment__fix_pointers(debug);
  f2__primcfunk__init__defragment__fix_pointers(trace);
  f2__primcfunk__init__defragment__fix_pointers(compile);
  
  f2__primcfunk__init__defragment__fix_pointers(fopen);
  f2__primcfunk__init__defragment__fix_pointers(fclose);
  
  f2__primcfunk__init__defragment__fix_pointers(this__cause);
  f2__primcfunk__init__defragment__fix_pointers(this__env);
  f2__primcfunk__init__defragment__fix_pointers(this__args);
  
  f2__primcfunk__init__defragment__fix_pointers(random);
  
  f2__primcfunk__init__defragment__fix_pointers(identity);
  
  f2__primcfunk__init__defragment__fix_pointers(demetropolize_once);
  f2__primcfunk__init__defragment__fix_pointers(demetropolize_full);
  f2__primcfunk__init__defragment__fix_pointers(exps_demetropolize_full);
  f2__primcfunk__init__defragment__fix_pointers(compile__special_symbol_exp);
  f2__primcfunk__init__defragment__fix_pointers(lookup_funkvar);
  f2__primcfunk__init__defragment__fix_pointers(jump_to_chunk);
  f2__primcfunk__init__defragment__fix_pointers(coerce_to_int);
  
  //f2__primcfunk__init(memory_image__save);
  //f2__primcfunk__init(memory_image__load);
  
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__v);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__i);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__id);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__idd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__idddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ipp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ippp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ipppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iid);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iiip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iiiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iiiip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__iiiiip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__p);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__pi);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__pp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__pppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ppppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__d);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__dd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__dddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ddddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__f);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__fff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__ffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__v__fffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__v);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__i);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__iii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__iiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__iiiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__iiiiip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ipp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ippp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ipppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__p);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__pp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__pppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ppppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__d);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__dd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__dddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ddddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__f);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__fff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__ffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__i__fffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__v);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__i);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__ii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__iii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__iiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__iiiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__d);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__dd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__ddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__dddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__ddddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__f);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__ff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__fff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__ffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__d__fffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__v);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__i);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__ii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__iii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__iiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__iiiii);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__d);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__dd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__ddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__dddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__ddddd);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__f);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__ff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__fff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__ffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__f__fffff);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__v);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__i);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__ip);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__ipp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__p);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__pp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__ppp);
  f2__primcfunk__init__defragment__fix_pointers(funkall__raw_c_funk__p__pppp);
  
  f2__primcfunk__init__defragment__fix_pointers(system__memorypool__total_global_memory);
  f2__primcfunk__init__defragment__fix_pointers(system__memorypool__total_free_memory);
  
  f2__primcfunk__init__defragment__fix_pointers(integer__to_float);
  f2__primcfunk__init__defragment__fix_pointers(integer__to_double);
  f2__primcfunk__init__defragment__fix_pointers(double__to_integer);
  f2__primcfunk__init__defragment__fix_pointers(double__to_float);
  f2__primcfunk__init__defragment__fix_pointers(double__add_double);
  f2__primcfunk__init__defragment__fix_pointers(double__subtract_double);
  f2__primcfunk__init__defragment__fix_pointers(double__multiply_by_double);
  f2__primcfunk__init__defragment__fix_pointers(double__divide_by_double);
  f2__primcfunk__init__defragment__fix_pointers(double__add_integer);
  f2__primcfunk__init__defragment__fix_pointers(double__subtract_integer);
  f2__primcfunk__init__defragment__fix_pointers(double__multiply_by_integer);
  f2__primcfunk__init__defragment__fix_pointers(double__divide_by_integer);
  f2__primcfunk__init__defragment__fix_pointers(float__to_integer);
  f2__primcfunk__init__defragment__fix_pointers(float__to_double);
  
  f2__primcfunk__init__defragment__fix_pointers(tensor__new_from_array_of_integer_dimensions);
  f2__primcfunk__init__defragment__fix_pointers(tensor__elt_from_array_of_integer_indices);
  
  f2__primcfunk__init__defragment__fix_pointers(funk2_node_handler__know_of_node);
  f2__primcfunk__init__defragment__fix_pointers(send_request_register_peer);
  
  f2__primcfunk__init__defragment__fix_pointers(system__peer_command_server__port_num);
  f2__primcfunk__init__defragment__fix_pointers(system__gethostname);
  
  f2__primcfunk__init__defragment__fix_pointers(larva);
  
  f2__primcfunk__init__defragment__fix_pointers(first);
  f2__primcfunk__init__defragment__fix_pointers(first__set);
  f2__primcfunk__init__defragment__fix_pointers(next);
  f2__primcfunk__init__defragment__fix_pointers(next__set);
  f2__primcfunk__init__defragment__fix_pointers(prev);
  f2__primcfunk__init__defragment__fix_pointers(prev__set);
  
  f2__primcfunk__init__defragment__fix_pointers(eq_hash_value);
  f2__primcfunk__init__defragment__fix_pointers(equals);
  //f2__primcfunk__init__1(is_funktional, exp);
  
  f2__primcfunk__init__defragment__fix_pointers(memory__test);
  f2__primcfunk__init__defragment__fix_pointers(memory__assert_valid);
}

void f2__primcfunks__reinitialize_globalvars() {
  // system
  
  f2__primcfunk__init__0(system__node_id);
  f2__primcfunk__init__1(system__environment, node_id);
  
  // funk2 pointer (f2ptr)
  
  f2__primcfunk__init__1(pointer, exp);
  f2__primcfunk__init__1(deref_pointer, pointer);
  
  // ptype
  
  // integer
  
  // double
  
  // float
  
  // pointer
  
  // cmutex
  
  // string
  
  //f2__funktional_primcfunk__init__2(string__equals,                this, that);
  f2__primcfunk__init__1(string__new_raw_c_string,      this);
  f2__primcfunk__init__1(string__new_from_raw_c_string, c_string);
  
  // symbol
  
  //f2__funktional_primcfunk__init__2(symbol__eq,     this, that);
  
  // chunk
  
  f2__primcfunk__init(chunk__copy);
  f2__primcfunk__init(chunk__read_bit8);
  f2__primcfunk__init(chunk__write_bit8_integer);
  f2__primcfunk__init(chunk__read_bit8_signed);
  f2__primcfunk__init(chunk__read_bit16);
  f2__primcfunk__init(chunk__write_bit16_integer);
  f2__primcfunk__init(chunk__read_bit16_signed);
  f2__primcfunk__init(chunk__read_bit32);
  f2__primcfunk__init(chunk__write_bit32_integer);
  f2__primcfunk__init(chunk__read_bit32_signed);
  f2__primcfunk__init(chunk__new_compiled_from_funk);
  
  // simple_array
  
  
  // traced_array
  
  
  f2__primcfunk__init__1(mkdir, directory_name);
  
  // cons
  
  f2__primcfunk__init__0_and_rest(conslist,             conslist);
  f2__primcfunk__init__1(         conslist__as__array,  this);
  f2__primcfunk__init__2(         conslist__first_n,    this, n);
  f2__primcfunk__init__1(         conslistlist__append, this);
  
  f2__primcfunk__init__0_and_rest(immutable_conslist, seq);
  
  // cause
  
  // fiber
  
  f2__primcfunk__init__1(sleep_for_nanoseconds_without_yield, nanoseconds);
  
  // time
  
  f2__primcfunk__init__0(time);

  
  
  // other complex functions
  
  f2__primcfunk__init(simple_paused_fiber);
  f2__primcfunk__init(fiber_parallel);
  f2__primcfunk__init(fiber__imagine);
  f2__primcfunk__init(test_imagine);
  
  f2__primcfunk__init__1(simple_length, seq);
  
  f2__primcfunk__init__2(integer__greater_than,      x, y);
  f2__primcfunk__init__2(integer__less_than,         x, y);
  f2__primcfunk__init__2(integer__add,               x, y);
  f2__primcfunk__init__2(integer__subtract,          x, y);
  f2__primcfunk__init__2(integer__multiply,          x, y);
  f2__primcfunk__init__2(integer__add_double,        x, y);
  f2__primcfunk__init__2(integer__subtract_double,   x, y);
  f2__primcfunk__init__2(integer__divide_by_integer, x, y);
  f2__primcfunk__init__2(integer__divide_by_double,  x, y);
  f2__primcfunk__init__2(integer__equal_sign,        x, y);
  f2__primcfunk__init__2(integer__not_equal_sign,    x, y);
  f2__primcfunk__init__2(integer__bitshift_left,     x, y);
  f2__primcfunk__init__2(integer__bitshift_right,    x, y);
  f2__primcfunk__init__2(integer__bit_and,           x, y);
  f2__primcfunk__init__2(integer__bit_or,            x, y);
  f2__primcfunk__init__2(integer__bit_xor,           x, y);
  f2__primcfunk__init__1(integer__bit_not,           x);
  f2__primcfunk__init__2(pointer__greater_than,      x, y);
  f2__primcfunk__init__2(pointer__less_than,         x, y);
  f2__primcfunk__init__2(pointer__subtract,          x, y);
  f2__primcfunk__init__2(pointer__equal_sign,        x, y);
  f2__primcfunk__init__2(pointer__not_equal_sign,    x, y);
  f2__primcfunk__init__1(null,                       x);
  f2__primcfunk__init__1(not,                        x);
  
  f2__primcfunk__init__2(eq,                         x, y);
  f2__primcfunk__init__2(contains, this, element);
  
  f2__primcfunk__init__1(reverse, this);
  
  f2__primcfunk__init__1(exp__print, exp);
  f2__primcfunk__init(write);
  f2__primcfunk__init(fwrite);
  f2__primcfunk__init(exp__format);
  f2__primcfunk__init(exp__format__html);
  f2__primcfunk__init(exp__fwrite_html);
  
  f2__primcfunk__init(debug);
  f2__primcfunk__init(trace);
  f2__primcfunk__init(compile);
  
  f2__primcfunk__init(fopen);
  f2__primcfunk__init(fclose);
  
  f2__primcfunk__init__0(this__cause);
  f2__primcfunk__init__0(this__env);
  f2__primcfunk__init__0(this__args);
  
  f2__primcfunk__init__1(random, sup_integer);
  
  f2__primcfunk__init(identity);
  
  f2__primcfunk__init(demetropolize_once);
  f2__primcfunk__init(demetropolize_full);
  f2__primcfunk__init(exps_demetropolize_full);
  f2__primcfunk__init(compile__special_symbol_exp);
  f2__primcfunk__init(lookup_funkvar);
  f2__primcfunk__init(jump_to_chunk);
  f2__primcfunk__init(coerce_to_int);
  
  //f2__primcfunk__init(memory_image__save);
  //f2__primcfunk__init(memory_image__load);
  
  f2__primcfunk__init(funkall__raw_c_funk__v__v);
  f2__primcfunk__init(funkall__raw_c_funk__v__i);
  f2__primcfunk__init(funkall__raw_c_funk__v__id);
  f2__primcfunk__init(funkall__raw_c_funk__v__idd);
  f2__primcfunk__init(funkall__raw_c_funk__v__iddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__idddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ip);
  f2__primcfunk__init(funkall__raw_c_funk__v__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ippp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ipppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iid);
  f2__primcfunk__init(funkall__raw_c_funk__v__iii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__iiiiip);
  f2__primcfunk__init(funkall__raw_c_funk__v__p);
  f2__primcfunk__init(funkall__raw_c_funk__v__pi);
  f2__primcfunk__init(funkall__raw_c_funk__v__pp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__pppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__ppppp);
  f2__primcfunk__init(funkall__raw_c_funk__v__d);
  f2__primcfunk__init(funkall__raw_c_funk__v__dd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__v__f);
  f2__primcfunk__init(funkall__raw_c_funk__v__ff);
  f2__primcfunk__init(funkall__raw_c_funk__v__fff);
  f2__primcfunk__init(funkall__raw_c_funk__v__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__v__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__i__v);
  f2__primcfunk__init(funkall__raw_c_funk__i__i);
  f2__primcfunk__init(funkall__raw_c_funk__i__ii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__i__iiiiip);
  f2__primcfunk__init(funkall__raw_c_funk__i__ip);
  f2__primcfunk__init(funkall__raw_c_funk__i__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ippp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ipppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__p);
  f2__primcfunk__init(funkall__raw_c_funk__i__pp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__pppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__ppppp);
  f2__primcfunk__init(funkall__raw_c_funk__i__d);
  f2__primcfunk__init(funkall__raw_c_funk__i__dd);
  f2__primcfunk__init(funkall__raw_c_funk__i__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__i__f);
  f2__primcfunk__init(funkall__raw_c_funk__i__ff);
  f2__primcfunk__init(funkall__raw_c_funk__i__fff);
  f2__primcfunk__init(funkall__raw_c_funk__i__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__i__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__d__v);
  f2__primcfunk__init(funkall__raw_c_funk__d__i);
  f2__primcfunk__init(funkall__raw_c_funk__d__ii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__d__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__d__d);
  f2__primcfunk__init(funkall__raw_c_funk__d__dd);
  f2__primcfunk__init(funkall__raw_c_funk__d__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__d__f);
  f2__primcfunk__init(funkall__raw_c_funk__d__ff);
  f2__primcfunk__init(funkall__raw_c_funk__d__fff);
  f2__primcfunk__init(funkall__raw_c_funk__d__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__d__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__f__v);
  f2__primcfunk__init(funkall__raw_c_funk__f__i);
  f2__primcfunk__init(funkall__raw_c_funk__f__ii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iiii);
  f2__primcfunk__init(funkall__raw_c_funk__f__iiiii);
  f2__primcfunk__init(funkall__raw_c_funk__f__d);
  f2__primcfunk__init(funkall__raw_c_funk__f__dd);
  f2__primcfunk__init(funkall__raw_c_funk__f__ddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__dddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__ddddd);
  f2__primcfunk__init(funkall__raw_c_funk__f__f);
  f2__primcfunk__init(funkall__raw_c_funk__f__ff);
  f2__primcfunk__init(funkall__raw_c_funk__f__fff);
  f2__primcfunk__init(funkall__raw_c_funk__f__ffff);
  f2__primcfunk__init(funkall__raw_c_funk__f__fffff);
  f2__primcfunk__init(funkall__raw_c_funk__p__v);
  f2__primcfunk__init(funkall__raw_c_funk__p__i);
  f2__primcfunk__init(funkall__raw_c_funk__p__ip);
  f2__primcfunk__init(funkall__raw_c_funk__p__ipp);
  f2__primcfunk__init(funkall__raw_c_funk__p__p);
  f2__primcfunk__init(funkall__raw_c_funk__p__pp);
  f2__primcfunk__init(funkall__raw_c_funk__p__ppp);
  f2__primcfunk__init(funkall__raw_c_funk__p__pppp);
  
  f2__primcfunk__init__1(system__memorypool__total_global_memory, index);
  f2__primcfunk__init__1(system__memorypool__total_free_memory,   index);
  
  f2__primcfunk__init(integer__to_float);
  f2__primcfunk__init(integer__to_double);
  f2__primcfunk__init(double__to_integer);
  f2__primcfunk__init(double__to_float);
  f2__primcfunk__init(double__add_double);
  f2__primcfunk__init(double__subtract_double);
  f2__primcfunk__init(double__multiply_by_double);
  f2__primcfunk__init(double__divide_by_double);
  f2__primcfunk__init(double__add_integer);
  f2__primcfunk__init(double__subtract_integer);
  f2__primcfunk__init(double__multiply_by_integer);
  f2__primcfunk__init(double__divide_by_integer);
  f2__primcfunk__init(float__to_integer);
  f2__primcfunk__init(float__to_double);
  
  f2__primcfunk__init(tensor__new_from_array_of_integer_dimensions);
  f2__primcfunk__init(tensor__elt_from_array_of_integer_indices);
  
  f2__primcfunk__init(funk2_node_handler__know_of_node);
  f2__primcfunk__init__4(send_request_register_peer, computer_id, node_id, ip_addr, port_num);
  
  f2__primcfunk__init(system__peer_command_server__port_num);
  f2__primcfunk__init(system__gethostname);
  
  f2__primcfunk__init__2(larva, larva_type, bug);
  
  f2__primcfunk__init(first);
  f2__primcfunk__init(first__set);
  f2__primcfunk__init(next);
  f2__primcfunk__init(next__set);
  f2__primcfunk__init(prev);
  f2__primcfunk__init(prev__set);
  
  f2__primcfunk__init__1(eq_hash_value, exp);
  f2__primcfunk__init__2(equals, x, y);
  //f2__primcfunk__init__1(is_funktional, exp);
  
  f2__primcfunk__init__0(memory__test);
  f2__primcfunk__init__0(memory__assert_valid);
}

void f2__primcfunks__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks", "", &f2__primcfunks__reinitialize_globalvars, &f2__primcfunks__defragment__fix_pointers);
  
  f2__primcfunks__reinitialize_globalvars();
}


