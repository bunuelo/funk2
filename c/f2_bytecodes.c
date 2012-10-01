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

void funk2_bytecode__init(funk2_bytecode_t* this) {
  this->bytecode__funk__symbol                                = -1;
  this->bytecode__funk__execution_count                       = 0;
  this->bytecode__jump_funk__symbol                           = -1;
  this->bytecode__jump_funk__execution_count                  = 0;
  this->bytecode__array__symbol                               = -1;
  this->bytecode__array__execution_count                      = 0;
  this->bytecode__cons__symbol                                = -1;
  this->bytecode__cons__execution_count                       = 0;
  this->bytecode__consp__symbol                               = -1;
  this->bytecode__consp__execution_count                      = 0;
  this->bytecode__car__symbol                                 = -1;
  this->bytecode__car__execution_count                        = 0;
  this->bytecode__cdr__symbol                                 = -1;
  this->bytecode__cdr__execution_count                        = 0;
  this->bytecode__car__set__symbol                            = -1;
  this->bytecode__car__set__execution_count                   = 0;
  this->bytecode__cdr__set__symbol                            = -1;
  this->bytecode__cdr__set__execution_count                   = 0;
  this->bytecode__array_elt__symbol                           = -1;
  this->bytecode__array_elt__execution_count                  = 0;
  this->bytecode__swap__symbol                                = -1;
  this->bytecode__swap__execution_count                       = 0;
  this->bytecode__push_constant__symbol                       = -1;
  this->bytecode__push_constant__execution_count              = 0;
  this->bytecode__push__symbol                                = -1;
  this->bytecode__push__execution_count                       = 0;
  this->bytecode__pop__symbol                                 = -1;
  this->bytecode__pop__execution_count                        = 0;
  this->bytecode__copy__symbol                                = -1;
  this->bytecode__copy__execution_count                       = 0;
  this->bytecode__lookup__symbol                              = -1;
  this->bytecode__lookup__execution_count                     = 0;
  this->bytecode__define__symbol                              = -1;
  this->bytecode__define__execution_count                     = 0;
  this->bytecode__type_var__mutate__symbol                    = -1;
  this->bytecode__type_var__mutate__execution_count           = 0;
  this->bytecode__globalize_type_var__symbol                  = -1;
  this->bytecode__globalize_type_var__execution_count         = 0;
  this->bytecode__jump__symbol                                = -1;
  this->bytecode__jump__execution_count                       = 0;
  this->bytecode__if_jump__symbol                             = -1;
  this->bytecode__if_jump__execution_count                    = 0;
  this->bytecode__else_jump__symbol                           = -1;
  this->bytecode__else_jump__execution_count                  = 0;
  this->bytecode__nop__symbol                                 = -1; // null operation (should be stripped out before executing [ideally])
  this->bytecode__nop__execution_count                        = 0;
  this->bytecode__debug__symbol                               = -1;
  this->bytecode__debug__execution_count                      = 0;
  this->bytecode__tracer__symbol                              = -1;
  this->bytecode__tracer__execution_count                     = 0;
  this->bytecode__compile__symbol                             = -1;
  this->bytecode__compile__execution_count                    = 0;
  this->bytecode__yield__symbol                               = -1;
  this->bytecode__yield__execution_count                      = 0;
  this->bytecode__newenv__symbol                              = -1;
  this->bytecode__newenv__execution_count                     = 0;
  this->bytecode__machine_code__symbol                        = -1;
  this->bytecode__machine_code__execution_count               = 0;
  
  // logic
  this->bytecode__eq__symbol                                  = -1;
  this->bytecode__eq__execution_count                         = 0;
  this->bytecode__not__symbol                                 = -1;
  this->bytecode__not__execution_count                        = 0;
  this->bytecode__and__symbol                                 = -1;
  this->bytecode__and__execution_count                        = 0;
  this->bytecode__or__symbol                                  = -1;
  this->bytecode__or__execution_count                         = 0;
  
  // math
  this->bytecode__add__symbol                                 = -1;
  this->bytecode__add__execution_count                        = 0;
  this->bytecode__negative__symbol                            = -1;
  this->bytecode__negative__execution_count                   = 0;
  this->bytecode__subtract__symbol                            = -1;
  this->bytecode__subtract__execution_count                   = 0;
  this->bytecode__multiply__symbol                            = -1;
  this->bytecode__multiply__execution_count                   = 0;
  this->bytecode__inverse__symbol                             = -1;
  this->bytecode__inverse__execution_count                    = 0;
  this->bytecode__divide__symbol                              = -1;
  this->bytecode__divide__execution_count                     = 0;
  this->bytecode__modulo__symbol                              = -1;
  this->bytecode__modulo__execution_count                     = 0;
  this->bytecode__increment__symbol                           = -1;
  this->bytecode__increment__execution_count                  = 0;
  this->bytecode__decrement__symbol                           = -1;
  this->bytecode__decrement__execution_count                  = 0;
  this->bytecode__numerically_equals__symbol                  = -1;
  this->bytecode__numerically_equals__execution_count         = 0;
  this->bytecode__less_than__symbol                           = -1;
  this->bytecode__less_than__execution_count                  = 0;
  this->bytecode__greater_than__symbol                        = -1;
  this->bytecode__greater_than__execution_count               = 0;
  
  // block
  this->bytecode__block_push__symbol                          = -1;
  this->bytecode__block_push__execution_count                 = 0;
  this->bytecode__block_enter__symbol                         = -1;
  this->bytecode__block_enter__execution_count                = 0;
  this->bytecode__block_define_rest_argument__symbol          = -1;
  this->bytecode__block_define_rest_argument__execution_count = 0;
  this->bytecode__block_define_argument__symbol               = -1;
  this->bytecode__block_define_argument__execution_count      = 0;
  this->bytecode__block_define_last_argument__symbol          = -1;
  this->bytecode__block_define_last_argument__execution_count = 0;
  this->bytecode__block_pop__symbol                           = -1;
  this->bytecode__block_pop__execution_count                  = 0;
  this->bytecode__block_exit_and_pop__symbol                  = -1;
  this->bytecode__block_exit_and_pop__execution_count         = 0;
  this->bytecode__block_exit_and_no_pop__symbol               = -1;
  this->bytecode__block_exit_and_no_pop__execution_count      = 0;
  this->bytecode__block_eval_args_begin__symbol               = -1;
  this->bytecode__block_eval_args_begin__execution_count      = 0;
  this->bytecode__block_eval_args_next__symbol                = -1;
  this->bytecode__block_eval_args_next__execution_count       = 0;
  this->bytecode__block_eval_args_end__symbol                 = -1;
  this->bytecode__block_eval_args_end__execution_count        = 0;
  
  this->bytecode_trace__print_depth = 3;
  
  this->expression_not_funkable__exception__tag = -1;
  
  this->push_pop_value_difference           = 0;
  this->push_pop_iter_difference            = 0;
  this->push_pop_program_counter_difference = 0;
  this->push_pop_args_difference            = 0;
  this->push_pop_return_difference          = 0;
  this->push_pop_env_difference             = 0;
  this->push_pop_trace_difference           = 0;
  
  this->bytecode_trace__print_depth = 3;
}

void funk2_bytecode__destroy(funk2_bytecode_t* this) {
  status("bytecode execution counts follow:");
  status("  bytecode__block_eval_args_next__execution_count       = " u64__fstr, this->bytecode__block_eval_args_next__execution_count);
  status("  bytecode__lookup__execution_count                     = " u64__fstr, this->bytecode__lookup__execution_count);
  status("  bytecode__block_pop__execution_count                  = " u64__fstr, this->bytecode__block_pop__execution_count);
  status("  bytecode__copy__execution_count                       = " u64__fstr, this->bytecode__copy__execution_count);
  status("  bytecode__funk__execution_count                       = " u64__fstr, this->bytecode__funk__execution_count);
  status("  bytecode__block_push__execution_count                 = " u64__fstr, this->bytecode__block_push__execution_count);
  status("  bytecode__block_eval_args_end__execution_count        = " u64__fstr, this->bytecode__block_eval_args_end__execution_count);
  status("  bytecode__block_eval_args_begin__execution_count      = " u64__fstr, this->bytecode__block_eval_args_begin__execution_count);
  status("  bytecode__push__execution_count                       = " u64__fstr, this->bytecode__push__execution_count);
  status("  bytecode__pop__execution_count                        = " u64__fstr, this->bytecode__pop__execution_count);
  status("  bytecode__block_enter__execution_count                = " u64__fstr, this->bytecode__block_enter__execution_count);
  status("  bytecode__block_define_last_argument__execution_count = " u64__fstr, this->bytecode__block_define_last_argument__execution_count);
  status("  bytecode__block_define_argument__execution_count      = " u64__fstr, this->bytecode__block_define_argument__execution_count);
  status("  bytecode__define__execution_count                     = " u64__fstr, this->bytecode__define__execution_count);
  status("  bytecode__else_jump__execution_count                  = " u64__fstr, this->bytecode__else_jump__execution_count);
  status("  bytecode__block_exit_and_pop__execution_count         = " u64__fstr, this->bytecode__block_exit_and_pop__execution_count);
  status("  bytecode__jump__execution_count                       = " u64__fstr, this->bytecode__jump__execution_count);
  status("  bytecode__block_define_rest_argument__execution_count = " u64__fstr, this->bytecode__block_define_rest_argument__execution_count);
  status("  bytecode__nop__execution_count                        = " u64__fstr, this->bytecode__nop__execution_count);
  status("  bytecode__type_var__mutate__execution_count           = " u64__fstr, this->bytecode__type_var__mutate__execution_count);
  status("  bytecode__swap__execution_count                       = " u64__fstr, this->bytecode__swap__execution_count);
  status("  bytecode__yield__execution_count                      = " u64__fstr, this->bytecode__yield__execution_count);
  status("  bytecode__cons__execution_count                       = " u64__fstr, this->bytecode__cons__execution_count);
  status("  bytecode__car__set__execution_count                   = " u64__fstr, this->bytecode__car__set__execution_count);
  status("  bytecode__cdr__set__execution_count                   = " u64__fstr, this->bytecode__cdr__set__execution_count);
  status("  bytecode__block_exit_and_no_pop__execution_count      = " u64__fstr, this->bytecode__block_exit_and_no_pop__execution_count);
  status("  bytecode__numerically_equals__execution_count         = " u64__fstr, this->bytecode__numerically_equals__execution_count);
  status("  bytecode__add__execution_count                        = " u64__fstr, this->bytecode__add__execution_count);
  status("  bytecode__greater_than__execution_count               = " u64__fstr, this->bytecode__greater_than__execution_count);
  status("  bytecode__subtract__execution_count                   = " u64__fstr, this->bytecode__subtract__execution_count);
  status("  bytecode__divide__execution_count                     = " u64__fstr, this->bytecode__divide__execution_count);
  status("  bytecode__multiply__execution_count                   = " u64__fstr, this->bytecode__multiply__execution_count);
  status("  bytecode__less_than__execution_count                  = " u64__fstr, this->bytecode__less_than__execution_count);
  status("  bytecode__not__execution_count                        = " u64__fstr, this->bytecode__not__execution_count);
  // zero counts
  status("  bytecode__globalize_type_var__execution_count         = " u64__fstr, this->bytecode__globalize_type_var__execution_count);
  status("  bytecode__push_constant__execution_count              = " u64__fstr, this->bytecode__push_constant__execution_count);
  status("  bytecode__jump_funk__execution_count                  = " u64__fstr, this->bytecode__jump_funk__execution_count);
  status("  bytecode__array__execution_count                      = " u64__fstr, this->bytecode__array__execution_count);
  status("  bytecode__consp__execution_count                      = " u64__fstr, this->bytecode__consp__execution_count);
  status("  bytecode__car__execution_count                        = " u64__fstr, this->bytecode__car__execution_count);
  status("  bytecode__cdr__execution_count                        = " u64__fstr, this->bytecode__cdr__execution_count);
  status("  bytecode__array_elt__execution_count                  = " u64__fstr, this->bytecode__array_elt__execution_count);
  status("  bytecode__if_jump__execution_count                    = " u64__fstr, this->bytecode__if_jump__execution_count);
  status("  bytecode__debug__execution_count                      = " u64__fstr, this->bytecode__debug__execution_count);
  status("  bytecode__tracer__execution_count                     = " u64__fstr, this->bytecode__tracer__execution_count);
  status("  bytecode__compile__execution_count                    = " u64__fstr, this->bytecode__compile__execution_count);
  status("  bytecode__newenv__execution_count                     = " u64__fstr, this->bytecode__newenv__execution_count);
  status("  bytecode__machine_code__execution_count               = " u64__fstr, this->bytecode__machine_code__execution_count);
  status("  bytecode__eq__execution_count                         = " u64__fstr, this->bytecode__eq__execution_count);
  status("  bytecode__and__execution_count                        = " u64__fstr, this->bytecode__and__execution_count);
  status("  bytecode__or__execution_count                         = " u64__fstr, this->bytecode__or__execution_count);
  status("  bytecode__negative__execution_count                   = " u64__fstr, this->bytecode__negative__execution_count);
  status("  bytecode__inverse__execution_count                    = " u64__fstr, this->bytecode__inverse__execution_count);
  status("  bytecode__modulo__execution_count                     = " u64__fstr, this->bytecode__modulo__execution_count);
  status("  bytecode__increment__execution_count                  = " u64__fstr, this->bytecode__increment__execution_count);
  status("  bytecode__decrement__execution_count                  = " u64__fstr, this->bytecode__decrement__execution_count);
}

