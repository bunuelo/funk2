// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__EXTENSION__SEMANTIC_PACKABLE_OBJECT__H
#define F2__EXTENSION__SEMANTIC_PACKABLE_OBJECT__H

#include "../semantic_ordered_object/semantic_ordered_object.h"
#include "../semantic_containment_object/semantic_containment_object.h"

// semantic_packable_object

f2ptr     raw__semantic_packable_object__new    (f2ptr cause, f2ptr semantic_realm);
f2ptr      f2__semantic_packable_object__new    (f2ptr cause, f2ptr semantic_realm);
boolean_t raw__semantic_packable_object__is_type(f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_packable_object__is_type(f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_packable_object__type   (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_packable_object__type   (f2ptr cause, f2ptr this);

f2ptr f2__semantic_packable_object_type__new(f2ptr cause);

// **

f2ptr f2__semantic_packable_object__core_extension__ping(f2ptr cause);
f2ptr f2__semantic_packable_object__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_packable_object__core_extension__destroy(f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_PACKABLE_OBJECT__H

