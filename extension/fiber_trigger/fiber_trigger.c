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

def_ceframe0(semantic_knowledge_base, fiber_trigger);

f2ptr raw__fiber_trigger__new(f2ptr cause) {
  return f2fiber_trigger__new(cause);
}

f2ptr f2__fiber_trigger__new(f2ptr cause) {
  return raw__fiber_trigger__new(cause);
}
export_cefunk0(fiber_trigger__new, 0, "Returns a new fiber_trigger object.");


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
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "fiber_trigger"), new__symbol(cause, "fiber_trigger__terminal_print_with_frame")));}
  return this;
}


// **

f2ptr f2__fiber_trigger__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_ping, 0, "");

f2ptr f2__fiber_trigger__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "fiber_trigger"), f2__fiber_trigger_type__new_aux(cause));
  status("fiber_trigger initialized.");
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_initialize, 0, "");

f2ptr f2__fiber_trigger__core_extension_destroy(f2ptr cause) {
  status("fiber_trigger destroyed.");
  return nil;
}
export_cefunk0(fiber_trigger__core_extension_destroy, 0, "");


