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

#ifndef F2__BUG__TYPE__H
#define F2__BUG__TYPE__H

#include "f2_primobjects.h"

typedef struct funk2_object_type__bug__slot_s funk2_object_type__bug__slot_t;
declare_object_type_2_slot(bug, bug_type, frame,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECTS__TYPE__H



#ifndef F2__BUG__H
#define F2__BUG__H

// bug

declare_primobject_2_slot(bug, bug_type, frame);

f2ptr f2__bug__new(f2ptr cause, f2ptr bug_type, f2ptr frame);
f2ptr f2__bug__new_from_larva(f2ptr cause, f2ptr larva);

f2ptr f2bug__primobject_type__new_aux(f2ptr cause);

// **

void f2__bug__initialize();

#endif // F2__BUG__H


