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


// double

double raw__double__log(f2ptr cause, double this) {
  return log(this);
}

f2ptr f2__double__log(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2double__new(cause, raw__double__log(cause, f2double__d(this, cause)));
}
def_pcfunk1(double__log, exp,
	    "",
	    return f2__double__log(this_cause, exp));


double raw__double__exp(f2ptr cause, double this) {
  return exp(this);
}

f2ptr f2__double__exp(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2double__new(cause, raw__double__exp(cause, f2double__d(this, cause)));
}
def_pcfunk1(double__exp, exp,
	    "",
	    return f2__double__exp(this_cause, exp));


// integer

double raw__integer__log(f2ptr cause, s64 this) {
  double this__d = (double)this;
  return log(this__d);
}

f2ptr f2__integer__log(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2double__new(cause, raw__integer__log(cause, f2integer__i(this, cause)));
}
def_pcfunk1(integer__log, exp,
	    "",
	    return f2__integer__log(this_cause, exp));


double raw__integer__exp(f2ptr cause, s64 this) {
  double this__d = (double)this;
  return exp(this__d);
}

f2ptr f2__integer__exp(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2double__new(cause, raw__integer__exp(cause, f2integer__i(this, cause)));
}
def_pcfunk1(integer__exp, exp,
	    "",
	    return f2__integer__exp(this_cause, exp));


// general

f2ptr f2__log(f2ptr cause, f2ptr exp) {
  f2ptr log_slot_type_funk = f2__object__slot__type_funk(cause, exp, new__symbol(cause, "get"), new__symbol(cause, "log"));
  if (! raw__funkable__is_type(cause, log_slot_type_funk)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "log-no_log_function_defined_for_object"),
				   new__symbol(cause, "exp"),      exp,
				   new__symbol(cause, "exp-type"), f2__object__type(cause, exp)));
  } else {
    return assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), log_slot_type_funk, f2list1__new(cause, exp)));
  }
}
def_pcfunk1(log, exp,
	    "",
	    return f2__log(this_cause, exp));


f2ptr f2__exp(f2ptr cause, f2ptr exp) {
  f2ptr exp_slot_type_funk = f2__object__slot__type_funk(cause, exp, new__symbol(cause, "get"), new__symbol(cause, "exp"));
  if (! raw__funkable__is_type(cause, exp_slot_type_funk)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "exp-no_exp_function_defined_for_object"),
				   new__symbol(cause, "exp"),      exp,
				   new__symbol(cause, "exp-type"), f2__object__type(cause, exp)));
  } else {
    return assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), exp_slot_type_funk, f2list1__new(cause, exp)));
  }
}
def_pcfunk1(exp, exp,
	    "",
	    return f2__exp(this_cause, exp));


// **

void f2__math__defragment__fix_pointers() {
  // double
  
  f2__primcfunk__init__defragment__fix_pointers(double__log);
  f2__primcfunk__init__defragment__fix_pointers(double__exp);
  
  // integer
  
  f2__primcfunk__init__defragment__fix_pointers(integer__log);
  f2__primcfunk__init__defragment__fix_pointers(integer__exp);
  
  // general
  
  f2__primcfunk__init__defragment__fix_pointers(log);
  f2__primcfunk__init__defragment__fix_pointers(exp);
}

void f2__math__reinitialize_globalvars() {
  // double
  
  f2__primcfunk__init(double__log);
  f2__primcfunk__init(double__exp);
  
  // integer
  
  f2__primcfunk__init(integer__log);
  f2__primcfunk__init(integer__exp);
  
  // general
  
  f2__primcfunk__init(log);
  f2__primcfunk__init(exp);
}

void f2__math__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "math", "", &f2__math__reinitialize_globalvars, &f2__math__defragment__fix_pointers);
  
  f2__math__reinitialize_globalvars();
}


