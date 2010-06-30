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

#ifndef F2__PRIMOBJECT__SET__TYPES__H
#define F2__PRIMOBJECT__SET__TYPES__H


// set

typedef struct funk2_object_type__set__slot_s funk2_object_type__set__slot_t;
declare_object_type_4_slot(set, write_mutex, key_count, bin_num_power, bin_array,
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr elements__symbol;
			   f2ptr elements__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   f2ptr an_arbitrary_element__symbol;
			   f2ptr an_arbitrary_element__funk;
			   );

#endif // F2__PRIMOBJECT__SET__TYPES__H

#ifndef F2__PRIMOBJECT__SET__H
#define F2__PRIMOBJECT__SET__H

#include "f2_primobjects.h"

// set

declare_primobject_4_slot(set, write_mutex, key_count, bin_num_power, bin_array);

f2ptr     raw__set__new       (f2ptr cause, s64 bin_num_power);
f2ptr      f2__set__new       (f2ptr cause);
f2ptr      f2__set__add       (f2ptr cause, f2ptr this, f2ptr key);
boolean_t raw__set__remove    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__remove    (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__lookup    (f2ptr cause, f2ptr this, f2ptr key);
boolean_t raw__set__contains  (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__contains  (f2ptr cause, f2ptr this, f2ptr key);
f2ptr      f2__set__slot_names(f2ptr cause, f2ptr this);
f2ptr     raw__set__elements  (f2ptr cause, f2ptr this);
f2ptr      f2__set__elements  (f2ptr cause, f2ptr this);
boolean_t raw__set__is_empty  (f2ptr cause, f2ptr this);
f2ptr      f2__set__is_empty  (f2ptr cause, f2ptr this);

f2ptr f2set__primobject_type__new_aux(f2ptr cause);

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

