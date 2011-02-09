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


// scheduler

def_primobject_1_slot(scheduler, processors);

f2ptr f2__scheduler__new(f2ptr cause, f2ptr processors) {return f2scheduler__new(cause, processors);}
def_pcfunk1(scheduler__new, processors, return f2__scheduler__new(this_cause, processors));


f2ptr raw__scheduler__active_fibers(f2ptr cause, f2ptr this) {
  f2ptr processors         = f2scheduler__processors(this, cause);
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

f2ptr f2__scheduler__active_fibers(f2ptr cause, f2ptr this) {
  if (! raw__scheduler__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__scheduler__active_fibers(cause, this);
}
def_pcfunk1(scheduler__active_fibers, this, return f2__scheduler__active_fibers(this_cause, this));


f2ptr raw__scheduler__processor_with_fewest_fibers(f2ptr cause, f2ptr this) {
  f2ptr processors = f2scheduler__processors(this, cause);
  u64 processors__length = raw__array__length(cause, processors);
  u64   min_length    = 0xffffffffffffffffull;
  f2ptr min_processor = nil;
  u64 i;
  for (i = 0; i < processors__length; i ++) {
    f2ptr processor = raw__array__elt(cause, processors, i);
    f2ptr active_fibers = f2processor__active_fibers(processor, cause);
    u64 fibers__length = raw__simple_length(cause, active_fibers);
    if (fibers__length < min_length) {
      min_length = fibers__length;
      min_processor = processor;
    }
  }
  return min_processor;
}

f2ptr f2__scheduler__processor_with_fewest_fibers(f2ptr cause, f2ptr this) {
  if (! raw__scheduler__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__scheduler__processor_with_fewest_fibers(cause, this);
}
def_pcfunk1(scheduler__processor_with_fewest_fibers, this, return f2__scheduler__processor_with_fewest_fibers(this_cause, this));


f2ptr raw__scheduler__add_fiber_to_least_used_processor(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr processor = raw__scheduler__processor_with_fewest_fibers(cause, this);
  return raw__processor__add_active_fiber(cause, processor, fiber);
}

f2ptr f2__scheduler__add_fiber_to_least_used_processor(f2ptr cause, f2ptr this, f2ptr fiber) {
  if ((! raw__scheduler__is_type(cause, this)) ||
      (! raw__fiber__is_type(cause, fiber))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__scheduler__add_fiber_to_least_used_processor(cause, this, fiber);
}
def_pcfunk2(scheduler__add_fiber_to_least_used_processor, this, fiber, return f2__scheduler__add_fiber_least_used_processor(this_cause, this, fiber));


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
  {char* slot_name = "active_fibers";                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_scheduler.active_fibers__funk);}
  {char* slot_name = "processor_with_fewest_fibers";      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processor_with_fewest_fibers__funk);}
  {char* slot_name = "add_fiber_to_least_used_processor"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_scheduler.add_fiber_to_least_used_processor__funk);}
  {char* slot_name = "terminal_print_with_frame";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_scheduler.terminal_print_with_frame__funk);}
  return this;
}


// global_scheduler

f2ptr f2__global_scheduler__active_fibers(f2ptr cause) {
  return raw__scheduler__active_fibers(cause, __funk2.operating_system.scheduler);
}
def_pcfunk0(global_scheduler__active_fibers, return f2__global_scheduler__active_fibers(this_cause));


f2ptr f2__global_scheduler__this_processor(f2ptr cause) {
  if (__funk2.operating_system.scheduler == nil) {
    error(nil, "f2__global_scheduler__this_processor error: __funk2.operating_system.scheduler == nil");
  }
  return raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), this_processor_thread__pool_index());
}
def_pcfunk0(global_scheduler__this_processor, return f2__global_scheduler__this_processor(this_cause));


f2ptr raw__global_scheduler__add_fiber_serial(f2ptr cause, f2ptr fiber) {
  f2ptr processor = f2__global_scheduler__this_processor(cause);
  return raw__processor__add_active_fiber(cause, processor, fiber);
}

f2ptr f2__global_scheduler__add_fiber_serial(f2ptr cause, f2ptr fiber) {
  if (! raw__fiber__is_type(cause, fiber)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__global_scheduler__add_fiber_serial(cause, fiber);
}
def_pcfunk1(global_scheduler__add_fiber_serial, fiber, return f2__global_scheduler__add_fiber_serial(this_cause, fiber));


f2ptr raw__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber) {
  return raw__scheduler__add_fiber_to_least_used_processor(cause, __funk2.operating_system.scheduler, fiber);
}

