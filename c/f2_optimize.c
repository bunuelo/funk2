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


// optimize_cause

def_primobject_3_slot(optimize_cause,
		      cause_type,
		      name,
		      args);

f2ptr f2__optimize_cause__new(f2ptr cause, f2ptr cause_type, f2ptr name, f2ptr args) {
  return f2optimize_cause__new(cause, cause_type, name, args);
}
def_pcfunk3(optimize_cause__new, cause_type, name, args, return f2__optimize_cause__new(this_cause, cause_type, name, args));


f2ptr raw__optimize_cause__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_cause"),
					       new__symbol(cause, "data_type"), f2__optimize_cause__cause_type(cause, this),
					       new__symbol(cause, "name"),      f2__optimize_cause__name(      cause, this),
					       new__symbol(cause, "args"),      f2__optimize_cause__args(      cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_cause__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_cause,     this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_cause__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_cause__terminal_print_with_frame, this, terminal_print_frame, return f2__optimize_cause__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_cause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_cause__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_cause.terminal_print_with_frame__funk);}
  return this;
}


// optimize_data

def_primobject_3_slot(optimize_data,
		      data_type,
		      name,
		      optimize_cause);

f2ptr f2__optimize_data__new(f2ptr cause, f2ptr data_type, f2ptr name, f2ptr optimize_cause) {
  return f2optimize_data__new(cause, data_type, name, optimize_cause);
}
def_pcfunk3(optimize_data__new, data_type, name, optimize_cause, return f2__optimize_data__new(this_cause, data_type, name, optimize_cause));


f2ptr raw__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_data"),
					       new__symbol(cause, "data_type"),      f2__optimize_data__data_type(     cause, this),
					       new__symbol(cause, "name"),           f2__optimize_data__name(          cause, this),
					       new__symbol(cause, "optimize_cause"), f2__optimize_data__optimize_cause(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_data,        this);
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

def_primobject_8_slot(optimize_fiber,
		      optimize_context,
		      stack,
		      value,
		      iter,
		      program_counter,
		      args,
		      return_reg,
		      env);

f2ptr f2__optimize_fiber__new(f2ptr cause, f2ptr optimize_context) {
  f2ptr stack            = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "stack"),           nil);
  f2ptr value            = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "value"),           nil);
  f2ptr iter             = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "iter"),            nil);
  f2ptr program_counter  = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "program_counter"), nil);
  f2ptr args             = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "args"),            nil);
  f2ptr return_reg       = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "return_reg"),      nil);
  f2ptr env              = f2__optimize_data__new(cause, new__symbol(cause, "initial-register"), new__symbol(cause, "env"),             nil);
  return f2optimize_fiber__new(cause,
			       optimize_context,
			       stack,
			       value,
			       iter,
			       program_counter,
			       args,
			       return_reg,
			       env);
}
def_pcfunk1(optimize_fiber__new, optimize_context, return f2__optimize_fiber__new(this_cause, optimize_context));


