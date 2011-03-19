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




// optimize_data_node

f2ptr raw__optimize_data_node__new(f2ptr cause, f2ptr type, f2ptr name) {
  f2ptr optimize_data = raw__array__new(cause, 3);
  raw__array__elt__set(cause, optimize_data, 0, new__symbol(cause, "optimize_data"));
  raw__array__elt__set(cause, optimize_data, 1, type);
  raw__array__elt__set(cause, optimize_data, 2, name);
  return f2__graph_node__new(cause, optimize_data);
}

boolean_t raw__optimize_data_node__is_type(f2ptr cause, f2ptr object) {
  if (! raw__graph_node__is_type(cause, object)) {
    return boolean__false;
  }
  f2ptr data = f2__graph_node__label(cause, object);
  return ((data != nil) &&
	  raw__array__is_type(cause, data) &&
	  (raw__array__length(cause, data) == 2) &&
	  raw__eq(cause, raw__array__elt(cause, data, 0), new__symbol(cause, "optimize_data")));
}

f2ptr raw__optimize_data_node__type(f2ptr cause, f2ptr this) {
  return raw__array__elt(cause, f2__graph_node__label(cause, this), 1);
}

f2ptr raw__optimize_data_node__name(f2ptr cause, f2ptr this) {
  return raw__array__elt(cause, f2__graph_node__label(cause, this), 2);
}




// optimize_context

def_primobject_3_slot(optimize_context,
		      graph,
		      stack,
		      register_frame,
		      variable_frame);

f2ptr f2__optimize_context__new(f2ptr cause) {
  f2ptr graph          = f2__graph__new(cause);
  f2ptr stack          = nil;
  f2ptr register_frame = f2__frame__new(cause);
  f2ptr variable_frame = f2__frame__new(cause);
  {
    f2ptr fiber_registers = f2list6__new(cause,
					 new__symbol(cause, "return"),
					 new__symbol(cause, "value"),
					 new__symbol(cause, "iter"),
					 new__symbol(cause, "program_counter"),
					 new__symbol(cause, "env"),
					 new__symbol(cause, "args"));
    f2ptr iter = fiber_registers;
    while (iter != nil) {
      f2ptr fiber_register = f2__cons__car(cause, iter);
      {
	f2ptr data_node = raw__optimize_data_node__new(cause, new__symbol(cause, "register"), fiber_register);
	raw__frame__add_var_value(cause, register_frame, fiber_register, data_node);
	raw__graph__add_node(cause, graph, data_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2optimize_context__new(cause,
				 graph,
				 stack,
				 register_frame,
				 variable_frame);
}
def_pcfunk0(optimize_context__new, return f2__optimize_context__new(this_cause));


f2ptr raw__optimize_context__prepare_to_call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr graph      = f2__optimize_context__graph(cause, this);
  f2ptr stack      = nil;
  f2ptr stack_iter = nil;
  {
    f2ptr args = f2__funk__args(cause, funk);
    {
      f2ptr iter = args;
      while (iter != nil) {
	f2ptr variable = f2__cons__car(cause, iter);
	{
	  f2ptr data_node = raw__optimize_data_node__new(cause, new__symbol(cause, "variable"), variable);
	  f2ptr new_cons = f2cons__new(cause, data_node, nil);
	  if (stack == nil) {
	    stack      = new_cons;
	    stack_iter = new_cons;
	  } else {
	    f2__cons__cdr__set(cause, stack_iter, new_cons);
	    stack_iter = new_cons;
	  }
	  raw__graph__add_node(cause, graph, data_node);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  f2__optimize_context__stack__set(cause, this, stack);
  return nil;
}



f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_context"),
					       new__symbol(cause, "graph"),                    f2__optimize_context__graph(                   cause, this),
					       new__symbol(cause, "stack"),                    f2__optimize_context__stack(                   cause, this),
					       new__symbol(cause, "node_fiber_register_hash"), f2__optimize_context__node_fiber_register_hash(cause, this),
					       new__symbol(cause, "node_variable_hash"),       f2__optimize_context__node_variable_hash(      cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_context,             this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_context__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_context__terminal_print_with_frame, this, terminal_print_frame, return f2__optimize_context__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_context__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_context__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk);}
  return this;
}




f2ptr raw__funk__optimize(f2ptr cause, f2ptr this) {
  f2ptr args                     = f2__funk__args(          cause, this);
  f2ptr body_bytecodes           = f2__funk__body_bytecodes(cause, this);
  f2ptr optimize_context         = f2__optimize_context__new(cause);
  f2ptr result = raw__optimize_context__prepare_to_call_funk(cause, optimize_context, this);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  {
    f2ptr graph                    = f2__optimize_context__graph(                   cause, optimize_context);
    f2ptr node_fiber_register_hash = f2__optimize_context__node_fiber_register_hash(cause, optimize_context);
    f2ptr node_variable_hash       = f2__optimize_context__node_variable_hash(      cause, optimize_context);
    {
      f2ptr iter = body_bytecodes;
      while (iter != nil) {
	f2ptr bytecode = f2__cons__car(cause, iter);
	{
	  
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return optimize_context;
}

f2ptr f2__funk__optimize(f2ptr cause, f2ptr this) {
  assert_argument_type(funk, this);
  return raw__funk__optimize(cause, this);
}


// **

void f2__optimize__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __optimize_context__symbol = new__symbol(cause, "optimize_context");
}

void f2__optimize__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars);
  
  f2__optimize__reinitialize_globalvars();
  
  // optimize_context
  
  initialize_primobject_4_slot(optimize_context,
			       graph,
			       stack,
			       node_fiber_register_hash,
			       node_variable_hash);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

