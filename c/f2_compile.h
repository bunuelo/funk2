// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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
  f2ptr f2__compile__local_apply_exp__symbol;
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

#ifdef DEBUG_COMPILE
#  define bcs_valid(value) check_bcs_valid(value)
#else
#  define bcs_valid(value) value
#endif

#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_fiber.h"
#include "f2_bytecodes.h"
#include "f2_globalenv.h"
#include "f2_nil.h"



f2ptr f2__compile__funk_bc            (f2ptr cause);
f2ptr f2__compile__jump_funk          (f2ptr cause);
f2ptr f2__compile__funk_env           (f2ptr cause);
f2ptr f2__compile__funk_local_copy    (f2ptr cause, f2ptr funk);
f2ptr f2__compile__array              (f2ptr cause, f2ptr length);
f2ptr f2__compile__cons               (f2ptr cause);
f2ptr f2__compile__consp              (f2ptr cause);
f2ptr f2__compile__car                (f2ptr cause);
f2ptr f2__compile__cdr                (f2ptr cause);
f2ptr f2__compile__car__set           (f2ptr cause);
f2ptr f2__compile__cdr__set           (f2ptr cause);
f2ptr f2__compile__array_elt          (f2ptr cause, f2ptr array, f2ptr index);
f2ptr f2__compile__set                (f2ptr cause, f2ptr reg, f2ptr exp);
f2ptr f2__compile__value__set         (f2ptr cause, f2ptr exp);
f2ptr f2__compile__iter__set          (f2ptr cause, f2ptr exp);
f2ptr f2__compile__args__set          (f2ptr cause, f2ptr exp);
f2ptr f2__compile__env__set           (f2ptr cause, f2ptr exp);
f2ptr f2__compile__swap               (f2ptr cause, f2ptr reg0, f2ptr reg1);
f2ptr f2__compile__swap_value_and_iter(f2ptr cause);
f2ptr f2__compile__swap_value_and_args(f2ptr cause);
f2ptr f2__compile__push_constant      (f2ptr cause, f2ptr constant);
f2ptr f2__compile__push               (f2ptr cause, f2ptr reg);
f2ptr f2__compile__push_value         (f2ptr cause);
f2ptr f2__compile__push_iter          (f2ptr cause);
f2ptr f2__compile__push_args          (f2ptr cause);
f2ptr f2__compile__push_env           (f2ptr cause);
f2ptr f2__compile__push_return        (f2ptr cause);
f2ptr f2__compile__pop                (f2ptr cause, f2ptr reg);
f2ptr f2__compile__pop_value          (f2ptr cause);
f2ptr f2__compile__pop_iter           (f2ptr cause);
f2ptr f2__compile__pop_args           (f2ptr cause);
f2ptr f2__compile__pop_env            (f2ptr cause);
f2ptr f2__compile__pop_return         (f2ptr cause);
f2ptr f2__compile__pop_nil            (f2ptr cause);
f2ptr f2__compile__copy               (f2ptr cause, f2ptr reg0, f2ptr reg1);
f2ptr f2__compile__copy_value_to_args (f2ptr cause);
f2ptr f2__compile__copy_value_to_iter (f2ptr cause);
f2ptr f2__compile__copy_iter_to_value (f2ptr cause);
f2ptr f2__compile__copy_iter_to_args  (f2ptr cause);
f2ptr f2__compile__copy_args_to_value (f2ptr cause);
f2ptr f2__compile__copy_args_to_iter  (f2ptr cause);
f2ptr f2__compile__copy_pc_to_return  (f2ptr cause);
f2ptr f2__compile__copy_return_to_pc  (f2ptr cause);

f2ptr f2__compile__lookup     (f2ptr cause, f2ptr type, f2ptr var);
f2ptr f2bytecode__lookup__type(f2ptr this, f2ptr cause);
f2ptr f2bytecode__lookup__var (f2ptr this, f2ptr cause);

