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

#ifndef F2__EXTENSION__FORGETFUL_EVENT_STREAM__H
#define F2__EXTENSION__FORGETFUL_EVENT_STREAM__H

#include "../../c/funk2.h"
#include "../event_stream/event_stream.h"

def_header_ceframe1(forgetful_event_stream, important_iterator_set);

f2ptr raw__forgetful_event_stream__new                      (f2ptr cause);
f2ptr  f2__forgetful_event_stream__new                      (f2ptr cause);
f2ptr raw__forgetful_event_stream__add                      (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr  f2__forgetful_event_stream__add                      (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr raw__forgetful_event_stream__remove                   (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr  f2__forgetful_event_stream__remove                   (f2ptr cause, f2ptr this, f2ptr event_stream_event);
void  raw__forgetful_event_stream__add_important_iterator   (f2ptr cause, f2ptr this, f2ptr iterator);
f2ptr  f2__forgetful_event_stream__add_important_iterator   (f2ptr cause, f2ptr this, f2ptr iterator);
void  raw__forgetful_event_stream__remove_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator);
f2ptr  f2__forgetful_event_stream__remove_important_iterator(f2ptr cause, f2ptr this, f2ptr iterator);

f2ptr f2__forgetful_event_stream_type__new_aux(f2ptr cause);

// **

f2ptr f2__forgetful_event_stream__core_extension__ping      (f2ptr cause);
f2ptr f2__forgetful_event_stream__core_extension__initialize(f2ptr cause);
f2ptr f2__forgetful_event_stream__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__FORGETFUL_EVENT_STREAM__H

