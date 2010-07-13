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

//#########################################################################
//
// This algorithm for Error-Correcting Subgraph Isomorphism Detection
//  comes from the thesis by Bruno T. Messmer:
//   http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.33.4206
//
//#########################################################################

/*
  TODO:
  - reimplement stuff using the redblacktree
   = find the way to use redblacktree (esp. funk object)
  - customizable cost
  - debug on more graphs
 */

//Help function

f2ptr raw__bruno_graph__edges_between_nodes(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__bruno_graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
  f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, left_node);
  f2ptr result = nil; //f2__ptypehash__new(cause);
  if (! edges_label_hash_right_node_hash) {
    return result;
  }
  f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash, right_node);
  if (! edges_label_hash) {
    return result;
  }
  ptypehash__keyvalue_pair__iteration
    (cause, edges_label_hash, pair__edge_label__edges,
     //f2ptr edge_label = f2__cons__car(cause, pair__edge_label__edges);
     //f2ptr edges      = f2__cons__cdr(cause, pair__edge_label__edges);
     //f2__ptypehash__add(cause, result, edge_label, f2integer__new(cause, 1)); //fix later f2__cons__length(cause, edges));
     result = f2__cons__new(cause, pair__edge_label__edges, result);
     );
  return result;
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
  f2ptr edit_sequence     = f2__ecs_edit_sequence__edit_sequence(cause, this);
  f2ptr new_edit_sequence = f2__cons__new(cause, f2__cons__new(cause, type, f2__cons__new(cause, from, to)), edit_sequence);
  f2__ecs_edit_sequence__edit_sequence__set(cause, this, new_edit_sequence);
  // Fix later
  u64 cost__i = f2integer__i(f2__ecs_edit_sequence__cost(cause, this), cause);
  cost__i += 1;
  if (raw__eq(cause, type, f2string__new(cause, 11, "Delete Node"))) cost__i += 99;
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
  //printf("Let's combine..."); f2__print(cause, this); printf(" and "); f2__print(cause, that); printf("!!\n");
  //f2__print(cause, lattice_node); printf("\n^^^\n");
  
  f2ptr this_isomorphism = f2__ecs_edit_sequence__isomorphism(cause, this);
  f2ptr that_isomorphism = f2__ecs_edit_sequence__isomorphism(cause, that);
  if (! f2__bruno_graph_isomorphism__is_disjoint_with(cause, this_isomorphism, that_isomorphism)) {
    return nil;
  }
  f2ptr new_ecs_edit_sequence = f2__ecs_edit_sequence__new(cause);
  //Make new edit sequence
  f2ptr new_edit_sequence = nil;
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
  f2__ecs_edit_sequence__edit_sequence__set(cause, new_ecs_edit_sequence, new_edit_sequence);
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
    (cause, this_mapped_node_hash, this_pair, {
     f2ptr this_node_right = f2__cons__car(cause, this_pair);
     f2ptr this_node_left  = f2__cons__cdr(cause, this_pair);
     ptypehash__keyvalue_pair__iteration 
       (cause, that_mapped_node_hash, that_pair, {
	 f2ptr that_node_right = f2__cons__car(cause, that_pair);
	 f2ptr that_node_left  = f2__cons__cdr(cause, that_pair);
	 //f2__print(cause, this_node_left); f2__print(cause, this_node_right); f2__print(cause, that_node_left); f2__print(cause, that_node_right); 
	 int i; int j;
	 for (i=0; i<2; i++) {
	   
	   f2ptr edge_in_between_iter = nil;
	   f2ptr edge_in_graph_iter   = nil;
	   f2ptr edge_in_graph_list   = nil;
	   if (!i) {
	     edge_in_between_iter = f2__bruno_graph__edges_between_nodes(cause, between_graph, this_node_left,  that_node_left );
	     edge_in_graph_list   = f2__bruno_graph__edges_between_nodes(cause, graph,         this_node_right, that_node_right);
	   } else {
	     edge_in_between_iter = f2__bruno_graph__edges_between_nodes(cause, between_graph, that_node_left,  this_node_left );
	     edge_in_graph_list   = f2__bruno_graph__edges_between_nodes(cause, graph,         that_node_right, this_node_right);
	   }
	   //f2__print(cause, edge_in_between_iter); f2__print(cause, edge_in_graph_list);

	   f2ptr edge_in_between_refined = nil;
	   f2ptr edge_in_graph_refined   = nil;
	   while (edge_in_between_iter) {
	     f2ptr edge_label = f2__cons__car(cause, f2__cons__car(cause, edge_in_between_iter));
	     edge_in_graph_iter = edge_in_graph_list;
	     //fix this later
	     edge_in_graph_list = nil;
	     int found = 0;
	     while (edge_in_graph_iter) {
	       //printf("##\n"); f2__print(cause,f2__cons__car(cause, f2__cons__car(cause, edge_in_graph_iter)));
	       //printf(" %d \n",                f2__cons__car(cause, f2__cons__car(cause, edge_in_graph_iter)));
	       //f2__print(cause, edge_label); printf(" %d \n", edge_label);
	       //f2__print(cause, raw__eq(cause, f2__cons__car(cause, f2__cons__car(cause, edge_in_graph_iter)), edge_label));
	       //printf("###\n");
	       if (!found && raw__eq(cause,    f2__cons__car(cause, f2__cons__car(cause, edge_in_graph_iter)), edge_label))
		 found = 1;
	       else
		 edge_in_graph_list = f2__cons__new(cause, f2__cons__car(cause, edge_in_graph_iter), edge_in_graph_list);
	       edge_in_graph_iter = f2__cons__cdr(cause, edge_in_graph_iter);
	     }
	     if (!found) edge_in_between_refined = f2__cons__new(cause, f2__cons__car(cause, edge_in_between_iter), edge_in_between_refined);
	     edge_in_between_iter = f2__cons__cdr(cause, edge_in_between_iter);
	   }
	   edge_in_graph_refined = edge_in_graph_list;
	   //f2__print(cause, edge_in_between_refined); printf(" !! \n"); f2__print(cause, edge_in_graph_refined); printf(" !! \n");

	   while (edge_in_between_refined && edge_in_graph_refined) {
	     f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, f2string__new(cause, 11, "Change Edge"),
					f2__cons__car(cause, edge_in_between_refined),
					f2__cons__car(cause, edge_in_graph_refined));
	     edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	     edge_in_graph_refined   = f2__cons__cdr(cause, edge_in_graph_refined);
	   }
	   while (edge_in_between_refined) {
	     f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, 
					f2string__new(cause, 11, "Delete Edge"), f2__cons__car(cause, edge_in_between_refined), nil);
	     edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	   }
	   while (edge_in_graph_refined) {
	     f2__ecs_edit_sequence__add(cause, new_ecs_edit_sequence, 
					f2string__new(cause, 11, "Insert Edge"), nil, f2__cons__car(cause, edge_in_graph_refined));
	     edge_in_graph_refined = f2__cons__cdr(cause, edge_in_graph_refined);
	   }
	 }
       }
	 );
    }
      );
  return new_ecs_edit_sequence;
}
f2ptr f2__ecs_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph) {
  return raw__ecs_edit_sequence__combine(cause, this, that, lattice_node, graph);
}
def_pcfunk4(ecs_edit_sequence__combine, this, that, lattice_node, graph, return f2__ecs_edit_sequence__combine(this_cause, this, that, lattice_node, graph));

