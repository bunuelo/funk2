// 
// Copyright (c) 2007-2010 Bo Morgan.
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

// doublelinklist primobject definition

defprimobject__static_slot(doublelinklist__write_mutex, 0);
defprimobject__static_slot(doublelinklist__length,      1);
defprimobject__static_slot(doublelinklist__cons_cells,  2);

f2ptr __doublelinklist__symbol = -1;

f2ptr f2doublelinklist__new(f2ptr cause, f2ptr write_mutex, f2ptr length, f2ptr cons_cells) {
  debug__assert(__doublelinklist__symbol != -1, nil, "f2doublelinklist__new error: used before primobjects initialized.");
  debug__assert((raw__integer__is_type(cause, length)), nil, "f2doublelinklist__new error: length is of wrong type.");
  f2ptr this = f2__primobject__new(cause, __doublelinklist__symbol, 3, nil);
  f2doublelinklist__write_mutex__set(this, cause, write_mutex);
  f2doublelinklist__length__set(     this, cause, length);
  f2doublelinklist__cons_cells__set( this, cause, cons_cells);
  return this;
}

// hardcoded doublelinklist functions

boolean_t raw__doublelinklist__is_type(f2ptr cause, f2ptr this) {return raw__array__is_type(cause, this) && f2primobject__is_doublelinklist(this, cause);}
f2ptr f2__doublelinklist__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__doublelinklist__is_type(cause, this));}
def_pcfunk1(doublelinklist__is_type, this, return f2__doublelinklist__is_type(this_cause, this));

f2ptr f2__doublelinklist__new(f2ptr cause, f2ptr elements) {
  return f2doublelinklist__new(cause, f2mutex__new(cause), f2__simple_length(cause, elements), elements);
}
def_pcfunk0_and_rest(doublelinklist__new, elements, return f2__doublelinklist__new(this_cause, elements));

f2ptr f2__doublelinklist__write_mutex(f2ptr cause, f2ptr this) {return f2doublelinklist__write_mutex(this, cause);}
def_pcfunk1(doublelinklist__write_mutex, this, return f2__doublelinklist__write_mutex(this_cause, this));

f2ptr f2__doublelinklist__write_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2doublelinklist__write_mutex__set(this, cause, value);}
def_pcfunk2(doublelinklist__write_mutex__set, this, value, return f2__doublelinklist__write_mutex__set(this_cause, this, value));

f2ptr f2__doublelinklist__length(f2ptr cause, f2ptr this) {return f2doublelinklist__length(this, cause);}
def_pcfunk1(doublelinklist__length, this, return f2__doublelinklist__length(this_cause, this));

f2ptr f2__doublelinklist__length__set(f2ptr cause, f2ptr this, f2ptr value) {return f2doublelinklist__length__set(this, cause, value);}
def_pcfunk2(doublelinklist__length__set, this, value, return f2__doublelinklist__length__set(this_cause, this, value));

f2ptr f2__doublelinklist__cons_cells(f2ptr cause, f2ptr this) {return f2doublelinklist__cons_cells(this, cause);}
def_pcfunk1(doublelinklist__cons_cells, this, return f2__doublelinklist__cons_cells(this_cause, this));

f2ptr f2__doublelinklist__cons_cells__set(f2ptr cause, f2ptr this, f2ptr value) {return f2doublelinklist__cons_cells__set(this, cause, value);}
def_pcfunk2(doublelinklist__cons_cells__set, this, value, return f2__doublelinklist__cons_cells__set(this_cause, this, value));

f2ptr f2__doublelinklist__car(f2ptr cause, f2ptr this) {
  f2ptr cons_cells = f2doublelinklist__cons_cells(this, cause);
  if (cons_cells == nil) {
    return f2larva__new(cause, 44);
  }
  return f2cons__car(cons_cells, cause);
}
def_pcfunk1(doublelinklist__car, this, return f2__doublelinklist__car(this_cause, this));

