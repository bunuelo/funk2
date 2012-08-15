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

#ifndef F2__FIBER__TYPE__H
#define F2__FIBER__TYPE__H

// fiber

typedef struct funk2_object_type__fiber__slot_s funk2_object_type__fiber__slot_t;

declare_object_type_30_slot(fiber,
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
			    bytes_allocated_count,
			    start_cycle_processor_bytes_allocated_count,
			    processor_assignment_scheduler_cmutex,
			    processor_assignment_index,
			    should_quit,
			    exit_cmutex,
			    exit_status,
			    bug_trigger,
			    complete_trigger,
			    
			    f2ptr execution_nanoseconds__symbol;   // get
			    f2ptr execution_nanoseconds__funk;
			    f2ptr execution_nanoseconds__set__symbol;   // set
			    f2ptr execution_nanoseconds__set__funk;
			    f2ptr start_cycle_execution_nanoseconds__symbol;   // get
			    f2ptr start_cycle_execution_nanoseconds__funk;
			    f2ptr start_cycle_execution_nanoseconds__set__symbol;   // set
			    f2ptr start_cycle_execution_nanoseconds__set__funk;
			    f2ptr increase_bytecode_count__symbol;   // execute
			    f2ptr increase_bytecode_count__funk;
			    f2ptr do_sleep_until_time__symbol;   // execute
			    f2ptr do_sleep_until_time__funk;
			    f2ptr sleep_for_nanoseconds__symbol; // execute
			    f2ptr sleep_for_nanoseconds__funk;
			    f2ptr is_complete__symbol; // get
			    f2ptr is_complete__funk;
			    f2ptr quit__symbol; // execute
			    f2ptr quit__funk;
			    f2ptr stack_trace__symbol; // get
			    f2ptr stack_trace__funk;
			    f2ptr wait_for_either_complete_or_encounter_bug__without_yield__symbol; // execute
			    f2ptr wait_for_either_complete_or_encounter_bug__without_yield__funk;
			    f2ptr terminal_print_with_frame__symbol; // execute
			    f2ptr terminal_print_with_frame__funk;
			    );


// fiber_stack_trace

typedef struct funk2_object_type__fiber_stack_trace__slot_s funk2_object_type__fiber_stack_trace__slot_t;

declare_object_type_1_slot(fiber_stack_trace,
			   stack,
			   f2ptr as__string__symbol; // get
			   f2ptr as__string__funk;
			   f2ptr next__symbol; // get
			   f2ptr next__funk;
			   f2ptr first__symbol; // get
			   f2ptr first__funk;
			   f2ptr print__symbol; // execute
			   f2ptr print__funk;
			   f2ptr as__printable__symbol; // get
			   f2ptr as__printable__funk;
			   f2ptr blocks__symbol; // get
			   f2ptr blocks__funk;
			   f2ptr terminal_print_with_frame__symbol; // execute
			   f2ptr terminal_print_with_frame__funk;
			   );


// fiber_stack_trace_block

typedef struct funk2_object_type__fiber_stack_trace_block__slot_s funk2_object_type__fiber_stack_trace_block__slot_t;

declare_object_type_2_slot(fiber_stack_trace_block,
			   funk,
			   argument_frame,
			   f2ptr funk_name__symbol; // get
			   f2ptr funk_name__funk;
			   f2ptr as__string__symbol; // get
			   f2ptr as__string__funk;
			   f2ptr printable_argument_frame__symbol; // get
			   f2ptr printable_argument_frame__funk;
			   f2ptr print__symbol; // execute
			   f2ptr print__funk;
			   f2ptr as__printable__symbol; // get
			   f2ptr as__printable__funk;
			   f2ptr terminal_print_with_frame__symbol; // execute
			   f2ptr terminal_print_with_frame__funk;
			   );


#endif // F2__FIBER__TYPE__H


#ifndef F2__FIBER__H
#define F2__FIBER__H

#ifdef DEBUG_BYTECODES
#  define debug_bc(code) code
#  define print_bytecode_stats(fptr) print_bytecode_stats__cfunk(fptr)
#else
#  define debug_bc(code)
#  define print_bytecode_stats(fptr)
#endif // DEBUG_BYTECODES

