// 
// Copyright (c) 2007-2010 Bo Morgan.
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



// fiber

def_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args, execution_nanoseconds);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args) {
  f2ptr program_counter       = nil;
  f2ptr stack                 = nil;
  f2ptr iter                  = nil;
  f2ptr env                   = parent_env;
  f2ptr args                  = nil;
  f2ptr return_reg            = nil;
  f2ptr value                 = nil;
  f2ptr trace                 = nil;
  f2ptr cause_reg             = cause;
  f2ptr keep_undead           = __funk2.globalenv.true__symbol;
  f2ptr is_zombie             = nil;
  f2ptr execute_mutex         = f2mutex__new(cause);
  f2ptr paused                = nil;
  f2ptr last_executed_time    = nil;
  f2ptr sleep_until_time      = nil;
  f2ptr larva_args            = nil;
  f2ptr execution_nanoseconds = f2integer__new(cause, 0);
  f2ptr new_fiber = f2fiber__new(cause, program_counter, stack, iter, env, args, return_reg, value, trace, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args, execution_nanoseconds);
  f2fiber__keep_undead__set(new_fiber, cause, __funk2.globalenv.true__symbol);
  f2fiber__funk(new_fiber, cause, cfunkable, cfunkable_args);
  
  //f2cause__fibers__set(cause, cause, f2cons__new(cause, new_fiber, f2cause__fibers(cause, cause)));
  
  return new_fiber;
}

def_pcfunk4(fiber__new, parent_fiber, parent_env, cfunkable, cfunkable_args, return f2__fiber__new(this_cause, parent_fiber, parent_env, cfunkable, cfunkable_args));

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time) {
  if (! raw__time__is_type(cause, until_time)) {
    return f2larva__new(cause, 1, nil);
  }
  f2fiber__sleep_until_time__set(this, cause, until_time);
  return nil;
}
def_pcfunk2(fiber__do_sleep_until_time, this, until_time, return f2__fiber__do_sleep_until_time(this_cause, this, until_time));

f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds) {
  if (! raw__integer__is_type(cause, nanoseconds)) {
    return f2larva__new(cause, 1, nil);
  }
  s64 nanoseconds__i = f2integer__i(nanoseconds, cause);
  return f2__fiber__do_sleep_until_time(cause, this, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970() + nanoseconds__i)));
}
def_pcfunk2(fiber__sleep_for_nanoseconds, this, nanoseconds, return f2__fiber__sleep_for_nanoseconds(this_cause, this, nanoseconds));

boolean_t raw__fiber__is_complete(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2fiber__is_complete(this, cause);
}

f2ptr f2__fiber__is_complete(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__fiber__is_complete(cause, this));
}
def_pcfunk1(fiber__is_complete, this, return f2__fiber__is_complete(this_cause, this));

f2ptr f2fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber__primobject_type__new(cause);
  {char* slot_name = "do_sleep_until_time";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk);}
  {char* slot_name = "sleep_for_nanoseconds"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk);}
  {char* slot_name = "is_complete";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk);}
  return this;
}




f2ptr f2__fiber__lookup_type_variable_value(f2ptr cause, f2ptr fiber, f2ptr type, f2ptr variable) {
  f2ptr env   = f2fiber__env(fiber, cause);
  f2ptr value = f2__environment__lookup_type_var_value(cause, env, type, variable);
  if (raw__larva__is_type(cause, value)) {
    value = f2__cause__lookup_type_var_value(cause, cause, type, variable);
  }
  if (raw__larva__is_type(cause, value)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "undefined_variable_type"), type);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "undefined_variable"),      variable);
    u64 larva_type = f2larva__larva_type(value, cause);
    return f2larva__new(cause, larva_type, f2__bug__new(cause, f2integer__new(cause, larva_type), bug_frame));
  }
  return value;
}

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
    f2__fiber__print(cause, fiber, bytecode);
    f2fiber__value__set(fiber, cause, f2larva__new(cause, 21, nil));
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


f2ptr raw__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  f2ptr iter = f2__fiber__stack(cause, this);
  while (iter) {
    f2ptr element = f2__cons__car(cause, iter);
    f2__print(cause, f2__exp__as__string(cause, element));
    if (raw__funkable__is_type(cause, element)) {
      printf("\nfunkable: "); f2__print(cause, element);
      f2ptr rest = f2__cons__cdr(cause, iter);
      if (rest) {
	f2ptr args = f2__cons__car(cause, rest);
	printf("\nargs: "); f2__print(cause, args);
      }
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return nil;
}

f2ptr f2__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber__print_stack_trace(cause, this);
}
def_pcfunk1(fiber__print_stack_trace, this, return f2__fiber__print_stack_trace(this_cause, this));


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


  // fiber
  
  initialize_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args, execution_nanoseconds);
  
  {char* symbol_str = "do_sleep_until_time"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__do_sleep_until_time, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk = never_gc(cfunk);}
  
  {char* symbol_str = "sleep_for_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__sleep_for_nanoseconds, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_complete"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__is_complete, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(fiber__print_stack_trace, this, "Prints a stack trace to help a human understand a fiber's current execution."); 

}

