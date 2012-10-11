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

// processor

def_primobject_9_slot(processor,
		      scheduler,
		      processor_thread,
		      active_fibers_scheduler_cmutex,
		      active_fibers_count_chunk,
		      active_fibers,
		      active_fibers_iter,
		      pool_index,
		      desc,
		      bytecode_count);

f2ptr f2__processor__new(f2ptr cause, f2ptr scheduler, f2ptr pool_index, f2ptr desc) {
  f2ptr processor_thread               = nil;
  f2ptr active_fibers_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr active_fibers_count_chunk      = raw__chunk__new(cause, sizeof(u64));
  f2ptr active_fibers                  = nil;
  f2ptr active_fibers_iter             = nil;
  f2ptr bytecode_count                 = f2integer__new(cause, 0);
  return f2processor__new(cause,
			  scheduler,
			  processor_thread,
			  active_fibers_scheduler_cmutex,
			  active_fibers_count_chunk,
			  active_fibers,
			  active_fibers_iter,
			  pool_index,
			  desc,
			  bytecode_count);
}
def_pcfunk3(processor__new, scheduler, pool_index, desc,
	    "",
	    return f2__processor__new(this_cause, scheduler, pool_index, desc));


// note: this is a scheduler funktion, see scheduler_cmutex__lock
u64 raw__processor__scheduler_active_fibers_count(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(active_fibers_scheduler_cmutex, cause);
  u64 active_fibers_count__i = raw__processor__active_fibers_count__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return active_fibers_count__i;
}


u64 raw__processor__active_fibers_count__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_count_chunk = f2processor__active_fibers_count_chunk(this, cause);
  return raw__chunk__bit64__elt(cause, active_fibers_count_chunk, 0);
}

u64 raw__processor__active_fibers_count(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  while (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause)) {
    f2__this__fiber__yield(cause);
  }
  u64 active_fibers_count__i = raw__processor__active_fibers_count__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return active_fibers_count__i;
}

f2ptr f2__processor__active_fibers_count(f2ptr cause, f2ptr this) {
  assert_argument_type(processor, this);
  return f2integer__new(cause, raw__processor__active_fibers_count(cause, this));
}
def_pcfunk1(processor__active_fibers_count, this,
	    "",
	    return f2__processor__active_fibers_count(this_cause, this));


void raw__processor__active_fibers_count__set__thread_unsafe(f2ptr cause, f2ptr this, u64 active_fibers_count__i) {
  f2ptr active_fibers_count_chunk = f2processor__active_fibers_count_chunk(this, cause);
  return raw__chunk__bit64__elt__set(cause, active_fibers_count_chunk, 0, active_fibers_count__i);
}


boolean_t raw__processor__add_active_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr processor_assignment_index = f2fiber__processor_assignment_index(fiber, cause);
  if (processor_assignment_index != nil) {
    return boolean__false;
  }
  pause_gc();
  {
    u64 active_fibers_count__i = raw__processor__active_fibers_count__thread_unsafe(cause, this);
    active_fibers_count__i ++;
    raw__processor__active_fibers_count__set__thread_unsafe(cause, this, active_fibers_count__i);
  }
  f2processor__active_fibers__set(this, cause, raw__cons__new(cause, fiber, f2processor__active_fibers(this, cause)));
  f2fiber__processor_assignment_index__set(fiber, cause, f2processor__pool_index(this, cause));
  resume_gc();
  return boolean__true;
}

f2ptr raw__processor__scheduler_add_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  if (! raw__processor__is_type(cause, this)) {
    error(nil, "attempted to add fiber to object that is not a processor.");
  }
  f2ptr active_fibers_scheduler_cmutex        = f2processor__active_fibers_scheduler_cmutex(   this,  cause);
  f2ptr processor_assignment_scheduler_cmutex = f2fiber__processor_assignment_scheduler_cmutex(fiber, cause);
  boolean_t both_locked                       = boolean__false;
  s64 lock_tries = 0;
  while (! both_locked) {
    both_locked                                                     = boolean__true;
    boolean_t active_fibers_scheduler_cmutex__failed_to_lock        = f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex,        cause);
    boolean_t processor_assignment_scheduler_cmutex__failed_to_lock = f2scheduler_cmutex__trylock(processor_assignment_scheduler_cmutex, cause);
    if (active_fibers_scheduler_cmutex__failed_to_lock) {
      both_locked = boolean__false;
    }
    if (processor_assignment_scheduler_cmutex__failed_to_lock) {
      both_locked = boolean__false;
    }
    if (! both_locked) {
      if (! active_fibers_scheduler_cmutex__failed_to_lock) {
	f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
      }
      if (! processor_assignment_scheduler_cmutex__failed_to_lock) {
	f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
      }
      //f2__this__fiber__yield(cause);
      lock_tries ++;
      if (lock_tries < 1000) {
	// spin fast
      } else if (lock_tries < 2000) {
	raw__fast_spin_sleep_yield();
      } else {
	raw__spin_sleep_yield();
      }
    }
  }
  boolean_t success = raw__processor__add_active_fiber__thread_unsafe(cause, this, fiber);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex,        cause);
  f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
  return f2bool__new(success);
}

