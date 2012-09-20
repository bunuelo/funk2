// 
// Copyright (c) 2007-2008 Bo Morgan.
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

#ifndef F2__SCHEDULER_THREAD_CONTROLLER__H
#define F2__SCHEDULER_THREAD_CONTROLLER__H

typedef struct funk2_scheduler_thread_controller_s {
  pthread_mutex_t need_wait_mutex;
  pthread_cond_t  need_wait_cond;
  boolean_t       need_wait;
  pthread_mutex_t waiting_count_mutex;
  pthread_cond_t  waiting_count_cond;
  s64             waiting_count;
} funk2_scheduler_thread_controller_t;

void funk2_scheduler_thread_controller__init                              (funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__destroy                           (funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__wait_for_scheduler_threads_to_wait(funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__let_scheduler_threads_continue    (funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__user_wait_politely                (funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__check_user_wait_politely          (funk2_scheduler_thread_controller_t* this);
void funk2_scheduler_thread_controller__need_wait__set                    (funk2_scheduler_thread_controller_t* this, boolean_t need_wait);

#endif // F2__SCHEDULER_THREAD_CONTROLLER__H

