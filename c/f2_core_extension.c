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

// core_extension_funk

def_frame_object__global__6_slot(core_extension_funk, filename, name, args, env, is_funktional, documentation);

f2ptr raw__core_extension_funk__new(f2ptr cause, f2ptr filename, f2ptr name, f2ptr args, f2ptr env, f2ptr is_funktional, f2ptr documentation) {
  return f2core_extension_funk__new(cause, filename, name, args, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__new(f2ptr cause, f2ptr filename, f2ptr name, f2ptr args, f2ptr env, f2ptr is_funktional, f2ptr documentation) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__symbol__is_type(cause, name)) ||
      (args && (! raw__cons__is_type(cause, args))) ||
      (env && (! raw__environment__is_type(cause, env))) ||
      (documentation && (! raw__string__is_type(cause, documentation)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__new(cause, filename, name, args, env, is_funktional, documentation);
}
def_pcfunk6(core_extension_funk__new, filename, name, args, env, is_funktional, documentation, return f2__core_extension_funk__new(cause, filename, name, args, env, is_funktional, documentation));


f2ptr f2core_extension_funk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_funk__primobject_type__new(cause);
  return this;
}



// **

void f2__core_extension__reinitialize_globalvars() {
}

void f2__core_extension__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension", "", &f2__core_extension__reinitialize_globalvars);
  
  f2__core_extension__reinitialize_globalvars();
  
  
  // core_extension_funk
  
  init_frame_object__6_slot(core_extension_funk, name, args, core_extension, env, is_funktional, documentation);
  
  f2__primcfunk__init__6(core_extension_funk__new, filename, name, args, env, is_funktional, documentation, "");
  
}

