// 
// Copyright (c) 2007-2008 Bo Morgan.
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

f2ptr __type_variable_not_defined__symbol;

f2ptr __current_environment__symbol;

// environment primobject

defprimobject__static_slot(environment__frame,      0);
defprimobject__static_slot(environment__parent_env, 1);
defprimobject__static_slot(environment__desc,       2);

f2ptr __environment__symbol;

f2ptr f2environment__new(f2ptr cause, f2ptr frame, f2ptr parent_env, f2ptr desc) {
  pause_gc();
  f2ptr this = f2__primobject__new(cause, __environment__symbol, 3, nil);
  f2environment__frame__set(     this, cause, frame);
  f2environment__parent_env__set(this, cause, parent_env);
  f2environment__desc__set(      this, cause, desc);
  resume_gc();
  return this;
}

boolean_t raw__environment__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && f2primobject__is_environment(this, cause));}
f2ptr f2__environment__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__environment__is_type(cause, this));}

void  environment__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value)     {frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);}

f2ptr environment__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  pause_gc();
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = frame__lookup_type_var_assignment_cons(cause, f2environment__frame(env, cause), type, var, __type_variable_not_defined__symbol);
    if (value != __type_variable_not_defined__symbol) {
      resume_gc(); return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  //printf ("\nvariable not defined: "); f2__write(nil, var); fflush(stdout);
  //f2ptr rv = f2type_variable_not_defined__exception__new(cause, var);
  f2ptr rv = f2larva__new(cause, 23);
  resume_gc(); return rv;
}

f2ptr environment__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  pause_gc();
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = frame__lookup_type_var_value(cause, f2environment__frame(env, cause), type, var, __type_variable_not_defined__symbol);
    if (value != __type_variable_not_defined__symbol) {
      resume_gc(); return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  //printf ("\nvariable not defined: "); f2__write(nil, var); fflush(stdout);
  //f2ptr rv = f2type_variable_not_defined__exception__new(cause, var);
  f2ptr rv = f2larva__new(cause, 23);
  resume_gc(); return rv;
}

f2ptr environment__safe_lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr result = environment__lookup_type_var_value(cause, this, type, var);
  if (raw__larva__is_type(cause, result)) {
    error(nil, "environment__safe_lookup_type_var_value failed to lookup variable.");
  }
  return result;
}

f2ptr environment__define_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  pause_gc();
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);
  resume_gc();
  return nil;
}

f2ptr environment__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  pause_gc();
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr result;
  while (env) {
    result = frame__type_var_value__set(cause, f2environment__frame(env, cause), type, var, value, __type_variable_not_defined__symbol);
    if (result != __type_variable_not_defined__symbol) {
      resume_gc(); return result;
    }
    env = f2environment__parent_env(env, cause);
  }
  printf ("\nset-var not defined: "); f2__write(nil, var); fflush(stdout);
  //f2ptr rv = f2type_variable_not_defined__exception__new(cause, var);
  f2ptr rv = f2larva__new(cause, 23);
  resume_gc(); return rv;
}

void print_environment_backtrace(f2ptr env) {
  f2ptr cause    = nil;
  f2ptr env_iter = env;
  while (env_iter) {
    printf("\nenv> desc: "); f2__write(cause, f2environment__desc(env_iter, cause));
    /*
      f2ptr frame = f2env__frame(env_iter);
      f2ptr binding_iter;
      printf("\n   > var bindings: ");
      {
      binding_iter = frame__var_bindings(frame);
      while (binding_iter) {
      f2ptr binding = raw__car(nil, binding_iter);
      f2ptr value = binding__value(binding);
      printf ("\n                 [");
      f2__write(nil, binding__var(binding));
      if (raw__consp(value)) {
      printf(" <>");
      } else {
      printf(" ");
      f2__write(nil, value);
      }
      printf ("]");
      binding_iter = raw__cdr(nil, binding_iter);
      }
      }
      printf("\n   > funkvar bindings: ");
      {
      binding_iter = frame__funkvar_bindings(frame);
      while (binding_iter) {
      f2ptr binding = raw__car(nil, binding_iter);
      f2ptr value = binding__value(binding);
      printf ("\n                 [");
      f2__write(nil, binding__var(binding));
      if (raw__consp(value)) {
      printf(" <>");
      } else {
      printf(" ");
      f2__write(nil, value);
      }
      printf ("]");
      binding_iter = raw__cdr(nil, binding_iter);
      }
      }
    */
    env_iter = f2environment__parent_env(env_iter, cause);
  }
}

void f2__primobject_environment__reinitialize_globalvar__symbols() {
  f2ptr cause = initial_cause(); //f2_primobject_environment_c__cause__new(initial_cause(), nil, nil);
  
  __type_variable_not_defined__symbol = f2symbol__new(initial_cause(), strlen("primobject:environment-type_variable_not_defined"), (u8*)"primobject:environment-type_variable_not_defined");
  
  __environment__symbol         = f2symbol__new(cause, strlen("environment"), (u8*)"environment");                                                                           
  __current_environment__symbol = f2symbol__new(cause, strlen("primobject:-current_environment-"), (u8*)"primobject:-current_environment-");                                                                     
}

void f2__primobject_environment__reinitialize_globalvar__exceptions() {
}

void f2__primobject_environment__reinitialize_globalvars() {
  f2__primobject_environment__reinitialize_globalvar__symbols();
  f2__primobject_environment__reinitialize_globalvar__exceptions();
}

void f2__primobject_environment__initialize() {
  pause_gc();
  f2__primobject_environment__reinitialize_globalvar__symbols();
  
  f2ptr cause = initial_cause();//f2_primobject_environment_c__cause__new(initial_cause(), nil, nil);
  
  global_environment__set(f2environment__new(cause, frame__new_empty_globalsize(cause),
					     nil,
					     f2symbol__new(cause, strlen("env:global_environment"), (u8*)"env:global_environment")));
  
  environment__add_var_value(cause, global_environment(), __type_variable_not_defined__symbol,         nil);
  
  environment__add_var_value(cause, global_environment(), __environment__symbol,         nil);
  environment__add_var_value(cause, global_environment(), __current_environment__symbol, nil);
  
  resume_gc();
  try_gc();
}

