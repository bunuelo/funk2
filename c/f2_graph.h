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
declare_object_type_1_slot(graph_node, label,
			   f2ptr eq__symbol;
			   f2ptr eq__funk;
			   f2ptr eq_hash_value__symbol;
			   f2ptr eq_hash_value__funk;
			   );

// graph_edge
typedef struct funk2_object_type__graph_edge__slot_s funk2_object_type__graph_edge__slot_t;
declare_object_type_3_slot(graph_edge, label, left_node, right_node,
			   f2ptr eq__symbol;
			   f2ptr eq__funk;
			   f2ptr eq_hash_value__symbol;
			   f2ptr eq_hash_value__funk;
			   );

// graph
typedef struct funk2_object_type__graph__slot_s funk2_object_type__graph__slot_t;
declare_object_type_4_slot(graph, variable_name_hash, node_set, edge_set,
			   );

// graph_variable
typedef struct funk2_object_type__graph_variable__slot_s funk2_object_type__graph_variable__slot_t;
declare_object_type_1_slot(graph_variable, name,
			   f2ptr eq__symbol;
			   f2ptr eq__funk;
			   f2ptr eq_hash_value__symbol;
			   f2ptr eq_hash_value__funk;
			   );

typedef struct funk2_graph_s {
} funk2_graph_t;

#endif // F2__GRAPH__TYPE__H

#ifndef F2__GRAPH__H
#define F2__GRAPH__H

#include "f2_primobjects.h"

// graph_node
declare_primobject_5_slot(graph_node, label);

// graph_edge
declare_primobject_3_slot(graph_edge, label, left_node, right_node);

// graph
declare_primobject_4_slot(graph, node_set, edge_set);

f2ptr  f2__graph__new(f2ptr cause);
f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node);
f2ptr  f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node);
f2ptr raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge);
f2ptr  f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge);

f2ptr f2graph__primobject_type__new_aux(f2ptr cause);

// graph_variable
declare_primobject_1_slot(graph_variable, name);

f2ptr f2__graph_variable__new(f2ptr cause, f2ptr name);

f2ptr f2graph_variable__primobject_type__new_aux(f2ptr cause);

// **

void f2__graph__initialize();

#endif // F2__GRAPH__H

