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

// bruno_graph_node

def_primobject_1_slot(bruno_graph_node, label);

f2ptr f2__bruno_graph_node__new(f2ptr cause, f2ptr label) {
  return f2bruno_graph_node__new(cause, label);
}
def_pcfunk1(bruno_graph_node__new, label, return f2__bruno_graph_node__new(this_cause, label));

// bruno_graph_edge

def_primobject_3_slot(bruno_graph_edge, label, left_node, right_node);

f2ptr f2__bruno_graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2bruno_graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(bruno_graph_edge__new, label, left_node, right_node, return f2__bruno_graph_edge__new(this_cause, label, left_node, right_node));

// bruno_graph

def_primobject_4_slot(bruno_graph, node_set, edge_set, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);

f2ptr f2__bruno_graph__new(f2ptr cause) {
  f2ptr node_set                                        = f2__set__new(cause);
  f2ptr edge_set                                        = f2__set__new(cause);
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__ptypehash__new(cause);
  f2ptr edges_label_hash_left_node_hash_right_node_hash = f2__ptypehash__new(cause);
  return f2bruno_graph__new(cause, node_set, edge_set, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);
}
def_pcfunk0(bruno_graph__new, return f2__bruno_graph__new(this_cause));

f2ptr raw__bruno_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set = f2__bruno_graph__node_set(cause, this);
  f2ptr already_contains_node = f2__set__add(cause, node_set, node);
  return already_contains_node;
}

f2ptr f2__bruno_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__bruno_graph__is_type(cause, this) || ! raw__bruno_graph_node__is_type(cause, node)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__add_node(cause, this, node);
}
def_pcfunk2(bruno_graph__add_node, this, node, return f2__bruno_graph__add_node(this_cause, this, node));

f2ptr raw__bruno_graph__add_new_node(f2ptr cause, f2ptr this, f2ptr label) {
  f2ptr node = f2__bruno_graph_node__new(cause, label);
  return raw__bruno_graph__add_node(cause, this, node);
}

f2ptr f2__bruno_graph__add_new_node(f2ptr cause, f2ptr this, f2ptr label) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__add_new_node(cause, this, label);
}
def_pcfunk2(bruno_graph__add_new_node, this, label, return f2__bruno_graph__add_new_node(this_cause, this, label));

f2ptr raw__bruno_graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  f2ptr edge_set              = f2__bruno_graph__edge_set(cause, this);
  f2ptr already_contains_edge = f2__set__add(cause, edge_set, edge);
  if (already_contains_edge == nil) {
    f2ptr left_node  = f2__bruno_graph_edge__left_node( cause, edge);
    f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
    f2ptr label      = f2__bruno_graph_edge__label(     cause, edge);
    f2__bruno_graph__add_node(cause, this, left_node);
    f2__bruno_graph__add_node(cause, this, right_node);
    {
      f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__bruno_graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
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
      f2__ptypehash__add(cause, edges_label_hash, label, f2cons__new(cause, edge, edges));
    }
    {
      f2ptr edges_label_hash_left_node_hash_right_node_hash = f2__bruno_graph__edges_label_hash_left_node_hash_right_node_hash(cause, this);
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
      f2__ptypehash__add(cause, edges_label_hash, label, f2cons__new(cause, edge, edges));
    }
  }
  return already_contains_edge;
}

f2ptr f2__bruno_graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_edge__is_type(cause, edge))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__add_edge(cause, this, edge);
}
def_pcfunk2(bruno_graph__add_edge, this, edge, return f2__bruno_graph__add_edge(this_cause, this, edge));

f2ptr raw__bruno_graph__add_new_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge = f2__bruno_graph_edge__new(cause, label, left_node, right_node);
  return raw__bruno_graph__add_edge(cause, this, edge);
}

f2ptr f2__bruno_graph__add_new_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, left_node)) ||
      (! raw__bruno_graph_node__is_type(cause, right_node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__add_new_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(bruno_graph__add_new_edge, this, label, left_node, right_node, return f2__bruno_graph__add_new_edge(this_cause, this, label, left_node, right_node));

u64 raw__bruno_graph__node_count(f2ptr cause, f2ptr this) {
  f2ptr node_set            = f2__bruno_graph__node_set(cause, this);
  f2ptr node_set__key_count = f2__set__key_count(cause, node_set);
  return f2integer__i(node_set__key_count, cause);
}

f2ptr f2__bruno_graph__node_count(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr node_set = f2__bruno_graph__node_set(cause, this);
  return f2__set__key_count(cause, node_set);
}
def_pcfunk1(bruno_graph__node_count, this, return f2__bruno_graph__node_count(this_cause, this));

boolean_t raw__bruno_graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set = f2__bruno_graph__node_set(cause, this);
  return raw__set__contains(cause, node_set, node);
}

f2ptr f2__bruno_graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, node))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__bruno_graph__contains_node(cause, this, node));
}
def_pcfunk2(bruno_graph__contains_node, this, node, return f2__bruno_graph__contains_node(this_cause, this, node));

