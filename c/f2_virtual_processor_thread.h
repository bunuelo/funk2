// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__VIRTUAL_PROCESSOR_THREAD__TYPES__H
#define F2__VIRTUAL_PROCESSOR_THREAD__TYPES__H

typedef struct funk2_virtual_processor_thread_cons_s funk2_virtual_processor_thread_cons_t;
typedef struct funk2_virtual_processor_thread_s      funk2_virtual_processor_thread_t;

#endif // F2__VIRTUAL_PROCESSOR_THREAD__TYPES__H

#ifndef F2__VIRTUAL_PROCESSOR_THREAD__H
#define F2__VIRTUAL_PROCESSOR_THREAD__H

struct funk2_virtual_processor_thread_cons_s {
  funk2_virtual_processor_thread_t*             virtual_processor_thread;
  struct funk2_virtual_processor_thread_cons_s* next;
};

struct funk2_virtual_processor_thread_s {
  pid_t                     tid; // as returned by gettid()
  funk2_processor_mutex_t   assignment_mutex;
  u64                       virtual_processor_assignment_index;
  u64                       processor_affinity_index;
  funk2_processor_thread_t* processor_thread;
  boolean_t                 exit;
  boolean_t                 exited;
  u64                       virtual_processor_stack_index;
  boolean_t                 paused;
  pthread_mutex_t           pause_cond_mutex;
  pthread_cond_t            pause_cond;
};

void* funk2_virtual_processor_thread__start_function                 (void* args);
void  funk2_virtual_processor_thread__init                           (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__destroy                        (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__signal_exit                    (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__finalize_exit                  (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__exit                           (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__pause_myself                   (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__unpause                        (funk2_virtual_processor_thread_t* this);
void  funk2_virtual_processor_thread__assign_to_virtual_processor    (funk2_virtual_processor_thread_t* this, u64 virtual_processor_assignment_index);
void  funk2_virtual_processor_thread__unassign_from_virtual_processor(funk2_virtual_processor_thread_t* this);

#endif // F2__VIRTUAL_PROCESSOR_THREAD__H

