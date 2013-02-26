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

#ifndef F2__MATH__H
#define F2__MATH__H

#include "f2_primfunks.h"


// double

double raw__double__log(f2ptr cause, double this);
f2ptr   f2__double__log(f2ptr cause, f2ptr this);


// integer

double raw__integer__log(f2ptr cause, s64 this);
f2ptr   f2__integer__log(f2ptr cause, f2ptr this);


// general

f2ptr f2__log(f2ptr cause, f2ptr exp);


// **

void f2__math__reinitialize_globalvars();
void f2__math__initialize();

#endif // F2__MATH__H

