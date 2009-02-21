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

f2ptr __thread__program_counter_reg__symbol;
f2ptr __thread__iter_reg__symbol;
f2ptr __thread__env_reg__symbol;
f2ptr __thread__args_reg__symbol;
f2ptr __thread__return_reg__symbol;
f2ptr __thread__value_reg__symbol;

int bytecode__pop__count                = 0;
int bytecode__push__count               = 0;
int bytecode__copy__count               = 0;
int bytecode__swap__count               = 0;
int bytecode__array__count              = 0;
int bytecode__cons__count               = 0;
int bytecode__car__set__count           = 0;
int bytecode__funk__count               = 0;
int bytecode__jump_funk__count          = 0;
int bytecode__set__count                = 0;
int bytecode__lookup_funkvar__count     = 0;
int bytecode__cdr__set__count           = 0;
int bytecode__array_elt__count          = 0;
int bytecode__else_jump__count          = 0;
int bytecode__car__count                = 0;
int bytecode__cdr__count                = 0;
int bytecode__lookup_type_var__count    = 0;
int bytecode__define_type_var__count    = 0;
int bytecode__type_var__set__count      = 0;
int bytecode__globalize_type_var__count = 0;
int bytecode__jump__count               = 0;
int bytecode__nop__count                = 0;
int bytecode__debug__count              = 0;
int bytecode__trace__count              = 0;
int bytecode__compile__count            = 0;
int bytecode__yield__count              = 0;
int bytecode__newenv__count             = 0;
int bytecode__machine_code__count       = 0;

void print_bytecode_stats__cfunk(FILE* fptr) {
  fprintf(fptr, "\nbytecode__pop__count                = %d", bytecode__pop__count);
  fprintf(fptr, "\nbytecode__push__count               = %d", bytecode__push__count);
  fprintf(fptr, "\nbytecode__copy__count               = %d", bytecode__copy__count);
  fprintf(fptr, "\nbytecode__swap__count               = %d", bytecode__swap__count);
  fprintf(fptr, "\nbytecode__array__count              = %d", bytecode__array__count);
  fprintf(fptr, "\nbytecode__cons__count               = %d", bytecode__cons__count);
  fprintf(fptr, "\nbytecode__car__set__count           = %d", bytecode__car__set__count);
  fprintf(fptr, "\nbytecode__funk__count               = %d", bytecode__funk__count);
  fprintf(fptr, "\nbytecode__jump_funk__count          = %d", bytecode__jump_funk__count);
  fprintf(fptr, "\nbytecode__set__count                = %d", bytecode__set__count);
  fprintf(fptr, "\nbytecode__cdr__set__count           = %d", bytecode__cdr__set__count);
  fprintf(fptr, "\nbytecode__array_elt__count          = %d", bytecode__array_elt__count);
  fprintf(fptr, "\nbytecode__lookup_type_var__count    = %d", bytecode__lookup_type_var__count);
  fprintf(fptr, "\nbytecode__define_type_var__count    = %d", bytecode__define_type_var__count);
  fprintf(fptr, "\nbytecode__else_jump__count          = %d", bytecode__else_jump__count);
  fprintf(fptr, "\nbytecode__car__count                = %d", bytecode__car__count);
  fprintf(fptr, "\nbytecode__cdr__count                = %d", bytecode__cdr__count);
  fprintf(fptr, "\nbytecode__type_var__set__count      = %d", bytecode__type_var__set__count);
  fprintf(fptr, "\nbytecode__globalize_type_var__count = %d", bytecode__globalize_type_var__count);
  fprintf(fptr, "\nbytecode__jump__count               = %d", bytecode__jump__count);
  fprintf(fptr, "\nbytecode__nop__count                = %d", bytecode__nop__count);
  fprintf(fptr, "\nbytecode__debug__count              = %d", bytecode__debug__count);
  fprintf(fptr, "\nbytecode__trace__count              = %d", bytecode__trace__count);
  fprintf(fptr, "\nbytecode__compile__count            = %d", bytecode__compile__count);
  fprintf(fptr, "\nbytecode__yield__count              = %d", bytecode__yield__count);
  fprintf(fptr, "\nbytecode__newenv__count             = %d", bytecode__newenv__count);
  fprintf(fptr, "\nbytecode__machine_code__count       = %d", bytecode__machine_code__count);
}

//f2ptr __thread__execute_bytecode__cause__symbol = -1;

//f2ptr f2thread__execute_bytecode__cause__new(f2ptr cause, f2ptr thread, f2ptr env, f2ptr bytecode) {
//  if (__thread__execute_bytecode__cause__symbol == -1) {error(thread, "__thread__execute_bytecode__cause__symbol is not yet defined.");}
//  return f2__cause__new(cause, nil, nil);//thread, env, __thread__execute_bytecode__cause__symbol, bytecode, nil);
//}

