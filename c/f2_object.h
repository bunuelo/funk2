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

#ifndef F2__OBJECT__TYPES__H
#define F2__OBJECT__TYPES__H

#include "f2_global.h"
#include "f2_ptypes_object_slots.h"

typedef struct funk2_object_s {
  f2ptr object__eq_hash_value__funk;
  f2ptr object__eq__funk;
  f2ptr object__equals_hash_value__funk;
  f2ptr object__equals_hash_value__loop_free__funk;
  f2ptr object__equals__funk;
} funk2_object_t;

#endif // F2__OBJECT__TYPES__H


#ifndef F2__OBJECT__H
#define F2__OBJECT__H

#include "f2_primfunks.h"
#include "f2_ptypes.h"
#include "f2_primobjects.h"
#include "f2_primobject_type_handler.h"
#include "f2_array.h"
#include "f2_bug.h"

typedef struct funk2_object_types_s {
  funk2_object_type__nil__slot_t   nil_type;   // unique (value zero in machine register, similar to NULL in c)
  funk2_ptype_object_types_t       ptype;      // parents of everything except nil
  funk2_object_type__array__slot_t array;      // interface to simple_array and traced_array
  funk2_primobject_object_types_t  primobject; // built from combinations of array and other ptypes
} funk2_object_types_t;

#define inherits_from(cause, this, type_name) raw__object__inherits_from(cause, this, new__symbol(cause, #type_name))

f2ptr      f2__object__type(f2ptr cause, f2ptr this);
f2ptr      f2__object__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);
boolean_t raw__object__inherits_from(f2ptr cause, f2ptr this, f2ptr type_name);
f2ptr      f2__object__inherits_from(f2ptr cause, f2ptr this, f2ptr type_name);
f2ptr      f2__object__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__object__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__object__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__object__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr      f2__object__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr      f2__object__property_scan(f2ptr cause, f2ptr fiber, f2ptr object, f2ptr property_funk);

f2ptr f2__object__get    (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__set    (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__execute(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);

f2ptr f2__object__get_0(f2ptr cause, f2ptr this, f2ptr slot);
f2ptr     object__get_0(f2ptr cause, f2ptr this, char* slot_cstr);
f2ptr f2__object__get_1(f2ptr cause, f2ptr this, f2ptr slot,      f2ptr arg0);
f2ptr     object__get_1(f2ptr cause, f2ptr this, char* slot_cstr, f2ptr arg0);
f2ptr f2__object__set_1(f2ptr cause, f2ptr this, f2ptr slot,      f2ptr arg0);
f2ptr f2__object__get_2(f2ptr cause, f2ptr this, f2ptr slot,      f2ptr arg0, f2ptr arg1);
f2ptr     object__get_2(f2ptr cause, f2ptr this, char* slot_cstr, f2ptr arg0, f2ptr arg1);

// **

void f2__object__reinitialize_globalvars();
void f2__object__initialize();

#endif // F2__OBJECT__H

