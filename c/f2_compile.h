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

#ifndef F2__COMPILE__H
#define F2__COMPILE__H

#ifdef DEBUG_COMPILE
#  define bcs_valid(value) check_bcs_valid(value)
#else
#  define bcs_valid(value) value
#endif

#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_thread.h"
#include "f2_bytecodes.h"
#include "f2_globalenv.h"

extern f2ptr check_bcs_valid(f2ptr bytecodes);

extern f2ptr __wrong_argument_number__bcs;

extern f2ptr f2__compile__funk_bc(f2ptr cause, bool tracewrap);

extern f2ptr f2__compile__funk(f2ptr context, bool tracewrap, f2ptr thread, f2ptr metro);
extern f2ptr f2__compile__metro(f2ptr context, bool tracewrap, f2ptr thread, f2ptr metro);
extern f2ptr f2__compile__rawcode(f2ptr context, bool tracewrap, f2ptr thread, f2ptr exps, bool protect_environment, bool optimize_tail_recursion, bool* popped_env_and_return, bool* is_funktional);
extern f2ptr f2__demetropolize_once(f2ptr context, f2ptr thread, f2ptr env, f2ptr exp);
extern f2ptr f2__demetropolize_full__with_status(f2ptr context, f2ptr thread, f2ptr env, f2ptr exp);
extern f2ptr f2__compile__special_symbol_exp(f2ptr context, bool tracewrap, f2ptr rte, f2ptr exp, bool protect_environment, bool optimize_tail_recursion, bool *popped_env_and_return, bool* is_funktional);
extern f2ptr raw__compile(f2ptr context, bool tracewrap, f2ptr thread, f2ptr exp, bool protect_environment, bool optimize_tail_recursion, bool *popped_env_and_return, bool* is_funktional);

extern void f2__compile__initialize();

#endif // F2__COMPILE__H

