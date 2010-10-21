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


// core_extension

def_frame_object__global__1_slot(core_extension, filename);

f2ptr raw__core_extension__new(f2ptr cause, f2ptr filename) {
  return f2core_extension__new(cause, filename);
}

f2ptr f2__core_extension__new(f2ptr cause, f2ptr filename) {
  if (! raw__string__is_type(cause, filename)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension__new(cause, filename);
}
def_pcfunk1(core_extension__new, filename, return f2__core_extension__new(this_cause, filename));


f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension__primobject_type__new(cause);
  return this;
}


// core_extension_handler

def_frame_object__global__1_slot(core_extension_handler, core_extension_filename_hash);

f2ptr raw__core_extension_handler__new(f2ptr cause) {
  f2ptr core_extension_filename_hash = f2__ptypehash__new(cause);
  return f2core_extension_handler__new(cause, core_extension_filename_hash);
}

f2ptr f2__core_extension_handler__new(f2ptr cause) {
  return raw__core_extension_handler__new(cause);
}
def_pcfunk0(core_extension_handler__new, return f2__core_extension_handler__new(this_cause));


f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_handler__primobject_type__new(cause);
  return this;
}





// **

void f2__core_extension__reinitialize_globalvars() {
}

void f2__core_extension__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension", "", &f2__core_extension__reinitialize_globalvars);
  
  f2__core_extension__reinitialize_globalvars();
  
  
  // core_extension
  
  init_frame_object__1_slot(core_extension, filename);
  
  f2__primcfunk__init__1(core_extension__new, filename, "");
  
  
  // core_extension_handler
  
  init_frame_object__1_slot(core_extension_handler, core_extension_filename_hash);
  
  f2__primcfunk__init__0(core_extension_handler__new, "");
  
  
}




