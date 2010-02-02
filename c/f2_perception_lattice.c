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

def_primobject_3_slot(perception_graph, nodes, edges_node_hash, edge_structure_hash_value);

f2ptr f2__perception_graph__new(f2ptr cause) {
  return f2perception_graph__new(cause, nil, f2__ptypehash__new(cause), f2integer__new(cause, 1));
}
def_pcfunk0(perception_graph__new, return f2__perception_graph__new(this_cause));

f2ptr f2__perception_graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash   = f2__perception_graph__edges_node_hash(cause, this);
  f2ptr node_ins_and_outs = f2__ptypehash__lookup(cause, edges_node_hash, node);
  if (! node_ins_and_outs) {
    node_ins_and_outs = f2cons__new(cause, nil, nil);
    f2__ptypehash__add(cause, edges_node_hash, node, node_ins_and_outs);
    f2ptr nodes = f2__perception_graph__nodes(cause, this);
    nodes = f2cons__new(cause, node, nodes);
    f2__perception_graph__nodes__set(cause, this, nodes);
  }
  return node_ins_and_outs;
}

f2ptr f2__perception_graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge                    = f2perception_graph_edge__new(cause, label, left_node, right_node);
  f2ptr left_node_ins_and_outs  = f2__perception_graph__add_node(cause, this, left_node);
  f2ptr right_node_ins_and_outs = f2__perception_graph__add_node(cause, this, right_node);
  f2ptr left_node_outs          = f2__cons__cdr(cause, left_node_ins_and_outs);
  f2ptr right_node_ins          = f2__cons__car(cause, right_node_ins_and_outs);
  left_node_outs = f2cons__new(cause, edge, left_node_outs);
  right_node_ins = f2cons__new(cause, edge, right_node_ins);
  f2__cons__cdr__set(cause, left_node_ins_and_outs,  left_node_outs);
  f2__cons__car__set(cause, right_node_ins_and_outs, right_node_ins);
  {
    f2ptr edge_structure_hash_value    = f2__perception_graph__edge_structure_hash_value(cause, this);
    u64   edge_structure_hash_value__i = f2integer__i(edge_structure_hash_value, cause);
    u64   left_node_outs__length       = raw__simple_length(cause, left_node_outs);
    u64   right_node_ins__length       = raw__simple_length(cause, right_node_ins);
    edge_structure_hash_value__i /=  left_node_outs__length;
    edge_structure_hash_value__i /=  right_node_ins__length;
    edge_structure_hash_value__i *= (left_node_outs__length + 1);
    edge_structure_hash_value__i *= (right_node_ins__length + 1);
    edge_structure_hash_value__i *= raw__eq_hash_value(cause, label);
    f2__perception_graph__edge_structure_hash_value__set(cause, this, f2integer__new(cause, edge_structure_hash_value__i));
  }
  return edge;
}

f2ptr f2__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
  return f2__ptypehash__lookup(cause, edges_node_hash, node);
}

f2ptr f2__perception_graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__car(cause, ins_and_outs);
}

f2ptr f2__perception_graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(cause, this, node);
  return f2__cons__cdr(cause, ins_and_outs);
}

f2ptr f2__perception_graph__new_from_string(f2ptr cause, f2ptr string) {
  if (! raw__string__is_type(cause, string)) {
    return f2larva__new(cause, 1);
  }
  f2ptr this = f2__perception_graph__new(cause);
  u64 string__length = raw__string__length(cause, string);
  s64 index = 0;
  u8 ch = raw__string__elt(cause, string, index);
  f2ptr prev_node = f2cons__new(cause, f2char__new(cause, ch), nil);
  for (index = 1; index < string__length; index ++) {
    ch = raw__string__elt(cause, string, index);
    f2ptr node = f2cons__new(cause, f2char__new(cause, ch), nil);
    f2__perception_graph__add_edge(cause, this, new__symbol(cause, "->"), prev_node, node);
    prev_node = node;
  }
  return this;
}
def_pcfunk1(perception_graph__new_from_string, string, return f2__perception_graph__new_from_string(this_cause, string));

