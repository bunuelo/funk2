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
    this->processor_thread__current_thread[i] = nil;
  }
}

void funk2_operating_system__destroy(funk2_operating_system_t* this) {
}


f2ptr f2__global_scheduler__this_processor(f2ptr cause) {
  return raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), this_processor_thread__pool_index());
}

void f2__processor__add_active_thread__thread_unsafe(f2ptr cause, f2ptr this, f2ptr thread) {
  f2ptr thread_cause = f2thread__cause_reg(thread, cause);
  if (thread_cause) {
    f2__cause__add_thread(cause, thread_cause, thread);
  }
  //f2ptr active_threads_mutex = f2processor__active_threads_mutex(this, cause);
  //f2mutex__lock(active_threads_mutex, cause);
  pause_gc();
  f2processor__active_threads__set(this, cause, f2cons__new(cause, thread, f2processor__active_threads(this, cause)));
  resume_gc();
  //f2mutex__unlock(active_threads_mutex, cause);
}

void f2__processor__add_active_thread(f2ptr cause, f2ptr this, f2ptr thread) {
  f2ptr active_threads_mutex = f2processor__active_threads_mutex(this, cause);
  f2mutex__lock(active_threads_mutex, cause);
  f2__processor__add_active_thread__thread_unsafe(cause, this, thread);
  f2mutex__unlock(active_threads_mutex, cause);
}

boolean_t f2__processor__remove_active_thread__thread_unsafe(f2ptr cause, f2ptr this, f2ptr thread) {
  f2ptr thread_cause = f2thread__cause_reg(thread, cause);
  if (thread_cause) {
    f2__cause__remove_thread(cause, thread_cause, thread);
  }
  boolean_t found_and_removed_thread = boolean__false;
  //f2ptr active_threads_mutex = f2processor__active_threads_mutex(this, cause);
  //f2mutex__lock(active_threads_mutex, cause);
  f2ptr active_threads_iter = f2processor__active_threads(this, cause);
  f2ptr active_threads_prev = nil;
  while (active_threads_iter) {
    f2ptr active_thread       = f2cons__car(active_threads_iter, cause);
    f2ptr active_threads_next = f2cons__cdr(active_threads_iter, cause);
    if (thread == active_thread) {
      if (active_threads_prev) {
	f2cons__cdr__set(active_threads_prev, cause, active_threads_next);
      } else {
	f2processor__active_threads__set(this, cause, active_threads_next);
      }
      found_and_removed_thread = boolean__true;
    }
    active_threads_iter = active_threads_next;
  }
  //f2mutex__unlock(active_threads_mutex, cause);
  return found_and_removed_thread;
}

boolean_t f2__processor__remove_active_thread(f2ptr cause, f2ptr this, f2ptr thread) {
  f2ptr active_threads_mutex = f2processor__active_threads_mutex(this, cause);
  f2mutex__lock(active_threads_mutex, cause);
  boolean_t result = f2__processor__remove_active_thread__thread_unsafe(cause, this, thread);
  f2mutex__unlock(active_threads_mutex, cause);
  return result;
}

u64 raw__processor__active_threads__length(f2ptr cause, f2ptr processor) {
  f2ptr processor__active_threads_mutex;
  processor__active_threads_mutex = f2processor__active_threads_mutex(processor, cause);
  f2mutex__lock(processor__active_threads_mutex, cause);
  f2ptr active_threads = f2processor__active_threads(processor, cause);
  u64 thread_num = raw__length(cause, active_threads);
  f2mutex__unlock(processor__active_threads_mutex, cause);
  return thread_num;
}

f2ptr f2__scheduler__processor_with_fewest_threads(f2ptr cause, f2ptr scheduler) {
  f2ptr processors = f2scheduler__processors(scheduler, cause);
  u64 processors__length = raw__array__length(cause, processors);
  u64   min_length    = 0xffffffffffffffffull;
  f2ptr min_processor = nil;
  u64 i;
  status("processor thread list:");
  for (i = 0; i < processors__length; i ++) {
    f2ptr processor = raw__array__elt(cause, processors, i);
    f2ptr active_threads = f2processor__active_threads(processor, cause);
    u64 threads__length = raw__length(cause, active_threads);
    status("  processor pool_index=" s64__fstr " active_thread_num=" u64__fstr ".", f2integer__i(f2processor__pool_index(processor, cause), cause), threads__length);
    if (threads__length < min_length) {
      min_length = threads__length;
      min_processor = processor;
    }
  }
  return min_processor;
}

void f2__global_scheduler__add_thread_serial(f2ptr cause, f2ptr thread) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  f2__processor__add_active_thread(cause, processor, thread);
}

