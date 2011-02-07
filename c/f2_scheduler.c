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

// funk2_operating_system

void funk2_operating_system__init(funk2_operating_system_t* this) {
  {
    int index;
    for (index = 0; index < memory_pool_num; index++) {
      funk2_processor_mutex__init(&(this->current_fiber_stack__mutex[index]));
      this->current_fiber_stack[index] = NULL;
    }
  }
}

void funk2_operating_system__destroy(funk2_operating_system_t* this) {
  {
    int index;
    for (index = 0; index < memory_pool_num; index++) {
      funk2_processor_mutex__destroy(&(this->current_fiber_stack__mutex[index]));
      {
	funk2_operating_system_current_fiber_cons_t* iter = this->current_fiber_stack[index];
	while (iter) {
	  funk2_operating_system_current_fiber_cons_t* next = iter->next;
	  f2__free(to_ptr(iter));
	  iter = next;
	}
      }
    }
  }
}

void funk2_operating_system__push_current_fiber(funk2_operating_system_t* this, u64 pool_index, f2ptr current_fiber) {
  funk2_operating_system_current_fiber_cons_t* cons = (funk2_operating_system_current_fiber_cons_t*)from_ptr(f2__malloc(sizeof(funk2_operating_system_current_fiber_cons_t)));
  cons->current_fiber = current_fiber;
  funk2_processor_mutex__lock(&(this->current_fiber_stack__mutex[pool_index]));
  cons->next                            = this->current_fiber_stack[pool_index];
  this->current_fiber_stack[pool_index] = cons;
  funk2_processor_mutex__unlock(&(this->current_fiber_stack__mutex[pool_index]));
}

f2ptr funk2_operating_system__pop_current_fiber(funk2_operating_system_t* this, u64 pool_index) {
  funk2_processor_mutex__lock(&(this->current_fiber_stack__mutex[pool_index]));
  funk2_operating_system_current_fiber_cons_t* cons  = this->current_fiber_stack[pool_index];
  if (cons == NULL) {
    error(nil, "funk2_operating_system__pop_current_fiber error: current_fiber_stack is NULL.");
  }
  f2ptr current_fiber                   = cons->current_fiber;
  this->current_fiber_stack[pool_index] = cons->next;
  funk2_processor_mutex__unlock(&(this->current_fiber_stack__mutex[pool_index]));
  f2__free(to_ptr(cons));
  return current_fiber;
}


// processor

def_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);

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

// scheduler

f2ptr f2__scheduler__processor_with_fewest_fibers(f2ptr cause, f2ptr scheduler) {
  f2ptr processors = f2scheduler__processors(scheduler, cause);
  u64 processors__length = raw__array__length(cause, processors);
  u64   min_length    = 0xffffffffffffffffull;
  f2ptr min_processor = nil;
  u64 i;
  //status("processor fiber list:");
  for (i = 0; i < processors__length; i ++) {
    f2ptr processor = raw__array__elt(cause, processors, i);
    f2ptr active_fibers = f2processor__active_fibers(processor, cause);
    u64 fibers__length = raw__simple_length(cause, active_fibers);
    //status("  processor pool_index=" s64__fstr " active_fiber_num=" u64__fstr ".", f2integer__i(f2processor__pool_index(processor, cause), cause), fibers__length);
    if (fibers__length < min_length) {
      min_length = fibers__length;
      min_processor = processor;
    }
  }
  return min_processor;
}


// scheduler

void f2__scheduler__add_fiber_to_least_used_processor(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr processor = f2__scheduler__processor_with_fewest_fibers(cause, this);
  //status("[adding fiber to least used processor " s64__fstr "]", f2integer__i(f2processor__pool_index(processor, cause), cause));
  f2__processor__add_active_fiber(cause, processor, fiber);
}

f2ptr f2__scheduler__processor_thread_current_fiber(int pool_index) {
  funk2_processor_mutex__lock(&(__funk2.operating_system.current_fiber_stack__mutex[pool_index]));
  funk2_operating_system_current_fiber_cons_t* cons  = __funk2.operating_system.current_fiber_stack[pool_index];
  if (cons == NULL) {
    error(nil, "f2__scheduler__processor_thread_current_fiber: this->current_fiber_stack[pool_index]=NULL");
  }
  f2ptr current_fiber = cons->current_fiber;
  funk2_processor_mutex__unlock(&(__funk2.operating_system.current_fiber_stack__mutex[pool_index]));
  return current_fiber;
}


// user functions

f2ptr f2__this__fiber(f2ptr cause) {
  return f2__scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
}


// processor

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
  //status("fiber_num = %d", fiber_num);
  //pool__resume_gc(this_processor_thread__pool_index());
  
  //if (did_something) {
  //printf("\nprocessor__execute_next_bytecodes: processor %d (%d) fiber_num = %d", this_processor_thread__pool_index(), processor, fiber_num);
  //}
  return did_something;
}



// scheduler

def_primobject_1_slot(scheduler, processors);

f2ptr f2__scheduler__new(f2ptr cause, f2ptr processors) {return f2scheduler__new(cause, processors);}
def_pcfunk1(scheduler__new, processors, return f2__scheduler__new(this_cause, processors));


