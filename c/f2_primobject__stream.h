// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#ifndef F2__PRIMOBJECT__STREAM__TYPES__H
#define F2__PRIMOBJECT__STREAM__TYPES__H

typedef struct funk2_object_type__stream__slot_s funk2_object_type__stream__slot_t;

// stream

struct funk2_object_type__stream__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr type__set__symbol;
  f2ptr type__set__funk;
  f2ptr ungetc_stack__symbol;
  f2ptr ungetc_stack__funk;
  f2ptr ungetc_stack__set__symbol;
  f2ptr ungetc_stack__set__funk;
  f2ptr rewind_stack__symbol;
  f2ptr rewind_stack__funk;
  f2ptr rewind_stack__set__symbol;
  f2ptr rewind_stack__set__funk;
  f2ptr rewindable__symbol;
  f2ptr rewindable__funk;
  f2ptr rewindable__set__symbol;
  f2ptr rewindable__set__funk;
  f2ptr rewind_length__symbol;
  f2ptr rewind_length__funk;
  f2ptr rewind_length__set__symbol;
  f2ptr rewind_length__set__funk;
  f2ptr file_descriptor__symbol;
  f2ptr file_descriptor__funk;
  f2ptr file_descriptor__set__symbol;
  f2ptr file_descriptor__set__funk;
  f2ptr string__symbol;
  f2ptr string__funk;
  f2ptr string__set__symbol;
  f2ptr string__set__funk;
  f2ptr index__symbol;
  f2ptr index__funk;
  f2ptr index__set__symbol;
  f2ptr index__set__funk;
  f2ptr try_read_character__symbol;
  f2ptr try_read_character__funk;
  f2ptr rewind__symbol;
  f2ptr rewind__funk;
  f2ptr rewind_to_length__symbol;
  f2ptr rewind_to_length__funk;
};

#endif // F2__PRIMOBJECT__STREAM__TYPES__H

#ifndef F2__PRIMOBJECT__STREAM__H
#define F2__PRIMOBJECT__STREAM__H

#include "f2_primobjects.h"

// stream

extern f2ptr __stream__symbol;
boolean_t raw__stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2stream__new(f2ptr cause, f2ptr type, f2ptr ungetc_stack, f2ptr rewind_stack, f2ptr rewindable, f2ptr rewind_length, f2ptr file_descriptor, f2ptr string, f2ptr index);
#define      f2primobject__is__stream(this, cause) raw__eq(cause, f2primobject__type(this, cause), __stream__symbol)

defprimobject__static_slot__prototype(stream__type);
#define      f2stream__type(                   this, cause)        primobject__static_slot__accessor(         this, stream__type, cause)
#define      f2stream__type__set(              this, cause, value) primobject__static_slot__set(              this, stream__type, cause, value)
#define      f2stream__type__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__type, cause)
#define      f2stream__type__trace(            this, cause)        primobject__static_slot__trace(            this, stream__type, cause)
#define      f2stream__type__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__file_descriptor, cause)

defprimobject__static_slot__prototype(stream__ungetc_stack);
#define      f2stream__ungetc_stack(                   this, cause)        primobject__static_slot__accessor(         this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__set(              this, cause, value) primobject__static_slot__set(              this, stream__ungetc_stack, cause, value)
#define      f2stream__ungetc_stack__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__trace(            this, cause)        primobject__static_slot__trace(            this, stream__ungetc_stack, cause)
#define      f2stream__ungetc_stack__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__ungetc_stack, cause)

defprimobject__static_slot__prototype(stream__rewind_stack);
#define      f2stream__rewind_stack(                   this, cause)        primobject__static_slot__accessor(         this, stream__rewind_stack, cause)
#define      f2stream__rewind_stack__set(              this, cause, value) primobject__static_slot__set(              this, stream__rewind_stack, cause, value)
#define      f2stream__rewind_stack__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__rewind_stack, cause)
#define      f2stream__rewind_stack__trace(            this, cause)        primobject__static_slot__trace(            this, stream__rewind_stack, cause)
#define      f2stream__rewind_stack__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__rewind_stack, cause)

