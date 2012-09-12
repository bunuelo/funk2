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

//#########################################################################
//
// This algorithm for Subgraph Isomorphism Detection
//  comes from the thesis by Bruno T. Messmer:
//   http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.33.4206
// 
// See also f2_graph_match_error_correcting.c for an approximate
// version of this lattice-based graph matching algorithm also
// developed by Messmer.
//
//#########################################################################

// graph_node

def_primobject_1_slot(graph_node, label);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label) {
  return f2graph_node__new(cause, label);
}
def_pcfunk1(graph_node__new, label,
	    "",
	    return f2__graph_node__new(this_cause, label));


f2ptr raw__graph_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_node"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "label"),             f2__graph_node__label(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_node,           this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__graph_node__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_node__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_node__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr raw__graph_node__as__dot_code(f2ptr cause, f2ptr this) {
  f2ptr color = f2__graphviz__exp__as__color(cause, this);
  if (color == nil) {
    color = new__string(cause, "#000000");
  }
  f2ptr label     = f2__graph_node__label(cause, this);
  f2ptr node_code = f2__graphviz__node(cause, f2__graphviz__exp__as__name(cause, this), f2__graphviz__exp__as__label(cause, label), color);
  return node_code;
}


f2ptr f2graph_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_node__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_node.terminal_print_with_frame__funk);}
  return this;
}


// graph_edge

def_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(graph_edge__new, label, left_node, right_node,
	    "",
	    return f2__graph_edge__new(this_cause, label, left_node, right_node));


f2ptr raw__graph_edge__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_edge"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "label"),             f2__graph_edge__label(     cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "left_node"),         f2__graph_edge__left_node( cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "right_node"),        f2__graph_edge__right_node(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_edge__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_edge,           this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__graph_edge__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_edge__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_edge__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr raw__graph_edge__as__dot_code(f2ptr cause, f2ptr this) {
  f2ptr this__label      = f2__graph_edge__label(cause, this);
  f2ptr this__left_node  = f2__graph_edge__left_node(cause, this);
  f2ptr this__right_node = f2__graph_edge__right_node(cause, this);
  f2ptr edge_code        = f2__graphviz__raw_labelled_edge(cause, this__label, f2__graphviz__exp__as__name(cause, this__left_node), f2__graphviz__exp__as__name(cause, this__right_node), nil);
  return edge_code;
}



f2ptr f2graph_edge__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_edge__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_edge.terminal_print_with_frame__funk);}
  return this;
}


// graph

def_primobject_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);

f2ptr f2__graph__new(f2ptr cause) {
  f2ptr node_set                                        = f2__set__new(cause);
  f2ptr edge_set                                        = f2__set__new(cause);
  f2ptr nodes_label_hash                                = f2__ptypehash__new(cause);
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__ptypehash__new(cause);
  f2ptr edges_label_hash_left_node_hash_right_node_hash = f2__ptypehash__new(cause);
  return f2graph__new(cause, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);
}
def_pcfunk0(graph__new,
	    "",
	    return f2__graph__new(this_cause));


f2ptr raw__graph__nodes(f2ptr cause, f2ptr this) {
  f2ptr node_set = f2__graph__node_set(cause, this);
  f2ptr nodes    = raw__set__elements(cause, node_set);
  return nodes;
}

f2ptr f2__graph__nodes(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return raw__graph__nodes(cause, this);
}
def_pcfunk1(graph__nodes, this,
	    "Returns the nodes in this graph.",
	    return f2__graph__nodes(this_cause, this));


f2ptr raw__graph__edges(f2ptr cause, f2ptr this) {
  f2ptr edge_set = f2__graph__edge_set(cause, this);
  f2ptr edges    = raw__set__elements(cause, edge_set);
  return edges;
}

f2ptr f2__graph__edges(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return raw__graph__edges(cause, this);
}
def_pcfunk1(graph__edges, this,
	    "Returns the edges in this graph.",
	    return f2__graph__edges(this_cause, this));


f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set = f2__graph__node_set(cause, this);
  f2ptr already_contains_node = f2__set__add(cause, node_set, node);
  if (already_contains_node == nil) {
    f2ptr nodes_label_hash = f2__graph__nodes_label_hash(cause, this);
    f2ptr node_label       = f2__graph_node__label(cause, node);
    f2__ptypehash__add(cause, nodes_label_hash, node_label, raw__cons__new(cause, node, f2__ptypehash__lookup(cause, nodes_label_hash, node_label)));
  }
  return already_contains_node;
}

f2ptr f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, node);
  return raw__graph__add_node(cause, this, node);
}
def_pcfunk2(graph__add_node, this, node,
	    "Add a graph_node to this graph.",
	    return f2__graph__add_node(this_cause, this, node));

f2ptr raw__graph__add_new_node(f2ptr cause, f2ptr this, f2ptr label) {
  f2ptr node = f2__graph_node__new(cause, label);
  return raw__graph__add_node(cause, this, node);
}

f2ptr f2__graph__add_new_node(f2ptr cause, f2ptr this, f2ptr label) {
  assert_argument_type(graph, this);
  return raw__graph__add_new_node(cause, this, label);
}
def_pcfunk2(graph__add_new_node, this, label,
	    "Add a new graph_node to this graph.",
	    return f2__graph__add_new_node(this_cause, this, label));


f2ptr raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  f2ptr edge_set              = f2__graph__edge_set(cause, this);
  f2ptr already_contains_edge = f2__set__add(cause, edge_set, edge);
  if (already_contains_edge == nil) {
    f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
    f2ptr right_node = f2__graph_edge__right_node(cause, edge);
    f2ptr label      = f2__graph_edge__label(     cause, edge);
    f2__graph__add_node(cause, this, left_node);
    f2__graph__add_node(cause, this, right_node);
    {
      f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
      f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, left_node);
      if (edges_label_hash_right_node_hash == nil) {
	edges_label_hash_right_node_hash = f2__ptypehash__new(cause);
	f2__ptypehash__add(cause, edges_label_hash_right_node_hash_left_node_hash, left_node, edges_label_hash_right_node_hash);
      }
      f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash, right_node);
      if (edges_label_hash == nil) {
	edges_label_hash = f2__ptypehash__new(cause);
	f2__ptypehash__add(cause, edges_label_hash_right_node_hash, right_node, edges_label_hash);
      }
      f2ptr edges = f2__ptypehash__lookup(cause, edges_label_hash, label);
      f2__ptypehash__add(cause, edges_label_hash, label, raw__cons__new(cause, edge, edges));
    }
    {
      f2ptr edges_label_hash_left_node_hash_right_node_hash = f2__graph__edges_label_hash_left_node_hash_right_node_hash(cause, this);
      f2ptr edges_label_hash_left_node_hash                 = f2__ptypehash__lookup(cause, edges_label_hash_left_node_hash_right_node_hash, right_node);
      if (edges_label_hash_left_node_hash == nil) {
	edges_label_hash_left_node_hash = f2__ptypehash__new(cause);
	f2__ptypehash__add(cause, edges_label_hash_left_node_hash_right_node_hash, right_node, edges_label_hash_left_node_hash);
      }
      f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_left_node_hash, left_node);
      if (edges_label_hash == nil) {
	edges_label_hash = f2__ptypehash__new(cause);
	f2__ptypehash__add(cause, edges_label_hash_left_node_hash, left_node, edges_label_hash);
      }
      f2ptr edges = f2__ptypehash__lookup(cause, edges_label_hash, label);
      f2__ptypehash__add(cause, edges_label_hash, label, raw__cons__new(cause, edge, edges));
    }
  }
  return already_contains_edge;
}

f2ptr f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_edge, edge);
  return raw__graph__add_edge(cause, this, edge);
}
def_pcfunk2(graph__add_edge, this, edge,
	    "Add a graph_edge to this graph.",
	    return f2__graph__add_edge(this_cause, this, edge));

f2ptr raw__graph__add_new_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge = f2__graph_edge__new(cause, label, left_node, right_node);
  return raw__graph__add_edge(cause, this, edge);
}

f2ptr f2__graph__add_new_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, left_node);
  assert_argument_type(graph_node, right_node);
  return raw__graph__add_new_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(graph__add_new_edge, this, label, left_node, right_node,
	    "Add a new graph_edge between two graph_nodes to this graph.",
	    return f2__graph__add_new_edge(this_cause, this, label, left_node, right_node));

u64 raw__graph__node_count(f2ptr cause, f2ptr this) {
  f2ptr node_set            = f2__graph__node_set(cause, this);
  f2ptr node_set__key_count = f2__set__key_count(cause, node_set);
  return f2integer__i(node_set__key_count, cause);
}

