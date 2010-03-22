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

#ifndef F2__PERCEPTION_LATTICE__TYPE__H
#define F2__PERCEPTION_LATTICE__TYPE__H

// graph_node
typedef struct funk2_object_type__graph_node__slot_s funk2_object_type__graph_node__slot_t;
declare_object_type_3_slot(graph_node, label, in_edge_hash, out_edge_hash, );

// graph_edge
typedef struct funk2_object_type__graph_edge__slot_s funk2_object_type__graph_edge__slot_t;
declare_object_type_3_slot(graph_edge, label, left_node, right_node, );

// graph_edge_type
typedef struct funk2_object_type__graph_edge_type__slot_s funk2_object_type__graph_edge_type__slot_t;
declare_object_type_3_slot(graph_edge_type, label, left_node_hash, right_node_hash, );

// graph
typedef struct funk2_object_type__graph__slot_s funk2_object_type__graph__slot_t;
declare_object_type_4_slot(graph, is_rooted, root, node_label_hash, edge_type_label_hash
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
			   f2ptr equals_hash_value__symbol;
			   f2ptr equals_hash_value__funk;
			   f2ptr part_not_contained_by__symbol;
			   f2ptr part_not_contained_by__funk;
			   f2ptr as__frame__symbol;
			   f2ptr as__frame__funk;
			   );

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

#endif // F2__PERCEPTION_LATTICE__TYPE__H

#ifndef F2__PERCEPTION_LATTICE__H
#define F2__PERCEPTION_LATTICE__H

#include "f2_primobjects.h"

// graph_node
declare_primobject_3_slot(graph_node, label, in_edge_hash, out_edge_hash);

// graph_edge
declare_primobject_3_slot(graph_edge, label, left_node, right_node);

// graph_edge_type
declare_primobject_3_slot(graph_edge_type, label, left_node, right_node);

// graph
declare_primobject_3_slot(graph, is_rooted, root, node_label_hash, edge_type_label_hash);

f2ptr      f2__graph__new(f2ptr cause);
f2ptr      f2__graph__equals_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label);
f2ptr      f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_label_node, f2ptr right_node_label);

f2ptr f2graph__primobject_type__new_aux(f2ptr cause);


// trans
declare_primobject_2_slot(trans, remove, add);

f2ptr f2trans__primobject_type__new_aux(f2ptr cause);

// **

void f2__perception_lattice__initialize();

#endif // F2__PERCEPTION_LATTICE__H

