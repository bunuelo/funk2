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

// ptypehash

def_primobject_4_slot(ptypehash,
		      creadwritelock,
		      key_count,
		      bin_num_power,
		      bin_array);

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

f2ptr raw__ptypehash__new(f2ptr cause, s64 bin_num_power__i) {
  f2ptr creadwritelock = f2creadwritelock__new(cause);
  f2ptr key_count      = f2integer__new(cause, 0);
  f2ptr bin_num_power  = f2integer__new(cause, bin_num_power__i);
  f2ptr bin_array      = raw__array__new(cause, 1ll << bin_num_power__i);
  f2ptr this = f2ptypehash__new(cause,
				creadwritelock,
				key_count,
				bin_num_power,
				bin_array);
  debug__assert(raw__ptypehash__valid(cause, this), nil, "raw__ptypehash__new assert failed: f2__ptypehash__valid(this)");
  return this;
}

#define ptypehash__default_start_bin_num_power 5
f2ptr f2__ptypehash__new(f2ptr cause) {return raw__ptypehash__new(cause, ptypehash__default_start_bin_num_power);}
def_pcfunk0(ptypehash__new,
	    "",
	    return f2__ptypehash__new(this_cause));

void raw__ptypehash__increase_size__thread_unsafe__debug(f2ptr cause, f2ptr this, char* source_filename, int source_line_number, char* source_funktion_name) {
  f2ptr bin_num_power        = f2ptypehash__bin_num_power(this, cause);
  u64   bin_num_power__i     = f2integer__i(bin_num_power, cause);
  f2ptr bin_array            = f2ptypehash__bin_array(this, cause);
  u64   new_bin_num_power__i = ((bin_num_power__i * 3) >> 1) + 1;
  f2ptr temp_ptypehash       = raw__ptypehash__new(cause, new_bin_num_power__i);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("raw__ptypehash__increase_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr " [\'%s\':%d %s]", bin_num, (1ll << new_bin_num_power__i), source_filename, source_line_number, source_funktion_name);
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

f2ptr raw__ptypehash__add__debug(f2ptr cause, f2ptr this, f2ptr key, f2ptr value, char* source_filename, int source_line_number, char* source_funktion_name) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__add assert failed: f2__ptypehash__valid(this)");
  f2creadwritelock__writelock(f2ptypehash__creadwritelock(this, cause), cause);
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
    keyvalue_pair = raw__cons__new(cause, key, value);
    raw__array__elt__set(cause, bin_array, index, raw__cons__new(cause, keyvalue_pair, raw__array__elt(cause, bin_array, index)));
    { // increase key count only if didn't already have this key.
      s64 key_count__i = f2integer__i(f2ptypehash__key_count(this, cause), cause);
      key_count__i ++;
      f2ptypehash__key_count__set(this, cause, f2integer__new(cause, key_count__i));
      if ((key_count__i << 1) >= (1ll << bin_num_power__i)) {
	raw__ptypehash__increase_size__thread_unsafe__debug(cause, this, source_filename, source_line_number, source_funktion_name);
      }
    }
  } else {
    f2cons__cdr__set(keyvalue_pair, cause, value);
  }
  f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__add__debug(f2ptr cause, f2ptr this, f2ptr key, f2ptr value, char* source_filename, int source_line_number, char* source_funktion_name) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__add__debug(cause, this, key, value, source_filename, source_line_number, source_funktion_name);
}
def_pcfunk3(ptypehash__add, this, slot_name, value,
	    "",
	    return f2__ptypehash__add(this_cause, this, slot_name, value));


boolean_t raw__ptypehash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__add assert failed: f2__ptypehash__valid(this)");
  boolean_t key_was_removed = boolean__false;
  f2creadwritelock__writelock(f2ptypehash__creadwritelock(this, cause), cause);
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
  f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
  return key_was_removed;
}

f2ptr f2__ptypehash__remove(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(ptypehash, this);
  return f2bool__new(raw__ptypehash__remove(cause, this, key));
}
def_pcfunk2(ptypehash__remove, this, key,
	    "",
	    return f2__ptypehash__remove(this_cause, this, key));


