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

#ifndef F2__CHUNK__H
#define F2__CHUNK__H

#include "f2_primfunks.h"

f2ptr raw__chunk__save(f2ptr cause, f2ptr this, f2ptr filename);
f2ptr  f2__chunk__save(f2ptr cause, f2ptr this, f2ptr filename);

f2ptr f2chunk__primobject_type__new_aux(f2ptr cause);

// **

void f2__chunk__reinitialize_globalvars();
void f2__chunk__initialize();

#endif // F2__CHUNK__H
