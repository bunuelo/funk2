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


// cause_group_interaction

def_primobject_9_slot(cause_group_interaction,
		      bytecode_count_scheduler_cmutex,
		      bytecode_count,
		      execution_nanoseconds_scheduler_cmutex,
		      execution_nanoseconds_chunk,
		      bytes_allocated_count_scheduler_cmutex,
		      bytes_allocated_count_chunk,
		      bytes_freed_count_scheduler_cmutex,
		      bytes_freed_count_chunk,
		      cause_group_interaction_interaction_ptypehash);

f2ptr f2__cause_group_interaction__new(f2ptr cause) {
  f2ptr bytecode_count_scheduler_cmutex        = f2scheduler_cmutex__new(cause);
  f2ptr bytecode_count                         = f2integer__new(cause, 0);
  f2ptr execution_nanoseconds_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr execution_nanoseconds_chunk            = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_allocated_count_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr bytes_allocated_count_chunk            = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_freed_count_scheduler_cmutex     = f2scheduler_cmutex__new(cause);
  f2ptr bytes_freed_count_chunk                = raw__chunk__new(cause, sizeof(u64));
  f2ptr cause_group_interaction_interaction_ptypehash      = f2__ptypehash__new(cause);
  return f2cause_group_interaction__new(cause,
			    bytecode_count_scheduler_cmutex,
			    bytecode_count,
			    execution_nanoseconds_scheduler_cmutex,
			    execution_nanoseconds_chunk,
			    bytes_allocated_count_scheduler_cmutex,
			    bytes_allocated_count_chunk,
			    bytes_freed_count_scheduler_cmutex,
			    bytes_freed_count_chunk,
			    cause_group_interaction_interaction_ptypehash);
}
def_pcfunk0(cause_group_interaction__new,
	    "",
	    return f2__cause_group_interaction__new(this_cause));


void raw__cause_group_interaction__increase_bytecode_count(f2ptr cause, f2ptr this, u64 relative_bytecode_count) {
  f2ptr bytecode_count_scheduler_cmutex = f2cause_group_interaction__bytecode_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytecode_count_scheduler_cmutex, cause);
  f2ptr bytecode_count     = f2cause_group_interaction__bytecode_count(this, cause);
  u64   bytecode_count__i  = (u64)f2integer__i(bytecode_count, cause);
  f2cause_group_interaction__bytecode_count__set(this, cause, f2integer__new(cause, (u64)(bytecode_count__i + relative_bytecode_count)));
  f2scheduler_cmutex__unlock(bytecode_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_bytecode_count(f2ptr cause, f2ptr this, f2ptr relative_bytecode_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     relative_bytecode_count);
  u64 relative_bytecode_count__i = (u64)f2integer__i(relative_bytecode_count, cause);
  raw__cause_group_interaction__increase_bytecode_count(cause, this, relative_bytecode_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_bytecode_count, this, relative_bytecode_count,
	    "",
	    return f2__cause_group_interaction__increase_bytecode_count(this_cause, this, relative_bytecode_count));


u64 raw__cause_group_interaction__execution_nanoseconds(f2ptr cause, f2ptr this) {
  f2ptr execution_nanoseconds_chunk = f2cause_group_interaction__execution_nanoseconds_chunk(this, cause);
  return f2chunk__bit64__elt(execution_nanoseconds_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__execution_nanoseconds(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__execution_nanoseconds(cause, this));
}
def_pcfunk1(cause_group_interaction__execution_nanoseconds, this,
	    "",
	    return f2__cause_group_interaction__execution_nanoseconds(this_cause, this));


void raw__cause_group_interaction__execution_nanoseconds__set(f2ptr cause, f2ptr this, u64 execution_nanoseconds) {
  f2ptr execution_nanoseconds_chunk = f2cause_group_interaction__execution_nanoseconds_chunk(this, cause);
  f2chunk__bit64__elt__set(execution_nanoseconds_chunk, 0, cause, execution_nanoseconds);
}

f2ptr f2__cause_group_interaction__execution_nanoseconds__set(f2ptr cause, f2ptr this, f2ptr execution_nanoseconds) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     execution_nanoseconds);
  u64 execution_nanoseconds__i = f2integer__i(execution_nanoseconds, cause);
  raw__cause_group_interaction__execution_nanoseconds__set(cause, this, execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__execution_nanoseconds__set, this, execution_nanoseconds,
	    "",
	    return f2__cause_group_interaction__execution_nanoseconds__set(this_cause, this, execution_nanoseconds));


void raw__cause_group_interaction__increase_execution_nanoseconds(f2ptr cause, f2ptr this, u64 relative_execution_nanoseconds) {
  f2ptr execution_nanoseconds_scheduler_cmutex = f2cause_group_interaction__execution_nanoseconds_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(execution_nanoseconds_scheduler_cmutex, cause);
  u64 execution_nanoseconds = raw__cause_group_interaction__execution_nanoseconds(cause, this);
  raw__cause_group_interaction__execution_nanoseconds__set(cause, this, execution_nanoseconds + relative_execution_nanoseconds);
  f2scheduler_cmutex__unlock(execution_nanoseconds_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_execution_nanoseconds(f2ptr cause, f2ptr this, f2ptr relative_execution_nanoseconds) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     relative_execution_nanoseconds);
  u64 relative_execution_nanoseconds__i = (u64)f2integer__i(relative_execution_nanoseconds, cause);
  raw__cause_group_interaction__increase_execution_nanoseconds(cause, this, relative_execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_execution_nanoseconds, this, relative_execution_nanoseconds,
	    "",
	    return f2__cause_group_interaction__increase_execution_nanoseconds(this_cause, this, relative_execution_nanoseconds));


u64 raw__cause_group_interaction__bytes_allocated_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_allocated_count_chunk = f2cause_group_interaction__bytes_allocated_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_allocated_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__bytes_allocated_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__bytes_allocated_count(cause, this));
}
def_pcfunk1(cause_group_interaction__bytes_allocated_count, this,
	    "",
	    return f2__cause_group_interaction__bytes_allocated_count(this_cause, this));


