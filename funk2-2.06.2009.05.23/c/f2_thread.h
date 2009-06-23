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

#ifndef F2__THREAD__H
#define F2__THREAD__H

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

extern f2ptr __thread__execute_bytecode__cause__symbol;

extern f2ptr __thread__program_counter_reg__symbol;
extern f2ptr __thread__iter_reg__symbol;
extern f2ptr __thread__env_reg__symbol;
extern f2ptr __thread__args_reg__symbol;
extern f2ptr __thread__return_reg__symbol;
extern f2ptr __thread__value_reg__symbol;

f2ptr global_critics();
void global_critics__set(f2ptr critics);

//extern f2ptr __global__user_thread;

void print_bytecode_stats__cfunk(FILE* fptr);

void f2__print_environment_stack(f2ptr cause, f2ptr rte, f2ptr env);

void f2__thread__execute_bytecode(f2ptr cause, f2ptr thread, f2ptr bytecode);
boolean_t f2__thread__execute_next_bytecode(f2ptr cause, f2ptr thread);

void f2__thread__initialize();

//#define global_user_thread() __global__user_thread

#endif // F2__THREAD__H

