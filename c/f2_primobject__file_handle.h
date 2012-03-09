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

#ifndef F2__PRIMOBJECT__FILE_HANDLE__TYPES__H
#define F2__PRIMOBJECT__FILE_HANDLE__TYPES__H

// file_handle

typedef struct funk2_object_type__file_handle__slot_s funk2_object_type__file_handle__slot_t;
declare_object_type_1_slot(file_handle,
			   file_descriptor,
			   f2ptr close__symbol;
			   f2ptr close__funk;
			   f2ptr nonblocking__set__symbol;
			   f2ptr nonblocking__set__funk;
			   f2ptr try_read_byte__symbol;
			   f2ptr try_read_byte__funk;
			   f2ptr write__symbol;
			   f2ptr write__funk;
			   f2ptr send__symbol;
			   f2ptr send__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__FILE_HANDLE__TYPES__H


#ifndef F2__PRIMOBJECT__FILE_HANDLE__H
#define F2__PRIMOBJECT__FILE_HANDLE__H

#include "f2_primfunks.h"

declare_primobject_1_slot(file_handle,
			  file_descriptor);

f2ptr   raw__file_handle__new             (f2ptr cause, s64 file_descriptor);
f2ptr    f2__file_handle__new             (f2ptr cause, f2ptr file_descriptor);
f2ptr   raw__file_handle__close           (f2ptr cause, f2ptr this);
f2ptr    f2__file_handle__close           (f2ptr cause, f2ptr this);
int     raw__file_handle__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value);
f2ptr    f2__file_handle__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr   raw__file_handle__try_read_byte   (f2ptr cause, f2ptr this);
f2ptr    f2__file_handle__try_read_byte   (f2ptr cause, f2ptr this);
ssize_t raw__file_handle__write           (f2ptr cause, f2ptr this, s64 data__length, u8* data);
f2ptr    f2__file_handle__write           (f2ptr cause, f2ptr this, f2ptr string);
ssize_t raw__file_handle__send            (f2ptr cause, f2ptr this, s64 data__length, u8* data);
f2ptr    f2__file_handle__send            (f2ptr cause, f2ptr this, f2ptr string);
int     raw__file_handle__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value);
f2ptr    f2__file_handle__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2file_handle__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject__file_handle__reinitialize_globalvars();
void f2__primobject__file_handle__initialize();
void f2__primobject__file_handle__defragment__fix_pointers();


#endif // F2__PRIMOBJECT__FILE_HANDLE__H

