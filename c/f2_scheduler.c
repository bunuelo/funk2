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

void funk2_operating_system__init(funk2_operating_system_t* this) {
  int i;
  for (i = 0; i < memory_pool_num; i++) {
    this->processor_thread__current_fiber[i] = nil;
  }
}

void funk2_operating_system__destroy(funk2_operating_system_t* this) {
}


f2ptr f2__global_scheduler__this_processor(f2ptr cause) {
  return raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), this_processor_thread__pool_index());
}

void f2__processor__add_active_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
  if (fiber_cause) {
    f2__cause__add_fiber(cause, fiber_cause, fiber);
  }
  //f2ptr active_fibers_mutex = f2processor__active_fibers_mutex(this, cause);
  //f2mutex__lock(active_fibers_mutex, cause);
  pause_gc();
  f2processor__active_fibers__set(this, cause, f2cons__new(cause, fiber, f2processor__active_fibers(this, cause)));
  resume_gc();
  //f2mutex__unlock(active_fibers_mutex, cause);
}

void f2__processor__add_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr active_fibers_mutex = f2processor__active_fibers_mutex(this, cause);
  f2mutex__lock(active_fibers_mutex, cause);
  f2__processor__add_active_fiber__thread_unsafe(cause, this, fiber);
  f2mutex__unlock(active_fibers_mutex, cause);
}

boolean_t f2__processor__remove_active_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
  if (fiber_cause) {
    f2__cause__remove_fiber(cause, fiber_cause, fiber);
  }
  boolean_t found_and_removed_fiber = boolean__false;
  //f2ptr active_fibers_mutex = f2processor__active_fibers_mutex(this, cause);
  //f2mutex__lock(active_fibers_mutex, cause);
  f2ptr active_fibers_iter = f2processor__active_fibers(this, cause);
  f2ptr active_fibers_prev = nil;
  while (active_fibers_iter) {
    f2ptr active_fiber       = f2cons__car(active_fibers_iter, cause);
    f2ptr active_fibers_next = f2cons__cdr(active_fibers_iter, cause);
    if (fiber == active_fiber) {
      if (active_fibers_prev) {
	f2cons__cdr__set(active_fibers_prev, cause, active_fibers_next);
      } else {
	f2processor__active_fibers__set(this, cause, active_fibers_next);
      }
      found_and_removed_fiber = boolean__true;
    }
    active_fibers_iter = active_fibers_next;
  }
  //f2mutex__unlock(active_fibers_mutex, cause);
  return found_and_removed_fiber;
}

boolean_t f2__processor__remove_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr active_fibers_mutex = f2processor__active_fibers_mutex(this, cause);
  f2mutex__lock(active_fibers_mutex, cause);
  boolean_t result = f2__processor__remove_active_fiber__thread_unsafe(cause, this, fiber);
  f2mutex__unlock(active_fibers_mutex, cause);
  return result;
}

u64 raw__processor__active_fibers__length(f2ptr cause, f2ptr processor) {
  f2ptr processor__active_fibers_mutex;
  processor__active_fibers_mutex = f2processor__active_fibers_mutex(processor, cause);
  f2mutex__lock(processor__active_fibers_mutex, cause);
  f2ptr active_fibers = f2processor__active_fibers(processor, cause);
  u64 fiber_num = raw__simple_length(cause, active_fibers);
  f2mutex__unlock(processor__active_fibers_mutex, cause);
  return fiber_num;
}

f2ptr f2__scheduler__processor_with_fewest_fibers(f2ptr cause, f2ptr scheduler) {
  f2ptr processors = f2scheduler__processors(scheduler, cause);
  u64 processors__length = raw__array__length(cause, processors);
  u64   min_length    = 0xffffffffffffffffull;
  f2ptr min_processor = nil;
  u64 i;
  status("processor fiber list:");
  for (i = 0; i < processors__length; i ++) {
    f2ptr processor = raw__array__elt(cause, processors, i);
    f2ptr active_fibers = f2processor__active_fibers(processor, cause);
    u64 fibers__length = raw__simple_length(cause, active_fibers);
    status("  processor pool_index=" s64__fstr " active_fiber_num=" u64__fstr ".", f2integer__i(f2processor__pool_index(processor, cause), cause), fibers__length);
    if (fibers__length < min_length) {
      min_length = fibers__length;
      min_processor = processor;
    }
  }
  return min_processor;
}

