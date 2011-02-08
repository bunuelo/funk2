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

// to-do: put all of this compiling code into bootstrap code (funk should compile itself because now compiling is too funky between fibers [need to keep bytecode equally multifunkable])

f2ptr f2cause__compiled_from__new(f2ptr cause, f2ptr name, f2ptr args) {
  release__assert(__funk2.compile.cause__compiled_from__symbol != -1, nil, "cause-compiled_from error: used before symbol defined.");
  return cause;
  //return f2cause__new(cause, nil, nil, __cause__compiled_from__symbol, f2cons__new(cause, name, args));
}

f2ptr check_bcs_valid(f2ptr bytecodes) {
  f2ptr iter = bytecodes;
  while (iter) {
    release__assert(raw__cons__is_type(nil, iter), nil, "bytecodes not cons (should be a list of bytecodes).");
    release__assert(raw__bytecode__is_type(nil, f2cons__car(iter, nil)), nil, "bytecode type is not correct.");
    iter = f2cons__cdr(iter, nil);
  }
  return bytecodes;
}

f2ptr f2__compile__funk_bc(f2ptr cause)                                               {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__funk__symbol,                nil,    nil,   nil), nil));}
f2ptr f2__compile__jump_funk(f2ptr cause)                                             {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__jump_funk__symbol,           nil,    nil,   nil), nil));}
f2ptr f2__compile__array(f2ptr cause, f2ptr length)                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__array__symbol,               length, nil,   nil), nil));}
f2ptr f2__compile__reg_array__elt(f2ptr cause, f2ptr reg, f2ptr index)                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__reg_array__elt__symbol,      reg,    index, nil), nil));}
f2ptr f2__compile__reg_array__elt__set(f2ptr cause, f2ptr reg, f2ptr index)           {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__reg_array__elt__set__symbol, reg,    index, nil), nil));}
f2ptr f2__compile__cons(f2ptr cause)                                                  {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cons__symbol,                nil,    nil,   nil), nil));}
f2ptr f2__compile__consp(f2ptr cause)                                                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__consp__symbol,               nil,    nil,   nil), nil));}
f2ptr f2__compile__car(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__car__set(f2ptr cause)                                              {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr__set(f2ptr cause)                                              {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__array_elt(f2ptr cause, f2ptr array, f2ptr index)                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__array_elt__symbol,           array,  index, nil), nil));}
f2ptr f2__compile__set(f2ptr cause, f2ptr reg, f2ptr exp)                             {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__set__symbol,                 reg,    exp,   nil), nil));}
f2ptr f2__compile__value__set(f2ptr cause, f2ptr exp)                                 {return bcs_valid(f2__compile__set(  cause, __fiber__value_reg__symbol, exp));}
f2ptr f2__compile__iter__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __fiber__iter_reg__symbol, exp));}
f2ptr f2__compile__args__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __fiber__args_reg__symbol, exp));}
f2ptr f2__compile__env__set(f2ptr cause, f2ptr exp)                                   {return bcs_valid(f2__compile__set(  cause, __fiber__env_reg__symbol, exp));}
f2ptr f2__compile__swap(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__swap__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__swap_value_and_iter(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__swap_value_and_args(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __fiber__value_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__push_constant(f2ptr cause, f2ptr constant)                         {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__push_constant__symbol, constant, nil, nil), nil));}
f2ptr f2__compile__push(f2ptr cause, f2ptr reg)                                       {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__push__symbol, reg, nil, nil),  nil));}
f2ptr f2__compile__push_value(f2ptr cause)                                            {return bcs_valid(f2__compile__push( cause, __fiber__value_reg__symbol));}
f2ptr f2__compile__push_iter(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __fiber__iter_reg__symbol));}
f2ptr f2__compile__push_args(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __fiber__args_reg__symbol));}
f2ptr f2__compile__push_env(f2ptr cause)                                              {return bcs_valid(f2__compile__push( cause, __fiber__env_reg__symbol));}
f2ptr f2__compile__push_return(f2ptr cause)                                           {return bcs_valid(f2__compile__push( cause, __fiber__return_reg__symbol));}
f2ptr f2__compile__pop(f2ptr cause, f2ptr reg)                                        {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__pop__symbol,  reg, nil, nil), nil));}
f2ptr f2__compile__pop_value(f2ptr cause)                                             {return bcs_valid(f2__compile__pop(  cause, __fiber__value_reg__symbol));}
f2ptr f2__compile__pop_iter(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __fiber__iter_reg__symbol));}
f2ptr f2__compile__pop_args(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __fiber__args_reg__symbol));}
f2ptr f2__compile__pop_env(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, __fiber__env_reg__symbol));}
f2ptr f2__compile__pop_return(f2ptr cause)                                            {return bcs_valid(f2__compile__pop(  cause, __fiber__return_reg__symbol));}
f2ptr f2__compile__pop_nil(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, nil));}
f2ptr f2__compile__copy(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__copy__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__copy_value_to_args(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__value_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__copy_value_to_iter(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__copy_iter_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__iter_reg__symbol, __fiber__value_reg__symbol));}
f2ptr f2__compile__copy_iter_to_args(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__iter_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__copy_args_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__args_reg__symbol, __fiber__value_reg__symbol));}
f2ptr f2__compile__copy_args_to_iter(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__args_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__copy_pc_to_return(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__program_counter_reg__symbol, __fiber__return_reg__symbol));}
f2ptr f2__compile__copy_return_to_pc(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__return_reg__symbol, __fiber__program_counter_reg__symbol));}

f2ptr f2__compile__lookup_type_var(f2ptr cause, f2ptr type, f2ptr var)                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__lookup_type_var__symbol, type, var, nil), nil));}
f2ptr f2bytecode__lookup_type_var__type(f2ptr this, f2ptr cause) {return f2bytecode__arg0(this, cause);}
f2ptr f2bytecode__lookup_type_var__var(f2ptr this, f2ptr cause)  {return f2bytecode__arg1(this, cause);}

f2ptr f2__compile__define_type_var(f2ptr cause, f2ptr type, f2ptr var)                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__define_type_var__symbol, type, var, nil), nil));}
f2ptr f2__compile__type_var__mutate(f2ptr cause, f2ptr type, f2ptr var)               {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__type_var__mutate__symbol, type, var, nil), nil));}
f2ptr f2__compile__globalize_type_var(f2ptr cause, f2ptr type, f2ptr var)             {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__globalize_type_var__symbol, type, var, nil), nil));}
f2ptr f2__compile__jump(f2ptr cause, f2ptr new_pc)                                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__if_jump(f2ptr cause, f2ptr new_pc)                                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__if_jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__else_jump(f2ptr cause, f2ptr new_pc)                               {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__else_jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__nop(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__nop__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__return_bytecode(f2ptr cause)                                       {return bcs_valid(f2__compile__copy( cause, __fiber__return_reg__symbol, __fiber__program_counter_reg__symbol));}
f2ptr f2__compile__debug(f2ptr cause, f2ptr value)                                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__debug__symbol, value, nil, nil), nil));}
f2ptr f2__compile__tracer(f2ptr cause, f2ptr name, f2ptr args)                        {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__tracer__symbol, name, args, nil), nil));}
f2ptr f2__compile__endfunk(f2ptr cause, f2ptr funk)                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__endfunk__symbol, funk, nil, nil), nil));}
f2ptr f2__compile__compile(f2ptr cause, f2ptr protect_environment)                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__compile__symbol, protect_environment, nil, nil), nil));}
f2ptr f2__compile__yield(f2ptr cause)                                                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__yield__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__newenv(f2ptr cause)                                                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__newenv__symbol, nil, nil, nil), nil));}

