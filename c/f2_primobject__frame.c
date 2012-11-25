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

// typedframe

boolean_t raw__typedframe__is_type(f2ptr cause, f2ptr this) {
  return (raw__frame__is_type(cause, this) && raw__frame__check_has_type_slot(cause, this, __funk2.primobject__frame.variable__symbol, __funk2.globalenv.type__symbol));
}

f2ptr f2__typedframe__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__typedframe__is_type(cause, this));}

f2ptr f2__typedframe__type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, __funk2.globalenv.type__symbol, nil);
}


void funk2_primobject__frame__init(funk2_primobject__frame_t* this) {
  f2ptr cause = initial_cause();
  
  environment__add_var_value(cause, global_environment(), this->frame__symbol,         nil);
  environment__add_var_value(cause, global_environment(), this->variable__symbol,      nil);
  environment__add_var_value(cause, global_environment(), this->funk_variable__symbol, nil);
}

void funk2_primobject__frame__reinit(funk2_primobject__frame_t* this) {
  f2ptr cause = initial_cause(); //f2_primobject_frame_c__cause__new(initial_cause(), nil, global_environment());
  this->frame__symbol         = new__symbol(cause, "frame");
  this->variable__symbol      = new__symbol(cause, "variable");
  this->funk_variable__symbol = new__symbol(cause, "funk_variable");
  
  this->type_variable_not_defined__larva  = never_gc(f2larva__new(cause, 23, nil));
  this->type_variable_not_defined__symbol = new__symbol(cause, "type_variable_not_defined");
}

void funk2_primobject__frame__defragment__fix_pointers(funk2_primobject__frame_t* this) {
  defragment__fix_pointer(this->frame__symbol);
  defragment__fix_pointer(this->variable__symbol);
  defragment__fix_pointer(this->funk_variable__symbol);
  
  defragment__fix_pointer(this->type_variable_not_defined__larva);
  defragment__fix_pointer(this->type_variable_not_defined__symbol);
}

void funk2_primobject__frame__destroy(funk2_primobject__frame_t* this) {
}

// frame

def_primobject_2_slot(frame, new_type_cmutex, type_ptypehash);

f2ptr f2__frame__new(f2ptr cause, f2ptr slot_value_pairs) {
  f2ptr this = f2frame__new(cause, f2cmutex__new(cause), raw__ptypehash__new(cause, 4));
  {
    f2ptr iter = slot_value_pairs;
    while (iter) {
      f2ptr key = f2__first(cause, iter);
      iter = f2__next(cause, iter);
      if (iter) {
	f2ptr value = f2__first(cause, iter);
	f2__frame__add_var_value(cause, this, key, value);
      } else {
	return f2larva__new(cause, 3, nil);
      }
      iter = f2__next(cause, iter);
    }
  }
  return this;
}
def_pcfunk0_and_rest(frame__new, slot_value_pairs,
		     "",
		     return f2__frame__new(this_cause, slot_value_pairs));

f2ptr raw__frame__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr frame__type_ptypehash = f2frame__type_ptypehash(this, cause);
  debug__assert(raw__ptypehash__is_type(cause, frame__type_ptypehash), nil, "frame__type_ptypehash is not ptypehash.");
  f2ptr type__ptypehash = f2__ptypehash__lookup(cause, frame__type_ptypehash, type);
  if (! type__ptypehash) {
    raw__cmutex__lock(cause, f2frame__new_type_cmutex(this, cause));
    type__ptypehash = f2__ptypehash__lookup(cause, frame__type_ptypehash, type);
    if (! type__ptypehash) {
      type__ptypehash = raw__ptypehash__new(cause, 6);
      f2__ptypehash__add(cause, frame__type_ptypehash, type, type__ptypehash);
    }
    f2cmutex__unlock(f2frame__new_type_cmutex(this, cause), cause);
  }
  debug__assert(raw__ptypehash__is_type(cause, type__ptypehash), nil, "type__ptypehash is not ptypehash.");
  f2__ptypehash__add(cause, type__ptypehash, var, value);
  return nil;
}

f2ptr f2__frame__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  assert_argument_type(frame, this);
  return raw__frame__add_type_var_value(cause, this, type, var, value);
}
def_pcfunk4(frame__add_type_var_value, this, type, var, value,
	    "",
	    return f2__frame__add_type_var_value(this_cause, this, type, var, value));


f2ptr raw__frame__remove_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr frame__type_ptypehash = f2frame__type_ptypehash(this, cause);
  debug__assert(raw__ptypehash__is_type(cause, frame__type_ptypehash), nil, "frame__type_ptypehash is not ptypehash.");
  f2ptr type__ptypehash = f2__ptypehash__lookup(cause, frame__type_ptypehash, type);
  if (type__ptypehash == nil) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),      new__symbol(cause, "frame_does_not_contain_type_var"),
				   new__symbol(cause, "this"),          this,
				   new__symbol(cause, "variable_type"), type,
				   new__symbol(cause, "variable_name"), var));
  }
  f2ptr key_was_removed = assert_value(f2__ptypehash__remove(cause, type__ptypehash, var));
  if (key_was_removed == nil) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),      new__symbol(cause, "frame_does_not_contain_type_var"),
				   new__symbol(cause, "this"),          this,
				   new__symbol(cause, "variable_type"), type,
				   new__symbol(cause, "variable_name"), var));
  }
  return nil;
}

f2ptr f2__frame__remove_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(frame, this);
  return raw__frame__remove_type_var(cause, this, type, var);
}
def_pcfunk3(frame__remove_type_var, this, type, var,
	    "",
	    return f2__frame__remove_type_var(this_cause, this, type, var));


f2ptr f2__frame__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, type__ptypehash, var);
    if (keyvalue_pair) {
      return keyvalue_pair;
    }
  }
  return not_defined_value;
}
def_pcfunk4(frame__lookup_type_var_assignment_cons, this, type, var, not_defined_value,
	    "",
	    return f2__frame__lookup_type_var_assignment_cons(this_cause, this, type, var, not_defined_value));

