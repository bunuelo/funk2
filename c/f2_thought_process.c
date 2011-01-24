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

#include "funk2.h"

// thought process

defprimobject__static_slot(thought_process__read_write_execute_slot_hash, 0);

//f2ptr __thought_process__symbol = -1;

f2ptr f2thought_process__new__trace_depth(f2ptr cause, f2ptr read_write_execute_slot_hash, int trace_depth) {
  release__assert(__funk2.thought_process.thought_process__symbol != -1, nil, "f2thought_process__new error: used before thought process initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __funk2.thought_process.thought_process__symbol, 1, nil, trace_depth);
  f2thought_process__read_write_execute_slot_hash__set__trace_depth(this, cause, read_write_execute_slot_hash, trace_depth);
  return this;
}

f2ptr f2thought_process__new(f2ptr cause, f2ptr read_write_execute_slot_hash) {
  return f2thought_process__new__trace_depth(cause, read_write_execute_slot_hash, 1);
}

boolean_t raw__thought_process__is_type(f2ptr cause, f2ptr x) {return (raw__primobject__is_type(cause, x) && f2primobject__is_thought_process(x, cause));}
f2ptr f2__thought_process__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__thought_process__is_type(cause, x));}

f2ptr f2thought_process__read_parent_types(f2ptr cause, f2ptr this) {
  f2ptr read_write_execute_slot_hash = f2thought_process__read_write_execute_slot_hash(this, cause);
  f2ptr read_write_execute           = f2__ptypehash__lookup(cause, read_write_execute_slot_hash, f2symbol__new(cause, strlen("parent_types"), (u8*)"parent_types"));
  f2ptr read_funk                    = raw__array__elt(cause, read_write_execute, 0);
  return read_funk;
}

// return most specific abstract type symbols for any ptype, primobject, or thought_process.

f2ptr f2__determine_real_thought_process_types(f2ptr cause, f2ptr exp) {
  if (exp) {
    if (raw__primobject__is_type(cause, exp)) {
      return f2cons__new(cause, f2primobject__object_type(exp, cause), nil);
    }
    ptype_t ptype = f2ptype__raw(exp, cause);
    switch(ptype) {
    case ptype_free_memory:     return f2cons__new(cause, __funk2.thought_process.ptype_free_memory__symbol,     nil);
    case ptype_newly_allocated: return f2cons__new(cause, __funk2.thought_process.ptype_newly_allocated__symbol, nil);
    case ptype_integer:         return f2cons__new(cause, __funk2.thought_process.ptype_integer__symbol,         nil);
    case ptype_double:          return f2cons__new(cause, __funk2.thought_process.ptype_double__symbol,          nil);
    case ptype_float:           return f2cons__new(cause, __funk2.thought_process.ptype_float__symbol,           nil);
    case ptype_pointer:         return f2cons__new(cause, __funk2.thought_process.ptype_pointer__symbol,         nil);
    case ptype_gfunkptr:        return f2cons__new(cause, __funk2.thought_process.ptype_gfunkptr__symbol,        nil);
    case ptype_mutex:           return f2cons__new(cause, __funk2.thought_process.ptype_mutex__symbol,           nil);
    case ptype_char:            return f2cons__new(cause, __funk2.thought_process.ptype_char__symbol,            nil);
    case ptype_string:          return f2cons__new(cause, __funk2.thought_process.ptype_string__symbol,          nil);
    case ptype_symbol:          return f2cons__new(cause, __funk2.thought_process.ptype_symbol__symbol,          nil);
    case ptype_chunk:           return f2cons__new(cause, __funk2.thought_process.ptype_chunk__symbol,           nil);
    case ptype_simple_array:    return f2cons__new(cause, __funk2.thought_process.ptype_simple_array__symbol,    nil);
    case ptype_traced_array:    return f2cons__new(cause, __funk2.thought_process.ptype_traced_array__symbol,    nil);
    case ptype_larva:           return f2cons__new(cause, __funk2.thought_process.ptype_larva__symbol,           nil);
    }
  }
  return nil;
}
def_pcfunk1(determine_real_thought_process_types, exp, return f2__determine_real_thought_process_types(this_cause, exp));

