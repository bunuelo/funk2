// 
// Copyright (c) 2007-2012 Bo Morgan.
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

def_primobject_30_slot(fiber,
		       program_counter,
		       stack,
		       iter,
		       env,
		       args,
		       return_reg,
		       value,
		       trace,
		       cause_reg_cmutex,
		       cause_reg,
		       keep_undead,
		       is_zombie,
		       parent_fiber,
		       parent_env,
		       execute_cmutex,
		       paused,
		       last_executed_time,
		       sleep_until_time,
		       execution_nanoseconds_chunk,
		       start_cycle_execution_nanoseconds_chunk,
		       bytecode_count,
		       bytes_allocated_count_chunk,
		       start_cycle_processor_bytes_allocated_count_chunk,
		       processor_assignment_scheduler_cmutex,
		       processor_assignment_index,
		       should_quit,
		       exit_cmutex,
		       exit_status,
		       bug_trigger,
		       complete_trigger);

f2ptr raw__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args) {
  f2ptr program_counter                                   = nil;
  f2ptr stack                                             = nil;
  f2ptr iter                                              = nil;
  f2ptr env                                               = parent_env;
  f2ptr args                                              = nil;
  f2ptr return_reg                                        = nil;
  f2ptr value                                             = nil;
  f2ptr trace                                             = nil;
  f2ptr cause_reg_cmutex                                  = f2__cmutex__new(cause);
  f2ptr cause_reg                                         = nil;
  f2ptr keep_undead                                       = __funk2.globalenv.true__symbol;
  f2ptr is_zombie                                         = nil;
  f2ptr execute_cmutex                                    = f2cmutex__new(cause);
  f2ptr paused                                            = nil;
  f2ptr last_executed_time                                = nil;
  f2ptr sleep_until_time                                  = nil;
  f2ptr execution_nanoseconds_chunk                       = raw__chunk__new(cause, sizeof(u64));
  f2ptr start_cycle_execution_nanoseconds_chunk           = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytecode_count                                    = f2integer__new(cause, 0);
  f2ptr bytes_allocated_count_chunk                       = raw__chunk__new(cause, sizeof(u64));
  f2ptr start_cycle_processor_bytes_allocated_count_chunk = raw__chunk__new(cause, sizeof(u64));
  f2ptr processor_assignment_scheduler_cmutex             = f2scheduler_cmutex__new(cause);
  f2ptr processor_assignment_index                        = nil;
  f2ptr should_quit                                       = nil;
  f2ptr exit_cmutex                                       = f2__cmutex__new(cause);
  f2ptr exit_status                                       = nil;
  f2ptr bug_trigger                                       = f2__fiber_trigger__new(cause);
  f2ptr complete_trigger                                  = f2__fiber_trigger__new(cause);
  f2ptr new_fiber = f2fiber__new(cause,
				 program_counter,
				 stack,
				 iter,
				 env,
				 args,
				 return_reg,
				 value,
				 trace,
				 cause_reg_cmutex,
				 cause_reg,
				 keep_undead,
				 is_zombie,
				 parent_fiber,
				 parent_env,
				 execute_cmutex,
				 paused,
				 last_executed_time,
				 sleep_until_time,
				 execution_nanoseconds_chunk,
				 start_cycle_execution_nanoseconds_chunk,
				 bytecode_count,
				 bytes_allocated_count_chunk,
				 start_cycle_processor_bytes_allocated_count_chunk,
				 processor_assignment_scheduler_cmutex,
				 processor_assignment_index,
				 should_quit,
				 exit_cmutex,
				 exit_status,
				 bug_trigger,
				 complete_trigger);
  f2fiber__keep_undead__set(new_fiber, cause, __funk2.globalenv.true__symbol);
  f2fiber__funk(new_fiber, cause, cfunkable, cfunkable_args);
  if (cause != nil) {
    raw__cause__add_fiber(cause, cause, new_fiber);
  }
  return new_fiber;
}

def_pcfunk4(fiber__new, parent_fiber, parent_env, cfunkable, cfunkable_args,
	    "",
	    return raw__fiber__new(this_cause, parent_fiber, parent_env, cfunkable, cfunkable_args));


u64 raw__fiber__execution_nanoseconds(f2ptr cause, f2ptr this) {
  f2ptr execution_nanoseconds_chunk = f2fiber__execution_nanoseconds_chunk(this, cause);
  return f2chunk__bit64__elt(execution_nanoseconds_chunk, 0, cause);
}

f2ptr f2__fiber__execution_nanoseconds(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return f2integer__new(cause, raw__fiber__execution_nanoseconds(cause, this));
}
def_pcfunk1(fiber__execution_nanoseconds, this,
	    "",
	    return f2__fiber__execution_nanoseconds(this_cause, this));


void raw__fiber__execution_nanoseconds__set(f2ptr cause, f2ptr this, u64 execution_nanoseconds) {
  f2ptr execution_nanoseconds_chunk = f2fiber__execution_nanoseconds_chunk(this, cause);
  f2chunk__bit64__elt__set(execution_nanoseconds_chunk, 0, cause, execution_nanoseconds);
}

