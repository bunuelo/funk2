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

def_primobject_5_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash, edges_edge_hash_left_node_hash, edges_edge_hash_right_node_hash);

f2ptr f2__graph_node__new(f2ptr cause, f2ptr label) {
  f2ptr edges_left_node_hash_edge_hash  = f2__ptypehash__new(cause);
  f2ptr edges_right_node_hash_edge_hash = f2__ptypehash__new(cause);
  f2ptr edges_edge_hash_left_node_hash  = f2__ptypehash__new(cause);
  f2ptr edges_edge_hash_right_node_hash = f2__ptypehash__new(cause);
  return f2graph_node__new(cause, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash, edges_edge_hash_left_node_hash, edges_edge_hash_right_node_hash);
}
def_pcfunk1(graph_node__new, label, return f2__graph_node__new(this_cause, label));


// graph_edge

def_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(graph_edge__new, label, left_node, right_node, return f2__graph_edge__new(this_cause, label, left_node, right_node));


// graph

def_primobject_4_slot(graph, variable_name_hash, root_node, node_label_hash, edge_type_label_hash);

f2ptr f2__graph__new(f2ptr cause) {
  f2ptr variable_name_hash   = nil;
  f2ptr root_node            = nil;
  f2ptr node_label_hash      = f2__ptypehash__new(cause);
  f2ptr edge_type_label_hash = f2__ptypehash__new(cause);
  return f2graph__new(cause, variable_name_hash, root_node, node_label_hash, edge_type_label_hash);
}
def_pcfunk0(graph__new, return f2__graph__new(this_cause));

f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  return nil;
}

f2ptr f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node_label) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__add_node(cause, this, node_label);
}
def_pcfunk2(graph__add_node, this, node_label, return f2__graph__add_node(this_cause, this, node_label));

f2ptr raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node, f2ptr right_node) {
  return nil;
}

f2ptr f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr edge_label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph_node__is_type(cause, left_node)) ||
      (! raw__graph_node__is_type(cause, right_node))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__graph__add_node(cause, this, edge_label, left_node, right_node);
}
def_pcfunk4(graph__add_edge, this, edge_label, left_node, right_node, return f2__graph__add_edge(this_cause, this, edge_label, left_node, right_node));

f2ptr f2graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph__primobject_type__new(cause);
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




f2ptr f2__graph__as__dot_code(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr node_codes = nil;
  {
    f2ptr nodes = f2__graph__nodes(cause, this);
    f2ptr iter = nodes;
    while (iter) {
      f2ptr node        = f2__cons__car(cause, iter);
      f2ptr node__label = f2__graph_node__label(cause, node);
      f2ptr color       = nil;
      if (f2__graph_variable__is_type(cause, node__label)) {
	color = new__string(cause, "#CF0000");
      } else {
	color = new__string(cause, "#000000");
      }
      f2ptr node_code   = f2__graphviz__node(cause, f2__graphviz__exp__as__name(cause, node__label), f2__graphviz__exp__as__label(cause, node__label), color);
      node_codes = f2cons__new(cause, node_code, node_codes);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr edge_codes = nil;
  {
    f2ptr edges = f2__graph__edges(cause, this);
    f2ptr iter = edges;
    while (iter) {
      f2ptr edge                    = f2__cons__car(cause, iter);
      f2ptr edge__label             = f2__graph_edge__label(cause, edge);
      f2ptr edge__left_node         = f2__graph_edge__left_node(cause, edge);
      f2ptr edge__right_node        = f2__graph_edge__right_node(cause, edge);
      f2ptr edge__left_node__label  = f2__graph_node__label(cause, edge__left_node);
      f2ptr edge__right_node__label = f2__graph_node__label(cause, edge__right_node);
      f2ptr edge_code               = f2__graphviz__raw_labelled_edge(cause, edge__label, f2__graphviz__exp__as__name(cause, edge__left_node__label), f2__graphviz__exp__as__name(cause, edge__right_node__label));
      edge_codes = f2cons__new(cause, edge_code, edge_codes);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return f2__graphviz__digraph(cause, f2list4__new(cause,
						   f2__graphviz__node_color(cause, new__string(cause, "#000000")),
						   f2__graphviz__edge_color(cause, new__string(cause, "#000000")),
						   f2__stringlist__rawcode(cause, node_codes),
						   f2__stringlist__rawcode(cause, edge_codes)));
}
def_pcfunk1(graph__as__dot_code, this, return f2__graph__as__dot_code(this_cause, this));


f2ptr f2__graph__abstract_frame_node_slot(f2ptr cause, f2ptr this, f2ptr slot_name) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr new_graph = f2__graph__new(cause);
  graph__node__iteration(cause, this, node,
			 f2ptr node__label = f2__graph_node__label(cause, node);
			 if (raw__frame__is_type(cause, node__label)) {
			   f2ptr node__slot_value = f2__frame__lookup_var_value(cause, node__label, slot_name, __funk2.primobject__frame.type_variable_not_defined__symbol);
			   if (! raw__eq(cause, node__slot_value, __funk2.primobject__frame.type_variable_not_defined__symbol)) {
			     f2__graph__add_node(cause, new_graph, node__slot_value);
			   }
			 }
			 );
  graph__edge__iteration(cause, this, edge,
			 f2ptr edge__label             = f2__graph_edge__label(cause, edge);
			 f2ptr edge__left_node         = f2__graph_edge__left_node(cause, edge);
			 f2ptr edge__left_node__label  = f2__graph_node__label(cause, edge__left_node);
			 f2ptr edge__right_node        = f2__graph_edge__right_node(cause, edge);
			 f2ptr edge__right_node__label = f2__graph_node__label(cause, edge__right_node);
			 if (raw__frame__is_type(cause, edge__left_node__label)) {
			   f2ptr edge__left_node__label__slot_value = f2__frame__lookup_var_value(cause, edge__left_node__label, slot_name, __funk2.primobject__frame.type_variable_not_defined__symbol);
			   if (! raw__eq(cause, edge__left_node__label__slot_value, __funk2.primobject__frame.type_variable_not_defined__symbol)) {
			     if (raw__frame__is_type(cause, edge__right_node__label)) {
			       f2ptr edge__right_node__label__slot_value = f2__frame__lookup_var_value(cause, edge__right_node__label, slot_name, __funk2.primobject__frame.type_variable_not_defined__symbol);
			       if (! raw__eq(cause, edge__right_node__label__slot_value, __funk2.primobject__frame.type_variable_not_defined__symbol)) {
				 f2__graph__add_edge(cause, new_graph, edge__label, edge__left_node__label__slot_value, edge__right_node__label__slot_value);
			       }
			     }
			   }
			 }
			 );
  return new_graph;
}
def_pcfunk2(graph__abstract_frame_node_slot, this, slot_name, return f2__graph__abstract_frame_node_slot(this_cause, this, slot_name));


// graph_variable

def_primobject_1_slot(graph_variable, name);

f2ptr f2__graph_variable__new(f2ptr cause, f2ptr name) {
  return f2graph_variable__new(cause, name);
}
def_pcfunk1(graph_variable__new, name, return f2__graph_variable__new(this_cause, name));

boolean_t raw__graph_variable__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__graph_variable__is_type(cause, that)) {
    return boolean__false;
  }
  return raw__eq(cause, f2__graph_variable__name(cause, this), f2__graph_variable__name(cause, that));
}

f2ptr f2__graph_variable__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__graph_variable__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__graph_variable__eq(cause, this, that));
}
def_pcfunk2(graph_variable__eq, this, that, return f2__graph_variable__eq(this_cause, this, that));

