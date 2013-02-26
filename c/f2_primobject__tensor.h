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

#ifndef F2__PRIMOBJECT__TENSOR__H
#define F2__PRIMOBJECT__TENSOR__H

#include "f2_primobjects.h"

// tensor

extern f2ptr __tensor__symbol;
boolean_t raw__tensor__is_type(f2ptr cause, f2ptr this);
f2ptr f2__tensor__is_type(f2ptr cause, f2ptr this);
f2ptr f2tensor__new(f2ptr cause, f2ptr dimensions, f2ptr data);
#define f2primobject__is_tensor(this, cause)                 raw__eq(cause, f2primobject__object_type(this, cause), __tensor__symbol)

defprimobject__static_slot__prototype(tensor__dimensions);
#define f2tensor__dimensions(            this, cause)        primobject__static_slot__accessor(  this, tensor__dimensions, cause)
#define f2tensor__dimensions__set(       this, cause, value) primobject__static_slot__set(       this, tensor__dimensions, cause, value)
#define f2tensor__dimensions__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, tensor__dimensions, cause)
#define f2tensor__dimensions__trace(     this, cause)        primobject__static_slot__trace(     this, tensor__dimensions, cause)
#define f2tensor__dimensions__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, tensor__dimensions, cause)

defprimobject__static_slot__prototype(tensor__data);
#define f2tensor__data(            this, cause)        primobject__static_slot__accessor(  this, tensor__data, cause)
#define f2tensor__data__set(       this, cause, value) primobject__static_slot__set(       this, tensor__data, cause, value)
#define f2tensor__data__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, tensor__data, cause)
#define f2tensor__data__trace(     this, cause)        primobject__static_slot__trace(     this, tensor__data, cause)
#define f2tensor__data__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, tensor__data, cause)

f2ptr f2__tensor__new_from_array_of_integer_dimensions(f2ptr cause, f2ptr dimensions, f2ptr fill_element);
f2ptr f2tensor__elt_from_array_of_integer_indices(f2ptr this, f2ptr indices, f2ptr cause);

void f2__primobject_tensor__reinitialize_globalvars();
void f2__primobject_tensor__initialize();

#endif // F2__PRIMOBJECT__TENSOR__H

