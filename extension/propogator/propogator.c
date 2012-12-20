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

#include "propogator.h"

// propogator

def_ceframe1(propogator, propogator, cell_set);

f2ptr raw__propogator__new(f2ptr cause) {
  f2ptr cell_set = f2__set__new(cause, nil);
  return f2propogator__new(cause, cell_set);
}

f2ptr f2__propogator__new(f2ptr cause) {
  return raw__propogator__new(cause);
}
export_cefunk0(propogator__new, 0, "Returns a new propogator object.");


void raw__propogator__add_cell(f2ptr cause, f2ptr this, f2ptr cell) {
  f2ptr cell_set = raw__propogator__cell_set(cause, this);
  raw__set__add(cause, cell_set, cell);
}

f2ptr f2__propogator__add_cell(f2ptr cause, f2ptr this, f2ptr cell) {
  if ((! raw__propogator__is_type(cause, this)) ||
      (! raw__propogator_cell__is_type(cause, cell))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__propogator__add_cell(cause, this, cell);
  return nil;
}
export_cefunk2(propogator__add_cell, this, cell, 0, "Adds a propogator_cell object to this propogator object.");


void raw__propogator__remove_cell(f2ptr cause, f2ptr this, f2ptr cell) {
  f2ptr cell_set = raw__propogator__cell_set(cause, this);
  raw__set__remove(cause, cell_set, cell);
}

f2ptr f2__propogator__remove_cell(f2ptr cause, f2ptr this, f2ptr cell) {
  if ((! raw__propogator__is_type(cause, this)) ||
      (! raw__propogator_cell__is_type(cause, cell))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__propogator__remove_cell(cause, this, cell);
  return nil;
}
export_cefunk2(propogator__remove_cell, this, cell, 0, "Adds a propogator_cell object to this propogator object.");


f2ptr f2__propogator_type__new_aux(f2ptr cause) {
  f2ptr this = f2__propogator_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_cell"),    f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator__add_cell")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_cell"), f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator__remove_cell")));}
  return this;
}



// propogator_cell

def_ceframe2(propogator, propogator_cell, propogator, value);

f2ptr raw__propogator_cell__new(f2ptr cause, f2ptr propogator) {
  f2ptr this = f2propogator_cell__new(cause, propogator, nil);
  raw__propogator__add_cell(cause, propogator, this);
  return this;
}

f2ptr f2__propogator_cell__new(f2ptr cause, f2ptr propogator) {
  if (! raw__propogator__is_type(cause, propogator)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_cell__new(cause, propogator);
}
export_cefunk1(propogator_cell__new, propogator, 0, "Returns a new propogator_cell object.");


f2ptr raw__propogator_cell__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this),
					       new__symbol(cause, "value"),             raw__propogator_cell__value(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__propogator_cell__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__propogator_cell__is_type(cause, this)) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_cell__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(propogator_cell__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__propogator_cell_type__new_aux(f2ptr cause) {
  f2ptr this = f2__propogator_cell_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator_cell__terminal_print_with_frame")));}
  return this;
}



// propogator_relation

def_ceframe2(propogator, propogator_relation, cell_port_frame, process_set);

f2ptr raw__propogator_relation__new(f2ptr cause) {
  f2ptr cell_port_frame = f2__frame__new(cause, nil);
  f2ptr process_set     = f2__set__new(cause, nil);
  return f2propogator_relation__new(cause, cell_port_frame, process_set);
}

f2ptr f2__propogator_relation__new(f2ptr cause) {
  return raw__propogator_relation__new(cause);
}
export_cefunk0(propogator_relation__new, 0, "Returns a new propogator_relation object.");


void raw__propogator_relation__add_cell_port(f2ptr cause, f2ptr this, f2ptr name, f2ptr cell) {
  f2ptr cell_port_frame = raw__propogator_relation__cell_port_frame(cause, this);
  raw__frame__add_var_value(cause, cell_port_frame, name, cell);
}

f2ptr f2__propogator_relation__add_cell_port(f2ptr cause, f2ptr this, f2ptr name, f2ptr cell) {
  if ((! raw__propogator_relation__is_type(cause, this)) ||
      (! raw__propogator_cell__is_type(cause, cell))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__propogator_relation__add_cell_port(cause, this, name, cell);
  return nil;
}
export_cefunk3(propogator_relation__add_cell_port, this, name, cell, 0, "Adds a named propogator_cell object to this propogator_relation.");



void raw__propogator_relation__add_process(f2ptr cause, f2ptr this, f2ptr process) {
  f2ptr process_set = raw__propogator_relation__process_set(cause, this);
  raw__set__add(cause, process_set, process);
}

f2ptr f2__propogator_relation__add_process(f2ptr cause, f2ptr this, f2ptr process) {
  if ((! raw__propogator_relation__is_type(cause, this)) ||
      (! raw__propogator_process__is_type(cause, process))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__propogator_relation__add_process(cause, this, process);
  return nil;
}
export_cefunk2(propogator_relation__add_process, this, process, 0, "Adds a propogator_process to this propogator_relation.");


void raw__propogator_relation__remove_process(f2ptr cause, f2ptr this, f2ptr process) {
  f2ptr process_set = raw__propogator_relation__process_set(cause, this);
  raw__set__remove(cause, process_set, process);
}

f2ptr f2__propogator_relation__remove_process(f2ptr cause, f2ptr this, f2ptr process) {
  if ((! raw__propogator_relation__is_type(cause, this)) ||
      (! raw__propogator_process__is_type(cause, process))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__propogator_relation__remove_process(cause, this, process);
  return nil;
}
export_cefunk2(propogator_relation__remove_process, this, process, 0, "Adds a propogator_process to this propogator_relation.");


f2ptr f2__propogator_relation_type__new_aux(f2ptr cause) {
  f2ptr this = f2__propogator_relation_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_cell_port"),  f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator_relation__add_cell_port")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_process"),    f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator_relation__add_process")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove_process"), f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator_relation__remove_process")));}
  return this;
}


