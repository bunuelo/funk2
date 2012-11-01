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

def_primobject_6_slot(cause_group_interaction,
		      read_events_count_chunk,
		      bytes_read_count_scheduler_cmutex,
		      bytes_read_count_chunk,
		      write_events_count_chunk,
		      bytes_written_count_scheduler_cmutex,
		      bytes_written_count_chunk);

f2ptr f2__cause_group_interaction__new(f2ptr cause) {
  f2ptr read_events_count_chunk              = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_read_count_scheduler_cmutex    = f2scheduler_cmutex__new(cause);
  f2ptr bytes_read_count_chunk               = raw__chunk__new(cause, sizeof(u64));
  f2ptr write_events_count_chunk             = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_written_count_scheduler_cmutex = f2scheduler_cmutex__new(cause);
  f2ptr bytes_written_count_chunk            = raw__chunk__new(cause, sizeof(u64));
  return f2cause_group_interaction__new(cause,
					read_events_count_chunk,
					bytes_read_count_scheduler_cmutex,
					bytes_read_count_chunk,
					write_events_count_chunk,
					bytes_written_count_scheduler_cmutex,
					bytes_written_count_chunk);
}
def_pcfunk0(cause_group_interaction__new,
	    "",
	    return f2__cause_group_interaction__new(this_cause));


u64 raw__cause_group_interaction__read_events_count(f2ptr cause, f2ptr this) {
  f2ptr read_events_count_chunk = f2cause_group_interaction__read_events_count_chunk(this, cause);
  return f2chunk__bit64__elt(read_events_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__read_events_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__read_events_count(cause, this));
}
def_pcfunk1(cause_group_interaction__read_events_count, this,
	    "",
	    return f2__cause_group_interaction__read_events_count(this_cause, this));


void raw__cause_group_interaction__read_events_count__set(f2ptr cause, f2ptr this, u64 read_events_count) {
  f2ptr read_events_count_chunk = f2cause_group_interaction__read_events_count_chunk(this, cause);
  f2chunk__bit64__elt__set(read_events_count_chunk, 0, cause, read_events_count);
}

f2ptr f2__cause_group_interaction__read_events_count__set(f2ptr cause, f2ptr this, f2ptr read_events_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     read_events_count);
  u64 read_events_count__i = f2integer__i(read_events_count, cause);
  raw__cause_group_interaction__read_events_count__set(cause, this, read_events_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__read_events_count__set, this, read_events_count,
	    "",
	    return f2__cause_group_interaction__read_events_count__set(this_cause, this, read_events_count));


u64 raw__cause_group_interaction__bytes_read_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_read_count_chunk = f2cause_group_interaction__bytes_read_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_read_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__bytes_read_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__bytes_read_count(cause, this));
}
def_pcfunk1(cause_group_interaction__bytes_read_count, this,
	    "",
	    return f2__cause_group_interaction__bytes_read_count(this_cause, this));


void raw__cause_group_interaction__bytes_read_count__set(f2ptr cause, f2ptr this, u64 bytes_read_count) {
  f2ptr bytes_read_count_chunk = f2cause_group_interaction__bytes_read_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_read_count_chunk, 0, cause, bytes_read_count);
}

f2ptr f2__cause_group_interaction__bytes_read_count__set(f2ptr cause, f2ptr this, f2ptr bytes_read_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     bytes_read_count);
  u64 bytes_read_count__i = f2integer__i(bytes_read_count, cause);
  raw__cause_group_interaction__bytes_read_count__set(cause, this, bytes_read_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__bytes_read_count__set, this, bytes_read_count,
	    "",
	    return f2__cause_group_interaction__bytes_read_count__set(this_cause, this, bytes_read_count));


void raw__cause_group_interaction__increase_bytes_read_count(f2ptr cause, f2ptr this, u64 relative_bytes_read_count) {
  f2ptr bytes_read_count_scheduler_cmutex = f2cause_group_interaction__bytes_read_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_read_count_scheduler_cmutex, cause);
  {
    u64 read_events_count = raw__cause_group_interaction__read_events_count(cause, this);
    raw__cause_group_interaction__read_events_count__set(cause, this, read_events_count + 1);
  }
  {
    u64 bytes_read_count = raw__cause_group_interaction__bytes_read_count(cause, this);
    raw__cause_group_interaction__bytes_read_count__set(cause, this, bytes_read_count + relative_bytes_read_count);
  }
  f2scheduler_cmutex__unlock(bytes_read_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_bytes_read_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_read_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     relative_bytes_read_count);
  u64 relative_bytes_read_count__i = (u64)f2integer__i(relative_bytes_read_count, cause);
  raw__cause_group_interaction__increase_bytes_read_count(cause, this, relative_bytes_read_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_bytes_read_count, this, relative_bytes_read_count,
	    "",
	    return f2__cause_group_interaction__increase_bytes_read_count(this_cause, this, relative_bytes_read_count));


