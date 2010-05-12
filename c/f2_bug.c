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



// bug

def_primobject_2_slot(bug, bug_type, frame);

f2ptr f2__bug__new(f2ptr cause, f2ptr type, f2ptr frame) {return f2bug__new(cause, type, frame);}
def_pcfunk2(bug__new, type, frame, return f2__bug__new(this_cause, type, frame));


// **

void f2__bug__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __bug__symbol = new__symbol(cause, "bug");
}


void f2__bug__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bug", "", &f2__bug__reinitialize_globalvars);
  
  f2__bug__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // bug
  
  initialize_primobject_2_slot(bug, bug_type, frame);
  
}

