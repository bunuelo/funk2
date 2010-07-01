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
/*
f2ptr raw__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  f2ptr  graph        = f2__bruno_graph__new(cause);
  f2ptr  node_set     = f2__bruno_graph__node_set(cause, this);
  f2ptr  unused_nodes = f2__set__new(cause);
  u64    node_count   = raw__bruno_graph__node_count(cause, this);
  f2ptr* node_queue   = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  u64    queue_front  = 0, queue_back = 0;
  { //chose 2 nodes at random
    set__iteration(cause, node_set, node, f2__set__add(cause, unused_nodes, node); );
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
		  if (f2__set__lookup(cause, unused_nodes, right_node) != nil) {
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
*/

f2ptr raw__graph__distances_from_node(f2ptr cause, f2ptr graph, f2ptr start_node) {
  f2ptr  distances_hash = f2__ptypehash__new(cause);
  u64    node_count     = graph__node_count(cause, graph);
  f2ptr* node_queue     = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  u64    queue_front    = 0,  queue_back = 0;
  f2__ptypehash__add(cause, distances_hash, start_node, 1);
  node_queue[queue_back++] = start_node;
  f2ptr current_node;
  while (queue_front < queue_back) {
    current_node = node_queue[queue_front++];
    u64 current_distance = f2__ptypehash__lookup(cause, distances_hash, current_node);
    f2ptr current_graph_node = f2__graph__lookup_node (cause, graph, current_node);
    graph_node__out_edge__iteration
      (cause, current_graph_node, edge,
       f2ptr right_graph_node = f2__graph_edge__right_node(cause, edge);
       f2ptr right_node       = f2__graph_edge__label(cause, right_graph_node);
       if (f2__ptypehash__lookup(cause, distances_hash, right_node) == nil) {
	 f2__ptypehash__add(cause, distances_hash, right_node, current_distance + 1);
	 node_queue[queue_back++] = right_node;
       }
       );
  }
  return f2__cons__new(cause, distances_hash, current_node);
}

f2ptr raw__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  f2ptr graph      = f2__bruno_graph__new(cause);
  f2ptr temp_graph = f2__graph__new(cause);
  u64   node_count = raw__bruno_graph__node_count(cause, this);
  f2ptr node_set   = f2__bruno_graph__node_set(cause, this);
  f2ptr edge_set   = f2__bruno_graph__edge_set(cause, this);
  set__iteration(cause, node_set, node, f2__graph__add_node(cause, temp_graph, node));
  set__iteration(cause, edge_set, edge,
		 f2ptr left_node  = f2__bruno_graph_edge__left_node(cause, edge);
		 f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
		 if (f2__graph__contains_edge(cause, temp_graph, 0, left_node, right_node) == nil) {
		   f2__graph__add_edge(cause, temp_graph, 0, left_node, right_node);
		   f2__graph__add_edge(cause, temp_graph, 0, right_node, left_node);
		 }
		 );
  f2ptr node_a;
  set__iteration(cause, node_set, node, node_a = node; break; );
  f2ptr pair_distances_from_a_node_b = raw__graph__distances_from_node(cause, temp_graph, node_a);
  f2ptr distances_from_a             = f2__cons__car(cause, pair_distances_from_a_node_b);
  f2ptr node_b                       = f2__cons__cdr(cause, pair_distances_from_a_node_b);
  if (f2integer__i(f2__ptypehash__key_count(cause, distances_from_a), cause) < node_count) {
    ptypehash__keyvalue_pair__iteration
      (cause, distances_from_a, pair_node_distance,
       f2__bruno_graph__add_node(cause, graph, f2__cons__car(cause, pair_node_distance));
       );
  }
  else {
    f2ptr distances_from_b = f2__cons__car(cause, raw__graph__distances_from_node(cause, temp_graph, node_b));
    set__iteration(cause, node_set, node,
		   if(f2__ptypehash__lookup(cause, distances_from_a, node) < f2__ptypehash__lookup(cause, distances_from_b, node)) {
			f2__bruno_graph__add_node(cause, graph, node);
		   }
		   );
  }
  set__iteration(cause, edge_set, edge,
		 f2ptr left_node  = f2__bruno_graph_edge__left_node(cause, edge);
		 f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
		 if (raw__bruno_graph__contains_node(cause, graph, left_node) &&
		     raw__bruno_graph__contains_node(cause, graph, right_node)) {
		   raw__bruno_graph__add_edge(cause, graph, edge);
		 }
		 );
  return graph;
  
}

f2ptr f2__bruno_graph__cluster(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  if (raw__bruno_graph__node_count(cause, this) < 2) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "bruno_graph_must_have_at_least_two_nodes"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "bruno_graph-cluster"));
    return f2larva__new(cause, 342, f2__bug__new(cause, f2integer__new(cause, 342), bug_frame));
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

