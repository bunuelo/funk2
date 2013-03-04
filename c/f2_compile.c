// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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
  //return f2cause__new(cause, nil, nil, __cause__compiled_from__symbol, raw__cons__new(cause, name, args));
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

f2ptr f2__compile__funk_bc(f2ptr cause)                                               {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__funk__symbol,                nil,    nil,   nil), nil));}
f2ptr f2__compile__jump_funk(f2ptr cause)                                             {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__jump_funk__symbol,           nil,    nil,   nil), nil));}
f2ptr f2__compile__funk_env(f2ptr cause)                                              {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__funk_env__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__array(f2ptr cause, f2ptr length)                                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__array__symbol,               length, nil,   nil), nil));}
f2ptr f2__compile__cons(f2ptr cause)                                                  {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cons__symbol,                nil,    nil,   nil), nil));}
f2ptr f2__compile__consp(f2ptr cause)                                                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__consp__symbol,               nil,    nil,   nil), nil));}
f2ptr f2__compile__car(f2ptr cause)                                                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr(f2ptr cause)                                                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__car__set(f2ptr cause)                                              {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr__set(f2ptr cause)                                              {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__array_elt(f2ptr cause, f2ptr array, f2ptr index)                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__array_elt__symbol,           array,  index, nil), nil));}
f2ptr f2__compile__set(f2ptr cause, f2ptr reg, f2ptr exp)                             {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__set__symbol,                 reg,    exp,   nil), nil));}
f2ptr f2__compile__value__set(f2ptr cause, f2ptr exp)                                 {return bcs_valid(f2__compile__set(  cause, __fiber__value_reg__symbol, exp));}
f2ptr f2__compile__iter__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __fiber__iter_reg__symbol, exp));}
f2ptr f2__compile__args__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __fiber__args_reg__symbol, exp));}
f2ptr f2__compile__env__set(f2ptr cause, f2ptr exp)                                   {return bcs_valid(f2__compile__set(  cause, __fiber__env_reg__symbol, exp));}
f2ptr f2__compile__swap(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__swap__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__swap_value_and_iter(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__swap_value_and_args(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __fiber__value_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__push_constant(f2ptr cause, f2ptr constant)                         {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__push_constant__symbol, constant, nil, nil), nil));}
f2ptr f2__compile__push(f2ptr cause, f2ptr reg)                                       {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__push__symbol, reg, nil, nil),  nil));}
f2ptr f2__compile__push_value(f2ptr cause)                                            {return bcs_valid(f2__compile__push( cause, __fiber__value_reg__symbol));}
f2ptr f2__compile__push_iter(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __fiber__iter_reg__symbol));}
f2ptr f2__compile__push_args(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __fiber__args_reg__symbol));}
f2ptr f2__compile__push_env(f2ptr cause)                                              {return bcs_valid(f2__compile__push( cause, __fiber__env_reg__symbol));}
f2ptr f2__compile__push_return(f2ptr cause)                                           {return bcs_valid(f2__compile__push( cause, __fiber__return_reg__symbol));}
f2ptr f2__compile__pop(f2ptr cause, f2ptr reg)                                        {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__pop__symbol,  reg, nil, nil), nil));}
f2ptr f2__compile__pop_value(f2ptr cause)                                             {return bcs_valid(f2__compile__pop(  cause, __fiber__value_reg__symbol));}
f2ptr f2__compile__pop_iter(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __fiber__iter_reg__symbol));}
f2ptr f2__compile__pop_args(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __fiber__args_reg__symbol));}
f2ptr f2__compile__pop_env(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, __fiber__env_reg__symbol));}
f2ptr f2__compile__pop_return(f2ptr cause)                                            {return bcs_valid(f2__compile__pop(  cause, __fiber__return_reg__symbol));}
f2ptr f2__compile__pop_nil(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, nil));}
f2ptr f2__compile__copy(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__copy__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__copy_value_to_args(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__value_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__copy_value_to_iter(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__copy_iter_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__iter_reg__symbol, __fiber__value_reg__symbol));}
f2ptr f2__compile__copy_iter_to_args(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__iter_reg__symbol, __fiber__args_reg__symbol));}
f2ptr f2__compile__copy_args_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __fiber__args_reg__symbol, __fiber__value_reg__symbol));}
f2ptr f2__compile__copy_args_to_iter(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__args_reg__symbol, __fiber__iter_reg__symbol));}
f2ptr f2__compile__copy_pc_to_return(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__program_counter_reg__symbol, __fiber__return_reg__symbol));}
f2ptr f2__compile__copy_return_to_pc(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __fiber__return_reg__symbol, __fiber__program_counter_reg__symbol));}

f2ptr f2__compile__lookup(f2ptr cause, f2ptr type, f2ptr var)                         {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__lookup__symbol, type, var, nil), nil));}
f2ptr f2bytecode__lookup__type(f2ptr this, f2ptr cause)                               {return f2bytecode__arg0(this, cause);}
f2ptr f2bytecode__lookup__var(f2ptr this, f2ptr cause)                                {return f2bytecode__arg1(this, cause);}

f2ptr f2__compile__define(f2ptr cause, f2ptr type, f2ptr var)                         {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__define__symbol, type, var, nil), nil));}
f2ptr f2__compile__type_var__mutate(f2ptr cause, f2ptr type, f2ptr var)               {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__type_var__mutate__symbol, type, var, nil), nil));}
f2ptr f2__compile__globalize_type_var(f2ptr cause, f2ptr type, f2ptr var)             {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__globalize_type_var__symbol, type, var, nil), nil));}
f2ptr f2__compile__jump(f2ptr cause, f2ptr new_pc)                                    {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__if_jump(f2ptr cause, f2ptr new_pc)                                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__if_jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__else_jump(f2ptr cause, f2ptr new_pc)                               {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__else_jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__nop(f2ptr cause)                                                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__nop__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__return_bytecode(f2ptr cause)                                       {return bcs_valid(f2__compile__copy( cause, __fiber__return_reg__symbol, __fiber__program_counter_reg__symbol));}
f2ptr f2__compile__debug(f2ptr cause, f2ptr value)                                    {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__debug__symbol, value, nil, nil), nil));}
f2ptr f2__compile__tracer(f2ptr cause, f2ptr name, f2ptr args)                        {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__tracer__symbol, name, args, nil), nil));}
f2ptr f2__compile__endfunk(f2ptr cause, f2ptr funk)                                   {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__endfunk__symbol, funk, nil, nil), nil));}
f2ptr f2__compile__compile(f2ptr cause, f2ptr protect_environment)                    {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__compile__symbol, protect_environment, nil, nil), nil));}
f2ptr f2__compile__yield(f2ptr cause)                                                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__yield__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__newenv(f2ptr cause)                                                {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__newenv__symbol, nil, nil, nil), nil));}

f2ptr f2__compile__lookup_var(f2ptr cause, f2ptr var)         {return bcs_valid(f2__compile__lookup(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__lookup_funkvar(f2ptr cause, f2ptr funkvar) {return bcs_valid(f2__compile__lookup(cause, __funk2.primobject__frame.funk_variable__symbol, funkvar));}

f2ptr f2__compile__define_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__define(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__define_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__define(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

f2ptr f2__compile__var__mutate(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__type_var__mutate(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__funkvar__mutate(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__type_var__mutate(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

f2ptr f2__compile__globalize_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__globalize_type_var(cause, __funk2.primobject__frame.variable__symbol,      var));}
f2ptr f2__compile__globalize_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__globalize_type_var(cause, __funk2.primobject__frame.funk_variable__symbol, var));}

// logic
f2ptr f2__compile__eq (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__eq__symbol,  result, x0, x1),  nil));}
f2ptr f2__compile__not(f2ptr cause, f2ptr result, f2ptr x)            {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__not__symbol, result, x,  nil), nil));}
f2ptr f2__compile__and(f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__and__symbol, result, x0, x1),  nil));}
f2ptr f2__compile__or (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__or__symbol,  result, x0, x1),  nil));}

// math
f2ptr f2__compile__add               (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__add__symbol,                result, x0, x1),  nil));}
f2ptr f2__compile__negative          (f2ptr cause, f2ptr result, f2ptr x)            {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__negative__symbol,           result, x,  nil), nil));}
f2ptr f2__compile__subtract          (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__subtract__symbol,           result, x0, x1),  nil));}
f2ptr f2__compile__multiply          (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__multiply__symbol,           result, x0, x1),  nil));}
f2ptr f2__compile__inverse           (f2ptr cause, f2ptr result, f2ptr x)            {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__inverse__symbol,            result, x,  nil), nil));}
f2ptr f2__compile__divide            (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__divide__symbol,             result, x0, x1),  nil));}
f2ptr f2__compile__modulo            (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__modulo__symbol,             result, x0, x1),  nil));}
f2ptr f2__compile__increment         (f2ptr cause, f2ptr result, f2ptr x)            {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__increment__symbol,          result, x,  nil), nil));}
f2ptr f2__compile__decrement         (f2ptr cause, f2ptr result, f2ptr x)            {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__decrement__symbol,          result, x,  nil), nil));}
f2ptr f2__compile__numerically_equals(f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__numerically_equals__symbol, result, x0, x1),  nil));}
f2ptr f2__compile__less_than         (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__less_than__symbol,          result, x0, x1),  nil));}
f2ptr f2__compile__greater_than      (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__greater_than__symbol,       result, x0, x1),  nil));}

// block
f2ptr f2__compile__block_push                (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_push__symbol,                 nil,      nil, nil), nil));}
f2ptr f2__compile__block_enter               (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_enter__symbol,                nil,      nil, nil), nil));}
f2ptr f2__compile__block_define_rest_argument(f2ptr cause, f2ptr argument) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_rest_argument__symbol, argument, nil, nil), nil));}
f2ptr f2__compile__block_define_argument     (f2ptr cause, f2ptr argument) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_argument__symbol,      argument, nil, nil), nil));}
f2ptr f2__compile__block_define_last_argument(f2ptr cause, f2ptr argument) {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_define_last_argument__symbol, argument, nil, nil), nil));}
f2ptr f2__compile__block_pop                 (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_pop__symbol,                  nil,      nil, nil), nil));}
f2ptr f2__compile__block_exit_and_pop        (f2ptr cause, f2ptr funk)     {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_exit_and_pop__symbol,         funk,     nil, nil), nil));}
f2ptr f2__compile__block_exit_and_no_pop     (f2ptr cause, f2ptr funk)     {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol,      funk,     nil, nil), nil));}
f2ptr f2__compile__block_eval_args_begin     (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_begin__symbol,      nil,      nil, nil), nil));}
f2ptr f2__compile__block_eval_args_next      (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_next__symbol,       nil,      nil, nil), nil));}
f2ptr f2__compile__block_eval_args_end       (f2ptr cause)                 {return bcs_valid(raw__cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__block_eval_args_end__symbol,        nil,      nil, nil), nil));}


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

f2ptr raw__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value);

//f2ptr __wrong_argument_number__bcs = nil; // this is like an interrupt pointer... (nil causes fiber to fail silently [this is a bug])

f2ptr f2__wrong_argument_number__bcs__set(f2ptr cause, f2ptr bytecodes) {
  environment__add_var_value(cause, global_environment(), new__symbol(cause, "--wrong_argument_number-bcs--"), bytecodes);
  __funk2.compile.wrong_argument_number__bcs = bytecodes;
  return nil;
}
def_pcfunk1(wrong_argument_number__bcs__set, bytecodes,
	    "Sets the interrupt for responding to the wrong number of arguments to a funk.",
	    return f2__wrong_argument_number__bcs__set(this_cause, bytecodes));


f2ptr f2__compile__push_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                      f2__compile__push_args( cause); f2ptr iter = full_bcs;
  iter = raw__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  iter = raw__list_cdr__set(cause, iter, f2__compile__push_constant(cause, __funk2.compile.debug_funk_call__symbol));
  return full_bcs;
}

f2ptr f2__compile__pop_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                       f2__compile__pop_nil(cause); f2ptr iter = full_bcs;
  iter = raw__list_cdr__set(cause, iter, f2__compile__pop_nil(cause));
  iter = raw__list_cdr__set(cause, iter, f2__compile__pop_nil(cause));
  return full_bcs;
}