f2ptr f2__graph__node_count(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  f2ptr node_set = f2__graph__node_set(cause, this);
  return f2__set__key_count(cause, node_set);
}
def_pcfunk1(graph__node_count, this,
	    "Returns the number of nodes in this graph.",
	    return f2__graph__node_count(this_cause, this));

boolean_t raw__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set = f2__graph__node_set(cause, this);
  return raw__set__contains(cause, node_set, node);
}

f2ptr f2__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, node);
  return f2bool__new(raw__graph__contains_node(cause, this, node));
}
def_pcfunk2(graph__contains_node, this, node,
	    "Returns true if this graph contains a graph_node.",
	    return f2__graph__contains_node(this_cause, this, node));


f2ptr raw__graph__nodes_with_label(f2ptr cause, f2ptr this, f2ptr label) {
  f2ptr nodes_label_hash = f2__graph__nodes_label_hash(cause, this);
  return raw__ptypehash__lookup(cause, nodes_label_hash, label);
}

f2ptr f2__graph__nodes_with_label(f2ptr cause, f2ptr this, f2ptr label) {
  assert_argument_type(graph, this);
  return raw__graph__nodes_with_label(cause, this, label);
}
def_pcfunk2(graph__nodes_with_label, this, label,
	    "Returns the list of nodes with this label.",
	    return f2__graph__nodes_with_label(this_cause, this, label));


boolean_t raw__graph__contains_node_label(f2ptr cause, f2ptr this, f2ptr label) {
  return (raw__graph__nodes_with_label(cause, this, label) != nil);
}

f2ptr f2__graph__contains_node_label(f2ptr cause, f2ptr this, f2ptr label) {
  assert_argument_type(graph, this);
  return f2bool__new(raw__graph__contains_node_label(cause, this, label));
}
def_pcfunk2(graph__contains_node_label, this, label,
	    "Returns whether or not a node within this graph has this label.",
	    return f2__graph__contains_node_label(this_cause, this, label));


boolean_t raw__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  f2ptr edge_set = f2__graph__edge_set(cause, this);
  return raw__set__contains(cause, edge_set, edge);
}

f2ptr f2__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_edge, edge);
  return f2bool__new(raw__graph__contains_edge(cause, this, edge));
}
def_pcfunk2(graph__contains_edge, this, edge,
	    "Returns true if this graph contains a graph_edge.",
	    return f2__graph__contains_edge(this_cause, this, edge));


boolean_t raw__graph__contains(f2ptr cause, f2ptr this, f2ptr graph) {
  {
    f2ptr graph__node_set = f2__graph__node_set(cause, graph);
    set__iteration(cause, graph__node_set, node,
		   if (! raw__graph__contains_node(cause, this, node)) {
		     return boolean__false;
		   }
		   );
  }
  {
    f2ptr graph__edge_set = f2__graph__edge_set(cause, graph);
    set__iteration(cause, graph__edge_set, edge,
		   if (! raw__graph__contains_edge(cause, this, edge)) {
		     return boolean__false;
		   }
		   );
  }
  return boolean__true;
}

f2ptr f2__graph__contains(f2ptr cause, f2ptr this, f2ptr graph) {
  assert_argument_type(graph, this);
  assert_argument_type(graph, graph);
  return f2bool__new(raw__graph__contains(cause, this, graph));
}
def_pcfunk2(graph__contains, this, graph,
	    "Returns true if this graph contains a graph as a subgraph.",
	    return f2__graph__contains(this_cause, this, graph));


f2ptr raw__graph__lookup_nodes_with_label(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr nodes_label_hash = f2__graph__nodes_label_hash(cause, this);
  return raw__ptypehash__lookup(cause, nodes_label_hash, node_label);
}

f2ptr f2__graph__lookup_nodes_with_label(f2ptr cause, f2ptr this, f2ptr node_label) {
  assert_argument_type(graph, this);
  return raw__graph__lookup_nodes_with_label(cause, this, node_label);
}
def_pcfunk2(graph__lookup_nodes_with_label, this, node_label,
	    "Returns the list of all nodes with the given label in this graph.",
	    return f2__graph__lookup_nodes_with_label(this_cause, this, node_label));



// assumes this is graph and has at least 2 nodes.
f2ptr raw__graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this) {
  f2ptr  graph      = f2__graph__new(cause);
  u64    node_count = raw__graph__node_count(cause, this);
  f2ptr* node_array = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  {
    f2ptr node_set = f2__graph__node_set(cause, this);
    {
      u64 index = 0;
      set__iteration(cause, node_set, node,
		     node_array[index] = node;
		     index ++;
		     );
    }
  }
  u64 subgraph_node_count   = node_count >> 1;
  u64 nodes_count_remaining = node_count;
  {
    s64 index = subgraph_node_count;
    while (index > 0) {
      f2ptr random_node;
      {
	u64 random_index                      = raw__random(nodes_count_remaining);
	random_node                           = node_array[random_index];
	node_array[random_index]              = node_array[nodes_count_remaining - 1];
	node_array[nodes_count_remaining - 1] = nil;
      }
      f2__graph__add_node(cause, graph, random_node);
      index                 --;
      nodes_count_remaining --;
    }
  }
  {
    f2ptr edge_set = f2__graph__edge_set(cause, this);
    set__iteration(cause, edge_set, edge,
		   f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
		   f2ptr right_node = f2__graph_edge__right_node(cause, edge);
		   if (raw__graph__contains_node(cause, graph, left_node) &&
		       raw__graph__contains_node(cause, graph, right_node)) {
		     raw__graph__add_edge(cause, graph, edge);
		   }
		   );
  }
  return graph;
}

f2ptr f2__graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  if (raw__graph__node_count(cause, this) < 2) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "graph_must_have_at_least_two_nodes"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "graph-random_nonempty_strict_subgraph"));
    return f2larva__new(cause, 342, f2__bug__new(cause, f2integer__new(cause, 342), bug_frame));
  }
  return raw__graph__random_nonempty_strict_subgraph(cause, this);
}
def_pcfunk1(graph__random_nonempty_strict_subgraph, this,
	    "When this graph contains N nodes, returns a random subgraph with N/2 nodes.  This graph must have at least 2 nodes.",
	    return f2__graph__random_nonempty_strict_subgraph(this_cause, this));

f2ptr raw__graph__minus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  {
    f2ptr this__node_set = f2__graph__node_set(cause, this);
    set__iteration(cause, this__node_set, node,
		   if (! raw__graph__contains_node(cause, that, node)) {
		     f2__graph__add_node(cause, graph, node);
		   }
		   );
  }
  {
    f2ptr this__edge_set = f2__graph__edge_set(cause, this);
    set__iteration(cause, this__edge_set, edge,
		   f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
		   f2ptr right_node = f2__graph_edge__right_node(cause, edge);
		   if (raw__graph__contains_node(cause, graph, left_node) &&
		       raw__graph__contains_node(cause, graph, right_node)) {
		     f2__graph__add_edge(cause, graph, edge);
		   }
		   );
  }
  return graph;
}

f2ptr f2__graph__minus(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(graph, this);
  assert_argument_type(graph, that);
  return raw__graph__minus(cause, this, that);
}
def_pcfunk2(graph__minus, this, that,
	    "Returns a subgraph of this graph without the nodes in that graph.",
	    return f2__graph__minus(this_cause, this, that));


f2ptr raw__graph__copy(f2ptr cause, f2ptr this) {
  f2ptr graph = f2__graph__new(cause);
  {
    f2ptr new_node_old_node_ptypehash = f2__ptypehash__new(cause);
    {
      f2ptr this__node_set = f2__graph__node_set(cause, this);
      set__iteration(cause, this__node_set, old_node,
		     f2ptr node_label = f2__graph_node__label(cause, old_node);
		     f2ptr new_node   = f2__graph_node__new(cause, node_label);
		     raw__ptypehash__add(cause, new_node_old_node_ptypehash, old_node, new_node);
		     f2__graph__add_node(cause, graph, new_node);
		     );
    }
    {
      f2ptr this__edge_set = f2__graph__edge_set(cause, this);
      set__iteration(cause, this__edge_set, old_edge,
		     f2ptr edge_label     = f2__graph_edge__label(     cause, old_edge);
		     f2ptr old_left_node  = f2__graph_edge__left_node( cause, old_edge);
		     f2ptr old_right_node = f2__graph_edge__right_node(cause, old_edge);
		     f2ptr new_left_node  = raw__ptypehash__lookup(cause, new_node_old_node_ptypehash, old_left_node);
		     f2ptr new_right_node = raw__ptypehash__lookup(cause, new_node_old_node_ptypehash, old_right_node);
		     f2ptr new_edge       = f2__graph_edge__new(cause, edge_label, new_left_node, new_right_node);
		     f2__graph__add_edge(cause, graph, new_edge);
		     );
    }
  }
  return graph;
}

