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

#ifndef F2__PROCESSOR_THREAD_HANDLER__H
#define F2__PROCESSOR_THREAD_HANDLER__H

#include "f2_processor_thread.h"

f2tid_t raw__gettid();

typedef struct funk2_processor_thread_handler_s {
  pthread_mutex_t                access_mutex;
  funk2_processor_thread_list_t* processor_thread_list;
} funk2_processor_thread_handler_t;

void                      funk2_processor_thread_handler__init                    (funk2_processor_thread_handler_t* this);
void                      funk2_processor_thread_handler__destroy                 (funk2_processor_thread_handler_t* this);
funk2_processor_thread_t* funk2_processor_thread_handler__add_new_processor_thread(funk2_processor_thread_handler_t* this, funk2_processor_thread_function_pointer_t start_function, void* args);
boolean_t                 funk2_processor_thread_handler__remove_processor_thread (funk2_processor_thread_handler_t* this, funk2_processor_thread_t* processor_thread);
funk2_processor_thread_t* funk2_processor_thread_handler__myself                  (funk2_processor_thread_handler_t* this);

s64 this_processor_thread__try_get_pool_index();
u64 this_processor_thread__pool_index();

// use these functions outside of the processor_thread_handler and friends:

f2tid_t raw__thread(funk2_processor_thread_function_pointer_t start_function, void* args);
void*   raw__join(f2tid_t tid);
void    raw__nanosleep(u64 nanoseconds);

#endif // F2__PROCESSOR_THREAD_HANDLER__H