f2ptr raw__string__append_char(f2ptr cause, f2ptr this, u8 ch) {
  if (! raw__string__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  u64 string__length = f2string__length(this, cause);
  u8* string_copy = (u8*)from_ptr(f2__malloc(string__length + 1));
  f2string__str_copy(this, cause, string_copy);
  string_copy[string__length] = ch;
  return f2string__new(cause, string__length + 1, string_copy);
}

f2ptr f2__perception_graph__to_string(f2ptr cause, f2ptr this) {
  if (! raw__perception_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
  f2ptr leftmost_node = nil;
  {
    f2ptr node = f2__ptypehash__an_arbitrary_key(cause, edges_node_hash);
    while (node) {
      leftmost_node = node;
      f2ptr ins  = f2__perception_graph__node__ins(cause, this, node);
      if (ins) {
	f2ptr edge = f2__cons__car(cause, ins);
	node = f2__perception_graph_edge__left_node(cause, edge);
      } else {
	node = nil;
      }
    }
  }
  f2ptr string = new__string(cause, "");
  {
    f2ptr node = leftmost_node;
    while (node) {
      if (! raw__cons__is_type(cause, node)) {
	return f2larva__new(cause, 1);
      }
      f2ptr character = f2__cons__car(cause, node);
      if (! raw__char__is_type(cause, character)) {
	return f2larva__new(cause, 1);
      }
      u8 ch = f2char__ch(character, cause);
      string = raw__string__append_char(cause, string, ch);
      f2ptr outs  = f2__perception_graph__node__outs(cause, this, node);
      if (outs) {
	f2ptr edge = f2__cons__car(cause, outs);
	node = f2__perception_graph_edge__right_node(cause, edge);
      } else {
	node = nil;
      }
    }
  }
  return string;
}
def_pcfunk1(perception_graph__to_string, this, return f2__perception_graph__to_string(this_cause, this));

boolean_t raw__perception_graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__edge_structure_hash_value = f2__perception_graph__edge_structure_hash_value(cause, this);
  f2ptr that__edge_structure_hash_value = f2__perception_graph__edge_structure_hash_value(cause, that);
  if (! raw__eq(cause, this__edge_structure_hash_value, that__edge_structure_hash_value)) {
    return boolean__false;
  }
  f2ptr hash = f2__hash(cause);
  
  return boolean__true;
}

f2ptr f2__perception_graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__perception_graph__equals(cause, this, that));
}
def_pcfunk2(perception_graph__equals, this, that, return f2__perception_graph__equals(this_cause, this, that));

u64 raw__perception_graph__equals_hash_value(f2ptr cause, f2ptr this) {
  return 0;
}

f2ptr f2__perception_graph__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, raw__perception_graph__equals_hash_value(cause, this));
}
def_pcfunk1(perception_graph__equals_hash_value, this, return f2__perception_graph__equals_hash_value(this_cause, this));

f2ptr f2perception_graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2perception_graph__primobject_type__new(cause);
  {char* slot_name = "equals";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__funk);}
  {char* slot_name = "equals_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__funk);}
  return this;
}

// **

void f2__perception_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "perception_lattice", "", &f2__perception_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __perception_graph_edge__symbol = new__symbol(cause, "perception_graph_edge");
  __perception_graph__symbol      = new__symbol(cause, "perception_graph");
}

void f2__perception_lattice__initialize() {
  f2__perception_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // perception_graph_edge
  initialize_primobject_3_slot(perception_graph_edge, label, left_node, right_node);
  
  // perception_graph
  initialize_primobject_3_slot(perception_graph, nodes, edges_node_hash, edge_structure_hash_value);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(perception_graph__equals, this, that, cfunk, 0, "checks for equality between two graphs."); __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(perception_graph__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_perception_graph.equals_hash_value__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(perception_graph__new_from_string, string, "creates a perception_graph of characters from a string.  (function used for debugging graph matching)");
  f2__primcfunk__init__1(perception_graph__to_string, this, "creates a string from a perception_graph made from a string.  (function used for debugging graph matching)");
  
}