void raw__cause_group_interaction__bytes_allocated_count__set(f2ptr cause, f2ptr this, u64 bytes_allocated_count) {
  f2ptr bytes_allocated_count_chunk = f2cause_group_interaction__bytes_allocated_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_allocated_count_chunk, 0, cause, bytes_allocated_count);
}

f2ptr f2__cause_group_interaction__bytes_allocated_count__set(f2ptr cause, f2ptr this, f2ptr bytes_allocated_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     bytes_allocated_count);
  u64 bytes_allocated_count__i = f2integer__i(bytes_allocated_count, cause);
  raw__cause_group_interaction__bytes_allocated_count__set(cause, this, bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__bytes_allocated_count__set, this, bytes_allocated_count,
	    "",
	    return f2__cause_group_interaction__bytes_allocated_count__set(this_cause, this, bytes_allocated_count));


void raw__cause_group_interaction__increase_bytes_allocated_count(f2ptr cause, f2ptr this, u64 relative_bytes_allocated_count) {
  f2ptr bytes_allocated_count_scheduler_cmutex = f2cause_group_interaction__bytes_allocated_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_allocated_count_scheduler_cmutex, cause);
  u64 bytes_allocated_count = raw__cause_group_interaction__bytes_allocated_count(cause, this);
  raw__cause_group_interaction__bytes_allocated_count__set(cause, this, bytes_allocated_count + relative_bytes_allocated_count);
  f2scheduler_cmutex__unlock(bytes_allocated_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_bytes_allocated_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_allocated_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     relative_bytes_allocated_count);
  u64 relative_bytes_allocated_count__i = (u64)f2integer__i(relative_bytes_allocated_count, cause);
  raw__cause_group_interaction__increase_bytes_allocated_count(cause, this, relative_bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_bytes_allocated_count, this, relative_bytes_allocated_count,
	    "",
	    return f2__cause_group_interaction__increase_bytes_allocated_count(this_cause, this, relative_bytes_allocated_count));


u64 raw__cause_group_interaction__bytes_freed_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_freed_count_chunk = f2cause_group_interaction__bytes_freed_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_freed_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__bytes_freed_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__bytes_freed_count(cause, this));
}
def_pcfunk1(cause_group_interaction__bytes_freed_count, this,
	    "",
	    return f2__cause_group_interaction__bytes_freed_count(this_cause, this));


void raw__cause_group_interaction__bytes_freed_count__set(f2ptr cause, f2ptr this, u64 bytes_freed_count) {
  f2ptr bytes_freed_count_chunk = f2cause_group_interaction__bytes_freed_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_freed_count_chunk, 0, cause, bytes_freed_count);
}

f2ptr f2__cause_group_interaction__bytes_freed_count__set(f2ptr cause, f2ptr this, f2ptr bytes_freed_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     bytes_freed_count);
  u64 bytes_freed_count__i = f2integer__i(bytes_freed_count, cause);
  raw__cause_group_interaction__bytes_freed_count__set(cause, this, bytes_freed_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__bytes_freed_count__set, this, bytes_freed_count,
	    "",
	    return f2__cause_group_interaction__bytes_freed_count__set(this_cause, this, bytes_freed_count));


void raw__cause_group_interaction__increase_bytes_freed_count(f2ptr cause, f2ptr this, u64 relative_bytes_freed_count) {
  f2ptr bytes_freed_count_scheduler_cmutex = f2cause_group_interaction__bytes_freed_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_freed_count_scheduler_cmutex, cause);
  u64 bytes_freed_count = raw__cause_group_interaction__bytes_freed_count(cause, this);
  raw__cause_group_interaction__bytes_freed_count__set(cause, this, bytes_freed_count + relative_bytes_freed_count);
  f2scheduler_cmutex__unlock(bytes_freed_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_bytes_freed_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_freed_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     relative_bytes_freed_count);
  u64 relative_bytes_freed_count__i = (u64)f2integer__i(relative_bytes_freed_count, cause);
  raw__cause_group_interaction__increase_bytes_freed_count(cause, this, relative_bytes_freed_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_bytes_freed_count, this, relative_bytes_freed_count,
	    "",
	    return f2__cause_group_interaction__increase_bytes_freed_count(this_cause, this, relative_bytes_freed_count));


// cause_group_interaction

f2ptr raw__cause_group_interaction__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"),                 new__symbol(cause, "cause_group_interaction"),
						new__symbol(cause, "bytecode_count"),                    f2__cause_group_interaction__bytecode_count(                   cause, this),
						new__symbol(cause, "execution_nanoseconds"),             f2__cause_group_interaction__execution_nanoseconds(            cause, this),
						new__symbol(cause, "bytes_allocated_count"),             f2__cause_group_interaction__bytes_allocated_count(            cause, this),
						new__symbol(cause, "bytes_freed_count"),                 f2__cause_group_interaction__bytes_freed_count(                cause, this),
						new__symbol(cause, "cause_group_interaction_interaction_ptypehash"), f2__cause_group_interaction__cause_group_interaction_interaction_ptypehash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__cause_group_interaction__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cause_group_interaction,          this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cause_group_interaction__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cause_group_interaction__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__cause_group_interaction__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2cause_group_interaction__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause_group_interaction__primobject_type__new(cause);
  {char* slot_name = "increase_bytecode_count";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytecode_count__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__set__funk);}
  {char* slot_name = "increase_execution_nanoseconds"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_execution_nanoseconds__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__set__funk);}
  {char* slot_name = "increase_bytes_allocated_count"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_allocated_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__set__funk);}
  {char* slot_name = "increase_bytes_freed_count";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_freed_count__funk);}
  {char* slot_name = "terminal_print_with_frame";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk);}
  return this;
}



// cause_group

def_primobject_9_slot(cause_group,
		      bytecode_count_scheduler_cmutex,
		      bytecode_count,
		      execution_nanoseconds_scheduler_cmutex,
		      execution_nanoseconds_chunk,
		      bytes_allocated_count_scheduler_cmutex,
		      bytes_allocated_count_chunk,
		      bytes_freed_count_scheduler_cmutex,
		      bytes_freed_count_chunk,
		      cause_group_interaction_ptypehash);

