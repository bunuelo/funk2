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

def_primobject_17_slot(cause,
		       fibers_mutex,
		       fibers,
		       frame,
		       allocate_traced_arrays,
		       bytecode_tracing_on,
		       memory_tracing_on,
		       imagination_stack,
		       bytecode_branch_callbacks,
		       bytecode_funk_callbacks,
		       bytecode_tracer_callbacks,
		       bytecode_endfunk_callbacks,
		       complete_funk_callbacks,
		       read_other_memory_callbacks,
		       write_other_memory_callbacks,
		       event_graph_mutex,
		       event_graph,
		       event_graph_last_event);

f2ptr f2__cause__new(f2ptr cause,
		     f2ptr allocate_traced_arrays,
		     f2ptr bytecode_tracing_on,
		     f2ptr memory_tracing_on,
		     f2ptr imagination_name,
		     f2ptr bytecode_branch_callbacks,
		     f2ptr bytecode_funk_callbacks,
		     f2ptr bytecode_tracer_callbacks,
		     f2ptr bytecode_endfunk_callbacks,
		     f2ptr complete_funk_callbacks,
		     f2ptr read_other_memory_callbacks,
		     f2ptr write_other_memory_callbacks) {
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
					      bytecode_branch_callbacks,
					      bytecode_funk_callbacks,
					      bytecode_tracer_callbacks,
					      bytecode_endfunk_callbacks,
					      complete_funk_callbacks,
					      read_other_memory_callbacks,
					      write_other_memory_callbacks,
					      event_graph_mutex,
					      event_graph,
					      event_graph_last_event);
  //printf("\nnew cause: " u64__fstr ".\n", this); fflush(stdout);
  return this;
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source) {
  if (source && (! raw__cause__is_type(cause, source))) {
    return f2larva__new(cause, 333, nil);
  }
  f2ptr allocate_traced_arrays       = cause__allocate_traced_arrays__default_value; // default values
  f2ptr bytecode_tracing_on          = nil;
  f2ptr memory_tracing_on            = nil;
  f2ptr imagination_stack            = nil;
  f2ptr bytecode_branch_callbacks    = nil;
  f2ptr bytecode_funk_callbacks      = nil;
  f2ptr bytecode_tracer_callbacks    = nil;
  f2ptr bytecode_endfunk_callbacks   = nil;
  f2ptr complete_funk_callbacks      = nil;
  f2ptr read_other_memory_callbacks  = nil;
  f2ptr write_other_memory_callbacks = nil;
  if (source) {
    allocate_traced_arrays       = f2__cause__allocate_traced_arrays(      cause, source);
    bytecode_tracing_on          = f2__cause__bytecode_tracing_on(         cause, source);
    memory_tracing_on            = f2__cause__memory_tracing_on(           cause, source);
    imagination_stack            = f2__cause__imagination_stack(           cause, source);
    bytecode_branch_callbacks    = f2__cause__bytecode_branch_callbacks(   cause, source);
    bytecode_funk_callbacks      = f2__cause__bytecode_funk_callbacks(     cause, source);
    bytecode_tracer_callbacks    = f2__cause__bytecode_tracer_callbacks(   cause, source);
    bytecode_endfunk_callbacks   = f2__cause__bytecode_endfunk_callbacks(  cause, source);
    complete_funk_callbacks      = f2__cause__complete_funk_callbacks(     cause, source);
    read_other_memory_callbacks  = f2__cause__read_other_memory_callbacks( cause, source);;
    write_other_memory_callbacks = f2__cause__write_other_memory_callbacks(cause, source);;
  }
  return f2__cause__new(cause,
			allocate_traced_arrays,
			bytecode_tracing_on,
			memory_tracing_on,
			imagination_stack,
			bytecode_branch_callbacks,
			bytecode_funk_callbacks,
			bytecode_tracer_callbacks,
			bytecode_endfunk_callbacks,
			complete_funk_callbacks,
			read_other_memory_callbacks,
			write_other_memory_callbacks);
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
  boolean_t complete_funk__occurred = boolean__false;
  f2ptr     complete_funk__funk;
  f2ptr     complete_funk__args;
  f2ptr     complete_funk__value;
  f2ptr     complete_funk__first_subevent;
  f2ptr     complete_funk__last_subevent;
  {
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
      if (raw__funkable__is_type(cause, funk)) {
	f2ptr matching_funk_event = nil;
	{
	  f2ptr funk__name = f2__funkable__name(cause, funk);
	  f2ptr iter = event_graph_last_event;
	  while (iter && (matching_funk_event == nil)) {
	    if (raw__frame__is_type(cause, iter)) {
	      f2ptr iter_event_frame = iter;
	      f2ptr event_type       = f2__frame__lookup_var_value(cause, iter_event_frame, new__symbol(cause, "event_type"), nil);
	      if (raw__eq(cause, event_type, new__symbol(cause, "funk"))) {
		f2ptr iter_event_frame__funk = f2__frame__lookup_var_value(cause, iter_event_frame, new__symbol(cause, "funk"), nil);
		if (raw__funkable__is_type(cause, iter_event_frame__funk)) {
		  f2ptr iter_event_frame__funk__name = f2__funkable__name(cause, iter_event_frame__funk);
		  if (raw__eq(cause, funk__name, iter_event_frame__funk__name)) {
		    matching_funk_event = iter_event_frame;
		    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "subfunk-span"), iter_event_frame, event_frame);
		    break;
		  }
		}
	      }
	    }
	    {
	      // first try jumping by subfunk-span if one exists.
	      f2ptr try_before_subfunk_span = raw__graph__right_node__an_arbitrary_left_node(cause, event_graph, iter, new__symbol(cause, "subfunk-span"));
	      if (try_before_subfunk_span != nil) {
		iter = try_before_subfunk_span;
	      }
	      // then, just go to the previous event.
	      iter = raw__graph__right_node__an_arbitrary_left_node(cause, event_graph, iter, and_then__symbol);
	    }
	  }
	}
	if (matching_funk_event != nil) {
	  f2ptr matching_funk_event__args = f2__frame__lookup_var_value(cause, matching_funk_event, new__symbol(cause, "args"), new__symbol(cause, "no-args-available"));
	  complete_funk__occurred       = boolean__true;
	  complete_funk__funk           = funk;
	  complete_funk__args           = matching_funk_event__args;
	  complete_funk__value          = value;
	  complete_funk__first_subevent = matching_funk_event;
	  complete_funk__last_subevent  = event_frame;
	  // call complete_funk callback
	}
      }
      f2__cause__event_graph_last_event__set(cause, this, event_frame);
    }
    raw__mutex__unlock(cause, event_graph_mutex);
  }
  if (complete_funk__occurred) {
    f2ptr complete_funk_callbacks = f2__cause__complete_funk_callbacks(cause, this);
    f2ptr fiber = f2__this__fiber(cause);
    {
      f2ptr iter = complete_funk_callbacks;
      while (iter) {
	f2ptr complete_funk_funk = f2__cons__car(cause, iter);
	f2ptr result = f2__force_funk_apply(cause, fiber, complete_funk_funk, f2list6__new(cause, this,
											   complete_funk__funk,
											   complete_funk__args,
											   complete_funk__value,
											   complete_funk__first_subevent,
											   complete_funk__last_subevent));
	if (raw__larva__is_type(cause, result)) {
	  printf("\nwarning: complete_funk_funk resulted in larva.");
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
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

f2ptr f2__cause__add_graph_event__complete_funk(f2ptr cause, f2ptr this, f2ptr funk, f2ptr args, f2ptr value, f2ptr first_subevent, f2ptr last_subevent) {
  if (this == nil) {
    return nil;
  }
  printf("\ncomplete_funk");
  f2__print(cause, funk);
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph            = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event = f2__cause__event_graph_last_event(cause, this);
    f2ptr complete_funk_event    = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, complete_funk_event, new__symbol(cause, "event_type"), new__symbol(cause, "complete-funk"));
    f2__frame__add_var_value(cause, complete_funk_event, new__symbol(cause, "funk"),       funk);
    f2__frame__add_var_value(cause, complete_funk_event, new__symbol(cause, "args"),       args);
    f2__frame__add_var_value(cause, complete_funk_event, new__symbol(cause, "value"),      value);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, complete_funk_event);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "first_subevent"), complete_funk_event, first_subevent);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "last_subevent"),  complete_funk_event, last_subevent);
    // scan forward adding subevent relations
    f2ptr iter = first_subevent;
    while (iter) {
      f2__graph__add_edge(cause, event_graph, new__symbol(cause, "subevent"), complete_funk_event, iter);
      if (iter == last_subevent) {
	iter = nil;
      } else {
	// don't try jumping if we're at the beginning of our own funktion because that will just take us to the end and we won't mark any subevents at all!
	if (iter != first_subevent) {
	  // first try jumping by subfunk-span if one exists.
	  f2ptr try_subfunk_span = raw__graph__left_node__an_arbitrary_right_node(cause, event_graph, iter, new__symbol(cause, "subfunk-span"));
	  if (try_subfunk_span != nil) {
	    iter = try_subfunk_span;
	  }
	}
	// then, just go to the next event.
	iter = raw__graph__left_node__an_arbitrary_right_node(cause, event_graph, iter, new__symbol(cause, "and-then"));
      }
    }
    f2__cause__event_graph_last_event__set(cause, this, complete_funk_event);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk6(cause__add_graph_event__complete_funk, this, funk, args, value, first_subevent, last_subevent, return f2__cause__add_graph_event__complete_funk(this_cause, this, funk, args, value, first_subevent, last_subevent));