// bruno_decomposition_lattice
#define INF 1000000000
void dfs_visit(f2ptr cause, f2ptr this, f2ptr node_parent_hash, f2ptr used_hash, f2ptr *root_to_leaf_list) {
  //printf("\n-->"); f2__print(cause, this);
  f2__ptypehash__add(cause, used_hash, this, 1);
  f2ptr lattice_node = f2__ptypehash__lookup(cause, node_parent_hash, this);
  if (lattice_node != nil) {
    f2ptr left_child_graph   = f2__bruno_decomposition_lattice_node__left_child_graph( cause, lattice_node);
    f2ptr right_child_graph  = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
    if(f2__ptypehash__lookup(cause, used_hash, left_child_graph)  == nil)
      dfs_visit(cause, left_child_graph, node_parent_hash, used_hash, root_to_leaf_list);
    if(f2__ptypehash__lookup(cause, used_hash, right_child_graph) == nil)
      dfs_visit(cause, right_child_graph, node_parent_hash, used_hash, root_to_leaf_list);
  }
  *root_to_leaf_list = f2__cons__new(cause, this, *root_to_leaf_list);
}

f2ptr raw__bruno_decomposition_lattice__ecs_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr unsolved_graph_set = f2__set__new(cause);
  //f2ptr alive_graph_set    = f2__set__new(cause);
  //f2ptr dead_graph_set     = f2__set__new(cause);
  f2ptr graph_set = f2__bruno_decomposition_lattice__graph_set(cause, this);
  f2ptr node_set  = f2__bruno_decomposition_lattice__node_set(cause, this);
  f2ptr root_graph_set    = f2__bruno_decomposition_lattice__root_graph_set(cause, this);
  f2ptr node_parent_hash  = f2__bruno_decomposition_lattice__node_parent_hash(cause, this);
  f2ptr node_left_child_hash  = f2__bruno_decomposition_lattice__node_left_child_hash( cause, this);
  f2ptr node_right_child_hash = f2__bruno_decomposition_lattice__node_right_child_hash(cause, this);
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
				  f2__ecs_edit_sequence__add(cause, edit_sequence, 
							     f2string__new(cause, 11, "Change Node"), leaf_graph__node, graph__node);
				}
				f2__ecs_edit_sequence__add_mapping(cause, edit_sequence, leaf_graph__node, graph__node);
				f2__set__add(cause, leaf_graph__open_edit_sequence_set, edit_sequence);
				);
		 //Add the delete node edit
		 f2ptr edit_sequence = f2__ecs_edit_sequence__new(cause);
		 f2__ecs_edit_sequence__add(cause, edit_sequence, f2string__new(cause, 11, "Delete Node"), leaf_graph__node, nil);
		 f2__set__add(cause, leaf_graph__open_edit_sequence_set, edit_sequence);
		 f2__ptypehash__add(cause, open_edit_sequence_set_hash, leaf_graph, leaf_graph__open_edit_sequence_set);
		 );
  printf("Prepare to TopSort...\n");
  // Topologically sort the decomposed graphs -- will be used for heuristics
  f2ptr used_hash         = f2__ptypehash__new(cause);
  f2ptr root_to_leaf_list = nil;
  set__iteration(cause, root_graph_set, root_graph, 
		 if (f2__ptypehash__lookup(cause, used_hash, root_graph) == nil) 
		   dfs_visit(cause, root_graph, node_parent_hash, used_hash, &root_to_leaf_list);
		 );
  f2ptr leaf_to_root_revs = root_to_leaf_list;
  f2ptr leaf_to_root_list = nil;
  while (leaf_to_root_revs) {
    leaf_to_root_list = f2__cons__new(cause, f2__cons__car(cause, leaf_to_root_revs), leaf_to_root_list);
    leaf_to_root_revs = f2__cons__cdr(cause, leaf_to_root_revs);
  }
  printf("TopSort Done!\n"); //f2__print(cause, leaf_to_root_list); f2__print(cause, root_to_leaf_list);

  u64 threshold = INF;
  while (1) {
    // Compute the heuristic function
    // Leaves up. For each graph S in the decomposition lattice,
    // g(S) = closed(S) is empty ? n(S) : C[closed(S)]
    // n(S) = min {C[open(S)], g(S.l) + n(S.r), n(S.l) + g(S.r)}
    f2ptr g_hash = f2__ptypehash__new(cause);
    f2ptr n_hash = f2__ptypehash__new(cause);
    f2ptr leaf_to_root_iter = leaf_to_root_list;
    while (leaf_to_root_iter) {
      f2ptr current_S   = f2__cons__car(cause, leaf_to_root_iter);
      //f2__print(cause, current_S);
      leaf_to_root_iter = f2__cons__cdr(cause, leaf_to_root_iter);
      
      f2ptr lattice_node = f2__ptypehash__lookup(cause, node_parent_hash, current_S);
      // Will get fixed when implemented with redblacktree
      u64 c_open = INF;
      f2ptr S_open_edit_sequence_set = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, current_S);
      set__iteration(cause, S_open_edit_sequence_set, S_open_edit_sequence,
		     f2ptr S_open_edit_sequence__cost = f2integer__i(f2__ecs_edit_sequence__cost(cause, S_open_edit_sequence), cause);
		     if (S_open_edit_sequence__cost < c_open) c_open = S_open_edit_sequence__cost;
		     );
      u64 c_closed = INF;
      f2ptr S_closed_edit_sequence_set = f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, current_S);
      if(! raw__set__is_empty(cause, S_closed_edit_sequence_set)) {
	set__iteration(cause, S_closed_edit_sequence_set, S_closed_edit_sequence,
		       f2ptr S_closed_edit_sequence__cost = f2integer__i(f2__ecs_edit_sequence__cost(cause, S_closed_edit_sequence), cause);
		       if (S_closed_edit_sequence__cost < c_closed) c_closed = S_closed_edit_sequence__cost;
		       );
      }
      if (lattice_node == nil) {  // leaf
	f2__ptypehash__add(cause, n_hash, current_S, c_open);
	if (raw__set__is_empty(cause, S_closed_edit_sequence_set))
	  f2__ptypehash__add(cause, g_hash, current_S, c_open);
	else
	  f2__ptypehash__add(cause, g_hash, current_S, c_closed);
      } else {
	f2ptr left_child_graph   = f2__bruno_decomposition_lattice_node__left_child_graph( cause, lattice_node);
	f2ptr right_child_graph  = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
	u64 gl_nr = f2__ptypehash__lookup(cause, g_hash, left_child_graph) + f2__ptypehash__lookup(cause, n_hash, right_child_graph);
	if (c_open > gl_nr) c_open = gl_nr;
	u64 nl_gr = f2__ptypehash__lookup(cause, n_hash, left_child_graph) + f2__ptypehash__lookup(cause, g_hash, right_child_graph);
	if (c_open > nl_gr) c_open = nl_gr;
	f2__ptypehash__add(cause, n_hash, current_S, c_open);
      }
    }
    //printf("N\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); printf("%d\n", f2__ptypehash__lookup(cause, n_hash, graph_s)););
    //printf("G\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); printf("%d\n", f2__ptypehash__lookup(cause, g_hash, graph_s)););
    
    // roots down
    // h(S) = min {g(S.sibling) + h(S.p)} over S.p
    f2ptr h_hash = f2__ptypehash__new(cause);
    f2ptr root_to_leaf_iter = root_to_leaf_list;
    f2ptr node_s = nil;
    while (root_to_leaf_iter) {
      f2ptr current_S   = f2__cons__car(cause, root_to_leaf_iter);
      f2__print(cause, current_S);
      root_to_leaf_iter = f2__cons__cdr(cause, root_to_leaf_iter);

      if (f2__ptypehash__lookup(cause, root_graph_set, current_S) != nil) {
	f2__ptypehash__add(cause, h_hash, current_S, 0);
      } else {
	u64 min_h = INF;
	node_s = f2__ptypehash__lookup(cause, node_left_child_hash, current_S);
	//f2__print(cause, node_s);
	if (node_s != nil) {
	  set__iteration(cause, node_s, lattice_node,
			 f2ptr parent_graph  = f2__bruno_decomposition_lattice_node__parent_graph(cause, lattice_node);
			 f2ptr sibling_graph = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
			 u64 gs_hp = f2__ptypehash__lookup(cause, g_hash, sibling_graph) + f2__ptypehash__lookup(cause, h_hash, parent_graph);
			 if (gs_hp < min_h) min_h = gs_hp;
			 );
	}
	node_s = f2__ptypehash__lookup(cause, node_right_child_hash, current_S);
	if (node_s != nil) {
	  set__iteration(cause, node_s, lattice_node,
			 f2ptr parent_graph  = f2__bruno_decomposition_lattice_node__parent_graph(cause, lattice_node);
			 f2ptr sibling_graph = f2__bruno_decomposition_lattice_node__left_child_graph(cause, lattice_node);
			 u64 gs_hp = f2__ptypehash__lookup(cause, g_hash, sibling_graph) + f2__ptypehash__lookup(cause, h_hash, parent_graph);
			 if (gs_hp < min_h) min_h = gs_hp;
			 );
	}
	f2__ptypehash__add(cause, h_hash, current_S, min_h);
      }
    }
    //printf("H\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); printf("%d\n", f2__ptypehash__lookup(cause, h_hash, graph_s)););

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
		   estimated_cost = estimated_cost + f2__ptypehash__lookup(cause, h_hash, alive_graph); //0;               // add heuristic here
		   if (estimated_cost < minimal_estimated_cost && estimated_cost <= threshold) {
		     minimal_estimated_cost = estimated_cost;
		     minimal_cost_graph = alive_graph;
		     minimal_open_edit_sequence = estimated_open_edit_sequence;
		   }
		   );
    if (minimal_cost_graph == nil) break;
    printf("%d %d\n", minimal_cost_graph, minimal_estimated_cost);
    //f2__print(cause, minimal_cost_graph); 
    //Move the smallest edit sequence to closed(S)
    f2ptr minimal_cost_graph__open_edit_sequence_set   = f2__ptypehash__lookup(cause, open_edit_sequence_set_hash, minimal_cost_graph);
    f2ptr minimal_cost_graph__closed_edit_sequence_set = f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, minimal_cost_graph);
    f2__set__remove(cause, minimal_cost_graph__open_edit_sequence_set, minimal_open_edit_sequence);
    f2__set__add(cause, minimal_cost_graph__closed_edit_sequence_set, minimal_open_edit_sequence);
    //Lessen the threshold
    if (f2__set__lookup(cause, root_graph_set, minimal_cost_graph) != nil) {
      threshold = minimal_estimated_cost; //f2integer__i(f2__ecs_edit_sequence__cost(cause, minimal_open_edit_sequence), cause);
    }
    //Solve the larger graph
    set__iteration(cause, unsolved_graph_set, unsolved_graph,
		   f2ptr lattice_node       = f2__ptypehash__lookup(cause, node_parent_hash, unsolved_graph);
		   if (lattice_node != nil) {
		     f2ptr left_child_graph   = f2__bruno_decomposition_lattice_node__left_child_graph( cause, lattice_node);
		     f2ptr right_child_graph  = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
		     //printf("##"); f2__print(cause, unsolved_graph); f2__print(cause, left_child_graph);
		     //f2__print(cause, right_child_graph); f2__print(cause, minimal_cost_graph); printf("##\n");
		     if (left_child_graph == minimal_cost_graph) {
		       //printf("L!\n");
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
		       //printf("R!\n");
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
		   }
		   );
  }
  //Output stuff -- fix later
  f2ptr answer = f2__ptypehash__new(cause);
  set__iteration(cause, root_graph_set, root_graph, 
		 f2__ptypehash__add(cause, answer, root_graph, f2__ptypehash__lookup(cause, closed_edit_sequence_set_hash, root_graph));
		 );
  return answer;
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