boolean_t raw__bruno_graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  f2ptr edge_set = f2__bruno_graph__edge_set(cause, this);
  return raw__set__contains(cause, edge_set, edge);
}

f2ptr f2__bruno_graph__contains_edge(f2ptr cause, f2ptr this, f2ptr edge) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_edge__is_type(cause, edge))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__bruno_graph__contains_edge(cause, this, edge));
}
def_pcfunk2(bruno_graph__contains_edge, this, edge, return f2__bruno_graph__contains_edge(this_cause, this, edge));

boolean_t raw__bruno_graph__contains(f2ptr cause, f2ptr this, f2ptr graph) {
  {
    f2ptr graph__node_set = f2__bruno_graph__node_set(cause, graph);
    set__iteration(cause, graph__node_set, node,
		   if (! raw__bruno_graph__contains_node(cause, this, node)) {
		     return boolean__false;
		   }
		   );
  }
  {
    f2ptr graph__edge_set = f2__bruno_graph__edge_set(cause, graph);
    set__iteration(cause, graph__edge_set, edge,
		   if (! raw__bruno_graph__contains_edge(cause, this, edge)) {
		     return boolean__false;
		   }
		   );
  }
  return boolean__true;
}

f2ptr f2__bruno_graph__contains(f2ptr cause, f2ptr this, f2ptr graph) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph__is_type(cause, graph))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__bruno_graph__contains(cause, this, graph));
}
def_pcfunk2(bruno_graph__contains, this, graph, return f2__bruno_graph__contains(this_cause, this, graph));

// assumes this is bruno_graph and has at least 2 nodes.
f2ptr raw__bruno_graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this) {
  f2ptr  graph      = f2__bruno_graph__new(cause);
  u64    node_count = raw__bruno_graph__node_count(cause, this);
  f2ptr* node_array = (f2ptr*)alloca(sizeof(f2ptr) * node_count);
  {
    f2ptr node_set = f2__bruno_graph__node_set(cause, this);
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
      f2__bruno_graph__add_node(cause, graph, random_node);
      index                 --;
      nodes_count_remaining --;
    }
  }
  {
    f2ptr edge_set = f2__bruno_graph__edge_set(cause, this);
    set__iteration(cause, edge_set, edge,
		   f2ptr left_node  = f2__bruno_graph_edge__left_node(cause, edge);
		   f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
		   if (raw__bruno_graph__contains_node(cause, graph, left_node) &&
		       raw__bruno_graph__contains_node(cause, graph, right_node)) {
		     raw__bruno_graph__add_edge(cause, graph, edge);
		   }
		   );
  }
  return graph;
}

f2ptr f2__bruno_graph__random_nonempty_strict_subgraph(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  if (raw__bruno_graph__node_count(cause, this) < 2) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "bruno_graph_must_have_at_least_two_nodes"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "bruno_graph-random_nonempty_strict_subgraph"));
    return f2larva__new(cause, 342, f2__bug__new(cause, f2integer__new(cause, 342), bug_frame));
  }
  return raw__bruno_graph__random_nonempty_strict_subgraph(cause, this);
}
def_pcfunk1(bruno_graph__random_nonempty_strict_subgraph, this, return f2__bruno_graph__random_nonempty_strict_subgraph(this_cause, this));

f2ptr raw__bruno_graph__minus(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__bruno_graph__new(cause);
  {
    f2ptr this__node_set = f2__bruno_graph__node_set(cause, this);
    set__iteration(cause, this__node_set, node,
		   if (! raw__bruno_graph__contains_node(cause, that, node)) {
		     f2__bruno_graph__add_node(cause, graph, node);
		   }
		   );
  }
  {
    f2ptr this__edge_set = f2__bruno_graph__edge_set(cause, this);
    set__iteration(cause, this__edge_set, edge,
		   f2ptr left_node  = f2__bruno_graph_edge__left_node(cause, edge);
		   f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
		   if (raw__bruno_graph__contains_node(cause, graph, left_node) &&
		       raw__bruno_graph__contains_node(cause, graph, right_node)) {
		     f2__bruno_graph__add_edge(cause, graph, edge);
		   }
		   );
  }
  return graph;
}

f2ptr f2__bruno_graph__minus(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__minus(cause, this, that);
}
def_pcfunk2(bruno_graph__minus, this, that, return f2__bruno_graph__minus(this_cause, this, that));