f2ptr f2__graph__copy(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return raw__graph__copy(cause, this);
}
def_pcfunk1(graph__copy, this,
	    "Returns a new graph that is a copy of this graph.",
	    return f2__graph__copy(this_cause, this));


f2ptr raw__graph__copy_with_node_label(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr graph = f2__graph__new(cause);
  {
    f2ptr new_node_old_node_ptypehash = f2__ptypehash__new(cause);
    {
      f2ptr this__node_set = f2__graph__node_set(cause, this);
      set__iteration(cause, this__node_set, old_node,
		     f2ptr new_node = f2__graph_node__new(cause, node_label);
		     raw__ptypehash__add(cause, new_node_old_node_ptypehash, old_node, new_node);
		     f2__graph__add_node(cause, graph, new_node);
		     );
    }
    {
      f2ptr this__edge_set = f2__graph__edge_set(cause, this);
      set__iteration(cause, this__edge_set, old_edge,
		     f2ptr edge_label     = f2__graph_edge__label(     cause, old_edge);
		     f2ptr old_left_node  = f2__graph_edge__left_node( cause, old_edge);
		     f2ptr old_right_node = f2__graph_edge__right_node(cause, old_edge);
		     f2ptr new_left_node  = raw__ptypehash__lookup(cause, new_node_old_node_ptypehash, old_left_node);
		     f2ptr new_right_node = raw__ptypehash__lookup(cause, new_node_old_node_ptypehash, old_right_node);
		     f2ptr new_edge       = f2__graph_edge__new(cause, edge_label, new_left_node, new_right_node);
		     f2__graph__add_edge(cause, graph, new_edge);
		     );
    }
  }
  return graph;
}

f2ptr f2__graph__copy_with_node_label(f2ptr cause, f2ptr this, f2ptr node_label) {
  assert_argument_type(graph, this);
  return raw__graph__copy_with_node_label(cause, this, node_label);
}
def_pcfunk2(graph__copy_with_node_label, this, node_label,
	    "",
	    return f2__graph__copy_with_node_label(this_cause, this, node_label));


f2ptr raw__graph__node_isomorphisms(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr isomorphisms = nil;
  {
    f2ptr node__label    = f2__graph_node__label(cause, node);
    f2ptr this__node_set = f2__graph__node_set(cause, this);
    set__iteration(cause, this__node_set, this__node,
		   f2ptr this__node__label = f2__graph_node__label(cause, this__node);
		   if (raw__eq(cause, node__label, this__node__label)) {
		     f2ptr isomorphism = f2__graph_isomorphism__new(cause);
		     f2__graph_isomorphism__add_mapping(cause, isomorphism, node, this__node);
		     isomorphisms = raw__cons__new(cause, isomorphism, isomorphisms);
		   }
		   );
  }
  return isomorphisms;
}

f2ptr f2__graph__node_isomorphisms(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, node);
  return raw__graph__node_isomorphisms(cause, this, node);
}
def_pcfunk2(graph__node_isomorphisms, this, node,
	    "Returns all single node isomorphisms between this graph and a graph_node.",
	    return f2__graph__node_isomorphisms(this_cause, this, node));


f2ptr raw__graph__edges_with_label_between_nodes(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
  f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, left_node);
  if (! edges_label_hash_right_node_hash) {
    return nil;
  }
  f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash, right_node);
  if (! edges_label_hash) {
    return nil;
  }
  f2ptr edges = f2__ptypehash__lookup(cause, edges_label_hash, label);
  return edges;
}

f2ptr f2__graph__edges_with_label_between_nodes(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, left_node);
  assert_argument_type(graph_node, right_node);
  return raw__graph__edges_with_label_between_nodes(cause, this, label, left_node, right_node);
}
def_pcfunk4(graph__edges_with_label_between_nodes, this, label, left_node, right_node,
	    "Returns edges directed from the left_node to the right_node that have the label in this graph.",
	    return f2__graph__edges_with_label_between_nodes(this_cause, this, label, left_node, right_node));



f2ptr raw__graph__edges_between_nodes(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
  f2ptr edges_label_hash_right_node_hash                = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash_left_node_hash, left_node);
  f2ptr result = nil; //f2__ptypehash__new(cause);
  if (! edges_label_hash_right_node_hash) {
    return result;
  }
  f2ptr edges_label_hash = f2__ptypehash__lookup(cause, edges_label_hash_right_node_hash, right_node);
  if (! edges_label_hash) {
    return result;
  }
  ptypehash__keyvalue_pair__iteration(cause, edges_label_hash, pair__edge_label__edges,
				      f2ptr edge_label = f2__cons__car(cause, pair__edge_label__edges);
				      f2ptr edges      = f2__cons__cdr(cause, pair__edge_label__edges);
				      while (edges) {
					result = f2__cons__new(cause, f2__cons__new(cause, edge_label, f2__cons__car(cause, edges)), result);
					edges  = f2__cons__cdr(cause, edges);
				      }
				      );
  return result;
}

f2ptr f2__graph__edges_between_nodes(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  assert_argument_type(graph,      this);
  assert_argument_type(graph_node, left_node);
  assert_argument_type(graph_node, right_node);
  return raw__graph__edges_between_nodes(cause, this, left_node, right_node);
}
def_pcfunk3(graph__edges_between_nodes, this, left_node, right_node,
	    "Returns edges directed from the left_node to the right_node.",
	    return f2__graph__edges_between_nodes(this_cause, this, left_node, right_node));


f2ptr raw__graph__connected_node_sets__expand_node(f2ptr cause, f2ptr this, f2ptr remaining_node_set, f2ptr connected_node_set, f2ptr node) {
  raw__set__remove(cause, remaining_node_set, node);
  raw__set__add(cause, connected_node_set, node);
  graph__node__out_edge__iteration(cause, this, node, edge,
				   f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
				   if (raw__set__contains(cause, remaining_node_set, edge__right_node)) {
				     f2ptr result = raw__graph__connected_node_sets__expand_node(cause, this, remaining_node_set, connected_node_set, edge__right_node);
				     if (raw__larva__is_type(cause, result)) {
				       return result;
				     }
				   }
				   );
  graph__node__in_edge__iteration(cause, this, node, edge,
				  f2ptr edge__left_node = f2__graph_edge__left_node(cause, edge);
				  if (raw__set__contains(cause, remaining_node_set, edge__left_node)) {
				    f2ptr result = raw__graph__connected_node_sets__expand_node(cause, this, remaining_node_set, connected_node_set, edge__left_node);
				    if (raw__larva__is_type(cause, result)) {
				      return result;
				    }
				  }
				  );
  return nil;
}

