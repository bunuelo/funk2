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

f2ptr f2__core_extension_initialize(f2ptr cause) {
  printf("\nmindmon: core_extension_initialize here... and how."); fflush(stdout);
  return nil;
}

f2ptr f2__core_extension_destroy(f2ptr cause) {
  printf("\nmindmon: core_extension_destroy here."); fflush(stdout);
  return nil;
}

export_cefunk0(core_extension_initialize);
export_cefunk0(core_extension_destroy);

