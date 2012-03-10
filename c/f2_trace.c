// 
// Copyright (c) 2007-2012 Bo Morgan.
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

void raw__array__tracing_on__set(f2ptr cause, f2ptr this, boolean_t tracing_on) {
  int this__length = raw__array__length(cause, this);
  int i;
  for (i = this__length - 1; i != 0; i --) {
    raw__array__elt__tracing_on__set(cause, this, i, f2bool__new(tracing_on));
    raw__array__elt__set(cause, this, i, raw__array__elt(cause, this, i));
  }
}


// **

void f2__trace__reinitialize_globalvars() {
  {char *str = "do_not_remember"; __funk2.trace.do_not_remember__symbol = new__symbol(initial_cause(), str);}
}

void f2__trace__defragment__fix_pointers() {
  // -- reintialize --
  
  defragment__fix_pointer(__funk2.trace.do_not_remember__symbol);
  
  
  // -- initialize --
}

void f2__trace__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "trace", "", &f2__trace__reinitialize_globalvars, &f2__trace__defragment__fix_pointers);
  
  f2__trace__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __funk2.trace.do_not_remember__symbol, nil);
  
  
}

