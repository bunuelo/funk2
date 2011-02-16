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

#include "../../c/funk2.h"
#include "timeline.h"


// timeline

def_ceframe1(timeline, timeline, width);


f2ptr raw__timeline__new(f2ptr cause, f2ptr timeline_events) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),  new__symbol(cause, "timeline"),
					    new__symbol(cause, "width"), width));
}

f2ptr f2__timeline__new(f2ptr cause, f2ptr width) {
  if (! raw__integer__is_type(cause, width)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__timeline__new(cause, width);
}
export_cefunk1(timeline__new, width, 0, "Returns a new timeline object.");


f2ptr f2__timeline_type__new_aux(f2ptr cause) {
  f2ptr this = f2__timeline_type__new(cause);
  return this;
}



// **

f2ptr f2__timeline__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(timeline__core_extension__ping, 0, "");

f2ptr f2__timeline__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "cairo"), new__symbol(cause, "cairo__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  f2__add_type(cause, new__symbol(cause, "timeline"), f2__timeline_type__new_aux(cause));
  status("timeline initialized.");
  return nil;
}
export_cefunk0(timeline__core_extension__initialize, 0, "");

f2ptr f2__timeline__core_extension__destroy(f2ptr cause) {
  status("timeline destroyed.");
  return nil;
}
export_cefunk0(timeline__core_extension__destroy, 0, "");