f2ptr raw__processor__add_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  if (! raw__processor__is_type(cause, this)) {
    error(nil, "attempted to add fiber to object that is not a processor.");
  }
  f2ptr active_fibers_scheduler_cmutex        = f2processor__active_fibers_scheduler_cmutex(   this,  cause);
  f2ptr processor_assignment_scheduler_cmutex = f2fiber__processor_assignment_scheduler_cmutex(fiber, cause);
  boolean_t both_locked                       = boolean__false;
  while (! both_locked) {
    both_locked                                                     = boolean__true;
    boolean_t active_fibers_scheduler_cmutex__failed_to_lock        = f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex,        cause);
    boolean_t processor_assignment_scheduler_cmutex__failed_to_lock = f2scheduler_cmutex__trylock(processor_assignment_scheduler_cmutex, cause);
    if (active_fibers_scheduler_cmutex__failed_to_lock) {
      both_locked = boolean__false;
    }
    if (processor_assignment_scheduler_cmutex__failed_to_lock) {
      both_locked = boolean__false;
    }
    if (! both_locked) {
      if (! active_fibers_scheduler_cmutex__failed_to_lock) {
	f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
      }
      if (! processor_assignment_scheduler_cmutex__failed_to_lock) {
	f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
      }
      f2__this__fiber__yield(cause);
      //raw__fast_spin_sleep_yield();
    }
  }
  boolean_t success = raw__processor__add_active_fiber__thread_unsafe(cause, this, fiber);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex,        cause);
  f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
  return f2bool__new(success);
}

f2ptr f2__processor__add_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(processor, this);
  assert_argument_type(fiber,     fiber);
  return raw__processor__add_active_fiber(cause, this, fiber);
}
def_pcfunk2(processor__add_active_fiber, this, fiber,
	    "",
	    return f2__processor__add_active_fiber(this_cause, this, fiber));


f2ptr raw__processor__remove_active_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr processor_assignment_index = f2fiber__processor_assignment_index(fiber, cause);
  if (processor_assignment_index == nil) {
    return f2larva__new(cause, 125112, nil);
  }
  boolean_t found_and_removed_fiber = boolean__false;
  f2ptr active_fibers_iter = f2processor__active_fibers(this, cause);
  f2ptr active_fibers_prev = nil;
  while (active_fibers_iter) {
    f2ptr active_fiber       = f2cons__car(active_fibers_iter, cause);
    f2ptr active_fibers_next = f2cons__cdr(active_fibers_iter, cause);
    if (fiber == active_fiber) {
      if (active_fibers_prev == nil) {
	f2processor__active_fibers__set(this, cause, active_fibers_next);
      } else {
	f2cons__cdr__set(active_fibers_prev, cause, active_fibers_next);
      }
      f2fiber__processor_assignment_index__set(fiber, cause, nil);
      found_and_removed_fiber = boolean__true;
      break;
    }
    active_fibers_prev = active_fibers_iter;
    active_fibers_iter = active_fibers_next;
  }
  if (found_and_removed_fiber) {
    u64 active_fibers_count__i = raw__processor__active_fibers_count__thread_unsafe(cause, this);
    if (active_fibers_count__i == 0) {
      error(nil, "attempted to decrement active_fibers_count below zero.");
    }
    active_fibers_count__i --;
    raw__processor__active_fibers_count__set__thread_unsafe(cause, this, active_fibers_count__i);
  }
  return f2bool__new(found_and_removed_fiber);
}

f2ptr raw__processor__remove_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr active_fibers_scheduler_cmutex        = f2processor__active_fibers_scheduler_cmutex(   this,  cause);
  f2ptr processor_assignment_scheduler_cmutex = f2fiber__processor_assignment_scheduler_cmutex(fiber, cause);
  {
    boolean_t both_locked = boolean__false;
    while (! both_locked) {
      both_locked                                                     = boolean__true;
      boolean_t active_fibers_scheduler_cmutex__failed_to_lock        = f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex,        cause);
      boolean_t processor_assignment_scheduler_cmutex__failed_to_lock = f2scheduler_cmutex__trylock(processor_assignment_scheduler_cmutex, cause);
      if (active_fibers_scheduler_cmutex__failed_to_lock) {
	both_locked = boolean__false;
      }
      if (processor_assignment_scheduler_cmutex__failed_to_lock) {
	both_locked = boolean__false;
      }
      if (! both_locked) {
	if (! active_fibers_scheduler_cmutex__failed_to_lock) {
	  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
	}
	if (! processor_assignment_scheduler_cmutex__failed_to_lock) {
	  f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
	}
	f2__this__fiber__yield(cause);
	//raw__fast_spin_sleep_yield();
      }
    }
  }
  f2ptr result = raw__processor__remove_active_fiber__thread_unsafe(cause, this, fiber);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex,        cause);
  f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
  return result;
}

