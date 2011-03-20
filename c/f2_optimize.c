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


// optimize_operation_node

f2ptr raw__optimize_operation_node__new(f2ptr cause, f2ptr type, f2ptr name) {
  f2ptr optimize_operation = raw__array__new(cause, 3);
  raw__array__elt__set(cause, optimize_operation, 0, new__symbol(cause, "optimize_operation"));
  raw__array__elt__set(cause, optimize_operation, 1, type);
  raw__array__elt__set(cause, optimize_operation, 2, name);
  return f2__graph_node__new(cause, optimize_operation);
}

boolean_t raw__optimize_operation_node__is_type(f2ptr cause, f2ptr object) {
  if (! raw__graph_node__is_type(cause, object)) {
    return boolean__false;
  }
  f2ptr data = f2__graph_node__label(cause, object);
  return ((data != nil) &&
	  raw__array__is_type(cause, data) &&
	  (raw__array__length(cause, data) == 2) &&
	  raw__eq(cause, raw__array__elt(cause, data, 0), new__symbol(cause, "optimize_operation")));
}

f2ptr raw__optimize_operation_node__type(f2ptr cause, f2ptr this) {
  return raw__array__elt(cause, f2__graph_node__label(cause, this), 1);
}

f2ptr raw__optimize_operation_node__name(f2ptr cause, f2ptr this) {
  return raw__array__elt(cause, f2__graph_node__label(cause, this), 2);
}




// optimize_context

def_primobject_5_slot(optimize_context,
		      operation_graph,
		      data_graph,
		      stack,
		      register_frame,
		      variable_frame);

f2ptr f2__optimize_context__new(f2ptr cause) {
  f2ptr operation_graph = f2__operation_graph__new(cause);
  f2ptr data_graph      = f2__data_graph__new(cause);
  f2ptr stack           = nil;
  f2ptr register_frame  = f2__frame__new(cause, nil);
  f2ptr variable_frame  = f2__frame__new(cause, nil);
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
				 operation_graph,
				 data_graph,
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


f2ptr raw__optimize_context__call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr body_bytecodes = f2__funk__body_bytecodes(cause, funk);
  f2ptr bytecode_iter  = body_bytecodes;
  while (bytecode_iter != nil) {
    f2ptr bytecode = f2__cons__car(cause, bytecode_iter);
    {
      f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
      if        (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk"))) {
	printf("\nbytecode jump-funk");
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk"))) {
	printf("\nbytecode funk");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array"))) {
	printf("\nbytecode array");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cons"))) {
	printf("\nbytecode cons");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "consp"))) {
	printf("\nbytecode consp");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car"))) {
	printf("\nbytecode car");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr"))) {
	printf("\nbytecode cdr");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car-set"))) {
	printf("\nbytecode car-set");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr-set"))) {
	printf("\nbytecode cdr-set");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array_elt"))) {
	printf("\nbytecode array_elt");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "set"))) {
	printf("\nbytecode set");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "swap"))) {
	printf("\nbytecode swap");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push"))) {
	printf("\nbytecode push");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push_constant"))) {
	printf("\nbytecode push_constant");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "pop"))) {
	printf("\nbytecode pop");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "copy"))) {
	printf("\nbytecode copy");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "lookup"))) {
	printf("\nbytecode lookup");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "define"))) {
	printf("\nbytecode define");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "mutate-type_var"))) {
	printf("\nbytecode mutate-type_var");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "globalize-type_var"))) {
	printf("\nbytecode globalize-type_var");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump"))) {
	printf("\nbytecode jump");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump"))) {
	printf("\nbytecode if-jump");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump"))) {
	printf("\nbytecode else-jump");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "nop"))) {
	printf("\nbytecode nop");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "debug"))) {
	printf("\nbytecode debug");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "tracer"))) {
	printf("\nbytecode tracer");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "endfunk"))) {
	printf("\nbytecode endfunk");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "compile"))) {
	printf("\nbytecode compile");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "yield"))) {
	printf("\nbytecode yield");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "newenv"))) {
	printf("\nbytecode newenv");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code"))) {
	printf("\nbytecode machine_code");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt"))) {
	printf("\nbytecode reg_array-elt");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt-set"))) {
	printf("\nbytecode reg_array-elt-set");
	
	
	// logic
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "eq"))) {
	printf("\nbytecode eq");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "not"))) {
	printf("\nbytecode not");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "and"))) {
	printf("\nbytecode and");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "or"))) {
	printf("\nbytecode or");
	
	
	// math
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "add"))) {
	printf("\nbytecode add");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "negative"))) {
	printf("\nbytecode negative");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "subtract"))) {
	printf("\nbytecode subtract");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "multiply"))) {
	printf("\nbytecode multiply");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "inverse"))) {
	printf("\nbytecode inverse");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "divide"))) {
	printf("\nbytecode divide");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "modulo"))) {
	printf("\nbytecode modulo");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "increment"))) {
	printf("\nbytecode increment");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "decrement"))) {
	printf("\nbytecode decrement");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "numerically_equals"))) {
	printf("\nbytecode numerically_equals");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "less_than"))) {
	printf("\nbytecode less_than");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "greater_than"))) {
	printf("\nbytecode greater_than");
	
	
	// block
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_push"))) {
	printf("\nbytecode block_push");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_enter"))) {
	printf("\nbytecode block_enter");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_rest_argument"))) {
	printf("\nbytecode block_define_rest_argument");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_argument"))) {
	printf("\nbytecode block_define_argument");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_last_argument"))) {
	printf("\nbytecode block_define_last_argument");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_pop"))) {
	printf("\nbytecode block_pop");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_pop"))) {
	printf("\nbytecode block_exit_and_pop");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_no_pop"))) {
	printf("\nbytecode block_exit_and_no_pop");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_begin"))) {
	printf("\nbytecode block_eval_args_begin");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_next"))) {
	printf("\nbytecode block_eval_args_next");
	
	
      } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_end"))) {
	printf("\nbytecode block_eval_args_end");
	
	
      } else {
	printf("\nbytecode UNRECOGNIZED: cannot optimize funk.");
	return f2larva__new(cause, 5123, nil);
      }
      
      
      
    }
    bytecode_iter = f2__cons__cdr(cause, bytecode_iter);
  }
  return nil;
}


f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_context"),
						new__symbol(cause, "operation_graph"), f2__optimize_context__operation_graph(cause, this),
						new__symbol(cause, "data_graph"),      f2__optimize_context__data_graph(     cause, this),
						new__symbol(cause, "stack"),           f2__optimize_context__stack(          cause, this),
						new__symbol(cause, "register_frame"),  f2__optimize_context__register_frame( cause, this),
						new__symbol(cause, "variable_frame"),  f2__optimize_context__variable_frame( cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_context,     this);
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
  f2ptr optimize_context = f2__optimize_context__new(cause);
  {
    f2ptr result = raw__optimize_context__prepare_to_call_funk(cause, optimize_context, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_context__call_funk(cause, optimize_context, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
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
  
  initialize_primobject_5_slot(optimize_context,
			       operation_graph,
			       data_graph,
			       stack,
			       register_frame,
			       variable_frame);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

