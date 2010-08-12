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

void funk2_virtual_processor_handler__init(funk2_virtual_processor_handler_t* this, u64 virtual_processor_count) {
  status("initializing virtual_processor_handler with " u64__fstr " virtual processor threads.", virtual_processor_count);
  this->virtual_processor_count = virtual_processor_count;
  this->virtual_processor       = (funk2_virtual_processor_t**)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t*) * virtual_processor_count));
  {
    s64 index;
    for (index = 0; index < virtual_processor_count; index ++) {
      funk2_virtual_processor_t* virtual_processor = (funk2_virtual_processor_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t)));
      funk2_virtual_processor__init(virtual_processor);
      this->virtual_processor[index] = virtual_processor;
    }
  }
  funk2_hash__init(&(this->index_processor_thread_hash), 10);
}


void funk2_virtual_processor_handler__destroy(funk2_virtual_processor_handler_t* this) {
  status("destroying virtual_processor_handler.");
  {
    s64 index;
    for (index = 0; index < this->virtual_processor_count; index ++) {
      funk2_virtual_processor__destroy(this->virtual_processor[index]);
    }
  }
  f2__free(to_ptr(this->virtual_processor));
  funk2_hash__destroy(&(this->index_processor_thread_hash));
}