f2ptr f2__compile__lookup_var(f2ptr cause, f2ptr var)         {return bcs_valid(f2__compile__lookup_type_var(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__lookup_funkvar(f2ptr cause, f2ptr funkvar) {return bcs_valid(f2__compile__lookup_type_var(cause, __funk2.primobject__frame.funk_variable__symbol, funkvar));}

f2ptr f2__compile__define_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__define_type_var(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__define_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__define_type_var(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

f2ptr f2__compile__var__mutate(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__type_var__mutate(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__funkvar__mutate(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__type_var__mutate(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

f2ptr f2__compile__globalize_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__globalize_type_var(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__globalize_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__globalize_type_var(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

f2ptr f2__compile__block_push(                f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_push__symbol,                 nil,      nil, nil), nil));}
f2ptr f2__compile__block_enter(               f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_enter__symbol,                nil,      nil, nil), nil));}
f2ptr f2__compile__block_define_rest_argument(f2ptr cause, f2ptr argument) {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_rest_argument__symbol, argument, nil, nil), nil));}
f2ptr f2__compile__block_define_argument(     f2ptr cause, f2ptr argument) {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_argument__symbol,      argument, nil, nil), nil));}
f2ptr f2__compile__block_define_last_argument(f2ptr cause, f2ptr argument) {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_last_argument__symbol, argument, nil, nil), nil));}
f2ptr f2__compile__block_pop(                 f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_pop__symbol,                  nil,      nil, nil), nil));}
f2ptr f2__compile__block_exit_and_pop(        f2ptr cause, f2ptr funk)     {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_exit_and_pop__symbol,         funk,     nil, nil), nil));}
f2ptr f2__compile__block_exit_and_no_pop(     f2ptr cause, f2ptr funk)     {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol,      funk,     nil, nil), nil));}
f2ptr f2__compile__block_eval_args_begin(     f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_begin__symbol,      nil,      nil, nil), nil));}
f2ptr f2__compile__block_eval_args_next(      f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_next__symbol,       nil,      nil, nil), nil));}
f2ptr f2__compile__block_eval_args_end(       f2ptr cause)                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_end__symbol,        nil,      nil, nil), nil));}


f2ptr f2__compile__symbol(f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  if (is_locally_funktional) {
    boolean_t exp__is_local_variable = boolean__false;
    f2ptr iter = local_variables;
    while (iter) {
      f2ptr local_variable = f2cons__car(iter, cause);
      if (raw__symbol__eq(cause, exp, local_variable)) {
	exp__is_local_variable = boolean__true;
	break;
      }
      iter = f2cons__cdr(iter, cause);
    }
    if (! exp__is_local_variable) {
      *is_locally_funktional = boolean__false;
    }
  }
  if (is_funktional) {
    *is_funktional = boolean__false;
  }
  return bcs_valid(f2__compile__lookup_var(cause, exp));
}

f2ptr f2__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value);

//f2ptr __wrong_argument_number__bcs = nil; // this is like an interrupt pointer... (nil causes fiber to fail silently [this is a bug])

f2ptr f2__wrong_argument_number__bcs__set(f2ptr cause, f2ptr bytecodes) {
  environment__add_var_value(cause, global_environment(), new__symbol(cause, "--wrong_argument_number-bcs--"), bytecodes);
  __funk2.compile.wrong_argument_number__bcs = bytecodes;
  return nil;
}
def_pcfunk1(wrong_argument_number__bcs__set, bytecodes, return f2__wrong_argument_number__bcs__set(this_cause, bytecodes));


f2ptr f2__compile__push_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                      f2__compile__push_args( cause); f2ptr iter = full_bcs;
  iter = f2__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  iter = f2__list_cdr__set(cause, iter, f2__compile__push_constant(cause, __funk2.compile.debug_funk_call__symbol));
  return full_bcs;
}

f2ptr f2__compile__pop_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                      f2__compile__pop_nil(cause); f2ptr iter = full_bcs;
  iter = f2__list_cdr__set(cause, iter, f2__compile__pop_nil(cause));
  iter = f2__list_cdr__set(cause, iter, f2__compile__pop_nil(cause));
  return full_bcs;
}

//
// This optimization almost works...  but this doesn't work if stream is globally defined, for example:
//
//  [defunk format [stream :rest exps]
//    [mapc [funk [exp] [exp-format stream exp]] exps]]
//
f2ptr f2__compile__funk__optimize_body_bytecodes(f2ptr cause, f2ptr funk, f2ptr body_bytecodes) {
  f2ptr next = nil;
  f2ptr prev = nil;
  f2ptr iter = body_bytecodes;
  //printf("\nbefore optimization: ");
  //f2__print(cause, body_bytecodes);
  while (iter) {
    f2ptr bytecode = f2cons__car(iter, cause);
    next           = f2cons__cdr(iter, cause);
    f2ptr bytecode__command = f2bytecode__command(bytecode, cause);
    if (raw__symbol__eq(cause, bytecode__command, __funk2.bytecode.bytecode__lookup_type_var__symbol)) {
      f2ptr type = f2bytecode__lookup_type_var__type(bytecode, cause);
      f2ptr var  = f2bytecode__lookup_type_var__var(bytecode, cause);
      if (raw__symbol__eq(cause, type, __funk2.primobject__frame.variable__symbol)) {
	f2ptr funk__args = f2funk__args(funk, cause);
	boolean_t var_is_funk_arg = 0;
	f2ptr funk_arg_iter = funk__args;
	while(funk_arg_iter) {
	  f2ptr funk_arg = f2cons__car(funk_arg_iter, cause);
	  if (raw__symbol__eq(cause, var, funk_arg)) {
	    var_is_funk_arg = 1;
	  }
	  funk_arg_iter = f2cons__cdr(funk_arg_iter, cause);
	}
	if (! var_is_funk_arg) {
	  f2ptr var_assignment_cons = f2__environment__lookup_type_var_assignment_cons(cause, f2funk__env(funk, cause), __funk2.primobject__frame.variable__symbol, var);
	  if (raw__cons__is_type(cause, var_assignment_cons)) {
	    f2ptr replacement_bcs = f2__compile__array_elt(cause, var_assignment_cons, f2integer__new(cause, defarray_slot__index_var(cons__cdr)));
	    //printf("\nf2__compile__funk__optimize_body_bytecodes: could optimize var lookup!");
	    //f2__write(cause, f2cons__car(var_assignment_cons, cause));
	    //f2__write(cause, replacement_bcs);
	    //f2__write(cause, f2array__elt(var_assignment_cons, 4, cause));
	    if (prev) {
	      f2cons__cdr__set(prev, cause, replacement_bcs);
	    } else {
	      body_bytecodes = replacement_bcs;
	    }
	    f2__list_cdr__set(cause, replacement_bcs, next);
	  } else {
	    printf("\ncouldn't optimize variable!");
	  }
	}
      } else if (raw__symbol__eq(cause, type, __funk2.primobject__frame.funk_variable__symbol)) {
	f2ptr funkvar_assignment_cons = f2__environment__lookup_type_var_assignment_cons(cause, f2funk__env(funk, cause), __funk2.primobject__frame.funk_variable__symbol, var);
	if (raw__cons__is_type(cause, funkvar_assignment_cons)) {
	  f2ptr replacement_bcs = f2__compile__array_elt(cause, funkvar_assignment_cons, f2integer__new(cause, defarray_slot__index_var(cons__cdr)));
	  //printf("\nf2__compile__funk__optimize_body_bytecodes: could optimize funkvar lookup!");
	  //f2__write(cause, f2cons__car(funkvar_assignment_cons, cause));
	  //f2__write(cause, replacement_bcs);
	  //f2__write(cause, f2array__elt(funkvar_assignment_cons, 4, cause));
	  if (prev) {
	    f2cons__cdr__set(prev, cause, replacement_bcs);
	  } else {
	    body_bytecodes = replacement_bcs;
	  }
	  f2__list_cdr__set(cause, replacement_bcs, next);
	} else {
	  printf("\ncouldn't optimize funk variable!");
	}
      }
    }
    prev = iter;
    iter = next;
  }
  //printf("\nafter optimization: ");
  //f2__print(cause, body_bytecodes);
  return body_bytecodes;;
}