boolean_t raw__expression__is_funktional(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(  cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (! raw__eq(cause, command, __funk2.globalenv.quote__symbol)) {
      return boolean__false;
    }
  } else if (raw__symbol__is_type(cause, expression)) {
    return boolean__false;
  }
  return boolean__true;
}

f2ptr raw__expression__optimize__if(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr condition = f2cons__car(cdr, cause);
    if (raw__expression__is_funktional(cause, condition)) {
      if (condition != nil) {
	f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
	if (raw__cons__is_type(cause, cdr__cdr)) {
	  f2ptr true_expression = f2cons__car(cdr__cdr, cause);
	  return true_expression;
	}
      } else {
	f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
	if (raw__cons__is_type(cause, cdr__cdr)) {
	  f2ptr false_expressions = f2cons__cdr(cdr__cdr, cause);
	  if (false_expressions == nil) {
	    return nil;
	  } else if (raw__cons__is_type(cause, false_expressions)) {
	    f2ptr false_expressions__cdr = f2cons__cdr(false_expressions, cause);
	    if (false_expressions__cdr == nil) {
	      f2ptr false_expression = f2cons__car(false_expressions, cause);
	      return false_expression;
	    }
	  }
	  return f2cons__new(cause, __funk2.globalenv.rawcode__symbol, false_expressions);
	}
      }
    } else {
      f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
      if (raw__cons__is_type(cause, cdr__cdr)) {
	boolean_t expression_changed    = boolean__false;
	f2ptr     true_expression       = f2cons__car(cdr__cdr, cause);
	f2ptr     false_expressions     = f2cons__cdr(cdr__cdr, cause);
	f2ptr     new_true_expression   = assert_value(raw__expression__optimize(cause, true_expression));
	if (true_expression != new_true_expression) {
	  expression_changed = boolean__true;
	}
	f2ptr new_false_expressions = nil;
	{
	  f2ptr false_expressions_iter     = false_expressions;
	  f2ptr new_false_expressions_iter = nil;
	  while (false_expressions_iter != nil) {
	    f2ptr false_expression = f2cons__car(false_expressions_iter, cause);
	    {
	      f2ptr new_false_expression = assert_value(raw__expression__optimize(cause, false_expression));
	      if (false_expression != new_false_expression) {
		expression_changed = boolean__true;
	      }
	      f2ptr new_cons = f2cons__new(cause, new_false_expression, nil);
	      if (new_false_expressions == nil) {
		new_false_expressions = new_cons;
	      } else {
		f2cons__cdr__set(new_false_expressions_iter, cause, new_cons);
	      }
	      new_false_expressions_iter = new_cons;
	    }
	    false_expressions_iter = f2cons__cdr(false_expressions_iter, cause);
	  }
	}
	if (expression_changed) {
	  return f2cons__new(cause, __funk2.globalenv.if__symbol, f2cons__new(cause, condition, f2cons__new(cause, new_true_expression, new_false_expressions)));
	}
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__while(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    boolean_t changed_expression = boolean__false;
    f2ptr     condition          = f2cons__car(cdr, cause);
    f2ptr     new_condition      = assert_value(raw__expression__optimize(cause, condition));
    if (new_condition == nil) {
      return nil;
    }
    if (condition != new_condition) {
      changed_expression = boolean__true;
    }
    f2ptr rest     = f2cons__cdr(cdr, cause);
    f2ptr new_rest = nil;
    {
      f2ptr rest_iter     = rest;
      f2ptr new_rest_iter = nil;
      while (rest_iter != nil) {
	f2ptr subexpression  = f2cons__car(rest_iter, cause);
	f2ptr rest_iter__cdr = f2cons__cdr(rest_iter, cause);
	{
	  f2ptr new_subexpression = assert_value(raw__expression__optimize(cause, subexpression));
	  if (subexpression != new_subexpression) {
	    changed_expression = boolean__true;
	  }
	  if (raw__expression__is_funktional(cause, new_subexpression)) {
	    changed_expression = boolean__true;
	  } else {
	    f2ptr new_cons = f2cons__new(cause, new_subexpression, nil);
	    if (new_rest == nil) {
	      new_rest = new_cons;
	    } else {
	      f2cons__cdr__set(new_rest_iter, cause, new_cons);
	    }
	    new_rest_iter = new_cons;
	  }
	}
	rest_iter = rest_iter__cdr;
      }
    }
    if (changed_expression) {
      return f2cons__new(cause, __funk2.globalenv.while__symbol, f2cons__new(cause, new_condition, new_rest));
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__apply(f2ptr cause, f2ptr expression) {
  if (raw__cons__is_type(cause, expression)) {
    f2ptr expression__cdr = f2cons__cdr(expression, cause);
    if (raw__cons__is_type(cause, expression__cdr)) {
      f2ptr funkable = f2cons__car(expression__cdr, cause);
      f2ptr expression__cddr = f2cons__cdr(expression__cdr, cause);
      if (raw__cons__is_type(cause, expression__cddr)) {
	f2ptr arguments = f2cons__car(expression__cddr, cause);
	{
	  if (raw__cons__is_type(cause, funkable)) {
	    f2ptr command = f2cons__car(funkable, cause);
	    if (raw__eq(cause, command, new__symbol(cause, "funk-new_copy_in_this_environment"))) {
	      f2ptr cdr = f2cons__cdr(funkable, cause);
	      if (raw__cons__is_type(cause, cdr)) {
		f2ptr compiled_funk = f2cons__car(cdr, cause);
		f2ptr compiled_funk__args = assert_value(f2__funk__args(cause, compiled_funk));
		if (compiled_funk__args == nil) {
		  f2ptr     compiled_funk__demetropolized_body = f2__funk__demetropolized_body(cause, compiled_funk);
		  boolean_t can_be_condensed                   = boolean__false;
		  {
		    f2ptr iter = compiled_funk__demetropolized_body;
		    while ((iter != nil) &&
			   (! can_be_condensed)) {
		      f2ptr car = f2cons__car(iter, cause);
		      f2ptr cdr = f2cons__cdr(iter, cause);
		      if ((cdr == nil) ||
			  (! raw__expression__is_funktional(cause, car))) {
			// do nothing.
		      } else {
			can_be_condensed = boolean__true;
		      }
		      iter = cdr;
		    }
		  }
		  if (can_be_condensed) {
		    f2ptr condensed_body_expressions = nil;
		    {
		      f2ptr iter           = compiled_funk__demetropolized_body;
		      f2ptr condensed_iter = nil;
		      while (iter != nil) {
			f2ptr car = f2cons__car(iter, cause);
			f2ptr cdr = f2cons__cdr(iter, cause);
			if ((cdr == nil) ||
			    (! raw__expression__is_funktional(cause, car))) {
			  f2ptr new_cons = f2cons__new(cause, car, nil);
			  if (condensed_iter == nil) {
			    condensed_body_expressions = new_cons;
			  } else {
			    f2cons__cdr__set(condensed_iter, cause, new_cons);
			  }
			  condensed_iter = new_cons;
			}
			iter = cdr;
		      }
		    }
		    if (condensed_body_expressions == nil) {
		      return nil;
		    } else if (f2cons__cdr(condensed_body_expressions, cause) == nil) {
		      return f2cons__car(condensed_body_expressions, cause);
		    }
		  }
		} else {
		  boolean_t variables_contain_rest = boolean__false;
		  {
		    f2ptr iter = compiled_funk__args;
		    while (iter != nil) {
		      f2ptr variable = f2cons__car(iter, cause);
		      if (raw__eq(cause, variable, new__symbol(cause, ":rest"))) {
			variables_contain_rest = boolean__true;
		      }
		      iter = f2cons__cdr(iter, cause);
		    }
		  }
		  if (! variables_contain_rest) {
		    if (raw__cons__is_type(cause, arguments)) {
		      f2ptr arguments_command = f2cons__car(arguments, cause);
		      if (raw__eq(cause, arguments_command, new__symbol(cause, "conslist"))) {
			f2ptr     reduced_compiled_funk    = compiled_funk;
			f2ptr     arguments_iter           = f2cons__cdr(arguments, cause);
			f2ptr     variables_iter           = compiled_funk__args;
			f2ptr     remaining_arguments      = nil;
			f2ptr     remaining_arguments_iter = nil;
			boolean_t funk_was_reduced         = boolean__false;
			while ((arguments_iter != nil) &&
			       (variables_iter != nil)) {
			  f2ptr     argument             = f2cons__car(arguments_iter, cause);
			  f2ptr     variable             = f2cons__car(variables_iter, cause);
			  boolean_t variable_was_removed = boolean__false;
			  if (raw__expression__is_funktional(cause, argument)) {
			    f2ptr result = raw__funk__new_with_replaced_variable(cause, reduced_compiled_funk, variable, argument);
			    if (! raw__larva__is_type(cause, result)) {
			      variable_was_removed  = boolean__true;
			      funk_was_reduced      = boolean__true;
			      reduced_compiled_funk = result;
			    }
			  }
			  if (! variable_was_removed) {
			    f2ptr new_arguments_cons = f2cons__new(cause, argument, nil);
			    if (remaining_arguments == nil) {
			      remaining_arguments = new_arguments_cons;
			    } else {
			      f2cons__cdr__set(remaining_arguments_iter, cause, new_arguments_cons);
			    }
			    remaining_arguments_iter = new_arguments_cons;
			  }
			  arguments_iter = f2cons__cdr(arguments_iter, cause);
			  variables_iter = f2cons__cdr(variables_iter, cause);
			}
			if (funk_was_reduced) {
			  f2ptr remaining_arguments_expression = (remaining_arguments == nil) ? nil : f2cons__new(cause, new__symbol(cause, "conslist"), remaining_arguments);
			  return f2list3__new(cause, __funk2.globalenv.local_apply__symbol, f2list2__new(cause, new__symbol(cause, "funk-new_copy_in_this_environment"), reduced_compiled_funk), remaining_arguments_expression);
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__local_apply(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr funkable = f2cons__car(cdr, cause);
    if (raw__cons__is_type(cause, funkable)) {
      f2ptr funkable__command = f2cons__car(funkable, cause);
      if (raw__eq(cause, funkable__command, new__symbol(cause, "funk-new_copy_in_this_environment"))) {
	f2ptr funkable__cdr = f2cons__cdr(funkable, cause);
	if (raw__cons__is_type(cause, funkable__cdr)) {
	  f2ptr funkable__funkable = f2cons__car(funkable__cdr, cause);
	  f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
	  if (raw__cons__is_type(cause, cdr__cdr)) {
	    f2ptr arguments = f2cons__car(cdr__cdr, cause);
	    return f2list3__new(cause, __funk2.globalenv.local_apply__symbol, funkable__funkable, arguments);
	  }
	}
      }
    } else if (raw__funk__is_type(cause, funkable)) {
      f2ptr funkable__args = f2funk__args(funkable, cause);
      if (funkable__args == nil) {
	f2ptr funkable__demetropolized_body = f2funk__demetropolized_body(funkable, cause);
	if (funkable__demetropolized_body == nil) {
	  return nil;
	} else if (raw__cons__is_type(cause, funkable__demetropolized_body)) {
	  f2ptr funkable__demetropolized_body__cdr = f2cons__cdr(funkable__demetropolized_body, cause);
	  if (funkable__demetropolized_body__cdr == nil) {
	    f2ptr funkable__demetropolized_body__car = f2cons__car(funkable__demetropolized_body, cause);
	    return funkable__demetropolized_body__car;
	  }
	}
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__rawcode(f2ptr cause, f2ptr expression) {
  f2ptr     rawcodes           = f2cons__cdr(expression, cause);
  f2ptr     new_rawcodes       = nil;
  boolean_t changed_expression = boolean__false;
  {
    f2ptr rawcodes_iter     = rawcodes;
    f2ptr new_rawcodes_iter = nil;
    while (rawcodes_iter != nil) {
      f2ptr rawcode            = f2cons__car(rawcodes_iter, cause);
      f2ptr rawcodes_iter__cdr = f2cons__cdr(rawcodes_iter, cause);
      {
	f2ptr new_rawcode = assert_value(raw__expression__optimize(cause, rawcode));
	if (rawcode != new_rawcode) {
	  changed_expression = boolean__true;
	}
	if ((rawcodes_iter__cdr != nil) &&
	    raw__expression__is_funktional(cause, new_rawcode)) {
	  changed_expression = boolean__true;
	} else {
	  f2ptr new_cons = f2cons__new(cause, new_rawcode, nil);
	  if (new_rawcodes == nil) {
	    new_rawcodes = new_cons;
	  } else {
	    f2cons__cdr__set(new_rawcodes_iter, cause, new_cons);
	  }
	  new_rawcodes_iter = new_cons;
	}
      }
      rawcodes_iter = rawcodes_iter__cdr;
    }
    if (changed_expression) {
      if (new_rawcodes == nil) {
	return nil;
      }
      f2ptr new_rawcodes__cdr = f2cons__cdr(new_rawcodes, cause);
      if (new_rawcodes__cdr == nil) {
	f2ptr new_rawcodes__car = f2cons__car(new_rawcodes, cause);
	return new_rawcodes__car;
      }
      return f2cons__new(cause, __funk2.globalenv.rawcode__symbol, new_rawcodes);
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__bytecode_add(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr arg1     = f2cons__car(cdr, cause);
    f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
    if (raw__cons__is_type(cause, cdr__cdr)) {
      f2ptr arg2 = f2cons__car(cdr__cdr, cause);
      if (raw__integer__is_type(     cause, arg1) ||
	  raw__double__is_type(      cause, arg1) ||
	  raw__float__is_type(       cause, arg1) ||
	  raw__largeinteger__is_type(cause, arg1)) {
	if (raw__integer__is_type(     cause, arg2) ||
	    raw__double__is_type(      cause, arg2) ||
	    raw__float__is_type(       cause, arg2) ||
	    raw__largeinteger__is_type(cause, arg2)) {
	  return f2__number__plus(cause, arg1, arg2);
	}
      }
      f2ptr arg1_optimized = raw__expression__optimize(cause, arg1);
      f2ptr arg2_optimized = raw__expression__optimize(cause, arg2);
      if ((arg1 != arg1_optimized) ||
	  (arg2 != arg2_optimized)) {
	return f2list3__new(cause, __funk2.globalenv.bytecode_add__symbol, arg1_optimized, arg2_optimized);
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__bytecode_subtract(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr arg1     = f2cons__car(cdr, cause);
    f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
    if (raw__cons__is_type(cause, cdr__cdr)) {
      f2ptr arg2 = f2cons__car(cdr__cdr, cause);
      if (raw__integer__is_type(     cause, arg1) ||
	  raw__double__is_type(      cause, arg1) ||
	  raw__float__is_type(       cause, arg1) ||
	  raw__largeinteger__is_type(cause, arg1)) {
	if (raw__integer__is_type(     cause, arg2) ||
	    raw__double__is_type(      cause, arg2) ||
	    raw__float__is_type(       cause, arg2) ||
	    raw__largeinteger__is_type(cause, arg2)) {
	  return f2__number__minus(cause, arg1, arg2);
	}
      }
      f2ptr arg1_optimized = raw__expression__optimize(cause, arg1);
      f2ptr arg2_optimized = raw__expression__optimize(cause, arg2);
      if ((arg1 != arg1_optimized) ||
	  (arg2 != arg2_optimized)) {
	return f2list3__new(cause, __funk2.globalenv.bytecode_subtract__symbol, arg1_optimized, arg2_optimized);
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__bytecode_multiply(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr arg1     = f2cons__car(cdr, cause);
    f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
    if (raw__cons__is_type(cause, cdr__cdr)) {
      f2ptr arg2 = f2cons__car(cdr__cdr, cause);
      if (raw__integer__is_type(     cause, arg1) ||
	  raw__double__is_type(      cause, arg1) ||
	  raw__float__is_type(       cause, arg1) ||
	  raw__largeinteger__is_type(cause, arg1)) {
	if (raw__integer__is_type(     cause, arg2) ||
	    raw__double__is_type(      cause, arg2) ||
	    raw__float__is_type(       cause, arg2) ||
	    raw__largeinteger__is_type(cause, arg2)) {
	  return f2__number__multiplied_by(cause, arg1, arg2);
	}
      }
      f2ptr arg1_optimized = raw__expression__optimize(cause, arg1);
      f2ptr arg2_optimized = raw__expression__optimize(cause, arg2);
      if ((arg1 != arg1_optimized) ||
	  (arg2 != arg2_optimized)) {
	return f2list3__new(cause, __funk2.globalenv.bytecode_multiply__symbol, arg1_optimized, arg2_optimized);
      }
    }
  }
  return expression;
}

f2ptr raw__expression__optimize__bytecode_divide(f2ptr cause, f2ptr expression) {
  f2ptr cdr = f2cons__cdr(expression, cause);
  if (raw__cons__is_type(cause, cdr)) {
    f2ptr arg1     = f2cons__car(cdr, cause);
    f2ptr cdr__cdr = f2cons__cdr(cdr, cause);
    if (raw__cons__is_type(cause, cdr__cdr)) {
      f2ptr arg2 = f2cons__car(cdr__cdr, cause);
      if (raw__integer__is_type(     cause, arg1) ||
	  raw__double__is_type(      cause, arg1) ||
	  raw__float__is_type(       cause, arg1) ||
	  raw__largeinteger__is_type(cause, arg1)) {
	if (raw__integer__is_type(     cause, arg2) ||
	    raw__double__is_type(      cause, arg2) ||
	    raw__float__is_type(       cause, arg2) ||
	    raw__largeinteger__is_type(cause, arg2)) {
	  return f2__number__divided_by(cause, arg1, arg2);
	}
      }
      f2ptr arg1_optimized = raw__expression__optimize(cause, arg1);
      f2ptr arg2_optimized = raw__expression__optimize(cause, arg2);
      if ((arg1 != arg1_optimized) ||
	  (arg2 != arg2_optimized)) {
	return f2list3__new(cause, __funk2.globalenv.bytecode_divide__symbol, arg1_optimized, arg2_optimized);
      }
    }
  }
  return expression;
}

boolean_t raw__is_compile_special_symbol(f2ptr cause, f2ptr exp) {
  return ((raw__symbol__eq(cause, exp, __funk2.globalenv.quote__symbol))                       ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.backquote__list__symbol))             ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.backquote__list_append__symbol))      ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.if__symbol))                          ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.while__symbol))                       ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.return__symbol))                      ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.apply__symbol))                       ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.local_apply__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.funkvar__symbol))                     ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.define_funk__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.define__symbol))                      ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.mutatefunk__symbol))                  ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.mutate__symbol))                      ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.globalize__symbol))                   ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.globalize_funk__symbol))              ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.yield__symbol))                       ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode__symbol))                    ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.rawcode__symbol))                     ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_eq__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_not__symbol))                ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_and__symbol))                ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_or__symbol))                 ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_add__symbol))                ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_negative__symbol))           ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_subtract__symbol))           ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_multiply__symbol))           ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_inverse__symbol))            ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_divide__symbol))             ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_modulo__symbol))             ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_increment__symbol))          ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_decrement__symbol))          ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_numerically_equals__symbol)) ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_less_than__symbol))          ||
	  (raw__symbol__eq(cause, exp, __funk2.globalenv.bytecode_greater_than__symbol)));
}

