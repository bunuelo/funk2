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

// hash

def_primobject_6_slot(hash, write_cmutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);

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

f2ptr raw__hash__new(f2ptr cause, s64 bin_num_power, f2ptr hash_value_funk, f2ptr equals_funk) {
  f2ptr bin_array = raw__array__new(cause, 1ll << bin_num_power);
  f2ptr this = f2hash__new(cause, f2cmutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array, hash_value_funk, equals_funk);
  debug__assert(raw__hash__valid(cause, this), nil, "raw__hash__new assert failed: f2__hash__valid(this)");
  return this;
}

#define hash__default_start_bin_num_power 3
f2ptr f2__hash__new(f2ptr cause, f2ptr hash_value_funk, f2ptr equals_funk) {return raw__hash__new(cause, hash__default_start_bin_num_power, hash_value_funk, equals_funk);}
def_pcfunk2(hash__new, hash_value_funk, equals_funk,
	    "",
	    return f2__hash__new(this_cause, hash_value_funk, equals_funk));

f2ptr f2__hash(f2ptr cause) {
  return f2__hash__new(cause, __funk2.object.object__equals_hash_value__funk, __funk2.object.object__equals__funk);
}
def_pcfunk0(hash,
	    "Returns a new hash table based on object-equals_hash_value and object-equals.",
	    return f2__hash(this_cause));

void f2__hash__double_size__thread_unsafe(f2ptr cause, f2ptr fiber, f2ptr this) {
  f2ptr hash_value_funk  = f2hash__hash_value_funk(this, cause);
  f2ptr equals_funk      = f2hash__equals_funk(this, cause);
  f2ptr bin_num_power    = f2hash__bin_num_power(this, cause);
  u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
  f2ptr bin_array        = f2hash__bin_array(this, cause);
  f2ptr temp_hash        = raw__hash__new(cause, bin_num_power__i + 1, hash_value_funk, equals_funk);
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
	f2__hash__add(cause, temp_hash, keyvalue_pair__key, keyvalue_pair__value);
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
  if (hash_value_funk == nil) {
    key__hash_value = raw__eq_hash_value(cause, object);
  } else {
    f2ptr hash_value_integer = f2__force_funk_apply(cause, fiber, hash_value_funk, raw__cons__new(cause, object, nil));
    key__hash_value = f2integer__i(hash_value_integer, cause);
  }
  return key__hash_value;
}

boolean_t raw__hash__equals_apply(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object_a, f2ptr object_b) {
  f2ptr     equals_funk = f2hash__equals_funk(this, cause);
  boolean_t equals      = boolean__false;
  if (equals_funk == nil) {
    equals = raw__eq(cause, object_a, object_b);
  } else {
    equals = (f2__force_funk_apply(cause, fiber, equals_funk, raw__cons__new(cause, object_a, raw__cons__new(cause, object_b, nil))) != nil);
  }
  return equals;
}

f2ptr raw__hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__add assert failed: f2__hash__valid(this)");
  f2cmutex__lock(f2hash__write_cmutex(this, cause), cause);
  f2ptr fiber              = f2__this__fiber(cause);
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
    keyvalue_pair = raw__cons__new(cause, key, value);
    raw__array__elt__set(cause, bin_array, index, raw__cons__new(cause, keyvalue_pair, raw__array__elt(cause, bin_array, index)));
    {
      s64 key_count__i = f2integer__i(f2hash__key_count(this, cause), cause);
      key_count__i ++;
      f2hash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
      if ((key_count__i << 1) >= (1ll << bin_num_power__i)) {
	f2__hash__double_size__thread_unsafe(cause, fiber, this);
      }
    }
  } else {
    f2cons__cdr__set(keyvalue_pair, cause, value);
  }
  f2cmutex__unlock(f2hash__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__hash__add(f2ptr cause, f2ptr this, f2ptr key, f2ptr value) {
  assert_argument_type(hash, this);
  return raw__hash__add(cause, this, key, value);
}
def_pcfunk3(hash__add, this, slot_name, value,
	    "",
	    return f2__hash__add(this_cause, this, slot_name, value));


boolean_t raw__hash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__add assert failed: f2__hash__valid(this)");
  boolean_t key_was_removed = boolean__false;
  f2cmutex__lock(f2hash__write_cmutex(this, cause), cause);
  {
    f2ptr fiber            = f2__this__fiber(cause);
    f2ptr bin_num_power    = f2hash__bin_num_power(this, cause);
    u64   bin_num_power__i = f2integer__i(bin_num_power, cause);
    f2ptr bin_array        = f2hash__bin_array(this, cause);
    u64   key__hash_value  = raw__hash__hash_value_apply(cause, fiber, this, key);
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
	if (raw__hash__equals_apply(cause, fiber, this, key, keyvalue_pair__key)) {
	  if (prev) {
	    f2cons__cdr__set(prev, cause, next);
	  } else {
	    raw__array__elt__set(cause, bin_array, index, next);
	  }
	  s64 key_count__i = f2integer__i(f2hash__key_count(this, cause), cause);
	  {
	    key_count__i --;
	    f2hash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
	  }
	  key_was_removed = boolean__true;
	  break;
	}
	prev = iter;
	iter = next;
      }
    }
  }
  f2cmutex__unlock(f2hash__write_cmutex(this, cause), cause);
  return key_was_removed;
}

f2ptr f2__hash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(hash, this);
  return f2bool__new(raw__hash__remove(cause, this, key));
}
def_pcfunk2(hash__remove, this, key,
	    "",
	    return f2__hash__remove(this_cause, this, key));


