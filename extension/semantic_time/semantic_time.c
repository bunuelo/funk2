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

#include "semantic_time.h"

def_ceframe1(semantic_time, semantic_time, value);

f2ptr raw__semantic_time__new(f2ptr cause, f2ptr value) {
  return f2semantic_time__new(cause, value);
}

f2ptr f2__semantic_time__new(f2ptr cause, f2ptr value) {
  if ((! raw__time__is_type(cause, value)) &&
      (! raw__eq(cause, new__symbol(cause, "before"), value)) &&
      (! raw__eq(cause, new__symbol(cause, "after"),  value)) &&
      (! raw__eq(cause, new__symbol(cause, "now"),    value))) {
    return f2larva__new(cause, 13516, nil);
  }
  return raw__semantic_time__new(cause, value);
}
export_cefunk1(semantic_time__new, value, 0, "Returns a new semantic_time object.  Possible initial values include any time object, or one of the symbols: before, after, or now.");


f2ptr f2__semantic_time_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_time_type__new(cause);
  //{f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "clear"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__clear")));}
  return this;
}



// **

f2ptr f2__semantic_time__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_time__core_extension__ping, 0, "");

f2ptr f2__semantic_time__core_extension__initialize(f2ptr cause) {
  status("semantic_time initialized.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__initialize, 0, "");

f2ptr f2__semantic_time__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_time"), f2__semantic_time_type__new_aux(cause));
  status("semantic_time types defined.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__define_types, 0, "");

f2ptr f2__semantic_time__core_extension__destroy(f2ptr cause) {
  status("semantic_time destroyed.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__destroy, 0, "");


