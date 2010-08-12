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

void funk2_virtual_processor_thread_handler__init(funk2_virtual_processor_thread_handler_t* this, u64 virtual_processor_thread_count) {
  status("initializing virtual_processor_thread_handler with " u64__fstr " virtual processor threads.", virtual_processor_thread_count);
  this->virtual_processor_thread_count = virtual_processor_thread_count;
  this->virtual_processor_thread       = (funk2_virtual_processor_thread_t**)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_t*) * virtual_processor_thread_count));
  {
    s64 index;
    for (index = 0; index < virtual_processor_thread_count; index ++) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = (funk2_virtual_processor_thread_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_t)));
      funk2_virtual_processor_thread__init(virtual_processor_thread);
      this->virtual_processor_thread[index] = virtual_processor_thread;
    }
  }
}


void funk2_virtual_processor_thread_handler__destroy(funk2_virtual_processor_thread_handler_t* this) {
  status("destroying virtual_processor_thread_handler.");
  {
    s64 index;
    for (index = 0; index < this->virtual_processor_thread_count; index ++) {
      funk2_virtual_processor_thread__destroy(this->virtual_processor_thread[index]);
    }
  }
  f2__free(to_ptr(this->virtual_processor_thread));
}


