// 
// Copyright (c) 2007-2012 Bo Morgan.
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
  - debug on more graphs
  - What should the error_correcting_subgraph_isomorphisms return?
  - analogies!
 */


// graph_edit_sequence

def_primobject_3_slot(graph_edit_sequence, operations, cost, isomorphism);

f2ptr f2__graph_edit_sequence__new(f2ptr cause) {
  f2ptr operations  = nil;
  f2ptr cost        = f2integer__new(cause, 0);
  f2ptr isomorphism = f2__graph_isomorphism__new(cause);
  return f2graph_edit_sequence__new(cause, operations, cost, isomorphism);
}
def_pcfunk0(graph_edit_sequence__new,
	    "",
	    return f2__graph_edit_sequence__new(this_cause));

f2ptr raw__graph_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to, f2ptr cost_function) {
  f2ptr operations     = f2__graph_edit_sequence__operations(cause, this);
  f2ptr new_operations = f2__cons__new(cause, f2__cons__new(cause, type, f2__cons__new(cause, from, to)), operations);
  //f2__print(cause, type); f2__print(cause, from); f2__print(cause, to);
  //f2__print(cause, f2__cons__new(cause, type, f2__cons__new(cause, from, to)));
  f2__graph_edit_sequence__operations__set(cause, this, new_operations);
  // Fix later
  u64 cost__i = f2integer__i(f2__graph_edit_sequence__cost(cause, this), cause);
  u64 add_cost = 0;
  if (cost_function == nil) {
    add_cost = 1;
    if (raw__eq(cause, type, new__string(cause, "Delete Node"))) add_cost = 100;
  } else {
    f2ptr add_cost_from_f = f2__force_funk_apply(cause, f2__this__fiber(cause), cost_function, f2list3__new(cause, type, from, to));
    if (!raw__integer__is_type(cause, add_cost_from_f)) {
      //Invalid stuff
      printf("INVALID VALUE\n"); f2__print(cause, add_cost_from_f);
      f2__graph_edit_sequence__cost__set(cause, this, f2integer__new(cause, cost__i + 1));
      return nil;
    }
    add_cost = f2integer__i(add_cost_from_f, cause);
    //printf("Add cost = %d\n", add_cost);
  }
  f2__graph_edit_sequence__cost__set(cause, this, f2integer__new(cause, cost__i + add_cost));
  return nil;
}
f2ptr f2__graph_edit_sequence__add(f2ptr cause, f2ptr this, f2ptr type, f2ptr from, f2ptr to, f2ptr cost_function) {
  return raw__graph_edit_sequence__add(cause, this, type, from, to, cost_function);
}
def_pcfunk5(graph_edit_sequence__add, this, type, from, to, cost_function,
	    "",
	    return f2__graph_edit_sequence__add(this_cause, this, type, from, to, cost_function));

f2ptr f2__graph_edit_sequence__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  return f2__graph_isomorphism__add_mapping(cause, f2__graph_edit_sequence__isomorphism(cause, this), left_node, right_node);
}
def_pcfunk3(graph_edit_sequence__add_mapping, this, left_node, right_node,
	    "",
	    return f2__graph_edit_sequence__add_mapping(this_cause, this, left_node, right_node));