f2ptr f2__fiber__execution_nanoseconds__set(f2ptr cause, f2ptr this, f2ptr execution_nanoseconds) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, execution_nanoseconds);
  u64 execution_nanoseconds__i = f2integer__i(execution_nanoseconds, cause);
  raw__fiber__execution_nanoseconds__set(cause, this, execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(fiber__execution_nanoseconds__set, this, execution_nanoseconds,
	    "",
	    return f2__fiber__execution_nanoseconds__set(this_cause, this, execution_nanoseconds));


u64 raw__fiber__start_cycle_execution_nanoseconds(f2ptr cause, f2ptr this) {
  f2ptr start_cycle_execution_nanoseconds_chunk = f2fiber__start_cycle_execution_nanoseconds_chunk(this, cause);
  return f2chunk__bit64__elt(start_cycle_execution_nanoseconds_chunk, 0, cause);
}

f2ptr f2__fiber__start_cycle_execution_nanoseconds(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return f2integer__new(cause, raw__fiber__start_cycle_execution_nanoseconds(cause, this));
}
def_pcfunk1(fiber__start_cycle_execution_nanoseconds, this,
	    "",
	    return f2__fiber__start_cycle_execution_nanoseconds(this_cause, this));


void raw__fiber__start_cycle_execution_nanoseconds__set(f2ptr cause, f2ptr this, u64 start_cycle_execution_nanoseconds) {
  f2ptr start_cycle_execution_nanoseconds_chunk = f2fiber__start_cycle_execution_nanoseconds_chunk(this, cause);
  f2chunk__bit64__elt__set(start_cycle_execution_nanoseconds_chunk, 0, cause, start_cycle_execution_nanoseconds);
}

f2ptr f2__fiber__start_cycle_execution_nanoseconds__set(f2ptr cause, f2ptr this, f2ptr start_cycle_execution_nanoseconds) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, start_cycle_execution_nanoseconds);
  u64 start_cycle_execution_nanoseconds__i = f2integer__i(start_cycle_execution_nanoseconds, cause);
  raw__fiber__start_cycle_execution_nanoseconds__set(cause, this, start_cycle_execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(fiber__start_cycle_execution_nanoseconds__set, this, start_cycle_execution_nanoseconds,
	    "",
	    return f2__fiber__start_cycle_execution_nanoseconds__set(this_cause, this, start_cycle_execution_nanoseconds));


u64 raw__fiber__bytes_allocated_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_allocated_count_chunk = f2fiber__bytes_allocated_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_allocated_count_chunk, 0, cause);
}

f2ptr f2__fiber__bytes_allocated_count(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return f2integer__new(cause, raw__fiber__bytes_allocated_count(cause, this));
}
def_pcfunk1(fiber__bytes_allocated_count, this,
	    "",
	    return f2__fiber__bytes_allocated_count(this_cause, this));


void raw__fiber__bytes_allocated_count__set(f2ptr cause, f2ptr this, u64 bytes_allocated_count) {
  f2ptr bytes_allocated_count_chunk = f2fiber__bytes_allocated_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_allocated_count_chunk, 0, cause, bytes_allocated_count);
}

f2ptr f2__fiber__bytes_allocated_count__set(f2ptr cause, f2ptr this, f2ptr bytes_allocated_count) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, bytes_allocated_count);
  u64 bytes_allocated_count__i = f2integer__i(bytes_allocated_count, cause);
  raw__fiber__bytes_allocated_count__set(cause, this, bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(fiber__bytes_allocated_count__set, this, bytes_allocated_count,
	    "",
	    return f2__fiber__bytes_allocated_count__set(this_cause, this, bytes_allocated_count));


u64 raw__fiber__start_cycle_processor_bytes_allocated_count(f2ptr cause, f2ptr this) {
  f2ptr start_cycle_processor_bytes_allocated_count_chunk = f2fiber__start_cycle_processor_bytes_allocated_count_chunk(this, cause);
  return f2chunk__bit64__elt(start_cycle_processor_bytes_allocated_count_chunk, 0, cause);
}

f2ptr f2__fiber__start_cycle_processor_bytes_allocated_count(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return f2integer__new(cause, raw__fiber__start_cycle_processor_bytes_allocated_count(cause, this));
}
def_pcfunk1(fiber__start_cycle_processor_bytes_allocated_count, this,
	    "",
	    return f2__fiber__start_cycle_processor_bytes_allocated_count(this_cause, this));


void raw__fiber__start_cycle_processor_bytes_allocated_count__set(f2ptr cause, f2ptr this, u64 start_cycle_processor_bytes_allocated_count) {
  f2ptr start_cycle_processor_bytes_allocated_count_chunk = f2fiber__start_cycle_processor_bytes_allocated_count_chunk(this, cause);
  f2chunk__bit64__elt__set(start_cycle_processor_bytes_allocated_count_chunk, 0, cause, start_cycle_processor_bytes_allocated_count);
}

f2ptr f2__fiber__start_cycle_processor_bytes_allocated_count__set(f2ptr cause, f2ptr this, f2ptr start_cycle_processor_bytes_allocated_count) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, start_cycle_processor_bytes_allocated_count);
  u64 start_cycle_processor_bytes_allocated_count__i = f2integer__i(start_cycle_processor_bytes_allocated_count, cause);
  raw__fiber__start_cycle_processor_bytes_allocated_count__set(cause, this, start_cycle_processor_bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(fiber__start_cycle_processor_bytes_allocated_count__set, this, start_cycle_processor_bytes_allocated_count,
	    "",
	    return f2__fiber__start_cycle_processor_bytes_allocated_count__set(this_cause, this, start_cycle_processor_bytes_allocated_count));


void raw__fiber__increase_bytecode_count(f2ptr cause, f2ptr this, u64 relative_bytecode_count) {
  {
    f2ptr bytecode_count     = f2fiber__bytecode_count(this, cause);
    u64   bytecode_count__i  = f2integer__i(bytecode_count, cause);
    f2fiber__bytecode_count__set(this, cause, f2integer__new(cause, bytecode_count__i + relative_bytecode_count));
  }
  {
    f2ptr cause_reg = f2fiber__cause_reg(this, cause);
    if (cause_reg != nil) {
      f2ptr cause_groups = f2cause__cause_groups(cause_reg, cause);
      {
	f2ptr iter = cause_groups;
	while (iter != nil) {
	  f2ptr cause_group = f2cons__car(iter, cause);
	  raw__cause_group__increase_bytecode_count(cause, cause_group, relative_bytecode_count);
	  iter = f2cons__cdr(iter, cause);
	}
      }
    }
  }
}

f2ptr f2__fiber__increase_bytecode_count(f2ptr cause, f2ptr this, f2ptr relative_bytecode_count) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, relative_bytecode_count);
  u64 relative_bytecode_count__i = f2integer__i(relative_bytecode_count, cause);
  raw__fiber__increase_bytecode_count(cause, this, relative_bytecode_count__i);
  return nil;
}
def_pcfunk2(fiber__increase_bytecode_count, this, relative_bytecode_count,
	    "",
	    return f2__fiber__increase_bytecode_count(this_cause, this, relative_bytecode_count));