f2ptr raw__expression__optimize__funkvar_call(f2ptr cause, f2ptr expression) {
  f2ptr     command            = f2cons__car(expression, cause);
  boolean_t expression_changed = boolean__false;
  f2ptr     rest               = f2cons__cdr(expression, cause);
  f2ptr     new_rest           = nil;
  {
    f2ptr new_rest_iter = nil;
    f2ptr rest_iter     = rest;
    while (rest_iter != nil) {
      f2ptr subexpression = f2cons__car(rest_iter, cause);
      {
	f2ptr new_subexpression = raw__expression__optimize(cause, subexpression);
	if (subexpression != new_subexpression) {
	  expression_changed = boolean__true;
	}
	f2ptr new_cons = f2cons__new(cause, new_subexpression, nil);
	if (new_rest == nil) {
	  new_rest = new_cons;
	} else {
	  f2cons__cdr__set(new_rest_iter, cause, new_cons);
	}
	new_rest_iter = new_cons;
      }
      rest_iter = f2cons__cdr(rest_iter, cause);
    }
  }
  if (expression_changed) {
    return f2cons__new(cause, command, new_rest);
  }
  return expression;
}

f2ptr raw__expression__optimize__special_expression(f2ptr cause, f2ptr expression) {
  f2ptr command = f2cons__car(expression, cause);
  if (raw__symbol__eq(cause, command, __funk2.globalenv.quote__symbol))                       {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.backquote__list__symbol))             {return raw__expression__optimize__funkvar_call(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.backquote__list_append__symbol))      {return raw__expression__optimize__funkvar_call(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.if__symbol))                          {return raw__expression__optimize__if(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.while__symbol))                       {return raw__expression__optimize__while(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.return__symbol))                      {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.apply__symbol))                       {return raw__expression__optimize__apply(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.local_apply__symbol))                 {return raw__expression__optimize__local_apply(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.funkvar__symbol))                     {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.define_funk__symbol))                 {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.define__symbol))                      {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.mutatefunk__symbol))                  {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.mutate__symbol))                      {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.globalize__symbol))                   {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.globalize_funk__symbol))              {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.yield__symbol))                       {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode__symbol))                    {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.rawcode__symbol))                     {return raw__expression__optimize__rawcode(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_eq__symbol))                 {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_not__symbol))                {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_and__symbol))                {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_or__symbol))                 {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_add__symbol))                {return raw__expression__optimize__bytecode_add(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_negative__symbol))           {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_subtract__symbol))           {return raw__expression__optimize__bytecode_subtract(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_multiply__symbol))           {return raw__expression__optimize__bytecode_multiply(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_inverse__symbol))            {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_divide__symbol))             {return raw__expression__optimize__bytecode_divide(cause, expression);}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_modulo__symbol))             {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_increment__symbol))          {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_decrement__symbol))          {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_numerically_equals__symbol)) {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_less_than__symbol))          {return expression;}
  if (raw__symbol__eq(cause, command, __funk2.globalenv.bytecode_greater_than__symbol))       {return expression;}
  status("tried to optimize special symbol exp: "); f2__write(cause, f2__this__fiber(cause), expression); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  status("raw__expression__optimize__special_expression error: expression is not special symbol expression.");
  return f2larva__new(cause, 126, nil);
}

f2ptr raw__expression__optimize(f2ptr cause, f2ptr expression) {
  f2ptr result = expression;
  if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (raw__is_compile_special_symbol(cause, command)) {
      result = raw__expression__optimize__special_expression(cause, expression);
    } else {
      result = raw__expression__optimize__funkvar_call(cause, expression);
    }
  }
  if (result != expression) {
    result = raw__expression__optimize(cause, result);
  }
  return result;
}

f2ptr f2__expression__optimize(f2ptr cause, f2ptr expression) {
  return raw__expression__optimize(cause, expression);
}
def_pcfunk1(expression__optimize, expression,
	    "Returns an optimized version of a demetropolized expression.",
	    return f2__expression__optimize(this_cause, expression));