void f2__scheduler__add_thread_to_least_used_processor(f2ptr cause, f2ptr this, f2ptr thread) {
  f2ptr processor = f2__scheduler__processor_with_fewest_threads(cause, this);
  status("[adding thread to least used processor " s64__fstr "]", f2integer__i(f2processor__pool_index(processor, cause), cause));
  f2__processor__add_active_thread(cause, processor, thread);
}

void f2__global_scheduler__add_thread_parallel(f2ptr cause, f2ptr thread) {
  f2__scheduler__add_thread_to_least_used_processor(cause, __funk2.operating_system.scheduler, thread);
}

void f2__global_scheduler__execute_mutex__lock(f2ptr cause) {
  funk2_processor_mutex__lock(&(__funk2.operating_system.scheduler__execute_mutex));
}

void f2__global_scheduler__execute_mutex__unlock(f2ptr cause) {
  funk2_processor_mutex__unlock(&(__funk2.operating_system.scheduler__execute_mutex));
}

f2ptr f2__scheduler__processor_thread_current_thread(int pool_index) {
  f2ptr thread = __funk2.operating_system.processor_thread__current_thread[pool_index];
  if (! thread) {
    error(nil, "f2__scheduler__processor_thread_current_thread: thread=nil");
  }
  return thread;
}


void execute_next_bytecodes__helper__found_larva_in_thread(f2ptr cause, f2ptr thread) {
  f2ptr larva = f2thread__value(thread, cause);
  f2thread__paused__set(thread, cause, __funk2.globalenv.true__symbol);
  f2ptr critics = f2thread__critics(thread, cause);
  if (critics) {
    pause_gc();
    f2thread__value__set(thread, cause, f2bug__new(cause, f2integer__new(cause, f2larva__type(larva, cause))));
    resume_gc();
  } else {
    f2thread__program_counter__set(thread, cause, nil);
  }
}

typedef enum scheduler_fast_loop_exit_reason_e {
  exit_reason__none = 0,
  exit_reason__is_complete,
  exit_reason__too_many_loops,
  exit_reason__reached_yield,
  exit_reason__found_larva
} scheduler_fast_loop_exit_reason_t;

