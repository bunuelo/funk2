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

// fiber_trigger

def_primobject_0_slot(fiber_trigger);

f2ptr raw__fiber_trigger__new(f2ptr cause) {
  return f2fiber_trigger__new(cause);
}

f2ptr f2__fiber_trigger__new(f2ptr cause) {
  return raw__fiber_trigger__new(cause);
}
def_pcfunk0(fiber_trigger__new, return f2__fiber_trigger__new(this_cause));


f2ptr raw__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  return raw__fiber_trigger_hash__unpause_trigger_fibers(cause, this);
}

f2ptr f2__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  if (! raw__fiber_trigger__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_trigger__trigger(cause, this);
}
def_pcfunk1(fiber_trigger__trigger, this, return f2__fiber_trigger__trigger(this_cause, this));


f2ptr f2fiber_trigger__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_trigger__primobject_type__new(cause);
  {char* slot_name = "trigger"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__funk);}
  return this;
}



// fiber_trigger_hash (a global ptypehash)

f2ptr f2__fiber_trigger_hash(f2ptr cause) {
  f2ptr fiber_trigger_hash = f2__environment__lookup_type_var_value(cause, global_environment(), new__symbol(cause, "variable"), new__symbol(cause, "fiber_trigger_hash"));
  if (raw__larva__is_type(cause, fiber_trigger_hash)) {
    fiber_trigger_hash = f2__ptypehash__new(cause);
    f2ptr result = f2__environment__add_type_var_value(cause, global_environment(), new__symbol(cause, "variable"), new__symbol(cause, "fiber_trigger_hash"), fiber_trigger_hash);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  } else {
    if (! raw__ptypehash__is_type(cause, fiber_trigger_hash)) {
      return f2larva__new(cause, 1, nil);
    }
  }
  return fiber_trigger_hash;
}


f2ptr raw__fiber_trigger_hash__add(f2ptr cause, f2ptr trigger, f2ptr fiber) {
  f2ptr fiber_trigger_hash = f2__fiber_trigger_hash(cause);
  if (raw__larva__is_type(cause, fiber_trigger_hash)) {
    return fiber_trigger_hash;
  }
  f2ptr fiber_set = raw__ptypehash__lookup(cause, fiber_trigger_hash, trigger);
  if (fiber_set == nil) {
    fiber_set = f2__set__new(cause);
    raw__ptypehash__add(cause, fiber_trigger_hash, trigger, fiber_set);
  }
  raw__set__add(cause, fiber_set, fiber);
  return nil;
}

f2ptr f2__fiber_trigger_hash__add(f2ptr cause, f2ptr trigger, f2ptr fiber) {
  if ((! raw__fiber_trigger__is_type(cause, trigger)) ||
      (! raw__fiber__is_type(cause, fiber))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_trigger_hash__add(cause, trigger, fiber);
}
def_pcfunk2(fiber_trigger_hash__add, trigger, fiber, return f2__fiber_trigger_hash__add(this_cause, trigger, fiber));


f2ptr raw__fiber_trigger_hash__unpause_trigger_fibers(f2ptr cause, f2ptr trigger) {
  f2ptr fiber_trigger_hash = f2__fiber_trigger_hash(cause);
  if (raw__larva__is_type(cause, fiber_trigger_hash)) {
    return fiber_trigger_hash;
  }
  f2ptr fiber_set = raw__ptypehash__lookup(cause, fiber_trigger_hash, trigger);
  if (fiber_set != nil) {
    set__iteration(cause, fiber_set, fiber,
		   if (! raw__fiber__is_type(cause, fiber)) {
		     return f2larva__new(cause, 1, nil);
		   }
		   f2__global_scheduler__add_fiber(cause, fiber));
    raw__ptypehash__add(cause, fiber_trigger_hash, trigger, nil);
  }
  return nil;
}


// **

void f2__primobject__fiber_trigger__reinitialize_globalvars() {
  __fiber_trigger__symbol = f2symbol__new(initial_cause(), strlen("fiber_trigger"), (u8*)"fiber_trigger");
}

void f2__primobject__fiber_trigger__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-fiber_trigger", "", &f2__primobject__fiber_trigger__reinitialize_globalvars);
  
  f2__primobject__fiber_trigger__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __fiber_trigger__symbol, nil);
  
  f2ptr cause = initial_cause();
  
  // fiber_trigger
  
  initialize_primobject_0_slot(fiber_trigger);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(fiber_trigger__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__funk = never_gc(cfunk);}
  
  {char* symbol_str = "trigger"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_trigger__trigger, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__funk = never_gc(cfunk);}
  
  {
    f2ptr result = f2__fiber_trigger_hash(cause);
    if (raw__larva__is_type(cause, result)) {
      error(nil, "f2__primobject__fiber_trigger__initialize error: initializing fiber_trigger_hash.");
    }
  }
  
  f2__primcfunk__init__2(fiber_trigger_hash__add, trigger, fiber, "Adds a fiber to a fiber_trigger's global activation set.");
  
}

