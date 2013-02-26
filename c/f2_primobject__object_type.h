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

#ifndef F2__PRIMOBJECT__OBJECT_TYPE__H
#define F2__PRIMOBJECT__OBJECT_TYPE__H

#include "f2_primobjects.h"

// object_type

extern f2ptr __object_type__symbol;
boolean_t raw__object_type__is_type(f2ptr cause, f2ptr this);
f2ptr f2__object_type__is_type(f2ptr cause, f2ptr this);
f2ptr f2object_type__new(f2ptr cause, f2ptr types, f2ptr frame);
#define f2primobject__is_object_type(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __object_type__symbol)

defprimobject__static_slot__prototype(object_type__types);
#define f2object_type__types(            this, cause)        primobject__static_slot__accessor(  this, object_type__types, cause)
#define f2object_type__types__set(       this, cause, value) primobject__static_slot__set(       this, object_type__types, cause, value)
#define f2object_type__types__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, object_type__types, cause)
#define f2object_type__types__trace(     this, cause)        primobject__static_slot__trace(     this, object_type__types, cause)
#define f2object_type__types__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, object_type__types, cause)

defprimobject__static_slot__prototype(object_type__frame);
#define f2object_type__frame(            this, cause)        primobject__static_slot__accessor(  this, object_type__frame, cause)
#define f2object_type__frame__set(       this, cause, value) primobject__static_slot__set(       this, object_type__frame, cause, value)
#define f2object_type__frame__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, object_type__frame, cause)
#define f2object_type__frame__trace(     this, cause)        primobject__static_slot__trace(     this, object_type__frame, cause)
#define f2object_type__frame__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, object_type__frame, cause)

f2ptr object_type__new(f2ptr cause);
f2ptr object_type__lookup_local_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr object_type__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
void  object_type__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr object_type__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr object_type__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);

void f2__primobject_object_type__reinitialize_globalvars();
void f2__primobject_object_type__initialize();

#endif // F2__PRIMOBJECT__OBJECT_TYPE__H

