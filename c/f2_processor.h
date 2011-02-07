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

#ifndef F2__PROCESSOR__TYPES__H
#define F2__PROCESSOR__TYPES__H

#include "f2_global.h"
#include "f2_fiber.h"
#include "f2_time.h"
#include "f2_processor_mutex.h"

typedef struct funk2_object_type__processor__slot_s funk2_object_type__processor__slot_t;

// processor

declare_object_type_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc,
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

#endif // F2__PROCESSOR__TYPES__H



#ifndef F2__PROCESSOR__H
#define F2__PROCESSOR__H

// processor

declare_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);

f2ptr f2processor__primobject_type__new_aux(f2ptr cause);


// processor

f2ptr f2processor__execute_next_bytecodes(f2ptr processor, f2ptr cause);


// **

void f2__processor__initialize();
void f2__processor__destroy();

#endif // F2__PROCESSOR__H