f2ptr raw__graph_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph, f2ptr cost_function) {
  //printf("Let's combine..."); f2__print(cause, this); printf(" and "); f2__print(cause, that); printf("!!\n");
  //f2__print(cause, lattice_node); printf("\n^^^\n");
  
  f2ptr this_isomorphism = f2__graph_edit_sequence__isomorphism(cause, this);
  f2ptr that_isomorphism = f2__graph_edit_sequence__isomorphism(cause, that);
  if (! f2__graph_isomorphism__is_disjoint_with(cause, this_isomorphism, that_isomorphism)) {
    return nil;
  }
  f2ptr new_graph_edit_sequence = f2__graph_edit_sequence__new(cause);
  //Make new edit sequence
  f2ptr new_operations   = nil;
  f2ptr temp_list        = nil;
  f2ptr operations__iter = f2__graph_edit_sequence__operations(cause, this);
  while (operations__iter) {
    temp_list = raw__cons__new(cause, f2__cons__car(cause, operations__iter), temp_list);
    operations__iter = f2__cons__cdr(cause, operations__iter);
  }
  operations__iter = f2__graph_edit_sequence__operations(cause, that);
  while (operations__iter) {
    temp_list = raw__cons__new(cause, f2__cons__car(cause, operations__iter), temp_list);
    operations__iter = f2__cons__cdr(cause, operations__iter);
  }
  operations__iter = temp_list;
  while (operations__iter) {
    new_operations = raw__cons__new(cause, f2__cons__car(cause, operations__iter), new_operations);
    operations__iter = f2__cons__cdr(cause, operations__iter);
  }
  f2__graph_edit_sequence__operations__set(cause, new_graph_edit_sequence, new_operations);
  //Make new cost
  u64 new_cost = f2integer__i(f2__graph_edit_sequence__cost(cause, this), cause) + f2integer__i(f2__graph_edit_sequence__cost(cause, that), cause);
  f2__graph_edit_sequence__cost__set(cause, new_graph_edit_sequence, f2integer__new(cause, new_cost));
  //Make new isomorphism
  f2ptr new_isomorphism = f2__graph_isomorphism__union(cause, this_isomorphism, that_isomorphism);
  f2__graph_edit_sequence__isomorphism__set(cause, new_graph_edit_sequence, new_isomorphism);
  //Add the between edges
  f2ptr between_graph = f2__graph_decomposition_lattice_node__between_graph(cause, lattice_node);
  f2ptr this_mapped_node_hash = f2__graph_isomorphism__left_node_right_node_hash(cause, this_isomorphism);
  f2ptr that_mapped_node_hash = f2__graph_isomorphism__left_node_right_node_hash(cause, that_isomorphism);
  ptypehash__keyvalue_pair__iteration 
    (cause, this_mapped_node_hash, this_pair, {
     f2ptr this_node_right = f2__cons__car(cause, this_pair);
     f2ptr this_node_left  = f2__cons__cdr(cause, this_pair);
     ptypehash__keyvalue_pair__iteration 
       (cause, that_mapped_node_hash, that_pair, {
	 f2ptr that_node_right = f2__cons__car(cause, that_pair);
	 f2ptr that_node_left  = f2__cons__cdr(cause, that_pair);
	 //f2__print(cause, this_node_left); f2__print(cause, this_node_right); f2__print(cause, that_node_left); f2__print(cause, that_node_right); 
	 int i;
	 for (i=0; i<2; i++) {
	   
	   f2ptr edge_in_between_iter = nil;
	   f2ptr edge_in_graph_iter   = nil;
	   f2ptr edge_in_graph_list   = nil;
	   if (!i) {
	     edge_in_between_iter = f2__graph__edges_between_nodes(cause, between_graph, this_node_left,  that_node_left );
	     edge_in_graph_list   = f2__graph__edges_between_nodes(cause, graph,         this_node_right, that_node_right);
	   } else {
	     edge_in_between_iter = f2__graph__edges_between_nodes(cause, between_graph, that_node_left,  this_node_left );
	     edge_in_graph_list   = f2__graph__edges_between_nodes(cause, graph,         that_node_right, this_node_right);
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
	       if (!found && raw__eq(cause, f2__cons__car(cause, f2__cons__car(cause, edge_in_graph_iter)), edge_label))
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
	     f2__graph_edit_sequence__add(cause, new_graph_edit_sequence, new__string(cause, "Change Edge"),
					f2__cons__cdr(cause, f2__cons__car(cause, edge_in_between_refined)),
					f2__cons__cdr(cause, f2__cons__car(cause, edge_in_graph_refined)), cost_function);
	     edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	     edge_in_graph_refined   = f2__cons__cdr(cause, edge_in_graph_refined);
	   }
	   while (edge_in_between_refined) {
	     f2__graph_edit_sequence__add(cause, new_graph_edit_sequence, 
					new__string(cause, "Delete Edge"),
                                        f2__cons__cdr(cause, f2__cons__car(cause, edge_in_between_refined)), nil, cost_function);
	     edge_in_between_refined = f2__cons__cdr(cause, edge_in_between_refined);
	   }
	   while (edge_in_graph_refined) {
	     f2__graph_edit_sequence__add(cause, new_graph_edit_sequence, new__string(cause, "Insert Edge"),
                                        nil, f2__cons__cdr(cause, f2__cons__car(cause, edge_in_graph_refined)), cost_function);
	     edge_in_graph_refined = f2__cons__cdr(cause, edge_in_graph_refined);
	   }
	 }
       }
	 );
    }
      );
  return new_graph_edit_sequence;
}
f2ptr f2__graph_edit_sequence__combine(f2ptr cause, f2ptr this, f2ptr that, f2ptr lattice_node, f2ptr graph, f2ptr cost_function) {
  return raw__graph_edit_sequence__combine(cause, this, that, lattice_node, graph, cost_function);
}
def_pcfunk5(graph_edit_sequence__combine, this, that, lattice_node, graph, cost_function,
	    "",
	    return f2__graph_edit_sequence__combine(this_cause, this, that, lattice_node, graph, cost_function));

