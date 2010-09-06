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

// traced_mutex

def_primobject_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack_trace, fibers_waiting_for_lock);

f2ptr f2__traced_mutex__new(f2ptr cause) {
  f2ptr mutex                   = f2mutex__new(cause);
  f2ptr fiber_with_lock         = nil;
  f2ptr lock_stack_trace        = nil;
  f2ptr fibers_waiting_for_lock = nil;
  return f2traced_mutex__new(cause, mutex, fiber_with_lock, lock_stack_trace, fibers_waiting_for_lock);
}
def_pcfunk0(traced_mutex__new, return f2__traced_mutex__new(this_cause));

f2ptr raw__traced_mutex__lock(f2ptr cause, f2ptr this) {
  f2__mutex__lock(cause, f2__traced_mutex__mutex(cause, this));
  return nil;
}

f2ptr f2__traced_mutex__lock(f2ptr cause, f2ptr this) {
  if (! raw__traced_mutex__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__traced_mutex__lock(cause, this);
}
def_pcfunk1(traced_mutex__lock, this, return f2__traced_mutex__lock(this_cause, this));


f2ptr raw__traced_mutex__unlock(f2ptr cause, f2ptr this) {
  f2__mutex__unlock(cause, f2__traced_mutex__mutex(cause, this));
  return nil;
}

f2ptr f2__traced_mutex__unlock(f2ptr cause, f2ptr this) {
  if (! raw__traced_mutex__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__traced_mutex__unlock(cause, this);
}
def_pcfunk1(traced_mutex__unlock, this, return f2__traced_mutex__unlock(this_cause, this));


boolean_t raw__traced_mutex__trylock(f2ptr cause, f2ptr this) {
  boolean_t failure = raw__mutex__trylock(cause, f2traced_mutex__mutex(this, cause));
  return failure;
}

f2ptr f2__traced_mutex__trylock(f2ptr cause, f2ptr this) {
  if (! raw__traced_mutex__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__traced_mutex__trylock(cause, this));
}
def_pcfunk1(traced_mutex__trylock, this, return f2__traced_mutex__trylock(this_cause, this));


boolean_t raw__traced_mutex__is_locked(f2ptr cause, f2ptr this) {
  return raw__mutex__is_locked(cause, f2traced_mutex__mutex(this, cause));
}

f2ptr f2__traced_mutex__is_locked(f2ptr cause, f2ptr this) {
  if (! raw__traced_mutex__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__traced_mutex__is_locked(cause, this));
}
def_pcfunk1(traced_mutex__is_locked, this, return f2__traced_mutex__is_locked(this_cause, this));


f2ptr f2traced_mutex__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2traced_mutex__primobject_type__new(cause);
  {char* slot_name = "lock";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__funk);}
  {char* slot_name = "unlock";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__funk);}
  {char* slot_name = "trylock";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__funk);}
  {char* slot_name = "is_locked"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__funk);}
  return this;
}


// **

void f2__primobject_traced_mutex__reinitialize_globalvars() {
  __traced_mutex__symbol = f2symbol__new(initial_cause(), strlen("traced_mutex"), (u8*)"traced_mutex");
}

void f2__primobject_traced_mutex__initialize() {
  f2__primobject_traced_mutex__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __traced_mutex__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // traced_mutex
  
  initialize_primobject_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack_trace, fibers_waiting_for_lock);
  
  {char* symbol_str = "lock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_mutex__lock, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.lock__funk = never_gc(cfunk);}
  {char* symbol_str = "unlock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_mutex__unlock, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.unlock__funk = never_gc(cfunk);}
  {char* symbol_str = "trylock"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_mutex__trylock, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.trylock__funk = never_gc(cfunk);}
  {char* symbol_str = "is_locked"; __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_mutex__is_locked, this, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_traced_mutex.is_locked__funk = never_gc(cfunk);}
  
}

