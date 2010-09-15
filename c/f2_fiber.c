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

def_primobject_21_slot(fiber,
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
		       processor_assignment_index,
		       should_quit);

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
  f2ptr should_quit                = nil;
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
				 processor_assignment_index,
				 should_quit);
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
  f2__fiber__should_quit__set(cause, this, f2bool__new(boolean__true));
}

f2ptr f2__fiber__quit(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  raw__fiber__quit(cause, this);
  return nil;
}
def_pcfunk1(fiber__quit, this, return f2__fiber__quit(this_cause, this));


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
  if      (command == __funk2.bytecode.bytecode__lookup_type_var__symbol)            {f2__fiber__bytecode__lookup_type_var(           fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_pop__symbol)                  {f2__fiber__bytecode__block_pop(                 fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_eval_args_begin__symbol)      {f2__fiber__bytecode__block_eval_args_begin(     fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_eval_args_end__symbol)        {f2__fiber__bytecode__block_eval_args_end(       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)                       {f2__fiber__bytecode__funk(                      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_push__symbol)                 {f2__fiber__bytecode__block_push(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_eval_args_next__symbol)       {f2__fiber__bytecode__block_eval_args_next(      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)                       {f2__fiber__bytecode__copy(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_enter__symbol)                {f2__fiber__bytecode__block_enter(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_define_last_argument__symbol) {f2__fiber__bytecode__block_define_last_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)                  {f2__fiber__bytecode__else_jump(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_define_argument__symbol)      {f2__fiber__bytecode__block_define_argument(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                        {f2__fiber__bytecode__nop(                       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__push__symbol)                       {f2__fiber__bytecode__push(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                        {f2__fiber__bytecode__pop(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)                       {f2__fiber__bytecode__jump(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol)      {f2__fiber__bytecode__block_exit_and_no_pop(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_define_rest_argument__symbol) {f2__fiber__bytecode__block_define_rest_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_pop__symbol)         {f2__fiber__bytecode__block_exit_and_pop(        fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)                      {f2__fiber__bytecode__yield(                     fiber, bytecode); return boolean__true;}
  else if (command == __funk2.bytecode.bytecode__type_var__mutate__symbol)           {f2__fiber__bytecode__type_var__mutate(          fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define_type_var__symbol)            {f2__fiber__bytecode__define_type_var(           fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)                       {f2__fiber__bytecode__swap(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)                       {f2__fiber__bytecode__cons(                      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)                   {f2__fiber__bytecode__car__set(                  fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)                   {f2__fiber__bytecode__cdr__set(                  fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol)         {f2__fiber__bytecode__globalize_type_var(        fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__push_constant__symbol)              {f2__fiber__bytecode__push_constant(             fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array__symbol)                      {f2__fiber__bytecode__array(                     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__symbol)             {f2__fiber__bytecode__reg_array__elt(            fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__reg_array__elt__set__symbol)        {f2__fiber__bytecode__reg_array__elt__set(       fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__consp__symbol)                      {f2__fiber__bytecode__consp(                     fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__jump_funk__symbol)                  {f2__fiber__bytecode__jump_funk(                 fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__set__symbol)                        {f2__fiber__bytecode__set(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__array_elt__symbol)                  {f2__fiber__bytecode__array_elt(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__if_jump__symbol)                    {f2__fiber__bytecode__if_jump(                   fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__car__symbol)                        {f2__fiber__bytecode__car(                       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__symbol)                        {f2__fiber__bytecode__cdr(                       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__debug__symbol)                      {f2__fiber__bytecode__debug(                     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__tracer__symbol)                     {f2__fiber__bytecode__tracer(                    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__endfunk__symbol)                    {f2__fiber__bytecode__endfunk(                   fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__compile__symbol)                    {f2__fiber__bytecode__compile(                   fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__newenv__symbol)                     {f2__fiber__bytecode__newenv(                    fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__machine_code__symbol)               {f2__fiber__bytecode__machine_code(              fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  
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
  return f2__fiber_stack_trace__new(cause, f2__fiber__stack(cause, this));
}

f2ptr f2__fiber__stack_trace(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber__stack_trace(cause, this);
}
def_pcfunk1(fiber__stack_trace, this, return f2__fiber__stack_trace(this_cause, this));


f2ptr raw__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  f2ptr fiber_stack_trace = raw__fiber__stack_trace(cause, this);
  if (raw__larva__is_type(cause, fiber_stack_trace)) {
    return fiber_stack_trace;
  }
  return f2__fiber_stack_trace__print(cause, fiber_stack_trace);
}

f2ptr f2__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  if (! raw__fiber__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber__print_stack_trace(cause, this);
}
def_pcfunk1(fiber__print_stack_trace, this, return f2__fiber__print_stack_trace(this_cause, this));


f2ptr raw__fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr frame = f2__frame__new(cause, f2list26__new(cause,
						    new__symbol(cause, "type"),                       new__symbol(cause, "fiber"),
						    new__symbol(cause, "cause_reg"),                  f2__fiber__cause_reg(                 cause, this),
						    new__symbol(cause, "keep_undead"),                f2__fiber__keep_undead(               cause, this),
						    new__symbol(cause, "is_zombie"),                  f2__fiber__is_zombie(                 cause, this),
						    new__symbol(cause, "is_complete"),                f2__fiber__is_complete(               cause, this),
						    new__symbol(cause, "execute_mutex"),              f2__fiber__execute_mutex(             cause, this),
						    new__symbol(cause, "paused"),                     f2__fiber__paused(                    cause, this),
						    new__symbol(cause, "last_executed_time"),         f2__fiber__last_executed_time(        cause, this),
						    new__symbol(cause, "sleep_until_time"),           f2__fiber__sleep_until_time(          cause, this),
						    new__symbol(cause, "execution_nanoseconds"),      f2__fiber__execution_nanoseconds(     cause, this),
						    new__symbol(cause, "bytecode_count"),             f2__fiber__bytecode_count(            cause, this),
						    new__symbol(cause, "processor_assignment_index"), f2__fiber__processor_assignment_index(cause, this),
						    new__symbol(cause, "stack_trace"),                f2__fiber__stack_trace(               cause, this)));
  f2__ptypehash__add(cause, raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame), this, frame);
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__fiber__is_type(cause, this)) &&
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(fiber__terminal_print_with_frame, this, terminal_print_frame, return f2__fiber__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber__primobject_type__new(cause);
  {char* slot_name = "do_sleep_until_time";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk);}
  {char* slot_name = "sleep_for_nanoseconds";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk);}
  {char* slot_name = "is_complete";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk);}
  {char* slot_name = "quit";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk);}
  {char* slot_name = "stack_trace";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__funk);}
  return this;
}




// fiber_stack_trace

def_primobject_1_slot(fiber_stack_trace,
		      stack);

f2ptr f2__fiber_stack_trace__new(f2ptr cause, f2ptr stack) {
  return f2fiber_stack_trace__new(cause, stack);
}
def_pcfunk1(fiber_stack_trace__new, stack, return f2__fiber_stack_trace__new(this_cause, stack));

f2ptr raw__fiber_stack_trace__as__string(f2ptr cause, f2ptr this) {
  return new__string(cause, "<fiber_stack_trace>");
}

f2ptr f2__fiber_stack_trace__as__string(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace__as__string(cause, this);
}
def_pcfunk1(fiber_stack_trace__as__string, this, return f2__fiber_stack_trace__as__string(this_cause, this));


f2ptr raw__fiber_stack_trace__next(f2ptr cause, f2ptr this) {
  boolean_t found_valid_block = boolean__false;
  f2ptr     iter              = f2__fiber_stack_trace__stack(cause, this);
  while ((iter != nil) && (! found_valid_block)) {
    if (! raw__cons__is_type(cause, iter)) {
      return f2larva__new(cause, 3, nil);
    }
    f2ptr element = f2__cons__car(cause, iter);
    if (raw__eq(cause, element, __funk2.compile.debug_funk_call__symbol)) {
      f2ptr iter_cdr = f2__cons__cdr(cause, iter);
      if (iter_cdr) {
	f2ptr funkable = f2__cons__car(cause, iter_cdr);
	if (raw__funkable__is_type(cause, funkable)) {
	  f2ptr iter_cdr_cdr = f2__cons__cdr(cause, iter_cdr);
	  if (iter_cdr_cdr) {
	    f2ptr args = f2__cons__car(cause, iter_cdr_cdr);
	    if ((args == nil) || raw__cons__is_type(cause, args)) {
	      found_valid_block = boolean__true;
	    }
	  }
	}
      }
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return (iter != nil) ? f2__fiber_stack_trace__new(cause, iter) : nil;
}

f2ptr f2__fiber_stack_trace__next(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace__next(cause, this);
}
def_pcfunk1(fiber_stack_trace__next, this, return f2__fiber_stack_trace__next(this_cause, this));


f2ptr raw__fiber_stack_trace__first(f2ptr cause, f2ptr this) {
  f2ptr block = nil;
  f2ptr iter  = f2__fiber_stack_trace__stack(cause, this);
  while ((iter != nil) && (block == nil)) {
    if (! raw__cons__is_type(cause, iter)) {
      return f2larva__new(cause, 3, nil);
    }
    f2ptr element = f2__cons__car(cause, iter);
    if (raw__eq(cause, element, __funk2.compile.debug_funk_call__symbol)) {
      f2ptr iter_cdr = f2__cons__cdr(cause, iter);
      if (iter_cdr) {
	f2ptr funkable = f2__cons__car(cause, iter_cdr);
	if (raw__funkable__is_type(cause, funkable)) {
	  f2ptr iter_cdr_cdr = f2__cons__cdr(cause, iter_cdr);
	  if (iter_cdr_cdr) {
	    f2ptr args = f2__cons__car(cause, iter_cdr_cdr);
	    if ((args == nil) || raw__cons__is_type(cause, args)) {
	      f2ptr argument_frame = f2__frame__new(cause, nil);
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
		  f2__frame__add_var_value(cause, argument_frame, arg_name, arg);
		  arg_name_iter = f2__cons__cdr(cause, arg_name_iter);
		  arg_iter      = f2__cons__cdr(cause, arg_iter);
		}
	      }
	      block = f2__fiber_stack_trace_block__new(cause, funkable, argument_frame);
	    }
	  }
	}
      }
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return block;
}

f2ptr f2__fiber_stack_trace__first(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace__first(cause, this);
}
def_pcfunk1(fiber_stack_trace__first, this, return f2__fiber_stack_trace__first(this_cause, this));


f2ptr raw__fiber_stack_trace__print(f2ptr cause, f2ptr this) {
  f2ptr iter = this;
  while (iter) {
    if (! raw__fiber_stack_trace__is_type(cause, iter)) {
      return f2larva__new(cause, 1, nil);
    }
    f2ptr block = f2__fiber_stack_trace__first(cause, iter);
    if (block != nil) {
      f2ptr result = f2__fiber_stack_trace_block__print(cause, block);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    iter = f2__fiber_stack_trace__next(cause, iter);
  }
  return nil;
}

f2ptr f2__fiber_stack_trace__print(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace__print(cause, this);
}
def_pcfunk1(fiber_stack_trace__print, this, return f2__fiber_stack_trace__print(this_cause, this));


f2ptr raw__fiber_stack_trace__as__printable(f2ptr cause, f2ptr this) {
  f2ptr printable_seq_reverse = nil;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__fiber_stack_trace__is_type(cause, iter)) {
	return f2larva__new(cause, 1, nil);
      }
      f2ptr block = f2__fiber_stack_trace__first(cause, iter);
      if (block != nil) {
	f2ptr printable_block = f2__fiber_stack_trace_block__as__printable(cause, block);
	if (raw__larva__is_type(cause, printable_block)) {
	  return printable_block;
	}
	printable_seq_reverse = f2cons__new(cause, printable_block, printable_seq_reverse);
      }
      iter = f2__fiber_stack_trace__next(cause, iter);
    }
  }
  return f2__reverse(cause, printable_seq_reverse);
}

f2ptr f2__fiber_stack_trace__as__printable(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace__as__printable(cause, this);
}
def_pcfunk1(fiber_stack_trace__as__printable, this, return f2__fiber_stack_trace__as__printable(this_cause, this));


f2ptr f2fiber_stack_trace__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_stack_trace__primobject_type__new(cause);
  {char* slot_name = "as-string";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__funk);}
  {char* slot_name = "next";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__funk);}
  {char* slot_name = "first";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__funk);}
  {char* slot_name = "print";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__funk);}
  {char* slot_name = "as-printable"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__funk);}
  return this;
}


// fiber_stack_trace_block

def_primobject_2_slot(fiber_stack_trace_block,
		      funk,
		      argument_frame);

f2ptr f2__fiber_stack_trace_block__new(f2ptr cause, f2ptr funk, f2ptr argument_frame) {
  return f2fiber_stack_trace_block__new(cause, funk, argument_frame);
}
def_pcfunk2(fiber_stack_trace_block__new, funk, argument_frame, return f2__fiber_stack_trace_block__new(this_cause, funk, argument_frame));

f2ptr raw__fiber_stack_trace_block__as__string(f2ptr cause, f2ptr this) {
  return new__string(cause, "<fiber_stack_trace_block>");
}

f2ptr f2__fiber_stack_trace_block__as__string(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace_block__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace_block__as__string(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__as__string, this, return f2__fiber_stack_trace_block__as__string(this_cause, this));


f2ptr raw__fiber_stack_trace_block__printable_argument_frame(f2ptr cause, f2ptr this) {
  f2ptr argument_frame  = f2__fiber_stack_trace_block__argument_frame(cause, this);
  return f2__exp__printable_value(cause, argument_frame);
}

f2ptr f2__fiber_stack_trace_block__printable_argument_frame(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace_block__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace_block__printable_argument_frame(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__printable_argument_frame, this, return f2__fiber_stack_trace_block__printable_argument_frame(this_cause, this));


f2ptr raw__fiber_stack_trace_block__print(f2ptr cause, f2ptr this) {
  f2__print(cause, f2__fiber_stack_trace_block__as__printable(cause, this));
  return nil;
}

f2ptr f2__fiber_stack_trace_block__print(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace_block__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace_block__print(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__print, this, return f2__fiber_stack_trace_block__print(this_cause, this));


f2ptr raw__fiber_stack_trace_block__as__printable(f2ptr cause, f2ptr this) {
  f2ptr funk                     = f2__fiber_stack_trace_block__funk(                    cause, this);
  f2ptr funk__name               = f2__funkable__name(                                   cause, funk);
  f2ptr printable_argument_frame = f2__fiber_stack_trace_block__printable_argument_frame(cause, this);
  return f2list2__new(cause, funk__name, printable_argument_frame);
}

f2ptr f2__fiber_stack_trace_block__as__printable(f2ptr cause, f2ptr this) {
  if (! raw__fiber_stack_trace_block__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_stack_trace_block__as__printable(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__as__printable, this, return f2__fiber_stack_trace_block__as__printable(this_cause, this));


f2ptr f2fiber_stack_trace_block__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_stack_trace_block__primobject_type__new(cause);
  {char* slot_name = "as-string";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__funk);}
  {char* slot_name = "printable_argument_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__funk);}
  {char* slot_name = "print";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__funk);}
  {char* slot_name = "as-printable";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__printable__funk);}
  return this;
}





// **

void f2__fiber__reinitialize_globalvars() {
  f2ptr cause = f2_fiber_c__cause__new(initial_cause());
  
  // initialize type symbols
  
  // fiber
  __fiber__symbol = new__symbol(cause, "fiber");
  
  // fiber_stack_trace
  __fiber_stack_trace__symbol = new__symbol(cause, "fiber_stack_trace");
  
  // fiber_stack_trace_block
  __fiber_stack_trace_block__symbol = new__symbol(cause, "fiber_stack_trace_block");
  
  
  
  // initialize fiber register symbols
  __fiber__program_counter_reg__symbol = new__symbol(cause, "program_counter");
  __fiber__iter_reg__symbol            = new__symbol(cause, "iter");
  __fiber__env_reg__symbol             = new__symbol(cause, "env");
  __fiber__args_reg__symbol            = new__symbol(cause, "args");
  __fiber__return_reg__symbol          = new__symbol(cause, "return");
  __fiber__value_reg__symbol           = new__symbol(cause, "value");
  
  // initialize other misc. symbols
  __fiber__environment_critics__symbol = new__symbol(cause, "-environment_critics-");
  
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
  
  initialize_primobject_21_slot(fiber,
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
				processor_assignment_index,
				should_quit);
  
  {char* symbol_str = "do_sleep_until_time"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__do_sleep_until_time, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk = never_gc(cfunk);}
  
  {char* symbol_str = "sleep_for_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__sleep_for_nanoseconds, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_complete"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__is_complete, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk = never_gc(cfunk);}
  
  {char* symbol_str = "quit"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__quit, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk = never_gc(cfunk);}
  
  {char* symbol_str = "stack_trace"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__stack_trace, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__terminal_print_with_frame, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(fiber__print_stack_trace, this, "Pretty prints a stack trace to help a human understand this fiber's current execution."); 


  // fiber_stack_trace
  
  initialize_primobject_1_slot(fiber_stack_trace,
			       stack);
  
  {char* symbol_str = "as-string"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__as__string, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__funk = never_gc(cfunk);}
  
  {char* symbol_str = "next"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__next, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__funk = never_gc(cfunk);}
  
  {char* symbol_str = "first"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__first, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__funk = never_gc(cfunk);}
  
  {char* symbol_str = "print"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__print, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__funk = never_gc(cfunk);}
  
  {char* symbol_str = "as-printable"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__as__printable, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__funk = never_gc(cfunk);}
  
  
  // fiber_stack_trace_block
  
  initialize_primobject_2_slot(fiber_stack_trace_block,
			       funk,
			       argument_frame);
  
  {char* symbol_str = "as-string"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__as__string, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__funk = never_gc(cfunk);}
  
  {char* symbol_str = "printable_argument_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__printable_argument_frame, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__funk = never_gc(cfunk);}
  
  {char* symbol_str = "print"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__print, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__funk = never_gc(cfunk);}
  
  
}

