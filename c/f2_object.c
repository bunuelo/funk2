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

f2ptr f2__object__type(f2ptr cause, f2ptr this) {
  if (! this) {
    return nil;
  }
  ptype_t ptype = f2ptype__raw(this, cause);
  switch (ptype) {
  case ptype_free_memory:
  case ptype_newly_allocated:
    error(nil, "shouldn't ever see this object ptype.");
    return nil;
  case ptype_integer:
    return f2symbol__new(cause, strlen("integer"), (u8*)"integer");
  case ptype_double:
    return f2symbol__new(cause, strlen("double"), (u8*)"double");
  case ptype_float:
    return f2symbol__new(cause, strlen("float"), (u8*)"float");
  case ptype_pointer:
    return f2symbol__new(cause, strlen("pointer"), (u8*)"pointer");
  case ptype_gfunkptr:
    return f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr");
  case ptype_mutex:
    return f2symbol__new(cause, strlen("mutex"), (u8*)"mutex");
  case ptype_char:
    return f2symbol__new(cause, strlen("char"), (u8*)"char");
  case ptype_string:
    return f2symbol__new(cause, strlen("string"), (u8*)"string");
  case ptype_symbol:
    return f2symbol__new(cause, strlen("symbol"), (u8*)"symbol");
  case ptype_chunk:
    return f2symbol__new(cause, strlen("chunk"), (u8*)"chunk");
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      //printf("\nprimobject_type_name: "); f2__print(cause, primobject_type_name); fflush(stdout);
      if (primobject_type_name == __funk2.primobject__frame.frame__symbol) {
	f2ptr test_get_type = f2__frame__lookup_var_value(cause, this, __funk2.globalenv.type__symbol, nil);
	if (test_get_type) {
	  primobject_type_name = test_get_type;
	}
      }
      return primobject_type_name;
    } else {
      if (ptype == ptype_simple_array) {
	return f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array");
      } else if (ptype == ptype_traced_array) {
	return f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array");
      }
    }
    return f2larva__new(cause, 1);
  case ptype_larva:
    return f2symbol__new(cause, strlen("larva"), (u8*)"larva");
  }
  return f2larva__new(cause, 1);
}
def_pcfunk1(object__type, this, return f2__object__type(this_cause, this));

