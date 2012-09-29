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

#ifndef F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H
#define F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H

// fiber_trigger

typedef struct funk2_object_type__fiber_trigger__slot_s funk2_object_type__fiber_trigger__slot_t;
declare_object_type_2_slot(fiber_trigger, cmutex, waiting_fiber_set,
			   f2ptr trigger__symbol;
			   f2ptr trigger__funk;
			   f2ptr add_waiting_fiber__symbol;
			   f2ptr add_waiting_fiber__funk;
			   f2ptr add_waiting_fiber_and_remove_from_scheduler__symbol;
			   f2ptr add_waiting_fiber_and_remove_from_scheduler__funk;
			   f2ptr trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__symbol;
			   f2ptr trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__funk;
			   f2ptr remove_from_scheduler_add_waiting_fiber_unlock_traced_cmutex_and_trigger_other__symbol;
			   f2ptr remove_from_scheduler_add_waiting_fiber_unlock_traced_cmutex_and_trigger_other__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__FIBER_TRIGGER__TYPES__H

#ifndef F2__PRIMOBJECT__FIBER_TRIGGER__H
#define F2__PRIMOBJECT__FIBER_TRIGGER__H

#include "f2_primobjects.h"

// fiber_trigger

declare_primobject_2_slot(fiber_trigger, cmutex, waiting_fiber_set);

f2ptr raw__fiber_trigger__new                                                                           (f2ptr cause);
f2ptr  f2__fiber_trigger__new                                                                           (f2ptr cause);
void  raw__fiber_trigger__add_waiting_fiber                                                             (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr  f2__fiber_trigger__add_waiting_fiber                                                             (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler                                   (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr  f2__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler                                   (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr raw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure  (f2ptr cause, f2ptr this, f2ptr traced_cmutex, f2ptr fiber);
f2ptr  f2__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure  (f2ptr cause, f2ptr this, f2ptr traced_cmutex, f2ptr fiber);
f2ptr raw__fiber_trigger__remove_from_scheduler_add_waiting_fiber_unlock_traced_cmutex_and_trigger_other(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr traced_cmutex, f2ptr other);
f2ptr  f2__fiber_trigger__remove_from_scheduler_add_waiting_fiber_unlock_traced_cmutex_and_trigger_other(f2ptr cause, f2ptr this, f2ptr fiber, f2ptr traced_cmutex, f2ptr other);
f2ptr raw__fiber_trigger__trigger                                                                       (f2ptr cause, f2ptr this);
f2ptr  f2__fiber_trigger__trigger                                                                       (f2ptr cause, f2ptr this);

f2ptr f2fiber_trigger__primobject_type__new_aux(f2ptr cause);


// **

void f2__primobject__fiber_trigger__reinitialize_globalvars();
void f2__primobject__fiber_trigger__initialize();

#endif // F2__PRIMOBJECT__FIBER_TRIGGER__H