scheduler_fast_loop_exit_reason_t execute_next_bytecodes__helper__fast_loop(f2ptr cause, f2ptr thread) {
  scheduler_fast_loop_exit_reason_t exit_reason = exit_reason__none;
  
  int i = 1000;
  while (! exit_reason) {
    if(i == 0) {
      exit_reason = exit_reason__too_many_loops;
      break;
    } else if (f2__thread__execute_next_bytecode(cause, thread)) {
      exit_reason = exit_reason__reached_yield;
      break;
    } else if (raw__larva__is_type(cause, f2thread__value(thread, cause))) {
      execute_next_bytecodes__helper__found_larva_in_thread(cause, thread);
      exit_reason = exit_reason__found_larva;
      break;
    } else if (f2thread__is_complete(thread, cause)) {
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
  f2ptr did_something    = nil;
  {
    f2__global_scheduler__execute_mutex__lock(cause);
    f2__global_scheduler__execute_mutex__unlock(cause);
  }
  f2ptr thread_iter      = f2processor__active_threads(processor, cause);
  f2ptr prev_thread_iter = nil;
  int thread_num         = 0;
  while (thread_iter) {
    f2ptr next_thread_iter = f2cons__cdr(thread_iter, cause);
    thread_num ++;
    f2ptr thread = f2cons__car(thread_iter, cause);
    int   prev_thread_iter__already_set = 0;
    boolean_t  need_to_launch_larva_handling_critic_thread = 0;
    if (f2mutex__trylock(f2thread__execute_mutex(thread, cause), cause) == 0) { // successful lock
      if (! f2thread__paused(thread, cause)) {
	f2ptr sleep_until_time = f2thread__sleep_until_time(thread, cause);
	boolean_t thread_needs_sleep = boolean__false;
	if (sleep_until_time) {
	  f2ptr nanoseconds_since_1970    = f2time__nanoseconds_since_1970(sleep_until_time, cause);
	  s64   nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
	  if (raw__nanoseconds_since_1970() >= nanoseconds_since_1970__i) {
	    f2thread__sleep_until_time__set(thread, cause, nil);
	  } else {
	    thread_needs_sleep = boolean__true;
	  }
	}
	if (! thread_needs_sleep) {
	  int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
	  release__assert(pool_index == this_processor_thread__pool_index(), thread, "f2processor__execute_next_bytecodes: pool_index != this_processor_thread__pool_index().");
	  f2ptr popped_thread = __funk2.operating_system.processor_thread__current_thread[pool_index];
	  __funk2.operating_system.processor_thread__current_thread[pool_index] = thread;
	  //printf("\n  got thread lock.");
	  if (raw__larva__is_type(cause, f2thread__value(thread, cause))) {
	    //printf("\nthread paused due to larva in value register.");
	  } else {
	    if ((! f2thread__is_complete(thread, cause))) {
	      //if (processor) {printf("\nprocessor "); f2__write(nil, f2processor__desc(processor));} else {printf("\nunknown processor");} printf(" executing thread 0x%X", (int)thread); fflush(stdout);
	      
	      did_something = __funk2.globalenv.true__symbol;
	      
	      scheduler_fast_loop_exit_reason_t exit_reason = execute_next_bytecodes__helper__fast_loop(cause, thread);
	      
	      pause_gc();
	      f2thread__last_executed_time__set(thread, cause, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970())));
	      resume_gc();
	      
	      if(exit_reason == exit_reason__found_larva) {
		need_to_launch_larva_handling_critic_thread = 1;
	      }
	      
	    } else {
	      if (! f2thread__is_zombie(thread, cause)) {
		f2thread__is_zombie__set(thread, cause, __funk2.globalenv.true__symbol);
	      } else {
		//printf("\n  thread completed.");
		if (! f2thread__keep_undead(thread, cause)) {
		  f2ptr last_executed_time = f2thread__last_executed_time(thread, cause);
		  if (last_executed_time) {
		    f2ptr nanoseconds_since_1970 = f2time__nanoseconds_since_1970(last_executed_time, cause);
		    u64 nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
		    if (raw__nanoseconds_since_1970() - nanoseconds_since_1970__i > 1 * nanoseconds_per_second) {
		      // anytime a thread is removed from processor active threads, it should be removed from it's cause so that it can be garbage collected.
		      f2ptr thread_cause = f2thread__cause_reg(thread, cause);
		      if (thread_cause) {
			f2__cause__remove_thread(cause, thread_cause, thread);
		      }
		      // bug: removing a thread here seems to drop needed threads sometimes.  (why?)
		      {
		      	f2ptr processor__active_threads_mutex;
		      	int lock_failed;
		      	do {
		      	  //f2__global_scheduler__execute_mutex__lock(cause);
		      	  processor__active_threads_mutex = f2processor__active_threads_mutex(processor, cause);
		      	  lock_failed = f2mutex__trylock(processor__active_threads_mutex, cause);
		      	  //f2__global_scheduler__execute_mutex__unlock(cause);
		      	  if (lock_failed) {
		      	    f2__sleep(1);
		      	  }
		      	} while (lock_failed);
		      	if (prev_thread_iter) {
		      	  f2cons__cdr__set(prev_thread_iter, cause, f2cons__cdr(thread_iter, cause));
		      	} else {
		      	  f2processor__active_threads__set(processor, cause, f2cons__cdr(thread_iter, cause));
		      	}
		      	f2mutex__unlock(processor__active_threads_mutex, cause);
		      }
		      prev_thread_iter__already_set = 1;
		    }
		  }
		}
	      }
	    }
	  }
	  __funk2.operating_system.processor_thread__current_thread[pool_index] = popped_thread;
	}
      } else { // (thread__paused)
      }
      f2mutex__unlock(f2thread__execute_mutex(thread, cause), cause);
    } else {
      //printf("\nthread locked couldn't execute...");
    }
    
    if(need_to_launch_larva_handling_critic_thread) {
      f2ptr critics = f2thread__critics(thread, cause);
      if (critics) {
	f2ptr thread_cause = f2thread__cause_reg(thread, cause);
	printf("\nlarva found in thread and thread has a critic, so launching critic thread in serial."); fflush(stdout);
	printf("\n  critic="); f2__print(cause, critics); fflush(stdout);
	pause_gc();
	f2ptr new_thread = f2__thread__new(thread_cause, thread, f2thread__env(thread, cause), critics, f2cons__new(cause, thread, nil));
	resume_gc();
	{
	  f2ptr processor__active_threads_mutex;
	  int lock_failed;
	  do {
	    processor__active_threads_mutex = f2processor__active_threads_mutex(processor, cause);
	    lock_failed = f2mutex__trylock(processor__active_threads_mutex, cause);
	    if (lock_failed) {
	      f2__sleep(1);
	    }
	  } while (lock_failed);
	  pause_gc();
	  f2processor__active_threads__set(processor, cause, f2cons__new(cause, new_thread, f2processor__active_threads(processor, cause)));
	  resume_gc();
	  f2mutex__unlock(processor__active_threads_mutex, cause);
	}	
	//printf("\n  processor="); f2__print(cause, processor); fflush(stdout);
      } else {
	f2__print(cause, thread);
	printf("\nlarva found in thread and thread has no critics, so doing nothing."); fflush(stdout);
	f2ptr larva = f2thread__value(thread, cause);
	if (! raw__larva__is_type(cause, larva)) {
	  printf("\n  larva is not a larva."); fflush(stdout);
	} else {
	  u64 raw_type = f2larva__type(larva, cause);
	  printf("\n  larva type=" u64__fstr, raw_type); fflush(stdout);
	  if (raw_type == 23) {
	    printf("\n  larva is symbol-undefined type"); fflush(stdout);
	    printf(", and last symbol was: "); fflush(stdout);
	    f2__print(nil, __funk2.primobject__environment.environment__last_23_larva_symbol); fflush(stdout);
	  }
	}
      }
    }
    
    if (! prev_thread_iter__already_set) {
      prev_thread_iter = thread_iter;
    }
    
    thread_iter = next_thread_iter;
  }
  //pool__resume_gc(this_processor_thread__pool_index());
  
  //if (did_something) {
  //printf("\nprocessor__execute_next_bytecodes: processor %d (%d) thread_num = %d", this_processor_thread__pool_index(), processor, thread_num);
  //}
  return did_something;
}

