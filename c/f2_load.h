// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__LOAD__H
#define F2__LOAD__H

#include "f2_reader.h"
#include "f2_compile.h"
#include "f2_fiber.h"

f2ptr raw__load(f2ptr cause, f2ptr filename);
f2ptr  f2__load(f2ptr cause, f2ptr filename);
def_pcfunk__prototype__declare(pcfunk__load);

void f2__load__initialize();

#endif // F2__LOAD__H