f2ptr raw__graph_edit_sequence__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_edit_sequence"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "operations"),        f2__graph_edit_sequence__operations( cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "cost"),              f2__graph_edit_sequence__cost(       cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "isomorphism"),       f2__graph_edit_sequence__isomorphism(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_edit_sequence__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_edit_sequence,  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__graph_edit_sequence__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_edit_sequence__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_edit_sequence__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2graph_edit_sequence__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_edit_sequence__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_edit_sequence.terminal_print_with_frame__funk);}
  return this;
}




// graph_decomposition_lattice

#define graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost (((u64)1) << 62)

void depth_first_search_visit(f2ptr cause, f2ptr this, f2ptr node_parent_hash, f2ptr used_hash, f2ptr *root_to_leaf_list) {  // For topological sort
  //printf("\n-->"); f2__print(cause, this);
  f2__ptypehash__add(cause, used_hash, this, 1);
  f2ptr lattice_node = f2__ptypehash__lookup(cause, node_parent_hash, this);
  if (lattice_node != nil) {
    f2ptr left_child_graph   = f2__graph_decomposition_lattice_node__left_child_graph( cause, lattice_node);
    f2ptr right_child_graph  = f2__graph_decomposition_lattice_node__right_child_graph(cause, lattice_node);
    if(f2__ptypehash__lookup(cause, used_hash, left_child_graph)  == nil)
      depth_first_search_visit(cause, left_child_graph, node_parent_hash, used_hash, root_to_leaf_list);
    if(f2__ptypehash__lookup(cause, used_hash, right_child_graph) == nil)
      depth_first_search_visit(cause, right_child_graph, node_parent_hash, used_hash, root_to_leaf_list);
  }
  *root_to_leaf_list = f2__cons__new(cause, this, *root_to_leaf_list);
}

f2ptr raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__cost(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr operations = f2__cons__car(cause, args);
  return f2__graph_edit_sequence__cost(cause, operations);
}

f2ptr raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__cost_compare(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args) {
  f2ptr cost_1 = f2__cons__car(cause, args);
  f2ptr cost_2 = f2__cons__car(cause, f2__cons__cdr(cause, args));
  if (f2__integer__eq(cause, cost_1, cost_2)) {
    return f2bool__new(cost_1 < cost_2);
  }
  return f2__integer__less_than(cause, cost_1, cost_2);
}

