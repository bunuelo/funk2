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

f2ptr raw__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  f2ptr  graph        = f2__bruno_graph__new(cause);
  f2ptr  unused_nodes = f2__bruno_graph__node_set(cause, this);
  u64    node_count   = raw__bruno_graph__node_count(cause, this);
  f2ptr* node_queue   = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  u64    queue_front  = 0, queue_back = 0;
  { //chose 2 nodes at random
    set__iteration(cause, unused_nodes, node,
		   node_queue[queue_back] = node;
		   queue_back++;
		   if (queue_back >= 2) break;
		   );
    f2__set__remove(cause, unused_nodes, node_queue[0]);
    f2__set__remove(cause, unused_nodes, node_queue[1]);
    f2__bruno_graph__add_node(cause, graph, node_queue[0]);
  }
  { //BFS
    while(queue_front < queue_back) {
      f2ptr current_node = node_queue[queue_front];
      queue_front++;
      f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__bruno_graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
      if (edges_label_hash_right_node_hash_left_node_hash == nil) continue;
      f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, current_node);
      if (edges_label_hash_right_node_hash == nil) continue;
      ptypehash__keyvalue_pair__iteration
	(cause, edges_label_hash_right_node_hash, pair_right_node_edges_label_hash,
	 {
	   f2ptr right_node       = f2__cons__car(cause, pair_right_node_edges_label_hash);
	   f2ptr edges_label_hash = f2__cons__cdr(cause, pair_right_node_edges_label_hash);
	   if (edges_label_hash == nil) continue;
	   ptypehash__keyvalue_pair__iteration
	     (cause, edges_label_hash, pair_edge_label_edges,
	      {
		f2ptr edges = f2__cons__cdr(cause, pair_edge_label_edges);
		while (edges) {
		  f2ptr edge = f2__cons__car(cause, edges);
		  if (f2__ptypehash__lookup(cause, unused_nodes, right_node)) {
		    f2__set__remove(cause, unused_nodes, right_node);
		    node_queue[queue_back] = right_node;
		    queue_back++;
		    if (f2__bruno_graph__contains_node(cause, graph, current_node)) {
		      raw__bruno_graph__add_node(cause, graph, right_node);
		      raw__bruno_graph__add_edge(cause, graph, edge);
		    }
		  }
		  else if (raw__bruno_graph__contains_node(cause, graph, right_node) &&
			   raw__bruno_graph__contains_node(cause, graph, current_node)) {
		    raw__bruno_graph__add_edge(cause, graph, edge);
		  }
		  edges = f2__cons__cdr(cause, edges);
		}
	      }
	      );
	 }
	 );
    }
  }
  return graph;
}

f2ptr f2__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__cluster(cause, this);
}
def_pcfunk1(bruno_graph__cluster, this, return f2__bruno_graph__cluster(this_cause, this));

// **

void f2__graph_cluster__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_cluster", "", &f2__graph_cluster__reinitialize_globalvars);
  
  //f2ptr cause = initial_cause();
}

void f2__graph_cluster__initialize() {
  f2__graph_cluster__reinitialize_globalvars();
  //f2ptr cause = initial_cause();
  
  f2__primcfunk__init__1(bruno_graph__cluster, this, "Cluster this bruno_graph.");
}

