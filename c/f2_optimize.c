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


// optimize_data

def_primobject_2_slot(optimize_data, data_type, name);

f2ptr f2__optimize_data__new(f2ptr cause, f2ptr data_type, f2ptr name) {
  return f2optimize_data__new(cause, data_type, name);
}
def_pcfunk2(optimize_data__new, data_type, name, return f2__optimize_data__new(this_cause, data_type, name));


f2ptr raw__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_data"),
					       new__symbol(cause, "data_type"), f2__optimize_data__data_type(cause, this),
					       new__symbol(cause, "name"),      f2__optimize_data__name(     cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_data,     this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_data__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_data__terminal_print_with_frame, this, terminal_print_frame, return f2__optimize_data__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_data__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_data__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk);}
  return this;
}


// optimize_fiber

def_primobject_2_slot(optimize_fiber,
		      stack,
		      register_hash);

f2ptr f2__optimize_fiber__new(f2ptr cause) {
  f2ptr stack         = nil;
  f2ptr register_hash = f2__ptypehash__new(cause);
  {
    f2ptr register_names = f2list6__new(cause,
					      new__symbol(cause, "return"),
					      new__symbol(cause, "value"),
					      new__symbol(cause, "iter"),
					      new__symbol(cause, "program_counter"),
					      new__symbol(cause, "env"),
					      new__symbol(cause, "args"));
    f2ptr iter = register_names;
    while (iter != nil) {
      f2ptr register_name = f2__cons__car(cause, iter);
      {
	f2ptr initial_register_data = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), register_name);
	raw__ptypehash__add(cause, register_hash, register_name, initial_register_data);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2optimize_fiber__new(cause,
				 stack,
				 register_hash);
}
def_pcfunk0(optimize_fiber__new, return f2__optimize_fiber__new(this_cause));


f2ptr raw__optimize_fiber__prepare_to_call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr args_reg      = nil;
  f2ptr args_reg_iter = nil;
  {
    f2ptr funk__args = f2__funk__args(cause, funk);
    {
      f2ptr iter = funk__args;
      while (iter != nil) {
	f2ptr variable_name = f2__cons__car(cause, iter);
	{
	  f2ptr initial_variable_data = f2__optimize_data__new(cause, new__symbol(cause, "initial-variable"), variable_name);
	  f2ptr new_cons = f2cons__new(cause, initial_variable_data, nil);
	  if (args_reg == nil) {
	    args_reg      = new_cons;
	    args_reg_iter = new_cons;
	  } else {
	    f2__cons__cdr__set(cause, args_reg_iter, new_cons);
	    args_reg_iter = new_cons;
	  }
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr register_hash = f2__optimize_fiber__register_hash(cause, this);
    raw__ptypehash__add(cause, register_hash, new__symbol(cause, "args"), args_reg);
    f2ptr funk__body_bytecodes = f2__funk__body_bytecodes(cause, funk);
    raw__ptypehash__add(cause, register_hash, new__symbol(cause, "program_counter"), funk__body_bytecodes);
  }
  return nil;
}


f2ptr raw__optimize_fiber__increment_program_counter(f2ptr cause, f2ptr this) {
  
  return nil;
}


// jump-funk

f2ptr raw__optimize_fiber__call_bytecode__jump__funk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: jump-funk");
  //f2ptr stack              = f2__optimize_fiber__stack(             cause, this);
  //f2ptr register_frame     = f2__optimize_fiber__register_frame(    cause, this);
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// funk

f2ptr raw__optimize_fiber__call_bytecode__funk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: funk");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// array

f2ptr raw__optimize_fiber__call_bytecode__array(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: array");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// cons

f2ptr raw__optimize_fiber__call_bytecode__cons(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cons");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// consp

f2ptr raw__optimize_fiber__call_bytecode__consp(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: consp");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// car

f2ptr raw__optimize_fiber__call_bytecode__car(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: car");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// cdr

f2ptr raw__optimize_fiber__call_bytecode__cdr(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cdr");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// car-set

f2ptr raw__optimize_fiber__call_bytecode__car__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: car-set");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// cdr-set

f2ptr raw__optimize_fiber__call_bytecode__cdr__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: cdr-set");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// array_elt

f2ptr raw__optimize_fiber__call_bytecode__array_elt(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: array_elt");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// set

f2ptr raw__optimize_fiber__call_bytecode__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: ");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// swap

f2ptr raw__optimize_fiber__call_bytecode__swap(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: swap");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// push

f2ptr raw__optimize_fiber__call_bytecode__push(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: push");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// push_constant

f2ptr raw__optimize_fiber__call_bytecode__push_constant(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: push_constant");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// pop

f2ptr raw__optimize_fiber__call_bytecode__pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: pop");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// copy

f2ptr raw__optimize_fiber__call_bytecode__copy(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: copy");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// lookup

f2ptr raw__optimize_fiber__call_bytecode__lookup(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: lookup");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// define

f2ptr raw__optimize_fiber__call_bytecode__define(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: define");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// mutate-type_var

f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: mutate-type_var");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// globalize-type_var

f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: globalize-type_var");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// jump

f2ptr raw__optimize_fiber__call_bytecode__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: jump");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// if-jump

f2ptr raw__optimize_fiber__call_bytecode__if__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: if-jump");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// else-jump

f2ptr raw__optimize_fiber__call_bytecode__else__jump(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: else-jump");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// nop

f2ptr raw__optimize_fiber__call_bytecode__nop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: nop");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// debug

f2ptr raw__optimize_fiber__call_bytecode__debug(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: debug");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// tracer

f2ptr raw__optimize_fiber__call_bytecode__tracer(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: tracer");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// endfunk

f2ptr raw__optimize_fiber__call_bytecode__endfunk(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: endfunk");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// compile

f2ptr raw__optimize_fiber__call_bytecode__compile(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: compile");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// yield

f2ptr raw__optimize_fiber__call_bytecode__yield(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: yield");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// newenv

f2ptr raw__optimize_fiber__call_bytecode__newenv(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: newenv");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// machine_code

f2ptr raw__optimize_fiber__call_bytecode__machine_code(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: machine_code");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// reg_array-elt

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: reg_array-elt");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// reg_array-elt-set

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__set(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: reg_array-elt-set");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// eq

f2ptr raw__optimize_fiber__call_bytecode__eq(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: eq");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// not

f2ptr raw__optimize_fiber__call_bytecode__not(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: not");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// and

f2ptr raw__optimize_fiber__call_bytecode__and(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: and");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// or

f2ptr raw__optimize_fiber__call_bytecode__or(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: ");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// add

f2ptr raw__optimize_fiber__call_bytecode__add(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: add");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// negative

f2ptr raw__optimize_fiber__call_bytecode__negative(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: negative");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// subtract

f2ptr raw__optimize_fiber__call_bytecode__subtract(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: subtract");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// multiply

f2ptr raw__optimize_fiber__call_bytecode__multiply(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: multiply");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// inverse

f2ptr raw__optimize_fiber__call_bytecode__inverse(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: inverse");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// divide

f2ptr raw__optimize_fiber__call_bytecode__divide(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: divide");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// modulo

f2ptr raw__optimize_fiber__call_bytecode__modulo(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: modulo");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// increment

f2ptr raw__optimize_fiber__call_bytecode__increment(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: increment");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// decrement

f2ptr raw__optimize_fiber__call_bytecode__decrement(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: decrement");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// numerically_equals

f2ptr raw__optimize_fiber__call_bytecode__numerically_equals(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: numerically_equals");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// less_than

f2ptr raw__optimize_fiber__call_bytecode__less_than(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: less_than");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// greater_than

f2ptr raw__optimize_fiber__call_bytecode__greater_than(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: greater_than");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_push

f2ptr raw__optimize_fiber__call_bytecode__block_push(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_push");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_enter

f2ptr raw__optimize_fiber__call_bytecode__block_enter(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_enter");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_define_rest_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_rest_argument");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_define_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_argument");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_define_last_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_define_last_argument");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_pop

f2ptr raw__optimize_fiber__call_bytecode__block_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_pop");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_exit_and_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_exit_and_pop");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_exit_and_no_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_exit_and_no_pop");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_eval_args_begin

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_begin");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_eval_args_next

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_next");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}


// block_eval_args_end

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end(f2ptr cause, f2ptr this, f2ptr bytecode) {
  printf("\noptimize: block_eval_args_end");
  //f2ptr node_bytecode_hash = f2__optimize_fiber__node_bytecode_hash(cause, this);
  //f2ptr bytecode_node      = raw__ptypehash__lookup(cause, node_bytecode_hash, bytecode);
  
  return nil;
}




f2ptr raw__optimize_fiber__call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr body_bytecodes = f2__funk__body_bytecodes(cause, funk);
  {
    f2ptr bytecode_iter = body_bytecodes;
    while (bytecode_iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, bytecode_iter);
      {
	f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
	if      (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__jump__funk(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__funk(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array")))                      {f2ptr result = raw__optimize_fiber__call_bytecode__array(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cons")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__cons(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "consp")))                      {f2ptr result = raw__optimize_fiber__call_bytecode__consp(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__car(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__cdr(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car-set")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__car__set(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr-set")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__cdr__set(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array_elt")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__array_elt(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "set")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__set(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "swap")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__swap(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__push(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push_constant")))              {f2ptr result = raw__optimize_fiber__call_bytecode__push_constant(             cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "pop")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__pop(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "copy")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__copy(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "lookup")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__lookup(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "define")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__define(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "mutate-type_var")))            {f2ptr result = raw__optimize_fiber__call_bytecode__mutate__type_var(          cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "globalize-type_var")))         {f2ptr result = raw__optimize_fiber__call_bytecode__globalize__type_var(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump")))                       {f2ptr result = raw__optimize_fiber__call_bytecode__jump(                      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__if__jump(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__else__jump(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "nop")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__nop(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "debug")))                      {f2ptr result = raw__optimize_fiber__call_bytecode__debug(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "tracer")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__tracer(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "endfunk")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__endfunk(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "compile")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__compile(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "yield")))                      {f2ptr result = raw__optimize_fiber__call_bytecode__yield(                     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "newenv")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__newenv(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code")))               {f2ptr result = raw__optimize_fiber__call_bytecode__machine_code(              cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt")))              {f2ptr result = raw__optimize_fiber__call_bytecode__reg_array__elt(            cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt-set")))          {f2ptr result = raw__optimize_fiber__call_bytecode__reg_array__elt__set(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "eq")))                         {f2ptr result = raw__optimize_fiber__call_bytecode__eq(                        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "not")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__not(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "and")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__and(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "or")))                         {f2ptr result = raw__optimize_fiber__call_bytecode__or(                        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "add")))                        {f2ptr result = raw__optimize_fiber__call_bytecode__add(                       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "negative")))                   {f2ptr result = raw__optimize_fiber__call_bytecode__negative(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "subtract")))                   {f2ptr result = raw__optimize_fiber__call_bytecode__subtract(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "multiply")))                   {f2ptr result = raw__optimize_fiber__call_bytecode__multiply(                  cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "inverse")))                    {f2ptr result = raw__optimize_fiber__call_bytecode__inverse(                   cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "divide")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__divide(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "modulo")))                     {f2ptr result = raw__optimize_fiber__call_bytecode__modulo(                    cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "increment")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__increment(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "decrement")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__decrement(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "numerically_equals")))         {f2ptr result = raw__optimize_fiber__call_bytecode__numerically_equals(        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "less_than")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__less_than(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "greater_than")))               {f2ptr result = raw__optimize_fiber__call_bytecode__greater_than(              cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_push")))                 {f2ptr result = raw__optimize_fiber__call_bytecode__block_push(                cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_enter")))                {f2ptr result = raw__optimize_fiber__call_bytecode__block_enter(               cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_rest_argument"))) {f2ptr result = raw__optimize_fiber__call_bytecode__block_define_rest_argument(cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_argument")))      {f2ptr result = raw__optimize_fiber__call_bytecode__block_define_argument(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_last_argument"))) {f2ptr result = raw__optimize_fiber__call_bytecode__block_define_last_argument(cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_pop")))                  {f2ptr result = raw__optimize_fiber__call_bytecode__block_pop(                 cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_pop")))         {f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_pop(        cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_no_pop")))      {f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_begin")))      {f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_begin(     cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_next")))       {f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_next(      cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
	else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_end")))        {f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_end(       cause, this, bytecode); if (raw__larva__is_type(cause, result)) {return result;}}
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


f2ptr raw__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_fiber"),
					       new__symbol(cause, "stack"),         f2__optimize_fiber__stack(        cause, this),
					       new__symbol(cause, "register_hash"), f2__optimize_fiber__register_hash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_fiber,     this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_fiber__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_fiber__terminal_print_with_frame, this, terminal_print_frame, return f2__optimize_fiber__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_fiber__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk);}
  return this;
}



// optimize_context

def_primobject_1_slot(optimize_context,
		      initial_fiber);

f2ptr f2__optimize_context__new(f2ptr cause) {
  f2ptr initial_fiber = f2__optimize_fiber__new(cause);
  return f2optimize_context__new(cause,
				 initial_fiber);
}
def_pcfunk0(optimize_context__new, return f2__optimize_context__new(this_cause));


f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_context"),
					       new__symbol(cause, "initial_fiber"), f2__optimize_context__initial_fiber(cause, this)));
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
  f2ptr initial_fiber    = f2__optimize_context__initial_fiber(cause, optimize_context);
  {
    f2ptr result = raw__optimize_fiber__prepare_to_call_funk(cause, initial_fiber, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_funk(cause, initial_fiber, this);
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
  
  __optimize_data__symbol  = new__symbol(cause, "optimize_data");
  __optimize_fiber__symbol = new__symbol(cause, "optimize_fiber");
  __optimize_data__symbol  = new__symbol(cause, "optimize_context");
}

void f2__optimize__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars);
  
  f2__optimize__reinitialize_globalvars();
  
  // optimize_data
  
  initialize_primobject_2_slot(optimize_data,
			       data_type,
			       name);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_data__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_data to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk = never_gc(cfunk);}
  

  // optimize_fiber
  
  initialize_primobject_2_slot(optimize_fiber,
			       stack,
			       register_hash);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_fiber__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_fiber to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_context
  
  initialize_primobject_1_slot(optimize_context,
			       initial_fiber);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_context to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

