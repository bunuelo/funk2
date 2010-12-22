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

#ifndef F2__EXTENSION__EVENT_STREAM__H
#define F2__EXTENSION__EVENT_STREAM__H

#include "../../c/funk2.h"


// event_stream_event

f2ptr raw__event_stream_event__time_value   (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr raw__event_stream_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);

f2ptr     raw__event_stream_event__new       (f2ptr cause, f2ptr time, f2ptr frame);
f2ptr      f2__event_stream_event__new       (f2ptr cause, f2ptr time, f2ptr frame);
boolean_t raw__event_stream_event__is_type   (f2ptr cause, f2ptr thing);
f2ptr      f2__event_stream_event__is_type   (f2ptr cause, f2ptr thing);
f2ptr     raw__event_stream_event__type      (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream_event__type      (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream_event__time      (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream_event__time      (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream_event__time__set (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__event_stream_event__time__set (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__event_stream_event__frame     (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream_event__frame     (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream_event__frame__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__event_stream_event__frame__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__event_stream_event_type__new(f2ptr cause);


// event_stream

f2ptr     raw__event_stream__new                         (f2ptr cause);
f2ptr      f2__event_stream__new                         (f2ptr cause);
boolean_t raw__event_stream__is_type                     (f2ptr cause, f2ptr thing);
f2ptr      f2__event_stream__is_type                     (f2ptr cause, f2ptr thing);
f2ptr     raw__event_stream__type                        (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream__type                        (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream__event_time_redblacktree     (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream__event_time_redblacktree     (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__event_stream_type__new(f2ptr cause);


// **

f2ptr f2__event_stream__core_extension_ping(f2ptr cause);
f2ptr f2__event_stream__core_extension_initialize(f2ptr cause);
f2ptr f2__event_stream__core_extension_destroy(f2ptr cause);

#endif // F2__EXTENSION__EVENT_STREAM__H

