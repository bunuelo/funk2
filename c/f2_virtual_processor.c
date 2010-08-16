// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#include "funk2.h"

// funk2_virtual_processor

void funk2_virtual_processor__init(funk2_virtual_processor_t* this, u64 index) {
  this->index = index;
  funk2_processor_mutex__init(&(this->execute_bytecodes_mutex));
  funk2_processor_mutex__init(&(this->free_virtual_processor_thread_count_mutex));
  this->free_virtual_processor_thread_count = 0;
  // start running at least one thread.
  funk2_virtual_processor__assure_at_least_one_free_virtual_processor_thread(this);
}

void funk2_virtual_processor__destroy(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__destroy(&(this->execute_bytecodes_mutex));
  funk2_processor_mutex__destroy(&(this->free_virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__assure_at_least_one_free_virtual_processor_thread(funk2_virtual_processor_t* this) {
  s64 free_virtual_processor_thread_count;
  {
    funk2_processor_mutex__lock(&(this->free_virtual_processor_thread_count_mutex));
    free_virtual_processor_thread_count = this->free_virtual_processor_thread_count;
    funk2_processor_mutex__unlock(&(this->free_virtual_processor_thread_count_mutex));
  }
  while (free_virtual_processor_thread_count < 1) {
    funk2_virtual_processor_thread_t* virtual_processor_thread = funk2_virtual_processor_handler__get_free_virtual_processor_thread(&(__funk2.virtual_processor_handler));
    funk2_virtual_processor_thread__assign_to_virtual_processor(virtual_processor_thread, this->index);
    {
      funk2_processor_mutex__lock(&(this->free_virtual_processor_thread_count_mutex));
      this->free_virtual_processor_thread_count ++;
      free_virtual_processor_thread_count = this->free_virtual_processor_thread_count;
      funk2_processor_mutex__unlock(&(this->free_virtual_processor_thread_count_mutex));
    }
  }
}

boolean_t funk2_virtual_processor__execute_next_bytecodes(funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread) {
  funk2_processor_mutex__lock(&(this->execute_bytecodes_mutex));
  {
    funk2_processor_mutex__lock(&(this->free_virtual_processor_thread_count_mutex));
    this->free_virtual_processor_thread_count --;
    funk2_processor_mutex__unlock(&(this->free_virtual_processor_thread_count_mutex));
  }
  this->execute_bytecodes_current_virtual_processor_thread = virtual_processor_thread;
  f2ptr     cause      = nil;
  f2ptr     processors = f2scheduler__processors(__funk2.operating_system.scheduler, cause);
  f2ptr     processor  = raw__array__elt(cause, processors, this->index);
  { // assert processor has correct index.
    int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
    if (pool_index != this->index) {
      error(nil, "funk2_virtual_processor__execute_next_bytecodes error: processor pool_index does not match processor position in scheduler array.");
    }
  }
  boolean_t did_something = f2processor__execute_next_bytecodes(processor, cause);
  funk2_scheduler_thread_controller__check_user_wait_politely(&(__funk2.scheduler_thread_controller));
  this->execute_bytecodes_current_virtual_processor_thread = NULL;
  {
    funk2_processor_mutex__lock(&(this->free_virtual_processor_thread_count_mutex));
    this->free_virtual_processor_thread_count ++;
    funk2_processor_mutex__unlock(&(this->free_virtual_processor_thread_count_mutex));
  }
  funk2_processor_mutex__unlock(&(this->execute_bytecodes_mutex));
  return did_something;
}

void funk2_virtual_processor__yield(funk2_virtual_processor_t* this) {
  if (! (this->execute_bytecodes_current_virtual_processor_thread)) {
    error(nil, "funk2_virtual_processor__yield error: execute_bytecodes_current_virtual_processor_thread is NULL.");
  }
  funk2_virtual_processor_thread_t* yielding_virtual_processor_thread = this->execute_bytecodes_current_virtual_processor_thread;
  this->execute_bytecodes_current_virtual_processor_thread = NULL;
  funk2_processor_mutex__unlock(&(this->execute_bytecodes_mutex));
  funk2_virtual_processor__assure_at_least_one_free_virtual_processor_thread(this);
  // let free processor execute some bytecodes before returning from yield...
  raw__spin_sleep_yield();
  funk2_processor_mutex__lock(&(this->execute_bytecodes_mutex));
  this->execute_bytecodes_current_virtual_processor_thread = yielding_virtual_processor_thread;
}

