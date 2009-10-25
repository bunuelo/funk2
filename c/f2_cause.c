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


// cause

def_primobject_13_slot(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_stack, event_buffer_first, event_buffer_last, current_events_mutex, current_events);

f2ptr f2__cause__define(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}
def_pcfunk3(cause__define, this, var, value, return f2__cause__define(this_cause, this, var, value));

f2ptr f2__cause__define__funk(f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.funk_variable__symbol, funkvar, value);
}
def_pcfunk3(cause__define__funk, this, funkvar, value, return f2__cause__define__funk(this_cause, this, funkvar, value));


f2ptr f2__cause__new(f2ptr cause, f2ptr allocate_traced_arrays, f2ptr bytecode_tracing_on, f2ptr memory_tracing_on, f2ptr subscribers, f2ptr imagination_name, f2ptr event_buffer_first, f2ptr event_buffer_last, f2ptr current_events) {
  f2ptr fibers_mutex         = f2mutex__new(cause);
  f2ptr fibers               = nil;
  f2ptr frame                = f2__frame__new(cause);
  f2ptr subscribers_mutex    = f2mutex__new(cause);
  f2ptr current_events_mutex = f2mutex__new(cause);
  return f2cause__new(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_name, event_buffer_first, event_buffer_last, current_events_mutex, current_events);
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source) {
  if (! raw__cause__is_type(cause, source)) {
    return f2larva__new(cause, 333);
  }
  f2ptr allocate_traced_arrays = nil; // default values
  f2ptr bytecode_tracing_on    = nil;
  f2ptr memory_tracing_on      = nil;
  f2ptr subscribers            = nil;
  f2ptr imagination_stack      = nil;
  if (cause) {
    allocate_traced_arrays = f2__cause__allocate_traced_arrays(cause, source);
    bytecode_tracing_on    = f2__cause__bytecode_tracing_on(   cause, source);
    memory_tracing_on      = f2__cause__memory_tracing_on(     cause, source);
    subscribers            = f2__cause__subscribers(           cause, source);
    imagination_stack      = f2__cause__imagination_stack(     cause, source);
  }
  return f2__cause__new(cause,
			allocate_traced_arrays,
			bytecode_tracing_on,
			memory_tracing_on,
			subscribers,
			imagination_stack,
			nil,  // event_buffer_first
			nil,  // event_buffer_last
			nil); // current_events
}

f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fibers_mutex = f2cause__fibers_mutex(this, cause);
  f2mutex__lock(fibers_mutex, cause);
  f2cause__fibers__set(this, cause, f2cons__new(cause, fiber, f2cause__fibers(this, cause)));
  f2mutex__unlock(fibers_mutex, cause);
  return nil;
}

f2ptr f2__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fibers_mutex = f2cause__fibers_mutex(this, cause);
  f2mutex__lock(fibers_mutex, cause);
  f2ptr prev = nil;
  f2ptr iter = f2cause__fibers(this, cause);
  while (iter) {
    f2ptr next = f2cons__cdr(iter, cause);
    f2ptr iter_fiber = f2cons__car(iter, cause);
    if (iter_fiber == fiber) {
      if (prev) {
	f2cons__cdr__set(prev, cause, next);
      } else {
	f2cause__fibers__set(this, cause, next);
      }
      break;
    }
    prev = iter;
    iter = next;
  }
  f2mutex__unlock(fibers_mutex, cause);
  if (! iter) {
    printf("\nf2__cause__remove_fiber warning: could not find fiber to remove."); fflush(stdout);
  }
  return nil;
}

f2ptr f2__cause__new_with_default_properties(f2ptr cause) {
  return f2__cause__new(cause, cause__allocate_traced_arrays__default_value, nil, nil, nil, nil, nil, nil, nil);
}

f2ptr f2__cause__new_default_with_memory_tracing_on(f2ptr cause) {
  f2ptr new_cause = f2__cause__new_with_default_properties(cause);
  f2cause__memory_tracing_on__set(new_cause, cause, __funk2.globalenv.true__symbol);
  return new_cause;
}

f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name) {
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause);
  f2cause__imagination_stack__set(new_cause, cause, f2cons__new(cause, imagination_name, f2cause__imagination_stack(cause, new_cause)));
  return new_cause;
}

void raw__cause__event_buffer__add(f2ptr cause, f2ptr event) {
  f2ptr event_buffer_last     = f2cause__event_buffer_last(cause, cause);
  f2ptr new_event_buffer_node = f2doublelink__new(cause, event_buffer_last, nil, event);
  if (event_buffer_last == nil) {
    f2cause__event_buffer_first__set(cause, cause, new_event_buffer_node);
  } else {
    f2doublelink__next__set(event_buffer_last, cause, new_event_buffer_node);
  }
  f2cause__event_buffer_last__set(cause, cause, new_event_buffer_node);
}

f2ptr f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr     cause_iter   = this;
  f2ptr     value        = nil;
  boolean_t keep_looping;
  do {
    keep_looping = boolean__false;
    f2ptr cause_frame = f2cause__frame(cause_iter, cause);
    if (cause_frame) {
      value = f2__frame__lookup_type_var_value(cause, cause_frame, type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    }
    if ((! cause_frame) || raw__larva__is_type(cause, value)) {
      cause_iter = f2__ptype__cause(cause, cause_iter);
      if (cause_iter) {
	keep_looping = boolean__true;
      } else {
	value = f2larva__new(cause, 23);
      }
    }
  } while (keep_looping);
  return value;
}


// **

void f2__cause__reinitialize_globalvars() {
}

void f2__cause__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "cause", "", &f2__cause__reinitialize_globalvars);
  f2__cause__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  //--
  
  // cause
  
  initialize_primobject_13_slot(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_stack, event_buffer_first, event_buffer_last, current_events_mutex, current_events);
  initialize_primobject_funk(cause, define);
  initialize_primobject_funk(cause, define__funk);
  
  
}