f2ptr f2__hash__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__lookup_keyvalue_pair assert failed: f2__hash__valid(this)");
  f2cmutex__lock(f2hash__write_cmutex(this, cause), cause);
  f2ptr fiber              = f2__this__fiber(cause);
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
      f2cmutex__unlock(f2hash__write_cmutex(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2cmutex__unlock(f2hash__write_cmutex(this, cause), cause);
  return nil;
}

boolean_t raw__hash__contains(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr keyvalue_pair = f2__hash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair != nil) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__hash__contains(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(hash, this);
  return raw__hash__contains(cause, this, key);
}
def_pcfunk2(hash__contains, this, key,
	    "",
	    return f2__hash__contains(this_cause, this, key));


f2ptr raw__hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__hash__valid(cause, this), nil, "f2__hash__lookup assert failed: f2__hash__valid(this)");
  f2ptr keyvalue_pair = f2__hash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}

f2ptr f2__hash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(hash, this);
  return raw__hash__lookup(cause, this, key);
}
def_pcfunk2(hash__lookup, this, slot_name,
	    "",
	    return f2__hash__lookup(this_cause, this, slot_name));


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
                            new_list = raw__cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(hash__slot_names, this,
	    "",
	    return f2__hash__slot_names(this_cause, this));

boolean_t raw__hash__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__hash__is_type(cause, that)) {
    return boolean__false;
  }
  f2ptr this__key_count    = f2__hash__key_count(cause, this);
  f2ptr that__key_count    = f2__hash__key_count(cause, that);
  u64   this__key_count__i = f2integer__i(this__key_count, cause);
  u64   that__key_count__i = f2integer__i(that__key_count, cause);
  if (this__key_count__i != that__key_count__i) {
    return boolean__false;
  }
  hash__iteration(cause, this, this__key, this__value,
		  f2ptr that__value = f2__hash__lookup(cause, that, this__key);
		  if (! f2__object__equals(cause, this__value, that__value)) {
		    return boolean__false;
		  }
		  );
  return boolean__true;
}

f2ptr f2__hash__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(hash, this);
  return f2bool__new(raw__hash__equals(cause, this, that));
}
def_pcfunk2(hash__equals, this, that,
	    "",
	    return f2__hash__equals(this_cause, this, that));

f2ptr f2__hash__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(hash, this);
  u64 hash_value = 1;
  hash__iteration(cause, this, key, value,
		  f2ptr key__equals_hash_value   = f2__object__equals_hash_value(cause, key);
		  f2ptr value__equals_hash_value = f2__object__equals_hash_value(cause, value);
		  if ((! raw__integer__is_type(cause, key__equals_hash_value)) ||
		      (! raw__integer__is_type(cause, value__equals_hash_value))) {
		    return f2larva__new(cause, 4, nil);
		  }
		  u64 key__equals_hash_value__i   = f2integer__i(key__equals_hash_value,   cause);
		  u64 value__equals_hash_value__i = f2integer__i(value__equals_hash_value, cause);
		  hash_value *= ((key__equals_hash_value__i   == 0) ? 1 : key__equals_hash_value__i);
		  hash_value *= ((value__equals_hash_value__i == 0) ? 1 : value__equals_hash_value__i);
		  );
  return f2integer__new(cause, hash_value);
}
def_pcfunk1(hash__equals_hash_value, this,
	    "",
	    return f2__hash__equals_hash_value(this_cause, this));

f2ptr raw__hash__as__frame(f2ptr cause, f2ptr this) {
  f2ptr frame = f2__frame__new(cause, nil);
  hash__iteration(cause, this, key, value,
		  f2__frame__add_var_value(cause, frame, key, value);
		  );
  return frame;
}

f2ptr f2__hash__as__frame(f2ptr cause, f2ptr this) {
  assert_argument_type(hash, this);
  return raw__hash__as__frame(cause, this);
}
def_pcfunk1(hash__as__frame, this,
	    "",
	    return f2__hash__as__frame(this_cause, this));


f2ptr f2hash__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2hash__primobject_type__new(cause);
  {char* slot_name = "slot_names";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__funk);}
  {char* slot_name = "add";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.add__funk);}
  {char* slot_name = "remove";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.remove__funk);}
  {char* slot_name = "lookup";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__funk);}
  {char* slot_name = "equals";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.equals__funk);}
  {char* slot_name = "equals_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.equals_hash_value__funk);}
  {char* slot_name = "as-frame";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_hash.as__frame__funk);}
  return this;
}

// **

void f2__primobject_hash__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  // hash
  
  initialize_primobject_6_slot__defragment__fix_pointers(hash, write_cmutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(hash__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__slot_names);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.add__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__add);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.add__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.remove__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__remove);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.remove__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__lookup);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.as__frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(hash__as__frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_hash.as__frame__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(hash);
  
}

void f2__primobject_hash__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // hash
  
  initialize_primobject_6_slot(hash, write_cmutex, key_count, bin_num_power, bin_array, hash_value_funk, equals_funk);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_hash.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(hash__new, this, hash_value_funk, equals_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.new__funk = never_gc(cfunk);}
  {char* symbol_str = "slot_names"; __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(hash__slot_names, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.slot_names__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_hash.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(hash__add, this, slot_name, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.add__funk = never_gc(cfunk);}
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_hash.remove__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__remove, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.remove__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__lookup, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_hash.equals__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__equals, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_hash.equals_hash_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__equals_hash_value, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "as-frame"; __funk2.globalenv.object_type.primobject.primobject_type_hash.as__frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(hash__as__frame, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_hash.as__frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(hash);
}

void f2__primobject_hash__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-hash", "", &f2__primobject_hash__reinitialize_globalvars, &f2__primobject_hash__defragment__fix_pointers);
  
  f2__primobject_hash__reinitialize_globalvars();
}

