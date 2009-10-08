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

// object_lattice

def_primobject_1_slot(object_lattice, thing);

f2ptr f2__object_lattice__new(f2ptr cause, f2ptr thing) {
  return f2object_lattice__new(cause, thing);
}
def_pcfunk1(object_lattice__new, thing, return f2__object_lattice__new(this_cause, thing));


// **

void f2__object_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "object_lattice", "", &f2__object_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __object_lattice__symbol = new__symbol(cause, "object_lattice");
}


void f2__object_lattice__initialize() {
  f2__object_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // object_lattice
  initialize_primobject_1_slot(object_lattice, thing);
  
}

