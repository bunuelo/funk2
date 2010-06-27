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
  return f2__set__add(cause, node_set, node);
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

// **

void f2__bruno_graph__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bruno_graph", "", &f2__bruno_graph__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __bruno_graph_node__symbol = new__symbol(cause, "bruno_graph_node");
  __bruno_graph_edge__symbol = new__symbol(cause, "bruno_graph_edge");
  __bruno_graph__symbol      = new__symbol(cause, "bruno_graph");
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
  
  f2__primcfunk__init__2(bruno_graph__add_node, this, node, "");
  f2__primcfunk__init__2(bruno_graph__add_new_node, this, label, "");
  
}

