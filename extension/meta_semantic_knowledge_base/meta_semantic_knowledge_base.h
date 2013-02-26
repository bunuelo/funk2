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

#ifndef F2__EXTENSION__META_SEMANTIC_KNOWLEDGE_BASE__H
#define F2__EXTENSION__META_SEMANTIC_KNOWLEDGE_BASE__H


// meta_semantic_frame

f2ptr     raw__meta_semantic_frame__new    (f2ptr cause, f2ptr realm);
f2ptr      f2__meta_semantic_frame__new    (f2ptr cause, f2ptr realm);
boolean_t raw__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing);
f2ptr      f2__meta_semantic_frame__is_type(f2ptr cause, f2ptr thing);
f2ptr     raw__meta_semantic_frame__type   (f2ptr cause, f2ptr this);
f2ptr      f2__meta_semantic_frame__type   (f2ptr cause, f2ptr this);

f2ptr f2__meta_semantic_frame_type__new(f2ptr cause);


// meta_semantic_object

f2ptr     raw__meta_semantic_object__new    (f2ptr cause, f2ptr realm);
f2ptr      f2__meta_semantic_object__new    (f2ptr cause, f2ptr realm);
boolean_t raw__meta_semantic_object__is_type(f2ptr cause, f2ptr thing);
f2ptr      f2__meta_semantic_object__is_type(f2ptr cause, f2ptr thing);
f2ptr     raw__meta_semantic_object__type   (f2ptr cause, f2ptr this);
f2ptr      f2__meta_semantic_object__type   (f2ptr cause, f2ptr this);

f2ptr f2__meta_semantic_object_type__new(f2ptr cause);


// meta_semantic_knowledge_base

f2ptr     raw__meta_semantic_knowledge_base__type_create                                       (f2ptr cause, f2ptr this, f2ptr name, f2ptr semantic_realm);
f2ptr     raw__meta_semantic_knowledge_base__new                                               (f2ptr cause, f2ptr name, f2ptr semantic_realm);
f2ptr      f2__meta_semantic_knowledge_base__new                                               (f2ptr cause, f2ptr name, f2ptr semantic_realm);
boolean_t raw__meta_semantic_knowledge_base__is_type                                           (f2ptr cause, f2ptr thing);
f2ptr      f2__meta_semantic_knowledge_base__is_type                                           (f2ptr cause, f2ptr thing);
f2ptr     raw__meta_semantic_knowledge_base__type                                              (f2ptr cause, f2ptr this);
f2ptr      f2__meta_semantic_knowledge_base__type                                              (f2ptr cause, f2ptr this);
f2ptr     raw__meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, s64 maximum_size, s64* exact_size);
f2ptr      f2__meta_semantic_knowledge_base__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash, f2ptr maximum_size, f2ptr exact_size_place);

f2ptr f2__meta_semantic_knowledge_base_type__new(f2ptr cause);


// relationship_meta_semantic_object

f2ptr     raw__relationship_meta_semantic_object__new                                               (f2ptr cause, f2ptr realm, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target);
f2ptr      f2__relationship_meta_semantic_object__new                                               (f2ptr cause, f2ptr realm, f2ptr relationship__source, f2ptr relationship__key_type, f2ptr relationship__key, f2ptr relationship__target);
boolean_t raw__relationship_meta_semantic_object__is_type                                           (f2ptr cause, f2ptr thing);
f2ptr      f2__relationship_meta_semantic_object__is_type                                           (f2ptr cause, f2ptr thing);
f2ptr     raw__relationship_meta_semantic_object__type                                              (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__type                                              (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__source                                            (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__source                                            (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__key_type                                          (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__key_type                                          (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__key                                               (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__key                                               (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__target                                            (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__target                                            (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__as__graphviz_color                                (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__as__graphviz_color                                (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__as__graphviz_label                                (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__as__graphviz_label                                (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__as__graphviz_name                                 (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__as__graphviz_name                                 (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__as__graphviz_edge_code                            (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__as__graphviz_edge_code                            (f2ptr cause, f2ptr this);
f2ptr     raw__relationship_meta_semantic_object__as__graphviz_edge_name                            (f2ptr cause, f2ptr this);
f2ptr      f2__relationship_meta_semantic_object__as__graphviz_edge_name                            (f2ptr cause, f2ptr this);
void      raw__relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash);
f2ptr      f2__relationship_meta_semantic_object__add_trans_level_edges_to_graph_with_node_ptypehash(f2ptr cause, f2ptr this, f2ptr graph, f2ptr node_ptypehash);

f2ptr f2__relationship_meta_semantic_object_type__new(f2ptr cause);


// **

f2ptr f2__meta_semantic_knowledge_base__core_extension__ping      (f2ptr cause);
f2ptr f2__meta_semantic_knowledge_base__core_extension__initialize(f2ptr cause);
f2ptr f2__meta_semantic_knowledge_base__core_extension__destroy   (f2ptr cause);


#endif // F2__EXTENSION__META_SEMANTIC_KNOWLEDGE_BASE__H

