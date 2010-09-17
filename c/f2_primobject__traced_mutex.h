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

#ifndef F2__PRIMOBJECT__TRACED_MUTEX__TYPES__H
#define F2__PRIMOBJECT__TRACED_MUTEX__TYPES__H

// traced_mutex

typedef struct funk2_object_type__traced_mutex__slot_s funk2_object_type__traced_mutex__slot_t;
declare_object_type_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack, fibers_waiting_for_lock,
			   f2ptr lock__symbol;
			   f2ptr lock__funk;
			   f2ptr unlock__symbol;
			   f2ptr unlock__funk;
			   f2ptr trylock__symbol;
			   f2ptr trylock__funk;
			   f2ptr is_locked__symbol;
			   f2ptr is_locked__funk;
			   f2ptr lock_stack_trace__symbol;
			   f2ptr lock_stack_trace__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__TRACED_MUTEX__TYPES__H

#ifndef F2__PRIMOBJECT__TRACED_MUTEX__H
#define F2__PRIMOBJECT__TRACED_MUTEX__H

#include "f2_primobjects.h"

// traced_mutex

declare_primobject_4_slot(traced_mutex, mutex, fiber_with_lock, lock_stack, fibers_waiting_for_lock);

f2ptr      f2__traced_mutex__new(             f2ptr cause);
f2ptr     raw__traced_mutex__lock(            f2ptr cause, f2ptr this);
f2ptr      f2__traced_mutex__lock(            f2ptr cause, f2ptr this);
f2ptr     raw__traced_mutex__unlock(          f2ptr cause, f2ptr this);
f2ptr      f2__traced_mutex__unlock(          f2ptr cause, f2ptr this);
boolean_t raw__traced_mutex__trylock(         f2ptr cause, f2ptr this);
f2ptr      f2__traced_mutex__trylock(         f2ptr cause, f2ptr this);
boolean_t raw__traced_mutex__is_locked(       f2ptr cause, f2ptr this);
f2ptr      f2__traced_mutex__is_locked(       f2ptr cause, f2ptr this);
f2ptr      f2__traced_mutex__lock_stack_trace(f2ptr cause, f2ptr this);


f2ptr f2traced_mutex__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject__traced_mutex__initialize();

#endif // F2__PRIMOBJECT__TRACED_MUTEX__H

