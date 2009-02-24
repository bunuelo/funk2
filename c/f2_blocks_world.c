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

// blocks_world_object

defprimobject__static_slot(blocks_world_object__name,      0);
defprimobject__static_slot(blocks_world_object__type,      1);
defprimobject__static_slot(blocks_world_object__rectangle, 2);
defprimobject__static_slot(blocks_world_object__color,     3);

f2ptr __blocks_world_object__symbol = -1;

f2ptr f2blocks_world_object__new(f2ptr cause, f2ptr name, f2ptr type, f2ptr rectangle, f2ptr color) {
  /*pause_gc();*/
  release__assert(__blocks_world_object__symbol != -1, nil, "f2blocks_world_object__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_object__symbol, 4, nil);
  f2blocks_world_object__name__set(     this, cause, name);
  f2blocks_world_object__type__set(     this, cause, type);
  f2blocks_world_object__rectangle__set(this, cause, rectangle);
  f2blocks_world_object__color__set(    this, cause, color);
  /*resume_gc();*/
  return this;
}


// **

void f2__blocks_world__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  __blocks_world_object__symbol = f2symbol__new(cause, strlen("blocks_world_object"), (u8*)"blocks_world_object");
}

void f2__blocks_world__initialize() {
  pause_gc();
  f2__blocks_world__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __blocks_world_object__symbol, nil);
  
  resume_gc();
  try_gc();
}

