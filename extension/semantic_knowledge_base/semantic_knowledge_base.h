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

#ifndef F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H
#define F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H

#include "../../c/funk2.h"
#include "../semantic_relationship_key/semantic_relationship_key.h"
#include "../semantic_frame/semantic_frame.h"
#include "../semantic_realm/semantic_realm.h"
#include "../equals_hash/equals_hash.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"
#include "../forgetful_event_stream/forgetful_event_stream.h"
#include "../lick/lick.h"

// semantic_knowledge_base

f2ptr raw__semantic_knowledge_base_event__time_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr raw__semantic_knowledge_base_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);

f2ptr     raw__semantic_knowledge_base__type_create_with_details                                    (f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame);
f2ptr     raw__semantic_knowledge_base__type_create                                                 (f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm);
f2ptr     raw__semantic_knowledge_base__new_with_details                                            (f2ptr cause, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame);
f2ptr     raw__semantic_knowledge_base__new                                                         (f2ptr cause, f2ptr name, f2ptr semantic_realm);
f2ptr      f2__semantic_knowledge_base__new                                                         (f2ptr cause, f2ptr name, f2ptr semantic_realm);
boolean_t raw__semantic_knowledge_base__is_type                                                     (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_knowledge_base__is_type                                                     (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_knowledge_base__type                                                        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__type                                                        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__name                                                        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__name                                                        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__name__set                                                   (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__name__set                                                   (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__semantic_realm                                              (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_realm                                              (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_realm__set                                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__semantic_realm__set                                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__semantic_frames                                             (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_frames                                             (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_frames__set                                        (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__semantic_frames__set                                        (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__as__graph                                                   (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__as__graph                                                   (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__add_semantic_frame                                          (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr      f2__semantic_knowledge_base__add_semantic_frame                                          (f2ptr cause, f2ptr this, f2ptr semantic_frame);
void      raw__semantic_knowledge_base__add_trace_callback_funk                                     (f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk);
f2ptr      f2__semantic_knowledge_base__add_trace_callback_funk                                     (f2ptr cause, f2ptr this, f2ptr trace_callback_name, f2ptr trace_callback_funk);
f2ptr     raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before   (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr      f2__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__before   (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr     raw__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after    (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr      f2__semantic_knowledge_base__add_trace_callback_funk__add_semantic_frame_value__after    (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr     raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk);
f2ptr      f2__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__before(f2ptr cause, f2ptr this, f2ptr funk);
f2ptr     raw__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr      f2__semantic_knowledge_base__add_trace_callback_funk__remove_semantic_frame_value__after (f2ptr cause, f2ptr this, f2ptr funk);
f2ptr     raw__semantic_knowledge_base__add_trace_event                                             (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__semantic_knowledge_base__add_trace_event                                             (f2ptr cause, f2ptr this, f2ptr event);
f2ptr     raw__semantic_knowledge_base__remove_semantic_frame                                       (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr      f2__semantic_knowledge_base__remove_semantic_frame                                       (f2ptr cause, f2ptr this, f2ptr semantic_frame);
boolean_t raw__semantic_knowledge_base__contains_semantic_frame                                     (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr      f2__semantic_knowledge_base__contains_semantic_frame                                     (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr     raw__semantic_knowledge_base__remove_all                                                  (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__remove_all                                                  (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__know_before_semantic_frame_value_addition                   (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_before_semantic_frame_value_addition                   (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_knowledge_base__know_after_semantic_frame_value_addition                    (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_after_semantic_frame_value_addition                    (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_knowledge_base__know_before_semantic_frame_value_removal                    (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_before_semantic_frame_value_removal                    (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_knowledge_base__know_after_semantic_frame_value_removal                     (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_after_semantic_frame_value_removal                     (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
boolean_t raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set                      (f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size);
f2ptr      f2__semantic_knowledge_base__recursively_add_semantic_frames_to_set                      (f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place);
boolean_t raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash                            (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64 *exact_size);
f2ptr      f2__semantic_knowledge_base__add_to_graph_with_node_ptypehash                            (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place);
f2ptr     raw__semantic_knowledge_base__semantic_frames                                             (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_frames                                             (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__copy_differences_to                                         (f2ptr cause, f2ptr this, f2ptr target);
f2ptr      f2__semantic_knowledge_base__copy_differences_to                                         (f2ptr cause, f2ptr this, f2ptr target);

f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause);


// noun_semantic_frame

f2ptr     raw__noun_semantic_frame__new            (f2ptr cause, f2ptr realm);
f2ptr      f2__noun_semantic_frame__new            (f2ptr cause, f2ptr realm);
boolean_t raw__noun_semantic_frame__is_type        (f2ptr cause, f2ptr thing);
f2ptr      f2__noun_semantic_frame__is_type        (f2ptr cause, f2ptr thing);
f2ptr     raw__noun_semantic_frame__type           (f2ptr cause, f2ptr this);
f2ptr      f2__noun_semantic_frame__type           (f2ptr cause, f2ptr this);
f2ptr     raw__noun_semantic_frame__add_noun       (f2ptr cause, f2ptr this, f2ptr noun);
f2ptr      f2__noun_semantic_frame__add_noun       (f2ptr cause, f2ptr this, f2ptr noun);
f2ptr     raw__noun_semantic_frame__add_classifier (f2ptr cause, f2ptr this, f2ptr classifier);
f2ptr      f2__noun_semantic_frame__add_classifier (f2ptr cause, f2ptr this, f2ptr classifier);
f2ptr     raw__noun_semantic_frame__add_adjective  (f2ptr cause, f2ptr this, f2ptr adjective);
f2ptr      f2__noun_semantic_frame__add_adjective  (f2ptr cause, f2ptr this, f2ptr adjective);
f2ptr     raw__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object);
f2ptr      f2__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object);

f2ptr f2__noun_semantic_frame_type__new(f2ptr cause);


// visual_object_semantic_frame

f2ptr     raw__visual_object_semantic_frame__new                   (f2ptr cause, f2ptr realm);
f2ptr      f2__visual_object_semantic_frame__new                   (f2ptr cause, f2ptr realm);
boolean_t raw__visual_object_semantic_frame__is_type               (f2ptr cause, f2ptr thing);
f2ptr      f2__visual_object_semantic_frame__is_type               (f2ptr cause, f2ptr thing);
f2ptr     raw__visual_object_semantic_frame__type                  (f2ptr cause, f2ptr this);
f2ptr      f2__visual_object_semantic_frame__type                  (f2ptr cause, f2ptr this);
f2ptr     raw__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name);
f2ptr      f2__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name);

f2ptr f2__visual_object_semantic_frame_type__new(f2ptr cause);

// **

f2ptr f2__semantic_knowledge_base__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension__destroy   (f2ptr cause);




#endif // F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H

