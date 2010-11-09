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

f2ptr raw__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  s64 width__i  = f2integer__i(width,  cause);
  s64 height__i = f2integer__i(height, cause);
  if ((width__i < 0) || (height__i < 0)) {
    return f2larva__new(cause, 2, nil);
  }
  if (rgb_data == nil) {
    rgb_data = raw__chunk__new(cause, 3 * width__i * height__i);
  } else {
    s64 rgb_data__length = f2chunk__length(rgb_data, cause);
    if (rgb_data__length != 3 * width__i * height__i) {
      return f2larva__new(cause, 3, nil);
    }
  }
  return f2__frame__new(cause, f2list6__new(cause,
					    new__symbol(cause, "width"),    width,
					    new__symbol(cause, "height"),   height,
					    new__symbol(cause, "rgb_data"), rgb_data));
}

f2ptr f2__image__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      ((rgb_data != nil) && (! raw__chunk__is_type(cause, rgb_data)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__image__new(cause, width, height, rgb_data);
}
export_cefunk3(image__new, width, height, rgb_data, 0, "Returns a new image object.  rgb_data can be nil, in which case a black image is returned.");



f2ptr f2__image__core_extension_initialize(f2ptr cause) {
  printf("\nimage initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_initialize, 0, "");

f2ptr f2__image__core_extension_destroy(f2ptr cause) {
  printf("\nimage destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(image__core_extension_destroy, 0, "");