u64 raw__cause_group_interaction__write_events_count(f2ptr cause, f2ptr this) {
  f2ptr write_events_count_chunk = f2cause_group_interaction__write_events_count_chunk(this, cause);
  return f2chunk__bit64__elt(write_events_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__write_events_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__write_events_count(cause, this));
}
def_pcfunk1(cause_group_interaction__write_events_count, this,
	    "",
	    return f2__cause_group_interaction__write_events_count(this_cause, this));


void raw__cause_group_interaction__write_events_count__set(f2ptr cause, f2ptr this, u64 write_events_count) {
  f2ptr write_events_count_chunk = f2cause_group_interaction__write_events_count_chunk(this, cause);
  f2chunk__bit64__elt__set(write_events_count_chunk, 0, cause, write_events_count);
}

f2ptr f2__cause_group_interaction__write_events_count__set(f2ptr cause, f2ptr this, f2ptr write_events_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     write_events_count);
  u64 write_events_count__i = f2integer__i(write_events_count, cause);
  raw__cause_group_interaction__write_events_count__set(cause, this, write_events_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__write_events_count__set, this, write_events_count,
	    "",
	    return f2__cause_group_interaction__write_events_count__set(this_cause, this, write_events_count));


u64 raw__cause_group_interaction__bytes_written_count(f2ptr cause, f2ptr this) {
  f2ptr bytes_written_count_chunk = f2cause_group_interaction__bytes_written_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytes_written_count_chunk, 0, cause);
}

f2ptr f2__cause_group_interaction__bytes_written_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group_interaction, this);
  return f2integer__new(cause, raw__cause_group_interaction__bytes_written_count(cause, this));
}
def_pcfunk1(cause_group_interaction__bytes_written_count, this,
	    "",
	    return f2__cause_group_interaction__bytes_written_count(this_cause, this));


void raw__cause_group_interaction__bytes_written_count__set(f2ptr cause, f2ptr this, u64 bytes_written_count) {
  f2ptr bytes_written_count_chunk = f2cause_group_interaction__bytes_written_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytes_written_count_chunk, 0, cause, bytes_written_count);
}

f2ptr f2__cause_group_interaction__bytes_written_count__set(f2ptr cause, f2ptr this, f2ptr bytes_written_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,     bytes_written_count);
  u64 bytes_written_count__i = f2integer__i(bytes_written_count, cause);
  raw__cause_group_interaction__bytes_written_count__set(cause, this, bytes_written_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__bytes_written_count__set, this, bytes_written_count,
	    "",
	    return f2__cause_group_interaction__bytes_written_count__set(this_cause, this, bytes_written_count));


void raw__cause_group_interaction__increase_bytes_written_count(f2ptr cause, f2ptr this, u64 relative_bytes_written_count) {
  f2ptr bytes_written_count_scheduler_cmutex = f2cause_group_interaction__bytes_written_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytes_written_count_scheduler_cmutex, cause);
  {
    u64 write_events_count = raw__cause_group_interaction__write_events_count(cause, this);
    raw__cause_group_interaction__write_events_count__set(cause, this, write_events_count + 1);
  }
  {
    u64 bytes_written_count = raw__cause_group_interaction__bytes_written_count(cause, this);
    raw__cause_group_interaction__bytes_written_count__set(cause, this, bytes_written_count + relative_bytes_written_count);
  }
  f2scheduler_cmutex__unlock(bytes_written_count_scheduler_cmutex, cause);
}

f2ptr f2__cause_group_interaction__increase_bytes_written_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_written_count) {
  assert_argument_type(cause_group_interaction, this);
  assert_argument_type(integer,                 relative_bytes_written_count);
  u64 relative_bytes_written_count__i = (u64)f2integer__i(relative_bytes_written_count, cause);
  raw__cause_group_interaction__increase_bytes_written_count(cause, this, relative_bytes_written_count__i);
  return nil;
}
def_pcfunk2(cause_group_interaction__increase_bytes_written_count, this, relative_bytes_written_count,
	    "",
	    return f2__cause_group_interaction__increase_bytes_written_count(this_cause, this, relative_bytes_written_count));


// cause_group_interaction

