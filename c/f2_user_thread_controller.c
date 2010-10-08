// 
// Copyright (c) 2007-2010 Bo Morgan.
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

// funk2_user_thread_controller__touch_all_protected_alloc_arrays

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->start = boolean__false;
  funk2_processor_mutex__init(&(this->done_mutex));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->done_count     = 0;
  this->everyone_done  = boolean__false;
  this->start          = boolean__true;
  while (this->done_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
  this->start         = boolean__false;
  this->everyone_done = boolean__true;
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__touch_all_protected_alloc_arrays(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count ++;
  funk2_processor_mutex__unlock(&(this->done_mutex));
  while (! (this->everyone_done)) {
    raw__fast_spin_sleep_yield();
  }
}

// funk2_user_thread_controller__blacken_grey_nodes

void funk2_user_thread_controller__blacken_grey_nodes__init(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  this->start = boolean__false;
  funk2_processor_mutex__init(&(this->done_mutex));
}

void funk2_user_thread_controller__blacken_grey_nodes__destroy(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
}

void funk2_user_thread_controller__blacken_grey_nodes__signal_execute(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  while (this->done_count > 0) {
    raw__fast_spin_sleep_yield();
  }
  this->everyone_done  = boolean__false;
  this->start          = boolean__true;
  while (this->done_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
  this->start         = boolean__false;
  this->everyone_done = boolean__true;
}

void funk2_user_thread_controller__blacken_grey_nodes__user_process(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__blacken_grey_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count ++;
  funk2_processor_mutex__unlock(&(this->done_mutex));
  while (! (this->everyone_done)) {
    raw__fast_spin_sleep_yield();
  }
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count --;
  funk2_processor_mutex__unlock(&(this->done_mutex));
}

// funk2_user_thread_controller__grey_from_other_nodes

void funk2_user_thread_controller__grey_from_other_nodes__init(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->start = boolean__false;
  funk2_processor_mutex__init(&(this->done_mutex));
}

void funk2_user_thread_controller__grey_from_other_nodes__destroy(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
}

void funk2_user_thread_controller__grey_from_other_nodes__signal_execute(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->done_count     = 0;
  this->everyone_done  = boolean__false;
  this->start          = boolean__true;
  while (this->done_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
  this->start         = boolean__false;
  this->everyone_done = boolean__true;
}

void funk2_user_thread_controller__grey_from_other_nodes__user_process(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__grey_from_other_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count ++;
  funk2_processor_mutex__unlock(&(this->done_mutex));
  while (! (this->everyone_done)) {
    raw__fast_spin_sleep_yield();
  }
}

// funk2_user_thread_controller__free_white_exps

void funk2_user_thread_controller__free_white_exps__init(funk2_user_thread_controller__free_white_exps_t* this) {
  this->start = boolean__false;
  funk2_processor_mutex__init(&(this->done_mutex));
}

void funk2_user_thread_controller__free_white_exps__destroy(funk2_user_thread_controller__free_white_exps_t* this) {
}

void funk2_user_thread_controller__free_white_exps__signal_execute(funk2_user_thread_controller__free_white_exps_t* this) {
  this->done_count     = 0;
  this->everyone_done  = boolean__false;
  this->start          = boolean__true;
  while (this->done_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
  this->start         = boolean__false;
  this->everyone_done = boolean__true;
}

void funk2_user_thread_controller__free_white_exps__user_process(funk2_user_thread_controller__free_white_exps_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__free_white_exps(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count ++;
  funk2_processor_mutex__unlock(&(this->done_mutex));
  while (! (this->everyone_done)) {
    raw__fast_spin_sleep_yield();
  }
}


// funk2_user_thread_controller__exit

void funk2_user_thread_controller__exit__init(funk2_user_thread_controller__exit_t* this) {
  this->start = boolean__false;
  funk2_processor_mutex__init(&(this->done_mutex));
}

void funk2_user_thread_controller__exit__destroy(funk2_user_thread_controller__exit_t* this) {
}

void funk2_user_thread_controller__exit__signal_execute(funk2_user_thread_controller__exit_t* this) {
  this->done_count     = 0;
  this->everyone_done  = boolean__false;
  this->start          = boolean__true;
  while (this->done_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
  this->start         = boolean__false;
  this->everyone_done = boolean__true;
}

void funk2_user_thread_controller__exit__user_process(funk2_user_thread_controller__exit_t* this) {
  status("funk2_user_thread_controller__exit__user_process: user exiting.");
  funk2_processor_mutex__lock(&(this->done_mutex));
  this->done_count ++;
  funk2_processor_mutex__unlock(&(this->done_mutex));
  funk2_virtual_processor_thread_t* virtual_processor_thread = funk2_virtual_processor_handler__my_virtual_processor_thread(&(__funk2.virtual_processor_handler));
  virtual_processor_thread->exit   = boolean__true;
  virtual_processor_thread->exited = boolean__true;
  pthread_exit(0);
}



// funk2_user_thread_controller

void funk2_user_thread_controller__init(funk2_user_thread_controller_t* this) {
  this->please_wait   = boolean__false;
  this->waiting_count = 0;
  funk2_processor_mutex__init(&(this->waiting_count_mutex));

  funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(&(this->touch_all_protected_alloc_arrays));
  funk2_user_thread_controller__blacken_grey_nodes__init(&(this->blacken_grey_nodes));
  funk2_user_thread_controller__grey_from_other_nodes__init(&(this->grey_from_other_nodes));
  funk2_user_thread_controller__free_white_exps__init(&(this->free_white_exps));
  funk2_user_thread_controller__exit__init(&(this->exit));
}

void funk2_user_thread_controller__destroy(funk2_user_thread_controller_t* this) {
  funk2_processor_mutex__destroy(&(this->waiting_count_mutex));
  
  funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(&(this->touch_all_protected_alloc_arrays));
  funk2_user_thread_controller__blacken_grey_nodes__destroy(&(this->blacken_grey_nodes));
  funk2_user_thread_controller__grey_from_other_nodes__destroy(&(this->grey_from_other_nodes));
  funk2_user_thread_controller__free_white_exps__destroy(&(this->free_white_exps));
  funk2_user_thread_controller__exit__destroy(&(this->exit));
}

void funk2_user_thread_controller__wait_for_all_user_threads_to_wait(funk2_user_thread_controller_t* this) {
  while (this->waiting_count < memory_pool_num) {
    raw__fast_spin_sleep_yield();
  }
}

void funk2_user_thread_controller__signal_user_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_mutex__lock(&(this->waiting_count_mutex));
  this->waiting_count ++;
  funk2_processor_mutex__unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__signal_user_done_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_mutex__lock(&(this->waiting_count_mutex));
  this->waiting_count --;
  funk2_processor_mutex__unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__user_wait_politely(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__signal_user_waiting_politely(this);
  while (this->please_wait || funk2_processor_mutex__trylock(&(this->waiting_count_mutex))) {
    if                   (this->touch_all_protected_alloc_arrays.start) {funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(&(this->touch_all_protected_alloc_arrays));}
    else if                            (this->blacken_grey_nodes.start) {funk2_user_thread_controller__blacken_grey_nodes__user_process(              &(this->blacken_grey_nodes));}
    else if                         (this->grey_from_other_nodes.start) {funk2_user_thread_controller__grey_from_other_nodes__user_process(           &(this->grey_from_other_nodes));}
    else if                               (this->free_white_exps.start) {funk2_user_thread_controller__free_white_exps__user_process(                 &(this->free_white_exps));}
    else if                                          (this->exit.start) {funk2_user_thread_controller__exit__user_process(                            &(this->exit));}
    raw__fast_spin_sleep_yield();
  }
  this->waiting_count --;
  funk2_processor_mutex__unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__user_check_wait_politely(funk2_user_thread_controller_t* this) {
  if (this->please_wait) {
    funk2_user_thread_controller__user_wait_politely(this);
  }
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(&(this->touch_all_protected_alloc_arrays));
}

void funk2_user_thread_controller__blacken_grey_nodes(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__blacken_grey_nodes__signal_execute(&(this->blacken_grey_nodes));
}

void funk2_user_thread_controller__grey_from_other_nodes(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__grey_from_other_nodes__signal_execute(&(this->grey_from_other_nodes));
}

void funk2_user_thread_controller__free_white_exps(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__free_white_exps__signal_execute(&(this->free_white_exps));
}

void funk2_user_thread_controller__exit(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__exit__signal_execute(&(this->exit));
}


