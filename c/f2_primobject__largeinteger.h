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

#ifndef F2__PRIMOBJECT__LARGEINTEGER__TYPES__H
#define F2__PRIMOBJECT__LARGEINTEGER__TYPES__H

// largeinteger

typedef struct funk2_object_type__largeinteger__slot_s funk2_object_type__largeinteger__slot_t;
declare_object_type_3_slot(largeinteger, access_mutex, negative, integer_array, );

#endif // F2__PRIMOBJECT__LARGEINTEGER__TYPES__H

#ifndef F2__PRIMOBJECT__LARGEINTEGER__H
#define F2__PRIMOBJECT__LARGEINTEGER__H

#include "f2_primobjects.h"

// largeinteger

declare_primobject_3_slot(largeinteger, access_mutex, negative, integer_array);

f2ptr f2__largeinteger__new(f2ptr cause, f2ptr value);

// **

void f2__primobject_largeinteger__reinitialize_globalvars();
void f2__primobject_largeinteger__initialize();

#endif // F2__PRIMOBJECT__LARGEINTEGER__H