f2ptr f2__cause__add_graph_event__read_other_memory(f2ptr cause, f2ptr this, f2ptr object, f2ptr slot_name) {
  if (this == nil) {
    return nil;
  }
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph             = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event  = f2__cause__event_graph_last_event(cause, this);
    f2ptr read_other_memory_event = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, read_other_memory_event, new__symbol(cause, "event_type"), new__symbol(cause, "read_other_memory"));
    f2__frame__add_var_value(cause, read_other_memory_event, new__symbol(cause, "object"),     object);
    f2__frame__add_var_value(cause, read_other_memory_event, new__symbol(cause, "slot_name"),  slot_name);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, read_other_memory_event);
    f2__cause__event_graph_last_event__set(cause, this, read_other_memory_event);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk3(cause__add_graph_event__read_other_memory, this, array, index, return f2__cause__add_graph_event__read_other_memory(this_cause, this, array, index));

f2ptr f2__cause__add_graph_event__write_other_memory(f2ptr cause, f2ptr this, f2ptr object, f2ptr slot_name, f2ptr old_value) {
  if (this == nil) {
    return nil;
  }
  f2ptr event_graph_mutex = f2__cause__event_graph_mutex(cause, this);
  raw__mutex__lock(cause, event_graph_mutex);
  {
    f2ptr event_graph             = f2__cause__get_event_graph__thread_unsafe(cause, this);
    f2ptr event_graph_last_event  = f2__cause__event_graph_last_event(cause, this);
    f2ptr write_other_memory_event = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, write_other_memory_event, new__symbol(cause, "event_type"), new__symbol(cause, "write_other_memory"));
    f2__frame__add_var_value(cause, write_other_memory_event, new__symbol(cause, "object"),     object);
    f2__frame__add_var_value(cause, write_other_memory_event, new__symbol(cause, "slot_name"),  slot_name);
    f2__frame__add_var_value(cause, write_other_memory_event, new__symbol(cause, "old_value"),  old_value);
    f2__graph__add_edge(cause, event_graph, new__symbol(cause, "and-then"), event_graph_last_event, write_other_memory_event);
    f2__cause__event_graph_last_event__set(cause, this, write_other_memory_event);
  }
  raw__mutex__unlock(cause, event_graph_mutex);
  return nil;
}
def_pcfunk4(cause__add_graph_event__write_other_memory, this, array, index, old_value, return f2__cause__add_graph_event__write_other_memory(this_cause, this, array, index, old_value));

