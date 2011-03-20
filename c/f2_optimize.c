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

def_primobject_6_slot(optimize_context,
		      operation_graph,
		      data_graph,
		      stack,
		      register_frame,
		      variable_frame,
		      node_bytecode_hash);

f2ptr f2__optimize_context__new(f2ptr cause) {
  f2ptr operation_graph    = f2__graph__new(cause);
  f2ptr data_graph         = f2__graph__new(cause);
  f2ptr stack              = nil;
  f2ptr register_frame     = f2__frame__new(cause, nil);
  f2ptr variable_frame     = f2__frame__new(cause, nil);
  f2ptr node_bytecode_hash = f2__ptypehash__new(cause);
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
	raw__graph__add_node(cause, data_graph, data_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2optimize_context__new(cause,
				 operation_graph,
				 data_graph,
				 stack,
				 register_frame,
				 variable_frame,
				 node_bytecode_hash);
}
def_pcfunk0(optimize_context__new, return f2__optimize_context__new(this_cause));


f2ptr raw__optimize_context__prepare_to_call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr data_graph = f2__optimize_context__data_graph(cause, this);
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
	  raw__graph__add_node(cause, data_graph, data_node);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  f2__optimize_context__stack__set(cause, this, stack);
  {
    f2ptr body_bytecodes     = f2__funk__body_bytecodes(cause, funk);
    f2ptr node_bytecode_hash = f2__optimize_context__node_bytecode_hash(cause, this);
    f2ptr operation_graph    = f2__optimize_context__operation_graph(   cause, this);
    {
      f2ptr prev_bytecode_node = nil;
      f2ptr bytecode_iter      = body_bytecodes;
      while (bytecode_iter != nil) {
	f2ptr bytecode = f2__cons__car(cause, bytecode_iter);
	{
	  f2ptr bytecode_node = raw__optimize_operation_node__new(cause, new__symbol(cause, "bytecode"), bytecode);
	  raw__ptypehash__add(cause, node_bytecode_hash, bytecode, bytecode_node);
	  raw__graph__add_node(cause, operation_graph, bytecode_node);
	  if (prev_bytecode_node != nil) {
	    raw__graph__add_new_edge(cause, operation_graph, new__symbol(cause, "next"), prev_bytecode_node, bytecode_node);
	  }
	  prev_bytecode_node = operation_node;
	}
	bytecode_iter = f2__cons__cdr(cause, bytecode_iter);
      }
    }
  }
  return nil;
}


// jump-funk

f2ptr raw__optimize_context__call_bytecode__jump__funk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: jump-funk");
  
  return nil;
}


// funk

f2ptr raw__optimize_context__call_bytecode__funk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: funk");
  
  return nil;
}


// array

f2ptr raw__optimize_context__call_bytecode__array(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: array");
  
  return nil;
}


// cons

f2ptr raw__optimize_context__call_bytecode__cons(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cons");
  
  return nil;
}


// consp

f2ptr raw__optimize_context__call_bytecode__consp(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: consp");
  
  return nil;
}


// car

f2ptr raw__optimize_context__call_bytecode__car(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: car");
  
  return nil;
}


// cdr

f2ptr raw__optimize_context__call_bytecode__cdr(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cdr");
  
  return nil;
}


// car-set

f2ptr raw__optimize_context__call_bytecode__car__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: car-set");
  
  return nil;
}


// cdr-set

f2ptr raw__optimize_context__call_bytecode__cdr__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cdr-set");
  
  return nil;
}


// array_elt

f2ptr raw__optimize_context__call_bytecode__array_elt(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: array_elt");
  
  return nil;
}


// set

f2ptr raw__optimize_context__call_bytecode__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: ");
  
  return nil;
}


// swap

f2ptr raw__optimize_context__call_bytecode__swap(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: swap");
  
  return nil;
}


// push

f2ptr raw__optimize_context__call_bytecode__push(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: push");
  
  return nil;
}


// push_constant

f2ptr raw__optimize_context__call_bytecode__push_constant(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: push_constant");
  
  return nil;
}


