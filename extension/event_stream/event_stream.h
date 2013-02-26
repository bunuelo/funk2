// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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
//#include "../fiber_trigger/fiber_trigger.h"

// event_stream_event

def_header_ceframe1(event_stream_event, time);

f2ptr raw__event_stream_event__time_value   (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr raw__event_stream_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);

f2ptr raw__event_stream_event__type_create(f2ptr cause, f2ptr this, f2ptr time);
f2ptr raw__event_stream_event__new        (f2ptr cause, f2ptr time);
f2ptr  f2__event_stream_event__new        (f2ptr cause, f2ptr time);

// event_stream

def_header_ceframe3(event_stream, event_time_redblacktree, add_trigger, remove_trigger);

f2ptr raw__event_stream__new                   (f2ptr cause);
f2ptr  f2__event_stream__new                   (f2ptr cause);
f2ptr raw__event_stream__add                   (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr  f2__event_stream__add                   (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr raw__event_stream__remove                (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr  f2__event_stream__remove                (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr raw__event_stream__size                  (f2ptr cause, f2ptr this);
f2ptr  f2__event_stream__size                  (f2ptr cause, f2ptr this);
f2ptr raw__event_stream__first                 (f2ptr cause, f2ptr this);
f2ptr  f2__event_stream__first                 (f2ptr cause, f2ptr this);
f2ptr raw__event_stream__last                  (f2ptr cause, f2ptr this);
f2ptr  f2__event_stream__last                  (f2ptr cause, f2ptr this);
f2ptr raw__event_stream__first_not_before      (f2ptr cause, f2ptr this, f2ptr time);
f2ptr  f2__event_stream__first_not_before      (f2ptr cause, f2ptr this, f2ptr time);
f2ptr raw__event_stream__last_not_after_or_at  (f2ptr cause, f2ptr this, f2ptr time);
f2ptr  f2__event_stream__last_not_after_or_at  (f2ptr cause, f2ptr this, f2ptr time);
f2ptr raw__event_stream__new__iterator         (f2ptr cause, f2ptr this);
f2ptr  f2__event_stream__new__iterator         (f2ptr cause, f2ptr this);
f2ptr raw__event_stream__remove_all            (f2ptr cause, f2ptr this);
f2ptr  f2__event_stream__remove_all            (f2ptr cause, f2ptr this);
f2ptr raw__event_stream__remove_all_before_time(f2ptr cause, f2ptr this, f2ptr time);
f2ptr  f2__event_stream__remove_all_before_time(f2ptr cause, f2ptr this, f2ptr time);


#define event_stream__iteration(cause, this, event, code) {		\
    redblacktree__iteration(cause, f2__event_stream__event_time_redblacktree(cause, this), event, code); \
  }

// event_stream_iterator

def_header_ceframe2(event_stream_iterator, event_stream, index_time);

f2ptr raw__event_stream_iterator__new(f2ptr cause, f2ptr event_stream, f2ptr index_time);
f2ptr  f2__event_stream_iterator__new(f2ptr cause, f2ptr event_stream, f2ptr index_time);

// **

f2ptr f2__event_stream__core_extension__ping(f2ptr cause);
f2ptr f2__event_stream__core_extension__initialize(f2ptr cause);
f2ptr f2__event_stream__core_extension__destroy(f2ptr cause);

#endif // F2__EXTENSION__EVENT_STREAM__H

