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

// agent

def_primobject_1_slot(agent, fiber);

f2ptr f2__agent__new(f2ptr cause, f2ptr fiber) {return f2agent__new(cause, fiber);}
def_pcfunk1(agent__new, fiber,
	    "",
	    return f2__agent__new(this_cause, fiber));



// **

void f2__agent__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __agent__symbol = new__symbol(cause, "agent");
}

void f2__agent__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "agent", "", &f2__agent__reinitialize_globalvars);
  
  f2__agent__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // agent
  initialize_primobject_1_slot(agent, fiber);
}


