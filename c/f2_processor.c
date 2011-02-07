// 
// Copyright (c) 2007-2011 Bo Morgan.
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

def_primobject_14_slot(processor,
		       scheduler,
		       processor_thread,
		       active_fibers_mutex,
		       active_fibers,
		       active_fibers_iter,
		       active_fibers_prev,
		       active_fibers_next,
		       newly_paused_fibers,
		       newly_paused_fibers_iter,
		       newly_paused_fibers_next,
		       sleeping_fibers_mutex,
		       sleeping_fibers,
		       pool_index,
		       desc);

f2ptr f2__processor__new(f2ptr cause) {
  return f2processor__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(processor__new, return f2__processor__new(this_cause));


f2ptr raw__processor__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list16__new(cause,
						new__symbol(cause, "print_object_type"),     new__symbol(cause, "processor"),
						new__symbol(cause, "processor_thread"),      f2__processor__processor_thread(     cause, this),
						new__symbol(cause, "active_fibers_mutex"),   f2__processor__active_fibers_mutex(  cause, this),
						new__symbol(cause, "active_fibers"),         f2__processor__active_fibers(        cause, this),
						new__symbol(cause, "sleeping_fibers_mutex"), f2__processor__sleeping_fibers_mutex(cause, this),
						new__symbol(cause, "sleeping_fibers"),       f2__processor__sleeping_fibers(      cause, this),
						new__symbol(cause, "pool_index"),            f2__processor__pool_index(           cause, this),
						new__symbol(cause, "desc"),                  f2__processor__desc(                 cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__processor__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__processor__is_type(cause, this)) &&
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__processor__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(processor__terminal_print_with_frame, this, terminal_print_frame, return f2__processor__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2processor__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2processor__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk);}
  return this;
}


void f2__processor__add_active_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
  if (fiber_cause) {
    f2__cause__add_fiber(cause, fiber_cause, fiber);
  }
  pause_gc();
  f2processor__active_fibers__set(this, cause, f2cons__new(cause, fiber, f2processor__active_fibers(this, cause)));
  f2fiber__processor_assignment_index__set(fiber, cause, f2processor__pool_index(this, cause));
  resume_gc();
}

void f2__processor__add_active_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  if (! raw__processor__is_type(cause, this)) {
    error(nil, "attempted to add fiber to object that is not a processor.");
  }
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
      f2fiber__processor_assignment_index__set(fiber, cause, nil);
      found_and_removed_fiber = boolean__true;
    }
    active_fibers_iter = active_fibers_next;
  }
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

#define execute_next_bytecodes__helper__fast_loop__max_bytecode_count (10*1024)

