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

// list

def_primobject_3_slot(list, write_cmutex, length, cons_cells);

f2ptr f2__list__new(f2ptr cause, f2ptr elements) {
  return f2list__new(cause, f2cmutex__new(cause), f2__simple_length(cause, elements), elements);
}
def_pcfunk0_and_rest(list__new, elements,
		     "",
		     return f2__list__new(this_cause, elements));

f2ptr f2__list__car(f2ptr cause, f2ptr this) {
  f2ptr cons_cells = f2list__cons_cells(this, cause);
  if (cons_cells == nil) {
    return f2larva__new(cause, 44, nil);
  }
  return f2cons__car(cons_cells, cause);
}
def_pcfunk1(list__car, this,
	    "",
	    return f2__list__car(this_cause, this));


f2ptr raw__list__cdr(f2ptr cause, f2ptr this) {
  f2ptr length     = f2list__length(this, cause);
  s64   length__i  = f2integer__i(length, cause);
  f2ptr cons_cells = f2list__cons_cells(this, cause);
  if (cons_cells == nil || length__i == 0) {
    return f2larva__new(cause, 44, nil);
  }
  f2ptr new_cons_cells = f2cons__cdr(cons_cells, cause);
  if (new_cons_cells) {
    return f2list__new(cause, f2cmutex__new(cause), f2integer__new(cause, length__i - 1), new_cons_cells);
  } else {
    return nil;
  }
}

f2ptr f2__list__cdr(f2ptr cause, f2ptr this) {
  assert_argument_type(list, this);
  return raw__list__cdr(cause, this);
}
def_pcfunk1(list__cdr, this,
	    "",
	    return f2__list__cdr(this_cause, this));


f2ptr raw__list__add(f2ptr cause, f2ptr this, f2ptr element) {
  f2cmutex__lock(f2list__write_cmutex(this, cause), cause);
  f2list__cons_cells__set(this, cause, raw__cons__new(cause, element, f2list__cons_cells(this, cause)));
  f2ptr length = f2list__length(this, cause);
  s64 length__i = f2integer__i(length, cause);
  f2list__length__set(this, cause, f2integer__new(cause, length__i + 1));
  f2cmutex__unlock(f2list__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__list__add(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(list, this);
  return raw__list__add(cause, this, element);
}
def_pcfunk2(list__add, this, element,
	    "",
	    return f2__list__add(this_cause, this, element));


f2ptr raw__list__lookup(f2ptr cause, f2ptr this, f2ptr element) {
  f2cmutex__lock(f2list__write_cmutex(this, cause), cause);
  f2ptr iter = f2list__cons_cells(this, cause);
  while (iter) {
    f2ptr iter__element = f2cons__car(iter, cause);
    if (raw__eq(cause, element, iter__element)) {
      f2cmutex__unlock(f2list__write_cmutex(this, cause), cause);
      return iter__element;
    }
    iter = f2cons__cdr(iter, cause);
  }
  f2cmutex__unlock(f2list__write_cmutex(this, cause), cause);
  return nil;
}

f2ptr f2__list__lookup(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(list, this);
  return raw__list__lookup(cause, this, element);
}
def_pcfunk2(list__lookup, this, element,
	    "",
	    return f2__list__lookup(this_cause, this, element));


f2ptr raw__list__equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr cons_cells = f2__list__cons_cells(cause, this);
  if (raw__list__is_type(cause, that)) {
    f2ptr that__cons_cells = f2__list__cons_cells(cause, that);
    return f2__object__equals(cause, cons_cells, that__cons_cells);
  }
  return f2__object__equals(cause, cons_cells, that);
}

f2ptr f2__list__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(list, this);
  return raw__list__equals(cause, this, that);
}
def_pcfunk2(list__equals, this, that,
	    "",
	    return f2__list__equals(this_cause, this, that));


f2ptr raw__list__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  f2ptr cons_cells = f2__list__cons_cells(cause, this);
  return f2__object__equals_hash_value__loop_free(cause, cons_cells, node_hash);
}

f2ptr f2__list__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  assert_argument_type(list,      this);
  assert_argument_type(ptypehash, node_hash);
  return raw__list__equals_hash_value__loop_free(cause, this, node_hash);
}
def_pcfunk2(list__equals_hash_value__loop_free, this, node_hash,
	    "",
	    return f2__list__equals_hash_value__loop_free(this_cause, this, node_hash));

f2ptr raw__list__equals_hash_value(f2ptr cause, f2ptr this) {
  f2ptr node_hash = f2__ptypehash__new(cause);
  return raw__list__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__list__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(list, this);
  return raw__list__equals_hash_value(cause, this);
}
def_pcfunk1(list__equals_hash_value, this,
	    "",
	    return f2__list__equals_hash_value(this_cause, this));


f2ptr raw__list__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  return raw__exp__terminal_print_with_frame__thread_unsafe(cause, f2__list__cons_cells(cause, this), terminal_print_frame);
}

f2ptr f2__list__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(list,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__list__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(list__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__list__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2list__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2list__primobject_type__new(cause);
  {char* slot_name = "add";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.add__funk);}
  {char* slot_name = "lookup";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__funk);}
  {char* slot_name = "car";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.car__funk);}
  {char* slot_name = "cdr";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.cdr__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_list.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__primobject_list__defragment__fix_pointers() {
  // -- reinitialize --
  
  // list
  
  initialize_primobject_3_slot__defragment__fix_pointers(list, write_cmutex, length, cons_cells);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.add__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__add);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.add__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.lookup__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__lookup);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.lookup__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.car__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__car);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.car__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.cdr__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__cdr);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.cdr__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(list__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_list.terminal_print_with_frame__funk);
  
  
  // -- initialize --
  
}

void f2__primobject_list__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // list
  
  initialize_primobject_3_slot(list, write_cmutex, length, cons_cells);
  
  {char* symbol_str = "add"; __funk2.globalenv.object_type.primobject.primobject_type_list.add__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(list__add, this, slot_name, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.add__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__lookup, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "car"; __funk2.globalenv.object_type.primobject.primobject_type_list.car__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__car, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.car__funk = never_gc(cfunk);}
  {char* symbol_str = "cdr"; __funk2.globalenv.object_type.primobject.primobject_type_list.cdr__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__cdr, this, slot_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.cdr__funk = never_gc(cfunk);}
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_list.equals__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__equals, this, that, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__loop_free__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(list__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_list.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(list__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_list.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject_list__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-list", "", &f2__primobject_list__reinitialize_globalvars, &f2__primobject_list__defragment__fix_pointers);
  
  f2__primobject_list__reinitialize_globalvars();
}

