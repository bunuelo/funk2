// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__PERCEPTION_LATTICE__TYPE__H
#define F2__PERCEPTION_LATTICE__TYPE__H

// perception_graph_edge
typedef struct funk2_object_type__perception_graph_edge__slot_s funk2_object_type__perception_graph_edge__slot_t;
declare_object_type_3_slot(perception_graph_edge, label, left_node, right_node, );

// perception_graph
typedef struct funk2_object_type__perception_graph__slot_s funk2_object_type__perception_graph__slot_t;
declare_object_type_4_slot(perception_graph, nodes, edges, edges_node_hash, edge_structure_hash_value,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   );

#endif // F2__PERCEPTION_LATTICE__TYPE__H

#ifndef F2__PERCEPTION_LATTICE__H
#define F2__PERCEPTION_LATTICE__H

#include "f2_primobjects.h"

// perception_graph_edge
declare_primobject_3_slot(perception_graph_edge, label, left_node, right_node);

// perception_graph
declare_primobject_4_slot(perception_graph, nodes, edges, edges_node_hash, edge_structure_hash_value);

f2ptr f2perception_graph__primobject_type__new_aux(f2ptr cause);

// **

void f2__perception_lattice__initialize();

#endif // F2__PERCEPTION_LATTICE__H