f2ptr raw__cause_group_interaction__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"),   new__symbol(cause, "cause_group_interaction"),
						new__symbol(cause, "read_events_count"),   f2__cause_group_interaction__read_events_count(  cause, this),
						new__symbol(cause, "bytes_read_count"),    f2__cause_group_interaction__bytes_read_count(   cause, this),
						new__symbol(cause, "write_events_count"),  f2__cause_group_interaction__write_events_count( cause, this),
						new__symbol(cause, "bytes_written_count"), f2__cause_group_interaction__bytes_written_count(cause, this)));
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
  {char* slot_name = "read_events_count";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__funk);}
  {char* slot_name = "read_events_count";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__set__funk);}
  {char* slot_name = "bytes_read_count";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__funk);}
  {char* slot_name = "bytes_read_count";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__set__funk);}
  {char* slot_name = "increase_bytes_read_count";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_read_count__funk);}
  {char* slot_name = "write_events_count";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__funk);}
  {char* slot_name = "write_events_count";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__set__funk);}
  {char* slot_name = "bytes_written_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__funk);}
  {char* slot_name = "bytes_written_count";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__set__funk);}
  {char* slot_name = "increase_bytes_written_count"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_written_count__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk);}
  return this;
}



// cause_group

def_primobject_11_slot(cause_group,
		       bytecode_count_scheduler_cmutex,
		       bytecode_count_chunk,
		       execution_nanoseconds_scheduler_cmutex,
		       execution_nanoseconds_chunk,
		       bytes_allocated_count_scheduler_cmutex,
		       bytes_allocated_count_chunk,
		       bytes_freed_count_scheduler_cmutex,
		       bytes_freed_count_chunk,
		       cause_group_interaction_scheduler_ptypehash,
		       counter_scheduler_ptypehash,
		       frame);

f2ptr f2__cause_group__new(f2ptr cause) {
  f2ptr bytecode_count_scheduler_cmutex             = f2scheduler_cmutex__new(cause);
  f2ptr bytecode_count_chunk                        = raw__chunk__new(cause, sizeof(u64));
  f2ptr execution_nanoseconds_scheduler_cmutex      = f2scheduler_cmutex__new(cause);
  f2ptr execution_nanoseconds_chunk                 = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_allocated_count_scheduler_cmutex      = f2scheduler_cmutex__new(cause);
  f2ptr bytes_allocated_count_chunk                 = raw__chunk__new(cause, sizeof(u64));
  f2ptr bytes_freed_count_scheduler_cmutex          = f2scheduler_cmutex__new(cause);
  f2ptr bytes_freed_count_chunk                     = raw__chunk__new(cause, sizeof(u64));
  f2ptr cause_group_interaction_scheduler_ptypehash = f2__scheduler_ptypehash__new(cause);
  f2ptr counter_scheduler_ptypehash                 = f2__scheduler_ptypehash__new(cause);
  f2ptr frame                                       = f2__frame__new(cause, nil);
  return f2cause_group__new(cause,
			    bytecode_count_scheduler_cmutex,
			    bytecode_count_chunk,
			    execution_nanoseconds_scheduler_cmutex,
			    execution_nanoseconds_chunk,
			    bytes_allocated_count_scheduler_cmutex,
			    bytes_allocated_count_chunk,
			    bytes_freed_count_scheduler_cmutex,
			    bytes_freed_count_chunk,
			    cause_group_interaction_scheduler_ptypehash,
			    counter_scheduler_ptypehash,
			    frame);
}
def_pcfunk0(cause_group__new,
	    "",
	    return f2__cause_group__new(this_cause));


u64 raw__cause_group__bytecode_count(f2ptr cause, f2ptr this) {
  f2ptr bytecode_count_chunk = f2cause_group__bytecode_count_chunk(this, cause);
  return f2chunk__bit64__elt(bytecode_count_chunk, 0, cause);
}

f2ptr f2__cause_group__bytecode_count(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group, this);
  return f2integer__new(cause, raw__cause_group__bytecode_count(cause, this));
}
def_pcfunk1(cause_group__bytecode_count, this,
	    "",
	    return f2__cause_group__bytecode_count(this_cause, this));


void raw__cause_group__bytecode_count__set(f2ptr cause, f2ptr this, u64 bytecode_count) {
  f2ptr bytecode_count_chunk = f2cause_group__bytecode_count_chunk(this, cause);
  f2chunk__bit64__elt__set(bytecode_count_chunk, 0, cause, bytecode_count);
}

f2ptr f2__cause_group__bytecode_count__set(f2ptr cause, f2ptr this, f2ptr bytecode_count) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     bytecode_count);
  u64 bytecode_count__i = f2integer__i(bytecode_count, cause);
  raw__cause_group__bytecode_count__set(cause, this, bytecode_count__i);
  return nil;
}
def_pcfunk2(cause_group__bytecode_count__set, this, bytecode_count,
	    "",
	    return f2__cause_group__bytecode_count__set(this_cause, this, bytecode_count));


