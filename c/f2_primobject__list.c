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

// list primobject definition

defprimobject__static_slot(list__write_mutex,   0);
defprimobject__static_slot(list__key_count,     1);
defprimobject__static_slot(list__bin_num_power, 2);
defprimobject__static_slot(list__bin_array,     3);

f2ptr __list__symbol = -1;

f2ptr f2list__new(f2ptr cause, f2ptr write_mutex, f2ptr key_count, f2ptr bin_num_power, f2ptr bin_array) {
  release__assert(__list__symbol != -1, nil, "f2list__new error: used before primobjects initialized.");
  release__assert((raw__integer__is_type(cause, bin_num_power) && raw__array__is_type(cause, bin_array)), nil, "f2list__new error: bin_num_power or bin_array are of wrong type.");
  f2ptr this = f2__primobject__new(cause, __list__symbol, 4, nil);
  f2list__write_mutex__set(  this, cause, write_mutex);
  f2list__key_count__set(    this, cause, key_count);
  f2list__bin_num_power__set(this, cause, bin_num_power);
  f2list__bin_array__set(    this, cause, bin_array);
  return this;
}

// hardcoded list functions

boolean_t raw__list__is_type(f2ptr cause, f2ptr this) {return raw__array__is_type(cause, this) && f2primobject__is_list(this, cause);}
f2ptr f2__list__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__list__is_type(cause, this));}
def_pcfunk1(list__is_type, this, return f2__list__is_type(this_cause, this));

boolean_t raw__list__valid(f2ptr cause, f2ptr this) {
  if (! raw__list__is_type(cause, this)) {return 0;}
  f2ptr bin_num_power = f2list__bin_num_power(this, cause);
  f2ptr bin_array     = f2list__bin_array(this, cause);
  if (! raw__integer__is_type(cause, bin_num_power)) {return 0;}
  if (! raw__array__is_type(cause, bin_array))       {return 0;}
  s64 bin_num_power__i = f2integer__i(bin_num_power, cause);
  s64 length           = raw__array__length(cause, bin_array);
  if (! (length == (1ll << bin_num_power__i))) {return 0;}
  return 1;
}

f2ptr raw__list__new(f2ptr cause, s64 bin_num_power) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2list__new(cause, f2mutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array);
  debug__assert(raw__list__valid(cause, this), nil, "raw__list__new assert failed: f2__list__valid(this)");
  return this;
}

#define list__default_start_bin_num_power 3
f2ptr f2__list__new(f2ptr cause) {return raw__list__new(cause, list__default_start_bin_num_power);}
def_pcfunk0(list__new, return f2__list__new(this_cause));

f2ptr f2__list__write_mutex(f2ptr cause, f2ptr this) {return f2list__write_mutex(this, cause);}
def_pcfunk1(list__write_mutex, this, return f2__list__write_mutex(this_cause, this));

f2ptr f2__list__write_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2list__write_mutex__set(this, cause, value);}
def_pcfunk2(list__write_mutex__set, this, value, return f2__list__write_mutex__set(this_cause, this, value));

f2ptr f2__list__key_count(f2ptr cause, f2ptr this) {return f2list__key_count(this, cause);}
def_pcfunk1(list__key_count, this, return f2__list__key_count(this_cause, this));

f2ptr f2__list__key_count__set(f2ptr cause, f2ptr this, f2ptr value) {return f2list__key_count__set(this, cause, value);}
def_pcfunk2(list__key_count__set, this, value, return f2__list__key_count__set(this_cause, this, value));

f2ptr f2__list__bin_num_power(f2ptr cause, f2ptr this) {return f2list__bin_num_power(this, cause);}
def_pcfunk1(list__bin_num_power, this, return f2__list__bin_num_power(this_cause, this));

f2ptr f2__list__bin_num_power__set(f2ptr cause, f2ptr this, f2ptr value) {return f2list__bin_num_power__set(this, cause, value);}
def_pcfunk2(list__bin_num_power__set, this, value, return f2__list__bin_num_power__set(this_cause, this, value));