f2ptr raw__frame__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, type__ptypehash, var);
    if (keyvalue_pair) {
      f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
      return retval;
    }
  }
  return not_defined_value;
}

f2ptr f2__frame__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value) {
  assert_argument_type(frame, this);
  return raw__frame__lookup_type_var_value(cause, this, type, var, not_defined_value);
}
def_pcfunk4(frame__lookup_type_var_value, this, type, var, not_defined_value,
	    "",
	    return f2__frame__lookup_type_var_value(this_cause, this, type, var, not_defined_value));

f2ptr raw__frame__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, type__ptypehash, var);
    if (keyvalue_pair) {
      f2cons__cdr__set(keyvalue_pair, cause, value);
      return nil;
    }
  }
  return not_defined_value;
}

f2ptr f2__frame__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value, f2ptr not_defined_value) {
  assert_argument_type(frame, this);
  return raw__frame__type_var_value__set(cause, this, type, var, value, not_defined_value);
}
def_pcfunk5(frame__type_var_value__set, this, type, var, value, not_defined_value,
	    "",
	    return f2__frame__type_var_value__set(this_cause, this, type, var, value, not_defined_value));


boolean_t raw__frame__contains_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr not_defined_value = __funk2.primobject__frame.type_variable_not_defined__symbol;
  f2ptr value             = raw__frame__lookup_type_var_value(cause, this, type, var, not_defined_value);
  return (! raw__eq(cause, value, not_defined_value));
}

f2ptr f2__frame__contains_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(frame, this);
  return f2bool__new(raw__frame__contains_type_var(cause, this, type, var));
}
def_pcfunk3(frame__contains_type_var, this, type, var,
	    "",
	    return f2__frame__contains_type_var(this_cause, this, type, var));


f2ptr f2__frame__contains(f2ptr cause, f2ptr this, f2ptr var) {
  return f2__frame__contains_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var);
}
def_pcfunk2(frame__contains, this, var,
	    "",
	    return f2__frame__contains(this_cause, this, var));


f2ptr raw__frame__type_var__mapc_keys(f2ptr cause, f2ptr this, f2ptr type, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  f2ptr retval = nil;
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    retval = raw__ptypehash__mapc_keys(cause, type__ptypehash, map_funk, aux_data);
  }
  return retval;
}

f2ptr raw__frame__key_types(f2ptr cause, f2ptr this) {
  f2ptr type_ptypehash = f2frame__type_ptypehash(this, cause);
  return f2__ptypehash__keys(cause, type_ptypehash);
}

f2ptr f2__frame__key_types(f2ptr cause, f2ptr this) {
  assert_argument_type(frame, this);
  return raw__frame__key_types(cause, this);
}
def_pcfunk1(frame__key_types, this,
	    "",
	    return f2__frame__key_types(this_cause, this));


f2ptr f2__frame__type_var__keys(f2ptr cause, f2ptr this, f2ptr type) {
  f2ptr retval = nil;
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    retval = f2__ptypehash__keys(cause, type__ptypehash);
  }
  return retval;
}
def_pcfunk2(frame__type_var__keys, this, type,
	    "",
	    return f2__frame__type_var__keys(this_cause, this, type));

f2ptr f2__frame__type_var__values(f2ptr cause, f2ptr this, f2ptr type) {
  f2ptr retval = nil;
  f2ptr type__keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, f2frame__type_ptypehash(this, cause), type);
  if (type__keyvalue_pair) {
    f2ptr type__ptypehash = f2cons__cdr(type__keyvalue_pair, cause);
    retval = f2__ptypehash__values(cause, type__ptypehash);
  }
  return retval;
}
def_pcfunk2(frame__type_var__values, this, type,
	    "",
	    return f2__frame__type_var__values(this_cause, this, type));

f2ptr f2__frame__var_ptypehash(f2ptr cause, f2ptr this) {return f2__ptypehash__lookup(cause, f2frame__type_ptypehash(this, cause), __funk2.primobject__frame.variable__symbol);}

f2ptr raw__frame__add_var_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  return f2__frame__add_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}

f2ptr f2__frame__add_var_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  assert_argument_type(frame, this);
  return raw__frame__add_var_value(cause, this, var, value);
}
def_pcfunk3(frame__add_var_value, this, var, value,
	    "",
	    return f2__frame__add_var_value(this_cause, this, var, value));

f2ptr f2__frame__lookup_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return f2__frame__lookup_type_var_assignment_cons(cause, this, __funk2.primobject__frame.variable__symbol, var, not_defined_value);}

f2ptr f2__frame__lookup_var_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return f2__frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, var, not_defined_value);}
def_pcfunk3(frame__lookup_var_value, this, var, not_defined_value,
	    "",
	    return f2__frame__lookup_var_value(this_cause, this, var, not_defined_value));

f2ptr f2__frame__var_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value) {return f2__frame__type_var_value__set(cause, this, __funk2.primobject__frame.variable__symbol, var, value, not_defined_value);}
def_pcfunk4(frame__var_value__set, this, var, value, not_defined_value,
	    "",
	    return f2__frame__var_value__set(this_cause, this, var, value, not_defined_value));

boolean_t raw__frame__contains_var(f2ptr cause, f2ptr this, f2ptr var) {
  return raw__frame__contains_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var);
}

f2ptr f2__frame__contains_var(f2ptr cause, f2ptr this, f2ptr var) {
  assert_argument_type(frame, this);
  return f2bool__new(raw__frame__contains_var(cause, this, var));
}
def_pcfunk2(frame__contains_var, this, var,
	    "Returns True [t] if this frame contains variable, otherwise False [nil].",
	    return f2__frame__contains_var(this_cause, this, var));


