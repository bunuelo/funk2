// 
// Copyright (c) 2007-2010 Bo Morgan.
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

def_primobject_18_slot(cause,
		       fibers_mutex,
		       fibers,
		       frame,
		       allocate_traced_arrays,
		       bytecode_tracing_on,
		       memory_tracing_on,
		       subscribers_mutex,
		       subscribers,
		       imagination_stack,
		       event_buffer_first,
		       event_buffer_last,
		       current_events_mutex,
		       current_events,
		       bytecode_branch_funks,
		       bytecode_funk_funks,
		       bytecode_tracer_funks,
		       bytecode_endfunk_funks,
		       event_trace);

f2ptr f2__cause__new(f2ptr cause,
		     f2ptr allocate_traced_arrays,
		     f2ptr bytecode_tracing_on,
		     f2ptr memory_tracing_on,
		     f2ptr subscribers,
		     f2ptr imagination_name,
		     f2ptr event_buffer_first,
		     f2ptr event_buffer_last,
		     f2ptr current_events,
		     f2ptr bytecode_branch_funks,
		     f2ptr bytecode_funk_funks,
		     f2ptr bytecode_tracer_funks,
		     f2ptr bytecode_endfunk_funks) {
  f2ptr fibers_mutex         = f2mutex__new(cause);
  f2ptr fibers               = nil;
  f2ptr frame                = f2__frame__new(cause);
  f2ptr subscribers_mutex    = f2mutex__new(cause);
  f2ptr current_events_mutex = f2mutex__new(cause);
  f2ptr event_trace          = nil;
  return f2cause__new(cause,
		      fibers_mutex,
		      fibers,
		      frame,
		      allocate_traced_arrays,
		      bytecode_tracing_on,
		      memory_tracing_on,
		      subscribers_mutex,
		      subscribers,
		      imagination_name,
		      event_buffer_first,
		      event_buffer_last,
		      current_events_mutex,
		      current_events,
		      bytecode_branch_funks,
		      bytecode_funk_funks,
		      bytecode_tracer_funks,
		      bytecode_endfunk_funks,
		      event_trace);
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source) {
  if (source && (! raw__cause__is_type(cause, source))) {
    return f2larva__new(cause, 333, nil);
  }
  f2ptr allocate_traced_arrays   = cause__allocate_traced_arrays__default_value; // default values
  f2ptr bytecode_tracing_on      = nil;
  f2ptr memory_tracing_on        = nil;
  f2ptr subscribers              = nil;
  f2ptr imagination_stack        = nil;
  f2ptr bytecode_branch_funks    = nil;
  f2ptr bytecode_funk_funks      = nil;
  f2ptr bytecode_tracer_funks    = nil;
  f2ptr bytecode_endfunk_funks   = nil;
  if (source) {
    allocate_traced_arrays = f2__cause__allocate_traced_arrays(cause, source);
    bytecode_tracing_on    = f2__cause__bytecode_tracing_on(   cause, source);
    memory_tracing_on      = f2__cause__memory_tracing_on(     cause, source);
    subscribers            = f2__cause__subscribers(           cause, source);
    imagination_stack      = f2__cause__imagination_stack(     cause, source);
    bytecode_branch_funks  = f2__cause__bytecode_branch_funks( cause, source);
    bytecode_funk_funks    = f2__cause__bytecode_funk_funks(   cause, source);
    bytecode_tracer_funks  = f2__cause__bytecode_tracer_funks( cause, source);
    bytecode_endfunk_funks = f2__cause__bytecode_endfunk_funks(cause, source);
  }
  return f2__cause__new(cause,
			allocate_traced_arrays,
			bytecode_tracing_on,
			memory_tracing_on,
			subscribers,
			imagination_stack,
			nil, // event_buffer_first
			nil, // event_buffer_last
			nil, // current_events
			bytecode_branch_funks,
			bytecode_funk_funks,
			bytecode_tracer_funks,
			bytecode_endfunk_funks);
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

f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name) {
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause, cause);
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
	value = f2larva__new(cause, 23, nil);
      }
    }
  } while (keep_looping);
  return value;
}

f2ptr f2__cause__define(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}
def_pcfunk3(cause__define, this, var, value, return f2__cause__define(this_cause, this, var, value));

f2ptr f2__cause__define__funk(f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.funk_variable__symbol, funkvar, value);
}
def_pcfunk3(cause__define__funk, this, funkvar, value, return f2__cause__define__funk(this_cause, this, funkvar, value));

f2ptr f2__cause(f2ptr cause) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause, cause);
  f2__fiber__cause_reg__set(cause, fiber, new_cause);
  return new_cause;
}
def_pcfunk0(cause, return f2__cause(this_cause));


f2ptr f2cause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause__primobject_type__new(cause);
  {char* slot_name = "define";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);}
  {char* slot_name = "define-funk"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);}
  return this;
}