f2ptr f2__compile__funk(f2ptr simple_cause, f2ptr fiber, f2ptr funk) {
  release__assert(__funk2.compile.f2__compile__funk__symbol != -1, nil, "__funk2.compile.f2__compile__funk__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__funk__symbol, f2cons__new(simple_cause, funk, nil));
  
  if (!funk) {
    status("f2__compile__funk error: funk is nil.");
    return f2larva__new(cause, 129, nil);
  }
  if (!raw__funk__is_type(cause, funk)) {
    status("f2__compile__funk error: !raw__funk__is_type(funk): funk variable value is not of type funk.");
    return f2larva__new(cause, 130, nil);
  }
  
  f2ptr funk_bcs = f2__compile__value__set(cause, funk);
  if (f2funk__body_bytecodes(funk, cause)) {return bcs_valid(funk_bcs);}
  
  boolean_t funk__is_funktional         = boolean__true;
  f2ptr     local_variables             = f2funk__args(funk, cause);
  boolean_t funk__is_locally_funktional = boolean__true;
  
  f2ptr full_bcs = f2__compile__block_enter(cause); f2ptr iter = full_bcs;
  
  // define args in funk environment
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
  f2ptr var_iter = f2funk__args(funk, cause);
  while (var_iter) {
    f2ptr var = f2cons__car(var_iter, cause);
    f2ptr cdr = f2cons__cdr(var_iter, cause);
    if (raw__symbol__eq(cause, var, __funk2.globalenv.and_rest__symbol)) {
      iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_rest_argument(cause, f2cons__car(cdr, cause)));
      var_iter = nil;
    } else {
      if (cdr) {
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_argument(cause, var));
      } else {
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_last_argument(cause, var));
      }
      var_iter = cdr;
    }
  }
  
  boolean_t popped_env_and_return     = boolean__false;
  boolean_t optimize_unused_beginning = boolean__true;
  f2ptr demetropolized_body = f2funk__demetropolized_body(funk, cause);
  if (raw__larva__is_type(cause, demetropolized_body)) {
    return demetropolized_body;
  }
  f2ptr body_bcs = f2__compile__rawcode(cause, fiber, demetropolized_body, boolean__false, boolean__true, &popped_env_and_return, &funk__is_funktional, local_variables, &funk__is_locally_funktional, optimize_unused_beginning);
  if (raw__larva__is_type(cause, body_bcs)) {
    return body_bcs;
  }
  if (body_bcs && (! raw__cons__is_type(cause, body_bcs))) {return body_bcs;}
  
  //body_bcs = f2__compile__funk__optimize_body_bytecodes(cause, bytecode_tracing_on, funk, body_bcs);
  
  iter = f2__list_cdr__set(cause, iter, body_bcs);
  
  if (! popped_env_and_return) {
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_exit_and_pop(cause, funk));
  } else {
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_exit_and_no_pop(cause, funk));
  }
  
  //f2funk__is_funktional__set(funk, cause, funk__is_locally_funktional ? __funk2.globalenv.true__symbol : nil);
  f2funk__body_bytecodes__set(funk, cause, full_bcs);
  return bcs_valid(funk_bcs);
}

f2ptr f2__compile__metro(f2ptr simple_cause, f2ptr fiber, f2ptr metro) {
  release__assert(__funk2.compile.f2__compile__metro__symbol != -1, nil, "__funk2.compile.f2__compile__metro__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__metro__symbol, f2cons__new(simple_cause, metro, nil));
  
  f2ptr metro_bcs = f2__compile__value__set(cause, metro);
  if (f2metro__body_bytecodes(metro, cause)) {return bcs_valid(metro_bcs);}
  
  boolean_t  metro__is_funktional         = boolean__true;
  f2ptr local_variables              = f2metro__args(metro, cause);
  boolean_t  metro__is_locally_funktional = boolean__true;
  
  f2ptr full_bcs = f2__compile__block_enter(cause); f2ptr iter = full_bcs;
  
  // define args in metro environment
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
  f2ptr var_iter = f2metro__args(metro, cause);
  while (var_iter) {
    
    f2ptr var = f2cons__car(var_iter, cause);
    f2ptr cdr = f2cons__cdr(var_iter, cause);
    if (raw__symbol__eq(cause, var, __funk2.globalenv.and_rest__symbol)) {
      iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_rest_argument(cause, f2cons__car(cdr, cause)));
      var_iter = nil;
    } else {
      if (cdr) {
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_argument(cause, var));
      } else {
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_define_last_argument(cause, var));
      }
      var_iter = cdr;
    }
  }
  
  boolean_t popped_env_and_return     = boolean__false;
  boolean_t optimize_unused_beginning = boolean__true;
  f2ptr body_bcs = f2__compile__rawcode(cause, fiber, f2metro__demetropolized_body(metro, cause), boolean__false, boolean__true, &popped_env_and_return, &metro__is_funktional, local_variables, &metro__is_locally_funktional, optimize_unused_beginning);
  if (body_bcs && (! raw__cons__is_type(cause, body_bcs))) {return body_bcs;}
  iter = f2__list_cdr__set(cause, iter, body_bcs);
  
  if (! popped_env_and_return) {
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_exit_and_pop(cause, metro));
  } else {
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_exit_and_no_pop(cause, metro));
  }
  
  f2metro__is_funktional__set(metro, cause, metro__is_locally_funktional ? __funk2.globalenv.true__symbol : nil);
  f2metro__body_bytecodes__set(metro, cause, full_bcs);
  //f2metro__machine_code__set(metro, cause, f2chunk__new_compiled_from_metro(cause, metro));
  return bcs_valid(metro_bcs);
}

// returns last cdr of initial list
f2ptr f2__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value) {
  f2ptr iter = seq;
  f2ptr cdr;
  while ((cdr = f2cons__cdr(iter, cause))) {iter = cdr;}
  f2cons__cdr__set(iter, cause, cdr_value);
  return bcs_valid(iter);
}

