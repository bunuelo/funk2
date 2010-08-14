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

void* funk2_virtual_processor_thread__start_function(void* args) {
  funk2_virtual_processor_thread_t* this = (funk2_virtual_processor_thread_t*)args;
  while(1) {
    raw__spin_sleep_yield();
  }
  return NULL;
}

void funk2_virtual_processor_thread__init(funk2_virtual_processor_thread_t* this) {
  this->virtual_processor_assignment_index = -1;
  funk2_processor_thread__init(&(this->processor_thread), funk2_virtual_processor_thread__start_function, this);
}

void funk2_virtual_processor_thread__destroy(funk2_virtual_processor_thread_t* this) {
  funk2_processor_thread__destroy(&(this->processor_thread));
}

