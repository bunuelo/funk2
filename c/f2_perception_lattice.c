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

// graph_node

def_primobject_3_slot(graph_node, label, in_edge_hash, out_edge_hash);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label, f2ptr in_edge_hash, f2ptr out_edge_hash) {
  return f2graph_node__new(cause, label, in_edge_hash, out_edge_hash);
}

// graph_edge

def_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2graph_edge__new(cause, label, left_node, right_node);
}

// graph_edge_type

def_primobject_3_slot(graph_edge_type, label, left_node_hash, right_node_hash);

f2ptr f2__graph_edge_type__new(f2ptr cause, f2ptr label, f2ptr left_node_hash, f2ptr right_node_hash) {
  return f2graph_edge_type__new(cause, label, left_node_hash, right_node_hash);
}

// graph

def_primobject_4_slot(graph, is_rooted, root, node_label_hash, edge_type_label_hash);

f2ptr f2__graph__new(f2ptr cause) {
  return f2graph__new(cause, nil, nil, f2__ptypehash__new(cause));
}
def_pcfunk0(graph__new, return f2__graph__new(this_cause));

f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  return nil;
}

f2ptr f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  return nil;
}
def_pcfunk2(graph__add_node, this, node, return f2__graph__add_node(this_cause, this, node));


boolean_t raw__graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  return boolean__false;
}

f2ptr f2__graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__subtract_node(cause, this, node_label));
}
def_pcfunk2(graph__subtract_node, this, node_label, return f2__graph__subtract_node(this_cause, this, node_label));


void raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
}

f2ptr f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node_label, f2ptr right_node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  raw__graph__add_edge(cause, this, edge_label, left_node_label, right_node_label);
  return nil;
}
def_pcfunk4(graph__add_edge, this, edge_label, left_node_label, right_node_label, return f2__graph__add_edge(this_cause, this, edge_label, left_node_label, right_node_label));

boolean_t raw__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  f2ptr node_label_hash = f2__graph__node_label_hash(cause, this);
  f2ptr node            = f2__ptypehash__lookup(cause, node_label_hash, node_label);
  return (node != nil);
}

f2ptr f2__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__contains_node(cause, this, node_label));
}
def_pcfunk2(graph__contains_node, this, node_label, return f2__graph__contains_node(this_cause, this, node_label));

boolean_t raw__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__graph__contains_node(cause, this, left_node)) ||
      (! raw__graph__contains_node(cause, this, right_node))) {
    return boolean__false;
  }
  return boolean__false;
}

f2ptr f2__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__contains_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(graph__contains_edge, this, label, left_node, right_node, return f2__graph__contains_edge(this_cause, this, label, left_node, right_node));

boolean_t raw__graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return boolean__false;
}

f2ptr f2__graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__subtract_edge(cause, this, label, left_node, right_node));
}
def_pcfunk4(graph__subtract_edge, this, label, left_node, right_node, return f2__graph__subtract_edge(this_cause, this, label, left_node, right_node));

// graph-equals

boolean_t raw__graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return boolean__false;
}

f2ptr f2__graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__equals(cause, this, that));
}
def_pcfunk2(graph__equals, this, that, return f2__graph__equals(this_cause, this, that));

// graph-equals_hash_value

f2ptr raw__graph__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, 1);
}

f2ptr f2__graph__equals_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__equals_hash_value(cause, this);
}
def_pcfunk1(graph__equals_hash_value, this, return f2__graph__equals_hash_value(this_cause, this));

boolean_t raw__rooted_graph__is_type(f2ptr cause, f2ptr this) {
  if (raw__graph__is_type( cause, this) &&
      f2__graph__is_rooted(cause, this)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__rooted_graph__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__rooted_graph__is_type(cause, this));
}

f2ptr raw__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  f2ptr frame = f2__frame__new(cause);
  return frame;
}

f2ptr f2__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  if (! raw__rooted_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__rooted_graph__as__frame(cause, this);
}
def_pcfunk1(rooted_graph__as__frame, this, return f2__rooted_graph__as__frame(this_cause, this));

f2ptr f2graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph__primobject_type__new(cause);
  {char* slot_name = "equals";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__funk);}
  {char* slot_name = "equals_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__funk);}
  {char* slot_name = "part_not_contained_by"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__funk);}
  {char* slot_name = "as-frame";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__funk);}
  return this;
}

