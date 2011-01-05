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
#include "conceptnet.h"


def_ceframe1(conceptnet, conceptnet, width);

f2ptr raw__conceptnet__new(f2ptr cause, f2ptr width) {
  return f2conceptnew__new(cause, width);
}

f2ptr f2__conceptnet__new(f2ptr cause, f2ptr width) {
  if (! raw__integer__is_type(cause, width)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__conceptnet__new(cause, width);
}
export_cefunk1(conceptnet__new, width, 0, "Returns a new conceptnet object.");


// **

f2ptr f2__conceptnet__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(conceptnet__core_extension_ping, 0, "");

f2ptr f2__conceptnet__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "conceptnet"), f2__conceptnet_type__new(cause));
  status("conceptnet initialized.");
  return nil;
}
export_cefunk0(conceptnet__core_extension_initialize, 0, "");

f2ptr f2__conceptnet__core_extension_destroy(f2ptr cause) {
  status("conceptnet destroyed.");
  return nil;
}
export_cefunk0(conceptnet__core_extension_destroy, 0, "");


