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
declare_object_type_5_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash, edges_edge_hash_left_node_hash, edges_edge_hash_right_node_hash, );

#define graph_node__in_edge__iteration(cause, this, edge, code) { \
   f2ptr this__edges_left_node_hash_edge_hash = f2__graph_node__edges_left_node_hash_edge_hash(cause, this); \
   ptypehash__value__iteration(cause, this__edges_left_node_hash_edge_hash, this__edges_left_node_hash, \
	                       ptypehash__value__iteration(cause, this__edges_left_node_hash, this__edges, \
	                                                   f2ptr iter = this__edges; \
			                                   while (iter) { \
			                                     f2ptr edge = f2__cons__car(cause, iter); \
			                                     { \
			                                       code; \
			                                     } \
			                                     iter = f2__cons__cdr(cause, iter); \
			                                   } \
			                                   ); \
                               ); \
}

#define graph_node__out_edge__iteration(cause, this, edge, code) { \
   f2ptr this__edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, this); \
   ptypehash__value__iteration(cause, this__edges_right_node_hash_edge_hash, this__edges_right_node_hash, \
	                       ptypehash__value__iteration(cause, this__edges_right_node_hash, this__edges, \
	                                                   f2ptr iter = this__edges; \
			                                   while (iter) { \
			                                     f2ptr edge = f2__cons__car(cause, iter); \
			                                     { \
			                                       code; \
			                                     } \
			                                     iter = f2__cons__cdr(cause, iter); \
			                                   } \
			                                   ); \
                               ); \
}

// graph_edge
typedef struct funk2_object_type__graph_edge__slot_s funk2_object_type__graph_edge__slot_t;
declare_object_type_3_slot(graph_edge, label, left_node, right_node, );

// graph_edge_type
typedef struct funk2_object_type__graph_edge_type__slot_s funk2_object_type__graph_edge_type__slot_t;
declare_object_type_3_slot(graph_edge_type, label, left_node_hash, right_node_hash, );

#define graph_edge_type__edge__iteration(cause, this, edge, code) { \
  f2ptr this__label    = f2__graph_edge_type__label(cause, this); \
  f2ptr left_node_hash = f2__graph_edge_type__left_node_hash(cause, this); \
  ptypehash__value__iteration(cause, left_node_hash, left_node, \
                              f2ptr left_node__edges_right_node_hash_edge_hash = f2__graph_node__edges_right_node_hash_edge_hash(cause, left_node); \
                              f2ptr left_node__edges_right_node_hash           = f2__ptypehash__lookup(cause, left_node__edges_right_node_hash_edge_hash, this__label); \
                              ptypehash__value__iteration(cause, left_node__edges_right_node_hash, edges, \
                                                          f2ptr iter = edges; \
                                                          while(iter) { \
  							    f2ptr edge = f2__cons__car(cause, iter); \
							    { \
                                                              code; \
                                                            } \
    							    iter = f2__cons__cdr(cause, iter); \
                                                          } \
							  )); \
}

// graph
typedef struct funk2_object_type__graph__slot_s funk2_object_type__graph__slot_t;
declare_object_type_4_slot(graph, variable_name_hash, root_node, node_label_hash, edge_type_label_hash,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   f2ptr part_not_contained_by__symbol;
			   f2ptr part_not_contained_by__funk;
			   f2ptr as__frame__symbol;
			   f2ptr as__frame__funk;
			   );

#define graph__node_count(cause, this) f2integer__i(f2__ptypehash__key_count(cause, f2__graph__node_label_hash(cause, this)), cause)

#define graph__node__iteration(cause, this, node, code) {	   \
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this); \
  ptypehash__value__iteration(cause, node_label_hash, node, code); \
}

#define graph__edge__iteration(cause, this, edge, code) { \
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this); \
  ptypehash__value__iteration(cause, node_label_hash, right_node,	\
                              f2ptr right_node__edges_left_node_hash_edge_hash = f2__graph_node__edges_left_node_hash_edge_hash(cause, right_node); \
                              ptypehash__value__iteration(cause, right_node__edges_left_node_hash_edge_hash, right_node__edges_left_node_hash, \
						          ptypehash__value__iteration(cause, right_node__edges_left_node_hash, right_node__edges, \
									              f2ptr iter = right_node__edges; \
									              while (iter) { \
										        f2ptr edge = f2__cons__car(cause, iter); \
										        { \
											  code; \
											} \
											iter = f2__cons__cdr(cause, iter); \
										      } \
										      ); \
                                                          ); \
			      ); \
}


