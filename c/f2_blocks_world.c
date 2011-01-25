// 
// Copyright (c) 2007-2011 Bo Morgan.
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

s64 raw__blocks_world__lower_left__x(f2ptr cause) {
  return 20;
}

f2ptr f2__blocks_world__lower_left__x(f2ptr cause) {
  return f2integer__new(cause, raw__blocks_world__lower_left__x(cause));
}
def_pcfunk0(blocks_world__lower_left__x, return f2__blocks_world__lower_left__x(this_cause));


s64 raw__blocks_world__lower_left__y(f2ptr cause) {
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
  release__assert(__blocks_world_rectangle__symbol != -1, nil, "f2blocks_world_rectangle__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_rectangle__symbol, 4, nil);
  f2blocks_world_rectangle__x0__set(this, cause, x0);
  f2blocks_world_rectangle__y0__set(this, cause, y0);
  f2blocks_world_rectangle__x1__set(this, cause, x1);
  f2blocks_world_rectangle__y1__set(this, cause, y1);
  return this;
}
def_pcfunk4(blocks_world_rectangle__new, x0, y0, x1, y1, return f2blocks_world_rectangle__new(this_cause, x0, y0, x1, y1));

f2ptr f2__blocks_world_rectangle__x0(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectangle__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_rectangle__x0(this, cause);
}
def_pcfunk1(blocks_world_rectangle__x0, this, return f2__blocks_world_rectangle__x0(this_cause, this));

f2ptr f2__blocks_world_rectangle__y0(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectangle__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_rectangle__y0(this, cause);
}
def_pcfunk1(blocks_world_rectangle__y0, this, return f2__blocks_world_rectangle__y0(this_cause, this));

f2ptr f2__blocks_world_rectangle__x1(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectangle__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_rectangle__x1(this, cause);
}
def_pcfunk1(blocks_world_rectangle__x1, this, return f2__blocks_world_rectangle__x1(this_cause, this));

f2ptr f2__blocks_world_rectangle__y1(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectangle__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_rectangle__y1(this, cause);
}
def_pcfunk1(blocks_world_rectangle__y1, this, return f2__blocks_world_rectangle__y1(this_cause, this));


boolean_t raw__blocks_world_rectangle__is_type(f2ptr cause, f2ptr this) {
  return (raw__primobject__is_type(cause, this) && f2primobject__is__blocks_world_rectangle(this, cause));
}

f2ptr f2__blocks_world_rectangle__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__blocks_world_rectangle__is_type(cause, this));
}
def_pcfunk1(blocks_world_rectangle__is_type, this, return f2__blocks_world_rectangle__is_type(this_cause, this));


f2ptr f2__blocks_world_rectangle__new_copy(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_rectangle__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr x0 = f2blocks_world_rectangle__x0(this, cause);
  f2ptr y0 = f2blocks_world_rectangle__y0(this, cause);
  f2ptr x1 = f2blocks_world_rectangle__x1(this, cause);
  f2ptr y1 = f2blocks_world_rectangle__y1(this, cause);
  return f2blocks_world_rectangle__new(cause, x0, y0, x1, y1);
}
def_pcfunk1(blocks_world_rectangle__new_copy, this, return f2__blocks_world_rectangle__new_copy(this_cause, this));


f2ptr raw__blocks_world_rectangle__create(f2ptr cause, s64 x0, s64 y0, s64 x1, s64 y1) {
  s64 min_x; s64 max_x; if (x0 < x1) {min_x = x0; max_x = x1;} else {min_x = x1; max_x = x0;}
  s64 min_y; s64 max_y; if (y0 < y1) {min_y = y0; max_y = y1;} else {min_y = y1; max_y = y0;}
  return f2blocks_world_rectangle__new(cause, f2integer__new(cause, min_x), f2integer__new(cause, min_y), f2integer__new(cause, max_x), f2integer__new(cause, max_y));
}

