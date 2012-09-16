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

#ifndef F2__VIRTUAL_PROCESSOR__TYPES__H
#define F2__VIRTUAL_PROCESSOR__TYPES__H

typedef struct funk2_processor_thread_array_s funk2_processor_thread_array_t;
typedef struct funk2_virtual_processor_s funk2_virtual_processor_t;

#endif // F2__VIRTUAL_PROCESSOR__TYPES__H

#ifndef F2__VIRTUAL_PROCESSOR__H
#define F2__VIRTUAL_PROCESSOR__H

#include "f2_virtual_processor_thread.h"

// processor_thread_array

struct funk2_processor_thread_array_s {
  u64                        alloc_length;
  u64                        length;
  funk2_processor_thread_t** array;
};

void funk2_processor_thread_array__init(   funk2_processor_thread_array_t* this);
void funk2_processor_thread_array__destroy(funk2_processor_thread_array_t* this);


// virtual_processor

struct funk2_virtual_processor_s {
  u64                                          index;
  funk2_processor_mutex_t                      execute_bytecodes_mutex;
  funk2_virtual_processor_thread_t*            execute_bytecodes_current_virtual_processor_thread;
  funk2_processor_mutex_t                      virtual_processor_thread_count_mutex;
  s64                                          assigned_virtual_processor_thread_count;
  s64                                          spinning_virtual_processor_thread_count;
  funk2_processor_mutex_t                      virtual_processor_thread_stack_mutex;
  funk2_virtual_processor_thread_cons_t*       virtual_processor_thread_stack;
  funk2_processor_mutex_t                      spinning_virtual_processor_thread_stack_mutex;
  funk2_virtual_processor_thread_doublelink_t* spinning_virtual_processor_thread_stack;
  funk2_virtual_processor_thread_doublelink_t* spinning_virtual_processor_thread_stack_end;
  funk2_processor_mutex_t                      yielding_virtual_processor_thread_circle_mutex;
  funk2_virtual_processor_thread_doublelink_t* yielding_virtual_processor_thread_circle;
};

void                              funk2_virtual_processor__init                                                 (funk2_virtual_processor_t* this, u64 index);
void                              funk2_virtual_processor__destroy                                              (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__assure_at_least_one_spinning_virtual_processor_thread(funk2_virtual_processor_t* this);
boolean_t                         funk2_virtual_processor__already_executing_next_bytecodes                     (funk2_virtual_processor_t* this);
boolean_t                         funk2_virtual_processor__execute_next_bytecodes                               (funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread);
void                              funk2_virtual_processor__know_of_one_less_assigned_virtual_processor_thread   (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__know_of_one_more_assigned_virtual_processor_thread   (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread   (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__know_of_one_more_spinning_virtual_processor_thread   (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__yield                                                (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__push_spinning_virtual_processor_thread               (funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread);
funk2_virtual_processor_thread_t* funk2_virtual_processor__peek_spinning_virtual_processor_thread               (funk2_virtual_processor_t* this);
funk2_virtual_processor_thread_t* funk2_virtual_processor__pop_spinning_virtual_processor_thread                (funk2_virtual_processor_t* this);
funk2_virtual_processor_thread_t* funk2_virtual_processor__end_peek_spinning_virtual_processor_thread           (funk2_virtual_processor_t* this);
funk2_virtual_processor_thread_t* funk2_virtual_processor__end_pop_spinning_virtual_processor_thread            (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__add_yielding_virtual_processor_thread                (funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread);
funk2_virtual_processor_thread_t* funk2_virtual_processor__peek_yielding_virtual_processor_thread               (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__remove_yielding_virtual_processor_thread             (funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread);
void                              funk2_virtual_processor__cycle_yielding_virtual_processor_threads             (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__try_unpause_next_yielding_virtual_processor_thread   (funk2_virtual_processor_t* this);
void                              funk2_virtual_processor__unpause_next_yielding_virtual_processor_thread       (funk2_virtual_processor_t* this);

#endif // F2__VIRTUAL_PROCESSOR__H

