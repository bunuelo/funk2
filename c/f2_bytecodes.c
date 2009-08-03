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

#include "funk2.h"

void funk2_bytecode__init(funk2_bytecode_t* this) {
  this->bytecode__funk__symbol               = -1;
  this->bytecode__jump_funk__symbol          = -1;
  this->bytecode__array__symbol              = -1;
  this->bytecode__cons__symbol               = -1;
  this->bytecode__consp__symbol              = -1;
  this->bytecode__car__symbol                = -1;
  this->bytecode__cdr__symbol                = -1;
  this->bytecode__car__set__symbol           = -1;
  this->bytecode__cdr__set__symbol           = -1;
  this->bytecode__array_elt__symbol          = -1;
  this->bytecode__swap__symbol               = -1;
  this->bytecode__push__symbol               = -1;
  this->bytecode__pop__symbol                = -1;
  this->bytecode__copy__symbol               = -1;
  this->bytecode__lookup_type_var__symbol    = -1;
  this->bytecode__define_type_var__symbol    = -1;
  this->bytecode__type_var__mutate__symbol   = -1;
  this->bytecode__globalize_type_var__symbol = -1;
  this->bytecode__jump__symbol               = -1;
  this->bytecode__else_jump__symbol          = -1;
  this->bytecode__nop__symbol                = -1; // null operation (should be stripped out before executing [ideally])
  this->bytecode__debug__symbol              = -1;
  this->bytecode__trace__symbol              = -1;
  this->bytecode__compile__symbol            = -1;
  this->bytecode__yield__symbol              = -1;
  this->bytecode__newenv__symbol             = -1;
  this->bytecode__machine_code__symbol       = -1;
  
  this->bytecode_trace__print_depth = 3;
  
  this->expression_not_funkable__exception__tag = -1;
  this->expression_not_funkable__exception      = -1;
  
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
}

