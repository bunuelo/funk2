// 
// Copyright (c) 2007-2008 Bo Morgan.
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

#ifndef F2__PRIMFUNKS__STDLIB__H
#define F2__PRIMFUNKS__STDLIB__H

//#define __USE_GNU

#include "f2_primfunks.h"

f2ptr f2__setenv(f2ptr cause, f2ptr name, f2ptr value, f2ptr overwrite);

void f2__primfunks__stdlib__reinitialize_globalvars();
void f2__primfunks__stdlib__initialize();

#endif // F2__PRIMFUNKS__STDLIB__H