f2ptr raw__optimize_fiber__prepare_to_call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr funk__body_bytecodes = f2__funk__body_bytecodes(cause, funk);
  f2ptr args_reg             = nil;
  f2ptr args_reg_iter        = nil;
  {
    f2ptr funk__args = f2__funk__args(cause, funk);
    {
      f2ptr iter = funk__args;
      while (iter != nil) {
	f2ptr variable_name = f2__cons__car(cause, iter);
	{
	  f2ptr initial_variable_data = f2__optimize_data__new(cause, new__symbol(cause, "initial-variable"), variable_name, nil);
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
  f2__optimize_fiber__args__set(           cause, this, args_reg);
  f2__optimize_fiber__program_counter__set(cause, this, funk__body_bytecodes);
  return nil;
}



// push registers

void raw__optimize_fiber__stack__push_constant       (f2ptr cause, f2ptr this, f2ptr constant) {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, constant, f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_value          (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__value(          this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_iter           (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__iter(           this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_program_counter(f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__program_counter(this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_args           (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__args(           this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_return_reg     (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__return_reg(     this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_env            (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, f2cons__new(cause, f2optimize_fiber__env(            this, cause), f2optimize_fiber__stack(this, cause)));}

// pop registers

void raw__optimize_fiber__stack__pop_value          (f2ptr cause, f2ptr this) {f2optimize_fiber__value__set(          this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_iter           (f2ptr cause, f2ptr this) {f2optimize_fiber__iter__set(           this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_program_counter(f2ptr cause, f2ptr this) {f2optimize_fiber__program_counter__set(this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_args           (f2ptr cause, f2ptr this) {f2optimize_fiber__args__set(           this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_return_reg     (f2ptr cause, f2ptr this) {f2optimize_fiber__return_reg__set(     this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_env            (f2ptr cause, f2ptr this) {f2optimize_fiber__env__set(            this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_nil            (f2ptr cause, f2ptr this) {f2optimize_fiber__stack__set(          this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}



f2ptr raw__optimize_fiber__increment_program_counter(f2ptr cause, f2ptr this) {
  f2ptr next_program_counter = nil;
  {
    f2ptr program_counter = f2__optimize_fiber__program_counter(cause, this);
    if (program_counter == nil) {
      return f2larva__new(cause, 523452, nil);
    }
    if (! raw__cons__is_type(cause, program_counter)) {
      return f2larva__new(cause, 523453, nil);
    }
    next_program_counter = f2__cons__cdr(cause, program_counter);
  }
  f2__optimize_fiber__program_counter__set(cause, this, next_program_counter);
  if (next_program_counter == nil) {
    f2ptr optimize_context = f2__optimize_fiber__optimize_context(cause, this);
    {
      f2ptr result = raw__optimize_context__active_fiber_finished(cause, optimize_context, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}


// jump-funk

f2ptr raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__jump__funk(f2ptr cause, f2ptr this) {
  printf("\noptimize: jump-funk");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc(cause, this);
}


// funk

f2ptr raw__optimize_fiber__call_bytecode__funk__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__funk(f2ptr cause, f2ptr this) {
  printf("\noptimize: funk");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__funk__no_increment_pc(cause, this);
}


// array

f2ptr raw__optimize_fiber__call_bytecode__array__no_increment_pc(f2ptr cause, f2ptr this, f2ptr length) {
  if (! raw__integer__is_type(cause, length)) {
    return f2larva__new(cause, 5235, nil);
  }
  f2ptr new_array = f2traced_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));
  f2__optimize_fiber__iter__set(cause, this, new_array);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__array(f2ptr cause, f2ptr this, f2ptr length) {
  printf("\noptimize: array");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__array__no_increment_pc(cause, this, length);
}


// cons

f2ptr raw__optimize_fiber__call_bytecode__cons__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr new_cons = f2cons__new(cause, nil, nil);
  f2__optimize_fiber__iter__set(cause, this, new_cons);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cons(f2ptr cause, f2ptr this) {
  printf("\noptimize: cons");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cons__no_increment_pc(cause, this);
}


// consp

f2ptr raw__optimize_fiber__call_bytecode__consp__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr result = f2bool__new(raw__cons__is_type(cause, f2__optimize_fiber__value(cause, this)));
  f2__optimize_fiber__value__set(cause, this, result);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__consp(f2ptr cause, f2ptr this) {
  printf("\noptimize: consp");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__consp__no_increment_pc(cause, this);
}


// car

f2ptr raw__optimize_fiber__call_bytecode__car__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr fiber__iter = f2__optimize_fiber__iter(cause, this);
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_car"));
    return f2larva__new(cause, 531, f2__bug__new(cause, f2integer__new(cause, 531), bug_frame));
  }
  f2ptr fiber__value = f2cons__car(fiber__iter, cause);
  f2__optimize_fiber__value__set(cause, this, fiber__value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__car(f2ptr cause, f2ptr this) {
  printf("\noptimize: car");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__car__no_increment_pc(cause, this);
}


// cdr

f2ptr raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr fiber__iter  = f2__optimize_fiber__iter(cause, this);
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_cdr"));
    return f2larva__new(cause, 5311, f2__bug__new(cause, f2integer__new(cause, 5311), bug_frame));
  }
  f2ptr fiber__value = f2cons__cdr(fiber__iter, cause);
  f2__optimize_fiber__value__set(cause, this, fiber__value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cdr(f2ptr cause, f2ptr this) {
  printf("\noptimize: cdr");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(cause, this);
}


// car-set

f2ptr raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(f2ptr cause, f2ptr this) {
  f2__cons__car__set(cause, f2__optimize_fiber__iter(cause, this), f2__optimize_fiber__value(cause, this));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__car__set(f2ptr cause, f2ptr this) {
  printf("\noptimize: car-set");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(cause, this);
}


// cdr-set

f2ptr raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc(f2ptr cause, f2ptr this) {
  f2__cons__cdr__set(cause, f2__optimize_fiber__iter(cause, this), f2__optimize_fiber__value(cause, this));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cdr__set(f2ptr cause, f2ptr this) {
  printf("\noptimize: cdr-set");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc(cause, this);
}


// array_elt

f2ptr raw__optimize_fiber__call_bytecode__array_elt__no_increment_pc(f2ptr cause, f2ptr this, f2ptr array, f2ptr index) {
  if (! raw__array__is_type(cause, array)) {
    return f2larva__new(cause, 51555, nil);
  }
  if (! raw__integer__is_type(cause, array)) {
    return f2larva__new(cause, 51556, nil);
  }
  f2__optimize_fiber__value__set(cause, this, f2__array__elt(cause, array, index));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__array_elt(f2ptr cause, f2ptr this, f2ptr array, f2ptr index) {
  printf("\noptimize: array_elt");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__array_elt__no_increment_pc(cause, this, array, index);
}


// set

f2ptr raw__optimize_fiber__call_bytecode__set__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp) {
  if      (raw__eq(cause, register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, exp);}
  else {
    return f2larva__new(cause, 5432661, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__set(f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp) {
  printf("\noptimize: ");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__set__no_increment_pc(cause, this, register_name, exp);
}


// swap

f2ptr raw__optimize_fiber__call_bytecode__swap__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1) {
  f2ptr value_0 = nil;
  f2ptr value_1 = nil;
  if      (raw__eq(cause, register_name_0, new__symbol(cause, "value")))           {value_0 = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "iter")))            {value_0 = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "program_counter"))) {value_0 = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "args")))            {value_0 = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "return_reg")))      {value_0 = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "env")))             {value_0 = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5432662, nil);
  }
  if      (raw__eq(cause, register_name_1, new__symbol(cause, "value")))           {value_1 = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "iter")))            {value_1 = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "program_counter"))) {value_1 = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "args")))            {value_1 = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "return_reg")))      {value_1 = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "env")))             {value_1 = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5432663, nil);
  }
  if      (raw__eq(cause, register_name_0, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, value_1);}
  else {
    return f2larva__new(cause, 5432664, nil);
  }
  if      (raw__eq(cause, register_name_1, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, value_0);}
  else {
    return f2larva__new(cause, 5432665, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__swap(f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1) {
  printf("\noptimize: swap");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__swap__no_increment_pc(cause, this, register_name_0, register_name_1);
}


// push

f2ptr raw__optimize_fiber__call_bytecode__push__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  if      (raw__eq(cause, register_name, new__symbol(cause, "value")))           {raw__optimize_fiber__stack__push_value(          cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {raw__optimize_fiber__stack__push_iter(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {raw__optimize_fiber__stack__push_program_counter(cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {raw__optimize_fiber__stack__push_args(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {raw__optimize_fiber__stack__push_return_reg(     cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {raw__optimize_fiber__stack__push_env(            cause, this);}
  else {
    return f2larva__new(cause, 5432369, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__push(f2ptr cause, f2ptr this, f2ptr register_name) {
  printf("\noptimize: push");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, register_name);
}


// push_constant

f2ptr raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(f2ptr cause, f2ptr this, f2ptr constant) {
  raw__optimize_fiber__stack__push_constant(cause, this, constant);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__push_constant(f2ptr cause, f2ptr this, f2ptr constant) {
  printf("\noptimize: push_constant");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(cause, this, constant);
}


// pop

f2ptr raw__optimize_fiber__call_bytecode__pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  if      (register_name == nil)                                                 {raw__optimize_fiber__stack__pop_nil(            cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "value")))           {raw__optimize_fiber__stack__pop_value(          cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {raw__optimize_fiber__stack__pop_iter(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {raw__optimize_fiber__stack__pop_program_counter(cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {raw__optimize_fiber__stack__pop_args(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {raw__optimize_fiber__stack__pop_return_reg(     cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {raw__optimize_fiber__stack__pop_env(            cause, this);}
  else {
    return f2larva__new(cause, 5432369, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__pop(f2ptr cause, f2ptr this, f2ptr register_name) {
  printf("\noptimize: pop");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, register_name);
}


// copy

f2ptr raw__optimize_fiber__call_bytecode__copy__no_increment_pc(f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name) {
  f2ptr from_value = nil;
  if      (raw__eq(cause, from_register_name, new__symbol(cause, "value")))           {from_value = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "iter")))            {from_value = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "program_counter"))) {from_value = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "args")))            {from_value = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "return_reg")))      {from_value = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "env")))             {from_value = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5433462, nil);
  }
  if      (raw__eq(cause, to_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, from_value);}
  else {
    return f2larva__new(cause, 5433564, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__copy(f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name) {
  printf("\noptimize: copy");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, from_register_name, to_register_name);
}


// lookup

f2ptr raw__optimize_fiber__call_bytecode__lookup__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr env   = f2__optimize_fiber__env(cause, this);
  f2ptr value = f2__environment__lookup_type_var_value(cause, env, type_name, var_name, value);
  if (raw__larva__is_type(cause, value)) {
    f2ptr optimize_cause = f2__optimize_cause__new(cause, new__symbol(cause, "bytecode"), new__symbol(cause, "lookup"), f2list2__new(cause, type_name, var_name));
    value = f2__optimize_data__new(cause, type_name, var_name, optimize_cause);
  }
  f2fiber__value__set(fiber, cause, fiber_value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__lookup(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  printf("\noptimize: lookup");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__lookup__no_increment_pc(cause, this, type_name, var_name);
}


// define

f2ptr raw__optimize_fiber__call_bytecode__define__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr env   = f2__optimize_fiber__env(  cause, this);
  f2ptr value = f2__optimize_fiber__value(cause, this);
  f2__optimize_fiber__value__set(cause, this, f2__environment__define_type_var_value(cause, env, type_name, var_name, value));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__define(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  printf("\noptimize: define");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, type_name, var_name);
}


// mutate-type_var

f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  printf("\noptimize: mutate-type_var");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__mutate__type_var__no_increment_pc(cause, this, type_name, var_name);
}


// globalize-type_var

f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  printf("\noptimize: globalize-type_var");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__globalize__type_var__no_increment_pc(cause, this, type_name, var_name);
}


// jump

f2ptr raw__optimize_fiber__call_bytecode__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  printf("\noptimize: jump");
  
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__jump__no_increment_pc(cause, this, new_program_counter);
}


// if-jump

f2ptr raw__optimize_fiber__call_bytecode__if__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__if__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  printf("\noptimize: if-jump");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__if__jump__no_increment_pc(cause, this, new_program_counter);
}


// else-jump

f2ptr raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__else__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  printf("\noptimize: else-jump");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(cause, this, new_program_counter);
}


// nop

f2ptr raw__optimize_fiber__call_bytecode__nop__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__nop(f2ptr cause, f2ptr this) {
  printf("\noptimize: nop");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__nop__no_increment_pc(cause, this);
}


// debug

f2ptr raw__optimize_fiber__call_bytecode__debug__no_increment_pc(f2ptr cause, f2ptr this, f2ptr debug_value) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__debug(f2ptr cause, f2ptr this, f2ptr debug_value) {
  printf("\noptimize: debug");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__debug__no_increment_pc(cause, this, debug_value);
}


// tracer

f2ptr raw__optimize_fiber__call_bytecode__tracer__no_increment_pc(f2ptr cause, f2ptr this, f2ptr name, f2ptr args) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__tracer(f2ptr cause, f2ptr this, f2ptr name, f2ptr args) {
  printf("\noptimize: tracer");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__tracer__no_increment_pc(cause, this, name, args);
}


// endfunk

f2ptr raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__endfunk(f2ptr cause, f2ptr this, f2ptr funk) {
  printf("\noptimize: endfunk");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(cause, this, funk);
}


// compile

f2ptr raw__optimize_fiber__call_bytecode__compile__no_increment_pc(f2ptr cause, f2ptr this, f2ptr protect_environment) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__compile(f2ptr cause, f2ptr this, f2ptr protect_environment) {
  printf("\noptimize: compile");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__compile__no_increment_pc(cause, this, protect_environment);
}


// yield

f2ptr raw__optimize_fiber__call_bytecode__yield__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__yield(f2ptr cause, f2ptr this) {
  printf("\noptimize: yield");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__yield__no_increment_pc(cause, this);
}


// newenv

f2ptr raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr parent_env = f2__optimize_fiber__env(cause, this);
  f2ptr new_env    = f2environment__new(cause,
					f2__frame__new(cause, nil),
					parent_env,
					f2symbol__new(cause, strlen("push-env"), (u8*)"push-env"));
  f2__optimize_fiber__env__set(cause, this, new_env);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__newenv(f2ptr cause, f2ptr this) {
  printf("\noptimize: newenv");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(cause, this);
}


// machine_code

f2ptr raw__optimize_fiber__call_bytecode__machine_code__no_increment_pc(f2ptr cause, f2ptr this, f2ptr chunk) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__machine_code(f2ptr cause, f2ptr this, f2ptr chunk) {
  printf("\noptimize: machine_code");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__machine_code__no_increment_pc(cause, this, chunk);
}


// reg_array-elt

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt(f2ptr cause, f2ptr this, f2ptr register_name) {
  printf("\noptimize: reg_array-elt");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__reg_array__elt__no_increment_pc(cause, this, register_name);
}


// reg_array-elt-set

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__set__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__set(f2ptr cause, f2ptr this, f2ptr register_name) {
  printf("\noptimize: reg_array-elt-set");
  
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__reg_array__elt__set__no_increment_pc(cause, this, register_name);
}


// eq

f2ptr raw__optimize_fiber__call_bytecode__eq__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__eq(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: eq");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__eq__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// not

f2ptr raw__optimize_fiber__call_bytecode__not__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__not(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  printf("\noptimize: not");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__not__no_increment_pc(cause, this, result_register, x_register_name);
}


// and

f2ptr raw__optimize_fiber__call_bytecode__and__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__and(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: and");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__and__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// or

f2ptr raw__optimize_fiber__call_bytecode__or__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__or(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: ");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__or__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// add

f2ptr raw__optimize_fiber__call_bytecode__add__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__add(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: add");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__add__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// negative

f2ptr raw__optimize_fiber__call_bytecode__negative__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__negative(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  printf("\noptimize: negative");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__negative__no_increment_pc(cause, this, result_register, x_register_name);
}


// subtract

f2ptr raw__optimize_fiber__call_bytecode__subtract__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__subtract(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: subtract");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__subtract__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// multiply

f2ptr raw__optimize_fiber__call_bytecode__multiply__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__multiply(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: multiply");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__multiply__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// inverse

f2ptr raw__optimize_fiber__call_bytecode__inverse__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__inverse(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  printf("\noptimize: inverse");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__inverse__no_increment_pc(cause, this, result_register, x_register_name);
}


// divide

f2ptr raw__optimize_fiber__call_bytecode__divide__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__divide(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: divide");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__divide__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// modulo

f2ptr raw__optimize_fiber__call_bytecode__modulo__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__modulo(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: modulo");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__modulo__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// increment

f2ptr raw__optimize_fiber__call_bytecode__increment__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__increment(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  printf("\noptimize: increment");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__increment__no_increment_pc(cause, this, result_register, x_register_name);
}


// decrement

f2ptr raw__optimize_fiber__call_bytecode__decrement__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__decrement(f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name) {
  printf("\noptimize: decrement");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__decrement__no_increment_pc(cause, this, result_register, x_register_name);
}


// numerically_equals

f2ptr raw__optimize_fiber__call_bytecode__numerically_equals__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__numerically_equals(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: numerically_equals");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__numerically_equals__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// less_than

f2ptr raw__optimize_fiber__call_bytecode__less_than__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__less_than(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: less_than");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__less_than__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// greater_than

f2ptr raw__optimize_fiber__call_bytecode__greater_than__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__greater_than(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  printf("\noptimize: greater_than");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__greater_than__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// block_push

f2ptr raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "return_reg"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "env"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(cause, this, __funk2.compile.debug_funk_call__symbol);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_push(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_push");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(cause, this);
}


// block_enter

f2ptr raw__optimize_fiber__call_bytecode__block_enter__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_enter(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_enter");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_enter__no_increment_pc(cause, this);
}


// block_define_rest_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
  printf("\noptimize: block_define_rest_argument");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_rest_argument__no_increment_pc(cause, this, variable_name);
}


// block_define_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__else_jump__no_increment_pc(cause, this, __funk2.compile.wrong_argument_number__bcs);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__car__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, __funk2.primobject__frame.variable__symbol, argument);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "value"), new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
  printf("\noptimize: block_define_argument");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_argument__no_increment_pc(cause, this, variable_name);
}


// block_define_last_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
  printf("\noptimize: block_define_last_argument");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_last_argument__no_increment_pc(cause, this, variable_name);
}


// block_pop

f2ptr raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_pop(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_pop");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc(cause, this);
}


// block_exit_and_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop(f2ptr cause, f2ptr this, f2ptr funk) {
  printf("\noptimize: block_exit_and_pop");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_exit_and_pop__no_increment_pc(cause, this, funk);
}


// block_exit_and_no_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(f2ptr cause, f2ptr this, f2ptr funk) {
  printf("\noptimize: block_exit_and_no_pop");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_exit_and_no_pop__no_increment_pc(cause, this, funk);
}


// block_eval_args_begin

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_eval_args_begin");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_begin__no_increment_pc(cause, this);
}


// block_eval_args_next

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_eval_args_next");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_next__no_increment_pc(cause, this);
}


// block_eval_args_end

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end__no_increment_pc(f2ptr cause, f2ptr this) {
  
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end(f2ptr cause, f2ptr this) {
  printf("\noptimize: block_eval_args_end");
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_end__no_increment_pc(cause, this);
}




f2ptr raw__optimize_fiber__call_next_bytecode(f2ptr cause, f2ptr this) {
  f2ptr bytecode = nil;
  {
    f2ptr program_counter = f2__optimize_fiber__program_counter(cause, this);
    if (! raw__cons__is_type(cause, program_counter)) {
      return f2larva__new(cause, 512431, nil);
    }
    bytecode = f2__cons__car(cause, program_counter);
  }
  {
    f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
    if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__jump__funk(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__funk(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array"))) {
      f2ptr length = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__array(cause, this, length);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cons"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cons(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "consp"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__consp(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__car(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cdr(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car-set"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__car__set(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr-set"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cdr__set(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array_elt"))) {
      f2ptr array  = f2__bytecode__arg0(cause, bytecode);
      f2ptr index  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__array_elt(cause, this, array, index);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "set"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr exp           = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__set(cause, this, register_name, exp);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "swap"))) {
      f2ptr register_name_0 = f2__bytecode__arg0(cause, bytecode);
      f2ptr register_name_1 = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__swap(cause, this, register_name_0, register_name_1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__push(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push_constant"))) {
      f2ptr constant = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__push_constant(cause, this, constant);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "pop"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__pop(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "copy"))) {
      f2ptr register_name_0 = f2__bytecode__arg0(cause, bytecode);
      f2ptr register_name_1 = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__copy(cause, this, register_name_0, register_name_1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "lookup"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__lookup(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "define"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__define(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "mutate-type_var"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__mutate__type_var(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "globalize-type_var"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__globalize__type_var(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__if__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__else__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "nop"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__nop(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "debug"))) {
      f2ptr debug_value = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__debug(cause, this, debug_value);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "tracer"))) {
      f2ptr name = f2__bytecode__arg0(cause, bytecode);
      f2ptr args = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__tracer(cause, this, name, args);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "endfunk"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__endfunk(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "compile"))) {
      f2ptr protect_environment = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__compile(cause, this, protect_environment);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "yield"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__yield(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "newenv"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__newenv(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code"))) {
      f2ptr chunk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__machine_code(cause, this, chunk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__reg_array__elt(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "reg_array-elt-set"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__reg_array__elt__set(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "eq"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__eq(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "not"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__not(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "and"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__and(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "or"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__or(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "add"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__add(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "negative"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__negative(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "subtract"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__subtract(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "multiply"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__multiply(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "inverse"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__inverse(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "divide"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__divide(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "modulo"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__modulo(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "increment"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__increment(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "decrement"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__decrement(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "numerically_equals"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__numerically_equals(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "less_than"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__less_than(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "greater_than"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__greater_than(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_push"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_push(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_enter"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_enter(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_rest_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_rest_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_last_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_last_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_pop"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_pop(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_pop"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_pop(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_no_pop"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_begin"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_begin(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_next"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_next(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_end"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_end(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else {
      printf("\nbytecode UNRECOGNIZED: cannot optimize funk.");
      return f2larva__new(cause, 5123, nil);
    }
  }
  return nil;
}


f2ptr raw__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list16__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_fiber"),
						new__symbol(cause, "stack"),           f2__optimize_fiber__stack(          cause, this),
						new__symbol(cause, "value"),           f2__optimize_fiber__value(          cause, this),
						new__symbol(cause, "iter"),            f2__optimize_fiber__iter(           cause, this),
						new__symbol(cause, "program_counter"), f2__optimize_fiber__program_counter(cause, this),
						new__symbol(cause, "args"),            f2__optimize_fiber__args(           cause, this),
						new__symbol(cause, "return_reg"),      f2__optimize_fiber__return_reg(     cause, this),
						new__symbol(cause, "env"),             f2__optimize_fiber__env(            cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_fiber,       this);
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

def_primobject_4_slot(optimize_context,
		      initial_fiber,
		      active_fiber_set,
		      branched_fiber_set,
		      finished_fiber_set);

f2ptr f2__optimize_context__new(f2ptr cause) {
  f2ptr initial_fiber      = nil;
  f2ptr active_fiber_set   = f2__set__new(cause);
  f2ptr branched_fiber_set = f2__set__new(cause);
  f2ptr finished_fiber_set = f2__set__new(cause);
  f2ptr this = f2optimize_context__new(cause,
				       initial_fiber,
				       active_fiber_set,
				       branched_fiber_set,
				       finished_fiber_set);
  initial_fiber = f2__optimize_fiber__new(cause, this);
  f2__optimize_context__initial_fiber__set(cause, this, initial_fiber);
  raw__optimize_context__add_active_fiber(cause, this, initial_fiber);
  return this;
}
def_pcfunk0(optimize_context__new, return f2__optimize_context__new(this_cause));


void raw__optimize_context__add_active_fiber(f2ptr cause, f2ptr this, f2ptr active_fiber) {
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  raw__set__add(cause, active_fiber_set, active_fiber);
}

f2ptr raw__optimize_context__active_fiber_finished(f2ptr cause, f2ptr this, f2ptr active_fiber) {
  {
    f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
    if (! raw__set__remove(cause, active_fiber_set, active_fiber)) {
      return f2larva__new(cause, 567264, nil);
    }
  }
  f2ptr finished_fiber = active_fiber;
  {
    f2ptr finished_fiber_set = f2__optimize_context__finished_fiber_set(cause, this);
    raw__set__add(cause, finished_fiber_set, finished_fiber);
  }
  return nil;
}

f2ptr raw__optimize_context__execute_one_bytecode(f2ptr cause, f2ptr this) {
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  if (raw__set__is_empty(cause, active_fiber_set)) {
    return f2larva__new(cause, 52464, nil);
  }
  f2ptr active_fiber = raw__set__an_arbitrary_element(cause, active_fiber_set);
  {
    f2ptr result = raw__optimize_fiber__call_next_bytecode(cause, active_fiber);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}


f2ptr raw__optimize_context__complete_simulation(f2ptr cause, f2ptr this) {
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  while (! raw__set__is_empty(cause, active_fiber_set)) {
    {
      f2ptr result = raw__optimize_context__execute_one_bytecode(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}

f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_context"),
						new__symbol(cause, "initial_fiber"),      f2__optimize_context__initial_fiber(     cause, this),
						new__symbol(cause, "active_fiber_set"),   f2__optimize_context__active_fiber_set(  cause, this),
						new__symbol(cause, "branched_fiber_set"), f2__optimize_context__branched_fiber_set(cause, this),
						new__symbol(cause, "finished_fiber_set"), f2__optimize_context__finished_fiber_set(cause, this)));
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
    f2ptr result = raw__optimize_context__complete_simulation(cause, optimize_context);
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
  
  __optimize_cause__symbol   = new__symbol(cause, "optimize_cause");
  __optimize_data__symbol    = new__symbol(cause, "optimize_data");
  __optimize_fiber__symbol   = new__symbol(cause, "optimize_fiber");
  __optimize_context__symbol = new__symbol(cause, "optimize_context");
}

void f2__optimize__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars);
  
  f2__optimize__reinitialize_globalvars();
  
  // optimize_cause
  
  initialize_primobject_3_slot(optimize_cause,
			       cause_type,
			       name,
			       args);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_cause.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_cause__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_cause to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_cause.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_data
  
  initialize_primobject_3_slot(optimize_data,
			       data_type,
			       name,
			       optimize_cause);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_data__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_data to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk = never_gc(cfunk);}
  

  // optimize_fiber
  
  initialize_primobject_7_slot(optimize_fiber,
			       stack,
			       value,
			       iter,
			       program_counter,
			       args,
			       return_reg,
			       env);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_fiber__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_fiber to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_context
  
  initialize_primobject_4_slot(optimize_context,
			       initial_fiber,
			       active_fiber_set,
			       branched_fiber_set,
			       finished_fiber_set);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints this optimize_context to the given terminal."); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
}

