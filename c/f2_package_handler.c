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


// package_handler

def_primobject_2_slot(package_handler,
		      package_frame,
		      package_search_paths);

f2ptr f2__package_handler__new(f2ptr cause) {
  f2ptr package_frame        = f2__frame__new(cause, nil);
  f2ptr package_search_paths = nil;
  return f2package__new(cause, package_frame, package_search_paths);
}
def_pcfunk0(package_handler__new,
	    "",
	    return f2__package_handler__new(this_cause));


f2ptr f2package_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package_handler__primobject_type__new(cause);
  return this;
}



// **

void f2__package_handler__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __package_handler__symbol = new__symbol(cause, "package_handler");
}

void f2__package_handler__initialize() {
  f2__package_handler__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "package_handler", "", &f2__cause__reinitialize_globalvars);
  //f2ptr cause = initial_cause();
  
  // package_handler
  
  initialize_primobject_2_slot(package,
			       package_frame,
			       package_search_paths);
  
}  