f2ptr f2__cause_group__new(f2ptr cause) {
  f2ptr bytecode_count_scheduler_cmutex        = f2scheduler_cmutex__new(cause);
  f2ptr bytecode_count                         = f2integer__new(cause, 0);
  f2ptr execution_nanoseconds_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr execution_nanoseconds_chunk            = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_allocated_count_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr bytes_allocated_count_chunk            = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_freed_count_scheduler_cmutex     = f2scheduler_cmutex__new(cause);
  f2ptr bytes_freed_count_chunk                = raw__chunk__new(cause, sizeof(u64));
  f2ptr cause_group_interaction_ptypehash      = f2__ptypehash__new(cause);
  return f2cause_group__new(cause,
			    bytecode_count_scheduler_cmutex,
			    bytecode_count,
			    execution_nanoseconds_scheduler_cmutex,
			    execution_nanoseconds_chunk,
			    bytes_allocated_count_scheduler_cmutex,
			    bytes_allocated_count_chunk,
			    bytes_freed_count_scheduler_cmutex,
			    bytes_freed_count_chunk,
			    cause_group_interaction_ptypehash);
}
def_pcfunk0(cause_group__new,
	    "",
	    return f2__cause_group__new(this_cause));


void raw__cause_group__increase_bytecode_count(f2ptr cause, f2ptr this, u64 relative_bytecode_count) {
  f2ptr bytecode_count_scheduler_cmutex = f2cause_group__bytecode_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytecode_count_scheduler_cmutex, cause);
  f2ptr bytecode_count     = f2cause_group__bytecode_count(this, cause);
  u64   bytecode_count__i  = (u64)f2integer__i(bytecode_count, cause);
  f2cause_group__bytecode_count__set(this, cause, f2integer__new(cause, (u64)(bytecode_count__i + relative_bytecode_count)));
  f2scheduler_cmutex__unlock(bytecode_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group__increase_bytecode_count(f2ptr cause, f2ptr this, f2ptr relative_bytecode_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     relative_bytecode_count);
  u64 relative_bytecode_count__i = (u64)f2integer__i(relative_bytecode_count, cause);
  raw__cause_group__increase_bytecode_count(cause, this, relative_bytecode_count__i);
  return nil;
}
def_pcfunk2(cause_group__increase_bytecode_count, this, relative_bytecode_count,
	    "",
	    return f2__cause_group__increase_bytecode_count(this_cause, this, relative_bytecode_count));


u64 raw__cause_group__execution_nanoseconds(f2ptr cause, f2ptr this) {
  f2ptr execution_nanoseconds_chunk = f2cause_group__execution_nanoseconds_chunk(this, cause);
  return f2chunk__bit64__elt(execution_nanoseconds_chunk, 0, cause);
}

f2ptr f2__cause_group__execution_nanoseconds(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group, this);
  return f2integer__new(cause, raw__cause_group__execution_nanoseconds(cause, this));
}
def_pcfunk1(cause_group__execution_nanoseconds, this,
	    "",
	    return f2__cause_group__execution_nanoseconds(this_cause, this));


void raw__cause_group__execution_nanoseconds__set(f2ptr cause, f2ptr this, u64 execution_nanoseconds) {
  f2ptr execution_nanoseconds_chunk = f2cause_group__execution_nanoseconds_chunk(this, cause);
  f2chunk__bit64__elt__set(execution_nanoseconds_chunk, 0, cause, execution_nanoseconds);
}

f2ptr f2__cause_group__execution_nanoseconds__set(f2ptr cause, f2ptr this, f2ptr execution_nanoseconds) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     execution_nanoseconds);
  u64 execution_nanoseconds__i = f2integer__i(execution_nanoseconds, cause);
  raw__cause_group__execution_nanoseconds__set(cause, this, execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(cause_group__execution_nanoseconds__set, this, execution_nanoseconds,
	    "",
	    return f2__cause_group__execution_nanoseconds__set(this_cause, this, execution_nanoseconds));


void raw__cause_group__increase_execution_nanoseconds(f2ptr cause, f2ptr this, u64 relative_execution_nanoseconds) {
  f2ptr execution_nanoseconds_scheduler_cmutex = f2cause_group__execution_nanoseconds_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(execution_nanoseconds_scheduler_cmutex, cause);
  u64 execution_nanoseconds = raw__cause_group__execution_nanoseconds(cause, this);
  raw__cause_group__execution_nanoseconds__set(cause, this, execution_nanoseconds + relative_execution_nanoseconds);
  f2scheduler_cmutex__unlock(execution_nanoseconds_scheduler_cmutex, cause);
}

f2ptr f2__cause_group__increase_execution_nanoseconds(f2ptr cause, f2ptr this, f2ptr relative_execution_nanoseconds) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     relative_execution_nanoseconds);
  u64 relative_execution_nanoseconds__i = (u64)f2integer__i(relative_execution_nanoseconds, cause);
  raw__cause_group__increase_execution_nanoseconds(cause, this, relative_execution_nanoseconds__i);
  return nil;
}
def_pcfunk2(cause_group__increase_execution_nanoseconds, this, relative_execution_nanoseconds,
	    "",
	    return f2__cause_group__increase_execution_nanoseconds(this_cause, this, relative_execution_nanoseconds));


u64 raw__cause_group__bytes_allocated_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_allocated_count_chunk = f2cause_group__bytes_allocated_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_allocated_count_chunk, 0, cause);
}

f2ptr f2__cause_group__bytes_allocated_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group, this);
  return f2integer__new(cause, raw__cause_group__bytes_allocated_count(cause, this));
}
def_pcfunk1(cause_group__bytes_allocated_count, this,
	    "",
	    return f2__cause_group__bytes_allocated_count(this_cause, this));


