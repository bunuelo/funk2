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

#ifndef F2__EXTENSION__SEMANTIC_EVENT_KNOWLEDGE_BASE__H
#define F2__EXTENSION__SEMANTIC_EVENT_KNOWLEDGE_BASE__H

#include "../../c/funk2.h"
#include "../semantic_event/semantic_event.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"
#include "../semantic_event_tree/semantic_event_tree.h"
#include "../semantic_event_transframe/semantic_event_transframe.h"


// semantic_event_knowledge_base

f2ptr     raw__semantic_event_knowledge_base__type_create                (f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm);
f2ptr     raw__semantic_event_knowledge_base__new                        (f2ptr cause, f2ptr name, f2ptr semantic_realm);
f2ptr      f2__semantic_event_knowledge_base__new                        (f2ptr cause, f2ptr name, f2ptr semantic_realm);
boolean_t raw__semantic_event_knowledge_base__is_type                    (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_event_knowledge_base__is_type                    (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_event_knowledge_base__type                       (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_event_knowledge_base__type                       (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_event_knowledge_base__semantic_event_tree        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_event_knowledge_base__semantic_event_tree        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_event_knowledge_base__events_containing_time     (f2ptr cause, f2ptr this, f2ptr semantic_time);
f2ptr      f2__semantic_event_knowledge_base__events_containing_time     (f2ptr cause, f2ptr this, f2ptr semantic_time);
f2ptr     raw__semantic_event_knowledge_base__events_overlapping_range   (f2ptr cause, f2ptr this, f2ptr semantic_left_time, f2ptr semantic_right_time);
f2ptr      f2__semantic_event_knowledge_base__events_overlapping_range   (f2ptr cause, f2ptr this, f2ptr semantic_left_time, f2ptr semantic_right_time);
f2ptr     raw__semantic_event_knowledge_base__events_overlapping_event   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr      f2__semantic_event_knowledge_base__events_overlapping_event   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr     raw__semantic_event_knowledge_base__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time);
f2ptr      f2__semantic_event_knowledge_base__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time);
f2ptr     raw__semantic_event_knowledge_base__events                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_event_knowledge_base__events                     (f2ptr cause, f2ptr this);

f2ptr f2__semantic_event_knowledge_base_type__new(f2ptr cause);


// **

f2ptr f2__semantic_event_knowledge_base__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_event_knowledge_base__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_event_knowledge_base__core_extension__destroy   (f2ptr cause);


#endif // F2__EXTENSION__SEMANTIC_EVENT_KNOWLEDGE_BASE__H

