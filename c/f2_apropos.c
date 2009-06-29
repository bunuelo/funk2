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

f2ptr f2__apropos(f2ptr cause, f2ptr this) {
  return nil;
}
def_pcfunk1(apropos, this, return f2__apropos(this_cause, this));


void f2__apropos__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_apropos_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__apropos__initialize() {
  //f2ptr cause = initial_cause(); //f2_apropos_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__apropos__reinitialize_globalvars();
  
  f2__primcfunk__init(apropos);
  
  resume_gc();
  try_gc();
}

