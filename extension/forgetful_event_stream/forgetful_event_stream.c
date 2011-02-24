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

#include "forgetful_event_stream.h"

def_ceframe1(forgetful_event_stream, forgetful_event_stream, important_iterator_set);

f2ptr raw__forgetful_event_stream__new(f2ptr cause) {
  f2ptr this = f2__event_stream__new(cause);
  f2ptr important_iterator_set = f2__set__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "type"),                   new__symbol(cause, "forgetful_event_stream"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "important_iterator_set"), important_iterator_set);
  return this;
}

f2ptr f2__forgetful_event_stream__new(f2ptr cause) {
  return raw__forgetful_event_stream__new(cause);
}
export_cefunk0(forgetful_event_stream__new, 0, "Returns a new forgetful_event_stream object.");


f2ptr f2__forgetful_event_stream_type__new_aux(f2ptr cause) {
  f2ptr this = f2__forgetful_event_stream_type__new(cause);
  f2__primobject_type__parents__set(cause, this, f2list1__new(cause, new__symbol(cause, "event_stream")));
  return this;
}



// **

f2ptr f2__forgetful_event_stream__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__ping, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "event_stream"), new__symbol(cause, "event_stream__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  status("forgetful_event_stream initialized.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__initialize, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "forgetful_event_stream"), f2__forgetful_event_stream_type__new_aux(cause));
  status("forgetful_event_stream types defined.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__define_types, 0, "");

f2ptr f2__forgetful_event_stream__core_extension__destroy(f2ptr cause) {
  status("forgetful_event_stream destroyed.");
  return nil;
}
export_cefunk0(forgetful_event_stream__core_extension__destroy, 0, "");


