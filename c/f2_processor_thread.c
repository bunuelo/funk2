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

void funk2_processor_thread__init(funk2_processor_thread_t* this, u64 index, funk2_processor_thread_function_pointer_t start_function, void* args) {
  this->index          = index;
  this->start_function = start_function;
  this->args           = args;
  int result = pthread_create(&(this->pthread), NULL, this->start_function, args);
  if (result != 0) {
    printf("\nfunk2_processor_thread__init: error creating new pthread.\n");
    perror("pthread_create");
    exit(-1);
  }
}

void funk2_processor_thread__destroy(funk2_processor_thread_t* this) {
  pthread_detach(this->pthread);
}



