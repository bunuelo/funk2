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

#include "fiber_trigger.h"


// fiber_trigger

def_ceframe0(fiber_trigger, fiber_trigger);

f2ptr raw__fiber_trigger__new(f2ptr cause) {
  return f2fiber_trigger__new(cause);
}

f2ptr f2__fiber_trigger__new(f2ptr cause) {
  return raw__fiber_trigger__new(cause);
}
export_cefunk0(fiber_trigger__new, 0, "Returns a new fiber_trigger object.");


f2ptr raw__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  return raw__fiber_trigger_hash__unpause_trigger_fibers(cause, this);
}

f2ptr f2__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  if (! raw__fiber_trigger__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_trigger__trigger(cause, this);
}
export_cefunk1(fiber_trigger__trigger, this, 0, "Unpauses all fibers that are globally registered to respond to the triggering of this fiber_trigger object.");


f2ptr raw__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list2__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "fiber_trigger")));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__fiber_trigger__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__fiber_trigger__terminal_print_with_frame(cause, this, terminal_print_frame);
}
export_cefunk2(fiber_trigger__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__fiber_trigger_type__new_aux(f2ptr cause) {
  f2ptr this = f2__fiber_trigger_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "trigger"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "fiber_trigger"), new__symbol(cause, "fiber_trigger__trigger")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "fiber_trigger"), new__symbol(cause, "fiber_trigger__terminal_print_with_frame")));}
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
export_cefunk2(fiber_trigger_hash__add, trigger, fiber, 0, "Adds a fiber to a fiber_trigger's global activation set.");




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
		   f2__fiber__paused__set(cause, fiber, nil);
		   fibers = f2cons__new(cause, fiber, fibers));
    raw__ptypehash__add(cause, fiber_trigger_hash, trigger, nil);
  }
  return nil;
}




// **

f2ptr f2__fiber_trigger__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_ping, 0, "");

f2ptr f2__fiber_trigger__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "fiber_trigger"), f2__fiber_trigger_type__new_aux(cause));
  {
    f2ptr result = f2__fiber_trigger_hash(cause);
    if (! raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("fiber_trigger initialized.");
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_initialize, 0, "");

f2ptr f2__fiber_trigger__core_extension_destroy(f2ptr cause) {
  status("fiber_trigger destroyed.");
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_destroy, 0, "");


