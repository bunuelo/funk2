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

#ifndef F2__GRAPH_MATCH_ERROR_CORRECTING__TYPE__H
#define F2__GRAPH_MATCH_ERROR_CORRECTING__TYPE__H

// ecs_edit_sequence
typedef struct funk2_object_type__ecs_edit_sequence__slot_s funk2_object_type__ecs_edit_sequence__slot_t;
declare_object_type_3_slot(ecs_edit_sequence, edit_sequence, cost, isomorphism, );

#endif

#ifndef F2__GRAPH_MATCH_ERROR_CORRECTING__H
#define F2__GRAPH_MATCH_ERROR_CORRECTING__H

#include "f2_primfunks.h"
#include "f2_primobjects.h"

// bruno_graph
f2ptr raw__bruno_graph__edges_between_nodes (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr  f2__bruno_graph__edges_between_nodes (f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);

// ecs_edit_sequence
declare_primobject_3_slot(ecs_edit_sequence, edit_sequence, cost, isomorphism);
f2ptr f2__ecs_edit_sequence__new(f2ptr cause);
f2ptr raw__ecs_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to);
f2ptr f2__ecs_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to);
f2ptr f2__ecs_edit_sequence__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr raw__ecs_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph);
f2ptr f2__ecs_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph);

// bruno_decomposition_lattice
f2ptr raw__bruno_decomposition_lattice__ecs_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph);
f2ptr f2__bruno_decomposition_lattice__ecs_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph);

// **

//void f2__graph_match_error_correcting__reinitialize_globalvars();
void f2__graph_match_error_correcting__initialize();

#endif // F2__GRAPH_MATCH_ERROR_CORRECTING__H

