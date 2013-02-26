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

#ifndef F2__GRAPH__TYPE__H
#define F2__GRAPH__TYPE__H

// graph_node
typedef struct funk2_object_type__graph_node__slot_s funk2_object_type__graph_node__slot_t;
declare_object_type_1_slot(graph_node, label,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// graph_edge
typedef struct funk2_object_type__graph_edge__slot_s funk2_object_type__graph_edge__slot_t;
declare_object_type_3_slot(graph_edge, label, left_node, right_node,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// graph
typedef struct funk2_object_type__graph__slot_s funk2_object_type__graph__slot_t;
declare_object_type_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash,
			   f2ptr connected_node_sets__symbol;
			   f2ptr connected_node_sets__funk;
			   f2ptr contains_cycle__symbol;
			   f2ptr contains_cycle__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// graph_isomorphism
typedef struct funk2_object_type__graph_isomorphism__slot_s funk2_object_type__graph_isomorphism__slot_t;
declare_object_type_2_slot(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// graph_decomposition_lattice_node
typedef struct funk2_object_type__graph_decomposition_lattice_node__slot_s funk2_object_type__graph_decomposition_lattice_node__slot_t;
declare_object_type_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// graph_decomposition_lattice
typedef struct funk2_object_type__graph_decomposition_lattice__slot_s funk2_object_type__graph_decomposition_lattice__slot_t;
declare_object_type_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__GRAPH__TYPE__H

#ifndef F2__GRAPH__H
#define F2__GRAPH__H

#include "f2_primobjects.h"

// graph_node
declare_primobject_1_slot(graph_node, label);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label);

f2ptr f2graph_node__primobject_type__new_aux(f2ptr cause);


// graph_edge
declare_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node);

f2ptr f2graph_edge__primobject_type__new_aux(f2ptr cause);


// graph
declare_primobject_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);

f2ptr      f2__graph__new                            (f2ptr cause);
f2ptr     raw__graph__nodes                          (f2ptr cause, f2ptr this);
f2ptr      f2__graph__nodes                          (f2ptr cause, f2ptr this);
f2ptr     raw__graph__edges                          (f2ptr cause, f2ptr this);
f2ptr      f2__graph__edges                          (f2ptr cause, f2ptr this);
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
f2ptr     raw__graph__nodes_with_label               (f2ptr cause, f2ptr this, f2ptr label);
f2ptr      f2__graph__nodes_with_label               (f2ptr cause, f2ptr this, f2ptr label);
boolean_t raw__graph__contains_node_label            (f2ptr cause, f2ptr this, f2ptr label);
f2ptr      f2__graph__contains_node_label            (f2ptr cause, f2ptr this, f2ptr label);
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
f2ptr     raw__graph__edges_with_label_between_nodes (f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node);
f2ptr      f2__graph__edges_with_label_between_nodes (f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node);
f2ptr     raw__graph__edges_between_nodes            (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr      f2__graph__edges_between_nodes            (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr     raw__graph__connected_node_sets            (f2ptr cause, f2ptr this);
f2ptr      f2__graph__connected_node_sets            (f2ptr cause, f2ptr this);
boolean_t raw__graph__contains_cycle                 (f2ptr cause, f2ptr this);
f2ptr      f2__graph__contains_cycle                 (f2ptr cause, f2ptr this);
f2ptr     raw__graph__as__dot_code                   (f2ptr cause, f2ptr this);
f2ptr      f2__graph__as__dot_code                   (f2ptr cause, f2ptr this);
f2ptr     raw__graph__terminal_print_with_frame      (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__graph__terminal_print_with_frame      (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

#define graph__node__out_edge__iteration(cause, this, node, edge, code) { \
    f2ptr graph__node__out_edge__iteration__edges_label_hash_right_node_hash_left_node_hash = f2__graph__edges_label_hash_right_node_hash_left_node_hash(cause, this); \
    f2ptr graph__node__out_edge__iteration__edges_label_hash_right_node_hash                = raw__ptypehash__lookup(cause, graph__node__out_edge__iteration__edges_label_hash_right_node_hash_left_node_hash, node); \
    if (graph__node__out_edge__iteration__edges_label_hash_right_node_hash != nil) { \
      ptypehash__value__iteration(cause, graph__node__out_edge__iteration__edges_label_hash_right_node_hash, graph__node__out_edge__iteration__edges_label_hash, \
				  if (graph__node__out_edge__iteration__edges_label_hash != nil) { \
				    ptypehash__value__iteration(cause, graph__node__out_edge__iteration__edges_label_hash, graph__node__out_edge__iteration__edges, \
								f2ptr graph__node__out_edge__iteration__edges__iter = graph__node__out_edge__iteration__edges; \
								while (graph__node__out_edge__iteration__edges__iter != nil) { \
								  f2ptr edge = f2__cons__car(cause, graph__node__out_edge__iteration__edges__iter); \
								  {	\
								    code; \
								  }	\
								  graph__node__out_edge__iteration__edges__iter = f2__cons__cdr(cause, graph__node__out_edge__iteration__edges__iter); \
								}	\
								);	\
				  }					\
				  );					\
    }									\
  }

#define graph__node__in_edge__iteration(cause, this, node, edge, code) { \
    f2ptr graph__node__in_edge__iteration__edges_label_hash_left_node_hash_right_node_hash = f2__graph__edges_label_hash_left_node_hash_right_node_hash(cause, this); \
    f2ptr graph__node__in_edge__iteration__edges_label_hash_left_node_hash                 = raw__ptypehash__lookup(cause, graph__node__in_edge__iteration__edges_label_hash_left_node_hash_right_node_hash, node); \
    if (graph__node__in_edge__iteration__edges_label_hash_left_node_hash != nil) { \
      ptypehash__value__iteration(cause, graph__node__in_edge__iteration__edges_label_hash_left_node_hash, graph__node__in_edge__iteration__edges_label_hash, \
				  if (graph__node__in_edge__iteration__edges_label_hash != nil) { \
				    ptypehash__value__iteration(cause, graph__node__in_edge__iteration__edges_label_hash, graph__node__in_edge__iteration__edges, \
								f2ptr graph__node__in_edge__iteration__edges__iter = graph__node__in_edge__iteration__edges; \
								while (graph__node__in_edge__iteration__edges__iter != nil) { \
								  f2ptr edge = f2__cons__car(cause, graph__node__in_edge__iteration__edges__iter); \
								  {	\
								    code; \
								  }	\
								  graph__node__in_edge__iteration__edges__iter = f2__cons__cdr(cause, graph__node__in_edge__iteration__edges__iter); \
								}	\
								);	\
				  }					\
				  );					\
    }									\
  }

f2ptr f2graph__primobject_type__new_aux(f2ptr cause);

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

f2ptr f2graph_isomorphism__primobject_type__new_aux(f2ptr cause);

// graph_decomposition_lattice_node
declare_primobject_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);

f2ptr raw__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph);
f2ptr  f2__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph);

f2ptr f2graph_decomposition_lattice_node__primobject_type__new_aux(f2ptr cause);

// graph_decomposition_lattice
declare_primobject_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);

f2ptr  f2__graph_decomposition_lattice__new            (f2ptr cause);
f2ptr raw__graph_decomposition_lattice__add_node       (f2ptr cause, f2ptr this, f2ptr node);
f2ptr  f2__graph_decomposition_lattice__add_node       (f2ptr cause, f2ptr this, f2ptr node);
void  raw__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph);
f2ptr  f2__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph);

f2ptr f2graph_decomposition_lattice__primobject_type__new_aux(f2ptr cause);

// **

void f2__graph__initialize();

#endif // F2__GRAPH__H

