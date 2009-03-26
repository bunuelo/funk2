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

// action primobject definition

defprimobject__static_slot(action__funk,          0);
defprimobject__static_slot(action__success_pairs, 1);
defprimobject__static_slot(action__failure_pairs, 2);

f2ptr __action__symbol = -1;

f2ptr f2action__new(f2ptr cause, f2ptr funk, f2ptr success_pairs, f2ptr failure_pairs) {
  if (__action__symbol == -1) {__action__symbol = f2symbol__new(cause, strlen("action"), (u8*)"action");}
  f2ptr this = f2__primobject__new(cause, __action__symbol, 3, nil);
  f2action__funk__set(         this, cause, funk);
  f2action__success_pairs__set(this, cause, success_pairs);
  f2action__failure_pairs__set(this, cause, failure_pairs);
  return this;
}

boolean_t raw__actionp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__action(this, cause));}
f2ptr f2__actionp(f2ptr this, f2ptr cause) {return f2bool__new(raw__actionp(this, cause));}


f2ptr f2__action__new(f2ptr cause, f2ptr funk) {
  return f2action__new(cause, funk, nil, nil);
}
def_pcfunk1(action__new, funk, return f2__action__new(this_cause, funk));

// **

void f2__primobject__action__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __action__symbol = f2symbol__new(cause, strlen("action"), (u8*)"action");
}

void f2__primobject__action__initialize() {
  pause_gc();
  f2__primobject__action__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __action__symbol, nil);
  
  f2__primcfunk__init__1(action__new, funk);
  
  resume_gc();
  try_gc();
}