void raw__cause_group__increase_bytecode_count(f2ptr cause, f2ptr this, u64 relative_bytecode_count) {
  f2ptr bytecode_count_scheduler_cmutex = f2cause_group__bytecode_count_scheduler_cmutex(this, cause);
  f2scheduler_cmutex__lock(bytecode_count_scheduler_cmutex, cause);
  u64 bytecode_count = raw__cause_group__bytecode_count(cause, this);
  raw__cause_group__bytecode_count__set(cause, this, bytecode_count + relative_bytecode_count);
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


f2ptr raw__cause_group__execution_time(f2ptr cause, f2ptr this) {
  f2ptr execution_nanoseconds = f2__cause_group__execution_nanoseconds(cause, this);
  return f2__relative_time__new(cause, execution_nanoseconds);
}

f2ptr f2__cause_group__execution_time(f2ptr cause, f2ptr this) {
  assert_argument_type(cause_group, this);
  return raw__cause_group__execution_time(cause, this);
}
def_pcfunk1(cause_group__execution_time, this,
	    "",
	    return f2__cause_group__execution_time(this_cause, this));


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


void raw__cause_group__add_cause_group_interaction(f2ptr cause, f2ptr this, f2ptr cause_group, f2ptr cause_group_interaction) {
  f2ptr cause_group_interaction_scheduler_ptypehash = f2cause_group__cause_group_interaction_scheduler_ptypehash(this, cause);
  raw__scheduler_ptypehash__add(cause, cause_group_interaction_scheduler_ptypehash, cause_group, cause_group_interaction);
}

f2ptr f2__cause_group__add_cause_group_interaction(f2ptr cause, f2ptr this, f2ptr cause_group, f2ptr cause_group_interaction) {
  assert_argument_type(cause_group,             this);
  assert_argument_type(cause_group,             cause_group);
  assert_argument_type(cause_group_interaction, cause_group_interaction);
  raw__cause_group__add_cause_group_interaction(cause, this, cause_group, cause_group_interaction);
  return nil;
}
def_pcfunk3(cause_group__add_cause_group_interaction, this, cause_group, cause_group_interaction,
	    "",
	    return f2__cause_group__add_cause_group_interaction(this_cause, this, cause_group, cause_group_interaction));


void raw__cause_group__assure_counter_exists(f2ptr cause, f2ptr this, f2ptr counter_name) {
  f2ptr counter_scheduler_ptypehash = f2cause_group__counter_scheduler_ptypehash(this, cause);
  if (! raw__scheduler_ptypehash__contains(cause, counter_scheduler_ptypehash, counter_name)) {
    f2ptr counter = raw__counter__new(cause);
    raw__scheduler_ptypehash__add(cause, counter_scheduler_ptypehash, counter_name, counter);
  }
}

f2ptr f2__cause_group__assure_counter_exists(f2ptr cause, f2ptr this, f2ptr counter_name) {
  assert_argument_type(cause_group, this);
  raw__cause_group__assure_counter_exists(cause, this, counter_name);
  return nil;
}
def_pcfunk2(cause_group__assure_counter_exists, this, counter_name,
	    "",
	    return f2__cause_group__assure_counter_exists(this_cause, this, counter_name));


f2ptr raw__cause_group__counter(f2ptr cause, f2ptr this, f2ptr counter_name) {
  f2ptr counter_scheduler_ptypehash = f2cause_group__counter_scheduler_ptypehash(this, cause);
  if (! raw__scheduler_ptypehash__contains(cause, counter_scheduler_ptypehash, counter_name)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),     new__symbol(cause, "cause_group-does-not-contain-counter"),
				   new__symbol(cause, "cause_group"),  this,
				   new__symbol(cause, "counter_name"), counter_name));
  }
  return raw__scheduler_ptypehash__lookup(cause, counter_scheduler_ptypehash, counter_name);
}

f2ptr f2__cause_group__counter(f2ptr cause, f2ptr this, f2ptr counter_name) {
  assert_argument_type(cause_group, this);
  return raw__cause_group__counter(cause, this, counter_name);
}
def_pcfunk2(cause_group__counter, this, counter_name,
	    "",
	    return f2__cause_group__counter(this_cause, this, counter_name));


void raw__cause_group__increment_counter_if_exists(f2ptr cause, f2ptr this, f2ptr counter_name, s64 relative_value__i) {
  f2ptr counter_scheduler_ptypehash = f2cause_group__counter_scheduler_ptypehash(this, cause);
  if (raw__scheduler_ptypehash__contains(cause, counter_scheduler_ptypehash, counter_name)) {
    f2ptr counter = raw__scheduler_ptypehash__lookup(cause, counter_scheduler_ptypehash, counter_name);
    raw__counter__increment(cause, counter, relative_value__i);
  }
}