void raw__cause_group__bytes_allocated_count__set(f2ptr cause, f2ptr this, u64 bytes_allocated_count) {
  f2ptr bytes_allocated_count_chunk = f2cause_group__bytes_allocated_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_allocated_count_chunk, 0, cause, bytes_allocated_count);
}

f2ptr f2__cause_group__bytes_allocated_count__set(f2ptr cause, f2ptr this, f2ptr bytes_allocated_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     bytes_allocated_count);
  u64 bytes_allocated_count__i = f2integer__i(bytes_allocated_count, cause);
  raw__cause_group__bytes_allocated_count__set(cause, this, bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(cause_group__bytes_allocated_count__set, this, bytes_allocated_count,
	    "",
	    return f2__cause_group__bytes_allocated_count__set(this_cause, this, bytes_allocated_count));


void raw__cause_group__increase_bytes_allocated_count(f2ptr cause, f2ptr this, u64 relative_bytes_allocated_count) {
  f2ptr bytes_allocated_count_scheduler_cmutex = f2cause_group__bytes_allocated_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_allocated_count_scheduler_cmutex, cause);
  u64 bytes_allocated_count = raw__cause_group__bytes_allocated_count(cause, this);
  raw__cause_group__bytes_allocated_count__set(cause, this, bytes_allocated_count + relative_bytes_allocated_count);
  f2scheduler_cmutex__unlock(bytes_allocated_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group__increase_bytes_allocated_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_allocated_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     relative_bytes_allocated_count);
  u64 relative_bytes_allocated_count__i = (u64)f2integer__i(relative_bytes_allocated_count, cause);
  raw__cause_group__increase_bytes_allocated_count(cause, this, relative_bytes_allocated_count__i);
  return nil;
}
def_pcfunk2(cause_group__increase_bytes_allocated_count, this, relative_bytes_allocated_count,
	    "",
	    return f2__cause_group__increase_bytes_allocated_count(this_cause, this, relative_bytes_allocated_count));


u64 raw__cause_group__bytes_freed_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_freed_count_chunk = f2cause_group__bytes_freed_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_freed_count_chunk, 0, cause);
}

f2ptr f2__cause_group__bytes_freed_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group, this);
  return f2integer__new(cause, raw__cause_group__bytes_freed_count(cause, this));
}
def_pcfunk1(cause_group__bytes_freed_count, this,
	    "",
	    return f2__cause_group__bytes_freed_count(this_cause, this));


void raw__cause_group__bytes_freed_count__set(f2ptr cause, f2ptr this, u64 bytes_freed_count) {
  f2ptr bytes_freed_count_chunk = f2cause_group__bytes_freed_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_freed_count_chunk, 0, cause, bytes_freed_count);
}

f2ptr f2__cause_group__bytes_freed_count__set(f2ptr cause, f2ptr this, f2ptr bytes_freed_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     bytes_freed_count);
  u64 bytes_freed_count__i = f2integer__i(bytes_freed_count, cause);
  raw__cause_group__bytes_freed_count__set(cause, this, bytes_freed_count__i);
  return nil;
}
def_pcfunk2(cause_group__bytes_freed_count__set, this, bytes_freed_count,
	    "",
	    return f2__cause_group__bytes_freed_count__set(this_cause, this, bytes_freed_count));


void raw__cause_group__increase_bytes_freed_count(f2ptr cause, f2ptr this, u64 relative_bytes_freed_count) {
  f2ptr bytes_freed_count_scheduler_cmutex = f2cause_group__bytes_freed_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_freed_count_scheduler_cmutex, cause);
  u64 bytes_freed_count = raw__cause_group__bytes_freed_count(cause, this);
  raw__cause_group__bytes_freed_count__set(cause, this, bytes_freed_count + relative_bytes_freed_count);
  f2scheduler_cmutex__unlock(bytes_freed_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group__increase_bytes_freed_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_freed_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     relative_bytes_freed_count);
  u64 relative_bytes_freed_count__i = (u64)f2integer__i(relative_bytes_freed_count, cause);
  raw__cause_group__increase_bytes_freed_count(cause, this, relative_bytes_freed_count__i);
  return nil;
}
def_pcfunk2(cause_group__increase_bytes_freed_count, this, relative_bytes_freed_count,
	    "",
	    return f2__cause_group__increase_bytes_freed_count(this_cause, this, relative_bytes_freed_count));


// cause_group

f2ptr raw__cause_group__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"),                 new__symbol(cause, "cause_group"),
						new__symbol(cause, "bytecode_count"),                    f2__cause_group__bytecode_count(                   cause, this),
						new__symbol(cause, "execution_nanoseconds"),             f2__cause_group__execution_nanoseconds(            cause, this),
						new__symbol(cause, "bytes_allocated_count"),             f2__cause_group__bytes_allocated_count(            cause, this),
						new__symbol(cause, "bytes_freed_count"),                 f2__cause_group__bytes_freed_count(                cause, this),
						new__symbol(cause, "cause_group_interaction_ptypehash"), f2__cause_group__cause_group_interaction_ptypehash(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__cause_group__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cause_group,          this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cause_group__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cause_group__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__cause_group__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2cause_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause_group__primobject_type__new(cause);
  {char* slot_name = "increase_bytecode_count";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__funk);}
  {char* slot_name = "increase_execution_nanoseconds"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__funk);}
  {char* slot_name = "increase_bytes_allocated_count"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__funk);}
  {char* slot_name = "increase_bytes_freed_count";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__funk);}
  {char* slot_name = "terminal_print_with_frame";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__funk);}
  return this;
}



// cause

def_primobject_17_slot(cause,
		       fibers_cmutex,
		       fibers,
		       frame,
		       allocate_traced_arrays,
		       bytecode_tracing_on,
		       memory_tracing_on,
		       imagination_stack,
		       bytecode_branch_callbacks,
		       bytecode_funk_callbacks,
		       bytecode_tracer_callbacks,
		       bytecode_endfunk_callbacks,
		       complete_funk_callbacks,
		       read_other_memory_callbacks,
		       write_other_memory_callbacks,
		       critics,
		       cause_groups_cmutex,
		       cause_groups);

