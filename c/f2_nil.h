// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__NIL__TYPES__H
#define F2__NIL__TYPES__H

#include "f2_global.h"

typedef struct funk2_object_type__nil__slot_s funk2_object_type__nil__slot_t;

struct funk2_object_type__nil__slot_s {
  f2ptr as__string__symbol;
  f2ptr as__string__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
};

#endif // F2__NIL__TYPES__H


#ifndef F2__NIL__H
#define F2__NIL__H

f2ptr     raw__nil__as__string               (f2ptr cause, f2ptr this);
boolean_t raw__nil__is_type                  (f2ptr cause, f2ptr this);
f2ptr      f2__nil__as__string               (f2ptr cause, f2ptr this);
f2ptr     raw__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__nil__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2nil__primobject_type__new(f2ptr cause);


// **

void f2__nil__initialize();

#endif // F2__NIL__H

