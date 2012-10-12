// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "pattern_match.h"

f2ptr raw__pattern_match__test(f2ptr cause) {
  return nil;
}

f2ptr f2__pattern_match__test(f2ptr cause) {
  return raw__pattern_match__test(cause);
}
export_cefunk0(pattern_match__test, 0, "Tests the pattern match core extension.");



// **

f2ptr f2__pattern_match__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(pattern_match__core_extension__ping, 0, "");

f2ptr f2__pattern_match__core_extension__initialize(f2ptr cause) {
  status("pattern_match initialized.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__initialize, 0, "");

f2ptr f2__pattern_match__core_extension__define_types(f2ptr cause) {
  status("pattern_match types defined.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__define_types, 0, "");

f2ptr f2__pattern_match__core_extension__destroy(f2ptr cause) {
  status("pattern_match destroyed.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__destroy, 0, "");