// pop

f2ptr raw__optimize_context__call_bytecode__pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: pop");
  
  return nil;
}


// copy

f2ptr raw__optimize_context__call_bytecode__copy(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: copy");
  
  return nil;
}


// lookup

f2ptr raw__optimize_context__call_bytecode__lookup(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: lookup");
  
  return nil;
}


// define

f2ptr raw__optimize_context__call_bytecode__define(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: define");
  
  return nil;
}


// mutate-type_var

f2ptr raw__optimize_context__call_bytecode__mutate__type_var(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: mutate-type_var");
  
  return nil;
}


// globalize-type_var

f2ptr raw__optimize_context__call_bytecode__globalize__type_var(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: globalize-type_var");
  
  return nil;
}


// jump

f2ptr raw__optimize_context__call_bytecode__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: jump");
  
  return nil;
}


// if-jump

f2ptr raw__optimize_context__call_bytecode__if__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: if-jump");
  
  return nil;
}


// else-jump

f2ptr raw__optimize_context__call_bytecode__else__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: else-jump");
  
  return nil;
}


// nop

f2ptr raw__optimize_context__call_bytecode__nop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: nop");
  
  return nil;
}


// debug

f2ptr raw__optimize_context__call_bytecode__debug(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: debug");
  
  return nil;
}


// tracer

f2ptr raw__optimize_context__call_bytecode__tracer(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: tracer");
  
  return nil;
}


// endfunk

f2ptr raw__optimize_context__call_bytecode__endfunk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: endfunk");
  
  return nil;
}


// compile

f2ptr raw__optimize_context__call_bytecode__compile(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: compile");
  
  return nil;
}


// yield

f2ptr raw__optimize_context__call_bytecode__yield(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: yield");
  
  return nil;
}


// newenv

f2ptr raw__optimize_context__call_bytecode__newenv(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: newenv");
  
  return nil;
}


// machine_code

f2ptr raw__optimize_context__call_bytecode__machine_code(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: machine_code");
  
  return nil;
}


// reg_array-elt

f2ptr raw__optimize_context__call_bytecode__reg_array__elt(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: reg_array-elt");
  
  return nil;
}


// reg_array-elt-set

f2ptr raw__optimize_context__call_bytecode__reg_array__elt__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: reg_array-elt-set");
  
  return nil;
}


// eq

f2ptr raw__optimize_context__call_bytecode__eq(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: eq");
  
  return nil;
}


// not

f2ptr raw__optimize_context__call_bytecode__not(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: not");
  
  return nil;
}


// and

f2ptr raw__optimize_context__call_bytecode__and(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: and");
  
  return nil;
}


// or

f2ptr raw__optimize_context__call_bytecode__or(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: ");
  
  return nil;
}


// add

f2ptr raw__optimize_context__call_bytecode__add(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: add");
  
  return nil;
}


// negative

f2ptr raw__optimize_context__call_bytecode__negative(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: negative");
  
  return nil;
}


// subtract

f2ptr raw__optimize_context__call_bytecode__subtract(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: subtract");
  
  return nil;
}


// multiply

f2ptr raw__optimize_context__call_bytecode__multiply(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: multiply");
  
  return nil;
}


// inverse

f2ptr raw__optimize_context__call_bytecode__inverse(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: inverse");
  
  return nil;
}


// divide

f2ptr raw__optimize_context__call_bytecode__divide(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: divide");
  
  return nil;
}


// modulo

f2ptr raw__optimize_context__call_bytecode__modulo(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: modulo");
  
  return nil;
}


// increment

f2ptr raw__optimize_context__call_bytecode__increment(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: increment");
  
  return nil;
}


// decrement

f2ptr raw__optimize_context__call_bytecode__decrement(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: decrement");
  
  return nil;
}


// numerically_equals

f2ptr raw__optimize_context__call_bytecode__numerically_equals(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: numerically_equals");
  
  return nil;
}


// less_than