scheduler_fast_loop_exit_reason_t execute_next_bytecodes__helper__fast_loop(f2ptr cause, f2ptr fiber) {
  //status("bytecode fast loop beginning.");
  scheduler_fast_loop_exit_reason_t exit_reason = exit_reason__none;
  
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
      exit_reason = exit_reason__found_larva;
      break;
    } else if (f2fiber__is_complete(fiber, cause)) {
      exit_reason = exit_reason__is_complete;
      break;
    } 
    i --;
  }
  
  pause_gc();
  {
    f2ptr bytecode_count     = f2fiber__bytecode_count(fiber, cause);
    u64   bytecode_count__i  = f2integer__i(bytecode_count, cause);
    bytecode_count__i       += (execute_next_bytecodes__helper__fast_loop__max_bytecode_count - i);
    bytecode_count           = f2integer__new(cause, bytecode_count__i);
    f2fiber__bytecode_count__set(fiber, cause, bytecode_count);
  }
  resume_gc();
  
  //status("bytecode fast loop done with %d loop fast cycles.", 1000-i);
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
    //status("trying to lock execute mutex for thread.");
    if (f2mutex__trylock(f2fiber__execute_mutex(fiber, cause), cause) == 0) { // successful lock
      //status("successfully locked execute mutex for thread.");
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
	      }
	      
	    } else {
	      //printf("\n  fiber completed.");
	      if (! f2fiber__is_zombie(fiber, cause)) {
		f2fiber__is_zombie__set(fiber, cause, __funk2.globalenv.true__symbol);
	      }
	      if (! f2fiber__keep_undead(fiber, cause)) {
		f2ptr last_executed_time = f2fiber__last_executed_time(fiber, cause);
		if (last_executed_time) {
		  f2ptr nanoseconds_since_1970 = f2time__nanoseconds_since_1970(last_executed_time, cause);
		  u64 nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
		  // This is a hack to avoid accidental fiber removal.  As one would expect, it doesn't really work.
		  if (raw__nanoseconds_since_1970() - nanoseconds_since_1970__i > nanoseconds_per_second) {
		    // anytime a fiber is removed from processor active fibers, it should be removed from it's cause so that it can be garbage collected.
		    f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
		    if (fiber_cause) {
		      f2__cause__remove_fiber(cause, fiber_cause, fiber);
		    }
		    if (f2fiber__is_zombie(fiber, cause)) {
		      f2fiber__is_zombie__set(fiber, cause, nil);
		    }
		    f2fiber__processor_assignment_index__set(fiber, cause, nil);
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
			  raw__fast_spin_sleep_yield();
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
	  
	  funk2_operating_system__pop_current_fiber(&(__funk2.operating_system), pool_index);
	}
      } else { // (fiber__paused)
	f2processor__newly_paused_fibers__set(cause, processor, f2cons__new(cause, f2processor__newly_paused_fibers(cause, processor)));
      }
      f2mutex__unlock(f2fiber__execute_mutex(fiber, cause), cause);
    } else {
      //printf("\nfiber locked couldn't execute...");
    }
    
    if (need_to_launch_larva_handling_critic_fiber) {
      f2ptr cause_reg = f2fiber__cause_reg(fiber, cause);
      f2ptr critics   = cause_reg ? f2cause__critics(cause_reg, cause) : nil;
      if (critics) {
	f2ptr fiber_cause = f2fiber__cause_reg(fiber, cause);
	if (raw__larva__is_type(cause, f2fiber__value(fiber, cause))) {
	  f2ptr larva      = f2fiber__value(fiber, cause);
	  u64   larva_type = raw__larva__larva_type(cause, larva);
	  status("larva type (" u64__fstr ") found in fiber and fiber has a critic, so launching critic fiber in serial.", larva_type);
	}
	//status("\n  critic="); f2__fiber__print(cause, nil, critics); fflush(stdout);
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
	      raw__fast_spin_sleep_yield();
	    }
	  } while (lock_failed);
	  pause_gc();
	  f2processor__active_fibers__set(processor, cause, f2cons__new(cause, new_fiber, f2processor__active_fibers(processor, cause)));
	  resume_gc();
	  f2mutex__unlock(processor__active_fibers_mutex, cause);
	}	
	//printf("\n  processor="); f2__print(cause, processor); fflush(stdout);
      } else {
	char status_msg[1024];
	snprintf(status_msg, 1023, "larva found in fiber and fiber has no critics, so doing nothing.");
	status(status_msg);
      }
    }
    
    if (! prev_fiber_iter__already_set) {
      f2processor__active_fibers_prev__set(processor, cause, f2processor__active_fibers_iter(processor, cause));
    }
    
    f2processor__active_fibers_iter__set(processor, cause, f2processor__active_fibers_next(processor, cause));
  }
  
  // remove newly paused fibers from active list.
  {
    f2processor__newly_paused_fibers_iter__set(processor, cause, f2processor__newly_paused_fibers(processor, cause));
    while (f2processor__newly_paused_fibers_iter(processor, cause)) {
      f2ptr newly_paused_fiber =                                   f2cons__car(f2processor__newly_paused_fibers_iter(processor, cause), cause);
      f2processor__newly_paused_fibers_next__set(processor, cause, f2cons__cdr(f2processor__newly_paused_fibers_iter(processor, cause), cause));
      {
	f2processor__active_fibers_iter__set(processor, cause, f2processor__active_fibers(processor, cause));
	f2processor__active_fibers_prev__set(processor, cause, nil);
	
	while (f2processor__active_fibers_iter(processor, cause)) {
	  f2ptr active_fiber =                                   f2cons__car(f2processor__active_fibers_iter(processor, cause), cause);
	  f2processor__active_fibers_next__set(processor, cause, f2cons__cdr(f2processor__active_fibers_iter(processor, cause), cause));
	  {
	    if (raw__eq(cause, newly_paused_fiber, active_fiber)) {
	      if (f2processor__active_fibers_prev(processor, cause) == nil) {
		f2processor__active_fibers__set(processor, cause, f2processor__active_fibers_next(processor, cause));
	      } else {
		f2cons__cdr__set(f2processor__active_fibers_prev(processor, cause), cause, f2processor__active_fibers_next(processor, cause));
	      }
	    }
	  }
	  f2processor__active_fibers_prev__set(processor, cause, f2processor__active_fibers_iter(processor, cause));
	  f2processor__active_fibers_iter__set(processor, cause, f2processor__active_fibers_next(processor, cause));
	}
      }
      f2processor__newly_paused_fibers_iter__set(processor, cause, f2processor__newly_paused_fibers_next(processor, cause));
    }
    f2processor__newly_paused_fibers__set(processor, cause, nil);
  }
  
  //status("fiber_num = %d", fiber_num);
  //pool__resume_gc(this_processor_thread__pool_index());
  
  //if (did_something) {
  //printf("\nprocessor__execute_next_bytecodes: processor %d (%d) fiber_num = %d", this_processor_thread__pool_index(), processor, fiber_num);
  //}
  return did_something;
}



// **

void f2__processor__reinitialize_globalvars() {
  f2ptr cause = f2_processor_c__cause__new(initial_cause());
  
  __processor__symbol = new__symbol(cause, "processor");
}

void f2__processor__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "processor", "", &f2__processor__reinitialize_globalvars);
  f2__processor__reinitialize_globalvars();
  
  f2ptr cause = f2_processor_c__cause__new(initial_cause());
  
  
  // processor
  
  initialize_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__processor__destroy() {
}