f2ptr raw__graph__connected_node_sets(f2ptr cause, f2ptr this) {
  f2ptr connected_node_sets = nil;
  f2ptr node_set            = f2__graph__node_set(cause, this);
  f2ptr remaining_node_set  = raw__set__new_copy(cause, node_set);
  while (! raw__set__is_empty(cause, remaining_node_set)) {
    f2ptr node               = raw__set__an_arbitrary_element(cause, remaining_node_set);
    f2ptr connected_node_set = f2__set__new(cause);
    {
      f2ptr result = raw__graph__connected_node_sets__expand_node(cause, this, remaining_node_set, connected_node_set, node);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    connected_node_sets = raw__cons__new(cause, connected_node_set, connected_node_sets);
  }
  return connected_node_sets;
}

f2ptr f2__graph__connected_node_sets(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return raw__graph__connected_node_sets(cause, this);
}
def_pcfunk1(graph__connected_node_sets, this,
	    "Returns a new list of sets of connected nodes within this graph.",
	    return f2__graph__connected_node_sets(this_cause, this));


boolean_t raw__graph__contains_cycle__expand_node(f2ptr cause, f2ptr this, f2ptr visited_but_not_finished_node_set, f2ptr finished_node_set, f2ptr node) {
  raw__set__add(cause, visited_but_not_finished_node_set, node);
  graph__node__out_edge__iteration(cause, this, node, edge,
				   f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
				   if (raw__set__contains(cause, visited_but_not_finished_node_set, edge__right_node)) {
				     return boolean__true;
				   }
				   if (! raw__set__contains(cause, finished_node_set, edge__right_node)) {
				     if (raw__graph__contains_cycle__expand_node(cause, this, visited_but_not_finished_node_set, finished_node_set, edge__right_node)) {
				       return boolean__true;
				     }
				   }
				   );
  raw__set__remove(cause, visited_but_not_finished_node_set, node);
  raw__set__add(cause, finished_node_set, node);
  return boolean__false;
}

boolean_t raw__graph__contains_cycle(f2ptr cause, f2ptr this) {
  f2ptr node_set                          = f2__graph__node_set(cause, this);
  f2ptr visited_but_not_finished_node_set = f2__set__new(cause);
  f2ptr finished_node_set                 = f2__set__new(cause);
  set__iteration(cause, node_set, node,
		 if (raw__graph__contains_cycle__expand_node(cause, this, visited_but_not_finished_node_set, finished_node_set, node)) {
		   // found cycle => is not acyclic
		   return boolean__true;
		 }
		 );
  // is acyclic
  return boolean__false;
}

f2ptr f2__graph__contains_cycle(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return f2bool__new(raw__graph__contains_cycle(cause, this));
}
def_pcfunk1(graph__contains_cycle, this,
	    "Returns true if this graph does not contain cycles.",
	    return f2__graph__contains_cycle(this_cause, this));




f2ptr raw__graph__as__dot_code(f2ptr cause, f2ptr this) {
  f2ptr node_codes = nil;
  {
    f2ptr node_set = f2__graph__node_set(cause, this);
    set__iteration(cause, node_set, node,
		   f2ptr node_code = raw__graph_node__as__dot_code(cause, node);
		   node_codes = raw__cons__new(cause, node_code, node_codes);
		   );
  }    
  f2ptr edge_codes = nil;
  {
    f2ptr edge_set = f2__graph__edge_set(cause, this);
    set__iteration(cause, edge_set, edge,
		   f2ptr edge_code = raw__graph_edge__as__dot_code(cause, edge);
		   edge_codes = raw__cons__new(cause, edge_code, edge_codes);
		   );
  }
  return f2__graphviz__digraph(cause, f2list4__new(cause,
						   f2__graphviz__node_color(cause, new__string(cause, "#000000")),
						   f2__graphviz__edge_color(cause, new__string(cause, "#000000")),
						   f2__stringlist__rawcode(cause, node_codes),
						   f2__stringlist__rawcode(cause, edge_codes)));
}

f2ptr f2__graph__as__dot_code(f2ptr cause, f2ptr this) {
  assert_argument_type(graph, this);
  return raw__graph__as__dot_code(cause, this);
}
def_pcfunk1(graph__as__dot_code, this,
	    "Returns graph as dot_code for rendering with the graphviz dot application.",
	    return f2__graph__as__dot_code(this_cause, this));


f2ptr raw__graph__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "node_set"),          f2__graph__node_set(cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "edge_set"),          f2__graph__edge_set(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__graph__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph__primobject_type__new(cause);
  {char* slot_name = "connected_node_sets";       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.connected_node_sets__funk);}
  {char* slot_name = "contains_cycle";            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.contains_cycle__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.terminal_print_with_frame__funk);}
  return this;
}




// graph_list

boolean_t raw__graph_list__is_type(f2ptr cause, f2ptr object) {
  f2ptr iter = object;
  while (iter != nil) {
    if ((! raw__cons__is_type(cause, iter)) &&
	(! raw__list__is_type(cause, iter))) {
      return boolean__false;
    }
    f2ptr element = f2__first(cause, iter);
    if (! raw__graph__is_type(cause, element)) {
      return boolean__false;
    }
    iter = f2__next(iter, cause);
  }
  return boolean__true;
}


f2ptr raw__graph_list__union(f2ptr cause, f2ptr this) {
  f2ptr new_graph = f2__graph__new(cause);
  {
    f2ptr iter = this;
    while (iter) {
      f2ptr graph = f2__first(cause, iter);
      {
	{
	  f2ptr node_set = f2__graph__node_set(cause, graph);
	  set__iteration(cause, node_set, node,
			 f2__graph__add_node(cause, new_graph, node);
			 );
	}
	{
	  f2ptr edge_set = f2__graph__edge_set(cause, graph);
	  set__iteration(cause, edge_set, edge,
			 f2__graph__add_edge(cause, new_graph, edge);
			 );
	}
      }
      iter = f2__next(cause, iter);
    }
  }
  return new_graph;
}

f2ptr f2__graph_list__union(f2ptr cause, f2ptr this) {
  assert_argument_type(graph_list, this);
  return raw__graph_list__union(cause, this);
}
def_pcfunk1(graph_list__union, this,
	    "Returns a new graph that is the union of all graphs in this list.",
	    return f2__graph_list__union(this_cause, this));



// graph_isomorphism

def_primobject_2_slot(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);

f2ptr f2__graph_isomorphism__new(f2ptr cause) {
  f2ptr right_node_left_node_hash = f2__ptypehash__new(cause);
  f2ptr left_node_right_node_hash = f2__ptypehash__new(cause);
  return f2graph_isomorphism__new(cause, right_node_left_node_hash, left_node_right_node_hash);
}
def_pcfunk0(graph_isomorphism__new,
	    "",
	    return f2__graph_isomorphism__new(this_cause));

void raw__graph_isomorphism__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  f2ptr right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr left_node_right_node_hash = f2__graph_isomorphism__left_node_right_node_hash(cause, this);
  f2__ptypehash__add(cause, right_node_left_node_hash, left_node, right_node);
  f2__ptypehash__add(cause, left_node_right_node_hash, right_node, left_node);
}

f2ptr f2__graph_isomorphism__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  assert_argument_type(graph_isomorphism, this);
  assert_argument_type(graph_node,        left_node);
  assert_argument_type(graph_node,        right_node);
  raw__graph_isomorphism__add_mapping(cause, this, left_node, right_node);
  return nil;
}
def_pcfunk3(graph_isomorphism__add_mapping, this, left_node, right_node,
	    "Add a graph_node mapping to a graph_isomorphism.",
	    return f2__graph_isomorphism__add_mapping(this_cause, this, left_node, right_node));

u64 raw__graph_isomorphism__mapping_count(f2ptr cause, f2ptr this) {
  f2ptr right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr key_count                 = f2__ptypehash__key_count(cause, right_node_left_node_hash);
  return f2integer__i(key_count, cause);
}

f2ptr f2__graph_isomorphism__mapping_count(f2ptr cause, f2ptr this) {
  assert_argument_type(graph_isomorphism, this);
  f2ptr right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr key_count                 = f2__ptypehash__key_count(cause, right_node_left_node_hash);
  return key_count;
}
def_pcfunk1(graph_isomorphism__mapping_count, this,
	    "Returns the number of node mappings in this graph_isomorphism.",
	    return f2__graph_isomorphism__mapping_count(this_cause, this));

boolean_t raw__graph_isomorphism__is_disjoint_with(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__mapping_count = raw__graph_isomorphism__mapping_count(cause, this);
  u64 that__mapping_count = raw__graph_isomorphism__mapping_count(cause, that);
  if (this__mapping_count > that__mapping_count) {
    {
      f2ptr swap = this;
      this = that;
      that = swap;
    }
    {
      u64 swap = this__mapping_count;
      this__mapping_count = that__mapping_count;
      that__mapping_count = swap;
    }
  }
  f2ptr this__right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr that__right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, that);
  f2ptr that__left_node_right_node_hash = f2__graph_isomorphism__left_node_right_node_hash(cause, that);
  ptypehash__iteration(cause, this__right_node_left_node_hash, this__left_node, this__right_node,
		       if (raw__ptypehash__contains(cause, that__right_node_left_node_hash, this__left_node) ||
			   raw__ptypehash__contains(cause, that__left_node_right_node_hash, this__right_node)) {
			 return boolean__false;
		       }
		       );
  return boolean__true;
}

f2ptr f2__graph_isomorphism__is_disjoint_with(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(graph_isomorphism, this);
  assert_argument_type(graph_isomorphism, that);
  return raw__graph_isomorphism__is_disjoint_with(cause, this, that);
}
def_pcfunk2(graph_isomorphism__is_disjoint_with, this, that,
	    "Returns true if this graph_isomorphism is disjoint with that graph_isomorphism.",
	    return f2__graph_isomorphism__is_disjoint_with(this_cause, this, that));

f2ptr raw__graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node) {
  f2ptr right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
  return raw__ptypehash__lookup(cause, right_node_left_node_hash, left_node);
}

f2ptr f2__graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node) {
  assert_argument_type(graph_isomorphism, this);
  assert_argument_type(graph_node,        left_node);
  return raw__graph_isomorphism__map_left_to_right(cause, this, left_node);
}
def_pcfunk2(graph_isomorphism__map_left_to_right, this, left_node,
	    "Maps a node on the left of this graph_isomorphism to the right.",
	    return f2__graph_isomorphism__map_left_to_right(this_cause, this, left_node));

