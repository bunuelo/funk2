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

#ifndef F2__PRIMOBJECT__SET__TYPES__H
#define F2__PRIMOBJECT__SET__TYPES__H


// set

typedef struct funk2_object_type__set__slot_s funk2_object_type__set__slot_t;
declare_object_type_4_slot(set, write_cmutex, key_count, bin_num_power, bin_array,
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr copy_from__symbol;
			   f2ptr copy_from__funk;
			   f2ptr new_copy__symbol;
			   f2ptr new_copy__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr contains__symbol;
			   f2ptr contains__funk;
			   f2ptr elements__symbol;
			   f2ptr elements__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   f2ptr union__symbol;
			   f2ptr union__funk;
			   f2ptr intersection__symbol;
			   f2ptr intersection__funk;
			   f2ptr minus__symbol;
			   f2ptr minus__funk;
			   f2ptr plus__symbol;
			   f2ptr plus__funk;
			   f2ptr is_subset_of__symbol;
			   f2ptr is_subset_of__funk;
			   f2ptr an_arbitrary_element__symbol;
			   f2ptr an_arbitrary_element__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__SET__TYPES__H

#ifndef F2__PRIMOBJECT__SET__H
#define F2__PRIMOBJECT__SET__H

#include "f2_primobjects.h"

// set

declare_primobject_4_slot(set, write_cmutex, key_count, bin_num_power, bin_array);

f2ptr     raw__set__new                 (f2ptr cause, s64 bin_num_power);
f2ptr      f2__set__new                 (f2ptr cause, f2ptr elements);
f2ptr     raw__set__add__debug          (f2ptr cause, f2ptr this, f2ptr key, char* source_filename, int source_line_number, char* source_funktion_name);
f2ptr      f2__set__add__debug          (f2ptr cause, f2ptr this, f2ptr key, char* source_filename, int source_line_number, char* source_funktion_name);
boolean_t raw__set__remove              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__remove              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__set__copy_from           (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__set__copy_from           (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__set__new_copy            (f2ptr cause, f2ptr this);
f2ptr      f2__set__new_copy            (f2ptr cause, f2ptr this);
f2ptr     raw__set__lookup              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__lookup              (f2ptr cause, f2ptr this, f2ptr key);
f2ptr     raw__set__an_arbitrary_element(f2ptr cause, f2ptr this);
f2ptr      f2__set__an_arbitrary_element(f2ptr cause, f2ptr this);
boolean_t raw__set__contains            (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__contains            (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__slot_names          (f2ptr cause, f2ptr this);
f2ptr     raw__set__elements            (f2ptr cause, f2ptr this);
f2ptr      f2__set__elements            (f2ptr cause, f2ptr this);
boolean_t raw__set__is_empty            (f2ptr cause, f2ptr this);
f2ptr      f2__set__is_empty            (f2ptr cause, f2ptr this);
f2ptr     raw__set__union               (f2ptr cause, f2ptr rest);
f2ptr      f2__set__union               (f2ptr cause, f2ptr rest);
f2ptr     raw__set__intersection        (f2ptr cause, f2ptr rest);
f2ptr      f2__set__intersection        (f2ptr cause, f2ptr rest);
f2ptr     raw__set__minus               (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__set__minus               (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__set__plus                (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__set__plus                (f2ptr cause, f2ptr this, f2ptr that);
boolean_t raw__set__is_subset_of        (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__set__is_subset_of        (f2ptr cause, f2ptr this, f2ptr that);

f2ptr f2set__primobject_type__new_aux(f2ptr cause);

#define raw__set__add(cause, this, key)                     raw__set__add__debug(cause, this, key, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)
#define  f2__set__add(cause, this, key)                      f2__set__add__debug(cause, this, key, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)
#define raw__set__increase_size__thread_unsafe(cause, this) raw__set__increase_size__thread_unsafe__debug(cause, this, (char*)__FILE__, __LINE__, (char*)__FUNCTION__)

#define set__iteration(cause, this, element, code) {			\
    f2ptr set__iteration__cause = (cause);				\
    f2ptr set__iteration__this  = (this);				\
    f2ptr set__iteration__bin_array         = f2set__bin_array(set__iteration__this, set__iteration__cause); \
    s64   set__iteration__bin_array__length = raw__array__length(set__iteration__cause, set__iteration__bin_array); \
    s64   set__iteration__index;							\
    for (set__iteration__index = 0; set__iteration__index < set__iteration__bin_array__length; set__iteration__index ++) {		\
      f2ptr set__iteration__key_iter = raw__array__elt(set__iteration__cause, set__iteration__bin_array, set__iteration__index); \
      while (set__iteration__key_iter) {						\
	f2ptr element = f2cons__car(set__iteration__key_iter, set__iteration__cause);	\
	{								\
	  code;								\
	}								\
	set__iteration__key_iter = f2cons__cdr(set__iteration__key_iter, set__iteration__cause);	\
      }									\
    }									\
  }

// **

void f2__primobject_set__reinitialize_globalvars();
void f2__primobject_set__initialize();

#endif // F2__PRIMOBJECT__SET__H

