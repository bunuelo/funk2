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

#ifndef F2__FIBER__TYPE__H
#define F2__FIBER__TYPE__H

// fiber

declare_object_type_18_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, execution_nanoseconds,
			    f2ptr do_sleep_until_time__symbol;   // execute
			    f2ptr do_sleep_until_time__funk;
			    f2ptr sleep_for_nanoseconds__symbol; // execute
			    f2ptr sleep_for_nanoseconds__funk;
			    f2ptr is_complete__symbol; // get
			    f2ptr is_complete__funk;
			    f2ptr quit__symbol; // execute
			    f2ptr quit__funk;
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

declare_primobject_18_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, execution_nanoseconds);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args);

#define __pure__f2fiber__is_complete(this, cause)  (!f2fiber__program_counter(this, cause))
#define f2fiber__is_complete(this, cause)          __pure__f2fiber__is_complete(this, cause)
//extern int f2fiber__is_complete(f2ptr this);

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time);
f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds);

f2ptr f2fiber__primobject_type__new_aux(f2ptr cause);





f2ptr f2__fiber__lookup_type_variable_value(f2ptr cause, f2ptr fiber, f2ptr type, f2ptr variable);

f2ptr global_critics();
void global_critics__set(f2ptr critics);

void f2__print_environment_stack(f2ptr cause, f2ptr rte, f2ptr env);

boolean_t f2__fiber__execute_bytecode(f2ptr cause, f2ptr fiber, f2ptr bytecode);
boolean_t f2__fiber__execute_next_bytecode(f2ptr cause, f2ptr fiber);

void f2__fiber__initialize();

#endif // F2__FIBER__H

