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

// traced_mutex

def_primobject_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack, fibers_waiting_for_lock);

f2ptr f2__traced_mutex__new(f2ptr cause) {
  f2ptr mutex                   = f2mutex__new(cause);
  f2ptr fiber_with_lock         = nil;
  f2ptr lock_stack              = nil;
  f2ptr fibers_waiting_for_lock = f2__ptypehash__new(cause);
  return f2traced_mutex__new(cause, mutex, fiber_with_lock, lock_stack, fibers_waiting_for_lock);
}
def_pcfunk0(traced_mutex__new, return f2__traced_mutex__new(this_cause));

f2ptr raw__traced_mutex__lock(f2ptr cause, f2ptr this) {
  f2ptr fiber                   = f2__this__fiber(cause);
  f2ptr fibers_waiting_for_lock = f2__traced_mutex__fibers_waiting_for_lock(cause, this);
  f2__ptypehash__add(cause, fibers_waiting_for_lock, fiber, f2bool__new(boolean__true));
  f2__mutex__lock(cause, f2__traced_mutex__mutex(cause, this));
  f2__ptypehash__remove(cause, fibers_waiting_for_lock, fiber);
  f2__traced_mutex__fiber_with_lock__set(cause, this, f2__this__fiber(cause));
  f2__traced_mutex__lock_stack__set(     cause, this, f2__fiber__stack_trace(cause, fiber));
  return nil;
}

f2ptr f2__traced_mutex__lock(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_mutex, this);
  return raw__traced_mutex__lock(cause, this);
}
def_pcfunk1(traced_mutex__lock, this, return f2__traced_mutex__lock(this_cause, this));


f2ptr raw__traced_mutex__unlock(f2ptr cause, f2ptr this) {
  if (! raw__mutex__is_locked(cause, f2__traced_mutex__mutex(cause, this))) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),     new__symbol(cause, "traced_mutex_already_unlocked"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "traced_mutex"), this);
    return f2larva__new(cause, 5467, f2__bug__new(cause, f2integer__new(cause, 5467), bug_frame));
  }
  f2__traced_mutex__fiber_with_lock__set(cause, this, nil);
  f2__traced_mutex__lock_stack__set(     cause, this, nil);
  f2__mutex__unlock(cause, f2__traced_mutex__mutex(cause, this));
  return nil;
}

f2ptr f2__traced_mutex__unlock(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_mutex, this);
  return raw__traced_mutex__unlock(cause, this);
}
def_pcfunk1(traced_mutex__unlock, this, return f2__traced_mutex__unlock(this_cause, this));


boolean_t raw__traced_mutex__trylock(f2ptr cause, f2ptr this) {
  boolean_t failure = raw__mutex__trylock(cause, f2__traced_mutex__mutex(cause, this));
  return failure;
}

f2ptr f2__traced_mutex__trylock(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_mutex, this);
  return f2bool__new(raw__traced_mutex__trylock(cause, this));
}
def_pcfunk1(traced_mutex__trylock, this, return f2__traced_mutex__trylock(this_cause, this));


boolean_t raw__traced_mutex__is_locked(f2ptr cause, f2ptr this) {
  return raw__mutex__is_locked(cause, f2__traced_mutex__mutex(cause, this));
}

f2ptr f2__traced_mutex__is_locked(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_mutex, this);
  return f2bool__new(raw__traced_mutex__is_locked(cause, this));
}
def_pcfunk1(traced_mutex__is_locked, this, return f2__traced_mutex__is_locked(this_cause, this));


f2ptr raw__traced_mutex__lock_stack_trace(f2ptr cause, f2ptr this) {
  return f2__fiber_stack_trace__new(cause, f2__traced_mutex__lock_stack(cause, this));
}

f2ptr f2__traced_mutex__lock_stack_trace(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_mutex, this);
  return raw__traced_mutex__lock_stack_trace(cause, this);
}
def_pcfunk1(traced_mutex__lock_stack_trace, this, return f2__traced_mutex__lock_stack_trace(this_cause, this));


f2ptr raw__traced_mutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"),       new__symbol(cause, "traced_mutex"),
						new__symbol(cause, "cause"),                   f2__ptype__cause(                         cause, this),
						new__symbol(cause, "mutex"),                   f2__traced_mutex__mutex(                  cause, this),
						new__symbol(cause, "fiber_with_lock"),         f2__traced_mutex__fiber_with_lock(        cause, this),
						new__symbol(cause, "lock_stack"),              f2__traced_mutex__lock_stack(             cause, this),
						new__symbol(cause, "fibers_waiting_for_lock"), f2__traced_mutex__fibers_waiting_for_lock(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__traced_mutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(traced_mutex,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__traced_mutex__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(traced_mutex__terminal_print_with_frame, this, terminal_print_frame, return f2__traced_mutex__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2traced_mutex__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2traced_mutex__primobject_type__new(cause);
  {char* slot_name = "lock";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__funk);}
  {char* slot_name = "unlock";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__funk);}
  {char* slot_name = "trylock";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__funk);}
  {char* slot_name = "is_locked";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__funk);}
  {char* slot_name = "lock_stack_trace";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock_stack_trace__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__primobject__traced_mutex__reinitialize_globalvars() {
  __traced_mutex__symbol = f2symbol__new(initial_cause(), strlen("traced_mutex"), (u8*)"traced_mutex");
}

void f2__primobject__traced_mutex__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-traced_mutex", "", &f2__primobject__traced_mutex__reinitialize_globalvars);
  
  f2__primobject__traced_mutex__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __traced_mutex__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // traced_mutex
  
  initialize_primobject_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack, fibers_waiting_for_lock);
  
  {char* symbol_str = "lock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_mutex__lock, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__funk = never_gc(cfunk);}
  {char* symbol_str = "unlock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_mutex__unlock, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__funk = never_gc(cfunk);}
  {char* symbol_str = "trylock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_mutex__trylock, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__funk = never_gc(cfunk);}
  {char* symbol_str = "is_locked"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_mutex__is_locked, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__funk = never_gc(cfunk);}
  {char* symbol_str = "lock_stack_trace"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock_stack_trace__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_mutex__lock_stack_trace, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock_stack_trace__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_mutex__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}

