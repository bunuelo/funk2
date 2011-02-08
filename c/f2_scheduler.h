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

#ifndef F2__SCHEDULER__TYPES__H
#define F2__SCHEDULER__TYPES__H

#define global_scheduler() __global__scheduler

#include "f2_primobjects.h"


// funk2_operating_system

typedef struct funk2_operating_system_current_fiber_cons_s funk2_operating_system_current_fiber_cons_t;
struct funk2_operating_system_current_fiber_cons_s {
  f2ptr                                               current_fiber;
  struct funk2_operating_system_current_fiber_cons_s* next;
};

typedef struct funk2_operating_system_s {
  f2ptr                                        scheduler;
  f2ptr                                        scheduler__symbol;
  funk2_processor_mutex_t                      current_fiber_stack__mutex[memory_pool_num];
  funk2_operating_system_current_fiber_cons_t* current_fiber_stack[memory_pool_num];
} funk2_operating_system_t;


typedef struct funk2_object_type__scheduler__slot_s funk2_object_type__scheduler__slot_t;

// scheduler

declare_object_type_1_slot(scheduler, processors,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__SCHEDULER__TYPES__H



#ifndef F2__SCHEDULER__H
#define F2__SCHEDULER__H

// funk2_operating_system

void  funk2_operating_system__init(              funk2_operating_system_t* this);
void  funk2_operating_system__destroy(           funk2_operating_system_t* this);
void  funk2_operating_system__push_current_fiber(funk2_operating_system_t* this, u64 pool_index, f2ptr current_fiber);
f2ptr funk2_operating_system__pop_current_fiber( funk2_operating_system_t* this, u64 pool_index);


// scheduler

declare_primobject_1_slot(scheduler, processors);

f2ptr f2scheduler__primobject_type__new_aux(f2ptr cause);

f2ptr raw__scheduler__processor_thread_current_fiber(int pool_index);


// global_scheduler

f2ptr  f2__global_scheduler__processors        ();
f2ptr  f2__global_scheduler__processors__set   (f2ptr cause, f2ptr value);
f2ptr  f2__global_scheduler__fibers            ();
f2ptr  f2__global_scheduler__fibers__set       (f2ptr cause, f2ptr value);
f2ptr  f2__global_scheduler__fiber_num         ();
f2ptr  f2__global_scheduler__fiber_num__set    (f2ptr cause, f2ptr value);
void  raw__global_scheduler__add_fiber_serial  (f2ptr cause, f2ptr fiber);
void  raw__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber);
void  raw__global_scheduler__complete_fiber    (f2ptr cause, f2ptr fiber);
f2ptr  f2__global_scheduler__complete_fiber    (f2ptr cause, f2ptr fiber);


// user functions

f2ptr raw__add_fiber          (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr  f2__this__fiber        (f2ptr cause); // returns current fiber.
void   f2__this__fiber__yield (f2ptr cause);
void   f2__print_fibers_stacks();


// **

void f2__scheduler__initialize();
void f2__scheduler__destroy();

#endif // F2__SCHEDULER__H

