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

// funk2_user_thread_controller__touch_all_protected_alloc_arrays

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__init(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__signal_execute(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  this->done_count = 0;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
  
  this->start = boolean__true;
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start         = boolean__false;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(funk2_user_thread_controller__touch_all_protected_alloc_arrays_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__touch_all_protected_alloc_arrays(&(__funk2.garbage_collector.gc_pool[pool_index]));
  pthread_mutex_lock(&(this->done_count_mutex));
  this->done_count ++;
  pthread_mutex_unlock(&(this->done_count_mutex));
  pthread_cond_broadcast(&(this->done_count_cond));
  {
    u64 wait_tries = 0;
    while (! (this->everyone_done)) {
      wait_tries ++;
      if (wait_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
}

// funk2_user_thread_controller__blacken_grey_nodes

void funk2_user_thread_controller__blacken_grey_nodes__init(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__blacken_grey_nodes__destroy(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__blacken_grey_nodes__signal_execute(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count > 0) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
  
  this->start = boolean__true;
  
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__blacken_grey_nodes__user_process(funk2_user_thread_controller__blacken_grey_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__blacken_grey_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  pthread_mutex_lock(&(this->done_count_mutex));
  this->done_count ++;
  pthread_mutex_unlock(&(this->done_count_mutex));
  pthread_cond_broadcast(&(this->done_count_cond));
  {
    u64 wait_tries = 0;
    while (! (this->everyone_done)) {
      wait_tries ++;
      if (wait_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
  pthread_mutex_lock(&(this->done_count_mutex));
  this->done_count --;
  pthread_mutex_unlock(&(this->done_count_mutex));
  pthread_cond_broadcast(&(this->done_count_cond));
}

// funk2_user_thread_controller__grey_from_other_nodes

void funk2_user_thread_controller__grey_from_other_nodes__init(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__grey_from_other_nodes__destroy(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__grey_from_other_nodes__signal_execute(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  this->done_count = 0;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done  = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
  
  this->start = boolean__true;
  
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__grey_from_other_nodes__user_process(funk2_user_thread_controller__grey_from_other_nodes_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__grey_from_other_nodes(&(__funk2.garbage_collector.gc_pool[pool_index]));
  pthread_mutex_lock(&(this->done_count_mutex));
  this->done_count ++;
  pthread_mutex_unlock(&(this->done_count_mutex));
  pthread_cond_broadcast(&(this->done_count_cond));
  {
    u64 wait_tries = 0;
    while (! (this->everyone_done)) {
      wait_tries ++;
      if (wait_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
}

// funk2_user_thread_controller__free_white_exps

void funk2_user_thread_controller__free_white_exps__init(funk2_user_thread_controller__free_white_exps_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__free_white_exps__destroy(funk2_user_thread_controller__free_white_exps_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__free_white_exps__signal_execute(funk2_user_thread_controller__free_white_exps_t* this) {
  this->done_count = 0;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done  = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));

  this->start = boolean__true;
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__free_white_exps__user_process(funk2_user_thread_controller__free_white_exps_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_garbage_collector_pool__free_white_exps(&(__funk2.garbage_collector.gc_pool[pool_index]));
  {
    pthread_mutex_lock(&(this->done_count_mutex));
    this->done_count ++;
    pthread_mutex_unlock(&(this->done_count_mutex));
    pthread_cond_broadcast(&(this->done_count_cond));
    {
      u64 wait_tries = 0;
      while (! (this->everyone_done)) {
	wait_tries ++;
	if (wait_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
      }
    }
  }
}


// funk2_user_thread_controller__remove_freed_fibers

void funk2_user_thread_controller__remove_freed_fibers__init(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__remove_freed_fibers__destroy(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__remove_freed_fibers__signal_execute(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  this->done_count = 0;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));

  this->start = boolean__true;
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__remove_freed_fibers__user_process(funk2_user_thread_controller__remove_freed_fibers_t* this) {
  int pool_index = this_processor_thread__pool_index();
  funk2_memorypool__remove_freed_fiber_bytes_freed_counts(&(__funk2.memory.pool[pool_index]));
  {
    pthread_mutex_lock(&(this->done_count_mutex));
    this->done_count ++;
    pthread_mutex_unlock(&(this->done_count_mutex));
    pthread_cond_broadcast(&(this->done_count_cond));
    {
      u64 wait_tries = 0;
      while (! (this->everyone_done)) {
	wait_tries ++;
	if (wait_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
      }
    }
  }
}


// funk2_user_thread_controller__exit

void funk2_user_thread_controller__exit__init(funk2_user_thread_controller__exit_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);
}

void funk2_user_thread_controller__exit__destroy(funk2_user_thread_controller__exit_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__exit__signal_execute(funk2_user_thread_controller__exit_t* this) {
  this->done_count = 0;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));

  this->start = boolean__true;
  
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
}

void funk2_user_thread_controller__exit__user_process(funk2_user_thread_controller__exit_t* this) {
  status("funk2_user_thread_controller__exit__user_process: user exiting.");
  pthread_mutex_lock(&(this->done_count_mutex));
  this->done_count ++;
  pthread_mutex_unlock(&(this->done_count_mutex));
  pthread_cond_broadcast(&(this->done_count_cond));
  funk2_virtual_processor_thread_t* virtual_processor_thread = funk2_virtual_processor_handler__my_virtual_processor_thread(&(__funk2.virtual_processor_handler));
  virtual_processor_thread->exit   = boolean__true;
  virtual_processor_thread->exited = boolean__true;
  pthread_exit(0);
}



// funk2_user_thread_controller__defragment__move_memory

void funk2_user_thread_controller__defragment__move_memory__init(funk2_user_thread_controller__defragment__move_memory_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);

  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      this->user_process_done[index] = boolean__false;
      pthread_mutex_init(&(this->user_process_already_waiting_mutex[index]), NULL);
    }
  }
}

void funk2_user_thread_controller__defragment__move_memory__destroy(funk2_user_thread_controller__defragment__move_memory_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
  
  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      pthread_mutex_destroy(&(this->user_process_already_waiting_mutex[index]));
    }
  }
}

void funk2_user_thread_controller__defragment__move_memory__signal_execute(funk2_user_thread_controller__defragment__move_memory_t* this) {
  this->done_count = 0;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));

  this->start = boolean__true;
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  
  this->start = boolean__false;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
  
  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      this->user_process_done[index] = boolean__false;
    }
  }
}

void funk2_user_thread_controller__defragment__move_memory__user_process(funk2_user_thread_controller__defragment__move_memory_t* this) {
  u64 pool_index = this_processor_thread__pool_index();
  if (pthread_mutex_trylock(&(this->user_process_already_waiting_mutex[pool_index])) == 0) {
    if ((! this->user_process_done[pool_index]) &&
	(! this->everyone_done)) {
      funk2_defragmenter__memory_pool__move_memory(&(__funk2.defragmenter), pool_index);
      
      this->user_process_done[pool_index] = boolean__true;
      pthread_mutex_lock(&(this->done_count_mutex));
      this->done_count ++;
      pthread_mutex_unlock(&(this->done_count_mutex));
      pthread_cond_broadcast(&(this->done_count_cond));
    }
    pthread_mutex_unlock(&(this->user_process_already_waiting_mutex[pool_index]));
  } else {
    raw__spin_sleep_yield();
  }
}



// funk2_user_thread_controller__defragment__fix_pointers

void funk2_user_thread_controller__defragment__fix_pointers__init(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  this->start = boolean__false;
  pthread_mutex_init(&(this->done_count_mutex), NULL);
  pthread_cond_init(&(this->done_count_cond), NULL);
  pthread_mutex_init(&(this->everyone_done_mutex), NULL);
  pthread_cond_init(&(this->everyone_done_cond), NULL);

  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      this->user_process_done[index] = boolean__false;
      pthread_mutex_init(&(this->user_process_already_waiting_mutex[index]), NULL);
    }
  }
}

void funk2_user_thread_controller__defragment__fix_pointers__destroy(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  pthread_mutex_destroy(&(this->done_count_mutex));
  pthread_cond_destroy(&(this->done_count_cond));
  pthread_mutex_destroy(&(this->everyone_done_mutex));
  pthread_cond_destroy(&(this->everyone_done_cond));
  
  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      pthread_mutex_destroy(&(this->user_process_already_waiting_mutex[index]));
    }
  }
}

void funk2_user_thread_controller__defragment__fix_pointers__signal_execute(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  this->done_count = 0;

  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done  = boolean__false;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));

  this->start = boolean__true;
  
  pthread_mutex_lock(&(this->done_count_mutex));
  {
    while (this->done_count < memory_pool_num) {
      pthread_cond_wait(&(this->done_count_cond), &(this->done_count_mutex));
    }
  }
  pthread_mutex_unlock(&(this->done_count_mutex));
  this->start         = boolean__false;
  
  pthread_mutex_lock(&(this->everyone_done_mutex));
  this->everyone_done = boolean__true;
  pthread_mutex_unlock(&(this->everyone_done_mutex));
  pthread_cond_broadcast(&(this->everyone_done_cond));
  
  {
    s64 index;
    for (index = 0; index < memory_pool_num; index ++) {
      this->user_process_done[index] = boolean__false;
    }
  }
}

void funk2_user_thread_controller__defragment__fix_pointers__user_process(funk2_user_thread_controller__defragment__fix_pointers_t* this) {
  u64 pool_index = this_processor_thread__pool_index();
  if (pthread_mutex_trylock(&(this->user_process_already_waiting_mutex[pool_index])) == 0) {
    if ((! this->user_process_done[pool_index]) &&
	(! this->everyone_done)) {
      funk2_defragmenter__memory_pool__fix_pointers(&(__funk2.defragmenter), pool_index);
      
      this->user_process_done[pool_index] = boolean__true;
      pthread_mutex_lock(&(this->done_count_mutex));
      this->done_count ++;
      pthread_mutex_unlock(&(this->done_count_mutex));
      pthread_cond_broadcast(&(this->done_count_cond));
    }
    pthread_mutex_unlock(&(this->user_process_already_waiting_mutex[pool_index]));
  } else {
    raw__spin_sleep_yield();
  }
}



// funk2_user_thread_controller

void funk2_user_thread_controller__init(funk2_user_thread_controller_t* this) {
  this->please_wait   = boolean__false;
  this->waiting_count = 0;
  pthread_mutex_init(&(this->waiting_count_mutex), NULL);
  
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
  pthread_mutex_destroy(&(this->waiting_count_mutex));
  
  funk2_user_thread_controller__touch_all_protected_alloc_arrays__destroy(&(this->touch_all_protected_alloc_arrays));
  funk2_user_thread_controller__blacken_grey_nodes__destroy(&(this->blacken_grey_nodes));
  funk2_user_thread_controller__grey_from_other_nodes__destroy(&(this->grey_from_other_nodes));
  funk2_user_thread_controller__free_white_exps__destroy(&(this->free_white_exps));
  funk2_user_thread_controller__remove_freed_fibers__destroy(&(this->remove_freed_fibers));
  funk2_user_thread_controller__exit__destroy(&(this->exit));
  funk2_user_thread_controller__defragment__move_memory__destroy(&(this->defragment__move_memory));
  funk2_user_thread_controller__defragment__fix_pointers__destroy(&(this->defragment__fix_pointers));
}

void funk2_user_thread_controller__wait_for_all_user_threads_to_wait(funk2_user_thread_controller_t* this) {
  {
    u64 wait_tries = 0;
    while (this->waiting_count < memory_pool_num) {
      wait_tries ++;
      if (wait_tries > 1000) {
	raw__spin_sleep_yield();
      } else {
	raw__fast_spin_sleep_yield();
      }
    }
  }
}

void funk2_user_thread_controller__signal_user_waiting_politely(funk2_user_thread_controller_t* this) {
  pthread_mutex_lock(&(this->waiting_count_mutex));
  this->waiting_count ++;
  pthread_mutex_unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__signal_user_done_waiting_politely(funk2_user_thread_controller_t* this) {
  pthread_mutex_lock(&(this->waiting_count_mutex));
  this->waiting_count --;
  pthread_mutex_unlock(&(this->waiting_count_mutex));
}

void funk2_user_thread_controller__user_wait_politely(funk2_user_thread_controller_t* this) {
  funk2_user_thread_controller__signal_user_waiting_politely(this);
  {
    u64 wait_tries = 0;
    while (this->please_wait || pthread_mutex_trylock(&(this->waiting_count_mutex))) {
      if                   (this->touch_all_protected_alloc_arrays.start) {funk2_user_thread_controller__touch_all_protected_alloc_arrays__user_process(&(this->touch_all_protected_alloc_arrays));}
      else if                            (this->blacken_grey_nodes.start) {funk2_user_thread_controller__blacken_grey_nodes__user_process(              &(this->blacken_grey_nodes));}
      else if                         (this->grey_from_other_nodes.start) {funk2_user_thread_controller__grey_from_other_nodes__user_process(           &(this->grey_from_other_nodes));}
      else if                               (this->free_white_exps.start) {funk2_user_thread_controller__free_white_exps__user_process(                 &(this->free_white_exps));}
      else if                           (this->remove_freed_fibers.start) {funk2_user_thread_controller__remove_freed_fibers__user_process(             &(this->remove_freed_fibers));}
      else if                                          (this->exit.start) {funk2_user_thread_controller__exit__user_process(                            &(this->exit));}
      else if                       (this->defragment__move_memory.start) {funk2_user_thread_controller__defragment__move_memory__user_process(         &(this->defragment__move_memory));}
      else if                      (this->defragment__fix_pointers.start) {funk2_user_thread_controller__defragment__fix_pointers__user_process(        &(this->defragment__fix_pointers));}
      {
	wait_tries ++;
	if (wait_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
      }
    }
  }
  this->waiting_count --;
  pthread_mutex_unlock(&(this->waiting_count_mutex));
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