f2ptr raw__funk__flatten_local_applies(f2ptr cause, f2ptr this) {
  f2ptr     demetropolized_body = assert_value(f2funk__demetropolized_body(this, cause));
  boolean_t can_optimize        = boolean__false;
  {
    f2ptr iter = demetropolized_body;
    while ((iter != nil) &&
	   (! can_optimize)) {
      f2ptr expression = f2cons__car(iter, cause);
      {
	if (raw__cons__is_type(cause, expression)) {
	  f2ptr command = f2cons__car(expression, cause);
	  if (raw__eq(cause, command, __funk2.globalenv.local_apply__symbol)) {
	    f2ptr cdr = f2cons__cdr(expression, cause);
	    if (raw__cons__is_type(cause, cdr)) {
	      f2ptr funkable = f2cons__car(cdr, cause);
	      if (raw__funk__is_type(cause, funkable)) {
		f2ptr funkable__args = f2funk__args(funkable, cause);
		if (funkable__args == nil) {
		  can_optimize = boolean__true;
		}
	      }
	    }
	  }
	}
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  if (can_optimize) {
    f2ptr new_demetropolized_body = nil;
    {
      f2ptr new_demetropolized_body_iter = nil;
      f2ptr iter                         = demetropolized_body;
      while (iter != nil) {
	f2ptr expression = f2cons__car(iter, cause);
	{
	  boolean_t expression_rewritten = boolean__false;
	  if (raw__cons__is_type(cause, expression)) {
	    f2ptr command = f2cons__car(expression, cause);
	    if (raw__eq(cause, command, __funk2.globalenv.local_apply__symbol)) {
	      f2ptr cdr = f2cons__cdr(expression, cause);
	      if (raw__cons__is_type(cause, cdr)) {
		f2ptr funkable = f2cons__car(cdr, cause);
		if (raw__funk__is_type(cause, funkable)) {
		  f2ptr funkable__args = f2funk__args(funkable, cause);
		  if (funkable__args == nil) {
		    expression_rewritten                = boolean__true;
		    f2ptr funkable__demetropolized_body = assert_value(f2funk__demetropolized_body(funkable, cause));
		    f2ptr funkable__iter                = funkable__demetropolized_body;
		    while (funkable__iter != nil) {
		      f2ptr funkable__expression = f2cons__car(funkable__iter, cause);
		      {
			f2ptr new_cons = f2cons__new(cause, funkable__expression, nil);
			if (new_demetropolized_body == nil) {
			  new_demetropolized_body = new_cons;
			} else {
			  f2cons__cdr__set(new_demetropolized_body_iter, cause, new_cons);
			}
			new_demetropolized_body_iter = new_cons;
		      }		
		      funkable__iter = f2cons__cdr(funkable__iter, cause);
		    }
		  }
		}
	      }
	    }
	  }
	  if (! expression_rewritten) {
	    f2ptr new_cons = f2cons__new(cause, expression, nil);
	    if (new_demetropolized_body == nil) {
	      new_demetropolized_body = new_cons;
	    } else {
	      f2cons__cdr__set(new_demetropolized_body_iter, cause, new_cons);
	    }
	    new_demetropolized_body_iter = new_cons;
	  }
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
    f2funk__demetropolized_body__set(this, cause, new_demetropolized_body);
  }
  return this;
}

f2ptr f2__compile__funk(f2ptr simple_cause, f2ptr fiber, f2ptr original_funk) {
  release__assert(__funk2.compile.f2__compile__funk__symbol != -1, nil, "__funk2.compile.f2__compile__funk__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__funk__symbol, raw__cons__new(simple_cause, original_funk, nil));
  assert_argument_type(fiber, fiber);
  assert_argument_type(funk,  original_funk);
  
  {
    f2ptr funk__demetropolized_body = f2funk__demetropolized_body(original_funk, cause);
    f2ptr new_demetropolized_body   = nil;
    {
      f2ptr new_demetropolized_body_iter = nil;
      f2ptr iter                         = funk__demetropolized_body;
      while (iter != nil) {
	f2ptr expression = f2cons__car(iter, cause);
	{
	  f2ptr new_expression = assert_value(raw__expression__optimize(cause, expression));
	  f2ptr new_cons       = f2cons__new(cause, new_expression, nil);
	  if (new_demetropolized_body == nil) {
	    new_demetropolized_body = new_cons;
	  } else {
	    f2cons__cdr__set(new_demetropolized_body_iter, cause, new_cons);
	  }
	  new_demetropolized_body_iter = new_cons;
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
    f2funk__demetropolized_body__set(original_funk, cause, new_demetropolized_body);
  }
  
  f2ptr funk = assert_value(raw__funk__flatten_local_applies(cause, original_funk));
  
  f2ptr funk_bcs = f2__compile__value__set(cause, funk);
  if (f2funk__body_bytecodes(funk, cause)) {
    return bcs_valid(funk_bcs);
  }
  
  boolean_t funk__is_funktional         = boolean__true;
  f2ptr     local_variables             = f2funk__args(funk, cause);
  boolean_t funk__is_locally_funktional = boolean__true;
  
  f2ptr full_bcs = f2__compile__block_enter(cause); f2ptr iter = full_bcs;
  
  // define args in funk environment
  f2ptr var_iter = f2funk__args(funk, cause);
  if (var_iter != nil) {
    iter = raw__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
    while (var_iter != nil) {
      f2ptr var = f2cons__car(var_iter, cause);
      f2ptr cdr = f2cons__cdr(var_iter, cause);
      if (raw__symbol__eq(cause, var, __funk2.globalenv.and_rest__symbol)) {
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_rest_argument(cause, f2cons__car(cdr, cause)));
	var_iter = nil;
      } else {
	if (cdr) {
	  iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_argument(cause, var));
	} else {
	  iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_last_argument(cause, var));
	}
	var_iter = cdr;
      }
    }
  }
  
  boolean_t popped_env_and_return     = boolean__false;
  boolean_t optimize_unused_beginning = boolean__true;
  

  f2ptr demetropolized_body = assert_value(f2funk__demetropolized_body(funk, cause));
  
  f2ptr body_bcs = assert_value(f2__compile__rawcode(cause, fiber, demetropolized_body, boolean__false, boolean__true, &popped_env_and_return, &funk__is_funktional, local_variables, &funk__is_locally_funktional, optimize_unused_beginning));
  
  if (body_bcs && (! raw__cons__is_type(cause, body_bcs))) {return body_bcs;}
  
  iter = raw__list_cdr__set(cause, iter, body_bcs);
  
  if (! popped_env_and_return) {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_exit_and_pop(cause, funk));
  } else {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_exit_and_no_pop(cause, funk));
  }
  
  {
    f2ptr optimize_chunk = raw__optimize_chunk__new_from_bytecodes(cause, full_bcs);
    full_bcs = raw__optimize_chunk__as__bytecodes(cause, optimize_chunk);
    /*
    f2funk__body_bytecodes__set(funk, cause, full_bcs);
    f2ptr optimized_bytecodes = raw__optimize_chunk__possible_optimized_funk_bytecodes(cause, optimize_chunk, funk);
    if (raw__larva__is_type(cause, optimized_bytecodes)) {
      return optimized_bytecodes;
    }
    if (optimized_bytecodes != nil) {
      full_bcs = optimized_bytecodes;
    }
    */
  }
  full_bcs = raw__bytecodes__remove_nops(cause, full_bcs);
  
  //f2funk__is_funktional__set(funk, cause, f2bool__new(funk__is_locally_funktional));
  f2funk__body_bytecodes__set(funk, cause, full_bcs);
  
  return bcs_valid(funk_bcs);
}

f2ptr f2__compile__metro(f2ptr simple_cause, f2ptr fiber, f2ptr metro) {
  release__assert(__funk2.compile.f2__compile__metro__symbol != -1, nil, "__funk2.compile.f2__compile__metro__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__metro__symbol, raw__cons__new(simple_cause, metro, nil));
  assert_argument_type(fiber, fiber);
  assert_argument_type(metro, metro);
  
  
  f2ptr metro_bcs = f2__compile__value__set(cause, metro);
  if (raw__metro__body_bytecodes(cause, metro)) {
    return bcs_valid(metro_bcs);
  }
  
  boolean_t  metro__is_funktional         = boolean__true;
  f2ptr      local_variables              = raw__metro__args(cause, metro);
  boolean_t  metro__is_locally_funktional = boolean__true;
  
  f2ptr full_bcs = f2__compile__block_enter(cause); f2ptr iter = full_bcs;
  
  // define args in metro environment
  iter = raw__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
  f2ptr var_iter = raw__metro__args(cause, metro);
  while (var_iter) {
    
    f2ptr var = f2cons__car(var_iter, cause);
    f2ptr cdr = f2cons__cdr(var_iter, cause);
    if (raw__symbol__eq(cause, var, __funk2.globalenv.and_rest__symbol)) {
      iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_rest_argument(cause, f2cons__car(cdr, cause)));
      var_iter = nil;
    } else {
      if (cdr) {
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_argument(cause, var));
      } else {
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_define_last_argument(cause, var));
      }
      var_iter = cdr;
    }
  }
  
  boolean_t popped_env_and_return     = boolean__false;
  boolean_t optimize_unused_beginning = boolean__true;
  f2ptr body_bcs = f2__compile__rawcode(cause, fiber, raw__metro__demetropolized_body(cause, metro), boolean__false, boolean__true, &popped_env_and_return, &metro__is_funktional, local_variables, &metro__is_locally_funktional, optimize_unused_beginning);
  if (body_bcs && (! raw__cons__is_type(cause, body_bcs))) {return body_bcs;}
  iter = raw__list_cdr__set(cause, iter, body_bcs);
  
  if (! popped_env_and_return) {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_exit_and_pop(cause, metro));
  } else {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_exit_and_no_pop(cause, metro));
  }
  
  raw__metro__is_funktional__set(cause, metro, metro__is_locally_funktional ? __funk2.globalenv.true__symbol : nil);
  raw__metro__body_bytecodes__set(cause, metro, full_bcs);
  
  //raw__metro__machine_code__set(cause, metro, f2chunk__new_compiled_from_metro(cause, metro));
  return bcs_valid(metro_bcs);
}

// returns last cdr of initial list
f2ptr raw__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value) {
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
  iter = raw__list_cdr__set(cause, iter, f2__compile__else_jump(cause, false_bcs));
  iter = raw__list_cdr__set(cause, iter, true_bcs);
  iter = raw__list_cdr__set(cause, iter, true_done_jump_end_bcs);
  iter = raw__list_cdr__set(cause, iter, false_bcs);
  iter = raw__list_cdr__set(cause, iter, end_nop_bcs);
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
  
  f2ptr     full_bcs           = nil;
  boolean_t exp__is_funktional = boolean__true;
  f2ptr     next               = nil;
  do {
    f2ptr exp = f2cons__car(exps, cause);
    next      = f2cons__cdr(exps, cause);
    full_bcs = assert_value(raw__compile(cause, fiber, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional));
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
  if (full_bcs && (! raw__cons__is_type(cause, full_bcs))) {
    return full_bcs;
  }
  exps = f2cons__cdr(exps, cause);
  
  f2ptr iter = full_bcs;
  while (exps) {
    if (! raw__cons__is_type(cause, exps)) {
      return f2__argument_type_check_failure__larva__new(simple_cause, exps);
      //error(nil, "f2__compile__rawcode error: exps is not of type cons.");
    }
    protect_subexp_environment     = (f2cons__cdr(exps, cause) != nil) || protect_environment;
    optimize_subexp_tail_recursion = (f2cons__cdr(exps, cause) == nil) && optimize_tail_recursion;
    
    f2ptr     exp_bcs            = nil;
    boolean_t exp__is_funktional = boolean__true;
    f2ptr     next               = nil;
    do {
      f2ptr exp = f2cons__car(exps, cause);
      next      = f2cons__cdr(exps, cause);
      exp_bcs = assert_value(raw__compile(cause, fiber, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional));
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
    if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
      return exp_bcs;
    }
    exps = f2cons__cdr(exps, cause);
    iter = raw__list_cdr__set(cause, iter, exp_bcs);
  }
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__if_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__if_exp__symbol != -1, nil, "__funk2.compile.f2__compile__if_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__if_exp__symbol, exps);
  assert_argument_type(fiber, fiber);
  
  if (! raw__cons__is_type(cause, exps)) {
    return f2larva__new(cause, 1, nil);
  }
  exps = f2cons__cdr(exps, cause); // skip |if|
  f2ptr cond_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause); if (!raw__cons__is_type(cause, exps)) {return f2larva__new(cause, 1, nil);}
  f2ptr true_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
  
  f2ptr false_exps = exps;
  if (false_exps && (! raw__cons__is_type(cause, false_exps))) {
    return f2larva__new(cause, 1, nil);
  }
  
  f2ptr cond_bcs = assert_value(raw__compile(cause, fiber, cond_exp, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional));
  if (cond_bcs && (! raw__cons__is_type(cause, cond_bcs))) {
    return f2larva__new(cause, 1, nil);
  }
  
  boolean_t true__popped_env_and_return = boolean__false;
  f2ptr true_bcs = assert_value(raw__compile(cause, fiber, true_exp, protect_environment, optimize_tail_recursion, &true__popped_env_and_return, is_funktional, local_variables, is_locally_funktional));
  if (true_bcs && (! raw__cons__is_type(cause, true_bcs))) {
    return f2larva__new(cause, 1, nil);
  }
  
  boolean_t false__popped_env_and_return = boolean__false;
  boolean_t optimize_unused_beginning    = boolean__true;
  f2ptr false_bcs = f2__compile__rawcode(cause, fiber, false_exps, protect_environment, optimize_tail_recursion, &false__popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
  if (false_bcs && (! raw__cons__is_type(cause, false_bcs))) {
    return f2larva__new(cause, 1, nil);
  }
  
  if (true__popped_env_and_return || false__popped_env_and_return) {
    *popped_env_and_return = boolean__true;
    
    if (! true__popped_env_and_return) {
      f2ptr block_pop = f2__compile__block_pop(cause);
      if (true_bcs) {
	raw__list_cdr__set(cause, true_bcs, block_pop);
      } else {
	true_bcs = block_pop;
      }
    }
    
    if (! false__popped_env_and_return) {
      f2ptr block_pop = f2__compile__block_pop(cause);
      if (false_bcs) {
	raw__list_cdr__set(cause, false_bcs, block_pop);
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
  iter = raw__list_cdr__set(cause, iter, f2__compile__else_jump(cause, false_jump_end_bcs));
  iter = raw__list_cdr__set(cause, iter, loop_bcs);
  iter = raw__list_cdr__set(cause, iter, loop_done_jump_cond_bcs);
  iter = raw__list_cdr__set(cause, iter, end_nop_bcs);
  //printf("\nfull_bcs: "); f2__print(nil, nil, full_bcs); fflush(stdout);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__while_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__while_exp__symbol != -1, nil, "__funk2.compile.f2__compile__while_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__while_exp__symbol, exps);
  
  if (! raw__cons__is_type(cause, exps)) {
    printf("\nf2__compile__while_exp error: exps="); f2__print(nil, exps); fflush(stdout);
    return f2larva__new(cause, 1, nil);
  }
  exps = f2cons__cdr(exps, cause); // skip |while|
  f2ptr cond_exp = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
  if (exps && (! raw__cons__is_type(cause, exps))) {
    printf("\ncompile error: exps="); f2__print(nil, exps); fflush(stdout);
    return f2larva__new(cause, 1, nil);
  }
  
  f2ptr loop_exps = exps;
  if (loop_exps && (! raw__cons__is_type(cause, loop_exps))) {
    printf("\nf2__compile__while_exp error: loop_exps="); f2__print(nil, loop_exps); fflush(stdout);
    return f2larva__new(cause, 1, nil);
  }
  
  f2ptr cond_bcs = assert_value(raw__compile(cause, fiber, cond_exp, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional));
  if (cond_bcs && (! raw__cons__is_type(cause, cond_bcs))) {
    printf("\nf2__compile__while_exp error: cond_bcs="); f2__print(nil, cond_bcs); fflush(stdout);
    return f2larva__new(cause, 1, nil);
  }
  
  boolean_t loop__popped_env_and_return    = boolean__false;
  boolean_t optimize_unused_beginning      = boolean__true;
  boolean_t protect_subexp_environment     = boolean__true || protect_environment;
  boolean_t optimize_subexp_tail_recursion = boolean__false && optimize_tail_recursion;
  f2ptr loop_bcs = assert_value(f2__compile__rawcode(cause, fiber, loop_exps, protect_subexp_environment, optimize_subexp_tail_recursion, &loop__popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning));
  if (loop_bcs && (! raw__cons__is_type(cause, loop_bcs))) {
    printf("\nf2__compile__while_exp error: loop_bcs="); f2__print(nil, loop_bcs); fflush(stdout);
    return f2larva__new(cause, 1, nil);
  }
  
  return bcs_valid(f2__compile__while(cause, cond_bcs, loop_bcs));
}

f2ptr f2__compile__return(f2ptr simple_cause, f2ptr value_bcs, boolean_t popped_env_and_return) {
  release__assert(__funk2.compile.f2__compile__return__symbol != -1, nil, "__funk2.compile.f2__compile__return__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__return__symbol, f2list1__new(simple_cause, value_bcs));
  
  if (! value_bcs) {
    value_bcs = f2__compile__nop(cause);
  }
  f2ptr full_bcs = value_bcs;
  f2ptr iter     = value_bcs;
  
  if (! popped_env_and_return) {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  }
  
  iter = raw__list_cdr__set(cause, iter, f2__compile__copy_return_to_pc(cause));
  
  //printf("\nfull_bcs: "); f2__print(nil, full_bcs); fflush(stdout);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__return_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__return_exp__symbol != -1, nil, "__funk2.compile.f2__compile__return_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__return_exp__symbol, exps);
  
  if (! raw__cons__is_type(cause, exps)) {
    return f2larva__new(cause, 1, nil);
  }
  exps = f2cons__cdr(exps, cause); // skip |return|
  f2ptr value_exp = nil;
  if (exps) {
    value_exp = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
    if (exps) {
      return f2larva__new(cause, 421435, nil);
    }
  }
  
  boolean_t value_popped_env_and_return = boolean__false;
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, &value_popped_env_and_return, is_funktional, local_variables, is_locally_funktional));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 1, nil);
  }
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
    f2ptr arg_cause   = f2cause__compiled_from__new(cause, __funk2.compile.f2__compile__eval_args__current_arg__symbol, raw__cons__new(cause, current_arg, nil));
    
    exp_bcs = assert_value(raw__compile(arg_cause, fiber, current_arg, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional));
    if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
      return f2larva__new(cause, 123451, nil);
    }
    iter = raw__list_cdr__set(cause, iter, exp_bcs);
    
    if (next_args) {
      exp_bcs = f2__compile__block_eval_args_next(cause); iter = raw__list_cdr__set(cause, iter, exp_bcs);
    } else {
      exp_bcs = f2__compile__block_eval_args_end(cause); iter = raw__list_cdr__set(cause, iter, exp_bcs);
    }
    args = next_args;
  }
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__define_funk_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__define_funk_exp__symbol != -1, nil, "__funk2.compile.f2__compile__define_funk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__define_funk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33135, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 33264, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 11353, nil);
  }
  f2ptr define_funkvar_bcs = f2__compile__define_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, define_funkvar_bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__define_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__define_exp__symbol != -1, nil, "__funk2.compile.f2__compile__define_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__define_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 313531, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 333573, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 135111, nil);
  }
  f2ptr define_var_bcs = f2__compile__define_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, define_var_bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__mutate_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__mutate_exp__symbol != -1, nil, "__funk2.compile.f2__compile__mutate_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__mutate_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 13533, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 34633, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 24661, nil);
  }
  f2ptr var_mutate__bcs = f2__compile__var__mutate(cause, var);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, var_mutate__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__mutatefunk_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__mutatefunk_exp__symbol != -1, nil, "__funk2.compile.f2__compile__mutatefunk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__mutatefunk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 3153333, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 3611613, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 135115, nil);
  }
  f2ptr funkvar_mutate__bcs = f2__compile__funkvar__mutate(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, funkvar_mutate__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__globalize_var_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__globalize_var_exp__symbol != -1, nil, "__funk2.compile.f2__compile__globalize_var_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__globalize_var_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 331536, nil);} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 331616, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 2146111, nil);
  }
  f2ptr var_set__bcs = f2__compile__globalize_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, var_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__globalize_funkvar_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__globalize_funkvar_exp__symbol != -1, nil, "__funk2.compile.f2__compile__globalize_funkvar_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__globalize_funkvar_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 313513, nil);} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return f2larva__new(cause, 361623, nil);} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = assert_value(raw__compile(cause, fiber, value_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (value_bcs && (! raw__cons__is_type(cause, value_bcs))) {
    return f2larva__new(cause, 135611, nil);
  }
  f2ptr funkvar_set__bcs = f2__compile__globalize_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = raw__list_cdr__set(cause, iter, funkvar_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr f2__compile__apply_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return) {
  release__assert(__funk2.compile.f2__compile__apply_exp__symbol != -1, nil, "__funk2.compile.f2__compile__apply_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__apply_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr funk_exp = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr args_exp = f2cons__car(exps, cause);
  
  f2ptr full_bcs = assert_value(raw__compile(cause, fiber, funk_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (full_bcs && (! raw__cons__is_type(cause, full_bcs))) {
    return f2larva__new(cause, 246416, nil);
  }
  f2ptr iter = full_bcs;
  
  iter          = raw__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  f2ptr exp_bcs = assert_value(raw__compile(cause, fiber, args_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
    return f2larva__new(cause, 131365, nil);
  }
  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  iter = raw__list_cdr__set(cause, iter, f2__compile__copy_value_to_args(cause));
  iter = raw__list_cdr__set(cause, iter, f2__compile__pop_value(cause));
  if (optimize_tail_recursion) {
    if (popped_env_and_return != NULL) {
      *popped_env_and_return = boolean__true;
    }
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  }
  if (protect_environment) {
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_push(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
  } else {
    iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
  }
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__local_apply_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return) {
  release__assert(__funk2.compile.f2__compile__local_apply_exp__symbol != -1, nil, "__funk2.compile.f2__compile__local_apply_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__local_apply_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr funk_exp = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! raw__cons__is_type(cause, exps)) {return __funk2.compile.compile__exception;} f2ptr args_exp = f2cons__car(exps, cause);
  
  f2ptr full_bcs = assert_value(raw__compile(cause, fiber, funk_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (full_bcs && (! raw__cons__is_type(cause, full_bcs))) {
    return f2larva__new(cause, 246416, nil);
  }
  f2ptr iter = full_bcs;
  
  iter          = raw__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  f2ptr exp_bcs = assert_value(raw__compile(cause, fiber, args_exp, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  if (exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
    return f2larva__new(cause, 131365, nil);
  }
  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  iter = raw__list_cdr__set(cause, iter, f2__compile__copy_value_to_args(cause));
  iter = raw__list_cdr__set(cause, iter, f2__compile__pop_value(cause));
  /*
  if (optimize_tail_recursion) {
    if (popped_env_and_return != NULL) {
      *popped_env_and_return = boolean__true;
    }
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
  }
  */
  /*
  if (protect_environment) {
  */
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_push(cause));
    //iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
    /*
  } else {
    //iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
    iter = raw__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
  }
    */
  return bcs_valid(full_bcs);
}

f2ptr raw__apply_funk(f2ptr simple_cause, f2ptr fiber, f2ptr funk, f2ptr args);

f2ptr f2__compile__funkvar_call(f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__funkvar_call__symbol != -1, nil, "__funk2.compile.f2__compile__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__funkvar_call__symbol, exps);
  
  f2ptr funkvar = f2cons__car(exps, cause);
  f2ptr funkvar_value = f2__fiber__lookup_type_variable_value(cause, fiber, __funk2.primobject__frame.funk_variable__symbol, funkvar);
  if (raw__metrocfunk__is_type(cause, funkvar_value)) {
    f2ptr metro_expansion_result = assert_value(f2__metrocfunk__apply(cause, funkvar_value, fiber, f2cons__cdr(exps, cause)));
    f2ptr exp_bcs                = assert_value(raw__compile(cause, fiber, metro_expansion_result, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional));
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
    f2ptr full_bcs = assert_value(f2__compile__eval_args(cause, fiber, f2cons__cdr(exps, cause), is_funktional, local_variables, is_locally_funktional)); f2ptr iter = full_bcs;
    boolean_t all_args_are_immutable = boolean__true;
    if ((is_funktional != NULL) && (*is_funktional)) {
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
      f2ptr funk_apply__result = assert_value(raw__apply_funk(cause, fiber, funkvar_value, f2cons__cdr(exps, cause)));
      full_bcs = f2__compile__value__set(cause, funk_apply__result); iter = full_bcs;
    } else {
      iter = raw__list_cdr__set(cause, iter, f2__compile__lookup_funkvar(cause, funkvar));
      if (optimize_tail_recursion) {
	if (popped_env_and_return) {
	  *popped_env_and_return = boolean__true;
	}
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
      }
      if (protect_environment) {
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_push(cause));
	iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
	iter = raw__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
	iter = raw__list_cdr__set(cause, iter, f2__compile__block_pop(cause));
      } else {
	iter = raw__list_cdr__set(cause, iter, f2__compile__funk_env(cause));
	iter = raw__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
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
  f2ptr new_fiber = assert_value(f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), metro, args));
  
  //printf ("\nCompile fiber created: 0x%X", (uint)new_fiber); fflush(stdout);
  assert_value(f2__global_scheduler__complete_fiber(cause, new_fiber));
  
  f2ptr value = assert_value(f2fiber__value(new_fiber, cause));
  if ((f2__fiber__paused(cause, new_fiber) != nil) &&
      raw__bug__is_type(cause, value)) {
    return f2larva__new(cause, 13532, value);
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
  f2ptr new_fiber = assert_value(f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), funk, args));
  
  //printf ("\nCompile fiber created: 0x%X", (uint)new_fiber); fflush(stdout);
  assert_value(f2__global_scheduler__complete_fiber(cause, new_fiber));
  
  f2ptr value = assert_value(f2fiber__value(new_fiber, cause));
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
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = raw__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = raw__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = raw__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = assert_value(raw__compile(cause, fiber, f2cons__car(args, cause), boolean__true, boolean__false, NULL, NULL, nil, NULL));
    if(exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
      return f2larva__new(cause, 135115, nil);
    }
    iter = raw__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(cause);                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(cause);                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__car__set(cause);                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
    args = f2cons__cdr(args, cause);
    if (args) {
      exp_bcs   = f2__compile__copy_iter_to_value(cause);                   iter = raw__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cons(cause);                                 iter = raw__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(cause);                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cdr__set(cause);                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(cause);                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
    }
  }
  exp_bcs       = f2__compile__copy_args_to_value(cause);                   iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return bcs_valid(full_bcs);
}

f2ptr f2__compile__backquote_append_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exps) {
  release__assert(__funk2.compile.f2__compile__backquote_append_exp__symbol != -1, nil, "__funk2.compile.f2__compile__backquote_append_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__backquote_append_exp__symbol, exps);
  
  f2ptr args = f2cons__cdr(exps, cause);
  if (! args) {
    return bcs_valid(f2__compile__value__set(cause, nil));
  }
  f2ptr cdr = f2cons__cdr(args, cause);
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = raw__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = raw__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = raw__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = assert_value(raw__compile(cause, fiber, f2cons__car(args, cause), boolean__true, boolean__false, NULL, NULL, nil, NULL));
    if(exp_bcs && (! raw__cons__is_type(cause, exp_bcs))) {
      return f2larva__new(cause, 113651, nil);
    }
    iter = raw__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(cause);                              iter = raw__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(cause);                              iter = raw__list_cdr__set(cause, iter, exp_bcs);
    if (cdr) {
      exp_bcs   = f2__compile__car__set(cause);                              iter = raw__list_cdr__set(cause, iter, exp_bcs);
    } else {
      exp_bcs   = f2__compile__cdr__set(cause);                              iter = raw__list_cdr__set(cause, iter, exp_bcs);
    }
    
    args = f2cons__cdr(args, cause);
    if (args) {
      cdr = f2cons__cdr(args, cause);
      if (cdr) {
	exp_bcs = f2__compile__copy_iter_to_value(cause);  iter = raw__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cons(cause);                iter = raw__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause); iter = raw__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cdr__set(cause);            iter = raw__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause); iter = raw__list_cdr__set(cause, iter, exp_bcs);
      }
    }
  }
  
  exp_bcs       = f2__compile__copy_args_to_value(cause);                   iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return bcs_valid(full_bcs);
}




// eq

f2ptr f2__compile__bytecode_eq_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__eq(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// not

f2ptr f2__compile__bytecode_not_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x        = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x__bcs = assert_value(raw__compile(cause, fiber, x, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x__bcs;                                                                          f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__not(cause, __fiber__value_reg__symbol, __fiber__value_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// and

f2ptr f2__compile__bytecode_and_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__and(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// or

f2ptr f2__compile__bytecode_or_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__or(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// add

f2ptr f2__compile__bytecode_add_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__add(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// negative

f2ptr f2__compile__bytecode_negative_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x        = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x__bcs = assert_value(raw__compile(cause, fiber, x, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x__bcs;                                                                          f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__negative(cause, __fiber__value_reg__symbol, __fiber__value_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// subtract

f2ptr f2__compile__bytecode_subtract_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__subtract(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// multiply

f2ptr f2__compile__bytecode_multiply_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__multiply(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// inverse

f2ptr f2__compile__bytecode_inverse_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x        = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x__bcs = assert_value(raw__compile(cause, fiber, x, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x__bcs;                                                                          f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__inverse(cause, __fiber__value_reg__symbol, __fiber__value_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// divide

f2ptr f2__compile__bytecode_divide_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__divide(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// modulo

f2ptr f2__compile__bytecode_modulo_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__modulo(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// increment

f2ptr f2__compile__bytecode_increment_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x        = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x__bcs = assert_value(raw__compile(cause, fiber, x, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x__bcs;                                                                          f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__increment(cause, __fiber__value_reg__symbol, __fiber__value_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// decrement

f2ptr f2__compile__bytecode_decrement_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x        = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x__bcs = assert_value(raw__compile(cause, fiber, x, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x__bcs;                                                                          f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__decrement(cause, __fiber__value_reg__symbol, __fiber__value_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// numerically_equals

f2ptr f2__compile__bytecode_numerically_equals_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__numerically_equals(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// less_than

f2ptr f2__compile__bytecode_less_than_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__less_than(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


// greater_than

f2ptr f2__compile__bytecode_greater_than_exp(f2ptr cause, f2ptr fiber, f2ptr exp) {
  assert_argument_type(cons, exp);
  f2ptr arg_iter = exp;                          arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x0       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(cons, arg_iter);
  f2ptr x1       = f2cons__car(arg_iter, cause); arg_iter = f2cons__cdr(arg_iter, cause); assert_argument_type(nil, arg_iter);
  f2ptr x0__bcs = assert_value(raw__compile(cause, fiber, x0, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr x1__bcs = assert_value(raw__compile(cause, fiber, x1, boolean__true, boolean__false, NULL, NULL, nil, NULL));
  f2ptr exp_bcs = x0__bcs;                                                                                                  f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = x1__bcs;                                                                                                  iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__push_value(cause);                                                                           iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_iter(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__pop_args(cause);                                                                             iter = raw__list_cdr__set(cause, iter, exp_bcs);
  exp_bcs       = f2__compile__greater_than(cause, __fiber__value_reg__symbol, __fiber__iter_reg__symbol, __fiber__args_reg__symbol); iter = raw__list_cdr__set(cause, iter, exp_bcs);
  return full_bcs;
}


f2ptr f2__compile__special_symbol_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__special_symbol_exp__symbol != -1, nil, "__funk2.compile.f2__compile__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__special_symbol_exp__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  f2ptr car = f2cons__car(exp, cause);
  if (raw__symbol__eq(cause, car, __funk2.globalenv.quote__symbol))                                                                                                                            {return bcs_valid(f2__compile__value__set(cause, f2cons__car(f2cons__cdr(exp, cause), cause)));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list__symbol))        {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__backquote_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list_append__symbol)) {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__backquote_append_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.if__symbol))                                                                                                                               {return bcs_valid(f2__compile__if_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.while__symbol))                                                                                                                            {return bcs_valid(f2__compile__while_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.return__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__return_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.apply__symbol))                  {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__apply_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.local_apply__symbol))            {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__local_apply_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return));}
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
    f2ptr globalize_funkvar_bcs = assert_value(f2__compile__globalize_funkvar_exp(cause, fiber, exp));
    return bcs_valid(globalize_funkvar_bcs);
  }
  if (raw__symbol__eq(cause, car, __funk2.globalenv.yield__symbol))                  {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__yield(cause));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode__symbol))               {return bcs_valid(f2__compile__bytecode_exp(cause, exp, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.rawcode__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__rawcode_exp(cause, exp, fiber, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_eq__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_eq_exp(                cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_not__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_not_exp(               cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_and__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_and_exp(               cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_or__symbol))                 {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_or_exp(                cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_add__symbol))                {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_add_exp(               cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_negative__symbol))           {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_negative_exp(          cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_subtract__symbol))           {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_subtract_exp(          cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_multiply__symbol))           {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_multiply_exp(          cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_inverse__symbol))            {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_inverse_exp(           cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_divide__symbol))             {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_divide_exp(            cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_modulo__symbol))             {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_modulo_exp(            cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_increment__symbol))          {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_increment_exp(         cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_decrement__symbol))          {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_decrement_exp(         cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_numerically_equals__symbol)) {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_numerically_equals_exp(cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_less_than__symbol))          {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_less_than_exp(         cause, fiber, exp));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_greater_than__symbol))       {if (is_funktional) {*is_funktional = boolean__false;} if (is_locally_funktional) {*is_locally_funktional = boolean__false;} return bcs_valid(f2__compile__bytecode_greater_than_exp(      cause, fiber, exp));}
  
  status("tried to compile special symbol exp: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  //error(nil, "f2__compile__special_symbol_exp error: expression is not special symbol expression.");
  return f2larva__new(cause, 127, nil);
}

void dont_know_how_to_compile() {
  status("don't know how to compile [breakpoint].");
}

f2ptr f2__compile__cons_exp(f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  release__assert(__funk2.compile.f2__compile__cons_exp__symbol != -1, nil, "__funk2.compile.f2__compile__cons_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__compile__cons_exp__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  f2ptr car = f2cons__car(exp, cause);
  //f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
  f2ptr funkvar_value = f2__fiber__lookup_type_variable_value(cause, fiber, __funk2.primobject__frame.funk_variable__symbol, car);
  // check to see if we can find metro binding for this funkvar.
  if (raw__metro__is_type(cause, funkvar_value) ||
      raw__metrocfunk__is_type(cause, funkvar_value)) {
    f2ptr metro_apply_result = catch_value(raw__apply_metro(cause, fiber, funkvar_value, f2cons__cdr(exp, cause)),
					   f2list4__new(cause,
							new__symbol(cause, "exp"),           exp,
							new__symbol(cause, "funkvar_value"), funkvar_value));
    return raw__compile(cause, fiber, metro_apply_result, boolean__true, boolean__false, NULL, is_funktional, local_variables, is_locally_funktional);
  }
  if (raw__is_compile_special_symbol(cause, car)) {
    f2ptr special_symbol_result = assert_value(f2__compile__special_symbol_exp(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));
    return bcs_valid(special_symbol_result);
  }
  if (raw__symbol__is_type(cause, car))          {return bcs_valid(f2__compile__funkvar_call(cause, fiber, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  status("tried to compile: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("don't know how to compile."); // should throw exception... (or return larva)
  dont_know_how_to_compile();
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_type"), new__symbol(cause, "do_not_know_how_to_compile"),
				 new__symbol(cause, "funkname"), new__symbol(cause, "compile-cons_exp"),
				 new__symbol(cause, "exp"),      exp));
}

f2ptr f2__compile__bytecode_exp(f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  if (! raw__cons__is_type(cause, exp)) {
    return f2larva__new(cause, 34621, nil);
  }
  f2ptr exp_iter = f2cons__cdr(exp, cause);
  if (! raw__cons__is_type(cause, exp_iter)) {
    return f2larva__new(cause, 2352351, nil);
  }
  f2ptr command = f2cons__car(exp_iter, cause);
  if (! raw__symbol__is_type(cause, command)) {
    return f2larva__new(cause, 123564, nil);
  }

  if        (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__push__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__pop__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__copy__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__swap__symbol)) {
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__array__symbol)) {
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
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__lookup__symbol)) {
    if (is_funktional) {
      *is_funktional = boolean__false;
    }
    if (is_locally_funktional) {
      *is_locally_funktional = boolean__false;
    }
  } else if (raw__symbol__eq(cause, command, __funk2.bytecode.bytecode__define__symbol)) {
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
  return raw__cons__new(cause, f2bytecode__new(cause, command, arg0, arg1, arg2), nil);
}

f2ptr f2__compile__rawcode_exp(f2ptr cause, f2ptr exp, f2ptr fiber, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional) {
  assert_argument_type(fiber, fiber);
  if (! raw__cons__is_type(cause, exp)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr exps = f2cons__cdr(exp, cause);
  if ((exps != nil) &&
      (! raw__cons__is_type(cause, exps))) {
    return f2larva__new(cause, 1, nil);
  }
  boolean_t optimize_unused_beginning = boolean__false;
  return f2__compile__rawcode(cause, fiber, exps, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
}

f2ptr f2__demetropolize__funkvar_call(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize__funkvar_call__symbol != -1, nil, "__funk2.compile.f2__demetropolize__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize__funkvar_call__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  f2ptr did_something = nil;
  f2ptr args = assert_value(f2__cons__cdr(cause, exp));
  if ((args != nil) && (! raw__cons__is_type(cause, args))) {
    return f2larva__new(cause, 125321, f2__bug__new(cause, f2integer__new(cause, 125321), f2__frame__new(cause, f2list6__new(cause,
															     new__symbol(cause, "bug_type"), new__symbol(cause, "args to demetropolize-funkvar_call is not of type conslist."),
															     new__symbol(cause, "funktion"), new__symbol(cause, "demetropolize-funkvar_call"),
															     new__symbol(cause, "args"),     args))));
  }
  if (args == nil) {
    return raw__cons__new(cause, nil, exp);
  }
  f2ptr exp__car = assert_value(f2__cons__car(cause, exp));
  f2ptr demetro_exp  = raw__cons__new(cause, exp__car, nil);
  f2ptr iter         = args;
  f2ptr demetro_iter = demetro_exp;
  while (iter) {
    f2ptr arg = assert_value(f2__cons__car(cause, iter));
    
    f2ptr demetro_arg__values = assert_value(f2__demetropolize_once(cause, fiber, env, arg));
    f2ptr demetro_arg__values__car = f2__cons__car(cause, demetro_arg__values);
    if(demetro_arg__values__car != nil) {
      did_something = __funk2.globalenv.true__symbol;
    }
    f2ptr demetro_arg = assert_value(f2__cons__cdr(cause, demetro_arg__values));
    
    f2ptr demetro_iter_next = raw__cons__new(cause, demetro_arg, nil);
    
    assert_value(f2__cons__cdr__set(cause, demetro_iter, demetro_iter_next));
    
    demetro_iter = demetro_iter_next;
    iter = assert_value(f2__cons__cdr(cause, iter));
  }
  return raw__cons__new(cause, did_something, demetro_exp);
}

f2ptr f2__demetropolize__special_symbol_exp(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize__special_symbol_exp__symbol != -1, nil, "__funk2.compile.f2__demetropolize__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize__special_symbol_exp__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  f2ptr car = f2cons__car(exp, cause);
  if (raw__symbol__eq(cause, car, __funk2.globalenv.quote__symbol))                       {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list__symbol))             {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list_append__symbol))      {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.if__symbol))                          {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.while__symbol))                       {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.return__symbol))                      {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.apply__symbol))                       {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.local_apply__symbol))                 {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.funkvar__symbol))                     {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define_funk__symbol))                 {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define__symbol))                      {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutatefunk__symbol))                  {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutate__symbol))                      {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize__symbol))                   {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize_funk__symbol))              {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.yield__symbol))                       {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode__symbol))                    {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.rawcode__symbol))                     {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_eq__symbol))                 {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_not__symbol))                {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_and__symbol))                {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_or__symbol))                 {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_add__symbol))                {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_negative__symbol))           {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_subtract__symbol))           {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_multiply__symbol))           {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_inverse__symbol))            {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_divide__symbol))             {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_modulo__symbol))             {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_increment__symbol))          {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_decrement__symbol))          {return raw__cons__new(cause, nil, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_numerically_equals__symbol)) {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_less_than__symbol))          {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_greater_than__symbol))       {return f2__demetropolize__funkvar_call(cause, fiber, env, exp);}
  status("tried to compile special symbol exp: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  status("f2__demetropolize__special_symbol_exp error: expression is not special symbol expression.");
  return f2larva__new(cause, 126, nil);
}