f2ptr f2__cause_group__increment_counter_if_exists(f2ptr cause, f2ptr this, f2ptr counter_name, f2ptr relative_value) {
  assert_argument_type(cause_group, this);
  assert_argument_type(integer,     relative_value);
  s64 relative_value__i = f2integer__i(relative_value, cause);
  raw__cause_group__increment_counter_if_exists(cause, this, counter_name, relative_value__i);
  return nil;
}
def_pcfunk3(cause_group__increment_counter_if_exists, this, counter_name, relative_value,
	    "",
	    return f2__cause_group__increment_counter_if_exists(this_cause, this, counter_name, relative_value));


f2ptr raw__cause_group__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr frame = f2cause_group__frame(this, cause);
  if (raw__frame__contains_type_var(cause, frame, type, var)) {
    return raw__frame__lookup_type_var_value(cause, frame, type, var, nil);
  } else {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "cause_group-lookup_type_var_value-variable_not_defined"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "type"),     type,
				   new__symbol(cause, "var"),      var));
  }
}

f2ptr f2__cause_group__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(cause_group, this);
  assert_argument_type(symbol,      type);
  assert_argument_type(symbol,      var);
  return raw__cause_group__lookup_type_var_value(cause, this, type, var);
}


f2ptr raw__cause_group__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr frame = f2cause_group__frame(this, cause);
  if (raw__frame__contains_type_var(cause, frame, type, var)) {
    return raw__frame__type_var_value__set(cause, frame, type, var, value, nil);
  } else {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "cause_group-lookup_type_var_value-set-variable_not_defined"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "type"),     type,
				   new__symbol(cause, "var"),      var));
  }
}

f2ptr f2__cause_group__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  assert_argument_type(cause_group, this);
  assert_argument_type(symbol,      type);
  assert_argument_type(symbol,      var);
  return raw__cause_group__type_var_value__set(cause, this, type, var, value);
}
def_pcfunk4(cause_group__type_var_value__set, this, type, var, value,
	    "",
	    return f2__cause_group__type_var_value__set(this_cause, this, type, var, value));




boolean_t raw__cause_group__type_var_defined(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr frame = f2cause_group__frame(this, cause);
  return raw__frame__contains_type_var(cause, frame, type, var);
}

f2ptr f2__cause_group__type_var_defined(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  assert_argument_type(cause_group, this);
  return f2bool__new(raw__cause_group__type_var_defined(cause, this, type, var));
}
def_pcfunk3(cause_group__type_var_defined, this, type, var,
	    "",
	    return f2__cause_group__type_var_defined(this_cause, this, type, var));


// cause_group

f2ptr raw__cause_group__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list18__new(cause,
						new__symbol(cause, "print_object_type"),                           new__symbol(cause, "cause_group"),
						new__symbol(cause, "print_object_slot_order"),                     f2list7__new(cause,
																new__symbol(cause, "bytecode_count"),
																new__symbol(cause, "execution_time"),
																new__symbol(cause, "bytes_allocated_count"),
																new__symbol(cause, "bytes_freed_count"),
																new__symbol(cause, "cause_group_interaction_scheduler_ptypehash"),
																new__symbol(cause, "counter_scheduler_ptypehash"),
																new__symbol(cause, "frame")),
						new__symbol(cause, "bytecode_count"),                              f2__cause_group__bytecode_count(                             cause, this),
						new__symbol(cause, "execution_time"),                              f2__cause_group__execution_time(                             cause, this),
						new__symbol(cause, "bytes_allocated_count"),                       f2__cause_group__bytes_allocated_count(                      cause, this),
						new__symbol(cause, "bytes_freed_count"),                           f2__cause_group__bytes_freed_count(                          cause, this),
						new__symbol(cause, "cause_group_interaction_scheduler_ptypehash"), f2__cause_group__cause_group_interaction_scheduler_ptypehash(cause, this),
						new__symbol(cause, "counter_scheduler_ptypehash"),                 f2__cause_group__counter_scheduler_ptypehash(                cause, this),
						new__symbol(cause, "frame"),                                       f2__cause_group__frame(                                      cause, this)));
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
  {char* slot_name = "bytecode_count";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__funk);}
  {char* slot_name = "bytecode_count";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__set__funk);}
  {char* slot_name = "increase_bytecode_count";        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__funk);}
  {char* slot_name = "execution_nanoseconds";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__funk);}
  {char* slot_name = "increase_execution_nanoseconds"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__funk);}
  {char* slot_name = "execution_time";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_time__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__funk);}
  {char* slot_name = "bytes_allocated_count";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_allocated_count__set__funk);}
  {char* slot_name = "increase_bytes_allocated_count"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_allocated_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__funk);}
  {char* slot_name = "bytes_freed_count";              f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytes_freed_count__set__funk);}
  {char* slot_name = "increase_bytes_freed_count";     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytes_freed_count__funk);}
  {char* slot_name = "add_cause_group_interaction";    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.add_cause_group_interaction__funk);}
  {char* slot_name = "assure_counter_exists";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.assure_counter_exists__funk);}
  {char* slot_name = "counter";                        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.counter__funk);}
  {char* slot_name = "increment_counter_if_exists";    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increment_counter_if_exists__funk);}
  {char* slot_name = "lookup_type_var_value";          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.lookup_type_var_value__funk);}
  {char* slot_name = "type_var_value-set";             f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value__set__funk);}
  {char* slot_name = "type_var_value_defined";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value_defined__funk);}
  {char* slot_name = "terminal_print_with_frame";      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause_group.terminal_print_with_frame__funk);}
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

