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

u64 raw__blocks_world__lower_left__x(f2ptr cause) {
  return 20;
}

f2ptr f2__blocks_world__lower_left__x(f2ptr cause) {
  return f2integer__new(cause, raw__blocks_world__lower_left__x(cause));
}
def_pcfunk0(blocks_world__lower_left__x, return f2__blocks_world__lower_left__x(this_cause));


u64 raw__blocks_world__lower_left__y(f2ptr cause) {
  return raw__termios__height() - 10;
}

f2ptr f2__blocks_world__lower_left__y(f2ptr cause) {
  return f2integer__new(cause, raw__blocks_world__lower_left__y(cause));
}
def_pcfunk0(blocks_world__lower_left__y, return f2__blocks_world__lower_left__y(this_cause));


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

bool raw__blocks_world_rectanglep(f2ptr this, f2ptr cause) {
  return (raw__primobjectp(this, cause) && f2primobject__is__blocks_world_rectangle(this, cause));
}


f2ptr f2__blocks_world_rectangle__new_copy(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectanglep(this, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr x0 = f2blocks_world_rectangle__x0(this, cause);
  f2ptr y0 = f2blocks_world_rectangle__y0(this, cause);
  f2ptr x1 = f2blocks_world_rectangle__x1(this, cause);
  f2ptr y1 = f2blocks_world_rectangle__y1(this, cause);
  return f2blocks_world_rectangle__new(cause, x0, y0, x1, y1);
}

f2ptr raw__blocks_world_rectangle__create(f2ptr cause, u64 x0, u64 y0, u64 x1, u64 y1) {
  u64 min_x; u64 max_x; if (x0 < x1) {min_x = x0; max_x = x1;} else {min_x = x1; max_x = x0;}
  u64 min_y; u64 max_y; if (y0 < y1) {min_y = y0; max_y = y1;} else {min_y = y1; max_y = y0;}
  return f2blocks_world_rectangle__new(cause, f2integer__new(cause, min_x), f2integer__new(cause, min_y), f2integer__new(cause, max_x), f2integer__new(cause, max_y));
}

f2ptr f2__blocks_world_rectangle__create(f2ptr cause, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1) {
  if ((! raw__integerp(x0, cause)) ||
      (! raw__integerp(y0, cause)) ||
      (! raw__integerp(x1, cause)) ||
      (! raw__integerp(y1, cause))) {
    return f2larva__new(cause, 1);
  }
  u64 raw_x0 = f2integer__i(x0, cause);
  u64 raw_y0 = f2integer__i(y0, cause);
  u64 raw_x1 = f2integer__i(x1, cause);
  u64 raw_y1 = f2integer__i(y1, cause);
  return raw__blocks_world_rectangle__create(cause, raw_x0, raw_y0, raw_x1, raw_y1);
}
def_pcfunk4(blocks_world_rectangle__create, x0, y0, x1, y1, return f2__blocks_world_rectangle__create(simple_cause, x0, y0, x1, y1));


/*
[defunk blocks_world_rectangle-render [this background_char]
  [let [[screen_height [termios-height]]]
    [ansi-stream-bordered_rectangle stdout
				    [+ 10 [blocks_world_rectangle-x0 this]]
				    [- screen_height [+ 10 [blocks_world_rectangle-y1 this]]]
				    [+ 10 [blocks_world_rectangle-x1 this]]
				    [- screen_height [+ 10 [blocks_world_rectangle-y0 this]]]
				    background_char]]]
*/

f2ptr raw__blocks_world_rectangle__render(f2ptr cause, f2ptr this, char background_char) {
  if ((! raw__blocks_world_rectanglep(this, cause))) {
    return f2larva__new(cause, 1);
  }
  //u64 lower_left__x = raw__blocks_world__lower_left__x(cause);
  u64 lower_left__y = raw__blocks_world__lower_left__y(cause);
  u64 rect__x0 = f2blocks_world_rectangle__x0(this, cause);
  u64 rect__y0 = f2blocks_world_rectangle__y0(this, cause);
  u64 rect__x1 = f2blocks_world_rectangle__x1(this, cause);
  u64 rect__y1 = f2blocks_world_rectangle__y1(this, cause);
  raw__ansi__stream__bordered_rectangle(cause, __funk2.globalenv.stdout_stream,
					(rect__x0 + 10),
					(lower_left__y - rect__y1),
					(rect__x1 + 10),
					(lower_left__y - rect__y0),
					background_char);
  return nil;
}

f2ptr f2__blocks_world_rectangle__render(f2ptr cause, f2ptr this, f2ptr background_char) {
  if (! raw__charp(background_char, cause)) {
    return f2larva__new(cause, 1);
  }
  char raw_background_char = f2char__ch(background_char, cause);
  return raw__blocks_world_rectangle__render(cause, this, raw_background_char);
}
def_pcfunk2(blocks_world_rectangle__render, this, background_char, return f2__blocks_world_rectangle__render(this_cause, this, background_char));

/*
[defunk blocks_world_rectangle-clear_line_above [this]
  [let [[screen_height [termios-height]]]
    [let [[y1 [- [- screen_height [+ 10 [blocks_world_rectangle-y1 this]]] 1]]]
      [ansi-stream-rectangle stdout
			     [+ 10 [blocks_world_rectangle-x0 this]]
			     y1
			     [+ 10 [blocks_world_rectangle-x1 this]]
			     y1
			     [string-elt ' ' 0]]]]]
*/

f2ptr f2__blocks_world_rectangle__clear_line_above(f2ptr cause, f2ptr this) {
  if ((! raw__blocks_world_rectanglep(this, cause))) {
    return f2larva__new(cause, 1);
  }
  //u64 lower_left__x = raw__blocks_world__lower_left__x(cause);
  u64 lower_left__y = raw__blocks_world__lower_left__y(cause);
  u64 rect__x0 = f2blocks_world_rectangle__x0(this, cause);
  //u64 rect__y0 = f2blocks_world_rectangle__y0(this, cause);
  u64 rect__x1 = f2blocks_world_rectangle__x1(this, cause);
  u64 rect__y1 = f2blocks_world_rectangle__y1(this, cause);
  u64 y1 = lower_left__y - rect__y1 - 1;
  raw__ansi__stream__rectangle(cause, __funk2.globalenv.stdout_stream, rect__x0 + 10, y1, rect__x1 + 10, y1, ' ');
  return nil;
}
def_pcfunk1(blocks_world_rectangle__clear_line_above, this, return f2__blocks_world_rectangle__clear_line_above(this_cause, this));

f2ptr raw__blocks_world_rectangle__translate(f2ptr cause, f2ptr this, s64 dx, s64 dy) {
  if ((! raw__blocks_world_rectanglep(this, cause))) {
    return f2larva__new(cause, 1);
  }
  s64 x0 = f2blocks_world_rectangle__x0(this, cause) + dx;
  s64 y0 = f2blocks_world_rectangle__y0(this, cause) + dy;
  s64 x1 = f2blocks_world_rectangle__x1(this, cause) + dx;
  s64 y1 = f2blocks_world_rectangle__y1(this, cause) + dy;
  f2blocks_world_rectangle__x0__set(this, cause, x0);
  f2blocks_world_rectangle__y0__set(this, cause, y0);
  f2blocks_world_rectangle__x1__set(this, cause, x1);
  f2blocks_world_rectangle__y1__set(this, cause, y1);
  return nil;
}

f2ptr f2__blocks_world_rectangle__translate(f2ptr cause, f2ptr this, f2ptr dx, f2ptr dy) {
  if ((! raw__integerp(dx, cause)) ||
      (! raw__integerp(dy, cause))) {
    return f2larva__new(cause, 1);
  }
  s8 raw_dx = f2integer__i(dx, cause);
  s8 raw_dy = f2integer__i(dy, cause);
  return raw__blocks_world_rectangle__translate(cause, this, raw_dx, raw_dy);
}
def_pcfunk3(blocks_world_rectangle__translate, this, dx, dy, return f2__blocks_world_rectangle__translate(this_cause, this, dx, dy));


f2ptr raw__blocks_world_rectangle__new_translate(f2ptr cause, f2ptr this, s64 dx, s64 dy) {
  f2ptr new_rectangle = f2__blocks_world_rectangle__new_copy(cause, this);
  raw__blocks_world_rectangle__translate(cause, new_rectangle, dx, dy);
  return new_rectangle;
}
f2ptr f2__blocks_world_rectangle__new_translate(f2ptr cause, f2ptr this, f2ptr dx, f2ptr dy) {
  if ((! raw__integerp(dx, cause)) ||
      (! raw__integerp(dy, cause))) {
    return f2larva__new(cause, 1);
  }
  s64 raw_dx = f2integer__i(dx, cause);
  s64 raw_dy = f2integer__i(dy, cause);
  return raw__blocks_world_rectangle__new_translate(cause, this, raw_dx, raw_dy);
}
def_pcfunk3(blocks_world_rectangle__new_translate, this, dx, dy, return f2__blocks_world_rectangle__new_translate(this_cause, this, dx, dy));

/*
[defunk blocks_world_rectangle-overlaps [this that]
  [if [not [blocks_world_rectangle? that]]
      [error `run-time `[blocks_world_rectangle-overlaps 'that is not blocks_world_rectangle' ,this ,that]]]
  [let [[a_x0 [blocks_world_rectangle-x0 this]]
	[a_y0 [blocks_world_rectangle-y0 this]]
	[a_x1 [blocks_world_rectangle-x1 this]]
	[a_y1 [blocks_world_rectangle-y1 this]]
	[b_x0 [blocks_world_rectangle-x0 that]]
	[b_y0 [blocks_world_rectangle-y0 that]]
	[b_x1 [blocks_world_rectangle-x1 that]]
	[b_y1 [blocks_world_rectangle-y1 that]]]
    [and [or [and [<= b_x0 a_x0] [>= b_x1 a_x1]]
	     [and [<= a_x0 b_x0] [>= a_x1 b_x1]]
	     [and [<= a_x0 b_x0] [>= a_x1 b_x0]]
	     [and [<= a_x0 b_x1] [>= a_x1 b_x1]]]
	 [or [and [<= b_y0 a_y0] [>= b_y1 a_y1]]
	     [and [<= a_y0 b_y0] [>= a_y1 b_y1]]
	     [and [<= a_y0 b_y0] [>= a_y1 b_y0]]
	     [and [<= a_y0 b_y1] [>= a_y1 b_y1]]]]]]
*/

f2ptr f2__blocks_world_rectangle__overlaps(f2ptr cause, f2ptr this, f2ptr rectangle) {
  if ((! raw__blocks_world_rectanglep(this, cause)) ||
      (! raw__blocks_world_rectanglep(rectangle, cause))) {
    return f2larva__new(cause, 1);
  }
  s64 a_x0 = f2blocks_world_rectangle__x0(this,      cause);
  s64 a_y0 = f2blocks_world_rectangle__y0(this,      cause);
  s64 a_x1 = f2blocks_world_rectangle__x1(this,      cause);
  s64 a_y1 = f2blocks_world_rectangle__y1(this,      cause);
  s64 b_x0 = f2blocks_world_rectangle__x0(rectangle, cause);
  s64 b_y0 = f2blocks_world_rectangle__y0(rectangle, cause);
  s64 b_x1 = f2blocks_world_rectangle__x1(rectangle, cause);
  s64 b_y1 = f2blocks_world_rectangle__y1(rectangle, cause);
  if ((((b_x0 <= a_x0) && (b_x1 >= a_x1)) ||
       ((a_x0 <= b_x0) && (a_x1 >= b_x1)) ||
       ((a_x0 <= b_x0) && (a_x1 >= b_x0)) ||
       ((a_x0 <= b_x1) && (a_x1 >= b_x1))) &&
      (((b_y0 <= a_y0) && (b_y1 >= a_y1)) ||
       ((a_y0 <= b_y0) && (a_y1 >= b_y1)) ||
       ((a_y0 <= b_y0) && (a_y1 >= b_y0)) ||
       ((a_y0 <= b_y1) && (a_y1 >= b_y1)))) {
    return __funk2.globalenv.true__symbol;
  }
  return nil;
}
def_pcfunk2(blocks_world_rectangle__overlaps, this, rectangle, return f2__blocks_world_rectangle__overlaps(this_cause, this, rectangle));


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

bool raw__blocks_world_colorp(f2ptr this, f2ptr cause) {
  return (raw__primobjectp(this, cause) && f2primobject__is__blocks_world_color(this, cause));
}


f2ptr f2__blocks_world_color__render(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_colorp(this, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr name = f2blocks_world_color__name(this, cause);
  if      (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.red__symbol))     {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 12);}
  else if (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.green__symbol))   {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 10);}
  else if (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.blue__symbol))    {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 11);}
  else if (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.white__symbol))   {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 15);}
  else if (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.magenta__symbol)) {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 13);}
  else if (f2__symbol__eq(cause, name, __funk2.globalenv.blocks_world.yellow__symbol))  {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 14);}
  else                                                                                  {raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 7);}
  return nil;
}
def_pcfunk1(blocks_world_color__render, this, return f2__blocks_world_color__render(this_cause, this));


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

