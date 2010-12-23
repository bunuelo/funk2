// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#ifndef F2__EXTENSION__LICK__H
#define F2__EXTENSION__LICK__H

#include "../../c/funk2.h"

f2ptr     raw__lick__new                  (f2ptr cause, f2ptr object);
f2ptr      f2__lick__new                  (f2ptr cause, f2ptr object);
boolean_t raw__lick__is_type              (f2ptr cause, f2ptr thing);
f2ptr      f2__lick__is_type              (f2ptr cause, f2ptr thing);
f2ptr     raw__lick__type                 (f2ptr cause, f2ptr this);
f2ptr      f2__lick__type                 (f2ptr cause, f2ptr this);
f2ptr     raw__lick__note_object_hash     (f2ptr cause, f2ptr this);
f2ptr      f2__lick__note_object_hash     (f2ptr cause, f2ptr this);
f2ptr     raw__lick__note_object_hash__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__lick__note_object_hash__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__lick__chunk_note_hash      (f2ptr cause, f2ptr this);
f2ptr      f2__lick__chunk_note_hash      (f2ptr cause, f2ptr this);
f2ptr     raw__lick__chunk_note_hash__set (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__lick__chunk_note_hash__set (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__lick__object__as__note     (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__lick__object__as__note     (f2ptr cause, f2ptr this, f2ptr object);



f2ptr f2__lick_type__new(f2ptr cause);

// **

f2ptr f2__lick__core_extension_ping(f2ptr cause);
f2ptr f2__lick__core_extension_initialize(f2ptr cause);
f2ptr f2__lick__core_extension_destroy(f2ptr cause);

#endif // F2__EXTENSION__LICK__H

