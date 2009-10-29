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



// bug

def_primobject_1_slot(bug, bug_type);

f2ptr f2__bug__new(f2ptr cause, f2ptr type) {return f2bug__new(cause, type);}
def_pcfunk1(bug__new, type, return f2__bug__new(this_cause, type));

f2ptr f2__bug__new_from_larva(f2ptr cause, f2ptr larva) {
  if (! raw__larva__is_type(cause, larva)) {
    return f2larva__new(cause, 1);
  }
  u64 larva_type = f2larva__larva_type(cause, larva);
  return f2__bug__new(cause, f2integer__new(cause, larva_type));
}


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
  
  initialize_primobject_1_slot(bug, bug_type);
  
}