f2ptr raw__bruno_graph__node_isomorphisms(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr isomorphisms = nil;
  {
    f2ptr node__label    = f2__bruno_graph_node__label(cause, node);
    f2ptr this__node_set = f2__bruno_graph__node_set(cause, this);
    set__iteration(cause, this__node_set, this__node,
		   f2ptr this__node__label = f2__bruno_graph_node__label(cause, this__node);
		   if (raw__eq(cause, node__label, this__node__label)) {
		     f2ptr isomorphism = f2__bruno_graph_isomorphism__new(cause);
		     f2__bruno_graph_isomorphism__add_mapping(cause, isomorphism, node, this__node);
		     isomorphisms = f2cons__new(cause, isomorphism, isomorphisms);
		   }
		   );
  }
  return isomorphisms;
}

f2ptr f2__bruno_graph__node_isomorphisms(f2ptr cause, f2ptr this, f2ptr node) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__node_isomorphisms(cause, this, node);
}
def_pcfunk2(bruno_graph__node_isomorphisms, this, node, return f2__bruno_graph__node_isomorphisms(this_cause, this, node));

f2ptr raw__bruno_graph__edges_with_label_between_nodes(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edges_label_hash_right_node_hash_left_node_hash = f2__bruno_graph__edges_label_hash_right_node_hash_left_node_hash(cause, this);
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

f2ptr f2__bruno_graph__edges_with_label_between_nodes(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__bruno_graph__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, left_node)) ||
      (! raw__bruno_graph_node__is_type(cause, right_node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph__edges_with_label_between_nodes(cause, this, label, left_node, right_node);
}
def_pcfunk4(bruno_graph__edges_with_label_between_nodes, this, label, left_node, right_node, return f2__bruno_graph__edges_with_label_between_nodes(this_cause, this, label, left_node, right_node));

// bruno_graph_isomorphism

def_primobject_2_slot(bruno_graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);

f2ptr f2__bruno_graph_isomorphism__new(f2ptr cause) {
  f2ptr right_node_left_node_hash = f2__ptypehash__new(cause);
  f2ptr left_node_right_node_hash = f2__ptypehash__new(cause);
  return f2bruno_graph_isomorphism__new(cause, right_node_left_node_hash, left_node_right_node_hash);
}
def_pcfunk0(bruno_graph_isomorphism__new, return f2__bruno_graph_isomorphism__new(this_cause));

void raw__bruno_graph_isomorphism__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  f2ptr right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr left_node_right_node_hash = f2__bruno_graph_isomorphism__left_node_right_node_hash(cause, this);
  f2__ptypehash__add(cause, right_node_left_node_hash, left_node, right_node);
  f2__ptypehash__add(cause, left_node_right_node_hash, right_node, left_node);
}

f2ptr f2__bruno_graph_isomorphism__add_mapping(f2ptr cause, f2ptr this, f2ptr left_node, f2ptr right_node) {
  if ((! raw__bruno_graph_isomorphism__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, left_node)) ||
      (! raw__bruno_graph_node__is_type(cause, right_node))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__bruno_graph_isomorphism__add_mapping(cause, this, left_node, right_node);
  return nil;
}
def_pcfunk3(bruno_graph_isomorphism__add_mapping, this, left_node, right_node, return f2__bruno_graph_isomorphism__add_mapping(this_cause, this, left_node, right_node));

u64 raw__bruno_graph_isomorphism__mapping_count(f2ptr cause, f2ptr this) {
  f2ptr right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr key_count                 = f2__ptypehash__key_count(cause, right_node_left_node_hash);
  return f2integer__i(key_count, cause);
}

f2ptr f2__bruno_graph_isomorphism__mapping_count(f2ptr cause, f2ptr this) {
  if (! raw__bruno_graph_isomorphism__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr key_count                 = f2__ptypehash__key_count(cause, right_node_left_node_hash);
  return key_count;
}
def_pcfunk1(bruno_graph_isomorphism__mapping_count, this, return f2__bruno_graph_isomorphism__mapping_count(this_cause, this));

boolean_t raw__bruno_graph_isomorphism__is_disjoint_with(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__mapping_count = raw__bruno_graph_isomorphism__mapping_count(cause, this);
  u64 that__mapping_count = raw__bruno_graph_isomorphism__mapping_count(cause, that);
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
  f2ptr this__right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
  f2ptr that__right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, that);
  f2ptr that__left_node_right_node_hash = f2__bruno_graph_isomorphism__left_node_right_node_hash(cause, that);
  ptypehash__iteration(cause, this__right_node_left_node_hash, this__left_node, this__right_node,
		       if (raw__ptypehash__contains(cause, that__right_node_left_node_hash, this__left_node) ||
			   raw__ptypehash__contains(cause, that__left_node_right_node_hash, this__right_node)) {
			 return boolean__false;
		       }
		       );
  return boolean__true;
}

