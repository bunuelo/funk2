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

// blocks_world_rectangle

defprimobject__static_slot(blocks_world_rectangle__x0, 0);
defprimobject__static_slot(blocks_world_rectangle__y0, 1);
defprimobject__static_slot(blocks_world_rectangle__x1, 2);
defprimobject__static_slot(blocks_world_rectangle__y1, 3);

f2ptr __blocks_world_rectangle__symbol = -1;

f2ptr f2blocks_world_rectangle__new(f2ptr cause, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1) {
  /*pause_gc();*/
  release__assert(__blocks_world_rectangle__symbol != -1, nil, "f2blocks_world_rectangle__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_object__symbol, 4, nil);
  f2blocks_world_rectangle__x0__set(this, cause, x0);
  f2blocks_world_rectangle__y0__set(this, cause, y0);
  f2blocks_world_rectangle__x1__set(this, cause, x1);
  f2blocks_world_rectangle__y1__set(this, cause, y1);
  /*resume_gc();*/
  return this;
}


// blocks_world_color

defprimobject__static_slot(blocks_world_color__name, 0);

f2ptr __blocks_world_color__symbol = -1;

f2ptr f2blocks_world_color__new(f2ptr cause, f2ptr name) {
  /*pause_gc();*/
  release__assert(__blocks_world_color__symbol != -1, nil, "f2blocks_world_color__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_object__symbol, 1, nil);
  f2blocks_world_color__name__set(this, cause, name);
  /*resume_gc();*/
  return this;
}


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


// blocks_world

defprimobject__static_slot(blocks_world__objects, 0);

f2ptr __blocks_world__symbol = -1;

f2ptr f2blocks_world__new(f2ptr cause, f2ptr objects) {
  /*pause_gc();*/
  release__assert(__blocks_world__symbol != -1, nil, "f2blocks_world__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world__symbol, 1, nil);
  f2blocks_world__objects__set(this, cause, objects);
  /*resume_gc();*/
  return this;
}


// **

void f2__blocks_world__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  __blocks_world_rectangle__symbol = f2symbol__new(cause, strlen("blocks_world_rectangle"), (u8*)"blocks_world_rectangle");
  __blocks_world_color__symbol     = f2symbol__new(cause, strlen("blocks_world_color"),     (u8*)"blocks_world_color");
  __blocks_world_object__symbol    = f2symbol__new(cause, strlen("blocks_world_object"),    (u8*)"blocks_world_object");
  __blocks_world__symbol           = f2symbol__new(cause, strlen("blocks_world"),           (u8*)"blocks_world");
}

void f2__blocks_world__initialize() {
  pause_gc();
  f2__blocks_world__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __blocks_world_rectangle__symbol, nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_color__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_object__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __blocks_world__symbol,           nil);
  
  resume_gc();
  try_gc();
}

