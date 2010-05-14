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

/*
defprimobject__static_slot(set__write_mutex,   0);
defprimobject__static_slot(set__key_count,     1);
defprimobject__static_slot(set__bin_num_power, 2);
defprimobject__static_slot(set__bin_array,     3);

f2ptr __set__symbol = -1;

f2ptr f2set__new(f2ptr cause, f2ptr write_mutex, f2ptr key_count, f2ptr bin_num_power, f2ptr bin_array) {
  release__assert(__set__symbol != -1, nil, "f2set__new error: used before primobjects initialized.");
  release__assert((raw__integer__is_type(cause, bin_num_power) && raw__array__is_type(cause, bin_array)), nil, "f2set__new error: bin_num_power or bin_array are of wrong type.");
  f2ptr this = f2__primobject__new(cause, __set__symbol, 4, nil);
  f2set__write_mutex__set(  this, cause, write_mutex);
  f2set__key_count__set(    this, cause, key_count);
  f2set__bin_num_power__set(this, cause, bin_num_power);
  f2set__bin_array__set(    this, cause, bin_array);
  return this;
}

// hardcoded set functions

boolean_t raw__set__is_type(f2ptr cause, f2ptr this) {return raw__array__is_type(cause, this) && f2primobject__is_set(this, cause);}
f2ptr f2__set__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__set__is_type(cause, this));}
def_pcfunk1(set__is_type, this, return f2__set__is_type(this_cause, this));
*/

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

/*
f2ptr f2__set__write_mutex(f2ptr cause, f2ptr this) {return f2set__write_mutex(this, cause);}
def_pcfunk1(set__write_mutex, this, return f2__set__write_mutex(this_cause, this));

f2ptr f2__set__write_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2set__write_mutex__set(this, cause, value);}
def_pcfunk2(set__write_mutex__set, this, value, return f2__set__write_mutex__set(this_cause, this, value));

f2ptr f2__set__key_count(f2ptr cause, f2ptr this) {return f2set__key_count(this, cause);}
def_pcfunk1(set__key_count, this, return f2__set__key_count(this_cause, this));

f2ptr f2__set__key_count__set(f2ptr cause, f2ptr this, f2ptr value) {return f2set__key_count__set(this, cause, value);}
def_pcfunk2(set__key_count__set, this, value, return f2__set__key_count__set(this_cause, this, value));

f2ptr f2__set__bin_num_power(f2ptr cause, f2ptr this) {return f2set__bin_num_power(this, cause);}
def_pcfunk1(set__bin_num_power, this, return f2__set__bin_num_power(this_cause, this));

f2ptr f2__set__bin_num_power__set(f2ptr cause, f2ptr this, f2ptr value) {return f2set__bin_num_power__set(this, cause, value);}
def_pcfunk2(set__bin_num_power__set, this, value, return f2__set__bin_num_power__set(this_cause, this, value));

f2ptr f2__set__bin_array(f2ptr cause, f2ptr this) {return f2set__bin_array(this, cause);}
def_pcfunk1(set__bin_array, this, return f2__set__bin_array(this_cause, this));

f2ptr f2__set__bin_array__set(f2ptr cause, f2ptr this, f2ptr value) {return f2set__bin_array__set(this, cause, value);}
def_pcfunk2(set__bin_array__set, this, value, return f2__set__bin_array__set(this_cause, this, value));
*/

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

f2ptr f2__set__lookup(f2ptr cause, f2ptr this, f2ptr key) {
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
def_pcfunk2(set__lookup, this, element, return f2__set__lookup(this_cause, this, element));

f2ptr f2__set__elements(f2ptr cause, f2ptr this) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__elements assert failed: f2__set__valid(this)");
  f2mutex__lock(f2set__write_mutex(this, cause), cause);
  f2ptr bin_array          = f2set__bin_array(this, cause);
  s64   bin_array__length  = raw__array__length(cause, bin_array);
  s64   index;
  f2ptr new_list = nil;
  for (index = 0; index < bin_array__length; index ++) {
    f2ptr key_iter = raw__array__elt(cause, bin_array, index);
    while (key_iter) {
      f2ptr iter__key = f2cons__car(key_iter, cause);
      new_list = f2cons__new(cause, iter__key, new_list);
      key_iter = f2cons__cdr(key_iter, cause);
    }
  }
  f2mutex__unlock(f2set__write_mutex(this, cause), cause);
  return new_list;
}
def_pcfunk1(set__elements, this, return f2__set__elements(this_cause, this));


f2ptr f2set__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2set__primobject_type__new(cause);
  {char* slot_name = "add";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk);}
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
  
  /*
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_set.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_set.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(set__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.new__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_set.write_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__write_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.write_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_set.write_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__write_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.write_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count"; __funk2.globalenv.object_type.primobject.primobject_type_set.key_count__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__key_count, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.key_count__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_set.key_count__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__key_count__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.key_count__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power"; __funk2.globalenv.object_type.primobject.primobject_type_set.bin_num_power__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__bin_num_power, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.bin_num_power__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power-set"; __funk2.globalenv.object_type.primobject.primobject_type_set.bin_num_power__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__bin_num_power__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.bin_num_power__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array"; __funk2.globalenv.object_type.primobject.primobject_type_set.bin_array__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__bin_array, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.bin_array__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array-set"; __funk2.globalenv.object_type.primobject.primobject_type_set.bin_array__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__bin_array__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.bin_array__set__funk = never_gc(cfunk);}
  */
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_set.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__add, this, element, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__lookup, this, element, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "elements"; __funk2.globalenv.object_type.primobject.primobject_type_set.elements__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__elements, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk = never_gc(cfunk);}
  
}

