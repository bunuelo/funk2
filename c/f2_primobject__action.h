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

#ifndef F2__PRIMOBJECT__ACTION__H
#define F2__PRIMOBJECT__ACTION__H

#include "f2_primobjects.h"

// action

extern f2ptr __action__symbol;
f2ptr f2action__new(f2ptr cause, f2ptr funk, f2ptr success_events_mutex, f2ptr success_events, f2ptr failure_events_mutex, f2ptr failure_events);
#define      f2primobject__is__action(this, cause) raw__eq(cause, f2primobject__type(this, cause), __action__symbol)

defprimobject__static_slot__prototype(action__funk);
#define      f2action__funk(                   this, cause)        primobject__static_slot__accessor(         this, action__funk, cause)
#define      f2action__funk__set(              this, cause, value) primobject__static_slot__set(              this, action__funk, cause, value)
#define      f2action__funk__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__funk, cause)
#define      f2action__funk__trace(            this, cause)        primobject__static_slot__trace(            this, action__funk, cause)
#define      f2action__funk__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__funk, cause)

defprimobject__static_slot__prototype(action__success_events_mutex);
#define      f2action__success_events_mutex(                   this, cause)        primobject__static_slot__accessor(         this, action__success_events_mutex, cause)
#define      f2action__success_events_mutex__set(              this, cause, value) primobject__static_slot__set(              this, action__success_events_mutex, cause, value)
#define      f2action__success_events_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__success_events_mutex, cause)
#define      f2action__success_events_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, action__success_events_mutex, cause)
#define      f2action__success_events_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__success_events_mutex, cause)

defprimobject__static_slot__prototype(action__success_events);
#define      f2action__success_events(                   this, cause)        primobject__static_slot__accessor(         this, action__success_events, cause)
#define      f2action__success_events__set(              this, cause, value) primobject__static_slot__set(              this, action__success_events, cause, value)
#define      f2action__success_events__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__success_events, cause)
#define      f2action__success_events__trace(            this, cause)        primobject__static_slot__trace(            this, action__success_events, cause)
#define      f2action__success_events__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__success_events, cause)

defprimobject__static_slot__prototype(action__failure_events_mutex);
#define      f2action__failure_events_mutex(                   this, cause)        primobject__static_slot__accessor(         this, action__failure_events_mutex, cause)
#define      f2action__failure_events_mutex__set(              this, cause, value) primobject__static_slot__set(              this, action__failure_events_mutex, cause, value)
#define      f2action__failure_events_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__failure_events_mutex, cause)
#define      f2action__failure_events_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, action__failure_events_mutex, cause)
#define      f2action__failure_events_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__failure_events_mutex, cause)

defprimobject__static_slot__prototype(action__failure_events);
#define      f2action__failure_events(                   this, cause)        primobject__static_slot__accessor(         this, action__failure_events, cause)
#define      f2action__failure_events__set(              this, cause, value) primobject__static_slot__set(              this, action__failure_events, cause, value)
#define      f2action__failure_events__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__failure_events, cause)
#define      f2action__failure_events__trace(            this, cause)        primobject__static_slot__trace(            this, action__failure_events, cause)
#define      f2action__failure_events__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__failure_events, cause)

boolean_t raw__action__is_type(f2ptr cause, f2ptr this);
f2ptr f2__action__is_type(f2ptr cause, f2ptr this);



// action_event

extern f2ptr __action_event__symbol;
f2ptr f2action_event__new(f2ptr cause, f2ptr action, f2ptr begin_time, f2ptr end_time);
#define      f2primobject__is__action_event(this, cause) raw__eq(cause, f2primobject__type(this, cause), __action_event__symbol)

defprimobject__static_slot__prototype(action_event__action);
#define      f2action_event__action(                   this, cause)        primobject__static_slot__accessor(         this, action_event__action, cause)
#define      f2action_event__action__set(              this, cause, value) primobject__static_slot__set(              this, action_event__action, cause, value)
#define      f2action_event__action__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action_event__action, cause)
#define      f2action_event__action__trace(            this, cause)        primobject__static_slot__trace(            this, action_event__action, cause)
#define      f2action_event__action__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action_event__action, cause)

defprimobject__static_slot__prototype(action_event__begin_time);
#define      f2action_event__begin_time(                   this, cause)        primobject__static_slot__accessor(         this, action_event__begin_time, cause)
#define      f2action_event__begin_time__set(              this, cause, value) primobject__static_slot__set(              this, action_event__begin_time, cause, value)
#define      f2action_event__begin_time__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action_event__begin_time, cause)
#define      f2action_event__begin_time__trace(            this, cause)        primobject__static_slot__trace(            this, action_event__begin_time, cause)
#define      f2action_event__begin_time__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action_event__begin_time, cause)

defprimobject__static_slot__prototype(action_event__end_time);
#define      f2action_event__end_time(                   this, cause)        primobject__static_slot__accessor(         this, action_event__end_time, cause)
#define      f2action_event__end_time__set(              this, cause, value) primobject__static_slot__set(              this, action_event__end_time, cause, value)
#define      f2action_event__end_time__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action_event__end_time, cause)
#define      f2action_event__end_time__trace(            this, cause)        primobject__static_slot__trace(            this, action_event__end_time, cause)
#define      f2action_event__end_time__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action_event__end_time, cause)

boolean_t raw__action_event__is_type(f2ptr cause, f2ptr this);
f2ptr f2__action_event__is_type(f2ptr cause, f2ptr this);



// **

void f2__primobject__action__reinitialize_globalvars();
void f2__primobject__action__initialize();

#endif // F2__PRIMOBJECT__ACTION__H

