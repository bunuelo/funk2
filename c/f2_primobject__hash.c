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

// hash

def_primobject_6_slot(hash, write_mutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);

boolean_t raw__hash__valid(f2ptr cause, f2ptr this) {
  if (! raw__hash__is_type(cause, this)) {return boolean__false;}
  f2ptr bin_num_power = f2hash__bin_num_power(this, cause);
  f2ptr bin_array     = f2hash__bin_array(this, cause);
  if (! raw__integer__is_type(cause, bin_num_power)) {return boolean__false;}
  if (! raw__array__is_type(cause, bin_array))       {return boolean__false;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return boolean__false;}
  return boolean__true;
}

f2ptr raw__hash__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2hash__new(cause, f2mutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array, nil, nil);
  debug__assert(raw__hash__valid(cause, this), nil, "raw__hash__new assert failed: f2__hash__valid(this)");
  return this;
}

#define hash__default_start_bin_num_power 3
f2ptr f2__hash__new(f2ptr cause) {return raw__hash__new(cause, hash__default_start_bin_num_power);}
def_pcfunk0(hash__new, return f2__hash__new(this_cause));

void f2__hash__double_size__thread_unsafe(f2ptr cause, f2ptr fiber, f2ptr this) {
  f2ptr bin_num_power    = f2hash__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2hash__bin_array(this, cause);
  f2ptr temp_hash   = raw__hash__new(cause, bin_num_power__i + 1);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("f2__hash__double_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr, bin_num, bin_num << 1);
    u64 bin_index;
    for (bin_index = 0; bin_index < bin_num; bin_index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, bin_index);
      while(keyvalue_pair_iter) {
	f2ptr iter__keyvalue_pair  = f2cons__car(keyvalue_pair_iter,  cause);
	f2ptr keyvalue_pair__key   = f2cons__car(iter__keyvalue_pair, cause);
	f2ptr keyvalue_pair__value = f2cons__cdr(iter__keyvalue_pair, cause);
	f2__hash__add(cause, fiber, temp_hash, keyvalue_pair__key, keyvalue_pair__value);
	keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
      }
    }
  }
  f2hash__bin_num_power__set(this, cause, f2hash__bin_num_power(temp_hash, cause));
  f2hash__bin_array__set(    this, cause, f2hash__bin_array(    temp_hash, cause));
}

u64 raw__hash__hash_value_apply(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object) {
  f2ptr hash_value_funk = f2hash__hash_value_funk(this, cause);
  u64   key__hash_value = 0;
  if (! hash_value_funk) {
    key__hash_value = raw__hash_value(cause, object);
  } else {
    // should use the hash_value_funk here...
    key__hash_value = raw__hash_value(cause, object);
  }
  return key__hash_value;
}

boolean_t raw__hash__equals_apply(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object_a, f2ptr object_b) {
  f2ptr equals_funk = f2hash__equals_funk(this, cause);
  boolean_t equals = boolean__false;
  if (! equals_funk) {
    equals = raw__equals(cause, object_a, object_b);
  } else {
    // should use the equals_funk here...
    equals = raw__equals(cause, object_a, object_b);
  }
  return equals;
}

f2ptr f2__hash__add(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__add assert failed: f2__hash__valid(this)");
  f2mutex__lock(f2hash__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2hash__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hash__bin_array(this, cause);
  u64   key__hash_value    = raw__hash__hash_value_apply(cause, fiber, this, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair      = nil;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr iter__keyvalue_pair = f2cons__car(keyvalue_pair_iter,  cause);
    f2ptr keyvalue_pair__key  = f2cons__car(iter__keyvalue_pair, cause);
    if (raw__hash__equals_apply(cause, fiber, this, key, keyvalue_pair__key)) {
      keyvalue_pair = iter__keyvalue_pair;
      break;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  if (! keyvalue_pair) {
    keyvalue_pair = f2cons__new(cause, key, value);
    raw__array__elt__set(cause, bin_array, index, f2cons__new(cause, keyvalue_pair, raw__array__elt(cause, bin_array, index)));
  } else {
    f2cons__cdr__set(keyvalue_pair, cause, value);
  }
  s64 key_count__i = f2integer__i(f2hash__key_count(this, cause), cause);
  {
    key_count__i ++;
    f2hash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
  }
  if (key_count__i >= (1ll << bin_num_power__i)) {
    f2__hash__double_size__thread_unsafe(cause, fiber, this);
  }
  f2mutex__unlock(f2hash__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk3(hash__add, this, slot_name, value, return f2__hash__add(this_cause, simple_fiber, this, slot_name, value));

f2ptr f2__hash__lookup_keyvalue_pair(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr key) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__lookup_keyvalue_pair assert failed: f2__hash__valid(this)");
  f2mutex__lock(f2hash__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2hash__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hash__bin_array(this, cause);
  u64   key__hash_value    = raw__hash__hash_value_apply(cause, fiber, this, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr keyvalue_pair      = f2cons__car(keyvalue_pair_iter, cause);
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
    if (raw__hash__equals_apply(cause, fiber, this, key, keyvalue_pair__key)) {
      f2mutex__unlock(f2hash__write_mutex(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2mutex__unlock(f2hash__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__hash__lookup(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr key) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__lookup assert failed: f2__hash__valid(this)");
  f2ptr keyvalue_pair = f2__hash__lookup_keyvalue_pair(cause, fiber, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}
def_pcfunk2(hash__lookup, this, slot_name, return f2__hash__lookup(this_cause, simple_fiber, this, slot_name));


f2ptr raw__hash__mapc_slot_names(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__mapc_slot_names assert failed: f2__hash__valid(this)");
  hash__key__iteration(cause, this, key,
                            (*map_funk)(cause, key, aux_data));
  return nil;
}


f2ptr f2__hash__slot_names(f2ptr cause, f2ptr this) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__slot_names assert failed: f2__hash__valid(this)");
  f2ptr new_list = nil;
  hash__key__iteration(cause, this, key,
                            new_list = f2cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(hash__slot_names, this, return f2__hash__slot_names(this_cause, this));

f2ptr f2hash__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2hash__primobject_type__new(cause);
  {char* slot_name = "slot_names";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__funk);}
  {char* slot_name = "add";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.add__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__funk);}
  return this;
}

// **

void f2__primobject_hash__reinitialize_globalvars() {
  __hash__symbol = f2symbol__new(initial_cause(), strlen("hash"), (u8*)"hash");
}

void f2__primobject_hash__initialize() {
  f2__primobject_hash__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __hash__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // hash
  
  initialize_primobject_6_slot(hash, write_mutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);
  
  {char* symbol_str = "slot_names"; __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hash__slot_names, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_hash.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(hash__add, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hash.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__lookup, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__funk = never_gc(cfunk);}
  
}