f2ptr raw__optimize_context__call_bytecode__less_than(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: less_than");
  
  return nil;
}


// greater_than

f2ptr raw__optimize_context__call_bytecode__greater_than(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: greater_than");
  
  return nil;
}


// block_push

f2ptr raw__optimize_context__call_bytecode__block_push(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_push");
  
  return nil;
}


// block_enter

f2ptr raw__optimize_context__call_bytecode__block_enter(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_enter");
  
  return nil;
}


// block_define_rest_argument

f2ptr raw__optimize_context__call_bytecode__block_define_rest_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_rest_argument");
  
  return nil;
}


// block_define_argument

f2ptr raw__optimize_context__call_bytecode__block_define_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_argument");
  
  return nil;
}


// block_define_last_argument

f2ptr raw__optimize_context__call_bytecode__block_define_last_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_last_argument");
  
  return nil;
}


// block_pop

f2ptr raw__optimize_context__call_bytecode__block_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_pop");
  
  return nil;
}


// block_exit_and_pop

f2ptr raw__optimize_context__call_bytecode__block_exit_and_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_exit_and_pop");
  
  return nil;
}


// block_exit_and_no_pop

f2ptr raw__optimize_context__call_bytecode__block_exit_and_no_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_exit_and_no_pop");
  
  return nil;
}


// block_eval_args_begin

f2ptr raw__optimize_context__call_bytecode__block_eval_args_begin(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_begin");
  
  return nil;
}


// block_eval_args_next

f2ptr raw__optimize_context__call_bytecode__block_eval_args_next(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_next");
  
  return nil;
}


// block_eval_args_end

f2ptr raw__optimize_context__call_bytecode__block_eval_args_end(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_end");
  
  return nil;
}