f2ptr raw__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time) {
  f2fiber__sleep_until_time__set(this, cause, until_time);
  return nil;
}

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time) {
  assert_argument_type(fiber, this);
  assert_argument_type(time,  until_time);
  raw__fiber__do_sleep_until_time(cause, this, until_time);
  return nil;
}
def_pcfunk2(fiber__do_sleep_until_time, this, until_time,
	    "",
	    return f2__fiber__do_sleep_until_time(this_cause, this, until_time));


f2ptr raw__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, s64 nanoseconds) {
  return f2__fiber__do_sleep_until_time(cause, this, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970() + nanoseconds)));
}

f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds) {
  assert_argument_type(fiber,   this);
  assert_argument_type(integer, nanoseconds);
  return raw__fiber__sleep_for_nanoseconds(cause, this, f2integer__i(nanoseconds, cause));
}
def_pcfunk2(fiber__sleep_for_nanoseconds, this, nanoseconds,
	    "",
	    return f2__fiber__sleep_for_nanoseconds(this_cause, this, nanoseconds));

boolean_t raw__fiber__is_complete(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  boolean_t is_complete;
  f2ptr     execute_cmutex = f2fiber__execute_cmutex(this, cause);
  if (! raw__cmutex__trylock(cause, execute_cmutex)) { // successful lock
    is_complete = (f2fiber__is_complete(this, cause) ? boolean__true : boolean__false);
    f2cmutex__unlock(execute_cmutex, cause);
  } else {
    // if we fail to lock the execute_cmutex, we assume that it is executing.
    is_complete = boolean__false;
  }
  return is_complete;
}

f2ptr f2__fiber__is_complete(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__fiber__is_complete(cause, this));
}
def_pcfunk1(fiber__is_complete, this,
	    "",
	    return f2__fiber__is_complete(this_cause, this));

void raw__fiber__quit(f2ptr cause, f2ptr this) {
  f2__fiber__should_quit__set(cause, this, f2bool__new(boolean__true));
  f2__fiber__paused__set(     cause, this, f2bool__new(boolean__false));
}

f2ptr f2__fiber__quit(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  raw__fiber__quit(cause, this);
  return nil;
}
def_pcfunk1(fiber__quit, this,
	    "",
	    return f2__fiber__quit(this_cause, this));


f2ptr f2__fiber__lookup_type_variable_value(f2ptr cause, f2ptr fiber, f2ptr type, f2ptr variable) {
  f2ptr env   = f2fiber__env(fiber, cause);
  f2ptr value = f2__environment__lookup_type_var_value(cause, env, type, variable);
  if (raw__larva__is_type(cause, value)) {
    value = catch_value(f2__cause__lookup_type_var_value(cause, cause, type, variable),
			f2list8__new(cause, new__symbol(cause, "bug_name"),      new__symbol(cause, "variable_does_not_exist_for_this_fiber"),
				     new__symbol(cause, "this"),          fiber,
				     new__symbol(cause, "variable_type"), type,
				     new__symbol(cause, "variable_name"), variable));
  }
  return value;
}

