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

f2ptr f2__number__as__double(f2ptr this) {
  return f2__object__get_0(cause, this, __funk2.number_globalvars.as__double__symbol);
}

double raw__number__as__raw_double(f2ptr this) {
  f2ptr value = f2__number__as__double(this);
  if (! raw__double__is_type(cause, value)) {
    return 0.0;
  }
  return f2double__d(value, cause);
}

f2ptr f2__number__multiplied_by(f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.multiplied_by__symbol, that);
}

f2ptr f2__number__divided_by(f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.divided_by__symbol, that);
}

f2ptr f2__number__plus(f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.plus__symbol, that);
}

f2ptr f2__number__minus(f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.minus__symbol, that);
}

f2ptr f2__number__is_greater_than(f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_greater_than__symbol, that);
}

f2ptr f2__number__is_less_than(f2ptr this, f2ptr number) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_less_than__symbol, that);
}

f2ptr f2__number__is_numerically_equal_to( f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_numerically_equal_to__symbol, that);
}

f2ptr f2__number__square_root(f2ptr this) {
  return f2__object__get_0(cause, this, __funk2.number_globalvars.square_root__symbol);
}

void funk2_number_globalvars__init(funk2_number_globalvars_t* this) {
  f2ptr cause = initial_cause();
  this->as__double__symbol              = new__symbol(cause, "as-double");
  this->multiplied_by__symbol           = new__symbol(cause, "multiplied_by");
  this->divided_by__symbol              = new__symbol(cause, "divided_by");
  this->plus__symbol                    = new__symbol(cause, "plus");
  this->minus__symbol                   = new__symbol(cause, "minus");
  this->is_greater_than__symbol         = new__symbol(cause, "is_greater_than");
  this->is_less_than__symbol            = new__symbol(cause, "is_less_than");
  this->is_numerically_equal_to__symbol = new__symbol(cause, "is_numerically_equal_to");
  this->square_root__symbol             = new__symbol(cause, "square_root");
}

// **

void f2__number__reinitialize_globalvars() {
  funk2_number_globalvars__init(&(__funk2.number_globalvars));
}

void f2__number__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "number", "", &f2__number__reinitialize_globalvars);
  
  f2__number__reinitialize_globalvars();
  
}

