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

def_primobject_14_slot(cause,
		       fibers_mutex,
		       fibers,
		       frame,
		       allocate_traced_arrays,
		       bytecode_tracing_on,
		       memory_tracing_on,
		       imagination_stack,
		       bytecode_branch_funks,
		       bytecode_funk_funks,
		       bytecode_tracer_funks,
		       bytecode_endfunk_funks,
		       event_graph_mutex,
		       event_graph,
		       event_graph_last_event);

f2ptr f2__cause__new(f2ptr cause,
		     f2ptr allocate_traced_arrays,
		     f2ptr bytecode_tracing_on,
		     f2ptr memory_tracing_on,
		     f2ptr imagination_name,
		     f2ptr bytecode_branch_funks,
		     f2ptr bytecode_funk_funks,
		     f2ptr bytecode_tracer_funks,
		     f2ptr bytecode_endfunk_funks) {
  f2ptr fibers_mutex           = f2mutex__new(cause);
  f2ptr fibers                 = nil;
  f2ptr frame                  = f2__frame__new(cause, nil);
  f2ptr event_graph_mutex      = f2mutex__new(cause);
  f2ptr event_graph            = nil;
  f2ptr event_graph_last_event = nil;
  f2ptr this                   = f2cause__new(cause,
					      fibers_mutex,
					      fibers,
					      frame,
					      allocate_traced_arrays,
					      bytecode_tracing_on,
					      memory_tracing_on,
					      imagination_name,
					      bytecode_branch_funks,
					      bytecode_funk_funks,
					      bytecode_tracer_funks,
					      bytecode_endfunk_funks,
					      event_graph_mutex,
					      event_graph,
					      event_graph_last_event);
  //printf("\nnew cause: " u64__fstr ".\n", this); fflush(stdout);
  return this;
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source) {
  if (source && (! raw__cause__is_type(cause, source))) {
    return f2larva__new(cause, 333, nil);
  }
  f2ptr allocate_traced_arrays   = cause__allocate_traced_arrays__default_value; // default values
  f2ptr bytecode_tracing_on      = nil;
  f2ptr memory_tracing_on        = nil;
  f2ptr imagination_stack        = nil;
  f2ptr bytecode_branch_funks    = nil;
  f2ptr bytecode_funk_funks      = nil;
  f2ptr bytecode_tracer_funks    = nil;
  f2ptr bytecode_endfunk_funks   = nil;
  if (source) {
    allocate_traced_arrays = f2__cause__allocate_traced_arrays(cause, source);
    bytecode_tracing_on    = f2__cause__bytecode_tracing_on(   cause, source);
    memory_tracing_on      = f2__cause__memory_tracing_on(     cause, source);
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
			imagination_stack,
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
  f2ptr fiber     = f2__this__fiber(cause);
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause, cause);
  { // should be atomic
    f2__fiber__cause_reg__set(cause, fiber, new_cause);
    f2__cause__add_fiber(cause, new_cause, fiber);
    if (cause) {
      f2__cause__remove_fiber(cause, cause, fiber);
    }
  }
  return new_cause;
}
def_pcfunk0(cause, return f2__cause(this_cause));

f2ptr f2__cause__get_event_graph__thread_unsafe(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr event_graph = f2__cause__event_graph(cause, this);
  if (event_graph == nil) {
    event_graph = f2__graph__new(cause);
    f2__cause__event_graph__set(cause, this, event_graph);
  }
  return event_graph;
}

f2ptr f2__cause__add_graph_event__funk(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr bytecode, f2ptr funk, f2ptr args) {
  if (this == nil) {
    return nil;
  }
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph            = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event = f2__cause__event_graph_last_event(cause, this);
    f2ptr event_frame            = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "event_type"), new__symbol(cause, "funk"));
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "fiber"),      fiber);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "bytecode"),   bytecode);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "funk"),       funk);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "args"),       args);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, event_frame);
    f2__cause__event_graph_last_event__set(cause, this, event_frame);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk5(cause__add_graph_event__funk, this, fiber, bytecode, funk, args, return f2__cause__add_graph_event__funk(this_cause, this, fiber, bytecode, funk, args));

