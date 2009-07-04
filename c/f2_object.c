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

f2ptr f2__object__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  ptype_t ptype = f2ptype__raw(this, cause);
  switch (ptype) {
  case ptype_free_memory:
  case ptype_newly_allocated:
    error(nil, "shouldn't ever see this object ptype.");
    return nil;
  case ptype_integer:  return f2__integer__slot__get_funk(cause, this, slot);
  case ptype_double:   return f2__double__slot__get_funk(cause, this, slot);
  case ptype_float:    return f2__float__slot__get_funk(cause, this, slot);
  case ptype_pointer:  return f2__pointer__slot__get_funk(cause, this, slot);
  case ptype_gfunkptr: return f2__gfunkptr__slot__get_funk(cause, this, slot);
  case ptype_mutex:    return f2__mutex__slot__get_funk(cause, this, slot);
  case ptype_char:     return f2__char__slot__get_funk(cause, this, slot);
  case ptype_string:   return f2__string__slot__get_funk(cause, this, slot);
  case ptype_symbol:   return f2__symbol__slot__get_funk(cause, this, slot);
  case ptype_chunk:    return f2__chunk__slot__get_funk(cause, this, slot);
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      //printf("\nprimobject_type_name: "); f2__print(cause, primobject_type_name); fflush(stdout);
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	printf("\nprimobject_type = nil\n"); fflush(stdout);
	return nil;
      }
      //printf("\nprimobject_type: "); f2__print(cause, primobject_type); fflush(stdout);
      return f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	return f2__simple_array__slot__get_funk(cause, this, slot);
      } else if (ptype == ptype_traced_array) {
	return f2__traced_array__slot__get_funk(cause, this, slot);
      }
      return f2larva__new(cause, 1);
    }
  case ptype_larva:
    return f2__larva__slot__get_funk(cause, this, slot);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(object__slot__get_funk, this, slot, return f2__object__slot__get_funk(this_cause, this, slot));

f2ptr f2__object__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  ptype_t ptype = f2ptype__raw(this, cause);
  switch (ptype) {
  case ptype_free_memory:
  case ptype_newly_allocated:
    error(nil, "shouldn't ever see this object ptype.");
    return nil;
  case ptype_integer:  return f2__integer__slot__set_funk(cause, this, slot);
  case ptype_double:   return f2__double__slot__set_funk(cause, this, slot);
  case ptype_float:    return f2__float__slot__set_funk(cause, this, slot);
  case ptype_pointer:  return f2__pointer__slot__set_funk(cause, this, slot);
  case ptype_gfunkptr: return f2__gfunkptr__slot__set_funk(cause, this, slot);
  case ptype_mutex:    return f2__mutex__slot__set_funk(cause, this, slot);
  case ptype_char:     return f2__char__slot__set_funk(cause, this, slot);
  case ptype_string:   return f2__string__slot__set_funk(cause, this, slot);
  case ptype_symbol:   return f2__symbol__slot__set_funk(cause, this, slot);
  case ptype_chunk:    return f2__chunk__slot__set_funk(cause, this, slot);
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      f2ptr primobject_type      = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	return nil;
      }
      return f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	return f2__simple_array__slot__set_funk(cause, this, slot);
      } else if (ptype == ptype_traced_array) {
	return f2__traced_array__slot__set_funk(cause, this, slot);
      }
      return f2larva__new(cause, 1);
    }
  case ptype_larva:
    return f2__larva__slot__set_funk(cause, this, slot);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(object__slot__set_funk, this, slot, return f2__object__slot__set_funk(this_cause, this, slot));

f2ptr f2__object__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  ptype_t ptype = f2ptype__raw(this, cause);
  switch (ptype) {
  case ptype_free_memory:
  case ptype_newly_allocated:
    error(nil, "shouldn't ever see this object ptype.");
    return nil;
  case ptype_integer:  return f2__integer__slot__execute_funk(cause, this, slot);
  case ptype_double:   return f2__double__slot__execute_funk(cause, this, slot);
  case ptype_float:    return f2__float__slot__execute_funk(cause, this, slot);
  case ptype_pointer:  return f2__pointer__slot__execute_funk(cause, this, slot);
  case ptype_gfunkptr: return f2__gfunkptr__slot__execute_funk(cause, this, slot);
  case ptype_mutex:    return f2__mutex__slot__execute_funk(cause, this, slot);
  case ptype_char:     return f2__char__slot__execute_funk(cause, this, slot);
  case ptype_string:   return f2__string__slot__execute_funk(cause, this, slot);
  case ptype_symbol:   return f2__symbol__slot__execute_funk(cause, this, slot);
  case ptype_chunk:    return f2__chunk__slot__execute_funk(cause, this, slot);
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      f2ptr primobject_type      = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	return nil;
      }
      return f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	return f2__simple_array__slot__execute_funk(cause, this, slot);
      } else if (ptype == ptype_traced_array) {
	return f2__traced_array__slot__execute_funk(cause, this, slot);
      }
      return f2larva__new(cause, 1);
    }
  case ptype_larva:
    return f2__larva__slot__execute_funk(cause, this, slot);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(object__slot__execute_funk, this, slot, return f2__object__slot__execute_funk(this_cause, this, slot));

// **

void f2__object__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_object_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__object__initialize() {
  //f2ptr cause = initial_cause(); //f2_object_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__2(object__slot__get_funk,     this, slot, "returns the slot get funk for the object, i.e. an accessor (e.g. value).");
  f2__primcfunk__init__2(object__slot__set_funk,     this, slot, "returns the slot set funk for the object, i.e. a mutator (e.g. value-set).");
  f2__primcfunk__init__2(object__slot__execute_funk, this, slot, "returns the slot execute funk for the object, i.e. a general executor (e.g. print-value).");
  
  resume_gc();
  try_gc();
}

