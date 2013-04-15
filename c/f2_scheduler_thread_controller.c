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
  funk2_processor_conditionlock__init(&(this->need_wait_conditionlock));
  this->need_wait = boolean__false;
  
  funk2_processor_conditionlock__init(&(this->waiting_count_conditionlock));
  this->waiting_count = 0;
}

void funk2_scheduler_thread_controller__destroy(funk2_scheduler_thread_controller_t* this) {
  funk2_processor_conditionlock__destroy(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->need_wait_conditionlock));
}

void funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(funk2_scheduler_thread_controller_t* this) {
  funk2_scheduler_thread_controller__need_wait__set(this, boolean__true);
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > __funk2.system_processor.processor_count) {
      error(nil, "funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait error: waiting_count is out of range.");
    }
  }
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
  status("management thread asking " u64__fstr " virtual_processors to wait politely.", ((u64)__funk2.system_processor.processor_count));
  
  funk2_processor_conditionlock__wait_while(this->waiting_count < __funk2.system_processor.processor_count, &(this->waiting_count_conditionlock));
  
  status("there are " u64__fstr " virtual_processors waiting politely.", ((u64)__funk2.system_processor.processor_count));
}

void funk2_scheduler_thread_controller__let_scheduler_threads_continue(funk2_scheduler_thread_controller_t* this) {
  status("management thread waiting for " u64__fstr " virtual_processors to continue.", ((u64)__funk2.system_processor.processor_count));
  funk2_scheduler_thread_controller__need_wait__set(this, boolean__false);
  
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  {
    s64 waiting_count = this->waiting_count;
    if (waiting_count < 0 || waiting_count > __funk2.system_processor.processor_count) {
      error(nil, "funk2_scheduler_thread_controller__let_scheduler_threads_continue error: waiting_count is out of range.");
    }
  }
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
  
  funk2_processor_conditionlock__wait_while(this->waiting_count > 0, &(this->waiting_count_conditionlock));
  
  status("all " u64__fstr " virtual_processors have continued.", ((u64)__funk2.system_processor.processor_count));
}

void funk2_scheduler_thread_controller__user_wait_politely(funk2_scheduler_thread_controller_t* this) {
  status("virtual processor " u64__fstr " waiting politely.", this_processor_thread__pool_index());
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  this->waiting_count ++;
  if (this->waiting_count > __funk2.system_processor.processor_count) {
    status(    "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > " u64__fstr ")", ((u64)__funk2.system_processor.processor_count));
    error(nil, "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count > __funk2.system_processor.processor_count)");
  }
  funk2_processor_conditionlock__broadcast(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
  
  funk2_processor_conditionlock__wait_while(this->need_wait, &(this->need_wait_conditionlock));
  
  status("virtual processor " u64__fstr " continuing.", this_processor_thread__pool_index());
  
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  this->waiting_count --;
  if (this->waiting_count < 0) {
    error(nil, "funk2_scheduler_thread_controller__user_wait_politely error: (waiting_count < 0)");
  }
  funk2_processor_conditionlock__broadcast(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
}

void funk2_scheduler_thread_controller__check_user_wait_politely(funk2_scheduler_thread_controller_t* this) {
  if (this->need_wait) {
    funk2_scheduler_thread_controller__user_wait_politely(this);
  }
}

void funk2_scheduler_thread_controller__need_wait__set(funk2_scheduler_thread_controller_t* this, boolean_t need_wait) {
  funk2_processor_conditionlock__lock(&(this->need_wait_conditionlock));
  this->need_wait = need_wait;
  funk2_processor_conditionlock__broadcast(&(this->need_wait_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->need_wait_conditionlock));
}

