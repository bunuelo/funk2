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

#include "funk2.h"
#include <stdio.h>

//Help function

f2ptr raw__bruno_graph__edges_between_nodes(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__bruno_graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
  f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, left_node);
  if (! edges_label_hash_right_node_hash) {
    return nil;
  }
  f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash, right_node);
  if (! edges_label_hash) {
    return nil;
  }
  ptypehash__keyvalue_pair__iteration
    (cause, edges_label_hash, pair__edge_label__edges,
     //I'll fix this later
     return f2cons__new(cause, f2__cons__car(cause, pair__edge_label__edges), nil);
     );
  return nil;
}

f2ptr f2__bruno_graph__edges_between_nodes(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  return raw__bruno_graph__edges_between_nodes(cause, this, left_node, right_node);
}
def_pcfunk3(bruno_graph__edges_between_nodes, this, left_node, right_node, return f2__bruno_graph__edges_between_nodes(this_cause, this, left_node, right_node));

//Edit Sequence

def_primobject_3_slot(ecs_edit_sequence, edit_sequence, cost, isomorphism);

f2ptr f2__ecs_edit_sequence__new(f2ptr cause) {
  f2ptr edit_sequence = nil;
  f2ptr cost              = f2integer__new(cause, 0);
  f2ptr isomorphism       = f2__bruno_graph_isomorphism__new(cause);
  return f2ecs_edit_sequence__new(cause, edit_sequence, cost, isomorphism);
}
def_pcfunk0(ecs_edit_sequence__new, return f2__ecs_edit_sequence__new(this_cause));

f2ptr raw__ecs_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to) {
  // Fix later
  u64 cost__i = f2integer__i(f2__ecs_edit_sequence__cost(cause, this), cause);
  cost__i += 1;
  f2__ecs_edit_sequence__cost__set(cause, this, f2integer__new(cause, cost__i));
  return nil;
}
f2ptr f2__ecs_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to) {
  return raw__ecs_edit_sequence__add(cause, this, type, from, to);
}
def_pcfunk4(ecs_edit_sequence__add, this, type, from, to, return f2__ecs_edit_sequence__add(this_cause, this, type, from, to));

f2ptr f2__ecs_edit_sequence__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  return f2__bruno_graph_isomorphism__add_mapping(cause, f2__ecs_edit_sequence__isomorphism(cause, this), left_node, right_node);
}
def_pcfunk3(ecs_edit_sequence__add_mapping, this, left_node, right_node, return f2__ecs_edit_sequence__add_mapping(this_cause, this, left_node, right_node));