// raw push and pop stack

/*
void raw__fiber__stack__raw_push(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr     old_stack          = f2fiber__stack(this, cause);
  boolean_t changed_free_stack = boolean__false;
  f2ptr     new_free_stack     = nil;
  f2ptr     new_cons           = nil;
  if (fiber__enable_stack_reuse) {
    f2ptr old_free_stack = f2fiber__free_stack(this, cause);
    if (old_free_stack != nil) {
      //status("reusing old_free_stack!");
      {
	new_cons           = old_free_stack;
	new_free_stack     = f2cons__cdr(old_free_stack, cause);
	changed_free_stack = boolean__true;
      }
      f2cons__car__set(new_cons, cause, value);
      f2cons__cdr__set(new_cons, cause, old_stack);
    } else {
      new_cons = raw__stack_cons__new(cause, value, old_stack);
    }
  } else {
    new_cons = raw__stack_cons__new(cause, value, old_stack);
  }
  f2fiber__stack__set(this, cause, new_cons);
  if (changed_free_stack) {
    f2fiber__free_stack__set(this, cause, new_free_stack);
  }
}

f2ptr raw__fiber__stack__raw_peek(f2ptr cause, f2ptr this) {
  f2ptr stack = f2fiber__stack(this, cause);
  if (stack == nil) {
    error(nil, "fiber stack is nil.");
  }
  f2ptr return_value = f2cons__car(stack, cause);
  return return_value;
}

void raw__fiber__stack__raw_pop(f2ptr cause, f2ptr this) {
  f2ptr free_cons = f2fiber__stack(this, cause);
  if (free_cons == nil) {
    error(nil, "fiber stack is nil.");
  }
  f2ptr new_stack = f2cons__cdr(free_cons, cause);
  if (fiber__enable_stack_reuse) {
    //status("adding to free_stack!");
    f2ptr old_free_stack = f2fiber__free_stack(this, cause);
    f2cons__car__set(free_cons, cause, nil);
    f2cons__cdr__set(free_cons, cause, old_free_stack);
    f2ptr new_free_stack = free_cons;
    f2fiber__free_stack__set(this, cause, new_free_stack);
  }
  f2fiber__stack__set(this, cause, new_stack);
}
*/

// push registers

void raw__fiber__stack__push_constant       (f2ptr cause, f2ptr this, f2ptr constant) {raw__fiber__push_stack(cause, this, constant);}
void raw__fiber__stack__push_value          (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__value(          this, cause));}
void raw__fiber__stack__push_iter           (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__iter(           this, cause));}
void raw__fiber__stack__push_program_counter(f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__program_counter(this, cause));}
void raw__fiber__stack__push_args           (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__args(           this, cause));}
void raw__fiber__stack__push_return_reg     (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__return_reg(     this, cause));}
void raw__fiber__stack__push_env            (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__env(            this, cause));}
void raw__fiber__stack__push_trace          (f2ptr cause, f2ptr this)                 {raw__fiber__push_stack(cause, this, f2fiber__trace(          this, cause));}

// pop registers

