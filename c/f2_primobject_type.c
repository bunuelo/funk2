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

// primobject_type

def_frame_object__global__2_slot(primobject_type, parents, documentation);

f2ptr f2__primobject_type__new(f2ptr cause, f2ptr parents) {
  f2ptr documentation = nil;
  return f2primobject_type__new(cause, parents, documentation);
}
def_pcfunk1(primobject_type__new, parents,
	    "create a new Funk2 object type.",
	    return f2__primobject_type__new(this_cause, parents));


f2ptr f2__primobject_type__add_slot_type(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr funkable) {
  assert_argument_type(frame,    this);
  assert_argument_type(symbol,   slot_type);
  assert_argument_type(symbol,   slot_name);
  assert_argument_type(funkable, funkable);
  return f2__frame__add_type_var_value(cause, this, slot_type, slot_name, funkable);
}
def_pcfunk4(primobject_type__add_slot_type, this, slot_type, slot_name, funkable,
	    "adds new type of slot funktion for an object type.",
	    return f2__primobject_type__add_slot_type(this_cause, this, slot_type, slot_name, funkable));


f2ptr f2__primobject_type__remove_slot_type(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  assert_argument_type(frame,  this);
  assert_argument_type(symbol, slot_type);
  assert_argument_type(symbol, slot_name);
  return f2__frame__remove_type_var(cause, this, slot_type, slot_name);
}
def_pcfunk3(primobject_type__remove_slot_type, this, slot_type, slot_name,
	    "removes current type of slot funktion for an object type.",
	    return f2__primobject_type__remove_slot_type(this_cause, this, slot_type, slot_name));


// lookup slot type

f2ptr f2__primobject_type__lookup_slot_type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  assert_argument_type(frame,  this);
  assert_argument_type(symbol, slot_type);
  assert_argument_type(symbol, slot_name);
  f2ptr this_binding = f2__frame__lookup_type_var_value(cause, this, slot_type, slot_name, nil);
  if (! this_binding) {
    f2ptr parents      = f2__frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "parents"), nil);
    f2ptr parents_iter = parents;
    while ((! this_binding) && parents_iter) {
      f2ptr parent      = f2cons__car(parents_iter, cause);
      f2ptr parent_type = f2__lookup_type(cause, parent);
      if (parent_type) {
	this_binding = f2__primobject_type__lookup_slot_type_funk(cause, parent_type, slot_type, slot_name);
      }
      parents_iter = f2cons__cdr(parents_iter, cause);
    }
  }
  return this_binding;
}
def_pcfunk3(primobject_type__lookup_slot_type_funk, this, slot_type, slot_name,
	    "lookup a primobject_type slot type funk.",
	    return f2__primobject_type__lookup_slot_type_funk(this_cause, this, slot_type, slot_name));

// scan slot names

f2ptr raw__primobject_type__type_funk__mapc_keys(f2ptr cause, f2ptr this, f2ptr type_name, void(* map_funk)(f2ptr cause, f2ptr slot_name, f2ptr aux_data), f2ptr aux_data) {
  assert_argument_type_or_nil(frame,  this);
  assert_argument_type(       symbol, type_name);
  if (! this) {
    return nil;
  }
  return raw__frame__type_var__mapc_keys(cause, this, type_name, map_funk, aux_data);
}

f2ptr f2__primobject_type__type_funk__keys(f2ptr cause, f2ptr this, f2ptr type_name) {
  assert_argument_type_or_nil(frame,  this);
  assert_argument_type(       symbol, type_name);
  if (! this) {
    return nil;
  }
  return f2__frame__type_var__keys(cause, this, type_name);
}
def_pcfunk2(primobject_type__type_funk__keys, this, type_name,
	    "get a list of type funk slot names.",
	    return f2__primobject_type__type_funk__keys(this_cause, this, type_name));

boolean_t raw__primobject_type__has_parent_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  if (! raw__primobject_type__is_type(cause, this)) {
    return boolean__false;
  }
  f2ptr parents = f2__primobject_type__parents(cause, this);
  {
    f2ptr parents_iter = parents;
    while (parents_iter) {
      f2ptr parent_name = f2__cons__car(cause, parents_iter);
      if (raw__symbol__eq(cause, parent_name, type_name)) {
	return boolean__true;
      }
      f2ptr parent_type = f2__lookup_type(cause, parent_name);
      if (raw__primobject_type__has_parent_type(cause, parent_type, type_name)) {
	return boolean__true;
      }
      parents_iter = f2__cons__cdr(cause, parents_iter);
    }
  }
  return boolean__false;
}

f2ptr f2__primobject_type__has_parent_type(f2ptr cause, f2ptr this, f2ptr type_name) {
  assert_argument_type(primobject_type, this);
  return f2bool__new(raw__primobject_type__has_parent_type(cause, this, type_name));
}
def_pcfunk2(primobject_type__has_parent_type, this, type_name,
	    "check if this primobject is type or has parent type of the type_name specified.",
	    return f2__primobject_type__has_parent_type(this_cause, this, type_name));


// **

void f2__primobject_type__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  // primobject_type
  
  init_frame_object__2_slot__defragment__fix_pointers(primobject_type, parents, documentation);
  
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__new);
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__add_slot_type);
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__remove_slot_type);
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__lookup_slot_type_funk);
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__type_funk__keys);
  f2__primcfunk__init__defragment__fix_pointers(primobject_type__has_parent_type);
}

void f2__primobject_type__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // primobject_type
  
  init_frame_object__2_slot(primobject_type, parents, documentation);
  
  f2__primcfunk__init__1(primobject_type__new,                   parents);
  f2__primcfunk__init__4(primobject_type__add_slot_type,         this, slot_type, slot_name, funkable);
  f2__primcfunk__init__3(primobject_type__remove_slot_type,      this, slot_type, slot_name);
  f2__primcfunk__init__3(primobject_type__lookup_slot_type_funk, this, slot_type, slot_name);
  f2__primcfunk__init__2(primobject_type__type_funk__keys,       this, slot_type);
  f2__primcfunk__init__2(primobject_type__has_parent_type,       this, type_name);
}

void f2__primobject_type__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_type", "", &f2__primobject_type__reinitialize_globalvars, &f2__primobject_type__defragment__fix_pointers);
  
  f2__primobject_type__reinitialize_globalvars();
}


