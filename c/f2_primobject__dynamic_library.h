// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__PRIMOBJECT__DYNAMIC_LIBRARY__H
#define F2__PRIMOBJECT__DYNAMIC_LIBRARY__H

#include "f2_primobjects.h"

// dynamic_library

extern f2ptr __dynamic_library__symbol;
f2ptr f2dynamic_library__new__trace_depth(f2ptr cause, f2ptr type, f2ptr directory, f2ptr name, int trace_depth);
f2ptr f2dynamic_library__new(f2ptr cause, f2ptr type, f2ptr directory, f2ptr name);
#define f2primobject__is__dynamic_library(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __dynamic_library__symbol)

defprimobject__static_slot__prototype(dynamic_library__type);
#define f2dynamic_library__type(                   this, cause)                     primobject__static_slot__accessor(         this, dynamic_library__type, cause)
#define f2dynamic_library__type__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, dynamic_library__type, cause, value, trace_depth)
#define f2dynamic_library__type__set(              this, cause, value)              primobject__static_slot__set(              this, dynamic_library__type, cause, value)
#define f2dynamic_library__type__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, dynamic_library__type, cause)
#define f2dynamic_library__type__trace(            this, cause)                     primobject__static_slot__trace(            this, dynamic_library__type, cause)
#define f2dynamic_library__type__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, dynamic_library__type, cause)

defprimobject__static_slot__prototype(dynamic_library__directory);
#define f2dynamic_library__directory(                   this, cause)                     primobject__static_slot__accessor(         this, dynamic_library__directory, cause)
#define f2dynamic_library__directory__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, dynamic_library__directory, cause, value, trace_depth)
#define f2dynamic_library__directory__set(              this, cause, value)              primobject__static_slot__set(              this, dynamic_library__directory, cause, value)
#define f2dynamic_library__directory__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, dynamic_library__directory, cause)
#define f2dynamic_library__directory__trace(            this, cause)                     primobject__static_slot__trace(            this, dynamic_library__directory, cause)
#define f2dynamic_library__directory__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, dynamic_library__directory, cause)

defprimobject__static_slot__prototype(dynamic_library__name);
#define f2dynamic_library__name(                   this, cause)                     primobject__static_slot__accessor(         this, dynamic_library__name, cause)
#define f2dynamic_library__name__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, dynamic_library__name, cause, value, trace_depth)
#define f2dynamic_library__name__set(              this, cause, value)              primobject__static_slot__set(              this, dynamic_library__name, cause, value)
#define f2dynamic_library__name__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, dynamic_library__name, cause)
#define f2dynamic_library__name__trace(            this, cause)                     primobject__static_slot__trace(            this, dynamic_library__name, cause)
#define f2dynamic_library__name__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, dynamic_library__name, cause)


// **

void f2__primobject__dynamic_library__reinitialize_globalvars();
void f2__primobject__dynamic_library__initialize();

#endif // F2__PRIMOBJECT__DYNAMIC_LIBRARY

