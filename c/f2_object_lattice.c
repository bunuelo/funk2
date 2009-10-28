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

void object_lattice__scan_and_incorporate_leafs__object_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber                        = raw__array__elt(cause, aux_data, 0);
  f2ptr object                       = raw__array__elt(cause, aux_data, 1);
  f2ptr this                         = raw__array__elt(cause, aux_data, 2);
  f2ptr start_nanoseconds_since_1970 = raw__array__elt(cause, aux_data, 3);
  {
    //printf("\nobject_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_funk = f2__object__slot__type_funk(cause, object, __funk2.globalenv.get__symbol, slot_name);
    f2ptr slot_value = f2__force_funk_apply(cause, fiber, slot_funk, f2cons__new(cause, object, nil));
    //f2__print(cause, fiber, slot_value);
    f2__object_lattice__scan_and_incorporate_leafs(cause, fiber, this, slot_value, start_nanoseconds_since_1970);
  }
}

void object_lattice__scan_and_incorporate_leafs__frame_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber                        = raw__array__elt(cause, aux_data, 0);
  f2ptr frame                        = raw__array__elt(cause, aux_data, 1);
  f2ptr this                         = raw__array__elt(cause, aux_data, 2);
  f2ptr start_nanoseconds_since_1970 = raw__array__elt(cause, aux_data, 3);
  {
    //printf("\nframe_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_value = f2__frame__lookup_var_value(cause, frame, slot_name, nil);
    //f2__print(cause, fiber, slot_value);
    f2__object_lattice__scan_and_incorporate_leafs(cause, fiber, this, slot_value, start_nanoseconds_since_1970);
  }
}

boolean_t raw__typedframe__is_type(f2ptr cause, f2ptr this) {
  return (raw__frame__is_type(cause, this) && raw__frame__check_has_type_slot(cause, this, __funk2.primobject__frame.variable__symbol, __funk2.globalenv.type__symbol));
}

f2ptr f2__typedframe__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__typedframe__is_type(cause, this));}

f2ptr f2__typedframe__type(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, __funk2.globalenv.type__symbol, nil);
}

boolean_t raw__object_lattice_primitive_data__is_type(f2ptr cause, f2ptr this) {
  return (! (raw__typedframe__is_type(cause, this) ||
	     raw__frame__is_type(     cause, this) ||
	     raw__primobject__is_type(cause, this) ||
	     raw__array__is_type(     cause, this)));
}

void f2__object_lattice__scan_and_incorporate_leafs__expand_node__primobject_slots(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr start_nanoseconds_since_1970) {
  f2ptr object_type_name = f2__object__type(cause, object);
  f2ptr object_type      = f2__lookup_type(cause, object_type_name);
  {
    f2ptr aux_data = raw__array__new(cause, 4);
    raw__array__elt__set(cause, aux_data, 0, fiber);
    raw__array__elt__set(cause, aux_data, 1, object);
    raw__array__elt__set(cause, aux_data, 2, this);
    raw__array__elt__set(cause, aux_data, 3, start_nanoseconds_since_1970);
    raw__primobject_type__type_funk__mapc_slot_names(cause, object_type, __funk2.globalenv.get__symbol, &object_lattice__scan_and_incorporate_leafs__object_slot_helper, aux_data);
  }
}

void f2__object_lattice__scan_and_incorporate_leafs__expand_node__frame_slots(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr frame, f2ptr start_nanoseconds_since_1970) {
  f2ptr aux_data = raw__array__new(cause, 4);
  raw__array__elt__set(cause, aux_data, 0, fiber);
  raw__array__elt__set(cause, aux_data, 1, frame);
  raw__array__elt__set(cause, aux_data, 2, this);
  raw__array__elt__set(cause, aux_data, 3, start_nanoseconds_since_1970);
  raw__frame__type_var__mapc_slot_names(cause, frame, __funk2.globalenv.get__symbol, &object_lattice__scan_and_incorporate_leafs__frame_slot_helper, aux_data);
}

void f2__object_lattice__scan_and_incorporate_leafs__expand_node__array_indices(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr array, f2ptr start_nanoseconds_since_1970) {
  u64 length = raw__array__length(cause, array);
  u64 index;
  for (index = 0; index < length; index ++) {
    f2ptr element = raw__array__elt(cause, array, index);
    f2__object_lattice__scan_and_incorporate_leafs(cause, fiber, this, element, start_nanoseconds_since_1970);
  }
}

void f2__object_lattice__scan_and_incorporate_leafs__expand_node(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr start_nanoseconds_since_1970) {
  if      (raw__typedframe__is_type(cause, object)) {f2__object_lattice__scan_and_incorporate_leafs__expand_node__primobject_slots(cause, fiber, this, object, start_nanoseconds_since_1970);}
  else if (raw__frame__is_type(     cause, object)) {f2__object_lattice__scan_and_incorporate_leafs__expand_node__frame_slots(     cause, fiber, this, object, start_nanoseconds_since_1970);}
  else if (raw__primobject__is_type(cause, object)) {f2__object_lattice__scan_and_incorporate_leafs__expand_node__primobject_slots(cause, fiber, this, object, start_nanoseconds_since_1970);}
  else if (raw__array__is_type(     cause, object)) {f2__object_lattice__scan_and_incorporate_leafs__expand_node__array_indices(   cause, fiber, this, object, start_nanoseconds_since_1970);}
}

