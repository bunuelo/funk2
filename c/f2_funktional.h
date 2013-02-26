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

#ifndef F2__FUNKTIONAL__H
#define F2__FUNKTIONAL__H

#include "f2_primfunks.h"

boolean_t raw__exp__is_immutable(f2ptr cause, f2ptr this);
f2ptr      f2__exp__is_immutable(f2ptr cause, f2ptr this);
boolean_t raw__funkable__is_funktional(f2ptr cause, f2ptr this);
f2ptr      f2__funkable__is_funktional(f2ptr cause, f2ptr this);

#endif // F2__FUNKTIONAL__H