void f2__thread__stack__push_value(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__value(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_iter(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__iter(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_program_counter(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__program_counter(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_args(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__args(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_return(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__return(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_env(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__env(thread, cause), f2thread__stack(thread, cause)));
}

void f2__thread__stack__push_trace(f2ptr cause, f2ptr thread) {
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__trace(thread, cause), f2thread__stack(thread, cause)));
}

// pop registers

void f2__thread__stack__pop_value(f2ptr thread, f2ptr cause)           {f2thread__value__set(          thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_iter(f2ptr thread, f2ptr cause)            {f2thread__iter__set(           thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_program_counter(f2ptr thread, f2ptr cause) {f2thread__program_counter__set(thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_args(f2ptr thread, f2ptr cause)            {f2thread__args__set(           thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_return(f2ptr thread, f2ptr cause)          {f2thread__return__set(         thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_env(f2ptr thread, f2ptr cause)             {f2thread__env__set(            thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_trace(f2ptr thread, f2ptr cause)           {f2thread__trace__set(          thread, cause, f2cons__car(f2thread__stack(thread, cause), cause)); f2thread__stack__set(thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}
void f2__thread__stack__pop_nil(f2ptr thread, f2ptr cause)             {f2thread__stack__set(          thread, cause, f2cons__cdr(f2thread__stack(thread, cause), cause));}

f2ptr f2__expression_not_funkable__exception__new(f2ptr cause, f2ptr funktion) {return f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, funktion);}

void unrecognized_bytecode_register__error(f2ptr thread, f2ptr cause, char* bytecode_name, f2ptr reg) {
  char reg_str[1024];
  if(raw__symbol__is_type(cause, reg)) {
    f2symbol__str_copy(reg, cause, (u8*)reg_str);
    reg_str[f2symbol__length(reg, cause)] = (u8)0;
  } else {
    sprintf(reg_str, "<not symbolic>");
  }
  char str[1024];
  sprintf(str, "%s error: unrecognized bytecode register (%s).", bytecode_name, reg_str);
  error(thread, str);
}

void f2__thread__increment_pc(f2ptr thread, f2ptr cause) {
  f2ptr pc_reg = f2thread__program_counter(thread, cause);
  release__assert(pc_reg, thread, "f2__thread__increment_pc error: pc_reg is nil.");
  f2thread__program_counter__set(thread, cause, f2cons__cdr(pc_reg, cause));
}


#ifdef DEBUG_BYTECODES
#  define bytecode_status(msg, rest...) status(msg, ## rest)
#else
#  define bytecode_status(msg, rest...)
#endif

// bytecode jump_funk []

int f2__thread__bytecode_helper__jump_funk__no_increment_pc_reg(f2ptr thread, f2ptr cause) {
  f2ptr funktion = f2thread__value(thread, cause);
  //assert(funktion != nil, thread, "f2__thread__bytecode__funk assertion failed: funktion is null.");
  
  if (raw__funk__is_type(cause, funktion)) {
    //trace2(bytecode__jump_funk, funktion, f2thread__args(thread));
    f2thread__env__set(thread, cause, f2funk__env(funktion, cause));
    f2ptr body_bcs           = f2funk__body_bytecodes(funktion, cause);
    if (raw__larva__is_type(cause, body_bcs)) {
      f2thread__value__set(thread, cause, body_bcs);
      return 1;
    }
    f2ptr machine_code = f2funk__machine_code(funktion, cause);
    f2thread__program_counter__set(thread, cause, body_bcs);
    if (machine_code) {
      return f2chunk__bytecode_jump(machine_code, cause, thread);
    } else {
      return 1;
    }
  } else if (raw__cfunk__is_type(cause, funktion)) {
    f2ptr args = f2thread__args(thread, cause);
    //trace2(bytecode__jump_funk, funktion, args);
    release__assert(!args || raw__cons__is_type(cause, args), thread, "args failed args type assertion.");
    f2ptr value = f2__cfunk__apply(cause, funktion, thread, args);
    f2thread__value__set(thread, cause, value);
    return 1;
  } else if (raw__metro__is_type(cause, funktion)) {
    //trace2(bytecode__jump_funk, funktion, f2thread__args(thread));
    f2thread__env__set(thread, cause, f2metro__env(funktion, cause));
    f2ptr body_bcs           = f2metro__body_bytecodes(funktion, cause);
    if (raw__larva__is_type(cause, body_bcs)) {
      f2thread__value__set(thread, cause, body_bcs);
      return 1;
    }
    f2ptr machine_code = f2metro__machine_code(funktion, cause);
    f2thread__program_counter__set(thread, cause, body_bcs);
    if (machine_code) {
      //fflush(stdout); f2__print_prompt("jumping to metro machine code: ", funktion); fflush(stdout);
      return f2chunk__bytecode_jump(machine_code, cause, thread);
    } else {
      return 1;
    }
  }
  f2ptr retval = f2larva__new(cause, 18);
  //f2__expression_not_funkable__exception__new(cause, funktion);
  //printf("\n"); f2__print(nil, retval); fflush(stdout); printf("\n");
  //error(thread, "error: expression not funkable");
  f2thread__value__set(thread, cause, retval);
  return 1;
}

int f2__thread__bytecode__jump_funk(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  return f2__thread__bytecode_helper__jump_funk__no_increment_pc_reg(thread, cause);
}


// bytecode funk []
//
//   note: this is where we set the return register (f2_compile.c assumes that this happens atomically with this bytecode).
//
int f2__thread__bytecode_helper__funk__no_increment_pc_reg(f2ptr thread, f2ptr cause) {
  f2thread__return__set(thread, cause, f2thread__program_counter(thread, cause)); // f2__thread__bytecode__copy(thread, __thread__program_counter_reg__symbol, __thread__return_reg__symbol);
  return f2__thread__bytecode_helper__jump_funk__no_increment_pc_reg(thread, cause);
}

int f2__thread__bytecode__funk(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  return f2__thread__bytecode_helper__funk__no_increment_pc_reg(thread, cause);
}


// bytecode array [length]

int f2__thread__bytecode__array(f2ptr thread, f2ptr bytecode, f2ptr length) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr new_array = f2traced_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));
  if (! new_array) {
    error(nil, "array bytecode error: new array is nil");
  }
  f2thread__iter__set(thread, cause, new_array);
  return 0;
}


// bytecode cons []

int f2__thread__bytecode__cons(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr new_cons = f2cons__new(cause, nil, nil);
  if (! new_cons) {error(nil, "cons bytecode error: new cons is nil");}
  f2thread__iter__set(thread, cause, new_cons);
  return 0;
}


// bytecode consp []

int f2__thread__bytecode__consp(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr result = f2bool__new(raw__cons__is_type(cause, f2thread__value(thread, cause)));
  f2thread__value__set(thread, cause, result);
  return 0;
}


// bytecode car []

int f2__thread__bytecode__car(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2cons__car(f2thread__iter(thread, cause), cause));
  return 0;
}


// bytecode cdr []

int f2__thread__bytecode__cdr(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2cons__cdr(f2thread__iter(thread, cause), cause));
  return 0;
}


// bytecode car__set []

int f2__thread__bytecode__car__set(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2cons__car__set(f2thread__iter(thread, cause), cause, f2thread__value(thread, cause));
  return 0;
}


// bytecode cdr__set []

int f2__thread__bytecode__cdr__set(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2cons__cdr__set(f2thread__iter(thread, cause), cause, f2thread__value(thread, cause));
  return 0;
}


// bytecode array_elt [array index]

int f2__thread__bytecode__array_elt(f2ptr thread, f2ptr bytecode, f2ptr array, f2ptr index) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2__array__elt(cause, array, index));
  return 0;
}


// bytecode set [reg f2ptr]

int f2__thread__bytecode__set__value_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__program_counter_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if (raw__exception__is_type(cause, exp)) {
    f2thread__value__set(thread, cause, exp);
  } else {
    f2thread__program_counter__set(thread, cause, exp);
  }
  return 1;
}

int f2__thread__bytecode__set__iter_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__args_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__return_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__env_reg(f2ptr thread, f2ptr bytecode, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, exp);
  return 0;
}

bytecode_jump__f2ptr_t f2__compile__bytecode__set(f2ptr cause, f2ptr reg) {
  if      (reg == __thread__value_reg__symbol)           {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__value_reg;}
  else if (reg == __thread__program_counter_reg__symbol) {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__program_counter_reg;}
  else if (reg == __thread__iter_reg__symbol)            {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__iter_reg;}
  else if (reg == __thread__args_reg__symbol)            {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__args_reg;}
  else if (reg == __thread__return_reg__symbol)          {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__return_reg;}
  else if (reg == __thread__env_reg__symbol)             {return (bytecode_jump__f2ptr_t)&f2__thread__bytecode__set__env_reg;}
  unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-set", reg);
  return NULL;
}

int f2__thread__bytecode__set(f2ptr thread, f2ptr bytecode, f2ptr reg, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__set(cause, reg))(thread, bytecode, exp);
}


// bytecode nop []

int f2__thread__bytecode__nop(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  return 0;
}


// bytecode swap [reg reg]

int f2__thread__bytecode__swap__return_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__value( thread, cause));
  f2thread__value__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__iter(  thread, cause));
  f2thread__iter__set(  thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__return(         thread, cause);
  f2thread__return__set(         thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__return_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__env(   thread, cause));
  f2thread__env__set(   thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__args(  thread, cause));
  f2thread__args__set(  thread, cause, temp);
  return 0;
}


int f2__thread__bytecode__swap__value_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__iter( thread, cause));
  f2thread__iter__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__value_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__value(          thread, cause);
  f2thread__value__set(          thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__value_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__env(  thread, cause));
  f2thread__env__set(  thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__value_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__args( thread, cause));
  f2thread__args__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__iter_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__iter(           thread, cause);
  f2thread__iter__set(           thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__iter_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                       f2thread__iter(thread, cause);
  f2thread__iter__set(thread, cause, f2thread__env( thread, cause));
  f2thread__env__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__iter_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                       f2thread__iter(thread, cause);
  f2thread__iter__set(thread, cause, f2thread__args(thread, cause));
  f2thread__args__set(thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__program_counter_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__program_counter(thread, cause);
  f2thread__program_counter__set(thread, cause, f2thread__env(            thread, cause));
  f2thread__env__set(            thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__program_counter_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__program_counter(thread, cause);
  f2thread__program_counter__set(thread, cause, f2thread__args(           thread, cause));
  f2thread__args__set(           thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__env_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                       f2thread__env( thread, cause);
  f2thread__env__set( thread, cause, f2thread__args(thread, cause));
  f2thread__args__set(thread, cause, temp);
  return 0;
}


bytecode_jump_t f2__compile__bytecode__swap(f2ptr cause, f2ptr reg0, f2ptr reg1) {
  if        (reg0 == __thread__return_reg__symbol)          {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__swap__return_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__swap__return_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__swap__return_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__swap__return_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__swap__return_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__value_reg__symbol)           {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__swap__return_reg__value_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__swap__value_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__swap__value_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__swap__value_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__swap__value_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__iter_reg__symbol)            {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__swap__return_reg__iter_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__swap__value_reg__iter_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__swap__iter_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__swap__iter_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__swap__iter_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__program_counter_reg__symbol) {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__swap__return_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__swap__value_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__swap__iter_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__swap__program_counter_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__swap__program_counter_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__env_reg__symbol)             {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__swap__return_reg__env_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__swap__value_reg__env_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__swap__iter_reg__env_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__swap__program_counter_reg__env_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__swap__env_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__args_reg__symbol)            {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__swap__return_reg__args_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__swap__value_reg__args_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__swap__iter_reg__args_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__swap__program_counter_reg__args_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__swap__env_reg__args_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__nop;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-swap (reg0)", reg0);
							     return (bytecode_jump_t)NULL;}
}

int f2__thread__bytecode__swap(f2ptr thread, f2ptr bytecode, f2ptr reg0, f2ptr reg1) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__swap(cause, reg0, reg1))(thread, bytecode);
}


// bytecode push [reg]

int f2__thread__bytecode__push__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_return(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_env(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_value(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_iter(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_args(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_program_counter(cause, thread);  
  return 0;
}

bytecode_jump_t f2__compile__bytecode__push(f2ptr cause, f2ptr reg) {
  if      (reg == __thread__return_reg__symbol)          {return &f2__thread__bytecode__push__return_reg;}
  else if (reg == __thread__env_reg__symbol)             {return &f2__thread__bytecode__push__env_reg;}
  else if (reg == __thread__value_reg__symbol)           {return &f2__thread__bytecode__push__value_reg;}
  else if (reg == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__push__iter_reg;}
  else if (reg == __thread__args_reg__symbol)            {return &f2__thread__bytecode__push__args_reg;}
  else if (reg == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__push__program_counter_reg;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-push", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__thread__bytecode__push(f2ptr thread, f2ptr bytecode, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__push(cause, reg))(thread, bytecode);
}

// bytecode pop [reg]

int f2__thread__bytecode__pop__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_return(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_env(thread, cause);
  release__assert(f2thread__env(thread, cause), thread, "env popped to nil.");
  release__assert(raw__environment__is_type(cause, f2thread__env(thread, cause)), thread, "assertion failed: popped to non-environment");
  //f2__print(nil, f2thread__env(thread));
  //fflush(stdout);
  return 0;
}

int f2__thread__bytecode__pop__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_value(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_iter(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_args(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_program_counter(thread, cause);
  return 1;
}

int f2__thread__bytecode__pop__nil(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_nil(thread, cause);
  return 0;
}

bytecode_jump_t f2__compile__bytecode__pop(f2ptr cause, f2ptr reg) {
  if      (reg == __thread__return_reg__symbol)          {return &f2__thread__bytecode__pop__return_reg;}
  else if (reg == __thread__env_reg__symbol)             {return &f2__thread__bytecode__pop__env_reg;}
  else if (reg == __thread__value_reg__symbol)           {return &f2__thread__bytecode__pop__value_reg;}
  else if (reg == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__pop__iter_reg;}
  else if (reg == __thread__args_reg__symbol)            {return &f2__thread__bytecode__pop__args_reg;}
  else if (reg == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__pop__program_counter_reg;}
  else if (reg == nil)                                   {return &f2__thread__bytecode__pop__nil;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-pop", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__thread__bytecode__pop(f2ptr thread, f2ptr bytecode, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__pop(cause, reg))(thread, bytecode);
}


// bytecode copy [reg reg]

int f2__thread__bytecode__copy__return_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__return(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__return_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__value_reg__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__value(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__value_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__iter_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__iter(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__iter_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__program_counter_reg__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, nil);
  
  f2thread__iter__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__env_reg__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__env(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__env_reg__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__args_reg__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__args(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__args_reg__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}


bytecode_jump_t f2__compile__bytecode__copy(f2ptr cause, f2ptr reg0, f2ptr reg1) {
  if        (reg0 == __thread__return_reg__symbol)          {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__copy__return_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__copy__return_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__copy__return_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__copy__return_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__copy__return_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__value_reg__symbol)           {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__copy__value_reg__return_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__copy__value_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__copy__value_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__copy__value_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__copy__value_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__iter_reg__symbol)            {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__copy__iter_reg__return_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__copy__iter_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__copy__iter_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__copy__iter_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__copy__iter_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__program_counter_reg__symbol) {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__copy__program_counter_reg__return_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__copy__program_counter_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__copy__program_counter_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__copy__program_counter_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__copy__program_counter_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__env_reg__symbol)             {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__copy__env_reg__return_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__copy__env_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__copy__env_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__copy__env_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__nop;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__copy__env_reg__args_reg;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else if (reg0 == __thread__args_reg__symbol)            {if      (reg1 == __thread__return_reg__symbol)          {return &f2__thread__bytecode__copy__args_reg__return_reg;}
                                                             else if (reg1 == __thread__value_reg__symbol)           {return &f2__thread__bytecode__copy__args_reg__value_reg;}
                                                             else if (reg1 == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__copy__args_reg__iter_reg;}
                                                             else if (reg1 == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__copy__args_reg__program_counter_reg;}
                                                             else if (reg1 == __thread__env_reg__symbol)             {return &f2__thread__bytecode__copy__args_reg__env_reg;}
                                                             else if (reg1 == __thread__args_reg__symbol)            {return &f2__thread__bytecode__nop;}
                                                             else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg1)", reg1);
							                                                              return (bytecode_jump_t)NULL;}
  } else                                                    {unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-copy (reg0)", reg0);
							     return (bytecode_jump_t)NULL;}
}

int f2__thread__bytecode__copy(f2ptr thread, f2ptr bytecode, f2ptr src_reg, f2ptr dest_reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__copy(cause, src_reg, dest_reg))(thread, bytecode);
}


// bytecode lookup_type_var [f2ptr f2ptr]

int f2__thread__bytecode__lookup_type_var(f2ptr thread, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env = f2thread__env(thread, cause);
  f2ptr thread_value = environment__lookup_type_var_value(cause, env, type, var);
  //if (raw__larva__is_type(cause, thread_value)) {
  //  thread_value = f2__cause__lookup_type_var_value(cause, cause, type, var);
  //}
  f2thread__value__set(thread, cause, thread_value);
  return 0;
}


// bytecode define_type_var [f2ptr f2ptr]

int f2__thread__bytecode__define_type_var(f2ptr thread, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env   = f2thread__env(thread, cause);
  f2ptr value = f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, environment__define_type_var_value(cause, env, type, var, value));
  return 0;
}


// bytecode type_var__mutate [f2ptr f2ptr]

int f2__thread__bytecode__type_var__mutate(f2ptr thread, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env        = f2thread__env(thread, cause);
  f2ptr value      = f2thread__value(thread, cause);
  f2ptr new_value = environment__type_var_value__set(cause, env, type, var, value);
  f2thread__value__set(thread, cause, new_value);
  return 0;
}


// bytecode globalize_type_var [f2ptr f2ptr]

int f2__thread__bytecode__globalize_type_var(f2ptr thread, f2ptr bytecode, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr value = f2thread__value(thread, cause);
  if (! raw__larva__is_type(cause, value)) {
    f2thread__value__set(thread, cause, environment__define_type_var_value(cause, global_environment(), type, var, value));
  }
  return 0;
}


// bytecode jump [f2ptr]

int f2__thread__bytecode__jump(f2ptr thread, f2ptr bytecode, f2ptr new_program_counter) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if (raw__exception__is_type(cause, new_program_counter)) {
    f2thread__value__set(thread, cause, new_program_counter);
  } else {
    f2thread__program_counter__set(thread, cause, new_program_counter);
  }
  return 1;
}


// bytecode else_jump [f2ptr]

int f2__thread__bytecode__else_jump(f2ptr thread, f2ptr bytecode, f2ptr new_program_counter) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if(! f2thread__value(thread, cause)) {
    if (raw__exception__is_type(cause, new_program_counter)) {
      f2thread__value__set(thread, cause, new_program_counter);
    } else {
      f2thread__program_counter__set(thread, cause, new_program_counter);
    }
  }
  return 1;
}


// bytecode debug [f2ptr]

int f2__thread__bytecode__debug(f2ptr thread, f2ptr bytecode, f2ptr value) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  printf("\ndebug: *** "); f2__write(thread, value); printf(" ***"); fflush(stdout);
  return 0;
}


// bytecode trace [f2ptr]

int f2__thread__bytecode__trace(f2ptr thread, f2ptr bytecode, f2ptr value) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr thread_trace   = f2thread__trace(thread, cause);
  f2ptr new_doublelink = f2doublelink__new(cause, thread_trace, nil, value);
  if (thread_trace) {
    f2doublelink__next__set(thread_trace, cause, new_doublelink);
  }
  f2thread__trace__set(thread, cause, new_doublelink);
  return 0;
}


// bytecode compile [boolean_t]

int f2__thread__bytecode__compile__protect_environment(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr protect_environment = __funk2.globalenv.true__symbol;
  boolean_t  is_funktional       = boolean__true;
  f2thread__value__set(thread, cause, raw__compile(cause, thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

int f2__thread__bytecode__compile__nil(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr protect_environment = nil;
  boolean_t  is_funktional       = boolean__true;
  f2thread__value__set(thread, cause, raw__compile(cause, thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

bytecode_jump_t f2__compile__bytecode__compile(f2ptr protect_environment) {
  if (protect_environment != nil) {
    return &f2__thread__bytecode__compile__protect_environment;
  } else {
    return &f2__thread__bytecode__compile__nil;
  }
}

int f2__thread__bytecode__compile(f2ptr thread, f2ptr bytecode, f2ptr protect_environment) {
  return (f2__compile__bytecode__compile(protect_environment))(thread, bytecode);
}


// bytecode yield []

int f2__thread__bytecode__yield(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  return 0;
}


// bytecode newenv []

int f2__thread__bytecode__newenv(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr parent_env = f2thread__env(thread, cause);
  f2ptr new_env    = f2environment__new(cause,
					f2__frame__new(cause),
					parent_env,
					f2symbol__new(cause, strlen("push-env"), (u8*)"push-env"));
  release__assert(new_env, thread, "new_env is nil");
  release__assert(raw__environment__is_type(cause, new_env), thread, "new_env is not environment");
  f2thread__env__set(thread, cause, new_env);
  return 0;
}


// bytecode machine_code [chunk]

int f2__thread__bytecode__machine_code(f2ptr thread, f2ptr bytecode, f2ptr chunk) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return f2chunk__bytecode_jump(chunk, cause, thread);
}


// bytecode reg_array__elt [reg]

void raw__thread__bytecode_helper__reg_array__elt(f2ptr cause, f2ptr bytecode, f2ptr thread, f2ptr reg_value) {
  f2ptr elt       = nil;
  if (! raw__array__is_type(cause, reg_value)) {
    elt = f2larva__new(cause, 1);
  } else {
    u64 length = f2__array__length(cause, reg_value);
    f2ptr index = f2bytecode__arg1(bytecode, cause);
    if (! raw__integer__is_type(cause, index)) {
      elt =  f2larva__new(cause, 1);
    } else {
      u64 raw_index = f2integer__i(index, cause);
      if (! raw__integer__is_type(cause, index)) {
	elt =  f2larva__new(cause, 1);
      } else {
	if (raw_index < 0 || raw_index >= length) {
	  elt =  f2larva__new(cause, 2);
	} else {
	  elt = raw__array__elt(cause, reg_value, raw_index);
	}
      }
    }
  }
  f2thread__value__set(thread, cause, elt);
}

int f2__thread__bytecode__reg_array__elt__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__return(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__env(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__value(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__iter(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__args(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__program_counter(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt(cause, bytecode, thread, reg_value);
  return 0;
}

bytecode_jump_t f2__compile__bytecode__reg_array__elt(f2ptr cause, f2ptr reg) {
  if      (reg == __thread__return_reg__symbol)          {return &f2__thread__bytecode__reg_array__elt__return_reg;}
  else if (reg == __thread__env_reg__symbol)             {return &f2__thread__bytecode__reg_array__elt__env_reg;}
  else if (reg == __thread__value_reg__symbol)           {return &f2__thread__bytecode__reg_array__elt__value_reg;}
  else if (reg == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__reg_array__elt__iter_reg;}
  else if (reg == __thread__args_reg__symbol)            {return &f2__thread__bytecode__reg_array__elt__args_reg;}
  else if (reg == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__reg_array__elt__program_counter_reg;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-reg_array__elt", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__thread__bytecode__reg_array__elt(f2ptr thread, f2ptr bytecode, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__reg_array__elt(cause, reg))(thread, bytecode);
}


// bytecode reg_array__elt__set [reg]

void raw__thread__bytecode_helper__reg_array__elt__set(f2ptr cause, f2ptr bytecode, f2ptr thread, f2ptr reg_value) {
  f2ptr elt = nil;
  if (! raw__array__is_type(cause, reg_value)) {
    elt = f2larva__new(cause, 1);
  } else {
    u64 length = f2__array__length(cause, reg_value);
    f2ptr index = f2bytecode__arg1(bytecode, cause);
    if (! raw__integer__is_type(cause, index)) {
      elt =  f2larva__new(cause, 1);
    } else {
      u64 raw_index = f2integer__i(index, cause);
      if (! raw__integer__is_type(cause, index)) {
	elt =  f2larva__new(cause, 1);
      } else {
	if (raw_index < 0 || raw_index >= length) {
	  elt =  f2larva__new(cause, 2);
	} else {
	  raw__array__elt__set(cause, reg_value, raw_index, f2thread__value(thread, cause));
	  //elt = nil;
	}
      }
    }
  }
  f2thread__value__set(thread, cause, elt);
}

int f2__thread__bytecode__reg_array__elt__set__return_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__return(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__set__env_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__env(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__set__value_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__value(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__set__iter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__iter(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__set__args_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__args(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

int f2__thread__bytecode__reg_array__elt__set__program_counter_reg(f2ptr thread, f2ptr bytecode) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr reg_value = f2thread__program_counter(thread, cause);
  
  raw__thread__bytecode_helper__reg_array__elt__set(cause, bytecode, thread, reg_value);
  return 0;
}

bytecode_jump_t f2__compile__bytecode__reg_array__elt__set(f2ptr cause, f2ptr reg) {
  if      (reg == __thread__return_reg__symbol)          {return &f2__thread__bytecode__reg_array__elt__set__return_reg;}
  else if (reg == __thread__env_reg__symbol)             {return &f2__thread__bytecode__reg_array__elt__set__env_reg;}
  else if (reg == __thread__value_reg__symbol)           {return &f2__thread__bytecode__reg_array__elt__set__value_reg;}
  else if (reg == __thread__iter_reg__symbol)            {return &f2__thread__bytecode__reg_array__elt__set__iter_reg;}
  else if (reg == __thread__args_reg__symbol)            {return &f2__thread__bytecode__reg_array__elt__set__args_reg;}
  else if (reg == __thread__program_counter_reg__symbol) {return &f2__thread__bytecode__reg_array__elt__set__program_counter_reg;}
  else {
    unrecognized_bytecode_register__error(nil, cause, "thread:bytecode-reg_array__elt__set", reg);
    return (bytecode_jump_t)NULL;
  }
}

int f2__thread__bytecode__reg_array__elt__set(f2ptr thread, f2ptr bytecode, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__reg_array__elt__set(cause, reg))(thread, bytecode);
}


// initialization of f2_bytecodes.c

void f2__bytecodes__reinitialize_globalvars() {
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  
  __funk2.bytecode.bytecode__jump_funk__symbol           = f2symbol__new(cause, strlen("jump-funk"),          (u8*)"jump-funk");
  __funk2.bytecode.bytecode__funk__symbol                = f2symbol__new(cause, strlen("funk"),               (u8*)"funk");
  __funk2.bytecode.bytecode__array__symbol               = f2symbol__new(cause, strlen("array"),              (u8*)"array");
  __funk2.bytecode.bytecode__cons__symbol                = f2symbol__new(cause, strlen("cons"),               (u8*)"cons");
  __funk2.bytecode.bytecode__consp__symbol               = f2symbol__new(cause, strlen("consp"),              (u8*)"consp");
  __funk2.bytecode.bytecode__car__symbol                 = f2symbol__new(cause, strlen("car"),                (u8*)"car");
  __funk2.bytecode.bytecode__cdr__symbol                 = f2symbol__new(cause, strlen("cdr"),                (u8*)"cdr");
  __funk2.bytecode.bytecode__car__set__symbol            = f2symbol__new(cause, strlen("car-set"),            (u8*)"car-set");
  __funk2.bytecode.bytecode__cdr__set__symbol            = f2symbol__new(cause, strlen("cdr-set"),            (u8*)"cdr-set");
  __funk2.bytecode.bytecode__array_elt__symbol           = f2symbol__new(cause, strlen("array_elt"),          (u8*)"array_elt");
  __funk2.bytecode.bytecode__set__symbol                 = f2symbol__new(cause, strlen("set"),                (u8*)"set");
  __funk2.bytecode.bytecode__swap__symbol                = f2symbol__new(cause, strlen("swap"),               (u8*)"swap");
  __funk2.bytecode.bytecode__push__symbol                = f2symbol__new(cause, strlen("push"),               (u8*)"push");
  __funk2.bytecode.bytecode__pop__symbol                 = f2symbol__new(cause, strlen("pop"),                (u8*)"pop");
  __funk2.bytecode.bytecode__copy__symbol                = f2symbol__new(cause, strlen("copy"),               (u8*)"copy");
  __funk2.bytecode.bytecode__lookup_type_var__symbol     = f2symbol__new(cause, strlen("lookup"),             (u8*)"lookup");
  __funk2.bytecode.bytecode__define_type_var__symbol     = f2symbol__new(cause, strlen("define"),             (u8*)"define");
  __funk2.bytecode.bytecode__type_var__mutate__symbol    = f2symbol__new(cause, strlen("mutate-type_var"),    (u8*)"mutate-type_var");
  __funk2.bytecode.bytecode__globalize_type_var__symbol  = f2symbol__new(cause, strlen("globalize-type_var"), (u8*)"globalize-type_var");
  __funk2.bytecode.bytecode__jump__symbol                = f2symbol__new(cause, strlen("jump"),               (u8*)"jump");
  __funk2.bytecode.bytecode__else_jump__symbol           = f2symbol__new(cause, strlen("else-jump"),          (u8*)"else-jump");
  __funk2.bytecode.bytecode__nop__symbol                 = f2symbol__new(cause, strlen("nop"),                (u8*)"nop");
  __funk2.bytecode.bytecode__debug__symbol               = f2symbol__new(cause, strlen("debug"),              (u8*)"debug");
  __funk2.bytecode.bytecode__trace__symbol               = f2symbol__new(cause, strlen("trace"),              (u8*)"trace");
  __funk2.bytecode.bytecode__compile__symbol             = f2symbol__new(cause, strlen("compile"),            (u8*)"compile");
  __funk2.bytecode.bytecode__yield__symbol               = f2symbol__new(cause, strlen("yield"),              (u8*)"yield");
  __funk2.bytecode.bytecode__newenv__symbol              = f2symbol__new(cause, strlen("newenv"),             (u8*)"newenv");
  __funk2.bytecode.bytecode__machine_code__symbol        = f2symbol__new(cause, strlen("machine_code"),       (u8*)"machine_code");
  __funk2.bytecode.bytecode__reg_array__elt__symbol      = f2symbol__new(cause, strlen("reg_array-elt"),      (u8*)"reg_array-elt");
  __funk2.bytecode.bytecode__reg_array__elt__set__symbol = f2symbol__new(cause, strlen("reg_array-elt-set"),  (u8*)"reg_array-elt-set");
  
  __funk2.bytecode.expression_not_funkable__exception__tag = f2symbol__new(cause, strlen("expression-not-funkable"), (u8*)"expression-not-funkable");
  __funk2.bytecode.expression_not_funkable__exception      = f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, nil);
}

void f2__bytecodes__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bytecodes", "", &f2__bytecodes__reinitialize_globalvars);
  
  f2__bytecodes__reinitialize_globalvars();
  
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  
  // exceptions
  
  __funk2.bytecode.expression_not_funkable__exception__tag = f2symbol__new(cause, strlen("expression-not-funkable"), (u8*)"expression-not-funkable");
  __funk2.bytecode.expression_not_funkable__exception      = f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, nil);
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.expression_not_funkable__exception__tag, __funk2.bytecode.expression_not_funkable__exception);
}

