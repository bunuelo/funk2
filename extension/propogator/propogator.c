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
  f2ptr cell_set = f2__set__new(cause);
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
  return raw__propogator__add_cell(cause, this, cell);
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
  return raw__propogator__remove_cell(cause, this, cell);
}
export_cefunk2(propogator__remove_cell, this, cell, 0, "Adds a propogator_cell object to this propogator object.");


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


// propogator_process

def_ceframe3(propogator, propogator_process, input_ports, output_ports, execute_funk);

f2ptr raw__propogator_process__new(f2ptr cause, f2ptr execute_funk) {
  f2ptr input_ports  = nil;
  f2ptr output_ports = nil;
  return f2propogator_process__new(cause, input_ports, output_ports, execute_funk);
}

f2ptr f2__propogator_process__new(f2ptr cause, f2ptr execute_funk) {
  if (! raw__funkable__is_type(cause, execute_funk)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_process__new(cause);
}
export_cefunk0(propogator_process__new, 0, "Returns a new propogator_process object.");


// propogator_relation

def_ceframe1(propogator, propogator_relation, cell_port_frame);

f2ptr raw__propogator_relation__new(f2ptr cause) {
  f2ptr cell_port_frame = f2__frame__new(cause, nil);
  return f2propogator_relation__new(cause, cell_port_frame);
}

f2ptr f2__propogator_relation__new(f2ptr cause) {
  if (! raw__propogator__is_type(cause, )) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__propogator_relation__new(cause);
}
export_cefunk0(propogator_relation__new, 0, "Returns a new propogator_relation object.");




// **

f2ptr f2__propogator__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(propogator__core_extension__ping, 0, "");


f2ptr f2__propogator__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "propogator"),          f2__propogator_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_cell"),     f2__propogator_cell_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_process"),  f2__propogator_process_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "propogator_relation"), f2__propogator_relation_type__new(cause));
  status("propogator initialized.");
  return nil;
}
export_cefunk0(propogator__core_extension__initialize, 0, "");


f2ptr f2__propogator__core_extension__destroy(f2ptr cause) {
  status("propogator destroyed.");
  return nil;
}
export_cefunk0(propogator__core_extension__destroy, 0, "");


