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

def_primobject_1_slot(matrix,
		      file_descriptor);

f2ptr raw__matrix__new(f2ptr cause, s64 file_descriptor) {
  if (__matrix__symbol == -1) {
    __matrix__symbol = new__symbol(cause, "matrix");
  }
  return f2matrix__new(cause,
			    f2integer__new(cause, file_descriptor));
}

f2ptr f2__matrix__new(f2ptr cause, f2ptr file_descriptor) {
  assert_argument_type(integer, file_descriptor);
  s64 file_descriptor__i = f2integer__i(file_descriptor, cause);
  return raw__matrix__new(cause, file_descriptor__i);
}
def_pcfunk1(matrix__new, file_descriptor,
	    "Returns a new matrix object for the given integral file_descriptor.",
	    return f2__matrix__new(this_cause, file_descriptor));




f2ptr raw__matrix__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "matrix"),
					       new__symbol(cause, "file_descriptor"),   f2__matrix__file_descriptor(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__matrix__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(matrix,          this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__matrix__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(matrix__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this matrix to the given terminal.",
	    return f2__matrix__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2matrix__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2matrix__primobject_type__new(cause);
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
  
  initialize_primobject_1_slot(matrix,
			       file_descriptor);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_matrix.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(matrix__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_matrix.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

