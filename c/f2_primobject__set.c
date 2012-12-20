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
#include <stdio.h>

// set

def_primobject_4_slot(set, write_cmutex, key_count, bin_num_power, bin_array);

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
  f2ptr this = f2set__new(cause, f2cmutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, bin_num_power), bin_array);
  debug__assert(raw__set__valid(cause, this), nil, "raw__set__new assert failed: f2__set__valid(this)");
  return this;
}

#define set__default_start_bin_num_power 3
f2ptr f2__set__new(f2ptr cause, f2ptr elements) {
  assert_argument_type(conslist, elements);
  f2ptr this = raw__set__new(cause, set__default_start_bin_num_power);
  {
    f2ptr iter = elements;
    while (iter != nil) {
      f2ptr element = f2cons__car(iter, cause);
      raw__set__add(cause, this, element);
      iter = f2cons__cdr(iter, cause);
    }
  }
  return this;
}
def_pcfunk0_and_rest(set__new, elements,
		     "",
		     return f2__set__new(this_cause));

void raw__set__increase_size__thread_unsafe__debug(f2ptr cause, f2ptr this, char* source_filename, int source_line_number, char* source_funktion_name) {
  f2ptr bin_num_power        = f2set__bin_num_power(this, cause);
  u64   bin_num_power__i     = f2integer__i(bin_num_power, cause);
  f2ptr bin_array            = f2set__bin_array(this, cause);
  u64   new_bin_num_power__i = ((bin_num_power__i * 9) >> 3) + 1;
  f2ptr temp_set             = raw__set__new(cause, new_bin_num_power__i);
  {
    u64 bin_num = 1ull << bin_num_power__i;
    status("raw__set__increase_size__thread_unsafe: increasing bin_num from " u64__fstr " to " u64__fstr " [\'%s\':%d %s]", bin_num, (1ll << new_bin_num_power__i), source_filename, source_line_number, source_funktion_name);
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

f2ptr raw__set__add__debug(f2ptr cause, f2ptr this, f2ptr key, char* source_filename, int source_line_number, char* source_funktion_name) {
  debug__assert(raw__set__valid(cause, this), nil, "raw__set__add assert failed: f2__set__valid(this)");
  raw__cmutex__lock(cause, f2set__write_cmutex(this, cause));
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
      f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
      return f2bool__new(boolean__true);
    }
    key_iter = f2cons__cdr(key_iter, cause);
  }
  raw__array__elt__set(cause, bin_array, index, raw__cons__new(cause, key, raw__array__elt(cause, bin_array, index)));
  s64 key_count__i = f2integer__i(f2set__key_count(this, cause), cause);
  {
    key_count__i ++;
    f2set__key_count__set(this, cause, f2integer__new(cause, key_count__i));
  }
  if (key_count__i >= (1ll << bin_num_power__i)) {
    raw__set__increase_size__thread_unsafe__debug(cause, this, source_filename, source_line_number, source_funktion_name);
  }
  f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__set__add__debug(f2ptr cause, f2ptr this, f2ptr key, char* source_filename, int source_line_number, char* source_funktion_name) {
  assert_argument_type(set, this);
  return raw__set__add__debug(cause, this, key, source_filename, source_line_number, source_funktion_name);
}
def_pcfunk2(set__add, this, element,
	    "",
	    return f2__set__add(this_cause, this, element));

boolean_t raw__set__remove(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__remove assert failed: f2__set__valid(this)");
  boolean_t key_was_removed = boolean__false;
  raw__cmutex__lock(cause, f2set__write_cmutex(this, cause));
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
  f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
  return key_was_removed;
}

f2ptr f2__set__remove(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(set, this);
  return f2bool__new(raw__set__remove(cause, this, key));
}
def_pcfunk2(set__remove, this, key,
	    "",
	    return f2__set__remove(this_cause, this, key));


f2ptr raw__set__copy_from(f2ptr cause, f2ptr this, f2ptr that) {
  set__iteration(cause, that, element,
		 raw__set__add(cause, this, element));
  return nil;
}

f2ptr f2__set__copy_from(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(set, this);
  assert_argument_type(set, that);
  return raw__set__copy_from(cause, this, that);
}
def_pcfunk2(set__copy_from, this, that,
	    "",
	    return f2__set__copy_from(this_cause, this, that));


f2ptr raw__set__new_copy(f2ptr cause, f2ptr this) {
  f2ptr new_set = f2__set__new(cause, nil);
  raw__set__copy_from(cause, new_set, this);
  return new_set;
}

f2ptr f2__set__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(set, this);
  return raw__set__new_copy(cause, this);
}
def_pcfunk1(set__new_copy, this,
	    "",
	    return f2__set__new_copy(this_cause, this));


