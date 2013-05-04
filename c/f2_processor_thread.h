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

#ifndef F2__PROCESSOR_THREAD__TYPES__H
#define F2__PROCESSOR_THREAD__TYPES__H

#include "f2_archconfig.h"

//#define DEBUG_PROCESSOR_THREAD

typedef void* (*funk2_processor_thread_function_pointer_t)(void*);

typedef u64 f2tid_t;

typedef struct funk2_processor_thread_s      funk2_processor_thread_t;
typedef struct funk2_processor_thread_list_s funk2_processor_thread_list_t;

#endif // F2__PROCESSOR_THREAD__TYPES__H


#ifndef F2__PROCESSOR_THREAD__H
#define F2__PROCESSOR_THREAD__H

#include <pthread.h>
#include "f2_processor_thread_event.h"
#include "f2_thread_safe_hash.h"

struct funk2_processor_thread_s {
  pthread_mutex_t                           tid_initialized_cond_mutex;
  pthread_cond_t                            tid_initialized_cond;
  boolean_t                                 tid_initialized;
  f2tid_t                                   tid;
  pthread_mutex_t                           added_to_handler_cond_mutex;
  pthread_cond_t                            added_to_handler_cond;
  boolean_t                                 added_to_handler;
  funk2_processor_thread_function_pointer_t start_function;
  void*                                     args;
  pthread_t                                 pthread;
  u64                                       execution_nanoseconds;
  u64                                       sleep_nanoseconds;
  void*                                     result;
  funk2_thread_safe_hash_t                  event_hash;
  u64                                       last_checked_in_nanoseconds_since_1970;
};

struct funk2_processor_thread_list_s {
  funk2_processor_thread_t              processor_thread;
  struct funk2_processor_thread_list_s* next;
};

void __funk2__nanosleep(u64 nanoseconds); // do not use from within a processor thread.

void                            funk2_processor_thread__init         (funk2_processor_thread_t* this, funk2_processor_thread_function_pointer_t start_function, void* args);
void                            funk2_processor_thread__destroy      (funk2_processor_thread_t* this);
funk2_processor_thread_event_t* funk2_processor_thread__create_event (funk2_processor_thread_t* this, char* message);
void                            funk2_processor_thread__destroy_event(funk2_processor_thread_t* this, funk2_processor_thread_event_t* event);
void                            funk2_processor_thread__start        (funk2_processor_thread_t* this);
void*                           funk2_processor_thread__join         (funk2_processor_thread_t* this, funk2_processor_thread_t* thread_to_join);
void                            funk2_processor_thread__nanosleep    (funk2_processor_thread_t* this, u64 nanoseconds);
void                            funk2_processor_thread__print_status (funk2_processor_thread_t* this);
void                            funk2_processor_thread__check_in     (funk2_processor_thread_t* this);

#endif // F2__PROCESSOR_THREAD__H

