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

#include "funk2.h"


void funk2_primobject__environment__init(funk2_primobject__environment_t* this) {
  environment__add_var_value(initial_cause(), global_environment(), this->environment__symbol,         nil);
  environment__add_var_value(initial_cause(), global_environment(), this->current_environment__symbol, nil);
}

void funk2_primobject__environment__reinit(funk2_primobject__environment_t* this) {
  this->environment__symbol         = new__symbol(initial_cause(), "environment");
  this->current_environment__symbol = new__symbol(initial_cause(), "current_environment");
}

void funk2_primobject__environment__defragment__fix_pointers(funk2_primobject__environment_t* this) {
  // -- reinitialize --
  
  defragment__fix_pointer(this->environment__symbol);
  defragment__fix_pointer(this->current_environment__symbol);
  
  
  // -- initialize --
}

void funk2_primobject__environment__destroy(funk2_primobject__environment_t* this) {
}

// environment

def_primobject_3_slot(environment, frame, parent_env, desc);

f2ptr raw__environment__new(f2ptr cause, f2ptr frame, f2ptr parent_env, f2ptr desc) {
  return f2environment__new(cause, frame, parent_env, desc);
}

f2ptr f2__environment__new(f2ptr cause, f2ptr frame, f2ptr parent_env, f2ptr desc) {
  assert_argument_type(       frame,       frame);
  assert_argument_type_or_nil(environment, parent_env);
  return raw__environment__new(cause, frame, parent_env, desc);
}
def_pcfunk3(environment__new, frame, parent_env, desc,
	    "",
	    return f2__environment__new(this_cause, frame, parent_env, desc));


f2ptr f2__environment__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {return f2__frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);}
def_pcfunk4(environment__add_type_var_value, this, type, var, value,
	    "",
	    return f2__environment__add_type_var_value(this_cause, this, type, var, value));

f2ptr f2__environment__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = f2__frame__lookup_type_var_assignment_cons(cause, f2environment__frame(env, cause), type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, value)) {
      return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"),      new__symbol(cause, "type_var_does_not_exist_in_environment"),
				 new__symbol(cause, "this"),          this,
				 new__symbol(cause, "variable_name"), var));
}

f2ptr f2__environment__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr value;
  while (env) {
    value = f2__frame__lookup_type_var_value(cause, f2environment__frame(env, cause), type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, value)) {
      return value;
    }
    env = f2environment__parent_env(env, cause);
  }
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"),      new__symbol(cause, "type_var_does_not_exist_in_environment"),
				 new__symbol(cause, "this"),          this,
				 new__symbol(cause, "variable_name"), var));
}
def_pcfunk3(environment__lookup_type_var_value, this, type, var,
	    "",
	    return f2__environment__lookup_type_var_value(this_cause, this, type, var));

f2ptr f2__environment__safe_lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr result = f2__environment__lookup_type_var_value(cause, this, type, var);
  if (raw__larva__is_type(cause, result)) {
    error(nil, "environment__safe_lookup_type_var_value failed to lookup variable.");
  }
  return result;
}

f2ptr f2__environment__define_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2__frame__add_type_var_value(cause, f2environment__frame(this, cause), type, var, value);
  return nil;
}

f2ptr f2__environment__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  release__assert(raw__environment__is_type(cause, this), nil, "this is not environment.");
  f2ptr env = this;
  f2ptr result;
  while (env) {
    result = f2__frame__type_var_value__set(cause, f2environment__frame(env, cause), type, var, value, __funk2.primobject__frame.type_variable_not_defined__larva);
    if (! raw__larva__is_type(cause, result)) {
      return result;
    }
    env = f2environment__parent_env(env, cause);
  }
  __funk2.primobject__environment.environment__last_23_larva_symbol = var;
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"),      new__symbol(cause, "type_var_does_not_exist_in_environment"),
				 new__symbol(cause, "this"),          this,
				 new__symbol(cause, "variable_name"), var));
}
def_pcfunk4(environment__type_var_value__set, this, type, var, value,
	    "",
	    return f2__environment__type_var_value__set(this_cause, this, type, var, value));


f2ptr raw__environment__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "environment"),
					       new__symbol(cause, "frame"),      f2__environment__frame(     cause, this),
					       new__symbol(cause, "parent_env"), f2__environment__parent_env(cause, this),
					       new__symbol(cause, "desc"),       f2__environment__desc(      cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__environment__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(environment,          this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__environment__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(environment__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__environment__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2environment__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2environment__primobject_type__new(cause);
  {char* slot_name = "add_type_var_value";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_environment.add_type_var_value__funk);}
  {char* slot_name = "type_var_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_environment.lookup_type_var_value__funk);}
  {char* slot_name = "type_var_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_environment.type_var_value__set__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_environment.terminal_print_with_frame__funk);}
  return this;
}

// **

void f2__primobject_environment__preinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  funk2_primobject__environment__reinit(&(__funk2.primobject__environment));
  
  reinitialize_primobject(environment);
}

void f2__primobject_environment__reinitialize_globalvars() {
  f2__primobject_environment__preinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // environment
  
  initialize_primobject_3_slot(environment, frame, parent_env, desc);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_environment.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(environment__new, frame, parent_env, desc, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_environment.new__funk = never_gc(cfunk);}
  {char* symbol_str = "add_type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_environment.add_type_var_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(environment__add_type_var_value, this, type, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_environment.add_type_var_value__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup_type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_environment.lookup_type_var_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(environment__lookup_type_var_value, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_environment.lookup_type_var_value__funk = never_gc(cfunk);}
  {char* symbol_str = "type_var_value-set"; __funk2.globalenv.object_type.primobject.primobject_type_environment.type_var_value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(environment__type_var_value__set, this, type, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_environment.type_var_value__set__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_environment.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(environment__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_environment.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

void f2__primobject_environment__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_primobject__environment__defragment__fix_pointers(&(__funk2.primobject__environment));
  
  
  // -- initialize --
  
  // environment
  
  initialize_primobject_3_slot__defragment__fix_pointers(environment, frame, parent_env, desc);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(environment__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.add_type_var_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(environment__add_type_var_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.add_type_var_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.lookup_type_var_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(environment__lookup_type_var_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.lookup_type_var_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.type_var_value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(environment__type_var_value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.type_var_value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(environment__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_environment.terminal_print_with_frame__funk);
  
}

void f2__primobject_environment__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-environment", "", &f2__primobject_environment__reinitialize_globalvars, &f2__primobject_environment__defragment__fix_pointers);
  
  f2__primobject_environment__preinitialize_globalvars();
  
  global_environment__set(f2environment__new(initial_cause(), f2__frame__new(initial_cause(), nil),
					     nil,
					     new__symbol(initial_cause(), "global_environment")));
  
  funk2_primobject__environment__init(&(__funk2.primobject__environment));
  
  f2__primobject_environment__reinitialize_globalvars();

}

