// 
// Copyright (c) 2007-2009 Bo Morgan.
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

// to-do: put all of this compiling code into bootstrap code (funk should compile itself because now compiling is too funky between threads [need to keep bytecode equally multifunkable])

f2ptr __compile__exception = -1;

f2ptr __cause__compiled_from__symbol = -1;
f2ptr f2cause__compiled_from__new(f2ptr cause, f2ptr name, f2ptr args) {
  release__assert(__cause__compiled_from__symbol != -1, nil, "cause-compiled_from error: used before symbol defined.");
  return nil;
  //return f2cause__new(cause, nil, nil, __cause__compiled_from__symbol, f2cons__new(cause, name, args));
}

f2ptr check_bcs_valid(f2ptr bytecodes) {
  f2ptr iter = bytecodes;
  while (iter) {
    debug__assert(raw__consp(iter, nil), nil, "bytecodes not cons (should be a list of bytecodes).");
    debug__assert(raw__bytecodep(f2cons__car(iter, nil), nil), nil, "bytecode type is not correct.");
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
f2ptr f2__compile__car(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__symbol,                 nil,    nil,   nil), nil));}
f2ptr f2__compile__car__set(f2ptr cause)                                              {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__car__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__cdr__set(f2ptr cause)                                              {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__cdr__set__symbol,            nil,    nil,   nil), nil));}
f2ptr f2__compile__array_elt(f2ptr cause, f2ptr array, f2ptr index)                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__array_elt__symbol,           array,  index, nil), nil));}
f2ptr f2__compile__set(f2ptr cause, f2ptr reg, f2ptr exp)                             {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__set__symbol,                 reg,    exp,   nil), nil));}
f2ptr f2__compile__value__set(f2ptr cause, f2ptr exp)                                 {return bcs_valid(f2__compile__set(  cause, __thread__value_reg__symbol, exp));}
f2ptr f2__compile__iter__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __thread__iter_reg__symbol, exp));}
f2ptr f2__compile__args__set(f2ptr cause, f2ptr exp)                                  {return bcs_valid(f2__compile__set(  cause, __thread__args_reg__symbol, exp));}
f2ptr f2__compile__env__set(f2ptr cause, f2ptr exp)                                   {return bcs_valid(f2__compile__set(  cause, __thread__env_reg__symbol, exp));}
f2ptr f2__compile__swap(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__swap__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__swap_value_and_iter(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __thread__value_reg__symbol, __thread__iter_reg__symbol));}
f2ptr f2__compile__swap_value_and_args(f2ptr cause)                                   {return bcs_valid(f2__compile__swap( cause, __thread__value_reg__symbol, __thread__args_reg__symbol));}
f2ptr f2__compile__push(f2ptr cause, f2ptr reg)                                       {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__push__symbol, reg, nil, nil),  nil));}
f2ptr f2__compile__push_value(f2ptr cause)                                            {return bcs_valid(f2__compile__push( cause, __thread__value_reg__symbol));}
f2ptr f2__compile__push_iter(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __thread__iter_reg__symbol));}
f2ptr f2__compile__push_args(f2ptr cause)                                             {return bcs_valid(f2__compile__push( cause, __thread__args_reg__symbol));}
f2ptr f2__compile__push_env(f2ptr cause)                                              {return bcs_valid(f2__compile__push( cause, __thread__env_reg__symbol));}
f2ptr f2__compile__push_return(f2ptr cause)                                           {return bcs_valid(f2__compile__push( cause, __thread__return_reg__symbol));}
f2ptr f2__compile__pop(f2ptr cause, f2ptr reg)                                        {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__pop__symbol,  reg, nil, nil), nil));}
f2ptr f2__compile__pop_value(f2ptr cause)                                             {return bcs_valid(f2__compile__pop(  cause, __thread__value_reg__symbol));}
f2ptr f2__compile__pop_iter(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __thread__iter_reg__symbol));}
f2ptr f2__compile__pop_args(f2ptr cause)                                              {return bcs_valid(f2__compile__pop(  cause, __thread__args_reg__symbol));}
f2ptr f2__compile__pop_env(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, __thread__env_reg__symbol));}
f2ptr f2__compile__pop_return(f2ptr cause)                                            {return bcs_valid(f2__compile__pop(  cause, __thread__return_reg__symbol));}
f2ptr f2__compile__pop_nil(f2ptr cause)                                               {return bcs_valid(f2__compile__pop(  cause, nil));}
f2ptr f2__compile__copy(f2ptr cause, f2ptr reg0, f2ptr reg1)                          {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__copy__symbol, reg0, reg1, nil), nil));}
f2ptr f2__compile__copy_value_to_args(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __thread__value_reg__symbol, __thread__args_reg__symbol));}
f2ptr f2__compile__copy_value_to_iter(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __thread__value_reg__symbol, __thread__iter_reg__symbol));}
f2ptr f2__compile__copy_iter_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __thread__iter_reg__symbol, __thread__value_reg__symbol));}
f2ptr f2__compile__copy_iter_to_args(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __thread__iter_reg__symbol, __thread__args_reg__symbol));}
f2ptr f2__compile__copy_args_to_value(f2ptr cause)                                    {return bcs_valid(f2__compile__copy( cause, __thread__args_reg__symbol, __thread__value_reg__symbol));}
f2ptr f2__compile__copy_args_to_iter(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __thread__args_reg__symbol, __thread__iter_reg__symbol));}
f2ptr f2__compile__copy_pc_to_return(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __thread__program_counter_reg__symbol, __thread__return_reg__symbol));}
f2ptr f2__compile__copy_return_to_pc(f2ptr cause)                                     {return bcs_valid(f2__compile__copy( cause, __thread__return_reg__symbol, __thread__program_counter_reg__symbol));}

f2ptr f2__compile__lookup_type_var(f2ptr cause, f2ptr type, f2ptr var)                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__lookup_type_var__symbol, type, var, nil), nil));}
f2ptr f2bytecode__lookup_type_var__type(f2ptr this, f2ptr cause) {return f2bytecode__arg0(this, cause);}
f2ptr f2bytecode__lookup_type_var__var(f2ptr this, f2ptr cause)  {return f2bytecode__arg1(this, cause);}

f2ptr f2__compile__define_type_var(f2ptr cause, f2ptr type, f2ptr var)                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__define_type_var__symbol, type, var, nil), nil));}
f2ptr f2__compile__type_var__set(f2ptr cause, f2ptr type, f2ptr var)                  {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__type_var__set__symbol, type, var, nil), nil));}
f2ptr f2__compile__globalize_type_var(f2ptr cause, f2ptr type, f2ptr var)             {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__globalize_type_var__symbol, type, var, nil), nil));}
f2ptr f2__compile__jump(f2ptr cause, f2ptr new_pc)                                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__else_jump(f2ptr cause, f2ptr new_pc)                               {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__else_jump__symbol, new_pc, nil, nil), nil));}
f2ptr f2__compile__nop(f2ptr cause)                                                   {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__nop__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__return(f2ptr cause)                                                {return bcs_valid(f2__compile__copy( cause, __thread__return_reg__symbol, __thread__program_counter_reg__symbol));}
f2ptr f2__compile__debug(f2ptr cause, f2ptr value)                                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__debug__symbol, value, nil, nil), nil));}
f2ptr f2__compile__trace(f2ptr cause, f2ptr value)                                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__trace__symbol, value, nil, nil), nil));}
f2ptr f2__compile__compile(f2ptr cause, f2ptr protect_environment)                    {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__compile__symbol, protect_environment, nil, nil), nil));}
f2ptr f2__compile__yield(f2ptr cause)                                                 {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__yield__symbol, nil, nil, nil), nil));}
f2ptr f2__compile__newenv(f2ptr cause)                                                {return bcs_valid(f2cons__new(cause, f2bytecode__new(cause, __funk2.bytecode.bytecode__newenv__symbol, nil, nil, nil), nil));}