f2ptr raw__ecs_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph) {
  printf("***\n");
  f2__print(cause, this); printf("\n");
  f2__print(cause, that); printf("\n");
  f2__print(cause, lattice_node); printf("\n^^^\n");
  
  f2ptr this_isomorphism = f2__ecs_edit_sequence__isomorphism(cause, this);
  f2ptr that_isomorphism = f2__ecs_edit_sequence__isomorphism(cause, that);
  if (! f2__bruno_graph_isomorphism__is_disjoint_with(cause, this_isomorphism, that_isomorphism)) {
    return nil;
  }
  f2ptr new_ecs_edit_sequence = f2__ecs_edit_sequence__new(cause);
  //Make new edit sequence
  f2ptr new_edit_sequence = f2__ecs_edit_sequence__edit_sequence(cause, new_ecs_edit_sequence);
  f2ptr temp_list = nil;
  f2ptr edit_sequence__iter = f2__ecs_edit_sequence__edit_sequence(cause, this);
  while (edit_sequence__iter) {
    temp_list = f2cons__new(cause, f2__cons__car(cause, edit_sequence__iter), temp_list);
    edit_sequence__iter = f2__cons__cdr(cause, edit_sequence__iter);
  }
  edit_sequence__iter = f2__ecs_edit_sequence__edit_sequence(cause, that);
  while (edit_sequence__iter) {
    temp_list = f2cons__new(cause, f2__cons__car(cause, edit_sequence__iter), temp_list);
    edit_sequence__iter = f2__cons__cdr(cause, edit_sequence__iter);
  }
  edit_sequence__iter = temp_list;
  while (edit_sequence__iter) {
    new_edit_sequence = f2cons__new(cause, f2__cons__car(cause, edit_sequence__iter), new_edit_sequence);
    edit_sequence__iter = f2__cons__cdr(cause, edit_sequence__iter);
  }
  //Make new cost
  u64 new_cost = f2integer__i(f2__ecs_edit_sequence__cost(cause, this), cause) + f2integer__i(f2__ecs_edit_sequence__cost(cause, that), cause);
  f2__ecs_edit_sequence__cost__set(cause, new_ecs_edit_sequence, f2integer__new(cause, new_cost));
  //Make new isomorphism
  f2ptr new_isomorphism = f2__bruno_graph_isomorphism__union(cause, this_isomorphism, that_isomorphism);
  f2__ecs_edit_sequence__isomorphism__set(cause, new_ecs_edit_sequence, new_isomorphism);
  //Add the between edges
  f2ptr between_graph = f2__bruno_decomposition_lattice_node__between_graph(cause, lattice_node);
  f2ptr this_mapped_node_hash = f2__bruno_graph_isomorphism__left_node_right_node_hash(cause, this_isomorphism);
  f2ptr that_mapped_node_hash = f2__bruno_graph_isomorphism__left_node_right_node_hash(cause, that_isomorphism);
  ptypehash__keyvalue_pair__iteration 
    (cause, this_mapped_node_hash, this_pair,
     f2ptr this_node_right = f2__cons__car(cause, this_pair);
     f2ptr this_node_left  = f2__cons__cdr(cause, this_pair);
     ptypehash__keyvalue_pair__iteration 
       (cause, that_mapped_node_hash, that_pair,
	f2ptr that_node_right = f2__cons__car(cause, that_pair);
	f2ptr that_node_left  = f2__cons__cdr(cause, that_pair);
	f2__print(cause, this_node_left); f2__print(cause, this_node_right); f2__print(cause, that_node_left); f2__print(cause, that_node_right); 
	{
	  f2ptr edge_in_between_iter = f2__bruno_graph__edges_between_nodes(cause, between_graph, this_node_left,  that_node_left );
	  f2ptr edge_in_graph_iter   = f2__bruno_graph__edges_between_nodes(cause, graph,         this_node_right, that_node_right);
	  f2__print(cause, edge_in_between_iter); f2__print(cause, edge_in_graph_iter);
	  //Assume sorted
	  f2ptr edge_in_between_refined = nil;
	  f2ptr edge_in_graph_refined   = nil;
	  while(edge_in_between_iter && edge_in_graph_iter) {
	    f2ptr edge_in_between = f2__cons__car(cause, edge_in_between_iter);
	    f2ptr edge_in_graph   = f2__cons__car(cause, edge_in_graph_iter);
	    if (edge_in_between < edge_in_graph) {
	      edge_in_between_refined = f2cons__new(cause, edge_in_between, edge_in_between_refined);
	      edge_in_between_iter    = f2__cons__cdr(cause, edge_in_between_iter);
	    } else if (edge_in_between > edge_in_graph) {
	      edge_in_graph_refined   = f2cons__new(cause, edge_in_graph, edge_in_graph_refined);
	      edge_in_graph_iter      = f2__cons__cdr(cause, edge_in_graph_iter);
	    } else {
	      edge_in_between_iter    = f2__cons__cdr(cause, edge_in_between_iter);
	      edge_in_graph_iter      = f2__cons__cdr(cause, edge_in_graph_iter);
	    }
	  }
	  f2__print(cause, edge_in_between_refined);
	  f2__print(cause, edge_in_graph_refined); printf("!! \n");
	  while (edge_in_between_refined && edge_in_graph_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "change edge label",
				       f2__cons__car(cause, edge_in_between_refined),
				       f2__cons__car(cause, edge_in_graph_refined));
	    edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	    edge_in_graph_refined   = f2__cons__cdr(cause, edge_in_graph_refined);
	  }
	  while (edge_in_between_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "delete edge", f2__cons__car(cause, edge_in_between_refined), nil);
	    edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	  }
	  while (edge_in_graph_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "insert edge", nil, f2__cons__car(cause, edge_in_graph_refined));
	    edge_in_graph_refined = f2__cons__cdr(cause, edge_in_graph_refined);
	  }
	}
	{
	  f2ptr edge_in_between_iter = f2__bruno_graph__edges_between_nodes(cause, between_graph, that_node_left,  this_node_left );
	  f2ptr edge_in_graph_iter   = f2__bruno_graph__edges_between_nodes(cause, graph,         that_node_right, this_node_right);
	  f2__print(cause, edge_in_between_iter); f2__print(cause, edge_in_graph_iter);
	  //Assume sorted
	  f2ptr edge_in_between_refined = nil;
	  f2ptr edge_in_graph_refined   = nil;
	  while(edge_in_between_iter && edge_in_graph_iter) {
	    f2ptr edge_in_between = f2__cons__car(cause, edge_in_between_iter);
	    f2ptr edge_in_graph   = f2__cons__car(cause, edge_in_graph_iter);
	    if (edge_in_between < edge_in_graph) {
	      edge_in_between_refined = f2cons__new(cause, edge_in_between, edge_in_between_refined);
	      edge_in_between_iter    = f2__cons__cdr(cause, edge_in_between_iter);
	    } else if (edge_in_between > edge_in_graph) {
	      edge_in_graph_refined   = f2cons__new(cause, edge_in_graph, edge_in_graph_refined);
	      edge_in_graph_iter      = f2__cons__cdr(cause, edge_in_graph_iter);
	    } else {
	      edge_in_between_iter    = f2__cons__cdr(cause, edge_in_between_iter);
	      edge_in_graph_iter      = f2__cons__cdr(cause, edge_in_graph_iter);
	    }
	  }
	  f2__print(cause, edge_in_between_refined);
	  f2__print(cause, edge_in_graph_refined); printf("!! \n");
	  while (edge_in_between_refined && edge_in_graph_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "change edge label",
				       f2__cons__car(cause, edge_in_between_refined),
				       f2__cons__car(cause, edge_in_graph_refined));
	    edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	    edge_in_graph_refined   = f2__cons__cdr(cause, edge_in_graph_refined);
	  }
	  while (edge_in_between_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "delete edge", f2__cons__car(cause, edge_in_between_refined), nil);
	    edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	  }
	  while (edge_in_graph_refined) {
	    f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, "insert edge", nil, f2__cons__car(cause, edge_in_graph_refined));
	    edge_in_graph_refined = f2__cons__cdr(cause, edge_in_graph_refined);
	  }
	}
	);
     );
  return new_ecs_edit_sequence;
}
f2ptr f2__ecs_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph) {
  return raw__ecs_edit_sequence__combine(cause, this, that, lattice_node, graph);
}
def_pcfunk4(ecs_edit_sequence__combine, this, that, lattice_node, graph, return f2__ecs_edit_sequence__combine(this_cause, this, that, lattice_node, graph));

