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


double raw__number__as__double(f2ptr cause, f2ptr this) {
  if      (raw__double__is_type(      cause, this)) {return raw__double__as__double(      cause, this);}
  else if (raw__float__is_type(       cause, this)) {return raw__float__as__double(       cause, this);}
  else if (raw__integer__is_type(     cause, this)) {return raw__integer__as__double(     cause, this);}
  else if (raw__largeinteger__is_type(cause, this)) {return raw__largeinteger__as__double(cause, this);}
  error(nil, "raw__number__as__double error: value is not a number.");
}

f2ptr f2__number__as__double(f2ptr cause, f2ptr this) {
  if (! raw__number__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2double__new(cause, raw__number__as__double(cause, this));
}
def_pcfunk1(number__as__double, this, return f2__number__as__double(this_cause, this));

// number multiply

f2ptr f2__number__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__multiplied_by(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__multiplied_by(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__multiplied_by(cause, this, number);
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__multiplied_by(cause, this, number);
  } else {
    return f2larva__new(cause, 1);
  }
}
def_pcfunk2(number__multiplied_by, this, number, return f2__number__multiplied_by(this_cause, this, number));

// number divide

f2ptr f2__number__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__divided_by(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__divided_by(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__divided_by(cause, this, number);
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__divided_by(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__divided_by, this, number, return f2__number__divided_by(this_cause, this, number));

// number add

f2ptr f2__number__plus(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__plus(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__plus(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__plus(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__integer__is_type(cause, number)) {
      return f2__pointer__plus(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__plus(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__plus, this, number, return f2__number__plus(this_cause, this, number));

// number subtract

f2ptr f2__number__minus(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__minus(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__minus(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__minus(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__integer__is_type(cause, number)) {
      return f2__pointer__subtract_integer(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__minus(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__minus, this, number, return f2__number__minus(this_cause, this, number));

// number greater_than

f2ptr f2__number__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__is_greater_than(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__is_greater_than(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__is_greater_than(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__is_greater_than(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__is_greater_than(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__is_greater_than, this, number, return f2__number__is_greater_than(this_cause, this, number));

// number less_than

f2ptr f2__number__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__is_less_than(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__is_less_than(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__is_less_than(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__is_less_than(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__is_less_than(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__is_less_than, this, number, return f2__number__is_less_than(this_cause, this, number));

// number equals

f2ptr f2__number__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  if (raw__integer__is_type(cause, this)) {
    return f2__integer__is_numerically_equal_to(cause, this, number);
  } else if (raw__double__is_type(cause, this)) {
    return f2__double__is_numerically_equal_to(cause, this, number);
  } else if (raw__float__is_type(cause, this)) {
    return f2__float__is_numerically_equal_to(cause, this, number);
  } else if (raw__pointer__is_type(cause, this)) {
    if (raw__pointer__is_type(cause, number)) {
      return f2__pointer__is_numerically_equal_to(cause, this, number);
    }
  } else if (raw__largeinteger__is_type(cause, this)) {
    return f2__largeinteger__is_numerically_equal_to(cause, this, number);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(number__is_numerically_equal_to, this, number, return f2__number__is_numerically_equal_to(this_cause, this, number));

// number square_root

f2ptr f2__number__square_root(f2ptr cause, f2ptr this) {
  if (raw__integer__is_type(cause, this)) {
    return raw__integer__square_root(cause, this);
  } else if (raw__double__is_type(cause, this)) {
    return raw__double__square_root(cause, this);
  } else if (raw__float__is_type(cause, this)) {
    return raw__float__square_root(cause, this);
  } else if (raw__largeinteger__is_type(cause, this)) {
    return raw__largeinteger__square_root(cause, this);
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
  
  f2__primcfunk__init__1(number__is_type,                 exp,          "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__1(number__as__double,              this,         "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__multiplied_by,           this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__divided_by,              this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__plus,                    this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__minus,                   this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__is_greater_than,         this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__is_less_than,            this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__2(number__is_numerically_equal_to, this, number, "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__1(number__square_root,             this,         "(cfunk defined in f2_arithmetic.c)");
  
}
