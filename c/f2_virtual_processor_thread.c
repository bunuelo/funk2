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

// funk2_virtual_processor_thread

void funk2_virtual_processor_thread__set_cpu_affinity_all(funk2_virtual_processor_thread_t* this) {
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  {
    s64 i;
    for (i = 0; i < __funk2.system_processor.processor_count; i ++) {
      CPU_SET(__funk2.system_processor.processor_affinity_index[i], &cpu_set);
    }
  }
  {
    int result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set);
    if (result != 0) {
      error(nil, "funk2_virtual_processor_thread__set_cpu_affinity_all error: sched_setaffinity");
    }
  }
}

void funk2_virtual_processor_thread__set_cpu_affinity(funk2_virtual_processor_thread_t* this, u64 cpu_index) {
  s64 system_cpu_index = cpu_index % __funk2.system_processor.processor_count;
  cpu_set_t cpu_set;
  CPU_ZERO(&cpu_set);
  CPU_SET(__funk2.system_processor.processor_affinity_index[system_cpu_index], &cpu_set);
  {
    int result = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set);
    if (result != 0) {
      error(nil, "funk2_virtual_processor_thread__set_cpu_affinity_all error: sched_setaffinity");
    }
  }
}

void* funk2_virtual_processor_thread__start_function(void* args) {
  funk2_virtual_processor_thread_t* this = (funk2_virtual_processor_thread_t*)args;
  this->tid = (pid_t)syscall(SYS_gettid);
  while (__funk2.memory.bootstrapping_mode) {
    raw__spin_sleep_yield();
  }
  status("starting virtual_processor_thread.");
  while (! (this->exit)) {
    u64 virtual_processor_assignment_index = -1;
    {
      boolean_t not_assigned_to_virtual_processor = boolean__true;
      while(not_assigned_to_virtual_processor &&
	    (! (this->exit))) {
	{
	  funk2_processor_mutex__lock(&(this->assignment_mutex));
	  virtual_processor_assignment_index = this->virtual_processor_assignment_index;
	  funk2_processor_mutex__unlock(&(this->assignment_mutex));
	}
	not_assigned_to_virtual_processor = (virtual_processor_assignment_index == -1);
	if (not_assigned_to_virtual_processor) {
	  // ****
	  funk2_virtual_processor_thread__pause_myself(this);
	  // ****
	}
	if (__funk2.virtual_processor_handler.hardware_affinities_enabled) {
	  if (this->processor_affinity_index != virtual_processor_assignment_index) {
	    if (virtual_processor_assignment_index == -1) {
	      funk2_virtual_processor_thread__set_cpu_affinity_all(this);
	    } else {
	      funk2_virtual_processor_thread__set_cpu_affinity(this, virtual_processor_assignment_index);
	    }
	  }
	  this->processor_affinity_index = virtual_processor_assignment_index;
	} else {
	  if (this->processor_affinity_index != -1) {
	    funk2_virtual_processor_thread__set_cpu_affinity_all(this);
	    this->processor_affinity_index = -1;
	  }
	}
      }
    }
    if (! (this->exit)) {
      funk2_virtual_processor_t* virtual_processor              = __funk2.virtual_processor_handler.virtual_processor[virtual_processor_assignment_index];
      boolean_t                  we_are_next_in_line_to_execute = boolean__false;
      s64                        assigned_virtual_processor_thread_count;
      s64                        spinning_virtual_processor_thread_count;
      s64                        working_virtual_processor_thread_count;
      {
	funk2_processor_mutex__lock(&(virtual_processor->virtual_processor_thread_count_mutex));
	assigned_virtual_processor_thread_count = virtual_processor->assigned_virtual_processor_thread_count;
	spinning_virtual_processor_thread_count = virtual_processor->spinning_virtual_processor_thread_count;
	funk2_processor_mutex__unlock(&(virtual_processor->virtual_processor_thread_count_mutex));
      }
      working_virtual_processor_thread_count = assigned_virtual_processor_thread_count - spinning_virtual_processor_thread_count;
      s64 line_length = this->virtual_processor_stack_index - working_virtual_processor_thread_count;
      if (line_length <= 1) {
	we_are_next_in_line_to_execute = boolean__true;
      } else if (line_length < 1) {
	status("funk2_virtual_processor_thread__start_function error: line length is less than one.  line_length=" s64__fstr, line_length);
	status("                                                      assigned_virtual_processor_thread_count = " s64__fstr, assigned_virtual_processor_thread_count);
	status("                                                      spinning_virtual_processor_thread_count = " s64__fstr, spinning_virtual_processor_thread_count);
	status("                                                      working_virtual_processor_thread_count  = " s64__fstr, working_virtual_processor_thread_count);
	error(nil, "funk2_virtual_processor_thread__start_function error: line length is less than one.");
      }
      if (we_are_next_in_line_to_execute) {
	boolean_t did_something = boolean__true;
	while (did_something) {
	  did_something = funk2_virtual_processor__execute_next_bytecodes(virtual_processor, this);
	}
	if (! did_something) {
	  // ****
	  funk2_virtual_processor_thread__pause_myself(this);
	  // ****
	}
      } else {	
	//
	// We could unassign virtual_processor_thread from virtual_processor here, but we don't want to very often.
	//
	if ((spinning_virtual_processor_thread_count > 8) &&
	    (line_length == (spinning_virtual_processor_thread_count - 1))) {
	  funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread(virtual_processor);
	  funk2_virtual_processor_thread__unassign_from_virtual_processor(this);
	} else {
	  // ****
	  funk2_virtual_processor_thread__pause_myself(this);
	  // ****
	  //f2__nanosleep((line_length + 1) * (line_length + 1) * deep_sleep_nanoseconds);
	}
	//raw__spin_sleep_yield();
      }
    }
  }
  this->exited = boolean__true;
  return NULL;
}

