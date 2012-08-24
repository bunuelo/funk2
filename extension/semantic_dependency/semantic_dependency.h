// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__EXTENSION__SEMANTIC_DEPENDENCY__H
#define F2__EXTENSION__SEMANTIC_DEPENDENCY__H

#include "../semantic_object/semantic_object.h"


// **

f2ptr f2__semantic_dependency__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_dependency__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_dependency__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_DEPENDENCY__H

