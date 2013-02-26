// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__PROCESSOR__TYPES__H
#define F2__PROCESSOR__TYPES__H

#include "f2_primobjects.h"

typedef struct funk2_object_type__processor__slot_s funk2_object_type__processor__slot_t;

// processor

declare_object_type_9_slot(processor,
			   scheduler,
			   processor_thread,
			   active_fibers_cmutex,
			   active_fibers_count_chunk,
			   active_fibers,
			   active_fibers_iter,
			   pool_index,
			   desc,
			   bytecode_count,
			   
			   f2ptr active_fibers_count__symbol;
			   f2ptr active_fibers_count__funk;
			   f2ptr add_active_fiber__symbol;
			   f2ptr add_active_fiber__funk;
			   f2ptr remove_active_fiber__symbol;
			   f2ptr remove_active_fiber__funk;
			   f2ptr current_active_fiber__symbol;
			   f2ptr current_active_fiber__funk;
			   f2ptr increment_current_active_fiber__symbol;
			   f2ptr increment_current_active_fiber__funk;
			   f2ptr reset_current_active_fiber__symbol;
			   f2ptr reset_current_active_fiber__funk;
			   f2ptr active_fibers__length__symbol;
			   f2ptr active_fibers__length__funk;
			   f2ptr active_fibers__contains__symbol;
			   f2ptr active_fibers__contains__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PROCESSOR__TYPES__H



#ifndef F2__PROCESSOR__H
#define F2__PROCESSOR__H

// processor

declare_primobject_9_slot(processor,
			  scheduler,
			  processor_thread,
			  active_fibers_cmutex,
			  active_fibers_count_chunk,
			  active_fibers,
			  active_fibers_iter,
			  pool_index,
			  desc,
			  bytecode_count);

f2ptr      f2__processor__new                                          (f2ptr cause, f2ptr scheduler, f2ptr pool_index, f2ptr desc);
u64       raw__processor__active_fibers_count__thread_unsafe           (f2ptr cause, f2ptr this);
u64       raw__processor__scheduler_active_fibers_count                (f2ptr cause, f2ptr this);
u64       raw__processor__active_fibers_count                          (f2ptr cause, f2ptr this);
f2ptr      f2__processor__active_fibers_count                          (f2ptr cause, f2ptr this);
void      raw__processor__active_fibers_count__set__thread_unsafe      (f2ptr cause, f2ptr this, u64 active_fibers_count__i);
boolean_t raw__processor__add_active_fiber__thread_unsafe              (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__scheduler_add_active_fiber                   (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__add_active_fiber                             (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__processor__add_active_fiber                             (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__remove_active_fiber__thread_unsafe           (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__remove_active_fiber                          (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__processor__remove_active_fiber                          (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__try_remove_active_fiber                      (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__try_remove_any_active_fiber                  (f2ptr cause, f2ptr this);
u64       raw__processor__active_fibers__length                        (f2ptr cause, f2ptr this);
f2ptr      f2__processor__active_fibers__length                        (f2ptr cause, f2ptr this);
boolean_t raw__processor__active_fibers__contains__thread_unsafe       (f2ptr cause, f2ptr this, f2ptr fiber);
boolean_t raw__processor__active_fibers__contains                      (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__processor__active_fibers__contains                      (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__processor__current_active_fiber__thread_unsafe          (f2ptr cause, f2ptr this);
f2ptr     raw__processor__current_active_fiber                         (f2ptr cause, f2ptr this);
f2ptr      f2__processor__current_active_fiber                         (f2ptr cause, f2ptr this);
boolean_t raw__processor__increment_current_active_fiber__thread_unsafe(f2ptr cause, f2ptr this);
boolean_t raw__processor__increment_current_active_fiber               (f2ptr cause, f2ptr this);
f2ptr      f2__processor__increment_current_active_fiber               (f2ptr cause, f2ptr this);
boolean_t raw__processor__reset_current_active_fiber__thread_unsafe    (f2ptr cause, f2ptr this);
boolean_t raw__processor__reset_current_active_fiber                   (f2ptr cause, f2ptr this);
f2ptr      f2__processor__reset_current_active_fiber                   (f2ptr cause, f2ptr this);
f2ptr     raw__processor__terminal_print_with_frame                    (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__processor__terminal_print_with_frame                    (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2processor__primobject_type__new_aux(f2ptr cause);


u64   raw__processor__active_fibers__length (f2ptr cause, f2ptr processor);
f2ptr    f2processor__execute_next_bytecodes(f2ptr processor, f2ptr cause);
void  raw__processor__reinitialize          (f2ptr cause, f2ptr this);
void  raw__processor__clean                 (f2ptr cause, f2ptr this);


// **

void f2__processor__reinitialize_globalvars();
void f2__processor__initialize();
void f2__processor__destroy();

#endif // F2__PROCESSOR__H