f2ptr f2__bruno_graph_isomorphism__is_disjoint_with(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__bruno_graph_isomorphism__is_type(cause, this)) ||
      (! raw__bruno_graph_isomorphism__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph_isomorphism__is_disjoint_with(cause, this, that);
}
def_pcfunk2(bruno_graph_isomorphism__is_disjoint_with, this, that, return f2__bruno_graph_isomorphism__is_disjoint_with(this_cause, this, that));

f2ptr raw__bruno_graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node) {
  f2ptr right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
  return raw__ptypehash__lookup(cause, right_node_left_node_hash, left_node);
}

f2ptr f2__bruno_graph_isomorphism__map_left_to_right(f2ptr cause, f2ptr this, f2ptr left_node) {
  if ((! raw__bruno_graph_isomorphism__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, left_node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph_isomorphism__map_left_to_right(cause, this, left_node);
}
def_pcfunk2(bruno_graph_isomorphism__map_left_to_right, this, left_node, return f2__bruno_graph_isomorphism__map_left_to_right(this_cause, this, left_node));

f2ptr raw__bruno_graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node) {
  f2ptr left_node_right_node_hash = f2__bruno_graph_isomorphism__left_node_right_node_hash(cause, this);
  return raw__ptypehash__lookup(cause, left_node_right_node_hash, right_node);
}

f2ptr f2__bruno_graph_isomorphism__map_right_to_left(f2ptr cause, f2ptr this, f2ptr right_node) {
  if ((! raw__bruno_graph_isomorphism__is_type(cause, this)) ||
      (! raw__bruno_graph_node__is_type(cause, right_node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph_isomorphism__map_right_to_left(cause, this, right_node);
}
def_pcfunk2(bruno_graph_isomorphism__map_right_to_left, this, right_node, return f2__bruno_graph_isomorphism__map_right_to_left(this_cause, this, right_node));

f2ptr raw__bruno_graph_isomorphism__union(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr isomorphism                     = f2__bruno_graph_isomorphism__new(cause);
  {
    f2ptr this__right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, this);
    ptypehash__iteration(cause, this__right_node_left_node_hash, left_node, right_node,
			 f2__bruno_graph_isomorphism__add_mapping(cause, isomorphism, left_node, right_node);
			 );
  }
  {
    f2ptr that__right_node_left_node_hash = f2__bruno_graph_isomorphism__right_node_left_node_hash(cause, that);
    ptypehash__iteration(cause, that__right_node_left_node_hash, left_node, right_node,
			 f2__bruno_graph_isomorphism__add_mapping(cause, isomorphism, left_node, right_node);
			 );
  }
  return isomorphism;
}

f2ptr f2__bruno_graph_isomorphism__union(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__bruno_graph_isomorphism__is_type(cause, this)) ||
      (! raw__bruno_graph_isomorphism__is_type(cause, this))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_graph_isomorphism__union(cause, this, that);
}
def_pcfunk2(bruno_graph_isomorphism__union, this, that, return f2__bruno_graph_isomorphism__union(this_cause, this, that));


// bruno_decomposition_lattice_node

def_primobject_4_slot(bruno_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph);

f2ptr raw__bruno_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph) {
  f2ptr between_graph          = f2__bruno_graph__new(cause);
  f2ptr parent_graph__edge_set = f2__bruno_graph__edge_set(cause, parent_graph);
  set__iteration(cause, parent_graph__edge_set, edge,
		 f2ptr left_node  = f2__bruno_graph_edge__left_node(cause, edge);
		 f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
		 if (raw__bruno_graph__contains_node(cause, left_child_graph, left_node)) {
		   if (raw__bruno_graph__contains_node(cause, right_child_graph, right_node)) {
		     f2__bruno_graph__add_edge(cause, between_graph, edge);
		   }
		 } else if (raw__bruno_graph__contains_node(cause, left_child_graph, right_node)) {
		   f2__bruno_graph__add_edge(cause, between_graph, edge);
		 }
		 );
  return f2bruno_decomposition_lattice_node__new(cause, parent_graph, left_child_graph, right_child_graph, between_graph);
}

f2ptr f2__bruno_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph) {
  if ((! raw__bruno_graph__is_type(cause, parent_graph)) ||
      (! raw__bruno_graph__is_type(cause, left_child_graph)) ||
      (! raw__bruno_graph__is_type(cause, right_child_graph))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_decomposition_lattice_node__new(cause, parent_graph, left_child_graph, right_child_graph);
}
def_pcfunk3(bruno_decomposition_lattice_node__new, parent_graph, left_child_graph, right_child_graph, return f2__bruno_decomposition_lattice_node__new(this_cause, parent_graph, left_child_graph, right_child_graph));

f2ptr raw__bruno_decomposition_lattice_node__combine_children_isomorphisms(f2ptr cause, f2ptr this, f2ptr left_child_isomorphisms, f2ptr right_child_isomorphisms, f2ptr graph) {
  f2ptr isomorphisms = nil;
  {
    f2ptr left_iter = left_child_isomorphisms;
    while (left_iter) {
      f2ptr left_isomorphism = f2__cons__car(cause, left_iter);
      {
	f2ptr right_iter = right_child_isomorphisms;
	while (right_iter) {
	  f2ptr right_isomorphism = f2__cons__car(cause, right_iter);
	  {
	    if (raw__bruno_graph_isomorphism__is_disjoint_with(cause, left_isomorphism, right_isomorphism)) {
	      boolean_t combined_isomorphism_is_valid = boolean__true;
	      f2ptr     between_graph                 = f2__bruno_decomposition_lattice_node__between_graph(cause, this);
	      f2ptr     between_graph__edge_set       = f2__bruno_graph__edge_set(cause, between_graph);
	      set__iteration(cause, between_graph__edge_set, edge,
			     f2ptr label             = f2__bruno_graph_edge__label(     cause, edge);
			     f2ptr left_node         = f2__bruno_graph_edge__left_node( cause, edge);
			     f2ptr right_node        = f2__bruno_graph_edge__right_node(cause, edge);
			     f2ptr edges             = f2__bruno_graph__edges_with_label_between_nodes(cause, between_graph, label, left_node, right_node);
			     f2ptr graph__left_node  = f2__bruno_graph_isomorphism__map_left_to_right(cause, left_isomorphism,  left_node);
			     f2ptr graph__right_node = f2__bruno_graph_isomorphism__map_left_to_right(cause, right_isomorphism, right_node);
			     f2ptr graph__edges      = f2__bruno_graph__edges_with_label_between_nodes(cause, graph, label, graph__left_node, graph__right_node);
			     if (raw__simple_length(cause, edges) != raw__simple_length(cause, graph__edges)) {
			       combined_isomorphism_is_valid = boolean__false;
			       goto raw__bruno_decomposition_lattice_node__combine_children_isomorphisms__found_unmatched_edge;
			     }
			     );
	    raw__bruno_decomposition_lattice_node__combine_children_isomorphisms__found_unmatched_edge:
	      if (combined_isomorphism_is_valid) {
		f2ptr isomorphism = f2__bruno_graph_isomorphism__union(cause, left_isomorphism, right_isomorphism);
		isomorphisms = f2cons__new(cause, isomorphism, isomorphisms);
	      }
	    }
	  }
	  right_iter = f2__cons__cdr(cause, right_iter);
	}
      }
      left_iter = f2__cons__cdr(cause, left_iter);
    }
  }
  return isomorphisms;
}

f2ptr f2__bruno_decomposition_lattice_node__combine_children_isomorphisms(f2ptr cause, f2ptr this, f2ptr left_child_isomorphisms, f2ptr right_child_isomorphisms, f2ptr graph) {
  if ((! raw__bruno_decomposition_lattice_node__is_type(cause, this)) ||
      (! raw__bruno_graph__is_type(cause, graph))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_decomposition_lattice_node__combine_children_isomorphisms(cause, this, left_child_isomorphisms, right_child_isomorphisms, graph);
}
def_pcfunk4(bruno_decomposition_lattice_node__combine_children_isomorphisms, this, left_child_isomorphisms, right_child_isomorphisms, graph, return f2__bruno_decomposition_lattice_node__combine_children_isomorphisms(this_cause, this, left_child_isomorphisms, right_child_isomorphisms, graph));


// bruno_decomposition_lattice

def_primobject_7_slot(bruno_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);

f2ptr f2__bruno_decomposition_lattice__new(f2ptr cause) {
  f2ptr graph_set             = f2__set__new(cause);
  f2ptr node_set              = f2__set__new(cause);
  f2ptr node_parent_hash      = f2__ptypehash__new(cause);
  f2ptr node_left_child_hash  = f2__ptypehash__new(cause);
  f2ptr node_right_child_hash = f2__ptypehash__new(cause);
  f2ptr leaf_graph_set        = f2__set__new(cause);
  f2ptr root_graph_set        = f2__set__new(cause);
  return f2bruno_decomposition_lattice__new(cause, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);
}
def_pcfunk0(bruno_decomposition_lattice__new, return f2__bruno_decomposition_lattice__new(this_cause));

f2ptr raw__bruno_decomposition_lattice__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set              = f2__bruno_decomposition_lattice__node_set(cause, this);
  f2ptr already_contains_node = f2__set__add(cause, node_set, node);
  if (already_contains_node == nil) {
    f2ptr graph_set      = f2__bruno_decomposition_lattice__graph_set(cause, this);
    f2ptr leaf_graph_set = f2__bruno_decomposition_lattice__leaf_graph_set(cause, this);
    {
      f2ptr parent_graph     = f2__bruno_decomposition_lattice_node__parent_graph(cause, node);
      f2__set__add(cause, graph_set, parent_graph);
      f2ptr node_parent_hash = f2__bruno_decomposition_lattice__node_parent_hash(cause, this);
      f2__ptypehash__add(cause, node_parent_hash, parent_graph, node);
    }
    {
      f2ptr left_child_graph     = f2__bruno_decomposition_lattice_node__left_child_graph(cause, node);
      f2__set__add(cause, graph_set, left_child_graph);
      f2ptr node_left_child_hash = f2__bruno_decomposition_lattice__node_left_child_hash(cause, this);
      f2__ptypehash__add(cause, node_left_child_hash, left_child_graph, node);
      if (raw__bruno_graph__node_count(cause, left_child_graph) == 1) {
	f2__set__add(cause, leaf_graph_set, left_child_graph);
      }
    }
    {
      f2ptr right_child_graph     = f2__bruno_decomposition_lattice_node__right_child_graph(cause, node);
      f2__set__add(cause, graph_set, right_child_graph);
      f2ptr node_right_child_hash = f2__bruno_decomposition_lattice__node_right_child_hash(cause, this);
      f2__ptypehash__add(cause, node_right_child_hash, right_child_graph, node);
      if (raw__bruno_graph__node_count(cause, right_child_graph) == 1) {
	f2__set__add(cause, leaf_graph_set, right_child_graph);
      }
    }
  }
  return already_contains_node;
}

f2ptr f2__bruno_decomposition_lattice__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  if ((! raw__bruno_decomposition_lattice__is_type(cause, this)) ||
      (! raw__bruno_decomposition_lattice_node__is_type(cause, node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bruno_decomposition_lattice__add_node(cause, this, node);
}
def_pcfunk2(bruno_decomposition_lattice__add_node, this, node, return f2__bruno_decomposition_lattice__add_node(this_cause, this, node));

void raw__bruno_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr maximum_isomorphic_graph = nil;
  u64   graph__node_count        = raw__bruno_graph__node_count(cause, graph);
  if (graph__node_count == 1) {
    return; // we're done.
  }
  f2ptr node_set = f2__bruno_decomposition_lattice__node_set(cause, this);
  set__iteration(cause, node_set, node,
		 f2ptr parent_graph = f2__bruno_decomposition_lattice_node__parent_graph(cause, node);
		 if (raw__bruno_graph__contains(cause, graph, parent_graph) &&
		     (raw__bruno_graph__node_count(cause, parent_graph) > (maximum_isomorphic_graph ? raw__bruno_graph__node_count(cause, maximum_isomorphic_graph) : 0))) {
		   maximum_isomorphic_graph = parent_graph;
		 }
		 );
  if (maximum_isomorphic_graph && (raw__bruno_graph__node_count(cause, graph) == raw__bruno_graph__node_count(cause, maximum_isomorphic_graph))) {
    return; // we're done.
  }
  if (maximum_isomorphic_graph == nil) {
    maximum_isomorphic_graph = f2__bruno_graph__random_nonempty_strict_subgraph(cause, graph);
    raw__bruno_decomposition_lattice__decompose_graph(cause, this, maximum_isomorphic_graph);
  }
  f2ptr remainder_graph = f2__bruno_graph__minus(cause, graph, maximum_isomorphic_graph);
  raw__bruno_decomposition_lattice__decompose_graph(cause, this, remainder_graph);
  f2ptr decomposition_lattice_node = f2__bruno_decomposition_lattice_node__new(cause, graph, maximum_isomorphic_graph, remainder_graph);
  raw__bruno_decomposition_lattice__add_node(cause, this, decomposition_lattice_node);
}

f2ptr f2__bruno_decomposition_lattice__decompose_graph(f2ptr cause, f2ptr this, f2ptr graph) {
  if ((! raw__bruno_decomposition_lattice__is_type(cause, this)) ||
      (! raw__bruno_graph__is_type(cause, graph))) {
    return f2larva__new(cause, 1, nil);
  }
  if (raw__bruno_graph__node_count(cause, graph) < 1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "cannot_decompose_empty_graph"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "bruno_decomposition_lattice-decompose_graph"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),     this);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "graph"),    graph);
    return f2larva__new(cause, 454, f2__bug__new(cause, f2integer__new(cause, 454), bug_frame));
  }
  raw__bruno_decomposition_lattice__decompose_graph(cause, this, graph);
  return nil;
}
def_pcfunk2(bruno_decomposition_lattice__decompose_graph, this, graph, return f2__bruno_decomposition_lattice__decompose_graph(this_cause, this, graph));