f2ptr raw__cause__add_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr cause_reg = f2fiber__cause_reg(fiber, cause);
  f2ptr result    = nil;
  if (cause_reg == nil) {
    f2fiber__cause_reg__set(fiber, cause, this);
    f2cause__fibers__set(   this,  cause, raw__cons__new(cause, fiber, f2cause__fibers(this, cause)));
  } else {
    result = f2larva__new(cause, 827152, nil);
  }
  return result;
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
  f2ptr result = raw__cause__add_fiber__thread_unsafe(cause, this, fiber);
  f2cmutex__unlock(fibers_cmutex,    cause);
  f2cmutex__unlock(cause_reg_cmutex, cause);
  return result;
}

f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  assert_argument_type(cause, this);
  assert_argument_type(fiber, fiber);
  return raw__cause__add_fiber(cause, this, fiber);
}


f2ptr raw__cause__remove_fiber__thread_unsafe(f2ptr cause, f2ptr this, f2ptr fiber) {
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
  return result;
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
  f2ptr result = raw__cause__remove_fiber__thread_unsafe(cause, this, fiber);
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
  f2cause__imagination_stack__set(new_cause, cause, raw__cons__new(cause, imagination_name, f2cause__imagination_stack(cause, new_cause)));
  return new_cause;
}

f2ptr raw__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr     cause_iter   = this;
  f2ptr     value        = nil;
  boolean_t keep_looping;
  do {
    keep_looping = boolean__false;
    f2ptr     cause_frame   = f2cause__frame(cause_iter, cause);
    boolean_t value_defined = boolean__false;
    if ((cause_frame != nil) &&
	raw__frame__contains_type_var(cause, cause_frame, type, var)) {
      value_defined = boolean__true;
      value         = raw__frame__lookup_type_var_value(cause, cause_frame, type, var, nil);
    }
    if (! value_defined) {
      f2ptr cause_groups     = f2cause__cause_groups(this, cause);
      f2ptr cause_group_iter = cause_groups;
      while (cause_group_iter != nil) {
	f2ptr cause_group = f2cons__car(cause_group_iter, cause);
	if (raw__cause_group__type_var_defined(cause, cause_group, type, var)) {
	  value_defined    = boolean__true;
	  value            = raw__cause_group__lookup_type_var_value(cause, cause_group, type, var);
	  cause_group_iter = nil;
	} else {
	  cause_group_iter = f2cons__cdr(cause_group_iter, cause);
	}
      }
    }
    if (! value_defined) {
      cause_iter = f2__ptype__cause(cause, cause_iter);
      if (cause_iter != nil) {
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
  assert_argument_type(cause,  this);
  assert_argument_type(symbol, type);
  assert_argument_type(symbol, var);
  return raw__cause__lookup_type_var_value(cause, this, type, var);
}


f2ptr raw__cause__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr     result       = nil;
  f2ptr     cause_iter   = this;
  boolean_t keep_looping;
  do {
    keep_looping = boolean__false;
    f2ptr     cause_frame   = f2cause__frame(cause_iter, cause);
    boolean_t value_defined = boolean__false;
    if ((cause_frame != nil) &&
	raw__frame__contains_type_var(cause, cause_frame, type, var)) {
      value_defined = boolean__true;
      result        = raw__frame__type_var_value__set(cause, cause_frame, type, var, value, nil);
    }
    if (! value_defined) {
      f2ptr cause_groups     = f2cause__cause_groups(this, cause);
      f2ptr cause_group_iter = cause_groups;
      while (cause_group_iter != nil) {
	f2ptr cause_group = f2cons__car(cause_group_iter, cause);
	if (raw__cause_group__type_var_defined(cause, cause_group, type, var)) {
	  value_defined    = boolean__true;
	  value            = raw__cause_group__type_var_value__set(cause, cause_group, type, var);
	  cause_group_iter = nil;
	} else {
	  cause_group_iter = f2cons__cdr(cause_group_iter, cause);
	}
      }
    }
    if (! value_defined) {
      cause_iter = f2__ptype__cause(cause, cause_iter);
      if (cause_iter != nil) {
	keep_looping = boolean__true;
      } else {
	result = new__error(f2list8__new(cause,
					 new__symbol(cause, "bug_name"),      new__symbol(cause, "type_var_does_not_exist_in_cause"),
					 new__symbol(cause, "this"),          this,
					 new__symbol(cause, "variable_type"), type,
					 new__symbol(cause, "variable_name"), var));
      }
    }
  } while (keep_looping);
  return result;
}

f2ptr f2__cause__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  assert_argument_type(cause,  this);
  assert_argument_type(symbol, type);
  assert_argument_type(symbol, var);
  return raw__cause__type_var_value__set(cause, this, type, var, value);
}
def_pcfunk4(cause__type_var_value__set, this, type, var, value,
	    "",
	    return f2__cause__type_var_value__set(this_cause, this, type, var, value));




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
  f2cause__cause_groups__set(this, cause, raw__cons__new(cause, cause_group, cause_groups));
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