f2ptr f2__object_lattice__scan_and_incorporate_leafs(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr start_nanoseconds_since_1970) {
  if (! object) {return nil;}
  if (raw__larva__is_type(cause, object)) {return nil;}
  if (! start_nanoseconds_since_1970) {start_nanoseconds_since_1970 = f2integer__new(cause, raw__nanoseconds_since_1970(cause));}
  u64 start_nanoseconds_since_1970__i = f2integer__i(start_nanoseconds_since_1970, cause);
  
  u64 object_creation_nanoseconds_since_1970 = raw__ptype__creation_nanoseconds_since_1970(cause, object);
  
  if (object_creation_nanoseconds_since_1970 >= start_nanoseconds_since_1970__i) {
    return nil;
  }
  
  f2ptr lattice_node_hash = f2__object_lattice__lattice_node_hash(cause, this);
  
  f2ptr lattice_node = f2__hash__lookup(cause, fiber, lattice_node_hash, object);
  if (! lattice_node) {
    lattice_node = f2__object_lattice_node__new(cause, nil, object);
    f2__hash__add(cause, fiber, lattice_node_hash, object, lattice_node);
    
    f2__object_lattice__scan_and_incorporate_leafs__expand_node(cause, fiber, this, object, start_nanoseconds_since_1970);
  }
  return nil;
}
def_pcfunk2(object_lattice__scan_and_incorporate_leafs, this, object, return f2__object_lattice__scan_and_incorporate_leafs(this_cause, simple_fiber, this, object, nil));


// scan_leafs

void object_lattice__scan_leafs__relation_scan(f2ptr cause, f2ptr fiber, f2ptr funk, f2ptr object, f2ptr this, f2ptr start_nanoseconds_since_1970, f2ptr slot_name, f2ptr slot_value) {
  
}

void object_lattice__scan_leafs__object_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber                        = raw__array__elt(cause, aux_data, 0);
  f2ptr node_funk                    = raw__array__elt(cause, aux_data, 1);
  f2ptr relation_funk                = raw__array__elt(cause, aux_data, 2);
  f2ptr object                       = raw__array__elt(cause, aux_data, 3);
  f2ptr this                         = raw__array__elt(cause, aux_data, 4);
  f2ptr start_nanoseconds_since_1970 = raw__array__elt(cause, aux_data, 5);
  {
    //printf("\nobject_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_funk = f2__object__slot__type_funk(cause, object, __funk2.globalenv.get__symbol, slot_name);
    f2ptr slot_value = f2__force_funk_apply(cause, fiber, slot_funk, f2cons__new(cause, object, nil));
    
    object_lattice__scan_leafs__relation_scan(cause, fiber, node_funk, relation_funk, object, this, start_nanoseconds_since_1970, slot_name, slot_value);
    
    //f2__print(cause, fiber, slot_value);
    f2__object_lattice__scan_leafs(cause, fiber, this, slot_value, node_funk, relation_funk, start_nanoseconds_since_1970);
  }
}

void object_lattice__scan_leafs__frame_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber                        = raw__array__elt(cause, aux_data, 0);
  f2ptr node_funk                    = raw__array__elt(cause, aux_data, 1);
  f2ptr relation_funk                = raw__array__elt(cause, aux_data, 2);
  f2ptr frame                        = raw__array__elt(cause, aux_data, 3);
  f2ptr this                         = raw__array__elt(cause, aux_data, 4);
  f2ptr start_nanoseconds_since_1970 = raw__array__elt(cause, aux_data, 5);
  {
    //printf("\nframe_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_value = f2__frame__lookup_var_value(cause, frame, slot_name, nil);
    //f2__print(cause, fiber, slot_value);
    f2__object_lattice__scan_leafs(cause, fiber, this, slot_value, node_funk, relation_funk, start_nanoseconds_since_1970);
  }
}

void f2__object_lattice__scan_leafs__expand_node__primobject_slots(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr node_funk, f2ptr relation_funk, f2ptr start_nanoseconds_since_1970) {
  f2ptr object_type_name = f2__object__type(cause, object);
  f2ptr object_type      = f2__lookup_type(cause, object_type_name);
  {
    f2ptr aux_data = raw__array__new(cause, 6);
    raw__array__elt__set(cause, aux_data, 0, fiber);
    raw__array__elt__set(cause, aux_data, 1, node_funk);
    raw__array__elt__set(cause, aux_data, 2, relation_funk);
    raw__array__elt__set(cause, aux_data, 3, object);
    raw__array__elt__set(cause, aux_data, 4, this);
    raw__array__elt__set(cause, aux_data, 5, start_nanoseconds_since_1970);
    raw__primobject_type__type_funk__mapc_slot_names(cause, object_type, __funk2.globalenv.get__symbol, &object_lattice__scan_leafs__object_slot_helper, aux_data);
  }
}