void raw__ptypehash__copy_from(f2ptr cause, f2ptr this, f2ptr that) {
  ptypehash__iteration(cause, that, key, value,
		       raw__ptypehash__add(cause, this, key, value));
}

f2ptr f2__ptypehash__copy_from(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(ptypehash, this);
  assert_argument_type(ptypehash, that);
  raw__ptypehash__copy_from(cause, this, that);
  return nil;
}
def_pcfunk2(ptypehash__copy_from, this, that,
	    "",
	    return f2__ptypehash__copy_from(this_cause, this, that));


f2ptr raw__ptypehash__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__lookup_keyvalue_pair assert failed: f2__ptypehash__valid(this)");
  //status("ptypehash (" u64__fstr ") attempting to lock write cmutex.", this);
  f2creadwritelock__readlock(f2ptypehash__creadwritelock(this, cause), cause);
  //status("ptypehash (" u64__fstr ") successfully locked write cmutex.", this);
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
    f2ptr keyvalue_pair__key = f2cons__car(keyvalue_pair,      cause);
    if (raw__eq(cause, key, keyvalue_pair__key)) {
      f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
      return keyvalue_pair;
    }
    keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
  }
  f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__lookup_keyvalue_pair(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__lookup_keyvalue_pair(cause, this, key);
}

f2ptr raw__ptypehash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__lookup assert failed: f2__ptypehash__valid(this)");
  f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair) {
    f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
    return retval;
  }
  return nil;
}

f2ptr f2__ptypehash__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__lookup(cause, this, key);
}
def_pcfunk2(ptypehash__lookup, this, slot_name,
	    "",
	    return f2__ptypehash__lookup(this_cause, this, slot_name));