f2ptr f2__frame__funkvar_ptypehash(f2ptr cause, f2ptr this) {return f2__ptypehash__lookup(cause, f2frame__type_ptypehash(this, cause), __funk2.primobject__frame.funk_variable__symbol);}

f2ptr f2__frame__add_funkvar_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {return f2__frame__add_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value);}
def_pcfunk3(frame__add_funkvar_value, this, funkvar, value,
	    "",
	    return f2__frame__add_var_value(this_cause, this, funkvar, value));

f2ptr f2__frame__lookup_funkvar_assignment_cons(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return f2__frame__lookup_type_var_assignment_cons(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, not_defined_value);}

f2ptr f2__frame__lookup_funkvar_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return f2__frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, not_defined_value);}
def_pcfunk3(frame__lookup_funkvar_value, this, funkvar, not_defined_value,
	    "",
	    return f2__frame__lookup_funkvar_value(this_cause, this, funkvar, not_defined_value));

f2ptr f2__frame__funkvar_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value) {return f2__frame__type_var_value__set(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value, not_defined_value);}
def_pcfunk4(frame__funkvar_value__set, this, funkvar, value, not_defined_value,
	    "",
	    return f2__frame__var_value__set(this_cause, this, funkvar, value, not_defined_value));

f2ptr f2__frame__var__keys(f2ptr cause, f2ptr this) {
  return f2__ptypehash__keys(cause, f2__frame__var_ptypehash(cause, this));
}
def_pcfunk1(frame__var__keys, this,
	    "",
	    return f2__frame__var__keys(this_cause, this));

f2ptr f2__frame__funkvar__keys(f2ptr cause, f2ptr this) {
  return f2__ptypehash__keys(cause, f2__frame__funkvar_ptypehash(cause, this));
}
def_pcfunk1(frame__funkvar__keys, this,
	    "",
	    return f2__frame__funkvar__keys(this_cause, this));


void raw__frame__copy(f2ptr cause, f2ptr this, f2ptr source) {
  frame__iteration(cause, source, type_slot_name, slot_name, slot_value, 
		   f2__frame__add_type_var_value(cause, this, type_slot_name, slot_name, slot_value));
}

f2ptr f2__frame__copy(f2ptr cause, f2ptr this, f2ptr source) {
  assert_argument_type(frame, this);
  assert_argument_type(frame, source);
  raw__frame__copy(cause, this, source);
  return nil;
}
def_pcfunk2(frame__copy, this, source,
	    "",
	    return f2__frame__copy(this_cause, this, source));


f2ptr raw__frame__new_copy(f2ptr cause, f2ptr this) {
  f2ptr copy = f2__frame__new(cause, nil);
  raw__frame__copy(cause, copy, this);
  return copy;
}

f2ptr f2__frame__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(frame, this);
  return raw__frame__new_copy(cause, this);
}
def_pcfunk1(frame__new_copy, this, 
	    "",
	    return f2__frame__new_copy(this_cause, this));


f2ptr f2__frame__copy_slots(f2ptr cause, f2ptr this, f2ptr source, f2ptr map_keys) {
  assert_argument_type(frame,    this);
  assert_argument_type(frame,    source);
  assert_argument_type(conslist, map_keys);
  frame__iteration(cause, source, type_slot_name, slot_name, slot_value, 
		   f2ptr map_keys_iter = map_keys;
		   while (map_keys_iter) {
		     f2ptr map_slot_name = f2__cons__car(cause, map_keys_iter);
		     if (raw__eq(cause, map_slot_name, slot_name)) {
		       f2__frame__add_type_var_value(cause, this, type_slot_name, slot_name, slot_value);
		     }
		     map_keys_iter = f2cons__cdr(map_keys_iter, cause);
		   }
		   );
  return nil;
}
def_pcfunk3(frame__copy_slots, this, source, map_keys,
	    "",
	    return f2__frame__copy_slots(this_cause, this, source, map_keys));

boolean_t raw__frame__check_has_type_slot(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr slot_name) {
  f2ptr not_defined_value = __funk2.primobject__frame.type_variable_not_defined__symbol;
  f2ptr result = f2__frame__lookup_type_var_value(cause, this, type_name, slot_name, not_defined_value);
  return (result != not_defined_value);
}

f2ptr f2__frame__check_has_type_slot(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr slot_name) {
  return f2bool__new(raw__frame__check_has_type_slot(cause, this, type_name, slot_name));
}
def_pcfunk3(frame__check_has_type_slot, this, type_name, slot_name,
	    "",
	    return f2__frame__check_has_type_slot(this_cause, this, type_name, slot_name));

void raw__frame__equals_hash_value__loop_free__map_funk(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr hash_value     = raw__array__elt(cause, aux_data, 2);
  if (raw__larva__is_type(cause, hash_value)) {
    return;
  }
  {
    u64   hash_value__i      = f2integer__i(hash_value, cause);
    f2ptr this               = raw__array__elt(cause, aux_data, 0);
    f2ptr node_hash          = raw__array__elt(cause, aux_data, 1);
    f2ptr subexp             = f2__frame__lookup_var_value(cause, this, slot_name, nil);
    if (subexp != nil) {
      //f2__print(cause, subexp);
      f2ptr subexp__hash_value = f2__object__equals_hash_value__loop_free(cause, subexp, node_hash);
      if (raw__larva__is_type(cause, subexp__hash_value)) {
	raw__array__elt__set(cause, aux_data, 2, subexp__hash_value);
	return;
      }
      {
	u64 subexp__hash_value__i = f2integer__i(subexp__hash_value, cause);
	u64 new_hash_value        = hash_value__i * subexp__hash_value__i;
	raw__array__elt__set(cause, aux_data, 2, f2integer__new(cause, new_hash_value));
      }
    }
  }
}

