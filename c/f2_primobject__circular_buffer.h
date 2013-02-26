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

#ifndef F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H
#define F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H

// circular_buffer

typedef struct funk2_object_type__circular_buffer__slot_s funk2_object_type__circular_buffer__slot_t;
declare_object_type_4_slot(circular_buffer, access_cmutex, start, end, bin_array,
			   f2ptr pop__symbol;
			   f2ptr pop__funk;
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   );

#endif // F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H

#ifndef F2__PRIMOBJECT__CIRCULAR_BUFFER__H
#define F2__PRIMOBJECT__CIRCULAR_BUFFER__H

#include "f2_primobjects.h"

// circular_buffer

declare_primobject_4_slot(circular_buffer, access_cmutex, start, end, bin_array);

f2ptr raw__circular_buffer__new_empty(f2ptr cause, u64 length);
f2ptr f2__circular_buffer__new(f2ptr cause);
f2ptr f2__circular_buffer__add(f2ptr cause, f2ptr this, f2ptr value);
f2ptr f2__circular_buffer__pop(f2ptr cause, f2ptr this);
boolean_t raw__circular_buffer__is_empty(f2ptr cause, f2ptr this);

f2ptr f2circular_buffer__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject_circular_buffer__reinitialize_globalvars();
void f2__primobject_circular_buffer__initialize();



#endif // F2__PRIMOBJECT__CIRCULAR_BUFFER__H
