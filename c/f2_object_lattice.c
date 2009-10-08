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

// object_lattice

def_primobject_1_slot(object_lattice, lattice_node_hash);

f2ptr f2__object_lattice__new(f2ptr cause) {
  return f2object_lattice__new(cause, f2__hashtable__new(cause));
}
def_pcfunk0(object_lattice__new, return f2__object_lattice__new(this_cause));


// object_lattice_node

def_primobject_2_slot(object_lattice_node, object_image_frame, object_reference_leaf);

f2ptr f2__object_lattice_node__new(f2ptr cause, f2ptr object_image_frame, f2ptr object_reference_leaf) {
  return f2object_lattice_node__new(cause, object_image_frame, object_reference_leaf);
}
def_pcfunk2(object_lattice_node__new, object_image_frame, object_reference_leaf, return f2__object_lattice_node__new(this_cause, object_image_frame, object_reference_leaf));



// **

void f2__object_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "object_lattice", "", &f2__object_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __object_lattice__symbol      = new__symbol(cause, "object_lattice");
  __object_lattice_node__symbol = new__symbol(cause, "object_lattice_node");
}


void f2__object_lattice__initialize() {
  f2__object_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // object_lattice
  initialize_primobject_1_slot(object_lattice, lattice_node_hash);
  
  // object_lattice_node
  initialize_primobject_2_slot(object_lattice_node, object_image_frame, object_reference_leaf);
  
}