f2ptr f2__demetropolize_once(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize_once__symbol != -1, nil, "__funk2.compile.f2__demetropolize_once__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize_once__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  if (raw__cons__is_type(cause, exp)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
      if (raw__metro__is_type(cause, funkvar_value) ||
	  raw__metrocfunk__is_type(cause, funkvar_value)) {
	f2ptr metro_apply_result = catch_value(raw__apply_metro(simple_cause, fiber, funkvar_value, f2cons__cdr(exp, cause)),
					       f2list4__new(cause,
							    new__symbol(cause, "exp"),           exp,
							    new__symbol(cause, "funkvar_value"), funkvar_value));
	values = raw__cons__new(simple_cause, __funk2.globalenv.true__symbol, metro_apply_result);
      }
      else if (raw__is_compile_special_symbol(cause, car)) {
	values = assert_value(f2__demetropolize__special_symbol_exp(simple_cause, fiber, env, exp));
      } else if (raw__symbol__is_type(cause, car)) {
	values = assert_value(f2__demetropolize__funkvar_call(simple_cause, fiber, env, exp));
      } else {
	values = raw__cons__new(simple_cause, nil, exp);
      }
    }
    
    f2ptr did_something = nil;
    if (f2cons__car(values, cause)) {
      did_something = __funk2.globalenv.true__symbol;
    }
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      return raw__cons__new(cause, __funk2.globalenv.true__symbol, retval);
    } else {
      return raw__cons__new(cause, nil, exp);
    }
  }
  return raw__cons__new(cause, nil, exp);
}