f2ptr f2__processor__remove_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(processor, this);
  assert_argument_type(fiber,     fiber);
  return raw__processor__remove_active_fiber(cause, this, fiber);
}
def_pcfunk2(processor__remove_active_fiber, this, fiber,
	    "",
	    return f2__processor__remove_active_fiber(this_cause, this, fiber));


f2ptr raw__processor__try_remove_active_fiber__active_fibers_thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr     processor_assignment_scheduler_cmutex                 = f2fiber__processor_assignment_scheduler_cmutex(fiber, cause);
  f2ptr     execute_cmutex                                        = f2fiber__execute_cmutex(fiber, cause);
  boolean_t all_locked                                            = boolean__true;
  boolean_t execute_cmutex__failed_to_lock                        = f2cmutex__trylock(execute_cmutex, cause);
  boolean_t processor_assignment_scheduler_cmutex__failed_to_lock = f2scheduler_cmutex__trylock(processor_assignment_scheduler_cmutex, cause);
  if (execute_cmutex__failed_to_lock) {
    all_locked = boolean__false;
  }
  if (processor_assignment_scheduler_cmutex__failed_to_lock) {
    all_locked = boolean__false;
  }
  f2ptr found_and_removed_active_fiber;
  if (! all_locked) {
    if (! execute_cmutex__failed_to_lock) {
      f2cmutex__unlock(execute_cmutex, cause);
    }
    if (! processor_assignment_scheduler_cmutex__failed_to_lock) {
      f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
    }
    found_and_removed_active_fiber = f2bool__new(boolean__false);
  } else {
    found_and_removed_active_fiber = raw__processor__remove_active_fiber__thread_unsafe(cause, this, fiber);
    f2cmutex__unlock(execute_cmutex, cause);
    f2scheduler_cmutex__unlock(processor_assignment_scheduler_cmutex, cause);
  }
  return found_and_removed_active_fiber;
}

f2ptr raw__processor__try_remove_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2ptr found_and_removed_active_fiber;
  if (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause) != 0) {
    found_and_removed_active_fiber = f2bool__new(boolean__false);
  } else {
    found_and_removed_active_fiber = raw__processor__try_remove_active_fiber__active_fibers_thread_unsafe(cause, this, fiber);
    f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  }
  return found_and_removed_active_fiber;
}

f2ptr raw__processor__try_remove_any_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2ptr removed_fiber                  = nil;
  if (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause) == 0) {
    f2ptr active_fibers = f2processor__active_fibers(this, cause);
    {
      f2ptr iter = active_fibers;
      while (iter != nil) {
	f2ptr active_fiber = f2cons__car(iter, cause);
	f2ptr found_and_removed_active_fiber = raw__processor__try_remove_active_fiber__active_fibers_thread_unsafe(cause, this, active_fiber);
	if (found_and_removed_active_fiber != nil) {
	  removed_fiber = active_fiber;
	  iter          = nil;
	} else {
	  iter = f2cons__cdr(iter, cause);
	}
      }
    }
    f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  }
  return removed_fiber;
}


// note: this is a scheduler funktion, see scheduler_cmutex__lock
f2ptr raw__processor__scheduler_current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(active_fibers_scheduler_cmutex, cause);
  f2ptr current_active_fiber = raw__processor__current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_active_fiber;
}


f2ptr raw__processor__current_active_fiber__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_iter = f2processor__active_fibers_iter(this, cause);
  if (active_fibers_iter == nil) {
    return nil;
  }
  return f2cons__car(active_fibers_iter, cause);
}

f2ptr raw__processor__current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  while (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause)) {
    f2__this__fiber__yield(cause);
  }
  f2ptr current_active_fiber = raw__processor__current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_active_fiber;
}

f2ptr f2__processor__current_active_fiber(f2ptr cause, f2ptr this) {
  assert_argument_type(processor, this);
  return raw__processor__current_active_fiber(cause, this);
}
def_pcfunk1(processor__current_active_fiber, this,
	    "",
	    return f2__processor__current_active_fiber(this_cause, this));



boolean_t raw__processor__increment_current_active_fiber__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_iter = f2processor__active_fibers_iter(this, cause);
  if (active_fibers_iter == nil) {
    return boolean__false;
  }
  active_fibers_iter = f2cons__cdr(active_fibers_iter, cause);
  f2processor__active_fibers_iter__set(this, cause, active_fibers_iter);
  boolean_t current_element_exists = (active_fibers_iter != nil);
  return current_element_exists;
}