typedef struct funk2_n_choose_k_indices_s {
  u64  n;
  u64  k;
  u64* indices;
} funk2_n_choose_k_indices_t;

void funk2_n_choose_k_indices__init(funk2_n_choose_k_indices_t* this, u64 n, u64 k) {
  if (! (n >= k)) {
    error(nil, "raw__n_choose_k_indices__new error: assertion failed (n >= k).");
  }
  this->n = n;
  this->k = k;
  if (this->k != 0) {
    this->indices = (u64*)from_ptr(f2__malloc(sizeof(u64) * (this->k)));
  } else {
    this->indices = (u64*)NULL;
  }
  {
    u64 index;
    for (index = 0; index < this->k; index ++) {
      this->indices[index] = index;
    }
  }
}

void funk2_n_choose_k_indices__destroy(funk2_n_choose_k_indices_t* this) {
  if (this->indices != NULL) {
    f2__free(to_ptr(this->indices));
  }
}

void funk2_n_choose_k_indices__print(funk2_n_choose_k_indices_t* this) {
  printf("\n  n = " u64__fstr ", k = " u64__fstr " (", this->n, this->k);
  u64 index;
  for (index = 0; index < this->k; index ++) {
    printf(" " u64__fstr, this->indices[index]);
  }
  printf(")\n");
}

boolean_t funk2_n_choose_k_indices__increment(funk2_n_choose_k_indices_t* this) {
  boolean_t done                = boolean__false;
  boolean_t done_with_increment = boolean__false;
  s64       index               = this->k - 1;
  while ((! done_with_increment) && (index >= 0)) {
    this->indices[index] ++;
    if (this->indices[index] > ((this->n - 1) + index - (this->k - 1))) {
      index --;
    } else {
      done_with_increment = boolean__true;
    }
  }
  if (! done_with_increment) {
    done = boolean__true;
  } else {
    index ++;
    for (; index < this->k; index ++) {
      this->indices[index] = this->indices[index - 1] + 1;
    }
  }
  return done;
}

f2ptr raw__graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  return graph;
}

f2ptr f2__graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__intersect(cause, this, that);
}
def_pcfunk2(graph__intersect, this, that, return f2__graph__intersect(this_cause, this, that));

f2ptr raw__graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  return graph;
}

f2ptr f2__graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__union(cause, this, that);
}
def_pcfunk2(graph__union, this, that, return f2__graph__union(this_cause, this, that));

f2ptr raw__graph__copy(f2ptr cause, f2ptr this) {
  f2ptr graph = f2__graph__new(cause);
  return graph;
}

f2ptr f2__graph__copy(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__copy(cause, this);
}
def_pcfunk1(graph__copy, this, return f2__graph__copy(this_cause, this));


f2ptr raw__graph__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr graph = f2__graph__new(cause);
  return graph;
}

f2ptr f2__graph__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__part_not_contained_by(cause, this, that);
}
def_pcfunk2(graph__part_not_contained_by, this, that, return f2__graph__part_not_contained_by(this_cause, this, that));

// trans

def_primobject_2_slot(trans, remove, add);

f2ptr f2__trans__new(f2ptr cause) {
  return f2trans__new(cause, nil, nil);
}
def_pcfunk0(trans__new, return f2__trans__new(this_cause));

f2ptr f2__trans__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, 1);
}
def_pcfunk1(trans__equals_hash_value, this, return f2__trans__equals_hash_value(this_cause, this));

f2ptr f2__trans__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return nil;
}
def_pcfunk2(trans__equals, this, that, return f2__trans__equals(this_cause, this, that));

f2ptr raw__trans__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr remove;
  {
    f2ptr this__remove   = f2__trans__remove(cause, this);
    f2ptr that__remove   = f2__trans__remove(cause, that);
    f2ptr remove__remove = object__get_1(cause, this__remove, "part_not_contained_by", that__remove);
    f2ptr remove__add    = object__get_1(cause, that__remove, "part_not_contained_by", this__remove);
    remove               = f2trans__new(cause, remove__remove, remove__add);
  }
  f2ptr add;
  {
    f2ptr this__add   = f2__trans__add(cause, this);
    f2ptr that__add   = f2__trans__add(cause, that);
    f2ptr add__remove = object__get_1(cause, this__add, "part_not_contained_by", that__add);
    f2ptr add__add    = object__get_1(cause, that__add, "part_not_contained_by", this__add);
    add               = f2trans__new(cause, add__remove, add__add);
  }
  return f2trans__new(cause, remove, add);
}