void  raw__fiber__stack__pop_value          (f2ptr cause, f2ptr this) {f2fiber__value__set(          this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_iter           (f2ptr cause, f2ptr this) {f2fiber__iter__set(           this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_program_counter(f2ptr cause, f2ptr this) {f2fiber__program_counter__set(this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_args           (f2ptr cause, f2ptr this) {f2fiber__args__set(           this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_return_reg     (f2ptr cause, f2ptr this) {f2fiber__return_reg__set(     this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_env            (f2ptr cause, f2ptr this) {f2fiber__env__set(            this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_trace          (f2ptr cause, f2ptr this) {f2fiber__trace__set(          this, cause, raw__fiber__peek_stack(cause, this)); raw__fiber__pop_stack(cause, this);}
void  raw__fiber__stack__pop_nil            (f2ptr cause, f2ptr this) {                                                                                 raw__fiber__pop_stack(cause, this);}


f2ptr f2__expression_not_funkable__exception__new(f2ptr cause, f2ptr funktion) {return f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, funktion);}

void unrecognized_bytecode_register__error(f2ptr fiber, f2ptr cause, char* bytecode_name, f2ptr reg) {
  char reg_utf8_str[1024];
  if(raw__symbol__is_type(cause, reg)) {
    raw__symbol__utf8_str_copy(cause, reg, (u8*)reg_utf8_str);
    reg_utf8_str[raw__symbol__utf8_length(cause, reg)] = (u8)0;
  } else {
    sprintf(reg_utf8_str, "<not symbolic>");
  }
  char str[1024];
  sprintf(str, "%s error: unrecognized bytecode register (%s).", bytecode_name, reg_utf8_str);
  error(fiber, str);
}

void f2__fiber__increment_pc(f2ptr fiber, f2ptr cause) {
  f2ptr pc_reg = f2fiber__program_counter(fiber, cause);
  debug__assert(pc_reg, fiber, "f2__fiber__increment_pc error: pc_reg is nil.");
#ifdef USE_BYTECODE_ARRAY
  f2ptr array         = raw__mutable_array_pointer__array(cause, pc_reg);
  u64   array__length = raw__array__length(cause, array);
  u64   index         = raw__mutable_array_pointer__index(cause, pc_reg);
  if (index < array__length - 1) {
    raw__mutable_array_pointer__index__set(cause, pc_reg, index + 1);
  } else {
    f2fiber__program_counter__set(fiber, cause, nil);
  }
#else
  f2fiber__program_counter__set(fiber, cause, f2cons__cdr(pc_reg, cause));
#endif
}


#ifdef DEBUG_BYTECODES
#  define bytecode_status(msg, rest...) status(msg, ## rest)
#else
#  define bytecode_status(msg, rest...)
#endif

f2ptr f2__bytecode_funk_funk__call_with_event(f2ptr cause, f2ptr bytecode_funk_funk, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr funk, f2ptr funk_args) {
  f2ptr args             = raw__cons__new(cause, object_cause, raw__cons__new(cause, fiber, raw__cons__new(cause, bytecode, raw__cons__new(cause, funk, raw__cons__new(cause, funk_args, nil)))));
  f2ptr reflective_value = f2__force_funk_apply(cause, fiber, bytecode_funk_funk, args);
  return reflective_value;
}

int raw__cause__call_all_endfunks(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr bytecode, f2ptr funktion);

// bytecode jump_funk []

int f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg(f2ptr fiber, f2ptr cause, f2ptr bytecode) {
  bytecode_status("bytecode jump_funk beginning.");
  f2ptr funktion = f2fiber__value(fiber, cause);
  //assert(funktion != nil, fiber, "f2__fiber__bytecode__funk assertion failed: funktion is null.");
  
  if (cause) {
    f2ptr bytecode_funk_callbacks = f2cause__bytecode_funk_callbacks(cause, cause);
    if (bytecode_funk_callbacks) {
      f2ptr funk_args = f2fiber__args(fiber, cause);
      {
	f2ptr bytecode_funk_callbacks_iter = bytecode_funk_callbacks;
	while (bytecode_funk_callbacks_iter) {
	  f2ptr bytecode_funk_callbacks_next = f2cons__cdr(bytecode_funk_callbacks_iter, cause);
	  f2ptr bytecode_funk_funk           = f2cons__car(bytecode_funk_callbacks_iter, cause);
	  {
	    f2ptr reflective_cause = nil;
	    f2ptr reflective_value = f2__bytecode_funk_funk__call_with_event(reflective_cause, bytecode_funk_funk, cause, fiber, bytecode, funktion, funk_args);
	    if (raw__larva__is_type(cause, reflective_value)) {
	      f2fiber__value__set(fiber, cause, reflective_value);
	      return 1;
	    }
	  }
	  bytecode_funk_callbacks_iter = bytecode_funk_callbacks_next;
	}
      }
    }
  }
  if (raw__funk__is_type(cause, funktion)) {
    //trace2(bytecode__jump_funk, funktion, f2fiber__args(fiber));
    f2ptr funk_env       = f2funk__env(funktion, cause);
#ifdef USE_BYTECODE_ARRAY
    f2ptr bytecode_array = f2funk__bytecode_array(funktion, cause);
    if (! raw__array__is_type(cause, bytecode_array)) {
      f2__print(nil, bytecode_array);
      error(nil, "bytecode_array not array.");
    }
#else
    f2ptr body_bcs       = f2funk__body_bytecodes(funktion, cause);
    if (raw__larva__is_type(cause, body_bcs)) {
      bytecode_status("body_bcs is larva!");
      f2fiber__value__set(fiber, cause, body_bcs);
      return 1;
    }
#endif

#ifdef USE_MACHINE_CODE
    f2ptr machine_code   = f2funk__machine_code(funktion, cause);
#endif

#ifdef DEBUG_BYTECODES
    {
      f2ptr name = f2funk__name(funktion, cause);
      u8*   str;
      if (raw__symbol__is_type(cause, name)) {
	u64 str_len = f2symbol__length(name, cause);
	str = (u8*)from_ptr(f2__malloc(str_len + 1));
	raw__symbol__utf8_str_copy(cause, name, str);
	str[str_len] = 0;
      } else {
	str = (u8*)from_ptr(f2__malloc(strlen("<none>") + 1));
	strcpy((char*)str, "<none>");
      }
      bytecode_status("executing funk name=|%s| body_bcs=%s machine_code=%s", str, body_bcs ? "<not nil>" : "nil", machine_code ? "<not nil>" : "nil");
      f2__free(to_ptr(str));
    }
#endif // DEBUG_BYTECODES

    f2fiber__env__set(            fiber, cause, funk_env);

#ifdef USE_BYTECODE_ARRAY
    f2fiber__program_counter__set(fiber, cause, raw__mutable_array_pointer__new(cause, bytecode_array, 0));
#else
    f2fiber__program_counter__set(fiber, cause, body_bcs);
#endif

#ifdef USE_MACHINE_CODE
    if (machine_code) {
      return f2chunk__bytecode_jump(machine_code, cause, fiber);
    } else {
      return 1;
    }
#else
    return 1;
#endif

  } else if (raw__cfunk__is_type(cause, funktion)) {

#ifdef DEBUG_BYTECODES
    {
      f2ptr name = f2cfunk__name(funktion, cause);
      u8*   name__utf8_str;
      if (raw__symbol__is_type(cause, name)) {
	u64 name__utf8_length = raw__symbol__utf8_length(cause, name);
	name__utf8_str = (u8*)from_ptr(f2__malloc(name__utf8_length + 1));
	raw__symbol__utf8_str_copy(cause, name, name__utf8_str);
	name__utf8_str[name__utf8_length] = 0;
      } else {
	name__utf8_str = (u8*)from_ptr(f2__malloc(strlen("<none>") + 1));
	strcpy((char*)name__utf8_str, "<none>");
      }
      bytecode_status("executing cfunk name=|%s|", name__utf8_str);
      f2__free(to_ptr(name__utf8_str));
    }
#endif // DEBUG_BYTECODES
    f2ptr return_reg = f2fiber__return_reg(fiber, cause);
    {
      f2ptr args = f2fiber__args(fiber, cause);
      debug__assert(!args || raw__cons__is_type(cause, args), fiber, "args failed args type assertion.");
      {
	f2ptr value = f2__cfunk__apply(cause, funktion, fiber, args);
	f2fiber__value__set(fiber, cause, value);
      }
    }
    f2fiber__program_counter__set(fiber, cause, return_reg);
    return raw__cause__call_all_endfunks(nil, cause, fiber, bytecode, funktion);
  } else if (raw__core_extension_funk__is_type(cause, funktion)) {
#ifdef DEBUG_BYTECODES
    {
      f2ptr name = f2__core_extension_funk__name(funktion, cause);
      u8*   name__utf8_str;
      if (raw__symbol__is_type(cause, name)) {
	u64 name__utf8_length = raw__symbol__utf8_length(cause, name);
	name__utf8_str = (u8*)from_ptr(f2__malloc(name__utf8_length + 1));
	raw__symbol__utf8_str_copy(cause, name, name__utf8_str);
	name__utf8_str[name__utf8_length] = 0;
      } else {
	name__utf8_str = (u8*)from_ptr(malloc(strlen("<none>") + 1));
	strcpy((char*)name__utf8_str, "<none>");
      }
      bytecode_status("executing core_extension_funk name=|%s|", name__utf8_str);
      f2__free(to_ptr(name__utf8_str));
    }
#endif // DEBUG_BYTECODES
    f2ptr return_reg = f2fiber__return_reg(fiber, cause);
    {
      f2ptr args = f2fiber__args(fiber, cause);
      {
	if ((args != nil) && (! raw__cons__is_type(cause, args))) {
	  f2ptr value = f2larva__new(cause, 1, nil);
	  f2fiber__value__set(fiber, cause, value);
	  return 1;
	}
	f2ptr value = f2__core_extension_funk__apply(cause, funktion, args);
	f2fiber__value__set(fiber, cause, value);
      }
    }
    f2fiber__program_counter__set(fiber, cause, return_reg);
    return raw__cause__call_all_endfunks(nil, cause, fiber, bytecode, funktion);
  } else if (raw__metro__is_type(cause, funktion)) {
#ifdef DEBUG_BYTECODES
    {
      f2ptr name = raw__metro__name(cause, funktion);
      u8*   name__utf8_str;
      if (raw__symbol__is_type(cause, name)) {
	u64 name__utf8_length = raw__symbol__utf8_length(cause, name);
	name__utf8_str = (u8*)from_ptr(f2__malloc(name__utf8_length + 1));
	raw__symbol__utf8_str_copy(cause, name, name__utf8_str);
	name__utf8_str[name__utf8_length] = 0;
      } else {
	name__utf8_str = (u8*)from_ptr(f2__malloc(strlen("<none>") + 1));
	strcpy((char*)name__utf8_str, "<none>");
      }
      bytecode_status("executing metro name=|%s|", name__utf8_str);
      f2__free(to_ptr(name__utf8_str));
    }
#endif // DEBUG_BYTECODES
    f2fiber__env__set(fiber, cause, raw__metro__env(cause, funktion));
#ifdef USE_BYTECODE_ARRAY
    f2ptr bytecode_array = raw__metro__bytecode_array(cause, funktion);
#else
    f2ptr body_bcs       = raw__metro__body_bytecodes(cause, funktion);
    if (raw__larva__is_type(cause, body_bcs)) {
      f2fiber__value__set(fiber, cause, body_bcs);
      return 1;
    }
#endif

#ifdef USE_MACHINE_CODE
    f2ptr machine_code   = raw__metro__machine_code(cause, funktion);
#endif

#ifdef USE_BYTECODE_ARRAY
    f2fiber__program_counter__set(fiber, cause, raw__mutable_array_pointer__new(cause, bytecode_array, 0));
#else
    f2fiber__program_counter__set(fiber, cause, body_bcs);
#endif

#ifdef USE_MACHINE_CODE
    if (machine_code) {
      //fflush(stdout); f2__print_prompt("jumping to metro machine code: ", funktion); fflush(stdout);
      return f2chunk__bytecode_jump(machine_code, cause, fiber);
    } else {
      return 1;
    }
#else
    return 1;
#endif
  }
  { // debugging code
    if (raw__chunk__is_type(cause, funktion)) {
      status("f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg bug: cannot_funk_unfunkable_funktion (saving chunk to 'larva_18.chunk'.");
      raw__chunk__save(cause, funktion, new__string(cause, "larva_18.chunk"));
    } else {
      status("f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg bug: cannot_funk_unfunkable_funktion.");
      f2__print(cause, funktion);
    }
    error(nil, "f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg bug: cannot_funk_unfunkable_funktion.");
  }
  f2ptr bug_frame = f2__frame__new(cause, nil);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "cannot_funk_unfunkable_funktion"));
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funktion"), funktion);
  f2ptr retval = f2larva__new(cause, 18, f2__bug__new(cause, f2integer__new(cause, 18), bug_frame));
  //f2__expression_not_funkable__exception__new(cause, funktion);
  //printf("\n"); f2__print(nil, retval); fflush(stdout); printf("\n");
  //error(fiber, "error: expression not funkable");
  f2fiber__value__set(fiber, cause, retval);
  return 1;
}

int f2__fiber__bytecode__jump_funk(f2ptr fiber, f2ptr bytecode) {
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg(fiber, cause, bytecode);
}


// bytecode funk []
//
//   note: this is where we set the return register (f2_compile.c assumes that this happens atomically with this bytecode).
//
int f2__fiber__bytecode_helper__funk__no_increment_pc_reg(f2ptr fiber, f2ptr cause, f2ptr bytecode) {
  bytecode_status("bytecode funk beginning.");
  f2fiber__return_reg__set(fiber, cause, f2fiber__program_counter(fiber, cause)); // f2__fiber__bytecode__copy(fiber, __fiber__program_counter_reg__symbol, __fiber__return_reg__symbol);
  return f2__fiber__bytecode_helper__jump_funk__no_increment_pc_reg(fiber, cause, bytecode);
}

int f2__fiber__bytecode__funk(f2ptr fiber, f2ptr bytecode) {
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__funk__execution_count ++;
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode_helper__funk__no_increment_pc_reg(fiber, cause, bytecode);
}


// bytecode array [length]

int f2__fiber__bytecode__array(f2ptr fiber, f2ptr bytecode, f2ptr length) {
  bytecode_status("bytecode array beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__array__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr new_array = f2traced_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));
  if (! new_array) {
    error(nil, "array bytecode error: new array is nil");
  }
  f2fiber__iter__set(fiber, cause, new_array);
  return 0;
}


// bytecode cons []

int f2__fiber__bytecode__cons__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2ptr new_cons = raw__cons__new(cause, nil, nil);
  if (! new_cons) {error(nil, "cons bytecode error: new cons is nil");}
  f2fiber__iter__set(fiber, cause, new_cons);
  return 0;
}


int f2__fiber__bytecode__cons(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode cons beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__cons__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__cons__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode consp []

int f2__fiber__bytecode__consp(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode consp beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__consp__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr result = f2bool__new(raw__cons__is_type(cause, f2fiber__value(fiber, cause)));
  f2fiber__value__set(fiber, cause, result);
  return 0;
}


// bytecode car []

int f2__fiber__bytecode__car__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2ptr fiber__iter = f2fiber__iter(fiber, cause);
  f2ptr fiber__value;
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_car"));
    fiber__value = f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  } else {
    fiber__value = f2cons__car(fiber__iter, cause);
  }
  
  f2fiber__value__set(fiber, cause, fiber__value);
  return 0;
}


int f2__fiber__bytecode__car(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode car beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__car__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__car__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode cdr []

int f2__fiber__bytecode__cdr__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2ptr fiber__iter  = f2fiber__iter(fiber, cause);
  f2ptr fiber__value;
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_cdr"));
    fiber__value = f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  } else {
    fiber__value = f2cons__cdr(fiber__iter, cause);
  }
  f2fiber__value__set(fiber, cause, fiber__value);
  return 0;
}

int f2__fiber__bytecode__cdr(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode cdr beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__cdr__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  return f2__fiber__bytecode__cdr__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode car__set []

int f2__fiber__bytecode__car__set__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2cons__car__set(f2fiber__iter(fiber, cause), cause, f2fiber__value(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__car__set(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode car-set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__car__set__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__car__set__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode cdr__set []

int f2__fiber__bytecode__cdr__set__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2cons__cdr__set(f2fiber__iter(fiber, cause), cause, f2fiber__value(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__cdr__set(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode cdr-set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__cdr__set__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__cdr__set__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode array_elt [array index]

int f2__fiber__bytecode__array_elt(f2ptr fiber, f2ptr bytecode, f2ptr array, f2ptr index) {
  bytecode_status("bytecode array_elt beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__array_elt__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, f2__array__elt(cause, array, index));
  return 0;
}


// bytecode set [reg f2ptr]

int f2__fiber__bytecode__set__value_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, exp);
  return 0;
}

int f2__fiber__bytecode__set__program_counter_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  if (raw__exception__is_type(cause, exp)) {
    f2fiber__value__set(fiber, cause, exp);
  } else {
    f2fiber__program_counter__set(fiber, cause, exp);
  }
  return 1;
}

int f2__fiber__bytecode__set__iter_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__iter__set(fiber, cause, exp);
  return 0;
}

int f2__fiber__bytecode__set__args_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__args__set(fiber, cause, exp);
  return 0;
}

int f2__fiber__bytecode__set__return_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, exp);
  return 0;
}

int f2__fiber__bytecode__set__env_reg(f2ptr fiber, f2ptr bytecode, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, exp);
  return 0;
}

bytecode_jump__f2ptr_t f2__compile__bytecode__set(f2ptr cause, f2ptr reg) {
  if      (reg == __fiber__value_reg__symbol)           {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__value_reg;}
  else if (reg == __fiber__program_counter_reg__symbol) {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__program_counter_reg;}
  else if (reg == __fiber__iter_reg__symbol)            {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__iter_reg;}
  else if (reg == __fiber__args_reg__symbol)            {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__args_reg;}
  else if (reg == __fiber__return_reg__symbol)          {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__return_reg;}
  else if (reg == __fiber__env_reg__symbol)             {return (bytecode_jump__f2ptr_t)&f2__fiber__bytecode__set__env_reg;}
  unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-set", reg);
  return NULL;
}

int f2__fiber__bytecode__set(f2ptr fiber, f2ptr bytecode, f2ptr reg, f2ptr exp) {
  bytecode_status("bytecode set beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__set__execution_count ++;
  
  return (f2__compile__bytecode__set(cause, reg))(fiber, bytecode, exp);
}


// bytecode nop []

int f2__fiber__bytecode__nop(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode nop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__nop__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return 0;
}


// bytecode swap [reg reg]

int f2__fiber__bytecode__swap__return_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                         f2fiber__return_reg(fiber, cause);
  f2fiber__return_reg__set(fiber, cause, f2fiber__value( fiber, cause));
  f2fiber__value__set( fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__return_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp = f2fiber__return_reg(fiber, cause);
  f2fiber__return_reg__set(fiber, cause, f2fiber__iter(  fiber, cause));
  f2fiber__iter__set(fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__return_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp = f2fiber__return_reg(fiber, cause);
  f2fiber__return_reg__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  f2fiber__program_counter__set(fiber, cause, temp);
  return 1;
}

int f2__fiber__bytecode__swap__return_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                         f2fiber__return_reg(fiber, cause);
  f2fiber__return_reg__set(fiber, cause, f2fiber__env(   fiber, cause));
  f2fiber__env__set(   fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__return_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                         f2fiber__return_reg(fiber, cause);
  f2fiber__return_reg__set(fiber, cause, f2fiber__args(  fiber, cause));
  f2fiber__args__set(  fiber, cause, temp);
  return 0;
}


int f2__fiber__bytecode__swap__value_reg__iter_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2ptr temp =                        f2fiber__value(fiber, cause);
  f2fiber__value__set(fiber, cause, f2fiber__iter( fiber, cause));
  f2fiber__iter__set( fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__value_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__swap__value_reg__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__swap__value_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp = f2fiber__value(fiber, cause);
  f2fiber__value__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  f2fiber__program_counter__set(fiber, cause, temp);
  return 1;
}

int f2__fiber__bytecode__swap__value_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp = f2fiber__value(fiber, cause);
  f2fiber__value__set(fiber, cause, f2fiber__env(  fiber, cause));
  f2fiber__env__set(  fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__value_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                        f2fiber__value(fiber, cause);
  f2fiber__value__set(fiber, cause, f2fiber__args( fiber, cause));
  f2fiber__args__set( fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__iter_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                                f2fiber__iter(           fiber, cause);
  f2fiber__iter__set(           fiber, cause, f2fiber__program_counter(fiber, cause));
  f2fiber__program_counter__set(fiber, cause, temp);
  return 1;
}

int f2__fiber__bytecode__swap__iter_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                       f2fiber__iter(fiber, cause);
  f2fiber__iter__set(fiber, cause, f2fiber__env( fiber, cause));
  f2fiber__env__set( fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__iter_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                       f2fiber__iter(fiber, cause);
  f2fiber__iter__set(fiber, cause, f2fiber__args(fiber, cause));
  f2fiber__args__set(fiber, cause, temp);
  return 0;
}

int f2__fiber__bytecode__swap__program_counter_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                                f2fiber__program_counter(fiber, cause);
  f2fiber__program_counter__set(fiber, cause, f2fiber__env(            fiber, cause));
  f2fiber__env__set(            fiber, cause, temp);
  return 1;
}

int f2__fiber__bytecode__swap__program_counter_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                                f2fiber__program_counter(fiber, cause);
  f2fiber__program_counter__set(fiber, cause, f2fiber__args(           fiber, cause));
  f2fiber__args__set(           fiber, cause, temp);
  return 1;
}

int f2__fiber__bytecode__swap__env_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr temp =                       f2fiber__env( fiber, cause);
  f2fiber__env__set( fiber, cause, f2fiber__args(fiber, cause));
  f2fiber__args__set(fiber, cause, temp);
  return 0;
}


bytecode_jump_t f2__compile__bytecode__swap(f2ptr cause, f2ptr reg0, f2ptr reg1) {
  if        (reg0 == __fiber__return_reg__symbol)          {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__swap__return_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__swap__return_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__swap__return_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__swap__return_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__swap__return_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__value_reg__symbol)           {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__swap__return_reg__value_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__swap__value_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__swap__value_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__swap__value_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__swap__value_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__iter_reg__symbol)            {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__swap__return_reg__iter_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__swap__value_reg__iter_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__swap__iter_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__swap__iter_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__swap__iter_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__program_counter_reg__symbol) {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__swap__return_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__swap__value_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__swap__iter_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__swap__program_counter_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__swap__program_counter_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__env_reg__symbol)             {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__swap__return_reg__env_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__swap__value_reg__env_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__swap__iter_reg__env_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__swap__program_counter_reg__env_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__swap__env_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__args_reg__symbol)            {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__swap__return_reg__args_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__swap__value_reg__args_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__swap__iter_reg__args_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__swap__program_counter_reg__args_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__swap__env_reg__args_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__nop;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-swap (reg0)", reg0);
							     return (bytecode_jump_t)NULL;}
}

int f2__fiber__bytecode__swap(f2ptr fiber, f2ptr bytecode, f2ptr reg0, f2ptr reg1) {
  bytecode_status("bytecode swap beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__swap__execution_count ++;
  
  return (f2__compile__bytecode__swap(cause, reg0, reg1))(fiber, bytecode);
}


// bytecode push_constant [constant]

int f2__fiber__bytecode__push_constant__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr constant) {
  raw__fiber__stack__push_constant(cause, fiber, constant);
  return 0;
}

int f2__fiber__bytecode__push_constant(f2ptr fiber, f2ptr bytecode, f2ptr constant) {
  bytecode_status("bytecode push_constant beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__push_constant__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push_constant__no_increment_pc_reg(cause, fiber, bytecode, constant);
}

// bytecode push [reg]

int f2__fiber__bytecode__push__return_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__push_return_reg(cause, fiber);  
  return 0;
}

int f2__fiber__bytecode__push__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push__return_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__push__env_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__push_env(cause, fiber);  
  return 0;
}

int f2__fiber__bytecode__push__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push__env_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__push__value_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__push_value(cause, fiber);  
  return 0;
}

int f2__fiber__bytecode__push__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__push__iter_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__push_iter(cause, fiber);  
  return 0;
}

int f2__fiber__bytecode__push__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__push__args_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__push_args(cause, fiber);  
  return 0;
}

int f2__fiber__bytecode__push__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__push__args_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__push__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  raw__fiber__stack__push_program_counter(cause, fiber);  
  return 0;
}

bytecode_jump_t f2__compile__bytecode__push(f2ptr cause, f2ptr reg) {
  if      (reg == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__push__return_reg;}
  else if (reg == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__push__env_reg;}
  else if (reg == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__push__value_reg;}
  else if (reg == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__push__iter_reg;}
  else if (reg == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__push__args_reg;}
  else if (reg == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__push__program_counter_reg;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-push", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__fiber__bytecode__push(f2ptr fiber, f2ptr bytecode, f2ptr reg) {
  bytecode_status("bytecode push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__push__execution_count ++;
  
  return (f2__compile__bytecode__push(cause, reg))(fiber, bytecode);
}

// bytecode pop [reg]

int f2__fiber__bytecode__pop__return_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__pop_return_reg(cause, fiber);
  return 0;
}

int f2__fiber__bytecode__pop__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__pop__return_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__pop__env_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__pop_env(cause, fiber);
  debug__assert(f2fiber__env(fiber, cause), fiber, "env popped to nil.");
  debug__assert(raw__environment__is_type(cause, f2fiber__env(fiber, cause)), fiber, "assertion failed: popped to non-environment");
  //f2__print(nil, f2fiber__env(fiber));
  //fflush(stdout);
  return 0;
}

int f2__fiber__bytecode__pop__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__pop__env_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__pop__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  raw__fiber__stack__pop_value(cause, fiber);
  return 0;
}

int f2__fiber__bytecode__pop__iter_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__pop_iter(cause, fiber);
  return 0;
}

