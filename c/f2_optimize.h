// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__OPTIMIZE__TYPES__H
#define F2__OPTIMIZE__TYPES__H

// optimize_cause

typedef struct funk2_object_type__optimize_cause__slot_s funk2_object_type__optimize_cause__slot_t;
declare_object_type_3_slot(optimize_cause,
			   cause_type,
			   name,
			   args,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_data

typedef struct funk2_object_type__optimize_data__slot_s funk2_object_type__optimize_data__slot_t;
declare_object_type_3_slot(optimize_data,
			   data_type,
			   name,
			   optimize_cause,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_side_effect

typedef struct funk2_object_type__optimize_side_effect__slot_s funk2_object_type__optimize_side_effect__slot_t;
declare_object_type_3_slot(optimize_side_effect,
			   side_effect_type,
			   name,
			   optimize_cause,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// optimize_fiber

typedef struct funk2_object_type__optimize_fiber__slot_s funk2_object_type__optimize_fiber__slot_t;
declare_object_type_12_slot(optimize_fiber,
			    optimize_context,
			    parent_branched_fiber,
			    optimize_cause,
			    children_branched_fibers,
			    optimize_side_effects,
			    stack,
			    value,
			    iter,
			    program_counter,
			    args,
			    return_reg,
			    env,
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

// optimize_context

typedef struct funk2_object_type__optimize_context__slot_s funk2_object_type__optimize_context__slot_t;
declare_object_type_5_slot(optimize_context,
			   initial_fiber,
			   active_fiber_set,
			   branched_fiber_set,
			   finished_fiber_set,
			   compile_expression,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__OPTIMIZE__TYPES__H


#ifndef F2__OPTIMIZE__H
#define F2__OPTIMIZE__H

#include "f2_frame_objects.h"

// optimize_cause

declare_primobject_3_slot(optimize_cause,
			  cause_type,
			  name,
			  args);

f2ptr f2optimize_cause__primobject_type__new_aux(f2ptr cause);


// optimize_data

declare_primobject_3_slot(optimize_data,
			  data_type,
			  name,
			  optimize_cause);

f2ptr raw__optimize_data__as__compile_expression(f2ptr cause, f2ptr this);

f2ptr f2optimize_data__primobject_type__new_aux(f2ptr cause);


// optimize_side_effect

declare_primobject_3_slot(optimize_side_effect,
			  side_effect_type,
			  name,
			  optimize_cause);

f2ptr raw__optimize_side_effect__as__compile_expression(f2ptr cause, f2ptr this);

f2ptr f2optimize_side_effect__primobject_type__new_aux(f2ptr cause);


// optimize_fiber

declare_primobject_12_slot(optimize_fiber,
			   optimize_context,
			   parent_branched_fiber,
			   optimize_cause,
			   children_branched_fibers,
			   optimize_side_effects,
			   stack,
			   value,
			   iter,
			   program_counter,
			   args,
			   return_reg,
			   env);

f2ptr raw__optimize_fiber__as__compile_expression(f2ptr cause, f2ptr this);

f2ptr f2optimize_fiber__primobject_type__new_aux(f2ptr cause);


// optimize_context

declare_primobject_5_slot(optimize_context,
			  initial_fiber,
			  active_fiber_set,
			  branched_fiber_set,
			  finished_fiber_set,
			  compile_expression);

f2ptr  f2__optimize_context__new                      (f2ptr cause);
void  raw__optimize_context__add_active_fiber         (f2ptr cause, f2ptr this, f2ptr active_fiber);
f2ptr raw__optimize_context__active_fiber_finished    (f2ptr cause, f2ptr this, f2ptr active_fiber);
f2ptr raw__optimize_context__active_fiber_branched    (f2ptr cause, f2ptr this, f2ptr active_fiber);
f2ptr raw__optimize_context__execute_one_bytecode     (f2ptr cause, f2ptr this);
f2ptr raw__optimize_context__complete_simulation      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2optimize_context__primobject_type__new_aux(f2ptr cause);














// optimize_bytecodes

f2ptr raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc                (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__jump__funk                                 (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__funk__no_increment_pc                      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__funk                                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__array__no_increment_pc                     (f2ptr cause, f2ptr this, f2ptr length);
f2ptr raw__optimize_fiber__call_bytecode__array                                      (f2ptr cause, f2ptr this, f2ptr length);
f2ptr raw__optimize_fiber__call_bytecode__cons__no_increment_pc                      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__cons                                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__conslist__no_increment_pc                  (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__conslist                                   (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__consp__no_increment_pc                     (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__consp                                      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__car__no_increment_pc                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__car                                        (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__cdr__no_increment_pc                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__cdr                                        (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__car__set__no_increment_pc                  (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__car__set                                   (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc                  (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__cdr__set                                   (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__array_elt__no_increment_pc                 (f2ptr cause, f2ptr this, f2ptr array, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__array_elt                                  (f2ptr cause, f2ptr this, f2ptr array, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__set__no_increment_pc                       (f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp);
f2ptr raw__optimize_fiber__call_bytecode__set                                        (f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp);
f2ptr raw__optimize_fiber__call_bytecode__swap__no_increment_pc                      (f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1);
f2ptr raw__optimize_fiber__call_bytecode__swap                                       (f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1);
f2ptr raw__optimize_fiber__call_bytecode__push__no_increment_pc                      (f2ptr cause, f2ptr this, f2ptr register_name);
f2ptr raw__optimize_fiber__call_bytecode__push                                       (f2ptr cause, f2ptr this, f2ptr register_name);
f2ptr raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc             (f2ptr cause, f2ptr this, f2ptr constant);
f2ptr raw__optimize_fiber__call_bytecode__push_constant                              (f2ptr cause, f2ptr this, f2ptr constant);
f2ptr raw__optimize_fiber__call_bytecode__pop__no_increment_pc                       (f2ptr cause, f2ptr this, f2ptr register_name);
f2ptr raw__optimize_fiber__call_bytecode__pop                                        (f2ptr cause, f2ptr this, f2ptr register_name);
f2ptr raw__optimize_fiber__call_bytecode__copy__no_increment_pc                      (f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name);
f2ptr raw__optimize_fiber__call_bytecode__copy                                       (f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name);
f2ptr raw__optimize_fiber__call_bytecode__lookup__no_increment_pc                    (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__lookup                                     (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__define__no_increment_pc                    (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__define                                     (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var__no_increment_pc          (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var                           (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var__no_increment_pc       (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var                        (f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name);
f2ptr raw__optimize_fiber__call_bytecode__jump__no_increment_pc                      (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__jump                                       (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__if__jump__no_increment_pc                  (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__if__jump                                   (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc                (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__else__jump                                 (f2ptr cause, f2ptr this, f2ptr new_program_counter);
f2ptr raw__optimize_fiber__call_bytecode__nop__no_increment_pc                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__nop                                        (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__debug__no_increment_pc                     (f2ptr cause, f2ptr this, f2ptr debug_value);
f2ptr raw__optimize_fiber__call_bytecode__debug                                      (f2ptr cause, f2ptr this, f2ptr debug_value);
f2ptr raw__optimize_fiber__call_bytecode__tracer__no_increment_pc                    (f2ptr cause, f2ptr this, f2ptr name, f2ptr args);
f2ptr raw__optimize_fiber__call_bytecode__tracer                                     (f2ptr cause, f2ptr this, f2ptr name, f2ptr args);
f2ptr raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc                   (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__endfunk                                    (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__compile__no_increment_pc                   (f2ptr cause, f2ptr this, f2ptr protect_environment);
f2ptr raw__optimize_fiber__call_bytecode__compile                                    (f2ptr cause, f2ptr this, f2ptr protect_environment);
f2ptr raw__optimize_fiber__call_bytecode__yield__no_increment_pc                     (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__yield                                      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__newenv__no_increment_pc                    (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__newenv                                     (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__machine_code__no_increment_pc              (f2ptr cause, f2ptr this, f2ptr chunk);
f2ptr raw__optimize_fiber__call_bytecode__machine_code                               (f2ptr cause, f2ptr this, f2ptr chunk);
f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__no_increment_pc            (f2ptr cause, f2ptr this, f2ptr x_register_name, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt                             (f2ptr cause, f2ptr this, f2ptr x_register_name, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__set__no_increment_pc       (f2ptr cause, f2ptr this, f2ptr x_register_name, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__reg_array__elt__set                        (f2ptr cause, f2ptr this, f2ptr x_register_name, f2ptr index);
f2ptr raw__optimize_fiber__call_bytecode__eq__no_increment_pc                        (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__eq                                         (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__not__no_increment_pc                       (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__not                                        (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__and__no_increment_pc                       (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__and                                        (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__or__no_increment_pc                        (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__or                                         (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__add__no_increment_pc                       (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__add                                        (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__negative__no_increment_pc                  (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__negative                                   (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__subtract__no_increment_pc                  (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__subtract                                   (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__multiply__no_increment_pc                  (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__multiply                                   (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__inverse__no_increment_pc                   (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__inverse                                    (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__divide__no_increment_pc                    (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__divide                                     (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__modulo__no_increment_pc                    (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__modulo                                     (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__increment__no_increment_pc                 (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__increment                                  (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__decrement__no_increment_pc                 (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__decrement                                  (f2ptr cause, f2ptr this, f2ptr result_register, f2ptr x_register_name);
f2ptr raw__optimize_fiber__call_bytecode__numerically_equals__no_increment_pc        (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__numerically_equals                         (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__less_than__no_increment_pc                 (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__less_than                                  (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__greater_than__no_increment_pc              (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__greater_than                               (f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name);
f2ptr raw__optimize_fiber__call_bytecode__block_push__no_increment_pc                (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_push                                 (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_enter__no_increment_pc               (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_enter                                (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument                 (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_define_argument__no_increment_pc     (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_define_argument                      (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument                 (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc                 (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_pop                                  (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop__no_increment_pc        (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop                         (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop__no_increment_pc     (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop                      (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin__no_increment_pc     (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin                      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next__no_increment_pc      (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next                       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end__no_increment_pc       (f2ptr cause, f2ptr this);
f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end                        (f2ptr cause, f2ptr this);



// funk-optimize

f2ptr raw__funk__optimize(f2ptr cause, f2ptr this);
f2ptr  f2__funk__optimize(f2ptr cause, f2ptr this);


// **

void f2__optimize__reinitialize_globalvars();
void f2__optimize__initialize();


#endif // F2__OPTIMIZE__H
