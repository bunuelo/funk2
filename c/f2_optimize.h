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

#ifndef F2__OPTIMIZE__TYPES__H
#define F2__OPTIMIZE__TYPES__H

// optimize_context

typedef struct funk2_object_type__optimize_context__slot_s funk2_object_type__optimize_context__slot_t;
declare_object_type_2_slot(optimize_context, node_fiber_register_hash, graph,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__OPTIMIZE__TYPES__H


#ifndef F2__OPTIMIZE__H
#define F2__OPTIMIZE__H

// optimize_context

declare_primobject_2_slot(optimize_context, node_fiber_register_hash, graph);


f2ptr raw__funk__optimize(f2ptr cause, f2ptr this);
f2ptr  f2__funk__optimize(f2ptr cause, f2ptr this);


// **

void f2__optimize__reinitialize_globalvars();
void f2__optimize__initialize();


#endif // F2__OPTIMIZE__H
