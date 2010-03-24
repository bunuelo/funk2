// 
// Copyright (c) 2007-2010 Bo Morgan.
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

// ptypehash

def_primobject_4_slot(ptypehash, write_mutex, key_count, bin_num_power, bin_array);

boolean_t raw__ptypehash__valid(f2ptr cause, f2ptr this) {
  if (! raw__ptypehash__is_type(cause, this)) {return boolean__false;}
  f2ptr bin_num_power = f2ptypehash__bin_num_power(this, cause);
  f2ptr bin_array     = f2ptypehash__bin_array(this, cause);
  if (! raw__integer__is_type(cause, bin_num_power)) {return boolean__false;}
  if (! raw__array__is_type(cause, bin_array))       {return boolean__false;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return boolean__false;}
  return boolean__true;
}

f2ptr raw__ptypehash__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2ptypehash__new(cause, f2mutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array);
  debug__assert(raw__ptypehash__valid(cause, this), nil, "raw__ptypehash__new assert failed: f2__ptypehash__valid(this)");
  return this;
}

#define ptypehash__default_start_bin_num_power 4
f2ptr f2__ptypehash__new(f2ptr cause) {return raw__ptypehash__new(cause, ptypehash__default_start_bin_num_power);}
def_pcfunk0(ptypehash__new, return f2__ptypehash__new(this_cause));

void f2__ptypehash__double_size__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr bin_num_power    = f2ptypehash__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2ptypehash__bin_array(this, cause);
  f2ptr temp_ptypehash   = raw__ptypehash__new(cause, bin_num_power__i + 1);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("f2__ptypehash__double_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr, bin_num, bin_num << 1);
    u64 bin_index;
    for (bin_index = 0; bin_index < bin_num; bin_index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, bin_index);
      while(keyvalue_pair_iter) {
	f2ptr iter__keyvalue_pair  = f2cons__car(keyvalue_pair_iter,  cause);
	f2ptr keyvalue_pair__key   = f2cons__car(iter__keyvalue_pair, cause);
	f2ptr keyvalue_pair__value = f2cons__cdr(iter__keyvalue_pair, cause);
	f2__ptypehash__add(cause, temp_ptypehash, keyvalue_pair__key, keyvalue_pair__value);
	keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
      }
    }
  }
  f2ptypehash__bin_num_power__set(this, cause, f2ptypehash__bin_num_power(temp_ptypehash, cause));
  f2ptypehash__bin_array__set(    this, cause, f2ptypehash__bin_array(    temp_ptypehash, cause));
}

f2ptr raw__ptypehash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__add assert failed: f2__ptypehash__valid(this)");
  f2mutex__lock(f2ptypehash__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2ptypehash__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2ptypehash__bin_array(this, cause);
  u64   key__hash_value    = raw__eq_hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair      = nil;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr iter__keyvalue_pair = f2cons__car(keyvalue_pair_iter,  cause);
    f2ptr keyvalue_pair__key  = f2cons__car(iter__keyvalue_pair, cause);
    if (raw__eq(cause, key, keyvalue_pair__key)) {
      keyvalue_pair = iter__keyvalue_pair;
      break;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  if (! keyvalue_pair) {
    keyvalue_pair = f2cons__new(cause, key, value);
    raw__array__elt__set(cause, bin_array, index, f2cons__new(cause, keyvalue_pair, raw__array__elt(cause, bin_array, index)));
    { // increase key count only if didn't already have this key.
      s64 key_count__i = f2integer__i(f2ptypehash__key_count(this, cause), cause);
      key_count__i ++;
      f2ptypehash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
      if ((key_count__i << 1) >= (1ll << bin_num_power__i)) {
	f2__ptypehash__double_size__thread_unsafe(cause, this);
      }
    }
  } else {
    f2cons__cdr__set(keyvalue_pair, cause, value);
  }
  f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  if (! raw__ptypehash__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__ptypehash__add(cause, this, key, value);
}
def_pcfunk3(ptypehash__add, this, slot_name, value, return f2__ptypehash__add(this_cause, this, slot_name, value));

boolean_t raw__ptypehash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__add assert failed: f2__ptypehash__valid(this)");
  boolean_t key_was_removed = boolean__false;
  f2mutex__lock(f2ptypehash__write_mutex(this, cause), cause);
  {
    f2ptr bin_num_power    = f2ptypehash__bin_num_power(this, cause);
    u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
    f2ptr bin_array        = f2ptypehash__bin_array(this, cause);
    u64   key__hash_value  = raw__eq_hash_value(cause, key);
    u64   hash_value       = (key__hash_value * PRIME_NUMBER__16_BIT);
    u64   hash_value_mask  = (0xffffffffffffffffll >> (64 - bin_num_power__i));
    u64   index            = hash_value & hash_value_mask;
    {
      f2ptr prev = nil;
      f2ptr iter = raw__array__elt(cause, bin_array, index);
      while(iter) {
	f2ptr next               = f2cons__cdr(iter, cause);
	f2ptr keyvalue_pair      = f2cons__car(iter, cause);
	f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
	if (raw__eq(cause, key, keyvalue_pair__key)) {
	  if (prev) {
	    f2cons__cdr__set(prev, cause, next);
	  } else {
	    raw__array__elt__set(cause, bin_array, index, next);
	  }
	  s64 key_count__i = f2integer__i(f2ptypehash__key_count(this, cause), cause);
	  {
	    key_count__i --;
	    f2ptypehash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
	  }
	  key_was_removed = boolean__true;
	  break;
	}
	prev = iter;
	iter = next;
      }
    }
  }
  f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
  return key_was_removed;
}

f2ptr f2__ptypehash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  if (! raw__ptypehash__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__ptypehash__remove(cause, this, key));
}
def_pcfunk2(ptypehash__remove, this, key, return f2__ptypehash__remove(this_cause, this, key));