f2ptr f2thought_process__new_from_exp(f2ptr cause, f2ptr exp, f2ptr bin_num_power) {
  release__assert(__funk2.thought_process.real_value_slot__symbol != -1, nil, "f2thought_process__new_from_exp error: used before thought process initialized.");
  release__assert(raw__integer__is_type(cause, bin_num_power),              nil, "f2thought_process__new_from_exp error: bin_num_power should be integer.");
  f2ptr read_write_execute_slot_hash = f2__ptypehash__new(cause);
  f2ptr read_funk                    = nil;
  f2ptr write_funk                   = nil;
  f2ptr execute_funk                 = nil;
  f2ptr read_write_execute = raw__array__new(cause, 3); raw__array__elt__set(cause, read_write_execute, 0, read_funk); raw__array__elt__set(cause, read_write_execute, 0, write_funk); raw__array__elt__set(cause, read_write_execute, 0, execute_funk);
  f2__ptypehash__add(cause, read_write_execute_slot_hash, __funk2.thought_process.real_value_slot__symbol, exp);
  return f2thought_process__new(cause, read_write_execute_slot_hash);
}

f2ptr f2__thought_process__real_value(f2ptr cause, f2ptr this) {
  release__assert(raw__thought_process__is_type(cause, this), cause, "f2thought_process__real_value assertion failed: this must be an thought_process.");
  f2ptr read_write_execute_slot_hash = f2thought_process__read_write_execute_slot_hash(this, cause);
  return f2__ptypehash__lookup(cause, read_write_execute_slot_hash, __funk2.thought_process.real_value_slot__symbol);
}

// thought_process-read_write_execute

f2ptr f2__thought_process__read_write_execute__lookup(f2ptr cause, f2ptr this, f2ptr slot) {
  if (! raw__thought_process__is_type(cause, this)) {return f2larva__new(cause, larva_type__invalid_type, nil);}
  f2ptr this__read_write_execute = nil;
  if (raw__thought_process__is_type(cause, this)) {
    f2ptr thought_process__read_write_execute_hash = f2thought_process__read_write_execute_slot_hash(this, cause);
    this__read_write_execute = f2__ptypehash__lookup(cause, thought_process__read_write_execute_hash, slot);
  } else {
    f2ptr parent_types     = f2__determine_real_thought_process_types(cause, this);
    f2ptr parent_type_iter = parent_types;
    while (parent_type_iter) {
      f2ptr parent_type = f2cons__car(parent_type_iter, cause);
      f2ptr thought_process__read_write_execute_slot_hash = f2thought_process__read_write_execute_slot_hash(cause, parent_type);
      this__read_write_execute = f2__ptypehash__lookup(cause, thought_process__read_write_execute_slot_hash, slot);
      if (! raw__exception__is_type(cause, this__read_write_execute)) {
	parent_type_iter = nil;
      } else {
	parent_type_iter = f2cons__cdr(parent_type_iter, cause);
      }
    }
  }
  return this__read_write_execute;
}

void f2__thought_process__read_write_execute__put(f2ptr cause, f2ptr this, f2ptr slot, f2ptr read_write_execute) {
  f2__ptypehash__add(cause, f2thought_process__read_write_execute_slot_hash(this, cause), slot, read_write_execute);
}

// read_write_execute

f2ptr f2__read_write_execute__new(f2ptr cause, f2ptr read_funk, f2ptr write_funk, f2ptr execute_funk) {
  f2ptr this = raw__array__new(cause, 3);
  raw__array__elt__set(cause, this, 0, read_funk);
  raw__array__elt__set(cause, this, 1, write_funk);
  raw__array__elt__set(cause, this, 2, execute_funk);
  return this;
}

// read_funk

f2ptr f2__thought_process__read_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (! lookup_read_write_execute) {
    return nil;
  }
  f2ptr read_slot = raw__array__elt(cause, lookup_read_write_execute, 0);
  return read_slot;
}
def_pcfunk2(thought_process__read_funk, this, slot, return f2__thought_process__read_funk(this_cause, this, slot));

f2ptr f2__thought_process__read_funk__put(f2ptr cause, f2ptr this, f2ptr slot, f2ptr read_funk) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (lookup_read_write_execute) {
    raw__array__elt__set(cause, lookup_read_write_execute, 0, read_funk);
  } else {
    f2__thought_process__read_write_execute__put(cause, this, slot, f2__read_write_execute__new(cause, read_funk, nil, nil));
  }
  return read_funk;
}
def_pcfunk3(thought_process__read_funk__put, this, slot, value, return f2__thought_process__read_funk__put(this_cause, this, slot, value));

