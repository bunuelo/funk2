// 
// Copyright (c) 2007-2012 Bo Morgan.
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

// stream

typedef struct funk2_object_type__stream__slot_s funk2_object_type__stream__slot_t;
declare_object_type_12_slot(stream, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number,
			    f2ptr try_read_byte__symbol;
			    f2ptr try_read_byte__funk;
			    f2ptr try_read_character__symbol;
			    f2ptr try_read_character__funk;
			    f2ptr rewind__symbol;
			    f2ptr rewind__funk;
			    f2ptr rewind_to_length__symbol;
			    f2ptr rewind_to_length__funk;
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

#endif // F2__PRIMOBJECT__STREAM__TYPES__H

#ifndef F2__PRIMOBJECT__STREAM__H
#define F2__PRIMOBJECT__STREAM__H

#include "f2_primobjects.h"

// stream

declare_primobject_12_slot(stream, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number);

boolean_t raw__file_stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__file_stream__is_type(f2ptr cause, f2ptr this);

boolean_t raw__socket_stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__socket_stream__is_type(f2ptr cause, f2ptr this);

boolean_t raw__string_stream__is_type(f2ptr cause, f2ptr this);
f2ptr f2__string_stream__is_type(f2ptr cause, f2ptr this);

f2ptr f2__string_stream(f2ptr cause, f2ptr string);

f2ptr raw__stream__new_open_file(f2ptr cause, char* filename, int mode);
f2ptr f2__stream__new_open_file(f2ptr cause, f2ptr filename, f2ptr mode);
f2ptr f2__file_stream__close(f2ptr cause, f2ptr this);
f2ptr f2__file_stream__new(f2ptr cause, f2ptr file_handle);
f2ptr f2__stream__close(f2ptr cause, f2ptr this);
f2ptr f2__stream__file_mode__rdonly(f2ptr cause);
f2ptr f2__stream__file_mode__creat(f2ptr cause);
f2ptr f2__stream__file_mode__rdwr(f2ptr cause);
f2ptr f2__stream__new_open_file__rdonly(f2ptr cause, f2ptr filename);
f2ptr f2__stream__new_open_file__rdwr(f2ptr cause, f2ptr filename);

f2ptr  f2__stream__ungetb(f2ptr cause, f2ptr this, f2ptr byte);
void  raw__stream__ungetb(f2ptr cause, f2ptr this, u8 byte__i);
f2ptr  f2__stream__try_read_byte(f2ptr cause, f2ptr this);
f2ptr  f2__stream__getb(f2ptr cause, f2ptr stream);

f2ptr  f2__stream__rewind(f2ptr cause, f2ptr this);

f2ptr raw__stream__rewind_to_length(f2ptr cause, f2ptr this, s64 length);
f2ptr  f2__stream__rewind_to_length(f2ptr cause, f2ptr this, f2ptr length);

f2ptr  f2__stream__ungetc(f2ptr cause, f2ptr this, f2ptr character);
void  raw__stream__ungetc(f2ptr cause, f2ptr this, funk2_character_t ch);
f2ptr  f2__stream__try_read_character(f2ptr cause, f2ptr this);
f2ptr  f2__stream__getc(f2ptr cause, f2ptr stream);

f2ptr f2stream__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject__stream__reinitialize_globalvars();
void f2__primobject__stream__defragment__fix_pointers();
void f2__primobject__stream__initialize();

#endif // F2__PRIMOBJECT__STREAM__H