f2ptr f2__global_scheduler__add_fiber_parallel(f2ptr cause, f2ptr fiber) {
  if (! raw__fiber__is_type(cause, fiber)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__global_scheduler__add_fiber_parallel(cause, fiber);
}
def_pcfunk1(global_scheduler__add_fiber_parallel, fiber, return f2__global_scheduler__add_fiber_parallel(this_cause, fiber));


f2ptr raw__global_scheduler__add_fiber(f2ptr cause, f2ptr fiber) {
  return raw__global_scheduler__add_fiber_parallel(cause, fiber);
}

f2ptr f2__global_scheduler__add_fiber(f2ptr cause, f2ptr fiber) {
  if (! raw__fiber__is_type(cause, fiber)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__global_scheduler__add_fiber(cause, fiber);
}
def_pcfunk1(global_scheduler__add_fiber, fiber, return f2__global_scheduler__add_fiber(this_cause, fiber));


f2ptr raw__global_scheduler__remove_fiber(f2ptr cause, f2ptr fiber) {
  f2ptr processor_assignment_index = f2fiber__processor_assignment_index(fiber, cause);
  if (processor_assignment_index == nil) {
    return f2larva__new(cause, 135, nil);
  }
  if (! raw__integer__is_type(cause, processor_assignment_index)) {
    return f2larva__new(cause, 11, nil);
  }
  s64 processor_assignment_index__i = f2integer__i(processor_assignment_index, cause);
  if ((processor_assignment_index__i < 0) ||
      (processor_assignment_index__i >= memory_pool_num)) {
    return f2larva__new(cause, 22, nil);
  }
  f2ptr processor = raw__array__elt(cause, f2scheduler__processors(__funk2.operating_system.scheduler, cause), processor_assignment_index__i);
  return raw__processor__remove_active_fiber(cause, processor, fiber);
}

f2ptr f2__global_scheduler__remove_fiber(f2ptr cause, f2ptr fiber) {
  if (! raw__fiber__is_type(cause, fiber)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__global_scheduler__remove_fiber(cause, fiber);
}
def_pcfunk1(global_scheduler__remove_fiber, fiber, return f2__global_scheduler__remove_fiber(this_cause, fiber));


void raw__global_scheduler__complete_fiber(f2ptr cause, f2ptr fiber) {
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
      f2__this__fiber__yield(cause);
    }
  } while (! complete);
}

f2ptr f2__global_scheduler__complete_fiber(f2ptr cause, f2ptr fiber) {
  if (! raw__fiber__is_type(cause, fiber)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__global_scheduler__complete_fiber(cause, fiber);
  return nil;
}
def_pcfunk1(global_scheduler__complete_fiber, fiber, return f2__global_scheduler__complete_fiber(this_cause, fiber));


f2ptr raw__global_scheduler__processor_thread_current_fiber(int pool_index) {
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
  return raw__scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
}
def_pcfunk0(this__fiber, return f2__this__fiber(this_cause));


void f2__this__fiber__yield(f2ptr cause) {
  funk2_virtual_processor_handler__yield(&(__funk2.virtual_processor_handler));
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
  
  f2__primcfunk__init__0(global_scheduler__active_fibers,             "Returns a new list of all currently active fibers.");
  f2__primcfunk__init__0(global_scheduler__this_processor,            "Returns the processor that is executing the current fiber.");
  f2__primcfunk__init__1(global_scheduler__add_fiber_serial,   fiber, "Adds the given fiber to the current fiber's processor.");
  f2__primcfunk__init__1(global_scheduler__add_fiber_parallel, fiber, "Adds the given fiber to the least used processor.");
  f2__primcfunk__init__1(global_scheduler__add_fiber,          fiber, "Adds the given fiber to the global scheduler.");
  f2__primcfunk__init__1(global_scheduler__remove_fiber,       fiber, "Removes the given fiber from it's assigned processor.");
  f2__primcfunk__init__1(global_scheduler__complete_fiber,     fiber, "Yields until the given fiber is complete.");
  
  f2__primcfunk__init__0(this__fiber, "Returns the currently executing fiber.");
}

void f2__scheduler__destroy() {
}