f2ptr raw__optimize_context__call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr body_bytecodes = f2__funk__body_bytecodes(cause, funk);
  {
    f2ptr bytecode_iter = body_bytecodes;
    while (bytecode_iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, bytecode_iter);
      {
	f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
	if      (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk")))                  {f2ptr result = raw__optimize_context__call_bytecode__jump__funk(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk")))                       {f2ptr result = raw__optimize_context__call_bytecode__funk(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array")))                      {f2ptr result = raw__optimize_context__call_bytecode__array(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cons")))                       {f2ptr result = raw__optimize_context__call_bytecode__cons(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "consp")))                      {f2ptr result = raw__optimize_context__call_bytecode__consp(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car")))                        {f2ptr result = raw__optimize_context__call_bytecode__car(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr")))                        {f2ptr result = raw__optimize_context__call_bytecode__cdr(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car-set")))                    {f2ptr result = raw__optimize_context__call_bytecode__car__set(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr-set")))                    {f2ptr result = raw__optimize_context__call_bytecode__cdr__set(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array_elt")))                  {f2ptr result = raw__optimize_context__call_bytecode__array_elt(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "set")))                        {f2ptr result = raw__optimize_context__call_bytecode__set(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "swap")))                       {f2ptr result = raw__optimize_context__call_bytecode__swap(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push")))                       {f2ptr result = raw__optimize_context__call_bytecode__push(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push_constant")))              {f2ptr result = raw__optimize_context__call_bytecode__push_constant(             cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "pop")))                        {f2ptr result = raw__optimize_context__call_bytecode__pop(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "copy")))                       {f2ptr result = raw__optimize_context__call_bytecode__copy(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "lookup")))                     {f2ptr result = raw__optimize_context__call_bytecode__lookup(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "define")))                     {f2ptr result = raw__optimize_context__call_bytecode__define(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "mutate-type_var")))            {f2ptr result = raw__optimize_context__call_bytecode__mutate__type_var(          cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "globalize-type_var")))         {f2ptr result = raw__optimize_context__call_bytecode__globalize__type_var(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump")))                       {f2ptr result = raw__optimize_context__call_bytecode__jump(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump")))                    {f2ptr result = raw__optimize_context__call_bytecode__if__jump(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump")))                  {f2ptr result = raw__optimize_context__call_bytecode__else__jump(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "nop")))                        {f2ptr result = raw__optimize_context__call_bytecode__nop(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "debug")))                      {f2ptr result = raw__optimize_context__call_bytecode__debug(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "tracer")))                     {f2ptr result = raw__optimize_context__call_bytecode__tracer(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "endfunk")))                    {f2ptr result = raw__optimize_context__call_bytecode__endfunk(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "compile")))                    {f2ptr result = raw__optimize_context__call_bytecode__compile(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "yield")))                      {f2ptr result = raw__optimize_context__call_bytecode__yield(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "newenv")))                     {f2ptr result = raw__optimize_context__call_bytecode__newenv(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code")))               {f2ptr result = raw__optimize_context__call_bytecode__machine_code(              cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt")))              {f2ptr result = raw__optimize_context__call_bytecode__reg_array__elt(            cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt-set")))          {f2ptr result = raw__optimize_context__call_bytecode__reg_array__elt__set(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "eq")))                         {f2ptr result = raw__optimize_context__call_bytecode__eq(                        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "not")))                        {f2ptr result = raw__optimize_context__call_bytecode__not(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "and")))                        {f2ptr result = raw__optimize_context__call_bytecode__and(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "or")))                         {f2ptr result = raw__optimize_context__call_bytecode__or(                        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "add")))                        {f2ptr result = raw__optimize_context__call_bytecode__add(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "negative")))                   {f2ptr result = raw__optimize_context__call_bytecode__negative(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "subtract")))                   {f2ptr result = raw__optimize_context__call_bytecode__subtract(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "multiply")))                   {f2ptr result = raw__optimize_context__call_bytecode__multiply(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "inverse")))                    {f2ptr result = raw__optimize_context__call_bytecode__inverse(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "divide")))                     {f2ptr result = raw__optimize_context__call_bytecode__divide(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "modulo")))                     {f2ptr result = raw__optimize_context__call_bytecode__modulo(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "increment")))                  {f2ptr result = raw__optimize_context__call_bytecode__increment(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "decrement")))                  {f2ptr result = raw__optimize_context__call_bytecode__decrement(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "numerically_equals")))         {f2ptr result = raw__optimize_context__call_bytecode__numerically_equals(        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "less_than")))                  {f2ptr result = raw__optimize_context__call_bytecode__less_than(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "greater_than")))               {f2ptr result = raw__optimize_context__call_bytecode__greater_than(              cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_push")))                 {f2ptr result = raw__optimize_context__call_bytecode__block_push(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_enter")))                {f2ptr result = raw__optimize_context__call_bytecode__block_enter(               cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_rest_argument"))) {f2ptr result = raw__optimize_context__call_bytecode__block_define_rest_argument(cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_argument")))      {f2ptr result = raw__optimize_context__call_bytecode__block_define_argument(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_last_argument"))) {f2ptr result = raw__optimize_context__call_bytecode__block_define_last_argument(cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_pop")))                  {f2ptr result = raw__optimize_context__call_bytecode__block_pop(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_pop")))         {f2ptr result = raw__optimize_context__call_bytecode__block_exit_and_pop(        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_no_pop")))      {f2ptr result = raw__optimize_context__call_bytecode__block_exit_and_no_pop(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_begin")))      {f2ptr result = raw__optimize_context__call_bytecode__block_eval_args_begin(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_next")))       {f2ptr result = raw__optimize_context__call_bytecode__block_eval_args_next(      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_end")))        {f2ptr result = raw__optimize_context__call_bytecode__block_eval_args_end(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else {
	  printf("\nbytecode UNRECOGNIZED: cannot optimize funk.");
	  return f2larva__new(cause, 5123, nil);
	}
      }
      bytecode_iter = f2__cons__cdr(cause, bytecode_iter);
    }
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
  
  initialize_primobject_6_slot(optimize_context,
			       operation_graph,
			       data_graph,
			       stack,
			       register_frame,
			       variable_frame,
			       node_bytecode_hash);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