void f2__global_scheduler__add_fiber_serial(f2ptr cause, f2ptr fiber) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  f2__processor__add_active_fiber(cause, processor, fiber);
}

void f2__scheduler__add_fiber_to_least_used_processor(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr processor = f2__scheduler__processor_with_fewest_fibers(cause, this);
  status("[adding fiber to least used processor " s64__fstr "]", f2integer__i(f2processor__pool_index(processor, cause), cause));
  f2__processor__add_active_fiber(cause, processor, fiber);
}

void f2__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber) {
  f2__scheduler__add_fiber_to_least_used_processor(cause, __funk2.operating_system.scheduler, fiber);
}

//void f2__global_scheduler__execute_mutex__lock(f2ptr cause) {
//  funk2_processor_mutex__lock(&(__funk2.operating_system.scheduler__execute_mutex));
//}

//void f2__global_scheduler__execute_mutex__unlock(f2ptr cause) {
//  funk2_processor_mutex__unlock(&(__funk2.operating_system.scheduler__execute_mutex));
//}

f2ptr f2__scheduler__processor_thread_current_fiber(int pool_index) {
  f2ptr fiber = __funk2.operating_system.processor_thread__current_fiber[pool_index];
  if (! fiber) {
    error(nil, "f2__scheduler__processor_thread_current_fiber: fiber=nil");
  }
  return fiber;
}


void execute_next_bytecodes__helper__found_larva_in_fiber(f2ptr cause, f2ptr fiber) {
  f2ptr larva = f2fiber__value(fiber, cause);
  f2fiber__paused__set(fiber, cause, __funk2.globalenv.true__symbol);
  f2ptr critics = f2fiber__critics(fiber, cause);
  if (critics) {
    pause_gc();
    f2fiber__value__set(fiber, cause, f2bug__new(cause, f2integer__new(cause, f2larva__larva_type(larva, cause))));
    resume_gc();
  } else {
    f2fiber__program_counter__set(fiber, cause, nil);
  }
}

typedef enum scheduler_fast_loop_exit_reason_e {
  exit_reason__none = 0,
  exit_reason__is_complete,
  exit_reason__too_many_loops,
  exit_reason__reached_yield,
  exit_reason__found_larva
} scheduler_fast_loop_exit_reason_t;

scheduler_fast_loop_exit_reason_t execute_next_bytecodes__helper__fast_loop(f2ptr cause, f2ptr fiber) {
  scheduler_fast_loop_exit_reason_t exit_reason = exit_reason__none;
  
  int i = 1000;
  while (! exit_reason) {
    if(i == 0) {
      exit_reason = exit_reason__too_many_loops;
      break;
    } else if (f2__fiber__execute_next_bytecode(cause, fiber)) {
      exit_reason = exit_reason__reached_yield;
      break;
    } else if (raw__larva__is_type(cause, f2fiber__value(fiber, cause))) {
      execute_next_bytecodes__helper__found_larva_in_fiber(cause, fiber);
      exit_reason = exit_reason__found_larva;
      break;
    } else if (f2fiber__is_complete(fiber, cause)) {
      exit_reason = exit_reason__is_complete;
      break;
    } 
    i --;
  }
  //printf("\ndone with %d loop fast cycle", 1000-i); fflush(stdout);
  return exit_reason;
}

