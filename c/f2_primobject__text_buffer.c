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

// text_buffer_character primobject definition

defprimobject__static_slot(text_buffer_character__character,        0);
defprimobject__static_slot(text_buffer_character__foreground_color, 1);
defprimobject__static_slot(text_buffer_character__background_color, 2);

f2ptr __text_buffer_character__symbol = -1;

f2ptr f2text_buffer_character__new(f2ptr cause, f2ptr character, f2ptr foreground_color, f2ptr background_color) {
  if (__text_buffer_character__symbol == -1) {__text_buffer_character__symbol = f2symbol__new(cause, strlen("text_buffer_character"), (u8*)"text_buffer_character");}
  f2ptr this = f2__primobject__new(cause, __text_buffer_character__symbol, 3, nil);
  f2text_buffer_character__character__set(       this, cause, character);
  f2text_buffer_character__foreground_color__set(this, cause, foreground_color);
  f2text_buffer_character__background_color__set(this, cause, background_color);
  return this;
}

boolean_t raw__text_buffer_character__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_buffer_character(this, cause));}
f2ptr f2__text_buffer_character__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__text_buffer_character__is_type(cause, this));}


// text_buffer primobject definition

defprimobject__static_slot(text_buffer__width,      0);
defprimobject__static_slot(text_buffer__height,     1);
defprimobject__static_slot(text_buffer__characters, 2);

f2ptr __text_buffer__symbol = -1;

f2ptr f2text_buffer__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr characters) {
  if (__text_buffer__symbol == -1) {__text_buffer__symbol = f2symbol__new(cause, strlen("text_buffer"), (u8*)"text_buffer");}
  f2ptr this = f2__primobject__new(cause, __text_buffer__symbol, 3, nil);
  f2text_buffer__width__set(     this, cause, width);
  f2text_buffer__height__set(    this, cause, height);
  f2text_buffer__characters__set(this, cause, characters);
  return this;
}

boolean_t raw__text_buffer__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_buffer(this, cause));}
f2ptr f2__text_buffer__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__text_buffer__is_type(cause, this));}

f2ptr raw__text_buffer__create(f2ptr cause, s64 width, s64 height) {
  if (width <= 0 || height <= 0) {
    return f2larva__new(cause, 56, nil);
  }
  f2ptr characters = raw__array__new(cause, width * height);
  s64 x, y;
  for (y = 0; y < height; y ++) {
    for (x = 0; x < width; x ++) {
      raw__array__elt__set(cause, characters, y * width + x, f2text_buffer_character__new(cause, f2char__new(cause, ' '), nil, nil));
    }
  }
  f2ptr text_buffer = f2text_buffer__new(cause, f2integer__new(cause, width), f2integer__new(cause, height), characters);
  return text_buffer; 
}