f2ptr raw__graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node) {
  f2ptr left_node_right_node_hash = f2__graph_isomorphism__left_node_right_node_hash(cause, this);
  return raw__ptypehash__lookup(cause, left_node_right_node_hash, right_node);
}

f2ptr f2__graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node) {
  assert_argument_type(graph_isomorphism, this);
  assert_argument_type(graph_node,        right_node);
  return raw__graph_isomorphism__map_right_to_left(cause, this, right_node);
}
def_pcfunk2(graph_isomorphism__map_right_to_left, this, right_node,
	    "Maps a node on the right of this graph_isomorphism to the left.",
	    return f2__graph_isomorphism__map_right_to_left(this_cause, this, right_node));

f2ptr raw__graph_isomorphism__union(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr isomorphism                     = f2__graph_isomorphism__new(cause);
  {
    f2ptr this__right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, this);
    ptypehash__iteration(cause, this__right_node_left_node_hash, left_node, right_node,
			 f2__graph_isomorphism__add_mapping(cause, isomorphism, left_node, right_node);
			 );
  }
  {
    f2ptr that__right_node_left_node_hash = f2__graph_isomorphism__right_node_left_node_hash(cause, that);
    ptypehash__iteration(cause, that__right_node_left_node_hash, left_node, right_node,
			 f2__graph_isomorphism__add_mapping(cause, isomorphism, left_node, right_node);
			 );
  }
  return isomorphism;
}

f2ptr f2__graph_isomorphism__union(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(graph_isomorphism, this);
  assert_argument_type(graph_isomorphism, that);
  return raw__graph_isomorphism__union(cause, this, that);
}
def_pcfunk2(graph_isomorphism__union, this, that,
	    "Returns a new graph_isomorphism representing the union between this graph_isomorphism and that graph_isomorphism.",
	    return f2__graph_isomorphism__union(this_cause, this, that));

f2ptr raw__graph_isomorphism__as__frame(f2ptr cause, f2ptr this) {
  return f2__ptypehash__as__frame(cause, f2__graph_isomorphism__right_node_left_node_hash(cause, this));
}

f2ptr f2__graph_isomorphism__as__frame(f2ptr cause, f2ptr this) {
  assert_argument_type(graph_isomorphism, this);
  return raw__graph_isomorphism__as__frame(cause, this);
}
def_pcfunk1(graph_isomorphism__as__frame, this,
	    "Returns a frame representing the left to right mapping ptypehash.",
	    return f2__graph_isomorphism__as__frame(this_cause, this));


f2ptr raw__graph_isomorphism__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = raw__graph_isomorphism__as__frame(cause, this);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_isomorphism"));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_isomorphism__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_isomorphism,    this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__graph_isomorphism__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_isomorphism__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_isomorphism__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2graph_isomorphism__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_isomorphism__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_isomorphism.terminal_print_with_frame__funk);}
  return this;
}


// graph_decomposition_lattice_node

def_primobject_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);

f2ptr raw__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph) {
  f2ptr between_graph          = f2__graph__new(cause);
  f2ptr parent_graph__edge_set = f2__graph__edge_set(cause, parent_graph);
  set__iteration(cause, parent_graph__edge_set, edge,
		 f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
		 f2ptr right_node = f2__graph_edge__right_node(cause, edge);
		 if (raw__graph__contains_node(cause, left_child_graph, left_node)) {
		   if (raw__graph__contains_node(cause, right_child_graph, right_node)) {
		     f2__graph__add_edge(cause, between_graph, edge);
		   }
		 } else if (raw__graph__contains_node(cause, left_child_graph, right_node)) {
		   f2__graph__add_edge(cause, between_graph, edge);
		 }
		 );
  //f2ptr root_graph_set = f2__ptypehash__new(cause);
  f2ptr root_graph_set = f2__set__new(cause);
  return f2graph_decomposition_lattice_node__new(cause, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);
}

f2ptr f2__graph_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph) {
  assert_argument_type(graph, parent_graph);
  assert_argument_type(graph, left_child_graph);
  assert_argument_type(graph, right_child_graph);
  return raw__graph_decomposition_lattice_node__new(cause, parent_graph, left_child_graph, right_child_graph);
}
def_pcfunk3(graph_decomposition_lattice_node__new, parent_graph, left_child_graph, right_child_graph,
	    "",
	    return f2__graph_decomposition_lattice_node__new(this_cause, parent_graph, left_child_graph, right_child_graph));


f2ptr raw__graph_decomposition_lattice_node__combine_children_isomorphisms(f2ptr cause, f2ptr this, f2ptr left_child_isomorphisms, f2ptr right_child_isomorphisms, f2ptr graph) {
  f2ptr isomorphisms = nil;
  //printf("\nnote -9.");
  {
    f2ptr left_iter = left_child_isomorphisms;
    while (left_iter) {
      f2ptr left_isomorphism = f2__cons__car(cause, left_iter);
      {
	f2ptr right_iter = right_child_isomorphisms;
	while (right_iter) {
	  f2ptr right_isomorphism = f2__cons__car(cause, right_iter);
	  {
	    if (raw__graph_isomorphism__is_disjoint_with(cause, left_isomorphism, right_isomorphism)) {
	      boolean_t combined_isomorphism_is_valid = boolean__true;
	      f2ptr     between_graph                 = f2__graph_decomposition_lattice_node__between_graph(cause, this);
	      f2ptr     between_graph__edge_set       = f2__graph__edge_set(cause, between_graph);
	      //printf("\nnote -8: between_graph = "); f2__print(cause, between_graph);
	      //printf("\nnote -8: left_isomorphism = "); f2__print(cause, left_isomorphism);
	      //printf("\nnote -8: right_isomorphism = "); f2__print(cause, right_isomorphism);
	      //printf("\nnote -8: graph = "); f2__print(cause, graph);
	      set__iteration(cause, between_graph__edge_set, edge,
			     f2ptr label             = f2__graph_edge__label(     cause, edge);
			     f2ptr left_node         = f2__graph_edge__left_node( cause, edge);
			     f2ptr right_node        = f2__graph_edge__right_node(cause, edge);
			     f2ptr edges             = f2__graph__edges_with_label_between_nodes(cause, between_graph, label, left_node, right_node);
			     f2ptr graph__left_node  = f2__graph_isomorphism__map_left_to_right(cause, left_isomorphism, left_node);
			     if (graph__left_node == nil) {
			       graph__left_node = f2__graph_isomorphism__map_left_to_right(cause, right_isomorphism, left_node);
			     }
			     f2ptr graph__right_node = f2__graph_isomorphism__map_left_to_right(cause, right_isomorphism, right_node);
			     if (graph__right_node == nil) {
			       graph__right_node = f2__graph_isomorphism__map_left_to_right(cause, left_isomorphism, right_node);
			     }
			     f2ptr graph__edges      = f2__graph__edges_with_label_between_nodes(cause, graph, label, graph__left_node, graph__right_node);
			     //printf("\nnote -7: left_node = "); f2__print(cause, left_node);
			     //printf("\nnote -7: right_node = "); f2__print(cause, right_node);
			     //printf("\nnote -7: graph__left_node = "); f2__print(cause, graph__left_node);
			     //printf("\nnote -7: graph__right_node = "); f2__print(cause, graph__right_node);
			     if (raw__simple_length(cause, edges) != raw__simple_length(cause, graph__edges)) {
			       //printf("\ndebug -6");
			       combined_isomorphism_is_valid = boolean__false;
			       goto raw__graph_decomposition_lattice_node__combine_children_isomorphisms__found_unmatched_edge;
			     }
			     );
	    raw__graph_decomposition_lattice_node__combine_children_isomorphisms__found_unmatched_edge:
	      if (combined_isomorphism_is_valid) {
		f2ptr isomorphism = f2__graph_isomorphism__union(cause, left_isomorphism, right_isomorphism);
		isomorphisms = raw__cons__new(cause, isomorphism, isomorphisms);
	      }
	    } else {
	      //printf("\ndebug -5");
	    }
	  }
	  right_iter = f2__cons__cdr(cause, right_iter);
	}
      }
      left_iter = f2__cons__cdr(cause, left_iter);
    }
  }
  //printf("\nnote -4: isomorphisms = "); f2__print(cause, isomorphisms);
  return isomorphisms;
}