f2ptr raw__frame__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if (raw__ptypehash__contains(cause, node_hash, this)) {
    return f2integer__new(cause, 1);
  }
  {
    f2ptr node_hash__key_count    = f2__ptypehash__key_count(cause, node_hash);
    u64   node_hash__key_count__i = f2integer__i(node_hash__key_count, cause);
    if (node_hash__key_count__i > max_equals_hash_value_recursion_depth) {
      return f2larva__new(cause, 334, nil);
    }
  }
  raw__ptypehash__add(cause, node_hash, this, __funk2.globalenv.true__symbol);
  f2ptr aux_data = raw__array__new(cause, 3);
  raw__array__elt__set(cause, aux_data, 0, this);
  raw__array__elt__set(cause, aux_data, 1, node_hash);
  raw__array__elt__set(cause, aux_data, 2, f2integer__new(cause, 1));
  f2ptr result = raw__frame__type_var__mapc_keys(cause, this, __funk2.primobject__frame.variable__symbol, raw__frame__equals_hash_value__loop_free__map_funk, aux_data);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2ptr hash_value = raw__array__elt(cause, aux_data, 2);
  return hash_value;
}

f2ptr f2__frame__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  assert_argument_type(frame,     this);
  assert_argument_type(ptypehash, node_hash);
  return raw__frame__equals_hash_value__loop_free(cause, this, node_hash);
}
def_pcfunk2(frame__equals_hash_value__loop_free, this, node_hash, 
	    "",
	    return f2__frame__equals_hash_value__loop_free(this_cause, this, node_hash));

f2ptr raw__frame__equals_hash_value(f2ptr cause, f2ptr this) {
  f2ptr node_hash = f2__ptypehash__new(cause);
  return raw__frame__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__frame__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(frame, this);
  return raw__frame__equals_hash_value(cause, this);
}
def_pcfunk1(frame__equals_hash_value, this,
	    "",
	    return f2__frame__equals_hash_value(this_cause, this));

void raw__frame__part_not_contained_by__map_funk(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr this              = raw__array__elt(cause, aux_data, 0);
  f2ptr that              = raw__array__elt(cause, aux_data, 1);
  f2ptr frame             = raw__array__elt(cause, aux_data, 2);
  f2ptr not_defined_value = __funk2.primobject__frame.type_variable_not_defined__symbol;
  f2ptr this__var_value   = f2__frame__lookup_var_value(cause, this, slot_name, not_defined_value);
  f2ptr that__var_value   = f2__frame__lookup_var_value(cause, that, slot_name, not_defined_value);
  if (! raw__eq(cause, this__var_value, that__var_value)) {
    f2__frame__add_var_value(cause, frame, slot_name, this__var_value);
  }
}

f2ptr f2__frame__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr frame    = f2__frame__new(cause, nil);
  f2ptr aux_data = raw__array__new(cause, 3);
  raw__array__elt__set(cause, aux_data, 0, this);
  raw__array__elt__set(cause, aux_data, 1, that);
  raw__array__elt__set(cause, aux_data, 2, frame);
  f2ptr result = raw__frame__type_var__mapc_keys(cause, this, __funk2.primobject__frame.variable__symbol, raw__frame__part_not_contained_by__map_funk, aux_data);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return frame;
}
def_pcfunk2(frame__part_not_contained_by, this, that,
	    "",
	    return f2__frame__part_not_contained_by(this_cause, this, that));

f2ptr raw__frame__add_to_graph_with_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
    f2__graph__add_node(cause, graph, this_node);
    frame__iteration(cause, this, type_slot_name, slot_name, slot_value,
		     f2ptr key_type_node   = f2__graph_node__new(cause, type_slot_name);
		     f2ptr key_node        = f2__graph_node__new(cause, slot_name);
		     f2ptr slot_value_node = f2__ptypehash__lookup(cause, node_ptypehash, slot_value);
		     if (slot_value_node == nil) {
		       slot_value_node = f2__graph_node__new(cause, slot_value);
		       if (raw__frame__is_type(cause, slot_value)) {
			 f2__ptypehash__add(cause, node_ptypehash, slot_value, slot_value_node);
		       }
		     }
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key_type"), this_node,     key_type_node);
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key"),      key_type_node, key_node);
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "value"),    key_node,      slot_value_node);
		     );
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}

f2ptr f2__frame__add_to_graph_with_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  assert_argument_type(frame,     this);
  assert_argument_type(graph,     graph);
  assert_argument_type(ptypehash, node_ptypehash);
  return raw__frame__add_to_graph_with_ptypehash(cause, this, graph, node_ptypehash);
}
def_pcfunk3(frame__add_to_graph_with_ptypehash, this, graph, node_ptypehash,
	    "",
	    return f2__frame__add_to_graph_with_ptypehash(this_cause, this, graph, node_ptypehash));


// this function is dangerous.  make sure that you are sure of the size of the recursive structure you are asking it to iterate over.
// this is function is safely used from the frame_ball core_extension.  it is recommended that you use that interface unless you know what you are doing.
f2ptr raw__frame__add_recursively_to_graph_with_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash) {
  f2ptr this_node = f2__ptypehash__lookup(cause, node_ptypehash, this);
  if (this_node == nil) {
    this_node = f2__graph_node__new(cause, this);
    f2__ptypehash__add(cause, node_ptypehash, this, this_node);
    f2__graph__add_node(cause, graph, this_node);
    frame__iteration(cause, this, type_slot_name, slot_name, slot_value,
		     f2ptr key_type_node   = f2__graph_node__new(cause, type_slot_name);
		     f2ptr key_node        = f2__graph_node__new(cause, slot_name);
		     f2ptr slot_value_node = f2__ptypehash__lookup(cause, node_ptypehash, slot_value);
		     if (slot_value_node == nil) {
		       slot_value_node = f2__graph_node__new(cause, slot_value);
		       if (raw__frame__is_type(cause, slot_value)) {
			 raw__frame__add_recursively_to_graph_with_ptypehash(cause, slot_value, graph, node_ptypehash);
		       }
		     }
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key_type"), this_node,     key_type_node);
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "key"),      key_type_node, key_node);
		     f2__graph__add_new_edge(cause, graph, new__symbol(cause, "value"),    key_node,      slot_value_node);
		     );
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}