f2ptr f2__compile__if(f2ptr simple_cause, f2ptr cond_bcs, f2ptr true_bcs, f2ptr false_bcs) {
  release__assert(__funk2.compile.f2__compile__if__symbol != -1, nil, "__funk2.compile.f2__compile__if__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__if__symbol, f2list3__new(simple_cause, cond_bcs, true_bcs, false_bcs));
  
  release__assert(cond_bcs, nil, "cond_bcs is nil"); release__assert(cond_bcs, nil, "true_bcs is nil");
  if (! false_bcs) {false_bcs = f2__compile__nop(cause);}
  f2ptr end_nop_bcs            = f2__compile__nop(cause);
  f2ptr true_done_jump_end_bcs = f2__compile__jump(cause, end_nop_bcs);
  f2ptr full_bcs = cond_bcs;
  f2ptr iter     = cond_bcs;
  iter = f2__list_cdr__set(cause, iter, f2__compile__else_jump(cause, false_bcs));
  iter = f2__list_cdr__set(cause, iter, true_bcs);
  iter = f2__list_cdr__set(cause, iter, true_done_jump_end_bcs);
  iter = f2__list_cdr__set(cause, iter, false_bcs);
  iter = f2__list_cdr__set(cause, iter, end_nop_bcs);
  //printf("\nfull_bcs: "); f2__print(nil, full_bcs); fflush(stdout);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__rawcode(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional, boolean_t optimize_unused) {
  release__assert(__funk2.compile.f2__compile__rawcode__symbol != -1, nil, "__funk2.compile.f2__compile__rawcode__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__rawcode__symbol, exps);
  
  //printf("rawcode: "); f2__write(exps); fflush(stdout);
  if (!exps) {
    return nil;
  }
  release__assert(raw__cons__is_type(cause, exps), nil, "exps failed cons type assertion.");
  
  boolean_t protect_subexp_environment     = (f2cons__cdr(exps, cause) != nil) || protect_environment;
  boolean_t optimize_subexp_tail_recursion = (f2cons__cdr(exps, cause) == nil) && optimize_tail_recursion;
  
  f2ptr full_bcs = nil;
  boolean_t  exp__is_funktional = boolean__true;
  f2ptr next = nil;
  do {
    f2ptr exp = f2cons__car(exps, cause);
    next      = f2cons__cdr(exps, cause);
    full_bcs = raw__compile(cause, fiber, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional);
    if (raw__larva__is_type(cause, full_bcs)) {
      return full_bcs;
    }
    if (! exp__is_funktional) {
      if (is_funktional) {
	*is_funktional = boolean__false;
      }
    }
    if (optimize_unused && exp__is_funktional && next) {
      status("optimizing funktional beginning of rawcode!");
      //f2__print(cause, exp);
      full_bcs = nil;
      exps     = next;
    }
  } while(optimize_unused && 
	  exp__is_funktional && next);
  if (!exps) {
    return full_bcs;
  }
  if (full_bcs && (! raw__cons__is_type(cause, full_bcs))) {return full_bcs;}
  exps = f2cons__cdr(exps, cause);
  
  f2ptr iter     = full_bcs;
  while (exps) {
    if (!raw__cons__is_type(cause, exps)) {
      return f2__argument_type_check_failure__larva__new(simple_cause, exps);
      //error(nil, "f2__compile__rawcode error: exps is not of type cons.");
    }
    protect_subexp_environment     = (f2cons__cdr(exps, cause) != nil) || protect_environment;
    optimize_subexp_tail_recursion = (f2cons__cdr(exps, cause) == nil) && optimize_tail_recursion;
    
    f2ptr     exp_bcs = nil;
    boolean_t exp__is_funktional = boolean__true;
    f2ptr     next = nil;
    do {
      f2ptr exp = f2cons__car(exps, cause);
      next      = f2cons__cdr(exps, cause);
      exp_bcs = raw__compile(cause, fiber, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional);
      if (raw__larva__is_type(cause, exp_bcs)) {
	return exp_bcs;
      }
      if (! exp__is_funktional) {
	if (is_funktional) {
	  *is_funktional = boolean__false;
	}
      }
      if (optimize_unused && exp__is_funktional && next) {
	status("optimizing funktional middle of rawcode!");
	//f2__print(cause, exp);
	exp_bcs = nil;
	exps    = next;
      }
    } while(optimize_unused &&
	    exp__is_funktional && next);
    if (!exps) {
      return full_bcs;
    }
    if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {return exp_bcs;}
    exps = f2cons__cdr(exps, cause);
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  }
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__if_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__if_exp__symbol != -1, nil, "__funk2.compile.f2__compile__if_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__if_exp__symbol, exps);
  
  if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;}
  exps = f2cons__cdr(exps, cause); // skip |if|
  f2ptr cond_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause); if (!raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;}
  f2ptr true_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
  
  f2ptr false_exps = exps;
  if (false_exps && (! raw__cons__is_type(cause, false_exps))) {return false_exps;}
  
  f2ptr cond_bcs   = raw__compile(cause, fiber, cond_exp, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
  if (raw__larva__is_type(cause, cond_bcs)) {
    return cond_bcs;
  }
  if (cond_bcs && (! raw__cons__is_type(cause, cond_bcs))) {return cond_bcs;}
  
  boolean_t true__popped_env_and_return = boolean__false;
  f2ptr true_bcs   = raw__compile(cause, fiber, true_exp, protect_environment, optimize_tail_recursion, &true__popped_env_and_return, is_funktional, local_variables, is_locally_funktional);
  if (raw__larva__is_type(cause, true_bcs)) {
    return true_bcs;
  }
  if (true_bcs && (! raw__cons__is_type(cause, true_bcs))) {return true_bcs;}
  
  boolean_t false__popped_env_and_return = boolean__false;
  boolean_t optimize_unused_beginning = boolean__true;
  f2ptr false_bcs = f2__compile__rawcode(cause, fiber, false_exps, protect_environment, optimize_tail_recursion, &false__popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
  if (false_bcs && (! raw__cons__is_type(cause, false_bcs))) {return false_bcs;}
  
  if (true__popped_env_and_return || false__popped_env_and_return) {
    *popped_env_and_return = boolean__true;
    
    if (! true__popped_env_and_return) {
      f2ptr block_pop = f2__compile__block_pop(cause);
      if (true_bcs) {
	f2__list_cdr__set(cause, true_bcs, block_pop);
      } else {
	true_bcs = block_pop;
      }
    }
    
    if (! false__popped_env_and_return) {
      f2ptr block_pop = f2__compile__block_pop(cause);
      if (false_bcs) {
	f2__list_cdr__set(cause, false_bcs, block_pop);
      } else {
	false_bcs = block_pop;
      }
    }
  }
  
  return bcs_valid(f2__compile__if(cause, cond_bcs, true_bcs, false_bcs));
}

f2ptr f2__compile__while(f2ptr simple_cause, f2ptr cond_bcs, f2ptr loop_bcs) {
  release__assert(__funk2.compile.f2__compile__while__symbol != -1, nil, "__funk2.compile.f2__compile__while__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__while__symbol, f2list2__new(simple_cause, cond_bcs, loop_bcs));
  
  release__assert(cond_bcs, nil, "cond_bcs is nil");
  if (! loop_bcs) {loop_bcs = f2__compile__nop(cause);}
  f2ptr end_nop_bcs             = f2__compile__nop(cause);
  f2ptr loop_done_jump_cond_bcs = f2__compile__jump(cause, cond_bcs);
  f2ptr false_jump_end_bcs      = f2__compile__jump(cause, end_nop_bcs);
  
  f2ptr full_bcs = cond_bcs;
  f2ptr iter     = cond_bcs;
  iter = f2__list_cdr__set(cause, iter, f2__compile__else_jump(cause, false_jump_end_bcs));
  iter = f2__list_cdr__set(cause, iter, loop_bcs);
  iter = f2__list_cdr__set(cause, iter, loop_done_jump_cond_bcs);
  iter = f2__list_cdr__set(cause, iter, end_nop_bcs);
  //printf("\nfull_bcs: "); f2__print(nil, nil, full_bcs); fflush(stdout);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__while_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__while_exp__symbol != -1, nil, "__funk2.compile.f2__compile__while_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__while_exp__symbol, exps);
  
  if (! raw__cons__is_type(cause, exps)) {printf("\nf2__compile__while_exp error: exps="); f2__print(nil, exps); fflush(stdout); return __funk2.compile.compile__exception;}
  exps = f2cons__cdr(exps, cause); // skip |while|
  f2ptr cond_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause); if (exps && (! raw__cons__is_type(cause, exps))) {printf("\ncompile error: exps="); f2__print(nil, exps); fflush(stdout); return __funk2.compile.compile__exception;}
  
  f2ptr loop_exps = exps;
  if (loop_exps && (! raw__cons__is_type(cause, loop_exps))) {printf("\nf2__compile__while_exp error: loop_exps="); f2__print(nil, loop_exps); fflush(stdout); return loop_exps;}
  
  f2ptr cond_bcs   = raw__compile(cause, fiber, cond_exp, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
  if (raw__larva__is_type(cause, cond_bcs)) {
    return cond_bcs;
  }
  if (cond_bcs && (! raw__cons__is_type(cause, cond_bcs))) {printf("\nf2__compile__while_exp error: cond_bcs="); f2__print(nil, cond_bcs); fflush(stdout); return cond_bcs;}
  
  boolean_t loop__popped_env_and_return    = boolean__false;
  boolean_t optimize_unused_beginning      = boolean__true;
  boolean_t protect_subexp_environment     = boolean__true || protect_environment;
  boolean_t optimize_subexp_tail_recursion = boolean__false && optimize_tail_recursion;
  f2ptr loop_bcs = f2__compile__rawcode(cause, fiber, loop_exps, protect_subexp_environment, optimize_subexp_tail_recursion, &loop__popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
  if (loop_bcs && (! raw__cons__is_type(cause, loop_bcs))) {printf("\nf2__compile__while_exp error: loop_bcs="); f2__print(nil, loop_bcs); fflush(stdout); return loop_bcs;}
  
  return bcs_valid(f2__compile__while(cause, cond_bcs, loop_bcs));
}

f2ptr f2__compile__return(f2ptr simple_cause, f2ptr value_bcs, boolean_t popped_env_and_return) {
  release__assert(__funk2.compile.f2__compile__return__symbol != -1, nil, "__funk2.compile.f2__compile__return__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__return__symbol, f2list1__new(simple_cause, value_bcs));
  
  if (! value_bcs) {value_bcs = f2__compile__nop(cause);}
  f2ptr full_bcs = value_bcs;
  f2ptr iter     = value_bcs;
  
  if (! popped_env_and_return) {
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  }
  
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_return_to_pc(cause));
  
  //printf("\nfull_bcs: "); f2__print(nil, full_bcs); fflush(stdout);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__return_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__return_exp__symbol != -1, nil, "__funk2.compile.f2__compile__return_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__return_exp__symbol, exps);
  
  if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;}
  exps = f2cons__cdr(exps, cause); // skip |return|
  f2ptr value_exp = nil;
  if (exps) {
    value_exp = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
    if (exps) {return __funk2.compile.compile__exception;}
  }
  
  boolean_t value_popped_env_and_return = boolean__false;
  f2ptr value_bcs = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, &value_popped_env_and_return, is_funktional, local_variables, is_locally_funktional);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  return bcs_valid(f2__compile__return(cause, value_bcs, value_popped_env_and_return));
}

f2ptr f2__compile__lookup_funkvar_exp(f2ptr simple_cause, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__lookup_funkvar_exp__symbol != -1, nil, "__funk2.compile.f2__compile__lookup_funkvar_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__lookup_funkvar_exp__symbol, exps);
  
  return bcs_valid(f2__compile__lookup_funkvar(cause, f2cons__car(f2cons__cdr(exps, cause), cause)));
}

f2ptr f2__compile__eval_args(f2ptr simple_cause, f2ptr fiber, f2ptr args, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__eval_args__symbol              != -1, nil, "__funk2.compile.f2__compile__eval_args__symbol not yet defined.");
  release__assert(__funk2.compile.f2__compile__eval_args__current_arg__symbol != -1, nil, "__funk2.compile.f2__compile__eval_args__current_arg__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__eval_args__symbol, args);
  
  if (! args) {
    return bcs_valid(f2__compile__args__set(cause, nil));
  }
  
  f2ptr exp_bcs = f2__compile__block_eval_args_begin(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  
  while (args) {
    f2ptr current_arg = f2cons__car(args, cause);
    f2ptr next_args   = f2cons__cdr(args, cause);
    f2ptr arg_cause   = f2cause__compiled_from__new(cause, __funk2.compile.f2__compile__eval_args__current_arg__symbol, f2cons__new(cause, current_arg, nil));
    
    exp_bcs     = raw__compile(arg_cause, fiber, current_arg, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
    if (raw__larva__is_type(cause, exp_bcs)) {
      return exp_bcs;
    }
    if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {return exp_bcs;}
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    if (next_args) {
      exp_bcs = f2__compile__block_eval_args_next(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
    } else {
      exp_bcs = f2__compile__block_eval_args_end(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
    }
    args = next_args;
  }
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__define_funk_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__define_funk_exp__symbol != -1, nil, "__funk2.compile.f2__compile__define_funk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__define_funk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs          = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr define_funkvar_bcs = f2__compile__define_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, define_funkvar_bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__define_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__define_exp__symbol != -1, nil, "__funk2.compile.f2__compile__define_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__define_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs      = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr define_var_bcs = f2__compile__define_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, define_var_bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__mutate_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__mutate_exp__symbol != -1, nil, "__funk2.compile.f2__compile__mutate_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__mutate_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr var_mutate__bcs = f2__compile__var__mutate(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, var_mutate__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__mutatefunk_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__mutatefunk_exp__symbol != -1, nil, "__funk2.compile.f2__compile__mutatefunk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__mutatefunk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs       = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr funkvar_mutate__bcs = f2__compile__funkvar__mutate(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, funkvar_mutate__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__globalize_var_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__globalize_var_exp__symbol != -1, nil, "__funk2.compile.f2__compile__globalize_var_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__globalize_var_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr var_set__bcs = f2__compile__globalize_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, var_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__globalize_funkvar_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__globalize_funkvar_exp__symbol != -1, nil, "__funk2.compile.f2__compile__globalize_funkvar_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__globalize_funkvar_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs       = raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, value_bcs)) {
    return value_bcs;
  }
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {return value_bcs;}
  f2ptr funkvar_set__bcs = f2__compile__globalize_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, funkvar_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__apply_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return) {
  release__assert(__funk2.compile.f2__compile__apply_exp__symbol != -1, nil, "__funk2.compile.f2__compile__apply_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__apply_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr funk_exp = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr args_exp = f2cons__car(exps, cause);
  
  f2ptr full_bcs = raw__compile(cause, fiber, funk_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, full_bcs)) {
    return full_bcs;
  }
  if (full_bcs && (! raw__cons__is_type(cause, full_bcs))) {
    return full_bcs;
  }
  f2ptr iter = full_bcs;
  
  iter          = f2__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  f2ptr exp_bcs = raw__compile(cause, fiber, args_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL);
  if (raw__larva__is_type(cause, exp_bcs)) {
    return exp_bcs;
  }
  if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
    return exp_bcs;
  }
  iter = f2__list_cdr__set(cause, iter, exp_bcs);
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_value_to_args(cause));
  iter = f2__list_cdr__set(cause, iter, f2__compile__pop_value(cause));
  if (optimize_tail_recursion) {
    if (popped_env_and_return != NULL) {
      //printf("\npopped env and return!"); fflush(stdout);
      *popped_env_and_return = boolean__true;
    }
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  }
  if (protect_environment) {
    //iter = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_push(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    //iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  } else {
    iter = f2__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
  }
  return bcs_valid(full_bcs);
}

f2ptr raw__apply_funk(f2ptr simple_cause, f2ptr fiber, f2ptr funk, f2ptr args);

f2ptr f2__compile__funkvar_call(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__funkvar_call__symbol != -1, nil, "__funk2.compile.f2__compile__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__funkvar_call__symbol, exps);
  
  f2ptr funkvar = f2cons__car(exps, cause);
  //f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), funkvar);
  f2ptr funkvar_value = f2__fiber__lookup_type_variable_value(cause, fiber, __funk2.primobject__frame.funk_variable__symbol, funkvar);
  if (raw__metrocfunk__is_type(cause, funkvar_value)) {
    f2ptr exp_bcs = raw__compile(cause, fiber, f2__metrocfunk__apply(cause, funkvar_value, fiber, f2cons__cdr(exps, cause)), boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
    if (raw__larva__is_type(cause, exp_bcs)) {
      return exp_bcs;
    }
    return bcs_valid(exp_bcs);
  } else {
    if ((! (raw__cfunk__is_type(cause, funkvar_value) ||
	    raw__funk__is_type(cause, funkvar_value))) ||
	(! raw__funkable__is_funktional(cause, funkvar_value))) {
      if (is_funktional) {
	*is_funktional = boolean__false;
      }
      if (is_locally_funktional) {
	*is_locally_funktional = boolean__false;
      }
    }
    f2ptr full_bcs = f2__compile__eval_args(cause, fiber, f2cons__cdr(exps, cause), is_funktional, local_variables, is_locally_funktional); f2ptr iter = full_bcs;
    if (raw__larva__is_type(cause, full_bcs)) {
      return full_bcs;
    }
    boolean_t all_args_are_immutable = boolean__true;
    if (is_funktional && (*is_funktional)) {
      f2ptr arg_iter = f2cons__cdr(exps, cause);
      while (arg_iter) {
	f2ptr arg = f2cons__car(arg_iter, cause);
	if (! raw__exp__is_immutable(cause, arg)) {
	  all_args_are_immutable = boolean__false;
	  break;
	}
	arg_iter = f2cons__cdr(arg_iter, cause);
      }
    }
    if (is_funktional && (*is_funktional) && all_args_are_immutable) {
      status("found funktional optimization opportunity!");
      f2ptr funk_apply__result = raw__apply_funk(cause, fiber, funkvar_value, f2cons__cdr(exps, cause));
      if (raw__larva__is_type(cause, funk_apply__result)) {
	return funk_apply__result;
      }
      full_bcs = f2__compile__value__set(cause, funk_apply__result); iter = full_bcs;
    } else {
      iter     = f2__list_cdr__set(cause, iter, f2__compile__lookup_funkvar(cause, funkvar));
      if (optimize_tail_recursion) {
	if (popped_env_and_return) {
	  //printf("\npopped env and return!"); fflush(stdout);
	  *popped_env_and_return = boolean__true;
	}
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
      }
      if (protect_environment) {
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
	////iter   = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause, bytecode_tracing_on));
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_push(cause));
	iter = f2__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
	iter = f2__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
	////iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause, bytecode_tracing_on));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
      } else {
	//printf("\ntail recursion optimized!"); fflush(stdout);
	//iter         = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause, bytecode_tracing_on));
	//iter         = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause, bytecode_tracing_on));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
	//iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause, bytecode_tracing_on));
	//iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause, bytecode_tracing_on));
      }
    }
    return bcs_valid(full_bcs);
  }
  status("shouldn't get here.");
  return f2larva__new(cause, 16, nil);
}

int __total_apply_metro_count = 0;

f2ptr raw__apply_metro(f2ptr simple_cause, f2ptr fiber, f2ptr metro, f2ptr args) {
  release__assert(__funk2.compile.raw__apply_metro__symbol != -1, nil, "__funk2.compile.raw__apply_metro__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.raw__apply_metro__symbol, f2list2__new(simple_cause, metro, args));
  
#ifdef DEBUG_COMPILE
  __total_apply_metro_count ++;
  if ((__total_apply_metro_count % 1000) == 0) {
    printf("\ntotal apply metro count = %d", __total_apply_metro_count);
  }
  //printf ("\nstarting apply metro."); fflush(stdout);
#endif // DEBUG_COMPILE
  
  //printf ("\nFiber 0x%X creating child compile fiber.", (uint)fiber); fflush(stdout);
  f2ptr new_fiber = f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), metro, args);
  
  //f2fiber__keep_undead__set(new_fiber, cause, __true__symbol);
  //printf ("\nCompile fiber created: 0x%X", (uint)new_fiber); fflush(stdout);
  f2__global_scheduler__complete_fiber(cause, new_fiber);
  
  f2ptr value = f2fiber__value(new_fiber, cause);
  f2fiber__keep_undead__set(new_fiber, cause, nil);
  if (raw__larva__is_type(cause, value)) {
    return value;
  }
  if ((f2__fiber__paused(cause, new_fiber) != nil) &&
      raw__bug__is_type(cause, value)) {
    return f2larva__new(cause, 32, value);
  }
  
  //printf ("\ncompleted apply metro: "); f2__write(fiber, value); fflush(stdout);
  
  return value;
}

int __total_apply_funk_count = 0;

f2ptr raw__apply_funk(f2ptr simple_cause, f2ptr fiber, f2ptr funk, f2ptr args) {
  release__assert(__funk2.compile.raw__apply_funk__symbol != -1, nil, "__funk2.compile.raw__apply_funk__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.raw__apply_funk__symbol, f2list2__new(simple_cause, funk, args));
  
#ifdef DEBUG_COMPILE
  __total_apply_funk_count ++;
  if ((__total_apply_funk_count % 1000) == 0) {
    printf("\ntotal apply funk count = %d", __total_apply_funk_count);
  }
  //printf ("\nstarting apply funk."); fflush(stdout);
#endif // DEBUG_COMPILE
  
  //printf ("\nFiber 0x%X creating child compile fiber.", (uint)fiber); fflush(stdout);
  f2ptr new_fiber = f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), funk, args);
  
  //f2fiber__keep_undead__set(new_fiber, cause, __true__symbol);
  //printf ("\nCompile fiber created: 0x%X", (uint)new_fiber); fflush(stdout);
  f2__global_scheduler__complete_fiber(cause, new_fiber);
  
  f2ptr value = f2fiber__value(new_fiber, cause);
  f2fiber__keep_undead__set(new_fiber, cause, nil);
  if (raw__larva__is_type(cause, value)) {
    return value;
  }
  if ((f2__fiber__paused(cause, new_fiber) != nil) &&
      raw__bug__is_type(cause, value)) {
    return f2larva__new(cause, 32, value);
  }
  
  //printf ("\ncompleted apply funk: "); f2__write(fiber, value); fflush(stdout);
  
  return value;
}

f2ptr f2__compile__backquote_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__backquote_exp__symbol != -1, nil, "__funk2.compile.f2__compile__backquote_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__backquote_exp__symbol, exps);
  
  f2ptr args = f2cons__cdr(exps, cause);
  if (! args) {return bcs_valid(f2__compile__value__set(cause, nil));}
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = raw__compile(cause, fiber, f2cons__car(args, cause), boolean__true, boolean__false, NULL, NULL, nil, NULL);
    if (raw__larva__is_type(cause, exp_bcs)) {
      return exp_bcs;
    }
    if(exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {return exp_bcs;}
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__car__set(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
    args = f2cons__cdr(args, cause);
    if (args) {
      exp_bcs   = f2__compile__copy_iter_to_value(cause);                   iter = f2__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cons(cause);                                 iter = f2__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(cause);                  iter = f2__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cdr__set(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(cause);                  iter = f2__list_cdr__set(cause, iter, exp_bcs);
    }
  }
  exp_bcs       = f2__compile__copy_args_to_value(cause);                   iter = f2__list_cdr__set(cause, iter, exp_bcs);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__backquote_append_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__backquote_append_exp__symbol != -1, nil, "__funk2.compile.f2__compile__backquote_append_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__backquote_append_exp__symbol, exps);
  
  f2ptr args = f2cons__cdr(exps, cause);
  if (! args) {return bcs_valid(f2__compile__value__set(cause, nil));}
  f2ptr cdr = f2cons__cdr(args, cause);
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = raw__compile(cause, fiber, f2cons__car(args, cause), boolean__true, boolean__false, NULL, NULL, nil, NULL);
    if (raw__larva__is_type(cause, exp_bcs)) {
      return exp_bcs;
    }
    if(exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {return exp_bcs;}
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    if (cdr) {
      exp_bcs   = f2__compile__car__set(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    } else {
      exp_bcs   = f2__compile__cdr__set(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    }

    args = f2cons__cdr(args, cause);
    if (args) {
      cdr = f2cons__cdr(args, cause);
      if (cdr) {
	exp_bcs = f2__compile__copy_iter_to_value(cause);  iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cons(cause);                iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cdr__set(cause);            iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
      }
    }
  }
  
  exp_bcs       = f2__compile__copy_args_to_value(cause);                   iter = f2__list_cdr__set(cause, iter, exp_bcs);
  return bcs_valid(full_bcs);
}

f2ptr f2__is_compile_special_symbol(f2ptr cause, f2ptr exp) {
  return ((raw__symbol__eq(cause, exp, __funk2.globalenv.quote__symbol))                  ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.backquote__list__symbol))        ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.backquote__list_append__symbol)) ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.if__symbol))                     ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.while__symbol))                  ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.return__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.apply__symbol))                  ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.funkvar__symbol))                ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.define_funk__symbol))            ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.define__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.mutatefunk__symbol))             ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.mutate__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.globalize__symbol))              ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.globalize_funk__symbol))         ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.yield__symbol))                  ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode__symbol))               ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.rawcode__symbol)));
}

