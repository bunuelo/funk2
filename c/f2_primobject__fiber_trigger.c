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

#include "funk2.h"

// fiber_trigger

def_primobject_2_slot(fiber_trigger, cmutex, waiting_fiber_set);

f2ptr raw__fiber_trigger__new(f2ptr cause) {
  f2ptr cmutex            = f2cmutex__new(cause);
  f2ptr waiting_fiber_set = f2__set__new(cause);
  return f2fiber_trigger__new(cause, cmutex, waiting_fiber_set);
}

f2ptr f2__fiber_trigger__new(f2ptr cause) {
  return raw__fiber_trigger__new(cause);
}
def_pcfunk0(fiber_trigger__new,
	    "",
	    return f2__fiber_trigger__new(this_cause));


f2ptr raw__fiber_trigger__trigger__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr waiting_fiber_set = f2__fiber_trigger__waiting_fiber_set(cause, this);
  f2__fiber_trigger__waiting_fiber_set__set(cause, this, f2__set__new(cause));
  set__iteration(cause, waiting_fiber_set, waiting_fiber,
		 if (! raw__fiber__is_type(cause, waiting_fiber)) {
		   return f2larva__new(cause, 11315, nil);
		 }
		 f2ptr processor_assignment_index = f2__fiber__processor_assignment_index(cause, waiting_fiber);
		 if (processor_assignment_index == nil) {
		   f2__global_scheduler__add_fiber(cause, waiting_fiber);
		 }
		 );
  return nil;
}

f2ptr raw__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  f2ptr cmutex = f2__fiber_trigger__cmutex(cause, this);
  raw__cmutex__lock(cause, cmutex);
  f2ptr result = raw__fiber_trigger__trigger__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, cmutex);
  return result;
}

f2ptr f2__fiber_trigger__trigger(f2ptr cause, f2ptr this) {
  assert_argument_type(fiber_trigger, this);
  return raw__fiber_trigger__trigger(cause, this);
}
def_pcfunk1(fiber_trigger__trigger, this,
	    "",
	    return f2__fiber_trigger__trigger(this_cause, this));


void raw__fiber_trigger__add_waiting_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {  
  f2ptr waiting_fiber_set = f2__fiber_trigger__waiting_fiber_set(cause, this);
  raw__set__add(cause, waiting_fiber_set, fiber);
}

void raw__fiber_trigger__add_waiting_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {  
  f2ptr cmutex = f2__fiber_trigger__cmutex(cause, this);
  raw__cmutex__lock(cause, cmutex);
  raw__fiber_trigger__add_waiting_fiber__thread_unsafe(cause, this, fiber);
  raw__cmutex__unlock(cause, cmutex);
}

f2ptr f2__fiber_trigger__add_waiting_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(fiber_trigger, this);
  assert_argument_type(fiber,         fiber);
  raw__fiber_trigger__add_waiting_fiber(cause, this, fiber);
  return nil;
}
def_pcfunk2(fiber_trigger__add_waiting_fiber, this, fiber,
	    "",
	    return f2__fiber_trigger__add_waiting_fiber(this_cause, this, fiber));


f2ptr raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  raw__fiber_trigger__add_waiting_fiber__thread_unsafe(cause, this, fiber);
  assert_value(raw__global_scheduler__remove_fiber(cause, fiber));
  return nil;
}

f2ptr raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr cmutex = f2__fiber_trigger__cmutex(cause, this);
  raw__cmutex__lock(cause, cmutex);
  f2ptr raw__global_scheduler__remove_fiber__result = raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler__thread_unsafe(cause, this, fiber);
  raw__cmutex__unlock(cause, cmutex);
  assert_value(raw__global_scheduler__remove_fiber__result);
  return nil;
}

f2ptr f2__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(fiber_trigger, this);
  assert_argument_type(fiber,         fiber);
  return raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler(cause, this, fiber);
}
def_pcfunk2(fiber_trigger__add_waiting_fiber_and_remove_from_scheduler, this, fiber,
	    "",
	    return f2__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler(this_cause, this, fiber));


