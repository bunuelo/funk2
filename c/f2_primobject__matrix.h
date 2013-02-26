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

#ifndef F2__PRIMOBJECT__MATRIX__TYPES__H
#define F2__PRIMOBJECT__MATRIX__TYPES__H

// matrix

typedef struct funk2_object_type__matrix__slot_s funk2_object_type__matrix__slot_t;
declare_object_type_4_slot(matrix,
			   mutate_cmutex,
			   zero_value,
			   column_row_ptypehash,
			   row_column_ptypehash,
			   f2ptr elt__symbol;
			   f2ptr elt__funk;
			   f2ptr elt__set__symbol;
			   f2ptr elt__set__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__MATRIX__TYPES__H


#ifndef F2__PRIMOBJECT__MATRIX__H
#define F2__PRIMOBJECT__MATRIX__H

#include "f2_primfunks.h"

declare_primobject_4_slot(matrix,
			  mutate_cmutex,
			  zero_value,
			  column_row_ptypehash,
			  row_column_ptypehash);

f2ptr raw__matrix__new(f2ptr cause);
f2ptr  f2__matrix__new(f2ptr cause);

f2ptr f2matrix__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject__matrix__reinitialize_globalvars();
void f2__primobject__matrix__initialize();


#endif // F2__PRIMOBJECT__MATRIX__H

