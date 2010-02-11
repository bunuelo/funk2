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

#include "funk2.h"

void funk2_event_router__init(funk2_event_router_t* this, u32 input_buffer__byte_num) {
  this->last_checked_event_buffers__nanoseconds_since_1970 = 0;
  this->distributed_event_last_tick                        = boolean__false;
}

void funk2_event_router__destroy(funk2_event_router_t* this) {
}

// this is called from socket rpc layer, so must not access any memory on a remote machine (i.e. scheduler, event_buffer_mutex, and event_buffer are assumed to be local objects)
f2ptr funk2_event_router__know_of_event(funk2_event_router_t* this, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data) {
  status("funk2_event_router__know_of_event: here.");
  boolean_t already_known = funk2_node_handler__node_event_id_is_known(&(__funk2.node_handler), node_id, event_id);
  f2ptr result = nil;
  if (! already_known) {
    f2ptr event = f2event__new(event_cause, f2pointer__new(event_cause, node_id), f2pointer__new(event_cause, event_id), type, data);
    f2ptr event_buffer_mutex = f2scheduler__event_buffer_mutex(__funk2.operating_system.scheduler, event_cause);
    f2mutex__lock(event_buffer_mutex, event_cause);
    f2ptr event_buffer = f2scheduler__event_buffer(__funk2.operating_system.scheduler, event_cause);
    result = f2__circular_buffer__add(event_cause, event_buffer, event);
    f2mutex__unlock(event_buffer_mutex, event_cause);
  }
  return result;
}

