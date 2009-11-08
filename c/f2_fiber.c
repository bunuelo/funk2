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

f2ptr __fiber__program_counter_reg__symbol;
f2ptr __fiber__iter_reg__symbol;
f2ptr __fiber__env_reg__symbol;
f2ptr __fiber__args_reg__symbol;
f2ptr __fiber__return_reg__symbol;
f2ptr __fiber__value_reg__symbol;

boolean_t f2__fiber__execute_bytecode(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  debug__assert(raw__fiber__is_type(nil, fiber), nil, "fiber type assertion failed.");
  debug__assert(raw__bytecode__is_type(nil, bytecode), nil, "bytecode type assertion failed.");
  debug__assert((! cause) || raw__cause__is_type(nil, cause), nil, "fiber type assertion failed.");
  //f2ptr cause = f2fiber__execute_bytecode__cause__new(f2fiber__cause_reg(fiber), fiber, f2fiber__env(fiber), bytecode);
  //f2fiber__cause_reg__set(fiber, cause, cause);
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__push__symbol)                {f2__fiber__bytecode__push(               fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                 {f2__fiber__bytecode__pop(                fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)                {f2__fiber__bytecode__copy(               fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)                {f2__fiber__bytecode__swap(               fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array__symbol)               {f2__fiber__bytecode__array(              fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__symbol)      {f2__fiber__bytecode__reg_array__elt(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__set__symbol) {f2__fiber__bytecode__reg_array__elt__set(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)                {f2__fiber__bytecode__cons(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__consp__symbol)               {f2__fiber__bytecode__consp(              fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)            {f2__fiber__bytecode__car__set(           fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)                {f2__fiber__bytecode__funk(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)           {f2__fiber__bytecode__jump_funk(          fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                 {f2__fiber__bytecode__set(                fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)            {f2__fiber__bytecode__cdr__set(           fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__array_elt__symbol)           {f2__fiber__bytecode__array_elt(          fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__lookup_type_var__symbol)     {f2__fiber__bytecode__lookup_type_var(    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define_type_var__symbol)     {f2__fiber__bytecode__define_type_var(    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__if_jump__symbol)             {f2__fiber__bytecode__if_jump(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)           {f2__fiber__bytecode__else_jump(          fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                 {f2__fiber__bytecode__car(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                 {f2__fiber__bytecode__cdr(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__type_var__mutate__symbol)    {f2__fiber__bytecode__type_var__mutate(   fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol)  {f2__fiber__bytecode__globalize_type_var( fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)                {f2__fiber__bytecode__jump(               fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                 {f2__fiber__bytecode__nop(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)               {f2__fiber__bytecode__debug(              fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__tracer__symbol)              {f2__fiber__bytecode__tracer(             fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__endfunk__symbol)             {f2__fiber__bytecode__endfunk(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)             {f2__fiber__bytecode__compile(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)               {f2__fiber__bytecode__yield(              fiber, bytecode); return boolean__true;}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)              {f2__fiber__bytecode__newenv(             fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)        {f2__fiber__bytecode__machine_code(       fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else {
    f2__print(cause, fiber, bytecode);
    f2fiber__value__set(fiber, cause, f2larva__new(cause, 21));
  }
  return boolean__false;
}

void f2__print_environment_stack(f2ptr cause, f2ptr fiber, f2ptr env) {
  f2ptr current_env_name__symbol = f2symbol__new(initial_cause(), strlen("-current_env_name-"), (u8*)"-current_env_name-");
  f2ptr env_name = environment__lookup_var_value(initial_cause(), env, current_env_name__symbol);
  if (raw__larva__is_type(cause, env_name)) {
    error(nil, "f2__print_environment_stack found larva.");
  }
  
  printf("\nenv name: ");
  f2__write(cause, fiber, env_name);
  f2ptr parent_env = f2environment__parent_env(env, cause);
  if (parent_env) {
    f2__print_environment_stack(cause, fiber, parent_env);
  }
}

f2ptr __fiber__environment_critics__symbol = -1;

boolean_t f2__fiber__execute_next_bytecode(f2ptr cause, f2ptr fiber) {
  boolean_t bytecode_is_yield = boolean__false;
  pause_gc();
  {  
    debug__assert(raw__fiber__is_type(nil, fiber), nil, "fiber type assertion failed.");
    debug__assert((! cause) || raw__cause__is_type(nil, cause), nil, "fiber type assertion failed.");
    
    f2ptr pc_reg = f2fiber__program_counter(fiber, cause);
    debug__assert(pc_reg != nil, nil, "(pc_reg != nil) assertion failure.");
    
    f2ptr bytecode = f2cons__car(pc_reg, cause);
    debug__assert(raw__bytecode__is_type(cause, bytecode), fiber, "f2__fiber__execute_next_bytecode error: assertion failed (raw__bytecode__is_type(bytecode)).");
    
    bytecode_is_yield = f2__fiber__execute_bytecode(cause, fiber, bytecode);
  }
  resume_gc();
  return bytecode_is_yield;
}

void f2__fiber__reinitialize_globalvars() {
  f2ptr cause = f2_fiber_c__cause__new(initial_cause());
  char* symbol_str;
  
  symbol_str = "program_counter";       __fiber__program_counter_reg__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "iter";                  __fiber__iter_reg__symbol            = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "env";                   __fiber__env_reg__symbol             = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "args";                  __fiber__args_reg__symbol            = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "return";                __fiber__return_reg__symbol          = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "value";                 __fiber__value_reg__symbol           = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "-environment_critics-"; __fiber__environment_critics__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
}

void f2__fiber__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "fiber", "", &f2__fiber__reinitialize_globalvars);
  
  f2__fiber__reinitialize_globalvars();
  f2ptr cause = f2_fiber_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), __fiber__program_counter_reg__symbol,     nil);
  environment__add_var_value(cause, global_environment(), __fiber__iter_reg__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __fiber__env_reg__symbol,                 nil);
  environment__add_var_value(cause, global_environment(), __fiber__args_reg__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __fiber__return_reg__symbol,              nil);
  environment__add_var_value(cause, global_environment(), __fiber__value_reg__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __fiber__environment_critics__symbol,     nil);
  //environment__add_var_value(cause, global_environment(), __fiber__execute_bytecode__cause__symbol, nil);
}

