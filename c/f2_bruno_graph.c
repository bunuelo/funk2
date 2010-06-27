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

def_primobject_4_slot(bruno_graph, node_set, edge_set, edges_left_node_hash, edges_right_node_hash);

f2ptr f2__bruno_graph__new(f2ptr cause) {
  f2ptr node_set              = f2__set__new(cause);
  f2ptr edge_set              = f2__set__new(cause);
  f2ptr edges_left_node_hash  = f2__ptypehash__new(cause);
  f2ptr edges_right_node_hash = f2__ptypehash__new(cause);
  return f2bruno_graph__new(cause, node_set, edge_set, edges_left_node_hash, edges_right_node_hash);
}
def_pcfunk0(bruno_graph__new, return f2__bruno_graph__new(this_cause));

f2ptr raw__bruno_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node_set = f2__bruno_graph__node_set(cause, this);
  f2ptr already_contains_node = f2__set__add(cause, node_set, node);
  return already_contains_node;
}

f2ptr f2__bruno_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__bruno_graph__is_type(cause, this)) {
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
    {
      f2ptr left_node = f2__bruno_graph_edge__left_node(cause, edge);
      f2__bruno_graph__add_node(cause, this, left_node);
      {
	f2ptr edges_left_node_hash = f2__bruno_graph__edges_left_node_hash(cause, this);
	f2ptr left_node_edges      = f2__ptypehash__lookup(cause, edges_left_node_hash, left_node);
	f2__ptypehash__add(cause, edges_left_node_hash, left_node, f2cons__new(cause, edge, left_node_edges));
      }
    }
    {
      f2ptr right_node = f2__bruno_graph_edge__right_node(cause, edge);
      f2__bruno_graph__add_node(cause, this, right_node);
      {
	f2ptr edges_right_node_hash = f2__bruno_graph__edges_right_node_hash(cause, this);
	f2ptr right_node_edges      = f2__ptypehash__lookup(cause, edges_right_node_hash, right_node);
	f2__ptypehash__add(cause, edges_right_node_hash, right_node, f2cons__new(cause, edge, right_node_edges));
      }
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


// bruno_graph_isomorphism

def_primobject_2_slot(bruno_graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);

f2ptr f2__bruno_graph_isomorphism__new(f2ptr cause) {
  f2ptr right_node_left_node_hash = f2__ptypehash__new(cause);
  f2ptr left_node_right_node_hash = f2__ptypehash__new(cause);
  return f2bruno_graph_isomorphism__new(cause, right_node_left_node_hash, left_node_right_node_hash);
}
def_pcfunk0(bruno_graph_isomorphism__new, return f2__bruno_graph_isomorphism__new(this_cause));


// bruno_decomposition_lattice_node

def_primobject_4_slot(bruno_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, edges);

f2ptr f2__bruno_decomposition_lattice_node__new(f2ptr cause, f2ptr parent_graph, f2ptr left_child_graph, f2ptr right_child_graph, f2ptr edges) {
  return f2bruno_decomposition_lattice_node__new(cause, parent_graph, left_child_graph, right_child_graph, edges);
}
def_pcfunk4(bruno_decomposition_lattice_node__new, parent_graph, left_child_graph, right_child_graph, edges, return f2__bruno_decomposition_lattice_node__new(this_cause, parent_graph, left_child_graph, right_child_graph, edges));


// bruno_decomposition_lattice

def_primobject_3_slot(bruno_decomposition_lattice, node_parent_hash, node_left_child_hash, node_right_child_hash);

f2ptr f2__bruno_decomposition_lattice__new(f2ptr cause) {
  f2ptr node_parent_hash      = f2__ptypehash__new(cause);
  f2ptr node_left_child_hash  = f2__ptypehash__new(cause);
  f2ptr node_right_child_hash = f2__ptypehash__new(cause);
  return f2bruno_decomposition_lattice__new(cause, node_parent_hash, node_left_child_hash, node_right_child_hash);
}
def_pcfunk0(bruno_decomposition_lattice__new, return f2__bruno_decomposition_lattice__new(this_cause));

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
  initialize_primobject_4_slot(bruno_graph, node_set, edge_set, edges_left_node_hash, edges_right_node_hash);
  
  f2__primcfunk__init__2(bruno_graph__add_node,     this, node,                         "Add a bruno_node to this bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__add_new_node, this, label,                        "Add a new node to this bruno_graph.");
  f2__primcfunk__init__2(bruno_graph__add_edge,     this, edge,                         "Add a bruno_edge to this bruno_graph.");
  f2__primcfunk__init__4(bruno_graph__add_new_edge, this, label, left_node, right_node, "Add a new edge between two bruno_nodes to this bruno_graph.");
  
  // bruno_graph_isomorphism
  initialize_primobject_2_slot(bruno_graph_isomorphism, right_node_left_node_hash, left_node_right_node_hash);
  
  // bruno_decomposition_lattice_node
  initialize_primobject_4_slot(bruno_decomposition_lattice_node, parent_graph, left_child_graph, right_child_graph, edges);
  
  // bruno_decomposition_lattice
  initialize_primobject_3_slot(bruno_decomposition_lattice, node_parent_hash, node_left_child_hash, node_right_child_hash);
  
}