void* processor__start_routine(void *ptr) {
  while (__funk2.memory.bootstrapping_mode) {
    sched_yield();
  }
  f2ptr cause     = nil;
  f2ptr processor = f2__global_scheduler__this_processor(cause);
#ifdef DEBUG_SCHEDULER
  printf("\nstarting processor %d (%d)", this_processor_thread__pool_index(), processor); fflush(stdout);
#endif // DEBUG_SCHEDULER
  while(1) {
    f2ptr did_something = nil;
    do {
      did_something = f2processor__execute_next_bytecodes(processor, cause);
      f2__sleep(1);
      sched_yield();
    } while (did_something);
    //printf("\nprocessor %d sleeping", this_processor_thread__pool_index()); fflush(stdout);
    //printf("\nprocessor__start_routine: processor %d (%d) sleeping (thread_num: %d)", this_processor_thread__pool_index(), processor, raw__length(f2processor__threads(processor))); fflush(stdout);
    f2__sleep(100000);
    sched_yield();
  }
  return nil;
}

void f2__scheduler__yield(f2ptr cause) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  if(! f2processor__execute_next_bytecodes(processor, cause)) {
    //f2ptr processor = f2__global_scheduler__this_processor();
    //printf("\nscheduler__yield: processor %d (%d) sleeping (thread_num: %d)", this_processor_thread__pool_index(), processor, raw__length(f2processor__threads(processor))); fflush(stdout);
    //f2__sleep(1000); // maybe this should be the average time to execute f2scheduler__execute_next_bytecodes (when it returns True)?
    sched_yield();
    f2__sleep(1);
    if (__funk2.memory.user_thread_controller.please_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
      funk2_user_thread_controller__user_wait_politely(&(__funk2.memory.user_thread_controller));
    }
  }
}

void f2__scheduler__complete_thread(f2ptr cause, f2ptr thread) {
  boolean_t complete = 0;
  do {
    if(f2mutex__trylock(f2thread__execute_mutex(thread, cause), cause) == 0) {
      if(f2thread__is_complete(thread, cause)) {
	complete = 1;
      }
      f2mutex__unlock(f2thread__execute_mutex(thread, cause), cause);
    }
    if (! complete) {
      f2__scheduler__yield(cause);
    }
  } while (!complete);
}

void f2__print_threads_stacks() {
  //f2ptr threads = f2__global_scheduler__threads();
  //while(threads) {
  //  f2ptr thread = f2cons__car(threads);
  //  printf("\nthread #x%x stack:", (int)thread);
  //  f2ptr env = f2thread__env(thread);
  //  f2__print_environment_stack(global_environment(), env);
  //  threads = f2cons__cdr(threads);
  //}
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
  
  funk2_processor_mutex__init(&(__funk2.operating_system.scheduler__execute_mutex));
  f2__global_scheduler__execute_mutex__lock(initial_cause());
  
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
				       nil,
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
  
  f2__global_scheduler__execute_mutex__unlock(cause);
  
  // **
  
  //f2__primcfunk__init(global_scheduler__add_thread_to_pool);
  //f2__primcfunk__init(global_scheduler__remove_thread_from_pool);
  //f2__primcfunk__init(global_scheduler__thread_num_in_pool);
  
}

void f2__scheduler__destroy() {
  f2__scheduler__stop_processors();
  f2__global_scheduler__execute_mutex__lock(initial_cause()); // unlock to restart...
}



