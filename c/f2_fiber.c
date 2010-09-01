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

def_primobject_20_slot(fiber,
		       program_counter,
		       stack,
		       iter,
		       env,
		       args,
		       return_reg,
		       value,
		       trace,
		       cause_reg,
		       keep_undead,
		       is_zombie,
		       parent_fiber,
		       parent_env,
		       execute_mutex,
		       paused,
		       last_executed_time,
		       sleep_until_time,
		       execution_nanoseconds,
		       bytecode_count,
		       processor_assignment_index);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args) {
  f2ptr program_counter            = nil;
  f2ptr stack                      = nil;
  f2ptr iter                       = nil;
  f2ptr env                        = parent_env;
  f2ptr args                       = nil;
  f2ptr return_reg                 = nil;
  f2ptr value                      = nil;
  f2ptr trace                      = nil;
  f2ptr cause_reg                  = cause;
  f2ptr keep_undead                = __funk2.globalenv.true__symbol;
  f2ptr is_zombie                  = nil;
  f2ptr execute_mutex              = f2mutex__new(cause);
  f2ptr paused                     = nil;
  f2ptr last_executed_time         = nil;
  f2ptr sleep_until_time           = nil;
  f2ptr execution_nanoseconds      = f2integer__new(cause, 0);
  f2ptr bytecode_count             = f2integer__new(cause, 0);
  f2ptr processor_assignment_index = nil;
  f2ptr new_fiber = f2fiber__new(cause,
				 program_counter,
				 stack,
				 iter,
				 env,
				 args,
				 return_reg,
				 value,
				 trace,
				 cause_reg,
				 keep_undead,
				 is_zombie,
				 parent_fiber,
				 parent_env,
				 execute_mutex,
				 paused,
				 last_executed_time,
				 sleep_until_time,
				 execution_nanoseconds,
				 bytecode_count,
				 processor_assignment_index);
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
  boolean_t is_complete;
  f2ptr     execute_mutex = f2fiber__execute_mutex(this, cause);
  if (! raw__mutex__trylock(cause, execute_mutex)) { // successful lock
    is_complete = (f2fiber__is_complete(this, cause) ? boolean__true : boolean__false);
    f2mutex__unlock(execute_mutex, cause);
  } else {
    // if we fail to lock the execute_mutex, we assume that it is executing.
    is_complete = boolean__false;
  }
  return is_complete;
}

f2ptr f2__fiber__is_complete(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__fiber__is_complete(cause, this));
}
def_pcfunk1(fiber__is_complete, this, return f2__fiber__is_complete(this_cause, this));

void raw__fiber__quit(f2ptr cause, f2ptr this) {
  f2ptr execute_mutex = f2__fiber__execute_mutex(cause, this);
  f2__mutex__lock(cause, execute_mutex);
  f2__fiber__program_counter__set(cause, this, nil);
  f2__mutex__unlock(cause, execute_mutex);
}

f2ptr f2__fiber__quit(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__fiber__quit(cause, this);
  return nil;
}
def_pcfunk1(fiber__quit, this, return f2__fiber__quit(this_cause, this));


f2ptr f2fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber__primobject_type__new(cause);
  {char* slot_name = "do_sleep_until_time";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk);}
  {char* slot_name = "sleep_for_nanoseconds"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk);}
  {char* slot_name = "is_complete";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk);}
  {char* slot_name = "quit";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk);}
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