bool raw__blocks_world_objectp(f2ptr this, f2ptr cause) {
  return (raw__primobjectp(this, cause) && f2primobject__is__blocks_world_object(this, cause));
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

bool raw__blocks_worldp(f2ptr this, f2ptr cause) {
  return (raw__primobjectp(this, cause) && f2primobject__is__blocks_world(this, cause));
}


// **

void f2__blocks_world__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  __blocks_world_rectangle__symbol = f2symbol__new(cause, strlen("blocks_world_rectangle"), (u8*)"blocks_world_rectangle");
  __blocks_world_color__symbol     = f2symbol__new(cause, strlen("blocks_world_color"),     (u8*)"blocks_world_color");
  __blocks_world_object__symbol    = f2symbol__new(cause, strlen("blocks_world_object"),    (u8*)"blocks_world_object");
  __blocks_world__symbol           = f2symbol__new(cause, strlen("blocks_world"),           (u8*)"blocks_world");
  
  __funk2.globalenv.blocks_world.red__symbol     = f2symbol__new(cause, strlen("red"),     (u8*)"red");
  __funk2.globalenv.blocks_world.green__symbol   = f2symbol__new(cause, strlen("green"),   (u8*)"green");
  __funk2.globalenv.blocks_world.blue__symbol    = f2symbol__new(cause, strlen("blue"),    (u8*)"blue");
  __funk2.globalenv.blocks_world.white__symbol   = f2symbol__new(cause, strlen("white"),   (u8*)"white");
  __funk2.globalenv.blocks_world.magenta__symbol = f2symbol__new(cause, strlen("magenta"), (u8*)"magenta");
  __funk2.globalenv.blocks_world.yellow__symbol  = f2symbol__new(cause, strlen("yellow"),  (u8*)"yellow");
}

void f2__blocks_world__initialize() {
  pause_gc();
  f2__blocks_world__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __blocks_world_rectangle__symbol, nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_color__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_object__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __blocks_world__symbol,           nil);
  
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.red__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.green__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.blue__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.white__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.magenta__symbol, nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.yellow__symbol,  nil);
  
  resume_gc();
  try_gc();
}

