// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__EXTENSION__SEMANTIC_EVENT_TREE__H
#define F2__EXTENSION__SEMANTIC_EVENT_TREE__H

#include "../../c/funk2.h"
#include "../interval_tree/interval_tree.h"
#include "../semantic_event/semantic_event.h"

def_header_ceframe1(semantic_event_tree, interval_tree);

f2ptr raw__semantic_event_tree__new                        (f2ptr cause);
f2ptr  f2__semantic_event_tree__new                        (f2ptr cause);
f2ptr raw__semantic_event_tree__insert                     (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr  f2__semantic_event_tree__insert                     (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr raw__semantic_event_tree__remove                     (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr  f2__semantic_event_tree__remove                     (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr raw__semantic_event_tree__contains                   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr  f2__semantic_event_tree__contains                   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr raw__semantic_event_tree__events_containing_time     (f2ptr cause, f2ptr this, f2ptr time);
f2ptr  f2__semantic_event_tree__events_containing_time     (f2ptr cause, f2ptr this, f2ptr time);
f2ptr raw__semantic_event_tree__events_overlapping_range   (f2ptr cause, f2ptr this, f2ptr left_semantic_time, f2ptr right_semantic_time);
f2ptr  f2__semantic_event_tree__events_overlapping_range   (f2ptr cause, f2ptr this, f2ptr left_semantic_time, f2ptr right_semantic_time);
f2ptr raw__semantic_event_tree__events_overlapping_event   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr  f2__semantic_event_tree__events_overlapping_event   (f2ptr cause, f2ptr this, f2ptr semantic_event);
f2ptr raw__semantic_event_tree__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time);
f2ptr  f2__semantic_event_tree__most_recent_filtered_events(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr semantic_time);
f2ptr raw__semantic_event_tree__events                     (f2ptr cause, f2ptr this);
f2ptr  f2__semantic_event_tree__events                     (f2ptr cause, f2ptr this);

f2ptr f2__semantic_event_tree_type__new_aux(f2ptr cause);

// **

f2ptr f2__semantic_event_tree__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_event_tree__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_event_tree__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_EVENT_TREE__H

