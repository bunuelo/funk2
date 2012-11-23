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

#ifndef F2__EXTENSION__EQUALS_HASH__H
#define F2__EXTENSION__EQUALS_HASH__H

f2ptr     raw__equals_hash__new                      (f2ptr cause, f2ptr hash);
f2ptr      f2__equals_hash__new                      (f2ptr cause);
boolean_t raw__equals_hash__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__equals_hash__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__equals_hash__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__hash                     (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__hash                     (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__hash__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__equals_hash__hash__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__equals_hash__key_count                (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__key_count                (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__add                      (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
f2ptr      f2__equals_hash__add                      (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
f2ptr     raw__equals_hash__remove                   (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__equals_hash__remove                   (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__equals_hash__lookup                   (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__equals_hash__lookup                   (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__equals_hash__keys                     (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__keys                     (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__values                   (f2ptr cause, f2ptr this);
f2ptr      f2__equals_hash__values                   (f2ptr cause, f2ptr this);
f2ptr     raw__equals_hash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__equals_hash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__equals_hash_type__new(f2ptr cause);

#define equals_hash__iteration(cause, this, key, value, code) {		\
    hash__iteration(cause, raw__equals_hash__hash(cause, this), key, value, code); \
  }

// **

f2ptr f2__equals_hash__core_extension__ping      (f2ptr cause);
f2ptr f2__equals_hash__core_extension__initialize(f2ptr cause);
f2ptr f2__equals_hash__core_extension__destroy   (f2ptr cause);


#endif // F2__EXTENSION__EQUALS_HASH__H

