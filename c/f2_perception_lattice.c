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

def_primobject_1_slot(perception_graph, edges_node_hash);

f2ptr f2__perception_graph__new(f2ptr cause) {
  return f2perception_graph__new(cause, f2__ptypehash__new(cause));
}
def_pcfunk0(perception_graph__new, return f2__perception_graph__new(this_cause));

f2ptr f2__perception_graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge            = f2perception_graph_edge__new(cause, label, left_node, right_node);
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
  f2ptr left_node_ins_and_outs = f2__ptypehash__lookup(cause, edges_node_hash, left_node);
  if (! left_node_ins_and_outs) {
    left_node_ins_and_outs = f2cons__new(cause, nil, nil);
  }
  f2ptr right_node_ins_and_outs = f2__ptypehash__lookup(cause, edges_node_hash, right_node);
  if (! right_node_ins_and_outs) {
    right_node_ins_and_outs = f2cons__new(cause, nil, nil);
  }
  f2ptr left_node_outs = f2__cons__cdr(cause, left_node_ins_and_outs);
  f2ptr right_node_ins = f2__cons__car(cause, right_node_ins_and_outs);
  f2__cons__cdr__set(cause, left_node_ins_and_outs,  f2cons__new(cause, edge, left_node_outs));
  f2__cons__car__set(cause, right_node_ins_and_outs, f2cons__new(cause, edge, right_node_ins));
  return nil;
}

f2ptr f2__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__perception_graph__edges_node_hash(cause, this);
  return f2__ptypehash__lookup(cause, edges_node_hash, left_node);
}

f2ptr f2__perception_graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node);
  return f2__cons__car(cause, ins_and_outs);
}

f2ptr f2__perception_graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__perception_graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node);
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
  f2ptr prev_character = f2char__new(cause, ch);
  for (index = 1; index < string__length; index ++) {
    ch = raw__string__elt(cause, string, index);
    f2ptr character = f2char__new(cause, ch);
    f2ptr edge = f2perception_graph__add_edge(cause, this, new__symbol(cause, "->"), prev_character, character);
    prev_character = character;
  }
  return this;
}
def_pcfunk1(perception_graph__new_from_string, string, return f2__perception_graph__new_from_string(this_cause, string));

/*
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
  f2ptr edges = f2__perception_graph__edges(cause, this);
  f2ptr leftmost_edge = nil;
  {
    f2ptr iter = edges;
    while (iter) {
      leftmost_edge = iter;
      iter = f2__perception_graph_edge__left_node(cause, iter);
    }
  }
  f2ptr string = new__string(cause, "");
  if (leftmost_edge) {
    f2ptr left_node = f2__perception_graph_edge__left_node(cause, leftmost_edge);
    if (! raw__char__is_type(cause, left_node)) {
      return f2larva__new(cause, 1);
    }
    u8 ch = f2char__ch(left_node, cause);
    string = raw__string__append_char(cause, string, ch);
  }
  {
    f2ptr iter = leftmost_edge;
    while (iter) {
      f2ptr right_node = f2__perception_graph_edge__right_node(cause, iter);
      if (! raw__char__is_type(cause, right_node)) {
	return f2larva__new(cause, 1);
      }
      u8 ch = f2char__ch(right_node, cause);
      string = raw__string__append_char(cause, string, ch);
    }
  }
  return string;
}
def_pcfunk1(perception_graph__to_string, this, return f2__perception_graph__to_string(this_cause, this));
*/

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
  initialize_primobject_1_slot(perception_graph, edges_node_hash);
  
  f2__primcfunk__init__1(perception_graph__new_from_string, string, "creates a perception_graph of characters from a string.  (function used for debugging graph matching)");
  //f2__primcfunk__init__1(perception_graph__to_string, this, "creates a string from a perception_graph made from a string.  (function used for debugging graph matching)");
}