f2ptr f2__graph_decomposition_lattice_node__combine_children_isomorphisms(f2ptr cause, f2ptr this, f2ptr left_child_isomorphisms, f2ptr right_child_isomorphisms, f2ptr graph) {
  assert_argument_type(graph_decomposition_lattice, this);
  assert_argument_type(graph,                       graph);
  return raw__graph_decomposition_lattice_node__combine_children_isomorphisms(cause, this, left_child_isomorphisms, right_child_isomorphisms, graph);
}
def_pcfunk4(graph_decomposition_lattice_node__combine_children_isomorphisms, this, left_child_isomorphisms, right_child_isomorphisms, graph,
	    "Combine children isomorphisms when they are non-overlapping.",
	    return f2__graph_decomposition_lattice_node__combine_children_isomorphisms(this_cause, this, left_child_isomorphisms, right_child_isomorphisms, graph));


f2ptr raw__graph_decomposition_lattice_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_decomposition_lattice_node"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "parent_graph"),      f2__graph_decomposition_lattice_node__parent_graph(cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "left_child_graph"),  f2__graph_decomposition_lattice_node__left_child_graph(cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "right_child_graph"), f2__graph_decomposition_lattice_node__right_child_graph(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_decomposition_lattice_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_decomposition_lattice_node, this);
  assert_argument_type(terminal_print_frame,             terminal_print_frame);
  return raw__graph_decomposition_lattice_node__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_decomposition_lattice_node__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_decomposition_lattice_node__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2graph_decomposition_lattice_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_decomposition_lattice_node__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice_node.terminal_print_with_frame__funk);}
  return this;
}


// graph_decomposition_lattice

def_primobject_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);

f2ptr f2__graph_decomposition_lattice__new(f2ptr cause) {
  f2ptr graph_set             = f2__set__new(cause);
  f2ptr node_set              = f2__set__new(cause);
  f2ptr node_parent_hash      = f2__ptypehash__new(cause);
  f2ptr node_left_child_hash  = f2__ptypehash__new(cause);
  f2ptr node_right_child_hash = f2__ptypehash__new(cause);
  f2ptr leaf_graph_set        = f2__set__new(cause);
  f2ptr root_graph_set        = f2__set__new(cause);
  return f2graph_decomposition_lattice__new(cause, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);
}
def_pcfunk0(graph_decomposition_lattice__new,
	    "",
	    return f2__graph_decomposition_lattice__new(this_cause));

f2ptr raw__graph_decomposition_lattice__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set              = f2__graph_decomposition_lattice__node_set(cause, this);
  f2ptr already_contains_node = f2__set__add(cause, node_set, node);
  if (already_contains_node == nil) {
    f2ptr graph_set      = f2__graph_decomposition_lattice__graph_set(cause, this);
    f2ptr leaf_graph_set = f2__graph_decomposition_lattice__leaf_graph_set(cause, this);
    {
      f2ptr parent_graph     = f2__graph_decomposition_lattice_node__parent_graph(cause, node);
      f2__set__add(cause, graph_set, parent_graph);
      f2ptr node_parent_hash = f2__graph_decomposition_lattice__node_parent_hash(cause, this);
      f2__ptypehash__add(cause, node_parent_hash, parent_graph, node);
    }
    {
      f2ptr left_child_graph     = f2__graph_decomposition_lattice_node__left_child_graph(cause, node);
      f2__set__add(cause, graph_set, left_child_graph);
      f2ptr node_left_child_hash = f2__graph_decomposition_lattice__node_left_child_hash(cause, this);
      f2ptr node_s = f2__ptypehash__lookup(cause, node_left_child_hash, left_child_graph);
      if (node_s == nil) {
	node_s = f2__set__new(cause);
	f2__ptypehash__add(cause, node_left_child_hash, left_child_graph, node_s);
      }
      f2__set__add(cause, node_s, node);
      if (raw__graph__node_count(cause, left_child_graph) == 1) {
	f2__set__add(cause, leaf_graph_set, left_child_graph);
      }
    }
    {
      f2ptr right_child_graph     = f2__graph_decomposition_lattice_node__right_child_graph(cause, node);
      f2__set__add(cause, graph_set, right_child_graph);
      f2ptr node_right_child_hash = f2__graph_decomposition_lattice__node_right_child_hash(cause, this);
      f2ptr node_s = f2__ptypehash__lookup(cause, node_right_child_hash, right_child_graph);
      if (node_s == nil) {
	node_s = f2__set__new(cause);
	f2__ptypehash__add(cause, node_right_child_hash, right_child_graph, node_s);
      }
      f2__set__add(cause, node_s, node);
      if (raw__graph__node_count(cause, right_child_graph) == 1) {
	f2__set__add(cause, leaf_graph_set, right_child_graph);
      }
    }
  }
  return already_contains_node;
}

f2ptr f2__graph_decomposition_lattice__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(graph_decomposition_lattice,      this);
  assert_argument_type(graph_decomposition_lattice_node, node);
  return raw__graph_decomposition_lattice__add_node(cause, this, node);
}
def_pcfunk2(graph_decomposition_lattice__add_node, this, node,
	    "Add a graph_decomposition_lattice_node to this graph_decomposition_lattice.",
	    return f2__graph_decomposition_lattice__add_node(this_cause, this, node));

void raw__graph_decomposition_lattice__decompose_graph_with_root_graph(f2ptr cause, f2ptr this, f2ptr graph, f2ptr root_graph) {
  f2ptr maximum_isomorphic_graph = nil;
  u64   graph__node_count        = raw__graph__node_count(cause, graph);
  if (graph__node_count == 1) {
    return; // we're done.
  }
  f2ptr node_set = f2__graph_decomposition_lattice__node_set(cause, this);
  set__iteration(cause, node_set, node,
		 f2ptr parent_graph = f2__graph_decomposition_lattice_node__parent_graph(cause, node);
		 if (raw__graph__contains(cause, graph, parent_graph) &&
		     (raw__graph__node_count(cause, parent_graph) > (maximum_isomorphic_graph ? raw__graph__node_count(cause, maximum_isomorphic_graph) : 0))) {
		   maximum_isomorphic_graph = parent_graph;
		 }
		 );
  if (maximum_isomorphic_graph && (raw__graph__node_count(cause, graph) == raw__graph__node_count(cause, maximum_isomorphic_graph))) {
    return; // we're done.
  }
  if (maximum_isomorphic_graph == nil) {
    maximum_isomorphic_graph = f2__graph__random_nonempty_strict_subgraph(cause, graph);
    raw__graph_decomposition_lattice__decompose_graph_with_root_graph(cause, this, maximum_isomorphic_graph, root_graph);
  }
  f2ptr remainder_graph = f2__graph__minus(cause, graph, maximum_isomorphic_graph);
  raw__graph_decomposition_lattice__decompose_graph_with_root_graph(cause, this, remainder_graph, root_graph);
  f2ptr decomposition_lattice_node = f2__graph_decomposition_lattice_node__new(cause, graph, maximum_isomorphic_graph, remainder_graph);
  {
    f2ptr root_graph_set = f2__graph_decomposition_lattice_node__root_graph_set(cause, decomposition_lattice_node);
    //f2__print(cause, root_graph);
    f2__set__add(cause, root_graph_set, root_graph);
    //f2__print(cause, root_graph_set);
  }
  raw__graph_decomposition_lattice__add_node(cause, this, decomposition_lattice_node);
}

void raw__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph) {
  raw__graph_decomposition_lattice__decompose_graph_with_root_graph(cause, this, graph, graph);
}

f2ptr f2__graph_decomposition_lattice__decompose_graph_with_root_graph(f2ptr cause, f2ptr this, f2ptr graph, f2ptr root_graph) {
  assert_argument_type(       graph_decomposition_lattice,      this);
  assert_argument_type(       graph,                            graph);
  assert_argument_type_or_nil(graph,                            root_graph);
  if (raw__graph__node_count(cause, graph) < 1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),   new__symbol(cause, "cannot_decompose_empty_graph"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),   new__symbol(cause, "graph_decomposition_lattice-decompose_graph_with_root_graph"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),       this);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "graph"),      graph);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "root_graph"), root_graph);
    return f2larva__new(cause, 454, f2__bug__new(cause, f2integer__new(cause, 454), bug_frame));
  }
  raw__graph_decomposition_lattice__decompose_graph_with_root_graph(cause, this, graph, root_graph);
  return nil;
}
def_pcfunk3(graph_decomposition_lattice__decompose_graph_with_root_graph, this, graph, root_graph,
	    "Decompose a graph into this graph_decomposition_lattice with given root_graph.",
	    return f2__graph_decomposition_lattice__decompose_graph_with_root_graph(this_cause, this, graph, root_graph));