boolean_t f2__fiber__execute_bytecode(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  debug__assert(raw__fiber__is_type(nil, fiber), nil, "fiber type assertion failed.");
  debug__assert(raw__bytecode__is_type(nil, bytecode), nil, "bytecode type assertion failed.");
  debug__assert((! cause) || raw__cause__is_type(nil, cause), nil, "fiber type assertion failed.");
  f2ptr command = f2bytecode__command(bytecode, cause);
  if      (command == __funk2.bytecode.bytecode__block_eval_args_next__symbol)       {f2__fiber__bytecode__block_eval_args_next(      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__lookup__symbol)                     {f2__fiber__bytecode__lookup(                    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_pop__symbol)                  {f2__fiber__bytecode__block_pop(                 fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__copy__symbol)                       {f2__fiber__bytecode__copy(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__funk__symbol)                       {f2__fiber__bytecode__funk(                      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_push__symbol)                 {f2__fiber__bytecode__block_push(                fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_eval_args_end__symbol)        {f2__fiber__bytecode__block_eval_args_end(       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_eval_args_begin__symbol)      {f2__fiber__bytecode__block_eval_args_begin(     fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__push__symbol)                       {f2__fiber__bytecode__push(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__pop__symbol)                        {f2__fiber__bytecode__pop(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_enter__symbol)                {f2__fiber__bytecode__block_enter(               fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_define_last_argument__symbol) {f2__fiber__bytecode__block_define_last_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_define_argument__symbol)      {f2__fiber__bytecode__block_define_argument(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__define__symbol)                     {f2__fiber__bytecode__define(                    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__else_jump__symbol)                  {f2__fiber__bytecode__else_jump(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_pop__symbol)         {f2__fiber__bytecode__block_exit_and_pop(        fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__jump__symbol)                       {f2__fiber__bytecode__jump(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__block_define_rest_argument__symbol) {f2__fiber__bytecode__block_define_rest_argument(fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__nop__symbol)                        {f2__fiber__bytecode__nop(                       fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__type_var__mutate__symbol)           {f2__fiber__bytecode__type_var__mutate(          fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__swap__symbol)                       {f2__fiber__bytecode__swap(                      fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__yield__symbol)                      {f2__fiber__bytecode__yield(                     fiber, bytecode); return boolean__true;}
  else if (command == __funk2.bytecode.bytecode__cons__symbol)                       {f2__fiber__bytecode__cons(                      fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__car__set__symbol)                   {f2__fiber__bytecode__car__set(                  fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__cdr__set__symbol)                   {f2__fiber__bytecode__cdr__set(                  fiber, bytecode);}
  else if (command == __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol)      {f2__fiber__bytecode__block_exit_and_no_pop(     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__numerically_equals__symbol)         {f2__fiber__bytecode__numerically_equals(        fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__add__symbol)                        {f2__fiber__bytecode__add(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__greater_than__symbol)               {f2__fiber__bytecode__greater_than(              fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__subtract__symbol)                   {f2__fiber__bytecode__subtract(                  fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__divide__symbol)                     {f2__fiber__bytecode__divide(                    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__multiply__symbol)                   {f2__fiber__bytecode__multiply(                  fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__less_than__symbol)                  {f2__fiber__bytecode__less_than(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__not__symbol)                        {f2__fiber__bytecode__not(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__globalize_type_var__symbol)         {f2__fiber__bytecode__globalize_type_var(        fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__push_constant__symbol)              {f2__fiber__bytecode__push_constant(             fiber, bytecode, f2bytecode__arg0(bytecode, cause));}

  else if (command == __funk2.bytecode.bytecode__array__symbol)                      {f2__fiber__bytecode__array(                     fiber, bytecode, f2bytecode__arg0(bytecode, cause));}
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
  else if (command == __funk2.bytecode.bytecode__eq__symbol)                         {f2__fiber__bytecode__eq(                        fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__and__symbol)                        {f2__fiber__bytecode__and(                       fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__or__symbol)                         {f2__fiber__bytecode__or(                        fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__negative__symbol)                   {f2__fiber__bytecode__negative(                  fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__inverse__symbol)                    {f2__fiber__bytecode__inverse(                   fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__modulo__symbol)                     {f2__fiber__bytecode__modulo(                    fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause), f2bytecode__arg2(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__increment__symbol)                  {f2__fiber__bytecode__increment(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  else if (command == __funk2.bytecode.bytecode__decrement__symbol)                  {f2__fiber__bytecode__decrement(                 fiber, bytecode, f2bytecode__arg0(bytecode, cause), f2bytecode__arg1(bytecode, cause));}
  
  else {
    f2__fiber__print(cause, fiber, command);
    f2__fiber__print(cause, fiber, bytecode);
    f2__fiber__print(cause, fiber, __funk2.bytecode.bytecode__block_enter__symbol);
    f2fiber__value__set(fiber, cause, f2larva__new(cause, 21, nil));
  }
  return boolean__false;
}

void f2__print_environment_stack(f2ptr cause, f2ptr fiber, f2ptr env) {
  f2ptr current_env_name__symbol = new__symbol(initial_cause(), "-current_env_name-");
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
  assert_argument_type(fiber, this);
  return raw__fiber__stack_trace(cause, this);
}
def_pcfunk1(fiber__stack_trace, this,
	    "",
	    return f2__fiber__stack_trace(this_cause, this));


f2ptr raw__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  f2ptr fiber_stack_trace = raw__fiber__stack_trace(cause, this);
  if (raw__larva__is_type(cause, fiber_stack_trace)) {
    return fiber_stack_trace;
  }
  return f2__fiber_stack_trace__print(cause, fiber_stack_trace);
}

f2ptr f2__fiber__print_stack_trace(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return raw__fiber__print_stack_trace(cause, this);
}
def_pcfunk1(fiber__print_stack_trace, this,
	    "Pretty prints a stack trace to help a human understand this fiber's current execution.",
	    return f2__fiber__print_stack_trace(this_cause, this));


f2ptr raw__fiber__wait_for_either_complete_or_encounter_bug__without_yield(f2ptr cause, f2ptr this) {
  f2ptr  this__fiber = f2__this__fiber(cause);
  f2ptr  exit_cmutex = f2__fiber__exit_cmutex(cause, this);
  {
    raw__cmutex__lock(cause, exit_cmutex);
    f2ptr exit_status = f2__fiber__exit_status(cause, this);
    if (exit_status == nil) {
      {
	f2ptr fiber__complete_trigger = f2fiber__complete_trigger(this, cause);
	f2ptr fiber__bug_trigger      = f2fiber__bug_trigger(     this, cause);
	f2__fiber_trigger__add_waiting_fiber(cause, fiber__complete_trigger, this__fiber);
	f2__fiber_trigger__add_waiting_fiber(cause, fiber__bug_trigger,      this__fiber);
      }
      f2__global_scheduler__remove_fiber(cause, this__fiber);
    }
    raw__cmutex__unlock(cause, exit_cmutex);
  }
  return nil;
}

f2ptr f2__fiber__wait_for_either_complete_or_encounter_bug__without_yield(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber, this);
  return raw__fiber__wait_for_either_complete_or_encounter_bug__without_yield(cause, this);
}
def_pcfunk1(fiber__wait_for_either_complete_or_encounter_bug__without_yield, this,
	    "",
	    return f2__fiber__wait_for_either_complete_or_encounter_bug__without_yield(this_cause, this));



void raw__fiber__handle_enter_virtual_processor(f2ptr cause, f2ptr this) {
  int pool_index = this_processor_thread__pool_index();
  raw__fiber__start_cycle_processor_bytes_allocated_count__set(cause, this, __funk2.memory.pool[pool_index].bytes_allocated_count);
  raw__fiber__start_cycle_execution_nanoseconds__set(cause, this, raw__nanoseconds_since_1970());
}

void raw__fiber__handle_exit_virtual_processor(f2ptr cause, f2ptr this) {
  {
    u64 end_execution_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    u64 start_cycle_execution_nanoseconds    = raw__fiber__start_cycle_execution_nanoseconds(cause, this);
    u64 execution_nanoseconds                = raw__fiber__execution_nanoseconds(cause, this);
    raw__fiber__execution_nanoseconds__set(cause, this, execution_nanoseconds + (end_execution_nanoseconds_since_1970 - start_cycle_execution_nanoseconds));
  }
  {
    int pool_index                                  = this_processor_thread__pool_index();
    u64 start_cycle_processor_bytes_allocated_count = raw__fiber__start_cycle_processor_bytes_allocated_count(cause, this);
    u64 bytes_allocated_count                       = raw__fiber__bytes_allocated_count(cause, this);
    raw__fiber__bytes_allocated_count__set(cause, this, bytes_allocated_count + __funk2.memory.pool[pool_index].bytes_allocated_count - start_cycle_processor_bytes_allocated_count);
  }
}



f2ptr raw__fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list30__new(cause,
						new__symbol(cause, "print_object_type"),          new__symbol(cause, "fiber"),
						new__symbol(cause, "cause_reg_cmutex"),           f2__fiber__cause_reg_cmutex(          cause, this),
						new__symbol(cause, "cause_reg"),                  f2__fiber__cause_reg(                 cause, this),
						new__symbol(cause, "keep_undead"),                f2__fiber__keep_undead(               cause, this),
						new__symbol(cause, "is_zombie"),                  f2__fiber__is_zombie(                 cause, this),
						new__symbol(cause, "is_complete"),                f2__fiber__is_complete(               cause, this),
						new__symbol(cause, "execute_cmutex"),             f2__fiber__execute_cmutex(            cause, this),
						new__symbol(cause, "paused"),                     f2__fiber__paused(                    cause, this),
						new__symbol(cause, "last_executed_time"),         f2__fiber__last_executed_time(        cause, this),
						new__symbol(cause, "sleep_until_time"),           f2__fiber__sleep_until_time(          cause, this),
						new__symbol(cause, "execution_nanoseconds"),      f2__fiber__execution_nanoseconds(     cause, this),
						new__symbol(cause, "bytecode_count"),             f2__fiber__bytecode_count(            cause, this),
						new__symbol(cause, "bytes_allocated_count"),      f2__fiber__bytes_allocated_count(     cause, this),
						new__symbol(cause, "processor_assignment_index"), f2__fiber__processor_assignment_index(cause, this),
						new__symbol(cause, "stack_trace"),                f2__fiber__stack_trace(               cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(fiber,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__fiber__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(fiber__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__fiber__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber__primobject_type__new(cause);
  {char* slot_name = "execution_nanoseconds";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__funk);}
  {char* slot_name = "execution_nanoseconds";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__set__funk);}
  {char* slot_name = "start_cycle_execution_nanoseconds";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__funk);}
  {char* slot_name = "start_cycle_execution_nanoseconds";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__set__funk);}
  {char* slot_name = "bytes_allocated_count";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__funk);}
  {char* slot_name = "bytes_allocated_count";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__set__funk);}
  {char* slot_name = "start_cycle_processor_bytes_allocated_count";             f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__funk);}
  {char* slot_name = "start_cycle_processor_bytes_allocated_count";             f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__set__funk);}
  {char* slot_name = "increase_bytecode_count";                                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.increase_bytecode_count__funk);}
  {char* slot_name = "do_sleep_until_time";                                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk);}
  {char* slot_name = "sleep_for_nanoseconds";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk);}
  {char* slot_name = "is_complete";                                             f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk);}
  {char* slot_name = "quit";                                                    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk);}
  {char* slot_name = "stack_trace";                                             f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__funk);}
  {char* slot_name = "wait_for_either_complete_or_encounter_bug-without_yield"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.wait_for_either_complete_or_encounter_bug__without_yield__funk);}
  {char* slot_name = "terminal_print_with_frame";                               f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__funk);}
  return this;
}





// fiber_stack_trace

def_primobject_1_slot(fiber_stack_trace,
		      stack);

f2ptr f2__fiber_stack_trace__new(f2ptr cause, f2ptr stack) {
  return f2fiber_stack_trace__new(cause, stack);
}
def_pcfunk1(fiber_stack_trace__new, stack,
	    "",
	    return f2__fiber_stack_trace__new(this_cause, stack));

f2ptr raw__fiber_stack_trace__as__string(f2ptr cause, f2ptr this) {
  return new__string(cause, "<fiber_stack_trace>");
}

f2ptr f2__fiber_stack_trace__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__as__string(cause, this);
}
def_pcfunk1(fiber_stack_trace__as__string, this,
	    "",
	    return f2__fiber_stack_trace__as__string(this_cause, this));


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
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__next(cause, this);
}
def_pcfunk1(fiber_stack_trace__next, this,
	    "",
	    return f2__fiber_stack_trace__next(this_cause, this));


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
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__first(cause, this);
}
def_pcfunk1(fiber_stack_trace__first, this,
	    "",
	    return f2__fiber_stack_trace__first(this_cause, this));


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
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__print(cause, this);
}
def_pcfunk1(fiber_stack_trace__print, this,
	    "",
	    return f2__fiber_stack_trace__print(this_cause, this));


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
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__as__printable(cause, this);
}
def_pcfunk1(fiber_stack_trace__as__printable, this,
	    "",
	    return f2__fiber_stack_trace__as__printable(this_cause, this));


f2ptr raw__fiber_stack_trace__blocks(f2ptr cause, f2ptr this) {
  f2ptr blocks      = nil;
  f2ptr blocks_iter = nil;
  f2ptr iter   = this;
  while (iter) {
    f2ptr block = raw__fiber_stack_trace__first(cause, iter);
    if (blocks == nil) {
      blocks      = f2cons__new(cause, block, nil);
      blocks_iter = blocks;
    } else {
      f2ptr next_blocks_iter = f2cons__new(cause, block, nil);
      f2__cons__cdr__set(cause, blocks_iter, next_blocks_iter);
      blocks_iter = next_blocks_iter;
    }
    iter = raw__fiber_stack_trace__next(cause, iter);
  }
  return blocks;
}

f2ptr f2__fiber_stack_trace__blocks(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace, this);
  return raw__fiber_stack_trace__blocks(cause, this);
}
def_pcfunk1(fiber_stack_trace__blocks, this,
	    "",
	    return f2__fiber_stack_trace__blocks(this_cause, this));


f2ptr raw__fiber_stack_trace__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "fiber_stack_trace"),
					       new__symbol(cause, "blocks"), f2__fiber_stack_trace__blocks(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber_stack_trace__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(fiber_stack_trace,    this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__fiber_stack_trace__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(fiber_stack_trace__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__fiber_stack_trace__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2fiber_stack_trace__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_stack_trace__primobject_type__new(cause);
  {char* slot_name = "as-string";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__funk);}
  {char* slot_name = "next";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__funk);}
  {char* slot_name = "first";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__funk);}
  {char* slot_name = "print";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__funk);}
  {char* slot_name = "as-printable";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__funk);}
  {char* slot_name = "blocks";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.blocks__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.terminal_print_with_frame__funk);}
  return this;
}


// fiber_stack_trace_block

def_primobject_2_slot(fiber_stack_trace_block,
		      funk,
		      argument_frame);

f2ptr f2__fiber_stack_trace_block__new(f2ptr cause, f2ptr funk, f2ptr argument_frame) {
  return f2fiber_stack_trace_block__new(cause, funk, argument_frame);
}
def_pcfunk2(fiber_stack_trace_block__new, funk, argument_frame,
	    "",
	    return f2__fiber_stack_trace_block__new(this_cause, funk, argument_frame));


f2ptr raw__fiber_stack_trace_block__funk_name(f2ptr cause, f2ptr this) {
  f2ptr funk = f2__fiber_stack_trace_block__funk(cause, this);
  f2ptr funk_name;
  if (raw__funkable__is_type(cause, funk)) {
    funk_name = f2__funkable__name(cause, funk);
  } else {
    funk_name = f2list2__new(cause, new__symbol(cause, "error:funk_is_not_funkable"), funk);
  }
  return funk_name;
}

f2ptr f2__fiber_stack_trace_block__funk_name(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace_block, this);
  return raw__fiber_stack_trace_block__funk_name(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__funk_name, this,
	    "",
	    return f2__fiber_stack_trace_block__funk_name(this_cause, this));


f2ptr raw__fiber_stack_trace_block__as__string(f2ptr cause, f2ptr this) {
  return new__string(cause, "<fiber_stack_trace_block>");
}

f2ptr f2__fiber_stack_trace_block__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace_block, this);
  return raw__fiber_stack_trace_block__as__string(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__as__string, this,
	    "",
	    return f2__fiber_stack_trace_block__as__string(this_cause, this));


f2ptr raw__fiber_stack_trace_block__printable_argument_frame(f2ptr cause, f2ptr this) {
  f2ptr argument_frame  = f2__fiber_stack_trace_block__argument_frame(cause, this);
  return f2__exp__printable_value(cause, argument_frame);
}

f2ptr f2__fiber_stack_trace_block__printable_argument_frame(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace_block, this);
  return raw__fiber_stack_trace_block__printable_argument_frame(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__printable_argument_frame, this,
	    "",
	    return f2__fiber_stack_trace_block__printable_argument_frame(this_cause, this));


f2ptr raw__fiber_stack_trace_block__print(f2ptr cause, f2ptr this) {
  f2__print(cause, f2__fiber_stack_trace_block__as__printable(cause, this));
  return nil;
}

f2ptr f2__fiber_stack_trace_block__print(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace_block, this);
  return raw__fiber_stack_trace_block__print(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__print, this,
	    "",
	    return f2__fiber_stack_trace_block__print(this_cause, this));


f2ptr raw__fiber_stack_trace_block__as__printable(f2ptr cause, f2ptr this) {
  f2ptr funk__name               = f2__fiber_stack_trace_block__funk_name(cause, this);
  f2ptr printable_argument_frame = f2__fiber_stack_trace_block__printable_argument_frame(cause, this);
  return f2list2__new(cause, funk__name, printable_argument_frame);
}

f2ptr f2__fiber_stack_trace_block__as__printable(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_stack_trace_block, this);
  return raw__fiber_stack_trace_block__as__printable(cause, this);
}
def_pcfunk1(fiber_stack_trace_block__as__printable, this,
	    "",
	    return f2__fiber_stack_trace_block__as__printable(this_cause, this));


f2ptr raw__fiber_stack_trace_block__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "fiber_stack_trace_block"),
					       new__symbol(cause, "funk_name"),         f2__fiber_stack_trace_block__funk_name(cause, this),
					       new__symbol(cause, "argument_frame"),    f2__fiber_stack_trace_block__argument_frame(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber_stack_trace_block__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(fiber_stack_trace_block, this);
  assert_argument_type(terminal_print_frame,    terminal_print_frame);
  return raw__fiber_stack_trace_block__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(fiber_stack_trace_block__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__fiber_stack_trace_block__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2fiber_stack_trace_block__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_stack_trace_block__primobject_type__new(cause);
  {char* slot_name = "funk_name";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.funk_name__funk);}
  {char* slot_name = "as-string";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__funk);}
  {char* slot_name = "printable_argument_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__funk);}
  {char* slot_name = "print";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__funk);}
  {char* slot_name = "as-printable";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__printable__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.terminal_print_with_frame__funk);}
  return this;
}





// **

void f2__fiber__defragment__fix_pointers() {
  // -- reinitialize --
  
  // initialize fiber register symbols
  defragment__fix_pointer(__fiber__program_counter_reg__symbol);
  defragment__fix_pointer(__fiber__iter_reg__symbol);
  defragment__fix_pointer(__fiber__env_reg__symbol);
  defragment__fix_pointer(__fiber__args_reg__symbol);
  defragment__fix_pointer(__fiber__return_reg__symbol);
  defragment__fix_pointer(__fiber__value_reg__symbol);
  
  // initialize other misc. symbols
  defragment__fix_pointer(__fiber__environment_critics__symbol);
  
  
  // -- initialize --
  
  // fiber
  
  initialize_primobject_30_slot__defragment__fix_pointers(fiber,
							  program_counter,
							  stack,
							  iter,
							  env,
							  args,
							  return_reg,
							  value,
							  trace,
							  cause_reg_cmutex,
							  cause_reg,
							  keep_undead,
							  is_zombie,
							  parent_fiber,
							  parent_env,
							  execute_cmutex,
							  paused,
							  last_executed_time,
							  sleep_until_time,
							  execution_nanoseconds_chunk,
							  start_cycle_execution_nanoseconds_chunk,
							  bytecode_count,
							  bytes_allocated_count_chunk,
							  start_cycle_processor_bytes_allocated_count_chunk,
							  processor_assignment_scheduler_cmutex,
							  processor_assignment_index,
							  should_quit,
							  exit_cmutex,
							  exit_status,
							  bug_trigger,
							  complete_trigger);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__execution_nanoseconds__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__start_cycle_execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__start_cycle_execution_nanoseconds__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__set__funk);
  

  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__bytes_allocated_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__start_cycle_processor_bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__start_cycle_processor_bytes_allocated_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__set__funk);
  

  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.increase_bytecode_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__increase_bytecode_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.increase_bytecode_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__do_sleep_until_time);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__sleep_for_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__is_complete);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__quit);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__stack_trace);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.wait_for_either_complete_or_encounter_bug__without_yield__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__wait_for_either_complete_or_encounter_bug__without_yield);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.wait_for_either_complete_or_encounter_bug__without_yield__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(fiber__print_stack_trace); 
  
  
  // fiber_stack_trace
  
  initialize_primobject_1_slot__defragment__fix_pointers(fiber_stack_trace,
							 stack);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__as__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__next);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__first);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__print);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__as__printable);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.terminal_print_with_frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.blocks__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace__blocks);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.blocks__funk);
  
  
  // fiber_stack_trace_block
  
  initialize_primobject_2_slot__defragment__fix_pointers(fiber_stack_trace_block,
							 funk,
							 argument_frame);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.funk_name__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace_block__funk_name);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.funk_name__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace_block__as__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace_block__printable_argument_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace_block__print);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_stack_trace_block__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.terminal_print_with_frame__funk);
}

