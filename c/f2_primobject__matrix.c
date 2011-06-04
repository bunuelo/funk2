// 
// Copyright (c) 2007-2011 Bo Morgan.
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

// matrix

def_primobject_4_slot(matrix,
		      mutate_cmutex,
		      zero_value,
		      column_row_ptypehash,
		      row_column_ptypehash);

f2ptr raw__matrix__new(f2ptr cause) {
  f2ptr mutate_cmutex        = f2__cmutex__new(cause);
  f2ptr zero_value           = f2integer__new(cause, 0);
  f2ptr column_row_ptypehash = nil;
  f2ptr row_column_ptypehash = nil;
  return f2matrix__new(cause,
		       mutate_cmutex,
		       zero_value,
		       column_row_ptypehash,
		       row_column_ptypehash);
}

f2ptr f2__matrix__new(f2ptr cause) {
  return raw__matrix__new(cause);
}
def_pcfunk0(matrix__new,
	    "Returns a new matrix object.",
	    return f2__matrix__new(this_cause));


f2ptr raw__matrix__elt(f2ptr cause, f2ptr this, f2ptr column, f2ptr row) {
  f2ptr column_row_ptypehash = f2__matrix__column_row_ptypehash(cause, this);
  if (column_row_ptypehash == nil) {
    return f2__matrix__zero_value(cause, this);
  }
  f2ptr value_column_ptypehash = raw__ptypehash__lookup(cause, column_row_ptypehash, row);
  if (value_column_ptypehash == nil) {
    return f2__matrix__zero_value(cause, this);
  }
  f2ptr value = raw__ptypehash__lookup(cause, value_column_ptypehash, column);
  if (value == nil) {
    return f2__matrix__zero_value(cause, this);
  }
  return value;
}

f2ptr f2__matrix__elt(f2ptr cause, f2ptr this, f2ptr column, f2ptr row) {
  assert_argument_type(matrix, this);
  return raw__matrix__elt(cause, this, column, row);
}
def_pcfunk3(matrix__elt, this, column, row,
	    "Returns the value for the given column and row of this matrix.",
	    return f2__matrix__elt(this_cause, this, column, row));


f2ptr raw__matrix__elt__set(f2ptr cause, f2ptr this, f2ptr column, f2ptr row, f2ptr value) {
  f2ptr mutate_cmutex = f2__matrix__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  {
    f2ptr column_row_ptypehash = f2__matrix__column_row_ptypehash(cause, this);
    if (column_row_ptypehash == nil) {
      column_row_ptypehash = f2__ptypehash__new(cause);
      f2__matrix__column_row_ptypehash__set(cause, this, column_row_ptypehash);
    }
    f2ptr row_column_ptypehash = f2__matrix__row_column_ptypehash(cause, this);
    if (row_column_ptypehash == nil) {
      row_column_ptypehash = f2__ptypehash__new(cause);
      f2__matrix__row_column_ptypehash__set(cause, this, row_column_ptypehash);
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
    raw__ptypehash__add(cause, value_column_ptypehash, column, value);
    raw__ptypehash__add(cause, value_row_ptypehash,    row,    value);
  }
  raw__cmutex__unlock(cause, mutate_cmutex);
  return nil;
}

f2ptr f2__matrix__elt__set(f2ptr cause, f2ptr this, f2ptr column, f2ptr row, f2ptr value) {
  assert_argument_type(matrix, this);
  return raw__matrix__elt__set(cause, this, column, row, value);
}
def_pcfunk4(matrix__elt__set, this, column, row, value,
	    "Sets the value for the given column and row of this matrix.",
	    return f2__matrix__elt__set(this_cause, this, column, row, value));


f2ptr raw__matrix__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"),    new__symbol(cause, "matrix"),
					       new__symbol(cause, "column_row_ptypehash"), f2__matrix__column_row_ptypehash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__matrix__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(matrix,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__matrix__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(matrix__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this matrix to the given terminal.",
	    return f2__matrix__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2matrix__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2matrix__primobject_type__new(cause);
  {char* slot_name = "elt";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__funk);}
  {char* slot_name = "elt";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__set__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_matrix.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__primobject__matrix__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __matrix__symbol = new__symbol(cause, "matrix");
}

void f2__primobject__matrix__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "matrix", "", &f2__primobject__matrix__reinitialize_globalvars);
  
  f2__primobject__matrix__reinitialize_globalvars();
  
  // matrix
  
  initialize_primobject_4_slot(matrix,
			       mutate_cmutex,
			       zero_value,
			       column_row_ptypehash,
			       row_column_ptypehash);
  
  {char* symbol_str = "elt"; __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(matrix__elt, this, column, row, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__funk = never_gc(cfunk);}
  {char* symbol_str = "elt-set"; __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(matrix__elt__set, this, column, row, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_matrix.elt__set__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_matrix.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(matrix__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_matrix.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