#define INF 1000000000
// bruno_decomposition_lattice

f2ptr raw__bruno_decomposition_lattice__ecs_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr unsolved_graph_set = f2__set__new(cause);
  //f2ptr alive_graph_set    = f2__set__new(cause);
  //f2ptr dead_graph_set     = f2__set__new(cause);
  f2ptr graph_set          = f2__bruno_decomposition_lattice__graph_set(cause, this);
  set__iteration(cause, graph_set, graph,
		 f2__set__add(cause, unsolved_graph_set, graph);
		 );
  //f2ptr isomorphisms_graph_hash = f2__ptypehash__new(cause);
  f2ptr open_edit_sequence_set_hash   = f2__ptypehash__new(cause);
  f2ptr closed_edit_sequence_set_hash = f2__ptypehash__new(cause);
  set__iteration(cause, graph_set, graph,
		 f2__ptypehash__add(cause, open_edit_sequence_set_hash, graph, f2__set__new(cause));
		 f2__ptypehash__add(cause, closed_edit_sequence_set_hash, graph, f2__set__new(cause));
		 );
  f2ptr leaf_graph_set                = f2__bruno_decomposition_lattice__leaf_graph_set(cause, this);
  set__iteration(cause, leaf_graph_set, leaf_graph,
		 f2ptr leaf_graph__node_set = f2__bruno_graph__node_set(cause, leaf_graph);
		 f2ptr leaf_graph__node     = nil;
		 set__iteration(cause, leaf_graph__node_set, leaf_graph__node_set__node,
				leaf_graph__node = leaf_graph__node_set__node;
				);

		 f2ptr leaf_graph__open_edit_sequence_set = f2__set__new(cause);
		 f2ptr graph__node_set = f2__bruno_graph__node_set(cause, graph);
		 //Add the change node edit
		 set__iteration(cause, graph__node_set, graph__node,
				f2ptr edit_sequence = f2__ecs_edit_sequence__new(cause);
				if (f2__bruno_graph_node__label(cause, leaf_graph__node) != f2__bruno_graph_node__label(cause, graph__node)) {
				  f2__ecs_edit_sequence__add(cause, edit_sequence, "Change Node Label", leaf_graph__node, graph__node);
				  f2__ecs_edit_sequence__add_mapping(cause, edit_sequence, leaf_graph__node, graph__node);
				}
				f2__set__add(cause, leaf_graph__open_edit_sequence_set, edit_sequence);
				);
		 //Add the delete node edit
		 f2ptr edit_sequence = f2__ecs_edit_sequence__new(cause);
		 f2__ecs_edit_sequence__add(cause, edit_sequence, "Delete Node", leaf_graph__node, nil);
		 //f2__set__add(cause, leaf_graph__open_edit_sequence_set, edit_sequence);
		 /*
		 f2__set__remove(cause, unsolved_graph_set, leaf_graph);
		 if (leaf_graph__open_edit_sequence_set != nil) {
		   f2__set__add(cause, alive_graph_set, leaf_graph);
		   f2__ptypehash__add(cause, open_edit_sequence_set_hash, leaf_graph, leaf_graph__open_edit_sequence_set);
		 } else {
		   f2__set__add(cause, dead_graph_set, leaf_graph);
		 }
		 */
		 f2__ptypehash__add(cause, open_edit_sequence_set_hash, leaf_graph, leaf_graph__open_edit_sequence_set);
		 );

  f2ptr node_parent_hash = f2__bruno_decomposition_lattice__node_parent_hash(cause, this);
  u64 threshold = INF;
  while (1) {
    u64 minimal_estimated_cost = INF;
    f2ptr minimal_cost_graph = nil;
    f2ptr minimal_open_edit_sequence = nil;
    //Find S in D with minimal C[open(S)] + h(S)
    //set__iteration(cause, alive_graph_set, alive_graph,
    set__iteration(cause, unsolved_graph_set, alive_graph,
		   u64 estimated_cost = INF;
		   f2ptr estimated_open_edit_sequence = nil;
		   f2ptr alive_graph__open_edit_sequence_set = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, alive_graph);
		   if (! raw__set__is_empty(cause, alive_graph__open_edit_sequence_set)) {
		     set__iteration(cause, alive_graph__open_edit_sequence_set, alive_graph__open_edit_sequence,
				    f2ptr alive_graph__open_edit_sequence__cost_ptr = f2__ecs_edit_sequence__cost(cause, alive_graph__open_edit_sequence);
				    u64   alive_graph__open_edit_sequence__cost     = f2integer__i(alive_graph__open_edit_sequence__cost_ptr, cause);
				    if (alive_graph__open_edit_sequence__cost < estimated_cost) {
				      estimated_cost = alive_graph__open_edit_sequence__cost;
				      estimated_open_edit_sequence = alive_graph__open_edit_sequence;
				    }
				    );
		   }
		   estimated_cost = estimated_cost + 0;               // add heuristic here
		   if (estimated_cost < minimal_estimated_cost && estimated_cost <= threshold) {
		     minimal_estimated_cost = estimated_cost;
		     minimal_cost_graph = alive_graph;
		     minimal_open_edit_sequence = estimated_open_edit_sequence;
		   }
		   );
    if (minimal_cost_graph == nil) break;
    printf("%d %d\n", minimal_cost_graph, minimal_estimated_cost);
    //Move the smallest edit sequence to closed(S)
    f2ptr minimal_cost_graph__open_edit_sequence_set   = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, minimal_cost_graph);
    f2ptr minimal_cost_graph__closed_edit_sequence_set = f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, minimal_cost_graph);
    f2__set__remove(cause, minimal_cost_graph__open_edit_sequence_set, minimal_open_edit_sequence);
    f2__set__add(cause, minimal_cost_graph__closed_edit_sequence_set, minimal_open_edit_sequence);
    //Lessen the threshold
    f2ptr root_graph_set = f2__bruno_decomposition_lattice__root_graph_set(cause, this);
    if (f2__set__lookup(cause, root_graph_set, minimal_cost_graph) != nil) {
      threshold = minimal_estimated_cost; //f2integer__i(f2__ecs_edit_sequence__cost(cause, minimal_open_edit_sequence), cause);
    }
    //Solve the larger graph
    set__iteration(cause, unsolved_graph_set, unsolved_graph,
		   f2ptr lattice_node       = f2__ptypehash__lookup(cause, node_parent_hash, unsolved_graph);
		   f2ptr left_child_graph   = f2__bruno_decomposition_lattice_node__left_child_graph( cause, lattice_node);
		   f2ptr right_child_graph  = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
		   if (left_child_graph == minimal_cost_graph) {
		     f2ptr unsolved_graph__open_edit_sequence_set = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, unsolved_graph);
		     f2ptr right_child_graph__closed_edit_sequence_set = f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, right_child_graph);
		     set__iteration(cause, right_child_graph__closed_edit_sequence_set, right_child_graph__closed_edit_sequence,
				    f2ptr combined_edit_sequence = f2__ecs_edit_sequence__combine(cause, minimal_open_edit_sequence, 
												  right_child_graph__closed_edit_sequence,
												  lattice_node, graph);
				    if (combined_edit_sequence != nil) {
				      f2__set__add(cause, unsolved_graph__open_edit_sequence_set, combined_edit_sequence);
				    }
				    );
		   } else if (right_child_graph == minimal_cost_graph) {
		     f2ptr unsolved_graph__open_edit_sequence_set = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, unsolved_graph);
		     f2ptr left_child_graph__closed_edit_sequence_set = f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, left_child_graph);
		     set__iteration(cause, left_child_graph__closed_edit_sequence_set, left_child_graph__closed_edit_sequence,
				    f2ptr combined_edit_sequence = f2__ecs_edit_sequence__combine(cause, minimal_open_edit_sequence, 
												  left_child_graph__closed_edit_sequence,
												  lattice_node, graph);
				    if (combined_edit_sequence != nil) {
				      f2__set__add(cause, unsolved_graph__open_edit_sequence_set, combined_edit_sequence);
				    }
				    );
		   }
		   );
  }
  //Output stuff
  return closed_edit_sequence_set_hash;
}

