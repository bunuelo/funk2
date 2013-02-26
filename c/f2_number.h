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

#ifndef F2__NUMBER__H
#define F2__NUMBER__H

#include "f2_global.h"

typedef struct funk2_number_globalvars_s {
  f2ptr as__double__symbol;
  f2ptr multiplied_by__symbol;
  f2ptr divided_by__symbol;
  f2ptr plus__symbol;
  f2ptr minus__symbol;
  f2ptr is_greater_than__symbol;
  f2ptr is_less_than__symbol;
  f2ptr is_numerically_equal_to__symbol;
  f2ptr square_root__symbol;
  f2ptr modulo__symbol;
} funk2_number_globalvars_t;

f2ptr f2__is_greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__is_less_than(f2ptr cause, f2ptr this, f2ptr that);

f2ptr  raw__number__as__double(f2ptr cause, f2ptr this);
f2ptr   f2__number__as__double(f2ptr cause, f2ptr this);
double raw__number__as__raw_double(f2ptr cause, f2ptr this);
f2ptr   f2__number__multiplied_by(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__divided_by(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__plus(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__minus(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__is_greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__is_less_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr   f2__number__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that);
f2ptr   f2__number__square_root(f2ptr cause, f2ptr this);
f2ptr   f2__number__modulo(f2ptr cause, f2ptr this, f2ptr that);

// **

void f2__number__reinitialize_globalvars();
void f2__number__initialize();

#endif // F2__NUMBER__H