f2ptr f2__list__bin_array(f2ptr cause, f2ptr this) {return f2list__bin_array(this, cause);}
def_pcfunk1(list__bin_array, this, return f2__list__bin_array(this_cause, this));

f2ptr f2__list__bin_array__set(f2ptr cause, f2ptr this, f2ptr value) {return f2list__bin_array__set(this, cause, value);}
def_pcfunk2(list__bin_array__set, this, value, return f2__list__bin_array__set(this_cause, this, value));

void f2__list__double_size__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr bin_num_power    = f2list__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2list__bin_array(this, cause);
  f2ptr temp_list   = raw__list__new(cause, bin_num_power__i + 1);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("f2__list__double_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr, bin_num, bin_num << 1);
    u64 bin_index;
    for (bin_index = 0; bin_index < bin_num; bin_index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, bin_index);
      while(keyvalue_pair_iter) {
	f2ptr iter__keyvalue_pair  = f2cons__car(keyvalue_pair_iter,  cause);
	f2ptr keyvalue_pair__key   = f2cons__car(iter__keyvalue_pair, cause);
	f2ptr keyvalue_pair__value = f2cons__cdr(iter__keyvalue_pair, cause);
	f2__list__add(cause, temp_list, keyvalue_pair__key, keyvalue_pair__value);
	keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
      }
    }
  }
  f2list__bin_num_power__set(this, cause, f2list__bin_num_power(temp_list, cause));
  f2list__bin_array__set(    this, cause, f2list__bin_array(    temp_list, cause));
}

f2ptr f2__list__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__list__valid(cause, this), nil, "f2__list__add assert failed: f2__list__valid(this)");
  f2mutex__lock(f2list__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2list__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2list__bin_array(this, cause);
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
  s64 key_count__i = f2integer__i(f2list__key_count(this, cause), cause);
  {
    key_count__i ++;
    f2list__key_count__set(this, cause, f2integer__new(cause, key_count__i));
  }
  if (key_count__i >= (1ll << bin_num_power__i)) {
    f2__list__double_size__thread_unsafe(cause, this);
  }
  f2mutex__unlock(f2list__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk3(list__add, this, slot_name, value, return f2__list__add(this_cause, this, slot_name, value));

f2ptr f2__list__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__list__valid(cause, this), nil, "f2__list__lookup_keyvalue_pair assert failed: f2__list__valid(this)");
  f2mutex__lock(f2list__write_mutex(this, cause), cause);
  f2ptr bin_num_power      = f2list__bin_num_power(this, cause);
  u64   bin_num_power__i   = f2integer__i(bin_num_power, cause);
  f2ptr bin_array          = f2list__bin_array(this, cause);
  u64   key__hash_value    = raw__hash_value(cause, key);
  u64   hash_value         = (key__hash_value * PRIME_NUMBER__16_BIT);
  u64   hash_value_mask    = (0xffffffffffffffffll >> (64 - bin_num_power__i));
  u64   index              = hash_value & hash_value_mask;
  f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
  while(keyvalue_pair_iter) {
    f2ptr keyvalue_pair      = f2cons__car(keyvalue_pair_iter, cause);
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair, cause);
    if (raw__equals(cause, key, keyvalue_pair__key)) {
      f2mutex__unlock(f2list__write_mutex(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2mutex__unlock(f2list__write_mutex(this, cause), cause);
  return nil;
}

f2ptr f2__list__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__list__valid(cause, this), nil, "f2__list__lookup assert failed: f2__list__valid(this)");
  f2ptr keyvalue_pair = f2__list__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}
def_pcfunk2(list__lookup, this, slot_name, return f2__list__lookup(this_cause, this, slot_name));



#define list__keyvalue_pair__iteration(cause, this, keyvalue_pair, code) {\
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  f2mutex__lock(f2list__write_mutex(iteration__this, iteration__cause), iteration__cause); \
  f2ptr iteration__bin_array          = f2list__bin_array(iteration__this, iteration__cause); \
  s64   iteration__bin_array__length  = raw__array__length(iteration__cause, iteration__bin_array); \
  s64   iteration__index; \
  for (iteration__index = 0; iteration__index < iteration__bin_array__length; iteration__index ++) { \
    f2ptr iteration__keyvalue_pair_iter = raw__array__elt(iteration__cause, iteration__bin_array, iteration__index); \
    while (iteration__keyvalue_pair_iter) { \
      f2ptr keyvalue_pair = f2cons__car(iteration__keyvalue_pair_iter, iteration__cause); \
      code; \
      iteration__keyvalue_pair_iter = f2cons__cdr(iteration__keyvalue_pair_iter, iteration__cause); \
    } \
  } \
  f2mutex__unlock(f2list__write_mutex(iteration__this, iteration__cause), iteration__cause); \
}

