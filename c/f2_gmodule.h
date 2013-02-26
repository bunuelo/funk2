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

#ifndef F2__GMODULE__H
#define F2__GMODULE__H

#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primobject__environment.h"
#include "f2_compile.h"
#include "f2_time.h"

boolean_t raw__gmodule__supported();
f2ptr      f2__gmodule__supported(f2ptr cause);
u8*       raw__gmodule__build_path(u8* directory, u8* module_name);
f2ptr      f2__gmodule__build_path(f2ptr cause, f2ptr directory, f2ptr module_name);
ptr       raw__gmodule__open(u8* filename, u64 flags);
f2ptr      f2__gmodule__open(f2ptr cause, f2ptr filename, f2ptr flags);
ptr       raw__gmodule__symbol(ptr module, u8* symbol_name);
f2ptr      f2__gmodule__symbol(f2ptr cause, f2ptr module, f2ptr symbol_name);
u8*       raw__gmodule__name(ptr module);
f2ptr      f2__gmodule__name(f2ptr cause, f2ptr module);
void      raw__gmodule__make_resident(ptr module);
f2ptr      f2__gmodule__make_resident(f2ptr cause, f2ptr module);
boolean_t raw__gmodule__close(ptr module);
f2ptr      f2__gmodule__close(f2ptr cause, f2ptr module);
u8*       raw__gmodule__error();
f2ptr      f2__gmodule__error(f2ptr cause);

// **

void f2__gmodule__reinitialize_globalvars();
void f2__gmodule__initialize();

#endif // F2__GMODULE__H