boolean_t raw__ptypehash__contains(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr keyvalue_pair = f2__ptypehash__lookup_keyvalue_pair(cause, this, key);
  if (keyvalue_pair != nil) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__ptypehash__contains(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(ptypehash, this);
  return f2bool__new(raw__ptypehash__contains(cause, this, key));
}
def_pcfunk2(ptypehash__contains, this, key,
	    "Returns boolean true [t] if the ptypehash contains the key., \"primobject_type funktion (defined in f2_primobjects.c)\"",
	    return f2__ptypehash__contains(this_cause, this, key));


f2ptr raw__ptypehash__an_arbitrary_keyvalue_pair(f2ptr cause, f2ptr this) {
  f2creadwritelock__readlock(f2ptypehash__creadwritelock(this, cause), cause);
  {
    f2ptr bin_array         = f2__ptypehash__bin_array(cause, this);
    u64   bin_array__length = raw__array__length(cause, bin_array);
    u64   index;
    for (index = 0; index < bin_array__length; index ++) {
      f2ptr keyvalue_pair_iter = raw__array__elt(cause, bin_array, index);
      if (keyvalue_pair_iter) {
	f2ptr keyvalue_pair = f2cons__car(keyvalue_pair_iter, cause);
	f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
	return keyvalue_pair;
      }
    }
  }
  f2creadwritelock__unlock(f2ptypehash__creadwritelock(this, cause), cause);
  return nil;
}

f2ptr f2__ptypehash__an_arbitrary_keyvalue_pair(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__an_arbitrary_keyvalue_pair(cause, this);
}
def_pcfunk1(ptypehash__an_arbitrary_keyvalue_pair, this,
	    "Returns an arbitrary keyvalue pair from a ptypehash.",
	    return f2__ptypehash__an_arbitrary_keyvalue_pair(this_cause, this));


f2ptr raw__ptypehash__an_arbitrary_key(f2ptr cause, f2ptr this) {
  f2ptr keyvalue_pair = f2__ptypehash__an_arbitrary_keyvalue_pair(cause, this);
  if (! keyvalue_pair) {
    return nil;
  }
  f2ptr key = f2__cons__car(cause, keyvalue_pair);
  return key;
}

f2ptr f2__ptypehash__an_arbitrary_key(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__an_arbitrary_key(cause, this);
}
def_pcfunk1(ptypehash__an_arbitrary_key, this,
	    "Returns an arbitrary key from a ptypehash.",
	    return f2__ptypehash__an_arbitrary_key(this_cause, this));


f2ptr raw__ptypehash__an_arbitrary_value(f2ptr cause, f2ptr this) {
  f2ptr keyvalue_pair = f2__ptypehash__an_arbitrary_keyvalue_pair(cause, this);
  if (! keyvalue_pair) {
    return nil;
  }
  f2ptr value = f2__cons__cdr(cause, keyvalue_pair);
  return value;
}

f2ptr f2__ptypehash__an_arbitrary_value(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__an_arbitrary_value(cause, this);
}
def_pcfunk1(ptypehash__an_arbitrary_value, this,
	    "Returns an arbitrary value from a ptypehash.",
	    return f2__ptypehash__an_arbitrary_value(this_cause, this));


f2ptr raw__ptypehash__copy(f2ptr cause, f2ptr this) {
  f2ptr new_hash = f2__ptypehash__new(cause);
  ptypehash__iteration(cause, this, key, value, raw__ptypehash__add(cause, new_hash, key, value));
  return new_hash;
}

f2ptr f2__ptypehash__copy(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__copy(cause, this);
}
def_pcfunk1(ptypehash__copy, this,
	    "Returns a new copy of this ptypehash.",
	    return f2__ptypehash__copy(this_cause, this));


f2ptr raw__ptypehash__mapc_keys(f2ptr cause, f2ptr this, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__mapc_keys assert failed: f2__ptypehash__valid(this)");
  ptypehash__key__iteration(cause, this, key,
                            (*map_funk)(cause, key, aux_data));
  return nil;
}


f2ptr f2__ptypehash__keys(f2ptr cause, f2ptr this) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__keys assert failed: f2__ptypehash__valid(this)");
  f2ptr new_list = nil;
  ptypehash__key__iteration(cause, this, key,
                            new_list = raw__cons__new(cause, key, new_list));
  return new_list;
}
def_pcfunk1(ptypehash__keys, this,
	    "",
	    return f2__ptypehash__keys(this_cause, this));

f2ptr f2__ptypehash__values(f2ptr cause, f2ptr this) {
  debug__assert(raw__ptypehash__valid(cause, this), nil, "f2__ptypehash__values assert failed: f2__ptypehash__valid(this)");
  f2ptr new_list = nil;
  ptypehash__value__iteration(cause, this, value,
			      new_list = raw__cons__new(cause, value, new_list));
  return new_list;
}
def_pcfunk1(ptypehash__values, this,
	    "",
	    return f2__ptypehash__values(this_cause, this));

boolean_t raw__ptypehash__is_empty(f2ptr cause, f2ptr this) {
  f2ptr key_count    = f2__ptypehash__key_count(cause, this);
  u64   key_count__i = f2integer__i(key_count, cause);
  return (key_count__i == 0);
}

f2ptr f2__ptypehash__is_empty(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return f2bool__new(raw__ptypehash__is_empty(cause, this));
}
def_pcfunk1(ptypehash__is_empty, this,
	    "",
	    return f2__ptypehash__is_empty(this_cause, this));

f2ptr raw__ptypehash__as__frame(f2ptr cause, f2ptr this) {
  f2ptr new_frame = f2__frame__new(cause, nil);
  ptypehash__iteration(cause, this, key, value,
		       f2__frame__add_var_value(cause, new_frame, key, value);
		       );
  return new_frame;
}

f2ptr f2__ptypehash__as__frame(f2ptr cause, f2ptr this) {
  assert_argument_type(ptypehash, this);
  return raw__ptypehash__as__frame(cause, this);
}
def_pcfunk1(ptypehash__as__frame, this,
	    "",
	    return f2__ptypehash__as__frame(this_cause, this));


