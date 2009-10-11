// 
// Copyright (c) 2007-2009 Bo Morgan.
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

// object_lattice_node

def_primobject_2_slot(object_lattice_node, object_image_frame, object_reference_leaf);

f2ptr f2__object_lattice_node__new(f2ptr cause, f2ptr object_image_frame, f2ptr object_reference_leaf) {
  return f2object_lattice_node__new(cause, object_image_frame, object_reference_leaf);
}
def_pcfunk2(object_lattice_node__new, object_image_frame, object_reference_leaf, return f2__object_lattice_node__new(this_cause, object_image_frame, object_reference_leaf));


// object_lattice

def_primobject_1_slot(object_lattice, lattice_node_hash);

f2ptr f2__object_lattice__new(f2ptr cause) {
  return f2object_lattice__new(cause, f2__hash__new(cause, nil, nil));
}
def_pcfunk0(object_lattice__new, return f2__object_lattice__new(this_cause));

void object_lattice__scan_accessor_type_and_incorporate_leafs__helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber                        = raw__array__elt(cause, aux_data, 0);
  f2ptr accessor_type                = raw__array__elt(cause, aux_data, 1);
  f2ptr object                       = raw__array__elt(cause, aux_data, 2);
  f2ptr this                         = raw__array__elt(cause, aux_data, 3);
  f2ptr start_nanoseconds_since_1970 = raw__array__elt(cause, aux_data, 4);
  {
    f2__print(cause, fiber, slot_name);
    f2ptr slot_funk = f2__object__slot__type_funk(cause, object, accessor_type, slot_name);
    f2ptr slot_value = f2__force_funk_apply(cause, fiber, slot_funk, f2cons__new(cause, object, nil));
    f2__print(cause, fiber, slot_value);
    f2__object_lattice__scan_accessor_type_and_incorporate_leafs(cause, fiber, this, accessor_type, slot_value, start_nanoseconds_since_1970);
  }
}

f2ptr f2__object_lattice__scan_accessor_type_and_incorporate_leafs(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr accessor_type, f2ptr object, f2ptr start_nanoseconds_since_1970) {
  if (! object) {return nil;}
  if (! start_nanoseconds_since_1970) {start_nanoseconds_since_1970 = f2integer__new(cause, raw__nanoseconds_since_1970(cause));}
  u64 start_nanoseconds_since_1970__i = f2integer__i(start_nanoseconds_since_1970, cause);
  
  u64 object_creation_nanoseconds_since_1970 = raw__ptype__creation_nanoseconds_since_1970(cause, object);
  
  if (object_creation_nanoseconds_since_1970 >= start_nanoseconds_since_1970__i) {
    return nil;
  }
  
  f2ptr object_type_name = f2__object__type(cause, object);
  f2ptr object_type      = f2__lookup_type(cause, object_type_name);
  
  f2ptr lattice_node_hash = f2__object_lattice__lattice_node_hash(cause, this);
  
  f2ptr result = nil;
  f2ptr lattice_node = f2__hash__lookup(cause, fiber, lattice_node_hash, object);
  if (! lattice_node) {
    lattice_node = f2__object_lattice_node__new(cause, nil, object);
    f2__hash__add(cause, fiber, lattice_node_hash, object, lattice_node);
    
    {
      f2ptr aux_data = raw__array__new(cause, 5);
      raw__array__elt__set(cause, aux_data, 0, fiber);
      raw__array__elt__set(cause, aux_data, 1, accessor_type);
      raw__array__elt__set(cause, aux_data, 2, object);
      raw__array__elt__set(cause, aux_data, 3, this);
      raw__array__elt__set(cause, aux_data, 4, start_nanoseconds_since_1970);
      result = raw__primobject_type__type_funk__mapc_slot_names(cause, object_type, accessor_type, &object_lattice__scan_accessor_type_and_incorporate_leafs__helper, aux_data);
    }
  }
  return result;
}
def_pcfunk3(object_lattice__scan_accessor_type_and_incorporate_leafs, this, accessor_type, object, return f2__object_lattice__scan_accessor_type_and_incorporate_leafs(this_cause, simple_fiber, this, accessor_type, object, nil));


// **

void f2__object_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "object_lattice", "", &f2__object_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __object_lattice_node__symbol = new__symbol(cause, "object_lattice_node");
  __object_lattice__symbol      = new__symbol(cause, "object_lattice");
}


void f2__object_lattice__initialize() {
  f2__object_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // object_lattice_node
  initialize_primobject_2_slot(object_lattice_node, object_image_frame, object_reference_leaf);
  
  // object_lattice
  initialize_primobject_1_slot(object_lattice, lattice_node_hash);
  f2__primcfunk__init__3(object_lattice__scan_accessor_type_and_incorporate_leafs, this, accessor_type, object, "(cfunk defined in f2_object_lattice.c)");
  
}