void raw__cause__increment_counters_if_exist(f2ptr cause, f2ptr this, f2ptr counter_name, s64 relative_value__i) {
  f2ptr cause_group_iter = f2cause__cause_groups(this, cause);
  while (cause_group_iter != nil) {
    f2ptr cause_group = f2cons__car(cause_group_iter, cause);
    raw__cause_group__increment_counter_if_exists(cause, cause_group, counter_name, 1);
    cause_group_iter = f2cons__cdr(cause_group_iter, cause);
  }
}

f2ptr f2__cause__increment_counters_if_exist(f2ptr cause, f2ptr this, f2ptr counter_name, f2ptr relative_value) {
  assert_argument_type(cause,   this);
  assert_argument_type(integer, relative_value);
  s64 relative_value__i = f2integer__i(relative_value, cause);
  raw__cause__increment_counters_if_exist(cause, this, counter_name, relative_value__i);
  return nil;
}
def_pcfunk3(cause__increment_counters_if_exist, this, counter_name, relative_value,
	    "Increments all cause_group counters of the given name if they exist.",
	    return f2__cause__increment_counters_if_exist(this_cause, this, counter_name, relative_value));


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
  {char* slot_name = "type_var_defined";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_defined__funk);}
  {char* slot_name = "var_defined";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.var_defined__funk);}
  {char* slot_name = "type_var_value";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.type_var_value__set__funk);}
  {char* slot_name = "var_value";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.var_value__set__funk);}
  {char* slot_name = "define";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk);}
  {char* slot_name = "define-funk";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk);}
  {char* slot_name = "lookup";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk);}
  {char* slot_name = "lookup-funk";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.lookup__funk__funk);}
  {char* slot_name = "add_cause_group";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.add_cause_group__funk);}
  {char* slot_name = "increment_counters_if_exist"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.increment_counters_if_exist__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__funk);}
  return this;
}

// **

