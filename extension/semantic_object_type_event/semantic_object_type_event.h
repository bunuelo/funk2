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

#ifndef F2__EXTENSION__SEMANTIC_OBJECT_TYPE_EVENT__H
#define F2__EXTENSION__SEMANTIC_OBJECT_TYPE_EVENT__H

#include "../semantic_know_of_existence_event/semantic_know_of_existence_event.h"


f2ptr     raw__semantic_object_type_event__type_create        (f2ptr cause, f2ptr this, f2ptr semantic_realm);
f2ptr     raw__semantic_object_type_event__new                (f2ptr cause, f2ptr semantic_realm);
f2ptr      f2__semantic_object_type_event__new                (f2ptr cause, f2ptr semantic_realm);
boolean_t raw__semantic_object_type_event__is_type            (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_object_type_event__is_type            (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_object_type_event__type               (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_object_type_event__type               (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_object_type_event__example__lookup_set(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_object_type_event__example__lookup_set(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_object_type_event__example__add       (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_object_type_event__example__add       (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_object_type_event__example__remove    (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_object_type_event__example__remove    (f2ptr cause, f2ptr this, f2ptr that);

// **

f2ptr f2__semantic_object_type_event__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_object_type_event__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_object_type_event__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_OBJECT_TYPE_EVENT__H

