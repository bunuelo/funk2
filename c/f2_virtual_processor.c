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

/*
// funk2_processor_thread_array

void funk2_processor_thread_array__init(funk2_processor_thread_array_t* this) {
  this->alloc_length = 1024;
  this->length       = 0;
  this->array        = (funk2_processor_thread_t**)from_ptr(f2__malloc(sizeof(funk2_processor_thread_t*) * this->alloc_length));
}

void funk2_processor_thread_array__destroy(funk2_processor_thread_array_t* this) {
  f2__free(to_ptr(this->array));
}

void funk2_processor_thread_array__double_size(funk2_processor_thread_array_t* this) {
  u64                        new_alloc_length = (this->alloc_length) << 1;
  funk2_processor_thread_t** old_array        = this->array;
  funk2_processor_thread_t** new_array        = (funk2_processor_thread_t**)from_ptr(f2__malloc(sizeof(funk2_processor_thread_t*) * new_alloc_length));
  {
    s64 index;
    for (index = 0; index < this->length; index ++) {
      new_array[index] = old_array[index];
    }
  }
  this->array        = new_array;
  this->alloc_length = new_alloc_length;
  f2__free(to_ptr(old_array));
}

void funk2_processor_thread_array__add(funk2_processor_thread_array_t* this, funk2_processor_thread_t* processor_thread) {
  if (this->length == this->alloc_length) {
    funk2_processor_thread_array__double_size(this);
  }
  this->array[this->length] = processor_thread;
  this->length ++;
}

void funk2_processor_thread_array__remove(funk2_processor_thread_array_t* this, s64 index) {
  if (index < 0 || index >= this->length) {
    error(nil, "funk2_processor_thread_array__remove error: index out of range.");
  }
  u64 move_count = ((this->length - index) - 1);
  if (move_count != 0) {
    memmove(this->array + index, this->array + index + 1, sizeof(*(this->array)) * move_count);
  }
  this->length --;
}
*/


// funk2_virtual_processor

void funk2_virtual_processor__init(funk2_virtual_processor_t* this, u64 index) {
  this->index = index;
  //funk2_processor_thread_array__init(&(this->processor_thread_array));
  funk2_processor_mutex__init(&(this->execute_bytecodes_mutex));
  funk2_processor_mutex__init(&(this->free_virtual_processor_thread_count_mutex));
  this->free_virtual_processor_thread_count = 0;
  // start running at least one thread.
  funk2_virtual_processor__assure_at_least_one_free_virtual_processor_thread(this);
}

void funk2_virtual_processor__destroy(funk2_virtual_processor_t* this) {
  funk2_processor_thread_array__destroy(&(this->processor_thread_array));
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
    funk2_virtual_processor_thread__assign_to_virtual_processor(this, index);
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
  f2ptr     cause         = nil;
  f2ptr     processors    = f2scheduler__processors(__funk2.operating_system.scheduler, cause);
  f2ptr     processor     = raw__array__elt(cause, processors, this->index);
  boolean_t did_something = f2processor__execute_next_bytecodes(this->processor, cause);
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
}

//void* processor__start_routine(void *ptr) {
//  status("processor here, waiting for bootstrap to complete before starting.");
//  while (__funk2.memory.bootstrapping_mode) {
//    raw__fast_spin_sleep_yield();
//  }
//  status("processor starting.");
//  f2ptr cause     = nil;
//  f2ptr processor = f2__global_scheduler__this_processor(cause);
//  int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
//  release__assert(pool_index == this_processor_thread__pool_index(), nil, "pool_index does not match pthread_self() generated pool index.");
//  
//  status("starting processor " u64__fstr " (" u64__fstr ")", (u64)this_processor_thread__pool_index(), (u64)processor);
//  while(1) {
//    f2ptr did_something = nil;
//    do {
//      did_something = f2processor__execute_next_bytecodes(processor, cause);
//      funk2_scheduler_thread_controller__check_user_wait_politely(&(__funk2.scheduler_thread_controller));
//      raw__fast_spin_sleep_yield();
//    } while (did_something);
//    //printf("\nprocessor %d sleeping", this_processor_thread__pool_index()); fflush(stdout);
//    //printf("\nprocessor__start_routine: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
//    raw__spin_sleep_yield();
//  }
//  return nil;
//}
//
//void f2__scheduler__yield(f2ptr cause) {
//  if (! __funk2.memory.bootstrapping_mode) {
//    f2ptr processor = f2__global_scheduler__this_processor(cause);
//    if(! f2processor__execute_next_bytecodes(processor, cause)) {
//      //f2ptr processor = f2__global_scheduler__this_processor();
//      //printf("\nscheduler__yield: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
//      //f2__sleep(1000); // maybe this should be the average time to execute f2scheduler__execute_next_bytecodes (when it returns True)?
//      raw__fast_spin_sleep_yield();
//      if (__funk2.user_thread_controller.please_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
//	funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
//      }
//    }
//  }
//}