f2ptr f2__cause__new(f2ptr cause,
		     f2ptr allocate_traced_arrays,
		     f2ptr bytecode_tracing_on,
		     f2ptr memory_tracing_on,
		     f2ptr imagination_name,
		     f2ptr bytecode_branch_callbacks,
		     f2ptr bytecode_funk_callbacks,
		     f2ptr bytecode_tracer_callbacks,
		     f2ptr bytecode_endfunk_callbacks,
		     f2ptr complete_funk_callbacks,
		     f2ptr read_other_memory_callbacks,
		     f2ptr write_other_memory_callbacks,
		     f2ptr critics,
		     f2ptr cause_groups) {
  f2ptr fibers_cmutex       = f2cmutex__new(cause);
  f2ptr fibers              = nil;
  f2ptr frame               = f2__frame__new(cause, nil);
  f2ptr cause_groups_cmutex = f2cmutex__new(cause);
  f2ptr this                = f2cause__new(cause,
					   fibers_cmutex,
					   fibers,
					   frame,
					   allocate_traced_arrays,
					   bytecode_tracing_on,
					   memory_tracing_on,
					   imagination_name,
					   bytecode_branch_callbacks,
					   bytecode_funk_callbacks,
					   bytecode_tracer_callbacks,
					   bytecode_endfunk_callbacks,
					   complete_funk_callbacks,
					   read_other_memory_callbacks,
					   write_other_memory_callbacks,
					   critics,
					   cause_groups_cmutex,
					   cause_groups);
  //printf("\nnew cause: " u64__fstr ".\n", this); fflush(stdout);
  return this;
}
def_pcfunk0(cause__new,
	    "",
	    return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source) {
  if (source && (! raw__cause__is_type(cause, source))) {
    return f2larva__new(cause, 333, nil);
  }
  f2ptr allocate_traced_arrays       = cause__allocate_traced_arrays__default_value; // default values
  f2ptr bytecode_tracing_on          = nil;
  f2ptr memory_tracing_on            = nil;
  f2ptr imagination_stack            = nil;
  f2ptr bytecode_branch_callbacks    = nil;
  f2ptr bytecode_funk_callbacks      = nil;
  f2ptr bytecode_tracer_callbacks    = nil;
  f2ptr bytecode_endfunk_callbacks   = nil;
  f2ptr complete_funk_callbacks      = nil;
  f2ptr read_other_memory_callbacks  = nil;
  f2ptr write_other_memory_callbacks = nil;
  f2ptr critics                      = nil;
  f2ptr cause_groups                 = nil;
  if (source) {
    allocate_traced_arrays       = f2__cause__allocate_traced_arrays(      cause, source);
    bytecode_tracing_on          = f2__cause__bytecode_tracing_on(         cause, source);
    memory_tracing_on            = f2__cause__memory_tracing_on(           cause, source);
    imagination_stack            = f2__cause__imagination_stack(           cause, source);
    bytecode_branch_callbacks    = f2__cause__bytecode_branch_callbacks(   cause, source);
    bytecode_funk_callbacks      = f2__cause__bytecode_funk_callbacks(     cause, source);
    bytecode_tracer_callbacks    = f2__cause__bytecode_tracer_callbacks(   cause, source);
    bytecode_endfunk_callbacks   = f2__cause__bytecode_endfunk_callbacks(  cause, source);
    complete_funk_callbacks      = f2__cause__complete_funk_callbacks(     cause, source);
    read_other_memory_callbacks  = f2__cause__read_other_memory_callbacks( cause, source);;
    write_other_memory_callbacks = f2__cause__write_other_memory_callbacks(cause, source);;
    critics                      = f2__cause__critics(                     cause, source);;
    cause_groups                 = f2__cause__cause_groups(                cause, source);;
  }
  return f2__cause__new(cause,
			allocate_traced_arrays,
			bytecode_tracing_on,
			memory_tracing_on,
			imagination_stack,
			bytecode_branch_callbacks,
			bytecode_funk_callbacks,
			bytecode_tracer_callbacks,
			bytecode_endfunk_callbacks,
			complete_funk_callbacks,
			read_other_memory_callbacks,
			write_other_memory_callbacks,
			critics,
			cause_groups);
}

f2ptr raw__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr     fibers_cmutex    = f2cause__fibers_cmutex(   this,  cause);
  f2ptr     cause_reg_cmutex = f2fiber__cause_reg_cmutex(fiber, cause);
  boolean_t both_locked     = boolean__false;
  while (! both_locked) {
    both_locked = boolean__true;
    boolean_t fibers_cmutex__failed_lock    = f2cmutex__trylock(fibers_cmutex,    cause);
    boolean_t cause_reg_cmutex__failed_lock = f2cmutex__trylock(cause_reg_cmutex, cause);
    if (fibers_cmutex__failed_lock)    {both_locked = boolean__false;}
    if (cause_reg_cmutex__failed_lock) {both_locked = boolean__false;}
    if (! both_locked) {
      if (! fibers_cmutex__failed_lock)    {f2cmutex__unlock(fibers_cmutex,    cause);}
      if (! cause_reg_cmutex__failed_lock) {f2cmutex__unlock(cause_reg_cmutex, cause);}
      f2__this__fiber__yield(cause);
    }
  }
  f2ptr cause_reg = f2fiber__cause_reg(fiber, cause);
  f2ptr result    = nil;
  if (cause_reg == nil) {
    f2fiber__cause_reg__set(fiber, cause, this);
    f2cause__fibers__set(   this,  cause, f2cons__new(cause, fiber, f2cause__fibers(this, cause)));
  } else {
    result = f2larva__new(cause, 827152, nil);
  }
  f2cmutex__unlock(fibers_cmutex,    cause);
  f2cmutex__unlock(cause_reg_cmutex, cause);
  return result;
}

f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(cause, this);
  assert_argument_type(fiber, fiber);
  return raw__cause__add_fiber(cause, this, fiber);
}