f2ptr f2__demetropolize_full__with_status(f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp) {
  release__assert(__funk2.compile.f2__demetropolize_full__symbol != -1, nil, "__funk2.compile.f2__demetropolize_full__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.f2__demetropolize_full__symbol, raw__cons__new(simple_cause, exp, nil));
  assert_argument_type(fiber, fiber);
  
  if (raw__cons__is_type(cause, exp)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2fiber__env(fiber, cause), car);
      if (raw__metro__is_type(cause, funkvar_value) ||
	  raw__metrocfunk__is_type(cause, funkvar_value)) {
	f2ptr metro_apply_result = catch_value(raw__apply_metro(simple_cause, fiber, funkvar_value, f2cons__cdr(exp, cause)),
					       f2list4__new(cause,
							    new__symbol(cause, "exp"),           exp,
							    new__symbol(cause, "funkvar_value"), funkvar_value));
	values = raw__cons__new(simple_cause, __funk2.globalenv.true__symbol, metro_apply_result);
      }
      else if (raw__is_compile_special_symbol(cause, car)) {
	values = assert_value(f2__demetropolize__special_symbol_exp(simple_cause, fiber, env, exp));
      } else if (raw__symbol__is_type(cause, car)) {
	values = assert_value(f2__demetropolize__funkvar_call(simple_cause, fiber, env, exp));
      } else {
	values = raw__cons__new(simple_cause, nil, exp);
      }
    }
    
    f2ptr did_something = nil;
    if(f2cons__car(values, cause)) {
      did_something = __funk2.globalenv.true__symbol;
    }
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      f2ptr demetropolize_result = assert_value(f2__demetropolize_full__with_status(cause, fiber, env, retval));
      return raw__cons__new(cause, __funk2.globalenv.true__symbol, f2cons__cdr(demetropolize_result, cause));
    } else {
      return raw__cons__new(cause, nil, exp);
    }
  }
  return raw__cons__new(cause, nil, exp);
}

