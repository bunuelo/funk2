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

#ifndef F2__PRIMOBJECT__COUNTER__TYPES__H
#define F2__PRIMOBJECT__COUNTER__TYPES__H

// counter

typedef struct funk2_object_type__counter__slot_s funk2_object_type__counter__slot_t;
declare_object_type_2_slot(counter,
			   cmutex,
			   value_chunk,
			   f2ptr value__symbol;
			   f2ptr value__funk;
			   f2ptr value__set__symbol;
			   f2ptr value__set__funk;
			   f2ptr increment__symbol;
			   f2ptr increment__funk;
			   f2ptr decrement__symbol;
			   f2ptr decrement__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__COUNTER__TYPES__H


#ifndef F2__PRIMOBJECT__COUNTER__H
#define F2__PRIMOBJECT__COUNTER__H

#include "f2_primfunks.h"

declare_primobject_2_slot(counter,
			  cmutex,
			  value_chunk);

f2ptr raw__counter__new       (f2ptr cause);
f2ptr  f2__counter__new       (f2ptr cause);
f2ptr raw__counter__value     (f2ptr cause, f2ptr this);
f2ptr  f2__counter__value     (f2ptr cause, f2ptr this);
void  raw__counter__value__set(f2ptr cause, f2ptr this, s64 value__i);
f2ptr  f2__counter__value__set(f2ptr cause, f2ptr this, f2ptr value);
void  raw__counter__increment (f2ptr cause, f2ptr this, s64 relative_value__i);
f2ptr  f2__counter__increment (f2ptr cause, f2ptr this, f2ptr relative_value);
void  raw__counter__decrement (f2ptr cause, f2ptr this, s64 relative_value__i);
f2ptr  f2__counter__decrement (f2ptr cause, f2ptr this, f2ptr relative_value);

f2ptr f2counter__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject__counter__reinitialize_globalvars();
void f2__primobject__counter__initialize();


#endif // F2__PRIMOBJECT__COUNTER__H

