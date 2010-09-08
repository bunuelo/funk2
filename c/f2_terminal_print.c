

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


// terminal_print_frame

def_frame_object__global__3_slot(terminal_print_frame, max_size, size, already_printed_hash);


f2ptr raw__exp__terminal_print(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  return nil;
}

f2ptr f2__exp__terminal_print(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__terminal_print_frame__is_type(cause, terminal_print_frame)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__exp__terminal_print(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_print, this, terminal_print_frame, return f2__exp__terminal_print(this_cause, this, terminal_print_frame));




// **

void f2__terminal_print__reinitialize_globalvars() {
}

void f2__terminal_print__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "terminal_print", "", &f2__terminal_print__reinitialize_globalvars);
  
  f2__terminal_print__reinitialize_globalvars();
  
  
  // terminal_print_frame
  
  init_frame_object__3_slot(terminal_print_frame, max_size, size, already_printed_hash);
  
  
  f2__primcfunk__init__2(exp__terminal_print, this, terminal_print_frame, "Prints a value given a terminal_print_frame.");
  
}

