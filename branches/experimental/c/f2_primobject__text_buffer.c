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

defprimobject__static_slot(text_buffer_character__character,  0);
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

defprimobject__static_slot(text_buffer__width,  0);
defprimobject__static_slot(text_buffer__height, 1);
defprimobject__static_slot(text_buffer__buffer, 2);

f2ptr __text_buffer__symbol = -1;

f2ptr f2text_buffer__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr buffer) {
  if (__text_buffer__symbol == -1) {__text_buffer__symbol = f2symbol__new(cause, strlen("text_buffer"), (u8*)"text_buffer");}
  f2ptr this = f2__primobject__new(cause, __text_buffer__symbol, 5, nil);
  f2text_buffer__width__set( this, cause, width);
  f2text_buffer__height__set(this, cause, height);
  f2text_buffer__buffer__set(this, cause, buffer);
  return this;
}

boolean_t raw__text_bufferp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__text_buffer(this, cause));}
f2ptr f2__text_bufferp(f2ptr this, f2ptr cause) {return f2bool__new(raw__text_bufferp(this, cause));}



// **

void f2__primobject__text_buffer__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __text_buffer_character__symbol = f2symbol__new(cause, strlen("text_buffer_character"), (u8*)"text_buffer_character");
  __text_buffer__symbol           = f2symbol__new(cause, strlen("text_buffer"),           (u8*)"text_buffer");
}

void f2__primobject__text_buffer__initialize() {
  pause_gc();
  f2__primobject__text_buffer__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __text_buffer_character__symbol, nil);
  environment__add_var_value(cause, global_environment(), __text_buffer__symbol,           nil);
  
  //f2__primcfunk__init(file_text_buffer__new);
  
  resume_gc();
  try_gc();
}