// note: this is a scheduler funktion, see scheduler_cmutex__lock
boolean_t raw__processor__scheduler_increment_current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(active_fibers_scheduler_cmutex, cause);
  boolean_t current_element_exists = raw__processor__increment_current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_element_exists;
}

boolean_t raw__processor__increment_current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  while (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause)) {
    f2__this__fiber__yield(cause);
  }
  boolean_t current_element_exists = raw__processor__increment_current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_element_exists;
}

f2ptr f2__processor__increment_current_active_fiber(f2ptr cause, f2ptr this) {
  assert_argument_type(processor, this);
  return raw__processor__increment_current_active_fiber(cause, this);
}
def_pcfunk1(processor__increment_current_active_fiber, this,
	    "",
	    return f2__processor__increment_current_active_fiber(this_cause, this));



boolean_t raw__processor__reset_current_active_fiber__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr active_fibers = f2processor__active_fibers(this, cause);
  f2processor__active_fibers_iter__set(this, cause, active_fibers);
  boolean_t current_element_exists = (active_fibers != nil);
  return current_element_exists;
}

// note: this is a scheduler funktion, see scheduler_cmutex__lock
boolean_t raw__processor__scheduler_reset_current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(active_fibers_scheduler_cmutex, cause);
  boolean_t current_element_exists = raw__processor__reset_current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_element_exists;
}

boolean_t raw__processor__reset_current_active_fiber(f2ptr cause, f2ptr this) {
  f2ptr active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  while (f2scheduler_cmutex__trylock(active_fibers_scheduler_cmutex, cause)) {
    f2__this__fiber__yield(cause);
  }
  boolean_t current_element_exists = raw__processor__reset_current_active_fiber__thread_unsafe(cause, this);
  f2scheduler_cmutex__unlock(active_fibers_scheduler_cmutex, cause);
  return current_element_exists;
}

f2ptr f2__processor__reset_current_active_fiber(f2ptr cause, f2ptr this) {
  assert_argument_type(processor, this);
  return raw__processor__reset_current_active_fiber(cause, this);
}
def_pcfunk1(processor__reset_current_active_fiber, this,
	    "",
	    return f2__processor__reset_current_active_fiber(this_cause, this));



// note: this is a scheduler funktion, see scheduler_cmutex__lock
u64 raw__processor__active_fibers__scheduler_length(f2ptr cause, f2ptr this) {
  f2ptr this__active_fibers_scheduler_cmutex;
  this__active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(this__active_fibers_scheduler_cmutex, cause);
  f2ptr active_fibers = f2processor__active_fibers(this, cause);
  u64 fiber_num = raw__simple_length(cause, active_fibers);
  f2scheduler_cmutex__unlock(this__active_fibers_scheduler_cmutex, cause);
  return fiber_num;
}

u64 raw__processor__active_fibers__length(f2ptr cause, f2ptr this) {
  f2ptr this__active_fibers_scheduler_cmutex;
  this__active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
  while (f2scheduler_cmutex__trylock(this__active_fibers_scheduler_cmutex, cause)) {
    f2__this__fiber__yield(cause);
  }
  f2ptr active_fibers = f2processor__active_fibers(this, cause);
  u64 fiber_num = raw__simple_length(cause, active_fibers);
  f2scheduler_cmutex__unlock(this__active_fibers_scheduler_cmutex, cause);
  return fiber_num;
}

f2ptr f2__processor__active_fibers__length(f2ptr cause, f2ptr this) {
  assert_argument_type(processor, this);
  return f2integer__new(cause, raw__processor__active_fibers__length(cause, this));
}
def_pcfunk1(processor__active_fibers__length, this,
	    "",
	    return f2__processor__active_fibers__length(this_cause, this));


