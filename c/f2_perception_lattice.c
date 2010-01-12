// 
// Copyright (c) 2007-2009 Bo Morgan.
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

// perception_graph_edge

def_primobject_3_slot(perception_graph_edge, label, left_node, right_node);

f2ptr f2__perception_graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2perception_graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(perception_graph_edge__new, label, left_node, right_node, return f2__perception_graph_edge__new(this_cause, label, left_node, right_node));


// perception_graph

def_primobject_1_slot(perception_graph, edges);

f2ptr f2__perception_graph__new(f2ptr cause) {
  return f2perception_graph__new(cause, nil);
}
def_pcfunk0(perception_graph__new, return f2__perception_graph__new(this_cause));


// **

void f2__perception_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "perception_lattice", "", &f2__perception_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __perception_graph_edge__symbol = new__symbol(cause, "perception_graph_node");
  __perception_graph__symbol      = new__symbol(cause, "perception_graph");
}


void f2__perception_lattice__initialize() {
  f2__perception_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // perception_graph_edge
  initialize_primobject_3_slot(perception_graph_edge, label, left_node, right_node);
  
  // perception_graph
  initialize_primobject_1_slot(perception_graph, edges);
  
}

