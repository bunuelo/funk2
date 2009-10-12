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
	  raw__float__is_type(  cause, exp));
}

f2ptr f2__number__is_type(f2ptr cause, f2ptr exp) {return f2bool__new(raw__number__is_type(cause, exp));}
def_pcfunk1(number__is_type, exp, return f2__number__is_type(this_cause, exp));

double raw__number__to_double(f2ptr cause, f2ptr this) {
  double d;
  if      (raw__double__is_type( cause, this)) {d = f2double__d( this, cause);}
  else if (raw__float__is_type(  cause, this)) {d = f2float__f(  this, cause);}
  else if (raw__integer__is_type(cause, this)) {d = f2integer__i(this, cause);}
  else                                         {d = 0.0;}
  return d;
}

f2ptr f2__number__to_double(f2ptr cause, f2ptr this) {return f2bool__new(raw__number__to_double(cause, this));}
def_pcfunk1(number__to_double, this, return f2__number__to_double(this_cause, this));





// **

void f2__arithmetic__reinitialize_globalvars() {
}

void f2__arithmetic__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "arithmetic", "", &f2__arithmetic__reinitialize_globalvars);
  
  f2__arithmetic__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  f2__primcfunk__init__1(number__is_type,   exp,  "(cfunk defined in f2_arithmetic.c)");
  f2__primcfunk__init__1(number__to_double, this, "(cfunk defined in f2_arithmetic.c)");
  
}
