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

// funk2_virtual_processor

void funk2_virtual_processor__init(funk2_virtual_processor_t* this, u64 index) {
  this->index = index;
  funk2_processor_mutex__init(&(this->execute_bytecodes_mutex));
  {
    funk2_processor_mutex__init(&(this->virtual_processor_thread_count_mutex));
    this->assigned_virtual_processor_thread_count = 0;
    this->spinning_virtual_processor_thread_count = 0;
  }
  {
    funk2_processor_mutex__init(&(this->virtual_processor_thread_stack_mutex));
    this->virtual_processor_thread_stack = NULL;
  }
  // start running at least one thread.
  funk2_virtual_processor__assure_at_least_one_spinning_virtual_processor_thread(this);
}

void funk2_virtual_processor__destroy(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__destroy(&(this->execute_bytecodes_mutex));
  funk2_processor_mutex__destroy(&(this->virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__assure_at_least_one_spinning_virtual_processor_thread(funk2_virtual_processor_t* this) {
  s64 spinning_virtual_processor_thread_count;
  {
    funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
    spinning_virtual_processor_thread_count = this->spinning_virtual_processor_thread_count;
    funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
  }
  while (spinning_virtual_processor_thread_count < 1) {
    //status("funk2_virtual_processor__assure_at_least_one_spinning_virtual_processor_thread: assigning free virtual_processor_thread to virtual_processor (" u64__fstr ")", this->index);
    funk2_virtual_processor_thread_t* virtual_processor_thread = funk2_virtual_processor_handler__get_free_virtual_processor_thread(&(__funk2.virtual_processor_handler));
    funk2_virtual_processor_thread__assign_to_virtual_processor(virtual_processor_thread, this->index);
    funk2_virtual_processor__know_of_one_more_spinning_virtual_processor_thread(this);
    {
      funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
      spinning_virtual_processor_thread_count = this->spinning_virtual_processor_thread_count;
      funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
    }
    {
      funk2_virtual_processor_thread_cons_t* cons = (funk2_virtual_processor_thread_cons_t*)from_ptr(f2__malloc(sizeof(funk2_virtual_processor_thread_cons_t)));
      cons->virtual_processor_thread = virtual_processor_thread;
      u64 current_virtual_processor_stack_index = 0;
      {
	funk2_processor_mutex__lock(&(this->virtual_processor_thread_stack_mutex));
	if (this->virtual_processor_thread_stack) {
	  current_virtual_processor_stack_index = this->virtual_processor_thread_stack->virtual_processor_thread->virtual_processor_stack_index;
	}
	cons->next                           = this->virtual_processor_thread_stack;
	this->virtual_processor_thread_stack = cons;
	funk2_processor_mutex__unlock(&(this->virtual_processor_thread_stack_mutex));
      }
      virtual_processor_thread->virtual_processor_stack_index = current_virtual_processor_stack_index + 1;
    }
  }
}

boolean_t funk2_virtual_processor__already_executing_next_bytecodes(funk2_virtual_processor_t* this) {
  return funk2_processor_mutex__is_locked(&(this->execute_bytecodes_mutex));
}

boolean_t funk2_virtual_processor__execute_next_bytecodes(funk2_virtual_processor_t* this, funk2_virtual_processor_thread_t* virtual_processor_thread) {
  boolean_t did_something = boolean__false;
  boolean_t locked_mutex  = boolean__false;
  {
    u64 lock_tries = 0;
    while ((! locked_mutex) &&
	   (! (virtual_processor_thread->exit))) {
      if (funk2_processor_mutex__trylock(&(this->execute_bytecodes_mutex)) == 0) {
	locked_mutex = boolean__true;
      }
      if (! locked_mutex) {
	lock_tries ++;
	if ((lock_tries > 1000) ||
	    __funk2.scheduler_thread_controller.please_wait ||
	    __funk2.user_thread_controller.please_wait) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
      }
    }
  }
  if (! (virtual_processor_thread->exit)) {
    funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread(this);
    this->execute_bytecodes_current_virtual_processor_thread = virtual_processor_thread;
    f2ptr cause      = nil;
    f2ptr processors = f2scheduler__processors(__funk2.operating_system.scheduler, cause);
    f2ptr processor  = raw__array__elt(cause, processors, this->index);
    { // assert processor has correct index.
      int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
      if (pool_index != this->index) {
	error(nil, "funk2_virtual_processor__execute_next_bytecodes error: virtual processor pool_index does not match processor position in scheduler array.");
      }
    }
    {
      // assert our virtual_processor_thread is known to have the correct index.
      int pool_index = this_processor_thread__pool_index();
      if (pool_index != this->index) {
	status("funk2_virtual_processor__execute_next_bytecodes error: virtual processor pool_index does not match this_processor_thread__pool_index().  pool_index=%d  this->index=%d", (int)pool_index, (int)(this->index));
	error(nil, "funk2_virtual_processor__execute_next_bytecodes error: virtual processor pool_index does not match this_processor_thread__pool_index().");
      }
    }
    did_something = f2processor__execute_next_bytecodes(processor, cause);
    funk2_scheduler_thread_controller__check_user_wait_politely(&(__funk2.scheduler_thread_controller));
    this->execute_bytecodes_current_virtual_processor_thread = NULL;
    funk2_virtual_processor__know_of_one_more_spinning_virtual_processor_thread(this);
  }
  if (locked_mutex) {
    funk2_processor_mutex__unlock(&(this->execute_bytecodes_mutex));
  }
  return did_something;
}

void funk2_virtual_processor__know_of_one_less_assigned_virtual_processor_thread(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
  this->assigned_virtual_processor_thread_count --;
  status("funk2_virtual_processor__know_of_one_less_assigned_virtual_processor_thread: processor_index=" u64__fstr " processor_thread_count=" s64__fstr, this->index, this->assigned_virtual_processor_thread_count);
  funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__know_of_one_more_assigned_virtual_processor_thread(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
  this->assigned_virtual_processor_thread_count ++;
  status("funk2_virtual_processor__know_of_one_more_assigned_virtual_processor_thread: processor_index=" u64__fstr " processor_thread_count=" s64__fstr, this->index, this->assigned_virtual_processor_thread_count);
  funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
  this->spinning_virtual_processor_thread_count --;
  //status("funk2_virtual_processor__know_of_one_less_spinning_virtual_processor_thread: this->spinning_virtual_processor_thread_count=" s64__fstr, this->spinning_virtual_processor_thread_count);
  funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__know_of_one_more_spinning_virtual_processor_thread(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
  this->spinning_virtual_processor_thread_count ++;
  //status("funk2_virtual_processor__know_of_one_more_spinning_virtual_processor_thread: this->spinning_virtual_processor_thread_count=" s64__fstr, this->spinning_virtual_processor_thread_count);
  funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
}

void funk2_virtual_processor__unpause_threads(funk2_virtual_processor_t* this) {
  funk2_processor_mutex__lock(&(this->virtual_processor_thread_stack_mutex));
  funk2_virtual_processor_thread_cons_t* cons = this->virtual_processor_thread_stack;
  while (cons != NULL) {
    funk2_virtual_processor_thread_t* virtual_processor_thread = cons->virtual_processor_thread;
    {
      s64 working_virtual_processor_thread_count = this->assigned_virtual_processor_thread_count - this->spinning_virtual_processor_thread_count;
      s64 line_length                            = virtual_processor_thread->virtual_processor_stack_index - working_virtual_processor_thread_count;
      if (line_length >= 0 &&
	  line_length <= 2) {
	funk2_virtual_processor_thread__unpause(virtual_processor_thread);
      }
    }
    cons = cons->next;
  }
  funk2_processor_mutex__unlock(&(this->virtual_processor_thread_stack_mutex));
}

void funk2_virtual_processor__yield(funk2_virtual_processor_t* this) {
  s64 working_virtual_processor_thread_count;
  {
    s64 assigned_virtual_processor_thread_count;
    s64 spinning_virtual_processor_thread_count;
    {
      funk2_processor_mutex__lock(&(this->virtual_processor_thread_count_mutex));
      assigned_virtual_processor_thread_count = this->assigned_virtual_processor_thread_count;
      spinning_virtual_processor_thread_count = this->spinning_virtual_processor_thread_count;
      funk2_processor_mutex__unlock(&(this->virtual_processor_thread_count_mutex));
    }
    working_virtual_processor_thread_count = assigned_virtual_processor_thread_count - spinning_virtual_processor_thread_count;
  }
  if (! (this->execute_bytecodes_current_virtual_processor_thread)) {
    error(nil, "funk2_virtual_processor__yield error: execute_bytecodes_current_virtual_processor_thread is NULL.");
  }
  funk2_virtual_processor_thread_t* yielding_virtual_processor_thread = this->execute_bytecodes_current_virtual_processor_thread;
  this->execute_bytecodes_current_virtual_processor_thread = NULL;
  f2ptr yielding_fiber   = funk2_operating_system__pop_current_fiber(&(__funk2.operating_system), this->index);
  f2ptr reflective_cause = nil;
  raw__fiber__handle_exit_virtual_processor(reflective_cause, yielding_fiber);
  {
    funk2_processor_mutex__unlock(&(this->execute_bytecodes_mutex));
    funk2_virtual_processor__assure_at_least_one_spinning_virtual_processor_thread(this);
    funk2_virtual_processor__unpause_threads(this);
    // let spinning processor execute some bytecodes before returning from yield...
    if (__funk2.scheduler_thread_controller.please_wait ||
	__funk2.user_thread_controller.please_wait) {
      f2__nanosleep(working_virtual_processor_thread_count * deep_sleep_nanoseconds);
    } else {
      raw__fast_spin_sleep_yield();
    }
    {
      boolean_t locked_mutex = boolean__false;
      {
	u64 lock_tries = 0;
	while ((! locked_mutex) &&
	       (! (yielding_virtual_processor_thread->exit))) {
	  if (funk2_processor_mutex__trylock(&(this->execute_bytecodes_mutex)) == 0) {
	    locked_mutex = boolean__true;
	  }
	  if (! locked_mutex) {
	    lock_tries ++;
	    if ((lock_tries > 1000) ||
		__funk2.scheduler_thread_controller.please_wait ||
		__funk2.user_thread_controller.please_wait) {
	      f2__nanosleep(working_virtual_processor_thread_count * deep_sleep_nanoseconds);
	    } else {
	      raw__fast_spin_sleep_yield();
	    }
	  }
	}
      }
      if (yielding_virtual_processor_thread->exit) {
	yielding_virtual_processor_thread->exited = boolean__true;
	pthread_exit(0);
      }
    }
  }
  funk2_operating_system__push_current_fiber(&(__funk2.operating_system), this->index, yielding_fiber);
  this->execute_bytecodes_current_virtual_processor_thread = yielding_virtual_processor_thread;
  raw__fiber__handle_enter_virtual_processor(reflective_cause, yielding_fiber);
}