void f2__cause__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  
  // cause_group_interaction
  
  initialize_primobject_6_slot__defragment__fix_pointers(cause_group_interaction,
							 read_events_count_chunk,
							 bytes_read_count_scheduler_cmutex,
							 bytes_read_count_chunk,
							 write_events_count_chunk,
							 bytes_written_count_scheduler_cmutex,
							 bytes_written_count_chunk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__read_events_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__read_events_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_read_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_read_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_read_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_bytes_read_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_read_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__write_events_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__write_events_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_written_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__bytes_written_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_written_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__increase_bytes_written_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_written_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group_interaction__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk);
  
  
  // cause_group
  
  initialize_primobject_11_slot__defragment__fix_pointers(cause_group,
							  bytecode_count_scheduler_cmutex,
							 bytecode_count_chunk,
							  execution_nanoseconds_scheduler_cmutex,
							  execution_nanoseconds_chunk,
							  bytes_allocated_count_scheduler_cmutex,
							  bytes_allocated_count_chunk,
							  bytes_freed_count_scheduler_cmutex,
							  bytes_freed_count_chunk,
							  cause_group_interaction_scheduler_ptypehash,
							  counter_scheduler_ptypehash,
							  frame);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytecode_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__bytecode_count__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__set__funk);
  
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
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_time__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__execution_time);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_time__funk);
  
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
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.add_cause_group_interaction__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__add_cause_group_interaction);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.add_cause_group_interaction__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.assure_counter_exists__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__assure_counter_exists);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.assure_counter_exists__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.counter__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__counter);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.counter__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increment_counter_if_exists__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__increment_counter_if_exists);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.increment_counter_if_exists__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.lookup_type_var_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__lookup_type_var_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.lookup_type_var_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__type_var_value__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value_defined__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause_group__type_var_value_defined);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value_defined__funk);
  
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
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.increment_counters_if_exist__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cause__increment_counters_if_exist);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_cause.increment_counters_if_exist__funk);
  
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
  
  initialize_primobject_6_slot(cause_group_interaction,
			       read_events_count_chunk,
			       bytes_read_count_scheduler_cmutex,
			       bytes_read_count_chunk,
			       write_events_count_chunk,
			       bytes_written_count_scheduler_cmutex,
			       bytes_written_count_chunk);
  
  {char* symbol_str = "read_events_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__read_events_count, this, relative_read_events_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "read_events_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__read_events_count__set, this, relative_read_events_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.read_events_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_read_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_read_count, this, relative_bytes_read_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_read_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_read_count__set, this, relative_bytes_read_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_read_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_read_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_read_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_bytes_read_count, this, relative_bytes_read_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_read_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "write_events_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__write_events_count, this, relative_write_events_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "write_events_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__write_events_count__set, this, relative_write_events_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.write_events_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_written_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_written_count, this, relative_bytes_written_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytes_written_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__bytes_written_count__set, this, relative_bytes_written_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.bytes_written_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytes_written_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_written_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__increase_bytes_written_count, this, relative_bytes_written_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.increase_bytes_written_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group_interaction__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group_interaction.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // cause_group
  
  initialize_primobject_11_slot(cause_group,
				bytecode_count_scheduler_cmutex,
				bytecode_count_chunk,
				execution_nanoseconds_scheduler_cmutex,
				execution_nanoseconds_chunk,
				bytes_allocated_count_scheduler_cmutex,
				bytes_allocated_count_chunk,
				bytes_freed_count_scheduler_cmutex,
				bytes_freed_count_chunk,
				cause_group_interaction_scheduler_ptypehash,
				counter_scheduler_ptypehash,
				frame);
  
  {char* symbol_str = "bytecode_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytecode_count, this, relative_bytecode_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "bytecode_count-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__bytecode_count__set, this, relative_bytecode_count__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.bytecode_count__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_bytecode_count"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_bytecode_count, this, relative_bytecode_count, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_bytecode_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_nanoseconds-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__execution_nanoseconds__set, this, relative_execution_nanoseconds__set, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_nanoseconds__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increase_execution_nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__increase_execution_nanoseconds, this, relative_execution_nanoseconds, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increase_execution_nanoseconds__funk = never_gc(cfunk);}
  
  {char* symbol_str = "execution_time"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_time__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__execution_time, this, relative_execution_time, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.execution_time__funk = never_gc(cfunk);}
  
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
  
  {char* symbol_str = "add_cause_group_interaction"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.add_cause_group_interaction__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause_group__add_cause_group_interaction, this, cause_group, cause_group_interaction, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.add_cause_group_interaction__funk = never_gc(cfunk);}
  
  {char* symbol_str = "assure_counter_exists"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.assure_counter_exists__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__assure_counter_exists, this, counter_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.assure_counter_exists__funk = never_gc(cfunk);}
  
  {char* symbol_str = "counter"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.counter__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__counter, this, counter_name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.counter__funk = never_gc(cfunk);}
  
  {char* symbol_str = "increment_counter_if_exists"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increment_counter_if_exists__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause_group__increment_counter_if_exists, this, counter_name, relative_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.increment_counter_if_exists__funk = never_gc(cfunk);}
  
  {char* symbol_str = "lookup_type_var_value"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.lookup_type_var_value__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__lookup_type_var_value, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.lookup_type_var_value__funk = never_gc(cfunk);}
  
  {char* symbol_str = "type_var_value-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__type_var_value__set, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value__set__funk = never_gc(cfunk);}
  
  {char* symbol_str = "type_var_value_defined"; __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value_defined__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause_group__type_var_value_defined, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause_group.type_var_value_defined__funk = never_gc(cfunk);}
  
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
  {char* symbol_str = "increment_counters_if_exist"; __funk2.globalenv.object_type.primobject.primobject_type_cause.increment_counters_if_exist__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(cause__increment_counters_if_exist, this, counter_name, relative_value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.increment_counters_if_exist__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_cause.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__0(cause);
}

void f2__cause__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "cause", "", &f2__cause__reinitialize_globalvars, &f2__cause__defragment__fix_pointers);
  
  f2__cause__reinitialize_globalvars();
}

