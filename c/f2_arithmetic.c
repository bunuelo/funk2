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

// number interface (integer, double, float)

boolean_t raw__number__is_type(f2ptr cause, f2ptr exp) {
  return (raw__integer__is_type(cause, exp) ||
	  raw__double__is_type( cause, exp) ||
	  raw__float__is_type(  cause, exp) ||
	  raw__largeinteger__is_type(  cause, exp));
}

f2ptr f2__number__is_type(f2ptr cause, f2ptr exp) {return f2bool__new(raw__number__is_type(cause, exp));}
def_pcfunk1(number__is_type, exp, return f2__number__is_type(this_cause, exp));

double raw__number__to_double(f2ptr cause, f2ptr this) {
  double d;
  if      (raw__double__is_type(      cause, this)) {d = f2double__d( this, cause);}
  else if (raw__float__is_type(       cause, this)) {d = f2float__f(  this, cause);}
  else if (raw__integer__is_type(     cause, this)) {d = f2integer__i(this, cause);}
  else if (raw__largeinteger__is_type(cause, this)) {d = raw__largeinteger__to_double(cause, this);}
  else                                              {d = 0.0;}
  return d;
}

f2ptr f2__number__to_double(f2ptr cause, f2ptr this) {return f2double__new(cause, raw__number__to_double(cause, this));}
def_pcfunk1(number__to_double, this, return f2__number__to_double(this_cause, this));

// number multiply