f2ptr raw__bruno_decomposition_lattice__subgraph_isomorphisms(f2ptr cause, f2ptr this, f2ptr graph) {
  f2ptr unsolved_graph_set = f2__set__new(cause);
  f2ptr alive_graph_set    = f2__set__new(cause);
  f2ptr dead_graph_set     = f2__set__new(cause);
  f2ptr graph_set          = f2__bruno_decomposition_lattice__graph_set(cause, this);
  set__iteration(cause, graph_set, graph,
		 f2__set__add(cause, unsolved_graph_set, graph);
		 );
  f2ptr isomorphisms_graph_hash       = f2__ptypehash__new(cause);
  f2ptr leaf_graph_set                = f2__bruno_decomposition_lattice__leaf_graph_set(cause, this);
  f2ptr lattice_node_left_child_hash  = f2__bruno_decomposition_lattice__node_left_child_hash(cause, this);
  f2ptr lattice_node_right_child_hash = f2__bruno_decomposition_lattice__node_right_child_hash(cause, this);
  set__iteration(cause, leaf_graph_set, leaf_graph,
		 f2ptr leaf_graph__node_set = f2__bruno_graph__node_set(cause, leaf_graph);
		 f2ptr leaf_graph__node     = nil;
		 set__iteration(cause, leaf_graph__node_set, leaf_graph__node_set__node,
				leaf_graph__node = leaf_graph__node_set__node;
				);
		 f2ptr leaf_graph__isomorphisms = f2__bruno_graph__node_isomorphisms(cause, graph, leaf_graph__node);
		 f2__set__remove(cause, unsolved_graph_set, leaf_graph);
		 if (leaf_graph__isomorphisms != nil) {
		   f2__set__add(cause, alive_graph_set, leaf_graph);
		   f2__ptypehash__add(cause, isomorphisms_graph_hash, leaf_graph, leaf_graph__isomorphisms);
		 } else {
		   f2__set__add(cause, dead_graph_set, leaf_graph);
		 }
		 );
  f2ptr node_parent_hash = f2__bruno_decomposition_lattice__node_parent_hash(cause, this);
  while (! raw__set__is_empty(cause, unsolved_graph_set)) {
    f2ptr solve_lattice_node = nil;
    f2ptr parent_graph       = nil;
    f2ptr left_child_graph   = nil;
    f2ptr right_child_graph  = nil;
    set__iteration(cause, unsolved_graph_set, unsolved_graph,
		   f2ptr lattice_node = f2__ptypehash__lookup(cause, node_parent_hash, unsolved_graph);
		   left_child_graph   = f2__bruno_decomposition_lattice_node__left_child_graph( cause, lattice_node);
		   right_child_graph  = f2__bruno_decomposition_lattice_node__right_child_graph(cause, lattice_node);
		   if (raw__set__contains(cause, alive_graph_set, left_child_graph) &&
		       raw__set__contains(cause, alive_graph_set, right_child_graph)) {
		     solve_lattice_node = lattice_node;
		     parent_graph       = unsolved_graph;
		     goto raw__bruno_decomposition_lattice__subgraph_isomorphisms__found_solve_lattice_node;
		   }
		   );
  raw__bruno_decomposition_lattice__subgraph_isomorphisms__found_solve_lattice_node:
    if (solve_lattice_node == nil) {
      break;
    }
    f2ptr left_child_graph__isomorphisms  = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, left_child_graph);
    f2ptr right_child_graph__isomorphisms = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, right_child_graph);
    f2ptr parent_graph__isomorphisms      = f2__bruno_decomposition_lattice_node__combine_children_isomorphisms(cause, solve_lattice_node, left_child_graph__isomorphisms, right_child_graph__isomorphisms, graph);
    if (parent_graph__isomorphisms == nil) {
      f2__set__remove(cause, unsolved_graph_set, parent_graph);
      f2__set__add(   cause,     dead_graph_set, parent_graph);
    } else {
      f2__set__add(cause, alive_graph_set, parent_graph);
      f2__ptypehash__add(cause, isomorphisms_graph_hash, parent_graph, parent_graph__isomorphisms);
      f2__set__remove(cause, alive_graph_set, left_child_graph);
      f2__set__add(cause, dead_graph_set, left_child_graph);
      f2__set__remove(cause, alive_graph_set, right_child_graph);
      f2__set__add(cause, dead_graph_set, right_child_graph);
    }
  }
  f2ptr isomorphisms = nil;
  set__iteration(cause, alive_graph_set, alive_graph,
		 f2ptr isomorphism = f2__ptypehash__lookup(cause, isomorphisms_graph_hash, alive_graph);
		 isomorphisms = f2cons__new(cause, isomorphism, isomorphisms);
		 );
  return isomorphisms;
}