defprimobject__static_slot__prototype(stream__rewindable);
#define      f2stream__rewindable(                   this, cause)        primobject__static_slot__accessor(         this, stream__rewindable, cause)
#define      f2stream__rewindable__set(              this, cause, value) primobject__static_slot__set(              this, stream__rewindable, cause, value)
#define      f2stream__rewindable__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__rewindable, cause)
#define      f2stream__rewindable__trace(            this, cause)        primobject__static_slot__trace(            this, stream__rewindable, cause)
#define      f2stream__rewindable__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__rewindable, cause)

defprimobject__static_slot__prototype(stream__rewind_length);
#define      f2stream__rewind_length(                   this, cause)        primobject__static_slot__accessor(         this, stream__rewind_length, cause)
#define      f2stream__rewind_length__set(              this, cause, value) primobject__static_slot__set(              this, stream__rewind_length, cause, value)
#define      f2stream__rewind_length__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__rewind_length, cause)
#define      f2stream__rewind_length__trace(            this, cause)        primobject__static_slot__trace(            this, stream__rewind_length, cause)
#define      f2stream__rewind_length__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__rewind_length, cause)

defprimobject__static_slot__prototype(stream__file_descriptor);
#define      f2stream__file_descriptor(            this, cause)        primobject__static_slot__accessor(  this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__set(       this, cause, value) primobject__static_slot__set(       this, stream__file_descriptor, cause, value)
#define      f2stream__file_descriptor__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__trace(     this, cause)        primobject__static_slot__trace(     this, stream__file_descriptor, cause)
#define      f2stream__file_descriptor__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, stream__file_descriptor, cause)

defprimobject__static_slot__prototype(stream__string);
#define      f2stream__string(                   this, cause)        primobject__static_slot__accessor(         this, stream__string, cause)
#define      f2stream__string__set(              this, cause, value) primobject__static_slot__set(              this, stream__string, cause, value)
#define      f2stream__string__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__string, cause)
#define      f2stream__string__trace(            this, cause)        primobject__static_slot__trace(            this, stream__string, cause)
#define      f2stream__string__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__string, cause)

defprimobject__static_slot__prototype(stream__index);
#define      f2stream__index(                   this, cause)        primobject__static_slot__accessor(         this, stream__index, cause)
#define      f2stream__index__set(              this, cause, value) primobject__static_slot__set(              this, stream__index, cause, value)
#define      f2stream__index__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, stream__index, cause)
#define      f2stream__index__trace(            this, cause)        primobject__static_slot__trace(            this, stream__index, cause)
#define      f2stream__index__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, stream__index, cause)

boolean_t raw__file_stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__file_stream__is_type(f2ptr cause, f2ptr this);

boolean_t raw__string_stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__string_stream__is_type(f2ptr cause, f2ptr this);

f2ptr raw__stream__new_open_file(f2ptr cause, char* filename, int mode);
f2ptr f2__stream__new_open_file(f2ptr cause, f2ptr filename, f2ptr mode);
f2ptr f2__file_stream__close(f2ptr cause, f2ptr this);
f2ptr f2__file_stream__new(f2ptr cause, f2ptr file_descriptor);
f2ptr f2__stream__close(f2ptr cause, f2ptr this);
f2ptr f2__stream__file_mode__rdonly(f2ptr cause);
f2ptr f2__stream__file_mode__creat(f2ptr cause);
f2ptr f2__stream__file_mode__rdwr(f2ptr cause);
f2ptr f2__stream__new_open_file__rdonly(f2ptr cause, f2ptr filename);
f2ptr f2__stream__new_open_file__rdwr(f2ptr cause, f2ptr filename);

f2ptr  f2__stream__ungetc(f2ptr cause, f2ptr this, f2ptr character);
void  raw__stream__ungetc(f2ptr cause, f2ptr this, char ch);
f2ptr  f2__stream__try_read_character(f2ptr cause, f2ptr this);
f2ptr  f2__stream__getc(f2ptr cause, f2ptr stream);
f2ptr  f2__stream__rewind(f2ptr cause, f2ptr this);
f2ptr raw__stream__rewind_to_length(f2ptr cause, f2ptr this, s64 length);
f2ptr  f2__stream__rewind_to_length(f2ptr cause, f2ptr this, f2ptr length);

f2ptr f2stream__primobject_type__new(f2ptr cause);

// **

void f2__primobject__stream__reinitialize_globalvars();
void f2__primobject__stream__initialize();

#endif // F2__PRIMOBJECT__STREAM__H