f2ptr f2processor__execute_next_bytecodes(f2ptr processor, f2ptr cause) {
  //pool__pause_gc(this_processor_thread__pool_index());
  f2ptr did_something = nil;
  
  f2processor__active_fibers_iter__set(processor, cause, f2processor__active_fibers(processor, cause));
  f2processor__active_fibers_prev__set(processor, cause, nil);
  
  int fiber_num = 0;
  while (f2processor__active_fibers_iter(processor, cause)) {
    f2processor__active_fibers_next__set(processor, cause, f2cons__cdr(f2processor__active_fibers_iter(processor, cause), cause));
    fiber_num ++;
    f2ptr fiber = f2cons__car(f2processor__active_fibers_iter(processor, cause), cause);
    int       prev_fiber_iter__already_set = 0;
    boolean_t need_to_launch_larva_handling_critic_fiber = 0;
    if (f2mutex__trylock(f2fiber__execute_mutex(fiber, cause), cause) == 0) { // successful lock
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
	  release__assert(pool_index == this_processor_thread__pool_index(), fiber, "f2processor__execute_next_bytecodes: pool_index != this_processor_thread__pool_index().");
	  f2ptr popped_fiber = __funk2.operating_system.processor_thread__current_fiber[pool_index];
	  __funk2.operating_system.processor_thread__current_fiber[pool_index] = fiber;
	  //printf("\n  got fiber lock.");
	  if (raw__larva__is_type(cause, f2fiber__value(fiber, cause))) {
	    //printf("\nfiber paused due to larva in value register.");
	  } else {
	    if ((! f2fiber__is_complete(fiber, cause))) {
	      //if (processor) {printf("\nprocessor "); f2__write(nil, f2processor__desc(processor));} else {printf("\nunknown processor");} printf(" executing fiber 0x%X", (int)fiber); fflush(stdout);
	      
	      did_something = __funk2.globalenv.true__symbol;
	      
	      u64 begin_execution_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
	      
	      scheduler_fast_loop_exit_reason_t exit_reason = execute_next_bytecodes__helper__fast_loop(cause, fiber);
	      
	      u64 end_execution_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
	      
	      f2ptr execution_nanoseconds    = f2fiber__execution_nanoseconds(fiber, cause);
	      u64   execution_nanoseconds__i = f2integer__i(execution_nanoseconds, cause);
	      
	      pause_gc();
	      f2fiber__execution_nanoseconds__set(fiber, cause, f2integer__new(cause, execution_nanoseconds__i + (end_execution_nanoseconds_since_1970 - begin_execution_nanoseconds_since_1970)));
	      f2fiber__last_executed_time__set(fiber, cause, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970())));
	      resume_gc();
	      
	      if(exit_reason == exit_reason__found_larva) {
		need_to_launch_larva_handling_critic_fiber = 1;
	      }
	      
	    } else {
	      if (! f2fiber__is_zombie(fiber, cause)) {
		f2fiber__is_zombie__set(fiber, cause, __funk2.globalenv.true__symbol);
	      } else {
		//printf("\n  fiber completed.");
		if (! f2fiber__keep_undead(fiber, cause)) {
		  f2ptr last_executed_time = f2fiber__last_executed_time(fiber, cause);
		  if (last_executed_time) {
		    f2ptr nanoseconds_since_1970 = f2time__nanoseconds_since_1970(last_executed_time, cause);
		    u64 nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
		    if (raw__nanoseconds_since_1970() - nanoseconds_since_1970__i > 1 * nanoseconds_per_second) {
		      // anytime a fiber is removed from processor active fibers, it should be removed from it's cause so that it can be garbage collected.
		      f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
		      if (fiber_cause) {
			f2__cause__remove_fiber(cause, fiber_cause, fiber);
		      }
		      // bug: removing a fiber here seems to drop needed fibers sometimes.  (why?)
		      {
		      	f2ptr processor__active_fibers_mutex;
		      	int lock_failed;
		      	do {
		      	  //f2__global_scheduler__execute_mutex__lock(cause);
		      	  processor__active_fibers_mutex = f2processor__active_fibers_mutex(processor, cause);
		      	  lock_failed = f2mutex__trylock(processor__active_fibers_mutex, cause);
		      	  //f2__global_scheduler__execute_mutex__unlock(cause);
		      	  if (lock_failed) {
		      	    f2__sleep(1);
		      	  }
		      	} while (lock_failed);
		      	if (f2processor__active_fibers_prev(processor, cause)) {
		      	  f2cons__cdr__set(f2processor__active_fibers_prev(processor, cause), cause, f2cons__cdr(f2processor__active_fibers_iter(processor, cause), cause));
		      	} else {
		      	  f2processor__active_fibers__set(processor, cause, f2cons__cdr(f2processor__active_fibers_iter(processor, cause), cause));
		      	}
		      	f2mutex__unlock(processor__active_fibers_mutex, cause);
		      }
		      prev_fiber_iter__already_set = 1;
		    }
		  }
		}
	      }
	    }
	  }
	  __funk2.operating_system.processor_thread__current_fiber[pool_index] = popped_fiber;
	}
      } else { // (fiber__paused)
      }
      f2mutex__unlock(f2fiber__execute_mutex(fiber, cause), cause);
    } else {
      //printf("\nfiber locked couldn't execute...");
    }
    
    if(need_to_launch_larva_handling_critic_fiber) {
      f2ptr critics = f2fiber__critics(fiber, cause);
      if (critics) {
	f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
	printf("\nlarva found in fiber and fiber has a critic, so launching critic fiber in serial."); fflush(stdout);
	printf("\n  critic="); f2__print(cause, nil, critics); fflush(stdout);
	pause_gc();
	f2ptr new_fiber = f2__fiber__new(fiber_cause, fiber, f2fiber__env(fiber, cause), critics, f2cons__new(cause, fiber, nil));
	resume_gc();
	{
	  f2ptr processor__active_fibers_mutex;
	  int lock_failed;
	  do {
	    processor__active_fibers_mutex = f2processor__active_fibers_mutex(processor, cause);
	    lock_failed = f2mutex__trylock(processor__active_fibers_mutex, cause);
	    if (lock_failed) {
	      f2__sleep(1);
	    }
	  } while (lock_failed);
	  pause_gc();
	  f2processor__active_fibers__set(processor, cause, f2cons__new(cause, new_fiber, f2processor__active_fibers(processor, cause)));
	  resume_gc();
	  f2mutex__unlock(processor__active_fibers_mutex, cause);
	}	
	//printf("\n  processor="); f2__print(cause, processor); fflush(stdout);
      } else {
	f2__print(cause, nil, fiber);
	printf("\nlarva found in fiber and fiber has no critics, so doing nothing."); fflush(stdout);
	f2ptr larva = f2fiber__value(fiber, cause);
	if (! raw__larva__is_type(cause, larva)) {
	  printf("\n  larva is not a larva."); fflush(stdout);
	} else {
	  u64 raw_type = f2larva__larva_type(larva, cause);
	  printf("\n  larva type=" u64__fstr, raw_type); fflush(stdout);
	  if (raw_type == 23) {
	    printf("\n  larva is symbol-undefined type"); fflush(stdout);
	    printf(", and last symbol was: "); fflush(stdout);
	    f2__print(nil, nil, __funk2.primobject__environment.environment__last_23_larva_symbol); fflush(stdout);
	  }
	}
      }
    }
    
    if (! prev_fiber_iter__already_set) {
      f2processor__active_fibers_prev__set(processor, cause, f2processor__active_fibers_iter(processor, cause));
    }
    
    f2processor__active_fibers_iter__set(processor, cause, f2processor__active_fibers_next(processor, cause));
  }
  //pool__resume_gc(this_processor_thread__pool_index());
  
  //if (did_something) {
  //printf("\nprocessor__execute_next_bytecodes: processor %d (%d) fiber_num = %d", this_processor_thread__pool_index(), processor, fiber_num);
  //}
  return did_something;
}