f2ptr f2__cause__add_graph_event__endfunk(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr bytecode, f2ptr value, f2ptr funk) {
  if (this == nil) {
    return nil;
  }
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph            = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event = f2__cause__event_graph_last_event(cause, this);
    f2ptr event_frame            = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "event_type"), new__symbol(cause, "endfunk"));
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "fiber"),      fiber);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "bytecode"),   bytecode);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "value"),      value);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "funk"),       funk);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, event_frame);
    f2ptr and_then__symbol = new__symbol(cause, "and-then");
    {
      f2ptr prev_iter = event_frame; // we're going backwards
      f2ptr iter      = event_graph_last_event;
      while (iter) {
	f2ptr iter_event_frame       = iter;
	f2ptr iter_event_frame__funk = f2__frame__lookup_var_value(cause, iter_event_frame, new__symbol(cause, "funk"), nil);
	if (raw__eq(cause, funk, iter_event_frame__funk)) {
	  f2__graph__add_edge(cause, event_graph, new__symbol(cause, "until"), iter_event_frame, event_frame);
	  f2__graph__remove_edge(cause, event_graph, new__symbol(cause, "and-then"), iter, prev_iter);
	  f2__graph__remove_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, event_frame);
	  break;
	}
	prev_iter = iter;
	iter      = raw__graph__right_node__an_arbitrary_left_node(cause, event_graph, iter, and_then__symbol);
      }
    }
    f2__cause__event_graph_last_event__set(cause, this, event_frame);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk5(cause__add_graph_event__endfunk, this, fiber, bytecode, value, funk, return f2__cause__add_graph_event__endfunk(this_cause, this, fiber, bytecode, value, funk));

f2ptr f2__cause__add_graph_event__branch(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr bytecode, f2ptr program_counter, f2ptr branch_program_counter, f2ptr value) {
  if (this == nil) {
    return nil;
  }
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph            = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event = f2__cause__event_graph_last_event(cause, this);
    f2ptr event_frame            = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "event_type"),             new__symbol(cause, "branch"));
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "fiber"),                  fiber);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "bytecode"),               bytecode);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "program_counter"),        program_counter);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "branch_program_counter"), branch_program_counter);
    f2__frame__add_var_value(cause, event_frame, new__symbol(cause, "value"),                  value);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, event_frame);
    f2__cause__event_graph_last_event__set(cause, this, event_frame);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk6(cause__add_graph_event__branch, this, fiber, bytecode, program_counter, branch_program_counter, value, return f2__cause__add_graph_event__branch(this_cause, this, fiber, bytecode, program_counter, branch_program_counter, value));


f2ptr f2cause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause__primobject_type__new(cause);
  {char* slot_name = "define";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);}
  {char* slot_name = "define-funk";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);}
  {char* slot_name = "add_graph_event-funk";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__funk__funk);}
  {char* slot_name = "add_graph_event-endfunk"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__endfunk__funk);}
  {char* slot_name = "add_graph_event-branch";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__branch__funk);}
  return this;
}




// **

void f2__cause__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __cause__symbol      = new__symbol(cause, "cause");
}

void f2__cause__initialize() {
  f2__cause__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "cause", "", &f2__cause__reinitialize_globalvars);
  f2ptr cause = initial_cause();
  
  //--
  
  // cause
  
  initialize_primobject_14_slot(cause,
				fibers_mutex,
				fibers,
				frame,
				allocate_traced_arrays,
				bytecode_tracing_on,
				memory_tracing_on,
				imagination_stack,
				bytecode_branch_funks,
				bytecode_funk_funks,
				bytecode_tracer_funks,
				bytecode_endfunk_funks,
				event_graph_mutex,
				event_graph,
				event_graph_last_event);
  
  {char* symbol_str = "define"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define, this, var, value, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk = never_gc(cfunk);}
  {char* symbol_str = "define-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define__funk, this, var, value, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk = never_gc(cfunk);}
  {char* symbol_str = "add_graph_event-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__funk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(cause__add_graph_event__funk, this, fiber, bytecode, funk, args, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__funk__funk = never_gc(cfunk);}
  {char* symbol_str = "add_graph_event-endfunk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__endfunk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(cause__add_graph_event__endfunk, this, fiber, bytecode, value, funk, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__endfunk__funk = never_gc(cfunk);}
  {char* symbol_str = "add_graph_event-branch"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__branch__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(cause__add_graph_event__branch, this, fiber, bytecode, program_counter, branch_program_counter, value, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__branch__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(cause, "Sets the current cause to be a new cause.  Properties are inherited from the previous cause.");
  
}