/*
[c/f2_bytecodes.c                           128] tid=0x2b93383266c0     0x3A05_18_10_20.446480000 funk2 status:   bytecode__pop__execution_count                        = 2309676
[c/f2_bytecodes.c                           127] tid=0x2b93383266c0     0x3A05_18_10_20.446467000 funk2 status:   bytecode__push__execution_count                       = 1872132
[c/f2_bytecodes.c                           129] tid=0x2b93383266c0     0x3A05_18_10_20.446493000 funk2 status:   bytecode__copy__execution_count                       = 812439
[c/f2_bytecodes.c                           125] tid=0x2b93383266c0     0x3A05_18_10_20.446429000 funk2 status:   bytecode__swap__execution_count                       = 708106
[c/f2_bytecodes.c                           118] tid=0x2b93383266c0     0x3A05_18_10_20.446301000 funk2 status:   bytecode__cons__execution_count                       = 626553
[c/f2_bytecodes.c                           122] tid=0x2b93383266c0     0x3A05_18_10_20.446392000 funk2 status:   bytecode__car__set__execution_count                   = 626548
[c/f2_bytecodes.c                           130] tid=0x2b93383266c0     0x3A05_18_10_20.446505000 funk2 status:   bytecode__lookup_type_var__execution_count            = 596701
[c/f2_bytecodes.c                           123] tid=0x2b93383266c0     0x3A05_18_10_20.446404000 funk2 status:   bytecode__cdr__set__execution_count                   = 358356
[c/f2_bytecodes.c                           115] tid=0x2b93383266c0     0x3A05_18_10_20.446261000 funk2 status:   bytecode__funk__execution_count                       = 262511
[c/f2_bytecodes.c                           146] tid=0x2b93383266c0     0x3A05_18_10_20.446745000 funk2 status:   bytecode__block_define_argument__execution_count      = 104625
[c/f2_bytecodes.c                           144] tid=0x2b93383266c0     0x3A05_18_10_20.446721000 funk2 status:   bytecode__block_enter__execution_count                = 101809
[c/f2_bytecodes.c                           145] tid=0x2b93383266c0     0x3A05_18_10_20.446733000 funk2 status:   bytecode__block_define_rest_argument__execution_count = 62142
[c/f2_bytecodes.c                           149] tid=0x2b93383266c0     0x3A05_18_10_20.446782000 funk2 status:   bytecode__block_exit_and_no_pop__execution_count      = 59925
[c/f2_bytecodes.c                           136] tid=0x2b93383266c0     0x3A05_18_10_20.446582000 funk2 status:   bytecode__else_jump__execution_count                  = 43925
[c/f2_bytecodes.c                           147] tid=0x2b93383266c0     0x3A05_18_10_20.446758000 funk2 status:   bytecode__block_define_last_argument__execution_count = 35568
[c/f2_bytecodes.c                           137] tid=0x2b93383266c0     0x3A05_18_10_20.446595000 funk2 status:   bytecode__nop__execution_count                        = 34541
[c/f2_bytecodes.c                           134] tid=0x2b93383266c0     0x3A05_18_10_20.446557000 funk2 status:   bytecode__jump__execution_count                       = 17629
[c/f2_bytecodes.c                           126] tid=0x2b93383266c0     0x3A05_18_10_20.446454000 funk2 status:   bytecode__push_constant__execution_count              = 15536
[c/f2_bytecodes.c                           148] tid=0x2b93383266c0     0x3A05_18_10_20.446770000 funk2 status:   bytecode__block_exit_and_pop__execution_count         = 17336
[c/f2_bytecodes.c                           131] tid=0x2b93383266c0     0x3A05_18_10_20.446520000 funk2 status:   bytecode__define_type_var__execution_count            = 13010
[c/f2_bytecodes.c                           132] tid=0x2b93383266c0     0x3A05_18_10_20.446532000 funk2 status:   bytecode__type_var__mutate__execution_count           = 5639
[c/f2_bytecodes.c                           141] tid=0x2b93383266c0     0x3A05_18_10_20.446667000 funk2 status:   bytecode__yield__execution_count                      = 4642
[c/f2_bytecodes.c                           133] tid=0x2b93383266c0     0x3A05_18_10_20.446545000 funk2 status:   bytecode__globalize_type_var__execution_count         = 350
[c/f2_bytecodes.c                           116] tid=0x2b93383266c0     0x3A05_18_10_20.446275000 funk2 status:   bytecode__jump_funk__execution_count                  = 0
[c/f2_bytecodes.c                           117] tid=0x2b93383266c0     0x3A05_18_10_20.446288000 funk2 status:   bytecode__array__execution_count                      = 0
[c/f2_bytecodes.c                           119] tid=0x2b93383266c0     0x3A05_18_10_20.446353000 funk2 status:   bytecode__consp__execution_count                      = 0
[c/f2_bytecodes.c                           120] tid=0x2b93383266c0     0x3A05_18_10_20.446367000 funk2 status:   bytecode__car__execution_count                        = 0
[c/f2_bytecodes.c                           121] tid=0x2b93383266c0     0x3A05_18_10_20.446379000 funk2 status:   bytecode__cdr__execution_count                        = 0
[c/f2_bytecodes.c                           124] tid=0x2b93383266c0     0x3A05_18_10_20.446417000 funk2 status:   bytecode__array_elt__execution_count                  = 0
[c/f2_bytecodes.c                           135] tid=0x2b93383266c0     0x3A05_18_10_20.446569000 funk2 status:   bytecode__if_jump__execution_count                    = 0
[c/f2_bytecodes.c                           138] tid=0x2b93383266c0     0x3A05_18_10_20.446620000 funk2 status:   bytecode__debug__execution_count                      = 0
[c/f2_bytecodes.c                           139] tid=0x2b93383266c0     0x3A05_18_10_20.446633000 funk2 status:   bytecode__tracer__execution_count                     = 0
[c/f2_bytecodes.c                           140] tid=0x2b93383266c0     0x3A05_18_10_20.446645000 funk2 status:   bytecode__compile__execution_count                    = 0
[c/f2_bytecodes.c                           142] tid=0x2b93383266c0     0x3A05_18_10_20.446690000 funk2 status:   bytecode__newenv__execution_count                     = 0
[c/f2_bytecodes.c                           143] tid=0x2b93383266c0     0x3A05_18_10_20.446703000 funk2 status:   bytecode__machine_code__execution_count               = 0
*/