f2ptr f2__text_buffer__create(f2ptr cause, f2ptr width, f2ptr height) {
  if ((! raw__integer__is_type(cause, width)) || 
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_width  = f2integer__i(width,  cause);
  s64 raw_height = f2integer__i(height, cause);
  return raw__text_buffer__create(cause, raw_width, raw_height);
}
def_pcfunk2(text_buffer__create, width, height, return f2__text_buffer__create(this_cause, width, height));

f2ptr raw__text_buffer__character(f2ptr cause, f2ptr this, s64 x, s64 y) {
  if (! raw__text_buffer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  if (x < 0 || y < 0) {
    return f2larva__new(cause, 57, nil);
  }
  f2ptr   width  = f2text_buffer__width(this, cause);
  s64 raw_width  = f2integer__i(width, cause);
  f2ptr   height = f2text_buffer__height(this, cause);
  s64 raw_height = f2integer__i(height, cause);
  if (x >= raw_width || y >= raw_height) {
    return f2larva__new(cause, 57, nil);
  }
  f2ptr characters = f2text_buffer__characters(this, cause);
  return raw__array__elt(cause, characters, y * raw_width + x);
}

f2ptr raw__text_buffer__character__set(f2ptr cause, f2ptr this, s64 x, s64 y, f2ptr text_char) {
  if ((! raw__text_buffer__is_type(cause, this)) ||
      (! raw__text_buffer_character__is_type(cause, text_char))) {
    return f2larva__new(cause, 1, nil);
  }
  if (x < 0 || y < 0) {
    return f2larva__new(cause, 57, nil);
  }
  f2ptr   width  = f2text_buffer__width(this, cause);
  s64 raw_width  = f2integer__i(width, cause);
  f2ptr   height = f2text_buffer__height(this, cause);
  s64 raw_height = f2integer__i(height, cause);
  if (x >= raw_width || y >= raw_height) {
    return f2larva__new(cause, 57, nil);
  }
  f2ptr characters = f2text_buffer__characters(this, cause);
  return raw__array__elt__set(cause, characters, y * raw_width + x, text_char);
}

f2ptr raw__text_buffer__draw_character(f2ptr cause, f2ptr this, s64 x, s64 y, f2ptr character, f2ptr foreground_color, f2ptr background_color) {
  if ((! raw__text_buffer__is_type(cause, this)) ||
      (! raw__char__is_type(cause, character))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr text_char = f2text_buffer_character__new(cause, character, foreground_color, background_color);
  return raw__text_buffer__character__set(cause, this, x, y, text_char);
}

/*
f2ptr raw__text_buffer__copy_rect(f2ptr cause, f2ptr this, f2ptr src_text_window, s64 dest_x0, s64 dest_y0, s64 x0, s64 y0, s64 x1, s64 y1) {
  if ((! raw__text_bufferp(this, cause)) ||
      (! raw__text_bufferp(src_text_window, cause))) {
    return f2larva__new(cause, 1, nil);
  }
  if (dest_x0 < 0 || dest_y0 < 0 || x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0) {
    return f2larva__new(cause, 2, nil);
  }
  f2ptr     width  = f2text_buffer__width(this, cause);
  f2ptr     height = f2text_buffer__height(this, cause);
  f2ptr src_width  = f2text_buffer__width(src_text_window, cause);
  f2ptr src_height = f2text_buffer__height(src_text_window, cause);
  s64   raw_width  = f2integer__i(width, cause);
  s64   raw_height = f2integer__i(height, cause);
  s64   raw_width  = f2integer__i(src_width, cause);
  s64   raw_height = f2integer__i(src_height, cause);
  
}
*/

// text_cursor primobject definition

defprimobject__static_slot(text_cursor__x,                0);
defprimobject__static_slot(text_cursor__y,                1);
defprimobject__static_slot(text_cursor__foreground_color, 2);
defprimobject__static_slot(text_cursor__background_color, 3);

f2ptr __text_cursor__symbol = -1;

f2ptr f2text_cursor__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr foreground_color, f2ptr background_color) {
  if (__text_cursor__symbol == -1) {__text_cursor__symbol = f2symbol__new(cause, strlen("text_cursor"), (u8*)"text_cursor");}
  f2ptr this = f2__primobject__new(cause, __text_cursor__symbol, 4, nil);
  f2text_cursor__x__set(               this, cause, x);
  f2text_cursor__y__set(               this, cause, y);
  f2text_cursor__foreground_color__set(this, cause, foreground_color);
  f2text_cursor__background_color__set(this, cause, background_color);
  return this;
}

boolean_t raw__text_cursor__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_cursor(this, cause));}
f2ptr      f2__text_cursor__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__text_cursor__is_type(cause, this));}


// text_window primobject definition

defprimobject__static_slot(text_window__double_buffer, 0);
defprimobject__static_slot(text_window__cursor,        1);

f2ptr __text_window__symbol = -1;