f2ptr raw__set__an_arbitrary_element(f2ptr cause, f2ptr this) {
  raw__cmutex__lock(cause, f2set__write_cmutex(this, cause));
  {
    f2ptr bin_array         = f2__set__bin_array(cause, this);
    u64   bin_array__length = raw__array__length(cause, bin_array);
    u64   index;
    for (index = 0; index < bin_array__length; index ++) {
      f2ptr key_iter = raw__array__elt(cause, bin_array, index);
      if (key_iter) {
	f2ptr key = f2cons__car(key_iter, cause);
	f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
	return key;
      }
    }
  }
  f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__set__an_arbitrary_element(f2ptr cause, f2ptr this) {
  assert_argument_type(set, this);
  return raw__set__an_arbitrary_element(cause, this);
}
def_pcfunk1(set__an_arbitrary_element, this,
	    "",
	    return f2__set__an_arbitrary_element(this_cause, this));


f2ptr raw__set__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__lookup assert failed: f2__set__valid(this)");
  raw__cmutex__lock(cause, f2set__write_cmutex(this, cause));
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
      f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
      return iter__key;
    }
    key_iter = f2cons__cdr(key_iter, cause);
  }
  f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__set__lookup(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(set, this);
  return raw__set__lookup(cause, this, key);
}
def_pcfunk2(set__lookup, this, element,
	    "",
	    return f2__set__lookup(this_cause, this, element));


boolean_t raw__set__contains(f2ptr cause, f2ptr this, f2ptr key) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__contains assert failed: f2__set__valid(this)");
  raw__cmutex__lock(cause, f2set__write_cmutex(this, cause));
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
      f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
      return boolean__true;
    }
    key_iter = f2cons__cdr(key_iter, cause);
  }
  f2cmutex__unlock(f2set__write_cmutex(this, cause), cause);
  return boolean__false;
}

f2ptr f2__set__contains(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(set, this);
  return f2bool__new(raw__set__contains(cause, this, key));
}
def_pcfunk2(set__contains, this, key,
	    "",
	    return f2__set__contains(this_cause, this, key));


f2ptr raw__set__elements(f2ptr cause, f2ptr this) {
  debug__assert(raw__set__valid(cause, this), nil, "f2__set__elements assert failed: f2__set__valid(this)");
  f2ptr new_list = nil;
  set__iteration(cause, this, element,
		 new_list = raw__cons__new(set__iteration__cause, element, new_list));
  return new_list;
}

f2ptr f2__set__elements(f2ptr cause, f2ptr this) {
  assert_argument_type(set, this);
  return raw__set__elements(cause, this);
}
def_pcfunk1(set__elements, this,
	    "",
	    return f2__set__elements(this_cause, this));