boolean_t f2__fiber__execute_bytecode(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  debug__assert(raw__fiber__is_type(nil, fiber), nil, "fiber type assertion failed.");
  debug__assert(raw__bytecode__is_type(nil, bytecode), nil, "bytecode type assertion failed.");
  debug__assert((! cause) || raw__cause__is_type(nil, cause), nil, "fiber type assertion failed.");
  //f2ptr cause = f2fiber__execute_bytecode__cause__new(f2fiber__cause_reg(fiber), fiber, f2fiber__env(fiber), bytecode);
  //f2fiber__cause_reg__set(fiber, cause, cause);
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__pop__symbol)                        {f2__fiber__bytecode__pop(                fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__push__symbol)                       {f2__fiber__bytecode__push(               fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)                       {f2__fiber__bytecode__copy(               fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)                       {f2__fiber__bytecode__swap(               fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)                       {f2__fiber__bytecode__cons(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)                   {f2__fiber__bytecode__car__set(           fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__lookup_type_var__symbol)            {f2__fiber__bytecode__lookup_type_var(    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)                   {f2__fiber__bytecode__cdr__set(           fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)                       {f2__fiber__bytecode__funk(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_define_argument__symbol)      {f2__fiber__bytecode__block_define_argument(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_enter__symbol)                {f2__fiber__bytecode__block_enter(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_define_rest_argument__symbol) {f2__fiber__bytecode__block_define_rest_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol)      {f2__fiber__bytecode__block_exit_and_no_pop(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)                  {f2__fiber__bytecode__else_jump(          fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_define_last_argument__symbol) {f2__fiber__bytecode__block_define_last_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                        {f2__fiber__bytecode__nop(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)                       {f2__fiber__bytecode__jump(               fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__push_constant__symbol)              {f2__fiber__bytecode__push_constant(      fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_pop__symbol)         {f2__fiber__bytecode__block_exit_and_pop(        fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define_type_var__symbol)            {f2__fiber__bytecode__define_type_var(    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__type_var__mutate__symbol)           {f2__fiber__bytecode__type_var__mutate(   fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)                      {f2__fiber__bytecode__yield(              fiber, bytecode); return boolean__true;}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol)         {f2__fiber__bytecode__globalize_type_var( fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  
  else if (command == __funk2.bytecode.bytecode__array__symbol)                      {f2__fiber__bytecode__array(              fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__symbol)             {f2__fiber__bytecode__reg_array__elt(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__set__symbol)        {f2__fiber__bytecode__reg_array__elt__set(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__consp__symbol)                      {f2__fiber__bytecode__consp(              fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)                  {f2__fiber__bytecode__jump_funk(          fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                        {f2__fiber__bytecode__set(                fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array_elt__symbol)                  {f2__fiber__bytecode__array_elt(          fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__if_jump__symbol)                    {f2__fiber__bytecode__if_jump(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                        {f2__fiber__bytecode__car(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                        {f2__fiber__bytecode__cdr(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)                      {f2__fiber__bytecode__debug(              fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__tracer__symbol)                     {f2__fiber__bytecode__tracer(             fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__endfunk__symbol)                    {f2__fiber__bytecode__endfunk(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)                    {f2__fiber__bytecode__compile(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)                     {f2__fiber__bytecode__newenv(             fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)               {f2__fiber__bytecode__machine_code(       fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  
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


f2ptr raw__fiber__stack_trace(f2ptr cause, f2ptr this) {
  f2ptr reverse_stack_trace = nil;
  {
    f2ptr iter = f2__fiber__stack(cause, this);
    while (iter) {
      f2ptr element = f2__cons__car(cause, iter);
      //f2__print(cause, f2__exp__as__string(cause, element));
      if (raw__eq(cause, element, __funk2.compile.debug_funk_call__symbol)) {
	f2ptr iter_cdr = f2__cons__cdr(cause, iter);
	if (iter_cdr) {
	  f2ptr funkable = f2__cons__car(cause, iter_cdr);
	  //printf("\nfunkable: ");
	  if (raw__funkable__is_type(cause, funkable)) {
	    f2ptr iter_cdr_cdr = f2__cons__cdr(cause, iter_cdr);
	    if (iter_cdr_cdr) {
	      f2ptr args = f2__cons__car(cause, iter_cdr_cdr);
	      //printf("\nargs: ");
	      if ((args == nil) || raw__cons__is_type(cause, args)) {
		//f2__print(cause, args);
		f2ptr funkall_frame = f2__frame__new(cause, nil);
		{
		  f2__frame__add_var_value(cause, funkall_frame, new__symbol(cause, "funk"), funkable);
		  {
		    f2ptr arg_frame = f2__frame__new(cause, nil);
		    {
		      f2ptr arg_names = f2__funkable__args(cause, funkable);
		      f2ptr arg_name_iter = arg_names;
		      f2ptr arg_iter = args;
		      while(arg_name_iter && arg_iter) {
			f2ptr arg_name = f2__cons__car(cause, arg_name_iter);
			f2ptr arg      = nil;
			if (raw__eq(cause, arg_name, __funk2.globalenv.and_rest__symbol)) {
			  f2ptr arg_name_iter_cdr = f2__cons__cdr(cause, arg_name_iter);
			  if (arg_name_iter_cdr) {
			    arg_name_iter = arg_name_iter_cdr; // skip ahead one in arg names.
			    arg_name      = f2__cons__car(cause, arg_name_iter_cdr);
			    arg           = arg_iter;
			  }
			} else {
			  arg = f2__cons__car(cause, arg_iter);
			}
			f2__frame__add_var_value(cause, arg_frame, arg_name, arg);
			arg_name_iter = f2__cons__cdr(cause, arg_name_iter);
			arg_iter      = f2__cons__cdr(cause, arg_iter);
		      }
		    }
		    f2__frame__add_var_value(cause, funkall_frame, new__symbol(cause, "arg_frame"), arg_frame);
		  }
		}
		reverse_stack_trace = f2cons__new(cause, funkall_frame, reverse_stack_trace);
	      } else {
		//printf("<not cons>");
	      }
	    }
	  }
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2__reverse(cause, reverse_stack_trace);
}

f2ptr f2__fiber__stack_trace(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber__stack_trace(cause, this);
}
def_pcfunk1(fiber__stack_trace, this, return f2__fiber__stack_trace(this_cause, this));


f2ptr raw__stack_trace_element__print_value(f2ptr cause, f2ptr this) {
  boolean_t this_is_printable;
  if (raw__cons__is_type(cause, this)) {
    f2ptr print_seq = nil;
    {
      s64   list_element_count = 0;
      f2ptr last_cons          = nil;
      f2ptr iter               = this;
      while (iter) {
	f2ptr element = f2__cons__car(cause, iter);
	f2ptr element_print_value = raw__stack_trace_element__print_value(cause, element);
	if (last_cons) {
	  f2ptr new_cons = f2cons__new(cause, element_print_value, nil);
	  f2__cons__cdr__set(cause, last_cons, new_cons);
	  last_cons = new_cons;
	} else {
	  last_cons = f2cons__new(cause, element_print_value, nil);
	  print_seq = last_cons;
	}
	list_element_count ++;
	if (list_element_count < 10) {
	  iter = f2__cons__cdr(cause, iter);
	} else {
	  f2ptr new_cons = f2cons__new(cause, new__symbol(cause, "..."), nil);
	  f2__cons__cdr__set(cause, last_cons, new_cons);
	  last_cons = new_cons;
	  iter = nil;
	}
      }
    }
    return print_seq;
  } else if (raw__array__is_type(cause, this)) {
    this_is_printable = boolean__false;
  } else {
    this_is_printable = boolean__true;
  }
  if (this_is_printable) {
    return this;
  } else {
    return f2list2__new(cause, f2__object__type(cause, this), new__symbol(cause, "<>"));
  }
}

f2ptr raw__stack_trace__print(f2ptr cause, f2ptr this) {
  f2ptr iter = this;
  while (iter) {
    f2ptr element = f2__cons__car(cause, iter);
    {
      if (! raw__frame__is_type(cause, element)) {
	return f2larva__new(cause, 39, nil);
      }
      f2ptr funkall_frame = element;
      {
	f2ptr funk = f2__frame__lookup_var_value(cause, funkall_frame, new__symbol(cause, "funk"), nil);
	{
	  if (! raw__funkable__is_type(cause, funk)) {
	    return f2larva__new(cause, 39, nil);
	  }
	  f2ptr funk__cause = f2__ptype__cause(cause, funk);
	  f2ptr funk__cause__source_expression = nil;
	  if (raw__cause__is_type(cause, funk__cause)) {
	    funk__cause__source_expression = f2__cause__lookup(cause, funk__cause, new__symbol(cause, "source_expression"));
	  }
	  f2ptr name        = f2__funkable__name(cause, funk);
	  {
	    f2ptr arg_frame   = f2__frame__lookup_var_value(cause, funkall_frame, new__symbol(cause, "arg_frame"), nil);
	    f2ptr print_frame = f2__frame__new(cause, nil);
	    frame__var__iteration(cause, arg_frame, slot_name, slot_value,
				  f2ptr print_value = raw__stack_trace_element__print_value(cause, slot_value);
				  f2__frame__add_var_value(cause, print_frame, slot_name, print_value);
				  );
	    f2__print(cause, f2list4__new(cause, name, print_frame, funk__cause__source_expression, funk__cause));
	  }
	}
      }
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return nil;
}

f2ptr raw__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  f2ptr stack_trace = raw__fiber__stack_trace(cause, this);
  if (raw__larva__is_type(cause, stack_trace)) {
    return stack_trace;
  }
  return raw__stack_trace__print(cause, stack_trace);
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
  
  initialize_primobject_20_slot(fiber,
				program_counter,
				stack,
				iter,
				env,
				args,
				return_reg,
				value,
				trace,
				cause_reg,
				keep_undead,
				is_zombie,
				parent_fiber,
				parent_env,
				execute_mutex,
				paused,
				last_executed_time,
				sleep_until_time,
				execution_nanoseconds,
				bytecode_count,
				processor_assignment_index);
  
  {char* symbol_str = "do_sleep_until_time"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__do_sleep_until_time, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk = never_gc(cfunk);}
  
  {char* symbol_str = "sleep_for_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__sleep_for_nanoseconds, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_complete"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__is_complete, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk = never_gc(cfunk);}
  
  {char* symbol_str = "quit"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__quit, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(fiber__stack_trace,       this, "Returns a stack trace of this fiber's current execution."); 
  f2__primcfunk__init__1(fiber__print_stack_trace, this, "Pretty prints a stack trace to help a human understand this fiber's current execution."); 

}

