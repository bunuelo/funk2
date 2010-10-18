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

#ifndef F2__COMPILE__TYPE__H
#define F2__COMPILE__TYPE__H

typedef struct funk2_compile_s funk2_compile_t;
struct funk2_compile_s {
  f2ptr cause__compiled_from__symbol;
  f2ptr compile__exception;
  
  f2ptr f2__compile__funk__symbol;
  f2ptr f2__compile__metro__symbol;
  f2ptr f2__compile__if__symbol;
  f2ptr f2__compile__if_exp__symbol;
  f2ptr f2__compile__while__symbol;
  f2ptr f2__compile__while_exp__symbol;
  f2ptr f2__compile__return__symbol;
  f2ptr f2__compile__return_exp__symbol;
  f2ptr f2__compile__rawcode__symbol;
  f2ptr f2__compile__lookup_funkvar_exp__symbol;
  f2ptr f2__compile__eval_args__symbol;
  f2ptr f2__compile__eval_args__current_arg__symbol;
  f2ptr f2__compile__define_funk_exp__symbol;
  f2ptr f2__compile__define_exp__symbol;
  f2ptr f2__compile__mutate_exp__symbol;
  f2ptr f2__compile__mutatefunk_exp__symbol;
  f2ptr f2__compile__globalize_var_exp__symbol;
  f2ptr f2__compile__globalize_funkvar_exp__symbol;
  f2ptr f2__compile__apply_exp__symbol;
  f2ptr f2__compile__funkvar_call__symbol;
  f2ptr raw__apply_metro__symbol;
  f2ptr raw__apply_funk__symbol;
  f2ptr f2__compile__backquote_exp__symbol;
  f2ptr f2__compile__backquote_append_exp__symbol;
  f2ptr f2__compile__special_symbol_exp__symbol;
  f2ptr f2__compile__cons_exp__symbol;
  f2ptr f2__demetropolize__special_symbol_exp__symbol;
  f2ptr f2__demetropolize__funkvar_call__symbol;
  f2ptr f2__demetropolize_once__symbol;
  f2ptr f2__demetropolize_full__symbol;
  f2ptr raw__compile__symbol;
  
  f2ptr debug_funk_call__symbol;
  
  f2ptr wrong_argument_number__bcs;
};


#endif // F2__COMPILE__TYPE__H

#ifndef F2__COMPILE__H
#define F2__COMPILE__H

//#ifdef DEBUG_COMPILE
#define bcs_valid(value) check_bcs_valid(value)
//#else
//#  define bcs_valid(value) value
//#endif

#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_fiber.h"
#include "f2_bytecodes.h"
#include "f2_globalenv.h"

f2ptr check_bcs_valid(f2ptr bytecodes);

f2ptr f2__compile__funk_bc(f2ptr cause);

f2ptr f2__compile__funk(f2ptr cause, f2ptr fiber, f2ptr metro);
f2ptr f2__compile__metro(f2ptr cause, f2ptr fiber, f2ptr metro);
f2ptr f2__compile__rawcode(f2ptr cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional, boolean_t optimize_unused_beginning);
f2ptr f2__compile__bytecode_exp(f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr f2__compile__rawcode_exp(f2ptr cause, f2ptr exp, f2ptr fiber, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr f2__demetropolize_once(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr f2__demetropolize_full__with_status(f2ptr cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr f2__compile__special_symbol_exp(f2ptr cause, f2ptr rte, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr raw__compile(f2ptr context_on, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);

void f2__compile__initialize();

#endif // F2__COMPILE__H

