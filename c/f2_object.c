// 
// Copyright (c) 2007-2011 Bo Morgan.
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
  case ptype_scheduler_cmutex:
    return f2symbol__new(cause, strlen("scheduler_cmutex"), (u8*)"scheduler_cmutex");
  case ptype_cmutex:
    return f2symbol__new(cause, strlen("cmutex"), (u8*)"cmutex");
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
      f2ptr primobject_type_name = f2primobject__object_type(this, cause);
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
    return f2larva__new(cause, 1, nil);
  case ptype_larva:
    return f2symbol__new(cause, strlen("larva"), (u8*)"larva");
  }
  return f2larva__new(cause, 1, nil);
}
def_pcfunk1(object__type, this, return f2__object__type(this_cause, this));


f2ptr f2__object__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (this == nil) {
    f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, nil);
    f2ptr result          = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
    if (! result) {
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "nil_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
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
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "integer_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_double: {
    f2ptr result = f2__double__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("double"), (u8*)"double"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "double_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_float: {
    f2ptr result = f2__float__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("float"), (u8*)"float"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "float_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_pointer: {
    f2ptr result = f2__pointer__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("pointer"), (u8*)"pointer"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "pointer_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_gfunkptr: {
    f2ptr result = f2__gfunkptr__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "gfunkptr_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_scheduler_cmutex: {
    f2ptr result = f2__scheduler_cmutex__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("scheduler_cmutex"), (u8*)"scheduler_cmutex"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "scheduler_cmutex_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_cmutex: {
    f2ptr result = f2__cmutex__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("cmutex"), (u8*)"cmutex"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "cmutex_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_char: {
    f2ptr result = f2__char__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("char"), (u8*)"char"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "char_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_string: {
    f2ptr result = f2__string__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("string"), (u8*)"string"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "string_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_symbol:{
    f2ptr result = f2__symbol__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("symbol"), (u8*)"symbol"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "symbol_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_chunk: {
    f2ptr result = f2__chunk__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("chunk"), (u8*)"chunk"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "chunk_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  case ptype_simple_array:
  case ptype_traced_array: {
    if (raw__primobject__is_type(cause, this)) {
      f2ptr primobject_type_name = f2primobject__object_type(this, cause);
      if (raw__eq(cause, primobject_type_name, __funk2.primobject__frame.frame__symbol)) {
	f2ptr test_get_type = f2__frame__lookup_var_value(cause, this, __funk2.globalenv.type__symbol, nil);
	if (test_get_type) {
	  primobject_type_name = test_get_type;
	}
      }
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, primobject_type_name);
      if (primobject_type == nil) {
	f2ptr bug_frame = f2__frame__new(cause, nil);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "could_not_determine_primobject_type"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
	return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
      }
      f2ptr result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
      if (! result) {
	f2ptr bug_frame = f2__frame__new(cause, nil);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "primobject_type_does_not_have_funktion"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
	return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
      }
      return result;
    } else {
      if (ptype == ptype_simple_array) {
	f2ptr result = f2__simple_array__slot__type_funk(cause, this, slot_type, slot_name);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array"));
	  result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
	}
	if (! result) {
	  f2ptr bug_frame = f2__frame__new(cause, nil);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "primobject_type_does_not_have_funktion"));
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
	  return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
	}
	return result;
      } else if (ptype == ptype_traced_array) {
	f2ptr result = f2__traced_array__slot__type_funk(cause, this, slot_type, slot_name);
	if (! result) {
	  f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array"));
	  result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
	  if (! result) {
	    result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
	  }
	}
	if (! result) {
	  f2ptr bug_frame = f2__frame__new(cause, nil);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "primobject_type_does_not_have_funktion"));
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
	  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
	  return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
	}
	return result;
      }
      {
	f2ptr bug_frame = f2__frame__new(cause, nil);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "we_should_not_get_here"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
	f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
	return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
      }
    }
  }
  case ptype_larva: {
    f2ptr result = f2__larva__slot__type_funk(cause, this, slot_type, slot_name);
    if (! result) {
      f2ptr primobject_type = funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, f2symbol__new(cause, strlen("larva"), (u8*)"larva"));
      result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, slot_name);
      if (! result) {
	result = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, slot_type, new__symbol(cause, "__undefined__"));
      }
    }
    if (! result) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "larva_type_does_not_have_funktion"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "object-slot-type_funk"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),      this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_type"), slot_type);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "slot_name"), slot_name);
      return f2larva__new(cause, 634, f2__bug__new(cause, f2integer__new(cause, 634), bug_frame));
    }
    return result;
  }
  }
  return f2larva__new(cause, 1, nil);
}
def_pcfunk3(object__slot__type_funk, this, slot_type, slot_name, return f2__object__slot__type_funk(this_cause, this, slot_type, slot_name));