f2ptr raw__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr     fibers_cmutex    = f2cause__fibers_cmutex(   this,  cause);
  f2ptr     cause_reg_cmutex = f2fiber__cause_reg_cmutex(fiber, cause);
  boolean_t both_locked     = boolean__false;
  while (! both_locked) {
    both_locked = boolean__true;
    boolean_t fibers_cmutex__failed_lock    = f2cmutex__trylock(fibers_cmutex,    cause);
    boolean_t cause_reg_cmutex__failed_lock = f2cmutex__trylock(cause_reg_cmutex, cause);
    if (fibers_cmutex__failed_lock)    {both_locked = boolean__false;}
    if (cause_reg_cmutex__failed_lock) {both_locked = boolean__false;}
    if (! both_locked) {
      if (! fibers_cmutex__failed_lock)    {f2cmutex__unlock(fibers_cmutex,    cause);}
      if (! cause_reg_cmutex__failed_lock) {f2cmutex__unlock(cause_reg_cmutex, cause);}
      f2__this__fiber__yield(cause);
    }
  }
  f2ptr cause_reg = f2fiber__cause_reg(fiber, cause);
  f2ptr result    = nil;
  if (cause_reg != nil) {
    f2fiber__cause_reg__set(fiber, cause, nil);
    {
      f2ptr prev = nil;
      f2ptr iter = f2cause__fibers(this, cause);
      while (iter) {
	f2ptr next = f2cons__cdr(iter, cause);
	f2ptr iter_fiber = f2cons__car(iter, cause);
	if (iter_fiber == fiber) {
	  if (prev) {
	    f2cons__cdr__set(prev, cause, next);
	  } else {
	    f2cause__fibers__set(this, cause, next);
	  }
	  break;
	}
	prev = iter;
	iter = next;
      }
      if (! iter) {
	printf("\nf2__cause__remove_fiber warning: could not find fiber to remove."); fflush(stdout);
	result = f2larva__new(cause, 827153, nil);
      }
    }
  } else {
    result = f2larva__new(cause, 827154, nil);
  }
  f2cmutex__unlock(fibers_cmutex,    cause);
  f2cmutex__unlock(cause_reg_cmutex, cause);
  return result;
}

f2ptr f2__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(cause, this);
  assert_argument_type(fiber, fiber);
  return raw__cause__remove_fiber(cause, this, fiber);
}



f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name) {
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause, cause);
  f2cause__imagination_stack__set(new_cause, cause, f2cons__new(cause, imagination_name, f2cause__imagination_stack(cause, new_cause)));
  return new_cause;
}

f2ptr raw__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr     cause_iter   = this;
  f2ptr     value        = nil;
  boolean_t keep_looping;
  do {
    keep_looping = boolean__false;
    f2ptr cause_frame = f2cause__frame(cause_iter, cause);
    if (cause_frame) {
      value = f2__frame__lookup_type_var_value(cause, cause_frame, type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    }
    if ((! cause_frame) || raw__larva__is_type(cause, value)) {
      cause_iter = f2__ptype__cause(cause, cause_iter);
      if (cause_iter) {
	keep_looping = boolean__true;
      } else {
	value = new__error(f2list8__new(cause,
					new__symbol(cause, "bug_name"),      new__symbol(cause, "type_var_does_not_exist_in_cause"),
					new__symbol(cause, "this"),          this,
					new__symbol(cause, "variable_type"), type,
					new__symbol(cause, "variable_name"), var));
      }
    }
  } while (keep_looping);
  return value;
}

f2ptr f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(cause, this);
  return raw__cause__lookup_type_var_value(cause, this, type, var);
}


boolean_t raw__cause__type_var_defined(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr cause_iter = this;
  while (cause_iter != nil) {
    f2ptr cause__frame = f2cause__frame(cause_iter, cause);
    if (raw__frame__contains_type_var(cause, cause__frame, type, var)) {
      return boolean__true;
    }
    cause_iter = f2__ptype__cause(cause, cause_iter);
  }
  return boolean__false;
}

f2ptr f2__cause__type_var_defined(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(cause, this);
  return f2bool__new(raw__cause__type_var_defined(cause, this, type, var));
}
def_pcfunk3(cause__type_var_defined, this, type, var,
	    "",
	    return f2__cause__type_var_defined(this_cause, this, type, var));


boolean_t raw__cause__var_defined(f2ptr cause, f2ptr this, f2ptr var) {
  return raw__cause__type_var_defined(cause, this, __funk2.primobject__frame.variable__symbol, var);
}

f2ptr f2__cause__var_defined(f2ptr cause, f2ptr this, f2ptr var) {
  assert_argument_type(cause, this);
  return f2bool__new(raw__cause__var_defined(cause, this, var));
}
def_pcfunk2(cause__var_defined, this, var,
	    "",
	    return f2__cause__var_defined(this_cause, this, var));


f2ptr raw__cause__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr cause_iter = this;
  while (cause_iter != nil) {
    f2ptr cause__frame = f2cause__frame(cause_iter, cause);
    if (raw__frame__contains_type_var(cause, cause__frame, type, var)) {
      raw__frame__add_type_var_value(cause, cause__frame, type, var, value);
      return nil;
    }
    cause_iter = f2__ptype__cause(cause, cause_iter);
  }
  return f2larva__new(cause, 621, f2__bug__new(cause, f2integer__new(cause, 621), f2__frame__new(cause, f2list8__new(cause,
														     new__symbol(cause, "bug_type"),      new__symbol(cause, "cannot_set_value_of_undefined_cause_variable"),
														     new__symbol(cause, "funkname"),      new__symbol(cause, "cause-type_var_value-set"),
														     new__symbol(cause, "variable_type"), type,
														     new__symbol(cause, "variable_name"), var))));
}

f2ptr f2__cause__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  assert_argument_type(cause, this);
  return raw__cause__type_var_value__set(cause, this, type, var, value);
}
def_pcfunk4(cause__type_var_value__set, this, type, var, value,
	    "",
	    return f2__cause__type_var_value__set(this_cause, this, type, var, value));


f2ptr raw__cause__var_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  return raw__cause__type_var_value__set(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}

