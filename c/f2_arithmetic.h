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

#ifndef F2__ARITHMETIC__H
#define F2__ARITHMETIC__H

boolean_t raw__number__is_type(f2ptr cause, f2ptr exp);
f2ptr      f2__number__is_type(f2ptr cause, f2ptr exp);
double    raw__number__as__double(f2ptr cause, f2ptr this);
f2ptr      f2__number__as__double(f2ptr cause, f2ptr this);

// **

void f2__arithmetic__initialize();

#endif // F2__ARITHMETIC__H

