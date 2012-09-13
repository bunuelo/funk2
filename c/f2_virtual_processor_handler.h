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

#ifndef F2__VIRTUAL_PROCESSOR_HANDLER__TYPES__H
#define F2__VIRTUAL_PROCESSOR_HANDLER__TYPES__H

typedef struct funk2_virtual_processor_handler_s funk2_virtual_processor_handler_t;

#endif // F2__VIRTUAL_PROCESSOR_HANDLER__TYPES__H

#ifndef F2__VIRTUAL_PROCESSOR_HANDLER__H
#define F2__VIRTUAL_PROCESSOR_HANDLER__H

#include "f2_global.h"
#include "f2_virtual_processor.h"
#include "f2_virtual_processor_thread.h"

struct funk2_virtual_processor_handler_s {
  funk2_processor_mutex_t                virtual_processor_index_processor_thread_hash_mutex;
  funk2_hash_t                           virtual_processor_index_processor_thread_hash;
  funk2_processor_mutex_t                all_virtual_processor_threads_mutex;
  funk2_virtual_processor_thread_cons_t* all_virtual_processor_threads;
  funk2_processor_mutex_t                free_virtual_processor_threads_mutex;
  funk2_virtual_processor_thread_cons_t* free_virtual_processor_threads;
  funk2_processor_mutex_t                virtual_processor_thread_processor_thread_hash_mutex;
  funk2_hash_t                           virtual_processor_thread_processor_thread_hash;
  funk2_processor_mutex_t                virtual_processor_index_pthread_hash_mutex;
  funk2_hash_t                           virtual_processor_index_pthread_hash;
  u64                                    virtual_processor_count;
  funk2_virtual_processor_t**            virtual_processor;
  boolean_t                              hardware_affinities_enabled;
};

void                              funk2_virtual_processor_handler__init                                                                (funk2_virtual_processor_handler_t* this, u64 virtual_processor_count);
void                              funk2_virtual_processor_handler__destroy                                                             (funk2_virtual_processor_handler_t* this);
void                              funk2_virtual_processor_handler__destroy_all_virtual_processor_threads                               (funk2_virtual_processor_handler_t* this);
void                              funk2_virtual_processor_handler__start_virtual_processors                                            (funk2_virtual_processor_handler_t* this);
funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__get_free_virtual_processor_thread                                   (funk2_virtual_processor_handler_t* this);
void                              funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor    (funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread, u64 virtual_processor_index);
void                              funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor(funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread);
funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__my_virtual_processor_thread                                         (funk2_virtual_processor_handler_t* this);
s64                               funk2_virtual_processor_handler__try_get_my_virtual_processor_index                                  (funk2_virtual_processor_handler_t* this);
u64                               funk2_virtual_processor_handler__my_virtual_processor_index                                          (funk2_virtual_processor_handler_t* this);
funk2_virtual_processor_t*        funk2_virtual_processor_handler__try_get_my_virtual_processor                                        (funk2_virtual_processor_handler_t* this);
funk2_virtual_processor_t*        funk2_virtual_processor_handler__my_virtual_processor                                                (funk2_virtual_processor_handler_t* this);
void                              funk2_virtual_processor_handler__yield                                                               (funk2_virtual_processor_handler_t* this);

// **

void f2__virtual_processor_handler__reinitialize_globalvars();
void f2__virtual_processor_handler__initialize();

#endif // F2__VIRTUAL_PROCESSOR_HANDLER__H