f2ptr f2__compile__special_symbol_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__special_symbol_exp__symbol != -1, nil, "__funk2.compile.f2__compile__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__special_symbol_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  if (raw__symbol__eq(cause, car, __funk2.globalenv.quote__symbol))                                                                                                                            {return bcs_valid(f2__compile__value__set(cause, f2cons__car(f2cons__cdr(exp, cause), cause)));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list__symbol))        {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__backquote_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list_append__symbol)) {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__backquote_append_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.if__symbol))                                                                                                                               {return bcs_valid(f2__compile__if_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.while__symbol))                                                                                                                            {return bcs_valid(f2__compile__while_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.return__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__return_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.apply__symbol))                  {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__apply_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.funkvar__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__lookup_funkvar_exp(cause, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define_funk__symbol))            {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__define_funk_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__define_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutatefunk__symbol))             {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__mutatefunk_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutate__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__mutate_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize__symbol))              {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__globalize_var_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize_funk__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
    f2ptr globalize_funkvar_bcs = f2__compile__globalize_funkvar_exp(cause, fiber, exp);
    if (raw__larva__is_type(cause, globalize_funkvar_bcs)) {
      return globalize_funkvar_bcs;
    }
    return bcs_valid(globalize_funkvar_bcs);
  }
  if (raw__symbol__eq(cause, car, __funk2.globalenv.yield__symbol))                  {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__yield(cause));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode__symbol))               {return bcs_valid(f2__compile__bytecode_exp(cause, exp, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.rawcode__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__rawcode_exp(cause, exp, fiber, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  status("tried to compile special symbol exp: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  //error(nil, "f2__compile__special_symbol_exp error: expression is not special symbol expression.");
  return f2larva__new(cause, 127, nil);
}

f2ptr f2__demetropolize__funkvar_call(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize__funkvar_call__symbol != -1, nil, "__funk2.compile.f2__demetropolize__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize__funkvar_call__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr did_something = nil;
  f2ptr args = f2cons__cdr(exp, cause);
  if (!args) {
    return f2cons__new(cause, nil, exp);
  }
  f2ptr demetro_exp  = f2cons__new(cause, f2cons__car(exp, cause), nil);
  f2ptr iter         = args;
  f2ptr demetro_iter = demetro_exp;
  while (iter) {
    f2ptr arg                 = f2cons__car(iter, cause);
    
    f2ptr demetro_arg__values = f2__demetropolize_once(cause, fiber, env, arg);
    if (raw__larva__is_type(cause, demetro_arg__values)) {
      return demetro_arg__values;
    }
    if(f2cons__car(demetro_arg__values, cause)) {
      did_something = __funk2.globalenv.true__symbol;
    }
    f2ptr demetro_arg         = f2cons__cdr(demetro_arg__values, cause);
    
    f2ptr demetro_iter_next   = f2cons__new(cause, demetro_arg, nil);
    
    f2cons__cdr__set(demetro_iter, cause, demetro_iter_next);
    
    demetro_iter = demetro_iter_next;
    iter         = f2cons__cdr(iter, cause);
  }
  return f2cons__new(cause, did_something, demetro_exp);
}

void dont_know_how_to_compile() {
  status("don't know how to compile [breakpoint].");
}

f2ptr f2__compile__cons_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__cons_exp__symbol != -1, nil, "__funk2.compile.f2__compile__cons_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__cons_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  //f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
  f2ptr funkvar_value = f2__fiber__lookup_type_variable_value(cause, fiber, __funk2.primobject__frame.funk_variable__symbol, car);
  
  if (raw__metro__is_type(cause, funkvar_value)) {
    f2ptr metro_apply_result = raw__apply_metro(cause, fiber, funkvar_value, f2cons__cdr(exp, cause));
    if (raw__larva__is_type(cause, metro_apply_result)) {
      return metro_apply_result;
    }
    return raw__compile(cause, fiber, metro_apply_result, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
  }
  if (f2__is_compile_special_symbol(cause, car)) {
    f2ptr special_symbol_result = f2__compile__special_symbol_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional);
    if (raw__larva__is_type(cause, special_symbol_result)) {
      return special_symbol_result;
    }
    return bcs_valid(special_symbol_result);
  }
  if (raw__symbol__is_type(cause, car))          {return bcs_valid(f2__compile__funkvar_call(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  status("tried to compile: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("don't know how to compile."); // should throw exception... (or return larva)
  dont_know_how_to_compile();
  {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "do_not_know_how_to_compile"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "compile-cons_exp"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "exp"),      exp);
    return f2larva__new(cause, 125, f2__bug__new(cause, f2integer__new(cause, 125), bug_frame));
  }
}

f2ptr f2__compile__bytecode_exp(f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  if (! raw__cons__is_type(cause, exp)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr exp_iter = f2cons__cdr(exp, cause);
  if (! raw__cons__is_type(cause, exp_iter)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr command = f2cons__car(exp_iter, cause);
  if (! raw__symbol__is_type(cause, command)) {
    return f2larva__new(cause, 1, nil);
  }

  if        (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__push__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__pop__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__copy__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__swap__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__array__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__reg_array__elt__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__reg_array__elt__set__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__cons__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__car__set__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__funk__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__jump_funk__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__set__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__cdr__set__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__array_elt__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__lookup_type_var__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__define_type_var__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__else_jump__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__car__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__cdr__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__type_var__mutate__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__globalize_type_var__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__jump__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__nop__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__debug__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__tracer__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__endfunk__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__compile__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__yield__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__newenv__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__machine_code__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  }
  
  f2ptr args    = f2cons__cdr(exp_iter, cause);
  if (! raw__cons__is_type(cause, args)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr arg0     = f2cons__car(args, cause);
  f2ptr cdr_args = f2cons__cdr(args, cause);
  if (! raw__cons__is_type(cause, cdr_args)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr arg1      = f2cons__car(cdr_args, cause);
  f2ptr cddr_args = f2cons__cdr(cdr_args, cause);
  if (! raw__cons__is_type(cause, cddr_args)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr arg2 = f2cons__car(cddr_args, cause);
  return f2cons__new(cause, f2bytecode__new(cause, command, arg0, arg1, arg2), nil);
}

f2ptr f2__compile__rawcode_exp(f2ptr cause, f2ptr exp, f2ptr fiber, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  if (! raw__cons__is_type(cause, exp)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr exps = f2cons__cdr(exp, cause);
  if (! raw__cons__is_type(cause, exps)) {
    return f2larva__new(cause, 1, nil);
  }
  //f2ptr f2__compile__rawcode(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  boolean_t optimize_unused_beginning = boolean__false;
  return f2__compile__rawcode(cause, fiber, exps, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
}

f2ptr f2__demetropolize__special_symbol_exp(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize__special_symbol_exp__symbol != -1, nil, "__funk2.compile.f2__demetropolize__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize__special_symbol_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  if (raw__symbol__eq(cause, car, __funk2.globalenv.quote__symbol))                  {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list__symbol))        {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list_append__symbol)) {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.if__symbol))                     {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.while__symbol))                  {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.return__symbol))                 {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.apply__symbol))                  {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.funkvar__symbol))                {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define_funk__symbol))            {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define__symbol))                 {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutatefunk__symbol))             {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutate__symbol))                 {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize__symbol))              {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize_funk__symbol))         {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.yield__symbol))                  {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode__symbol))               {return f2cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.rawcode__symbol))                {return f2cons__new(cause, nil, exp);}
  status("tried to compile special symbol exp: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  status("f2__demetropolize__special_symbol_exp error: expression is not special symbol expression.");
  return f2larva__new(cause, 126, nil);
}

f2ptr f2__demetropolize_once(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize_once__symbol != -1, nil, "__funk2.compile.f2__demetropolize_once__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize_once__symbol, f2cons__new(simple_cause, exp, nil));
  if (raw__cons__is_type(cause, exp)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
      if      (raw__metro__is_type(cause, funkvar_value)) {
	f2ptr metro_apply_result = raw__apply_metro(simple_cause, fiber, funkvar_value, f2cons__cdr(exp, cause));
	if (raw__larva__is_type(cause, metro_apply_result)) {
	  return metro_apply_result;
	}
	values = f2cons__new(simple_cause, __funk2.globalenv.true__symbol, metro_apply_result);
      }
      else if (f2__is_compile_special_symbol(cause, car)) {values = f2__demetropolize__special_symbol_exp(simple_cause, fiber, env, exp);}
      else if (raw__symbol__is_type(cause, car))          {values = f2__demetropolize__funkvar_call(simple_cause, fiber, env, exp);}
      else                                                {values = f2cons__new(simple_cause, nil, exp);}
    }
    
    f2ptr did_something = nil;
    if(f2cons__car(values, cause)) {did_something = __funk2.globalenv.true__symbol;}
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      return f2cons__new(cause, __funk2.globalenv.true__symbol, retval);
    } else {
      return f2cons__new(cause, nil, exp);
    }
  }
  return f2cons__new(cause, nil, exp);
}

f2ptr f2__demetropolize_full__with_status(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize_full__symbol != -1, nil, "__funk2.compile.f2__demetropolize_full__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize_full__symbol, f2cons__new(simple_cause, exp, nil));
  if (raw__cons__is_type(cause, exp)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
      if      (raw__metro__is_type(cause, funkvar_value)) {
	f2ptr metro_apply_result = raw__apply_metro(simple_cause, fiber, funkvar_value, f2cons__cdr(exp, cause));
	if (raw__larva__is_type(cause, metro_apply_result)) {
	  return metro_apply_result;
	}
	values = f2cons__new(simple_cause, __funk2.globalenv.true__symbol, metro_apply_result);
      }
      else if (f2__is_compile_special_symbol(cause, car)) {values = f2__demetropolize__special_symbol_exp(simple_cause, fiber, env, exp);}
      else if (raw__symbol__is_type(cause, car))          {values = f2__demetropolize__funkvar_call(simple_cause, fiber, env, exp);}
      else                                                {values = f2cons__new(simple_cause, nil, exp);}
    }
    
    f2ptr did_something = nil;
    if(f2cons__car(values, cause)) {did_something = __funk2.globalenv.true__symbol;}
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      f2ptr demetropolize_result = f2__demetropolize_full__with_status(cause, fiber, env, retval);
      if (raw__larva__is_type(cause, demetropolize_result)) {
	return demetropolize_result;
      }
      return f2cons__new(cause, __funk2.globalenv.true__symbol, f2cons__cdr(demetropolize_result, cause));
    } else {
      return f2cons__new(cause, nil, exp);
    }
  }
  return f2cons__new(cause, nil, exp);
}



int __compile__recursion_count = 0;
int __total_enter_compile_count = 0;
int __total_compile_count = 0;

void enter_compile_debug() {
  __total_enter_compile_count ++;
  if ((__total_enter_compile_count % 1000) == 0) {
    printf("\ntotal enter compile count = %d", __total_enter_compile_count);
  }
  //printf("\ncompile starting.");
}

f2ptr raw__compile(f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.raw__compile__symbol != -1, nil, "__funk2.compile.raw__compile__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.raw__compile__symbol, f2cons__new(simple_cause, exp, nil));
#ifdef DEBUG_COMPILE
  if (__compile__recursion_count == 0) {enter_compile_debug();}
  __total_compile_count ++;
  if ((__total_compile_count % 1000) == 0) {
    printf("\ntotal compile count = %d", __total_compile_count);
  }
  __compile__recursion_count ++;
#endif // DEBUG_COMPILE
  f2ptr result_bcs = nil;
  if      (!exp)                                {result_bcs = f2__compile__value__set(cause, nil);}
  else if (raw__integer__is_type(cause, exp))   {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__pointer__is_type(cause, exp))   {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__float__is_type(cause, exp))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__double__is_type(cause, exp))    {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__gfunkptr__is_type(cause, exp))  {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__string__is_type(cause, exp))    {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__symbol__is_type(cause, exp))    {result_bcs = f2__compile__symbol(    cause, exp, is_funktional, local_variables, is_locally_funktional);}
  else if (raw__cons__is_type(cause, exp))      {result_bcs = f2__compile__cons_exp(  cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional);}
  else if (raw__array__is_type(cause, exp))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__cfunk__is_type(cause, exp))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__funk__is_type(cause, exp))      {result_bcs = f2__compile__funk(      cause, fiber, exp);}
  else if (raw__metro__is_type(cause, exp))     {result_bcs = f2__compile__metro(     cause, fiber, exp);}
  else if (raw__exception__is_type(cause, exp)) {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__bytecode__is_type(cause, exp))  {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__larva__is_type(cause, exp))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__char__is_type(cause, exp))      {result_bcs = f2__compile__value__set(cause, exp);}
  else {
    status("unrecognized type in compile.");
    return f2larva__new(cause, 128, nil);
  }
  __compile__recursion_count --;
#ifdef DEBUG_COMPILE
  if (__compile__recursion_count == 0) {
    //printf("\ncompile ending.");
  }
#endif // DEBUG_COMPILE
  if (raw__larva__is_type(cause, result_bcs)) {
    return result_bcs;
  }
  return bcs_valid(result_bcs);
}

void f2__compile__reinitialize_globalvars() {
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  {char* str = "compile:cause-compiled_from"; __funk2.compile.cause__compiled_from__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:exception";           __funk2.compile.compile__exception           = f2symbol__new(cause, strlen(str), (u8*)str);}
  
  {char* str = "compile:f2__compile__funk";                     __funk2.compile.f2__compile__funk__symbol                     = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__metro";                    __funk2.compile.f2__compile__metro__symbol                    = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__if";                       __funk2.compile.f2__compile__if__symbol                       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__if_exp";                   __funk2.compile.f2__compile__if_exp__symbol                   = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__while";                    __funk2.compile.f2__compile__while__symbol                    = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__while_exp";                __funk2.compile.f2__compile__while_exp__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__return";                   __funk2.compile.f2__compile__return__symbol                   = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__return_exp";               __funk2.compile.f2__compile__return_exp__symbol               = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__rawcode";                  __funk2.compile.f2__compile__rawcode__symbol                  = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__lookup_funkvar_exp";       __funk2.compile.f2__compile__lookup_funkvar_exp__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__eval_args";                __funk2.compile.f2__compile__eval_args__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__eval_args__current_arg";   __funk2.compile.f2__compile__eval_args__current_arg__symbol   = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__define_funk_exp";          __funk2.compile.f2__compile__define_funk_exp__symbol          = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__define_exp";               __funk2.compile.f2__compile__define_exp__symbol               = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__mutate_exp";               __funk2.compile.f2__compile__mutate_exp__symbol               = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__mutatefunk_exp";           __funk2.compile.f2__compile__mutatefunk_exp__symbol           = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__globalize_var_exp";        __funk2.compile.f2__compile__globalize_var_exp__symbol        = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__globalize_funkvar_exp";    __funk2.compile.f2__compile__globalize_funkvar_exp__symbol    = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__apply_exp";                __funk2.compile.f2__compile__apply_exp__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__funkvar_call";             __funk2.compile.f2__compile__funkvar_call__symbol             = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__apply_metro";                      __funk2.compile.raw__apply_metro__symbol                      = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__apply_funk";                       __funk2.compile.raw__apply_funk__symbol                       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__backquote_exp";            __funk2.compile.f2__compile__backquote_exp__symbol            = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__backquote_append_exp";     __funk2.compile.f2__compile__backquote_append_exp__symbol     = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__special_symbol_exp";       __funk2.compile.f2__compile__special_symbol_exp__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__cons_exp";                 __funk2.compile.f2__compile__cons_exp__symbol                 = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize__special_symbol_exp"; __funk2.compile.f2__demetropolize__special_symbol_exp__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize__funkvar_call";       __funk2.compile.f2__demetropolize__funkvar_call__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize_once";                __funk2.compile.f2__demetropolize_once__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize_full";                __funk2.compile.f2__demetropolize_full__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__compile";                          __funk2.compile.raw__compile__symbol                          = f2symbol__new(cause, strlen(str), (u8*)str);}
  
  {char* str = "debug_funk_call";                               __funk2.compile.debug_funk_call__symbol                       = f2symbol__new(cause, strlen(str), (u8*)str);}
  
  __funk2.compile.wrong_argument_number__bcs = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "--wrong_argument_number-bcs--"));
}

void f2__compile__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "compile", "", &f2__compile__reinitialize_globalvars);
  
  f2__compile__reinitialize_globalvars();
  
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), __funk2.compile.cause__compiled_from__symbol, nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.compile__exception, f2exception__new(cause, __funk2.compile.compile__exception, nil));
  
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__funk__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__metro__symbol,                    nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__if__symbol,                       nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__rawcode__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__while__symbol,                    nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__while_exp__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__return__symbol,                   nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__return_exp__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__if_exp__symbol,                   nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__lookup_funkvar_exp__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__eval_args__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__eval_args__current_arg__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__define_funk_exp__symbol,          nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__define_exp__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__mutate_exp__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__mutatefunk_exp__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__globalize_var_exp__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__globalize_funkvar_exp__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__apply_exp__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__funkvar_call__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.raw__apply_metro__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.raw__apply_funk__symbol,                       nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__backquote_exp__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__backquote_append_exp__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__special_symbol_exp__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__compile__cons_exp__symbol,                 nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__demetropolize__special_symbol_exp__symbol, nil);
  //environment__add_var_value(cause, global_environment(), __f2__demetropolize__cons_exp__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__demetropolize__funkvar_call__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__demetropolize_once__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.f2__demetropolize_full__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.compile.raw__compile__symbol,                          nil);
  
  //f2__primcfunk__init__1(string__to_symbol, this, "convert any string to a new symbol.  for any two strings that are equal, the symbols returned by this function will be eq.");
  f2__primcfunk__init__1(wrong_argument_number__bcs__set, bytecodes, "sets the interrupt for responding to the wrong number of arguments to a funk.");
  
}