f2ptr f2__compile__lookup_var(f2ptr cause, f2ptr var)         {return bcs_valid(f2__compile__lookup_type_var(cause, __frame__variable_type__symbol,      var));}
f2ptr f2__compile__lookup_funkvar(f2ptr cause, f2ptr funkvar) {return bcs_valid(f2__compile__lookup_type_var(cause, __frame__funk_variable_type__symbol, funkvar));}

f2ptr f2__compile__define_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__define_type_var(cause, __frame__variable_type__symbol,      var));}
f2ptr f2__compile__define_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__define_type_var(cause, __frame__funk_variable_type__symbol, var));}

f2ptr f2__compile__var__set(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__type_var__set(cause, __frame__variable_type__symbol,      var));}
f2ptr f2__compile__funkvar__set(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__type_var__set(cause, __frame__funk_variable_type__symbol, var));}

f2ptr f2__compile__globalize_var(f2ptr cause, f2ptr var)     {return bcs_valid(f2__compile__globalize_type_var(cause, __frame__variable_type__symbol,      var));}
f2ptr f2__compile__globalize_funkvar(f2ptr cause, f2ptr var) {return bcs_valid(f2__compile__globalize_type_var(cause, __frame__funk_variable_type__symbol, var));}

f2ptr f2__compile__symbol(f2ptr cause, f2ptr exp, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  if (is_locally_funktional) {
    bool exp__is_local_variable = false;
    f2ptr iter = local_variables;
    while (iter) {
      f2ptr local_variable = f2cons__car(iter, cause);
      if (f2__symbol__eq(cause, exp, local_variable)) {
	exp__is_local_variable = true;
	break;
      }
      iter = f2cons__cdr(iter, cause);
    }
    if (! exp__is_local_variable) {
      *is_locally_funktional = false;
    }
  }
  if (is_funktional) {
    *is_funktional = false;
  }
  return bcs_valid(f2__compile__lookup_var(cause, exp));
}

f2ptr f2__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value);

f2ptr __wrong_argument_number__bcs = nil; // this is like an interrupt pointer... (nil causes thread to fail silently [this is a bug])

f2ptr f2__compile__push_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                      f2__compile__push_args( cause); f2ptr iter = full_bcs;
  iter = f2__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  return full_bcs;
}

f2ptr f2__compile__pop_debug_funk_call(f2ptr cause) {
  f2ptr full_bcs =                      f2__compile__pop_nil(cause); f2ptr iter = full_bcs;
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
    if (bytecode__command == __funk2.bytecode.bytecode__lookup_type_var__symbol) {
      f2ptr type = f2bytecode__lookup_type_var__type(bytecode, cause);
      f2ptr var  = f2bytecode__lookup_type_var__var(bytecode, cause);
      if (type == __frame__variable_type__symbol) {
	f2ptr funk__args = f2funk__args(funk, cause);
	bool var_is_funk_arg = 0;
	f2ptr funk_arg_iter = funk__args;
	while(funk_arg_iter) {
	  f2ptr funk_arg = f2cons__car(funk_arg_iter, cause);
	  if (var == funk_arg) {
	    var_is_funk_arg = 1;
	  }
	  funk_arg_iter = f2cons__cdr(funk_arg_iter, cause);
	}
	if (! var_is_funk_arg) {
	  f2ptr var_assignment_cons = environment__lookup_type_var_assignment_cons(cause, f2funk__env(funk, cause), __frame__variable_type__symbol, var);
	  if (raw__consp(var_assignment_cons, cause)) {
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
      } else if (type == __frame__funk_variable_type__symbol) {
	f2ptr funkvar_assignment_cons = environment__lookup_type_var_assignment_cons(cause, f2funk__env(funk, cause), __frame__funk_variable_type__symbol, var);
	if (raw__consp(funkvar_assignment_cons, cause)) {
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

f2ptr __f2__compile__funk__symbol = -1;
f2ptr   f2__compile__funk(f2ptr simple_cause, f2ptr thread, f2ptr funk) {
  release__assert(__f2__compile__funk__symbol != -1, nil, "__f2__compile__funk__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__funk__symbol, f2cons__new(simple_cause, funk, nil));
  
  if (!funk) {error(thread, "\nf2__compile__funk error: funk is nil.");}
  if (!raw__funkp(funk, cause)) {error(thread, "\nf2__compile__funk error: !raw__funkp(funk): funk variable value is not of type funk.");}
  
  f2ptr funk_bcs = f2__compile__value__set(cause, funk);
  if (f2funk__body_bytecodes(funk, cause)) {return bcs_valid(funk_bcs);}
  
  bool  funk__is_funktional         = true;
  f2ptr local_variables             = f2funk__args(funk, cause);
  bool  funk__is_locally_funktional = true;
  
  // save return and environment registers
  f2ptr full_bcs =                                f2__compile__push_return(cause); f2ptr iter = full_bcs;
  iter           = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
  iter           = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause));
  iter           = f2__list_cdr__set(cause, iter, f2__compile__newenv(cause));
  
  // define args in funk environment
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
  f2ptr var_iter = f2funk__args(funk, cause);
  while (var_iter) {
    
    f2ptr var = f2cons__car(var_iter, cause);
    f2ptr cdr = f2cons__cdr(var_iter, cause);
    if (var == __funk2.globalenv.and_rest__symbol) {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__copy_iter_to_value(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, f2cons__car(cdr, cause)));
      var_iter = nil;
      
    } else {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__copy_iter_to_value(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__else_jump(cause, __wrong_argument_number__bcs));
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__car(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, var));
      
      if (cdr) {
	iter = f2__list_cdr__set(cause, iter, f2__compile__cdr(cause));
	iter = f2__list_cdr__set(cause, iter, f2__compile__copy_value_to_iter(cause));
      }
      
      var_iter = cdr;
    }
  }
  
  bool popped_env_and_return     = false;
  bool optimize_unused_beginning = true;
  f2ptr body_bcs = f2__compile__rawcode(cause, thread, f2funk__demetropolized_body(funk, cause), false, true, &popped_env_and_return, &funk__is_funktional, local_variables, &funk__is_locally_funktional, optimize_unused_beginning);
  if (body_bcs && (! raw__consp(body_bcs, cause))) {return body_bcs;}
  
  //body_bcs = f2__compile__funk__optimize_body_bytecodes(cause, bytecode_tracing_on, funk, body_bcs);
  
  iter = f2__list_cdr__set(cause, iter, body_bcs);
  
  if (!popped_env_and_return) {
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
    //printf("\nnot popped_env_and_return!!!!"); fflush(stdout);
  }
  
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_return_to_pc(cause));
  
  f2funk__is_funktional__set(funk, cause, funk__is_locally_funktional ? __funk2.globalenv.true__symbol : nil);
  f2funk__body_bytecodes__set(funk, cause, full_bcs);
  return bcs_valid(funk_bcs);
}

f2ptr __f2__compile__metro__symbol = -1;
f2ptr   f2__compile__metro(f2ptr simple_cause, f2ptr thread, f2ptr metro) {
  release__assert(__f2__compile__metro__symbol != -1, nil, "__f2__compile__metro__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__metro__symbol, f2cons__new(simple_cause, metro, nil));
  
  f2ptr metro_bcs = f2__compile__value__set(cause, metro);
  if (f2metro__body_bytecodes(metro, cause)) {return bcs_valid(metro_bcs);}
  
  bool  metro__is_funktional         = true;
  f2ptr local_variables              = f2metro__args(metro, cause);
  bool  metro__is_locally_funktional = true;
  
  // save return and environment registers
  f2ptr full_bcs =                                f2__compile__push_return(cause); f2ptr iter = full_bcs;
  iter           = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
  iter           = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause));
  iter           = f2__list_cdr__set(cause, iter, f2__compile__newenv(cause));
  
  // define args in metro environment
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause));
  f2ptr var_iter = f2metro__args(metro, cause);
  while (var_iter) {
    
    f2ptr var = f2cons__car(var_iter, cause);
    f2ptr cdr = f2cons__cdr(var_iter, cause);
    if (var == __funk2.globalenv.and_rest__symbol) {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__copy_iter_to_value(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, f2cons__car(cdr, cause)));
      var_iter = nil;
      
    } else {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__car(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, var));
      
      if (cdr) {
	iter = f2__list_cdr__set(cause, iter, f2__compile__cdr(cause));
	iter = f2__list_cdr__set(cause, iter, f2__compile__copy_value_to_iter(cause));
      }
      
      var_iter = cdr;
    }
  }
  
  bool popped_env_and_return     = false;
  bool optimize_unused_beginning = true;
  f2ptr body_bcs = f2__compile__rawcode(cause, thread, f2metro__demetropolized_body(metro, cause), false, true, &popped_env_and_return, &metro__is_funktional, local_variables, &metro__is_locally_funktional, optimize_unused_beginning);
  if (body_bcs && (! raw__consp(body_bcs, cause))) {return body_bcs;}
  iter = f2__list_cdr__set(cause, iter, body_bcs);
  
  if (!popped_env_and_return) {
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
  }
  
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_return_to_pc(cause));
  
  f2metro__is_funktional__set(metro, cause, metro__is_locally_funktional ? __funk2.globalenv.true__symbol : nil);
  f2metro__body_bytecodes__set(metro, cause, full_bcs);
  //f2metro__machine_code__set(metro, cause, f2chunk__new_compiled_from_metro(cause, metro));
  return bcs_valid(metro_bcs);
}