boolean_t raw__processor__active_fibers__contains__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  boolean_t contains_fiber = boolean__false;
  {
    f2ptr active_fibers = f2processor__active_fibers(this, cause);
    {
      f2ptr iter = active_fibers;
      while (iter != nil) {
	f2ptr active_fiber = f2cons__car(iter, cause);
	if (fiber == active_fiber) {
	  contains_fiber = boolean__true;
	  break;
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
  }
  return contains_fiber;
}

// note: this is a scheduler funktion, see scheduler_cmutex__lock
boolean_t raw__processor__active_fibers__scheduler_contains(f2ptr cause, f2ptr this, f2ptr fiber) {
  boolean_t contains_fiber = boolean__false;
  {
    f2ptr this__active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
    f2scheduler_cmutex__lock(this__active_fibers_scheduler_cmutex, cause);
    contains_fiber = raw__processor__active_fibers__contains__thread_unsafe(cause, this, fiber);
    f2scheduler_cmutex__unlock(this__active_fibers_scheduler_cmutex, cause);
  }
  return contains_fiber;
}

boolean_t raw__processor__active_fibers__contains(f2ptr cause, f2ptr this, f2ptr fiber) {
  boolean_t contains_fiber = boolean__false;
  {
    f2ptr this__active_fibers_scheduler_cmutex = f2processor__active_fibers_scheduler_cmutex(this, cause);
    while (f2scheduler_cmutex__trylock(this__active_fibers_scheduler_cmutex, cause)) {
      f2__this__fiber__yield(cause);
    }
    contains_fiber = raw__processor__active_fibers__contains__thread_unsafe(cause, this, fiber);
    f2scheduler_cmutex__unlock(this__active_fibers_scheduler_cmutex, cause);
  }
  return contains_fiber;
}

f2ptr f2__processor__active_fibers__contains(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(processor, this);
  assert_argument_type(fiber,     fiber);
  return f2bool__new(raw__processor__active_fibers__contains(cause, this, fiber));
}
def_pcfunk2(processor__active_fibers__contains, this, fiber,
	    "",
	    return f2__processor__active_fibers__contains(this_cause, this, fiber));


// processor

f2ptr raw__processor__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list16__new(cause,
						new__symbol(cause, "print_object_type"),              new__symbol(cause, "processor"),
						new__symbol(cause, "processor_thread"),               f2__processor__processor_thread(              cause, this),
						new__symbol(cause, "active_fibers_scheduler_cmutex"), f2__processor__active_fibers_scheduler_cmutex(cause, this),
						new__symbol(cause, "active_fibers_count"),            f2__processor__active_fibers_count(           cause, this),
						new__symbol(cause, "active_fibers"),                  f2__processor__active_fibers(                 cause, this),
						new__symbol(cause, "pool_index"),                     f2__processor__pool_index(                    cause, this),
						new__symbol(cause, "desc"),                           f2__processor__desc(                          cause, this),
						new__symbol(cause, "bytecode_count"),                 f2__processor__bytecode_count(                cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__processor__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(processor,            this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__processor__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(processor__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__processor__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2processor__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2processor__primobject_type__new(cause);
  {char* slot_name = "active_fibers_count";            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers_count__funk);}
  {char* slot_name = "add_active_fiber";               f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.add_active_fiber__funk);}
  {char* slot_name = "remove_active_fiber";            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.remove_active_fiber__funk);}
  {char* slot_name = "current_active_fiber";           f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.current_active_fiber__funk);}
  {char* slot_name = "increment_current_active_fiber"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.increment_current_active_fiber__funk);}
  {char* slot_name = "reset_current_active_fiber";     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.reset_current_active_fiber__funk);}
  {char* slot_name = "active_fibers-length";           f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__length__funk);}
  {char* slot_name = "active_fibers-contains";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__contains__funk);}
  {char* slot_name = "terminal_print_with_frame";      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk);}
  return this;
}




void execute_next_bytecodes__helper__found_larva_in_fiber(f2ptr cause, f2ptr fiber) {
  f2ptr larva = f2fiber__value(fiber, cause);
  f2fiber__paused__set(fiber, cause, __funk2.globalenv.true__symbol);
  {
    pause_gc();
    f2ptr bug = f2larva__bug(larva, cause);
    if (! bug) {
      bug = f2__bug__new_from_larva(cause, larva);
    } else if (raw__larva__is_type(cause, bug)) {
      bug = f2__bug__new(cause, f2integer__new(cause, f2larva__larva_type(larva, cause)), f2__frame__new(cause, nil));
    }
    if (raw__larva__is_type(cause, bug)) {
      printf("\nwhoops, translated larva into larva!"); fflush(stdout);
      f2fiber__value__set(fiber, cause, nil);
    } else {
      f2ptr bug_frame = f2__bug__frame(cause, bug);
      if (bug_frame == nil) {
	bug_frame = f2__frame__new(cause, nil);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "unknown_type_of_frameless_larva"));
	f2__bug__frame__set(cause, bug, bug_frame);
      }
      if (raw__frame__is_type(cause, bug_frame)) {
	if (! raw__frame__contains_var(cause, bug_frame, new__symbol(cause, "fiber"))) {
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "fiber"), fiber);
	}
      }
      //printf("\nbug: ");
      //f2__print(cause, bug);
      f2fiber__value__set(fiber, cause, bug);
    }
    
    {
      f2ptr exit_cmutex = f2fiber__exit_cmutex(fiber, cause);
      f2cmutex__lock(exit_cmutex, cause);
      f2fiber__exit_status__set(fiber, cause, new__symbol(cause, "bug"));
      f2__fiber_trigger__trigger(cause, f2fiber__bug_trigger(fiber, cause));
      f2cmutex__unlock(exit_cmutex, cause);
    }
    
    resume_gc();
  }
}

