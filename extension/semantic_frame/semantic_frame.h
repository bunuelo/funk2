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

#ifndef F2__EXTENSION__SEMANTIC_FRAME__H
#define F2__EXTENSION__SEMANTIC_FRAME__H

#include "../../c/funk2.h"
#include "../semantic_relationship_key/semantic_relationship_key.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"
#include "../semantic_frame/semantic_frame.h"
#include "../semantic_realm/semantic_realm.h"
#include "../equals_hash/equals_hash.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"
#include "../forgetful_event_stream/forgetful_event_stream.h"
#include "../lick/lick.h"



// semantic_frame_event

f2ptr     raw__semantic_frame_event__new                      (f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame_event__new                      (f2ptr cause, f2ptr time, f2ptr event_type, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
boolean_t raw__semantic_frame_event__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame_event__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame_event__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__time                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__time                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__time__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__time__set                (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__event_type               (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__event_type               (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__event_type__set          (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__event_type__set          (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__key_type                 (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__key_type                 (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__key_type__set            (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__key_type__set            (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__key                      (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__key                      (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__key__set                 (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__key__set                 (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__value                    (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event__value                    (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event__value__set               (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event__value__set               (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_frame_event__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_frame_event_type__new(f2ptr cause);


// semantic_frame_event_redblacktree

f2ptr     raw__semantic_frame_event_redblacktree__new                      (f2ptr cause);
f2ptr      f2__semantic_frame_event_redblacktree__new                      (f2ptr cause);
boolean_t raw__semantic_frame_event_redblacktree__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame_event_redblacktree__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame_event_redblacktree__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event_redblacktree__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event_redblacktree__redblacktree             (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_event_redblacktree__redblacktree             (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_event_redblacktree__redblacktree__set        (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_event_redblacktree__redblacktree__set        (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_frame_event_redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_frame_event_redblacktree_type__new(f2ptr cause);


// semantic_frame

f2ptr     raw__semantic_frame_event__time_value                            (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr     raw__semantic_frame_event__compare_value                         (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr     raw__semantic_frame__type_create                                 (f2ptr cause, f2ptr this, f2ptr semantic_realm);
f2ptr     raw__semantic_frame__new                                         (f2ptr cause, f2ptr semantic_realm);
f2ptr      f2__semantic_frame__new                                         (f2ptr cause, f2ptr semantic_realm);
boolean_t raw__semantic_frame__is_type                                     (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame__is_type                                     (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame__type                                        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__type                                        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__semantic_realm                              (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__semantic_realm                              (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__semantic_realm__set                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__semantic_realm__set                         (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_add                                   (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_add                                   (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_add__set                              (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_add__set                              (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_remove                                (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_remove                                (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_remove__set                           (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_remove__set                           (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__trace_event_redblacktree                    (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__trace_event_redblacktree                    (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__trace_event_redblacktree__set               (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__trace_event_redblacktree__set               (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__frame                                       (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__frame                                       (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__frame__set                                  (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__frame__set                                  (f2ptr cause, f2ptr this, f2ptr value);
void      raw__semantic_frame__initialize_tracing                          (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__add                                         (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__add                                         (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__add_event__new                              (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__remove                                      (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__remove                                      (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__remove_event__new                           (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__lookup_set                                  (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup_set                                  (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__lookup_reverse_set                          (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup_reverse_set                          (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__lookup_type_var_value                       (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup_type_var_value                       (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__replace_type_var_value                      (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__replace_type_var_value                      (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__remove_all                                  (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__remove_all                                  (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr     raw__semantic_frame__replace_all                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__replace_all                                 (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
void      raw__semantic_frame__know_of_addition_to_semantic_knowledge_base (f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
f2ptr      f2__semantic_frame__know_of_addition_to_semantic_knowledge_base (f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
void      raw__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
f2ptr      f2__semantic_frame__know_of_removal_from_semantic_knowledge_base(f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
boolean_t raw__semantic_frame__recursively_add_to_set                      (f2ptr cause, f2ptr this, f2ptr set, s64 maximum_size, s64* exact_size);
f2ptr      f2__semantic_frame__recursively_add_to_set                      (f2ptr cause, f2ptr this, f2ptr set, f2ptr maximum_size, f2ptr exact_size_place);
void      raw__semantic_frame__add_to_graph_with_node_ptypehash            (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash);
f2ptr      f2__semantic_frame__add_to_graph_with_node_ptypehash            (f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash);
f2ptr     raw__semantic_frame__as__graphviz_label                          (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__as__graphviz_label                          (f2ptr cause, f2ptr this);
boolean_t raw__semantic_frame__is_semantic_type                            (f2ptr cause, f2ptr this, f2ptr type_name);
f2ptr      f2__semantic_frame__is_semantic_type                            (f2ptr cause, f2ptr this, f2ptr type_name);
f2ptr     raw__semantic_frame__terminal_print_with_frame                   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_frame__terminal_print_with_frame                   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_frame_type__new(f2ptr cause);

#define semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value, code) { \
    f2ptr semantic_frame__iteration__frame = raw__semantic_frame__frame(cause, this); \
    frame__iteration(cause, semantic_frame__iteration__frame, key_type_name, key_name, semantic_frame__iteration__slot_value_set, \
		     set__iteration(cause, semantic_frame__iteration__slot_value_set, slot_value, \
				    code));				\
  }

#define semantic_frame__value__iteration(cause, this, slot_value, code) { \
    f2ptr semantic_frame__iteration__frame = raw__semantic_frame__frame(cause, this); \
    frame__value__iteration(cause, semantic_frame__iteration__frame, semantic_frame__iteration__slot_value_set, \
			    set__iteration(cause, semantic_frame__iteration__slot_value_set, slot_value, \
					   code));			\
  }


f2ptr f2__object__semantic__lookup_set       (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__semantic__lookup_set__apply(f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__semantic__add              (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__semantic__add__apply       (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__semantic__remove           (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);
f2ptr f2__object__semantic__remove__apply    (f2ptr cause, f2ptr this, f2ptr slot, f2ptr args);



// **

f2ptr f2__semantic_frame__core_extension__ping        (f2ptr cause);
f2ptr f2__semantic_frame__core_extension__initialize  (f2ptr cause);
f2ptr f2__semantic_frame__core_extension__define_types(f2ptr cause);
f2ptr f2__semantic_frame__core_extension__destroy     (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_FRAME__H