f2ptr f2text_window__new(f2ptr cause, f2ptr double_buffer, f2ptr cursor) {
  if (__text_window__symbol == -1) {__text_window__symbol = f2symbol__new(cause, strlen("text_window"), (u8*)"text_window");}
  f2ptr this = f2__primobject__new(cause, __text_window__symbol, 2, nil);
  f2text_window__double_buffer__set(this, cause, double_buffer);
  f2text_window__cursor__set(       this, cause, cursor);
  return this;
}

boolean_t raw__text_window__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_window(this, cause));}
f2ptr f2__text_window__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__text_window__is_type(cause, this));}

f2ptr raw__text_window__create(f2ptr cause, s64 width, s64 height) {
  if (width < 0 || height < 0) {
    return f2larva__new(cause, 58, nil);
  }
  f2ptr double_buffer = raw__array__new(cause, 2);
  f2ptr front_buffer = raw__text_buffer__create(cause, width, height);
  f2ptr back_buffer  = raw__text_buffer__create(cause, width, height);
  raw__array__elt__set(cause, double_buffer, 0, front_buffer);
  raw__array__elt__set(cause, double_buffer, 1, back_buffer);
  f2ptr cursor = f2text_cursor__new(cause, f2integer__new(cause, 0), f2integer__new(cause, 0), nil, nil);
  f2ptr text_window = f2text_window__new(cause, double_buffer, cursor);
  return text_window;
}

f2ptr f2__text_window__create(f2ptr cause, f2ptr width, f2ptr height) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_width  = f2integer__i(width,  cause);
  s64 raw_height = f2integer__i(height, cause);
  return raw__text_window__create(cause, raw_width, raw_height);
}
def_pcfunk2(text_window__create, width, height, return f2__text_window__create(this_cause, width, height));

f2ptr raw__text_window__stream__render(f2ptr cause, f2ptr this, f2ptr stream, s64 screen_x0, s64 screen_y0, s64 x0, s64 y0, s64 x1, s64 y1) {
  if ((! raw__text_window__is_type(cause, this)) ||
      (! raw__stream__is_type(cause, stream))) {
    return f2larva__new(cause, 1, nil);
  }
  if (x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0) {
    return f2larva__new(cause, 2, nil);
  }
  if (x0 > x1 || y0 > y1) {
    return f2larva__new(cause, 3, nil);
  }
  f2ptr double_buffer = f2text_window__double_buffer(this, cause);
  f2ptr front_buffer  = raw__array__elt(cause, double_buffer, 0);
  f2ptr width  = f2text_buffer__width(front_buffer, cause);
  f2ptr height = f2text_buffer__height(front_buffer, cause);
  s64 raw_width  = f2integer__i(width,  cause);
  s64 raw_height = f2integer__i(height, cause);
  if (x0 >= raw_width || y0 >= raw_height || x1 >= raw_width || y1 >= raw_height) {
    return f2larva__new(cause, 4, nil);
  }
  s64 render_width  = (x1 - x0) + 1;
  s64 render_height = (y1 - y0) + 1;
  s64 screen_x1 = screen_x0 + render_width  - 1;
  s64 screen_y1 = screen_y0 + render_height - 1;
  if (screen_x0 < 0 || screen_y0 < 0 || screen_x1 < 0 || screen_y1 < 0) {
    return f2larva__new(cause, 5, nil);
  }
  s64 screen_width  = raw__termios__width();
  s64 screen_height = raw__termios__height();
  if (screen_x0 >= screen_width || screen_y0 >= screen_height || screen_x1 >= screen_width || screen_y1 >= screen_height) {
    return f2larva__new(cause, 6, nil);
  }
  s64 ix, iy;
  for (iy = y0; iy <= y1; iy ++) {
    raw__ansi__stream__move_cursor(cause, stream, screen_x0, screen_y0 + (iy - y0));
    for (ix = x0; ix <= x1; ix ++) {
      f2ptr text_char = raw__text_buffer__character(cause, front_buffer, ix, iy);
      f2ptr character = f2text_buffer_character__character(text_char, cause);
      char ch = f2char__ch(character, cause);
      raw__stream__writef(cause, stream, "%c", ch);
    }
  }
  return nil;
}

