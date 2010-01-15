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

// largeinteger

def_primobject_3_slot(largeinteger, access_mutex, negative, integer_array);

// **

void f2__primobject_largeinteger__reinitialize_globalvars() {
  __largeinteger__symbol = f2symbol__new(initial_cause(), strlen("largeinteger"), (u8*)"largeinteger");
}

void f2__primobject_largeinteger__initialize() {
  f2__primobject_largeinteger__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __largeinteger__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // largeinteger
  
  initialize_primobject_3_slot(largeinteger, access_mutex, negative, integer_array);
  
}