#define list__iteration(cause, this, key, value, code) {\
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  list__keyvalue_pair__iteration(iteration__cause, iteration__this, keyvalue_pair, \
                                      f2ptr key   = f2cons__car(keyvalue_pair, iteration__cause); \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code);
}

#define list__key__iteration(cause, this, key, code) {\
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  list__keyvalue_pair__iteration(iteration__cause, iteration__this, keyvalue_pair, \
                                      f2ptr key = f2cons__car(keyvalue_pair, iteration__cause); \
                                      code);
}

#define list__value__iteration(cause, this, value, code) {\
  f2ptr iteration__cause = (cause); \
  f2ptr iteration__this  = (this); \
  list__keyvalue_pair__iteration(iteration__cause, iteration__this, keyvalue_pair, \
                                      f2ptr value = f2cons__cdr(keyvalue_pair, iteration__cause); \
                                      code);
}

f2ptr f2__list__slot_names(f2ptr cause, f2ptr this) {
  debug__assert(raw__list__valid(cause, this), nil, "f2__list__lookup_keyvalue_pair assert failed: f2__list__valid(this)");
  f2ptr new_list = nil;
  list__key__iteration(cause, this, key,
                            new_list = f2cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(list__slot_names, this, return f2__list__slot_names(this_cause, this));

f2ptr f2list__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_list.is_type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_list.new__funk);}
  {char* slot_name = "write_mutex";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__funk,   __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__set__funk, nil);}
  {char* slot_name = "key_count";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__funk,     __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__set__funk, nil);}
  {char* slot_name = "bin_num_power"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__funk, __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__set__funk, nil);}
  {char* slot_name = "bin_array";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__funk,     __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__set__funk, nil);}
  {char* slot_name = "slot_names";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.slot_names__funk,    nil, nil);}
  {char* slot_name = "add";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_list.add__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__funk);}
  return this;
}


// **

void f2__primobject_list__reinitialize_globalvars() {
  __list__symbol = f2symbol__new(initial_cause(), strlen("list"), (u8*)"list");
}

void f2__primobject_list__initialize() {
  f2__primobject_list__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __list__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // list
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_list.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_list.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(list__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.new__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__write_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__write_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.write_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count"; __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__key_count, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__funk = never_gc(cfunk);}
  {char* symbol_str = "key_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__key_count__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.key_count__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power"; __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__bin_num_power, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_num_power-set"; __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__bin_num_power__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.bin_num_power__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array"; __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__bin_array, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__funk = never_gc(cfunk);}
  {char* symbol_str = "bin_array-set"; __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__bin_array__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.bin_array__set__funk = never_gc(cfunk);}
  {char* symbol_str = "slot_names"; __funk2.globalenv.object_type.primobject.primobject_type_list.slot_names__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__slot_names, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.slot_names__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_list.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(list__add, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__lookup, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__funk = never_gc(cfunk);}
  
}