#define inherits_from(cause, this, type_name) raw__object__inherits_from(cause, this, new__symbol(cause, #type_name))

boolean_t raw__object__inherits_from(f2ptr cause, f2ptr this, f2ptr type_name) {
  f2ptr this__type_name = f2__object__type(cause, this);
  if (raw__eq(cause, this__type_name, type_name)) {
    return boolean__true;
  }
  f2ptr this__primobject_type = f2__lookup_type(cause, this__type_name);
  if (! raw__primobject_type__is_type(cause, this__primobject_type)) {
    return boolean__false;
  }
  return raw__primobject_type__has_parent_type(cause, this__primobject_type, type_name);
}

f2ptr f2__object__inherits_from(f2ptr cause, f2ptr this, f2ptr type_name) {
  assert_argument_type(symbol, type_name);
  return f2bool__new(raw__object__inherits_from(cause, this, type_name));
}
def_pcfunk2(object__inherits_from, this, type_name, return f2__object__inherits_from(this_cause, this, type_name));


#define object__get__no_such_slot     789
#define object__set__no_such_slot     790
#define object__execute__no_such_slot 791

f2ptr f2__object__cfunk_get(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__get__no_such_slot, f2__bug__new(cause, f2integer__new(cause, object__get__no_such_slot), f2__frame__new(cause, f2list10__new(cause,
																				    new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_get_funk"),
																				    new__symbol(cause, "funkname"), new__symbol(cause, "object-get"),
																				    new__symbol(cause, "this"),     this,
																				    new__symbol(cause, "slot"),     slot,
																				    new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
def_pcfunk2_and_rest(object__get,        this, slot, args, return f2__object__get(this_cause, this, slot, args));
def_pcfunk3(         object__get__apply, this, slot, args, return f2__object__get(this_cause, this, slot, args));

f2ptr f2__object__set(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.set__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__set__no_such_slot, f2__bug__new(cause, f2integer__new(cause, object__set__no_such_slot), f2__frame__new(cause, f2list10__new(cause,
																				    new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_set_funk"),
																				    new__symbol(cause, "funkname"), new__symbol(cause, "object-set"),
																				    new__symbol(cause, "this"),     this,
																				    new__symbol(cause, "slot"),     slot,
																				    new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
def_pcfunk2_and_rest(object__set,        this, slot, args, return f2__object__set(this_cause, this, slot, args));
def_pcfunk3(         object__set__apply, this, slot, args, return f2__object__set(this_cause, this, slot, args));

f2ptr f2__object__execute(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.execute__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__execute__no_such_slot, f2__bug__new(cause, f2integer__new(cause, object__execute__no_such_slot), f2__frame__new(cause, f2list10__new(cause,
																					    new__symbol(cause, "bug_type"), new__symbol(cause, "object_does_not_have_execute_funk"),
																					    new__symbol(cause, "funkname"), new__symbol(cause, "object-execute"),
																					    new__symbol(cause, "this"),     this,
																					    new__symbol(cause, "slot"),     slot,
																					    new__symbol(cause, "args"),     args))));
  }
  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, args));
  if (raw__larva__is_type(cause, result)) {
    f2__terminal_print(cause, result);
  }
  return result;
}
def_pcfunk2_and_rest(object__execute,        this, slot, args, return f2__object__execute(this_cause, this, slot, args));
def_pcfunk3(         object__execute__apply, this, slot, args, return f2__object__execute(this_cause, this, slot, args));

f2ptr f2__object__get_0(f2ptr cause, f2ptr this, f2ptr slot) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__get__no_such_slot, nil);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, nil));
}

f2ptr object__get_0(f2ptr cause, f2ptr this, char* slot_cstr) {
  return f2__object__get_0(cause, this, new__symbol(cause, slot_cstr));
}

f2ptr f2__object__get_1(f2ptr cause, f2ptr this, f2ptr slot, f2ptr arg0) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__get__no_such_slot, nil);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, arg0, nil)));
}

