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

#ifndef F2__PRIMOBJECT__PTYPEHASH__TYPES__H
#define F2__PRIMOBJECT__PTYPEHASH__TYPES__H

// ptypehash

typedef struct funk2_object_type__ptypehash__slot_s funk2_object_type__ptypehash__slot_t;
declare_object_type_4_slot(ptypehash, write_mutex, key_count, bin_num_power, bin_array,
			   f2ptr slot_names__symbol;
			   f2ptr slot_names__funk;
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   );

#endif // F2__PRIMOBJECT__PTYPEHASH__TYPES__H

#ifndef F2__PRIMOBJECT__PTYPEHASH__H
#define F2__PRIMOBJECT__PTYPEHASH__H

#include "f2_primobjects.h"

// ptypehash

declare_primobject_4_slot(ptypehash, write_mutex, key_count, bin_num_power, bin_array);

f2ptr     raw__ptypehash__new                       (f2ptr cause, s64 bin_num_power);
f2ptr      f2__ptypehash__new                       (f2ptr cause);
f2ptr     raw__ptypehash__add                       (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
f2ptr      f2__ptypehash__add                       (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
boolean_t raw__ptypehash__remove                    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__ptypehash__remove                    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__ptypehash__lookup_keyvalue_pair      (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__ptypehash__lookup_keyvalue_pair      (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__ptypehash__lookup                    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__ptypehash__lookup                    (f2ptr cause, f2ptr this, f2ptr key);
boolean_t raw__ptypehash__contains                  (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__ptypehash__an_arbitrary_keyvalue_pair(f2ptr cause, f2ptr this);
f2ptr      f2__ptypehash__an_arbitrary_key          (f2ptr cause, f2ptr this);
f2ptr      f2__ptypehash__an_arbitrary_value        (f2ptr cause, f2ptr this);
f2ptr      f2__ptypehash__copy                      (f2ptr cause, f2ptr this);
boolean_t raw__ptypehash__is_empty                  (f2ptr cause, f2ptr this);
f2ptr      f2__ptypehash__is_empty                  (f2ptr cause, f2ptr this);

f2ptr raw__ptypehash__mapc_slot_names(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data);

f2ptr f2__ptypehash__slot_names(f2ptr cause, f2ptr this);

f2ptr f2ptypehash__primobject_type__new(f2ptr cause);
f2ptr f2ptypehash__primobject_type__new_aux(f2ptr cause);

#define ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, code) { \
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  f2ptr iteration__bin_array          = f2ptypehash__bin_array(iteration__this, iteration__cause); \
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

#define ptypehash__iteration(cause, this, key, value, code) {\
  ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr key   = f2cons__car(keyvalue_pair, iteration__cause); \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code); \
}

#define ptypehash__key__iteration(cause, this, key, code) {\
  ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr key = f2cons__car(keyvalue_pair, iteration__cause); \
                                      code); \
}

#define ptypehash__value__iteration(cause, this, value, code) {\
  ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code); \
}

// **

void f2__primobject_ptypehash__reinitialize_globalvars();
void f2__primobject_ptypehash__initialize();

#endif // F2__PRIMOBJECT__PTYPEHASH__H

