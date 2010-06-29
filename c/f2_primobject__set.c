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

// set

def_primobject_4_slot(set, write_mutex, key_count, bin_num_power, bin_array);

boolean_t raw__set__valid(f2ptr cause, f2ptr this) {
  if (! raw__set__is_type(cause, this)) {return 0;}
  f2ptr bin_num_power = f2set__bin_num_power(this, cause);
  f2ptr bin_array     = f2set__bin_array(this, cause);
  if (! raw__integer__is_type(cause, bin_num_power)) {return 0;}
  if (! raw__array__is_type(cause, bin_array))       {return 0;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return 0;}
  return 1;
}

f2ptr raw__set__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2set__new(cause, f2mutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array);
  debug__assert(raw__set__valid(cause, this), nil, "raw__set__new assert failed: f2__set__valid(this)");
  return this;
}

#define set__default_start_bin_num_power 3
f2ptr f2__set__new(f2ptr cause) {return raw__set__new(cause, set__default_start_bin_num_power);}
def_pcfunk0(set__new, return f2__set__new(this_cause));

void f2__set__double_size__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr bin_num_power    = f2set__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2set__bin_array(this, cause);
  f2ptr temp_set         = raw__set__new(cause, bin_num_power__i + 1);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("f2__set__double_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr, bin_num, bin_num << 1);
    u64 bin_index;
    for (bin_index = 0; bin_index < bin_num; bin_index ++) {
      f2ptr key_iter = raw__array__elt(cause, bin_array, bin_index);
      while(key_iter) {
	f2ptr key  = f2cons__car(key_iter,  cause);
	f2__set__add(cause, temp_set, key);
	key_iter = f2cons__cdr(key_iter, cause);
      }
    }
  }
  f2set__bin_num_power__set(this, cause, f2set__bin_num_power(temp_set, cause));
  f2set__bin_array__set(    this, cause, f2set__bin_array(    temp_set, cause));
}

f2ptr f2__set__add(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__add assert failed: f2__set__valid(this)");
  f2mutex__lock(f2set__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2set__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2set__bin_array(this, cause);
  u64   key__hash_value    = raw__eq_hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr key_iter           = raw__array__elt(cause, bin_array, index);
  while(key_iter) {
    f2ptr iter__key = f2cons__car(key_iter,  cause);
    if (raw__eq(cause, key, iter__key)) {
      return f2bool__new(boolean__true);
    }
    key_iter = f2cons__cdr(key_iter, cause);
  }
  raw__array__elt__set(cause, bin_array, index, f2cons__new(cause, key, raw__array__elt(cause, bin_array, index)));
  s64 key_count__i = f2integer__i(f2set__key_count(this, cause), cause);
  {
    key_count__i ++;
    f2set__key_count__set(this, cause, f2integer__new(cause, key_count__i));
  }
  if (key_count__i >= (1ll << bin_num_power__i)) {
    f2__set__double_size__thread_unsafe(cause, this);
  }
  f2mutex__unlock(f2set__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk2(set__add, this, element, return f2__set__add(this_cause, this, element));

boolean_t raw__set__remove(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__remove assert failed: f2__set__valid(this)");
  boolean_t key_was_removed = boolean__false;
  f2mutex__lock(f2set__write_mutex(this, cause), cause);
  {
    f2ptr bin_num_power    = f2set__bin_num_power(this, cause);
    u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
    f2ptr bin_array        = f2set__bin_array(this, cause);
    u64   key__hash_value  = raw__eq_hash_value(cause, key);
    u64   hash_value       = (key__hash_value * PRIME_NUMBER__16_BIT);
    u64   hash_value_mask  = (0xffffffffffffffffll >> (64 - bin_num_power__i));
    u64   index            = hash_value & hash_value_mask;
    {
      f2ptr prev = nil;
      f2ptr iter = raw__array__elt(cause, bin_array, index);
      while(iter) {
	f2ptr next      = f2cons__cdr(iter, cause);
	f2ptr iter__key = f2cons__car(iter, cause);
	if (raw__eq(cause, key, iter__key)) {
	  if (prev) {
	    f2cons__cdr__set(prev, cause, next);
	  } else {
	    raw__array__elt__set(cause, bin_array, index, next);
	  }
	  s64 key_count__i = f2integer__i(f2set__key_count(this, cause), cause);
	  {
	    key_count__i --;
	    f2set__key_count__set(this, cause, f2integer__new(cause, key_count__i));
	  }
	  key_was_removed = boolean__true;
	  break;
	}
	prev = iter;
	iter = next;
      }
    }
  }
  f2mutex__unlock(f2set__write_mutex(this, cause), cause);
  return key_was_removed;
}

f2ptr f2__set__remove(f2ptr cause, f2ptr this, f2ptr key) {
  if (! raw__set__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__set__remove(cause, this, key));
}
def_pcfunk2(set__remove, this, key, return f2__set__remove(this_cause, this, key));

f2ptr raw__set__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__lookup assert failed: f2__set__valid(this)");
  f2mutex__lock(f2set__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2set__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2set__bin_array(this, cause);
  u64   key__hash_value    = raw__eq_hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr key_iter           = raw__array__elt(cause, bin_array, index);
  while(key_iter) {
    f2ptr iter__key = f2cons__car(key_iter, cause);
    if (raw__eq(cause, key, iter__key)) {
      f2mutex__unlock(f2set__write_mutex(this, cause), cause);
      return iter__key;
    }
    key_iter = f2cons__cdr(key_iter, cause);
  }
  f2mutex__unlock(f2set__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__set__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  if (! raw__set__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__set__lookup(cause, this, key);
}
def_pcfunk2(set__lookup, this, element, return f2__set__lookup(this_cause, this, element));

boolean_t raw__set__contains(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr set__key = f2__set__lookup(cause, this, key);
  if (set__key) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__set__contains(f2ptr cause, f2ptr this, f2ptr key) {
  if (! raw__set__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__set__contains(cause, this, key));
}

f2ptr raw__set__elements(f2ptr cause, f2ptr this) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__elements assert failed: f2__set__valid(this)");
  f2ptr new_list = nil;
  set__iteration(cause, this, element,
		 new_list = f2cons__new(set__iteration__cause, element, new_list));
  return new_list;
}

f2ptr f2__set__elements(f2ptr cause, f2ptr this) {
  if (! raw__set__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__set__elements(cause, this);
}
def_pcfunk1(set__elements, this, return f2__set__elements(this_cause, this));


f2ptr f2set__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2set__primobject_type__new(cause);
  {char* slot_name = "add";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk);}
  {char* slot_name = "remove";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.remove__funk);}
  {char* slot_name = "lookup";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk);}
  {char* slot_name = "elements"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk);}
  return this;
}


// **

void f2__primobject_set__reinitialize_globalvars() {
  __set__symbol = new__symbol(initial_cause(), "set");
}

void f2__primobject_set__initialize() {
  f2__primobject_set__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __set__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // set
  
  initialize_primobject_4_slot(set, write_mutex, key_count, bin_num_power, bin_array);
  
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_set.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__add, this, element, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk = never_gc(cfunk);}
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_set.remove__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__remove, this, element, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.remove__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__lookup, this, element, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "elements"; __funk2.globalenv.object_type.primobject.primobject_type_set.elements__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__elements, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk = never_gc(cfunk);}
  
}

