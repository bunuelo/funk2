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

#ifndef F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H
#define F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H

// fiber_trigger

typedef struct funk2_object_type__fiber_trigger__slot_s funk2_object_type__fiber_trigger__slot_t;
declare_object_type_1_slot(fiber_trigger, test,
			   );

#endif // F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H

#ifndef F2__PRIMOBJECT__FIBER_TRIGGER__H
#define F2__PRIMOBJECT__FIBER_TRIGGER__H

#include "f2_primobjects.h"

// fiber_trigger

declare_primobject_1_slot(fiber_trigger, test);

f2ptr raw__fiber_trigger__new(f2ptr cause);
f2ptr  f2__fiber_trigger__new(f2ptr cause);


f2ptr f2fiber_trigger__primobject_type__new_aux(f2ptr cause);


// **

void f2__primobject__fiber_trigger__reinitialize_globalvars();
void f2__primobject__fiber_trigger__initialize();

#endif // F2__PRIMOBJECT__FIBER_TRIGGER__H

