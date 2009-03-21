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

// text_buffer_character primobject definition

defprimobject__static_slot(text_buffer_character__character,        0);
defprimobject__static_slot(text_buffer_character__foreground_color, 1);
defprimobject__static_slot(text_buffer_character__background_color, 2);

f2ptr __text_buffer_character__symbol = -1;

f2ptr f2text_buffer_character__new(f2ptr cause, f2ptr character, f2ptr foreground_color, f2ptr background_color) {
  if (__text_buffer_character__symbol == -1) {__text_buffer_character__symbol = f2symbol__new(cause, strlen("text_buffer_character"), (u8*)"text_buffer_character");}
  f2ptr this = f2__primobject__new(cause, __text_buffer_character__symbol, 5, nil);
  f2text_buffer_character__character__set( this, cause, character);
  f2text_buffer_character__foreground_color__set(this, cause, foreground_color);
  f2text_buffer_character__background_color__set(this, cause, background_color);
  return this;
}

boolean_t raw__text_buffer_characterp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_buffer_character(this, cause));}
f2ptr f2__text_buffer_characterp(f2ptr this, f2ptr cause) {return f2bool__new(raw__text_buffer_characterp(this, cause));}


// text_buffer primobject definition

defprimobject__static_slot(text_buffer__width,      0);
defprimobject__static_slot(text_buffer__height,     1);
defprimobject__static_slot(text_buffer__characters, 2);

f2ptr __text_buffer__symbol = -1;

f2ptr f2text_buffer__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr characters) {
  if (__text_buffer__symbol == -1) {__text_buffer__symbol = f2symbol__new(cause, strlen("text_buffer"), (u8*)"text_buffer");}
  f2ptr this = f2__primobject__new(cause, __text_buffer__symbol, 5, nil);
  f2text_buffer__width__set(     this, cause, width);
  f2text_buffer__height__set(    this, cause, height);
  f2text_buffer__characters__set(this, cause, characters);
  return this;
}

boolean_t raw__text_bufferp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_buffer(this, cause));}
f2ptr f2__text_bufferp(f2ptr this, f2ptr cause) {return f2bool__new(raw__text_bufferp(this, cause));}

f2ptr raw__text_buffer__create(f2ptr cause, s64 width, s64 height) {
  if (width <= 0 || height <= 0) {
    return f2larva__new(cause, 56);
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
  if ((! raw__integerp(width, cause)) || 
      (! raw__integerp(height, cause))) {
    return f2larva__new(cause, 1);
  }
  s64 raw_width  = f2integer__i(width,  cause);
  s64 raw_height = f2integer__i(height, cause);
  return raw__text_buffer__create(cause, raw_width, raw_height);
}
def_pcfunk2(text_buffer__create, width, height, return f2__text_buffer__create(this_cause, width, height));

f2ptr raw__text_buffer__character(f2ptr cause, f2ptr this, s64 x, s64 y) {
  if (! raw__text_bufferp(this, cause)) {
    return f2larva__new(cause, 1);
  }
  if (x < 0 || y < 0) {
    return f2larva__new(cause, 57);
  }
  f2ptr   width  = f2text_buffer__width(this, cause);
  s64 raw_width  = f2integer__i(width, cause);
  f2ptr   height = f2text_buffer__height(this, cause);
  s64 raw_height = f2integer__i(height, cause);
  if (x >= raw_width || y >= raw_height) {
    return f2larva__new(cause, 57);
  }
  f2ptr characters = f2text_buffer__characters(this, cause);
  return raw__array__elt(cause, characters, y * raw_width + x);
}

f2ptr raw__text_buffer__character__set(f2ptr cause, f2ptr this, s64 x, s64 y, f2ptr text_char) {
  if ((! raw__text_bufferp(this, cause)) ||
      (! raw__text_buffer_characterp(text_char, cause))) {
    return f2larva__new(cause, 1);
  }
  if (x < 0 || y < 0) {
    return f2larva__new(cause, 57);
  }
  f2ptr   width  = f2text_buffer__width(this, cause);
  s64 raw_width  = f2integer__i(width, cause);
  f2ptr   height = f2text_buffer__height(this, cause);
  s64 raw_height = f2integer__i(height, cause);
  if (x >= raw_width || y >= raw_height) {
    return f2larva__new(cause, 57);
  }
  f2ptr characters = f2text_buffer__characters(this, cause);
  return raw__array__elt__set(cause, characters, y * raw_width + x, text_char);
}

f2ptr raw__text_buffer__draw_character(f2ptr cause, f2ptr this, s64 x, s64 y, f2ptr character, f2ptr foreground_color, f2ptr background_color) {
  if ((! raw__text_bufferp(this, cause)) ||
      (! raw__charp(character, cause))) {
    return f2larva__new(cause, 1);
  }
  f2ptr text_char = f2text_buffer_character__new(cause, character, foreground_color, background_color);
  return raw__text_buffer__character__set(cause, this, x, y, text_char);
}


// text_window primobject definition

defprimobject__static_slot(text_window__width,      0);
defprimobject__static_slot(text_window__height,     1);
defprimobject__static_slot(text_window__characters, 2);

f2ptr __text_window__symbol = -1;

f2ptr f2text_window__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr characters) {
  if (__text_window__symbol == -1) {__text_window__symbol = f2symbol__new(cause, strlen("text_window"), (u8*)"text_window");}
  f2ptr this = f2__primobject__new(cause, __text_window__symbol, 5, nil);
  f2text_window__width__set(     this, cause, width);
  f2text_window__height__set(    this, cause, height);
  f2text_window__characters__set(this, cause, characters);
  return this;
}

boolean_t raw__text_windowp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_window(this, cause));}
f2ptr f2__text_windowp(f2ptr this, f2ptr cause) {return f2bool__new(raw__text_windowp(this, cause));}


// **

void f2__primobject__text_buffer__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __text_buffer_character__symbol = f2symbol__new(cause, strlen("text_buffer_character"), (u8*)"text_buffer_character");
  __text_buffer__symbol           = f2symbol__new(cause, strlen("text_buffer"),           (u8*)"text_buffer");
  __text_window__symbol           = f2symbol__new(cause, strlen("text_window"),           (u8*)"text_window");
}

void f2__primobject__text_buffer__initialize() {
  pause_gc();
  f2__primobject__text_buffer__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __text_buffer_character__symbol, nil);
  environment__add_var_value(cause, global_environment(), __text_buffer__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __text_window__symbol,           nil);
  
  f2__primcfunk__init__2(text_buffer__create, width, height);
  
  resume_gc();
  try_gc();
}