f2ptr f2__graph_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph) {
  f2__graph_decomposition_lattice__decompose_graph_with_root_graph(cause, this, graph, graph);
  f2ptr root_graph_set = f2__graph_decomposition_lattice__root_graph_set(cause, this);
  f2__set__add(cause, root_graph_set, graph);
  return nil;
}
def_pcfunk2(graph_decomposition_lattice__decompose_graph, this, graph,
	    "Decompose a graph into this graph_decomposition_lattice, assuming graph is also a root graph.",
	    return f2__graph_decomposition_lattice__decompose_graph(this_cause, this, graph));

f2ptr raw__graph_decomposition_lattice__subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr unsolved_graph_set = f2__set__new(cause);
  f2ptr alive_graph_set    = f2__set__new(cause);
  f2ptr dead_graph_set     = f2__set__new(cause);
  f2ptr graph_set          = f2__graph_decomposition_lattice__graph_set(cause, this);
  set__iteration(cause, graph_set, graph,
		 f2__set__add(cause, unsolved_graph_set, graph);
		 );
  f2ptr isomorphisms_graph_hash = f2__ptypehash__new(cause);
  f2ptr leaf_graph_set          = f2__graph_decomposition_lattice__leaf_graph_set(cause, this);
  set__iteration(cause, leaf_graph_set, leaf_graph,
		 f2ptr leaf_graph__node_set = f2__graph__node_set(cause, leaf_graph);
		 f2ptr leaf_graph__node     = nil;
		 set__iteration(cause, leaf_graph__node_set, leaf_graph__node_set__node,
				leaf_graph__node = leaf_graph__node_set__node;
				);
		 f2ptr leaf_graph__isomorphisms = f2__graph__node_isomorphisms(cause, graph, leaf_graph__node);
		 f2__set__remove(cause, unsolved_graph_set, leaf_graph);
		 if (leaf_graph__isomorphisms != nil) {
		   f2__set__add(cause, alive_graph_set, leaf_graph);
		   f2__ptypehash__add(cause, isomorphisms_graph_hash, leaf_graph, leaf_graph__isomorphisms);
		 } else {
		   //printf("\ndebug 0");
		   f2__set__add(cause, dead_graph_set, leaf_graph);
		 }
		 );
  f2ptr node_parent_hash = f2__graph_decomposition_lattice__node_parent_hash(cause, this);
  while (! raw__set__is_empty(cause, unsolved_graph_set)) {
    f2ptr solve_lattice_node = nil;
    f2ptr parent_graph       = nil;
    f2ptr left_child_graph   = nil;
    f2ptr right_child_graph  = nil;
    set__iteration(cause, unsolved_graph_set, unsolved_graph,
		   f2ptr lattice_node = f2__ptypehash__lookup(cause, node_parent_hash, unsolved_graph);
		   left_child_graph   = f2__graph_decomposition_lattice_node__left_child_graph( cause, lattice_node);
		   right_child_graph  = f2__graph_decomposition_lattice_node__right_child_graph(cause, lattice_node);
		   if (raw__set__contains(cause, alive_graph_set, left_child_graph) &&
		       raw__set__contains(cause, alive_graph_set, right_child_graph)) {
		     solve_lattice_node = lattice_node;
		     parent_graph       = unsolved_graph;
		     goto raw__graph_decomposition_lattice__subgraph_isomorphisms__found_solve_lattice_node;
		   } else {
		     //printf("\ndebug 1");
		   }
		   );
  raw__graph_decomposition_lattice__subgraph_isomorphisms__found_solve_lattice_node:
    if (solve_lattice_node == nil) {
      //printf("\ndebug 2");
      break;
    }
    f2ptr left_child_graph__isomorphisms  = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, left_child_graph);
    f2ptr right_child_graph__isomorphisms = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, right_child_graph);
    f2ptr parent_graph__isomorphisms      = f2__graph_decomposition_lattice_node__combine_children_isomorphisms(cause, solve_lattice_node, left_child_graph__isomorphisms, right_child_graph__isomorphisms, graph);
    f2__set__remove(cause, unsolved_graph_set, parent_graph);
    if (parent_graph__isomorphisms == nil) {
      //printf("\ndebug 3: solve_lattice_node  "); f2__print(cause, solve_lattice_node);
      //printf("\ndebug 3: left_child_graph__isomorphisms  "); f2__print(cause, left_child_graph__isomorphisms);
      //printf("\ndebug 3: right_child_graph__isomorphisms  "); f2__print(cause, right_child_graph__isomorphisms);
      f2__set__add(cause, dead_graph_set, parent_graph);
    } else {
      f2__set__add(cause, alive_graph_set, parent_graph);
      f2__ptypehash__add(cause, isomorphisms_graph_hash, parent_graph, parent_graph__isomorphisms);
      f2__set__remove(cause, alive_graph_set,  left_child_graph);
      f2__set__add(   cause,  dead_graph_set,  left_child_graph);
      f2__set__remove(cause, alive_graph_set, right_child_graph);
      f2__set__add(   cause,  dead_graph_set, right_child_graph);
    }
  }
  f2ptr root_graph_isomorphisms_pairs = nil;
  //f2__print(cause, root_graph_isomorphisms_pairs);
  set__iteration(cause, alive_graph_set, alive_graph,
		 f2ptr isomorphisms = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, alive_graph);
		 //f2__print(cause, isomorphisms);
		 if (isomorphisms != nil) {
		   f2ptr lattice_node   = f2__ptypehash__lookup(cause, node_parent_hash, alive_graph);
		   //f2__print(cause, lattice_node);
		   if (lattice_node) {
		     f2ptr root_graph_set = f2__graph_decomposition_lattice_node__root_graph_set(cause, lattice_node);
		     //f2__print(cause, root_graph_set);
		     set__iteration(cause, root_graph_set, root_graph,
				    root_graph_isomorphisms_pairs = raw__cons__new(cause, f2list2__new(cause, root_graph, isomorphisms), root_graph_isomorphisms_pairs);
				    );
		   }
		 }
		 );
  return root_graph_isomorphisms_pairs;
}

f2ptr f2__graph_decomposition_lattice__subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  assert_argument_type(graph_decomposition_lattice, this);
  assert_argument_type(graph,                       graph);
  return raw__graph_decomposition_lattice__subgraph_isomorphisms(cause, this, graph);
}
def_pcfunk2(graph_decomposition_lattice__subgraph_isomorphisms, this, graph,
	    "Returns all subgraph isomorphisms to model graphs decomposed into this graph_decomposition_lattice.",
	    return f2__graph_decomposition_lattice__subgraph_isomorphisms(this_cause, this, graph));

f2ptr raw__graph_decomposition_lattice__subgraph_max_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr root_graph_isomorphisms_pairs    = raw__graph_decomposition_lattice__subgraph_isomorphisms(cause, this, graph);
  f2ptr max_root_graph_isomorphism_pairs = nil;
  {
    f2ptr pair_iter = root_graph_isomorphisms_pairs;
    while (pair_iter) {
      f2ptr root_graph_isomorphisms_pair = f2__cons__car(cause, pair_iter);
      {
	f2ptr root_graph                     = f2__cons__car(cause, root_graph_isomorphisms_pair);
	f2ptr isomorphisms                   = f2__cons__car(cause, f2__cons__cdr(cause, root_graph_isomorphisms_pair));
	f2ptr max_isomorphism                = nil;
	u64   max_isomorphism__mapping_count = 0;
	{
	  f2ptr iter = isomorphisms;
	  while (iter) {
	    f2ptr isomorphism = f2__cons__car(cause, iter);
	    {
	      u64 mapping_count = raw__graph_isomorphism__mapping_count(cause, isomorphism);
	      if (mapping_count > max_isomorphism__mapping_count) {
		max_isomorphism                = isomorphism;
		max_isomorphism__mapping_count = mapping_count;
	      }
	    }
	    iter = f2__cons__cdr(cause, iter);
	  }
	}
	max_root_graph_isomorphism_pairs = raw__cons__new(cause, f2list2__new(cause, root_graph, max_isomorphism), max_root_graph_isomorphism_pairs);
      }
      pair_iter = f2__cons__cdr(cause, pair_iter);
    }
  }
  return max_root_graph_isomorphism_pairs;
}

f2ptr f2__graph_decomposition_lattice__subgraph_max_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  assert_argument_type(graph_decomposition_lattice, this);
  assert_argument_type(graph,                       graph);
  return raw__graph_decomposition_lattice__subgraph_max_isomorphisms(cause, this, graph);
}
def_pcfunk2(graph_decomposition_lattice__subgraph_max_isomorphisms, this, graph,
	    "Returns maximum subgraph isomorphisms to model graphs decomposed into this graph_decomposition_lattice.",
	    return f2__graph_decomposition_lattice__subgraph_max_isomorphisms(this_cause, this, graph));