boolean_t raw__set__is_empty(f2ptr cause, f2ptr this) {
  f2ptr key_count    = f2__set__key_count(cause, this);
  u64   key_count__i = f2integer__i(key_count, cause);
  if (key_count__i == 0) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__set__is_empty(f2ptr cause, f2ptr this) {
  assert_argument_type(set, this);
  return f2bool__new(raw__set__is_empty(cause, this));
}
def_pcfunk1(set__is_empty, this,
	    "",
	    return f2__set__is_empty(this_cause, this));


f2ptr raw__set__union(f2ptr cause, f2ptr rest) {
  f2ptr set = f2__set__new(cause, nil);
  {
    f2ptr iter = rest;
    while (iter != nil) {
      f2ptr iter__set = f2__cons__car(cause, iter);
      assert_argument_type(set, iter__set);
      {
	set__iteration(cause, iter__set, element,
		       f2__set__add(cause, set, element);
		       );
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return set;
}

f2ptr f2__set__union(f2ptr cause, f2ptr rest) {
  assert_argument_type(conslist, rest);
  return raw__set__union(cause, rest);
}
def_pcfunk0_and_rest(set__union, rest,
		     "Returns a new set that represents the union of the given sets.",
		     return f2__set__union(this_cause, rest));


f2ptr raw__set__intersection(f2ptr cause, f2ptr rest) {
  f2ptr set  = nil;
  f2ptr iter = rest;
  if (rest == nil) {
    set = f2__set__new(cause, nil);
  } else {
    f2ptr first_set = f2__cons__car(cause, iter);
    assert_argument_type(set, first_set);
    set = f2__set__new_copy(cause, first_set);
    iter = f2__cons__cdr(cause, iter);
  }
  while (iter != nil) {
    f2ptr iter__set = f2__cons__car(cause, iter);
    assert_argument_type(set, iter__set);
    {
      set__iteration(cause, set, element,
		     if (! raw__set__contains(cause, iter__set, element)) {
		       f2__set__remove(cause, set, element);
		     }
		     );
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return set;
}

f2ptr f2__set__intersection(f2ptr cause, f2ptr rest) {
  assert_argument_type(conslist, rest);
  return raw__set__intersection(cause, rest);
}
def_pcfunk0_and_rest(set__intersection, rest,
		     "Returns a new set that represents the intersection of the given sets.",
		     return f2__set__intersection(this_cause, rest));


f2ptr raw__set__minus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr new_set = f2__set__new(cause, nil);
  set__iteration(cause, this, element,
		 if (! raw__set__contains(cause, that, element)) {
		   raw__set__add(cause, new_set, element);
		 }
		 );
  return new_set;
}

f2ptr f2__set__minus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(set, this);
  assert_argument_type(set, that);
  return raw__set__minus(cause, this, that);
}
def_pcfunk2(set__minus, this, that,
	    "Returns a new set that represents the subtraction of that set from this set.",
	    return f2__set__minus(this_cause, this, that));


f2ptr raw__set__plus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr new_set = f2__set__new(cause, nil);
  set__iteration(cause, this, element,
		 raw__set__add(cause, new_set, element);
		 );
  set__iteration(cause, that, element,
		 if (! raw__set__contains(cause, new_set, element)) {
		   raw__set__add(cause, new_set, element);
		 }
		 );
  return new_set;
}

f2ptr f2__set__plus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(set, this);
  assert_argument_type(set, that);
  return raw__set__plus(cause, this, that);
}
def_pcfunk2(set__plus, this, that,
	    "Returns a new set that represents the addition of that set to this set.",
	    return f2__set__plus(this_cause, this, that));


boolean_t raw__set__is_subset_of(f2ptr cause, f2ptr this, f2ptr that) {
  set__iteration(cause, this, element,
		 if (! raw__set__contains(cause, that, element)) {
		   return boolean__false;
		 }
		 );
  return boolean__true;
}

f2ptr f2__set__is_subset_of(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(set, this);
  assert_argument_type(set, that);
  return f2bool__new(raw__set__is_subset_of(cause, this, that));
}
def_pcfunk2(set__is_subset_of, this, that,
	    "Returns whether or not this set is a subset of that set.",
	    return f2__set__is_subset_of(this_cause, this, that));


f2ptr raw__set__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "set"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "elements"),          f2__set__elements(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__set__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(set,                  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__set__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(set__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__set__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2set__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2set__primobject_type__new(cause);
  {char* slot_name = "add";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk);}
  {char* slot_name = "remove";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.remove__funk);}
  {char* slot_name = "copy_from";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.copy_from__funk);}
  {char* slot_name = "new_copy";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.new_copy__funk);}
  {char* slot_name = "lookup";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk);}
  {char* slot_name = "contains";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.contains__funk);}
  {char* slot_name = "elements";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk);}
  {char* slot_name = "is_empty";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.is_empty__funk);}
  {char* slot_name = "union";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.union__funk);}
  {char* slot_name = "intersection";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.intersection__funk);}
  {char* slot_name = "minus";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.minus__funk);}
  {char* slot_name = "plus";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.plus__funk);}
  {char* slot_name = "is_subset_of";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.is_subset_of__funk);}
  {char* slot_name = "an_arbitrary_element";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.an_arbitrary_element__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_set.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__primobject_set__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  
  // -- initialize --
  
  // set
  
  initialize_primobject_4_slot__defragment__fix_pointers(set, write_cmutex, key_count, bin_num_power, bin_array);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.add__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__add);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.add__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.remove__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__remove);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.remove__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.copy_from__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__copy_from);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.copy_from__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.new_copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__new_copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.new_copy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.lookup__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__lookup);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.elements__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__elements);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.is_empty__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__is_empty);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.is_empty__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.union__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__union);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.union__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.intersection__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__intersection);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.intersection__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.minus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__minus);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.minus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.plus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__plus);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.plus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.is_subset_of__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__is_subset_of);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.is_subset_of__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.an_arbitrary_element__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__an_arbitrary_element);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.an_arbitrary_element__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(set__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_set.terminal_print_with_frame__funk);
  
}