void* processor__start_routine(void *ptr) {
  while (__funk2.memory.bootstrapping_mode) {
    sched_yield();
    f2__sleep(1);
  }
  f2ptr cause     = nil;
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
  release__assert(pool_index == this_processor_thread__pool_index(), nil, "pool_index does not match pthread_self() generated pool index.");
  
#ifdef DEBUG_SCHEDULER
  printf("\nstarting processor %d (%d)", this_processor_thread__pool_index(), processor); fflush(stdout);
#endif // DEBUG_SCHEDULER
  while(1) {
    f2ptr did_something = nil;
    do {
      did_something = f2processor__execute_next_bytecodes(processor, cause);
      funk2_scheduler_thread_controller__check_user_wait_politely(&(__funk2.scheduler_thread_controller));
      f2__sleep(1);
      sched_yield();
    } while (did_something);
    //printf("\nprocessor %d sleeping", this_processor_thread__pool_index()); fflush(stdout);
    //printf("\nprocessor__start_routine: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
    f2__sleep(100000);
    sched_yield();
  }
  return nil;
}

void f2__scheduler__yield(f2ptr cause) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  if(! f2processor__execute_next_bytecodes(processor, cause)) {
    //f2ptr processor = f2__global_scheduler__this_processor();
    //printf("\nscheduler__yield: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
    //f2__sleep(1000); // maybe this should be the average time to execute f2scheduler__execute_next_bytecodes (when it returns True)?
    sched_yield();
    f2__sleep(1);
    if (__funk2.user_thread_controller.please_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
      funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
    }
  }
}

