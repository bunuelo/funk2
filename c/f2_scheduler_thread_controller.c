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

void funk2_scheduler_thread_controller__init(funk2_scheduler_thread_controller_t* this) {
  pthread_mutex_init(&(this->need_wait_mutex), NULL);
  pthread_cond_init(&(this->need_wait_cond), NULL);
  this->need_wait = boolean__false;
  
  pthread_mutex_init(&(this->waiting_count_mutex), NULL);
  pthread_cond_init(&(this->waiting_count_cond), NULL);
  this->waiting_count = 0;
}

void funk2_scheduler_thread_controller__destroy(funk2_scheduler_thread_controller_t* this) {
  pthread_mutex_destroy(&(this->waiting_count_mutex));
  pthread_cond_destroy(&(this->waiting_count_cond));
  pthread_mutex_destroy(&(this->need_wait_mutex));
  pthread_cond_destroy(&(this->need_wait_cond));
}

void funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(funk2_scheduler_thread_controller_t* this) {
  funk2_scheduler_thread_controller__need_wait__set(this, boolean__true);
  pthread_mutex_lock(&(this->waiting_count_mutex));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > __funk2.system_processor.processor_count) {
      error(nil, "funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait error: waiting_count is out of range.");
    }
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  status("management thread asking " u64__fstr " virtual_processors to wait politely.", ((u64)__funk2.system_processor.processor_count));
  
  pthread_cond_wait_while(this->waiting_count < __funk2.system_processor.processor_count, &(this->waiting_count_cond), &(this->waiting_count_mutex));
  
  status("there are " u64__fstr " virtual_processors waiting politely.", ((u64)__funk2.system_processor.processor_count));
}

void funk2_scheduler_thread_controller__let_scheduler_threads_continue(funk2_scheduler_thread_controller_t* this) {
  status("management thread waiting for " u64__fstr " virtual_processors to continue.", ((u64)__funk2.system_processor.processor_count));
  funk2_scheduler_thread_controller__need_wait__set(this, boolean__false);
  
  pthread_mutex_lock(&(this->waiting_count_mutex));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > __funk2.system_processor.processor_count) {
      error(nil, "funk2_scheduler_thread_controller__let_scheduler_threads_continue error: waiting_count is out of range.");
    }
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  
  pthread_cond_wait_while(this->waiting_count > 0, &(this->waiting_count_cond), &(this->waiting_count_mutex));
  
  status("all " u64__fstr " virtual_processors have continued.", ((u64)__funk2.system_processor.processor_count));
}

void funk2_scheduler_thread_controller__user_wait_politely(funk2_scheduler_thread_controller_t* this) {
  status("virtual processor " u64__fstr " waiting politely.", this_processor_thread__pool_index());
  pthread_mutex_lock(&(this->waiting_count_mutex));
  this->waiting_count ++;
  if (this->waiting_count > __funk2.system_processor.processor_count) {
    status(    "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > " u64__fstr ")", ((u64)__funk2.system_processor.processor_count));
    error(nil, "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > __funk2.system_processor.processor_count)");
  }
  pthread_mutex_unlock(&(this->waiting_count_mutex));
  pthread_cond_broadcast(&(this->waiting_count_cond));
  
  pthread_cond_wait_while(this->need_wait, &(this->need_wait_cond), &(this->need_wait_mutex));
  
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
  if (this->need_wait) {
    funk2_scheduler_thread_controller__user_wait_politely(this);
  }
}

void funk2_scheduler_thread_controller__need_wait__set(funk2_scheduler_thread_controller_t* this, boolean_t need_wait) {
  pthread_mutex_lock(&(this->need_wait_mutex));
  this->need_wait = need_wait;
  pthread_mutex_unlock(&(this->need_wait_mutex));
  pthread_cond_broadcast(&(this->need_wait_cond));
}

