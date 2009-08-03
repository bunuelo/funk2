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


void funk2_primobject__environment__init(funk2_primobject__environment_t* this) {
  environment__add_var_value(initial_cause(), global_environment(), this->environment__symbol,         nil);
  environment__add_var_value(initial_cause(), global_environment(), this->current_environment__symbol, nil);
}

void funk2_primobject__environment__reinit(funk2_primobject__environment_t* this) {
  this->environment__symbol         = f2symbol__new(initial_cause(), strlen("environment"),         (u8*)"environment");
  this->current_environment__symbol = f2symbol__new(initial_cause(), strlen("current_environment"), (u8*)"current_environment");
}

void funk2_primobject__environment__destroy(funk2_primobject__environment_t* this) {
}

// environment primobject

defprimobject__static_slot(environment__frame,      0);
defprimobject__static_slot(environment__parent_env, 1);
defprimobject__static_slot(environment__desc,       2);

f2ptr f2environment__new(f2ptr cause, f2ptr frame, f2ptr parent_env, f2ptr desc) {
  f2ptr this = f2__primobject__new(cause, __funk2.primobject__environment.environment__symbol, 3, nil);
  f2environment__frame__set(     this, cause, frame);
  f2environment__parent_env__set(this, cause, parent_env);
  f2environment__desc__set(      this, cause, desc);
  return this;
}

boolean_t raw__environment__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && f2primobject__is_environment(this, cause));}
f2ptr f2__environment__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__environment__is_type(cause, this));}

void environment__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);}

f2ptr environment__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = frame__lookup_type_var_assignment_cons(cause, f2environment__frame(env, cause), type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, value)) {
      return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return __funk2.primobject__frame.type_variable_not_defined__larva;
}

f2ptr environment__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = frame__lookup_type_var_value(cause, f2environment__frame(env, cause), type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, value)) {
      return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return __funk2.primobject__frame.type_variable_not_defined__larva;
}

f2ptr environment__safe_lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr result = environment__lookup_type_var_value(cause, this, type, var);
  if (raw__larva__is_type(cause, result)) {
    error(nil, "environment__safe_lookup_type_var_value failed to lookup variable.");
  }
  return result;
}

f2ptr environment__define_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);
  return nil;
}

f2ptr environment__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr result;
  while (env) {
    result = frame__type_var_value__set(cause, f2environment__frame(env, cause), type, var, value, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, result)) {
      return result;
    }
    env = f2environment__parent_env(env, cause);
  }
  printf ("\nset-var not defined: "); f2__write(nil, var); fflush(stdout);
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return __funk2.primobject__frame.type_variable_not_defined__larva;
}

// **

void f2__primobject_environment__reinitialize_globalvars() {
  funk2_primobject__environment__reinit(&(__funk2.primobject__environment));
}

void f2__primobject_environment__initialize() {
  f2__primobject_environment__reinitialize_globalvars();
  
  global_environment__set(f2environment__new(initial_cause(), f2__frame__new(initial_cause()),
					     nil,
					     f2symbol__new(initial_cause(), strlen("global_environment"), (u8*)"global_environment")));
  
  funk2_primobject__environment__init(&(__funk2.primobject__environment));
}