void f2__thread__execute_bytecode(f2ptr cause, f2ptr thread, f2ptr bytecode) {
  debug__assert(raw__threadp(thread, nil), nil, "thread type assertion failed.");
  debug__assert(raw__bytecodep(bytecode, nil), nil, "bytecode type assertion failed.");
  debug__assert((! cause) || raw__causep(cause, nil), nil, "thread type assertion failed.");
  //f2ptr cause = f2thread__execute_bytecode__cause__new(f2thread__cause_reg(thread), thread, f2thread__env(thread), bytecode);
  //f2thread__cause_reg__set(thread, cause, cause);
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__push__symbol)               {f2__thread__bytecode__push(              thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                {f2__thread__bytecode__pop(               thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)               {f2__thread__bytecode__copy(              thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)               {f2__thread__bytecode__swap(              thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array__symbol)              {f2__thread__bytecode__array(             thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)               {f2__thread__bytecode__cons(              thread);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)           {f2__thread__bytecode__car__set(          thread);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)               {f2__thread__bytecode__funk(              thread);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)          {f2__thread__bytecode__jump_funk(         thread);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                {f2__thread__bytecode__set(               thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)           {f2__thread__bytecode__cdr__set(          thread);}
  else if (command == __funk2.bytecode.bytecode__array_elt__symbol)          {f2__thread__bytecode__array_elt(         thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__lookup_type_var__symbol)    {f2__thread__bytecode__lookup_type_var(   thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define_type_var__symbol)    {f2__thread__bytecode__define_type_var(   thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)          {f2__thread__bytecode__else_jump(         thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                {f2__thread__bytecode__car(               thread);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                {f2__thread__bytecode__cdr(               thread);}
  else if (command == __funk2.bytecode.bytecode__type_var__set__symbol)      {f2__thread__bytecode__type_var__set(     thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol) {f2__thread__bytecode__globalize_type_var(thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)               {f2__thread__bytecode__jump(              thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                {f2__thread__bytecode__nop(               thread);}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)              {f2__thread__bytecode__debug(             thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__trace__symbol)              {f2__thread__bytecode__trace(             thread, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)            {f2__thread__bytecode__compile(           thread, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)              {}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)             {f2__thread__bytecode__newenv(            thread);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)       {f2__thread__bytecode__machine_code(      thread, f2bytecode__arg0(bytecode, cause));}
  else {
    f2thread__value__set(thread, cause, f2larva__new(cause, 21));
  }
}

void f2__print_environment_stack(f2ptr cause, f2ptr thread, f2ptr env) {
  pause_gc();
  f2ptr current_env_name__symbol = f2symbol__new(initial_cause(), strlen("-current_env_name-"), (u8*)"-current_env_name-");
  f2ptr env_name = environment__lookup_var_value(initial_cause(), env, current_env_name__symbol);
  resume_gc();
  if (raw__larvap(env_name, cause)) {
    error(nil, "f2__print_environment_stack found larva.");
  }
  
  printf("\nenv name: ");
  f2__write(thread, env_name);
  f2ptr parent_env = f2environment__parent_env(env, cause);
  if (parent_env) {
    f2__print_environment_stack(cause, thread, parent_env);
  }
}

f2ptr __thread__environment_critics__symbol = -1;

bool f2__thread__execute_next_bytecode(f2ptr cause, f2ptr thread) {
  debug__assert(raw__threadp(thread, nil), nil, "thread type assertion failed.");
  debug__assert((! cause) || raw__causep(cause, nil), nil, "thread type assertion failed.");
  
  f2ptr pc_reg = f2thread__program_counter(thread, cause);
  release__assert(pc_reg != nil, nil, "(pc_reg != nil) assertion failure.");
  
  f2ptr bytecode = f2cons__car(pc_reg, cause);
  debug__assert(raw__bytecodep(bytecode, cause), thread, "f2__thread__execute_next_bytecode error: assertion failed (raw__bytecodep(bytecode)).");
  
  bool bytecode_is_yield = 0;
  if (f2bytecode__command(bytecode, cause) == __funk2.bytecode.bytecode__yield__symbol) {
    bytecode_is_yield = 1;
    f2thread__program_counter__set(thread, f2thread__cause_reg(thread, cause), f2cons__cdr(pc_reg, cause));
  } else {
    f2__thread__execute_bytecode(cause, thread, bytecode);
  }
  
  return bytecode_is_yield;
}

void f2__thread__reinitialize_globalvars() {
  f2ptr cause = f2_thread_c__cause__new(initial_cause());
  char* symbol_str;
  
  symbol_str = "thread:program-counter-reg";    __thread__program_counter_reg__symbol     = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:iter-reg";               __thread__iter_reg__symbol                = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:env-reg";                __thread__env_reg__symbol                 = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:args-reg";               __thread__args_reg__symbol                = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:return-reg";             __thread__return_reg__symbol              = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:value-reg";              __thread__value_reg__symbol               = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "thread:-environment_critics-";  __thread__environment_critics__symbol     = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  //symbol_str = "thread:execute_bytecode-cause"; __thread__execute_bytecode__cause__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
}

void f2__thread__initialize() {
  f2__thread__reinitialize_globalvars();
  f2ptr cause = f2_thread_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), __thread__program_counter_reg__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __thread__iter_reg__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __thread__env_reg__symbol,                 nil);
  environment__add_var_value(cause, global_environment(), __thread__args_reg__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __thread__return_reg__symbol,              nil);
  environment__add_var_value(cause, global_environment(), __thread__value_reg__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __thread__environment_critics__symbol,     nil);
  //environment__add_var_value(cause, global_environment(), __thread__execute_bytecode__cause__symbol, nil);
}

