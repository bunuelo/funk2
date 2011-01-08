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

#ifndef F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H
#define F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H


// semantic_realm

f2ptr     raw__semantic_realm__new                               (f2ptr cause);
f2ptr      f2__semantic_realm__new                               (f2ptr cause);
boolean_t raw__semantic_realm__is_type                           (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_realm__is_type                           (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_realm__type                              (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__type                              (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__semantic_hash                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__semantic_hash                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__semantic_hash__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_realm__semantic_hash__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_realm__meta_relationship_hash            (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__meta_relationship_hash            (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__meta_relationship_hash__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_realm__meta_relationship_hash__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_realm__lookup_object_key                 (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__lookup_object_key                 (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__add_object_key                    (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__add_object_key                    (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__object_key                        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__object_key                        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__key_count                         (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__key_count                         (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_realm__terminal_print_with_frame         (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_realm__terminal_print_with_frame         (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_realm_type__new(f2ptr cause);


// semantic_frame_event

f2ptr     raw__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame_event__new(f2ptr cause, f2ptr time, f2ptr event_type, f2ptr key_type, f2ptr key, f2ptr value);
boolean_t raw__semantic_frame_event__is_type(f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame_event__is_type(f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame_event__type(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__type(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__time(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__time(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__time__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__time__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__event_type(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__event_type(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__event_type__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__key_type(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__key_type(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__key_type__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__key(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__key(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__key__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__value(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__value(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__value__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_frame_event_type__new(f2ptr cause);


// semantic_frame_event_redblacktree

f2ptr     raw__semantic_frame_event_redblacktree__new(f2ptr cause);
f2ptr      f2__semantic_frame_event_redblacktree__new(f2ptr cause);
boolean_t raw__semantic_frame_event_redblacktree__is_type(f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame_event_redblacktree__is_type(f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame_event_redblacktree__type(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event_redblacktree__type(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event_redblacktree__redblacktree(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event_redblacktree__redblacktree(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event_redblacktree__redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_frame_event_redblacktree_type__new(f2ptr cause);


// semantic_frame

f2ptr     raw__semantic_frame_event__time_value                       (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr     raw__semantic_frame_event__compare_value                    (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr     raw__semantic_frame__new                                    (f2ptr cause, f2ptr semantic_realm);
f2ptr      f2__semantic_frame__new                                    (f2ptr cause, f2ptr semantic_realm);
boolean_t raw__semantic_frame__is_type                                (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame__is_type                                (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame__type                                   (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__type                                   (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__semantic_realm                         (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__semantic_realm                         (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__semantic_realm__set                    (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__semantic_realm__set                    (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_add                              (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_add                              (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_add__set                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_add__set                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_remove                           (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_remove                           (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_remove__set                      (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_remove__set                      (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_event_redblacktree               (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_event_redblacktree               (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_event_redblacktree__set          (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_event_redblacktree__set          (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__frame                                  (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__frame                                  (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__frame__set                             (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__frame__set                             (f2ptr cause, f2ptr this, f2ptr value);
void      raw__semantic_frame__initialize_tracing                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__add                                    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__add                                    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__remove                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__remove                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__lookup                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__lookup_single_value                    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup_single_value                    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__remove_all                             (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__remove_all                             (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__replace_all                            (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__replace_all                            (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__add_recursively_to_graph_with_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash);
f2ptr     raw__semantic_frame__as__graphviz_label                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__as__graphviz_label                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_type__new                               (f2ptr cause);

#define semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value, code) { \
    f2ptr semantic_frame__iteration__frame = raw__semantic_frame__frame(cause, this); \
    frame__iteration(cause, semantic_frame__iteration__frame, key_type_name, key_name, semantic_frame__iteration__slot_value_set, \
		     set__iteration(cause, semantic_frame__iteration__slot_value_set, slot_value, \
				    code));				\
  }



// semantic_knowledge_base

f2ptr raw__semantic_knowledge_base_event__time_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr raw__semantic_knowledge_base_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);

f2ptr     raw__semantic_knowledge_base__new                                   (f2ptr cause, f2ptr name, f2ptr semantic_realm, f2ptr semantic_frame_set, f2ptr trace_event_stream, f2ptr trace_add_semantic_frame, f2ptr trace_remove_semantic_frame);
f2ptr      f2__semantic_knowledge_base__new                                   (f2ptr cause, f2ptr name, f2ptr semantic_realm);
boolean_t raw__semantic_knowledge_base__is_type                               (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_knowledge_base__is_type                               (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_knowledge_base__type                                  (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__type                                  (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__name                                  (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__name                                  (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__name__set                             (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__name__set                             (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__semantic_realm                        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_realm                        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_realm__set                   (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__semantic_realm__set                   (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__semantic_frames                       (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_frames                       (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_frames__set                  (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__semantic_frames__set                  (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__as__graph                             (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__as__graph                             (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__add_semantic_frame                    (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr      f2__semantic_knowledge_base__add_semantic_frame                    (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr     raw__semantic_knowledge_base__add_trace_event                       (f2ptr cause, f2ptr this, f2ptr event);
f2ptr      f2__semantic_knowledge_base__add_trace_event                       (f2ptr cause, f2ptr this, f2ptr event);
f2ptr     raw__semantic_knowledge_base__know_of_semantic_frame_value_addition (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_of_semantic_frame_value_addition (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_knowledge_base__know_of_semantic_frame_value_removal  (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_knowledge_base__know_of_semantic_frame_value_removal  (f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
boolean_t raw__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size);
f2ptr      f2__semantic_knowledge_base__recursively_add_semantic_frames_to_set(f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place);
boolean_t raw__semantic_knowledge_base__add_to_graph_with_node_ptypehash      (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64 *exact_size);
f2ptr      f2__semantic_knowledge_base__add_to_graph_with_node_ptypehash      (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place);

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

f2ptr f2__semantic_knowledge_base__core_extension_ping(f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension_initialize(f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause);




#endif // F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H

