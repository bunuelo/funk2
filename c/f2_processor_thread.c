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

void* start_processor_thread_wrapper(void* data) {
  funk2_processor_thread_t* this = (funk2_processor_thread_t*)data;
  pthread_mutex_lock(&(this->initialized_cond_mutex));
  this->tid = raw__gettid();
  pthread_mutex_unlock(&(this->initialized_cond_mutex));
  pthread_cond_signal(&(this->initialized_cond));
  status("start_processor_thread_wrapper tid=" u64__fstr, (u64)(this->tid));
  void* return_value = (*(this->start_function))(this->args);
  boolean_t success = funk2_processor_thread_handler__remove_processor_thread(&(__funk2.processor_thread_handler), this);
  if (! success) {
    error(nil, "start_processor_thread_wrapper error: failed to remove processor_thread from processor_thread_handler.");
  }
  return return_value;
}

void funk2_processor_thread__init(funk2_processor_thread_t* this, funk2_processor_thread_function_pointer_t start_function, void* args) {
  pthread_mutex_init(&(this->initialized_cond_mutex), NULL);
  pthread_cond_init(&(this->initialized_cond), NULL);
  this->initialized    = boolean__false;
  this->start_function = start_function;
  this->args           = args;
}

void funk2_processor_thread__start(funk2_processor_thread_t* this) {
  int result = create_thread_with_large_stack(&(this->pthread), start_processor_thread_wrapper, this);
  if (result != 0) {
    printf("\nfunk2_processor_thread__init: error creating new pthread.\n");
    perror("pthread_create");
    exit(-1);
  }
  pthread_mutex_lock(&(this->initialized_cond_mutex));
  while (! (this->initialized)) {
    pthread_cond_wait(&(this->initialized_cond), &(this->initialized_cond_mutex));
  }
  pthread_mutex_unlock(&(this->initialized_cond_mutex));
}

void funk2_processor_thread__destroy(funk2_processor_thread_t* this) {
  pthread_mutex_destroy(&(this->initialized_cond_mutex));
  pthread_cond_destroy(&(this->initialized_cond));
}

// never call this function directly from within a processor thread.
void __funk2__nanosleep(u64 nanoseconds) {
#if defined(HAVE_NANOSLEEP)
  struct timespec sleepTime;
  struct timespec remainingSleepTime;
  sleepTime.tv_sec  = nanoseconds / nanoseconds_per_second;
  sleepTime.tv_nsec = nanoseconds - ((nanoseconds / nanoseconds_per_second) * nanoseconds_per_second);
  nanosleep(&sleepTime, &remainingSleepTime);
#else
#  if defined(HAVE_CAPITAL_SLEEP)
  Sleep((nanoseconds + 500000) / 1000000);
#  else
#    if defined(HAVE_SLEEP)
  sleep((nanoseconds + 500000000) / 1000000000);
#    else
#      error No sleep function could be compiled into the Funk2 build.
#    endif // HAVE_SLEEP
#  endif // HAVE_CAPITAL_SLEEP
#endif // NANOSLEEP
}

// must only be called by owner (use raw__nanosleep from f2_time.c)
void funk2_processor_thread__nanosleep(funk2_processor_thread_t* this, u64 nanoseconds) {
  u64 start_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  __funk2__nanosleep(nanoseconds);
  u64 end_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  this->sleep_nanoseconds += (end_nanoseconds_since_1970 - start_nanoseconds_since_1970);
}