f2ptr f2__cause__var_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  assert_argument_type(cause, this);
  return raw__cause__var_value__set(cause, this, var, value);
}
def_pcfunk3(cause__var_value__set, this, var, value,
	    "",
	    return f2__cause__var_value__set(this_cause, this, var, value));


boolean_t raw__cause__allocate_traced_arrays(f2ptr cause, f2ptr this) {
  if (! this) {
    return (cause__allocate_traced_arrays__default_value != nil);
  }
  if (! raw__cause__is_type(cause, this)) {
    status("error: cause is not a cause");
    return boolean__false;
  }
  return (f2cause__allocate_traced_arrays(this, cause) != nil);
}

void raw__cause__define_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr cause_frame = f2cause__frame(this, cause);
  f2__frame__add_type_var_value(cause, cause_frame, type, var, value);
}

f2ptr f2__cause__define_type_var(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  assert_argument_type(cause, this);
  raw__cause__define_type_var(cause, this, type, var, value);
  return nil;
}


void raw__cause__define(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  raw__cause__define_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}

f2ptr f2__cause__define(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  assert_argument_type(cause, this);
  raw__cause__define_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
  return nil;
}
def_pcfunk3(cause__define, this, var, value,
	    "",
	    return f2__cause__define(this_cause, this, var, value));


void raw__cause__define__funk(f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value) {
  raw__cause__define_type_var(cause, this, __funk2.primobject__frame.funk_variable__symbol, funkvar, value);
}

f2ptr f2__cause__define__funk(f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value) {
  assert_argument_type(cause, this);
  raw__cause__define__funk(cause, this, funkvar, value);
  return nil;
}
def_pcfunk3(cause__define__funk, this, funkvar, value,
	    "",
	    return f2__cause__define__funk(this_cause, this, funkvar, value));


f2ptr raw__cause__lookup(f2ptr cause, f2ptr this, f2ptr var) {
  f2ptr result = raw__cause__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, var);
  if (raw__larva__is_type(cause, result)) {
    return nil;
  }
  return result;
}

f2ptr f2__cause__lookup(f2ptr cause, f2ptr this, f2ptr var) {
  assert_argument_type(cause, this);
  return raw__cause__lookup(cause, this, var);
}
def_pcfunk2(cause__lookup, this, var,
	    "",
	    return f2__cause__lookup(this_cause, this, var));

f2ptr f2__cause__lookup__funk(f2ptr cause, f2ptr this, f2ptr funkvar) {
  f2ptr result = f2__cause__lookup_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, funkvar);
  if (raw__larva__is_type(cause, result)) {
    return nil;
  }
  return result;
}
def_pcfunk2(cause__lookup__funk, this, funkvar,
	    "",
	    return f2__cause__lookup__funk(this_cause, this, funkvar));

f2ptr f2__cause(f2ptr cause) {
  f2ptr fiber     = f2__this__fiber(cause);
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause, cause);
  { // should be atomic
    f2ptr cause_reg = f2fiber__cause_reg(fiber, cause);
    if (! raw__eq(cause, cause, cause_reg)) {
      printf("\nf2__cause warning: cause is not the same as cause_reg."); fflush(stdout);
    }
    f2ptr old_cause = cause_reg;
    if (old_cause != nil) {
      f2ptr result = raw__cause__remove_fiber(cause, old_cause, fiber);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = raw__cause__add_fiber(cause, new_cause, fiber);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return new_cause;
}
def_pcfunk0(cause,
	    "Sets the current cause to be a new cause.  Properties are inherited from the previous cause.",
	    return f2__cause(this_cause));


void raw__cause__add_cause_group(f2ptr cause, f2ptr this, f2ptr cause_group) {
  f2ptr cause_groups_cmutex = f2cause__cause_groups_cmutex(this, cause);
  raw__cmutex__lock(cause, cause_groups_cmutex);
  f2ptr cause_groups = f2cause__cause_groups(this, cause);
  f2cause__cause_groups__set(this, cause, f2cons__new(cause, cause_group, cause_groups));
  raw__cmutex__unlock(cause, cause_groups_cmutex);
}

f2ptr f2__cause__add_cause_group(f2ptr cause, f2ptr this, f2ptr cause_group) {
  assert_argument_type(cause,       this);
  assert_argument_type(cause_group, cause_group);
  raw__cause__add_cause_group(cause, this, cause_group);
  return nil;
}
def_pcfunk2(cause__add_cause_group, this, cause_group,
	    "Adds a cause_group to this cause object in a thread-safe way.",
	    return f2__cause__add_cause_group(this_cause, this, cause_group));


// cause

f2ptr raw__cause__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"),      new__symbol(cause, "cause"),
						new__symbol(cause, "frame"),                  f2__cause__frame(                 cause, this),
						new__symbol(cause, "allocate_traced_arrays"), f2__cause__allocate_traced_arrays(cause, this),
						new__symbol(cause, "imagination_stack"),      f2__cause__imagination_stack(     cause, this),
						new__symbol(cause, "cause_groups"),           f2__cause__cause_groups(          cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__cause__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cause,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cause__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cause__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__cause__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2cause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cause__primobject_type__new(cause);
  {char* slot_name = "type_var_defined";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__funk);}
  {char* slot_name = "var_defined";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__funk);}
  {char* slot_name = "type_var_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__funk);}
  {char* slot_name = "var_value";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__funk);}
  {char* slot_name = "define";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);}
  {char* slot_name = "define-funk";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);}
  {char* slot_name = "lookup";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk);}
  {char* slot_name = "lookup-funk";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__funk);}
  {char* slot_name = "add_cause_group";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__funk);}
  return this;
}

// **