f2ptr raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph, f2ptr cost_function) {
  
  f2ptr value_cfunk = f2cfunk__new(cause, nil, 
				   f2list1__new(cause, new__symbol(cause, "x")),
				   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__cost)), global_environment(), nil, nil);
  
  f2ptr value_compare_cfunk = f2cfunk__new(cause, nil, 
					   f2list2__new(cause, new__symbol(cause, "x"), new__symbol(cause, "y")),
					   f2pointer__new(cause, raw_executable__to__relative_ptr(raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__cost_compare)), global_environment(), nil, nil);
  
  f2ptr graph_set             = f2__graph_decomposition_lattice__graph_set            (cause, this);
  //f2ptr node_set              = f2__graph_decomposition_lattice__node_set             (cause, this);
  f2ptr root_graph_set        = f2__graph_decomposition_lattice__root_graph_set       (cause, this);
  f2ptr node_parent_hash      = f2__graph_decomposition_lattice__node_parent_hash     (cause, this);
  f2ptr node_left_child_hash  = f2__graph_decomposition_lattice__node_left_child_hash (cause, this);
  f2ptr node_right_child_hash = f2__graph_decomposition_lattice__node_right_child_hash(cause, this);
  
  f2ptr unsolved_graph_set = f2__set__new(cause, nil);
  set__iteration(cause, graph_set, graph,
		 f2__set__add(cause, unsolved_graph_set, graph);
		 );
  
  f2ptr open_operations_rbt_hash   = f2__ptypehash__new(cause);   // rbt = redblacktree
  f2ptr closed_operations_rbt_hash = f2__ptypehash__new(cause);
  set__iteration(cause, graph_set, graph,
		 f2__ptypehash__add(cause, open_operations_rbt_hash,   graph, f2__redblacktree__new(cause, value_cfunk, value_compare_cfunk));
		 f2__ptypehash__add(cause, closed_operations_rbt_hash, graph, f2__redblacktree__new(cause, value_cfunk, value_compare_cfunk));
		 );

  f2ptr leaf_graph_set = f2__graph_decomposition_lattice__leaf_graph_set(cause, this);
  set__iteration(cause, leaf_graph_set, leaf_graph,
		 f2ptr leaf_graph__node_set = f2__graph__node_set(cause, leaf_graph);
		 f2ptr leaf_graph__node     = nil;
		 set__iteration(cause, leaf_graph__node_set, leaf_graph__node_set__node,
				leaf_graph__node = leaf_graph__node_set__node;
				);

		 f2ptr leaf_graph__open_operations_rbt = f2__ptypehash__lookup(cause, open_operations_rbt_hash, leaf_graph);
		 f2ptr graph__node_set = f2__graph__node_set(cause, graph);
		 //Add the change node edit
		 set__iteration(cause, graph__node_set, graph__node,
				f2ptr operations = f2__graph_edit_sequence__new(cause);
				if (f2__graph_node__label(cause, leaf_graph__node) != f2__graph_node__label(cause, graph__node)) {
				  f2__graph_edit_sequence__add(cause, operations, 
							     new__string(cause, "Change Node"), leaf_graph__node, graph__node, cost_function);
				}
				f2__graph_edit_sequence__add_mapping(cause, operations, leaf_graph__node, graph__node);
				f2__redblacktree__insert(cause, leaf_graph__open_operations_rbt, operations);
				);
		 //Add the delete node edit
		 f2ptr operations = f2__graph_edit_sequence__new(cause);
		 f2__graph_edit_sequence__add(cause, operations, new__string(cause, "Delete Node"), leaf_graph__node, nil, cost_function);
		 f2__redblacktree__insert(cause, leaf_graph__open_operations_rbt, operations);
		 );

  // Topologically sort the decomposed graphs -- will be used for heuristics
  //printf("Prepare to TopSort...\n");
  f2ptr used_hash         = f2__ptypehash__new(cause);
  f2ptr root_to_leaf_list = nil;
  set__iteration(cause, root_graph_set, root_graph, 
		 if (f2__ptypehash__lookup(cause, used_hash, root_graph) == nil) 
		   depth_first_search_visit(cause, root_graph, node_parent_hash, used_hash, &root_to_leaf_list);
		 );
  f2ptr leaf_to_root_revs = root_to_leaf_list;
  f2ptr leaf_to_root_list = nil;
  while (leaf_to_root_revs) {
    leaf_to_root_list = f2__cons__new(cause, f2__cons__car(cause, leaf_to_root_revs), leaf_to_root_list);
    leaf_to_root_revs = f2__cons__cdr(cause, leaf_to_root_revs);
  }
  //printf("TopSort Done!\n"); //f2__print(cause, leaf_to_root_list); f2__print(cause, root_to_leaf_list);

  u64 threshold = graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost;
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
      u64 c_open = graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost;
      f2ptr S_open_operations_rbt = f2__ptypehash__lookup(cause, open_operations_rbt_hash, current_S);
      f2ptr S_minimal_open_operations = f2__redblacktree__minimum(cause, S_open_operations_rbt);
      if (S_minimal_open_operations != nil) c_open = f2integer__i(f2__graph_edit_sequence__cost(cause, S_minimal_open_operations), cause);
      //u64 c_closed = graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost;
      f2ptr S_closed_operations_rbt = f2__ptypehash__lookup(cause, closed_operations_rbt_hash, current_S);
      //f2ptr S_minimal_closed_operations = f2__redblacktree__minimum(cause, S_closed_operations_rbt);
      //if (S_minimal_closed_operations != nil) {
      //	c_closed = f2integer__i(f2__graph_edit_sequence__cost(cause, S_minimal_closed_operations), cause);
      //}
      
      if (lattice_node == nil) {  // leaf
	f2__ptypehash__add(cause, n_hash, current_S, f2integer__new(cause, c_open));
      } else {
	f2ptr left_child_graph   = f2__graph_decomposition_lattice_node__left_child_graph( cause, lattice_node);
	f2ptr right_child_graph  = f2__graph_decomposition_lattice_node__right_child_graph(cause, lattice_node);
	u64 gl_nr = f2integer__i(f2__ptypehash__lookup(cause, g_hash, left_child_graph), cause) + f2integer__i(f2__ptypehash__lookup(cause, n_hash, right_child_graph), cause);
	if (c_open > gl_nr) c_open = gl_nr;
	u64 nl_gr = f2integer__i(f2__ptypehash__lookup(cause, n_hash, left_child_graph), cause) + f2integer__i(f2__ptypehash__lookup(cause, g_hash, right_child_graph), cause);
	if (c_open > nl_gr) c_open = nl_gr;
	f2__ptypehash__add(cause, n_hash, current_S, f2integer__new(cause, c_open));
      }
      if (raw__set__is_empty(cause, S_closed_operations_rbt))
	f2__ptypehash__add(cause, g_hash, current_S, f2integer__new(cause, c_open));
      else
	f2__ptypehash__add(cause, g_hash, current_S, f2integer__new(cause, f2integer__i(f2__ptypehash__lookup(cause, n_hash, current_S), cause)));
      //f2__print(cause, n_hash); f2__print(cause, g_hash);
    }
    //printf("N\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); f2__print(cause, f2__ptypehash__lookup(cause, n_hash, graph_s)););
    //printf("G\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); f2__print(cause, f2__ptypehash__lookup(cause, g_hash, graph_s)););
    
    // roots down
    // h(S) = min {g(S.sibling) + h(S.p)} over S.p
    f2ptr h_hash = f2__ptypehash__new(cause);
    f2ptr root_to_leaf_iter = root_to_leaf_list;
    f2ptr node_s = nil;
    while (root_to_leaf_iter) {
      f2ptr current_S   = f2__cons__car(cause, root_to_leaf_iter);
      //f2__print(cause, current_S);
      root_to_leaf_iter = f2__cons__cdr(cause, root_to_leaf_iter);

      if (f2__ptypehash__lookup(cause, root_graph_set, current_S) != nil) {
	f2__ptypehash__add(cause, h_hash, current_S, f2integer__new(cause, 0));
      } else {
	u64 min_h = graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost;
	node_s = f2__ptypehash__lookup(cause, node_left_child_hash, current_S);
	//f2__print(cause, node_s);
	if (node_s != nil) {
	  set__iteration(cause, node_s, lattice_node,
			 f2ptr parent_graph  = f2__graph_decomposition_lattice_node__parent_graph(cause, lattice_node);
			 f2ptr sibling_graph = f2__graph_decomposition_lattice_node__right_child_graph(cause, lattice_node);
			 u64 gs_hp = f2integer__i(f2__ptypehash__lookup(cause, g_hash, sibling_graph), cause) + f2integer__i(f2__ptypehash__lookup(cause, h_hash, parent_graph), cause);
			 if (gs_hp < min_h) min_h = gs_hp;
			 );
	}
	node_s = f2__ptypehash__lookup(cause, node_right_child_hash, current_S);
	if (node_s != nil) {
	  set__iteration(cause, node_s, lattice_node,
			 f2ptr parent_graph  = f2__graph_decomposition_lattice_node__parent_graph(cause, lattice_node);
			 f2ptr sibling_graph = f2__graph_decomposition_lattice_node__left_child_graph(cause, lattice_node);
			 u64 gs_hp = f2integer__i(f2__ptypehash__lookup(cause, g_hash, sibling_graph), cause) + f2integer__i(f2__ptypehash__lookup(cause, h_hash, parent_graph), cause);
			 if (gs_hp < min_h) min_h = gs_hp;
			 );
	}
	f2__ptypehash__add(cause, h_hash, current_S, f2integer__new(cause, min_h));
      }
    }
    //printf("H\n"); set__iteration(cause, graph_set, graph_s, f2__print(cause, graph_s); f2__print(cause, f2__ptypehash__lookup(cause, h_hash, graph_s)););
    
    u64 minimal_estimated_cost = graph_decomposition_lattice__error_correcting_subgraph_isomorphisms__maximum_possible_cost;
    f2ptr minimal_cost_graph = nil;
    f2ptr minimal_open_operations = nil;
    //Find S in D with minimal C[open(S)] + h(S)
    //set__iteration(cause, alive_graph_set, alive_graph,
    set__iteration(cause, unsolved_graph_set, alive_graph,
                   f2ptr alive_graph__open_operations_rbt = f2__ptypehash__lookup(cause, open_operations_rbt_hash, alive_graph);
                   f2ptr estimated_open_operations = f2__redblacktree__minimum(cause, alive_graph__open_operations_rbt);
                   if (estimated_open_operations) {
                     u64 estimated_cost = f2integer__i(f2__graph_edit_sequence__cost(cause, estimated_open_operations), cause)
                                        + f2integer__i(f2__ptypehash__lookup(cause, h_hash, alive_graph), cause);
                     if (estimated_cost < minimal_estimated_cost && estimated_cost <= threshold) {
                       minimal_estimated_cost = estimated_cost;
                       minimal_cost_graph = alive_graph;
                       minimal_open_operations = estimated_open_operations;
                     }
                   }
		   );
    if (minimal_cost_graph == nil) break;
    //printf("%d %d\n", minimal_cost_graph, minimal_estimated_cost);
    //f2__print(cause, minimal_cost_graph); 
    //Move the smallest edit sequence to closed(S)
    f2ptr minimal_cost_graph__open_operations_rbt   = f2__ptypehash__lookup(cause, open_operations_rbt_hash, minimal_cost_graph);
    f2ptr minimal_cost_graph__closed_operations_rbt = f2__ptypehash__lookup(cause, closed_operations_rbt_hash, minimal_cost_graph);
    f2__redblacktree__remove(cause, minimal_cost_graph__open_operations_rbt, minimal_open_operations);
    f2__redblacktree__insert(cause, minimal_cost_graph__closed_operations_rbt, minimal_open_operations);
    //Lessen the threshold
    if (f2__set__lookup(cause, root_graph_set, minimal_cost_graph) != nil) {
      threshold = minimal_estimated_cost; //f2integer__i(f2__graph_edit_sequence__cost(cause, minimal_open_operations), cause);
    }
    //Solve the larger graph
    set__iteration(cause, unsolved_graph_set, unsolved_graph,
		   f2ptr lattice_node       = f2__ptypehash__lookup(cause, node_parent_hash, unsolved_graph);
		   if (lattice_node != nil) {
		     f2ptr left_child_graph   = f2__graph_decomposition_lattice_node__left_child_graph( cause, lattice_node);
		     f2ptr right_child_graph  = f2__graph_decomposition_lattice_node__right_child_graph(cause, lattice_node);
		     //printf("##"); f2__print(cause, unsolved_graph); f2__print(cause, left_child_graph);
		     //f2__print(cause, right_child_graph); f2__print(cause, minimal_cost_graph); printf("##\n");
		     if (left_child_graph == minimal_cost_graph) {
		       //printf("L!\n");
		       f2ptr unsolved_graph__open_operations_rbt = f2__ptypehash__lookup(cause, open_operations_rbt_hash, unsolved_graph);
		       f2ptr right_child_graph__closed_operations_rbt = f2__ptypehash__lookup(cause, closed_operations_rbt_hash, right_child_graph);
		       redblacktree__iteration(cause, right_child_graph__closed_operations_rbt, right_child_graph__closed_operations,
                                               f2ptr combined_operations = f2__graph_edit_sequence__combine(cause, minimal_open_operations, 
                                                                                                             right_child_graph__closed_operations,
                                                                                                             lattice_node, graph, cost_function);
                                               if (combined_operations != nil) {
                                                 f2__redblacktree__insert(cause, unsolved_graph__open_operations_rbt, combined_operations);
                                               }
                                               );
		     } else if (right_child_graph == minimal_cost_graph) {
		       //printf("R!\n");
		       f2ptr unsolved_graph__open_operations_rbt = f2__ptypehash__lookup(cause, open_operations_rbt_hash, unsolved_graph);
		       f2ptr left_child_graph__closed_operations_rbt = f2__ptypehash__lookup(cause, closed_operations_rbt_hash, left_child_graph);
		       redblacktree__iteration(cause, left_child_graph__closed_operations_rbt, left_child_graph__closed_operations,
                                               f2ptr combined_operations = f2__graph_edit_sequence__combine(cause, minimal_open_operations, 
                                                                                                             left_child_graph__closed_operations,
                                                                                                             lattice_node, graph, cost_function);
                                               if (combined_operations != nil) {
                                                 f2__redblacktree__insert(cause, unsolved_graph__open_operations_rbt, combined_operations);
                                               }
                                               );
		     }
		   }
		   );
  }
  //Output stuff -- fix later
  f2ptr answer = f2__ptypehash__new(cause);
  set__iteration(cause, root_graph_set, root_graph, 
                 f2ptr closed_operations_rbt = f2__ptypehash__lookup(cause, closed_operations_rbt_hash, root_graph);
		 if (closed_operations_rbt != nil) {
		   f2ptr best_match = f2__redblacktree__minimum(cause, closed_operations_rbt);
		   if (raw__larva__is_type(cause, best_match)) {
		     return best_match;
		   }
		   f2__ptypehash__add(cause, answer, root_graph, best_match);
		 }
		 );
  return answer;
}

