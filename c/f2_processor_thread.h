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

#ifndef F2__PROCESSOR_THREAD__H
#define F2__PROCESSOR_THREAD__H

#include <pthread.h>

typedef void* (*funk2_processor_thread_function_pointer_t)(void*);

typedef struct funk2_processor_thread_s {
  u64                                       index;
  funk2_processor_thread_function_pointer_t start_function;
  void*                                     args;
  pthread_t                                 pthread;
} funk2_processor_thread_t;

typedef struct funk2_processor_thread_list_s {
  funk2_processor_thread_t              processor_thread;
  struct funk2_processor_thread_list_s* next;
} funk2_processor_thread_list_t;

void funk2_processor_thread__init(funk2_processor_thread_t* this, u64 index, funk2_processor_thread_function_pointer_t start_function, void* args);
void funk2_processor_thread__destroy(funk2_processor_thread_t* this);


#endif // F2__PROCESSOR_THREAD__H