f2ptr raw__funk__new_with_replaced_variable(f2ptr cause, f2ptr this, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr old_name                = f2funk__name(               this, cause);
  f2ptr old_args                = f2funk__args(               this, cause);
  f2ptr old_demetropolized_body = f2funk__demetropolized_body(this, cause);
  f2ptr old_env                 = f2funk__env(                this, cause);
  f2ptr new_args                = nil;
  {
    f2ptr iter          = old_args;
    f2ptr new_args_iter = nil;
    while (iter != nil) {
      f2ptr arg = f2cons__car(iter, cause);
      if (! raw__eq(cause, arg, replace_variable)) {
	f2ptr new_cons = f2cons__new(cause, arg, nil);
	if (new_args == nil) {
	  new_args = new_cons;
	} else {
	  f2cons__cdr__set(new_args_iter, cause, new_cons);
	}
	new_args_iter = new_cons;
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr new_demetropolized_body = nil;
  {
    f2ptr iter                         = old_demetropolized_body;
    f2ptr new_demetropolized_body_iter = nil;
    while (iter != nil) {
      f2ptr expression = f2cons__car(iter, cause);
      {
	f2ptr new_expression = assert_value(raw__expression__replace_variable(cause, expression, replace_variable, replace_argument));
	f2ptr new_cons       = f2cons__new(cause, new_expression, nil);
	if (new_demetropolized_body == nil) {
	  new_demetropolized_body = new_cons;
	} else {
	  f2cons__cdr__set(new_demetropolized_body_iter, cause, new_cons);
	}
	new_demetropolized_body_iter = new_cons;
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr fiber                                       = assert_value(f2__this__fiber(cause));
  f2ptr fiber__environment                          = assert_value(f2__fiber__env(cause, fiber));
  f2ptr new_demetropolized_body__demetropolize_full = assert_value(f2__exps_demetropolize_full(cause, fiber, fiber__environment, new_demetropolized_body));
  f2ptr compiled_funk                               = assert_value(f2__funk__new(cause, fiber, old_env, old_name, new_args, new_demetropolized_body__demetropolize_full, new_demetropolized_body, nil, nil, nil));
  return compiled_funk;
}

f2ptr raw__expression__replace_variable__funkvar_call(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr command        = f2cons__car(expression, cause);
  f2ptr new_expression = f2cons__new(cause, command, nil);
  {
    f2ptr iter                = f2cons__cdr(expression, cause);
    f2ptr new_expression_iter = new_expression;
    while (iter != nil) {
      f2ptr subexpression = f2cons__car(iter, cause);
      {
	f2ptr new_subexpression = assert_value(raw__expression__replace_variable(cause, subexpression, replace_variable, replace_argument));
	f2ptr new_cons          = f2cons__new(cause, new_subexpression, nil);
	if (new_expression == nil) {
	  new_expression = new_cons;
	} else {
	  f2cons__cdr__set(new_expression_iter, cause, new_cons);
	}
	new_expression_iter = new_cons;
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return new_expression;
}

f2ptr raw__expression__replace_variable__local_apply(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr funkable             = f2cons__car(cdr, cause);
  if (! raw__funk__is_type(cause, funkable)) {
    return f2larva__new(cause, 555, nil);
    //return new__error(f2list6__new(cause,
    //				   new__symbol(cause, "bug_name"),         new__symbol(cause, "expression-replace_variable-local_apply-funkable_must_be_funk_to_safely_remove_variable"),
    //				   new__symbol(cause, "expression"),       expression,
    //				   new__symbol(cause, "replace_variable"), replace_variable,
    //				   new__symbol(cause, "replace_argument"), replace_argument));
  }
  f2ptr new_funkable         = assert_value(raw__funk__new_with_replaced_variable(cause, funkable, replace_variable, replace_argument));
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr arguments            = f2cons__car(cdr_cdr, cause);
  f2ptr new_arguments        = assert_value(raw__expression__replace_variable(cause, arguments, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.local_apply__symbol, new_funkable, new_arguments);
}

f2ptr raw__expression__replace_variable__apply(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  // cannot remove variables unless the apply has been reduced to a local_apply.
  return f2larva__new(cause, 555, nil);
}

f2ptr raw__expression__replace_variable__define_funk(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.define_funk__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__define(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  if (raw__eq(cause, variable_name, replace_variable)) {
    return f2larva__new(cause, 555, nil);
  }
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.define__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__mutatefunk(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.mutatefunk__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__mutate(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  if (raw__eq(cause, variable_name, replace_variable)) {
    return f2larva__new(cause, 555, nil);
  }
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.mutate__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__globalize(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.globalize__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__globalize_funk(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  f2ptr cdr_cdr              = f2cons__cdr(cdr, cause);
  f2ptr value_expression     = f2cons__car(cdr_cdr, cause);
  f2ptr new_value_expression = assert_value(raw__expression__replace_variable(cause, value_expression, replace_variable, replace_argument));
  return f2list3__new(cause, __funk2.globalenv.globalize_funk__symbol, variable_name, new_value_expression);
}

f2ptr raw__expression__replace_variable__bytecode_increment(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  if (raw__eq(cause, variable_name, replace_variable)) {
    return f2larva__new(cause, 555, nil);
  }
  return f2list2__new(cause, __funk2.globalenv.bytecode_increment__symbol, variable_name);
}

f2ptr raw__expression__replace_variable__bytecode_decrement(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr                  = f2cons__cdr(expression, cause);
  f2ptr variable_name        = f2cons__car(cdr, cause);
  if (raw__eq(cause, variable_name, replace_variable)) {
    return f2larva__new(cause, 555, nil);
  }
  return f2list2__new(cause, __funk2.globalenv.bytecode_decrement__symbol, variable_name);
}

f2ptr raw__expression__replace_variable__funk__new_copy_in_this_environment(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr cdr      = f2cons__cdr(expression, cause);
  f2ptr funkable = f2cons__car(cdr, cause);
  if (! raw__funk__is_type(cause, funkable)) {
    return f2larva__new(cause, 555, nil);
  }
  f2ptr new_funkable = assert_value(raw__funk__new_with_replaced_variable(cause, funkable, replace_variable, replace_argument));
  return f2list2__new(cause, new__symbol(cause, "funk-new_copy_in_this_environment"), new_funkable);
}

f2ptr raw__expression__replace_variable__special_symbol_exp(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr car = f2cons__car(exp, cause);
  if (raw__symbol__eq(cause, car, __funk2.globalenv.quote__symbol))                         {return exp;}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list__symbol))               {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.backquote__list_append__symbol))        {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.if__symbol))                            {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.while__symbol))                         {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.return__symbol))                        {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.apply__symbol))                         {return assert_value(raw__expression__replace_variable__apply(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.local_apply__symbol))                   {return assert_value(raw__expression__replace_variable__local_apply(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.funkvar__symbol))                       {return exp;}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define_funk__symbol))                   {return assert_value(raw__expression__replace_variable__define_funk(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.define__symbol))                        {return assert_value(raw__expression__replace_variable__define(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutatefunk__symbol))                    {return assert_value(raw__expression__replace_variable__mutatefunk(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.mutate__symbol))                        {return assert_value(raw__expression__replace_variable__mutate(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize__symbol))                     {return assert_value(raw__expression__replace_variable__globalize(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.globalize_funk__symbol))                {return assert_value(raw__expression__replace_variable__globalize_funk(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.yield__symbol))                         {return exp;}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode__symbol))                      {return exp;} // should handle special case
  if (raw__symbol__eq(cause, car, __funk2.globalenv.rawcode__symbol))                       {return exp;} // should handle special case?
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_eq__symbol))                   {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_not__symbol))                  {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_and__symbol))                  {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_or__symbol))                   {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_add__symbol))                  {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_negative__symbol))             {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_subtract__symbol))             {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_multiply__symbol))             {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_inverse__symbol))              {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_divide__symbol))               {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_modulo__symbol))               {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_increment__symbol))            {return assert_value(raw__expression__replace_variable__bytecode_increment(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_decrement__symbol))            {return assert_value(raw__expression__replace_variable__bytecode_decrement(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_numerically_equals__symbol))   {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_less_than__symbol))            {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  if (raw__symbol__eq(cause, car, __funk2.globalenv.bytecode_greater_than__symbol))         {return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, exp, replace_variable, replace_argument));}
  status("tried to compile special symbol exp: "); f2__write(cause, fiber, exp); fflush(stdout);
  status("isn't a special symbol expression."); // should throw exception...
  status("raw__expression__replace_variable__special_symbol_exp error: expression is not special symbol expression.");
  return f2larva__new(cause, 12643, nil);
}