f2ptr f2__blocks_world_rectangle__create(f2ptr cause, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1) {
  if ((! raw__integer__is_type(cause, x0)) ||
      (! raw__integer__is_type(cause, y0)) ||
      (! raw__integer__is_type(cause, x1)) ||
      (! raw__integer__is_type(cause, y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_x0 = f2integer__i(x0, cause);
  s64 raw_y0 = f2integer__i(y0, cause);
  s64 raw_x1 = f2integer__i(x1, cause);
  s64 raw_y1 = f2integer__i(y1, cause);
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
  if ((! raw__blocks_world_rectangle__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  //s64 lower_left__x = raw__blocks_world__lower_left__x(cause);
  s64 lower_left__y = raw__blocks_world__lower_left__y(cause);
  f2ptr rect__x0 = f2blocks_world_rectangle__x0(this, cause);
  f2ptr rect__y0 = f2blocks_world_rectangle__y0(this, cause);
  f2ptr rect__x1 = f2blocks_world_rectangle__x1(this, cause);
  f2ptr rect__y1 = f2blocks_world_rectangle__y1(this, cause);
  if ((! raw__integer__is_type(cause, rect__x0)) ||
      (! raw__integer__is_type(cause, rect__y0)) ||
      (! raw__integer__is_type(cause, rect__x1)) ||
      (! raw__integer__is_type(cause, rect__y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw__rect__x0 = f2integer__i(rect__x0, cause);
  s64 raw__rect__y0 = f2integer__i(rect__y0, cause);
  s64 raw__rect__x1 = f2integer__i(rect__x1, cause);
  s64 raw__rect__y1 = f2integer__i(rect__y1, cause);
  raw__ansi__stream__bordered_rectangle(cause, __funk2.globalenv.stdout_stream,
					(raw__rect__x0 + 10),
					(lower_left__y - raw__rect__y1),
					(raw__rect__x1 + 10),
					(lower_left__y - raw__rect__y0),
					background_char);
  return nil;
}

f2ptr f2__blocks_world_rectangle__render(f2ptr cause, f2ptr this, f2ptr background_char) {
  if (! raw__char__is_type(cause, background_char)) {
    return f2larva__new(cause, 1, nil);
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
  if ((! raw__blocks_world_rectangle__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  //s64 lower_left__x = raw__blocks_world__lower_left__x(cause);
  s64 lower_left__y = raw__blocks_world__lower_left__y(cause);

  f2ptr rect__x0 = f2blocks_world_rectangle__x0(this, cause);
  //f2ptr rect__y0 = f2blocks_world_rectangle__y0(this, cause);
  f2ptr rect__x1 = f2blocks_world_rectangle__x1(this, cause);
  f2ptr rect__y1 = f2blocks_world_rectangle__y1(this, cause);
  if ((! raw__integer__is_type(cause, rect__x0)) ||
      //(! raw__integer__is_type(cause, rect__y0)) ||
      (! raw__integer__is_type(cause, rect__x1)) ||
      (! raw__integer__is_type(cause, rect__y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw__rect__x0 = f2integer__i(rect__x0, cause);
  //s64 raw__rect__y0 = f2integer__i(rect__y0, cause);
  s64 raw__rect__x1 = f2integer__i(rect__x1, cause);
  s64 raw__rect__y1 = f2integer__i(rect__y1, cause);

  s64 y1 = lower_left__y - raw__rect__y1 - 1;
  raw__ansi__stream__rectangle(cause, __funk2.globalenv.stdout_stream, raw__rect__x0 + 10, y1, raw__rect__x1 + 10, y1, ' ');
  return nil;
}
def_pcfunk1(blocks_world_rectangle__clear_line_above, this, return f2__blocks_world_rectangle__clear_line_above(this_cause, this));

f2ptr raw__blocks_world_rectangle__translate(f2ptr cause, f2ptr this, s64 dx, s64 dy) {
  if ((! raw__blocks_world_rectangle__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr x0 = f2blocks_world_rectangle__x0(this, cause);
  f2ptr y0 = f2blocks_world_rectangle__y0(this, cause);
  f2ptr x1 = f2blocks_world_rectangle__x1(this, cause);
  f2ptr y1 = f2blocks_world_rectangle__y1(this, cause);
  if ((! raw__integer__is_type(cause, x0)) ||
      (! raw__integer__is_type(cause, y0)) ||
      (! raw__integer__is_type(cause, x1)) ||
      (! raw__integer__is_type(cause, y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_new_x0 = f2integer__i(x0, cause) + dx;
  s64 raw_new_y0 = f2integer__i(y0, cause) + dy;
  s64 raw_new_x1 = f2integer__i(x1, cause) + dx;
  s64 raw_new_y1 = f2integer__i(y1, cause) + dy;
  f2blocks_world_rectangle__x0__set(this, cause, f2integer__new(cause, raw_new_x0));
  f2blocks_world_rectangle__y0__set(this, cause, f2integer__new(cause, raw_new_y0));
  f2blocks_world_rectangle__x1__set(this, cause, f2integer__new(cause, raw_new_x1));
  f2blocks_world_rectangle__y1__set(this, cause, f2integer__new(cause, raw_new_y1));
  return nil;
}

f2ptr f2__blocks_world_rectangle__translate(f2ptr cause, f2ptr this, f2ptr dx, f2ptr dy) {
  if ((! raw__integer__is_type(cause, dx)) ||
      (! raw__integer__is_type(cause, dy))) {
    return f2larva__new(cause, 1, nil);
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
  if ((! raw__integer__is_type(cause, dx)) ||
      (! raw__integer__is_type(cause, dy))) {
    return f2larva__new(cause, 1, nil);
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
  if ((! raw__blocks_world_rectangle__is_type(cause, this)) ||
      (! raw__blocks_world_rectangle__is_type(cause, rectangle))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr a_x0 = f2blocks_world_rectangle__x0(this,      cause);
  f2ptr a_y0 = f2blocks_world_rectangle__y0(this,      cause);
  f2ptr a_x1 = f2blocks_world_rectangle__x1(this,      cause);
  f2ptr a_y1 = f2blocks_world_rectangle__y1(this,      cause);
  f2ptr b_x0 = f2blocks_world_rectangle__x0(rectangle, cause);
  f2ptr b_y0 = f2blocks_world_rectangle__y0(rectangle, cause);
  f2ptr b_x1 = f2blocks_world_rectangle__x1(rectangle, cause);
  f2ptr b_y1 = f2blocks_world_rectangle__y1(rectangle, cause);
  if ((! raw__integer__is_type(cause, a_x0)) ||
      (! raw__integer__is_type(cause, a_y0)) ||
      (! raw__integer__is_type(cause, a_x1)) ||
      (! raw__integer__is_type(cause, a_y1)) ||
      (! raw__integer__is_type(cause, b_x0)) ||
      (! raw__integer__is_type(cause, b_y0)) ||
      (! raw__integer__is_type(cause, b_x1)) ||
      (! raw__integer__is_type(cause, b_y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_a_x0 = f2integer__i(a_x0, cause);
  s64 raw_a_y0 = f2integer__i(a_y0, cause);
  s64 raw_a_x1 = f2integer__i(a_x1, cause);
  s64 raw_a_y1 = f2integer__i(a_y1, cause);
  s64 raw_b_x0 = f2integer__i(b_x0, cause);
  s64 raw_b_y0 = f2integer__i(b_y0, cause);
  s64 raw_b_x1 = f2integer__i(b_x1, cause);
  s64 raw_b_y1 = f2integer__i(b_y1, cause);
  if ((((raw_b_x0 <= raw_a_x0) && (raw_b_x1 >= raw_a_x1)) ||
       ((raw_a_x0 <= raw_b_x0) && (raw_a_x1 >= raw_b_x1)) ||
       ((raw_a_x0 <= raw_b_x0) && (raw_a_x1 >= raw_b_x0)) ||
       ((raw_a_x0 <= raw_b_x1) && (raw_a_x1 >= raw_b_x1))) &&
      (((raw_b_y0 <= raw_a_y0) && (raw_b_y1 >= raw_a_y1)) ||
       ((raw_a_y0 <= raw_b_y0) && (raw_a_y1 >= raw_b_y1)) ||
       ((raw_a_y0 <= raw_b_y0) && (raw_a_y1 >= raw_b_y0)) ||
       ((raw_a_y0 <= raw_b_y1) && (raw_a_y1 >= raw_b_y1)))) {
    return __funk2.globalenv.true__symbol;
  }
  return nil;
}
def_pcfunk2(blocks_world_rectangle__overlaps, this, rectangle, return f2__blocks_world_rectangle__overlaps(this_cause, this, rectangle));


// blocks_world_color

defprimobject__static_slot(blocks_world_color__name, 0);

f2ptr __blocks_world_color__symbol = -1;

f2ptr f2blocks_world_color__new(f2ptr cause, f2ptr name) {
  release__assert(__blocks_world_color__symbol != -1, nil, "f2blocks_world_color__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_color__symbol, 1, nil);
  f2blocks_world_color__name__set(this, cause, name);
  return this;
}
def_pcfunk1(blocks_world_color__new, name, return f2blocks_world_color__new(this_cause, name));

boolean_t raw__blocks_world_color__is_type(f2ptr cause, f2ptr this) {
  return (raw__primobject__is_type(cause, this) && f2primobject__is__blocks_world_color(this, cause));
}

f2ptr f2__blocks_world_color__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__blocks_world_color__is_type(cause, this));
}
def_pcfunk1(blocks_world_color__is_type, this, return f2__blocks_world_color__is_type(this_cause, this));

f2ptr f2__blocks_world_color__name(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_color__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_color__name(this, cause);
}
def_pcfunk1(blocks_world_color__name, this, return f2__blocks_world_color__name(this_cause, this));


f2ptr f2__blocks_world_color__render(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_color__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
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

defprimobject__static_slot(blocks_world_object__name,           0);
defprimobject__static_slot(blocks_world_object__type,           1);
defprimobject__static_slot(blocks_world_object__rectangle,      2);
defprimobject__static_slot(blocks_world_object__color,          3);
defprimobject__static_slot(blocks_world_object__ignore_gravity, 4);
defprimobject__static_slot(blocks_world_object__holding_object, 5);

f2ptr __blocks_world_object__symbol = -1;

f2ptr f2blocks_world_object__new(f2ptr cause, f2ptr name, f2ptr type, f2ptr rectangle, f2ptr color, f2ptr ignore_gravity, f2ptr holding_object) {
  release__assert(__blocks_world_object__symbol != -1, nil, "f2blocks_world_object__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_object__symbol, 6, nil);
  f2blocks_world_object__name__set(          this, cause, name);
  f2blocks_world_object__type__set(          this, cause, type);
  f2blocks_world_object__rectangle__set(     this, cause, rectangle);
  f2blocks_world_object__color__set(         this, cause, color);
  f2blocks_world_object__ignore_gravity__set(this, cause, ignore_gravity);
  f2blocks_world_object__holding_object__set(this, cause, holding_object);
  return this;
}
def_pcfunk6(blocks_world_object__new, name, type, rectangle, color, ignore_gravity, holding_object, return f2blocks_world_object__new(this_cause, name, type, rectangle, color, ignore_gravity, holding_object));

boolean_t raw__blocks_world_object__is_type(f2ptr cause, f2ptr this) {
  return (raw__primobject__is_type(cause, this) && f2primobject__is__blocks_world_object(this, cause));
}

f2ptr f2__blocks_world_object__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__blocks_world_object__is_type(cause, this));
}
def_pcfunk1(blocks_world_object__is_type, this, return f2__blocks_world_object__is_type(this_cause, this));

f2ptr f2__blocks_world_object__name(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__name(this, cause);
}
def_pcfunk1(blocks_world_object__name, this, return f2__blocks_world_object__name(this_cause, this));

f2ptr f2__blocks_world_object__type(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__type(this, cause);
}
def_pcfunk1(blocks_world_object__type, this, return f2__blocks_world_object__type(this_cause, this));

f2ptr f2__blocks_world_object__rectangle(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__rectangle(this, cause);
}
def_pcfunk1(blocks_world_object__rectangle, this, return f2__blocks_world_object__rectangle(this_cause, this));

f2ptr f2__blocks_world_object__color(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__color(this, cause);
}
def_pcfunk1(blocks_world_object__color, this, return f2__blocks_world_object__color(this_cause, this));

f2ptr f2__blocks_world_object__ignore_gravity(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__ignore_gravity(this, cause);
}
def_pcfunk1(blocks_world_object__ignore_gravity, this, return f2__blocks_world_object__ignore_gravity(this_cause, this));

f2ptr f2__blocks_world_object__ignore_gravity__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__ignore_gravity__set(this, cause, value);
}
def_pcfunk2(blocks_world_object__ignore_gravity__set, this, value, return f2__blocks_world_object__ignore_gravity__set(this_cause, this, value));

f2ptr f2__blocks_world_object__holding_object(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__holding_object(this, cause);
}
def_pcfunk1(blocks_world_object__holding_object, this, return f2__blocks_world_object__holding_object(this_cause, this));

f2ptr f2__blocks_world_object__holding_object__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_object__holding_object__set(this, cause, value);
}
def_pcfunk2(blocks_world_object__holding_object__set, this, value, return f2__blocks_world_object__holding_object__set(this_cause, this, value));


/*
[defunk blocks_world_object-render [this]
  [let [[type [blocks_world_object-type this]]]
    [let [[render_char [cond [[eq type `table]   [string-elt '-' 0]]
			     [[eq type `block]   [string-elt '*' 0]]
			     [[eq type `gripper] [string-elt '~' 0]]
			     [t                  [string-elt '?' 0]]]]]
      [let [[rectangle [blocks_world_object-rectangle this]]]
	[let [[color [blocks_world_object-color this]]]
	  [blocks_world_color-render color]
	  [blocks_world_rectangle-render rectangle render_char]
	  [ansi-stream-foreground stdout 15]
	  ]]]]]
*/

f2ptr f2__blocks_world_object__render(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr type = f2blocks_world_object__type(this, cause);
  char render_char;
  if (type == __funk2.globalenv.blocks_world.table__symbol) {
    render_char = '-';
  } else if (type == __funk2.globalenv.blocks_world.block__symbol) {
    if (f2blocks_world_object__ignore_gravity(this, cause)) {
      render_char = '+';
    } else {
      render_char = '*';
    }
  } else if (type == __funk2.globalenv.blocks_world.gripper__symbol) {
    if (f2blocks_world_object__holding_object(this, cause)) {
      render_char = '-';
    } else {
      render_char = '~';
    }
  } else {
    render_char = '?';
  }
  f2ptr rectangle = f2blocks_world_object__rectangle(this, cause);
  f2ptr color     = f2blocks_world_object__color(this, cause);
  if (raw__larva__is_type(cause, f2__blocks_world_color__render(cause, color))) {
    return f2larva__new(cause, 2, nil);
  }
  if (raw__larva__is_type(cause, raw__blocks_world_rectangle__render(cause, rectangle, render_char))) {
    return f2larva__new(cause, 2, nil);
  }
  raw__ansi__stream__foreground(cause, __funk2.globalenv.stdout_stream, 7);
  return nil;
}
def_pcfunk1(blocks_world_object__render, this, return f2__blocks_world_object__render(this_cause, this));

/*
[defunk blocks_world_object-translate_overlaps_objects [this dx dy objects]
  [let [[rectangle [blocks_world_object-rectangle this]]]
    [let [[translate_rectangle [blocks_world_rectangle-new_translate rectangle dx dy]]]
      [let [[object_iter          objects]
	    [found_overlap_object nil]]
	[while object_iter
	  [let [[object [car object_iter]]]
	    [let [[object_rectangle [blocks_world_object-rectangle object]]]
	      [if [blocks_world_rectangle-overlaps translate_rectangle object_rectangle]
		  [prog [set found_overlap_object object]
			[set object_iter          nil]]
		[set object_iter [cdr object_iter]]]]]]
	found_overlap_object]]]]
 */

f2ptr raw__blocks_world_object__translate_overlaps_objects(f2ptr cause, f2ptr this, s64 dx, s64 dy, f2ptr objects) {
  if (! raw__blocks_world_object__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr rectangle           = f2blocks_world_object__rectangle(this, cause);
  f2ptr translate_rectangle = raw__blocks_world_rectangle__new_translate(cause, rectangle, dx, dy);
  
  f2ptr object_iter = objects;
  while (object_iter) {
    if (! raw__cons__is_type(cause, object_iter)) {
      return f2larva__new(cause, 1, nil);
    }
    f2ptr object = f2cons__car(object_iter, cause);
    if (! raw__blocks_world_object__is_type(cause, object)) {
      return f2larva__new(cause, 1, nil);
    }
    f2ptr object_rectangle = f2blocks_world_object__rectangle(object, cause);
    f2ptr overlaps_result = f2__blocks_world_rectangle__overlaps(cause, translate_rectangle, object_rectangle);
    if (raw__larva__is_type(cause, overlaps_result)) {
      return overlaps_result; // propogate error larva
    }
    if (overlaps_result) {
      return object;
    }
    object_iter = f2cons__cdr(object_iter, cause);
  }
  return nil;
}

f2ptr f2__blocks_world_object__translate_overlaps_objects(f2ptr cause, f2ptr this, f2ptr dx, f2ptr dy, f2ptr objects) {
  if ((! raw__integer__is_type(cause, dx)) ||
      (! raw__integer__is_type(cause, dy))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_dx = f2integer__i(dx, cause);
  s64 raw_dy = f2integer__i(dy, cause);
  return raw__blocks_world_object__translate_overlaps_objects(cause, this, raw_dx, raw_dy, objects);
}
def_pcfunk4(blocks_world_object__translate_overlaps_objects, this, dx, dy, objects, return f2__blocks_world_object__translate_overlaps_objects(this_cause, this, dx, dy, objects));


// blocks_world

defprimobject__static_slot(blocks_world_physics__objects, 0);

f2ptr __blocks_world_physics__symbol = -1;

f2ptr f2blocks_world_physics__new(f2ptr cause, f2ptr objects) {
  release__assert(__blocks_world_physics__symbol != -1, nil, "f2blocks_world_physics__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __blocks_world_physics__symbol, 1, nil);
  f2blocks_world_physics__objects__set(this, cause, objects);
  return this;
}
def_pcfunk1(blocks_world_physics__new, objects, return f2blocks_world_physics__new(this_cause, objects));

f2ptr f2__blocks_world_physics__objects(f2ptr cause, f2ptr this) {
  if (! raw__blocks_world_physics__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2blocks_world_physics__objects(this, cause);
}
def_pcfunk1(blocks_world_physics__objects, this, return f2__blocks_world_physics__objects(this_cause, this));

boolean_t raw__blocks_world_physics__is_type(f2ptr cause, f2ptr this) {
  return (raw__primobject__is_type(cause, this) && f2primobject__is__blocks_world_physics(this, cause));
}

f2ptr f2__blocks_world_physics__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__blocks_world_physics__is_type(cause, this));
}
def_pcfunk1(blocks_world_physics__is_type, this, return f2__blocks_world_physics__is_type(this_cause, this));

// **

void f2__blocks_world__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  __blocks_world_rectangle__symbol = f2symbol__new(cause, strlen("blocks_world_rectangle"), (u8*)"blocks_world_rectangle");
  __blocks_world_color__symbol     = f2symbol__new(cause, strlen("blocks_world_color"),     (u8*)"blocks_world_color");
  __blocks_world_object__symbol    = f2symbol__new(cause, strlen("blocks_world_object"),    (u8*)"blocks_world_object");
  __blocks_world_physics__symbol   = f2symbol__new(cause, strlen("blocks_world_physics"),   (u8*)"blocks_world_physics");
  
  __funk2.globalenv.blocks_world.red__symbol     = f2symbol__new(cause, strlen("red"),     (u8*)"red");
  __funk2.globalenv.blocks_world.green__symbol   = f2symbol__new(cause, strlen("green"),   (u8*)"green");
  __funk2.globalenv.blocks_world.blue__symbol    = f2symbol__new(cause, strlen("blue"),    (u8*)"blue");
  __funk2.globalenv.blocks_world.white__symbol   = f2symbol__new(cause, strlen("white"),   (u8*)"white");
  __funk2.globalenv.blocks_world.magenta__symbol = f2symbol__new(cause, strlen("magenta"), (u8*)"magenta");
  __funk2.globalenv.blocks_world.yellow__symbol  = f2symbol__new(cause, strlen("yellow"),  (u8*)"yellow");

  __funk2.globalenv.blocks_world.table__symbol   = f2symbol__new(cause, strlen("table"),   (u8*)"table");
  __funk2.globalenv.blocks_world.block__symbol   = f2symbol__new(cause, strlen("block"),   (u8*)"block");
  __funk2.globalenv.blocks_world.gripper__symbol = f2symbol__new(cause, strlen("gripper"), (u8*)"gripper");
}

void f2__blocks_world__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "blocks_world", "", &f2__blocks_world__reinitialize_globalvars);
  
  f2__blocks_world__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_blocks_world_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __blocks_world_rectangle__symbol, nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_color__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_object__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __blocks_world_physics__symbol,   nil);
  
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.red__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.green__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.blue__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.white__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.magenta__symbol, nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.yellow__symbol,  nil);
  
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.table__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.block__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.globalenv.blocks_world.gripper__symbol, nil);
  
  f2__primcfunk__init(blocks_world__lower_left__x, "");
  f2__primcfunk__init(blocks_world__lower_left__y, "");
  
  f2__primcfunk__init(blocks_world_rectangle__new, "");
  f2__primcfunk__init(blocks_world_rectangle__is_type, "");
  f2__primcfunk__init(blocks_world_rectangle__x0, "");
  f2__primcfunk__init(blocks_world_rectangle__y0, "");
  f2__primcfunk__init(blocks_world_rectangle__x1, "");
  f2__primcfunk__init(blocks_world_rectangle__y1, "");
  f2__primcfunk__init(blocks_world_rectangle__new_copy, "");
  f2__primcfunk__init(blocks_world_rectangle__create, "");
  f2__primcfunk__init(blocks_world_rectangle__render, "");
  f2__primcfunk__init(blocks_world_rectangle__clear_line_above, "");
  f2__primcfunk__init(blocks_world_rectangle__translate, "");
  f2__primcfunk__init(blocks_world_rectangle__new_translate, "");
  f2__primcfunk__init(blocks_world_rectangle__overlaps, "");
  
  f2__primcfunk__init(blocks_world_color__new, "");
  f2__primcfunk__init(blocks_world_color__is_type, "");
  f2__primcfunk__init(blocks_world_color__name, "");
  f2__primcfunk__init(blocks_world_color__render, "");
  
  f2__primcfunk__init(blocks_world_object__new, "");
  f2__primcfunk__init(blocks_world_object__is_type, "");
  f2__primcfunk__init(blocks_world_object__name, "");
  f2__primcfunk__init(blocks_world_object__type, "");
  f2__primcfunk__init(blocks_world_object__rectangle, "");
  f2__primcfunk__init(blocks_world_object__color, "");
  f2__primcfunk__init(blocks_world_object__ignore_gravity, "");
  f2__primcfunk__init(blocks_world_object__ignore_gravity__set, "");
  f2__primcfunk__init(blocks_world_object__holding_object, "");
  f2__primcfunk__init(blocks_world_object__holding_object__set, "");
  f2__primcfunk__init(blocks_world_object__render, "");
  f2__primcfunk__init(blocks_world_object__translate_overlaps_objects, "");
  
  f2__primcfunk__init(blocks_world_physics__new, "");
  f2__primcfunk__init(blocks_world_physics__is_type, "");
  f2__primcfunk__init(blocks_world_physics__objects, "");
}

