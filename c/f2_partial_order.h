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

#ifndef F2__PARTIAL_ORDER__TYPES__H
#define F2__PARTIAL_ORDER__TYPES__H

// partial_order_node
typedef struct funk2_object_type__partial_order_node__slot_s funk2_object_type__partial_order_node__slot_t;
declare_object_type_1_slot(partial_order_node, label,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PARTIAL_ORDER__TYPES__H


#ifndef F2__PARTIAL_ORDER__H
#define F2__PARTIAL_ORDER__H

#include "f2_primobjects.h"

// partial_order_node
declare_primobject_1_slot(partial_order_node, label);

f2ptr f2__partial_order_node__new(f2ptr cause, f2ptr label);

f2ptr f2partial_order_node__primobject_type__new_aux(f2ptr cause);


// **

void f2__partial_order__initialize();

#endif // F2__PARTIAL_ORDER__H