void f2__object_lattice__scan_leafs__expand_node__frame_slots(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr frame, f2ptr node_funk, f2ptr relation_funk, f2ptr start_nanoseconds_since_1970) {
  f2ptr aux_data = raw__array__new(cause, 5);
  raw__array__elt__set(cause, aux_data, 0, fiber);
  raw__array__elt__set(cause, aux_data, 1, node_funk);
  raw__array__elt__set(cause, aux_data, 2, relation_funk);
  raw__array__elt__set(cause, aux_data, 3, frame);
  raw__array__elt__set(cause, aux_data, 4, this);
  raw__array__elt__set(cause, aux_data, 5, start_nanoseconds_since_1970);
  raw__frame__type_var__mapc_slot_names(cause, frame, __funk2.globalenv.get__symbol, &object_lattice__scan_leafs__frame_slot_helper, aux_data);
}

void f2__object_lattice__scan_leafs__expand_node__array_indices(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr array, f2ptr node_funk, f2ptr relation_funk, f2ptr start_nanoseconds_since_1970) {
  u64 length = raw__array__length(cause, array);
  u64 index;
  for (index = 0; index < length; index ++) {
    f2ptr element = raw__array__elt(cause, array, index);
    f2__object_lattice__scan_leafs(cause, fiber, this, element, node_funk, relation_funk, start_nanoseconds_since_1970);
  }
}

void f2__object_lattice__scan_leafs__expand_node(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr node_funk, f2ptr relation_funk, f2ptr start_nanoseconds_since_1970) {
  if      (raw__typedframe__is_type(cause, object)) {f2__object_lattice__scan_leafs__expand_node__primobject_slots(cause, fiber, this, object, node_funk, relation_funk, start_nanoseconds_since_1970);}
  else if (raw__frame__is_type(     cause, object)) {f2__object_lattice__scan_leafs__expand_node__frame_slots(     cause, fiber, this, object, node_funk, relation_funk, start_nanoseconds_since_1970);}
  else if (raw__primobject__is_type(cause, object)) {f2__object_lattice__scan_leafs__expand_node__primobject_slots(cause, fiber, this, object, node_funk, relation_funk, start_nanoseconds_since_1970);}
  else if (raw__array__is_type(     cause, object)) {f2__object_lattice__scan_leafs__expand_node__array_indices(   cause, fiber, this, object, node_funk, relation_funk, start_nanoseconds_since_1970);}
}

f2ptr f2__object_lattice__scan_leafs(f2ptr cause, f2ptr fiber, f2ptr this, f2ptr object, f2ptr node_funk, f2ptr relation_funk, f2ptr start_nanoseconds_since_1970) {
  if (! object) {return nil;}
  if (raw__larva__is_type(cause, object)) {return nil;}
  if (! start_nanoseconds_since_1970) {start_nanoseconds_since_1970 = f2integer__new(cause, raw__nanoseconds_since_1970(cause));}
  u64 start_nanoseconds_since_1970__i = f2integer__i(start_nanoseconds_since_1970, cause);
  
  u64 object_creation_nanoseconds_since_1970 = raw__ptype__creation_nanoseconds_since_1970(cause, object);
  
  if (object_creation_nanoseconds_since_1970 >= start_nanoseconds_since_1970__i) {
    return nil;
  }
  
  f2ptr lattice_node_hash = f2__object_lattice__lattice_node_hash(cause, this);
  
  f2ptr lattice_node = f2__hash__lookup(cause, fiber, lattice_node_hash, object);
  if (! lattice_node) {
    lattice_node = f2__object_lattice_node__new(cause, nil, object);
    f2__hash__add(cause, fiber, lattice_node_hash, object, lattice_node);
    
    if (node_funk) {
      f2__force_funk_apply(cause, fiber, node_funk, f2cons__new(cause, object, nil));
    }
    
    f2__object_lattice__scan_leafs__expand_node(cause, fiber, this, object, node_funk, relation_funk, start_nanoseconds_since_1970);
  }
  return nil;
}
def_pcfunk4(object_lattice__scan_leafs, this, object, node_funk, relation_funk, return f2__object_lattice__scan_leafs(this_cause, simple_fiber, this, object, node_funk, relation_funk, nil));


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
  f2__primcfunk__init__2(object_lattice__scan_and_incorporate_leafs, this, object,                           "(cfunk defined in f2_object_lattice.c)");
  f2__primcfunk__init__4(object_lattice__scan_leafs,                 this, object, node_funk, relation_funk, "executes node_funk for every lattice node in object, while executing relation_funk for every semantic-triple relation (either or both can be nil).  (cfunk defined in f2_object_lattice.c)");
  
}

