// 
// Copyright (c) 2007-2009 Bo Morgan.
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

void funk2_processor_thread_handler__init(funk2_processor_thread_handler_t* this) {
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
}

funk2_processor_thread_t* funk2_processor_thread_handler__add_new_processor_thread(funk2_processor_thread_handler_t* this, funk2_processor_thread_function_pointer_t start_function, void* args) {
  funk2_processor_thread_list_t* new_processor_thread_node = (funk2_processor_thread_list_t*)f2__malloc(sizeof(funk2_processor_thread_list_t));
  funk2_processor_thread_t*      processor_thread          = &(new_processor_thread_node->processor_thread);
  funk2_processor_thread__init(processor_thread, this->processor_thread_next_index, start_function, args);
  this->processor_thread_next_index ++;
  new_processor_thread_node->next = this->processor_thread_list;
  this->processor_thread_list = new_processor_thread_node;
  return processor_thread;
}

funk2_processor_thread_t* funk2_processor_thread_handler__myself(funk2_processor_thread_handler_t* this) {
  pthread_t                      tid  = pthread_self();
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  while (iter) {
    if (iter->processor_thread.pthread == tid) {
      return &(iter->processor_thread);
    }
    iter = iter->next;
  }
  return NULL;
}

void funk2_processor_thread_handler__remove_pthread(funk2_processor_thread_handler_t* this, pthread_t tid) {
  funk2_processor_thread_list_t* prev = NULL;
  funk2_processor_thread_list_t* iter = this->processor_thread_list;
  while (iter) {
    funk2_processor_thread_list_t* next = iter->next;
    if (iter->processor_thread.pthread == tid) {
      if (prev) {
	prev->next = next;
      } else {
	this->processor_thread_list = next;
      }
      funk2_processor_thread__destroy(&(iter->processor_thread));
      f2__free(iter);
    }
    iter = next;
  }
  return NULL;
}

void funk2_processor_thread_handler__exit_myself(funk2_processor_thread_handler_t* this) {
  funk2_processor_thread_handler__remove_pthread(this, pthread_self());
  pthread_exit(0);
}

u64 this_processor_thread__pool_index() {
  funk2_processor_thread_t* this_processor_thread = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  if (this_processor_thread == NULL) {
    return 0;
  }
  //printf("\npool_index=" u64__fstr "\n", this_processor_thread->index); fflush(stdout);
  return this_processor_thread->index;
}