f2ptr object__get_1(f2ptr cause, f2ptr this, char* slot_cstr, f2ptr arg0) {
  return f2__object__get_1(cause, this, new__symbol(cause, slot_cstr), arg0);
}

f2ptr f2__object__set_1(f2ptr cause, f2ptr this, f2ptr slot, f2ptr arg0) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.set__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__set__no_such_slot, nil);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, arg0, nil)));
}

f2ptr f2__object__get_2(f2ptr cause, f2ptr this, f2ptr slot, f2ptr arg0, f2ptr arg1) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, slot);
  if (! raw__funkable__is_type(cause, funk)) {
    if (raw__larva__is_type(cause, funk)) {
      return funk;
    }
    return f2larva__new(cause, object__get__no_such_slot, nil);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, arg0, f2cons__new(cause, arg1, nil))));
}

f2ptr object__get_2(f2ptr cause, f2ptr this, char* slot_cstr, f2ptr arg0, f2ptr arg1) {
  return f2__object__get_2(cause, this, new__symbol(cause, slot_cstr), arg0, arg1);
}




f2ptr f2__object__eq(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, __funk2.globalenv.eq__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(this == that);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, that, nil)));
}
def_pcfunk2(object__eq, this, that, return f2__object__eq(this_cause, this, that));

f2ptr f2__object__eq_hash_value(f2ptr cause, f2ptr this) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, __funk2.globalenv.eq_hash_value__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return ((this == nil) ? f2integer__new(cause, 1) : f2integer__new(cause, (u64)this));
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, nil));
}
def_pcfunk1(object__eq_hash_value, this, return f2__object__eq_hash_value(this_cause, this));

f2ptr f2__object__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return f2__object__get_1(cause, this, __funk2.globalenv.equals__symbol, that);
}
def_pcfunk2(object__equals, this, that, return f2__object__equals(this_cause, this, that));

f2ptr f2__object__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if (this == __funk2.memory.global_environment_f2ptr) {
    return f2integer__new(cause, 1);
  }
  f2ptr result = f2__object__get_1(cause, this, __funk2.globalenv.equals_hash_value__loop_free__symbol, node_hash);
  if (raw__larva__is_type(cause, result) && raw__larva__larva_type(cause, result) == object__get__no_such_slot) {
    result = f2__object__get_0(cause, this, __funk2.globalenv.equals_hash_value__symbol);
  }
  return result;
}
def_pcfunk2(object__equals_hash_value__loop_free, this, node_hash, return f2__object__equals_hash_value__loop_free(this_cause, this, node_hash));

f2ptr f2__object__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2__object__get_0(cause, this, __funk2.globalenv.equals_hash_value__symbol);
}
def_pcfunk1(object__equals_hash_value, this, return f2__object__equals_hash_value(this_cause, this));


// property_scan

f2ptr object__property_scan__property_scan(f2ptr cause, f2ptr fiber, f2ptr property_funk, f2ptr object, f2ptr type_name, f2ptr slot_name, f2ptr slot_value) {
  if (property_funk) {
    return f2__force_funk_apply(cause, fiber, property_funk, f2cons__new(cause, type_name, f2cons__new(cause, slot_name, f2cons__new(cause, slot_value, nil))));
  }
  return nil;
}

void object__property_scan__map_funk(f2ptr cause, f2ptr slot_name, f2ptr aux_data) {
  f2ptr larva_found   = raw__array__elt(cause, aux_data, 0);
  f2ptr fiber         = raw__array__elt(cause, aux_data, 1);
  f2ptr object        = raw__array__elt(cause, aux_data, 2);
  f2ptr type_name     = raw__array__elt(cause, aux_data, 3);
  f2ptr property_funk = raw__array__elt(cause, aux_data, 4);
  
  f2ptr slot_funk = f2__object__slot__type_funk(cause, object, __funk2.globalenv.get__symbol, slot_name);
  if (raw__larva__is_type(cause, slot_funk)) {
    larva_found = slot_funk;
  } else {
    f2ptr slot_value = f2__force_funk_apply(cause, fiber, slot_funk, f2cons__new(cause, object, nil));
    if (raw__larva__is_type(cause, slot_value)) {
      slot_value = f2__bug__new_from_larva(cause, slot_value);
    }
    f2ptr result = object__property_scan__property_scan(cause, fiber, property_funk, object, type_name, slot_name, slot_value);
    if (raw__larva__is_type(cause, result)) {
      larva_found = result;
    } else {
      // do more
    }
  }
  raw__array__elt__set(cause, aux_data, 0, larva_found);
}

