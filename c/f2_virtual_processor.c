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

// funk2_processor_thread_array

void funk2_processor_thread_array__init(funk2_processor_thread_array_t* this) {
  this->alloc_length = 1024;
  this->length       = 0;
  this->array        = (funk2_processor_thread_t**)from_ptr(f2__malloc(sizeof(funk2_processor_thread_t*) * this->alloc_length));
}

void funk2_processor_thread_array__destroy(funk2_processor_thread_array_t* this) {
  f2__free(to_ptr(this->array));
}


// funk2_virtual_processor

void funk2_virtual_processor__init(funk2_virtual_processor_t* this) {
  funk2_processor_thread_array__init(&(this->processor_thread_array));
}

void funk2_virtual_processor__destroy(funk2_virtual_processor_t* this) {
  funk2_processor_thread_array__destroy(&(this->processor_thread_array));
}



