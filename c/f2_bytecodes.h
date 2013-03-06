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

#ifndef F2__BYTECODES__H
#define F2__BYTECODES__H

#include "f2_ptypes.h"
#include "f2_compile.h"
#include "f2_primobject__frame.h"

typedef struct funk2_bytecode_s {
  f2ptr bytecode__funk__symbol;
  u64   bytecode__funk__execution_count;
  f2ptr bytecode__jump_funk__symbol;
  u64   bytecode__jump_funk__execution_count;
  f2ptr bytecode__funk_env__symbol;
  u64   bytecode__funk_env__execution_count;
  f2ptr bytecode__jump_machine_code__symbol;
  u64   bytecode__jump_machine_code__execution_count;
  f2ptr bytecode__funk_local_copy__symbol;
  u64   bytecode__funk_local_copy__execution_count;
  f2ptr bytecode__array__symbol;
  u64   bytecode__array__execution_count;
  f2ptr bytecode__cons__symbol;
  u64   bytecode__cons__execution_count;
  f2ptr bytecode__consp__symbol;
  u64   bytecode__consp__execution_count;
  f2ptr bytecode__car__symbol;
  u64   bytecode__car__execution_count;
  f2ptr bytecode__cdr__symbol;
  u64   bytecode__cdr__execution_count;
  f2ptr bytecode__car__set__symbol;
  u64   bytecode__car__set__execution_count;
  f2ptr bytecode__cdr__set__symbol;
  u64   bytecode__cdr__set__execution_count;
  f2ptr bytecode__array_elt__symbol;
  u64   bytecode__array_elt__execution_count;
  f2ptr bytecode__set__symbol;
  u64   bytecode__set__execution_count;
  f2ptr bytecode__swap__symbol;
  u64   bytecode__swap__execution_count;
  f2ptr bytecode__push__symbol;
  u64   bytecode__push__execution_count;
  f2ptr bytecode__push_constant__symbol;
  u64   bytecode__push_constant__execution_count;
  f2ptr bytecode__pop__symbol;
  u64   bytecode__pop__execution_count;
  f2ptr bytecode__copy__symbol;
  u64   bytecode__copy__execution_count;
  f2ptr bytecode__lookup__symbol;
  u64   bytecode__lookup__execution_count;
  f2ptr bytecode__define__symbol;
  u64   bytecode__define__execution_count;
  f2ptr bytecode__type_var__mutate__symbol;
  u64   bytecode__type_var__mutate__execution_count;
  f2ptr bytecode__globalize_type_var__symbol;
  u64   bytecode__globalize_type_var__execution_count;
  f2ptr bytecode__jump__symbol;
  u64   bytecode__jump__execution_count;
  f2ptr bytecode__if_jump__symbol;
  u64   bytecode__if_jump__execution_count;
  f2ptr bytecode__else_jump__symbol;
  u64   bytecode__else_jump__execution_count;
  f2ptr bytecode__nop__symbol;
  u64   bytecode__nop__execution_count;
  f2ptr bytecode__debug__symbol;
  u64   bytecode__debug__execution_count;
  f2ptr bytecode__tracer__symbol;
  u64   bytecode__tracer__execution_count;
  f2ptr bytecode__endfunk__symbol;
  u64   bytecode__endfunk__execution_count;
  f2ptr bytecode__compile__symbol;
  u64   bytecode__compile__execution_count;
  f2ptr bytecode__yield__symbol;
  u64   bytecode__yield__execution_count;
  f2ptr bytecode__newenv__symbol;
  u64   bytecode__newenv__execution_count;
  f2ptr bytecode__machine_code__symbol;
  u64   bytecode__machine_code__execution_count;
  
  // logic
  f2ptr bytecode__eq__symbol;
  u64   bytecode__eq__execution_count;
  f2ptr bytecode__not__symbol;
  u64   bytecode__not__execution_count;
  f2ptr bytecode__and__symbol;
  u64   bytecode__and__execution_count;
  f2ptr bytecode__or__symbol;
  u64   bytecode__or__execution_count;
  
  // math
  f2ptr bytecode__add__symbol;
  u64   bytecode__add__execution_count;
  f2ptr bytecode__negative__symbol;
  u64   bytecode__negative__execution_count;
  f2ptr bytecode__subtract__symbol;
  u64   bytecode__subtract__execution_count;
  f2ptr bytecode__multiply__symbol;
  u64   bytecode__multiply__execution_count;
  f2ptr bytecode__inverse__symbol;
  u64   bytecode__inverse__execution_count;
  f2ptr bytecode__divide__symbol;
  u64   bytecode__divide__execution_count;
  f2ptr bytecode__modulo__symbol;
  u64   bytecode__modulo__execution_count;
  f2ptr bytecode__increment__symbol;
  u64   bytecode__increment__execution_count;
  f2ptr bytecode__decrement__symbol;
  u64   bytecode__decrement__execution_count;
  f2ptr bytecode__numerically_equals__symbol;
  u64   bytecode__numerically_equals__execution_count;
  f2ptr bytecode__less_than__symbol;
  u64   bytecode__less_than__execution_count;
  f2ptr bytecode__greater_than__symbol;
  u64   bytecode__greater_than__execution_count;
  
  // block
  f2ptr bytecode__block_push__symbol;
  u64   bytecode__block_push__execution_count;
  f2ptr bytecode__block_enter__symbol;
  u64   bytecode__block_enter__execution_count;
  f2ptr bytecode__block_define_rest_argument__symbol;
  u64   bytecode__block_define_rest_argument__execution_count;
  f2ptr bytecode__block_define_argument__symbol;
  u64   bytecode__block_define_argument__execution_count;
  f2ptr bytecode__block_define_last_argument__symbol;
  u64   bytecode__block_define_last_argument__execution_count;
  f2ptr bytecode__block_pop__symbol;
  u64   bytecode__block_pop__execution_count;
  f2ptr bytecode__block_exit_and_pop__symbol;
  u64   bytecode__block_exit_and_pop__execution_count;
  f2ptr bytecode__block_exit_and_no_pop__symbol;
  u64   bytecode__block_exit_and_no_pop__execution_count;
  f2ptr bytecode__block_eval_args_begin__symbol;
  u64   bytecode__block_eval_args_begin__execution_count;
  f2ptr bytecode__block_eval_args_next__symbol;
  u64   bytecode__block_eval_args_next__execution_count;
  f2ptr bytecode__block_eval_args_end__symbol;
  u64   bytecode__block_eval_args_end__execution_count;
  
  f2ptr expression_not_funkable__exception__tag;
  
  int push_pop_value_difference;
  int push_pop_iter_difference;
  int push_pop_program_counter_difference;
  int push_pop_args_difference;
  int push_pop_return_difference;
  int push_pop_env_difference;
  int push_pop_trace_difference;
  
  int bytecode_trace__print_depth;
} funk2_bytecode_t;

