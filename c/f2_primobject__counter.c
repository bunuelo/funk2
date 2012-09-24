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

// counter

def_primobject_4_slot(counter,
		      mutate_cmutex,
		      zero_value,
		      column_row_ptypehash,
		      row_column_ptypehash);

f2ptr raw__counter__new(f2ptr cause) {
  f2ptr mutate_cmutex        = f2__cmutex__new(cause);
  f2ptr zero_value           = f2integer__new(cause, 0);
  f2ptr column_row_ptypehash = nil;
  f2ptr row_column_ptypehash = nil;
  return f2counter__new(cause,
		       mutate_cmutex,
		       zero_value,
		       column_row_ptypehash,
		       row_column_ptypehash);
}

f2ptr f2__counter__new(f2ptr cause) {
  return raw__counter__new(cause);
}
def_pcfunk0(counter__new,
	    "Returns a new counter object.",
	    return f2__counter__new(this_cause));


f2ptr raw__counter__elt(f2ptr cause, f2ptr this, f2ptr column, f2ptr row) {
  f2ptr column_row_ptypehash = f2__counter__column_row_ptypehash(cause, this);
  if (column_row_ptypehash == nil) {
    return f2__counter__zero_value(cause, this);
  }
  f2ptr value_column_ptypehash = raw__ptypehash__lookup(cause, column_row_ptypehash, row);
  if (value_column_ptypehash == nil) {
    return f2__counter__zero_value(cause, this);
  }
  f2ptr value = raw__ptypehash__lookup(cause, value_column_ptypehash, column);
  if (value == nil) {
    return f2__counter__zero_value(cause, this);
  }
  return value;
}

f2ptr f2__counter__elt(f2ptr cause, f2ptr this, f2ptr column, f2ptr row) {
  assert_argument_type(counter, this);
  return raw__counter__elt(cause, this, column, row);
}
def_pcfunk3(counter__elt, this, column, row,
	    "Returns the value for the given column and row of this counter.",
	    return f2__counter__elt(this_cause, this, column, row));


f2ptr raw__counter__elt__set(f2ptr cause, f2ptr this, f2ptr column, f2ptr row, f2ptr value) {
  f2ptr zero_value  = f2__counter__zero_value(cause, this);
  f2ptr equals_zero = assert_value(f2__number__is_numerically_equal_to(cause, value, zero_value));
  if (equals_zero != nil) {
    value = nil;
  }
  f2ptr mutate_cmutex = f2__counter__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  {
    f2ptr column_row_ptypehash = f2__counter__column_row_ptypehash(cause, this);
    if (column_row_ptypehash == nil) {
      column_row_ptypehash = f2__ptypehash__new(cause);
      f2__counter__column_row_ptypehash__set(cause, this, column_row_ptypehash);
    }
    f2ptr row_column_ptypehash = f2__counter__row_column_ptypehash(cause, this);
    if (row_column_ptypehash == nil) {
      row_column_ptypehash = f2__ptypehash__new(cause);
      f2__counter__row_column_ptypehash__set(cause, this, row_column_ptypehash);
    }
    f2ptr value_column_ptypehash = raw__ptypehash__lookup(cause, column_row_ptypehash, row);
    if (value_column_ptypehash == nil) {
      value_column_ptypehash = f2__ptypehash__new(cause);
      raw__ptypehash__add(cause, column_row_ptypehash, row, value_column_ptypehash);
    }
    f2ptr value_row_ptypehash = raw__ptypehash__lookup(cause, row_column_ptypehash, column);
    if (value_row_ptypehash == nil) {
      value_row_ptypehash = f2__ptypehash__new(cause);
      raw__ptypehash__add(cause, row_column_ptypehash, column, value_row_ptypehash);
    }
    if (value != nil) {
      raw__ptypehash__add(cause, value_column_ptypehash, column, value);
      raw__ptypehash__add(cause, value_row_ptypehash,    row,    value);
    } else {
      raw__ptypehash__remove(cause, value_column_ptypehash, column);
      raw__ptypehash__remove(cause, value_row_ptypehash,    row);
      if (raw__ptypehash__is_empty(cause, value_column_ptypehash)) {
	raw__ptypehash__remove(cause, column_row_ptypehash, row);
	if (raw__ptypehash__is_empty(cause, column_row_ptypehash)) {
	  f2__counter__column_row_ptypehash__set(cause, this, nil);
	}
      }
      if (raw__ptypehash__is_empty(cause, value_row_ptypehash)) {
	raw__ptypehash__remove(cause, row_column_ptypehash, column);
	if (raw__ptypehash__is_empty(cause, row_column_ptypehash)) {
	  f2__counter__row_column_ptypehash__set(cause, this, nil);
	}
      }
    }
  }
  raw__cmutex__unlock(cause, mutate_cmutex);
  return nil;
}

f2ptr f2__counter__elt__set(f2ptr cause, f2ptr this, f2ptr column, f2ptr row, f2ptr value) {
  assert_argument_type(counter, this);
  return raw__counter__elt__set(cause, this, column, row, value);
}
def_pcfunk4(counter__elt__set, this, column, row, value,
	    "Sets the value for the given column and row of this counter.",
	    return f2__counter__elt__set(this_cause, this, column, row, value));


f2ptr raw__counter__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"),    new__symbol(cause, "counter"),
					       new__symbol(cause, "column_row_ptypehash"), f2__counter__column_row_ptypehash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__counter__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(counter,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__counter__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(counter__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this counter to the given terminal.",
	    return f2__counter__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2counter__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2counter__primobject_type__new(cause);
  {char* slot_name = "elt";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__funk);}
  {char* slot_name = "elt";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__set__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__primobject__counter__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // counter
  
  initialize_primobject_4_slot__defragment__fix_pointers(counter,
							 mutate_cmutex,
							 zero_value,
							 column_row_ptypehash,
							 row_column_ptypehash);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk);
  
}

void f2__primobject__counter__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // counter
  
  initialize_primobject_4_slot(counter,
			       mutate_cmutex,
			       zero_value,
			       column_row_ptypehash,
			       row_column_ptypehash);
  
  {char* symbol_str = "elt"; __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(counter__elt, this, column, row, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__funk = never_gc(cfunk);}
  {char* symbol_str = "elt-set"; __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(counter__elt__set, this, column, row, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.elt__set__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(counter__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject__counter__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "counter", "", &f2__primobject__counter__reinitialize_globalvars, &f2__primobject__counter__defragment__fix_pointers);
  
  f2__primobject__counter__reinitialize_globalvars();
}

