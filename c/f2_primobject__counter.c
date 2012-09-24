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

// counter

def_primobject_2_slot(counter,
		      scheduler_cmutex,
		      value_chunk);

f2ptr raw__counter__new(f2ptr cause) {
  f2ptr scheduler_cmutex = f2__scheduler_cmutex__new(cause);
  f2ptr value_chunk      = raw__chunk__new(cause, sizeof(s64));
  return f2counter__new(cause,
			scheduler_cmutex,
			value_chunk);
}

f2ptr f2__counter__new(f2ptr cause) {
  return raw__counter__new(cause);
}
def_pcfunk0(counter__new,
	    "Returns a new counter object.",
	    return f2__counter__new(this_cause));


f2ptr raw__counter__value(f2ptr cause, f2ptr this) {
  f2ptr scheduler_cmutex = f2counter__scheduler_cmutex(this, cause);
  f2ptr value_chunk      = f2counter__value_chunk(this, cause);
  f2scheduler_cmutex__lock(scheduler_cmutex, cause);
  s64 value__i = raw__chunk__bit64__elt(cause, value_chunk, 0);
  f2scheduler_cmutex__unlock(scheduler_cmutex, cause);
  return f2integer__new(cause, value__i);
}

f2ptr f2__counter__value(f2ptr cause, f2ptr this) {
  assert_argument_type(counter, this);
  return raw__counter__value(cause, this);
}
def_pcfunk1(counter__value, this,
	    "Returns the value of the thread safe counter.",
	    return f2__counter__value(this_cause, this));


void raw__counter__value__set(f2ptr cause, f2ptr this, s64 value__i) {
  f2ptr scheduler_cmutex = f2counter__scheduler_cmutex(this, cause);
  f2ptr value_chunk      = f2counter__value_chunk(this, cause);
  f2scheduler_cmutex__lock(scheduler_cmutex, cause);
  raw__chunk__bit64__elt__set(cause, value_chunk, 0, value__i);
  f2scheduler_cmutex__unlock(scheduler_cmutex, cause);
}

f2ptr f2__counter__value__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(counter, this);
  assert_argument_type(integer, value);
  s64 value__i = f2integer__i(value, cause);
  raw__counter__value__set(cause, this, value__i);
  return nil;
}
def_pcfunk2(counter__value__set, this, value,
	    "Sets the value of the thread safe counter.",
	    return f2__counter__value__set(this_cause, this, value));


void raw__counter__increment(f2ptr cause, f2ptr this, s64 relative_value__i) {
  f2ptr scheduler_cmutex = f2counter__scheduler_cmutex(this, cause);
  f2ptr value_chunk      = f2counter__value_chunk(this, cause);
  f2scheduler_cmutex__lock(scheduler_cmutex, cause);
  s64 old_value__i = raw__chunk__bit64__elt(cause, value_chunk, 0);
  s64 new_value__i = old_value__i + relative_value__i;
  raw__chunk__bit64__elt__set(cause, value_chunk, 0, new_value__i);
  f2scheduler_cmutex__unlock(scheduler_cmutex, cause);
}

f2ptr f2__counter__increment(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(counter, this);
  assert_argument_type(integer, value);
  s64 value__i = f2integer__i(value, cause);
  raw__counter__increment(cause, this, value__i);
  return nil;
}
def_pcfunk2(counter__increment, this, value,
	    "Increments the value of the thread safe counter.",
	    return f2__counter__increment(this_cause, this, value));


void raw__counter__decrement(f2ptr cause, f2ptr this, s64 relative_value__i) {
  f2ptr scheduler_cmutex = f2counter__scheduler_cmutex(this, cause);
  f2ptr value_chunk      = f2counter__value_chunk(this, cause);
  f2scheduler_cmutex__lock(scheduler_cmutex, cause);
  s64 old_value__i = raw__chunk__bit64__elt(cause, value_chunk, 0);
  s64 new_value__i = old_value__i + relative_value__i;
  raw__chunk__bit64__elt__set(cause, value_chunk, 0, new_value__i);
  f2scheduler_cmutex__unlock(scheduler_cmutex, cause);
}

f2ptr f2__counter__decrement(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(counter, this);
  assert_argument_type(integer, value);
  s64 value__i = f2integer__i(value, cause);
  raw__counter__decrement(cause, this, value__i);
  return nil;
}
def_pcfunk2(counter__decrement, this, value,
	    "Decrements the value of the thread safe counter.",
	    return f2__counter__decrement(this_cause, this, value));


f2ptr raw__counter__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "counter"),
					       new__symbol(cause, "value"),             f2__counter__value(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__counter__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(counter,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__counter__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(counter__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this counter to the given terminal.",
	    return f2__counter__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2counter__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2counter__primobject_type__new(cause);
  {char* slot_name = "value";                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.value__funk);}
  {char* slot_name = "value";                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.value__set__funk);}
  {char* slot_name = "increment";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.increment__funk);}
  {char* slot_name = "decrement";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.decrement__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__primobject__counter__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // counter
  
  initialize_primobject_2_slot__defragment__fix_pointers(counter,
							 scheduler_cmutex,
							 value_chunk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.increment__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__increment);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.increment__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.decrement__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__decrement);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.decrement__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(counter__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk);
  
}

void f2__primobject__counter__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // counter
  
  initialize_primobject_2_slot(counter,
			       scheduler_cmutex,
			       value_chunk);
  
  {char* symbol_str = "value__set"; __funk2.globalenv.object_type.primobject.primobject_type_counter.value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(counter__value__set, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.value__set__funk = never_gc(cfunk);}
  {char* symbol_str = "value"; __funk2.globalenv.object_type.primobject.primobject_type_counter.value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(counter__value, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.value__funk = never_gc(cfunk);}
  {char* symbol_str = "increment"; __funk2.globalenv.object_type.primobject.primobject_type_counter.increment__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(counter__increment, this, relative_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.increment__funk = never_gc(cfunk);}
  {char* symbol_str = "decrement"; __funk2.globalenv.object_type.primobject.primobject_type_counter.decrement__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(counter__decrement, this, relative_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.decrement__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(counter__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_counter.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject__counter__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "counter", "", &f2__primobject__counter__reinitialize_globalvars, &f2__primobject__counter__defragment__fix_pointers);
  
  f2__primobject__counter__reinitialize_globalvars();
}

