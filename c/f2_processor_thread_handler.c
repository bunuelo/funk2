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
  pthread_spin_init(&(this->access_spinlock), PTHREAD_PROCESS_PRIVATE);
  this->processor_thread_list       = NULL;
}

void funk2_processor_thread_handler__destroy(funk2_processor_thread_handler_t* this) {
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  while (iter) {
    funk2_processor_thread_list_t* next = iter->next;
    funk2_processor_thread__destroy(&(iter->processor_thread));
    f2__free(to_ptr(iter));
    iter = next;
  }
  pthread_spin_destroy(&(this->access_spinlock));
}

funk2_processor_thread_t* funk2_processor_thread_handler__add_new_processor_thread(funk2_processor_thread_handler_t* this, funk2_processor_thread_function_pointer_t start_function, void* args) {
  status("processor_thread_handler starting new processor thread.");
  funk2_processor_thread_list_t* new_processor_thread_node = (funk2_processor_thread_list_t*)from_ptr(f2__malloc(sizeof(funk2_processor_thread_list_t)));
  funk2_processor_thread_t*      processor_thread          = &(new_processor_thread_node->processor_thread);
  
  funk2_processor_thread__init(processor_thread, start_function, args);
  
  pthread_spin_lock(&(this->access_spinlock));
  new_processor_thread_node->next = this->processor_thread_list;
  this->processor_thread_list = new_processor_thread_node;
  pthread_spin_unlock(&(this->access_spinlock));
  
  funk2_processor_thread__start(processor_thread);
  
  return processor_thread;
}

boolean_t funk2_processor_thread_handler__remove_processor_thread(funk2_processor_thread_handler_t* this, funk2_processor_thread_t* processor_thread) {
  boolean_t                      success = boolean__false;
  funk2_processor_thread_list_t* prev    = NULL;
  pthread_spin_lock(&(this->access_spinlock));
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  while (iter != NULL) {
    funk2_processor_thread_list_t* next = iter->next;
    if (&(iter->processor_thread) == processor_thread) {
      success = boolean__true;
      if (prev != NULL) {
	prev->next = next;
      } else {
	this->processor_thread_list = next;
      }
      funk2_processor_thread__destroy(&(iter->processor_thread));
      f2__free(to_ptr(iter));
      break;
    }
    prev = iter;
    iter = next;
  }
  pthread_spin_unlock(&(this->access_spinlock));
  return success;
}

funk2_processor_thread_t* funk2_processor_thread_handler__lookup_tid(funk2_processor_thread_handler_t* this, f2tid_t tid) {
  pthread_spin_lock(&(this->access_spinlock));
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  while (iter) {
    if (iter->processor_thread.tid == tid) {
      funk2_processor_thread_t* return_value = &(iter->processor_thread);
      pthread_spin_unlock(&(this->access_spinlock));
      return return_value;
    }
    iter = iter->next;
  }
  pthread_spin_unlock(&(this->access_spinlock));
  return NULL;
}

funk2_processor_thread_t* funk2_processor_thread_handler__myself(funk2_processor_thread_handler_t* this) {
  f2tid_t tid = raw__gettid();
  return funk2_processor_thread_handler__lookup_tid(this, tid);
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
  boolean_t success = funk2_processor_thread_handler__remove_processor_thread(&(__funk2.processor_thread_handler), processor_thread);
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