typedef enum scheduler_fast_loop_exit_reason_e {
  exit_reason__none = 0,
  exit_reason__is_complete,
  exit_reason__too_many_loops,
  exit_reason__reached_yield,
  exit_reason__found_larva
} scheduler_fast_loop_exit_reason_t;

#define execute_next_bytecodes__helper__fast_loop__max_bytecode_count (128)

scheduler_fast_loop_exit_reason_t execute_next_bytecodes__helper__fast_loop(f2ptr cause, f2ptr fiber) {
  //status("bytecode fast loop beginning.");
  scheduler_fast_loop_exit_reason_t exit_reason = exit_reason__none;
  
  pause_gc();
  raw__fiber__handle_enter_virtual_processor(cause, fiber);
  resume_gc();
  
  int i = execute_next_bytecodes__helper__fast_loop__max_bytecode_count;
  while (! exit_reason) {
    if(i == 0) {
      exit_reason = exit_reason__too_many_loops;
      break;
    } else if (f2__fiber__execute_next_bytecode(cause, fiber)) {
      exit_reason = exit_reason__reached_yield;
      break;
    } else if (raw__larva__is_type(cause, f2fiber__value(fiber, cause))) {
      execute_next_bytecodes__helper__found_larva_in_fiber(cause, fiber);
      //printf("found larva in fiber."); f2__print(cause, f2fiber__value(fiber, cause)); fflush(stdout);
      exit_reason = exit_reason__found_larva;
      break;
    } else if (f2fiber__is_complete(fiber, cause)) {
      exit_reason = exit_reason__is_complete;
      break;
    } 
    i --;
  }
  
  pause_gc();
  raw__fiber__handle_exit_virtual_processor(cause, fiber);
  raw__fiber__increase_bytecode_count(cause, fiber, execute_next_bytecodes__helper__fast_loop__max_bytecode_count - i);
  resume_gc();
  
  //status("bytecode fast loop done with %d loop fast cycles.", 1000-i);
  return exit_reason;
}

u64 last_balance_scheduler_nanoseconds_since_1970 = 0;