f2ptr f2__bytecode_funk_callback__create_and_trace_event(f2ptr cause, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr funk, f2ptr args) {
  f2ptr start_time       = f2__time(cause);
  f2ptr end_time         = nil;
  f2ptr funk_bytecode    = bytecode;
  f2ptr endfunk_bytecode = nil;
  f2ptr value            = nil;
  f2ptr funk_event = f2__funk_event__new(cause, object_cause, funk, start_time, end_time, fiber, funk_bytecode, args, endfunk_bytecode, value);
  if (object_cause) {
    f2ptr event_trace = f2__cause__event_trace(cause, object_cause);
    f2ptr doublelink = f2__doublelink__new(cause, event_trace, nil, funk_event);
    f2__doublelink__next__set(cause, event_trace, doublelink);
    f2__cause__event_trace__set(cause, object_cause, doublelink);
  }
  return nil;
}
def_pcfunk5(bytecode_funk_callback__create_and_trace_event, object_cause, fiber, bytecode, funk, args, return f2__bytecode_funk_callback__create_and_trace_event(this_cause, object_cause, fiber, bytecode, funk, args));

f2ptr f2__bytecode_endfunk_callback__finish_and_abstract_event(f2ptr cause, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr value, f2ptr funk) {
  if (object_cause) {
    f2ptr event_trace = f2__cause__event_trace(cause, object_cause);
    f2ptr iter = event_trace;
    while (iter) {
      f2ptr prev = f2__doublelink__prev(cause, iter);
      f2ptr funk_event = f2__doublelink__value(cause, iter);
      f2ptr funk_event__funk = f2__funk_event__funk(cause, funk_event);
      if (raw__eq(cause, funk, funk_event__funk)) {
	f2ptr end_time         = f2__time(cause);
	f2ptr endfunk_bytecode = bytecode;
	f2__funk_event__end_time__set(        cause, funk_event, end_time);
	f2__funk_event__endfunk_bytecode__set(cause, funk_event, endfunk_bytecode);
	f2__funk_event__value__set(           cause, funk_event, value);
      }
      iter = prev;
    }
  }
  return nil;
}
def_pcfunk5(bytecode_endfunk_callback__finish_and_abstract_event, object_cause, fiber, bytecode, value, funk, return f2__bytecode_endfunk_callback__finish_and_abstract_event(this_cause, object_cause, fiber, bytecode, value, funk));


// funk2_event

def_primobject_9_slot(funk_event,
		      object_cause,
		      funk,
		      start_time,
		      end_time,
		      fiber,
		      funk_bytecode,
		      args,
		      endfunk_bytecode,
		      value);

f2ptr f2__funk_event__new(f2ptr cause, f2ptr object_cause, f2ptr funk, f2ptr start_time, f2ptr end_time, f2ptr fiber, f2ptr funk_bytecode, f2ptr args, f2ptr endfunk_bytecode, f2ptr value) {
  return f2funk_event__new(cause, object_cause, funk, start_time, end_time, fiber, funk_bytecode, args, endfunk_bytecode, value);
}
def_pcfunk0(funk_event__new, return f2__funk_event__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil, nil));


// **

void f2__cause__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __cause__symbol      = new__symbol(cause, "cause");
  __funk_event__symbol = new__symbol(cause, "funk_event");
}

void f2__cause__initialize() {
  f2__cause__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "cause", "", &f2__cause__reinitialize_globalvars);
  f2ptr cause = initial_cause();
  
  //--
  
  // cause
  
  initialize_primobject_18_slot(cause,
				fibers_mutex,
				fibers,
				frame,
				allocate_traced_arrays,
				bytecode_tracing_on,
				memory_tracing_on,
				subscribers_mutex,
				subscribers,
				imagination_stack,
				event_buffer_first,
				event_buffer_last,
				current_events_mutex,
				current_events,
				bytecode_branch_funks,
				bytecode_funk_funks,
				bytecode_tracer_funks,
				bytecode_endfunk_funks,
				event_trace);
  
  {char* symbol_str = "define"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define, this, var, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk = never_gc(cfunk);}
  {char* symbol_str = "define-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define__funk, this, var, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(cause, "Sets the current cause to be a new cause.  Properties are inherited from the previous cause.");
  
  f2__primcfunk__init__5(bytecode_funk_callback__create_and_trace_event, object_cause, fiber, bytecode, funk, args, "(cfunk defined in f2_cause.c)");
  f2__primcfunk__init__5(bytecode_endfunk_callback__finish_and_abstract_event, object_cause, fiber, bytecode, value, funk, "(cfunk defined in f2_cause.c)");
  
  // funk_event
  
  initialize_primobject_9_slot(funk_event,
			       object_cause,
			       funk,
			       start_time,
			       end_time,
			       fiber,
			       funk_bytecode,
			       args,
			       endfunk_bytecode,
			       value);
}

