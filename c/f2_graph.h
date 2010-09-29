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

#ifndef F2__GRAPH__TYPE__H
#define F2__GRAPH__TYPE__H

// graph_node
typedef struct funk2_object_type__graph_node__slot_s funk2_object_type__graph_node__slot_t;
declare_object_type_1_slot(graph_node, label, );

// graph_edge
typedef struct funk2_object_type__graph_edge__slot_s funk2_object_type__graph_edge__slot_t;
declare_object_type_3_slot(graph_edge, label, left_node, right_node, );

// graph
typedef struct funk2_object_type__graph__slot_s funk2_object_type__graph__slot_t;
declare_object_type_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash, );

// graph_isomorphism
typedef struct funk2_object_type__graph_isomorphism__slot_s funk2_object_type__graph_isomorphism__slot_t;
declare_object_type_2_slot(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash, );

// graph_decomposition_lattice_node
typedef struct funk2_object_type__graph_decomposition_lattice_node__slot_s funk2_object_type__graph_decomposition_lattice_node__slot_t;
declare_object_type_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set, );

// graph_decomposition_lattice
typedef struct funk2_object_type__graph_decomposition_lattice__slot_s funk2_object_type__graph_decomposition_lattice__slot_t;
declare_object_type_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set, );

#endif // F2__GRAPH__TYPE__H

#ifndef F2__GRAPH__H
#define F2__GRAPH__H

#include "f2_primobjects.h"

// graph_node
declare_primobject_1_slot(graph_node, label);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label);

// graph_edge
declare_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node);

// graph
declare_primobject_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);

f2ptr      f2__graph__new                            (f2ptr cause);
f2ptr     raw__graph__add_node                       (f2ptr cause, f2ptr this, f2ptr node);
f2ptr      f2__graph__add_node                       (f2ptr cause, f2ptr this, f2ptr node);
f2ptr     raw__graph__add_new_node                   (f2ptr cause, f2ptr this, f2ptr label);
f2ptr      f2__graph__add_new_node                   (f2ptr cause, f2ptr this, f2ptr label);
f2ptr     raw__graph__add_edge                       (f2ptr cause, f2ptr this, f2ptr edge);
f2ptr      f2__graph__add_edge                       (f2ptr cause, f2ptr this, f2ptr edge);
f2ptr     raw__graph__add_new_edge                   (f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node);
f2ptr      f2__graph__add_new_edge                   (f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node);
u64       raw__graph__node_count                     (f2ptr cause, f2ptr this);
f2ptr      f2__graph__node_count                     (f2ptr cause, f2ptr this);
boolean_t raw__graph__contains_node                  (f2ptr cause, f2ptr this, f2ptr node);
f2ptr      f2__graph__contains_node                  (f2ptr cause, f2ptr this, f2ptr node);
boolean_t raw__graph__contains_edge                  (f2ptr cause, f2ptr this, f2ptr edge);
f2ptr      f2__graph__contains_edge                  (f2ptr cause, f2ptr this, f2ptr edge);
boolean_t raw__graph__contains                       (f2ptr cause, f2ptr this, f2ptr graph);
f2ptr      f2__graph__contains                       (f2ptr cause, f2ptr this, f2ptr graph);
f2ptr     raw__graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this);
f2ptr      f2__graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this);
f2ptr     raw__graph__minus                          (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__graph__minus                          (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__graph__node_isomorphisms              (f2ptr cause, f2ptr this, f2ptr node);
f2ptr      f2__graph__node_isomorphisms              (f2ptr cause, f2ptr this, f2ptr node);

// graph_isomorphism
declare_primobject_2_slot(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);

f2ptr      f2__graph_isomorphism__new              (f2ptr cause);
f2ptr      f2__graph_isomorphism__new              (f2ptr cause);
void      raw__graph_isomorphism__add_mapping      (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr      f2__graph_isomorphism__add_mapping      (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
u64       raw__graph_isomorphism__mapping_count    (f2ptr cause, f2ptr this);
f2ptr      f2__graph_isomorphism__mapping_count    (f2ptr cause, f2ptr this);
boolean_t raw__graph_isomorphism__is_disjoint_with (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__graph_isomorphism__is_disjoint_with (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__graph_isomorphism__union            (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__graph_isomorphism__union            (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node);
f2ptr      f2__graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node);
f2ptr     raw__graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node);
f2ptr      f2__graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node);
f2ptr     raw__graph_isomorphism__as__frame        (f2ptr cause, f2ptr this);
f2ptr      f2__graph_isomorphism__as__frame        (f2ptr cause, f2ptr this);

// graph_decomposition_lattice_node
declare_primobject_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);

f2ptr raw__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph);
f2ptr  f2__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph);

// graph_decomposition_lattice
declare_primobject_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);

f2ptr  f2__graph_decomposition_lattice__new            (f2ptr cause);
f2ptr raw__graph_decomposition_lattice__add_node       (f2ptr cause, f2ptr this, f2ptr node);
f2ptr  f2__graph_decomposition_lattice__add_node       (f2ptr cause, f2ptr this, f2ptr node);
void  raw__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph);
f2ptr  f2__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph);

// **

void f2__graph__initialize();

#endif // F2__GRAPH__H

