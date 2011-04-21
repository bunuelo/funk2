// 
// Copyright (c) 2007-2011 Bo Morgan.
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

// int pthread_num_processors_np(void);
// int pthread_processor_bind_np(int request, pthread_spu_t *answer, pthread_spu_t spu, pthread_t tid);
// int pthread_processor_id_np(int request, pthread_spu_t *answer, pthread_spu_t spu);


// funk2_virtual_processor_handler

void funk2_virtual_processor_handler__init(funk2_virtual_processor_handler_t* this, u64 virtual_processor_count) {
  status("initializing virtual_processor_handler with " u64__fstr " virtual processor threads.", virtual_processor_count);
  {
    funk2_processor_mutex__init(&(this->virtual_processor_index_processor_thread_hash_mutex));
    funk2_hash__init(&(this->virtual_processor_index_processor_thread_hash), 10);
  }
  {
    funk2_processor_mutex__init(&(this->all_virtual_processor_threads_mutex));
    this->all_virtual_processor_threads = NULL;
  }
  {
    funk2_processor_mutex__init(&(this->free_virtual_processor_threads_mutex));
    this->free_virtual_processor_threads = NULL;
  }
  {
    funk2_processor_mutex__init(&(this->virtual_processor_thread_processor_thread_hash_mutex));
    funk2_hash__init(&(this->virtual_processor_thread_processor_thread_hash), 10);
  }
  {
    funk2_processor_mutex__init(&(this->virtual_processor_index_pthread_hash_mutex));
    funk2_hash__init(&(this->virtual_processor_index_pthread_hash), 10);
  }
  this->virtual_processor_count = virtual_processor_count;
  this->virtual_processor       = NULL;
}

void funk2_virtual_processor_handler__destroy(funk2_virtual_processor_handler_t* this) {
  status("destroying virtual_processor_handler.");
  funk2_virtual_processor_handler__destroy_all_virtual_processor_threads(this);
  {
    s64 index;
    for (index = 0; index < this->virtual_processor_count; index ++) {
      funk2_virtual_processor__destroy(this->virtual_processor[index]);
    }
  }
  f2__free(to_ptr(this->virtual_processor));
  {
    funk2_processor_mutex__destroy(&(this->virtual_processor_index_processor_thread_hash_mutex));
    funk2_hash__destroy(&(this->virtual_processor_index_processor_thread_hash));
  }
  {
    funk2_processor_mutex__destroy(&(this->all_virtual_processor_threads_mutex));
    funk2_virtual_processor_thread_cons_t* iter = this->all_virtual_processor_threads;
    while (iter) {
      funk2_virtual_processor_thread_cons_t* next = iter->next;
      f2__free(to_ptr(iter));
      iter = next;
    }
  }
  {
    funk2_processor_mutex__destroy(&(this->free_virtual_processor_threads_mutex));
    funk2_virtual_processor_thread_cons_t* iter = this->free_virtual_processor_threads;
    while (iter) {
      funk2_virtual_processor_thread_cons_t* next = iter->next;
      f2__free(to_ptr(iter));
      iter = next;
    }
  }
  {
    funk2_processor_mutex__destroy(&(this->virtual_processor_thread_processor_thread_hash_mutex));
    funk2_hash__destroy(&(this->virtual_processor_thread_processor_thread_hash));
  }
  {
    funk2_processor_mutex__destroy(&(this->virtual_processor_index_pthread_hash_mutex));
    funk2_hash__destroy(&(this->virtual_processor_index_pthread_hash));
  }
}

void funk2_virtual_processor_handler__destroy_all_virtual_processor_threads(funk2_virtual_processor_handler_t* this) {
  funk2_processor_mutex__lock(&(this->all_virtual_processor_threads_mutex));
  {
    funk2_virtual_processor_thread_cons_t* iter = this->all_virtual_processor_threads;
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__signal_exit(virtual_processor_thread);
      iter = iter->next;
    }
  }
  {
    funk2_virtual_processor_thread_cons_t* iter = this->all_virtual_processor_threads;
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__finalize_exit(virtual_processor_thread);
      iter = iter->next;
    }
  }
  {
    funk2_virtual_processor_thread_cons_t* iter = this->all_virtual_processor_threads;
    while (iter) {
      funk2_virtual_processor_thread_t* virtual_processor_thread = iter->virtual_processor_thread;
      funk2_virtual_processor_thread__destroy(virtual_processor_thread);
      f2__free(to_ptr(virtual_processor_thread));
      iter = iter->next;
    }
  }
  funk2_processor_mutex__unlock(&(this->all_virtual_processor_threads_mutex));
}

void funk2_virtual_processor_handler__start_virtual_processors(funk2_virtual_processor_handler_t* this) {
  if (this->virtual_processor != NULL) {
    error(nil, "funk2_virtual_processor_handler__start_virtual_processors error: virtual_processor array seems to already be initialized.");
  }
  this->virtual_processor = (funk2_virtual_processor_t**)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t*) * (this->virtual_processor_count)));
  {
    s64 index;
    for (index = 0; index < (this->virtual_processor_count); index ++) {
      this->virtual_processor[index] = (funk2_virtual_processor_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_t)));
    }
  }
  {
    s64 index;
    for (index = 0; index < (this->virtual_processor_count); index ++) {
      funk2_virtual_processor__init(this->virtual_processor[index], index);
    }
  }
}

funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__get_free_virtual_processor_thread(funk2_virtual_processor_handler_t* this) {
  funk2_virtual_processor_thread_t* virtual_processor_thread = NULL;
  if (! (this->free_virtual_processor_threads)) {
    virtual_processor_thread = (funk2_virtual_processor_thread_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_t)));
    funk2_virtual_processor_thread__init(virtual_processor_thread);
    {
      funk2_processor_mutex__lock(&(this->virtual_processor_thread_processor_thread_hash_mutex));
      funk2_hash__add(&(this->virtual_processor_thread_processor_thread_hash), (u64)to_ptr(virtual_processor_thread->processor_thread), (u64)to_ptr(virtual_processor_thread));
      funk2_processor_mutex__unlock(&(this->virtual_processor_thread_processor_thread_hash_mutex));
    }
    {
      funk2_virtual_processor_thread_cons_t* cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_cons_t)));
      cons->virtual_processor_thread              = virtual_processor_thread;
      {
	funk2_processor_mutex__lock(&(this->all_virtual_processor_threads_mutex));
	cons->next                  = this->all_virtual_processor_threads;
	this->all_virtual_processor_threads = cons;
	funk2_processor_mutex__unlock(&(this->all_virtual_processor_threads_mutex));
      }
    }
  } else {
    funk2_processor_mutex__lock(&(this->free_virtual_processor_threads_mutex));
    funk2_virtual_processor_thread_cons_t* cons = this->free_virtual_processor_threads;
    this->free_virtual_processor_threads        = cons->next;
    virtual_processor_thread                    = cons->virtual_processor_thread;
    funk2_processor_mutex__unlock(&(this->free_virtual_processor_threads_mutex));
    f2__free(to_ptr(cons));
  }
  return virtual_processor_thread;
}

void funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor(funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread, u64 virtual_processor_index) {
  //status("funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor: virtual_processor_index=" u64__fstr, virtual_processor_index);
  {
    funk2_processor_mutex__lock(&(this->virtual_processor_index_processor_thread_hash_mutex));
    funk2_hash__add(&(this->virtual_processor_index_processor_thread_hash), (u64)to_ptr(virtual_processor_thread), virtual_processor_index);
    funk2_processor_mutex__unlock(&(this->virtual_processor_index_processor_thread_hash_mutex));
  }
  {
    funk2_processor_mutex__lock(&(this->virtual_processor_index_pthread_hash_mutex));
    funk2_hash__add(&(this->virtual_processor_index_pthread_hash), (u64)(virtual_processor_thread->processor_thread->pthread), (u64)virtual_processor_index);
    funk2_processor_mutex__unlock(&(this->virtual_processor_index_pthread_hash_mutex));
  }
  funk2_virtual_processor__know_of_one_more_assigned_virtual_processor_thread(this->virtual_processor[virtual_processor_index]);
}

void funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor(funk2_virtual_processor_handler_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread) {
  u64 virtual_processor_index = virtual_processor_thread->virtual_processor_assignment_index;
  //status("funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor: virtual_processor_thread->virtual_processor_assignment_index=" u64__fstr, virtual_processor_index);
  {
    funk2_processor_mutex__lock(&(this->virtual_processor_index_processor_thread_hash_mutex));
    funk2_hash__remove(&(this->virtual_processor_index_processor_thread_hash), (u64)to_ptr(virtual_processor_thread));
    funk2_processor_mutex__unlock(&(this->virtual_processor_index_processor_thread_hash_mutex));
  }
  {
    funk2_processor_mutex__lock(&(this->virtual_processor_index_pthread_hash_mutex));
    funk2_hash__remove(&(this->virtual_processor_index_pthread_hash), (u64)(virtual_processor_thread->processor_thread->pthread));
    funk2_processor_mutex__unlock(&(this->virtual_processor_index_pthread_hash_mutex));
  }
  funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread(this->virtual_processor[virtual_processor_index]);
  { // add to free processor thread list
    funk2_processor_mutex__lock(&(this->free_virtual_processor_threads_mutex));
    funk2_virtual_processor_thread_cons_t* cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_cons_t)));
    cons->next                                  = this->free_virtual_processor_threads;
    cons->virtual_processor_thread              = this->virtual_processor[virtual_processor_index];
    this->free_virtual_processor_threads        = cons;
    funk2_processor_mutex__unlock(&(this->free_virtual_processor_threads_mutex));
  }
}

funk2_virtual_processor_thread_t* funk2_virtual_processor_handler__my_virtual_processor_thread(funk2_virtual_processor_handler_t* this) {
  funk2_processor_thread_t*         processor_thread         = funk2_processor_thread_handler__myself(&(__funk2.processor_thread_handler));
  funk2_virtual_processor_thread_t* virtual_processor_thread = (funk2_virtual_processor_thread_t*)from_ptr(funk2_hash__lookup(&(this->virtual_processor_thread_processor_thread_hash), (u64)to_ptr(processor_thread)));
  return virtual_processor_thread;
}

u64 funk2_virtual_processor_handler__my_virtual_processor_index(funk2_virtual_processor_handler_t* this) {
  if (__funk2.memory.bootstrapping_mode) {
    return 0;
  }
  pthread_t pthread                 = pthread_self();
  u64       virtual_processor_index = funk2_hash__lookup(&(this->virtual_processor_index_pthread_hash), (u64)pthread);
  return virtual_processor_index;
}

funk2_virtual_processor_t* funk2_virtual_processor_handler__my_virtual_processor(funk2_virtual_processor_handler_t* this) {
  u64 virtual_processor_assignment_index = funk2_virtual_processor_handler__my_virtual_processor_index(this);
  return this->virtual_processor[virtual_processor_assignment_index];
}

void funk2_virtual_processor_handler__yield(funk2_virtual_processor_handler_t* this) {
  funk2_virtual_processor_t* virtual_processor = funk2_virtual_processor_handler__my_virtual_processor(this);
  funk2_virtual_processor__yield(virtual_processor);
}

