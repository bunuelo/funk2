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

// time primobject definition

defprimobject__static_slot(time__microseconds_since_1970, 0);

f2ptr __time__symbol = -1;

f2ptr f2time__new(f2ptr cause, f2ptr microseconds_since_1970) {
  if (__time__symbol == -1) {__time__symbol = f2symbol__new(cause, strlen("time"), (u8*)"time");}
  f2ptr this = f2__primobject__new(cause, __time__symbol, 1, nil);
  f2time__microseconds_since_1970__set(this, cause, microseconds_since_1970);
  return this;
}

boolean_t raw__time__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__time(this, cause));}
f2ptr f2__time__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__time__is_type(cause, this));}

// returns a new time object that represents the time of the call.
f2ptr f2__time(f2ptr cause) {
  return f2time__new(cause, f2__system_microseconds_since_1970(cause));
}
def_pcfunk0(time, return f2__time(this_cause));

// **

void f2__primobject__time__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __time__symbol = f2symbol__new(cause, strlen("time"), (u8*)"time");
}

void f2__primobject__time__initialize() {
  pause_gc();
  f2__primobject__time__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __time__symbol, nil);
  
  f2__primcfunk__init__0(time, "");
  
  resume_gc();
  try_gc();
}

