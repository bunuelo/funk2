// 
// Copyright (c) 2007-2012 Bo Morgan.
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

void funk2_scheduler_thread_controller__init(funk2_scheduler_thread_controller_t* this) {
  this->please_wait   = boolean__false;
  
  pthread_mutex_init(&(this->waiting_count_mutex), NULL);
  pthread_cond_init(&(this->waiting_count_cond), NULL);
  this->waiting_count = 0;
}

void funk2_scheduler_thread_controller__destroy(funk2_scheduler_thread_controller_t* this) {
  pthread_mutex_destroy(&(this->waiting_count_mutex));
  pthread_cond_destroy(&(this->waiting_count_cond));
}

void funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(funk2_scheduler_thread_controller_t* this) {
  this->please_wait = boolean__true;
  pthread_mutex_lock(&(this->waiting_count_mutex));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > memory_pool_num) {
      error(nil, "funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait error: waiting_count is out of range.");
    }
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  status("management thread asking " u64__fstr " virtual_processors to wait politely.", ((u64)memory_pool_num));
  
  pthread_mutex_lock(&(this->waiting_count_mutex));
  while (this->waiting_count < memory_pool_num) {
    pthread_cond_wait(&(this->waiting_count_cond), &(this->waiting_count_mutex));
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  status("there are " u64__fstr " virtual_processors waiting politely.", ((u64)memory_pool_num));
}

void funk2_scheduler_thread_controller__let_scheduler_threads_continue(funk2_scheduler_thread_controller_t* this) {
  status("management thread waiting for " u64__fstr " virtual_processors to continue.", ((u64)memory_pool_num));
  this->please_wait = boolean__false;
  
  pthread_mutex_lock(&(this->waiting_count_mutex));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > memory_pool_num) {
      error(nil, "funk2_scheduler_thread_controller__let_scheduler_threads_continue error: waiting_count is out of range.");
    }
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  
  pthread_mutex_lock(&(this->waiting_count_mutex));
  while (waiting_count > 0) {
    pthread_cond_wait(&(this->waiting_count_cond), &(this->waiting_count_mutex));
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  
  status("all " u64__fstr " virtual_processors have continued.", ((u64)memory_pool_num));
}

void funk2_scheduler_thread_controller__user_wait_politely(funk2_scheduler_thread_controller_t* this) {
  status("virtual processor " u64__fstr " waiting politely.", this_processor_thread__pool_index());
  pthread_mutex_lock(&(this->waiting_count_mutex));
  this->waiting_count ++;
  if (this->waiting_count > memory_pool_num) {
    status(    "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > " u64__fstr ")", ((u64)memory_pool_num));
    error(nil, "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > memory_pool_num)");
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  pthread_cond_broadcast(&(this->waiting_count_cond));
  
  while (this->please_wait) {
    raw__fast_spin_sleep_yield();
  }
  
  status("virtual processor " u64__fstr " continuing.", this_processor_thread__pool_index());
  
  pthread_mutex_lock(&(this->waiting_count_mutex));
  this->waiting_count --;
  if (this->waiting_count < 0) {
    error(nil, "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count < 0)");
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  pthread_cond_broadcast(&(this->waiting_count_cond));
}

void funk2_scheduler_thread_controller__check_user_wait_politely(funk2_scheduler_thread_controller_t* this) {
  if (this->please_wait) {
    funk2_scheduler_thread_controller__user_wait_politely(this);
  }
}

