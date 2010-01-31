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

#ifndef F2__OBJECT__H
#define F2__OBJECT__H

#include "f2_primfunks.h"
#include "f2_ptypes.h"
#include "f2_primobjects.h"
#include "f2_primobject_type_handler.h"
#include "f2_array.h"
#include "f2_bug.h"

typedef struct funk2_object_types_s {
  funk2_ptype_object_types_t       ptype;
  funk2_primobject_object_types_t  primobject;
  funk2_object_type__array__slot_t array;
} funk2_object_types_t;

f2ptr f2__object__type(f2ptr cause, f2ptr this);
f2ptr f2__object__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);
f2ptr f2__object__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__object__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__object__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__object__equals_hash_value(f2ptr cause, f2ptr this);

f2ptr f2__object__property_scan(f2ptr cause, f2ptr fiber, f2ptr object, f2ptr property_funk);

// **

void f2__object__reinitialize_globalvars();
void f2__object__initialize();

#endif // F2__OBJECT__H

