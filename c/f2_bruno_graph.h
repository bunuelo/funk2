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

#ifndef F2__BRUNO_GRAPH__TYPE__H
#define F2__BRUNO_GRAPH__TYPE__H

// bruno_graph_node
typedef struct funk2_object_type__bruno_graph_node__slot_s funk2_object_type__bruno_graph_node__slot_t;
declare_object_type_1_slot(bruno_graph_node, label, );

// bruno_graph_edge
typedef struct funk2_object_type__bruno_graph_edge__slot_s funk2_object_type__bruno_graph_edge__slot_t;
declare_object_type_3_slot(bruno_graph_edge, label, left_node, right_node, );

// bruno_graph
typedef struct funk2_object_type__bruno_graph__slot_s funk2_object_type__bruno_graph__slot_t;
declare_object_type_2_slot(bruno_graph, edge_left_node_hash, edge_right_node_hash, );

#endif // F2__BRUNO_GRAPH__TYPE__H

#ifndef F2__BRUNO_GRAPH__H
#define F2__BRUNO_GRAPH__H

#include "f2_primobjects.h"

// bruno_graph_node
declare_primobject_1_slot(bruno_graph_node, label);

// bruno_graph_edge
declare_primobject_3_slot(bruno_graph_edge, label, left_node, right_node);

// bruno_graph
declare_primobject_2_slot(bruno_graph, edge_left_node_hash, edge_right_node_hash);

// **

void f2__bruno_graph__initialize();

#endif // F2__BRUNO_GRAPH__H