f2ptr f2__text_window__stream__render(f2ptr cause, f2ptr this, f2ptr stream, f2ptr screen_x0, f2ptr screen_y0, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1) {
  if ((! raw__integer__is_type(cause, screen_x0)) ||
      (! raw__integer__is_type(cause, screen_y0)) ||
      (! raw__integer__is_type(cause, x0)) ||
      (! raw__integer__is_type(cause, y0)) ||
      (! raw__integer__is_type(cause, x1)) ||
      (! raw__integer__is_type(cause, y1))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 raw_screen_x0 = f2integer__i(screen_x0, cause);
  s64 raw_screen_y0 = f2integer__i(screen_y0, cause);
  s64 raw_x0 = f2integer__i(x0, cause);
  s64 raw_y0 = f2integer__i(y0, cause);
  s64 raw_x1 = f2integer__i(x1, cause);
  s64 raw_y1 = f2integer__i(y1, cause);
  return raw__text_window__stream__render(cause, this, stream, raw_screen_x0, raw_screen_y0, raw_x0, raw_y0, raw_x1, raw_y1);
}
def_pcfunk8(text_window__stream__render, this, stream, screen_x0, screen_y0, x0, y0, x1, y1, return f2__text_window__stream__render(this_cause, this, stream, screen_x0, screen_y0, x0, y0, x1, y1));

/*
f2ptr raw__text_window__copy_rect(f2ptr cause, f2ptr this, f2ptr src_text_window, s64 dest_x0, s64 dest_y0, s64 x0, s64 y0, s64 x1, s64 y1) {
  if ((! raw__text_windowp(this,            cause)) ||
      (! raw__text_windowp(src_text_window, cause))) {
    return f2larva__new(cause, 1, nil);
  }
  if (dest_x0 < 0 || dest_y0 < 0 || x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0) {
    return f2larva__new(cause, 2, nil);
  }
  if (x0 > x1 || y0 > y1) {
    return f2larva__new(cause, 3, nil);
  }
  f2ptr double_buffer = f2text_window__double_buffer(this, cause);
  f2ptr front_buffer  = raw__array__elt(cause, double_buffer, 0);
  f2ptr back_buffer   = raw__array__elt(cause, double_buffer, 1);
  
}
*/

/*
f2ptr raw__text_window__new_resized(f2ptr cause, f2ptr this, s64 new_width, s64 new_height) {
  if (! raw__text_windowp(this, cause)) {
    return f2larva__new(cause, 1, nil);
  }
  if (new_width <= 0 || new_height <= 0) {
    return f2larva__new(cause, 2, nil);
  }
  f2ptr new_text_window = raw__text_window__create(cause, new_width, new_height);
  f2ptr double_buffer 
}
*/

// **

void f2__primobject__text_buffer__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __text_buffer_character__symbol = f2symbol__new(cause, strlen("text_buffer_character"), (u8*)"text_buffer_character");
  __text_buffer__symbol           = f2symbol__new(cause, strlen("text_buffer"),           (u8*)"text_buffer");
  __text_cursor__symbol           = f2symbol__new(cause, strlen("text_cursor"),           (u8*)"text_cursor");
  __text_window__symbol           = f2symbol__new(cause, strlen("text_window"),           (u8*)"text_window");
}

void f2__primobject__text_buffer__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__text_buffer", "", &f2__primobject__text_buffer__reinitialize_globalvars);
  
  f2__primobject__text_buffer__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __text_buffer_character__symbol, nil);
  environment__add_var_value(cause, global_environment(), __text_buffer__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __text_cursor__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __text_window__symbol,           nil);
  
  f2__primcfunk__init__2(text_buffer__create, width, height, "");
  f2__primcfunk__init__2(text_window__create, width, height, "");
  f2__primcfunk__init__8(text_window__stream__render, this, stream, screen_x0, screen_y0, x0, y0, x1, y1, "");
}