u64 raw__graph_variable__eq_hash_value(f2ptr cause, f2ptr this) {
  return raw__eq_hash_value(cause, f2__graph_variable__name(cause, this));
}

f2ptr f2__graph_variable__eq_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__graph_variable__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2integer__new(cause, raw__graph_variable__eq_hash_value(cause, this));
}
def_pcfunk1(graph_variable__eq_hash_value, this, return f2__graph_variable__eq_hash_value(this_cause, this));

f2ptr f2graph_variable__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph_variable__primobject_type__new(cause);
  {char* slot_name = "eq";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__funk);}
  return this;
}


// **

void f2__graph__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graph", "", &f2__graph__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __graph_node__symbol      = new__symbol(cause, "graph_node");
  __graph_edge__symbol      = new__symbol(cause, "graph_edge");
  __graph__symbol           = new__symbol(cause, "graph");
  __graph_variable__symbol  = new__symbol(cause, "graph_variable");
}

void f2__graph__initialize() {
  f2__graph__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // graph_node
  initialize_primobject_5_slot(graph_node, label, edges_left_node_hash_edge_hash, edges_right_node_hash_edge_hash, edges_edge_hash_left_node_hash, edges_edge_hash_right_node_hash);
  
  f2__primcfunk__init__1(graph_node__has_edges, this, "returns true if node has at least one edge, false otherwise.");
  
  // graph_edge
  initialize_primobject_3_slot(graph_edge, label, left_node, right_node);
  
  // graph
  initialize_primobject_4_slot(graph, variable_name_hash, root_node, node_label_hash, edge_type_label_hash);
  
  f2__primcfunk__init__2(graph__add_node,     this, node_label,                        "Add a node to this graph.");
  f2__primcfunk__init__4(graph__add_edge,     this, edge_label, left_node, right_node, "Add an edge between two nodes in this graph.");
  f2__primcfunk__init__1(graph__as__dot_code, this,                                    "Returns dot code in a string suitable for graphing with graphviz.");
  
  // graph_variable
  initialize_primobject_1_slot(graph_variable, name);
  
  {char* symbol_str = "eq"; __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph_variable__eq, this, that, cfunk, 0, "checks for equality between two graph variables."); __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq__funk = never_gc(cfunk);}
  {char* symbol_str = "eq_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph_variable__eq_hash_value, this, cfunk, 0, "returns hash value for graph variable."); __funk2.globalenv.object_type.primobject.primobject_type_graph_variable.eq_hash_value__funk = never_gc(cfunk);}
  
}