f2ptr f2cause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause__primobject_type__new(cause);
  {char* slot_name = "define";                             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);}
  {char* slot_name = "define-funk";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);}
  {char* slot_name = "add_graph_event-funk";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__funk__funk);}
  {char* slot_name = "add_graph_event-endfunk";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__endfunk__funk);}
  {char* slot_name = "add_graph_event-branch";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__branch__funk);}
  {char* slot_name = "add_graph_event-complete_funk";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__complete_funk__funk);}
  {char* slot_name = "add_graph_event-read_other_memory";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__read_other_memory__funk);}
  {char* slot_name = "add_graph_event-write_other_memory"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__write_other_memory__funk);}
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
  
  initialize_primobject_17_slot(cause,
				fibers_mutex,
				fibers,
				frame,
				allocate_traced_arrays,
				bytecode_tracing_on,
				memory_tracing_on,
				imagination_stack,
				bytecode_branch_callbacks,
				bytecode_funk_callbacks,
				bytecode_tracer_callbacks,
				bytecode_endfunk_callbacks,
				complete_funk_callbacks,
				read_other_memory_callbacks,
				write_other_memory_callbacks,
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
  {char* symbol_str = "add_graph_event-complete_funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__complete_funk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(cause__add_graph_event__complete_funk, this, funk, args, value, first_subevent, last_subevent, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__complete_funk__funk = never_gc(cfunk);}
  {char* symbol_str = "add_graph_event-read_other_memory"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__read_other_memory__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__add_graph_event__read_other_memory, this, object, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__read_other_memory__funk = never_gc(cfunk);}
  {char* symbol_str = "add_graph_event-write_other_memory"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__write_other_memory__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(cause__add_graph_event__write_other_memory, this, object, slot_name, old_value, cfunk, 0, "primobject_type funktion (defined in f2_cause.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_graph_event__write_other_memory__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(cause, "Sets the current cause to be a new cause.  Properties are inherited from the previous cause.");
  
}