f2ptr object__property_scan__property_scan__by_type(f2ptr cause, f2ptr fiber, f2ptr object, f2ptr type_name, f2ptr property_funk) {
  f2ptr larva_found = nil;
  {
    f2ptr type = f2__lookup_type(cause, type_name);
    if (raw__primobject_type__is_type(cause, type)) {
      {
	{
	  f2ptr parents = f2__primobject_type__parents(cause, type);
	  f2ptr parent_iter = parents;
	  while (parent_iter) {
	    f2ptr parent_name = f2__cons__car(cause, parent_iter);
	    f2ptr result = object__property_scan__property_scan__by_type(cause, fiber, object, parent_name, property_funk);
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	    parent_iter = f2__cons__cdr(cause, parent_iter);
	  }
	}
	
	f2ptr aux_data = raw__array__new(cause, 5);
	raw__array__elt__set(cause, aux_data, 0, larva_found);
	raw__array__elt__set(cause, aux_data, 1, fiber);
	raw__array__elt__set(cause, aux_data, 2, object);
	raw__array__elt__set(cause, aux_data, 3, type_name);
	raw__array__elt__set(cause, aux_data, 4, property_funk);
	f2ptr result                = raw__primobject_type__type_funk__mapc_keys(cause, type, __funk2.globalenv.get__symbol, &object__property_scan__map_funk, aux_data);
	f2ptr larva_found_in_helper = raw__array__elt(cause, aux_data, 0);
	if (raw__larva__is_type(cause, larva_found_in_helper)) {
	  larva_found = larva_found_in_helper;
	} else if (raw__larva__is_type(cause, result)) {
	  larva_found = result;
	} else {
	  // do more
	}
      }
    }
  }
  return larva_found;
}

f2ptr f2__object__property_scan(f2ptr cause, f2ptr fiber, f2ptr object, f2ptr property_funk) {
  f2ptr type_name = f2__object__type(cause, object);
  return object__property_scan__property_scan__by_type(cause, fiber, object, type_name, property_funk);
}

def_pcfunk2(object__property_scan, object, property_funk, return f2__object__property_scan(this_cause, simple_fiber, object, property_funk));

// **

void f2__object__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_object_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__object__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "object", "", &f2__object__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__2_and_rest(object__get,            this, slot, args, "");
  f2__primcfunk__init__3(         object__get__apply,     this, slot, args, "");
  f2__primcfunk__init__2_and_rest(object__set,            this, slot, args, "");
  f2__primcfunk__init__3(         object__set__apply,     this, slot, args, "");
  f2__primcfunk__init__2_and_rest(object__execute,        this, slot, args, "");
  f2__primcfunk__init__3(         object__execute__apply, this, slot, args, "");
  
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(object__eq,                           this, that,      cfunk, 0, "returns whether two objects are eq according to the source object eq function.");        __funk2.object.object__eq__funk                           = never_gc(cfunk);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(object__eq_hash_value,                this,            cfunk, 0, "returns the eq_hash_value of the object.");                                              __funk2.object.object__eq_hash_value__funk                = never_gc(cfunk);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(object__equals,                       this, that,      cfunk, 0, "returns whether two objects are equal according to the source object equals function."); __funk2.object.object__equals__funk                       = never_gc(cfunk);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(object__equals_hash_value,            this,            cfunk, 0, "returns the equals_hash_value of the object.");                                          __funk2.object.object__equals_hash_value__funk            = never_gc(cfunk);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(object__equals_hash_value__loop_free, this, node_hash, cfunk, 0, "returns the equals_hash_value of the object when a node_hash is supplied.");             __funk2.object.object__equals_hash_value__loop_free__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(object__type,            this,                       "Returns the symbolic type name of the object.");
  f2__primcfunk__init__3(object__slot__type_funk, this, slot_type, slot_name, "Returns the slot type funk for the object (e.g. types: get, set, execute).");
  f2__primcfunk__init__2(object__inherits_from,   this, type_name,            "Returns whether this object inherits from a type interface.");
  f2__primcfunk__init__2(object__property_scan,   this, property_funk,        "Property scan funk of type, [funk [name value] ...].");
}