f2ptr f2__object__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (! this) {
    return nil;
  }
  ptype_t ptype = f2ptype__raw(this, cause);
  switch (ptype) {
  case ptype_free_memory:
  case ptype_newly_allocated:
    error(nil, "shouldn't ever see this object ptype.");
    return nil;
  case ptype_integer: {
    f2ptr result = f2__integer__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("integer"), (u8*)"integer"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_double: {
    f2ptr result = f2__double__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("double"), (u8*)"double"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_float: {
    f2ptr result = f2__float__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("float"), (u8*)"float"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_pointer: {
    f2ptr result = f2__pointer__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("pointer"), (u8*)"pointer"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_gfunkptr: {
    f2ptr result = f2__gfunkptr__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_mutex: {
    f2ptr result = f2__mutex__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("mutex"), (u8*)"mutex"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_char: {
    f2ptr result = f2__char__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("char"), (u8*)"char"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_string: {
    f2ptr result = f2__string__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("string"), (u8*)"string"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_symbol:{
    f2ptr result = f2__symbol__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("symbol"), (u8*)"symbol"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_chunk: {
    f2ptr result = f2__chunk__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("chunk"), (u8*)"chunk"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  case ptype_simple_array:
  case ptype_traced_array: {
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      //printf("\nprimobject_type_name: "); f2__print(cause, primobject_type_name); fflush(stdout);
      if (primobject_type_name == __funk2.primobject__frame.frame__symbol) {
	f2ptr test_get_type = f2__frame__lookup_var_value(cause, this, __funk2.globalenv.type__symbol, nil);
	if (test_get_type) {
	  primobject_type_name = test_get_type;
	}
      }
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      //printf("\nprimobject_type = "); fflush(stdout);
      //f2__print(cause, primobject_type); fflush(stdout);
      //printf("\n"); fflush(stdout);
      if (primobject_type == nil) {
	printf("\nprimobject_type = nil\n"); fflush(stdout);
	return nil;
      }
      //printf("\nprimobject_type: "); f2__print(cause, primobject_type); fflush(stdout);
      return f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    } else {
      if (ptype == ptype_simple_array) {
	f2ptr result = f2__simple_array__slot__type_funk(cause, this, slot_type, slot_name);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array"));
	  result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
	}
	return result;
      } else if (ptype == ptype_traced_array) {
	f2ptr result = f2__traced_array__slot__type_funk(cause, this, slot_type, slot_name);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array"));
	  result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
	}
	return result;
      }
      return f2larva__new(cause, 1);
    }
  }
  case ptype_larva: {
    f2ptr result = f2__larva__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("larva"), (u8*)"larva"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    }
    return result;
  }
  }
  return f2larva__new(cause, 1);
}
def_pcfunk3(object__slot__type_funk, this, slot_type, slot_name, return f2__object__slot__type_funk(this_cause, this, slot_type, slot_name));

f2ptr f2__object__hash_value(f2ptr cause, f2ptr fiber, f2ptr this) {
  f2ptr hash_value_funk = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, __funk2.globalenv.hash_value__symbol);
  return f2__force_funk_apply(cause, fiber, hash_value_funk, f2cons__new(cause, this, nil));
}
def_pcfunk1(object__hash_value, this, return f2__object__hash_value(this_cause, simple_fiber, this));



// property_scan

f2ptr object__mapc_relations__property_scan(f2ptr cause, f2ptr fiber, f2ptr property_funk, f2ptr object, f2ptr slot_name, f2ptr slot_value) {
  if (property_funk) {
    return f2__force_funk_apply(cause, fiber, property_funk, f2cons__new(cause, slot_name, f2cons__new(cause, slot_value, nil)));
  }
  return nil;
}

void object__property_scan__object_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber         = raw__array__elt(cause, aux_data, 0);
  f2ptr property_funk = raw__array__elt(cause, aux_data, 1);
  f2ptr object        = raw__array__elt(cause, aux_data, 2);
  f2ptr found_larva   = raw__array__elt(cause, aux_data, 3);
  if (found_larva) {
    return;
  }
  
  {
    //printf("\nobject_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_funk = f2__object__slot__type_funk(cause, object, __funk2.globalenv.get__symbol, slot_name);
    f2ptr slot_value = f2__force_funk_apply(cause, fiber, slot_funk, f2cons__new(cause, object, nil));
    
    if (! found_larva) {
      f2ptr property_scan_result = object__property_scan__property_scan(cause, fiber, property_funk, object, slot_name, slot_value);
      if (raw__larva__is_type(cause, property_scan_result)) {
	found_larva = property_scan_result;
      }
      
      ////f2__print(cause, fiber, slot_value);
      //f2ptr property_scan_result = f2__object__property_scan(cause, fiber, this, slot_value, property_funk);
      //if (raw__larva__is_type(cause, property_scan_result)) {
      //found_larva = property_scan_result;
      //}
    }
  }
  
  raw__array__elt__set(cause, aux_data, 6, found_larva);
}

void object__property_scan__frame_slot_helper(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr fiber         = raw__array__elt(cause, aux_data, 0);
  f2ptr property_funk = raw__array__elt(cause, aux_data, 1);
  f2ptr frame         = raw__array__elt(cause, aux_data, 2);
  f2ptr found_larva   = raw__array__elt(cause, aux_data, 3);
  if (found_larva) {
    return;
  }
  
  {
    //printf("\nframe_slot:");
    //f2__print(cause, fiber, slot_name);
    f2ptr slot_value = f2__frame__lookup_var_value(cause, frame, slot_name, nil);
    if (raw__larva__is_type(cause, slot_value)) {
      found_larva = slot_value;
    }
    
    if (! found_larva) {
      f2ptr property_scan_result = object__property_scan__property_scan(cause, fiber, property_funk, frame, slot_name, slot_value);
      if (raw__larva__is_type(cause, property_scan_result)) {
	found_larva = property_scan_result;
      }
      
      ////f2__print(cause, fiber, slot_value);
      //f2ptr property_scan_result = f2__object__property_scan(cause, fiber, slot_value, property_funk);
      //if (raw__larva__is_type(cause, property_scan_result)) {
      //	found_larva = property_scan_result;
      //}
    }
  }
  
  raw__array__elt__set(cause, aux_data, 4, found_larva);
}

f2ptr f2__object__property_scan__primobject_slots(f2ptr cause, f2ptr fiber, f2ptr f2ptr object, f2ptr property_funk) {
  f2ptr object_type_name = f2__object__type(cause, object);
  f2ptr object_type      = f2__lookup_type(cause, object_type_name);
  f2ptr found_larva      = nil;
  {
    f2ptr aux_data = raw__array__new(cause, 4);
    raw__array__elt__set(cause, aux_data, 0, fiber);
    raw__array__elt__set(cause, aux_data, 1, property_funk);
    raw__array__elt__set(cause, aux_data, 2, object);
    raw__array__elt__set(cause, aux_data, 3, found_larva);
    raw__primobject_type__type_funk__mapc_slot_names(cause, object_type, __funk2.globalenv.get__symbol, &object__property_scan__object_slot_helper, aux_data);
    found_larva = raw__array__elt(cause, aux_data, 4);
  }
  return found_larva;
}

f2ptr f2__object__property_scan__frame_slots(f2ptr cause, f2ptr fiber, f2ptr frame, f2ptr property_funk) {
  f2ptr found_larva = nil;
  {
    f2ptr aux_data = raw__array__new(cause, 4);
    raw__array__elt__set(cause, aux_data, 0, fiber);
    raw__array__elt__set(cause, aux_data, 1, property_funk);
    raw__array__elt__set(cause, aux_data, 2, frame);
    raw__array__elt__set(cause, aux_data, 3, found_larva);
    raw__frame__type_var__mapc_slot_names(cause, frame, __funk2.globalenv.get__symbol, &object__property_scan__frame_slot_helper, aux_data);
    found_larva = raw__array__elt(cause, aux_data, 4);
  }
  return found_larva;
}

f2ptr f2__object__property_scan__array_indices(f2ptr cause, f2ptr fiber, f2ptr array, f2ptr property_funk) {
  u64 length = raw__array__length(cause, array);
  u64 index;
  for (index = 0; index < length; index ++) {
    f2ptr element = raw__array__elt(cause, array, index);
    {
      f2ptr property_scan_result = object__property_scan__property_scan(cause, fiber, property_funk, object, array, f2integer__new(cause, index), element);
      if (raw__larva__is_type(cause, property_scan_result)) {
	return property_scan_result;
      }
      
      //f2__print(cause, fiber, slot_value);
      //f2ptr property_scan_result = f2__object__property_scan(cause, fiber, element, property_funk);
      //if (raw__larva__is_type(cause, property_scan_result)) {
      //	return property_scan_result;
      //}
    }
  }
  return nil;
}

f2ptr f2__object__property_scan(f2ptr cause, f2ptr fiber, f2ptr object, f2ptr property_funk) {
  if      (raw__typedframe__is_type(cause, objects)) {return f2__object__property_scan__primobject_slots(cause, fiber, objects, property_funk);}
  else if (raw__frame__is_type(     cause, objects)) {return f2__object__property_scan__frame_slots(     cause, fiber, objects, property_funk);}
  else if (raw__primobject__is_type(cause, objects)) {return f2__object__property_scan__primobject_slots(cause, fiber, objects, property_funk);}
  else if (raw__array__is_type(     cause, objects)) {return f2__object__property_scan__array_indices(   cause, fiber, objects, property_funk);}
  return nil;
}

def_pcfunk3(object__property_scan, objects, property_funk, return f2__object__property_scan(this_cause, simple_fiber, objects, property_funk));

// **

void f2__object__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_object_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__object__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "object", "", &f2__object__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__1(object__type,            this,                       "returns the symbolic type name of the object.");
  f2__primcfunk__init__3(object__slot__type_funk, this, slot_type, slot_name, "returns the slot type funk for the object (e.g. types: get, set, execute).");
  f2__primcfunk__init__1(object__hash_value,      this,                       "returns the hash_value of the object.");
  f2__primcfunk__init__3(object__property_scan,   this, property_funk,        "property scan funk of type, [funk [name value] ...].");
}

