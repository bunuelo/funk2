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
  this->bytecode__car__symbol                = -1;
  this->bytecode__cdr__symbol                = -1;
  this->bytecode__car__set__symbol           = -1;
  this->bytecode__cdr__set__symbol           = -1;
  this->bytecode__array_elt__symbol          = -1;
  this->bytecode__set__symbol                = -1;
  this->bytecode__swap__symbol               = -1;
  this->bytecode__push__symbol               = -1;
  this->bytecode__pop__symbol                = -1;
  this->bytecode__copy__symbol               = -1;
  this->bytecode__lookup_type_var__symbol    = -1;
  this->bytecode__define_type_var__symbol    = -1;
  this->bytecode__type_var__set__symbol      = -1;
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
  
  // push registers
  
  this->bytecode_trace__print_depth = 3;
}

void funk2_bytecode__destroy(funk2_bytecode_t* this) {
}

//void f2__thread__push_value(f2ptr cause, f2ptr thread)           {f2ptr reg = f2thread__value_register(thread);           if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_value_register(thread, reg);}
//void f2__thread__push_iter(f2ptr cause, f2ptr thread)            {f2ptr reg = f2thread__iter_register(thread);            if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_iter_register(thread, reg);}
//void f2__thread__push_program_counter(f2ptr cause, f2ptr thread) {f2ptr reg = f2thread__program_counter_register(thread); if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause,      f2cons__car(reg),   reg);} f2thread__set_program_counter_register(thread, reg);}
//void f2__thread__push_args(f2ptr cause, f2ptr thread)            {f2ptr reg = f2thread__args_register(thread);            if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_args_register(thread, reg);}
//void f2__thread__push_return(f2ptr cause, f2ptr thread)          {f2ptr reg = f2thread__return_register(thread);          if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_return_register(thread, reg);}
//void f2__thread__push_env(f2ptr cause, f2ptr thread)             {f2ptr reg = f2thread__env_register(thread);             if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_env_register(thread, reg);}
//void f2__thread__push_trace(f2ptr cause, f2ptr thread)           {f2ptr reg = f2thread__trace_register(thread);           if (!reg) {reg = f2cons__new(cause, nil, nil);} else {reg = f2cons__new(cause, nil/*f2cons__car(reg)*/, reg);} f2thread__set_trace_register(thread, reg);}

//void f2__thread__pop_value(f2ptr thread)           {f2ptr reg = f2thread__value_register(thread);           if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_value_register(thread, reg);}
//void f2__thread__pop_iter(f2ptr thread)            {f2ptr reg = f2thread__iter_register(thread);            if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_iter_register(thread, reg);}
//void f2__thread__pop_program_counter(f2ptr thread) {f2ptr reg = f2thread__program_counter_register(thread); if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_program_counter_register(thread, reg);}
//void f2__thread__pop_args(f2ptr thread)            {f2ptr reg = f2thread__args_register(thread);            if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_args_register(thread, reg);}
//void f2__thread__pop_return(f2ptr thread)          {f2ptr reg = f2thread__return_register(thread);          if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_return_register(thread, reg);}
//void f2__thread__pop_env(f2ptr thread)             {f2ptr reg = f2thread__env_register(thread);             if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_env_register(thread, reg);}
//void f2__thread__pop_trace(f2ptr thread)           {f2ptr reg = f2thread__trace_register(thread);           if (!reg) {reg = nil;} else {reg = f2cons__cdr(reg);} f2thread__set_trace_register(thread, reg);}