f2ptr f2__scheduler__active_fibers(f2ptr cause) {
  f2ptr processors         = f2scheduler__processors(__funk2.operating_system.scheduler, cause);
  u64   processors__length = raw__array__length(cause, processors);
  f2ptr seq                = nil;
  u64   processors_index;
  for (processors_index = 0; processors_index < processors__length; processors_index ++) {
    f2ptr processor = raw__array__elt(cause, processors, processors_index);
    f2ptr active_fibers = f2processor__active_fibers(processor, cause);
    {
      f2ptr iter = active_fibers;
      while (iter) {
	f2ptr fiber = f2__cons__car(cause, iter);
	seq = f2cons__new(cause, fiber, seq);
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return seq;
}
def_pcfunk0(scheduler__active_fibers, return f2__scheduler__active_fibers(this_cause));

void f2__scheduler__complete_fiber(f2ptr cause, f2ptr fiber) {
  boolean_t complete = 0;
  do {
    if(f2mutex__trylock(f2fiber__execute_mutex(fiber, cause), cause) == 0) {
      if(f2fiber__is_complete(fiber, cause)) {
	complete = 1;
      }
      f2mutex__unlock(f2fiber__execute_mutex(fiber, cause), cause);
    }
    if (! complete) {
      f2__scheduler__yield(cause);
    }
  } while (!complete);
}

void f2processor__start_new_processor_thread(f2ptr cause, long processor_index) {
  funk2_processor_thread_t* new_processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), processor__start_routine, (void*)(long)processor_index);
  //pthread_t raw_pthread;
  //if(pthread_create(&raw_pthread, NULL, (pthread_start_routine)processor__start_routine, (void*)(long)processor_index)) {
  //  error(nil, "couldn't create processor pthread.");
  //}
  pause_gc();
  f2ptr processor_thread = f2pointer__new(cause, to_ptr(new_processor_thread));
  f2ptr processor = raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), processor_index);
  f2processor__processor_thread__set(processor, cause, processor_thread);
  resume_gc();
}

//void f2__scheduler__exec_with_main_pthread(f2ptr cause) {
//  processor__start_routine((void*)(long)this_pthread__pool_index());
//}

void f2__scheduler__start_processors() {
  pause_gc();
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  int i;
  for (i = 0; i < scheduler_processor_num; i ++) {
    f2processor__start_new_processor_thread(cause, i);
  }
  resume_gc();
}

void f2__scheduler__stop_processors() {
  status("f2__scheduler__stop_processors note: doing nothing.");
}

void f2__scheduler__reinitialize_globalvars() {
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  
  __funk2.operating_system.scheduler__symbol = f2symbol__new(cause, strlen("scheduler:global_scheduler"), (u8*)"scheduler:global_scheduler");
  __funk2.operating_system.scheduler         = environment__safe_lookup_var_value(cause, global_environment(), __funk2.operating_system.scheduler__symbol);
  
}

void f2__scheduler__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "scheduler", "", &f2__scheduler__reinitialize_globalvars);
  
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  
  f2ptr processors = raw__array__new(cause, scheduler_processor_num);
  
  f2ptr event_buffer = raw__circular_buffer__new_empty(cause, 1024);
  
  f2ptr scheduler = f2scheduler__new(cause, processors, f2mutex__new(cause), nil, f2mutex__new(cause), event_buffer);
  
  int i;
  for (i = 0; i < scheduler_processor_num; i ++) {
    f2ptr processor = f2processor__new(cause, 
				       scheduler,
				       nil,
				       f2mutex__new(cause),
				       nil, // active_fibers
				       nil, // active_fibers_iter
				       nil, // active_fibers_prev
				       nil, // active_fibers_next
				       f2mutex__new(cause),
				       nil,
				       f2integer__new(cause, i),
				       f2integer__new(cause, i));
    raw__array__elt__set(cause, processors, i, processor);
  }
  
  __funk2.operating_system.scheduler__symbol = f2symbol__new(cause, strlen("scheduler:global_scheduler"), (u8*)"scheduler:global_scheduler");
  
  environment__add_var_value(cause, global_environment(), __funk2.operating_system.scheduler__symbol, scheduler);
  
  __funk2.operating_system.scheduler = environment__safe_lookup_var_value(cause, global_environment(), __funk2.operating_system.scheduler__symbol);
  
  f2__scheduler__reinitialize_globalvars();
  
  f2__primcfunk__init__0(scheduler__active_fibers, "returns a new list of all currently active fibers.");
}

void f2__scheduler__destroy() {
  f2__scheduler__stop_processors();
}



