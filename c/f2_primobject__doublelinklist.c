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

// doublelinklist

def_primobject_3_slot(doublelinklist, write_cmutex, length, cons_cells);

f2ptr f2__doublelinklist__new(f2ptr cause, f2ptr elements) {
  return f2doublelinklist__new(cause, f2cmutex__new(cause), f2__simple_length(cause, elements), elements);
}
def_pcfunk0_and_rest(doublelinklist__new, elements,
		     "",
		     return f2__doublelinklist__new(this_cause, elements));

f2ptr f2__doublelinklist__car(f2ptr cause, f2ptr this) {
  f2ptr cons_cells = f2doublelinklist__cons_cells(this, cause);
  if (cons_cells == nil) {
    return f2larva__new(cause, 44, nil);
  }
  return f2cons__car(cons_cells, cause);
}
def_pcfunk1(doublelinklist__car, this,
	    "",
	    return f2__doublelinklist__car(this_cause, this));

f2ptr f2__doublelinklist__cdr(f2ptr cause, f2ptr this) {
  f2ptr length     = f2doublelinklist__length(this, cause);
  s64   length__i  = f2integer__i(length, cause);
  f2ptr cons_cells = f2doublelinklist__cons_cells(this, cause);
  if (cons_cells == nil || length__i == 0) {
    return f2larva__new(cause, 44, nil);
  }
  return f2doublelinklist__new(cause, f2cmutex__new(cause), f2integer__new(cause, length__i - 1), f2cons__cdr(cons_cells, cause));
}
def_pcfunk1(doublelinklist__cdr, this,
	    "",
	    return f2__doublelinklist__cdr(this_cause, this));

f2ptr f2__doublelinklist__add(f2ptr cause, f2ptr this, f2ptr element) {
  raw__cmutex__lock(cause, f2doublelinklist__write_cmutex(this, cause));
  f2doublelinklist__cons_cells__set(this, cause, raw__cons__new(cause, element, f2doublelinklist__cons_cells(this, cause)));
  f2ptr length = f2doublelinklist__length(this, cause);
  s64 length__i = f2integer__i(length, cause);
  f2doublelinklist__length__set(this, cause, f2integer__new(cause, length__i + 1));
  f2cmutex__unlock(f2doublelinklist__write_cmutex(this, cause), cause);
  return nil;
}
def_pcfunk2(doublelinklist__add, this, element,
	    "",
	    return f2__doublelinklist__add(this_cause, this, element));

f2ptr f2__doublelinklist__lookup(f2ptr cause, f2ptr this, f2ptr element) {
  raw__cmutex__lock(cause, f2doublelinklist__write_cmutex(this, cause));
  f2ptr iter = f2doublelinklist__cons_cells(this, cause);
  while (iter) {
    f2ptr iter__element = f2cons__car(iter, cause);
    if (raw__eq(cause, element, iter__element)) {
      f2cmutex__unlock(f2doublelinklist__write_cmutex(this, cause), cause);
      return iter__element;
    }
    iter = f2cons__cdr(iter, cause);
  }
  f2cmutex__unlock(f2doublelinklist__write_cmutex(this, cause), cause);
  return nil;
}
def_pcfunk2(doublelinklist__lookup, this, element,
	    "",
	    return f2__doublelinklist__lookup(this_cause, this, element));

f2ptr f2doublelinklist__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2doublelinklist__primobject_type__new(cause);
  {char* slot_name = "add";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__funk);}
  {char* slot_name = "car";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__funk);}
  {char* slot_name = "cdr";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__funk);}
  return this;
}


// **

void f2__primobject_doublelinklist__reinitialize_globalvars() {
  __doublelinklist__symbol = new__symbol(initial_cause(), "doublelinklist");
}

void f2__primobject_doublelinklist__initialize() {
  f2__primobject_doublelinklist__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __doublelinklist__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // doublelinklist
  
  initialize_primobject_3_slot(doublelinklist, write_cmutex, length, cons_cells);
  
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(doublelinklist__add, this, slot_name, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__lookup, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "car"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__car, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__funk = never_gc(cfunk);}
  {char* symbol_str = "cdr"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__cdr, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__funk = never_gc(cfunk);}
  
}