void funk2_bytecode__init(funk2_bytecode_t* this);
void funk2_bytecode__destroy(funk2_bytecode_t* this);

// There is no significance to the fact that the cause and fiber variables appear in different orders for the fiber push and pop functions.
// A global decision has been made as to the correct order: (funk2_type_t subfunk_this, f2ptr cause, f2ptr fiber, f2ptr this, f2ptr arg0, f2ptr arg1, ...)

void f2__fiber__stack__push_value(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_iter(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_program_counter(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_args(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_return(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_env(f2ptr cause, f2ptr fiber);
void f2__fiber__stack__push_trace(f2ptr cause, f2ptr fiber);

void f2__fiber__stack__pop_value(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_iter(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_program_counter(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_args(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_return(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_env(f2ptr fiber, f2ptr cause);
void f2__fiber__stack__pop_trace(f2ptr fiber, f2ptr cause);


// bytecode_jump_t is used for compiling bytecodes to machine code jump pointers

typedef int (*bytecode_jump_t)(             f2ptr fiber, f2ptr bytecode);
typedef int (*bytecode_jump__f2ptr_t)(      f2ptr fiber, f2ptr bytecode, f2ptr arg0);
typedef int (*bytecode_jump__f2ptr_f2ptr_t)(f2ptr fiber, f2ptr bytecode, f2ptr arg0, f2ptr arg1);


// bytecode definitions (and bytecode_jump compiling functions)

int                    f2__fiber__bytecode__funk                                   (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode_helper__funk__no_increment_pc_reg       (f2ptr fiber, f2ptr cause, f2ptr bytecode);
int                    f2__fiber__bytecode__jump_funk                              (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__funk_env                               (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__jump_machine_code                      (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__funk_local_copy                        (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__array                                  (f2ptr fiber, f2ptr bytecode, f2ptr length);
int                    f2__fiber__bytecode__cons                                   (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__conslist                               (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__consp                                  (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__car                                    (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__cdr                                    (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__car__set                               (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__cdr__set                               (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__array_elt                              (f2ptr fiber, f2ptr bytecode, f2ptr array, f2ptr index);
int                    f2__fiber__bytecode__array_elt__set                         (f2ptr fiber, f2ptr bytecode, f2ptr array, f2ptr index);
int                    f2__fiber__bytecode__set                                    (f2ptr fiber, f2ptr bytecode, f2ptr reg, f2ptr exp);
int                    f2__fiber__bytecode__nop                                    (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__swap                                   (f2ptr fiber, f2ptr bytecode, f2ptr reg0, f2ptr reg1);
int                    f2__fiber__bytecode__push_constant                          (f2ptr fiber, f2ptr bytecode, f2ptr constant);
int                    f2__fiber__bytecode__push                                   (f2ptr fiber, f2ptr bytecode, f2ptr reg);
int                    f2__fiber__bytecode__pop                                    (f2ptr fiber, f2ptr bytecode, f2ptr reg);
int                    f2__fiber__bytecode__copy                                   (f2ptr fiber, f2ptr bytecode, f2ptr src_reg, f2ptr dest_reg);
int                    f2__fiber__bytecode__lookup                                 (f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__define                                 (f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__type_var__mutate                       (f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__globalize_type_var                     (f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__jump                                   (f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__if_jump                                (f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__else_jump                              (f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__debug                                  (f2ptr fiber, f2ptr bytecode, f2ptr value);
int                    f2__fiber__bytecode__tracer                                 (f2ptr fiber, f2ptr bytecode, f2ptr name, f2ptr args);
int                    f2__fiber__bytecode__endfunk                                (f2ptr fiber, f2ptr bytecode, f2ptr funk);
int                    f2__fiber__bytecode__compile                                (f2ptr fiber, f2ptr bytecode, f2ptr protect_environment);
int                    f2__fiber__bytecode__yield                                  (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__newenv                                 (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__machine_code                           (f2ptr fiber, f2ptr bytecode, f2ptr chunk);

// logic
int                    f2__fiber__bytecode__eq__no_increment_pc_reg                (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__eq                                     (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__not__no_increment_pc_reg               (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__not                                    (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__and__no_increment_pc_reg               (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__and                                    (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__or__no_increment_pc_reg                (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__or                                     (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);

// math
int                    f2__fiber__bytecode__add__no_increment_pc_reg               (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__add                                    (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__negative__no_increment_pc_reg          (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__negative                               (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__subtract__no_increment_pc_reg          (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__subtract                               (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__multiply__no_increment_pc_reg          (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__multiply                               (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__inverse__no_increment_pc_reg           (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__inverse                                (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__divide__no_increment_pc_reg            (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__divide                                 (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__modulo__no_increment_pc_reg            (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__modulo                                 (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__increment__no_increment_pc_reg         (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__increment                              (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__decrement__no_increment_pc_reg         (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__decrement                              (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x);
int                    f2__fiber__bytecode__numerically_equals__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__numerically_equals                     (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__less_than__no_increment_pc_reg         (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__less_than                              (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__greater_than__no_increment_pc_reg      (f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);
int                    f2__fiber__bytecode__greater_than                           (f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1);

// block
int                    f2__fiber__bytecode__block_push                             (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__block_enter                            (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__block_define_rest_argument             (f2ptr fiber, f2ptr bytecode, f2ptr argument);
int                    f2__fiber__bytecode__block_define_argument                  (f2ptr fiber, f2ptr bytecode, f2ptr argument);
int                    f2__fiber__bytecode__block_define_last_argument             (f2ptr fiber, f2ptr bytecode, f2ptr argument);
int                    f2__fiber__bytecode__block_pop                              (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__block_exit_and_pop                     (f2ptr fiber, f2ptr bytecode, f2ptr funk);
int                    f2__fiber__bytecode__block_exit_and_no_pop                  (f2ptr fiber, f2ptr bytecode, f2ptr funk);
int                    f2__fiber__bytecode__block_eval_args_begin                  (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__block_eval_args_next                   (f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__block_eval_args_end                    (f2ptr fiber, f2ptr bytecode);



bytecode_jump__f2ptr_t f2__compile__bytecode__set(    f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__swap(   f2ptr cause, f2ptr reg0, f2ptr reg1);
bytecode_jump_t        f2__compile__bytecode__push(   f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__pop(    f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__copy(   f2ptr cause, f2ptr reg0, f2ptr reg1);
bytecode_jump_t        f2__compile__bytecode__compile(f2ptr protect_environment);

void                   f2__bytecodes__initialize();

#endif // F2__BYTECODES__H
