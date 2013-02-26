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

#ifndef F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H
#define F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H

// doublelinklist

typedef struct funk2_object_type__doublelinklist__slot_s funk2_object_type__doublelinklist__slot_t;
declare_object_type_3_slot(doublelinklist, write_cmutex, length, cons_cells,
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr car__symbol;
			   f2ptr car__funk;
			   f2ptr cdr__symbol;
			   f2ptr cdr__funk;
			   );

#endif // F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H

#ifndef F2__PRIMOBJECT__DOUBLELINKLIST__H
#define F2__PRIMOBJECT__DOUBLELINKLIST__H

#include "f2_primobjects.h"

// doublelinklist

declare_primobject_3_slot(doublelinklist, write_cmutex, length, cons_cells);

f2ptr f2__doublelinklist__new   (f2ptr cause, f2ptr elements);
f2ptr f2__doublelinklist__add   (f2ptr cause, f2ptr this, f2ptr element);
f2ptr f2__doublelinklist__lookup(f2ptr cause, f2ptr this, f2ptr element);

f2ptr f2doublelinklist__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject_doublelinklist__reinitialize_globalvars();
void f2__primobject_doublelinklist__initialize();

#endif // F2__PRIMOBJECT__DOUBLELINKLIST__H