f2ptr raw__graph_decomposition_lattice__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "graph_decomposition_lattice"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "root_graph_set"),    f2__graph_decomposition_lattice__root_graph_set(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__graph_decomposition_lattice__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(graph_decomposition_lattice, this);
  assert_argument_type(terminal_print_frame,        terminal_print_frame);
  return raw__graph_decomposition_lattice__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(graph_decomposition_lattice__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__graph_decomposition_lattice__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2graph_decomposition_lattice__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_decomposition_lattice__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__graph__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // graph_node
  initialize_primobject_1_slot__defragment__fix_pointers(graph_node, label);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_node.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_node__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_node.terminal_print_with_frame__funk);
  
  // graph_edge
  initialize_primobject_3_slot__defragment__fix_pointers(graph_edge, label, left_node, right_node);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_edge.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_edge__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_edge.terminal_print_with_frame__funk);
  
  // graph
  initialize_primobject_5_slot__defragment__fix_pointers(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);
  
  f2__primcfunk__init__defragment__fix_pointers(graph__nodes);
  f2__primcfunk__init__defragment__fix_pointers(graph__edges);
  f2__primcfunk__init__defragment__fix_pointers(graph__add_node);
  f2__primcfunk__init__defragment__fix_pointers(graph__add_new_node);
  f2__primcfunk__init__defragment__fix_pointers(graph__add_edge);
  f2__primcfunk__init__defragment__fix_pointers(graph__add_new_edge);
  f2__primcfunk__init__defragment__fix_pointers(graph__node_count);
  f2__primcfunk__init__defragment__fix_pointers(graph__contains_node);
  f2__primcfunk__init__defragment__fix_pointers(graph__nodes_with_label);
  f2__primcfunk__init__defragment__fix_pointers(graph__contains_node_label);
  f2__primcfunk__init__defragment__fix_pointers(graph__contains_edge);
  f2__primcfunk__init__defragment__fix_pointers(graph__contains);
  f2__primcfunk__init__defragment__fix_pointers(graph__lookup_nodes_with_label);
  f2__primcfunk__init__defragment__fix_pointers(graph__random_nonempty_strict_subgraph);
  f2__primcfunk__init__defragment__fix_pointers(graph__minus);
  f2__primcfunk__init__defragment__fix_pointers(graph__copy);
  f2__primcfunk__init__defragment__fix_pointers(graph__copy_with_node_label);
  f2__primcfunk__init__defragment__fix_pointers(graph__node_isomorphisms);
  f2__primcfunk__init__defragment__fix_pointers(graph__edges_with_label_between_nodes);
  f2__primcfunk__init__defragment__fix_pointers(graph__edges_between_nodes);
  f2__primcfunk__init__defragment__fix_pointers(graph__as__dot_code);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.connected_node_sets__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph__connected_node_sets);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.connected_node_sets__funk);

  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.contains_cycle__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph__contains_cycle);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.contains_cycle__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph.terminal_print_with_frame__funk);
  
  // graph_list
  f2__primcfunk__init__defragment__fix_pointers(graph_list__union);
  
  // graph_isomorphism
  initialize_primobject_2_slot__defragment__fix_pointers(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);
  
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__add_mapping);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__mapping_count);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__is_disjoint_with);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__map_left_to_right);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__map_right_to_left);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__union);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__as__frame);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_isomorphism.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_isomorphism__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_isomorphism.terminal_print_with_frame__funk);
  
  // graph_decomposition_lattice_node
  initialize_primobject_5_slot__defragment__fix_pointers(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);
  
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice_node__combine_children_isomorphisms);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice_node.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice_node__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice_node.terminal_print_with_frame__funk);
  
  // graph_decomposition_lattice
  initialize_primobject_7_slot__defragment__fix_pointers(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);
  
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__add_node);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__decompose_graph_with_root_graph);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__decompose_graph);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__subgraph_isomorphisms);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__subgraph_max_isomorphisms);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(graph_decomposition_lattice__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice.terminal_print_with_frame__funk);
  
}

void f2__graph__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // graph_node
  initialize_primobject_1_slot(graph_node, label);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_node.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_node.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph_edge
  initialize_primobject_3_slot(graph_edge, label, left_node, right_node);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_edge.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_edge__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_edge.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph
  initialize_primobject_5_slot(graph, node_set, edge_set, nodes_label_hash, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);
  
  f2__primcfunk__init__1(graph__nodes,                           this);
  f2__primcfunk__init__1(graph__edges,                           this);
  f2__primcfunk__init__2(graph__add_node,                        this, node);
  f2__primcfunk__init__2(graph__add_new_node,                    this, label);
  f2__primcfunk__init__2(graph__add_edge,                        this, edge);
  f2__primcfunk__init__4(graph__add_new_edge,                    this, label, left_node, right_node);
  f2__primcfunk__init__1(graph__node_count,                      this);
  f2__primcfunk__init__2(graph__contains_node,                   this, node);
  f2__primcfunk__init__2(graph__nodes_with_label,                this, label);
  f2__primcfunk__init__2(graph__contains_node_label,             this, label);
  f2__primcfunk__init__2(graph__contains_edge,                   this, edge);
  f2__primcfunk__init__2(graph__contains,                        this, graph);
  f2__primcfunk__init__2(graph__lookup_nodes_with_label,         this, node_label);
  f2__primcfunk__init__1(graph__random_nonempty_strict_subgraph, this);
  f2__primcfunk__init__2(graph__minus,                           this, that);
  f2__primcfunk__init__1(graph__copy,                            this);
  f2__primcfunk__init__2(graph__copy_with_node_label,            this, node_label);
  f2__primcfunk__init__2(graph__node_isomorphisms,               this, node);
  f2__primcfunk__init__4(graph__edges_with_label_between_nodes,  this, label, left_node, right_node);
  f2__primcfunk__init__3(graph__edges_between_nodes,             this, left_node, right_node);
  f2__primcfunk__init__1(graph__as__dot_code,                    this);
  
  __funk2.globalenv.object_type.primobject.primobject_type_graph.connected_node_sets__symbol = new__symbol(cause, "connected_node_sets");
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__connected_node_sets, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph.connected_node_sets__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_graph.contains_cycle__symbol = new__symbol(cause, "contains_cycle");
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__contains_cycle, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph.contains_cycle__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_graph.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph_list
  f2__primcfunk__init__1(graph_list__union, this);
  
  // graph_isomorphism
  initialize_primobject_2_slot(graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);
  
  f2__primcfunk__init__3(graph_isomorphism__add_mapping,               this, left_node, right_node);
  f2__primcfunk__init__1(graph_isomorphism__mapping_count,             this);
  f2__primcfunk__init__2(graph_isomorphism__is_disjoint_with,          this, that);
  f2__primcfunk__init__2(graph_isomorphism__map_left_to_right,         this, left_node);
  f2__primcfunk__init__2(graph_isomorphism__map_right_to_left,         this, right_node);
  f2__primcfunk__init__2(graph_isomorphism__union,                     this, that);
  f2__primcfunk__init__1(graph_isomorphism__as__frame,                 this);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_isomorphism.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_isomorphism__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_isomorphism.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph_decomposition_lattice_node
  initialize_primobject_5_slot(graph_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph, root_graph_set);
  
  f2__primcfunk__init__4(graph_decomposition_lattice_node__combine_children_isomorphisms, this, left_child_isomorphisms, right_child_isomorphisms, graph);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice_node.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_decomposition_lattice_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice_node.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // graph_decomposition_lattice
  initialize_primobject_7_slot(graph_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);
  
  f2__primcfunk__init__2(graph_decomposition_lattice__add_node,                        this, node);
  f2__primcfunk__init__3(graph_decomposition_lattice__decompose_graph_with_root_graph, this, graph, root_graph);
  f2__primcfunk__init__2(graph_decomposition_lattice__decompose_graph,                 this, graph);
  f2__primcfunk__init__2(graph_decomposition_lattice__subgraph_isomorphisms,           this, graph);
  f2__primcfunk__init__2(graph_decomposition_lattice__subgraph_max_isomorphisms,       this, graph);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_decomposition_lattice__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_graph_decomposition_lattice.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__graph__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph", "", &f2__graph__reinitialize_globalvars, &f2__graph__defragment__fix_pointers);
  
  f2__graph__reinitialize_globalvars();
}