/*
f2ptr f2__compile__funk__backup(f2ptr cause, bool bytecode_tracing_on, f2ptr thread, f2ptr funk) {
  if (!funk) {error(thread, "\nf2__compile__funk error: funk is nil.");}
  f2ptr funk_bcs = f2__compile__value__set(cause, bytecode_tracing_on, funk);
  if (f2funk__body_bytecodes(funk)) {return bcs_valid(funk_bcs);}
  
  // save return and environment registers
  f2ptr full_bcs =              f2__compile__push_return(cause, bytecode_tracing_on); f2ptr iter = full_bcs;  
  
  // define args in funk environment
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_args_to_iter(cause, bytecode_tracing_on));
  f2ptr var_iter = f2funk__args(funk);
  while (var_iter) {
    
    f2ptr var = raw__car(nil, var_iter);
    f2ptr cdr = raw__cdr(nil, var_iter);
    if (var == __and_rest__symbol) {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__copy_iter_to_value(cause, bytecode_tracing_on));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, bytecode_tracing_on, raw__car(nil, cdr)));
      var_iter = nil;
      
    } else {
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__copy_iter_to_value(cause, bytecode_tracing_on));
      iter = f2__list_cdr__set(cause, iter, f2__compile__else_jump(cause, bytecode_tracing_on, __wrong_argument_number__bcs));
      
      iter = f2__list_cdr__set(cause, iter, f2__compile__car(cause, bytecode_tracing_on));
      iter = f2__list_cdr__set(cause, iter, f2__compile__define_var(cause, bytecode_tracing_on, var));
      
      if (cdr) {
	iter = f2__list_cdr__set(cause, iter, f2__compile__cdr(cause, bytecode_tracing_on));
	iter = f2__list_cdr__set(cause, iter, f2__compile__copy_value_to_iter(cause, bytecode_tracing_on));
      }
      
      var_iter = cdr;
    }
  }
  
  iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause, bytecode_tracing_on));
  
  // execute funk body
  f2ptr body_bcs = f2__compile__rawcode(cause, bytecode_tracing_on, thread, f2funk__body(funk), false, true, NULL);
  if (raw__exceptionp(body_bcs)) {return body_bcs;}
  iter = f2__list_cdr__set(cause, iter, body_bcs);
  
  iter = f2__list_cdr__set(cause, iter, f2__compile__copy_return_to_pc(cause, bytecode_tracing_on));
  
  f2funk__body_bytecodes__set(funk, cause, full_bcs);
  return bcs_valid(funk_bcs);
}
*/

// returns last cdr of initial list
f2ptr f2__list_cdr__set(f2ptr cause, f2ptr seq, f2ptr cdr_value) {
  f2ptr iter = seq;
  f2ptr cdr;
  while ((cdr = f2cons__cdr(iter, cause))) {iter = cdr;}
  f2cons__cdr__set(iter, cause, cdr_value);
  return bcs_valid(iter);
}

