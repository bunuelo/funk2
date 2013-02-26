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

#include "funk2.h"

f2ptr f2__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_less_than__symbol, that);
}
def_pcfunk2(is_less_than, this, that,
	    "Compares this object to that object using the is_less_than member funktion of this object.",
	    return f2__is_less_than(this_cause, this, that));


f2ptr f2__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_greater_than__symbol, that);
}
def_pcfunk2(is_greater_than, this, that,
	    "Compares this object to that object using the is_greater_than member funktion of this object.",
	    return f2__is_greater_than(this_cause, this, that));


f2ptr raw__number__as__double(f2ptr cause, f2ptr this) {
  return f2__object__get_0(cause, this, __funk2.number_globalvars.as__double__symbol);
}

f2ptr f2__number__as__double(f2ptr cause, f2ptr this) {
  return raw__number__as__double(cause, this);
}

double raw__number__as__raw_double(f2ptr cause, f2ptr this) {
  f2ptr value = f2__number__as__double(cause, this);
  if (! raw__double__is_type(cause, value)) {
    return 0.0;
  }
  return f2double__d(value, cause);
}

f2ptr f2__number__multiplied_by(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.multiplied_by__symbol, that);
}

f2ptr f2__number__divided_by(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.divided_by__symbol, that);
}

f2ptr f2__number__plus(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.plus__symbol, that);
}

f2ptr f2__number__minus(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.minus__symbol, that);
}

f2ptr f2__number__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__is_greater_than(cause, this, that);
}

f2ptr f2__number__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__is_less_than(cause, this, that);
}

f2ptr f2__number__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.is_numerically_equal_to__symbol, that);
}

f2ptr f2__number__square_root(f2ptr cause, f2ptr this) {
  return f2__object__get_0(cause, this, __funk2.number_globalvars.square_root__symbol);
}

f2ptr f2__number__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.number_globalvars.modulo__symbol, that);
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
  this->modulo__symbol                  = new__symbol(cause, "modulo");
}

void funk2_number_globalvars__defragment__fix_pointers(funk2_number_globalvars_t* this) {
  defragment__fix_pointer(this->as__double__symbol);
  defragment__fix_pointer(this->multiplied_by__symbol);
  defragment__fix_pointer(this->divided_by__symbol);
  defragment__fix_pointer(this->plus__symbol);
  defragment__fix_pointer(this->minus__symbol);
  defragment__fix_pointer(this->is_greater_than__symbol);
  defragment__fix_pointer(this->is_less_than__symbol);
  defragment__fix_pointer(this->is_numerically_equal_to__symbol);
  defragment__fix_pointer(this->square_root__symbol);
  defragment__fix_pointer(this->modulo__symbol);
}

// **

void f2__number__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_number_globalvars__defragment__fix_pointers(&(__funk2.number_globalvars));
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(is_greater_than);
  f2__primcfunk__init__defragment__fix_pointers(is_less_than);
  
}

void f2__number__reinitialize_globalvars() {
  funk2_number_globalvars__init(&(__funk2.number_globalvars));
  
  f2__primcfunk__init__2(is_greater_than, this, that);
  f2__primcfunk__init__2(is_less_than,    this, that);
}

void f2__number__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "number", "", &f2__number__reinitialize_globalvars, &f2__number__defragment__fix_pointers);
  
  f2__number__reinitialize_globalvars();
}

