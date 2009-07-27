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

void funk2_user_thread_controller__init(funk2_user_thread_controller_t* this) {
  this->please_wait   = boolean__false;
  this->waiting_count = 0;
  funk2_processor_mutex__init(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__destroy(funk2_user_thread_controller_t* this) {
  funk2_processor_mutex__destroy(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__wait_for_all_user_threads_to_wait(funk2_user_thread_controller_t* this) {
  while (this->waiting_count < memory_pool_num) {
    sched_yield();
  }
}

void funk2_user_thread_controller__user_wait_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_mutex__lock(&(this->waiting_count_mutex));
  this->waiting_count ++;
  funk2_processor_mutex__unlock(&(this->waiting_count_mutex));
  while (this->please_wait) {
    f2__sleep(1);
    sched_yield();
  }
  funk2_processor_mutex__lock(&(this->waiting_count_mutex));
  this->waiting_count --;
  funk2_processor_mutex__unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__user_check_wait_politely(funk2_user_thread_controller_t* this) {
  if (this->please_wait) {
    funk2_user_thread_controller__user_wait_politely(this);
  }
}