void funk2_virtual_processor_thread__init(funk2_virtual_processor_thread_t* this) {
  funk2_processor_mutex__init(&(this->assignment_mutex));
  this->tid                                = (pid_t)0;
  this->virtual_processor_assignment_index = -1;
  this->exit                               = boolean__false;
  this->exited                             = boolean__false;
  this->virtual_processor_stack_index      = 0;
  this->processor_affinity_index           = -1;
  this->processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), funk2_virtual_processor_thread__start_function, this);
  this->paused = boolean__false;
  pthread_mutex_init(&(this->pause_cond_mutex), NULL);
  pthread_cond_init(&(this->pause_cond), NULL);
}

void funk2_virtual_processor_thread__destroy(funk2_virtual_processor_thread_t* this) {
  funk2_virtual_processor_thread__exit(this);
  funk2_processor_thread__destroy(this->processor_thread);
  pthread_mutex_destroy(&(this->pause_cond_mutex));
  pthread_cond_destroy(&(this->pause_cond));
}

void funk2_virtual_processor_thread__signal_exit(funk2_virtual_processor_thread_t* this) {
  if (this->paused) {
    funk2_virtual_processor_thread__unpause(this);
  }
  this->exit = boolean__true;
}

void funk2_virtual_processor_thread__finalize_exit(funk2_virtual_processor_thread_t* this) {
  status("funk2_virtual_processor_thread__exit: waiting for virtual_processor_thread to exit.");
  while (! (this->exited)) {
    raw__spin_sleep_yield();
  }
  status("funk2_virtual_processor_thread__exit: virtual_processor_thread exited.");
}

void funk2_virtual_processor_thread__exit(funk2_virtual_processor_thread_t* this) {
  funk2_virtual_processor_thread__signal_exit(this);
  funk2_virtual_processor_thread__finalize_exit(this);
}

void funk2_virtual_processor_thread__pause_myself(funk2_virtual_processor_thread_t* this) {
  this->paused = boolean__true;
  pthread_mutex_lock(&(this->pause_cond_mutex));
  pthread_cond_wait(&(this->pause_cond), &(this->pause_cond_mutex));
  pthread_mutex_unlock(&(this->pause_cond_mutex));
  this->paused = boolean__false;
}

void funk2_virtual_processor_thread__unpause(funk2_virtual_processor_thread_t* this) {
  pthread_mutex_lock(&(this->pause_cond_mutex));
  pthread_cond_signal(&(this->pause_cond));
  pthread_mutex_unlock(&(this->pause_cond_mutex));
}

void funk2_virtual_processor_thread__assign_to_virtual_processor(funk2_virtual_processor_thread_t* this, u64 virtual_processor_assignment_index) {
  funk2_processor_mutex__lock(&(this->assignment_mutex));
  //status("funk2_virtual_processor_thread__assign_to_virtual_processor: virtual_processor_thread assigned to virtual_processor " u64__fstr ".", virtual_processor_assignment_index);
  if (this->virtual_processor_assignment_index != -1) {
    error(nil, "funk2_virtual_processor_thread__assign_to_virtual_processor error: attempted to assign virtual_processor_thread when already assigned.");
  }
  this->virtual_processor_assignment_index = virtual_processor_assignment_index;
  funk2_virtual_processor_handler__know_of_virtual_processor_thread_assignment_to_virtual_processor(&(__funk2.virtual_processor_handler), this, virtual_processor_assignment_index);
  funk2_processor_mutex__unlock(&(this->assignment_mutex));
  if (this->paused) {
    funk2_virtual_processor_thread__unpause(this);
  }
}

void funk2_virtual_processor_thread__unassign_from_virtual_processor(funk2_virtual_processor_thread_t* this) {
  funk2_processor_mutex__lock(&(this->assignment_mutex));
  if (this->virtual_processor_assignment_index == -1) {
    error(nil, "funk2_virtual_processor_thread__unassign_from_virtual_processor error: attempted to unassign virtual_processor_thread when already unassigned.");
  }
  status("funk2_virtual_processor_thread__unassign_from_virtual_processor: virtual_processor_thread unassigned from virtual_processor " u64__fstr ".", this->virtual_processor_assignment_index);
  funk2_virtual_processor_handler__know_of_virtual_processor_thread_unassignment_from_virtual_processor(&(__funk2.virtual_processor_handler), this);
  this->virtual_processor_assignment_index = -1;
  funk2_processor_mutex__unlock(&(this->assignment_mutex));
}
