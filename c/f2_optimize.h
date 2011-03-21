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

// optimize_cause

typedef struct funk2_object_type__optimize_data__slot_s funk2_object_type__optimize_data__slot_t;
declare_object_type_3_slot(optimize_cause,
			   cause_type,
			   name,
			   args,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_data

typedef struct funk2_object_type__optimize_data__slot_s funk2_object_type__optimize_data__slot_t;
declare_object_type_3_slot(optimize_data,
			   data_type,
			   name,
			   optimize_cause,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_fiber

typedef struct funk2_object_type__optimize_fiber__slot_s funk2_object_type__optimize_fiber__slot_t;
declare_object_type_2_slot(optimize_fiber,
			   stack,
			   register_hash,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_context

typedef struct funk2_object_type__optimize_context__slot_s funk2_object_type__optimize_context__slot_t;
declare_object_type_1_slot(optimize_context,
			   initial_fiber,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__OPTIMIZE__TYPES__H


#ifndef F2__OPTIMIZE__H
#define F2__OPTIMIZE__H

#include "f2_frame_objects.h"

// optimize_cause

declare_primobject_3_slot(optimize_cause,
			  cause_type,
			  name,
			  args);

f2ptr f2optimize_cause__primobject_type__new_aux(f2ptr cause);


// optimize_data

declare_primobject_3_slot(optimize_data,
			  data_type,
			  name,
			  optimize_cause);

f2ptr f2optimize_data__primobject_type__new_aux(f2ptr cause);


// optimize_fiber

declare_primobject_2_slot(optimize_fiber,
			  stack,
			  register_hash);

f2ptr f2optimize_fiber__primobject_type__new_aux(f2ptr cause);


// optimize_context

declare_primobject_1_slot(optimize_context,
			  initial_fiber);

f2ptr f2optimize_context__primobject_type__new_aux(f2ptr cause);


f2ptr raw__funk__optimize(f2ptr cause, f2ptr this);
f2ptr  f2__funk__optimize(f2ptr cause, f2ptr this);


// **

void f2__optimize__reinitialize_globalvars();
void f2__optimize__initialize();


#endif // F2__OPTIMIZE__H