#include "f2_global.h"
#include "f2_memory.h"
#include "f2_compile.h"
#include "f2_primobject__environment.h"
#include "f2_ptypes.h"
#include "f2_primfunks.h"
#include "f2_print.h"

extern f2ptr __fiber__execute_bytecode__cause__symbol;

extern f2ptr __fiber__program_counter_reg__symbol;
extern f2ptr __fiber__iter_reg__symbol;
extern f2ptr __fiber__env_reg__symbol;
extern f2ptr __fiber__args_reg__symbol;
extern f2ptr __fiber__return_reg__symbol;
extern f2ptr __fiber__value_reg__symbol;

// fiber

declare_primobject_30_slot(fiber,
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
			   bytes_allocated_count,
			   start_cycle_processor_bytes_allocated_count,
			   processor_assignment_scheduler_cmutex,
			   processor_assignment_index,
			   should_quit,
			   exit_cmutex,
			   exit_status,
			   bug_trigger,
			   complete_trigger);

f2ptr raw__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args);

#define __pure__f2fiber__is_complete(this, cause)  (f2fiber__program_counter(this, cause) == nil)
#define f2fiber__is_complete(this, cause)          __pure__f2fiber__is_complete(this, cause)

boolean_t raw__fiber__is_complete(f2ptr cause, f2ptr this);
f2ptr      f2__fiber__is_complete(f2ptr cause, f2ptr this);

void  raw__fiber__increase_bytecode_count       (f2ptr cause, f2ptr this, u64   relative_bytecode_count);
f2ptr  f2__fiber__increase_bytecode_count       (f2ptr cause, f2ptr this, f2ptr relative_bytecode_count);
f2ptr  f2__fiber__do_sleep_until_time           (f2ptr cause, f2ptr this, f2ptr until_time);
f2ptr  f2__fiber__sleep_for_nanoseconds         (f2ptr cause, f2ptr this, f2ptr nanoseconds);
void  raw__fiber__handle_enter_virtual_processor(f2ptr cause, f2ptr this);
void  raw__fiber__handle_exit_virtual_processor (f2ptr cause, f2ptr this);

f2ptr f2fiber__primobject_type__new_aux(f2ptr cause);





f2ptr f2__fiber__lookup_type_variable_value(f2ptr cause, f2ptr fiber, f2ptr type, f2ptr variable);

f2ptr global_critics();
void global_critics__set(f2ptr critics);

void f2__print_environment_stack(f2ptr cause, f2ptr rte, f2ptr env);

boolean_t f2__fiber__execute_bytecode(f2ptr cause, f2ptr fiber, f2ptr bytecode);
boolean_t f2__fiber__execute_next_bytecode(f2ptr cause, f2ptr fiber);

f2ptr raw__fiber__stack_trace(f2ptr cause, f2ptr this);
f2ptr  f2__fiber__stack_trace(f2ptr cause, f2ptr this);
f2ptr raw__fiber__print_stack_trace(f2ptr cause, f2ptr this);
f2ptr  f2__fiber__print_stack_trace(f2ptr cause, f2ptr this);

// fiber_stack_trace

declare_primobject_1_slot(fiber_stack_trace,
			  stack);

f2ptr f2__fiber_stack_trace__new(          f2ptr cause, f2ptr stack);
f2ptr f2__fiber_stack_trace__as__string(   f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace__next(         f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace__first(        f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace__print(        f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace__as__printable(f2ptr cause, f2ptr this);


f2ptr f2fiber_stack_trace__primobject_type__new_aux(f2ptr cause);


// fiber_stack_trace_block

declare_primobject_2_slot(fiber_stack_trace_block,
			  funk,
			  argument_frame);

f2ptr f2__fiber_stack_trace_block__new(                     f2ptr cause, f2ptr funk, f2ptr argument_frame);
f2ptr f2__fiber_stack_trace_block__as__string(              f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace_block__printable_argument_frame(f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace_block__print(                   f2ptr cause, f2ptr this);
f2ptr f2__fiber_stack_trace_block__as__printable(           f2ptr cause, f2ptr this);


f2ptr f2fiber_stack_trace_block__primobject_type__new_aux(f2ptr cause);


// **

void f2__fiber__initialize();

#endif // F2__FIBER__H