void f2__thread__stack__push_value(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__value(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_iter(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__iter(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_program_counter(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__program_counter(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_args(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__args(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_return(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__return(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_env(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__env(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
}

void f2__thread__stack__push_trace(f2ptr cause, f2ptr thread) {
  pause_gc();
  f2thread__stack__set(thread, cause, f2cons__new(cause, f2thread__trace(thread, cause), f2thread__stack(thread, cause)));
  resume_gc();
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
  if(raw__symbolp(reg, cause)) {
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


// bytecode jump_funk []

void raw__thread__bytecode_trace__jump_funk(f2ptr cause, f2ptr thread) {
  status("bytecode trace: jump_funk");
}

int f2__thread__bytecode_helper__jump_funk__no_increment_pc_reg(f2ptr thread, f2ptr cause) {
  f2ptr funktion = f2thread__value(thread, cause);
  //assert(funktion != nil, thread, "f2__thread__bytecode__funk assertion failed: funktion is null.");
  
  if (raw__funkp(funktion, cause)) {
    //trace2(bytecode__jump_funk, funktion, f2thread__args(thread));
    f2thread__env__set(thread, cause, f2funk__env(funktion, cause));
    f2ptr body_bcs           = f2funk__body_bytecodes(funktion, cause);
    if (raw__larvap(body_bcs, cause)) {
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
  } else if (raw__cfunkp(funktion, cause)) {
    f2ptr args = f2thread__args(thread, cause);
    //trace2(bytecode__jump_funk, funktion, args);
    release__assert(!args || raw__consp(args, cause), thread, "args failed args type assertion.");
    f2ptr value = f2__cfunk__apply(cause, funktion, thread, args);
    f2thread__value__set(thread, cause, value);
    return 1;
  } else if (raw__metrop(funktion, cause)) {
    //trace2(bytecode__jump_funk, funktion, f2thread__args(thread));
    f2thread__env__set(thread, cause, f2metro__env(funktion, cause));
    f2ptr body_bcs           = f2metro__body_bytecodes(funktion, cause);
    if (raw__larvap(body_bcs, cause)) {
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

int f2__thread__bytecode__jump_funk(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  if (f2cause__bytecode_tracing_on(cause, cause)) {
    raw__thread__bytecode_trace__jump_funk(f2ptr cause, f2ptr thread);
  }
  
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


int f2__thread__bytecode__funk(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  f2__thread__increment_pc(thread, cause);
  return f2__thread__bytecode_helper__funk__no_increment_pc_reg(thread, cause);
}


// bytecode array [length]

int f2__thread__bytecode__array(f2ptr thread, f2ptr length) {
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

int f2__thread__bytecode__cons(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr new_cons = f2cons__new(cause, nil, nil);
  if (! new_cons) {error(nil, "cons bytecode error: new cons is nil");}
  f2thread__iter__set(thread, cause, new_cons);
  return 0;
}


// bytecode car []

int f2__thread__bytecode__car(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2cons__car(f2thread__iter(thread, cause), cause));
  return 0;
}


// bytecode cdr []

int f2__thread__bytecode__cdr(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2cons__cdr(f2thread__iter(thread, cause), cause));
  return 0;
}


// bytecode car__set []

int f2__thread__bytecode__car__set(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2cons__car__set(f2thread__iter(thread, cause), cause, f2thread__value(thread, cause));
  return 0;
}


// bytecode cdr__set []

int f2__thread__bytecode__cdr__set(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2cons__cdr__set(f2thread__iter(thread, cause), cause, f2thread__value(thread, cause));
  return 0;
}


// bytecode array_elt [array index]

int f2__thread__bytecode__array_elt(f2ptr thread, f2ptr array, f2ptr index) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2__array__elt(cause, array, index));
  return 0;
}


// bytecode set [reg f2ptr]

int f2__thread__bytecode__set__value_reg(f2ptr thread, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__program_counter_reg(f2ptr thread, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if (raw__exceptionp(exp, cause)) {
    f2thread__value__set(thread, cause, exp);
  } else {
    f2thread__program_counter__set(thread, cause, exp);
  }
  return 1;
}

int f2__thread__bytecode__set__iter_reg(f2ptr thread, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__args_reg(f2ptr thread, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__return_reg(f2ptr thread, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, exp);
  return 0;
}

int f2__thread__bytecode__set__env_reg(f2ptr thread, f2ptr exp) {
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

int f2__thread__bytecode__set(f2ptr thread, f2ptr reg, f2ptr exp) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__set(cause, reg))(thread, exp);
}


// bytecode nop []

int f2__thread__bytecode__nop(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  return 0;
}


// bytecode swap [reg reg]

int f2__thread__bytecode__swap__return_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__value( thread, cause));
  f2thread__value__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__iter(  thread, cause));
  f2thread__iter__set(  thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__return(         thread, cause);
  f2thread__return__set(         thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__return_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__env(   thread, cause));
  f2thread__env__set(   thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__return_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                         f2thread__return(thread, cause);
  f2thread__return__set(thread, cause, f2thread__args(  thread, cause));
  f2thread__args__set(  thread, cause, temp);
  return 0;
}


int f2__thread__bytecode__swap__value_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__iter( thread, cause));
  f2thread__iter__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__value_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__value(          thread, cause);
  f2thread__value__set(          thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__value_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__env(  thread, cause));
  f2thread__env__set(  thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__value_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                        f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, f2thread__args( thread, cause));
  f2thread__args__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__iter_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__iter(           thread, cause);
  f2thread__iter__set(           thread, cause, f2thread__program_counter(thread, cause));
  f2thread__program_counter__set(thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__iter_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                       f2thread__iter(thread, cause);
  f2thread__iter__set(thread, cause, f2thread__env( thread, cause));
  f2thread__env__set( thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__iter_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                       f2thread__iter(thread, cause);
  f2thread__iter__set(thread, cause, f2thread__args(thread, cause));
  f2thread__args__set(thread, cause, temp);
  return 0;
}

int f2__thread__bytecode__swap__program_counter_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__program_counter(thread, cause);
  f2thread__program_counter__set(thread, cause, f2thread__env(            thread, cause));
  f2thread__env__set(            thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__program_counter_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr temp =                                  f2thread__program_counter(thread, cause);
  f2thread__program_counter__set(thread, cause, f2thread__args(           thread, cause));
  f2thread__args__set(           thread, cause, temp);
  return 1;
}

int f2__thread__bytecode__swap__env_reg__args_reg(f2ptr thread) {
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

int f2__thread__bytecode__swap(f2ptr thread, f2ptr reg0, f2ptr reg1) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__swap(cause, reg0, reg1))(thread);
}


// bytecode push [reg]

int f2__thread__bytecode__push__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_return(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_env(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_value(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_iter(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__push_args(cause, thread);  
  return 0;
}

int f2__thread__bytecode__push__program_counter_reg(f2ptr thread) {
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

int f2__thread__bytecode__push(f2ptr thread, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__push(cause, reg))(thread);
}

// bytecode pop [reg]

int f2__thread__bytecode__pop__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_return(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_env(thread, cause);
  release__assert(f2thread__env(thread, cause), thread, "env popped to nil.");
  release__assert(raw__environmentp(f2thread__env(thread, cause), cause), thread, "assertion failed: popped to non-environment");
  //f2__print(nil, f2thread__env(thread));
  //fflush(stdout);
  return 0;
}

int f2__thread__bytecode__pop__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_value(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_iter(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_args(thread, cause);
  return 0;
}

int f2__thread__bytecode__pop__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2__thread__stack__pop_program_counter(thread, cause);
  return 1;
}

int f2__thread__bytecode__pop__nil(f2ptr thread) {
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

int f2__thread__bytecode__pop(f2ptr thread, f2ptr reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__pop(cause, reg))(thread);
}


// bytecode copy [reg reg]

int f2__thread__bytecode__copy__return_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__return(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__return_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__return_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__return(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__value_reg__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__value(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__value_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__value_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__value(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__iter_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__iter(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__iter_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__iter_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__iter(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__program_counter_reg__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, nil);
  
  f2thread__iter__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__env_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__env__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__program_counter_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__program_counter(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__env_reg__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__env_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__env(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__env_reg__args_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__args__set(thread, cause, f2thread__env(thread, cause));
  return 0;
}


int f2__thread__bytecode__copy__args_reg__return_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__return__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__value_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__value__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__iter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__iter__set(thread, cause, f2thread__args(thread, cause));
  return 0;
}

int f2__thread__bytecode__copy__args_reg__program_counter_reg(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2thread__program_counter__set(thread, cause, f2thread__args(thread, cause));
  return 1;
}

int f2__thread__bytecode__copy__args_reg__env_reg(f2ptr thread) {
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

int f2__thread__bytecode__copy(f2ptr thread, f2ptr src_reg, f2ptr dest_reg) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return (f2__compile__bytecode__copy(cause, src_reg, dest_reg))(thread);
}


// bytecode lookup_type_var [f2ptr f2ptr]

int f2__thread__bytecode__lookup_type_var(f2ptr thread, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env   = f2thread__env(thread, cause);
  f2thread__value__set(thread, cause, environment__lookup_type_var_value(cause, env, type, var));
  return 0;
}


// bytecode define_type_var [f2ptr f2ptr]

int f2__thread__bytecode__define_type_var(f2ptr thread, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env   = f2thread__env(thread, cause);
  f2ptr value = f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, environment__define_type_var_value(cause, env, type, var, value));
  return 0;
}


// bytecode type_var__set [f2ptr f2ptr]

int f2__thread__bytecode__type_var__set(f2ptr thread, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr env   = f2thread__env(thread, cause);
  f2ptr value = f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, environment__type_var_value__set(cause, env, type, var, value));
  return 0;
}


// bytecode globalize_type_var [f2ptr f2ptr]

int f2__thread__bytecode__globalize_type_var(f2ptr thread, f2ptr type, f2ptr var) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr value = f2thread__value(thread, cause);
  f2thread__value__set(thread, cause, environment__define_type_var_value(cause, global_environment(), type, var, value));
  return 0;
}


// bytecode jump [f2ptr]

int f2__thread__bytecode__jump(f2ptr thread, f2ptr new_program_counter) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if (raw__exceptionp(new_program_counter, cause)) {
    f2thread__value__set(thread, cause, new_program_counter);
  } else {
    f2thread__program_counter__set(thread, cause, new_program_counter);
  }
  return 1;
}


// bytecode else_jump [f2ptr]

int f2__thread__bytecode__else_jump(f2ptr thread, f2ptr new_program_counter) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  if(! f2thread__value(thread, cause)) {
    if (raw__exceptionp(new_program_counter, cause)) {
      f2thread__value__set(thread, cause, new_program_counter);
    } else {
      f2thread__program_counter__set(thread, cause, new_program_counter);
    }
  }
  return 1;
}


// bytecode debug [f2ptr]

int f2__thread__bytecode__debug(f2ptr thread, f2ptr value) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  printf("\ndebug: *** "); f2__write(thread, value); printf(" ***"); fflush(stdout);
  return 0;
}


// bytecode trace [f2ptr]

int f2__thread__bytecode__trace(f2ptr thread, f2ptr value) {
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


// bytecode compile [bool bool]

int f2__thread__bytecode__compile__tracewrap__protect_environment(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr tracewrap           = __funk2.globalenv.true__symbol;
  f2ptr protect_environment = __funk2.globalenv.true__symbol;
  bool  is_funktional       = true;
  f2thread__value__set(thread, cause, raw__compile(cause, (tracewrap != nil), thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

int f2__thread__bytecode__compile__tracewrap__nil(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr tracewrap           = __funk2.globalenv.true__symbol;
  f2ptr protect_environment = nil;
  bool  is_funktional       = true;
  f2thread__value__set(thread, cause, raw__compile(cause, (tracewrap != nil), thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

int f2__thread__bytecode__compile__nil__protect_environment(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr tracewrap           = nil;
  f2ptr protect_environment = __funk2.globalenv.true__symbol;
  bool  is_funktional       = true;
  f2thread__value__set(thread, cause, raw__compile(cause, (tracewrap != nil), thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

int f2__thread__bytecode__compile__nil__nil(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr tracewrap           = nil;
  f2ptr protect_environment = nil;
  bool  is_funktional       = true;
  f2thread__value__set(thread, cause, raw__compile(cause, (tracewrap != nil), thread, f2thread__value(thread, cause), (protect_environment != nil), (protect_environment == nil), NULL, &is_funktional, nil, NULL));
  return 0;
}

bytecode_jump_t f2__compile__bytecode__compile(f2ptr tracewrap, f2ptr protect_environment) {
  if (tracewrap != nil) {
    if (protect_environment != nil) {
      return &f2__thread__bytecode__compile__tracewrap__protect_environment;
    } else {
      return &f2__thread__bytecode__compile__tracewrap__nil;
    }
  } else {
    if (protect_environment != nil) {
      return &f2__thread__bytecode__compile__nil__protect_environment;
    } else {
      return &f2__thread__bytecode__compile__nil__nil;
    }
  }
}

int f2__thread__bytecode__compile(f2ptr thread, f2ptr tracewrap, f2ptr protect_environment) {return (f2__compile__bytecode__compile(tracewrap, protect_environment))(thread);}


// bytecode yield []

int f2__thread__bytecode__yield(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  error(nil, "f2__thread__bytecode__yield error: not yet implemented!");
  return 0;
}


// bytecode newenv []

int f2__thread__bytecode__newenv(f2ptr thread) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  f2__thread__increment_pc(thread, cause);
  
  f2ptr parent_env = f2thread__env(thread, cause);
  f2ptr new_env    = f2environment__new(cause,
					frame__new_empty(cause),
					parent_env,
					f2symbol__new(cause, strlen("bytecode:push-env"), (u8*)"bytecode:push-env"));
  release__assert(new_env, thread, "new_env is nil");
  release__assert(raw__environmentp(new_env, cause), thread, "new_env is not environment");
  f2thread__env__set(thread, cause, new_env);
  return 0;
}


// bytecode machine_code [chunk]

int f2__thread__bytecode__machine_code(f2ptr thread, f2ptr chunk) {
  f2ptr cause = f2thread__cause_reg(thread, nil);
  
  return f2chunk__bytecode_jump(chunk, cause, thread);
}


// initialization of f2_bytecodes.c

void f2__bytecodes__reinitialize_globalvars() {
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  
  __funk2.bytecode.bytecode__jump_funk__symbol          = f2symbol__new(cause, strlen("bytecode:jump-funk"),          (u8*)"bytecode:jump-funk");
  __funk2.bytecode.bytecode__funk__symbol               = f2symbol__new(cause, strlen("bytecode:funk"),               (u8*)"bytecode:funk");
  __funk2.bytecode.bytecode__array__symbol              = f2symbol__new(cause, strlen("bytecode:array"),              (u8*)"bytecode:array");
  __funk2.bytecode.bytecode__cons__symbol               = f2symbol__new(cause, strlen("bytecode:cons"),               (u8*)"bytecode:cons");
  __funk2.bytecode.bytecode__car__symbol                = f2symbol__new(cause, strlen("bytecode:car"),                (u8*)"bytecode:car");
  __funk2.bytecode.bytecode__cdr__symbol                = f2symbol__new(cause, strlen("bytecode:cdr"),                (u8*)"bytecode:cdr");
  __funk2.bytecode.bytecode__car__set__symbol           = f2symbol__new(cause, strlen("bytecode:car-set"),            (u8*)"bytecode:car-set");
  __funk2.bytecode.bytecode__cdr__set__symbol           = f2symbol__new(cause, strlen("bytecode:cdr-set"),            (u8*)"bytecode:cdr-set");
  __funk2.bytecode.bytecode__array_elt__symbol          = f2symbol__new(cause, strlen("bytecode:array_elt"),          (u8*)"bytecode:array_elt");
  __funk2.bytecode.bytecode__set__symbol                = f2symbol__new(cause, strlen("bytecode:set"),                (u8*)"bytecode:set");
  __funk2.bytecode.bytecode__swap__symbol               = f2symbol__new(cause, strlen("bytecode:swap"),               (u8*)"bytecode:swap");
  __funk2.bytecode.bytecode__push__symbol               = f2symbol__new(cause, strlen("bytecode:push"),               (u8*)"bytecode:push");
  __funk2.bytecode.bytecode__pop__symbol                = f2symbol__new(cause, strlen("bytecode:pop"),                (u8*)"bytecode:pop");
  __funk2.bytecode.bytecode__copy__symbol               = f2symbol__new(cause, strlen("bytecode:copy"),               (u8*)"bytecode:copy");
  __funk2.bytecode.bytecode__lookup_type_var__symbol    = f2symbol__new(cause, strlen("bytecode:lookup-type_var"),    (u8*)"bytecode:lookup-type_var");
  __funk2.bytecode.bytecode__define_type_var__symbol    = f2symbol__new(cause, strlen("bytecode:define-type_var"),    (u8*)"bytecode:define-type_var");
  __funk2.bytecode.bytecode__type_var__set__symbol      = f2symbol__new(cause, strlen("bytecode:type_var-set"),       (u8*)"bytecode:type_var-set");
  __funk2.bytecode.bytecode__globalize_type_var__symbol = f2symbol__new(cause, strlen("bytecode:globalize-type_var"), (u8*)"bytecode:globalize-type_var");
  __funk2.bytecode.bytecode__jump__symbol               = f2symbol__new(cause, strlen("bytecode:jump"),               (u8*)"bytecode:jump");
  __funk2.bytecode.bytecode__else_jump__symbol          = f2symbol__new(cause, strlen("bytecode:else-jump"),          (u8*)"bytecode:else-jump");
  __funk2.bytecode.bytecode__nop__symbol                = f2symbol__new(cause, strlen("bytecode:nop"),                (u8*)"bytecode:nop");
  __funk2.bytecode.bytecode__debug__symbol              = f2symbol__new(cause, strlen("bytecode:debug"),              (u8*)"bytecode:debug");
  __funk2.bytecode.bytecode__trace__symbol              = f2symbol__new(cause, strlen("bytecode:trace"),              (u8*)"bytecode:trace");
  __funk2.bytecode.bytecode__compile__symbol            = f2symbol__new(cause, strlen("bytecode:compile"),            (u8*)"bytecode:compile");
  __funk2.bytecode.bytecode__yield__symbol              = f2symbol__new(cause, strlen("bytecode:yield"),              (u8*)"bytecode:yield");
  __funk2.bytecode.bytecode__newenv__symbol             = f2symbol__new(cause, strlen("bytecode:newenv"),             (u8*)"bytecode:newenv");
  __funk2.bytecode.bytecode__machine_code__symbol       = f2symbol__new(cause, strlen("bytecode:machine_code"),       (u8*)"bytecode:machine_code");
  
  __funk2.bytecode.expression_not_funkable__exception__tag = f2symbol__new(cause, strlen("bytecode:expression-not-funkable"), (u8*)"bytecode:expression-not-funkable");
  __funk2.bytecode.expression_not_funkable__exception      = f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, nil);
}

void f2__bytecodes__initialize() {
  f2__bytecodes__reinitialize_globalvars();
  
  f2ptr cause = f2_bytecodes_c__cause__new(initial_cause());
  char *str;
  f2ptr new_symbol;
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__jump_funk__symbol, nil);
  str = "bytecode:jump_funk-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__jump_funk)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__funk__symbol, nil);
  str = "bytecode:funk-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__funk)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__array__symbol, nil);
  str = "bytecode:array-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__array)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__cons__symbol, nil);
  str = "bytecode:cons-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__cons)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__car__symbol, nil);
  str = "bytecode:car-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__car)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__cdr__symbol, nil);
  str = "bytecode:cdr-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__cdr)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__car__set__symbol, nil);
  str = "bytecode:car-set-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__car__set)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__cdr__set__symbol, nil);
  str = "bytecode:cdr-set-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__cdr__set)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__array_elt__symbol, nil);
  str = "bytecode:array_elt-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__array_elt)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__set__symbol, nil);
  str = "bytecode:set-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__set)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__swap__symbol, nil);
  str = "bytecode:swap-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__swap)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__push__symbol, nil);
  str = "bytecode:push-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__push)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__pop__symbol, nil);
  str = "bytecode:pop-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__pop)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__copy__symbol, nil);
  str = "bytecode:copy-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__copy)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__lookup_type_var__symbol, nil);
  str = "bytecode:lookup_type_var-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__lookup_type_var)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__define_type_var__symbol, nil);
  str = "bytecode:define_type_var-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__define_type_var)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__type_var__set__symbol, nil);
  str = "bytecode:type_var-set-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__type_var__set)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__globalize_type_var__symbol, nil);
  str = "bytecode:globalize_type_var-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__globalize_type_var)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__jump__symbol, nil);
  str = "bytecode:jump-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__jump)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__else_jump__symbol, nil);
  str = "bytecode:else_jump-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__else_jump)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__nop__symbol, nil);
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__debug__symbol, nil);
  str = "bytecode:debug-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__debug)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__trace__symbol, nil);
  str = "bytecode:trace-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__trace)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__compile__symbol, nil);
  str = "bytecode:compile-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__compile)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__yield__symbol, nil);
  str = "bytecode:yield-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__yield)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__newenv__symbol, nil);
  str = "bytecode:newenv-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__newenv)));
  
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.bytecode__machine_code__symbol, nil);
  str = "bytecode:machine_code-machine_code_ptr"; new_symbol = f2symbol__new(cause, strlen(str), (u8*)str);
  environment__add_var_value(cause, global_environment(), new_symbol, f2pointer__new(cause, to_ptr(f2__thread__bytecode__machine_code)));
  
  // exceptions
  
  __funk2.bytecode.expression_not_funkable__exception__tag = f2symbol__new(cause, strlen("bytecode:expression-not-funkable"), (u8*)"bytecode:expression-not-funkable");
  __funk2.bytecode.expression_not_funkable__exception      = f2exception__new(cause, __funk2.bytecode.expression_not_funkable__exception__tag, nil);
  environment__add_var_value(cause, global_environment(), __funk2.bytecode.expression_not_funkable__exception__tag, __funk2.bytecode.expression_not_funkable__exception);
}