f2ptr __f2__compile__if__symbol = -1;
f2ptr f2__compile__if(f2ptr simple_cause, f2ptr cond_bcs, f2ptr true_bcs, f2ptr false_bcs) {
  release__assert(__f2__compile__if__symbol != -1, nil, "__f2__compile__if__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__if__symbol, f2list3__new(simple_cause, cond_bcs, true_bcs, false_bcs));
  
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

f2ptr __f2__compile__rawcode__symbol = -1;
f2ptr f2__compile__rawcode(f2ptr simple_cause, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional, bool optimize_unused) {
  release__assert(__f2__compile__rawcode__symbol != -1, nil, "__f2__compile__rawcode__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__rawcode__symbol, exps);
  
  //printf("rawcode: "); f2__write(exps); fflush(stdout);
  if (!exps) {
    return nil;
  }
  release__assert(raw__consp(exps, cause), nil, "exps failed cons type assertion.");
  
  bool protect_subexp_environment     = (f2cons__cdr(exps, cause) != nil) || protect_environment;
  bool optimize_subexp_tail_recursion = (f2cons__cdr(exps, cause) == nil) && optimize_tail_recursion;
  
  f2ptr full_bcs = nil;
  bool  exp__is_funktional = true;
  f2ptr next = nil;
  do {
    f2ptr exp = f2cons__car(exps, cause);
    next      = f2cons__cdr(exps, cause);
    full_bcs = raw__compile(cause, thread, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional);
    if (! exp__is_funktional) {
      if (is_funktional) {
	*is_funktional = false;
      }
    }
    if (optimize_unused && exp__is_funktional && next) {
      status("optimizing funktional beginning of rawcode!");
      //f2__print(cause, exp);
      full_bcs = nil;
      exps     = next;
    }
  } while(optimize_unused && exp__is_funktional && next);
  if (!exps) {
    return full_bcs;
  }
  if (full_bcs && (! raw__consp(full_bcs, cause))) {return full_bcs;}
  exps = f2cons__cdr(exps, cause);
  
  f2ptr iter     = full_bcs;
  while (exps) {
    if (!raw__consp(exps, cause)) {
      return f2__argument_type_check_failure__exception__new(simple_cause, exps);
      //error(nil, "f2__compile__rawcode error: exps is not of type cons.");
    }
    protect_subexp_environment     = (f2cons__cdr(exps, cause) != nil) || protect_environment;
    optimize_subexp_tail_recursion = (f2cons__cdr(exps, cause) == nil) && optimize_tail_recursion;
    
    f2ptr exp_bcs = nil;
    bool  exp__is_funktional = true;
    f2ptr next = nil;
    do {
      f2ptr exp = f2cons__car(exps, cause);
      next      = f2cons__cdr(exps, cause);
      exp_bcs = raw__compile(cause, thread, exp, protect_subexp_environment, optimize_subexp_tail_recursion, popped_env_and_return, &exp__is_funktional, local_variables, is_locally_funktional);
      if (! exp__is_funktional) {
	if (is_funktional) {
	  *is_funktional = false;
	}
      }
      
      if (optimize_unused && exp__is_funktional && next) {
	status("optimizing funktional middle of rawcode!");
	//f2__print(cause, exp);
	exp_bcs = nil;
	exps    = next;
      }
      
    } while(optimize_unused && exp__is_funktional && next);
    if (!exps) {
      return full_bcs;
    }
    if (exp_bcs && (! raw__consp(exp_bcs, cause))) {return exp_bcs;}
    exps = f2cons__cdr(exps, cause);
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  }
  return bcs_valid(full_bcs);
}

f2ptr __f2__compile__if_exp__symbol = -1;
f2ptr f2__compile__if_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__f2__compile__if_exp__symbol != -1, nil, "__f2__compile__if_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__if_exp__symbol, exps);
  
  if (! raw__consp(exps, cause)) {return __compile__exception;}
  exps = f2cons__cdr(exps, cause); // skip |if|
  f2ptr cond_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause); if (!raw__consp(exps, cause)) {return __compile__exception;}
  f2ptr true_exp   = f2cons__car(exps, cause); exps = f2cons__cdr(exps, cause);
  
  f2ptr false_exps = exps;
  if (false_exps && (! raw__consp(false_exps, cause))) {return false_exps;}
  
  f2ptr cond_bcs   = raw__compile(cause, thread, cond_exp, true, false, NULL, is_funktional, local_variables, is_locally_funktional);
  if (cond_bcs && (! raw__consp(cond_bcs, cause))) {return cond_bcs;}
  
  bool true__popped_env_and_return = false;
  f2ptr true_bcs   = raw__compile(cause, thread, true_exp, protect_environment, optimize_tail_recursion, &true__popped_env_and_return, is_funktional, local_variables, is_locally_funktional);
  if (true_bcs && (! raw__consp(true_bcs, cause))) {return true_bcs;}
  
  bool false__popped_env_and_return = false;
  bool optimize_unused_beginning = true;
  f2ptr false_bcs = f2__compile__rawcode(cause, thread, false_exps, protect_environment, optimize_tail_recursion, &false__popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
  if (false_bcs && (! raw__consp(false_bcs, cause))) {return false_bcs;}
  
  if (true__popped_env_and_return || false__popped_env_and_return) {
    *popped_env_and_return = true;
    
    if (!true__popped_env_and_return) {
      // add pop env and pop return to true_bcs
      f2ptr iter;
      {
	f2ptr compile_pop = f2__compile__pop_debug_funk_call(cause);
	if (true_bcs) {
	  iter = f2__list_cdr__set(cause, true_bcs, compile_pop);
	} else {
	  iter = true_bcs = compile_pop;
	}
      }
      iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
    }
    
    if (!false__popped_env_and_return) {
      // add pop env and pop return to false_bcs
      f2ptr iter;
      {
	f2ptr compile_pop = f2__compile__pop_debug_funk_call(cause);
	if (false_bcs) {
	  iter = f2__list_cdr__set(cause, false_bcs, compile_pop);
	} else {
	  iter = false_bcs = compile_pop;
	}
      }
      iter = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
      iter = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
    }
  }
  
  return bcs_valid(f2__compile__if(cause, cond_bcs, true_bcs, false_bcs));
}

f2ptr __f2__compile__lookup_funkvar_exp__symbol = -1;
f2ptr f2__compile__lookup_funkvar_exp(f2ptr simple_cause, f2ptr exps) {
  release__assert(__f2__compile__lookup_funkvar_exp__symbol != -1, nil, "__f2__compile__lookup_funkvar_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__lookup_funkvar_exp__symbol, exps);
  
  return bcs_valid(f2__compile__lookup_funkvar(cause, f2cons__car(f2cons__cdr(exps, cause), cause)));
}

f2ptr __f2__compile__eval_args__symbol = -1;
f2ptr __f2__compile__eval_args__current_arg__symbol = -1;
f2ptr f2__compile__eval_args(f2ptr simple_cause, f2ptr thread, f2ptr args, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__f2__compile__eval_args__symbol              != -1, nil, "__f2__compile__eval_args__symbol not yet defined.");
  release__assert(__f2__compile__eval_args__current_arg__symbol != -1, nil, "__f2__compile__eval_args__current_arg__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__eval_args__symbol, args);
  
  if (! args) {return bcs_valid(f2__compile__args__set(cause, nil));}
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    f2ptr current_arg = f2cons__car(args, cause);
    f2ptr arg_cause = f2cause__compiled_from__new(cause, __f2__compile__eval_args__current_arg__symbol, f2cons__new(cause, current_arg, nil));
    
    exp_bcs     = f2__compile__push_iter(arg_cause);                            iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(arg_cause);                            iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    
    exp_bcs     = raw__compile(arg_cause, thread, current_arg, true, false, NULL, is_funktional, local_variables, is_locally_funktional);
    if (exp_bcs && (! raw__consp(exp_bcs, cause))) {return exp_bcs;}
    iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(arg_cause);                             iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(arg_cause);                             iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__car__set(arg_cause);                             iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    args = f2cons__cdr(args, cause);
    if (args) {
      exp_bcs   = f2__compile__copy_iter_to_value(arg_cause);                   iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cons(arg_cause);                                 iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(arg_cause);                  iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
      exp_bcs   = f2__compile__cdr__set(arg_cause);                             iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
      exp_bcs   = f2__compile__swap_value_and_iter(arg_cause);                  iter = f2__list_cdr__set(arg_cause, iter, exp_bcs);
    }
  }
  return bcs_valid(full_bcs);
}

f2ptr __f2__compile__define_funk_exp__symbol = -1;
f2ptr   f2__compile__define_funk_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__define_funk_exp__symbol != -1, nil, "__f2__compile__define_funk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__define_funk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs          = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr define_funkvar_bcs = f2__compile__define_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, define_funkvar_bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__define_exp__symbol = -1;
f2ptr   f2__compile__define_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__define_exp__symbol != -1, nil, "__f2__compile__define_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__define_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs      = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr define_var_bcs = f2__compile__define_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, define_var_bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__set_exp__symbol = -1;
f2ptr f2__compile__set_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__set_exp__symbol != -1, nil, "__f2__compile__set_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__set_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr var_set__bcs = f2__compile__var__set(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, var_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__setfunk_exp__symbol = -1;
f2ptr f2__compile__setfunk_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__setfunk_exp__symbol != -1, nil, "__f2__compile__setfunk_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__setfunk_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs       = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr funkvar_set__bcs = f2__compile__funkvar__set(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, funkvar_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__globalize_var_exp__symbol = -1;
f2ptr f2__compile__globalize_var_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__globalize_var_exp__symbol != -1, nil, "__f2__compile__globalize_var_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__globalize_var_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr var       = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr var_set__bcs = f2__compile__globalize_var(cause, var);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, var_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__globalize_funkvar_exp__symbol = -1;
f2ptr f2__compile__globalize_funkvar_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__globalize_funkvar_exp__symbol != -1, nil, "__f2__compile__globalize_funkvar_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__globalize_funkvar_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr funkvar   = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! exps) {return __argument_number_check_failure__exception;} f2ptr value_exp = f2cons__car(exps, cause);
  f2ptr value_bcs       = raw__compile(cause, thread, value_exp, true, false, NULL, NULL, nil, NULL);
  if (value_bcs && (! raw__consp(value_bcs, cause))) {return value_bcs;}
  f2ptr funkvar_set__bcs = f2__compile__globalize_funkvar(cause, funkvar);
  
  f2ptr iter = value_bcs;
  iter = f2__list_cdr__set(cause, iter, funkvar_set__bcs);
  return bcs_valid(value_bcs);
}

f2ptr __f2__compile__apply_exp__symbol = -1;
f2ptr f2__compile__apply_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool *popped_env_and_return) {
  release__assert(__f2__compile__apply_exp__symbol != -1, nil, "__f2__compile__apply_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__apply_exp__symbol, exps);
  
  exps = f2cons__cdr(exps, cause); if (! raw__consp(exps, cause)) {return __compile__exception;} f2ptr funk_exp = f2cons__car(exps, cause);
  exps = f2cons__cdr(exps, cause); if (! raw__consp(exps, cause)) {return __compile__exception;} f2ptr args_exp = f2cons__car(exps, cause);
  
  f2ptr full_bcs = raw__compile(cause, thread, funk_exp, true, false, NULL, NULL, nil, NULL);
  if (full_bcs && (! raw__consp(full_bcs, cause))) {
    return full_bcs;
  }
  f2ptr iter = full_bcs;
  
  iter           = f2__list_cdr__set(cause, iter, f2__compile__push_value(cause));
  f2ptr exp_bcs  = raw__compile(cause, thread, args_exp, true, false, NULL, NULL, nil, NULL);
  if (exp_bcs && (! raw__consp(exp_bcs, cause))) {
    return exp_bcs;
  }
  iter           = f2__list_cdr__set(cause, iter, exp_bcs);
  iter           = f2__list_cdr__set(cause, iter, f2__compile__copy_value_to_args(cause));
  iter           = f2__list_cdr__set(cause, iter, f2__compile__pop_value(cause));
  if (optimize_tail_recursion) {
    if (popped_env_and_return != NULL) {
      //printf("\npopped env and return!"); fflush(stdout);
      *popped_env_and_return = true;
    }
    //iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_nil(cause, bytecode_tracing_on));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
  }
  if (protect_environment) {
    iter         = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
  } else {
    //printf("\ntail recursion optimized!"); fflush(stdout);
    //iter         = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause, bytecode_tracing_on));
    //iter         = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause, bytecode_tracing_on));
    iter         = f2__list_cdr__set(cause, iter, f2__compile__jump_funk(cause));
    //iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause, bytecode_tracing_on));
    //iter         = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause, bytecode_tracing_on));
  }
  return bcs_valid(full_bcs);
}

f2ptr raw__apply_funk(f2ptr simple_cause, f2ptr thread, f2ptr funk, f2ptr args);

f2ptr __f2__compile__funkvar_call__symbol = -1;
f2ptr   f2__compile__funkvar_call(f2ptr simple_cause, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__f2__compile__funkvar_call__symbol != -1, nil, "__f2__compile__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__funkvar_call__symbol, exps);
  
  f2ptr funkvar = f2cons__car(exps, cause);
  f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2thread__env(thread, cause), funkvar);
  if (raw__metrocfunkp(funkvar_value, cause)) {
    return bcs_valid(raw__compile(cause, thread, f2__metrocfunk__apply(cause, funkvar_value, thread, f2cons__cdr(exps, cause)), true, false, NULL, is_funktional, local_variables, is_locally_funktional));
  } else {
    if ((! (raw__cfunkp(funkvar_value, cause) ||
	    raw__funkp(funkvar_value, cause))) ||
	(! raw__funkable__is_funktional(cause, funkvar_value))) {
      if (is_funktional) {
	*is_funktional = false;
      }
      if (is_locally_funktional) {
	*is_locally_funktional = false;
      }
    }
    f2ptr full_bcs = f2__compile__eval_args(cause, thread, f2cons__cdr(exps, cause), is_funktional, local_variables, is_locally_funktional); f2ptr iter = full_bcs;
    bool all_args_are_immutable = true;
    if (is_funktional && (*is_funktional)) {
      f2ptr arg_iter = f2cons__cdr(exps, cause);
      while (arg_iter) {
	f2ptr arg = f2cons__car(arg_iter, cause);
	if (! raw__exp__is_immutable(cause, arg)) {
	  all_args_are_immutable = false;
	  break;
	}
	arg_iter = f2cons__cdr(arg_iter, cause);
      }
    }
    if (is_funktional && (*is_funktional) && all_args_are_immutable) {
      status("found funktional optimization opportunity!");
      f2ptr funk_apply__result = raw__apply_funk(cause, thread, funkvar_value, f2cons__cdr(exps, cause));
      full_bcs = f2__compile__value__set(cause, funk_apply__result); iter = full_bcs;
    } else {
      iter     = f2__list_cdr__set(cause, iter, f2__compile__lookup_funkvar(cause, funkvar));
      if (optimize_tail_recursion) {
	if (popped_env_and_return) {
	  //printf("\npopped env and return!"); fflush(stdout);
	  *popped_env_and_return = true;
	}
	iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
      }
      if (protect_environment) {
	iter   = f2__list_cdr__set(cause, iter, f2__compile__push_return(cause));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__push_env(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__push_debug_funk_call(cause, bytecode_tracing_on));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__funk_bc(cause));
	//iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_debug_funk_call(cause, bytecode_tracing_on));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_env(cause));
	iter   = f2__list_cdr__set(cause, iter, f2__compile__pop_return(cause));
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
  error(nil, "shouldn't get here.");
  return f2larva__new(cause, 16);
}

int __total_apply_metro_count = 0;

f2ptr __raw__apply_metro__symbol = -1;
f2ptr raw__apply_metro(f2ptr simple_cause, f2ptr thread, f2ptr metro, f2ptr args) {
  release__assert(__raw__apply_metro__symbol != -1, nil, "__raw__apply_metro__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __raw__apply_metro__symbol, f2list2__new(simple_cause, metro, args));
  
#ifdef DEBUG_COMPILE
  __total_apply_metro_count ++;
  if ((__total_apply_metro_count % 1000) == 0) {
    printf("\ntotal apply metro count = %d", __total_apply_metro_count);
  }
  //printf ("\nstarting apply metro."); fflush(stdout);
#endif // DEBUG_COMPILE
  
  //printf ("\nThread 0x%X creating child compile thread.", (uint)thread); fflush(stdout);
  f2ptr new_thread = f2__thread_serial(cause, thread, f2thread__env(thread, cause), metro, args);
  
  //f2thread__keep_undead__set(new_thread, cause, __true__symbol);
  //printf ("\nCompile thread created: 0x%X", (uint)new_thread); fflush(stdout);
  f2__scheduler__complete_thread(cause, new_thread);
  
  f2ptr value = f2thread__value(new_thread, cause);
  f2thread__keep_undead__set(new_thread, cause, nil);
  
  //printf ("\ncompleted apply metro: "); f2__write(thread, value); fflush(stdout);
  
  return value;
}

int __total_apply_funk_count = 0;

f2ptr __raw__apply_funk__symbol = -1;
f2ptr raw__apply_funk(f2ptr simple_cause, f2ptr thread, f2ptr funk, f2ptr args) {
  release__assert(__raw__apply_funk__symbol != -1, nil, "__raw__apply_funk__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __raw__apply_funk__symbol, f2list2__new(simple_cause, funk, args));
  
#ifdef DEBUG_COMPILE
  __total_apply_funk_count ++;
  if ((__total_apply_funk_count % 1000) == 0) {
    printf("\ntotal apply funk count = %d", __total_apply_funk_count);
  }
  //printf ("\nstarting apply funk."); fflush(stdout);
#endif // DEBUG_COMPILE
  
  //printf ("\nThread 0x%X creating child compile thread.", (uint)thread); fflush(stdout);
  f2ptr new_thread = f2__thread_serial(cause, thread, f2thread__env(thread, cause), funk, args);
  
  //f2thread__keep_undead__set(new_thread, cause, __true__symbol);
  //printf ("\nCompile thread created: 0x%X", (uint)new_thread); fflush(stdout);
  f2__scheduler__complete_thread(cause, new_thread);
  
  f2ptr value = f2thread__value(new_thread, cause);
  f2thread__keep_undead__set(new_thread, cause, nil);
  
  //printf ("\ncompleted apply funk: "); f2__write(thread, value); fflush(stdout);
  
  return value;
}

f2ptr __f2__compile__backquote_exp__symbol = -1;
f2ptr f2__compile__backquote_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__backquote_exp__symbol != -1, nil, "__f2__compile__backquote_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__backquote_exp__symbol, exps);
  
  f2ptr args = f2cons__cdr(exps, cause);
  if (! args) {return bcs_valid(f2__compile__value__set(cause, nil));}
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = raw__compile(cause, thread, f2cons__car(args, cause), true, false, NULL, NULL, nil, NULL);
    if(exp_bcs && (! raw__consp(exp_bcs, cause))) {return exp_bcs;}
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

f2ptr __f2__compile__backquote_append_exp__symbol = -1;
f2ptr f2__compile__backquote_append_exp(f2ptr simple_cause, f2ptr thread, f2ptr exps) {
  release__assert(__f2__compile__backquote_append_exp__symbol != -1, nil, "__f2__compile__backquote_append_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__backquote_append_exp__symbol, exps);
  
  f2ptr args = f2cons__cdr(exps, cause);
  if (! args) {return bcs_valid(f2__compile__value__set(cause, nil));}
  f2ptr cdr = f2cons__cdr(args, cause);
  f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  while (args) {
    exp_bcs     = f2__compile__push_iter(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__push_args(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = raw__compile(cause, thread, f2cons__car(args, cause), true, false, NULL, NULL, nil, NULL);
    if(exp_bcs && (! raw__consp(exp_bcs, cause))) {return exp_bcs;}
    iter = f2__list_cdr__set(cause, iter, exp_bcs);
    
    exp_bcs     = f2__compile__pop_args(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
    exp_bcs     = f2__compile__pop_iter(cause);                             iter = f2__list_cdr__set(cause, iter, exp_bcs);
    if (cdr) {
      exp_bcs   = f2__compile__car__set(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    } else {
      exp_bcs   = f2__compile__cdr__set(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
    }

    args = f2cons__cdr(args, cause);
    if (args) {
      cdr = f2cons__cdr(args, cause);
      if (cdr) {
	exp_bcs = f2__compile__copy_iter_to_value(cause);                   iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cons(cause);                                 iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause);                  iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__cdr__set(cause);                              iter = f2__list_cdr__set(cause, iter, exp_bcs);
	exp_bcs = f2__compile__swap_value_and_iter(cause);                  iter = f2__list_cdr__set(cause, iter, exp_bcs);
      }
    }
  }
  
  exp_bcs       = f2__compile__copy_args_to_value(cause);                   iter = f2__list_cdr__set(cause, iter, exp_bcs);
  return bcs_valid(full_bcs);
}

f2ptr f2__is_compile_special_symbol(f2ptr exp) {
  return ((exp == __funk2.globalenv.quote__symbol)                  ||
	  (exp == __funk2.globalenv.backquote__list__symbol)        ||
	  (exp == __funk2.globalenv.backquote__list_append__symbol) ||
	  (exp == __funk2.globalenv.if__symbol)                     ||
	  (exp == __funk2.globalenv.apply__symbol)                  ||
	  (exp == __funk2.globalenv.funkvar__symbol)                ||
	  (exp == __funk2.globalenv.define_funk__symbol)            ||
	  (exp == __funk2.globalenv.define__symbol)                 ||
	  (exp == __funk2.globalenv.setfunk__symbol)                ||
	  (exp == __funk2.globalenv.set__symbol)                    ||
	  (exp == __funk2.globalenv.globalize__symbol)              ||
	  (exp == __funk2.globalenv.globalize_funk__symbol)         ||
	  (exp == __funk2.globalenv.yield__symbol)                  ||
	  (exp == __funk2.globalenv.bytecode__symbol)               ||
	  (exp == __funk2.globalenv.rawcode__symbol));
}

f2ptr __f2__compile__special_symbol_exp__symbol = -1;
f2ptr f2__compile__special_symbol_exp(f2ptr simple_cause, f2ptr thread, f2ptr exp, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__f2__compile__special_symbol_exp__symbol != -1, nil, "__f2__compile__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__special_symbol_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  if (car == __funk2.globalenv.quote__symbol)                                                                                                                            {return bcs_valid(f2__compile__value__set(cause, f2cons__car(f2cons__cdr(exp, cause), cause)));}
  if (car == __funk2.globalenv.backquote__list__symbol)        {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__backquote_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.backquote__list_append__symbol) {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__backquote_append_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.if__symbol)                                                                                                                               {return bcs_valid(f2__compile__if_exp(cause, thread, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (car == __funk2.globalenv.apply__symbol)                  {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__apply_exp(cause, thread, exp, protect_environment, optimize_tail_recursion, popped_env_and_return));}
  if (car == __funk2.globalenv.funkvar__symbol)                {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__lookup_funkvar_exp(cause, exp));}
  if (car == __funk2.globalenv.define_funk__symbol)            {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__define_funk_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.define__symbol)                 {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__define_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.setfunk__symbol)                {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__setfunk_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.set__symbol)                    {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__set_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.globalize__symbol)              {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__globalize_var_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.globalize_funk__symbol)         {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__globalize_funkvar_exp(cause, thread, exp));}
  if (car == __funk2.globalenv.yield__symbol)                  {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__yield(cause));}
  if (car == __funk2.globalenv.bytecode__symbol)               {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__bytecode_exp(cause, exp));}
  if (car == __funk2.globalenv.rawcode__symbol)                {if (is_funktional) {*is_funktional = false;} if (is_locally_funktional) {*is_locally_funktional = false;} return bcs_valid(f2__compile__rawcode_exp(cause, exp, thread, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  printf("tried to compile special symbol exp: "); f2__write(cause, exp); fflush(stdout);
  printf("isn't a special symbol expression."); // should throw exception...
  error(nil, "f2__compile__special_symbol_exp error: expression is not special symbol expression.");
}

f2ptr __f2__demetropolize__funkvar_call__symbol = -1;
f2ptr f2__demetropolize__funkvar_call(f2ptr simple_cause, f2ptr thread, f2ptr env, f2ptr exp) {
  release__assert(__f2__demetropolize__funkvar_call__symbol != -1, nil, "__f2__demetropolize__funkvar_call__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__demetropolize__funkvar_call__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr did_something = nil;
  f2ptr args = f2cons__cdr(exp, cause);
  if (!args) {return f2cons__new(cause, nil, exp);}
  f2ptr demetro_exp  = f2cons__new(cause, f2cons__car(exp, cause), nil);
  f2ptr iter         = args;
  f2ptr demetro_iter = demetro_exp;
  while(iter) {
    f2ptr arg                 = f2cons__car(iter, cause);
    
    f2ptr demetro_arg__values = f2__demetropolize_once(cause, thread, env, arg);
    if(f2cons__car(demetro_arg__values, cause)) {did_something = __funk2.globalenv.true__symbol;}
    f2ptr demetro_arg         = f2cons__cdr(demetro_arg__values, cause);
    
    f2ptr demetro_iter_next   = f2cons__new(cause, demetro_arg, nil);
    
    f2cons__cdr__set(demetro_iter, cause, demetro_iter_next);
    
    demetro_iter = demetro_iter_next;
    iter         = f2cons__cdr(iter, cause);
  }
  return f2cons__new(cause, did_something, demetro_exp);
}

f2ptr __f2__compile__cons_exp__symbol = -1;
f2ptr f2__compile__cons_exp(f2ptr simple_cause, f2ptr thread, f2ptr exp, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__f2__compile__cons_exp__symbol != -1, nil, "__f2__compile__cons_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__compile__cons_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2thread__env(thread, cause), car);
  if (raw__metrop(funkvar_value, cause))    {return bcs_valid(raw__compile(cause, thread, raw__apply_metro(cause, thread, funkvar_value, f2cons__cdr(exp, cause)), true, false, NULL, is_funktional, local_variables, is_locally_funktional));}
  if (f2__is_compile_special_symbol(car))   {return bcs_valid(f2__compile__special_symbol_exp(cause, thread, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  if (raw__symbolp(car, cause))             {return bcs_valid(f2__compile__funkvar_call(cause, thread, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional));}
  printf("tried to compile: "); f2__write(cause, exp); fflush(stdout);
  printf("don't know how to compile type."); // should throw exception... (or return larva)
  return funkvar_value;
}

f2ptr f2__compile__bytecode_exp(f2ptr cause, f2ptr exp) {
  if (! raw__consp(exp, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr exp_iter = f2cons__cdr(exp, cause);
  if (! raw__consp(exp_iter, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr command = f2cons__car(exp_iter, cause);
  if (! raw__symbolp(command, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr args    = f2cons__cdr(exp_iter, cause);
  if (! raw__consp(args, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr arg0     = f2cons__car(args, cause);
  f2ptr cdr_args = f2cons__cdr(args, cause);
  if (! raw__consp(cdr_args, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr arg1      = f2cons__car(cdr_args, cause);
  f2ptr cddr_args = f2cons__cdr(cdr_args, cause);
  if (! raw__consp(cddr_args, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr arg2 = f2cons__car(cddr_args, cause);
  return f2cons__new(cause, f2bytecode__new(cause, command, arg0, arg1, arg2), nil);
}

f2ptr f2__compile__rawcode_exp(f2ptr cause, f2ptr exp, f2ptr thread, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  if (! raw__consp(exp, cause)) {
    return f2larva__new(cause, 1);
  }
  f2ptr exps = f2cons__cdr(exp, cause);
  if (! raw__consp(exps, cause)) {
    return f2larva__new(cause, 1);
  }
  //f2ptr f2__compile__rawcode(f2ptr simple_cause, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  bool optimize_unused_beginning = false;
  return f2__compile__rawcode(cause, thread, exps, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional, optimize_unused_beginning);
}

f2ptr __f2__demetropolize__special_symbol_exp__symbol = -1;
f2ptr   f2__demetropolize__special_symbol_exp(f2ptr simple_cause, f2ptr thread, f2ptr env, f2ptr exp) {
  release__assert(__f2__demetropolize__special_symbol_exp__symbol != -1, nil, "__f2__demetropolize__special_symbol_exp__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__demetropolize__special_symbol_exp__symbol, f2cons__new(simple_cause, exp, nil));
  
  f2ptr car = f2cons__car(exp, cause);
  if (car == __funk2.globalenv.quote__symbol)                  {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.backquote__list__symbol)        {return f2__demetropolize__funkvar_call(cause, thread, env, exp);}
  if (car == __funk2.globalenv.backquote__list_append__symbol) {return f2__demetropolize__funkvar_call(cause, thread, env, exp);}
  if (car == __funk2.globalenv.if__symbol)                     {return f2__demetropolize__funkvar_call(cause, thread, env, exp);}
  if (car == __funk2.globalenv.apply__symbol)                  {return f2__demetropolize__funkvar_call(cause, thread, env, exp);}
  if (car == __funk2.globalenv.funkvar__symbol)                {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.define_funk__symbol)            {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.define__symbol)                 {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.setfunk__symbol)                {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.set__symbol)                    {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.globalize__symbol)              {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.globalize_funk__symbol)         {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.yield__symbol)                  {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.bytecode__symbol)               {return f2cons__new(cause, nil, exp);}
  if (car == __funk2.globalenv.rawcode__symbol)                {return f2cons__new(cause, nil, exp);}
  printf("tried to compile special symbol exp: "); f2__write(cause, exp); fflush(stdout);
  printf("isn't a special symbol expression."); // should throw exception...
  error(nil, "f2__demetropolize__special_symbol_exp error: expression is not special symbol expression.");
}

f2ptr __f2__demetropolize_once__symbol = -1;
f2ptr   f2__demetropolize_once(f2ptr simple_cause, f2ptr thread, f2ptr env, f2ptr exp) {
  release__assert(__f2__demetropolize_once__symbol != -1, nil, "__f2__demetropolize_once__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__demetropolize_once__symbol, f2cons__new(simple_cause, exp, nil));
  if (raw__consp(exp, cause)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2thread__env(thread, cause), car);
      if      (raw__metrop(funkvar_value, cause))  {values = f2cons__new(simple_cause, __funk2.globalenv.true__symbol, raw__apply_metro(simple_cause, thread, funkvar_value, f2cons__cdr(exp, cause)));}
      else if (f2__is_compile_special_symbol(car)) {values = f2__demetropolize__special_symbol_exp(simple_cause, thread, env, exp);}
      else if (raw__symbolp(car, cause))           {values = f2__demetropolize__funkvar_call(simple_cause, thread, env, exp);}
      else                                         {values = f2cons__new(simple_cause, nil, exp);}
    }
    
    f2ptr did_something = nil;
    if(f2cons__car(values, cause)) {did_something = __funk2.globalenv.true__symbol;}
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      return f2cons__new(cause, __funk2.globalenv.true__symbol, retval);
      //return f2cons__new(cause, __true__symbol, raw__cdr(cause, f2__demetropolize(cause, thread, env, retval)));
    } else {
      return f2cons__new(cause, nil, exp);
    }
  }
  return f2cons__new(cause, nil, exp);
}

f2ptr __f2__demetropolize_full__symbol = -1;
f2ptr   f2__demetropolize_full__with_status(f2ptr simple_cause, f2ptr thread, f2ptr env, f2ptr exp) {
  release__assert(__f2__demetropolize_full__symbol != -1, nil, "__f2__demetropolize_full__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __f2__demetropolize_full__symbol, f2cons__new(simple_cause, exp, nil));
  if (raw__consp(exp, cause)) {
    f2ptr values = nil;
    {
      f2ptr car = f2cons__car(exp, cause);
      f2ptr funkvar_value = environment__lookup_funkvar_value(cause, f2thread__env(thread, cause), car);
      if      (raw__metrop(funkvar_value, cause))  {values = f2cons__new(simple_cause, __funk2.globalenv.true__symbol, raw__apply_metro(simple_cause, thread, funkvar_value, f2cons__cdr(exp, cause)));}
      else if (f2__is_compile_special_symbol(car)) {values = f2__demetropolize__special_symbol_exp(simple_cause, thread, env, exp);}
      else if (raw__symbolp(car, cause))           {values = f2__demetropolize__funkvar_call(simple_cause, thread, env, exp);}
      else                                         {values = f2cons__new(simple_cause, nil, exp);}
    }
    
    f2ptr did_something = nil;
    if(f2cons__car(values, cause)) {did_something = __funk2.globalenv.true__symbol;}
    f2ptr retval = f2cons__cdr(values, cause);
    if (did_something) {
      return f2cons__new(cause, __funk2.globalenv.true__symbol, f2cons__cdr(f2__demetropolize_full__with_status(cause, thread, env, retval), cause));
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

f2ptr __raw__compile__symbol = -1;
f2ptr   raw__compile(f2ptr simple_cause, f2ptr thread, f2ptr exp, bool protect_environment, bool optimize_tail_recursion, bool *popped_env_and_return, bool* is_funktional, f2ptr local_variables, bool* is_locally_funktional) {
  release__assert(__raw__compile__symbol != -1, nil, "__raw__compile__symbol not yet defined.");
  f2ptr cause = f2cause__compiled_from__new(simple_cause, __raw__compile__symbol, f2cons__new(simple_cause, exp, nil));
#ifdef DEBUG_COMPILE
  if (__compile__recursion_count == 0) {enter_compile_debug();}
  __total_compile_count ++;
  if ((__total_compile_count % 1000) == 0) {
    printf("\ntotal compile count = %d", __total_compile_count);
  }
  __compile__recursion_count ++;
#endif // DEBUG_COMPILE
  pause_gc();
  f2ptr result_bcs = nil;
  if      (!exp)                        {result_bcs = f2__compile__value__set(cause, nil);}
  else if (raw__integerp(exp, cause))   {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__pointerp(exp, cause))   {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__doublep(exp, cause))    {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__gfunkptrp(exp, cause))  {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__stringp(exp, cause))    {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__symbolp(exp, cause))    {result_bcs = f2__compile__symbol(    cause, exp, is_funktional, local_variables, is_locally_funktional);}
  else if (raw__consp(exp, cause))      {result_bcs = f2__compile__cons_exp(  cause, thread, exp, protect_environment, optimize_tail_recursion, popped_env_and_return, is_funktional, local_variables, is_locally_funktional);}
  else if (raw__arrayp(exp, cause))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__cfunkp(exp, cause))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__funkp(exp, cause))      {result_bcs = f2__compile__funk(      cause, thread, exp);}
  else if (raw__metrop(exp, cause))     {result_bcs = f2__compile__metro(     cause, thread, exp);}
  else if (raw__exceptionp(exp, cause)) {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__bytecodep(exp, cause))  {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__larvap(exp, cause))     {result_bcs = f2__compile__value__set(cause, exp);}
  else if (raw__charp(exp, cause))      {result_bcs = f2__compile__value__set(cause, exp);}
  else {
    error(nil, "unrecognized type in compile.");
  }
  result_bcs = bcs_valid(result_bcs);
  resume_gc();
  __compile__recursion_count --;
#ifdef DEBUG_COMPILE
  if (__compile__recursion_count == 0) {
    //printf("\ncompile ending.");
  }
#endif // DEBUG_COMPILE
  return result_bcs;
}

void f2__compile__reinitialize_globalvars() {
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  {char* str = "compile:cause-compiled_from"; __cause__compiled_from__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:exception";           __compile__exception           = f2symbol__new(cause, strlen(str), (u8*)str);}
  
  {char* str = "compile:f2__compile__funk";                     __f2__compile__funk__symbol                     = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__metro";                    __f2__compile__metro__symbol                    = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__if";                       __f2__compile__if__symbol                       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__rawcode";                  __f2__compile__rawcode__symbol                  = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__if_exp";                   __f2__compile__if_exp__symbol                   = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__lookup_funkvar_exp";       __f2__compile__lookup_funkvar_exp__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__eval_args";                __f2__compile__eval_args__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__eval_args__current_arg";   __f2__compile__eval_args__current_arg__symbol   = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__define_funk_exp";          __f2__compile__define_funk_exp__symbol          = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__define_exp";               __f2__compile__define_exp__symbol               = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__set_exp";                  __f2__compile__set_exp__symbol                  = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__setfunk_exp";              __f2__compile__setfunk_exp__symbol              = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__globalize_var_exp";        __f2__compile__globalize_var_exp__symbol        = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__globalize_funkvar_exp";    __f2__compile__globalize_funkvar_exp__symbol    = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__apply_exp";                __f2__compile__apply_exp__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__funkvar_call";             __f2__compile__funkvar_call__symbol             = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__apply_metro";                      __raw__apply_metro__symbol                      = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__apply_funk";                       __raw__apply_funk__symbol                       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__backquote_exp";            __f2__compile__backquote_exp__symbol            = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__backquote_append_exp";     __f2__compile__backquote_append_exp__symbol     = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__special_symbol_exp";       __f2__compile__special_symbol_exp__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__compile__cons_exp";                 __f2__compile__cons_exp__symbol                 = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize__special_symbol_exp"; __f2__demetropolize__special_symbol_exp__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  //{char* str = "compile:f2__demetropolize__cons_exp";           __f2__demetropolize__cons_exp__symbol           = f2symbol__new(cause, strlen(str), str);}
  {char* str = "compile:f2__demetropolize__funkvar_call";       __f2__demetropolize__funkvar_call__symbol       = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize_once";                __f2__demetropolize_once__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:f2__demetropolize_full";                __f2__demetropolize_full__symbol                = f2symbol__new(cause, strlen(str), (u8*)str);}
  {char* str = "compile:raw__compile";                          __raw__compile__symbol                          = f2symbol__new(cause, strlen(str), (u8*)str);}
}

void f2__compile__initialize() {
  f2__compile__reinitialize_globalvars();
  
  f2ptr cause = f2_compile_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), __cause__compiled_from__symbol, nil);
  environment__add_var_value(cause, global_environment(), __compile__exception, f2exception__new(cause, __compile__exception, nil));
  
  environment__add_var_value(cause, global_environment(), __f2__compile__funk__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__metro__symbol,                    nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__if__symbol,                       nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__rawcode__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__if_exp__symbol,                   nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__lookup_funkvar_exp__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__eval_args__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__eval_args__current_arg__symbol,   nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__define_funk_exp__symbol,          nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__define_exp__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__set_exp__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__setfunk_exp__symbol,              nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__globalize_var_exp__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__globalize_funkvar_exp__symbol,    nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__apply_exp__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__funkvar_call__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __raw__apply_metro__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __raw__apply_funk__symbol,                       nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__backquote_exp__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__backquote_append_exp__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__special_symbol_exp__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __f2__compile__cons_exp__symbol,                 nil);
  environment__add_var_value(cause, global_environment(), __f2__demetropolize__special_symbol_exp__symbol, nil);
  //environment__add_var_value(cause, global_environment(), __f2__demetropolize__cons_exp__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __f2__demetropolize__funkvar_call__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __f2__demetropolize_once__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __f2__demetropolize_full__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __raw__compile__symbol,                          nil);
}

