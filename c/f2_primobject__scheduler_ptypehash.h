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

#ifndef F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__TYPES__H
#define F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__TYPES__H

// scheduler_ptypehash

typedef struct funk2_object_type__scheduler_ptypehash__slot_s funk2_object_type__scheduler_ptypehash__slot_t;
declare_object_type_4_slot(scheduler_ptypehash, creadwritelock, key_count, bin_num_power, bin_array,
			   f2ptr contains__symbol;
			   f2ptr contains__funk;
			   f2ptr an_arbitrary_keyvalue_pair__symbol;
			   f2ptr an_arbitrary_keyvalue_pair__funk;
			   f2ptr an_arbitrary_key__symbol;
			   f2ptr an_arbitrary_key__funk;
			   f2ptr an_arbitrary_value__symbol;
			   f2ptr an_arbitrary_value__funk;
			   f2ptr copy__symbol;
			   f2ptr copy__funk;
			   f2ptr keys__symbol;
			   f2ptr keys__funk;
			   f2ptr values__symbol;
			   f2ptr values__funk;
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr copy_from__symbol;
			   f2ptr copy_from__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   f2ptr as__frame__symbol;
			   f2ptr as__frame__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__TYPES__H

#ifndef F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__H
#define F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__H

#include "f2_primobjects.h"

// scheduler_ptypehash

declare_primobject_4_slot(scheduler_ptypehash, creadwritelock, key_count, bin_num_power, bin_array);

f2ptr     raw__scheduler_ptypehash__new                       (f2ptr cause, s64 bin_num_power);
f2ptr      f2__scheduler_ptypehash__new                       (f2ptr cause);
f2ptr     raw__scheduler_ptypehash__add__debug                (f2ptr cause, f2ptr this, f2ptr key, f2ptr value, char* source_filename, int source_line_number, char* source_funktion_name);
f2ptr      f2__scheduler_ptypehash__add__debug                (f2ptr cause, f2ptr this, f2ptr key, f2ptr value, char* source_filename, int source_line_number, char* source_funktion_name);
boolean_t raw__scheduler_ptypehash__remove                    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__scheduler_ptypehash__remove                    (f2ptr cause, f2ptr this, f2ptr key);
void      raw__scheduler_ptypehash__copy_from                 (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_ptypehash__copy_from                 (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__scheduler_ptypehash__lookup_keyvalue_pair      (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__scheduler_ptypehash__lookup_keyvalue_pair      (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__scheduler_ptypehash__lookup                    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__scheduler_ptypehash__lookup                    (f2ptr cause, f2ptr this, f2ptr key);
boolean_t raw__scheduler_ptypehash__contains                  (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__scheduler_ptypehash__an_arbitrary_keyvalue_pair(f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_ptypehash__an_arbitrary_key          (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_ptypehash__an_arbitrary_value        (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_ptypehash__copy                      (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_ptypehash__is_empty                  (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_ptypehash__is_empty                  (f2ptr cause, f2ptr this);
f2ptr     raw__scheduler_ptypehash__as__frame                 (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_ptypehash__as__frame                 (f2ptr cause, f2ptr this);

f2ptr raw__scheduler_ptypehash__mapc_keys(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data);

f2ptr f2__scheduler_ptypehash__keys(f2ptr cause, f2ptr this);
f2ptr f2__scheduler_ptypehash__values(f2ptr cause, f2ptr this);

f2ptr f2scheduler_ptypehash__primobject_type__new(f2ptr cause);
f2ptr f2scheduler_ptypehash__primobject_type__new_aux(f2ptr cause);

#define raw__scheduler_ptypehash__add(cause, this, key, value)              raw__scheduler_ptypehash__add__debug(cause, this, key, value, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)
#define  f2__scheduler_ptypehash__add(cause, this, key, value)               f2__scheduler_ptypehash__add__debug(cause, this, key, value, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)
#define raw__scheduler_ptypehash__increase_size__thread_unsafe(cause, this) raw__scheduler_ptypehash__increase_size__thread_unsafe__debug(cause, this, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)

#define scheduler_ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, code) { \
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  f2ptr iteration__bin_array          = f2scheduler_ptypehash__bin_array(iteration__this, iteration__cause); \
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

#define scheduler_ptypehash__iteration(cause, this, key, value, code) { \
  scheduler_ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr key   = f2cons__car(keyvalue_pair, iteration__cause); \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code); \
}

#define scheduler_ptypehash__key__iteration(cause, this, key, code) { \
  scheduler_ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr key = f2cons__car(keyvalue_pair, iteration__cause); \
                                      code); \
}

#define scheduler_ptypehash__value__iteration(cause, this, value, code) { \
  scheduler_ptypehash__keyvalue_pair__iteration(cause, this, keyvalue_pair, \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code); \
}

// **

void f2__primobject__scheduler_ptypehash__preinitialize_globalvars();
void f2__primobject__scheduler_ptypehash__reinitialize_globalvars();
void f2__primobject__scheduler_ptypehash__initialize();

#endif // F2__PRIMOBJECT__SCHEDULER_PTYPEHASH__H