void f2__cause__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  
  // cause_group_interaction
  
  initialize_primobject_9_slot__defragment__fix_pointers(cause_group_interaction,
							 bytecode_count_scheduler_cmutex,
							 bytecode_count,
							 execution_nanoseconds_scheduler_cmutex,
							 execution_nanoseconds_chunk,
							 bytes_allocated_count_scheduler_cmutex,
							 bytes_allocated_count_chunk,
							 bytes_freed_count_scheduler_cmutex,
							 bytes_freed_count_chunk,
							 cause_group_interaction_interaction_ptypehash);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytecode_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_bytecode_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytecode_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__execution_nanoseconds__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_allocated_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_freed_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_freed_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_freed_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_bytes_freed_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_freed_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk);
  
  
  // cause_group
  
  initialize_primobject_9_slot__defragment__fix_pointers(cause_group,
							 bytecode_count_scheduler_cmutex,
							 bytecode_count,
							 execution_nanoseconds_scheduler_cmutex,
							 execution_nanoseconds_chunk,
							 bytes_allocated_count_scheduler_cmutex,
							 bytes_allocated_count_chunk,
							 bytes_freed_count_scheduler_cmutex,
							 bytes_freed_count_chunk,
							 cause_group_interaction_ptypehash);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__increase_bytecode_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__execution_nanoseconds__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__increase_execution_nanoseconds);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytes_allocated_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__increase_bytes_allocated_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytes_freed_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytes_freed_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__increase_bytes_freed_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__funk);
  
  
  // cause
  
  initialize_primobject_17_slot__defragment__fix_pointers(cause,
							  fibers_cmutex,
							  fibers,
							  frame,
							  allocate_traced_arrays,
							  bytecode_tracing_on,
							  memory_tracing_on,
							  imagination_stack,
							  bytecode_branch_callbacks,
							  bytecode_funk_callbacks,
							  bytecode_tracer_callbacks,
							  bytecode_endfunk_callbacks,
							  complete_funk_callbacks,
							  read_other_memory_callbacks,
							  write_other_memory_callbacks,
							  critics,
							  cause_groups_cmutex,
							  cause_groups);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__type_var_defined);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__var_defined);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__type_var_value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__var_value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.define__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__define);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__define__funk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__lookup);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__lookup__funk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__add_cause_group);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(cause);
}

void f2__cause__preinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  reinitialize_primobject(cause);
}
  
void f2__cause__reinitialize_globalvars() {
  f2__cause__preinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  //--
  
  
  // cause_group_interaction
  
  initialize_primobject_9_slot(cause_group_interaction,
			       bytecode_count_scheduler_cmutex,
			       bytecode_count,
			       execution_nanoseconds_scheduler_cmutex,
			       execution_nanoseconds_chunk,
			       bytes_allocated_count_scheduler_cmutex,
			       bytes_allocated_count_chunk,
			       bytes_freed_count_scheduler_cmutex,
			       bytes_freed_count_chunk,
			       cause_group_interaction_interaction_ptypehash);
  
  {char* symbol_str = "increase_bytecode_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytecode_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_bytecode_count, this, relative_bytecode_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytecode_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__execution_nanoseconds__set, this, relative_execution_nanoseconds__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.execution_nanoseconds__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_allocated_count, this, relative_bytes_allocated_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_allocated_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_allocated_count__set, this, relative_bytes_allocated_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_allocated_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_bytes_allocated_count, this, relative_bytes_allocated_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_allocated_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_freed_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_freed_count, this, relative_bytes_freed_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_freed_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_freed_count__set, this, relative_bytes_freed_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_freed_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_freed_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_freed_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_bytes_freed_count, this, relative_bytes_freed_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_freed_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // cause_group
  
  initialize_primobject_9_slot(cause_group,
			       bytecode_count_scheduler_cmutex,
			       bytecode_count,
			       execution_nanoseconds_scheduler_cmutex,
			       execution_nanoseconds_chunk,
			       bytes_allocated_count_scheduler_cmutex,
			       bytes_allocated_count_chunk,
			       bytes_freed_count_scheduler_cmutex,
			       bytes_freed_count_chunk,
			       cause_group_interaction_ptypehash);
  
  {char* symbol_str = "increase_bytecode_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_bytecode_count, this, relative_bytecode_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__execution_nanoseconds__set, this, relative_execution_nanoseconds__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytes_allocated_count, this, relative_bytes_allocated_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_allocated_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytes_allocated_count__set, this, relative_bytes_allocated_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_allocated_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_bytes_allocated_count, this, relative_bytes_allocated_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_freed_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytes_freed_count, this, relative_bytes_freed_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_freed_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytes_freed_count__set, this, relative_bytes_freed_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_freed_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_bytes_freed_count, this, relative_bytes_freed_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // cause
  
  initialize_primobject_17_slot(cause,
				fibers_cmutex,
				fibers,
				frame,
				allocate_traced_arrays,
				bytecode_tracing_on,
				memory_tracing_on,
				imagination_stack,
				bytecode_branch_callbacks,
				bytecode_funk_callbacks,
				bytecode_tracer_callbacks,
				bytecode_endfunk_callbacks,
				complete_funk_callbacks,
				read_other_memory_callbacks,
				write_other_memory_callbacks,
				critics,
				cause_groups_cmutex,
				cause_groups);
  
  {char* symbol_str = "type_var_defined"; __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__type_var_defined, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__funk = never_gc(cfunk);}
  {char* symbol_str = "var_defined"; __funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__var_defined, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__funk = never_gc(cfunk);}
  {char* symbol_str = "type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__type_var_value__set, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__funk = never_gc(cfunk);}
  {char* symbol_str = "var_value"; __funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__var_value__set, this, type, var, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__funk = never_gc(cfunk);}
  {char* symbol_str = "define"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define, this, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk = never_gc(cfunk);}
  {char* symbol_str = "define-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__define__funk, this, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup"; __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__lookup, this, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk = never_gc(cfunk);}
  {char* symbol_str = "lookup-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__lookup__funk, this, var, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__funk = never_gc(cfunk);}
  {char* symbol_str = "add_cause_group"; __funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__add_cause_group, this, cause_group, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(cause);
}

void f2__cause__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "cause", "", &f2__cause__reinitialize_globalvars, &f2__cause__defragment__fix_pointers);
  
  f2__cause__reinitialize_globalvars();
}

