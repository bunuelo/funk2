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

#ifndef F2__PRIMOBJECT__TIME__H
#define F2__PRIMOBJECT__TIME__H

#include "f2_primobjects.h"

// time

extern f2ptr __time__symbol;
f2ptr f2time__new(f2ptr cause, f2ptr microseconds_since_1970);
#define      f2primobject__is__time(this, cause) raw__eq(cause, f2primobject__type(this, cause), __time__symbol)

defprimobject__static_slot__prototype(time__microseconds_since_1970);
#define      f2time__microseconds_since_1970(                   this, cause)        primobject__static_slot__accessor(         this, time__microseconds_since_1970, cause)
#define      f2time__microseconds_since_1970__set(              this, cause, value) primobject__static_slot__set(              this, time__microseconds_since_1970, cause, value)
#define      f2time__microseconds_since_1970__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, time__microseconds_since_1970, cause)
#define      f2time__microseconds_since_1970__trace(            this, cause)        primobject__static_slot__trace(            this, time__microseconds_since_1970, cause)
#define      f2time__microseconds_since_1970__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, time__microseconds_since_1970, cause)

boolean_t raw__timep(f2ptr this, f2ptr cause);
f2ptr      f2__timep(f2ptr this, f2ptr cause);


// **

void f2__primobject__time__reinitialize_globalvars();
void f2__primobject__time__initialize();

#endif // F2__PRIMOBJECT__TIME__H