void f2__primobject_set__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // set
  
  initialize_primobject_4_slot(set, write_cmutex, key_count, bin_num_power, bin_array);
  
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_set.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__add, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.add__funk = never_gc(cfunk);}
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_set.remove__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__remove, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.remove__funk = never_gc(cfunk);}
  {char* symbol_str = "copy_from"; __funk2.globalenv.object_type.primobject.primobject_type_set.copy_from__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__copy_from, this, that, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.copy_from__funk = never_gc(cfunk);}
  {char* symbol_str = "new_copy"; __funk2.globalenv.object_type.primobject.primobject_type_set.new_copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__new_copy, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.new_copy__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__lookup, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "contains"; __funk2.globalenv.object_type.primobject.primobject_type_set.contains__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__contains, this, key, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.contains__funk = never_gc(cfunk);}
  {char* symbol_str = "elements"; __funk2.globalenv.object_type.primobject.primobject_type_set.elements__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__elements, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.elements__funk = never_gc(cfunk);}
  {char* symbol_str = "is_empty"; __funk2.globalenv.object_type.primobject.primobject_type_set.is_empty__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__is_empty, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.is_empty__funk = never_gc(cfunk);}
  {char* symbol_str = "union"; __funk2.globalenv.object_type.primobject.primobject_type_set.union__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__union, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.union__funk = never_gc(cfunk);}
  {char* symbol_str = "intersection"; __funk2.globalenv.object_type.primobject.primobject_type_set.intersection__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__intersection, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.intersection__funk = never_gc(cfunk);}
  {char* symbol_str = "minus"; __funk2.globalenv.object_type.primobject.primobject_type_set.minus__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__minus, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.minus__funk = never_gc(cfunk);}
  {char* symbol_str = "plus"; __funk2.globalenv.object_type.primobject.primobject_type_set.plus__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__plus, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.plus__funk = never_gc(cfunk);}
  {char* symbol_str = "is_subset_of"; __funk2.globalenv.object_type.primobject.primobject_type_set.is_subset_of__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__is_subset_of, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.is_subset_of__funk = never_gc(cfunk);}
  {char* symbol_str = "an_arbitrary_element"; __funk2.globalenv.object_type.primobject.primobject_type_set.an_arbitrary_element__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(set__an_arbitrary_element, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.an_arbitrary_element__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_set.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(set__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_set.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject_set__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-set", "", &f2__primobject_set__reinitialize_globalvars, &f2__primobject_set__defragment__fix_pointers);
  
  f2__primobject_set__reinitialize_globalvars();
}

