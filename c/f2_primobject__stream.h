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

#ifndef F2__PRIMOBJECT__STREAM__H
#define F2__PRIMOBJECT__STREAM__H

#include "f2_primobjects.h"

// stream

extern f2ptr __stream__symbol;
f2ptr f2stream__new(f2ptr cause, f2ptr integer_value, f2ptr ungetc_stack);
#define      f2primobject__is__stream(this, cause) raw__eq(cause, f2primobject__type(this, cause), __stream__symbol)

defprimobject__static_slot__prototype(stream__file_descriptor);
#define      f2stream__file_descriptor(            this, cause)        primobject__static_slot__accessor(  this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__set(       this, cause, value) primobject__static_slot__set(       this, stream__file_descriptor, cause, value)
#define      f2stream__file_descriptor__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__trace(     this, cause)        primobject__static_slot__trace(     this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, stream__file_descriptor, cause)

defprimobject__static_slot__prototype(stream__ungetc_stack);
#define      f2stream__ungetc_stack(            this, cause)        primobject__static_slot__accessor(  this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__set(       this, cause, value) primobject__static_slot__set(       this, stream__ungetc_stack, cause, value)
#define      f2stream__ungetc_stack__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__trace(     this, cause)        primobject__static_slot__trace(     this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, stream__ungetc_stack, cause)

bool raw__streamp(f2ptr this, f2ptr cause);
f2ptr f2__streamp(f2ptr this, f2ptr cause);

f2ptr raw__stream__new_open_file(f2ptr cause, char* filename, int mode);
f2ptr f2__stream__new_open_file(f2ptr cause, f2ptr filename, f2ptr mode);
f2ptr f2__stream__close(f2ptr cause, f2ptr this);
f2ptr f2__stream__file_mode__rdonly(f2ptr cause);
f2ptr f2__stream__file_mode__creat(f2ptr cause);
f2ptr f2__stream__file_mode__rdwr(f2ptr cause);
f2ptr f2__stream__new_open_file__rdonly(f2ptr cause, f2ptr filename);
f2ptr f2__stream__new_open_file__rdwr(f2ptr cause, f2ptr filename);

f2ptr f2__stream__ungetc(f2ptr cause, f2ptr this, f2ptr character);
void  raw__stream__ungetc(f2ptr cause, f2ptr this, char ch);
f2ptr f2__stream__try_read_character(f2ptr cause, f2ptr this);

// **

void f2__primobject__stream__reinitialize_globalvars();
void f2__primobject__stream__initialize();

#endif // F2__PRIMOBJECT__STREAM__H
