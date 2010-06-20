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

// package

def_primobject_1_slot(package,
		      dependencies);

f2ptr f2__package__new(f2ptr cause, f2ptr dependencies) {return f2package__new(cause, dependencies);}
def_pcfunk1(package__new, dependencies, return f2__package__new(this_cause, dependencies));

f2ptr f2package__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package__primobject_type__new(cause);
  return this;
}

// **

void f2__package__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __package__symbol = new__symbol(cause, "package");
}

void f2__package__initialize() {
  f2__package__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "package", "", &f2__cause__reinitialize_globalvars);
  f2ptr cause = initial_cause();
  
  //--
  
  // package
  
  initialize_primobject_1_slot(package,
			       dependencies);
  
}

