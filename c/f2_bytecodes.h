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

#ifndef F2__BYTECODES__H
#define F2__BYTECODES__H

#include "f2_ptypes.h"
#include "f2_compile.h"
#include "f2_primobject__frame.h"
#include "f2_thought_process.h"

typedef struct funk2_bytecode_s {
  f2ptr bytecode__funk__symbol;
  f2ptr bytecode__jump_funk__symbol;
  f2ptr bytecode__array__symbol;
  f2ptr bytecode__cons__symbol;
  f2ptr bytecode__consp__symbol;
  f2ptr bytecode__car__symbol;
  f2ptr bytecode__cdr__symbol;
  f2ptr bytecode__car__set__symbol;
  f2ptr bytecode__cdr__set__symbol;
  f2ptr bytecode__array_elt__symbol;
  f2ptr bytecode__set__symbol;
  f2ptr bytecode__swap__symbol;
  f2ptr bytecode__push__symbol;
  f2ptr bytecode__push_constant__symbol;
  f2ptr bytecode__pop__symbol;
  f2ptr bytecode__copy__symbol;
  f2ptr bytecode__lookup_type_var__symbol;
  f2ptr bytecode__define_type_var__symbol;
  f2ptr bytecode__type_var__mutate__symbol;
  f2ptr bytecode__globalize_type_var__symbol;
  f2ptr bytecode__jump__symbol;
  f2ptr bytecode__if_jump__symbol;
  f2ptr bytecode__else_jump__symbol;
  f2ptr bytecode__nop__symbol;
  f2ptr bytecode__debug__symbol;
  f2ptr bytecode__tracer__symbol;
  f2ptr bytecode__endfunk__symbol;
  f2ptr bytecode__compile__symbol;
  f2ptr bytecode__yield__symbol;
  f2ptr bytecode__newenv__symbol;
  f2ptr bytecode__machine_code__symbol;
  f2ptr bytecode__reg_array__elt__symbol;
  f2ptr bytecode__reg_array__elt__set__symbol;
  
  f2ptr expression_not_funkable__exception__tag;
  f2ptr expression_not_funkable__exception;
  
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

int                    f2__fiber__bytecode__funk(                            f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode_helper__funk__no_increment_pc_reg(f2ptr fiber, f2ptr cause, f2ptr bytecode);
int                    f2__fiber__bytecode__jump_funk(                       f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__array(                           f2ptr fiber, f2ptr bytecode, f2ptr length);
int                    f2__fiber__bytecode__cons(                            f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__consp(                           f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__car(                             f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__cdr(                             f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__car__set(                        f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__cdr__set(                        f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__array_elt(                       f2ptr fiber, f2ptr bytecode, f2ptr array, f2ptr index);
int                    f2__fiber__bytecode__array_elt__set(                  f2ptr fiber, f2ptr bytecode, f2ptr array, f2ptr index);
int                    f2__fiber__bytecode__set(                             f2ptr fiber, f2ptr bytecode, f2ptr reg, f2ptr exp);
int                    f2__fiber__bytecode__nop(                             f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__swap(                            f2ptr fiber, f2ptr bytecode, f2ptr reg0, f2ptr reg1);
int                    f2__fiber__bytecode__push_constant(                   f2ptr fiber, f2ptr bytecode, f2ptr constant);
int                    f2__fiber__bytecode__push(                            f2ptr fiber, f2ptr bytecode, f2ptr reg);
int                    f2__fiber__bytecode__pop(                             f2ptr fiber, f2ptr bytecode, f2ptr reg);
int                    f2__fiber__bytecode__copy(                            f2ptr fiber, f2ptr bytecode, f2ptr src_reg, f2ptr dest_reg);
int                    f2__fiber__bytecode__lookup_type_var(                 f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__define_type_var(                 f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__type_var__mutate(                f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__globalize_type_var(              f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var);
int                    f2__fiber__bytecode__jump(                            f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__if_jump(                         f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__else_jump(                       f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter);
int                    f2__fiber__bytecode__debug(                           f2ptr fiber, f2ptr bytecode, f2ptr value);
int                    f2__fiber__bytecode__tracer(                          f2ptr fiber, f2ptr bytecode, f2ptr name, f2ptr args);
int                    f2__fiber__bytecode__endfunk(                         f2ptr fiber, f2ptr bytecode, f2ptr funk);
int                    f2__fiber__bytecode__compile(                         f2ptr fiber, f2ptr bytecode, f2ptr protect_environment);
int                    f2__fiber__bytecode__yield(                           f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__newenv(                          f2ptr fiber, f2ptr bytecode);
int                    f2__fiber__bytecode__machine_code(                    f2ptr fiber, f2ptr bytecode, f2ptr chunk);
int                    f2__fiber__bytecode__reg_array__elt(                  f2ptr fiber, f2ptr bytecode, f2ptr reg);
int                    f2__fiber__bytecode__reg_array__elt__set(             f2ptr fiber, f2ptr bytecode, f2ptr reg);

bytecode_jump__f2ptr_t f2__compile__bytecode__set(    f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__swap(   f2ptr cause, f2ptr reg0, f2ptr reg1);
bytecode_jump_t        f2__compile__bytecode__push(   f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__pop(    f2ptr cause, f2ptr reg);
bytecode_jump_t        f2__compile__bytecode__copy(   f2ptr cause, f2ptr reg0, f2ptr reg1);
bytecode_jump_t        f2__compile__bytecode__compile(f2ptr protect_environment);

void                   f2__bytecodes__initialize();

#endif // F2__BYTECODES__H
