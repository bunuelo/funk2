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

// funk2_virtual_processor_thread

void* funk2_virtual_processor_thread__start_function(void* args) {
  funk2_virtual_processor_thread_t* this = (funk2_virtual_processor_thread_t*)args;
  while (1) {
    u64       virtual_processor_assignment_index = -1;
    boolean_t not_assigned_to_virtual_processor  = boolean__true;
    while(not_assigned_to_virtual_processor) {
      funk2_processor_mutex__lock(&(this->assignment_mutex));
      virtual_processor_assignment_index = this->virtual_processor_assignment_index;
      funk2_processor_mutex__unlock(&(this->assignment_mutex));
      not_assigned_to_virtual_processor = (virtual_processor_assignment_index == -1);
      if (not_assigned_to_virtual_processor) {
	raw__spin_sleep_yield();
      }
    }
    funk2_virtual_processor_t* virtual_processor = __funk2.virtual_processor_handler.virtual_processor[virtual_processor_assignment_index];
    boolean_t                  did_something     = boolean__true;
    while (did_something) {
      did_something = funk2_virtual_processor__execute_next_bytecodes(virtual_processor, this);
    }
    raw__spin_sleep_yield();
  }
  return NULL;
}

void funk2_virtual_processor_thread__init(funk2_virtual_processor_thread_t* this) {
  funk2_processor_mutex__init(&(this->assignment_mutex));
  this->virtual_processor_assignment_index = -1;
  this->processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), funk2_virtual_processor_thread__start_function, this);
  //funk2_processor_thread__init(&(this->processor_thread), -1, funk2_virtual_processor_thread__start_function, this);
}

void funk2_virtual_processor_thread__destroy(funk2_virtual_processor_thread_t* this) {
  funk2_processor_thread__destroy(this->processor_thread);
}

void funk2_virtual_processor_thread__assign_to_virtual_processor(funk2_virtual_processor_thread_t* this, u64 virtual_processor_assignment_index) {
  funk2_processor_mutex__lock(&(this->assignment_mutex));
  status("funk2_virtual_processor_thread__assign_to_virtual_processor: virtual_processor_thread assigned to virtual_processor " u64__fstr ".", virtual_processor_assignment_index);
  if (this->virtual_processor_assignment_index != -1) {
    error(nil, "funk2_virtual_processor_thread__assign_to_virtual_processor error: attempted to assign virtual_processor_thread when already assigned.");
  }
  this->virtual_processor_assignment_index = virtual_processor_assignment_index;
  funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor(&(__funk2.virtual_processor_handler), this, virtual_processor_assignment_index);
  funk2_processor_mutex__unlock(&(this->assignment_mutex));
}