f2ptr raw__frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr use_one_line = raw__terminal_print_frame__use_one_line(cause, terminal_print_frame);
  f2ptr max_size     = raw__terminal_print_frame__max_size(cause, terminal_print_frame);
  s64   max_size__i  = f2integer__i(max_size, cause);
  funk2_character_t frame_string[128];
  u64               frame_string__length;
  {
    f2ptr x    = raw__terminal_print_frame__x(cause, terminal_print_frame);
    s64   x__i = f2integer__i(x, cause);
    raw__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, f2integer__new(cause, x__i + 2));
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__frame__foreground);
    frame_string__length = funk2_character_string__snprintf(frame_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__left_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, frame_string__length, frame_string);
  }
  f2ptr object_type       = f2__object__type(cause, this);
  f2ptr object_slot_order = nil;
  if (raw__eq(cause, object_type, __frame__symbol)) {
    f2ptr print_object_type = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "print_object_type"), nil);
    if (print_object_type != nil) {
      object_type = print_object_type;
    }
    f2ptr print_object_slot_order = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "print_object_slot_order"), nil);
    if (print_object_slot_order != nil) {
      object_slot_order = print_object_slot_order;
    }
  }
  {
    f2ptr result;
    if (raw__symbol__is_type(cause, object_type)) {
      result = raw__type_symbol__terminal_print_with_frame(cause, object_type, terminal_print_frame);
    } else {
      result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, object_type, terminal_print_frame);
    }
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
    if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
      return nil;
    }
  }
  boolean_t types_exist_besides_variables = boolean__false;
  s64 slot_count                          = 0;
  s64 type_slot_name__max_length          = 0;
  s64 slot_name__max_length               = 0;
  //f2__print(cause, terminal_print_frame);
  frame__slot__iteration(cause, this, type_slot_name, slot_name,
			 boolean_t slot_should_be_printed = boolean__true;
			 if (raw__eq(cause, type_slot_name, __funk2.primobject__frame.variable__symbol)) {
			   if (raw__eq(cause, slot_name, __funk2.globalenv.type__symbol) ||
			       raw__eq(cause, slot_name, new__symbol(cause, "print_object_type")) ||
			       raw__eq(cause, slot_name, new__symbol(cause, "print_object_slot_order"))) {
			     slot_should_be_printed = boolean__false;
			   }
			 } else {
			   types_exist_besides_variables = boolean__true;
			 }
			 if (slot_should_be_printed) {
			   {
			     f2ptr x_offset = raw__terminal_print_frame__expression_x_offset__thread_unsafe(cause, terminal_print_frame, type_slot_name);
			     //f2__print(cause, x_offset);
			     if (raw__larva__is_type(cause, x_offset)) {
			       return x_offset;
			     }
			     s64 x_offset__i = f2integer__i(x_offset, cause);
			     //printf("\nx_offset__i=" s64__fstr, x_offset__i);
			     if (x_offset__i > type_slot_name__max_length) {
			       type_slot_name__max_length = x_offset__i;
			     }
			   }
			   {
			     f2ptr x_offset = raw__terminal_print_frame__expression_x_offset__thread_unsafe(cause, terminal_print_frame, slot_name);
			     //f2__print(cause, x_offset);
			     if (raw__larva__is_type(cause, x_offset)) {
			       return x_offset;
			     }
			     s64 x_offset__i = f2integer__i(x_offset, cause);
			     //printf("\nx_offset__i=" s64__fstr, x_offset__i);
			     if (x_offset__i > slot_name__max_length) {
			       slot_name__max_length = x_offset__i;
			     }
			   }
			   slot_count ++;
			 }
			 );
  if (slot_count > 0) {
    if (use_one_line == nil) {
      frame_string__length = funk2_character_string__snprintf(frame_string, 128, "\n");
      raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, frame_string__length, frame_string);
    } else {
      frame_string__length = funk2_character_string__snprintf(frame_string, 128, " ");
      raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, frame_string__length, frame_string);
    }
  }
  {
    f2ptr size    =  raw__terminal_print_frame__size(cause, terminal_print_frame);
    s64   size__i =  f2integer__i(size, cause);
    size__i       ++;
    size          =  f2integer__new(cause, size__i);
    raw__terminal_print_frame__size__set(cause, terminal_print_frame, size);
    if (size__i > max_size__i) {
      f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, new__symbol(cause, "..."), terminal_print_frame);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
      raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
    } else {
      s64                slot_index                     = 0;
      funk2_character_t* type_slot_name_string          = (funk2_character_t*)from_ptr(f2__malloc((type_slot_name__max_length + 1) * sizeof(funk2_character_t)));
      s64                type_slot_name_string__length;
      funk2_character_t* slot_name_string               = (funk2_character_t*)from_ptr(f2__malloc((slot_name__max_length      + 1) * sizeof(funk2_character_t)));
      s64                slot_name_string__length       = 0;
      boolean_t          failed_size_constraint         = boolean__false;
      //f2__print(cause, terminal_print_frame);
      {
	f2ptr object_type_slot_pairs = nil;
	{
	  {
	    f2ptr iter = object_slot_order;
	    while (iter != nil) {
	      f2ptr object_slot = f2__cons__car(cause, iter);
	      object_type_slot_pairs = raw__cons__new(cause, raw__cons__new(cause, __funk2.primobject__frame.variable__symbol, object_slot), object_type_slot_pairs);
	      iter = f2__cons__cdr(cause, iter);
	    }
	  }
	  frame__slot__iteration(cause, this, type_slot_name, slot_name,
				 boolean_t slot_should_be_printed = boolean__true;
				 if (raw__eq(cause, type_slot_name, __funk2.primobject__frame.variable__symbol)) {
				   if (raw__eq(cause, slot_name, __funk2.globalenv.type__symbol) ||
				       raw__eq(cause, slot_name, new__symbol(cause, "print_object_type")) ||
				       raw__eq(cause, slot_name, new__symbol(cause, "print_object_slot_order"))) {
				     slot_should_be_printed = boolean__false;
				   }
				 }
				 if (slot_should_be_printed) {
				   boolean_t found_slot_in_order = boolean__false;
				   {
				     f2ptr iter = object_type_slot_pairs;
				     while (iter != nil) {
				       f2ptr object_type_slot_pair = f2__cons__car(cause, iter);
				       f2ptr order_slot_type = f2__cons__car(cause, object_type_slot_pair);
				       f2ptr order_slot      = f2__cons__cdr(cause, object_type_slot_pair);
				       if (raw__eq(cause, type_slot_name, order_slot_type) &&
					   raw__eq(cause, slot_name, order_slot)) {
					 found_slot_in_order = boolean__true;
					 iter = nil;
				       } else {
					 iter = f2__cons__cdr(cause, iter);
				       }
				     }
				   }
				   if (! found_slot_in_order) {
				     object_type_slot_pairs = raw__cons__new(cause, raw__cons__new(cause, type_slot_name, slot_name), object_type_slot_pairs);
				   }
				 }
				 );
	  object_type_slot_pairs = f2__reverse(cause, object_type_slot_pairs);
	}
	f2ptr object_type_slot_pairs_iter = object_type_slot_pairs;
	while (object_type_slot_pairs_iter != nil) {
	  f2ptr object_type_slot_pair = f2__cons__car(cause, object_type_slot_pairs_iter);
	  f2ptr type_slot_name = f2__cons__car(cause, object_type_slot_pair);
	  f2ptr slot_name      = f2__cons__cdr(cause, object_type_slot_pair);
	  f2ptr slot_value     = raw__frame__lookup_type_var_value(cause, this, type_slot_name, slot_name, nil);
	  {
	    boolean_t already_failed_size_constraint = failed_size_constraint;
	    {
	      f2ptr size    = raw__terminal_print_frame__size(cause, terminal_print_frame);
	      s64   size__i = f2integer__i(size, cause);
	      if (size__i >= max_size__i) {
		failed_size_constraint = boolean__true;
	      }
	    }
	    if (failed_size_constraint) {
	      if (! already_failed_size_constraint) {
		raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
		f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, new__symbol(cause, "..."), terminal_print_frame);
		if (raw__larva__is_type(cause, result)) {
		  return result;
		}
	      }
	    } else {
	      f2ptr size               = raw__terminal_print_frame__size(cause, terminal_print_frame);
	      s64   size__i            = f2integer__i(size, cause);
	      s64   frame__length_left = slot_count - slot_index;
	      {
		s64   subexp_size__i  = 0;
		f2ptr subexp_size     = f2integer__new(cause, subexp_size__i);
		f2ptr indent_distance = raw__terminal_print_frame__indent_distance(cause, terminal_print_frame);
		{
		  u64   subexp_max_size__i;
		  if (frame__length_left > 0) {
		    subexp_max_size__i = (max_size__i - size__i + (frame__length_left - 1)) / frame__length_left;
		  } else {
		    subexp_max_size__i = 0;
		  }
		  f2ptr subexp_max_size    = f2integer__new(cause, subexp_max_size__i);
		  {		       
		    raw__terminal_print_frame__size__set(    cause, terminal_print_frame, subexp_size);
		    raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, subexp_max_size);
		    
		    if (types_exist_besides_variables) {
		      f2ptr before_type_slot_name_x    = raw__terminal_print_frame__x(cause, terminal_print_frame);
		      s64   before_type_slot_name_x__i = f2integer__i(before_type_slot_name_x, cause);
		      if (raw__symbol__is_type(cause, type_slot_name)) {
			f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, type_slot_name, terminal_print_frame);
			if (raw__larva__is_type(cause, result)) {
			  return result;
			}
		      } else {
			f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, type_slot_name, terminal_print_frame);
			if (raw__larva__is_type(cause, result)) {
			  return result;
			}
		      }
		      if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
			raw__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i + subexp_size__i));
			raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
			return nil;
		      }
		      if (use_one_line == nil) {
			f2ptr new_x    = raw__terminal_print_frame__x(cause, terminal_print_frame);
			//f2__print(cause, new_x);
			s64   new_x__i = f2integer__i(new_x, cause);
			{
			  u64 index;
			  //printf("\ntype_slot_name__max_length=" s64__fstr, type_slot_name__max_length);
			  //printf("\nnew_x__i=" s64__fstr, new_x__i);
			  //printf("\nbefore_type_slot_name_x__i=" s64__fstr, before_type_slot_name_x__i);
			  for (index = 0; (index < (type_slot_name__max_length - (new_x__i - before_type_slot_name_x__i))) && (index < type_slot_name__max_length); index ++) {
			    type_slot_name_string[index] = (funk2_character_t)' ';
			  }
			  type_slot_name_string[index]  = 0;
			  type_slot_name_string__length = index;
			}
			raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, type_slot_name_string__length, type_slot_name_string);
		      }
		      {
			u64               temp_string__length = 1;
			funk2_character_t temp_string[1]; temp_string[0] = (funk2_character_t)' ';
			raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, temp_string__length, temp_string);
		      }
		    }
		  }
		  {
		    f2ptr size    = raw__terminal_print_frame__size(cause, terminal_print_frame);
		    s64   size__i = f2integer__i(size, cause);
		    if (size__i >= max_size__i) {
		      failed_size_constraint = boolean__true;
		    }
		  }
		  if (failed_size_constraint) {
		    raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
		    f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, new__symbol(cause, "..."), terminal_print_frame);
		    if (raw__larva__is_type(cause, result)) {
		      return result;
		    }
		  } else {
		    {
		      f2ptr before_slot_name_x    = raw__terminal_print_frame__x(cause, terminal_print_frame);
		      s64   before_slot_name_x__i = f2integer__i(before_slot_name_x, cause);
		      if (raw__symbol__is_type(cause, slot_name)) {
			f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, slot_name, terminal_print_frame);
			if (raw__larva__is_type(cause, result)) {
			  return result;
			}
		      } else {
			f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, slot_name, terminal_print_frame);
			if (raw__larva__is_type(cause, result)) {
			  return result;
			}
		      }
		      if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
			raw__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i + subexp_size__i));
			raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
			return nil;
		      }
		      if (use_one_line == nil) {
			f2ptr new_x    = raw__terminal_print_frame__x(cause, terminal_print_frame);
			//f2__print(cause, new_x);
			s64   new_x__i = f2integer__i(new_x, cause);
			{
			  u64 index;
			  //printf("\nslot_name__max_length=" s64__fstr, slot_name__max_length);
			  //printf("\nnew_x__i=" s64__fstr, new_x__i);
			  //printf("\nbefore_slot_name_x__i=" s64__fstr, before_slot_name_x__i);
			  for (index = 0; (index < (slot_name__max_length - (new_x__i - before_slot_name_x__i))) && (index < slot_name__max_length); index ++) {
			    slot_name_string[index] = (funk2_character_t)' ';
			  }
			  slot_name_string[index]  = 0;
			  slot_name_string__length = index;
			}
			raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, slot_name_string__length, slot_name_string);
		      }
		    }
		    {
		      slot_name_string__length = 1;
		      slot_name_string[0] = (funk2_character_t)' ';
		      raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, slot_name_string__length, slot_name_string);
		    }
		    {
		      f2ptr size    = raw__terminal_print_frame__size(cause, terminal_print_frame);
		      s64   size__i = f2integer__i(size, cause);
		      if (size__i >= max_size__i) {
			failed_size_constraint = boolean__true;
		      }
		    }
		    if (failed_size_constraint) {
		      raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
		      f2ptr result = raw__key_symbol__terminal_print_with_frame(cause, new__symbol(cause, "..."), terminal_print_frame);
		      if (raw__larva__is_type(cause, result)) {
			return result;
		      }
		    } else {
		      f2ptr can_print_on_one_line = raw__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, terminal_print_frame, slot_value);
		      if (raw__larva__is_type(cause, can_print_on_one_line)) {
			return can_print_on_one_line;
		      }
		      if (can_print_on_one_line != nil) {
			raw__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
		      }
		      {
			f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, slot_value, terminal_print_frame);
			if (raw__larva__is_type(cause, result)) {
			  return result;
			}
		      }
		      if (can_print_on_one_line != nil) {
			raw__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, use_one_line);
		      }
		    }
		    if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
		      raw__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i + subexp_size__i));
		      raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
		      return nil;
		    }
		  }
		}
		raw__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
		if (slot_index < slot_count - 1) {
		  if (use_one_line == nil) {
		    u64               temp_string__length = 1;
		    funk2_character_t temp_string[1]; temp_string[0] = (funk2_character_t)'\n';
		    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, temp_string__length, temp_string);
		  } else {
		    u64               temp_string__length = 1;
		    funk2_character_t temp_string[1]; temp_string[0] = (funk2_character_t)' ';
		    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, temp_string__length, temp_string);
		  }
		}
		subexp_size    = raw__terminal_print_frame__size(cause, terminal_print_frame);
		subexp_size__i = f2integer__i(subexp_size, cause);
		
		size__i += subexp_size__i;
		size     = f2integer__new(cause, size__i);
	      }
	      raw__terminal_print_frame__size__set(    cause, terminal_print_frame, size);
	      raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
	      slot_index ++;
	    }
	  }
	  object_type_slot_pairs_iter = f2__cons__cdr(cause, object_type_slot_pairs_iter);
	}
      }
    }
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__frame__foreground);
    frame_string__length = funk2_character_string__snprintf(frame_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__right_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, frame_string__length, frame_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__frame__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(frame,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__frame__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(frame__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__frame__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2frame__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2frame__primobject_type__new(cause);
  {char* slot_name = "add_type_var_value";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.add_type_var_value__funk);}
  {char* slot_name = "remove_type_var";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.remove_type_var__funk);}
  {char* slot_name = "type_var_assignment_cons";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_assignment_cons__funk);}
  {char* slot_name = "type_var_value";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_value__funk);}
  {char* slot_name = "type_var_value";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var_value__set__funk);}
  {char* slot_name = "contains_type_var";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.contains_type_var__funk);}
  {char* slot_name = "contains";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.contains__funk);}
  {char* slot_name = "type_var-keys";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__keys__funk);}
  {char* slot_name = "key_types";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.key_types__funk);}
  {char* slot_name = "type_var-values";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__values__funk);}
  {char* slot_name = "copy";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.copy__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.new_copy__funk);}
  {char* slot_name = "copy_slots";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.copy_slots__funk);}
  {char* slot_name = "check_has_type_slot";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.check_has_type_slot__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__funk);}
  {char* slot_name = "part_not_contained_by";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.part_not_contained_by__funk);}
  {char* slot_name = "add_to_graph_with_ptypehash"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.add_to_graph_with_ptypehash__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_frame.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__primobject_frame__preinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  funk2_primobject__frame__reinit(&(__funk2.primobject__frame));
  
  reinitialize_primobject(frame);
}

