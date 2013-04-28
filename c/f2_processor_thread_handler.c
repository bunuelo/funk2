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

f2tid_t raw__gettid() {
#if (HAVE_SYSCALL_SYS_GETTID == 1)
  return (pid_t)syscall(SYS_gettid);
#else
#  if defined(HAVE_PTHREAD_GETW32THREADHANDLE_NP)
  HANDLE my_thread = pthread_getw32threadhandle_np(pthread_self());
  return (f2tid_t)to_ptr(my_thread);
#  else
#    error No definition of raw__gettid()
#  endif
#endif // (HAVE_SYSCALL_SYS_GETTID == 1)
}

// funk2_processor_thread_handler

void funk2_processor_thread_handler__init(funk2_processor_thread_handler_t* this) {
  funk2_thread_safe_hash__init(&(this->processor_thread_tid_hash), 16);
}

void funk2_processor_thread_handler__destroy(funk2_processor_thread_handler_t* this) {
  funk2_thread_safe_hash__value__iteration(&(this->processor_thread_tid_hash), processor_thread_ptr,
					   funk2_processor_thread_t* processor_thread = (funk2_processor_thread_t*)from_ptr(processor_thread_ptr);
					   funk2_processor_thread__destroy(processor_thread);
					   f2__free(to_ptr(processor_thread));
					   );
  funk2_thread_safe_hash__destroy(&(this->processor_thread_tid_hash));
}

funk2_processor_thread_t* funk2_processor_thread_handler__add_new_processor_thread(funk2_processor_thread_handler_t* this, funk2_processor_thread_function_pointer_t start_function, void* args) {
  status("processor_thread_handler starting new processor thread.");
  funk2_processor_thread_t* processor_thread = (funk2_processor_thread_t*)from_ptr(f2__malloc(sizeof(funk2_processor_thread_t)));
  
  funk2_processor_thread__init(processor_thread, start_function, args);
  
  funk2_processor_thread__start(processor_thread);
  
  funk2_thread_safe_hash__add(&(this->processor_thread_tid_hash), processor_thread->tid, (u64)to_ptr(processor_thread));
  
  return processor_thread;
}

boolean_t funk2_processor_thread_handler__remove_processor_thread(funk2_processor_thread_handler_t* this, f2tid_t tid) {
  boolean_t success = funk2_thread_safe_hash__remove(&(this->processor_thread_tid_hash), tid);
  return success;
}

funk2_processor_thread_t* funk2_processor_thread_handler__lookup_tid(funk2_processor_thread_handler_t* this, f2tid_t tid) {
  u64 result = funk2_thread_safe_hash__try_lookup(&(this->processor_thread_tid_hash), tid, (u64)to_ptr(NULL));
  return (funk2_processor_thread_t*)from_ptr(result);
}

funk2_processor_thread_t* funk2_processor_thread_handler__myself(funk2_processor_thread_handler_t* this) {
  f2tid_t my_tid = raw__gettid();
  return funk2_processor_thread_handler__lookup_tid(this, my_tid);
}

void funk2_processor_thread_handler__print_status(funk2_processor_thread_handler_t* this) {
  status("vvv processor_thread_handler vvv");
  funk2_thread_safe_hash__value__iteration(&(this->processor_thread_tid_hash), value,
					   funk2_processor_thread_t* processor_thread = (funk2_processor_thread_t*)from_ptr(value);
					   funk2_processor_thread__print_status(processor_thread);
					   );
  status("^^^ processor_thread_handler ^^^");
}

s64 this_processor_thread__try_get_pool_index() {
  return funk2_virtual_processor_handler__try_get_my_virtual_processor_index(&(__funk2.virtual_processor_handler));
}

u64 this_processor_thread__pool_index() {
  return funk2_virtual_processor_handler__my_virtual_processor_index(&(__funk2.virtual_processor_handler));
}

f2tid_t raw__thread(funk2_processor_thread_function_pointer_t start_function, void* args) {
  funk2_processor_thread_t* processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), start_function, args);
  return processor_thread->tid;
}

void* raw__join(f2tid_t tid) {
  funk2_processor_thread_t* processor_thread = funk2_processor_thread_handler__lookup_tid(&(__funk2.processor_thread_handler), tid);
  if (processor_thread == NULL) {
    status("raw__join failed to lookup processor_thread from processor_thread_handler.  tid=" u64__fstr, (u64)tid);
    error(nil, "raw__join failed to lookup processor_thread from processor_thread_handler.");
  }
  void*     result  = funk2_processor_thread__join(processor_thread);
  boolean_t success = funk2_processor_thread_handler__remove_processor_thread(&(__funk2.processor_thread_handler), tid);
  if (! success) {
    status("raw__join failed to remove processor_thread from processor_thread_handler.  tid=" u64__fstr, (u64)tid);
    error(nil, "raw__join failed to remove processor_thread from processor_thread_handler.");
  }
  status("raw__join successful.  tid=" u64__fstr, (u64)tid);
  return result;
}

void raw__nanosleep(u64 nanoseconds) {
  funk2_processor_thread_t* my_processor_thread = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  if (my_processor_thread == NULL) {
    error(nil, "raw__processor_thread_handler__nanosleep my_processor_thread==NULL.");
  }
  funk2_processor_thread__nanosleep(my_processor_thread, nanoseconds);
}

funk2_processor_thread_event_t* raw__begin_event(char* message) {
  funk2_processor_thread_t*       my_processor_thread = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  funk2_processor_thread_event_t* event               = funk2_processor_thread__create_event(my_processor_thread, message);
  return event;
}

void raw__end_event(funk2_processor_thread_event_t* event) {
  funk2_processor_thread_t* my_processor_thread = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  funk2_processor_thread__remove_event(my_processor_thread, event);
}

void raw__thread_status() {
  funk2_processor_thread_handler__print_status(&(__funk2.processor_thread_handler));
}