f2ptr raw__ptypehash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = raw__ptypehash__as__frame(cause, this);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "ptypehash"));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__ptypehash__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(ptypehash,            this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__ptypehash__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(ptypehash__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__ptypehash__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2ptypehash__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2ptypehash__primobject_type__new(cause);
  {char* slot_name = "contains";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.contains__funk);}
  {char* slot_name = "an_arbitrary_keyvalue_pair"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_keyvalue_pair__funk);}
  {char* slot_name = "an_arbitrary_key";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_key__funk);}
  {char* slot_name = "an_arbitrary_value";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_value__funk);}
  {char* slot_name = "copy";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy__funk);}
  {char* slot_name = "keys";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.keys__funk);}
  {char* slot_name = "values";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.values__funk);}
  {char* slot_name = "add";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__funk);}
  {char* slot_name = "remove";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__funk);}
  {char* slot_name = "copy_from";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy_from__funk);}
  {char* slot_name = "lookup";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__funk);}
  {char* slot_name = "is_empty";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.is_empty__funk);}
  {char* slot_name = "as-frame";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.as__frame__funk);}
  {char* slot_name = "terminal_print_with_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.terminal_print_with_frame__funk);}
  return this;
}

// **

void f2__primobject__ptypehash__preinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  reinitialize_primobject(ptypehash);

}

void f2__primobject__ptypehash__reinitialize_globalvars() {
  f2__primobject__ptypehash__preinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // ptypehash
  
  initialize_primobject_4_slot(ptypehash, creadwritelock, key_count, bin_num_power, bin_array);
  
  {char* symbol_str = "contains"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.contains__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptypehash__contains, this, key, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.contains__funk = never_gc(cfunk);}
  {char* symbol_str = "an_arbitrary_keyvalue_pair"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_keyvalue_pair__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__an_arbitrary_keyvalue_pair, this, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_keyvalue_pair__funk = never_gc(cfunk);}
  {char* symbol_str = "an_arbitrary_key"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_key__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__an_arbitrary_key, this, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_key__funk = never_gc(cfunk);}
  {char* symbol_str = "an_arbitrary_value"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__an_arbitrary_value, this, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_value__funk = never_gc(cfunk);}
  {char* symbol_str = "copy"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__copy, this, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy__funk = never_gc(cfunk);}
  
  {char* symbol_str = "keys"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.keys__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__keys, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.keys__funk = never_gc(cfunk);}
  {char* symbol_str = "values"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.values__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__values, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.values__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(ptypehash__add, this, slot_name, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__funk = never_gc(cfunk);}
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(ptypehash__remove, this, slot_name, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__funk = never_gc(cfunk);}
  {char* symbol_str = "copy_from"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy_from__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptypehash__copy_from, this, that, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy_from__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptypehash__lookup, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "is_empty"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.is_empty__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__is_empty, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.is_empty__funk = never_gc(cfunk);}
  {char* symbol_str = "as-frame"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.as__frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptypehash__as__frame, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.as__frame__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptypehash__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ptypehash.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

void f2__primobject__ptypehash__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // ptypehash
  
  initialize_primobject_4_slot__defragment__fix_pointers(ptypehash, creadwritelock, key_count, bin_num_power, bin_array);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_keyvalue_pair__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__an_arbitrary_keyvalue_pair);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_keyvalue_pair__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_key__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__an_arbitrary_key);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_key__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__an_arbitrary_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.an_arbitrary_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.keys__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__keys);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.keys__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.values__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__values);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.values__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__add);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.add__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__remove);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.remove__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy_from__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__copy_from);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.copy_from__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__lookup);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.lookup__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.is_empty__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__is_empty);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.is_empty__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.as__frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__as__frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.as__frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptypehash__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ptypehash.terminal_print_with_frame__funk);
}

void f2__primobject__ptypehash__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-ptypehash", "", &f2__primobject__ptypehash__reinitialize_globalvars, &f2__primobject__ptypehash__defragment__fix_pointers);
  
  f2__primobject__ptypehash__reinitialize_globalvars();
  
}