int f2__fiber__bytecode__pop__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__pop__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__pop__args_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__pop_args(cause, fiber);
  return 0;
}

int f2__fiber__bytecode__pop__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__pop__args_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__pop__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  raw__fiber__stack__pop_program_counter(cause, fiber);
  return 1;
}

int f2__fiber__bytecode__pop__nil__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  raw__fiber__stack__pop_nil(cause, fiber);
  return 0;
}

int f2__fiber__bytecode__pop__nil(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__pop__nil__no_increment_pc_reg(cause, fiber, bytecode);
}

bytecode_jump_t f2__compile__bytecode__pop(f2ptr cause, f2ptr reg) {
  if      (reg == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__pop__return_reg;}
  else if (reg == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__pop__env_reg;}
  else if (reg == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__pop__value_reg;}
  else if (reg == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__pop__iter_reg;}
  else if (reg == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__pop__args_reg;}
  else if (reg == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__pop__program_counter_reg;}
  else if (reg == nil)                                   {return &f2__fiber__bytecode__pop__nil;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-pop", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__fiber__bytecode__pop(f2ptr fiber, f2ptr bytecode, f2ptr reg) {
  bytecode_status("bytecode pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__pop__execution_count ++;
  
  return (f2__compile__bytecode__pop(cause, reg))(fiber, bytecode);
}


// bytecode copy [reg reg]

int f2__fiber__bytecode__copy__return_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, f2fiber__return_reg(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__return_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__iter__set(fiber, cause, f2fiber__return_reg(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__return_reg__program_counter_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2fiber__program_counter__set(fiber, cause, f2fiber__return_reg(fiber, cause));
  return 1;
}

int f2__fiber__bytecode__copy__return_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__copy__return_reg__program_counter_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__copy__return_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, f2fiber__return_reg(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__return_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__args__set(fiber, cause, f2fiber__return_reg(fiber, cause));
  return 0;
}


int f2__fiber__bytecode__copy__value_reg__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, f2fiber__value(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__value_reg__iter_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2fiber__iter__set(fiber, cause, f2fiber__value(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__value_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__copy__value_reg__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__copy__value_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__program_counter__set(fiber, cause, f2fiber__value(fiber, cause));
  return 1;
}

int f2__fiber__bytecode__copy__value_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, f2fiber__value(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__value_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__args__set(fiber, cause, f2fiber__value(fiber, cause));
  return 0;
}


int f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2fiber__value__set(fiber, cause, f2fiber__iter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__iter_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
}

int f2__fiber__bytecode__copy__iter_reg__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, f2fiber__iter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__iter_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__program_counter__set(fiber, cause, f2fiber__iter(fiber, cause));
  return 1;
}

int f2__fiber__bytecode__copy__iter_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, f2fiber__iter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__iter_reg__args_reg__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2fiber__args__set(fiber, cause, f2fiber__iter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__iter_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__copy__iter_reg__args_reg__no_increment_pc_reg(cause, fiber, bytecode);
}


int f2__fiber__bytecode__copy__program_counter_reg__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__program_counter_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__program_counter_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, nil);
  
  f2fiber__iter__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__program_counter_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__program_counter_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__args__set(fiber, cause, f2fiber__program_counter(fiber, cause));
  return 0;
}


int f2__fiber__bytecode__copy__env_reg__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, f2fiber__env(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__env_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, f2fiber__env(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__env_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__iter__set(fiber, cause, f2fiber__env(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__env_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__program_counter__set(fiber, cause, f2fiber__env(fiber, cause));
  return 1;
}

int f2__fiber__bytecode__copy__env_reg__args_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__args__set(fiber, cause, f2fiber__env(fiber, cause));
  return 0;
}


int f2__fiber__bytecode__copy__args_reg__return_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__return_reg__set(fiber, cause, f2fiber__args(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__args_reg__value_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__value__set(fiber, cause, f2fiber__args(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__args_reg__iter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__iter__set(fiber, cause, f2fiber__args(fiber, cause));
  return 0;
}

int f2__fiber__bytecode__copy__args_reg__program_counter_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__program_counter__set(fiber, cause, f2fiber__args(fiber, cause));
  return 1;
}

int f2__fiber__bytecode__copy__args_reg__env_reg(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2fiber__env__set(fiber, cause, f2fiber__args(fiber, cause));
  return 0;
}


bytecode_jump_t f2__compile__bytecode__copy(f2ptr cause, f2ptr reg0, f2ptr reg1) {
  if        (reg0 == __fiber__return_reg__symbol)          {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__copy__return_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__copy__return_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__copy__return_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__copy__return_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__copy__return_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__value_reg__symbol)           {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__copy__value_reg__return_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__copy__value_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__copy__value_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__copy__value_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__copy__value_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__iter_reg__symbol)            {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__copy__iter_reg__return_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__copy__iter_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__copy__iter_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__copy__iter_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__copy__iter_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__program_counter_reg__symbol) {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__copy__program_counter_reg__return_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__copy__program_counter_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__copy__program_counter_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__copy__program_counter_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__copy__program_counter_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__env_reg__symbol)             {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__copy__env_reg__return_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__copy__env_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__copy__env_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__copy__env_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__nop;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__copy__env_reg__args_reg;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else if (reg0 == __fiber__args_reg__symbol)            {if      (reg1 == __fiber__return_reg__symbol)          {return &f2__fiber__bytecode__copy__args_reg__return_reg;}
                                                            else if (reg1 == __fiber__value_reg__symbol)           {return &f2__fiber__bytecode__copy__args_reg__value_reg;}
                                                            else if (reg1 == __fiber__iter_reg__symbol)            {return &f2__fiber__bytecode__copy__args_reg__iter_reg;}
                                                            else if (reg1 == __fiber__program_counter_reg__symbol) {return &f2__fiber__bytecode__copy__args_reg__program_counter_reg;}
                                                            else if (reg1 == __fiber__env_reg__symbol)             {return &f2__fiber__bytecode__copy__args_reg__env_reg;}
                                                            else if (reg1 == __fiber__args_reg__symbol)            {return &f2__fiber__bytecode__nop;}
                                                            else                                                    {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg1)", reg1);
							                                                             return (bytecode_jump_t)NULL;}
  } else                                                   {unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-copy (reg0)", reg0);
						            return (bytecode_jump_t)NULL;}
}

int f2__fiber__bytecode__copy(f2ptr fiber, f2ptr bytecode, f2ptr src_reg, f2ptr dest_reg) {
  bytecode_status("bytecode copy beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__copy__execution_count ++;
  
  return (f2__compile__bytecode__copy(cause, src_reg, dest_reg))(fiber, bytecode);
}


// bytecode lookup [f2ptr f2ptr]

int f2__fiber__bytecode__lookup(f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__lookup__execution_count ++;
#ifdef DEBUG_BYTECODES
  {
    u64 var__utf8_length;
    u8* var__utf8_str;
    if (raw__symbol__is_type(cause, var)) {
      var__utf8_length = raw__symbol__utf8_length(cause, var);
      var__utf8_str = (u8*)from_ptr(f2__malloc(var__utf8_length + 1));
      raw__symbol__utf8_str_copy(cause, var, var__utf8_str);
      var__utf8_str[var__utf8_length] = 0;
    } else {
      var__utf8_str = (u8*)from_ptr(f2__malloc(strlen("<non-symbol>") + 1));
      strcpy((char*)var__utf8_str, "<non-symbol>");
    }
    f2ptr env = f2fiber__env(fiber, cause);
    bytecode_status("bytecode lookup beginning.  var=%s env=%s", var__utf8_str, env ? "<non-nil>" : "nil");
    f2__free(to_ptr(var__utf8_str));
  }
#endif // DEBUG_BYTECODES  
  f2ptr fiber_value = f2__fiber__lookup_type_variable_value(cause, fiber, type, var);
  f2__fiber__increment_pc(fiber, cause);
  f2fiber__value__set(fiber, cause, fiber_value);
  bytecode_status("bytecode lookup ending.  fiber_value=%s", fiber_value ? "<non-nil>" : "nil");
  return 0;
}


// bytecode define [f2ptr f2ptr]

int f2__fiber__bytecode__define__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr env   = f2fiber__env(fiber, cause);
  f2ptr value = f2fiber__value(fiber, cause);
  f2fiber__value__set(fiber, cause, f2__environment__define_type_var_value(cause, env, type, var, value));
  return 0;
}

int f2__fiber__bytecode__define(f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var) {
  bytecode_status("bytecode define beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__define__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__define__no_increment_pc_reg(cause, fiber, bytecode, type, var);
}


// bytecode type_var__mutate [f2ptr f2ptr]

int f2__fiber__bytecode__type_var__mutate(f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var) {
  bytecode_status("bytecode type_var-mutate beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__type_var__mutate__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr env       = f2fiber__env(fiber, cause);
  f2ptr value     = f2fiber__value(fiber, cause);
  f2ptr new_value = f2__environment__type_var_value__set(cause, env, type, var, value);
  f2fiber__value__set(fiber, cause, new_value);
  return 0;
}


// bytecode globalize_type_var [f2ptr f2ptr]

int f2__fiber__bytecode__globalize_type_var(f2ptr fiber, f2ptr bytecode, f2ptr type, f2ptr var) {
  bytecode_status("bytecode globalize_type_var beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__globalize_type_var__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr value = f2fiber__value(fiber, cause);
  if (! raw__larva__is_type(cause, value)) {
    f2fiber__value__set(fiber, cause, f2__environment__define_type_var_value(cause, global_environment(), type, var, value));
  }
  return 0;
}


// bytecode jump [f2ptr]

int f2__fiber__bytecode__jump(f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter) {
  bytecode_status("bytecode jump beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__jump__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  if (raw__exception__is_type(cause, new_program_counter)) {
    f2fiber__value__set(fiber, cause, new_program_counter);
  } else {
    f2fiber__program_counter__set(fiber, cause, new_program_counter);
  }
  return 1;
}

f2ptr f2__bytecode_branch_funk__call_with_event(f2ptr cause, f2ptr bytecode_branch_funk, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr program_counter, f2ptr branch_program_counter, f2ptr value) {
  f2ptr args             = raw__cons__new(cause, object_cause, raw__cons__new(cause, fiber, raw__cons__new(cause, bytecode, raw__cons__new(cause, program_counter, raw__cons__new(cause, branch_program_counter, raw__cons__new(cause, value, nil))))));
  f2ptr reflective_value = f2__force_funk_apply(cause, fiber, bytecode_branch_funk, args);
  return reflective_value;
}

// bytecode if_jump [f2ptr]

int f2__fiber__bytecode__if_jump(f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter) {
  bytecode_status("bytecode if_jump beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__if_jump__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr value = f2fiber__value(fiber, cause);
  
  if (cause) {
    f2ptr bytecode_branch_callbacks = f2cause__bytecode_branch_callbacks(cause, cause);
    if (bytecode_branch_callbacks) {
      f2ptr program_counter = f2fiber__program_counter(fiber, cause);
      {
	f2ptr bytecode_branch_callbacks_iter = bytecode_branch_callbacks;
	while (bytecode_branch_callbacks_iter) {
	  f2ptr bytecode_branch_callbacks_next = f2cons__cdr(bytecode_branch_callbacks_iter, cause);
	  f2ptr bytecode_branch_funk       = f2cons__car(bytecode_branch_callbacks_iter, cause);
	  {
	    f2ptr reflective_cause = nil;
	    f2ptr reflective_value = f2__bytecode_branch_funk__call_with_event(reflective_cause, bytecode_branch_funk, cause, fiber, bytecode, program_counter, new_program_counter, value);
	    if (raw__larva__is_type(cause, reflective_value)) {
	      f2fiber__value__set(fiber, cause, reflective_value);
	      return 1;
	    }
	  }
	  bytecode_branch_callbacks_iter = bytecode_branch_callbacks_next;
	}
      }
    }
  }
  
  if (value) {
    if (raw__exception__is_type(cause, new_program_counter)) {
      f2fiber__value__set(fiber, cause, new_program_counter);
    } else {
      f2fiber__program_counter__set(fiber, cause, new_program_counter);
    }
  }
  return 1;
}


// bytecode else_jump [f2ptr]

int f2__fiber__bytecode__else_jump__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter) {
  f2ptr value = f2fiber__value(fiber, cause);
  
  if (cause) {
    f2ptr bytecode_branch_callbacks = f2cause__bytecode_branch_callbacks(cause, cause);
    if (bytecode_branch_callbacks) {
      f2ptr program_counter = f2fiber__program_counter(fiber, cause);
      {
	f2ptr bytecode_branch_callbacks_iter = bytecode_branch_callbacks;
	//f2ptr bytecode_branch_callbacks_prev = nil;
	while (bytecode_branch_callbacks_iter) {
	  f2ptr bytecode_branch_callbacks_next = f2cons__cdr(bytecode_branch_callbacks_iter, cause);
	  f2ptr bytecode_branch_funk       = f2cons__car(bytecode_branch_callbacks_iter, cause);
	  {
	    f2ptr reflective_cause = nil;
	    f2ptr reflective_value = f2__bytecode_branch_funk__call_with_event(reflective_cause, bytecode_branch_funk, cause, fiber, bytecode, program_counter, new_program_counter, value);
	    if (raw__larva__is_type(cause, reflective_value)) {
	      f2fiber__value__set(fiber, cause, reflective_value);
	      return 1;
	    }
	    //if (reflective_value) {
	    //  // remove this funk from list (return nil for default repetitive tracing behavior).
	    //  if (bytecode_branch_callbacks_prev) {
	    //	f2cons__cdr__set(bytecode_branch_callbacks_prev, cause, bytecode_branch_callbacks_next);
	    //  } else {
	    //	f2cons__cdr__set(bytecode_branch_callbacks_prev, cause, bytecode_branch_callbacks_next);
	    //  }
	    //}
	  }
	  bytecode_branch_callbacks_iter = bytecode_branch_callbacks_next;
	}
      }
    }
  }
  
  if (! value) {
    if (raw__exception__is_type(cause, new_program_counter)) {
      f2fiber__value__set(fiber, cause, new_program_counter);
    } else {
      f2fiber__program_counter__set(fiber, cause, new_program_counter);
    }
  }
  return 1;
}


int f2__fiber__bytecode__else_jump(f2ptr fiber, f2ptr bytecode, f2ptr new_program_counter) {
  bytecode_status("bytecode else_jump beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__else_jump__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);

  return f2__fiber__bytecode__else_jump__no_increment_pc_reg(cause, fiber, bytecode, new_program_counter);
}


// bytecode debug [f2ptr]

int f2__fiber__bytecode__debug(f2ptr fiber, f2ptr bytecode, f2ptr value) {
  bytecode_status("bytecode debug beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__debug__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  printf("\ndebug: *** "); f2__write(cause, fiber, value); printf(" ***"); fflush(stdout);
  return 0;
}


f2ptr f2__bytecode_tracer_funk__call_with_event(f2ptr cause, f2ptr bytecode_tracer_funk, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr value) {
  f2ptr args             = raw__cons__new(cause, object_cause, raw__cons__new(cause, fiber, raw__cons__new(cause, bytecode, raw__cons__new(cause, value, nil))));
  f2ptr reflective_value = f2__force_funk_apply(cause, fiber, bytecode_tracer_funk, args);
  return reflective_value;
}

// bytecode tracer [f2ptr f2ptr]

int f2__fiber__bytecode__tracer(f2ptr fiber, f2ptr bytecode, f2ptr name, f2ptr args) {
  bytecode_status("bytecode tracer beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__tracer__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  if (cause) {
    f2ptr bytecode_tracer_callbacks = f2cause__bytecode_tracer_callbacks(cause, cause);
    if (bytecode_tracer_callbacks) {
      f2ptr value = f2fiber__value(fiber, cause);
      {
	f2ptr bytecode_tracer_callbacks_iter = bytecode_tracer_callbacks;
	//f2ptr bytecode_tracer_callbacks_prev = nil;
	while (bytecode_tracer_callbacks_iter) {
	  f2ptr bytecode_tracer_callbacks_next = f2cons__cdr(bytecode_tracer_callbacks_iter, cause);
	  f2ptr bytecode_tracer_funk           = f2cons__car(bytecode_tracer_callbacks_iter, cause);
	  {
	    f2ptr reflective_cause = nil;
	    f2ptr reflective_value = f2__bytecode_tracer_funk__call_with_event(reflective_cause, bytecode_tracer_funk, cause, fiber, bytecode, value);
	    if (raw__larva__is_type(cause, reflective_value)) {
	      f2fiber__value__set(fiber, cause, reflective_value);
	      return 1;
	    }
	  }
	  bytecode_tracer_callbacks_iter = bytecode_tracer_callbacks_next;
	}
      }
    }
  }
  
  return 0;
}


f2ptr f2__bytecode_endfunk_funk__call_with_event(f2ptr cause, f2ptr bytecode_endfunk_funk, f2ptr object_cause, f2ptr fiber, f2ptr bytecode, f2ptr value, f2ptr funk) {
  f2ptr args             = raw__cons__new(cause, object_cause, raw__cons__new(cause, fiber, raw__cons__new(cause, bytecode, raw__cons__new(cause, value, raw__cons__new(cause, funk, nil)))));
  f2ptr reflective_value = f2__force_funk_apply(cause, fiber, bytecode_endfunk_funk, args);
  return reflective_value;
}

int raw__cause__call_all_endfunks(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr bytecode, f2ptr funk) {
  if (this) {
    f2ptr bytecode_endfunk_callbacks = f2cause__bytecode_endfunk_callbacks(this, cause);
    if (bytecode_endfunk_callbacks) {
      f2ptr value = f2fiber__value(fiber, cause);
      {
	f2ptr bytecode_endfunk_callbacks_iter = bytecode_endfunk_callbacks;
	//f2ptr bytecode_endfunk_callbacks_prev = nil;
	while (bytecode_endfunk_callbacks_iter) {
	  f2ptr bytecode_endfunk_callbacks_next = f2cons__cdr(bytecode_endfunk_callbacks_iter, cause);
	  f2ptr bytecode_endfunk_funk       = f2cons__car(bytecode_endfunk_callbacks_iter, cause);
	  {
	    f2ptr reflective_value = f2__bytecode_endfunk_funk__call_with_event(cause, bytecode_endfunk_funk, this, fiber, bytecode, value, funk);
	    if (raw__larva__is_type(cause, reflective_value)) {
	      f2fiber__value__set(fiber, cause, reflective_value);
	      return 1;
	    }
	  }
	  bytecode_endfunk_callbacks_iter = bytecode_endfunk_callbacks_next;
	}
      }
    }
  }
  return 0;
}

// bytecode endfunk [f2ptr]

int f2__fiber__bytecode__endfunk__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr funk) {
  return raw__cause__call_all_endfunks(nil, cause, fiber, bytecode, funk);
}

int f2__fiber__bytecode__endfunk(f2ptr fiber, f2ptr bytecode, f2ptr funk) {
  bytecode_status("bytecode endfunk beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__endfunk__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__endfunk__no_increment_pc_reg(cause, fiber, bytecode, funk);
}


// bytecode compile [boolean_t]

int f2__fiber__bytecode__compile__protect_environment(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode compile beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr protect_environment = __funk2.globalenv.true__symbol;
  boolean_t  is_funktional       = boolean__true;
  f2fiber__value__set(fiber, cause, raw__compile(cause, fiber, f2fiber__value(fiber, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

int f2__fiber__bytecode__compile__nil(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode compile beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  
  f2__fiber__increment_pc(fiber, cause);
  
  f2ptr protect_environment = nil;
  boolean_t  is_funktional       = boolean__true;
  f2fiber__value__set(fiber, cause, raw__compile(cause, fiber, f2fiber__value(fiber, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

bytecode_jump_t f2__compile__bytecode__compile(f2ptr protect_environment) {
  bytecode_status("bytecode compile beginning.");
  if (protect_environment != nil) {
    return &f2__fiber__bytecode__compile__protect_environment;
  } else {
    return &f2__fiber__bytecode__compile__nil;
  }
}

int f2__fiber__bytecode__compile(f2ptr fiber, f2ptr bytecode, f2ptr protect_environment) {
  bytecode_status("bytecode compile beginning.");
  __funk2.bytecode.bytecode__compile__execution_count ++;
  return (f2__compile__bytecode__compile(protect_environment))(fiber, bytecode);
}


// bytecode yield []

int f2__fiber__bytecode__yield(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode yield beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__yield__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  return 0;
}


// bytecode newenv []

int f2__fiber__bytecode__newenv__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  f2ptr parent_env = f2fiber__env(fiber, cause);
  f2ptr new_env    = f2environment__new(cause,
					f2__frame__new(cause, nil),
					parent_env,
					new__symbol(cause, "push-env"));
  debug__assert(new_env, fiber, "new_env is nil");
  debug__assert(raw__environment__is_type(cause, new_env), fiber, "new_env is not environment");
  f2fiber__env__set(fiber, cause, new_env);
  return 0;
}

int f2__fiber__bytecode__newenv(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode newenv beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__newenv__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__newenv__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode machine_code [chunk]

int f2__fiber__bytecode__machine_code(f2ptr fiber, f2ptr bytecode, f2ptr chunk) {
  bytecode_status("bytecode machine_code beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__machine_code__execution_count ++;
  
  return f2chunk__bytecode_jump(chunk, cause, fiber);
}


// bytecode block_push []

int f2__fiber__bytecode__block_push__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__push__return_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__env_reg__no_increment_pc_reg(   cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__args_reg__no_increment_pc_reg(  cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__value_reg__no_increment_pc_reg( cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push_constant__no_increment_pc_reg(   cause, fiber, bytecode, __funk2.compile.debug_funk_call__symbol);
  return yield_after_this_bytecode;
}

int f2__fiber__bytecode__block_push(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_push beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_push__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__block_push__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode block_enter []

int f2__fiber__bytecode__block_enter(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_enter beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_enter__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__block_push__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__newenv__no_increment_pc_reg(    cause, fiber, bytecode);
  return yield_after_this_bytecode;
}


// bytecode block_define_rest_argument []

int f2__fiber__bytecode__block_define_rest_argument(f2ptr fiber, f2ptr bytecode, f2ptr argument) {
  bytecode_status("bytecode block_define_rest_argument beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_define_rest_argument__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__define__no_increment_pc_reg(          cause, fiber, bytecode, __funk2.primobject__frame.variable__symbol, argument);
  return yield_after_this_bytecode;
}


// bytecode block_define_argument []

int f2__fiber__bytecode__block_define_argument(f2ptr fiber, f2ptr bytecode, f2ptr argument) {
  bytecode_status("bytecode block_define_argument beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_define_argument__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__else_jump__no_increment_pc_reg(                cause, fiber, bytecode, __funk2.compile.wrong_argument_number__bcs);
  yield_after_this_bytecode |= f2__fiber__bytecode__car__no_increment_pc_reg(                      cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__define__no_increment_pc_reg(          cause, fiber, bytecode, __funk2.primobject__frame.variable__symbol, argument);
  yield_after_this_bytecode |= f2__fiber__bytecode__cdr__no_increment_pc_reg(                      cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__value_reg__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  return yield_after_this_bytecode;
}


// bytecode block_define_last_argument []

int f2__fiber__bytecode__block_define_last_argument(f2ptr fiber, f2ptr bytecode, f2ptr argument) {
  bytecode_status("bytecode block_last_argument beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_define_last_argument__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__else_jump__no_increment_pc_reg(                cause, fiber, bytecode, __funk2.compile.wrong_argument_number__bcs);
  yield_after_this_bytecode |= f2__fiber__bytecode__car__no_increment_pc_reg(                      cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__define__no_increment_pc_reg(          cause, fiber, bytecode, __funk2.primobject__frame.variable__symbol, argument);
  return yield_after_this_bytecode;
}


// bytecode block_pop []

int f2__fiber__bytecode__block_pop__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__nil__no_increment_pc_reg(       cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__nil__no_increment_pc_reg(       cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__nil__no_increment_pc_reg(       cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__env_reg__no_increment_pc_reg(   cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__return_reg__no_increment_pc_reg(cause, fiber, bytecode);
  return yield_after_this_bytecode;
}


int f2__fiber__bytecode__block_pop(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_pop__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__block_pop__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode block_exit_and_pop []

int f2__fiber__bytecode__block_exit_and_pop(f2ptr fiber, f2ptr bytecode, f2ptr funk) {
  bytecode_status("bytecode block_exit_and_pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_exit_and_pop__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__endfunk__no_increment_pc_reg(                              cause, fiber, bytecode, funk);
  yield_after_this_bytecode |= f2__fiber__bytecode__block_pop__no_increment_pc_reg(                            cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__return_reg__program_counter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  return yield_after_this_bytecode;
}


// bytecode block_exit_and_no_pop []

int f2__fiber__bytecode__block_exit_and_no_pop(f2ptr fiber, f2ptr bytecode, f2ptr funk) {
  bytecode_status("bytecode block_exit_and_no_pop beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_exit_and_no_pop__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  int yield_after_this_bytecode = 0;
  yield_after_this_bytecode |= f2__fiber__bytecode__endfunk__no_increment_pc_reg(                              cause, fiber, bytecode, funk);
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__return_reg__program_counter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  return yield_after_this_bytecode;
}


// bytecode block_eval_args_begin []

int f2__fiber__bytecode__block_eval_args_begin__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  int yield_after_this_bytecode = 0;
  
  //f2ptr exp_bcs = f2__compile__cons(cause); f2ptr full_bcs = exp_bcs; f2ptr iter = exp_bcs;
  //exp_bcs       = f2__compile__copy_iter_to_args(cause);                    iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs       = f2__compile__push_iter(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs       = f2__compile__push_args(cause);                            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  
  yield_after_this_bytecode |= f2__fiber__bytecode__cons__no_increment_pc_reg(                    cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__iter_reg__args_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__iter_reg__no_increment_pc_reg(          cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__args_reg__no_increment_pc_reg(          cause, fiber, bytecode);
  
  return yield_after_this_bytecode;
}


int f2__fiber__bytecode__block_eval_args_begin(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_eval_args_begin beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_eval_args_begin__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__block_eval_args_begin__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode block_eval_args_next []

int f2__fiber__bytecode__block_eval_args_next__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  int yield_after_this_bytecode = 0;
  
  //exp_bcs = f2__compile__pop_args(cause);            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__pop_iter(cause);            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__car__set(cause);            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__copy_iter_to_value(cause);  iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__cons(cause);                iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__swap_value_and_iter(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__cdr__set(cause);            iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__swap_value_and_iter(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__push_iter(cause);           iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__push_args(cause);           iter = f2__list_cdr__set(cause, iter, exp_bcs);
  
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__args_reg__no_increment_pc_reg(            cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__iter_reg__no_increment_pc_reg(            cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__car__set__no_increment_pc_reg(                 cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__copy__iter_reg__value_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__cons__no_increment_pc_reg(                     cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__swap__value_reg__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__cdr__set__no_increment_pc_reg(                 cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__swap__value_reg__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__iter_reg__no_increment_pc_reg(           cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__push__args_reg__no_increment_pc_reg(           cause, fiber, bytecode);
  
  return yield_after_this_bytecode;
}


int f2__fiber__bytecode__block_eval_args_next(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_eval_args_next beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_eval_args_next__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__block_eval_args_next__no_increment_pc_reg(cause, fiber, bytecode);
}


// bytecode block_eval_args_end []

int f2__fiber__bytecode__block_eval_args_end__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode) {
  int yield_after_this_bytecode = 0;
  
  //exp_bcs = f2__compile__pop_args(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__pop_iter(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
  //exp_bcs = f2__compile__car__set(cause); iter = f2__list_cdr__set(cause, iter, exp_bcs);
  
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__args_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__pop__iter_reg__no_increment_pc_reg(cause, fiber, bytecode);
  yield_after_this_bytecode |= f2__fiber__bytecode__car__set__no_increment_pc_reg(     cause, fiber, bytecode);
  
  return yield_after_this_bytecode;
}


int f2__fiber__bytecode__block_eval_args_end(f2ptr fiber, f2ptr bytecode) {
  bytecode_status("bytecode block_eval_args_end beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__block_eval_args_end__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__block_eval_args_end__no_increment_pc_reg(cause, fiber, bytecode);
}


//  bytecode eq [result x0 x1]




int f2__fiber__bytecode__eq__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-eq (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-eq (x1)", x1);
  }
  f2ptr result__value = f2__eq(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-eq (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__eq(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode eq beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__eq__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__eq__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode not [result x]

int f2__fiber__bytecode__not__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  f2ptr x__value = nil;
  if      (x == __fiber__return_reg__symbol)          {x__value = f2fiber__return_reg(     fiber, cause);}
  else if (x == __fiber__value_reg__symbol)           {x__value = f2fiber__value(          fiber, cause);}
  else if (x == __fiber__iter_reg__symbol)            {x__value = f2fiber__iter(           fiber, cause);}
  else if (x == __fiber__program_counter_reg__symbol) {x__value = f2fiber__program_counter(fiber, cause);}
  else if (x == __fiber__env_reg__symbol)             {x__value = f2fiber__env(            fiber, cause);}
  else if (x == __fiber__args_reg__symbol)            {x__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-not (x)", x);
  }
  f2ptr result__value = f2__not(cause, x__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-not (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__not(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  bytecode_status("bytecode not beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__not__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__not__no_increment_pc_reg(cause, fiber, bytecode, result, x);
}


//  bytecode and [result x0 x1]

int f2__fiber__bytecode__and__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-and (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-and (x1)", x1);
  }
  f2ptr result__value = f2__and(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-and (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__and(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode and beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__and__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__and__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode or [result x0 x1]

int f2__fiber__bytecode__or__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-or (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-or (x1)", x1);
  }
  f2ptr result__value = f2__or(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-or (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__or(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode or beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__or__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__or__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode add [result x0 x1]

int f2__fiber__bytecode__add__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-add (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-add (x1)", x1);
  }
  f2ptr result__value = f2__add(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-add (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__add(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode add beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__add__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__add__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode negative [result x]

int f2__fiber__bytecode__negative__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  f2ptr x__value = nil;
  if      (x == __fiber__return_reg__symbol)          {x__value = f2fiber__return_reg(     fiber, cause);}
  else if (x == __fiber__value_reg__symbol)           {x__value = f2fiber__value(          fiber, cause);}
  else if (x == __fiber__iter_reg__symbol)            {x__value = f2fiber__iter(           fiber, cause);}
  else if (x == __fiber__program_counter_reg__symbol) {x__value = f2fiber__program_counter(fiber, cause);}
  else if (x == __fiber__env_reg__symbol)             {x__value = f2fiber__env(            fiber, cause);}
  else if (x == __fiber__args_reg__symbol)            {x__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-negative (x)", x);
  }
  f2ptr result__value = f2__negative(cause, x__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-negative (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__negative(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  bytecode_status("bytecode negative beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__negative__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__negative__no_increment_pc_reg(cause, fiber, bytecode, result, x);
}


//  bytecode subtract [result x0 x1]

int f2__fiber__bytecode__subtract__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-subtract (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-subtract (x1)", x1);
  }
  f2ptr result__value = f2__subtract(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-subtract (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__subtract(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode subtract beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__subtract__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__subtract__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode multiply [result x0 x1]

int f2__fiber__bytecode__multiply__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-multiply (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-multiply (x1)", x1);
  }
  f2ptr result__value = f2__multiply(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-multiply (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__multiply(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode multiply beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__multiply__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__multiply__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode inverse [result x]

int f2__fiber__bytecode__inverse__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  f2ptr x__value = nil;
  if      (x == __fiber__return_reg__symbol)          {x__value = f2fiber__return_reg(     fiber, cause);}
  else if (x == __fiber__value_reg__symbol)           {x__value = f2fiber__value(          fiber, cause);}
  else if (x == __fiber__iter_reg__symbol)            {x__value = f2fiber__iter(           fiber, cause);}
  else if (x == __fiber__program_counter_reg__symbol) {x__value = f2fiber__program_counter(fiber, cause);}
  else if (x == __fiber__env_reg__symbol)             {x__value = f2fiber__env(            fiber, cause);}
  else if (x == __fiber__args_reg__symbol)            {x__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-inverse (x)", x);
  }
  f2ptr result__value = f2__inverse(cause, x__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-inverse (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__inverse(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  bytecode_status("bytecode inverse beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__inverse__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__inverse__no_increment_pc_reg(cause, fiber, bytecode, result, x);
}


//  bytecode divide [result x0 x1]

int f2__fiber__bytecode__divide__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-divide (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-divide (x1)", x1);
  }
  f2ptr result__value = f2__divide(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-divide (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__divide(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode divide beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__divide__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__divide__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode modulo [result x0 x1]

int f2__fiber__bytecode__modulo__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-modulo (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-modulo (x1)", x1);
  }
  f2ptr result__value = f2__modulo(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-modulo (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__modulo(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode modulo beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__modulo__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__modulo__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode increment [result x]

int f2__fiber__bytecode__increment__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  f2ptr x__value = nil;
  if      (x == __fiber__return_reg__symbol)          {x__value = f2fiber__return_reg(     fiber, cause);}
  else if (x == __fiber__value_reg__symbol)           {x__value = f2fiber__value(          fiber, cause);}
  else if (x == __fiber__iter_reg__symbol)            {x__value = f2fiber__iter(           fiber, cause);}
  else if (x == __fiber__program_counter_reg__symbol) {x__value = f2fiber__program_counter(fiber, cause);}
  else if (x == __fiber__env_reg__symbol)             {x__value = f2fiber__env(            fiber, cause);}
  else if (x == __fiber__args_reg__symbol)            {x__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-increment (x)", x);
  }
  f2ptr result__value = f2__increment(cause, x__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-increment (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__increment(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  bytecode_status("bytecode increment beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__increment__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__increment__no_increment_pc_reg(cause, fiber, bytecode, result, x);
}


//  bytecode decrement [result x]

int f2__fiber__bytecode__decrement__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  f2ptr x__value = nil;
  if      (x == __fiber__return_reg__symbol)          {x__value = f2fiber__return_reg(     fiber, cause);}
  else if (x == __fiber__value_reg__symbol)           {x__value = f2fiber__value(          fiber, cause);}
  else if (x == __fiber__iter_reg__symbol)            {x__value = f2fiber__iter(           fiber, cause);}
  else if (x == __fiber__program_counter_reg__symbol) {x__value = f2fiber__program_counter(fiber, cause);}
  else if (x == __fiber__env_reg__symbol)             {x__value = f2fiber__env(            fiber, cause);}
  else if (x == __fiber__args_reg__symbol)            {x__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-decrement (x)", x);
  }
  f2ptr result__value = f2__decrement(cause, x__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-decrement (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__decrement(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x) {
  bytecode_status("bytecode decrement beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__decrement__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__decrement__no_increment_pc_reg(cause, fiber, bytecode, result, x);
}


//  bytecode numerically_equals [result x0 x1]

int f2__fiber__bytecode__numerically_equals__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-numerically_equals (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-numerically_equals (x1)", x1);
  }
  f2ptr result__value = f2__numerically_equals(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-numerically_equals (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__numerically_equals(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode numerically_equals beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__numerically_equals__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__numerically_equals__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode less_than [result x0 x1]

int f2__fiber__bytecode__less_than__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-less_than (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-less_than (x1)", x1);
  }
  f2ptr result__value = f2__less_than(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-less_than (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__less_than(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode less_than beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__less_than__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__less_than__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}


//  bytecode greater_than [result x0 x1]

int f2__fiber__bytecode__greater_than__no_increment_pc_reg(f2ptr cause, f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  f2ptr x0__value = nil;
  if      (x0 == __fiber__return_reg__symbol)          {x0__value = f2fiber__return_reg(     fiber, cause);}
  else if (x0 == __fiber__value_reg__symbol)           {x0__value = f2fiber__value(          fiber, cause);}
  else if (x0 == __fiber__iter_reg__symbol)            {x0__value = f2fiber__iter(           fiber, cause);}
  else if (x0 == __fiber__program_counter_reg__symbol) {x0__value = f2fiber__program_counter(fiber, cause);}
  else if (x0 == __fiber__env_reg__symbol)             {x0__value = f2fiber__env(            fiber, cause);}
  else if (x0 == __fiber__args_reg__symbol)            {x0__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-greater_than (x0)", x0);
  }
  f2ptr x1__value = nil;
  if      (x1 == __fiber__return_reg__symbol)          {x1__value = f2fiber__return_reg(     fiber, cause);}
  else if (x1 == __fiber__value_reg__symbol)           {x1__value = f2fiber__value(          fiber, cause);}
  else if (x1 == __fiber__iter_reg__symbol)            {x1__value = f2fiber__iter(           fiber, cause);}
  else if (x1 == __fiber__program_counter_reg__symbol) {x1__value = f2fiber__program_counter(fiber, cause);}
  else if (x1 == __fiber__env_reg__symbol)             {x1__value = f2fiber__env(            fiber, cause);}
  else if (x1 == __fiber__args_reg__symbol)            {x1__value = f2fiber__args(           fiber, cause);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-greater_than (x1)", x1);
  }
  f2ptr result__value = f2__greater_than(cause, x0__value, x1__value);
  if      (result == __fiber__return_reg__symbol)          {f2fiber__return_reg__set(     fiber, cause, result__value);}
  else if (result == __fiber__value_reg__symbol)           {f2fiber__value__set(          fiber, cause, result__value);}
  else if (result == __fiber__iter_reg__symbol)            {f2fiber__iter__set(           fiber, cause, result__value);}
  else if (result == __fiber__program_counter_reg__symbol) {f2fiber__program_counter__set(fiber, cause, result__value);}
  else if (result == __fiber__env_reg__symbol)             {f2fiber__env__set(            fiber, cause, result__value);}
  else if (result == __fiber__args_reg__symbol)            {f2fiber__args__set(           fiber, cause, result__value);}
  else {
    unrecognized_bytecode_register__error(nil, cause, "fiber:bytecode-greater_than (result)", result);
  }
  return 0;
}

int f2__fiber__bytecode__greater_than(f2ptr fiber, f2ptr bytecode, f2ptr result, f2ptr x0, f2ptr x1) {
  bytecode_status("bytecode greater_than beginning.");
  f2ptr cause = f2fiber__cause_reg(fiber, nil);
  __funk2.bytecode.bytecode__greater_than__execution_count ++;
  
  f2__fiber__increment_pc(fiber, cause);
  
  return f2__fiber__bytecode__greater_than__no_increment_pc_reg(cause, fiber, bytecode, result, x0, x1);
}







// initialization of f2_bytecodes.c

void f2__bytecodes__reinitialize_globalvars() {
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  
  __funk2.bytecode.bytecode__jump_funk__symbol                  = new__symbol(cause, "jump-funk");
  __funk2.bytecode.bytecode__funk__symbol                       = new__symbol(cause, "funk");
  __funk2.bytecode.bytecode__array__symbol                      = new__symbol(cause, "array");
  __funk2.bytecode.bytecode__cons__symbol                       = new__symbol(cause, "cons");
  __funk2.bytecode.bytecode__consp__symbol                      = new__symbol(cause, "consp");
  __funk2.bytecode.bytecode__car__symbol                        = new__symbol(cause, "car");
  __funk2.bytecode.bytecode__cdr__symbol                        = new__symbol(cause, "cdr");
  __funk2.bytecode.bytecode__car__set__symbol                   = new__symbol(cause, "car-set");
  __funk2.bytecode.bytecode__cdr__set__symbol                   = new__symbol(cause, "cdr-set");
  __funk2.bytecode.bytecode__array_elt__symbol                  = new__symbol(cause, "array_elt");
  __funk2.bytecode.bytecode__set__symbol                        = new__symbol(cause, "set");
  __funk2.bytecode.bytecode__swap__symbol                       = new__symbol(cause, "swap");
  __funk2.bytecode.bytecode__push__symbol                       = new__symbol(cause, "push");
  __funk2.bytecode.bytecode__push_constant__symbol              = new__symbol(cause, "push_constant");
  __funk2.bytecode.bytecode__pop__symbol                        = new__symbol(cause, "pop");
  __funk2.bytecode.bytecode__copy__symbol                       = new__symbol(cause, "copy");
  __funk2.bytecode.bytecode__lookup__symbol                     = new__symbol(cause, "lookup");
  __funk2.bytecode.bytecode__define__symbol                     = new__symbol(cause, "define");
  __funk2.bytecode.bytecode__type_var__mutate__symbol           = new__symbol(cause, "mutate-type_var");
  __funk2.bytecode.bytecode__globalize_type_var__symbol         = new__symbol(cause, "globalize-type_var");
  __funk2.bytecode.bytecode__jump__symbol                       = new__symbol(cause, "jump");
  __funk2.bytecode.bytecode__if_jump__symbol                    = new__symbol(cause, "if-jump");
  __funk2.bytecode.bytecode__else_jump__symbol                  = new__symbol(cause, "else-jump");
  __funk2.bytecode.bytecode__nop__symbol                        = new__symbol(cause, "nop");
  __funk2.bytecode.bytecode__debug__symbol                      = new__symbol(cause, "debug");
  __funk2.bytecode.bytecode__tracer__symbol                     = new__symbol(cause, "tracer");
  __funk2.bytecode.bytecode__endfunk__symbol                    = new__symbol(cause, "endfunk");
  __funk2.bytecode.bytecode__compile__symbol                    = new__symbol(cause, "compile");
  __funk2.bytecode.bytecode__yield__symbol                      = new__symbol(cause, "yield");
  __funk2.bytecode.bytecode__newenv__symbol                     = new__symbol(cause, "newenv");
  __funk2.bytecode.bytecode__machine_code__symbol               = new__symbol(cause, "machine_code");
  
  // logic
  __funk2.bytecode.bytecode__eq__symbol                         = new__symbol(cause, "eq");
  __funk2.bytecode.bytecode__not__symbol                        = new__symbol(cause, "not");
  __funk2.bytecode.bytecode__and__symbol                        = new__symbol(cause, "and");
  __funk2.bytecode.bytecode__or__symbol                         = new__symbol(cause, "or");
  
  // math
  __funk2.bytecode.bytecode__add__symbol                        = new__symbol(cause, "add");
  __funk2.bytecode.bytecode__negative__symbol                   = new__symbol(cause, "negative");
  __funk2.bytecode.bytecode__subtract__symbol                   = new__symbol(cause, "subtract");
  __funk2.bytecode.bytecode__multiply__symbol                   = new__symbol(cause, "multiply");
  __funk2.bytecode.bytecode__inverse__symbol                    = new__symbol(cause, "inverse");
  __funk2.bytecode.bytecode__divide__symbol                     = new__symbol(cause, "divide");
  __funk2.bytecode.bytecode__modulo__symbol                     = new__symbol(cause, "modulo");
  __funk2.bytecode.bytecode__increment__symbol                  = new__symbol(cause, "increment");
  __funk2.bytecode.bytecode__decrement__symbol                  = new__symbol(cause, "decrement");
  __funk2.bytecode.bytecode__numerically_equals__symbol         = new__symbol(cause, "numerically_equals");
  __funk2.bytecode.bytecode__less_than__symbol                  = new__symbol(cause, "less_than");
  __funk2.bytecode.bytecode__greater_than__symbol               = new__symbol(cause, "greater_than");
  
  // block
  __funk2.bytecode.bytecode__block_push__symbol                 = new__symbol(cause, "block_push");
  __funk2.bytecode.bytecode__block_enter__symbol                = new__symbol(cause, "block_enter");
  __funk2.bytecode.bytecode__block_define_rest_argument__symbol = new__symbol(cause, "block_define_rest_argument");
  __funk2.bytecode.bytecode__block_define_argument__symbol      = new__symbol(cause, "block_define_argument");
  __funk2.bytecode.bytecode__block_define_last_argument__symbol = new__symbol(cause, "block_define_last_argument");
  __funk2.bytecode.bytecode__block_pop__symbol                  = new__symbol(cause, "block_pop");
  __funk2.bytecode.bytecode__block_exit_and_pop__symbol         = new__symbol(cause, "block_exit_and_pop");
  __funk2.bytecode.bytecode__block_exit_and_no_pop__symbol      = new__symbol(cause, "block_exit_and_no_pop");
  __funk2.bytecode.bytecode__block_eval_args_begin__symbol      = new__symbol(cause, "block_eval_args_begin");
  __funk2.bytecode.bytecode__block_eval_args_next__symbol       = new__symbol(cause, "block_eval_args_next");
  __funk2.bytecode.bytecode__block_eval_args_end__symbol        = new__symbol(cause, "block_eval_args_end");
  
  __funk2.bytecode.expression_not_funkable__exception__tag = new__symbol(cause, "expression-not-funkable");
}

void f2__bytecodes__defragment__fix_pointers() {
  // -- reinitialize --
  
  defragment__fix_pointer(__funk2.bytecode.bytecode__jump_funk__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__funk__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__array__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__cons__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__consp__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__car__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__cdr__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__car__set__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__cdr__set__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__array_elt__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__set__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__swap__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__push__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__push_constant__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__pop__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__copy__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__lookup__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__define__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__type_var__mutate__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__globalize_type_var__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__jump__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__if_jump__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__else_jump__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__nop__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__debug__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__tracer__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__endfunk__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__compile__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__yield__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__newenv__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__machine_code__symbol);
  
  // logic
  defragment__fix_pointer(__funk2.bytecode.bytecode__eq__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__not__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__and__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__or__symbol);
  
  // math
  defragment__fix_pointer(__funk2.bytecode.bytecode__add__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__negative__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__subtract__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__multiply__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__inverse__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__divide__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__modulo__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__increment__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__decrement__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__numerically_equals__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__less_than__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__greater_than__symbol);
  
  // block
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_push__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_enter__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_define_rest_argument__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_define_argument__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_define_last_argument__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_pop__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_exit_and_pop__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_exit_and_no_pop__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_eval_args_begin__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_eval_args_next__symbol);
  defragment__fix_pointer(__funk2.bytecode.bytecode__block_eval_args_end__symbol);
  
  
  // -- initialize --
  
  // exceptions
  
  defragment__fix_pointer(__funk2.bytecode.expression_not_funkable__exception__tag);
  
}

void f2__bytecodes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bytecodes", "", &f2__bytecodes__reinitialize_globalvars, &f2__bytecodes__defragment__fix_pointers);
  
  f2__bytecodes__reinitialize_globalvars();
  
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  
  // exceptions
  
  __funk2.bytecode.expression_not_funkable__exception__tag = new__symbol(cause, "expression-not-funkable");
}