f2ptr f2processor__execute_next_bytecodes(f2ptr processor, f2ptr processor_cause) {
  //pool__pause_gc(this_processor_thread__pool_index());
  f2ptr did_something = nil;
  
  pause_gc();
  funk2_memorypool__user_flush_creation_fiber_bytes_freed_counts(nil, &(__funk2.memory.pool[this_processor_thread__pool_index()]));
  {
    u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    if ((nanoseconds_since_1970 - last_balance_scheduler_nanoseconds_since_1970) > 1000000000) {
      raw__scheduler__scheduler_balance_processor_load(nil, __funk2.operating_system.scheduler, processor);
      last_balance_scheduler_nanoseconds_since_1970 = nanoseconds_since_1970;
    }
  }
  resume_gc();
  
  raw__processor__reset_current_active_fiber(processor_cause, processor);
  
  int fiber_num = 0;
  {
    f2ptr fiber;
    while ((fiber = raw__processor__current_active_fiber(processor_cause, processor)) != nil) {
      fiber_num ++;
      boolean_t need_to_launch_larva_handling_critic_fiber = 0;
      if (f2cmutex__trylock(f2fiber__execute_cmutex(fiber, processor_cause), processor_cause) == 0) { // successful lock
	f2ptr cause = f2fiber__cause_reg(fiber, processor_cause);
	if (! f2fiber__paused(fiber, cause)) {
	  f2ptr sleep_until_time = f2fiber__sleep_until_time(fiber, cause);
	  boolean_t fiber_needs_sleep = boolean__false;
	  if (sleep_until_time) {
	    f2ptr nanoseconds_since_1970    = f2time__nanoseconds_since_1970(sleep_until_time, cause);
	    s64   nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
	    if (raw__nanoseconds_since_1970() >= nanoseconds_since_1970__i) {
	      f2fiber__sleep_until_time__set(fiber, cause, nil);
	    } else {
	      fiber_needs_sleep = boolean__true;
	    }
	  }
	  if (! fiber_needs_sleep) {
	    int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
	    { // assert that we are sane.
	      int this_processor_thread__pool_index__value = this_processor_thread__pool_index();
	      if (pool_index != this_processor_thread__pool_index__value) {
		status("f2processor__execute_next_bytecodes: pool_index != this_processor_thread__pool_index().  pool_index=%d  this_processor_thread__pool_index()=%d", pool_index, this_processor_thread__pool_index__value);
		error(nil, "f2processor__execute_next_bytecodes: pool_index != this_processor_thread__pool_index().");
	      }
	    }
	    
	    funk2_operating_system__push_current_fiber(&(__funk2.operating_system), pool_index, fiber);
	    
	    //printf("\n  got fiber lock.");
	    if (raw__larva__is_type(cause, f2fiber__value(fiber, cause))) {
	      //printf("\nfiber paused due to larva in value register.");
	    } else {
	      if (! f2fiber__is_complete(fiber, cause)) {
		//if (processor) {printf("\nprocessor "); f2__write(nil, f2processor__desc(processor));} else {printf("\nunknown processor");} printf(" executing fiber 0x%X", (int)fiber); fflush(stdout);
		
		if (f2fiber__should_quit(fiber, cause) != nil) {
		  
		  // quit here, while we have lock.
		  f2fiber__program_counter__set(fiber, cause, nil);
		  
		} else {
		  
		  did_something = __funk2.globalenv.true__symbol;
		  
		  {
		    f2ptr before_fiber__bytecode_count    = f2fiber__bytecode_count(fiber, cause);;
		    u64   before_fiber__bytecode_count__i = (u64)f2integer__i(before_fiber__bytecode_count, cause);
		    
		    // fast inner loop
		    scheduler_fast_loop_exit_reason_t exit_reason = execute_next_bytecodes__helper__fast_loop(cause, fiber);
		    
		    {
		      f2ptr fiber__bytecode_count        = f2fiber__bytecode_count(fiber, cause);;
		      u64   fiber__bytecode_count__i     = (u64)f2integer__i(fiber__bytecode_count, cause);
		      f2ptr processor__bytecode_count    = f2processor__bytecode_count(processor, cause);
		      u64   processor__bytecode_count__i = (u64)f2integer__i(processor__bytecode_count, cause);
		      pause_gc();
		      f2processor__bytecode_count__set(processor, cause, f2integer__new(cause, processor__bytecode_count__i + (fiber__bytecode_count__i - before_fiber__bytecode_count__i)));
		      resume_gc();
		    }
		    
		    if(exit_reason == exit_reason__found_larva) {
		      need_to_launch_larva_handling_critic_fiber = 1;
		    }
		  }
		}
		
	      } else {
		//printf("\n  fiber completed.");
		if (! f2fiber__is_zombie(fiber, cause)) {
		  f2fiber__is_zombie__set(fiber, cause, __funk2.globalenv.true__symbol);
		}
		if (! f2fiber__keep_undead(fiber, cause)) {
		  f2ptr exit_cmutex = f2fiber__exit_cmutex(fiber, cause);
		  if (f2cmutex__trylock(exit_cmutex, cause) == 0) {
		    pause_gc();
		    
		    // anytime a fiber is removed from processor active fibers, it should be removed from it's cause so that it can be garbage collected.
		    f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
		    if (fiber_cause != nil) {
		      raw__cause__remove_fiber(cause, fiber_cause, fiber);
		    }
		    if (f2fiber__is_zombie(fiber, cause)) {
		      f2fiber__is_zombie__set(fiber, cause, nil);
		    }
		    
		    f2ptr found_and_removed_fiber = raw__processor__remove_active_fiber(cause, processor, fiber);
		    if ((found_and_removed_fiber == nil) ||
			raw__larva__is_type(cause, found_and_removed_fiber)) {
		      printf("\nerror removing active fiber at completion."); fflush(stdout);
		      status(  "error removing active fiber at completion.");
		    }
		    
		    f2fiber__exit_status__set(fiber, cause, new__symbol(cause, "complete"));
		    f2__fiber_trigger__trigger(cause, f2fiber__complete_trigger(fiber, cause));
		    
		    f2cmutex__unlock(exit_cmutex, cause);
		    
		    resume_gc();
		  }
		}
	      }
	    }
	  
	    funk2_operating_system__pop_current_fiber(&(__funk2.operating_system), pool_index);
	  }
	} else { // (fiber__paused)
	}
	f2cmutex__unlock(f2fiber__execute_cmutex(fiber, cause), cause);
      } else {
	//printf("\nfiber locked couldn't execute...");
      }
      
      if (need_to_launch_larva_handling_critic_fiber) {
	f2ptr cause_reg = f2fiber__cause_reg(fiber, processor_cause);
	f2ptr critics   = cause_reg ? f2cause__critics(cause_reg, processor_cause) : nil;
	if (critics) {
	  f2ptr fiber_cause = f2fiber__cause_reg(fiber, processor_cause);
	  if (raw__larva__is_type(processor_cause, f2fiber__value(fiber, processor_cause))) {
	    f2ptr larva      = f2fiber__value(fiber, processor_cause);
	    u64   larva_type = raw__larva__larva_type(processor_cause, larva);
	    status("larva type (" u64__fstr ") found in fiber and fiber has a critic, so launching critic fiber in serial.", larva_type);
	  }
	  //status("\n  critic="); f2__fiber__print(cause, nil, critics); fflush(stdout);
	  pause_gc();
	  f2ptr new_fiber = raw__fiber__new(fiber_cause, fiber, f2fiber__env(fiber, processor_cause), critics, raw__cons__new(processor_cause, fiber, nil));
	  {
	    f2ptr result = raw__processor__add_active_fiber(fiber_cause, processor, new_fiber);
	    if (raw__larva__is_type(processor_cause, result)) {
	      status(    "processor-execute_next_bytecodes: error adding critic fiber.");
	      error(nil, "processor-execute_next_bytecodes: error adding critic fiber.");
	    }
	  }
	  resume_gc();
	} else {
	  char status_msg[1024];
	  if (raw__bug__is_type(processor_cause, f2fiber__value(fiber, processor_cause))) {
	    f2ptr bug      = f2fiber__value(fiber, processor_cause);
	    f2ptr bug_type = f2__bug__bug_type(processor_cause, bug);
	    if (raw__integer__is_type(processor_cause, bug_type)) {
	      u64 bug_type__i = f2integer__i(bug_type, processor_cause);
	      snprintf(status_msg, 1023, "bug type (" u64__fstr ") found in fiber and fiber has no critics, so doing nothing.", bug_type__i);
	    } else {
	      snprintf(status_msg, 1023, "larva found in fiber (but bug_type is not integer) and fiber has no critics, so doing nothing.");
	    }
	  } else {
	    snprintf(status_msg, 1023, "larva found in fiber (but is not bug now) and fiber has no critics, so doing nothing.");
	  }
	  status(status_msg);
	}
      }
    
      raw__processor__increment_current_active_fiber(processor_cause, processor);
    } // end of fiber while
  }
  
  return did_something;
}

