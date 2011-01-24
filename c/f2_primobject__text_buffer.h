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

#ifndef F2__PRIMOBJECT__TEXT_BUFFER__H
#define F2__PRIMOBJECT__TEXT_BUFFER__H

#include "f2_primobjects.h"

// text_buffer_character

extern f2ptr __text_buffer_character__symbol;
f2ptr f2text_buffer_character__new(f2ptr cause, f2ptr character, f2ptr foreground_color, f2ptr background_color);
#define      f2primobject__is__text_buffer_character(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __text_buffer_character__symbol)

defprimobject__static_slot__prototype(text_buffer_character__character);
#define      f2text_buffer_character__character(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer_character__character, cause)
#define      f2text_buffer_character__character__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer_character__character, cause, value)
#define      f2text_buffer_character__character__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer_character__character, cause)
#define      f2text_buffer_character__character__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer_character__character, cause)
#define      f2text_buffer_character__character__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer_character__character, cause)

defprimobject__static_slot__prototype(text_buffer_character__foreground_color);
#define      f2text_buffer_character__foreground_color(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer_character__foreground_color, cause)
#define      f2text_buffer_character__foreground_color__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer_character__foreground_color, cause, value)
#define      f2text_buffer_character__foreground_color__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer_character__foreground_color, cause)
#define      f2text_buffer_character__foreground_color__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer_character__foreground_color, cause)
#define      f2text_buffer_character__foreground_color__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer_character__foreground_color, cause)

defprimobject__static_slot__prototype(text_buffer_character__background_color);
#define      f2text_buffer_character__background_color(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer_character__background_color, cause)
#define      f2text_buffer_character__background_color__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer_character__background_color, cause, value)
#define      f2text_buffer_character__background_color__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer_character__background_color, cause)
#define      f2text_buffer_character__background_color__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer_character__background_color, cause)
#define      f2text_buffer_character__background_color__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer_character__background_color, cause)

boolean_t raw__text_buffer_character__is_type(f2ptr cause, f2ptr this);
f2ptr f2__text_buffer_character__is_type(f2ptr cause, f2ptr this);


// text_buffer

extern f2ptr __text_buffer__symbol;
f2ptr f2text_buffer__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr characters);
#define      f2primobject__is__text_buffer(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __text_buffer__symbol)

defprimobject__static_slot__prototype(text_buffer__width);
#define      f2text_buffer__width(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__width, cause)
#define      f2text_buffer__width__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__width, cause, value)
#define      f2text_buffer__width__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__width, cause)
#define      f2text_buffer__width__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__width, cause)
#define      f2text_buffer__width__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__width, cause)

defprimobject__static_slot__prototype(text_buffer__height);
#define      f2text_buffer__height(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__height, cause)
#define      f2text_buffer__height__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__height, cause, value)
#define      f2text_buffer__height__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__height, cause)
#define      f2text_buffer__height__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__height, cause)
#define      f2text_buffer__height__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__height, cause)

defprimobject__static_slot__prototype(text_buffer__characters);
#define      f2text_buffer__characters(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__characters, cause)
#define      f2text_buffer__characters__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__characters, cause, value)
#define      f2text_buffer__characters__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__characters, cause)
#define      f2text_buffer__characters__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__characters, cause)
#define      f2text_buffer__characters__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__characters, cause)

boolean_t raw__text_buffer__is_type(f2ptr cause, f2ptr this);
f2ptr f2__text_buffer__is_type(f2ptr cause, f2ptr this);


// text_cursor

extern f2ptr __text_cursor__symbol;
f2ptr f2text_cursor__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr foreground_color, f2ptr background_color);
#define      f2primobject__is__text_cursor(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __text_cursor__symbol)

defprimobject__static_slot__prototype(text_cursor__x);
#define      f2text_cursor__x(                   this, cause)        primobject__static_slot__accessor(         this, text_cursor__x, cause)
#define      f2text_cursor__x__set(              this, cause, value) primobject__static_slot__set(              this, text_cursor__x, cause, value)
#define      f2text_cursor__x__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_cursor__x, cause)
#define      f2text_cursor__x__trace(            this, cause)        primobject__static_slot__trace(            this, text_cursor__x, cause)
#define      f2text_cursor__x__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_cursor__x, cause)

