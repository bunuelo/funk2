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

#ifndef F2__PRIMOBJECT__TEXT_BUFFER__H
#define F2__PRIMOBJECT__TEXT_BUFFER__H

#include "f2_primobjects.h"

// text_buffer

extern f2ptr __text_buffer__symbol;
f2ptr f2text_buffer__new(f2ptr cause, f2ptr type, f2ptr ungetc_stack, f2ptr file_descriptor, f2ptr string, f2ptr index);
#define      f2primobject__is__text_buffer(this, cause) raw__eq(cause, f2primobject__type(this, cause), __text_buffer__symbol)

defprimobject__static_slot__prototype(text_buffer__type);
#define      f2text_buffer__type(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__type, cause)
#define      f2text_buffer__type__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__type, cause, value)
#define      f2text_buffer__type__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__type, cause)
#define      f2text_buffer__type__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__type, cause)
#define      f2text_buffer__type__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__file_descriptor, cause)

defprimobject__static_slot__prototype(text_buffer__ungetc_stack);
#define      f2text_buffer__ungetc_stack(            this, cause)        primobject__static_slot__accessor(  this, text_buffer__ungetc_stack, cause)
#define      f2text_buffer__ungetc_stack__set(       this, cause, value) primobject__static_slot__set(       this, text_buffer__ungetc_stack, cause, value)
#define      f2text_buffer__ungetc_stack__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, text_buffer__ungetc_stack, cause)
#define      f2text_buffer__ungetc_stack__trace(     this, cause)        primobject__static_slot__trace(     this, text_buffer__ungetc_stack, cause)
#define      f2text_buffer__ungetc_stack__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, text_buffer__ungetc_stack, cause)

defprimobject__static_slot__prototype(text_buffer__file_descriptor);
#define      f2text_buffer__file_descriptor(            this, cause)        primobject__static_slot__accessor(  this, text_buffer__file_descriptor, cause)
#define      f2text_buffer__file_descriptor__set(       this, cause, value) primobject__static_slot__set(       this, text_buffer__file_descriptor, cause, value)
#define      f2text_buffer__file_descriptor__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, text_buffer__file_descriptor, cause)
#define      f2text_buffer__file_descriptor__trace(     this, cause)        primobject__static_slot__trace(     this, text_buffer__file_descriptor, cause)
#define      f2text_buffer__file_descriptor__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, text_buffer__file_descriptor, cause)

defprimobject__static_slot__prototype(text_buffer__string);
#define      f2text_buffer__string(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__string, cause)
#define      f2text_buffer__string__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__string, cause, value)
#define      f2text_buffer__string__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__string, cause)
#define      f2text_buffer__string__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__string, cause)
#define      f2text_buffer__string__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__string, cause)

defprimobject__static_slot__prototype(text_buffer__index);
#define      f2text_buffer__index(                   this, cause)        primobject__static_slot__accessor(         this, text_buffer__index, cause)
#define      f2text_buffer__index__set(              this, cause, value) primobject__static_slot__set(              this, text_buffer__index, cause, value)
#define      f2text_buffer__index__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, text_buffer__index, cause)
#define      f2text_buffer__index__trace(            this, cause)        primobject__static_slot__trace(            this, text_buffer__index, cause)
#define      f2text_buffer__index__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, text_buffer__index, cause)

boolean_t raw__text_bufferp(f2ptr this, f2ptr cause);
f2ptr      f2__text_bufferp(f2ptr this, f2ptr cause);

// **

void f2__primobject__text_buffer__reinitialize_globalvars();
void f2__primobject__text_buffer__initialize();

#endif // F2__PRIMOBJECT__TEXT_BUFFER__H
