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

#ifndef F2__EXTENSION__FIBER_TRIGGER__H
#define F2__EXTENSION__FIBER_TRIGGER__H

#include "../../c/funk2.h"

// fiber_trigger

def_header_ceframe0(fiber_trigger, fiber_trigger);

f2ptr raw__fiber_trigger__new                      (f2ptr cause);
f2ptr  f2__fiber_trigger__new                      (f2ptr cause);
f2ptr raw__fiber_trigger__trigger                  (f2ptr cause, f2ptr this);
f2ptr  f2__fiber_trigger__trigger                  (f2ptr cause, f2ptr this);
f2ptr raw__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__fiber_trigger_type__new_aux(f2ptr cause);


// fiber_trigger_hash (a global ptypehash)

f2ptr  f2__fiber_trigger_hash                        (f2ptr cause);
f2ptr raw__fiber_trigger_hash__add                   (f2ptr cause, f2ptr trigger, f2ptr fiber);
f2ptr  f2__fiber_trigger_hash__add                   (f2ptr cause, f2ptr trigger, f2ptr fiber);
f2ptr raw__fiber_trigger_hash__unpause_trigger_fibers(f2ptr cause, f2ptr trigger);



// **

f2ptr f2__fiber_trigger__core_extension_ping      (f2ptr cause);
f2ptr f2__fiber_trigger__core_extension_initialize(f2ptr cause);
f2ptr f2__fiber_trigger__core_extension_destroy   (f2ptr cause);

#endif // F2__EXTENSION__FIBER_TRIGGER__H