f2ptr f2__compile__define            (f2ptr cause, f2ptr type, f2ptr var);
f2ptr f2__compile__type_var__mutate  (f2ptr cause, f2ptr type, f2ptr var);
f2ptr f2__compile__globalize_type_var(f2ptr cause, f2ptr type, f2ptr var);
f2ptr f2__compile__jump              (f2ptr cause, f2ptr new_pc);
f2ptr f2__compile__if_jump           (f2ptr cause, f2ptr new_pc);
f2ptr f2__compile__else_jump         (f2ptr cause, f2ptr new_pc);
f2ptr f2__compile__nop               (f2ptr cause);
f2ptr f2__compile__return_bytecode   (f2ptr cause);
f2ptr f2__compile__debug             (f2ptr cause, f2ptr value);
f2ptr f2__compile__tracer            (f2ptr cause, f2ptr name, f2ptr args);
f2ptr f2__compile__endfunk           (f2ptr cause, f2ptr funk);
f2ptr f2__compile__compile           (f2ptr cause, f2ptr protect_environment);
f2ptr f2__compile__yield             (f2ptr cause);
f2ptr f2__compile__newenv            (f2ptr cause);

f2ptr f2__compile__lookup_var    (f2ptr cause, f2ptr var);
f2ptr f2__compile__lookup_funkvar(f2ptr cause, f2ptr funkvar);

f2ptr f2__compile__define_var    (f2ptr cause, f2ptr var);
f2ptr f2__compile__define_funkvar(f2ptr cause, f2ptr var);

f2ptr f2__compile__var__mutate    (f2ptr cause, f2ptr var);
f2ptr f2__compile__funkvar__mutate(f2ptr cause, f2ptr var);

f2ptr f2__compile__globalize_var    (f2ptr cause, f2ptr var);
f2ptr f2__compile__globalize_funkvar(f2ptr cause, f2ptr var);

