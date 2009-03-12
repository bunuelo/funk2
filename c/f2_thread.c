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

void f2__thread__execute_bytecode(f2ptr cause, f2ptr thread, f2ptr bytecode) {
  debug__assert(raw__threadp(thread, nil), nil, "thread type assertion failed.");
  debug__assert(raw__bytecodep(bytecode, nil), nil, "bytecode type assertion failed.");
  debug__assert((! cause) || raw__causep(cause, nil), nil, "thread type assertion failed.");
  //f2ptr cause = f2thread__execute_bytecode__cause__new(f2thread__cause_reg(thread), thread, f2thread__env(thread), bytecode);
  //f2thread__cause_reg__set(thread, cause, cause);
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__push__symbol)                {f2__thread__bytecode__push(               thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                 {f2__thread__bytecode__pop(                thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)                {f2__thread__bytecode__copy(               thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)                {f2__thread__bytecode__swap(               thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array__symbol)               {f2__thread__bytecode__array(              thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__symbol)      {f2__thread__bytecode__reg_array__elt(     thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__set__symbol) {f2__thread__bytecode__reg_array__elt__set(thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)                {f2__thread__bytecode__cons(               thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)            {f2__thread__bytecode__car__set(           thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)                {f2__thread__bytecode__funk(               thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)           {f2__thread__bytecode__jump_funk(          thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                 {f2__thread__bytecode__set(                thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)            {f2__thread__bytecode__cdr__set(           thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__array_elt__symbol)           {f2__thread__bytecode__array_elt(          thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__lookup_type_var__symbol)     {f2__thread__bytecode__lookup_type_var(    thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define_type_var__symbol)     {f2__thread__bytecode__define_type_var(    thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)           {f2__thread__bytecode__else_jump(          thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                 {f2__thread__bytecode__car(                thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                 {f2__thread__bytecode__cdr(                thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__type_var__set__symbol)       {f2__thread__bytecode__type_var__set(      thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol)  {f2__thread__bytecode__globalize_type_var( thread, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)                {f2__thread__bytecode__jump(               thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                 {f2__thread__bytecode__nop(                thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)               {f2__thread__bytecode__debug(              thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__trace__symbol)               {f2__thread__bytecode__trace(              thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)             {f2__thread__bytecode__compile(            thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)               {}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)              {f2__thread__bytecode__newenv(             thread, bytecode);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)        {f2__thread__bytecode__machine_code(       thread, bytecode, f2bytecode__arg0(bytecode, cause));}
  else {
    f2__print(cause, bytecode);
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

boolean_t f2__thread__execute_next_bytecode(f2ptr cause, f2ptr thread) {
  debug__assert(raw__threadp(thread, nil), nil, "thread type assertion failed.");
  debug__assert((! cause) || raw__causep(cause, nil), nil, "thread type assertion failed.");
  
  f2ptr pc_reg = f2thread__program_counter(thread, cause);
  release__assert(pc_reg != nil, nil, "(pc_reg != nil) assertion failure.");
  
  f2ptr bytecode = f2cons__car(pc_reg, cause);
  debug__assert(raw__bytecodep(bytecode, cause), thread, "f2__thread__execute_next_bytecode error: assertion failed (raw__bytecodep(bytecode)).");
  
  boolean_t bytecode_is_yield = 0;
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
  
  symbol_str = "program_counter";       __thread__program_counter_reg__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "iter";                  __thread__iter_reg__symbol            = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "env";                   __thread__env_reg__symbol             = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "args";                  __thread__args_reg__symbol            = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "return";                __thread__return_reg__symbol          = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "value";                 __thread__value_reg__symbol           = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "-environment_critics-"; __thread__environment_critics__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
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

