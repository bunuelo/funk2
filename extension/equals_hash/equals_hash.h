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

#ifndef F2__EXTENSION__EQUALS_HASH__H
#define F2__EXTENSION__EQUALS_HASH__H

f2ptr     raw__equals_hash__new       (f2ptr cause, f2ptr width);
f2ptr      f2__equals_hash__new       (f2ptr cause, f2ptr width);
boolean_t raw__equals_hash__is_type   (f2ptr cause, f2ptr thing);
f2ptr      f2__equals_hash__is_type   (f2ptr cause, f2ptr thing);
f2ptr     raw__equals_hash__type      (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__type      (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__width     (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__width     (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__width__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__equals_hash__width__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__equals_hash_type__new(f2ptr cause);

// **

f2ptr f2__equals_hash__core_extension_ping      (f2ptr cause);
f2ptr f2__equals_hash__core_extension_initialize(f2ptr cause);
f2ptr f2__equals_hash__core_extension_destroy   (f2ptr cause);

#endif // F2__EXTENSION__EQUALS_HASH__H