void raw__processor__reinitialize(f2ptr cause, f2ptr this) {
  f2ptr active_fibers = f2processor__active_fibers(this, cause);
  f2ptr iter = active_fibers;
  while (iter != nil) {
    f2ptr active_fiber = f2cons__car(iter, cause);
    raw__fiber__reinitialize(cause, active_fiber);
    iter = f2cons__cdr(iter, cause);
  }
}


void raw__processor__clean(f2ptr cause, f2ptr this) {
  f2ptr active_fibers = f2processor__active_fibers(this, cause);
  {
    f2ptr iter = active_fibers;
    while (iter != nil) {
      f2ptr active_fiber = f2cons__car(iter, cause);
      raw__fiber__clean(cause, active_fiber);
      iter = f2cons__cdr(iter, cause);
    }
  }
}

// **

void f2__processor__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  // processor
  
  initialize_primobject_9_slot__defragment__fix_pointers(processor,
							 scheduler,
							 processor_thread,
							 active_fibers_scheduler_cmutex,
							 active_fibers_count_chunk,
							 active_fibers,
							 active_fibers_iter,
							 pool_index,
							 desc,
							 bytecode_count);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__active_fibers_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.add_active_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__add_active_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.add_active_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.remove_active_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__remove_active_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.remove_active_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.current_active_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__current_active_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.current_active_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.increment_current_active_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__increment_current_active_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.increment_current_active_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.reset_current_active_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__reset_current_active_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.reset_current_active_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__active_fibers__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__active_fibers__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(processor__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk);
}

void f2__processor__reinitialize_globalvars() {
  f2ptr cause = f2_processor_c__cause__new(initial_cause());
  
  
  // processor
  
  initialize_primobject_9_slot(processor,
			       scheduler,
			       processor_thread,
			       active_fibers_scheduler_cmutex,
			       active_fibers_count_chunk,
			       active_fibers,
			       active_fibers_iter,
			       pool_index,
			       desc,
			       bytecode_count);
  
  {char* symbol_str = "active_fibers_count"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__active_fibers_count, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers_count__funk = never_gc(cfunk);}
  {char* symbol_str = "add_active_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_processor.add_active_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__add_active_fiber, this, fiber, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.add_active_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "remove_active_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_processor.remove_active_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__remove_active_fiber, this, fiber, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.remove_active_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "current_active_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_processor.current_active_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__current_active_fiber, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.current_active_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "increment_current_active_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_processor.increment_current_active_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__increment_current_active_fiber, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.increment_current_active_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "reset_current_active_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_processor.reset_current_active_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__reset_current_active_fiber, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.reset_current_active_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "active_fibers-length"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__length__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__active_fibers__length, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__length__funk = never_gc(cfunk);}
  {char* symbol_str = "active_fibers-contains"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__contains__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__active_fibers__contains, this, fiber, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_fibers__contains__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__processor__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "processor", "", &f2__processor__reinitialize_globalvars, &f2__processor__defragment__fix_pointers);
  
  f2__processor__reinitialize_globalvars();
}

void f2__processor__destroy() {
}