f2ptr f2__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph, f2ptr cost_function) {
  assert_argument_type(       graph_decomposition_lattice, this);
  assert_argument_type(       graph,                       graph);
  assert_argument_type_or_nil(funkable,                    cost_function);
  return raw__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(cause, this, graph, cost_function);
}
def_pcfunk3(graph_decomposition_lattice__error_correcting_subgraph_isomorphisms, this, graph, cost_function,
	    "",
	    return f2__graph_decomposition_lattice__error_correcting_subgraph_isomorphisms(this_cause, this, graph, cost_function));


// **

void f2__graph_match_error_correcting__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // graph_edit_sequence
  initialize_primobject_3_slot__defragment__fix_pointers(graph_edit_sequence, operations, cost, isomorphism);
  //f2__primcfunk__init__defragment__fix_pointers(graph_edit_sequence__new);
  f2__primcfunk__init__defragment__fix_pointers(graph_edit_sequence__add);
  f2__primcfunk__init__defragment__fix_pointers(graph_edit_sequence__add_mapping);
  f2__primcfunk__init__defragment__fix_pointers(graph_edit_sequence__combine);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_edit_sequence.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_edit_sequence__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_edit_sequence.terminal_print_with_frame__funk);
  
  // graph_decomposition_lattice
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__error_correcting_subgraph_isomorphisms);
}

void f2__graph_match_error_correcting__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // graph_edit_sequence
  initialize_primobject_3_slot(graph_edit_sequence, operations, cost, isomorphism);
  f2__primcfunk__init__0(graph_edit_sequence__new);
  f2__primcfunk__init__5(graph_edit_sequence__add, this, type, from, to, cost_function);
  f2__primcfunk__init__3(graph_edit_sequence__add_mapping, this, left_node, right_node);
  f2__primcfunk__init__5(graph_edit_sequence__combine, this, that, lattice_node, graph, cost_function);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_edit_sequence.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_edit_sequence__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_edit_sequence.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph_decomposition_lattice
  f2__primcfunk__init__3(graph_decomposition_lattice__error_correcting_subgraph_isomorphisms, this, graph, cost_function);
}

void f2__graph_match_error_correcting__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_match_error_correcting", "", &f2__graph_match_error_correcting__reinitialize_globalvars, &f2__graph_match_error_correcting__defragment__fix_pointers);
  
  f2__graph_match_error_correcting__reinitialize_globalvars();
}