// logic
f2ptr f2__compile__eq (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__not(f2ptr cause, f2ptr result, f2ptr x);
f2ptr f2__compile__and(f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__or (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);

// math
f2ptr f2__compile__add               (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__negative          (f2ptr cause, f2ptr result, f2ptr x);
f2ptr f2__compile__subtract          (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__multiply          (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__inverse           (f2ptr cause, f2ptr result, f2ptr x);
f2ptr f2__compile__divide            (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__modulo            (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__increment         (f2ptr cause, f2ptr result, f2ptr x);
f2ptr f2__compile__decrement         (f2ptr cause, f2ptr result, f2ptr x);
f2ptr f2__compile__numerically_equals(f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__less_than         (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);
f2ptr f2__compile__greater_than      (f2ptr cause, f2ptr result, f2ptr x0, f2ptr x1);

// block
f2ptr f2__compile__block_push                (f2ptr cause);
f2ptr f2__compile__block_enter               (f2ptr cause);
f2ptr f2__compile__block_define_rest_argument(f2ptr cause, f2ptr argument);
f2ptr f2__compile__block_define_argument     (f2ptr cause, f2ptr argument);
f2ptr f2__compile__block_define_last_argument(f2ptr cause, f2ptr argument);
f2ptr f2__compile__block_pop                 (f2ptr cause);
f2ptr f2__compile__block_exit_and_pop        (f2ptr cause, f2ptr funk);
f2ptr f2__compile__block_exit_and_no_pop     (f2ptr cause, f2ptr funk);
f2ptr f2__compile__block_eval_args_begin     (f2ptr cause);
f2ptr f2__compile__block_eval_args_next      (f2ptr cause);
f2ptr f2__compile__block_eval_args_end       (f2ptr cause);


f2ptr      f2__compile__symbol                              (f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__wrong_argument_number__bcs__set              (f2ptr cause, f2ptr bytecodes);
f2ptr      f2__compile__push_debug_funk_call                (f2ptr cause);
f2ptr      f2__compile__pop_debug_funk_call                 (f2ptr cause);
boolean_t raw__expression__is_funktional                    (f2ptr cause, f2ptr expression);
f2ptr     raw__expression__optimize                         (f2ptr cause, f2ptr expression);
f2ptr      f2__expression__optimize                         (f2ptr cause, f2ptr expression);
f2ptr      f2__compile__funk                                (f2ptr simple_cause, f2ptr fiber, f2ptr funk);
f2ptr      f2__compile__metro                               (f2ptr simple_cause, f2ptr fiber, f2ptr metro);
f2ptr     raw__list_cdr__set                                (f2ptr cause, f2ptr seq, f2ptr cdr_value);
f2ptr      f2__compile__if                                  (f2ptr simple_cause, f2ptr cond_bcs, f2ptr true_bcs, f2ptr false_bcs);
f2ptr      f2__compile__rawcode                             (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional,
							     boolean_t optimize_unused);
f2ptr      f2__compile__if_exp                              (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__while                               (f2ptr simple_cause, f2ptr cond_bcs, f2ptr loop_bcs);
f2ptr      f2__compile__while_exp                           (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__return                              (f2ptr simple_cause, f2ptr value_bcs, boolean_t popped_env_and_return);
f2ptr      f2__compile__return_exp                          (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__lookup_funkvar_exp                  (f2ptr simple_cause, f2ptr exps);
f2ptr      f2__compile__eval_args                           (f2ptr simple_cause, f2ptr fiber, f2ptr args, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__define_funk_exp                     (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__define_exp                          (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__mutate_exp                          (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__mutatefunk_exp                      (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__globalize_var_exp                   (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__globalize_funkvar_exp               (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__apply_exp                           (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return);
f2ptr      f2__compile__local_apply_exp                     (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return);
f2ptr      f2__compile__funkvar_call                        (f2ptr simple_cause, f2ptr fiber, f2ptr exps, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr     raw__apply_metro                                  (f2ptr simple_cause, f2ptr fiber, f2ptr metro, f2ptr args);
f2ptr     raw__apply_funk                                   (f2ptr simple_cause, f2ptr fiber, f2ptr funk, f2ptr args);
f2ptr      f2__compile__backquote_exp                       (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__backquote_append_exp                (f2ptr simple_cause, f2ptr fiber, f2ptr exps);
f2ptr      f2__compile__bytecode_eq_exp                     (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_not_exp                    (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_and_exp                    (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_or_exp                     (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_add_exp                    (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_negative_exp               (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_subtract_exp               (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_multiply_exp               (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_inverse_exp                (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_divide_exp                 (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_modulo_exp                 (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_increment_exp              (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_decrement_exp              (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_numerically_equals_exp     (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_less_than_exp              (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr      f2__compile__bytecode_greater_than_exp           (f2ptr cause, f2ptr fiber, f2ptr exp);
boolean_t raw__is_compile_special_symbol                    (f2ptr cause, f2ptr exp);
f2ptr      f2__compile__special_symbol_exp                  (f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__demetropolize__funkvar_call                  (f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr      f2__compile__cons_exp                            (f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__bytecode_exp                        (f2ptr cause, f2ptr exp, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__compile__rawcode_exp                         (f2ptr cause, f2ptr exp, f2ptr fiber, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t* popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);
f2ptr      f2__demetropolize__special_symbol_exp            (f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr      f2__demetropolize_once                           (f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr      f2__demetropolize_full__with_status              (f2ptr simple_cause, f2ptr fiber, f2ptr env, f2ptr exp);
f2ptr     raw__funk__new_with_replaced_variable             (f2ptr cause, f2ptr this, f2ptr replace_variable, f2ptr replace_argument);
f2ptr     raw__undemetropolized_expression__replace_variable(f2ptr cause, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument);
f2ptr     raw__expression__replace_variable                 (f2ptr cause, f2ptr expression, f2ptr replace_variable, f2ptr replace_argument);
f2ptr     raw__compile                                      (f2ptr simple_cause, f2ptr fiber, f2ptr exp, boolean_t protect_environment, boolean_t optimize_tail_recursion, boolean_t *popped_env_and_return, boolean_t* is_funktional, f2ptr local_variables, boolean_t* is_locally_funktional);



// **

void f2__compile__initialize();

#endif // F2__COMPILE__H