defprimobject__static_slot__prototype(text_cursor__y);
#define      f2text_cursor__y(                   this, cause)        primobject__static_slot__accessor(         this, text_cursor__y, cause)
#define      f2text_cursor__y__set(              this, cause, value) primobject__static_slot__set(              this, text_cursor__y, cause, value)
#define      f2text_cursor__y__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_cursor__y, cause)
#define      f2text_cursor__y__trace(            this, cause)        primobject__static_slot__trace(            this, text_cursor__y, cause)
#define      f2text_cursor__y__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_cursor__y, cause)

defprimobject__static_slot__prototype(text_cursor__foreground_color);
#define      f2text_cursor__foreground_color(                   this, cause)        primobject__static_slot__accessor(         this, text_cursor__foreground_color, cause)
#define      f2text_cursor__foreground_color__set(              this, cause, value) primobject__static_slot__set(              this, text_cursor__foreground_color, cause, value)
#define      f2text_cursor__foreground_color__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_cursor__foreground_color, cause)
#define      f2text_cursor__foreground_color__trace(            this, cause)        primobject__static_slot__trace(            this, text_cursor__foreground_color, cause)
#define      f2text_cursor__foreground_color__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_cursor__foreground_color, cause)

defprimobject__static_slot__prototype(text_cursor__background_color);
#define      f2text_cursor__background_color(                   this, cause)        primobject__static_slot__accessor(         this, text_cursor__background_color, cause)
#define      f2text_cursor__background_color__set(              this, cause, value) primobject__static_slot__set(              this, text_cursor__background_color, cause, value)
#define      f2text_cursor__background_color__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_cursor__background_color, cause)
#define      f2text_cursor__background_color__trace(            this, cause)        primobject__static_slot__trace(            this, text_cursor__background_color, cause)
#define      f2text_cursor__background_color__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_cursor__background_color, cause)

boolean_t raw__text_cursor__is_type(f2ptr cause, f2ptr this);
f2ptr      f2__text_cursor__is_type(f2ptr cause, f2ptr this);


// text_window

extern f2ptr __text_window__symbol;
f2ptr f2text_window__new(f2ptr cause, f2ptr double_buffer, f2ptr cursor);
#define      f2primobject__is__text_window(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __text_window__symbol)

defprimobject__static_slot__prototype(text_window__double_buffer);
#define      f2text_window__double_buffer(                   this, cause)        primobject__static_slot__accessor(         this, text_window__double_buffer, cause)
#define      f2text_window__double_buffer__set(              this, cause, value) primobject__static_slot__set(              this, text_window__double_buffer, cause, value)
#define      f2text_window__double_buffer__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_window__double_buffer, cause)
#define      f2text_window__double_buffer__trace(            this, cause)        primobject__static_slot__trace(            this, text_window__double_buffer, cause)
#define      f2text_window__double_buffer__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_window__double_buffer, cause)

defprimobject__static_slot__prototype(text_window__cursor);
#define      f2text_window__cursor(                   this, cause)        primobject__static_slot__accessor(         this, text_window__cursor, cause)
#define      f2text_window__cursor__set(              this, cause, value) primobject__static_slot__set(              this, text_window__cursor, cause, value)
#define      f2text_window__cursor__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_window__cursor, cause)
#define      f2text_window__cursor__trace(            this, cause)        primobject__static_slot__trace(            this, text_window__cursor, cause)
#define      f2text_window__cursor__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_window__cursor, cause)

boolean_t raw__text_window__is_type(f2ptr cause, f2ptr this);
f2ptr f2__text_window__is_type(f2ptr cause, f2ptr this);


// **

void f2__primobject__text_buffer__reinitialize_globalvars();
void f2__primobject__text_buffer__initialize();

#endif // F2__PRIMOBJECT__TEXT_BUFFER__H
