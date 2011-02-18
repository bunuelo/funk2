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

#include "propogator.h"

def_ceframe1(propogator, propogator_cell, value);

f2ptr raw__propogator_cell__new(f2ptr cause) {
  return f2propogator_cell__new(cause, nil);
}

f2ptr f2__propogator_cell__new(f2ptr cause) {
  return raw__propogator_cell__new(cause);
}
def_cefunk0(propogator_cell__new, 0, "Returns a new propogator_cell object.");


// **

f2ptr f2__propogator__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(propogator__core_extension__ping, 0, "");

f2ptr f2__propogator__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "propogator"), f2__propogator_cell_type__new(cause));
  status("propogator initialized.");
  return nil;
}
export_cefunk0(propogator__core_extension__initialize, 0, "");

f2ptr f2__propogator__core_extension__destroy(f2ptr cause) {
  status("propogator destroyed.");
  return nil;
}
export_cefunk0(propogator__core_extension__destroy, 0, "");