// write_funk

f2ptr f2__thought_process__write_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (! lookup_read_write_execute) {
    return nil;
  }
  f2ptr write_slot = raw__array__elt(cause, lookup_read_write_execute, 1);
  return write_slot;
}
def_pcfunk2(thought_process__write_funk, this, slot, return f2__thought_process__write_funk(this_cause, this, slot));

f2ptr f2__thought_process__write_funk__put(f2ptr cause, f2ptr this, f2ptr slot, f2ptr write_funk) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (lookup_read_write_execute) {
    raw__array__elt__set(cause, lookup_read_write_execute, 1, write_funk);
  } else {
    f2__thought_process__read_write_execute__put(cause, this, slot, f2__read_write_execute__new(cause, nil, write_funk, nil));
  }
  return write_funk;
}
def_pcfunk3(thought_process__write_funk__put, this, slot, value, return f2__thought_process__write_funk__put(this_cause, this, slot, value));

// execute_funk

f2ptr f2__thought_process__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (! lookup_read_write_execute) {
    return nil;
  }
  f2ptr execute_slot = raw__array__elt(cause, lookup_read_write_execute, 2);
  return execute_slot;
}
def_pcfunk2(thought_process__execute_funk, this, slot, return f2__thought_process__execute_funk(this_cause, this, slot));

f2ptr f2__thought_process__execute_funk__put(f2ptr cause, f2ptr this, f2ptr slot, f2ptr execute_funk) {
  f2ptr lookup_read_write_execute = f2__thought_process__read_write_execute__lookup(cause, this, slot);
  if (lookup_read_write_execute) {
    raw__array__elt__set(cause, lookup_read_write_execute, 2, execute_funk);
  } else {
    f2__thought_process__read_write_execute__put(cause, this, slot, f2__read_write_execute__new(cause, nil, nil, execute_funk));
  }
  return execute_funk;
}
def_pcfunk3(thought_process__execute_funk__put, this, slot, value, return f2__thought_process__execute_funk__put(this_cause, this, slot, value));

f2ptr f2__abstract(f2ptr cause, f2ptr exp) {
  f2ptr retval = f2thought_process__new_from_exp(cause, exp, f2integer__new(cause, 4));
  return retval;
}
def_pcfunk1(abstract, x, return f2__abstract(this_cause, x));

f2ptr f2__realize(f2ptr cause, f2ptr exp) {
  if (raw__thought_process__is_type(cause, exp)) {
    return f2__thought_process__real_value(cause, exp);
  }
  return exp;
}
def_pcfunk1(realize, x, return f2__realize(this_cause, x));

// end of objects

void funk2_thought_process__init(funk2_thought_process_t* this) {
  this->ptype_memory__symbol                     = -1;
  this->ptype_free_memory__symbol                = -1;
  this->ptype_newly_allocated__symbol            = -1;
  this->ptype_integer__symbol                    = -1;
  this->ptype_double__symbol                     = -1;
  this->ptype_float__symbol                      = -1;
  this->ptype_pointer__symbol                    = -1;
  this->ptype_gfunkptr__symbol                   = -1;
  this->ptype_mutex__symbol                      = -1;
  this->ptype_char__symbol                       = -1;
  this->ptype_string__symbol                     = -1;
  this->ptype_symbol__symbol                     = -1;
  this->ptype_chunk__symbol                      = -1;
  this->ptype_simple_array__symbol               = -1;
  this->ptype_traced_array__symbol               = -1;
  this->ptype_larva__symbol                      = -1;
  // thought_process_type
  this->thought_process_type__symbol             = -1;
  // thought_process
  this->thought_process__symbol                  = -1;
  
  this->global_thought_process_type_hash__symbol = -1;
  this->global_thought_process_type_hash         = -1;
}

void funk2_thought_process__destroy(funk2_thought_process_t* this) {
}

void f2__funk2_thought_process__add_type(f2ptr cause, f2ptr name, f2ptr thought_process_type) {
  f2__ptypehash__add(cause, __funk2.thought_process.global_thought_process_type_hash, name, thought_process_type);
}

f2ptr f2__funk2_thought_process__lookup_type(f2ptr cause, f2ptr name) {
  return f2__ptypehash__lookup(cause, __funk2.thought_process.global_thought_process_type_hash, name);
}

