// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__OBJECT__H
#define F2__OBJECT__H

#include "f2_primfunks.h"
#include "f2_ptypes.h"
#include "f2_primobjects.h"
#include "f2_primobject_type_handler.h"

typedef struct funk2_object_types_s {
  funk2_ptype_object_types_t      ptype;
  funk2_primobject_object_types_t primobject;
} funk2_object_types_t;

// **

void f2__object__reinitialize_globalvars();
void f2__object__initialize();

#endif // F2__OBJECT__H

