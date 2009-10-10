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

// hashtable primobject definition

/*
defprimobject__static_slot(hashtable__write_mutex,   0);
defprimobject__static_slot(hashtable__key_count,     1);
defprimobject__static_slot(hashtable__bin_num_power, 2);
defprimobject__static_slot(hashtable__bin_array,     3);

f2ptr __hashtable__symbol = -1;
*/

def_primobject_4_slot(hashtable, write_mutex, key_count, bin_num_power, bin_array);

boolean_t raw__hashtable__valid(f2ptr cause, f2ptr this) {
  if (! raw__hashtable__is_type(cause, this)) {return boolean__false;}
  f2ptr bin_num_power = f2hashtable__bin_num_power(this, cause);
  f2ptr bin_array     = f2hashtable__bin_array(this, cause);
  if (! raw__integer__is_type(cause, bin_num_power)) {return boolean__false;}
  if (! raw__array__is_type(cause, bin_array))       {return boolean__false;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return boolean__false;}
  return boolean__true;
}

f2ptr raw__hashtable__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2hashtable__new(cause, f2mutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array);
  debug__assert(raw__hashtable__valid(cause, this), nil, "raw__hashtable__new assert failed: f2__hashtable__valid(this)");
  return this;
}

#define hashtable__default_start_bin_num_power 3
f2ptr f2__hashtable__new(f2ptr cause) {return raw__hashtable__new(cause, hashtable__default_start_bin_num_power);}
def_pcfunk0(hashtable__new, return f2__hashtable__new(this_cause));

/*
f2ptr f2hashtable__new(f2ptr cause, f2ptr write_mutex, f2ptr key_count, f2ptr bin_num_power, f2ptr bin_array) {
  release__assert(__hashtable__symbol != -1, nil, "f2hashtable__new error: used before primobjects initialized.");
  release__assert((raw__integer__is_type(cause, bin_num_power) && raw__array__is_type(cause, bin_array)), nil, "f2hashtable__new error: bin_num_power or bin_array are of wrong type.");
  f2ptr this = f2__primobject__new(cause, __hashtable__symbol, 4, nil);
  f2hashtable__write_mutex__set(  this, cause, write_mutex);
  f2hashtable__key_count__set(    this, cause, key_count);
  f2hashtable__bin_num_power__set(this, cause, bin_num_power);
  f2hashtable__bin_array__set(    this, cause, bin_array);
  return this;
}

// hardcoded hashtable functions


boolean_t raw__hashtable__is_type(f2ptr cause, f2ptr this) {return raw__array__is_type(cause, this) && f2primobject__is__hashtable(this, cause);}
f2ptr f2__hashtable__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__hashtable__is_type(cause, this));}
def_pcfunk1(hashtable__is_type, this, return f2__hashtable__is_type(this_cause, this));

f2ptr f2__hashtable__write_mutex(f2ptr cause, f2ptr this) {return f2hashtable__write_mutex(this, cause);}
def_pcfunk1(hashtable__write_mutex, this, return f2__hashtable__write_mutex(this_cause, this));

f2ptr f2__hashtable__write_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2hashtable__write_mutex__set(this, cause, value);}
def_pcfunk2(hashtable__write_mutex__set, this, value, return f2__hashtable__write_mutex__set(this_cause, this, value));

f2ptr f2__hashtable__key_count(f2ptr cause, f2ptr this) {return f2hashtable__key_count(this, cause);}
def_pcfunk1(hashtable__key_count, this, return f2__hashtable__key_count(this_cause, this));

f2ptr f2__hashtable__key_count__set(f2ptr cause, f2ptr this, f2ptr value) {return f2hashtable__key_count__set(this, cause, value);}
def_pcfunk2(hashtable__key_count__set, this, value, return f2__hashtable__key_count__set(this_cause, this, value));

f2ptr f2__hashtable__bin_num_power(f2ptr cause, f2ptr this) {return f2hashtable__bin_num_power(this, cause);}
def_pcfunk1(hashtable__bin_num_power, this, return f2__hashtable__bin_num_power(this_cause, this));

f2ptr f2__hashtable__bin_num_power__set(f2ptr cause, f2ptr this, f2ptr value) {return f2hashtable__bin_num_power__set(this, cause, value);}
def_pcfunk2(hashtable__bin_num_power__set, this, value, return f2__hashtable__bin_num_power__set(this_cause, this, value));

f2ptr f2__hashtable__bin_array(f2ptr cause, f2ptr this) {return f2hashtable__bin_array(this, cause);}
def_pcfunk1(hashtable__bin_array, this, return f2__hashtable__bin_array(this_cause, this));

f2ptr f2__hashtable__bin_array__set(f2ptr cause, f2ptr this, f2ptr value) {return f2hashtable__bin_array__set(this, cause, value);}
def_pcfunk2(hashtable__bin_array__set, this, value, return f2__hashtable__bin_array__set(this_cause, this, value));

*/

