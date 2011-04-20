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
  return f2package_handler__new(cause, package_frame, package_search_paths);
}
def_pcfunk0(package_handler__new,
	    "",
	    return f2__package_handler__new(this_cause));


f2ptr raw__package_handler__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "package_handler"),
					       new__symbol(cause, "package_frame"),        f2__package_handler__package_frame(       cause, this),
					       new__symbol(cause, "package_search_paths"), f2__package_handler__package_search_paths(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__package_handler__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(package_handler,      this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__package_handler__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(package_handler__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints a package_handler object using a terminal_print_frame.",
	    return f2__package_handler__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2package_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package_handler__primobject_type__new(cause);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), __funk2.globalenv.object_type.primobject.primobject_type_package_handler.terminal_print_with_frame__funk);
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
  f2ptr cause = initial_cause();
  
  // package_handler
  
  initialize_primobject_2_slot(package_handler,
			       package_frame,
			       package_search_paths);
  
  __funk2.globalenv.object_type.primobject.primobject_type_package_handler.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(package_handler__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_package_handler.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}  
