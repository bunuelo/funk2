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

#ifndef F2__CORE_EXTENSION__TYPES__H
#define F2__CORE_EXTENSION__TYPES__H

// core_extension

typedef struct funk2_object_type__core_extension__slot_s funk2_object_type__core_extension__slot_t;
struct funk2_object_type__core_extension__slot_s {
  f2ptr initialize__symbol;
  f2ptr initialize__funk;
  f2ptr destroy__symbol;
  f2ptr destroy__funk;
  f2ptr assure_initialized__symbol;
  f2ptr assure_initialized__funk;
};

#endif // F2__CORE_EXTENSION__TYPES__H

#ifndef F2__CORE_EXTENSION__H
#define F2__CORE_EXTENSION__H

#include "f2_primfunks.h"



f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause);


f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause);

// **

void f2__core_extension__initialize();


#endif // F2__CORE_EXTENSION__H