void f2__hashtable__double_size__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr bin_num_power    = f2hashtable__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2hashtable__bin_array(this, cause);
  f2ptr temp_hashtable   = raw__hashtable__new(cause, bin_num_power__i + 1);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("f2__hashtable__double_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr, bin_num, bin_num << 1);
    u64 bin_index;
    for (bin_index = 0; bin_index < bin_num; bin_index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, bin_index);
      while(keyvalue_pair_iter) {
	f2ptr iter__keyvalue_pair  = f2cons__car(keyvalue_pair_iter,  cause);
	f2ptr keyvalue_pair__key   = f2cons__car(iter__keyvalue_pair, cause);
	f2ptr keyvalue_pair__value = f2cons__cdr(iter__keyvalue_pair, cause);
	f2__hashtable__add(cause, temp_hashtable, keyvalue_pair__key, keyvalue_pair__value);
	keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
      }
    }
  }
  f2hashtable__bin_num_power__set(this, cause, f2hashtable__bin_num_power(temp_hashtable, cause));
  f2hashtable__bin_array__set(    this, cause, f2hashtable__bin_array(    temp_hashtable, cause));
}

f2ptr f2__hashtable__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__add assert failed: f2__hashtable__valid(this)");
  f2mutex__lock(f2hashtable__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2hashtable__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hashtable__bin_array(this, cause);
  u64   key__hash_value    = raw__hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair      = nil;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr iter__keyvalue_pair = f2cons__car(keyvalue_pair_iter,  cause);
    f2ptr keyvalue_pair__key  = f2cons__car(iter__keyvalue_pair, cause);
    if (raw__equals(cause, key, keyvalue_pair__key)) {
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
  s64 key_count__i = f2integer__i(f2hashtable__key_count(this, cause), cause);
  {
    key_count__i ++;
    f2hashtable__key_count__set(this, cause, f2integer__new(cause, key_count__i));
  }
  if (key_count__i >= (1ll << bin_num_power__i)) {
    f2__hashtable__double_size__thread_unsafe(cause, this);
  }
  f2mutex__unlock(f2hashtable__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk3(hashtable__add, this, slot_name, value, return f2__hashtable__add(this_cause, this, slot_name, value));

f2ptr f2__hashtable__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__lookup_keyvalue_pair assert failed: f2__hashtable__valid(this)");
  f2mutex__lock(f2hashtable__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2hashtable__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2hashtable__bin_array(this, cause);
  u64   key__hash_value    = raw__hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr keyvalue_pair      = f2cons__car(keyvalue_pair_iter, cause);
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
    if (raw__equals(cause, key, keyvalue_pair__key)) {
      f2mutex__unlock(f2hashtable__write_mutex(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2mutex__unlock(f2hashtable__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__hashtable__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__lookup assert failed: f2__hashtable__valid(this)");
  f2ptr keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}
def_pcfunk2(hashtable__lookup, this, slot_name, return f2__hashtable__lookup(this_cause, this, slot_name));


f2ptr raw__hashtable__mapc_slot_names(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__mapc_slot_names assert failed: f2__hashtable__valid(this)");
  hashtable__key__iteration(cause, this, key,
                            (*map_funk)(cause, key, aux_data));
  return nil;
}


f2ptr f2__hashtable__slot_names(f2ptr cause, f2ptr this) {
  debug__assert(raw__hashtable__valid(cause, this), nil, "f2__hashtable__slot_names assert failed: f2__hashtable__valid(this)");
  f2ptr new_list = nil;
  hashtable__key__iteration(cause, this, key,
                            new_list = f2cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(hashtable__slot_names, this, return f2__hashtable__slot_names(this_cause, this));

f2ptr f2hashtable__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2hashtable__primobject_type__new(cause);
  {char* slot_name = "slot_names";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hashtable.slot_names__funk);}
  {char* slot_name = "add";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hashtable.add__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hashtable.lookup__funk);}
  return this;
}

// **

void f2__primobject_hashtable__reinitialize_globalvars() {
  __hashtable__symbol = f2symbol__new(initial_cause(), strlen("hashtable"), (u8*)"hashtable");
}

void f2__primobject_hashtable__initialize() {
  f2__primobject_hashtable__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __hashtable__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // hashtable
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(hashtable__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.new__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.write_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__write_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.write_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.write_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hashtable__write_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.write_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.key_count__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__key_count, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.key_count__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.key_count__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hashtable__key_count__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.key_count__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_num_power__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__bin_num_power, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_num_power__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power-set"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_num_power__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hashtable__bin_num_power__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_num_power__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_array__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__bin_array, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_array__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array-set"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_array__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hashtable__bin_array__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.bin_array__set__funk = never_gc(cfunk);}
  {char* symbol_str = "slot_names"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.slot_names__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hashtable__slot_names, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.slot_names__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(hashtable__add, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_hashtable.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hashtable__lookup, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_hashtable.lookup__funk = never_gc(cfunk);}
  
}