f2ptr f2__integer__multiply_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__multiply_overflows(value, number_value)) {
      return f2integer__new(cause, value * number_value);
    } else {
      return f2__largeinteger__multiply(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__multiply(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__multiply_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value * raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__multiply_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value * (float)raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__largeinteger__multiply_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__integer__multiply_by_number(cause, number, this);
  } else if (raw__double__is_type(cause, number)) {
    return f2__double__multiply_by_number(cause, number, this);
  } else if (raw__float__is_type(cause, number)) {
    return f2__float__multiply_by_number(cause, number, this);
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__multiply(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__multiply_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__multiply_by_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__multiply_by_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__multiply_by_number(cause, this, number);
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__multiply_by_number(cause, this, number);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk2(number__multiply_by_number, this, number, return f2__number__multiply_by_number(this_cause, this, number));

// number divide

f2ptr f2__integer__divide_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2integer__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__divide(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__divide_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value / raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__divide_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value / raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__largeinteger__divide_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__largeinteger__divide(cause, this, f2__largeinteger__new(cause, number));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, raw__largeinteger__to_double(cause, this) / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, (float)raw__largeinteger__to_double(cause, this) / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__divide(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__divide_by_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__divide_by_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__divide_by_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__divide_by_number(cause, this, number);
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__divide_by_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__divide_by_number, this, number, return f2__number__divide_by_number(this_cause, this, number));

// number add

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

f2ptr f2__integer__add_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, number_value)) {
      return f2integer__new(cause, value + number_value);
    } else {
      return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__add_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value + raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__add_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value + (float)raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__pointer__add_integer(f2ptr cause, f2ptr this, f2ptr integer) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return f2pointer__new(cause, f2pointer__p(this, cause) + f2integer__i(integer, cause));
}

f2ptr f2__largeinteger__add_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__integer__add_number(cause, number, this);
  } else if (raw__double__is_type(cause, number)) {
    return f2__double__add_number(cause, number, this);
  } else if (raw__float__is_type(cause, number)) {
    return f2__float__add_number(cause, number, this);
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__add(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__add_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__add_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__add_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__add_number(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__integer__is_type(cause, number)) {
      return f2__pointer__add_integer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__add_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__add_number, this, number, return f2__number__add_number(this_cause, this, number));

// number subtract

f2ptr f2__integer__subtract_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, -number_value) && ((number_value == 0) || (-number_value != number_value))) {
      return f2integer__new(cause, value - f2integer__i(number, cause));
    } else {
      return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__subtract_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value - raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__subtract_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value - (float)raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__pointer__subtract_integer(f2ptr cause, f2ptr this, f2ptr integer) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return f2pointer__new(cause, f2pointer__p(this, cause) - f2integer__i(integer, cause));
}

f2ptr f2__largeinteger__subtract_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__largeinteger__subtract(cause, this, f2__largeinteger__new(cause, number));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, raw__largeinteger__to_double(cause, this) - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, ((float)raw__largeinteger__to_double(cause, this)) - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__subtract(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__subtract_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__subtract_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__subtract_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__subtract_number(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__integer__is_type(cause, number)) {
      return f2__pointer__subtract_integer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__subtract_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__subtract_number, this, number, return f2__number__subtract_number(this_cause, this, number));

// number greater_than

f2ptr f2__integer__greater_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__greater_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__greater_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__greater_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > ((float)raw__largeinteger__to_double(cause, number)));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__pointer__greater_than_pointer(f2ptr cause, f2ptr this, f2ptr integer) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__pointer__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(f2pointer__p(this, cause) > f2pointer__p(integer, cause));
}

f2ptr f2__largeinteger__greater_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__largeinteger__greater_than(cause, this, f2__largeinteger__new(cause, number));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(raw__largeinteger__to_double(cause, this) > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(((float)raw__largeinteger__to_double(cause, this)) > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__greater_than(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__greater_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__greater_than_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__greater_than_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__greater_than_number(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__greater_than_pointer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__greater_than_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__greater_than_number, this, number, return f2__number__greater_than_number(this_cause, this, number));

// number less_than

f2ptr f2__integer__less_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__less_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__less_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__less_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < ((float)raw__largeinteger__to_double(cause, number)));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__pointer__less_than_pointer(f2ptr cause, f2ptr this, f2ptr integer) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__pointer__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(f2pointer__p(this, cause) < f2pointer__p(integer, cause));
}

f2ptr f2__largeinteger__less_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__largeinteger__less_than(cause, this, f2__largeinteger__new(cause, number));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(raw__largeinteger__to_double(cause, this) < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(((float)raw__largeinteger__to_double(cause, this)) < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__less_than(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__less_than_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__less_than_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__less_than_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__less_than_number(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__less_than_pointer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__less_than_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__less_than_number, this, number, return f2__number__less_than_number(this_cause, this, number));

// number equals

f2ptr f2__integer__equals_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__integer__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__equals(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__double__equals_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__double__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == raw__largeinteger__to_double(cause, number));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__float__equals_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__float__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == ((float)raw__largeinteger__to_double(cause, number)));
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__pointer__equals_pointer(f2ptr cause, f2ptr this, f2ptr integer) {
  if ((! raw__pointer__is_type(cause, this)) ||
      (! raw__pointer__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(f2pointer__p(this, cause) == f2pointer__p(integer, cause));
}

f2ptr f2__largeinteger__equals_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (! raw__largeinteger__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  if (raw__integer__is_type(cause, number)) {
    return f2__largeinteger__equals(cause, this, f2__largeinteger__new(cause, number));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(raw__largeinteger__to_double(cause, this) == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(((float)raw__largeinteger__to_double(cause, this)) == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__equals(cause, this, number);
  }
  return f2larva__new(cause, 1);
}

f2ptr f2__number__equals_number(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__equals_number(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__equals_number(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__equals_number(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__equals_pointer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__equals_number(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__equals_number, this, number, return f2__number__equals_number(this_cause, this, number));

// number square_root

f2ptr f2__number__square_root(f2ptr cause, f2ptr this) {
  if (raw__integer__is_type(cause, this)) {
    s64 i = f2integer__i(this, cause);
    if (i < 0) {
      return f2larva__new(cause, 5);
    }
    return f2integer__new(cause, u64__sqrt(i));
  } else if (raw__double__is_type(cause, this)) {
    double d = f2double__d(this, cause);
    if (d < 0) {
      return f2larva__new(cause, 5);
    }
    return f2double__new(cause, sqrt(d));
  } else if (raw__float__is_type(cause, this)) {
    float f = f2float__f(this, cause);
    if (f < 0) {
      return f2larva__new(cause, 5);
    }
    return f2float__new(cause, sqrtf(f));
  } else if (raw__largeinteger__is_type(cause, this)) {
    if (f2__largeinteger__is_negative(cause, this) != nil) {
      return f2larva__new(cause, 5);
    }
    return f2__largeinteger__square_root(cause, this);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk1(number__square_root, this, return f2__number__square_root(this_cause, this));

// **

void f2__arithmetic__reinitialize_globalvars() {
}

void f2__arithmetic__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "arithmetic", "", &f2__arithmetic__reinitialize_globalvars);
  
  f2__arithmetic__reinitialize_globalvars();
  
  f2__primcfunk__init__1(number__is_type,             exp,          "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__1(number__to_double,           this,         "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__multiply_by_number,  this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__divide_by_number,    this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__add_number,          this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__subtract_number,     this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__greater_than_number, this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__less_than_number,    this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__equals_number,       this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__1(number__square_root,         this,         "(cfunk defined in f2_arithmetic.c)");
  
}