// define thought process type ptype_free_memory

f2ptr f2__ptype_free_memory__type_eq(f2ptr cause, f2ptr exp) {return f2bool__new((f2ptype__raw(exp, cause) == ptype_free_memory));}
def_pcfunk1(ptype_free_memory__type_eq, exp, return f2__ptype_free_memory__type_eq(this_cause, exp));

f2ptr f2__ptype_free_memory__parent_types(f2ptr cause, f2ptr this) {
  return nil;
}
def_pcfunk1(ptype_free_memory__parent_types, this, return f2__ptype_free_memory__parent_types(this_cause, this));

/*
f2ptr f2__read_write_execute__new(f2ptr cause, f2ptr read_funk, f2ptr write_funk, f2ptr execute_funk) {
  f2ptr this = f2array__new(cause, 3, NULL);
  f2array__elt__set(read_write_execute, 0, cause, read_funk);
  f2array__elt__set(read_write_execute, 1, cause, write_funk);
  f2array__elt__set(read_write_execute, 2, cause, execute_funk);
  return this;
}
*/

void raw__read_write_execute_slot_hash__add_read_write_execute_slot(f2ptr cause, f2ptr this, char* slot_name, f2ptr read_funk, f2ptr write_funk, f2ptr execute_funk) {
  f2__ptypehash__add(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), f2__read_write_execute__new(cause, read_funk, write_funk, execute_funk));
}

void f2__thought_process__init_default_slots(f2ptr cause, f2ptr this) {
  f2ptr read_write_execute_slot_hash = f2thought_process__read_write_execute_slot_hash(this, cause);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "type_eq",          nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "name",             nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "real_value",       nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "parent_types",     nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "child_types",      nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "translation_hash", nil, nil, nil);
  raw__read_write_execute_slot_hash__add_read_write_execute_slot(cause, read_write_execute_slot_hash, "thematic_klines",  nil, nil, nil);
}

f2ptr f2__thought_process__new(f2ptr cause) {
  f2ptr this = f2thought_process__new(cause, f2__ptypehash__new(cause));
  f2__thought_process__init_default_slots(cause, this);
  return this;
}
def_pcfunk0(thought_process, return f2__thought_process__new(this_cause));

void f2__thought_process_type__init_default_slots(f2ptr cause, f2ptr this) {
  f2__thought_process__init_default_slots(cause, this);
}

void f2__define__thought_process_type__ptype_free_memory(f2ptr cause) {
  //f2ptr thought_process = 
  f2thought_process__new(cause, f2__ptypehash__new(cause));
  f2__thought_process__init_default_slots(cause, __funk2.thought_process.ptype_free_memory__symbol);
}

// initialization

