// 
// Copyright (c) 2007-2009 Bo Morgan.
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
  this->last_checked_event_buffers__microseconds_since_1970 = 0;
  this->distributed_event_last_tick                         = false;
}

void funk2_event_router__destroy(funk2_event_router_t* this) {
}

// this is called from socket rpc layer, so must not access any memory on a remote machine (i.e. scheduler, event_buffer_mutex, and event_buffer are assumed to be local objects)
f2ptr funk2_event_router__know_of_event(funk2_event_router_t* this, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data) {
  status("funk2_event_router__know_of_event: here.");
  bool already_known = funk2_node_handler__node_event_id_is_known(&(__funk2.node_handler), node_id, event_id);
  f2ptr result = nil;
  if (! already_known) {
    f2ptr event = f2event__new(event_cause, f2pointer__new(event_cause, node_id), f2pointer__new(event_cause, event_id), type, data);
    f2ptr event_buffer_mutex = f2scheduler__event_buffer_mutex(__funk2.operating_system.scheduler, event_cause);
    f2mutex__lock(event_buffer_mutex, event_cause);
    f2ptr event_buffer = f2scheduler__event_buffer(__funk2.operating_system.scheduler, event_cause);
    result = f2__circular_buffer__add(event_cause, event_buffer, event);
    f2mutex__unlock(event_buffer_mutex, event_cause);
  }
  if (result != __funk2.primobject__circular_buffer.full__symbol) {
    status("funk2_event_router__know_of_event warning: scheduler event buffer is full, so dropping event.");
  }
  return result;
}

/*
f2ptr f2__scheduler__handle_input_events(f2ptr cause, f2ptr scheduler) {
  f2ptr event_buffer_mutex = f2scheduler__event_buffer_mutex(scheduler, cause);
  if (f2mutex__trylock(event_buffer_mutex, cause) != 0) { // unsuccessful lock
    return nil;
  }
  f2ptr event_buffer = f2scheduler__event_buffer(scheduler, cause);
  f2ptr event = f2__circular_buffer__remove(cause, event_buffer);
  f2mutex__unlock(event_buffer_mutex, cause);
  if (event != __funk2.primobject__circular_buffer.empty__symbol) {
    status("f2__scheduler__handle_input_events found event.");
    f2ptr      event_cause = f2event__cause(event, cause);
    node_id_t  node_id     = f2event__node_id(event, cause);
    event_id_t event_id    = f2event__event_id(event, cause);
    f2ptr      type        = f2event__type(event, cause);
    funk2_node_handler__know_of_node_event(&(__funk2.node_handler), event_cause, node_id, event_id, type, data);
    f2ptr subscriber_iter = f2scheduler__event_subscribers(__global__scheduler, event_cause);
    while (subscriber_iter) {
      f2ptr event_subscriber = f2cons__car(subscriber_iter, event_cause);
      f2ptr event_type_iter  = f2event_subscriber__event_types(event_subscriber, event_cause);
      while (event_type_iter) {
	f2ptr subscriber_event_type = f2cons__car(event_type_iter, event_cause);
	if (raw__symbol__equals(event_cause, subscriber_event_type, type)) {
	  f2ptr event_buffer_mutex = f2event_subscriber__event_buffer_mutex(event_subscriber, event_cause);
	  f2mutex__lock(event_buffer_mutex, event_cause);
	  {
	    f2ptr event_buffer = f2event_subscriber__event_buffer(event_subscriber, event_cause);
	    f2ptr result = f2__circular_buffer__add(event_cause, event_buffer, f2event__new(event_cause, type, data));
	    if (raw__symbol__equals(event_cause, result, __funk2.primobject__circular_buffer.full__symbol)) {
	      status("funk2_event_router__handle_input_events warning: circular_buffer full.");
	    }
	  }
	  f2mutex__unlock(event_buffer_mutex, event_cause);
	}
	event_type_iter = f2cons__cdr(event_type_iter, event_cause);
      }
      subscriber_iter = f2cons__cdr(subscriber_iter, event_cause);
    }
  }
  return __funk2.globalenv.true__symbol;
}

// this should be called from funk2 and not from "rpc socket layer"
void funk2_event_router__handle_subscriber_scheduling(f2ptr cause, funk2_event_router_t* this) {
  u64 microseconds_since_1970 = raw__system_microseconds_since_1970();
  if (this->distributed_event_last_tick || (microseconds_since_1970 - this->last_checked_event_buffers__microseconds_since_1970) >= 100000) {
    this->distributed_event_last_tick = false;
    f2ptr cause = initial_cause();
    f2ptr scheduler = __global__scheduler;
    f2ptr event_subscriber_iter = f2scheduler__event_subscribers(scheduler, cause);
    while (event_subscriber_iter) {
      f2ptr event_subscriber = f2cons__car(event_subscriber_iter, cause);
      
      f2ptr event_buffer_mutex = f2event_subscriber__event_buffer_mutex(event_subscriber, cause);
      if (f2mutex__trylock(event_buffer_mutex, cause) == 0) { // successful lock
	
	f2ptr event_buffer = f2event_subscriber__event_buffer(event_subscriber, cause);
	if (! raw__circular_buffer__is_empty(cause, event_buffer)) {
	  f2ptr thread               = f2event_subscriber__thread(event_subscriber, cause);
	  f2ptr thread_execute_mutex = f2thread__execute_mutex(thread, cause);
	  if (f2mutex__trylock(thread_execute_mutex, cause) == 0) { // successful lock
	    if (f2thread__is_complete(thread, cause)) {
	      f2ptr event    = f2__circular_buffer__remove(cause, event_buffer);
	      f2ptr funkable = f2event_subscriber__funkable(event_subscriber, cause);
	      f2ptr args     = f2cons__new(cause, event, nil);
	      f2thread__funk(thread, cause, funkable, args);
	      f2__global_scheduler__add_thread_parallel(cause, thread);
	      this->distributed_event_last_tick = true;
	    }
	    f2mutex__unlock(thread_execute_mutex, cause);
	  }
	}
	f2mutex__unlock(event_buffer_mutex, cause);
      }
      event_subscriber_iter = f2cons__cdr(event_subscriber_iter, cause);
    }
    this->last_checked_event_buffers__microseconds_since_1970 = microseconds_since_1970;
  }
}
*/