f2ptr raw__scheduler__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "scheduler"),
					       new__symbol(cause, "processors"), f2__scheduler__processors(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__scheduler__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__scheduler__is_type(cause, this)) &&
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__scheduler__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(scheduler__terminal_print_with_frame, this, terminal_print_frame, return f2__scheduler__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2scheduler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2scheduler__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_scheduler.terminal_print_with_frame__funk);}
  return this;
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
  boolean_t complete = boolean__false;
  do {
    if(f2mutex__trylock(f2fiber__execute_mutex(fiber, cause), cause) == 0) {
      if(f2fiber__is_complete(fiber, cause) ||
	 (f2fiber__paused(fiber, cause) && raw__bug__is_type(cause, f2fiber__value(fiber, cause)))) {
	complete = boolean__true;
      }
      f2mutex__unlock(f2fiber__execute_mutex(fiber, cause), cause);
    }
    if (! complete) {
      f2__scheduler__yield(cause);
    }
  } while (! complete);
}

#if defined(F2__USE_VIRTUAL_PROCESSORS)

void f2__scheduler__yield(f2ptr cause) {
  funk2_virtual_processor_handler__yield(&(__funk2.virtual_processor_handler));
}

#else // not F2__USE_VIRTUAL_PROCESSORS


// processor

void* processor__start_routine(void *ptr) {
  status("processor here, waiting for bootstrap to complete before starting.");
  while (__funk2.memory.bootstrapping_mode) {
    raw__fast_spin_sleep_yield();
  }
  status("processor starting.");
  f2ptr cause     = nil;
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  int pool_index = f2integer__i(f2processor__pool_index(processor, cause), cause);
  release__assert(pool_index == this_processor_thread__pool_index(), nil, "pool_index does not match pthread_self() generated pool index.");
  
  status("starting processor " u64__fstr " (" u64__fstr ")", (u64)this_processor_thread__pool_index(), (u64)processor);
  while(1) {
    f2ptr did_something = nil;
    do {
      did_something = f2processor__execute_next_bytecodes(processor, cause);
      funk2_scheduler_thread_controller__check_user_wait_politely(&(__funk2.scheduler_thread_controller));
      raw__fast_spin_sleep_yield();
    } while (did_something);
    //printf("\nprocessor %d sleeping", this_processor_thread__pool_index()); fflush(stdout);
    //printf("\nprocessor__start_routine: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
    raw__spin_sleep_yield();
  }
  return nil;
}


// scheduler

void f2__scheduler__yield(f2ptr cause) {
  if (! __funk2.memory.bootstrapping_mode) {
    f2ptr processor = f2__global_scheduler__this_processor(cause);
    if(! f2processor__execute_next_bytecodes(processor, cause)) {
      //f2ptr processor = f2__global_scheduler__this_processor();
      //printf("\nscheduler__yield: processor %d (%d) sleeping (fiber_num: %d)", this_processor_thread__pool_index(), processor, raw__simple_length(f2processor__fibers(processor))); fflush(stdout);
      //f2__sleep(1000); // maybe this should be the average time to execute f2scheduler__execute_next_bytecodes (when it returns True)?
      raw__fast_spin_sleep_yield();
      if (__funk2.user_thread_controller.please_wait && pthread_self() != __funk2.memory.memory_handling_thread) {
	funk2_user_thread_controller__user_wait_politely(&(__funk2.user_thread_controller));
      }
    }
  }
}


// processor

void f2processor__start_new_processor_thread(f2ptr cause, long processor_index) {
  funk2_processor_thread_t* new_processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), processor__start_routine, (void*)(long)processor_index);
  pause_gc();
  f2ptr processor_thread = f2pointer__new(cause, to_ptr(new_processor_thread));
  f2ptr processor = raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), processor_index);
  f2processor__processor_thread__set(processor, cause, processor_thread);
  resume_gc();
}


// scheduler

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

#endif // F2__USE_VIRTUAL_PROCESSORS


// global_scheduler

f2ptr f2__global_scheduler__this_processor(f2ptr cause) {
  if (__funk2.operating_system.scheduler == nil) {
    error(nil, "f2__global_scheduler__this_processor error: __funk2.operating_system.scheduler == nil");
  }
  return raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), this_processor_thread__pool_index());
}


void f2__global_scheduler__add_fiber_serial(f2ptr cause, f2ptr fiber) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  f2__processor__add_active_fiber(cause, processor, fiber);
}


void f2__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber) {
  f2__scheduler__add_fiber_to_least_used_processor(cause, __funk2.operating_system.scheduler, fiber);
}




// **

void f2__scheduler__initialize_global_symbolic_vars() {
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  
  __processor__symbol = new__symbol(cause, "processor");
  __scheduler__symbol = new__symbol(cause, "scheduler");
}

void f2__scheduler__reinitialize_globalvars() {
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  
  f2__scheduler__initialize_global_symbolic_vars();
  
  __funk2.operating_system.scheduler__symbol = f2symbol__new(cause, strlen("scheduler:global_scheduler"), (u8*)"scheduler:global_scheduler");
  __funk2.operating_system.scheduler         = environment__safe_lookup_var_value(cause, global_environment(), __funk2.operating_system.scheduler__symbol);
}

void f2__scheduler__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "scheduler", "", &f2__scheduler__reinitialize_globalvars);
  
  f2ptr cause = f2_scheduler_c__cause__new(initial_cause());
  f2__scheduler__initialize_global_symbolic_vars();
  
  // processor
  
  initialize_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // scheduler
  
  initialize_primobject_1_slot(scheduler, processors);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // allocate scheduler and processors
  
  f2ptr processors = raw__array__new(cause, scheduler_processor_num);
  
  f2ptr scheduler = f2scheduler__new(cause, processors);
  
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
#if defined(F2__USE_VIRTUAL_PROCESSORS)

#else // not F2__USE_VIRTUAL_PROCESSORS

  f2__scheduler__stop_processors();

#endif // F2__USE_VIRTUAL_PROCESSORS
}



