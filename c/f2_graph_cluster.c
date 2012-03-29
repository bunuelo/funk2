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

f2ptr raw__graph__distances_from_node(f2ptr cause, f2ptr this, f2ptr start_node) {
  f2ptr  distances_hash = f2__ptypehash__new(cause);
  u64    node_count     = raw__graph__node_count(cause, this);
  f2ptr* node_queue     = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  u64    queue_front    = 0,  queue_back = 0;
  f2__ptypehash__add(cause, distances_hash, start_node, 1);
  node_queue[queue_back++] = start_node;
  f2ptr current_node;
  while (queue_front < queue_back) {
    current_node = node_queue[queue_front++];
    u64 current_distance = f2__ptypehash__lookup(cause, distances_hash, current_node);
    f2ptr hash_from_current_node           = f2__graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
    f2ptr edges_label_hash_right_node_hash = f2__ptypehash__lookup(cause, hash_from_current_node, current_node);
    if (edges_label_hash_right_node_hash != nil) {
      ptypehash__keyvalue_pair__iteration
	(cause, edges_label_hash_right_node_hash, pair__right_node__edges_label_hash,
	 f2ptr right_node = f2__cons__car(cause, pair__right_node__edges_label_hash);
	 if(f2__ptypehash__lookup(cause, distances_hash, right_node) == nil) {
	   f2__ptypehash__add(cause, distances_hash, right_node, current_distance + 1);
	   node_queue[queue_back++] = right_node;
	 }
	 );
    }
    f2ptr hash_to_current_node            = f2__graph__edges_label_hash_left_node_hash_right_node_hash(cause, this);
    f2ptr edges_label_hash_left_node_hash = f2__ptypehash__lookup(cause, hash_to_current_node, current_node);
    if(edges_label_hash_left_node_hash != nil) {
      ptypehash__keyvalue_pair__iteration
	(cause, edges_label_hash_left_node_hash, pair__left_node__edges_label_hash,
	 f2ptr left_node = f2__cons__car(cause, pair__left_node__edges_label_hash);
	 if(f2__ptypehash__lookup(cause, distances_hash, left_node) == nil) {
	   f2__ptypehash__add(cause, distances_hash, left_node, current_distance + 1);
	   node_queue[queue_back++] = left_node;
	 }
	 );
    }
  }
  return f2__cons__new(cause, distances_hash, current_node);
}

f2ptr raw__graph__cluster(f2ptr cause, f2ptr this) {
  f2ptr graph      = f2__graph__new(cause);
  u64   node_count = raw__graph__node_count(cause, this);
  f2ptr node_set   = f2__graph__node_set(cause, this);
  f2ptr edge_set   = f2__graph__edge_set(cause, this);
  f2ptr node_a     = nil;
  set__iteration(cause, node_set, node, node_a = node; break; );
  f2ptr pair__distances_from_a__node_b = raw__graph__distances_from_node(cause, this, node_a);
  f2ptr distances_from_a               = f2__cons__car(cause, pair__distances_from_a__node_b);
  f2ptr node_b                         = f2__cons__cdr(cause, pair__distances_from_a__node_b);
  if (f2integer__i(f2__ptypehash__key_count(cause, distances_from_a), cause) < node_count) {
    ptypehash__keyvalue_pair__iteration
      (cause, distances_from_a, pair_node_distance,
       f2__graph__add_node(cause, graph, f2__cons__car(cause, pair_node_distance));
       );
  }
  else {
    f2ptr distances_from_b = f2__cons__car(cause, raw__graph__distances_from_node(cause, this, node_b));
    set__iteration(cause, node_set, node,
		   if(f2__ptypehash__lookup(cause, distances_from_a, node) < f2__ptypehash__lookup(cause, distances_from_b, node)) {
			f2__graph__add_node(cause, graph, node);
		   }
		   );
  }
  set__iteration(cause, edge_set, edge,
		 f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
		 f2ptr right_node = f2__graph_edge__right_node(cause, edge);
		 if (raw__graph__contains_node(cause, graph, left_node) &&
		     raw__graph__contains_node(cause, graph, right_node)) {
		   raw__graph__add_edge(cause, graph, edge);
		 }
		 );
  return graph;  
}

f2ptr f2__graph__cluster(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  if (raw__graph__node_count(cause, this) < 2) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "graph_must_have_at_least_two_nodes"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "graph-cluster"));
    return f2larva__new(cause, 342, f2__bug__new(cause, f2integer__new(cause, 342), bug_frame));
  }
  return raw__graph__cluster(cause, this);
}
def_pcfunk1(graph__cluster, this,
	    "Cluster this graph.",
	    return f2__graph__cluster(this_cause, this));

// **

void f2__graph_cluster__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(graph__cluster);
}

void f2__graph_cluster__reinitialize_globalvars() {
  f2__primcfunk__init__1(graph__cluster, this);
}

void f2__graph_cluster__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph_cluster", "", &f2__graph_cluster__reinitialize_globalvars, &f2__graph_cluster__defragment__fix_pointers);
  
  f2__graph_cluster__reinitialize_globalvars();
}

