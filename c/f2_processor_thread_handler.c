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

void funk2_processor_thread_handler__init(funk2_processor_thread_handler_t* this) {
  pthread_spin_init(&(this->access_spinlock));
  this->processor_thread_next_index = 0;
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
  
  funk2_processor_thread__init(processor_thread, -1, start_function, args);
  
  this->processor_thread_next_index ++;
  pthread_spin_lock(&(this->access_spinlock));
  new_processor_thread_node->next = this->processor_thread_list;
  this->processor_thread_list = new_processor_thread_node;
  pthread_spin_unlock(&(this->access_spinlock));
  return processor_thread;
}

funk2_processor_thread_t* funk2_processor_thread_handler__myself(funk2_processor_thread_handler_t* this) {
  pthread_t                      tid  = pthread_self();
  pthread_spin_lock(&(this->access_spinlock));
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  pthread_spin_unlock(&(this->access_spinlock));
  while (iter) {
    if (pthread_equal(iter->processor_thread.pthread, tid)) {
      pthread_spin_lock(&(this->access_spinlock));
      funk2_processor_thread_t* return_value = &(iter->processor_thread);
      pthread_spin_unlock(&(this->access_spinlock));
      return return_value;
    }
    pthread_spin_lock(&(this->access_spinlock));
    iter = iter->next;
    pthread_spin_unlock(&(this->access_spinlock));
  }
  return NULL;
}

void funk2_processor_thread_handler__remove_pthread(funk2_processor_thread_handler_t* this, pthread_t tid) {
  funk2_processor_thread_list_t* prev = NULL;
  pthread_spin_lock(&(this->access_spinlock));
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  pthread_spin_unlock(&(this->access_spinlock));
  while (iter) {
    pthread_spin_lock(&(this->access_spinlock));
    funk2_processor_thread_list_t* next = iter->next;
    pthread_spin_unlock(&(this->access_spinlock));
    if (pthread_equal(iter->processor_thread.pthread, tid)) {
      if (prev) {
	pthread_spin_lock(&(this->access_spinlock));
	prev->next = next;
	pthread_spin_unlock(&(this->access_spinlock));
      } else {
	pthread_spin_lock(&(this->access_spinlock));
	this->processor_thread_list = next;
	pthread_spin_unlock(&(this->access_spinlock));
      }
      funk2_processor_thread__destroy(&(iter->processor_thread));
      f2__free(to_ptr(iter));
    }
    iter = next;
  }
}

s64 this_processor_thread__try_get_pool_index() {
  return funk2_virtual_processor_handler__try_get_my_virtual_processor_index(&(__funk2.virtual_processor_handler));
}

u64 this_processor_thread__pool_index() {
  return funk2_virtual_processor_handler__my_virtual_processor_index(&(__funk2.virtual_processor_handler));
}

void raw__processor_thread_handler__nanosleep(u64 nanoseconds) {
  funk2_processor_thread_t* my_processor_thread = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  if (my_processor_thread == NULL) {
    error(nil, "raw__processor_thread_handler__nanosleep my_processor_thread==NULL.");
  }
  funk2_processor_thread__nanosleep(my_processor_thread, nanoseconds);
}

