// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
//   Panupong Pasupat (2010): Error correcting graph isomorphisms.
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

#ifndef F2__GRAPH_MATCH_ERROR_CORRECTING__TYPES__H
#define F2__GRAPH_MATCH_ERROR_CORRECTING__TYPES__H

// graph_edit_sequence
typedef struct funk2_object_type__graph_edit_sequence__slot_s funk2_object_type__graph_edit_sequence__slot_t;
declare_object_type_3_slot(graph_edit_sequence, operations, cost, isomorphism,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__GRAPH_MATCH_ERROR_CORRECTING__TYPES__H


#ifndef F2__GRAPH_MATCH_ERROR_CORRECTING__H
#define F2__GRAPH_MATCH_ERROR_CORRECTING__H

#include "f2_primfunks.h"
#include "f2_primobjects.h"

// graph_edit_sequence
declare_primobject_3_slot(graph_edit_sequence, operations, cost, isomorphism);
f2ptr  f2__graph_edit_sequence__new        (f2ptr cause);
f2ptr raw__graph_edit_sequence__add        (f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to, f2ptr cost_function);
f2ptr  f2__graph_edit_sequence__add        (f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to, f2ptr cost_function);
f2ptr  f2__graph_edit_sequence__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node);
f2ptr raw__graph_edit_sequence__combine    (f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph, f2ptr cost_function);
f2ptr  f2__graph_edit_sequence__combine    (f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph, f2ptr cost_function);

f2ptr f2graph_edit_sequence__primobject_type__new_aux(f2ptr cause);

// graph_decomposition_lattice
f2ptr raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph, f2ptr cost_function);
f2ptr  f2__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph, f2ptr cost_function);

// **

void f2__graph_match_error_correcting__initialize();

#endif // F2__GRAPH_MATCH_ERROR_CORRECTING__H

