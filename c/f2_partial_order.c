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

// partial_order_node

def_primobject_1_slot(partial_order_node, label);

f2ptr f2__partial_order_node__new(f2ptr cause, f2ptr label) {
  return f2partial_order_node__new(cause, label);
}
def_pcfunk1(partial_order_node__new, label,
	    "",
	    return f2__partial_order_node__new(this_cause, label));


f2ptr raw__partial_order_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "partial_order_node"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "label"),             f2__partial_order_node__label(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__partial_order_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(partial_order_node,   this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__partial_order_node__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(partial_order_node__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__partial_order_node__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2partial_order_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2partial_order_node__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_partial_order_node.terminal_print_with_frame__funk);}
  return this;
}




// **

void f2__partial_order__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // partial_order_node
  initialize_primobject_1_slot__defragment__fix_pointers(partial_order_node, label);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_partial_order_node.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(partial_order_node__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_partial_order_node.terminal_print_with_frame__funk);
  
}

void f2__partial_order__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // partial_order_node
  initialize_primobject_1_slot(partial_order_node, label);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_partial_order_node.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(partial_order_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_partial_order_node.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__partial_order__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "partial_order", "", &f2__partial_order__reinitialize_globalvars, &f2__partial_order__defragment__fix_pointers);
  
  f2__partial_order__reinitialize_globalvars();
}