f2ptr f2__trans__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__trans__is_type(cause, this)) ||
      (! raw__trans__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__trans__part_not_contained_by(cause, this, that);
}
def_pcfunk2(trans__part_not_contained_by, this, that, return f2__trans__part_not_contained_by(this_cause, this, that));

f2ptr f2trans__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2trans__primobject_type__new(cause);
  {char* slot_name = "equals";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.equals__funk);}
  {char* slot_name = "equals_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.equals_hash_value__funk);}
  {char* slot_name = "part_not_contained_by"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.part_not_contained_by__funk);}
  return this;
}


// difference
//
//   Takes any two object of a type that implements the part_not_contained_by get function)
//
//   Returns a trans object representing the difference between this and that.
//
f2ptr f2__difference(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr remove = object__get_1(cause, this, "part_not_contained_by", that);
  f2ptr add    = object__get_1(cause, that, "part_not_contained_by", this);
  return f2trans__new(cause, remove, add);
}
def_pcfunk2(difference, this, that, return f2__difference(this_cause, this, that));


// **

void f2__perception_lattice__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "perception_lattice", "", &f2__perception_lattice__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __graph_edge__symbol = new__symbol(cause, "graph_edge");
  __graph__symbol      = new__symbol(cause, "graph");
  __trans__symbol      = new__symbol(cause, "trans");
}

void f2__perception_lattice__initialize() {
  f2__perception_lattice__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // graph_node
  initialize_primobject_3_slot(graph_node, label, in_edge_hash, out_edge_hash);
  
  // graph_edge
  initialize_primobject_3_slot(graph_edge, label, left_node, right_node);
  
  // graph_edge_type
  initialize_primobject_3_slot(graph_edge_type, label, left_node_hash, right_node_hash);
  
  // graph
  initialize_primobject_4_slot(graph, is_rooted, root, node_label_hash, edge_type_label_hash);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__equals, this, that, cfunk, 0, "checks for equality between two graphs."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "part_not_contained_by"; __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__part_not_contained_by, this, that, cfunk, 0, "calculates the subgraph of this graph that is not contained in that graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__funk = never_gc(cfunk);}
  {char* symbol_str = "as-frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(rooted_graph__as__frame, this, cfunk, 0, "returns a rooted graph as a frame."); __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__2(graph__add_node,              this, node,                         "add a node to a graph by mutation.");
  f2__primcfunk__init__4(graph__add_edge,              this, label, left_node, right_node, "add an edge to a graph by mutation.");
  f2__primcfunk__init__2(graph__contains_node,         this, node,                         "returns boolean true if this graph contains node.");
  f2__primcfunk__init__4(graph__contains_edge,         this, label, left_node, right_node, "returns boolean true if this graph contains edge.");
  f2__primcfunk__init__2(graph__intersect,             this, that,                         "returns the intersection of two graphs.");
  f2__primcfunk__init__2(graph__union,                 this, that,                         "returns the union of two graphs.");
  f2__primcfunk__init__2(graph__subtract_node,         this, node,                         "subtract node from this graph.");
  f2__primcfunk__init__4(graph__subtract_edge,         this, label, left_node, right_node, "subtract an edge from a perception graph.");
  f2__primcfunk__init__1(graph__copy,                  this,                               "returns a copy of this graph.");
  f2__primcfunk__init__2(graph__part_not_contained_by, this, that,                         "determines the maximal part of this graph that is not contained in that graph.");
  
  // trans
  initialize_primobject_2_slot(trans, remove, add);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_trans.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(trans__equals, this, that, cfunk, 0, "checks for equality between two transs."); __funk2.globalenv.object_type.primobject.primobject_type_trans.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_trans.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(trans__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a trans."); __funk2.globalenv.object_type.primobject.primobject_type_trans.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "part_not_contained_by"; __funk2.globalenv.object_type.primobject.primobject_type_trans.part_not_contained_by__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(trans__part_not_contained_by, this, that, cfunk, 0, "determines the maximal part of this trans that is not contained in that trans."); __funk2.globalenv.object_type.primobject.primobject_type_trans.part_not_contained_by__funk = never_gc(cfunk);}
  
  // difference
  f2__primcfunk__init__2(difference, this, that, "returns a trans object representing the difference between two objects implementing the part_not_contained_by get type function.");
  
}

