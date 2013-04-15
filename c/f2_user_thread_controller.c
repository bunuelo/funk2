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

// funk2_user_thread_controller__touch_all_protected_alloc_arrays

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__touch_all_protected_alloc_arrays(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
  this->done_count ++;
  funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
  
  funk2_processor_conditionlock__wait_while(! (this->everyone_done), &(this->everyone_done_conditionlock));
}

// funk2_user_thread_controller__blacken_grey_nodes

void funk2_user_thread_controller__blacken_grey_nodes__init(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__blacken_grey_nodes__destroy(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__blacken_grey_nodes__signal_execute(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  
  funk2_processor_conditionlock__wait_while(this->done_count > 0, &(this->done_count_conditionlock));
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__blacken_grey_nodes__user_process(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__blacken_grey_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
  this->done_count ++;
  funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
  
  funk2_processor_conditionlock__wait_while(! (this->everyone_done), &(this->everyone_done_conditionlock));
  
  funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
  this->done_count --;
  funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
}

// funk2_user_thread_controller__grey_from_other_nodes

void funk2_user_thread_controller__grey_from_other_nodes__init(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__grey_from_other_nodes__destroy(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__grey_from_other_nodes__signal_execute(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done  = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__grey_from_other_nodes__user_process(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__grey_from_other_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
  this->done_count ++;
  funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
  
  funk2_processor_conditionlock__wait_while(! (this->everyone_done), &(this->everyone_done_conditionlock));
}

// funk2_user_thread_controller__free_white_exps

void funk2_user_thread_controller__free_white_exps__init(funk2_user_thread_controller__free_white_exps_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__free_white_exps__destroy(funk2_user_thread_controller__free_white_exps_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__free_white_exps__signal_execute(funk2_user_thread_controller__free_white_exps_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done  = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__free_white_exps__user_process(funk2_user_thread_controller__free_white_exps_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__free_white_exps(&(__funk2.garbage_collector.gc_pool[pool_index]));
  {
    funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
    this->done_count ++;
    funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
    funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
    
    funk2_processor_conditionlock__wait_while(! (this->everyone_done), &(this->everyone_done_conditionlock));
  }
}


// funk2_user_thread_controller__remove_freed_fibers

void funk2_user_thread_controller__remove_freed_fibers__init(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__remove_freed_fibers__destroy(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__remove_freed_fibers__signal_execute(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__remove_freed_fibers__user_process(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__remove_freed_fiber_bytes_freed_counts(&(__funk2.memory.pool[pool_index]));
  {
    funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
    this->done_count ++;
    funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
    funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
    
    funk2_processor_conditionlock__wait_while(! (this->everyone_done), &(this->everyone_done_conditionlock));
  }
}


// funk2_user_thread_controller__exit

void funk2_user_thread_controller__exit__init(funk2_user_thread_controller__exit_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__exit__destroy(funk2_user_thread_controller__exit_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__exit__signal_execute(funk2_user_thread_controller__exit_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
}

void funk2_user_thread_controller__exit__user_process(funk2_user_thread_controller__exit_t* this) {
  status("funk2_user_thread_controller__exit__user_process: user exiting.");
  funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
  this->done_count ++;
  funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
  funk2_virtual_processor_thread_t* virtual_processor_thread = funk2_virtual_processor_handler__my_virtual_processor_thread(&(__funk2.virtual_processor_handler));
  virtual_processor_thread->exit   = boolean__true;
  virtual_processor_thread->exited = boolean__true;
  pthread_exit(0);
}



// funk2_user_thread_controller__defragment__move_memory

void funk2_user_thread_controller__defragment__move_memory__init(funk2_user_thread_controller__defragment__move_memory_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
  
  this->user_process_done                  = (boolean_t*)              from_ptr(f2__malloc(sizeof(boolean_t)               * __funk2.system_processor.processor_count));
  this->user_process_already_waiting_mutex = (funk2_processor_mutex_t*)from_ptr(f2__malloc(sizeof(funk2_processor_mutex_t) * __funk2.system_processor.processor_count));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      this->user_process_done[index] = boolean__false;
      funk2_processor_mutex__init(&(this->user_process_already_waiting_mutex[index]));
    }
  }
}

void funk2_user_thread_controller__defragment__move_memory__destroy(funk2_user_thread_controller__defragment__move_memory_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      funk2_processor_mutex__destroy(&(this->user_process_already_waiting_mutex[index]));
    }
  }
  
  f2__free(to_ptr(this->user_process_done));
  f2__free(to_ptr(this->user_process_already_waiting_mutex));
}

void funk2_user_thread_controller__defragment__move_memory__signal_execute(funk2_user_thread_controller__defragment__move_memory_t* this) {
  this->done_count = 0;

  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      this->user_process_done[index] = boolean__false;
    }
  }
}

void funk2_user_thread_controller__defragment__move_memory__user_process(funk2_user_thread_controller__defragment__move_memory_t* this) {
  u64 pool_index = this_processor_thread__pool_index();
  if (funk2_processor_mutex__trylock(&(this->user_process_already_waiting_mutex[pool_index])) == 0) {
    if ((! this->user_process_done[pool_index]) &&
	(! this->everyone_done)) {
      funk2_defragmenter__memory_pool__move_memory(&(__funk2.defragmenter), pool_index);
      
      this->user_process_done[pool_index] = boolean__true;
      funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
      this->done_count ++;
      funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
      funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
    }
    funk2_processor_mutex__unlock(&(this->user_process_already_waiting_mutex[pool_index]));
  } else {
    raw__nanosleep(1000000);
  }
}



// funk2_user_thread_controller__defragment__fix_pointers

void funk2_user_thread_controller__defragment__fix_pointers__init(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  this->start = boolean__false;
  funk2_processor_conditionlock__init(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__init(&(this->everyone_done_conditionlock));
  
  this->user_process_done                  = (boolean_t*)              from_ptr(f2__malloc(sizeof(boolean_t)               * __funk2.system_processor.processor_count));
  this->user_process_already_waiting_mutex = (funk2_processor_mutex_t*)from_ptr(f2__malloc(sizeof(funk2_processor_mutex_t) * __funk2.system_processor.processor_count));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      this->user_process_done[index] = boolean__false;
      funk2_processor_mutex__init(&(this->user_process_already_waiting_mutex[index]));
    }
  }
}

void funk2_user_thread_controller__defragment__fix_pointers__destroy(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  funk2_processor_conditionlock__destroy(&(this->done_count_conditionlock));
  funk2_processor_conditionlock__destroy(&(this->everyone_done_conditionlock));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      funk2_processor_mutex__destroy(&(this->user_process_already_waiting_mutex[index]));
    }
  }
  
  f2__free(to_ptr(this->user_process_done));
  f2__free(to_ptr(this->user_process_already_waiting_mutex));
}

void funk2_user_thread_controller__defragment__fix_pointers__signal_execute(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  this->done_count = 0;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done  = boolean__false;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  this->start = boolean__true;
  funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(&(__funk2.user_thread_controller));
  
  funk2_processor_conditionlock__wait_while(this->done_count < __funk2.system_processor.processor_count, &(this->done_count_conditionlock));
  
  this->start = boolean__false;
  
  funk2_processor_conditionlock__lock(&(this->everyone_done_conditionlock));
  this->everyone_done = boolean__true;
  funk2_processor_conditionlock__broadcast(&(this->everyone_done_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->everyone_done_conditionlock));
  
  {
    s64 index;
    for (index = 0; index < __funk2.system_processor.processor_count; index ++) {
      this->user_process_done[index] = boolean__false;
    }
  }
}

void funk2_user_thread_controller__defragment__fix_pointers__user_process(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  u64 pool_index = this_processor_thread__pool_index();
  if (funk2_processor_mutex__trylock(&(this->user_process_already_waiting_mutex[pool_index])) == 0) {
    if ((! this->user_process_done[pool_index]) &&
	(! this->everyone_done)) {
      funk2_defragmenter__memory_pool__fix_pointers(&(__funk2.defragmenter), pool_index);
      
      this->user_process_done[pool_index] = boolean__true;
      funk2_processor_conditionlock__lock(&(this->done_count_conditionlock));
      this->done_count ++;
      funk2_processor_conditionlock__broadcast(&(this->done_count_conditionlock));
      funk2_processor_conditionlock__unlock(&(this->done_count_conditionlock));
    }
    funk2_processor_mutex__unlock(&(this->user_process_already_waiting_mutex[pool_index]));
  } else {
    raw__nanosleep(1000000);
  }
}



// funk2_user_thread_controller

void funk2_user_thread_controller__init(funk2_user_thread_controller_t* this) {
  this->need_wait   = boolean__false;
  
  funk2_processor_conditionlock__init(&(this->waiting_count_conditionlock));
  this->waiting_count = 0;
  
  this->total_nanoseconds_spent_waiting = (u64*)from_ptr(f2__malloc(sizeof(u64) * __funk2.system_processor.processor_count));
  
  {
    int pool_index;
    for (pool_index = 0; pool_index < __funk2.system_processor.processor_count; pool_index ++) {
      this->total_nanoseconds_spent_waiting[pool_index] = 0;
    }
  }
  
  funk2_processor_conditionlock__init(&(this->something_to_do_while_waiting_politely_conditionlock));
  
  funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(&(this->touch_all_protected_alloc_arrays));
  funk2_user_thread_controller__blacken_grey_nodes__init(&(this->blacken_grey_nodes));
  funk2_user_thread_controller__grey_from_other_nodes__init(&(this->grey_from_other_nodes));
  funk2_user_thread_controller__free_white_exps__init(&(this->free_white_exps));
  funk2_user_thread_controller__remove_freed_fibers__init(&(this->remove_freed_fibers));
  funk2_user_thread_controller__exit__init(&(this->exit));
  funk2_user_thread_controller__defragment__move_memory__init(&(this->defragment__move_memory));
  funk2_user_thread_controller__defragment__fix_pointers__init(&(this->defragment__fix_pointers));
}

void funk2_user_thread_controller__destroy(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__destroy(&(this->waiting_count_conditionlock));
  
  funk2_processor_conditionlock__destroy(&(this->something_to_do_while_waiting_politely_conditionlock));
  
  funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(&(this->touch_all_protected_alloc_arrays));
  funk2_user_thread_controller__blacken_grey_nodes__destroy(&(this->blacken_grey_nodes));
  funk2_user_thread_controller__grey_from_other_nodes__destroy(&(this->grey_from_other_nodes));
  funk2_user_thread_controller__free_white_exps__destroy(&(this->free_white_exps));
  funk2_user_thread_controller__remove_freed_fibers__destroy(&(this->remove_freed_fibers));
  funk2_user_thread_controller__exit__destroy(&(this->exit));
  funk2_user_thread_controller__defragment__move_memory__destroy(&(this->defragment__move_memory));
  funk2_user_thread_controller__defragment__fix_pointers__destroy(&(this->defragment__fix_pointers));
  
  f2__free(to_ptr(this->total_nanoseconds_spent_waiting));
}

void funk2_user_thread_controller__wait_for_all_user_threads_to_wait(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__wait_while(this->waiting_count < __funk2.system_processor.processor_count, &(this->waiting_count_conditionlock));
}

void funk2_user_thread_controller__signal_user_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  this->waiting_count ++;
  funk2_processor_conditionlock__broadcast(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
}

void funk2_user_thread_controller__signal_user_done_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  this->waiting_count --;
  funk2_processor_conditionlock__broadcast(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
}

void funk2_user_thread_controller__user_wait_politely(funk2_user_thread_controller_t* this) {
  u64 pool_index                           = this_processor_thread__pool_index();
  u64 start_waiting_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  funk2_user_thread_controller__signal_user_waiting_politely(this);
  
  {
    funk2_poller_t poller;
    boolean_t      poller_initialized = boolean__false;
    s64            wait_tries         = 0;
    while (this->need_wait) {
      if (funk2_processor_conditionlock__trylock(&(this->something_to_do_while_waiting_politely_conditionlock)) == 0) {
	while (this->need_wait                                  &&
	       (! (this->touch_all_protected_alloc_arrays.start ||
		   this->blacken_grey_nodes.start               ||
		   this->grey_from_other_nodes.start            ||
		   this->free_white_exps.start                  ||
		   this->remove_freed_fibers.start              ||
		   this->exit.start                             ||
		   this->defragment__move_memory.start          ||
		   this->defragment__fix_pointers.start))) {
	  funk2_processor_conditionlock__wait(&(this->something_to_do_while_waiting_politely_conditionlock));
	}
	funk2_processor_conditionlock__unlock(&(this->something_to_do_while_waiting_politely_conditionlock));
      } else {
	if (wait_tries < 1000) {
	  wait_tries ++;
	  raw__fast_spin_sleep_yield();
	} else {
	  if (! poller_initialized) {
	    funk2_poller__init(&poller, poller__deep_sleep_percentage, poller__deep_sleep_average_length);
	    funk2_poller__reset(&poller);
	    poller_initialized = boolean__true;
	  } else {
	    funk2_poller__sleep(&poller);
	  }
	}
      }
      
      if      (this->touch_all_protected_alloc_arrays.start) {funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(&(this->touch_all_protected_alloc_arrays));}
      else if (this->blacken_grey_nodes.start)               {funk2_user_thread_controller__blacken_grey_nodes__user_process(              &(this->blacken_grey_nodes));}
      else if (this->grey_from_other_nodes.start)            {funk2_user_thread_controller__grey_from_other_nodes__user_process(           &(this->grey_from_other_nodes));}
      else if (this->free_white_exps.start)                  {funk2_user_thread_controller__free_white_exps__user_process(                 &(this->free_white_exps));}
      else if (this->remove_freed_fibers.start)              {funk2_user_thread_controller__remove_freed_fibers__user_process(             &(this->remove_freed_fibers));}
      else if (this->exit.start)                             {funk2_user_thread_controller__exit__user_process(                            &(this->exit));}
      else if (this->defragment__move_memory.start)          {funk2_user_thread_controller__defragment__move_memory__user_process(         &(this->defragment__move_memory));}
      else if (this->defragment__fix_pointers.start)         {funk2_user_thread_controller__defragment__fix_pointers__user_process(        &(this->defragment__fix_pointers));}
    }
    if (poller_initialized) {
      funk2_poller__destroy(&poller);
    }
  }
  
  funk2_processor_conditionlock__lock(&(this->waiting_count_conditionlock));
  this->waiting_count --;
  funk2_processor_conditionlock__broadcast(&(this->waiting_count_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->waiting_count_conditionlock));
  this->total_nanoseconds_spent_waiting[pool_index] += (raw__nanoseconds_since_1970() - start_waiting_nanoseconds_since_1970);
}

void funk2_user_thread_controller__user_check_wait_politely(funk2_user_thread_controller_t* this) {
  if (this->need_wait) {
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

void funk2_user_thread_controller__remove_freed_fibers(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__remove_freed_fibers__signal_execute(&(this->remove_freed_fibers));
}

void funk2_user_thread_controller__exit(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__exit__signal_execute(&(this->exit));
}

void funk2_user_thread_controller__defragment__move_memory(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__defragment__move_memory__signal_execute(&(this->defragment__move_memory));
}

void funk2_user_thread_controller__defragment__fix_pointers(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__defragment__fix_pointers__signal_execute(&(this->defragment__fix_pointers));
}

void funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__lock(&(this->something_to_do_while_waiting_politely_conditionlock));
}

void funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(funk2_user_thread_controller_t* this) {
  funk2_processor_conditionlock__broadcast(&(this->something_to_do_while_waiting_politely_conditionlock));
  funk2_processor_conditionlock__unlock(&(this->something_to_do_while_waiting_politely_conditionlock));
}

void funk2_user_thread_controller__need_wait__set(funk2_user_thread_controller_t* this, boolean_t need_wait) {
  if (! need_wait) {
    funk2_user_thread_controller__begin_signal_something_to_do_while_waiting_politely(this);
    this->need_wait = boolean__false;
    funk2_user_thread_controller__end_signal_something_to_do_while_waiting_politely(this);
  } else {
    this->need_wait = boolean__true;
  }
}


s64 funk2_user_thread_controller__total_processor_time_used(funk2_user_thread_controller_t* this, s64 processor_index) {
  return this->total_nanoseconds_spent_waiting[processor_index];
}

u64 raw__user_thread_controller__total_processor_time_used(f2ptr cause, s64 processor_index) {
  return funk2_user_thread_controller__total_processor_time_used(&(__funk2.user_thread_controller), processor_index);
}

f2ptr f2__user_thread_controller__total_processor_time_used(f2ptr cause, f2ptr processor_index) {
  assert_argument_type(integer, processor_index);
  s64 processor_index__i = f2integer__i(processor_index, cause);
  if ((processor_index__i < 0) || (processor_index__i >= __funk2.system_processor.processor_count)) {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"),        new__symbol(cause, "user_thread_controller-total_processor_time_used-processor_index_out_of_range"),
				   new__symbol(cause, "processor_index"), processor_index));
  }
  return f2integer__new(cause, raw__user_thread_controller__total_processor_time_used(cause, processor_index__i));
}
def_pcfunk1(user_thread_controller__total_processor_time_used, processor_index,
	    "",
	    return f2__user_thread_controller__total_processor_time_used(this_cause, processor_index));


// **

void f2__user_thread_controller__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(user_thread_controller__total_processor_time_used);
}

void f2__user_thread_controller__reinitialize_globalvars() {
  f2__primcfunk__init__0(user_thread_controller__total_processor_time_used);
}

void f2__user_thread_controller__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "user_thread_controller", "", &f2__user_thread_controller__reinitialize_globalvars, &f2__user_thread_controller__defragment__fix_pointers);
  
  f2__user_thread_controller__reinitialize_globalvars();
}