void f2__thought_process__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_thought_process_c__cause__new(initial_cause(), nil, nil);
  
  __funk2.thought_process.thought_process_type__symbol             = f2symbol__new(cause, strlen("thought_process_type"),                      (u8*)"thought_process_type");
  __funk2.thought_process.ptype_free_memory__symbol                = f2symbol__new(cause, strlen("thought_process:ptype_free_memory"),         (u8*)"thought_process:ptype_free_memory");
  __funk2.thought_process.ptype_newly_allocated__symbol            = f2symbol__new(cause, strlen("thought_process:ptype_newly_allocated"),     (u8*)"thought_process:ptype_newly_allocated");
  __funk2.thought_process.ptype_integer__symbol                    = f2symbol__new(cause, strlen("thought_process:ptype_integer"),             (u8*)"thought_process:ptype_integer");
  __funk2.thought_process.ptype_double__symbol                     = f2symbol__new(cause, strlen("thought_process:ptype_double"),              (u8*)"thought_process:ptype_double");
  __funk2.thought_process.ptype_float__symbol                      = f2symbol__new(cause, strlen("thought_process:ptype_float"),               (u8*)"thought_process:ptype_float");
  __funk2.thought_process.ptype_pointer__symbol                    = f2symbol__new(cause, strlen("thought_process:ptype_pointer"),             (u8*)"thought_process:ptype_pointer");
  __funk2.thought_process.ptype_gfunkptr__symbol                   = f2symbol__new(cause, strlen("thought_process:ptype_gfunkptr"),            (u8*)"thought_process:ptype_gfunkptr");
  __funk2.thought_process.ptype_mutex__symbol                      = f2symbol__new(cause, strlen("thought_process:ptype_mutex"),               (u8*)"thought_process:ptype_mutex");
  __funk2.thought_process.ptype_char__symbol                       = f2symbol__new(cause, strlen("thought_process:ptype_char"),                (u8*)"thought_process:ptype_char");
  __funk2.thought_process.ptype_string__symbol                     = f2symbol__new(cause, strlen("thought_process:ptype_string"),              (u8*)"thought_process:ptype_string");
  __funk2.thought_process.ptype_symbol__symbol                     = f2symbol__new(cause, strlen("thought_process:ptype_symbol"),              (u8*)"thought_process:ptype_symbol");
  __funk2.thought_process.ptype_chunk__symbol                      = f2symbol__new(cause, strlen("thought_process:ptype_chunk"),               (u8*)"thought_process:ptype_chunk");
  __funk2.thought_process.ptype_simple_array__symbol               = f2symbol__new(cause, strlen("thought_process:ptype_simple_array"),        (u8*)"thought_process:ptype_simple_array");
  __funk2.thought_process.ptype_traced_array__symbol               = f2symbol__new(cause, strlen("thought_process:ptype_traced_array"),        (u8*)"thought_process:ptype_traced_array");
  __funk2.thought_process.ptype_larva__symbol                      = f2symbol__new(cause, strlen("thought_process:ptype_larva"),               (u8*)"thought_process:ptype_larva");
  __funk2.thought_process.thought_process__symbol                  = f2symbol__new(cause, strlen("thought_process"),                           (u8*)"thought_process");
  __funk2.thought_process.real_value_slot__symbol                  = f2symbol__new(cause, strlen("thought_process:real_value"),                (u8*)"thought_process:real_value");
  
  __funk2.thought_process.global_thought_process_type_hash__symbol = f2symbol__new(cause, strlen("thought_process:thought_process_type_hash"), (u8*)"thought_process:thought_process_type_hash");
  __funk2.thought_process.global_thought_process_type_hash         = f2__ptypehash__new(cause);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.global_thought_process_type_hash__symbol, __funk2.thought_process.global_thought_process_type_hash);
  
}

void f2__thought_process__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "thought_process", "", &f2__thought_process__reinitialize_globalvars);
  
  f2__thought_process__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_thought_process_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.thought_process_type__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.thought_process__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.real_value_slot__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_free_memory__symbol,                nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_newly_allocated__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_integer__symbol,                    nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_double__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_float__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_pointer__symbol,                    nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_gfunkptr__symbol,                   nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_mutex__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_char__symbol,                       nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_string__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_symbol__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_chunk__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_simple_array__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_traced_array__symbol,               nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.ptype_larva__symbol,                      nil);
  environment__add_var_value(cause, global_environment(), __funk2.thought_process.global_thought_process_type_hash__symbol, __funk2.thought_process.global_thought_process_type_hash);
  
  //f2__primcfunk__init(abstract);
  //f2__primcfunk__init(realize);
  //f2__primcfunk__init(determine_thought_process_types);
  //f2__primcfunk__init(thought_process);
  //f2__primcfunk__init(thought_process__lookup_read_slot);
  //f2__primcfunk__init(thought_process__lookup_write_slot);
  //f2__primcfunk__init(thought_process__lookup_execute_slot);
  //f2__primcfunk__init(thought_process__read_funk);
  //f2__primcfunk__init(thought_process__read_funk__put);
  //f2__primcfunk__init(thought_process__write_funk);
  //f2__primcfunk__init(thought_process__write_funk__put);
  //f2__primcfunk__init(thought_process__execute_funk);
  //f2__primcfunk__init(thought_process__execute_funk__put);
  
  f2__primcfunk__init(thought_process__read_funk, "");
  f2__primcfunk__init(thought_process__read_funk__put, "");
  f2__primcfunk__init(thought_process__write_funk, "");
  f2__primcfunk__init(thought_process__write_funk__put, "");
  f2__primcfunk__init(thought_process__execute_funk, "");
  f2__primcfunk__init(thought_process__execute_funk__put, "");
  f2__primcfunk__init(abstract, "");
  f2__primcfunk__init(realize, "");
  f2__primcfunk__init(thought_process, "");
}

