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

#ifndef THOUGHT_PROCESS__H
#define THOUGHT_PROCESS__H

#include "f2_primobjects.h"

// thought_process_types

typedef struct funk2_thought_process_s {
  f2ptr ptype_free_memory__symbol;
  f2ptr ptype_newly_allocated__symbol;
  f2ptr ptype_memory__symbol;
  f2ptr ptype_integer__symbol;
  f2ptr ptype_double__symbol;
  f2ptr ptype_float__symbol;
  f2ptr ptype_pointer__symbol;
  f2ptr ptype_gfunkptr__symbol;
  f2ptr ptype_scheduler_cmutex__symbol;
  f2ptr ptype_cmutex__symbol;
  f2ptr ptype_char__symbol;
  f2ptr ptype_string__symbol;
  f2ptr ptype_symbol__symbol;
  f2ptr ptype_chunk__symbol;
  f2ptr ptype_simple_array__symbol;
  f2ptr ptype_traced_array__symbol;
  f2ptr ptype_larva__symbol;
  // thought_process_type
  f2ptr thought_process_type__symbol;
  // thought_process
  f2ptr thought_process__symbol;
  f2ptr real_value_slot__symbol;
  f2ptr global_thought_process_type_hash__symbol;
  f2ptr global_thought_process_type_hash;
} funk2_thought_process_t;

// thought_process

boolean_t raw__thought_process__is_type(f2ptr cause, f2ptr x);
f2ptr f2__thought_process__is_type(f2ptr cause, f2ptr x);
f2ptr f2thought_process__new__trace_depth(f2ptr cause, f2ptr read_write_execute_slot_hash, int trace_depth);
f2ptr f2thought_process__new(f2ptr cause, f2ptr read_write_execute_slot_hash);


#define f2primobject__is_thought_process(this, cause) (f2primobject__object_type(this, cause) == __funk2.thought_process.thought_process__symbol)

defprimobject__static_slot__prototype(thought_process__read_write_execute_slot_hash);
#define f2thought_process__read_write_execute_slot_hash(                  this, cause)                     primobject__static_slot__accessor(        this, thought_process__read_write_execute_slot_hash, cause)
#define f2thought_process__read_write_execute_slot_hash__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, thought_process__read_write_execute_slot_hash, cause, value, trace_depth)
#define f2thought_process__read_write_execute_slot_hash__set(             this, cause, value)              primobject__static_slot__set(             this, thought_process__read_write_execute_slot_hash, cause, value)
#define f2thought_process__read_write_execute_slot_hash__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, thought_process__read_write_execute_slot_hash, cause)
#define f2thought_process__read_write_execute_slot_hash__trace(           this, cause)                     primobject__static_slot__trace(           this, thought_process__read_write_execute_slot_hash, cause)
#define f2thought_process__read_write_execute_slot_hash__cause(           this, cause)                     primobject__static_slot__cause(           this, thought_process__read_write_execute_slot_hash, cause)


// thought process initialization

void funk2_thought_process__init(funk2_thought_process_t* this);
void funk2_thought_process__destroy(funk2_thought_process_t* this);

void f2__thought_process__reinitialize_globalvars();
void f2__thought_process__initialize();


#endif // THOUGHT_PROCESS__H

