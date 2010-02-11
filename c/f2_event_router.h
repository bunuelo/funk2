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

#ifndef F2__EVENT_ROUTER__H
#define F2__EVENT_ROUTER__H

#include "f2_funk2_node.h"

typedef struct funk2_event_router_s {
  u64       last_checked_event_buffers__nanoseconds_since_1970;
  boolean_t distributed_event_last_tick;
} funk2_event_router_t;

void  funk2_event_router__init(funk2_event_router_t* this, u32 input_buffer__byte_num);
void  funk2_event_router__destroy(funk2_event_router_t* this);
void  funk2_event_router__add_subscriber(funk2_event_router_t* this, f2ptr event_type_list, f2ptr fiber, f2ptr funkable);
f2ptr funk2_event_router__know_of_event(funk2_event_router_t* this, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data);
void  funk2_event_router__handle_input_events(funk2_event_router_t* this);
void  funk2_event_router__handle_subscriber_scheduling(funk2_event_router_t* this);

#endif // F2__EVENT_ROUTER__H