f2ptr f2__doublelinklist__cdr(f2ptr cause, f2ptr this) {
  f2ptr length     = f2doublelinklist__length(this, cause);
  s64   length__i  = f2integer__i(length, cause);
  f2ptr cons_cells = f2doublelinklist__cons_cells(this, cause);
  if (cons_cells == nil || length__i == 0) {
    return f2larva__new(cause, 44);
  }
  return f2doublelinklist__new(cause, f2mutex__new(cause), f2integer__new(cause, length__i - 1), f2cons__cdr(cons_cells, cause));
}
def_pcfunk1(doublelinklist__cdr, this, return f2__doublelinklist__cdr(this_cause, this));

f2ptr f2__doublelinklist__add(f2ptr cause, f2ptr this, f2ptr element) {
  f2mutex__lock(f2doublelinklist__write_mutex(this, cause), cause);
  f2doublelinklist__cons_cells__set(this, cause, f2cons__new(cause, element, f2doublelinklist__cons_cells(this, cause)));
  f2ptr length = f2doublelinklist__length(this, cause);
  s64 length__i = f2integer__i(length, cause);
  f2doublelinklist__length__set(this, cause, f2integer__new(cause, length__i + 1));
  f2mutex__unlock(f2doublelinklist__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk2(doublelinklist__add, this, element, return f2__doublelinklist__add(this_cause, this, element));

f2ptr f2__doublelinklist__lookup(f2ptr cause, f2ptr this, f2ptr element) {
  f2mutex__lock(f2doublelinklist__write_mutex(this, cause), cause);
  f2ptr iter = f2doublelinklist__cons_cells(this, cause);
  while (iter) {
    f2ptr iter__element = f2cons__car(iter, cause);
    if (raw__eq(cause, element, iter__element)) {
      f2mutex__unlock(f2doublelinklist__write_mutex(this, cause), cause);
      return iter__element;
    }
    iter = f2cons__cdr(iter, cause);
  }
  f2mutex__unlock(f2doublelinklist__write_mutex(this, cause), cause);
  return nil;
}
def_pcfunk2(doublelinklist__lookup, this, element, return f2__doublelinklist__lookup(this_cause, this, element));

f2ptr f2doublelinklist__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "primobject"), nil));
  {char* slot_name = "is_type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.is_type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.new__funk);}
  {char* slot_name = "write_mutex";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__funk);}
  {char* slot_name = "write_mutex";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__set__funk);}
  {char* slot_name = "length";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__funk);}
  {char* slot_name = "length";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__set__funk);}
  {char* slot_name = "cons_cells";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__funk);}
  {char* slot_name = "cons_cells";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__set__funk);}
  {char* slot_name = "add";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__funk);}
  {char* slot_name = "lookup";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__funk);}
  {char* slot_name = "car";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__funk);}
  {char* slot_name = "cdr";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__funk);}
  return this;
}


// **

void f2__primobject_doublelinklist__reinitialize_globalvars() {
  __doublelinklist__symbol = f2symbol__new(initial_cause(), strlen("doublelinklist"), (u8*)"doublelinklist");
}

void f2__primobject_doublelinklist__initialize() {
  f2__primobject_doublelinklist__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __doublelinklist__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // doublelinklist
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelinklist__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(doublelinklist__new, elements, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.new__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelinklist__write_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "write_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__write_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.write_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "length"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelinklist__length, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__funk = never_gc(cfunk);}
  {char* symbol_str = "length-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__length__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.length__set__funk = never_gc(cfunk);}
  {char* symbol_str = "cons_cells"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelinklist__cons_cells, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__funk = never_gc(cfunk);}
  {char* symbol_str = "cons_cells-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__cons_cells__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cons_cells__set__funk = never_gc(cfunk);}
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(doublelinklist__add, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__lookup, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "car"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__car, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.car__funk = never_gc(cfunk);}
  {char* symbol_str = "cdr"; __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelinklist__cdr, this, slot_name, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelinklist.cdr__funk = never_gc(cfunk);}
  
}

