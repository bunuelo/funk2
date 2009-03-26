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

// action primobject definition

defprimobject__static_slot(action__funk,           0);
defprimobject__static_slot(action__success_events, 1);
defprimobject__static_slot(action__failure_events, 2);

f2ptr __action__symbol = -1;

f2ptr f2action__new(f2ptr cause, f2ptr funk, f2ptr success_events, f2ptr failure_events) {
  if (__action__symbol == -1) {__action__symbol = f2symbol__new(cause, strlen("action"), (u8*)"action");}
  f2ptr this = f2__primobject__new(cause, __action__symbol, 3, nil);
  f2action__funk__set(         this, cause, funk);
  f2action__success_events__set(this, cause, success_events);
  f2action__failure_events__set(this, cause, failure_events);
  return this;
}

boolean_t raw__actionp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__action(this, cause));}
f2ptr f2__actionp(f2ptr this, f2ptr cause) {return f2bool__new(raw__actionp(this, cause));}


f2ptr f2__action__new(f2ptr cause, f2ptr funk) {
  return f2action__new(cause, funk, nil, nil);
}
def_pcfunk1(action__new, funk, return f2__action__new(this_cause, funk));

// action_event primobject definition

defprimobject__static_slot(action_event__action,     0);
defprimobject__static_slot(action_event__begin_time, 1);
defprimobject__static_slot(action_event__end_time,   2);

f2ptr __action_event__symbol = -1;

f2ptr f2action_event__new(f2ptr cause, f2ptr action, f2ptr begin_time, f2ptr end_time) {
  if (__action_event__symbol == -1) {__action_event__symbol = f2symbol__new(cause, strlen("action_event"), (u8*)"action_event");}
  f2ptr this = f2__primobject__new(cause, __action_event__symbol, 3, nil);
  f2action_event__action__set(    this, cause, action);
  f2action_event__begin_time__set(this, cause, begin_time);
  f2action_event__end_time__set(  this, cause, end_time);
  return this;
}

boolean_t raw__action_eventp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__action_event(this, cause));}
f2ptr f2__action_eventp(f2ptr this, f2ptr cause) {return f2bool__new(raw__action_eventp(this, cause));}


f2ptr f2__action__begin(f2ptr cause, f2ptr this) {
  if (cause) {
    f2ptr microseconds_since_1970 = f2__system_microseconds_since_1970(cause);
    if (! raw__causep(cause, cause)) {
      return f2larva__new(cause, 1);
    }
    f2ptr action_event = f2action_event__new(cause, this, microseconds_since_1970, nil);
    f2ptr current_events_mutex = f2cause__current_events_mutex(this, cause);
    f2mutex__lock(current_events_mutex, cause);
    f2cause__current_events__set(this, cause, f2cons__new(cause, action_event, f2cause__current_events(this, cause)));
    f2mutex__unlock(current_events_mutex, cause);
  }
  return nil;
}
def_pcfunk1(action__begin, this, return f2__action__begin(this_cause, this));

f2ptr f2__action__end(f2ptr cause, f2ptr this) {
  if (cause) {
    f2ptr microseconds_since_1970 = f2__system_microseconds_since_1970(cause);
    if (! raw__causep(cause, cause)) {
      return f2larva__new(cause, 1);
    }
    f2ptr current_events_mutex = f2cause__current_events_mutex(this, cause);
    f2mutex__lock(current_events_mutex, cause);
    f2ptr current_events_prev = nil;
    f2ptr current_events_iter = f2cause__current_events(this, cause);
    while (current_events_iter) {
      f2ptr action_event = f2cons__car(current_events_iter, cause);
      f2ptr action = f2action_event__action(current_event, cause);
      if (action == this) {
	if (current_events_prev) {
	  f2cons__cdr__set(current_events_prev, cause, f2cons__cdr(current_events_iter, cause));
	} else {
	  f2cause__current_events__set(cause, cause, f2cons__cdr(current_events_iter, cause));
	}
	f2action_event__end_time__set(action_event, cause, microseconds_since_1970);
      }
      current_events_prev = current_events_iter;
      current_events_iter = f2cons__cdr(current_events_iter, cause);
    }
    f2cause__current_events__set(cause, cause, f2cons__new(cause, action_event, f2cause__current_events(this, cause)));
    f2mutex__unlock(current_events_mutex, cause);
  }
  return nil;
}
def_pcfunk1(action__end, this, return f2__action__end(this_cause, this));


// **

void f2__primobject__action__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __action__symbol       = f2symbol__new(cause, strlen("action"),       (u8*)"action");
  __action_event__symbol = f2symbol__new(cause, strlen("action_event"), (u8*)"action_event");
}

void f2__primobject__action__initialize() {
  pause_gc();
  f2__primobject__action__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __action__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __action_event__symbol, nil);
  
  f2__primcfunk__init__1(action__new,   funk);
  f2__primcfunk__init__1(action__begin, this);
  f2__primcfunk__init__1(action__end,   this);
  
  resume_gc();
  try_gc();
}