f2ptr raw__demetropolized_expression__replace_variable(f2ptr cause, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr env   = f2fiber__env(fiber, cause);
  if (raw__symbol__is_type(cause, expression)) {
    if (raw__eq(cause, expression, replace_variable)) {
      return replace_argument;
    }
  }
  if (raw__cons__is_type(cause, expression)) {
    f2ptr command = f2cons__car(expression, cause);
    if (raw__is_compile_special_symbol(cause, command)) {
      return assert_value(raw__expression__replace_variable__special_symbol_exp(cause, fiber, env, expression, replace_variable, replace_argument));
    } else if (raw__eq(cause, command, new__symbol(cause, "funk-new_copy_in_this_environment"))) {
      return assert_value(raw__expression__replace_variable__funk__new_copy_in_this_environment(cause, fiber, env, expression, replace_variable, replace_argument));
    } else if (raw__cons__is_type(cause, expression)) {
      return assert_value(raw__expression__replace_variable__funkvar_call(cause, fiber, env, expression, replace_variable, replace_argument));
    }
  }
  return expression;
}

f2ptr raw__undemetropolized_expression__replace_variable(f2ptr cause, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  f2ptr fiber                     = f2__this__fiber(cause);
  f2ptr env                       = f2fiber__env(fiber, cause);
  f2ptr demetropolized_expression = assert_value(f2__demetropolize_full(cause, fiber, env, expression));
  return raw__demetropolized_expression__replace_variable(cause, demetropolized_expression, replace_variable, replace_argument);
}

// should only be used on demetropolized expressions (as are found in funks, during compile)
f2ptr raw__expression__replace_variable(f2ptr cause, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument) {
  return raw__demetropolized_expression__replace_variable(cause, expression, replace_variable, replace_argument);
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
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __funk2.compile.raw__compile__symbol, raw__cons__new(simple_cause, exp, nil));
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
  assert_value(result_bcs);
  return bcs_valid(result_bcs);
}


// **

void f2__compile__defragment__fix_pointers() {
  // -- reinitialize --

  defragment__fix_pointer(__funk2.compile.cause__compiled_from__symbol);
  defragment__fix_pointer(__funk2.compile.compile__exception);
  
  defragment__fix_pointer(__funk2.compile.f2__compile__funk__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__metro__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__if__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__if_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__while__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__while_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__return__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__return_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__rawcode__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__lookup_funkvar_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__eval_args__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__eval_args__current_arg__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__define_funk_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__define_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__mutate_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__mutatefunk_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__globalize_var_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__globalize_funkvar_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__apply_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__local_apply_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__funkvar_call__symbol);
  defragment__fix_pointer(__funk2.compile.raw__apply_metro__symbol);
  defragment__fix_pointer(__funk2.compile.raw__apply_funk__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__backquote_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__backquote_append_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__special_symbol_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__compile__cons_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__demetropolize__special_symbol_exp__symbol);
  defragment__fix_pointer(__funk2.compile.f2__demetropolize__funkvar_call__symbol);
  defragment__fix_pointer(__funk2.compile.f2__demetropolize_once__symbol);
  defragment__fix_pointer(__funk2.compile.f2__demetropolize_full__symbol);
  defragment__fix_pointer(__funk2.compile.raw__compile__symbol);
  
  defragment__fix_pointer(__funk2.compile.debug_funk_call__symbol);
  
  defragment__fix_pointer(__funk2.compile.wrong_argument_number__bcs);
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(wrong_argument_number__bcs__set);
  f2__primcfunk__init__defragment__fix_pointers(expression__optimize);
  
  
}

void f2__compile__reinitialize_globalvars() {
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  {char* str = "compile:cause-compiled_from"; __funk2.compile.cause__compiled_from__symbol = new__symbol(cause, str);}
  {char* str = "compile:exception";           __funk2.compile.compile__exception           = new__symbol(cause, str);}
  
  {char* str = "compile:f2__compile__funk";                     __funk2.compile.f2__compile__funk__symbol                     = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__metro";                    __funk2.compile.f2__compile__metro__symbol                    = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__if";                       __funk2.compile.f2__compile__if__symbol                       = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__if_exp";                   __funk2.compile.f2__compile__if_exp__symbol                   = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__while";                    __funk2.compile.f2__compile__while__symbol                    = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__while_exp";                __funk2.compile.f2__compile__while_exp__symbol                = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__return";                   __funk2.compile.f2__compile__return__symbol                   = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__return_exp";               __funk2.compile.f2__compile__return_exp__symbol               = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__rawcode";                  __funk2.compile.f2__compile__rawcode__symbol                  = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__lookup_funkvar_exp";       __funk2.compile.f2__compile__lookup_funkvar_exp__symbol       = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__eval_args";                __funk2.compile.f2__compile__eval_args__symbol                = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__eval_args__current_arg";   __funk2.compile.f2__compile__eval_args__current_arg__symbol   = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__define_funk_exp";          __funk2.compile.f2__compile__define_funk_exp__symbol          = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__define_exp";               __funk2.compile.f2__compile__define_exp__symbol               = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__mutate_exp";               __funk2.compile.f2__compile__mutate_exp__symbol               = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__mutatefunk_exp";           __funk2.compile.f2__compile__mutatefunk_exp__symbol           = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__globalize_var_exp";        __funk2.compile.f2__compile__globalize_var_exp__symbol        = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__globalize_funkvar_exp";    __funk2.compile.f2__compile__globalize_funkvar_exp__symbol    = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__apply_exp";                __funk2.compile.f2__compile__apply_exp__symbol                = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__local_apply_exp";          __funk2.compile.f2__compile__local_apply_exp__symbol          = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__funkvar_call";             __funk2.compile.f2__compile__funkvar_call__symbol             = new__symbol(cause, str);}
  {char* str = "compile:raw__apply_metro";                      __funk2.compile.raw__apply_metro__symbol                      = new__symbol(cause, str);}
  {char* str = "compile:raw__apply_funk";                       __funk2.compile.raw__apply_funk__symbol                       = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__backquote_exp";            __funk2.compile.f2__compile__backquote_exp__symbol            = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__backquote_append_exp";     __funk2.compile.f2__compile__backquote_append_exp__symbol     = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__special_symbol_exp";       __funk2.compile.f2__compile__special_symbol_exp__symbol       = new__symbol(cause, str);}
  {char* str = "compile:f2__compile__cons_exp";                 __funk2.compile.f2__compile__cons_exp__symbol                 = new__symbol(cause, str);}
  {char* str = "compile:f2__demetropolize__special_symbol_exp"; __funk2.compile.f2__demetropolize__special_symbol_exp__symbol = new__symbol(cause, str);}
  {char* str = "compile:f2__demetropolize__funkvar_call";       __funk2.compile.f2__demetropolize__funkvar_call__symbol       = new__symbol(cause, str);}
  {char* str = "compile:f2__demetropolize_once";                __funk2.compile.f2__demetropolize_once__symbol                = new__symbol(cause, str);}
  {char* str = "compile:f2__demetropolize_full";                __funk2.compile.f2__demetropolize_full__symbol                = new__symbol(cause, str);}
  {char* str = "compile:raw__compile";                          __funk2.compile.raw__compile__symbol                          = new__symbol(cause, str);}
  
  {char* str = "debug_funk_call";                               __funk2.compile.debug_funk_call__symbol                       = new__symbol(cause, str);}
  
  __funk2.compile.wrong_argument_number__bcs = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "--wrong_argument_number-bcs--"));
  
  f2__primcfunk__init__1(wrong_argument_number__bcs__set, bytecodes);
  f2__primcfunk__init__1(expression__optimize, expression);
}

void f2__compile__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "compile", "", &f2__compile__reinitialize_globalvars, &f2__compile__defragment__fix_pointers);
  
  f2__compile__reinitialize_globalvars();
  
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), __funk2.compile.compile__exception, f2exception__new(cause, __funk2.compile.compile__exception, nil));
  
  __funk2.compile.wrong_argument_number__bcs = nil;
}