// propogator_process

def_ceframe4(propogator, propogator_process, relation, input_ports, output_ports, execute_funk);

f2ptr raw__propogator_process__new(f2ptr cause, f2ptr relation, f2ptr input_ports, f2ptr output_ports, f2ptr execute_funk) {
  f2ptr this = f2propogator_process__new(cause, relation, input_ports, output_ports, execute_funk);
  raw__propogator_relation__add_process(cause, relation, this);
  return this;
}

f2ptr f2__propogator_process__new(f2ptr cause, f2ptr relation, f2ptr input_ports, f2ptr output_ports, f2ptr execute_funk) {
  if ((! raw__propogator_relation__is_type(cause, relation)) ||
      (! raw__funkable__is_type(cause, execute_funk)) ||
      (! raw__conslist__is_type(cause, input_ports)) ||
      (! raw__conslist__is_type(cause, output_ports))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_process__new(cause, relation, input_ports, output_ports, execute_funk);
}
export_cefunk4(propogator_process__new, relation, input_ports, output_ports, execute_funk, 0, "Returns a new propogator_process object.");


f2ptr raw__propogator_process__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), f2__object__type(cause, this),
					       new__symbol(cause, "input_ports"),       raw__propogator_process__input_ports(cause, this),
					       new__symbol(cause, "output_ports"),      raw__propogator_process__output_ports(cause, this),
					       new__symbol(cause, "execute_funk"),      raw__propogator_process__execute_funk(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__propogator_process__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__propogator_process__is_type(cause, this)) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_process__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(propogator_process__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__propogator_process_type__new_aux(f2ptr cause) {
  f2ptr this = f2__propogator_process_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "propogator"), new__symbol(cause, "propogator_process__terminal_print_with_frame")));}
  return this;
}






// **

f2ptr f2__propogator__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(propogator__core_extension__ping, 0, "");


f2ptr f2__propogator__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "propogator"),          f2__propogator_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_cell"),     f2__propogator_cell_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_relation"), f2__propogator_relation_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_process"),  f2__propogator_process_type__new_aux(cause));
  status("propogator initialized.");
  return nil;
}
export_cefunk0(propogator__core_extension__initialize, 0, "");


f2ptr f2__propogator__core_extension__destroy(f2ptr cause) {
  status("propogator destroyed.");
  return nil;
}
export_cefunk0(propogator__core_extension__destroy, 0, "");


