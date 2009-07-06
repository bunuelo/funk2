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
  case ptype_integer: {
    f2ptr result = f2__integer__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("integer"), (u8*)"integer"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_double: {
    f2ptr result = f2__double__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("double"), (u8*)"double"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_float: {
    f2ptr result = f2__float__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("float"), (u8*)"float"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_pointer: {
    f2ptr result = f2__pointer__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("pointer"), (u8*)"pointer"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_gfunkptr: {
    f2ptr result = f2__gfunkptr__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_mutex: {
    f2ptr result = f2__mutex__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("mutex"), (u8*)"mutex"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_char: {
    f2ptr result = f2__char__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("char"), (u8*)"char"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_string: {
    f2ptr result = f2__string__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("string"), (u8*)"string"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_symbol:{
    f2ptr result = f2__symbol__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("symbol"), (u8*)"symbol"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_chunk: {
    f2ptr result = f2__chunk__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("chunk"), (u8*)"chunk"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_simple_array:
  case ptype_traced_array: {
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      //printf("\nprimobject_type_name: "); f2__print(cause, primobject_type_name); fflush(stdout);
      if (primobject_type_name == __frame__symbol) {
	f2ptr test_get_type = frame__lookup_var_value(cause, this, f2symbol__new(cause, strlen("type"), (u8*)"type"), nil);
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
      return f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	f2ptr result = f2__simple_array__slot__get_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array"));
	  result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
	}
	return result;
      } else if (ptype == ptype_traced_array) {
	f2ptr result = f2__traced_array__slot__get_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array"));
	  result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
	}
	return result;
      }
      return f2larva__new(cause, 1);
    }
  }
  case ptype_larva: {
    f2ptr result = f2__larva__slot__get_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("larva"), (u8*)"larva"));
      result = f2__primobject_type__lookup_slot_get_funk(cause, primobject_type, slot);
    }
    return result;
  }
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
  case ptype_integer: {
    f2ptr result = f2__integer__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("integer"), (u8*)"integer"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_double: {
    f2ptr result = f2__double__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("double"), (u8*)"double"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_float: {
    f2ptr result = f2__float__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("float"), (u8*)"float"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_pointer: {
    f2ptr result = f2__pointer__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("pointer"), (u8*)"pointer"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_gfunkptr: {
    f2ptr result = f2__gfunkptr__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_mutex: {
    f2ptr result = f2__mutex__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("mutex"), (u8*)"mutex"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_char: {
    f2ptr result = f2__char__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("char"), (u8*)"char"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_string: {
    f2ptr result = f2__string__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("string"), (u8*)"string"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_symbol: {
    f2ptr result = f2__symbol__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("symbol"), (u8*)"symbol"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_chunk: {
    f2ptr result = f2__chunk__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("chunk"), (u8*)"chunk"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      if (primobject_type_name == __frame__symbol) {
	f2ptr test_get_type = frame__lookup_var_value(cause, this, f2symbol__new(cause, strlen("type"), (u8*)"type"), nil);
	if (test_get_type) {
	  primobject_type_name = test_get_type;
	}
      }
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	return nil;
      }
      return f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	f2ptr result = f2__simple_array__slot__set_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array"));
	  result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
	}
	return result;
      } else if (ptype == ptype_traced_array) {
	f2ptr result = f2__traced_array__slot__set_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array"));
	  result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
	}
	return result;
      }
      return f2larva__new(cause, 1);
    }
  case ptype_larva: {
    f2ptr result = f2__larva__slot__set_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("larva"), (u8*)"larva"));
      result = f2__primobject_type__lookup_slot_set_funk(cause, primobject_type, slot);
    }
    return result;
  }
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
  case ptype_integer: {
    f2ptr result = f2__integer__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("integer"), (u8*)"integer"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_double: {
    f2ptr result = f2__double__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("double"), (u8*)"double"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_float: {
    f2ptr result = f2__float__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("float"), (u8*)"float"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_pointer: {
    f2ptr result = f2__pointer__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("pointer"), (u8*)"pointer"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_gfunkptr: {
    f2ptr result = f2__gfunkptr__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_mutex: {
    f2ptr result = f2__mutex__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("mutex"), (u8*)"mutex"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_char: {
    f2ptr result = f2__char__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("char"), (u8*)"char"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_string: {
    f2ptr result = f2__string__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("string"), (u8*)"string"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_symbol: {
    f2ptr result = f2__symbol__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("symbol"), (u8*)"symbol"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_chunk: {
    f2ptr result = f2__chunk__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("chunk"), (u8*)"chunk"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
  case ptype_simple_array:
  case ptype_traced_array:
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__type(this, cause);
      if (primobject_type_name == __frame__symbol) {
	f2ptr test_get_type = frame__lookup_var_value(cause, this, f2symbol__new(cause, strlen("type"), (u8*)"type"), nil);
	if (test_get_type) {
	  primobject_type_name = test_get_type;
	}
      }
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	return nil;
      }
      return f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    } else {
      if (ptype == ptype_simple_array) {
	f2ptr result = f2__simple_array__slot__execute_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array"));
	  result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
	}
	return result;
      } else if (ptype == ptype_traced_array) {
	f2ptr result = f2__traced_array__slot__execute_funk(cause, this, slot);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array"));
	  result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
	}
	return result;
      }
      return f2larva__new(cause, 1);
    }
  case ptype_larva: {
    f2ptr result = f2__larva__slot__execute_funk(cause, this, slot);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("larva"), (u8*)"larva"));
      result = f2__primobject_type__lookup_slot_execute_funk(cause, primobject_type, slot);
    }
    return result;
  }
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