void f2__primobject_frame__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  f2__primcfunk__init(frame__add_var_value);
  f2__primcfunk__init(frame__lookup_var_value);
  f2__primcfunk__init(frame__var_value__set);
  f2__primcfunk__init__2(frame__contains_var, this, var);
  f2__primcfunk__init(frame__add_funkvar_value);
  f2__primcfunk__init(frame__lookup_funkvar_value);
  f2__primcfunk__init(frame__funkvar_value__set);
  f2__primcfunk__init(frame__var__keys);
  f2__primcfunk__init(frame__funkvar__keys);
  
  funk2_primobject__frame__init(&(__funk2.primobject__frame));
  
  // frame
  
  initialize_primobject_2_slot(frame, new_type_cmutex, type_ptypehash);
  
  {char* symbol_str = "add_type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_frame.add_type_var_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(frame__add_type_var_value, this, type, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.add_type_var_value__funk = never_gc(cfunk);}
  {char* symbol_str = "remove_type_var"; __funk2.globalenv.object_type.primobject.primobject_type_frame.remove_type_var__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(frame__remove_type_var, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.remove_type_var__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup_type_var_assignment_cons"; __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_assignment_cons__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(frame__lookup_type_var_assignment_cons, this, type, var, not_defined_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_assignment_cons__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup_type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(frame__lookup_type_var_value, this, type, var, not_defined_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_value__funk = never_gc(cfunk);}
  {char* symbol_str = "contains_type_var"; __funk2.globalenv.object_type.primobject.primobject_type_frame.contains_type_var__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(frame__contains_type_var, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.contains_type_var__funk = never_gc(cfunk);}
  {char* symbol_str = "contains"; __funk2.globalenv.object_type.primobject.primobject_type_frame.contains__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__contains, this, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.contains__funk = never_gc(cfunk);}
  {char* symbol_str = "type_var_value-set"; __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var_value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(frame__type_var_value__set, this, type, var, value, not_defined_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var_value__set__funk = never_gc(cfunk);}
  {char* symbol_str = "type_var-keys"; __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__keys__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__type_var__keys, this, type, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__keys__funk = never_gc(cfunk);}
  {char* symbol_str = "key_types"; __funk2.globalenv.object_type.primobject.primobject_type_frame.key_types__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(frame__key_types, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.key_types__funk = never_gc(cfunk);}
  {char* symbol_str = "type_var-values"; __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__values__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__type_var__values, this, type, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__values__funk = never_gc(cfunk);}
  {char* symbol_str = "copy"; __funk2.globalenv.object_type.primobject.primobject_type_frame.copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__copy, this, source, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.copy__funk = never_gc(cfunk);}
  {char* symbol_str = "new_copy"; __funk2.globalenv.object_type.primobject.primobject_type_frame.new_copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(frame__new_copy, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.new_copy__funk = never_gc(cfunk);}
  {char* symbol_str = "copy_slots"; __funk2.globalenv.object_type.primobject.primobject_type_frame.copy_slots__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(frame__copy_slots, this, source, map_keys, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.copy_slots__funk = never_gc(cfunk);}
  {char* symbol_str = "check_has_type_slot"; __funk2.globalenv.object_type.primobject.primobject_type_frame.check_has_type_slot__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(frame__check_has_type_slot, this, type_name, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.check_has_type_slot__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__loop_free__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(frame__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "part_not_contained_by"; __funk2.globalenv.object_type.primobject.primobject_type_frame.part_not_contained_by__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__part_not_contained_by, this, that, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.part_not_contained_by__funk = never_gc(cfunk);}
  {char* symbol_str = "add_to_graph_with_ptypehash"; __funk2.globalenv.object_type.primobject.primobject_type_frame.add_to_graph_with_ptypehash__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(frame__add_to_graph_with_ptypehash, this, graph, node_ptypehash, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.add_to_graph_with_ptypehash__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_frame.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(frame__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_frame.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

void f2__primobject_frame__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_primobject__frame__defragment__fix_pointers(&(__funk2.primobject__frame));
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(frame__add_var_value);
  f2__primcfunk__init__defragment__fix_pointers(frame__lookup_var_value);
  f2__primcfunk__init__defragment__fix_pointers(frame__var_value__set);
  f2__primcfunk__init__defragment__fix_pointers(frame__contains_var);
  f2__primcfunk__init__defragment__fix_pointers(frame__add_funkvar_value);
  f2__primcfunk__init__defragment__fix_pointers(frame__lookup_funkvar_value);
  f2__primcfunk__init__defragment__fix_pointers(frame__funkvar_value__set);
  f2__primcfunk__init__defragment__fix_pointers(frame__var__keys);
  f2__primcfunk__init__defragment__fix_pointers(frame__funkvar__keys);
  
  // frame
  
  initialize_primobject_2_slot__defragment__fix_pointers(frame, new_type_cmutex, type_ptypehash);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.add_type_var_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__add_type_var_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.add_type_var_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.remove_type_var__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__remove_type_var);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.remove_type_var__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_assignment_cons__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__lookup_type_var_assignment_cons);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_assignment_cons__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__lookup_type_var_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.lookup_type_var_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.contains_type_var__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__contains_type_var);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.contains_type_var__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var_value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__type_var_value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var_value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__keys__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__type_var__keys);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__keys__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.key_types__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__key_types);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.key_types__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__values__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__type_var__values);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.type_var__values__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.copy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.new_copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__new_copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.new_copy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.copy_slots__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__copy_slots);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.copy_slots__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.check_has_type_slot__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__check_has_type_slot);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.check_has_type_slot__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.part_not_contained_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__part_not_contained_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.part_not_contained_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.add_to_graph_with_ptypehash__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__add_to_graph_with_ptypehash);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.add_to_graph_with_ptypehash__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(frame__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_frame.terminal_print_with_frame__funk);
  
}

void f2__primobject_frame__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-frame", "", &f2__primobject_frame__reinitialize_globalvars, &f2__primobject_frame__defragment__fix_pointers);
  
  f2__primobject_frame__reinitialize_globalvars();
}

