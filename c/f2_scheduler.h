// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__SCHEDULER__H
#define F2__SCHEDULER__H

#define global_scheduler() __global__scheduler

#include "f2_fiber.h"
#include "f2_time.h"
#include "f2_processor_mutex.h"

typedef struct funk2_operating_system_s {
  //  funk2_processor_mutex_t scheduler__execute_mutex;
  f2ptr                   scheduler;
  f2ptr                   scheduler__symbol;
  f2ptr                   processor_thread__current_fiber[memory_pool_num];
} funk2_operating_system_t;

//extern f2ptr f2scheduler__new(f2ptr context, f2ptr processors, f2ptr fibers, f2ptr fiber_num);
//extern f2ptr f2scheduler__processors(f2ptr this);
//extern f2ptr f2scheduler__processors__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__fibers(f2ptr this);
//extern f2ptr f2scheduler__fibers__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__fiber_num(f2ptr this);
//extern f2ptr f2scheduler__fiber_num__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__add_fiber(f2ptr context, f2ptr this, f2ptr fiber);

void funk2_operating_system__init(funk2_operating_system_t* this);
void funk2_operating_system__destroy(funk2_operating_system_t* this);

f2ptr f2__global_scheduler__processors();
f2ptr f2__global_scheduler__processors__set(f2ptr cause, f2ptr value);
f2ptr f2__global_scheduler__fibers();
f2ptr f2__global_scheduler__fibers__set(f2ptr cause, f2ptr value);
f2ptr f2__global_scheduler__fiber_num();
f2ptr f2__global_scheduler__fiber_num__set(f2ptr cause, f2ptr value);
void  f2__global_scheduler__add_fiber_serial(f2ptr cause, f2ptr fiber);
void  f2__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber);

f2ptr f2__scheduler__processor_thread_current_fiber(int pool_index);
f2ptr f2__this__fiber(f2ptr cause); // returns current fiber.

f2ptr f2processor__execute_next_bytecodes(f2ptr processor, f2ptr cause);

f2ptr f2__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber);

void f2__scheduler__yield(f2ptr cause);
void f2__scheduler__complete_fiber(f2ptr cause, f2ptr fiber);

void f2__print_fibers_stacks();

void f2__scheduler__start_processors();
void f2__scheduler__stop_processors();

void f2__scheduler__initialize();
void f2__scheduler__destroy();

#endif // F2__SCHEDULER__H