f2ptr f2__ptypehash__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__lookup_keyvalue_pair assert failed: f2__ptypehash__valid(this)");
  f2mutex__lock(f2ptypehash__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2ptypehash__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2ptypehash__bin_array(this, cause);
  u64   key__hash_value    = raw__eq_hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr keyvalue_pair      = f2cons__car(keyvalue_pair_iter, cause);
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
    if (raw__eq(cause, key, keyvalue_pair__key)) {
      f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__lookup assert failed: f2__ptypehash__valid(this)");
  f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}
def_pcfunk2(ptypehash__lookup, this, slot_name, return f2__ptypehash__lookup(this_cause, this, slot_name));

boolean_t raw__ptypehash__contains(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__ptypehash__an_arbitrary_keyvalue_pair(f2ptr cause, f2ptr this) {
  f2mutex__lock(f2ptypehash__write_mutex(this, cause), cause);
  {
    f2ptr bin_array         = f2__ptypehash__bin_array(cause, this);
    u64   bin_array__length = raw__array__length(cause, bin_array);
    u64   index;
    for (index = 0; index < bin_array__length; index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
      if (keyvalue_pair_iter) {
	f2ptr keyvalue_pair = f2cons__car(keyvalue_pair_iter, cause);
	f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
	return keyvalue_pair;
      }
    }
  }
  f2mutex__unlock(f2ptypehash__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__an_arbitrary_key(f2ptr cause, f2ptr this) {
  f2ptr keyvalue_pair = f2__ptypehash__an_arbitrary_keyvalue_pair(cause, this);
  if (! keyvalue_pair) {
    return nil;
  }
  f2ptr key = f2__cons__car(cause, keyvalue_pair);
  return key;
}

f2ptr f2__ptypehash__an_arbitrary_value(f2ptr cause, f2ptr this) {
  f2ptr keyvalue_pair = f2__ptypehash__an_arbitrary_keyvalue_pair(cause, this);
  if (! keyvalue_pair) {
    return nil;
  }
  f2ptr value = f2__cons__cdr(cause, keyvalue_pair);
  return value;
}

f2ptr raw__ptypehash__mapc_slot_names(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__mapc_slot_names assert failed: f2__ptypehash__valid(this)");
  ptypehash__key__iteration(cause, this, key,
                            (*map_funk)(cause, key, aux_data));
  return nil;
}


f2ptr f2__ptypehash__slot_names(f2ptr cause, f2ptr this) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__slot_names assert failed: f2__ptypehash__valid(this)");
  f2ptr new_list = nil;
  ptypehash__key__iteration(cause, this, key,
                            new_list = f2cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(ptypehash__slot_names, this, return f2__ptypehash__slot_names(this_cause, this));


f2ptr f2ptypehash__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2ptypehash__primobject_type__new(cause);
  {char* slot_name = "slot_names";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.slot_names__funk);}
  {char* slot_name = "add";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__funk);}
  {char* slot_name = "remove";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__funk);}
  return this;
}

// **

void f2__primobject_ptypehash__reinitialize_globalvars() {
  __ptypehash__symbol = f2symbol__new(initial_cause(), strlen("ptypehash"), (u8*)"ptypehash");
}

void f2__primobject_ptypehash__initialize() {
  f2__primobject_ptypehash__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __ptypehash__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // ptypehash
  
  initialize_primobject_4_slot(ptypehash, write_mutex, key_count, bin_num_power, bin_array);
  
  {char* symbol_str = "slot_names"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.slot_names__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__slot_names, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.slot_names__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(ptypehash__add, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__funk = never_gc(cfunk);}
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(ptypehash__remove, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptypehash__lookup, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__funk = never_gc(cfunk);}
  
}

