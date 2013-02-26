// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

// 8 megabytes used to be necessary with reentrant bytecodes, but now
// this should only need to be 500k or so, but increase this number
// when stack overflows occur.  (hard to tell, I know...)
#define REQUIRED_STACK_SIZE (1*1024*1024)

int create_thread_with_large_stack(pthread_t *out_thread, void *thread_func, void *arg) {
  int            err = 0;
  pthread_attr_t stack_size_attribute;
  size_t         stack_size = 0;

  // Initialize the attribute
  err = pthread_attr_init(&stack_size_attribute);
  if (err) {
    return err;
  }
  
  // Get the default value
  err = pthread_attr_getstacksize(&stack_size_attribute, &stack_size);
  if (err) {
    return err;
  }
  
  // If the default size does not fit our needs, set the attribute with our required value
  if (stack_size < REQUIRED_STACK_SIZE) {
    err = pthread_attr_setstacksize(&stack_size_attribute, REQUIRED_STACK_SIZE);
    if (err) {
      return err;
    }
  }
  
  // Create the thread with our attribute
  err = pthread_create(out_thread, &stack_size_attribute, thread_func, arg);
  return err;
}


void funk2_processor_thread__init(funk2_processor_thread_t* this, u64 index, funk2_processor_thread_function_pointer_t start_function, void* args) {
  this->index          = index;
  this->start_function = start_function;
  this->args           = args;
  int result = create_thread_with_large_stack(&(this->pthread), this->start_function, args);
  if (result != 0) {
    printf("\nfunk2_processor_thread__init: error creating new pthread.\n");
    perror("pthread_create");
    exit(-1);
  }
}

void funk2_processor_thread__destroy(funk2_processor_thread_t* this) {
  //pthread_detach(this->pthread);
}