void f2__fiber__reinitialize_globalvars() {
  f2ptr cause = f2_fiber_c__cause__new(initial_cause());
  
  // fiber
  
  initialize_primobject_30_slot(fiber,
				program_counter,
				stack,
				iter,
				env,
				args,
				return_reg,
				value,
				trace,
				cause_reg_cmutex,
				cause_reg,
				keep_undead,
				is_zombie,
				parent_fiber,
				parent_env,
				execute_cmutex,
				paused,
				last_executed_time,
				sleep_until_time,
				execution_nanoseconds_chunk,
				start_cycle_execution_nanoseconds_chunk,
				bytecode_count,
				bytes_allocated_count_chunk,
				start_cycle_processor_bytes_allocated_count_chunk,
				processor_assignment_scheduler_cmutex,
				processor_assignment_index,
				should_quit,
				exit_cmutex,
				exit_status,
				bug_trigger,
				complete_trigger);
  
  {char* symbol_str = "execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__execution_nanoseconds, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__funk = never_gc(cfunk);}
  {char* symbol_str = "execution_nanoseconds-set"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__execution_nanoseconds__set, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.execution_nanoseconds__set__funk = never_gc(cfunk);}
  {char* symbol_str = "start_cycle_execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__start_cycle_execution_nanoseconds, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__funk = never_gc(cfunk);}
  {char* symbol_str = "start_cycle_execution_nanoseconds-set"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__start_cycle_execution_nanoseconds__set, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_execution_nanoseconds__set__funk = never_gc(cfunk);}

  {char* symbol_str = "bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__bytes_allocated_count, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__funk = never_gc(cfunk);}
  {char* symbol_str = "bytes_allocated_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__bytes_allocated_count__set, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.bytes_allocated_count__set__funk = never_gc(cfunk);}
  {char* symbol_str = "start_cycle_processor_bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__start_cycle_processor_bytes_allocated_count, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__funk = never_gc(cfunk);}
  {char* symbol_str = "start_cycle_processor_bytes_allocated_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__start_cycle_processor_bytes_allocated_count__set, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.start_cycle_processor_bytes_allocated_count__set__funk = never_gc(cfunk);}

  {char* symbol_str = "increase_bytecode_count"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.increase_bytecode_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__increase_bytecode_count, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.increase_bytecode_count__funk = never_gc(cfunk);}
  {char* symbol_str = "do_sleep_until_time"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__do_sleep_until_time, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.do_sleep_until_time__funk = never_gc(cfunk);}
  {char* symbol_str = "sleep_for_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__sleep_for_nanoseconds, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.sleep_for_nanoseconds__funk = never_gc(cfunk);}
  {char* symbol_str = "is_complete"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__is_complete, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.is_complete__funk = never_gc(cfunk);}
  {char* symbol_str = "quit"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__quit, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.quit__funk = never_gc(cfunk);}
  {char* symbol_str = "stack_trace"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__stack_trace, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.stack_trace__funk = never_gc(cfunk);}
  {char* symbol_str = "wait_for_either_complete_or_encounter_bug-without_yield"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.wait_for_either_complete_or_encounter_bug__without_yield__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__wait_for_either_complete_or_encounter_bug__without_yield, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.wait_for_either_complete_or_encounter_bug__without_yield__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber__terminal_print_with_frame, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(fiber__print_stack_trace, this); 
  
  
  // fiber_stack_trace
  
  initialize_primobject_1_slot(fiber_stack_trace,
			       stack);
  
  {char* symbol_str = "as-string"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__as__string, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__string__funk = never_gc(cfunk);}
  {char* symbol_str = "next"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__next, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.next__funk = never_gc(cfunk);}
  {char* symbol_str = "first"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__first, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.first__funk = never_gc(cfunk);}
  {char* symbol_str = "print"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__print, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.print__funk = never_gc(cfunk);}
  {char* symbol_str = "as-printable"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__as__printable, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.as__printable__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(fiber_stack_trace__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.terminal_print_with_frame__funk = never_gc(cfunk);}
  {char* symbol_str = "blocks"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.blocks__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace__blocks, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace.blocks__funk = never_gc(cfunk);}
  
  
  // fiber_stack_trace_block
  
  initialize_primobject_2_slot(fiber_stack_trace_block,
			       funk,
			       argument_frame);
  
  {char* symbol_str = "funk_name"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.funk_name__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__funk_name, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.funk_name__funk = never_gc(cfunk);}
  {char* symbol_str = "as-string"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__as__string, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.as__string__funk = never_gc(cfunk);}
  {char* symbol_str = "printable_argument_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__printable_argument_frame, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.printable_argument_frame__funk = never_gc(cfunk);}
  {char* symbol_str = "print"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_stack_trace_block__print, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.print__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(fiber_stack_trace_block__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_stack_trace_block.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // reinitialize fiber register symbols
  __fiber__program_counter_reg__symbol = new__symbol(cause, "program_counter");
  __fiber__iter_reg__symbol            = new__symbol(cause, "iter");
  __fiber__env_reg__symbol             = new__symbol(cause, "env");
  __fiber__args_reg__symbol            = new__symbol(cause, "args");
  __fiber__return_reg__symbol          = new__symbol(cause, "return");
  __fiber__value_reg__symbol           = new__symbol(cause, "value");
  
  // reinitialize other misc. symbols
  __fiber__environment_critics__symbol = new__symbol(cause, "-environment_critics-");
  
}

void f2__fiber__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "fiber", "", &f2__fiber__reinitialize_globalvars, &f2__fiber__defragment__fix_pointers);
  
  f2__fiber__reinitialize_globalvars();
}