// **

void f2__bruno_graph__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bruno_graph", "", &f2__bruno_graph__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __bruno_graph_node__symbol                 = new__symbol(cause, "bruno_graph_node");
  __bruno_graph_edge__symbol                 = new__symbol(cause, "bruno_graph_edge");
  __bruno_graph__symbol                      = new__symbol(cause, "bruno_graph");
  __bruno_graph_isomorphism__symbol          = new__symbol(cause, "bruno_graph_isomorphism");
  __bruno_decomposition_lattice_node__symbol = new__symbol(cause, "bruno_decomposition_lattice_node");
  __bruno_decomposition_lattice__symbol      = new__symbol(cause, "bruno_decomposition_lattice");
}

void f2__bruno_graph__initialize() {
  f2__bruno_graph__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // bruno_graph_node
  initialize_primobject_1_slot(bruno_graph_node, label);
  
  // bruno_graph_edge
  initialize_primobject_3_slot(bruno_graph_edge, label, left_node, right_node);
  
  // bruno_graph
  initialize_primobject_4_slot(bruno_graph, node_set, edge_set, edges_label_hash_right_node_hash_left_node_hash, edges_label_hash_left_node_hash_right_node_hash);
  
  f2__primcfunk__init__2(bruno_graph__add_node,                        this, node,                         "Add a bruno_graph_node to this bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__add_new_node,                    this, label,                        "Add a new bruno_graph_node to this bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__add_edge,                        this, edge,                         "Add a bruno_graph_edge to this bruno_graph.");
  f2__primcfunk__init__4(bruno_graph__add_new_edge,                    this, label, left_node, right_node, "Add a new bruno_graph_edge between two bruno_graph_nodes to this bruno_graph.");
  f2__primcfunk__init__1(bruno_graph__node_count,                      this,                               "Returns the number of nodes in this bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__contains_node,                   this, node,                         "Returns true if this bruno_graph contains a bruno_graph_node.");
  f2__primcfunk__init__2(bruno_graph__contains_edge,                   this, edge,                         "Returns true if this bruno_graph contains a bruno_graph_edge.");
  f2__primcfunk__init__2(bruno_graph__contains,                        this, graph,                        "Returns true if this bruno_graph contains a bruno_graph as a subgraph.");
  f2__primcfunk__init__1(bruno_graph__random_nonempty_strict_subgraph, this,                               "When this bruno_graph contains N nodes, returns a random subgraph with N/2 nodes.  This bruno_graph must have at least 2 nodes.");
  f2__primcfunk__init__2(bruno_graph__minus,                           this, that,                         "Returns a subgraph of this bruno_graph without the nodes in that bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__node_isomorphisms,               this, node,                         "Returns all single node isomorphisms between this bruno_graph and a bruno_graph_node.");
  f2__primcfunk__init__4(bruno_graph__edges_with_label_between_nodes,  this, label, left_node, right_node, "Returns edges directed from the left_node to the right_node that have the label in this bruno_graph.");
  
  // bruno_graph_isomorphism
  initialize_primobject_2_slot(bruno_graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);
  
  f2__primcfunk__init__3(bruno_graph_isomorphism__add_mapping,       this, left_node, right_node, "Add a bruno_graph_node mapping to a bruno_graph_isomorphism.");
  f2__primcfunk__init__1(bruno_graph_isomorphism__mapping_count,     this,                        "Returns the number of node mappings in this bruno_graph_isomorphism.");
  f2__primcfunk__init__2(bruno_graph_isomorphism__is_disjoint_with,  this, that,                  "Returns true if this bruno_graph_isomorphism is disjoint with that bruno_graph_isomorphism.");
  f2__primcfunk__init__2(bruno_graph_isomorphism__map_left_to_right, this, left_node,             "Maps a node on the left of this bruno_graph_isomorphism to the right.");
  f2__primcfunk__init__2(bruno_graph_isomorphism__map_right_to_left, this, right_node,            "Maps a node on the right of this bruno_graph_isomorphism to the left.");
  f2__primcfunk__init__2(bruno_graph_isomorphism__union,             this, that,                  "Returns a new bruno_graph_isomorphism representing the union between this bruno_graph_isomorphism and that bruno_graph_isomorphism.");
  
  // bruno_decomposition_lattice_node
  initialize_primobject_4_slot(bruno_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, between_graph);
  
  f2__primcfunk__init__4(bruno_decomposition_lattice_node__combine_children_isomorphisms, this, left_child_isomorphisms, right_child_isomorphisms, graph, "Combine children isomorphisms when they are non-overlapping.");
  
  // bruno_decomposition_lattice
  initialize_primobject_7_slot(bruno_decomposition_lattice, graph_set, node_set, node_parent_hash, node_left_child_hash, node_right_child_hash, leaf_graph_set, root_graph_set);
  
  f2__primcfunk__init__2(bruno_decomposition_lattice__add_node,        this, node,  "Add a bruno_decomposition_lattice_node to this bruno_decomposition_lattice.");
  f2__primcfunk__init__2(bruno_decomposition_lattice__decompose_graph, this, graph, "Decompose a bruno_graph into this bruno_decomposition_lattice.");
  
}

