// 
// Copyright (c) 2007-2011 Bo Morgan.
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

f2ptr f2__funk__optimize(f2ptr cause, f2ptr this) {
  f2ptr args           = f2__funk__args(          cause, this);
  f2ptr body_bytecodes = f2__funk__body_bytecodes(cause, this);
  {
    f2ptr iter = body_bytecodes;
    while (iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, iter);
      {
	
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return body_bytecodes;
}


// **

void f2__optimize__reinitialize_globalvars() {
}

void f2__optimize__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars);
  
  f2__optimize__reinitialize_globalvars();
  
  f2__primcfunk__init__1(funk__optimize, this, "Optimizes this funk for faster execution.");
}

