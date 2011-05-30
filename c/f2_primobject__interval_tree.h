// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H
#define F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H

// interval_tree

typedef struct funk2_object_type__interval_tree__slot_s funk2_object_type__interval_tree__slot_t;
declare_object_type_4_slot(interval_tree, mutate_mutex, head, value_funk, value_comparison_funk,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H

#ifndef F2__PRIMOBJECT__INTERVAL_TREE__H
#define F2__PRIMOBJECT__INTERVAL_TREE__H

#include "f2_primobjects.h"

// interval_tree

declare_primobject_4_slot(interval_tree, mutate_mutex, head, value_funk, value_comparison_funk);

f2ptr     raw__interval_tree__new(f2ptr cause, f2ptr head, f2ptr value_funk, f2ptr value_comparison_funk);
f2ptr      f2__interval_tree__new(f2ptr cause, f2ptr value_funk, f2ptr value_comparison_funk);

f2ptr f2interval_tree__primobject_type__new_aux(f2ptr cause);


// **

void f2__primobject__interval_tree__reinitialize_globalvars();
void f2__primobject__interval_tree__initialize();

#endif // F2__PRIMOBJECT__INTERVAL_TREE__H


