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


// circular_buffer

def_primobject_4_slot(circular_buffer, access_cmutex, start, end, bin_array);

f2ptr raw__circular_buffer__new_empty(f2ptr cause, u64 length) {
  return f2circular_buffer__new(cause, f2cmutex__new(cause), f2integer__new(cause, 0), f2integer__new(cause, 0), raw__array__new(cause, length));
}

f2ptr f2__circular_buffer__new(f2ptr cause) {
  return raw__circular_buffer__new_empty(cause, 8);
}
def_pcfunk0(circular_buffer__new,
	    "",
	    return f2__circular_buffer__new(this_cause));

f2ptr f2__circular_buffer__pop(f2ptr cause, f2ptr this) {
  raw__cmutex__lock(cause, f2circular_buffer__access_cmutex(this, cause));
  u64 raw_start = f2integer__i(f2circular_buffer__start(this, cause), cause);
  u64 raw_end   = f2integer__i(f2circular_buffer__end(this, cause), cause);
  if (raw_start == raw_end) {
    f2cmutex__unlock(f2circular_buffer__access_cmutex(this, cause), cause);
    return nil;
  }
  f2ptr bin_array = f2circular_buffer__bin_array(this, cause);
  u64   bin_array__length = raw__array__length(cause, bin_array);
  f2ptr elt = raw__array__elt(cause, bin_array, raw_start);
  raw_start ++;
  if (raw_start == bin_array__length) {
    raw_start = 0;
  }
  f2circular_buffer__start__set(this, cause, f2integer__new(cause, raw_start));
  f2cmutex__unlock(f2circular_buffer__access_cmutex(this, cause), cause);
  return elt;
}
def_pcfunk1(circular_buffer__pop, this,
	    "",
	    return f2__circular_buffer__pop(this_cause, this));

void raw__circular_buffer__double_size(f2ptr cause, f2ptr this) {
  u64   raw_start             = f2integer__i(f2circular_buffer__start(this, cause), cause);
  u64   raw_end               = f2integer__i(f2circular_buffer__end(this, cause), cause);
  f2ptr bin_array             = f2circular_buffer__bin_array(this, cause);
  u64   bin_array__length     = raw__array__length(cause, bin_array);
  u64   new_bin_array__length = bin_array__length << 1;
  f2ptr new_bin_array         = raw__array__new(cause, new_bin_array__length);
  u64 new_index = 0;
  u64 index     = raw_start;
  while (index != raw_end) {
    raw__array__elt__set(cause, new_bin_array, new_index, raw__array__elt(cause, bin_array, index));
    index ++;
    if (index == bin_array__length) {
      index = 0;
    }
    new_index ++;
  }
  f2circular_buffer__start__set(    this, cause, f2integer__new(cause, 0));
  f2circular_buffer__end__set(      this, cause, f2integer__new(cause, new_index));
  f2circular_buffer__bin_array__set(this, cause, new_bin_array);
}

f2ptr f2__circular_buffer__add(f2ptr cause, f2ptr this, f2ptr value) {
  raw__cmutex__lock(cause, f2circular_buffer__access_cmutex(this, cause));
  boolean_t just_resized;
  u64       raw_start;
  u64       raw_end;
  f2ptr     bin_array;
  u64       bin_array__length;
  u64       next_end;
  do {
    just_resized      = boolean__false;
    raw_start         = f2integer__i(f2circular_buffer__start(this, cause), cause);
    raw_end           = f2integer__i(f2circular_buffer__end(this, cause), cause);
    bin_array         = f2circular_buffer__bin_array(this, cause);
    bin_array__length = raw__array__length(cause, bin_array);
    next_end = raw_end + 1;
    if (next_end == bin_array__length) {
      next_end = 0;
    }
    if (next_end == raw_start) {
      raw__circular_buffer__double_size(cause, this);
      just_resized = boolean__true;
    }
  } while (just_resized);
  raw__array__elt__set(cause, bin_array, raw_end, value);
  f2circular_buffer__end__set(this, cause, f2integer__new(cause, next_end));
  f2cmutex__unlock(f2circular_buffer__access_cmutex(this, cause), cause);
  return nil;
}
def_pcfunk2(circular_buffer__add, this, value,
	    "",
	    return f2__circular_buffer__add(this_cause, this, value));

boolean_t raw__circular_buffer__is_empty(f2ptr cause, f2ptr this) {
  raw__cmutex__lock(cause, f2circular_buffer__access_cmutex(this, cause));
  f2ptr start = f2circular_buffer__start(this, cause);
  f2ptr end   = f2circular_buffer__end(this, cause);
  u64 raw_start = f2integer__i(start, cause);
  u64 raw_end   = f2integer__i(end, cause);
  f2cmutex__unlock(f2circular_buffer__access_cmutex(this, cause), cause);
  return (raw_start == raw_end);
}

f2ptr f2__circular_buffer__is_empty(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__circular_buffer__is_empty(cause, this));
}
def_pcfunk1(circular_buffer__is_empty, this,
	    "",
	    return f2__circular_buffer__is_empty(this_cause, this));

f2ptr f2circular_buffer__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2circular_buffer__primobject_type__new(cause);
  {char* slot_name = "pop";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.pop__funk);}
  {char* slot_name = "add";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.add__funk);}
  {char* slot_name = "is_empty"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.is_empty__funk);}
  return this;
}


// **

void f2__primobject_circular_buffer__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // circular_buffer
  
  initialize_primobject_4_slot__defragment__fix_pointers(circular_buffer, access_cmutex, start, end, bin_array);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(circular_buffer__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.pop__symbol);
  f2__primcfunk__init__defragment__fix_pointers(circular_buffer__pop);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.pop__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.add__symbol);
  f2__primcfunk__init__defragment__fix_pointers(circular_buffer__add);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.add__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.is_empty__symbol);
  f2__primcfunk__init__defragment__fix_pointers(circular_buffer__is_empty);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.is_empty__funk);
}

void f2__primobject_circular_buffer__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // circular_buffer
  
  initialize_primobject_4_slot(circular_buffer, access_cmutex, start, end, bin_array);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(circular_buffer__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.new__funk = never_gc(cfunk);}
  {char* symbol_str = "pop"; __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.pop__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(circular_buffer__pop, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.pop__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(circular_buffer__add, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.add__funk = never_gc(cfunk);}
  {char* symbol_str = "is_empty"; __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.is_empty__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(circular_buffer__is_empty, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_circular_buffer.is_empty__funk = never_gc(cfunk);}
}

void f2__primobject_circular_buffer__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_circular_buffer", "", &f2__primobject_circular_buffer__reinitialize_globalvars, &f2__primobject_circular_buffer__defragment__fix_pointers);
  
  f2__primobject_circular_buffer__reinitialize_globalvars();
}

