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
  pthread_mutex_lock(&(this->tid_initialized_cond_mutex));
  this->tid             = raw__gettid();
  this->tid_initialized = boolean__true;
  pthread_cond_signal(&(this->tid_initialized_cond));
  pthread_mutex_unlock(&(this->tid_initialized_cond_mutex));
  status("start_processor_thread_wrapper tid=" u64__fstr, (u64)(this->tid));
  pthread_mutex_lock(&(this->added_to_handler_cond_mutex));
  while (! (this->added_to_handler)) {
    pthread_cond_wait(&(this->added_to_handler_cond), &(this->added_to_handler_cond_mutex));
  }
  funk2_processor_thread_event_t* event = raw__begin_event("start_processor_thread_wrapper");
  void* return_value = (*(this->start_function))(this->args);
  raw__end_event(event);
  this->result = return_value;
  return return_value;
}

void funk2_processor_thread__init(funk2_processor_thread_t* this, funk2_processor_thread_function_pointer_t start_function, void* args) {
  pthread_mutex_init(&(this->tid_initialized_cond_mutex), NULL);
  pthread_cond_init(&(this->tid_initialized_cond), NULL);
  this->tid_initialized = boolean__false;
  pthread_mutex_init(&(this->added_to_handler_cond_mutex), NULL);
  pthread_cond_init(&(this->added_to_handler_cond), NULL);
  this->added_to_handler = boolean__false;
  this->start_function  = start_function;
  this->args            = args;
  funk2_thread_safe_hash__init(&(this->event_hash), 10);
}

void funk2_processor_thread__destroy(funk2_processor_thread_t* this) {
  pthread_mutex_destroy(&(this->tid_initialized_cond_mutex));
  pthread_cond_destroy(&(this->tid_initialized_cond));
  pthread_mutex_destroy(&(this->added_to_handler_cond_mutex));
  pthread_cond_destroy(&(this->added_to_handler_cond));
  funk2_thread_safe_hash__key__iteration(&(this->event_hash), key,
					 funk2_processor_thread_event_t* event = (funk2_processor_thread_event_t*)from_ptr(key);
					 funk2_processor_thread_event__destroy(event);
					 f2__free(to_ptr(event));
					 );
  funk2_thread_safe_hash__destroy(&(this->event_hash));
}

// must only be called by owner (use raw__begin_event from f2_processor_thread_handler.[ch])
funk2_processor_thread_event_t* funk2_processor_thread__create_event(funk2_processor_thread_t* this, char* message) {
  funk2_processor_thread__check_in(this);
  u64                             nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  funk2_processor_thread_event_t* event                  = (funk2_processor_thread_event_t*)from_ptr(f2__malloc(sizeof(funk2_processor_thread_event_t)));
  funk2_processor_thread_event__init(event, nanoseconds_since_1970, message);
  funk2_thread_safe_hash__add(&(this->event_hash), (u64)to_ptr(event), (u64)to_ptr(event));
  return event;
}

// must only be called by owner (use raw__end_event from f2_processor_thread_handler.[ch])
void funk2_processor_thread__remove_event(funk2_processor_thread_t* this, funk2_processor_thread_event_t* event) {
  funk2_thread_safe_hash__remove(&(this->event_hash), (u64)to_ptr(event));
  funk2_processor_thread__check_in(this);
}

void funk2_processor_thread__start(funk2_processor_thread_t* this) {
  int result = create_thread_with_large_stack(&(this->pthread), start_processor_thread_wrapper, this);
  if (result != 0) {
    printf("\nfunk2_processor_thread__init: error creating new pthread.\n");
    perror("pthread_create");
    exit(-1);
  }
  pthread_mutex_lock(&(this->tid_initialized_cond_mutex));
  while (! (this->tid_initialized)) {
    pthread_cond_wait(&(this->tid_initialized_cond), &(this->tid_initialized_cond_mutex));
  }
  pthread_mutex_unlock(&(this->tid_initialized_cond_mutex));
}

// must only be called by owner (use raw__join from f2_processor_thread_handler.[ch])
void* funk2_processor_thread__join(funk2_processor_thread_t* this, funk2_processor_thread_t* thread_to_join) {
  funk2_processor_thread_event_t* event = funk2_processor_thread__create_event(this, "funk2_processor_thread__join");
  int join_result = pthread_join(thread_to_join->pthread, NULL);
  funk2_processor_thread__remove_event(this, event);
  if (join_result != 0) {
    switch(join_result) {
    case EDEADLK:
      status("funk2_processor_thread__join error: A deadlock was detected (e.g., two threads tried to join with each other); or thread specifies the calling thread.");
      break;
    case EINVAL:
      status("funk2_processor_thread__join error: Thread is not a joinable thread OR Another thread is already waiting to join with thread.");
      break;
    case ESRCH:
      status("funk2_processor_thread__join error: No thread with the ID thread could be found.");
      break;
    default:
      status("funk2_processor_thread__join error: Unknown error.");
      break;
    }
    error(nil, "funk2_processor_thread__join error.");
  }
  return thread_to_join->result;
}

// calling this funktion directly from within a processor thread does not perform accounting.
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

// must only be called by owner (use raw__nanosleep from f2_processor_thread_handler.[ch])
void funk2_processor_thread__nanosleep(funk2_processor_thread_t* this, u64 nanoseconds) {
  funk2_processor_thread_event_t* event = funk2_processor_thread__create_event(this, "funk2_processor_thread__nanosleep");
  u64 start_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  __funk2__nanosleep(nanoseconds);
  u64 end_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  this->sleep_nanoseconds += (end_nanoseconds_since_1970 - start_nanoseconds_since_1970);
  funk2_processor_thread__remove_event(this, event);
}

void funk2_processor_thread__print_status(funk2_processor_thread_t* this) {
  status("  processor_thread tid=" u64__fstr, this->tid);
  funk2_thread_safe_hash__key__iteration(&(this->event_hash), key,
					 funk2_processor_thread_event_t* event = (funk2_processor_thread_event_t*)from_ptr(key);
					 funk2_processor_thread_event__print_status(event);
					 );
}

void funk2_processor_thread__check_in(funk2_processor_thread_t* this) {
#if defined(DEBUG_PROCESSOR_THREAD)
  {
    f2tid_t tid = raw__gettid();
    if (tid != this->tid) {
      error(nil, "funk2_processor_thread__check_in debug fatal error: tid != this->tid");
    }
  }
#endif // DEBUG_PROCESSOR_THREAD
  this->last_checked_in_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
}
