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

#include "f2_thread.h"
#include "f2_time.h"

typedef struct funk2_operating_system_s {
  pthread_mutex_t scheduler__execute_mutex;
  f2ptr           scheduler;
  f2ptr           scheduler__symbol;
  f2ptr           pthread__current_thread[memory_pool_num];
} funk2_operating_system_t;

//extern f2ptr f2scheduler__new(f2ptr context, f2ptr processors, f2ptr threads, f2ptr thread_num);
//extern f2ptr f2scheduler__processors(f2ptr this);
//extern f2ptr f2scheduler__processors__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__threads(f2ptr this);
//extern f2ptr f2scheduler__threads__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__thread_num(f2ptr this);
//extern f2ptr f2scheduler__thread_num__set(f2ptr this, f2ptr value);
//extern f2ptr f2scheduler__add_thread(f2ptr context, f2ptr this, f2ptr thread);

void funk2_operating_system__init(funk2_operating_system_t* this);
void funk2_operating_system__destroy(funk2_operating_system_t* this);

f2ptr f2__global_scheduler__processors();
f2ptr f2__global_scheduler__processors__set(f2ptr cause, f2ptr value);
f2ptr f2__global_scheduler__threads();
f2ptr f2__global_scheduler__threads__set(f2ptr cause, f2ptr value);
f2ptr f2__global_scheduler__thread_num();
f2ptr f2__global_scheduler__thread_num__set(f2ptr cause, f2ptr value);
void  f2__global_scheduler__add_thread_serial(f2ptr cause, f2ptr thread);
void  f2__global_scheduler__add_thread_parallel(f2ptr cause, f2ptr thread);

f2ptr f2__scheduler__pthread_current_thread(int pool_index);

f2ptr f2processor__execute_next_bytecodes(f2ptr processor, f2ptr cause);

//extern f2ptr f2processor__new(f2ptr context, f2ptr scheduler, f2ptr pthread, f2ptr desc);
//extern f2ptr f2processor__scheduler(f2ptr this);
//extern f2ptr f2processor__scheduler__set(f2ptr this, f2ptr value);
//extern f2ptr f2processor__pthread(f2ptr this);
//extern f2ptr f2processor__pthread__set(f2ptr this, f2ptr value);
//extern f2ptr f2processor__desc(f2ptr this);
//extern f2ptr f2processor__desc__set(f2ptr this, f2ptr value);

f2ptr f2__add_thread(f2ptr cause, f2ptr this, f2ptr thread);

void f2__global_scheduler__execute_mutex__lock(f2ptr cause);
void f2__global_scheduler__execute_mutex__unlock(f2ptr cause);

void f2__scheduler__yield(f2ptr cause);
void f2__scheduler__complete_thread(f2ptr cause, f2ptr thread);

void f2__print_threads_stacks();

void f2__scheduler__exec_with_main_pthread(f2ptr cause);

void f2__scheduler__start_processors();
void f2__scheduler__stop_processors();

void f2__scheduler__initialize();
void f2__scheduler__destroy();

#endif // F2__SCHEDULER__H