// pattern_graph
typedef struct funk2_object_type__pattern_graph__slot_s funk2_object_type__pattern_graph__slot_t;
declare_object_type_2_slot(pattern_graph, variable_label_hash, graph, );

// graph_variable
typedef struct funk2_object_type__graph_variable__slot_s funk2_object_type__graph_variable__slot_t;
declare_object_type_1_slot(graph_variable, name,
			   f2ptr eq__symbol;
			   f2ptr eq__funk;
			   f2ptr eq_hash_value__symbol;
			   f2ptr eq_hash_value__funk;
			   );

// graph_map
typedef struct funk2_object_type__graph_map__slot_s funk2_object_type__graph_map__slot_t;
declare_object_type_1_slot(graph_map, node_indices, );

// trans
typedef struct funk2_object_type__trans__slot_s funk2_object_type__trans__slot_t;
declare_object_type_2_slot(trans, remove, add,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   f2ptr part_not_contained_by__symbol;
			   f2ptr part_not_contained_by__funk;
			   );

typedef struct funk2_graph_s {
  f2ptr common_variable_subgraph_possibility__compare__symbol;
  f2ptr common_variable_subgraph_possibility__compare__funk;
} funk2_graph_t;

#endif // F2__GRAPH__TYPE__H

#ifndef F2__GRAPH__H
#define F2__GRAPH__H

#include "f2_primobjects.h"

// graph_node
declare_primobject_5_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash, edges_edge_hash_left_node_hash, edges_edge_hash_right_node_hash);

// graph_edge
declare_primobject_3_slot(graph_edge, label, left_node, right_node);

// graph_edge_type
declare_primobject_3_slot(graph_edge_type, label, left_node_hash, right_node_hash);

// graph
declare_primobject_4_slot(graph, variable_name_hash, root_node, node_label_hash, edge_type_label_hash);

f2ptr      f2__graph__new(f2ptr cause);
f2ptr      f2__graph__equals_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__graph__remove_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label);
f2ptr      f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_label_node, f2ptr right_node_label);
f2ptr     raw__graph__nodes(f2ptr cause, f2ptr this);
f2ptr      f2__graph__nodes(f2ptr cause, f2ptr this);
boolean_t raw__graph__has_nodes(f2ptr cause, f2ptr this);
f2ptr      f2__graph__has_nodes(f2ptr cause, f2ptr this);
f2ptr     raw__graph__edges(f2ptr cause, f2ptr this);
f2ptr      f2__graph__edges(f2ptr cause, f2ptr this);
f2ptr     raw__graph__variables(f2ptr cause, f2ptr this);
f2ptr      f2__graph__variables(f2ptr cause, f2ptr this);

boolean_t raw__graph__is_rooted(f2ptr cause, f2ptr this);
void      raw__graph__make_rooted(f2ptr cause, f2ptr this, f2ptr root_node_label);
f2ptr      f2__graph__make_rooted(f2ptr cause, f2ptr this, f2ptr root_node_label);
void      raw__graph__make_rootless(f2ptr cause, f2ptr this);
f2ptr      f2__graph__make_rootless(f2ptr cause, f2ptr this);
f2ptr      f2__graph__as__dot_code(f2ptr cause, f2ptr this);

f2ptr f2graph__primobject_type__new_aux(f2ptr cause);

// trans
declare_primobject_2_slot(trans, remove, add);

f2ptr f2trans__primobject_type__new_aux(f2ptr cause);

// pattern_graph
declare_primobject_2_slot(pattern_graph, variable_label_hash, graph);

// graph_variable
declare_primobject_1_slot(graph_variable, name);

f2ptr f2__graph_variable__new(f2ptr cause, f2ptr name);
f2ptr f2__graph_variable__new_wildcard(f2ptr cause);

f2ptr f2graph_variable__primobject_type__new_aux(f2ptr cause);

// graph_map
declare_primobject_1_slot(graph_map, node_indices);

// **

void f2__graph__initialize();

#endif // F2__GRAPH__H

