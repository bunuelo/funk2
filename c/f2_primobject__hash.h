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

#ifndef F2__PRIMOBJECT__HASH__TYPES__H
#define F2__PRIMOBJECT__HASH__TYPES__H

// hash

typedef struct funk2_object_type__hash__slot_s funk2_object_type__hash__slot_t;
declare_object_type_6_slot(hash, write_cmutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk,
			   f2ptr keys__symbol;
			   f2ptr keys__funk;
			   f2ptr values__symbol;
			   f2ptr values__funk;
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   f2ptr as__frame__symbol;
			   f2ptr as__frame__funk;
			   );

#endif // F2__PRIMOBJECT__HASH__TYPES__H

#ifndef F2__PRIMOBJECT__HASH__H
#define F2__PRIMOBJECT__HASH__H

#include "f2_primobjects.h"

// hash

declare_primobject_6_slot(hash, write_cmutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);

f2ptr      f2__hash                      (f2ptr cause);
f2ptr     raw__hash__new                 (f2ptr cause, s64 bin_num_power, f2ptr hash_value_funk, f2ptr equals_funk);
f2ptr      f2__hash__new                 (f2ptr cause, f2ptr hash_value_funk, f2ptr equals_funk);
f2ptr     raw__hash__add                 (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
f2ptr      f2__hash__add                 (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
boolean_t raw__hash__remove              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__hash__remove              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__hash__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key);
boolean_t raw__hash__contains            (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__hash__contains            (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__hash__lookup              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__hash__lookup              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__hash__keys                (f2ptr cause, f2ptr this);
f2ptr      f2__hash__keys                (f2ptr cause, f2ptr this);
f2ptr     raw__hash__values              (f2ptr cause, f2ptr this);
f2ptr      f2__hash__values              (f2ptr cause, f2ptr this);

f2ptr raw__hash__as__frame(f2ptr cause, f2ptr this);
f2ptr  f2__hash__as__frame(f2ptr cause, f2ptr this);

f2ptr f2hash__primobject_type__new(f2ptr cause);
f2ptr f2hash__primobject_type__new_aux(f2ptr cause);

#define hash__keyvalue_pair__iteration(cause, this, keyvalue_pair, code) {\
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  f2ptr iteration__bin_array          = f2hash__bin_array(iteration__this, iteration__cause); \
  s64   iteration__bin_array__length  = raw__array__length(iteration__cause, iteration__bin_array); \
  s64   iteration__index; \
  for (iteration__index = 0; iteration__index < iteration__bin_array__length; iteration__index ++) { \
    f2ptr iteration__keyvalue_pair_iter = raw__array__elt(iteration__cause, iteration__bin_array, iteration__index); \
    while (iteration__keyvalue_pair_iter) { \
      f2ptr keyvalue_pair = f2cons__car(iteration__keyvalue_pair_iter, iteration__cause); \
      code; \
      iteration__keyvalue_pair_iter = f2cons__cdr(iteration__keyvalue_pair_iter, iteration__cause); \
    } \
  } \
}

#define hash__iteration(cause, this, key, value, code) {\
  hash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                 f2ptr key   = f2cons__car(keyvalue_pair, iteration__cause); \
                                 f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                 code); \
}

#define hash__key__iteration(cause, this, key, code) {\
  hash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                 f2ptr key = f2cons__car(keyvalue_pair, iteration__cause); \
                                 code); \
}

#define hash__value__iteration(cause, this, value, code) {\
  hash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code); \
}

// **

void f2__primobject_hash__reinitialize_globalvars();
void f2__primobject_hash__initialize();

#endif // F2__PRIMOBJECT__HASH__H