f2ptr f2__bruno_decomposition_lattice__ecs_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  if ((! raw__bruno_decomposition_lattice__is_type(cause, this)) ||
      (! raw__bruno_graph__is_type(cause, graph))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_decomposition_lattice__ecs_isomorphisms(cause, this, graph);
}
def_pcfunk2(bruno_decomposition_lattice__ecs_isomorphisms, this, graph, return f2__bruno_decomposition_lattice__ecs_isomorphisms(this_cause, this, graph));

//Test modules

f2ptr f2__error_correcting__test(f2ptr cause) {
  return nil;
}
def_pcfunk0(error_correcting__test, return f2__error_correcting__test(this_cause));

// **

void f2__graph_match_error_correcting__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __ecs_edit_sequence__symbol = new__symbol(cause, "ecs_edit_sequence");
}

void f2__graph_match_error_correcting__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_match_error_correcting", "", &f2__graph_match_error_correcting__reinitialize_globalvars);
  
  f2__graph_match_error_correcting__reinitialize_globalvars();

  f2__primcfunk__init__0(error_correcting__test, "Test error correcting graph matching.");
  
  // bruno_graph
  f2__primcfunk__init__3(bruno_graph__edges_between_nodes, this, left_node, right_node, "");

  // ecs_edit_sequence
  initialize_primobject_3_slot(ecs_edit_sequence, edit_sequence, cost, isomorphism);
  f2__primcfunk__init__0(ecs_edit_sequence__new, "");
  f2__primcfunk__init__4(ecs_edit_sequence__add, this, type, from, to, "");
  f2__primcfunk__init__3(ecs_edit_sequence__add_mapping, this, left_node, right_node, "");
  f2__primcfunk__init__4(ecs_edit_sequence__combine, this, that, lattice_node, graph, "");

  // bruno_decomposition_lattice
  f2__primcfunk__init__2(bruno_decomposition_lattice__ecs_isomorphisms, this, graph, "");
  
}

