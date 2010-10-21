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

#include "../../c/funk2.h"

#define CAUSALITY_DYLIB "extension/causality/.libs/libcausality.so"

f2ptr f2__causality_type__new(f2ptr cause) {
  f2ptr type = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  f2__primobject_type__add_slot_type(cause, type, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), new__core_extension_funk(cause, CAUSALITY_DYLIB, causality__terminal_print_with_frame));
  f2__primobject_type__add_slot_type(cause, type, new__symbol(cause, "get"),     new__symbol(cause, "cause_set"),                 new__core_extension_funk(cause, CAUSALITY_DYLIB, causality__cause_set));
  f2__primobject_type__add_slot_type(cause, type, new__symbol(cause, "set"),     new__symbol(cause, "cause_set"),                 new__core_extension_funk(cause, CAUSALITY_DYLIB, causality__cause_set__set));
  return type;
}

f2ptr f2__causality__new(f2ptr cause) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),      new__symbol(cause, "causality"),
					    new__symbol(cause, "cause_set"), f2__set__new(cause)));
}
export_cefunk0(causality__new, 0, "");

f2ptr f2__causality__cause_set(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cause_set"), f2larva__new(cause, 1324, nil));
}
export_cefunk1(causality__cause_set, this, 0, "");

f2ptr f2__causality__cause_set__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "cause_set"), value);
}
export_cefunk2(causality__cause_set__set, this, value, 0, "");

f2ptr f2__causality__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "causality"),
					       new__symbol(cause, "cause_set"),         f2__causality__cause_set(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}
export_cefunk2(causality__terminal_print_with_frame, this, terminal_print_frame, 0, "");


f2ptr f2__causality__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "causality"), f2__causality_type__new(cause));
}
export_cefunk0(causality__core_extension_initialize, 0, "");

f2ptr f2__causality__core_extension_destroy(f2ptr cause) {
}
export_cefunk0(causality__core_extension_destroy, 0, "");