f2ptr raw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure(f2ptr cause, f2ptr this, f2ptr traced_cmutex, f2ptr fiber) {
  printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 0\n"); fflush(stdout);
  f2ptr this__cmutex = assert_value(f2__fiber_trigger__cmutex(cause, this));
  raw__cmutex__lock(cause, this__cmutex);
  printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 1\n"); fflush(stdout);
  f2ptr lock_failure = raw__traced_cmutex__trylock(cause, traced_cmutex);
  if (raw__larva__is_type(cause, lock_failure)) {
    printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 2\n"); fflush(stdout);
    raw__cmutex__unlock(cause, this__cmutex);
    printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 3\n"); fflush(stdout);
    return lock_failure;
  }
  printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 4\n"); fflush(stdout);
  if (lock_failure != nil) {
    printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 5\n"); fflush(stdout);
    f2ptr result = raw__fiber_trigger__add_waiting_fiber_and_remove_from_scheduler__thread_unsafe(cause, this, fiber);
    printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 6\n"); fflush(stdout);
    if (raw__larva__is_type(cause, result)) {
      printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 7\n"); fflush(stdout);
      raw__cmutex__unlock(cause, this__cmutex);
      printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 8\n"); fflush(stdout);
      return result;
    }
  }
  printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 9\n"); fflush(stdout);
  raw__cmutex__unlock(cause, this__cmutex);
  printf("\nraw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure: debug 10\n"); fflush(stdout);
  return lock_failure;
}

f2ptr f2__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure(f2ptr cause, f2ptr this, f2ptr traced_cmutex, f2ptr fiber) {
  assert_argument_type(fiber_trigger, this);
  assert_argument_type(traced_cmutex, traced_cmutex);
  assert_argument_type(fiber,         fiber);
  return raw__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure(cause, this, traced_cmutex, fiber);
}
def_pcfunk3(fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure, this, traced_cmutex, fiber,
	    "",
	    return f2__fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure(this_cause, this, traced_cmutex, fiber));


f2ptr raw__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list4__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "fiber_trigger"),
					       new__symbol(cause, "waiting_fiber_set"), f2__fiber_trigger__waiting_fiber_set(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__fiber_trigger__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(fiber_trigger,        this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__fiber_trigger__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(fiber_trigger__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__fiber_trigger__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2fiber_trigger__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2fiber_trigger__primobject_type__new(cause);
  {char* slot_name = "trigger";                                                                      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__funk);}
  {char* slot_name = "add_waiting_fiber";                                                            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber__funk);}
  {char* slot_name = "add_waiting_fiber_and_remove_from_scheduler";                                  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber_and_remove_from_scheduler__funk);}
  {char* slot_name = "trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__funk);}
  {char* slot_name = "terminal_print_with_frame";                                                    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.terminal_print_with_frame__funk);}
  return this;
}



// **

void f2__primobject__fiber_trigger__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // fiber_trigger
  
  initialize_primobject_2_slot__defragment__fix_pointers(fiber_trigger, cmutex, waiting_fiber_set);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__trigger);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__add_waiting_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber_and_remove_from_scheduler__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__add_waiting_fiber_and_remove_from_scheduler);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber_and_remove_from_scheduler__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(fiber_trigger__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.terminal_print_with_frame__funk);
}

void f2__primobject__fiber_trigger__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // fiber_trigger
  
  initialize_primobject_2_slot(fiber_trigger, cmutex, waiting_fiber_set);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(fiber_trigger__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.new__funk = never_gc(cfunk);}
  
  {char* symbol_str = "trigger"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(fiber_trigger__trigger, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trigger__funk = never_gc(cfunk);}
  {char* symbol_str = "add_waiting_fiber"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(fiber_trigger__add_waiting_fiber, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber__funk = never_gc(cfunk);}
  {char* symbol_str = "add_waiting_fiber_and_remove_from_scheduler"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber_and_remove_from_scheduler__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(fiber_trigger__add_waiting_fiber_and_remove_from_scheduler, this, fiber, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.add_waiting_fiber_and_remove_from_scheduler__funk = never_gc(cfunk);}
  {char* symbol_str = "trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(fiber_trigger__trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure, this, traced_cmutex, fiber, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.trylock_traced_cmutex_add_waiting_fiber_and_remove_from_scheduler_on_failure__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(fiber_trigger__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_fiber_trigger.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject__fiber_trigger__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-fiber_trigger", "", &f2__primobject__fiber_trigger__reinitialize_globalvars, &f2__primobject__fiber_trigger__defragment__fix_pointers);
  
  f2__primobject__fiber_trigger__reinitialize_globalvars();
}

