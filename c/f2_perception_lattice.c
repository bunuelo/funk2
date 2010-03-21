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

// graph_edge

def_primobject_3_slot(graph_edge, label, left_node, right_node);

f2ptr f2__graph_edge__new(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2graph_edge__new(cause, label, left_node, right_node);
}
def_pcfunk3(graph_edge__new, label, left_node, right_node, return f2__graph_edge__new(this_cause, label, left_node, right_node));


// graph

def_primobject_6_slot(graph, is_rooted, root, nodes, edges, edges_node_hash, edge_structure_hash_value);

f2ptr f2__graph__new(f2ptr cause) {
  return f2graph__new(cause, nil, nil, nil, nil, f2__ptypehash__new(cause), f2integer__new(cause, 1));
}
def_pcfunk0(graph__new, return f2__graph__new(this_cause));

f2ptr raw__graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash   = f2__graph__edges_node_hash(cause, this);
  f2ptr node_ins_and_outs = f2__ptypehash__lookup(cause, edges_node_hash, node);
  if (! node_ins_and_outs) {
    node_ins_and_outs = f2cons__new(cause, nil, nil);
    f2__ptypehash__add(cause, edges_node_hash, node, node_ins_and_outs);
    f2ptr nodes = f2__graph__nodes(cause, this);
    nodes = f2cons__new(cause, node, nodes);
    f2__graph__nodes__set(cause, this, nodes);
  }
  return node_ins_and_outs;
}

f2ptr f2__graph__add_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__add_node(cause, this, node);
}
def_pcfunk2(graph__add_node, this, node, return f2__graph__add_node(this_cause, this, node));


boolean_t raw__graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__graph__edges_node_hash(cause, this);
  boolean_t node_was_removed = raw__ptypehash__contains(cause, edges_node_hash, node);
  f2ptr node_ins_and_outs = f2__ptypehash__lookup(cause, edges_node_hash, node);
  if (node_ins_and_outs) {
    f2ptr ins  = f2__cons__car(cause, node_ins_and_outs);
    {
      f2ptr iter = ins;
      while (iter) {
	f2ptr edge = f2__cons__car(cause, iter);
	f2ptr next = f2__cons__cdr(cause, iter);
	{
	  f2ptr label      = f2__graph_edge__label(cause, edge);
	  f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
	  f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	  raw__graph__subtract_edge(cause, this, label, left_node, right_node);
	}
	iter = next;
      }
    }
    f2ptr outs = f2__cons__cdr(cause, node_ins_and_outs);
    {
      f2ptr iter = outs;
      while (iter) {
	f2ptr edge = f2__cons__car(cause, iter);
	f2ptr next = f2__cons__cdr(cause, iter);
	{
	  f2ptr label      = f2__graph_edge__label(cause, edge);
	  f2ptr left_node  = f2__graph_edge__left_node(cause, edge);
	  f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	  raw__graph__subtract_edge(cause, this, label, left_node, right_node);
	}
	iter = next;
      }
    }
  }
  raw__ptypehash__remove(cause, edges_node_hash, node);
  f2ptr nodes = f2__graph__nodes(cause, this);
  {
    f2ptr prev = nil;
    f2ptr iter = nodes;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr nodes__node = f2__cons__car(cause, iter);
      if (raw__eq(cause, nodes__node, node)) {
	if (prev) {
	  f2__cons__cdr__set(cause, prev, next);
	} else {
	  f2__graph__nodes__set(cause, this, next);
	}
      }
      prev = iter;
      iter = next;
    }
  }
  return node_was_removed;
}

f2ptr f2__graph__subtract_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__subtract_node(cause, this, node));
}
def_pcfunk2(graph__subtract_node, this, node, return f2__graph__subtract_node(this_cause, this, node));


f2ptr raw__graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge                    = f2graph_edge__new(cause, label, left_node, right_node);
  f2ptr left_node_ins_and_outs  = f2__graph__add_node(cause, this, left_node);
  f2ptr right_node_ins_and_outs = f2__graph__add_node(cause, this, right_node);
  f2ptr left_node_outs          = f2__cons__cdr(cause, left_node_ins_and_outs);
  f2ptr right_node_ins          = f2__cons__car(cause, right_node_ins_and_outs);
  left_node_outs = f2cons__new(cause, edge, left_node_outs);
  right_node_ins = f2cons__new(cause, edge, right_node_ins);
  f2__cons__cdr__set(cause, left_node_ins_and_outs,  left_node_outs);
  f2__cons__car__set(cause, right_node_ins_and_outs, right_node_ins);
  {
    f2ptr edge_structure_hash_value    = f2__graph__edge_structure_hash_value(cause, this);
    u64   edge_structure_hash_value__i = f2integer__i(edge_structure_hash_value, cause);
    u64   left_node_outs__length       = raw__simple_length(cause, left_node_outs);
    u64   right_node_ins__length       = raw__simple_length(cause, right_node_ins);
    edge_structure_hash_value__i /=  left_node_outs__length;
    edge_structure_hash_value__i /=  right_node_ins__length;
    edge_structure_hash_value__i *= (left_node_outs__length + 1);
    edge_structure_hash_value__i *= (right_node_ins__length + 1);
    edge_structure_hash_value__i *= raw__eq_hash_value(cause, label);
    f2__graph__edge_structure_hash_value__set(cause, this, f2integer__new(cause, edge_structure_hash_value__i));
  }
  f2__graph__edges__set(cause, this, f2cons__new(cause, edge, f2__graph__edges(cause, this)));
  return edge;
}

f2ptr f2__graph__add_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__add_edge(cause, this, label, left_node, right_node);
}
def_pcfunk4(graph__add_edge, this, label, left_node, right_node, return f2__graph__add_edge(this_cause, this, label, left_node, right_node));

f2ptr raw__graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr edges_node_hash = f2__graph__edges_node_hash(cause, this);
  return f2__ptypehash__lookup(cause, edges_node_hash, node);
}

f2ptr f2__graph__node__ins_and_outs(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__node__ins_and_outs(cause, this, node);
}
def_pcfunk2(graph__node__ins_and_outs, this, node, return f2__graph__node__ins_and_outs(this_cause, this, node));

boolean_t raw__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  return (f2__graph__node__ins_and_outs(cause, this, node) != nil);
}

f2ptr f2__graph__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__contains_node(cause, this, node));
}
def_pcfunk2(graph__contains_node, this, node, return f2__graph__contains_node(this_cause, this, node));

f2ptr raw__graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__graph__node__ins_and_outs(cause, this, node);
  return f2__cons__car(cause, ins_and_outs);
}

f2ptr f2__graph__node__ins(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__node__ins(cause, this, node);
}
def_pcfunk2(graph__node__ins, this, node, return f2__graph__node__ins(this_cause, this, node));


f2ptr raw__graph__node__ins__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr ins) {
  f2ptr ins_and_outs = f2__graph__node__ins_and_outs(cause, this, node);
  return f2__cons__car__set(cause, ins_and_outs, ins);
}

f2ptr f2__graph__node__ins__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr ins) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__node__ins__set(cause, this, node, ins);
}
def_pcfunk3(graph__node__ins__set, this, node, ins, return f2__graph__node__ins__set(this_cause, this, node, ins));


f2ptr raw__graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr ins_and_outs = f2__graph__node__ins_and_outs(cause, this, node);
  return f2__cons__cdr(cause, ins_and_outs);
}

f2ptr f2__graph__node__outs(f2ptr cause, f2ptr this, f2ptr node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__node__outs(cause, this, node);
}
def_pcfunk2(graph__node__outs, this, node, return f2__graph__node__outs(this_cause, this, node));


f2ptr raw__graph__node__outs__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr outs) {
  f2ptr ins_and_outs = f2__graph__node__ins_and_outs(cause, this, node);
  return f2__cons__cdr__set(cause, ins_and_outs, outs);
}

f2ptr f2__graph__node__outs__set(f2ptr cause, f2ptr this, f2ptr node, f2ptr outs) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__node__outs__set(cause, this, node, outs);
}
def_pcfunk3(graph__node__outs__set, this, node, outs, return f2__graph__node__outs__set(this_cause, this, node, outs));


boolean_t raw__graph__contains_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if ((! raw__graph__contains_node(cause, this, left_node)) ||
      (! raw__graph__contains_node(cause, this, right_node))) {
    return boolean__false;
  }
  f2ptr left_node__outs = raw__graph__node__outs(cause, this, left_node);
  {
    f2ptr iter = left_node__outs;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__graph_edge__label(     cause, edge);
	f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
	if (raw__eq(cause, label,      edge__label) &&
	    raw__eq(cause, right_node, edge__right_node)) {
	  return boolean__true;
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
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

f2ptr f2__graph__new_from_string(f2ptr cause, f2ptr string) {
  if (! raw__string__is_type(cause, string)) {
    return f2larva__new(cause, 1);
  }
  f2ptr this = f2__graph__new(cause);
  u64 string__length = raw__string__length(cause, string);
  s64 index = 0;
  u8 ch = raw__string__elt(cause, string, index);
  f2ptr prev_node = f2cons__new(cause, f2char__new(cause, ch), nil);
  for (index = 1; index < string__length; index ++) {
    ch = raw__string__elt(cause, string, index);
    f2ptr node = f2cons__new(cause, f2char__new(cause, ch), nil);
    f2__graph__add_edge(cause, this, new__symbol(cause, "->"), prev_node, node);
    prev_node = node;
  }
  return this;
}
def_pcfunk1(graph__new_from_string, string, return f2__graph__new_from_string(this_cause, string));

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

f2ptr f2__graph__to_string(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr edges_node_hash = f2__graph__edges_node_hash(cause, this);
  f2ptr leftmost_node = nil;
  {
    f2ptr node = f2__ptypehash__an_arbitrary_key(cause, edges_node_hash);
    while (node) {
      leftmost_node = node;
      f2ptr ins  = f2__graph__node__ins(cause, this, node);
      if (ins) {
	f2ptr edge = f2__cons__car(cause, ins);
	node = f2__graph_edge__left_node(cause, edge);
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
      f2ptr outs  = f2__graph__node__outs(cause, this, node);
      if (outs) {
	f2ptr edge = f2__cons__car(cause, outs);
	node = f2__graph_edge__right_node(cause, edge);
      } else {
	node = nil;
      }
    }
  }
  return string;
}
def_pcfunk1(graph__to_string, this, return f2__graph__to_string(this_cause, this));

// graph-equals

boolean_t raw__graph__nodes_contains(f2ptr cause, f2ptr this, f2ptr nodes) {
  f2ptr iter = nodes;
  while (iter) {
    f2ptr node = f2__cons__car(cause, iter);
    if (! raw__graph__contains_node(cause, this, node)) {
      return boolean__false;
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return boolean__true;
}

boolean_t raw__graph__nodes_equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nodes         = f2__graph__nodes(cause, this);
  u64   this__nodes__length = raw__simple_length(cause, this__nodes);
  f2ptr that__nodes         = f2__graph__nodes(cause, this);
  u64   that__nodes__length = raw__simple_length(cause, that__nodes);
  if (this__nodes__length != that__nodes__length) {
    return boolean__false;
  }
  return raw__graph__nodes_contains(cause, this, that__nodes);
}

boolean_t raw__graph__edges_contains(f2ptr cause, f2ptr this, f2ptr edges) {
  f2ptr iter = edges;
  while (iter) {
    f2ptr edge = f2__cons__car(cause, iter);
    {
      f2ptr label      = f2__graph_edge__label(     cause, edge);
      f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
      f2ptr right_node = f2__graph_edge__right_node(cause, edge);
      if (! raw__graph__contains_edge(cause, this, label, left_node, right_node)) {
	return boolean__false;
      }
    }
    iter = f2__cons__cdr(cause, iter);
  }
  return boolean__true;
}

boolean_t raw__graph__edges_equals(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__edges         = f2__graph__edges(cause, this);
  u64   this__edges__length = raw__simple_length(cause, this__edges);
  f2ptr that__edges         = f2__graph__edges(cause, this);
  u64   that__edges__length = raw__simple_length(cause, that__edges);
  if (this__edges__length != that__edges__length) {
    return boolean__false;
  }
  return raw__graph__edges_contains(cause, this, that__edges);
}

boolean_t raw__graph__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__graph__nodes_equals(cause, this, that)) {
    return boolean__false;
  }
  if (! raw__graph__edges_equals(cause, this, that)) {
    return boolean__false;
  }
  return boolean__true;
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
  u64 total_hash_value = 1;
  {
    f2ptr nodes      = f2__graph__nodes(cause, this);
    {
      f2ptr iter = nodes;
      while (iter) {
	f2ptr node       = f2__cons__car(cause, iter);
	f2ptr hash_value = f2__object__eq_hash_value(cause, node);
	if (raw__larva__is_type(cause, hash_value) || (! raw__integer__is_type(cause, hash_value))) {
	  return hash_value;
	}
	u64 hash_value__i = f2integer__i(hash_value, cause);
	total_hash_value *= ((hash_value__i != 0) ? hash_value__i : 1);
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr edges = f2__graph__edges(cause, this);
    {
      f2ptr edges_iter = edges;
      while (edges_iter) {
	f2ptr edge = f2__cons__car(cause, edges_iter);
	{
	  f2ptr label      = f2__graph_edge__label(     cause, edge);
	  f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
	  f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	  {
	    f2ptr hash_value = f2__object__eq_hash_value(cause, label);
	    if (raw__larva__is_type(cause, hash_value) || (! raw__integer__is_type(cause, hash_value))) {
	      return hash_value;
	    }
	    u64 hash_value__i = f2integer__i(hash_value, cause);
	    total_hash_value *= ((hash_value__i != 0) ? hash_value__i : 1);
	  }
	  {
	    f2ptr hash_value = f2__object__eq_hash_value(cause, left_node);
	    if (raw__larva__is_type(cause, hash_value) || (! raw__integer__is_type(cause, hash_value))) {
	      return hash_value;
	    }
	    u64 hash_value__i = f2integer__i(hash_value, cause);
	    total_hash_value *= ((hash_value__i != 0) ? hash_value__i : 1);
	  }
	  {
	    f2ptr hash_value = f2__object__eq_hash_value(cause, right_node);
	    if (raw__larva__is_type(cause, hash_value) || (! raw__integer__is_type(cause, hash_value))) {
	      return hash_value;
	    }
	    u64 hash_value__i = f2integer__i(hash_value, cause);
	    total_hash_value *= ((hash_value__i != 0) ? hash_value__i : 1);
	  }
	}
	edges_iter = f2__cons__cdr(cause, edges_iter);
      }
    }
  }
  return f2integer__new(cause, total_hash_value);
}

f2ptr f2__graph__equals_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__equals_hash_value(cause, this);
}
def_pcfunk1(graph__equals_hash_value, this, return f2__graph__equals_hash_value(this_cause, this));

f2ptr f2graph__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2graph__primobject_type__new(cause);
  {char* slot_name = "equals";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__funk);}
  {char* slot_name = "equals_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__funk);}
  {char* slot_name = "part_not_contained_by"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__funk);}
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

f2ptr raw__graph__subgraphs_of_node_range(f2ptr cause, f2ptr this, u64 min_node_count, u64 max_node_count) {
  f2ptr nodes         = f2__graph__nodes(cause, this);
  u64   nodes__length = raw__simple_length(cause, nodes);
  if (min_node_count > max_node_count) {
    return nil;
  }
  if (nodes__length < min_node_count) {
    return nil;
  }
  if (nodes__length < max_node_count) {
    max_node_count = nodes__length;
  }
  f2ptr* nodes_array = (f2ptr*)alloca(sizeof(f2ptr) * nodes__length);
  {
    u64   index = 0;
    f2ptr iter  = nodes;
    while (iter) {
      f2ptr node         = f2__cons__car(cause, iter);
      nodes_array[index] = node;
      iter               = f2__cons__cdr(cause, iter);
      index ++;
    }
  }
  f2ptr subgraphs = nil;
  {
    u64 node_count;
    for (node_count = min_node_count; node_count <= max_node_count; node_count ++) {
      funk2_n_choose_k_indices_t node_choose;
      funk2_n_choose_k_indices__init(&node_choose, nodes__length, node_count);
      boolean_t done = boolean__false;
      while (! done) {
	{
	  //printf("\nnode_choose: "); funk2_n_choose_k_indices__print(&node_choose);
	  
	  f2ptr node_hash = f2__ptypehash__new(cause);
	  {
	    u64 index;
	    for (index = 0; index < node_choose.k; index ++) {
	      f2ptr node = nodes_array[node_choose.indices[index]];
	      f2__ptypehash__add(cause, node_hash, node, __funk2.globalenv.true__symbol);
	    }
	  }
	  {
	    f2ptr graph__edges = nil;
	    {
	      u64 index;
	      for (index = 0; index < node_choose.k; index ++) {
		f2ptr node = nodes_array[node_choose.indices[index]];
		f2ptr outs = f2__graph__node__outs(cause, this, node);
		{
		  f2ptr iter = outs;
		  while (iter) {
		    f2ptr edge       = f2__cons__car(cause, iter);
		    f2ptr right_node = f2__graph_edge__right_node(cause, edge);
		    if (f2__ptypehash__lookup(cause, node_hash, right_node)) {
		      graph__edges = f2cons__new(cause, edge, graph__edges);
		    }
		    iter = f2__cons__cdr(cause, iter);
		  }
		}
	      }
	    }
	    {
	      u64    graph__edges__length = raw__simple_length(cause, graph__edges);
	      u64    edges_array__length  = graph__edges__length;
	      f2ptr* edges_array          = (f2ptr*)alloca(sizeof(f2ptr) * edges_array__length);
	      {
		u64   index = 0;
		f2ptr iter  = graph__edges;
		while (iter) {
		  f2ptr edge         = f2__cons__car(cause, iter);
		  edges_array[index] = edge;
		  index ++;
		  iter = f2__cons__cdr(cause, iter);
		}
	      }
	      {
		u64 edge_choose_k;
		for (edge_choose_k = 0; edge_choose_k <= edges_array__length; edge_choose_k ++) {
		  funk2_n_choose_k_indices_t edge_choose;
		  funk2_n_choose_k_indices__init(&edge_choose, edges_array__length, edge_choose_k);
		  boolean_t edges_done = boolean__false;
		  while (! edges_done) {
		    //printf("\nedge_choose: "); funk2_n_choose_k_indices__print(&edge_choose);
		    {
		      f2ptr graph = f2__graph__new(cause);
		      {
			u64 index;
			for (index = 0; index < node_choose.k; index ++) {
			  f2ptr node = nodes_array[node_choose.indices[index]];
			  f2__graph__add_node(cause, graph, node);
			}
		      }
		      {
			u64 index;
			for (index = 0; index < edge_choose.k; index ++) {
			  f2ptr edge = edges_array[edge_choose.indices[index]];
			  {
			    f2ptr edge__label      = f2__graph_edge__label(     cause, edge);
			    f2ptr edge__left_node  = f2__graph_edge__left_node( cause, edge);
			    f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
			    f2__graph__add_edge(cause, graph, edge__label, edge__left_node, edge__right_node);
			  }
			}
		      }
		      subgraphs = f2cons__new(cause, graph, subgraphs);
		    }
		    edges_done = funk2_n_choose_k_indices__increment(&edge_choose);
		  }
		  funk2_n_choose_k_indices__destroy(&edge_choose);
		}
	      }
	    }
	  }
	  done = funk2_n_choose_k_indices__increment(&node_choose);
	}
      }
      funk2_n_choose_k_indices__destroy(&node_choose);
    }
  }
  return subgraphs;
}

f2ptr f2__graph__subgraphs_of_node_range(f2ptr cause, f2ptr this, f2ptr min_node_count, f2ptr max_node_count) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, min_node_count)) ||
      (! raw__integer__is_type(cause, max_node_count))) {
    return f2larva__new(cause, 1);
  }
  s64 min_node_count__i = f2integer__i(min_node_count, cause);
  s64 max_node_count__i = f2integer__i(max_node_count, cause);
  if ((min_node_count__i < 0) ||
      (max_node_count__i < 0)) {
    return f2larva__new(cause, 5);
  }
  return raw__graph__subgraphs_of_node_range(cause, this, min_node_count__i, max_node_count__i);
}
def_pcfunk3(graph__subgraphs_of_node_range, this, min_node_count, max_node_count, return f2__graph__subgraphs_of_node_range(this_cause, this, min_node_count, max_node_count));

f2ptr raw__graph__subgraphs(f2ptr cause, f2ptr this) {
  f2ptr nodes         = f2__graph__nodes(cause, this);
  u64   nodes__length = raw__simple_length(cause, nodes);
  return raw__graph__subgraphs_of_node_range(cause, this, 0, nodes__length);
}

f2ptr f2__graph__subgraphs(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__subgraphs(cause, this);
}
def_pcfunk1(graph__subgraphs, this, return f2__graph__subgraphs(this_cause, this));

f2ptr raw__graph__intersect(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__nodes         = f2__graph__nodes(cause, this);
  f2ptr that__nodes         = f2__graph__nodes(cause, that);
  u64   this__nodes__length = raw__simple_length(cause, this__nodes);
  u64   that__nodes__length = raw__simple_length(cause, that__nodes);
  f2ptr small;
  f2ptr large;
  u64   small__nodes__length;
  u64   large__nodes__length;
  if (this__nodes__length < that__nodes__length) {
    small                = this;
    large                = that;
    small__nodes__length = this__nodes__length;
    large__nodes__length = that__nodes__length;
  } else {
    small                = that;
    large                = this;
    small__nodes__length = that__nodes__length;
    large__nodes__length = this__nodes__length;
  }
  f2ptr new_graph = f2__graph__new(cause);
  {
    f2ptr small__nodes = f2__graph__nodes(cause, small);
    f2ptr small__edges = f2__graph__edges(cause, small);
    {
      f2ptr iter = small__nodes;
      while (iter) {
	f2ptr node = f2__cons__car(cause, iter);
	if (f2__graph__contains_node(cause, large, node)) {
	  f2__graph__add_node(cause, new_graph, node);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
    {
      f2ptr iter = small__edges;
      while (iter) {
	f2ptr small__edge = f2__cons__car(cause, iter);
	{
	  f2ptr small__left_node = f2__graph_edge__left_node(cause, small__edge);
	  if (f2__graph__contains_node(cause, large, small__left_node)) {
	    f2ptr shared__left_node = small__left_node;
	    f2ptr small__right_node = f2__graph_edge__right_node(cause, small__edge);
	    if (f2__graph__contains_node(cause, large, small__right_node)) {
	      f2ptr shared__right_node = small__right_node;
	      f2ptr small__label = f2__graph_edge__label(cause, small__edge);
	      f2ptr large__left_node__outs = f2__graph__node__outs(cause, large, shared__left_node);
	      {
		f2ptr large_outs_iter = large__left_node__outs;
		while (large_outs_iter) {
		  f2ptr large__left_node__out_edge             = f2__cons__car(cause, large_outs_iter);
		  f2ptr large__left_node__out_edge__right_node = f2__graph_edge__right_node(cause, large__left_node__out_edge);
		  if (raw__eq(cause, shared__right_node, large__left_node__out_edge__right_node)) {
		    f2ptr large__label = f2__graph_edge__label(cause, large__left_node__out_edge);
		    if (raw__eq(cause, small__label, large__label)) {
		      f2ptr shared__label = small__label;
		      f2__graph__add_edge(cause, new_graph, shared__label, shared__left_node, shared__right_node);
		    }
		  }
		  large_outs_iter = f2__cons__cdr(cause, large_outs_iter);
		}
	      }
	    }
	  }
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return new_graph;
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
  f2ptr new_graph = f2__graph__new(cause);
  {
    f2ptr this__nodes         = f2__graph__nodes(cause, this);
    f2ptr that__nodes         = f2__graph__nodes(cause, that);
    u64   this__nodes__length = raw__simple_length(cause, this__nodes);
    u64   that__nodes__length = raw__simple_length(cause, that__nodes);
    {
      f2ptr small__nodes;
      f2ptr large__nodes;
      if (this__nodes__length < that__nodes__length) {
	small__nodes = this__nodes;
	large__nodes = that__nodes;
      } else {
	small__nodes = that__nodes;
	large__nodes = this__nodes;
      }
      {
	f2ptr iter = large__nodes;
	while (iter) {
	  f2ptr node = f2__cons__car(cause, iter);
	  f2__graph__add_node(cause, new_graph, node);
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      {
	f2ptr iter = small__nodes;
	while (iter) {
	  f2ptr node = f2__cons__car(cause, iter);
	  if (! f2__graph__contains_node(cause, new_graph, node)) {
	    f2__graph__add_node(cause, new_graph, node);
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
    f2ptr this__edges         = f2__graph__edges(cause, this);
    f2ptr that__edges         = f2__graph__edges(cause, that);
    u64   this__edges__length = raw__simple_length(cause, this__edges);
    u64   that__edges__length = raw__simple_length(cause, that__edges);
    {
      f2ptr small__edges;
      f2ptr large__edges;
      f2ptr small;
      f2ptr large;
      if (this__edges__length < that__edges__length) {
	small__edges = this__edges;
	large__edges = that__edges;
	small        = this;
	large        = that;
      } else {
	small__edges = that__edges;
	large__edges = this__edges;
	small        = that;
	large        = this;
      }
      {
	f2ptr iter = large__edges;
	while (iter) {
	  f2ptr edge = f2__cons__car(cause, iter);
	  {
	    f2ptr label      = f2__graph_edge__label(     cause, edge);
	    f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
	    f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	    f2__graph__add_edge(cause, new_graph, label, left_node, right_node);
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      {
	f2ptr iter = small__edges;
	while (iter) {
	  f2ptr edge = f2__cons__car(cause, iter);
	  {
	    f2ptr label      = f2__graph_edge__label(     cause, edge);
	    f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
	    f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	    if (! raw__graph__contains_edge(cause, small, label, left_node, right_node)) {
	      f2__graph__add_edge(cause, new_graph, label, left_node, right_node);
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
    }
  }
  return new_graph;
}

f2ptr f2__graph__union(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__graph__is_type(cause, this)) ||
      (! raw__graph__is_type(cause, that))) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__union(cause, this, that);
}
def_pcfunk2(graph__union, this, that, return f2__graph__union(this_cause, this, that));

boolean_t raw__graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  boolean_t left_node__outs__was_removed = boolean__false;
  f2ptr     left_node__outs              = raw__graph__node__outs(cause, this, left_node);
  {
    f2ptr prev = nil;
    f2ptr iter = left_node__outs;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    left_node__outs = next;
	    raw__graph__node__outs__set(cause, this, left_node, left_node__outs);
	  }
	  left_node__outs__was_removed = boolean__true;
	}
      }
      prev = iter;
      iter = next;
    }
  }
  boolean_t right_node__ins__was_removed = boolean__false;
  f2ptr     right_node__ins              = raw__graph__node__ins(cause, this, right_node);
  {
    f2ptr prev = nil;
    f2ptr iter = right_node__ins;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    right_node__ins = next;
	    raw__graph__node__ins__set(cause, this, right_node, right_node__ins);
	  }
	  right_node__ins__was_removed = boolean__true;
	}
      }
      prev = iter;
      iter = next;
    }
  }
  boolean_t edges__was_removed = boolean__false;
  f2ptr edges = f2__graph__edges(cause, this);
  {
    f2ptr prev = nil;
    f2ptr iter = edges;
    while (iter) {
      f2ptr next = f2__cons__cdr(cause, iter);
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr edge__label      = f2__graph_edge__label(     cause, edge);
	f2ptr edge__left_node  = f2__graph_edge__left_node( cause, edge);
	f2ptr edge__right_node = f2__graph_edge__right_node(cause, edge);
	if (raw__eq(cause, edge__label,      label)     &&
	    raw__eq(cause, edge__left_node,  left_node) &&
	    raw__eq(cause, edge__right_node, right_node)) {
	  if (prev) {
	    f2__cons__cdr__set(cause, prev, next);
	  } else {
	    f2__graph__edges__set(cause, this, next);
	  }
	  edges__was_removed = boolean__true;
	}
      }
      prev = iter;
      iter = next;
    }
  }
  release__assert(left_node__outs__was_removed == right_node__ins__was_removed && right_node__ins__was_removed == edges__was_removed, nil, "!(left_node__outs__was_removed == right_node__ins__was_removed == edges__was_removed)");
  // edges removed.  remove nodes if removed edge was last edge (node has no edges now).
  if (right_node__ins == nil) {
    f2ptr right_node__outs = raw__graph__node__outs(cause, this, right_node);
    if (right_node__outs == nil) {
      raw__graph__subtract_node(cause, this, right_node);
    }
  }
  if (left_node__outs == nil) {
    f2ptr left_node__ins = raw__graph__node__ins(cause, this, left_node);
    if (left_node__ins == nil) {
      raw__graph__subtract_node(cause, this, left_node);
    }
  }
  return left_node__outs__was_removed;
}

f2ptr f2__graph__subtract_edge(f2ptr cause, f2ptr this, f2ptr label, f2ptr left_node, f2ptr right_node) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__graph__subtract_edge(cause, this, label, left_node, right_node));
}
def_pcfunk4(graph__subtract_edge, this, label, left_node, right_node, return f2__graph__subtract_edge(this_cause, this, label, left_node, right_node));

f2ptr raw__graph__copy(f2ptr cause, f2ptr this) {
  f2ptr new_graph = f2__graph__new(cause);
  f2ptr nodes = f2__graph__nodes(cause, this);
  {
    f2ptr iter = nodes;
    while (iter) {
      f2ptr node = f2__cons__car(cause, iter);
      raw__graph__add_node(cause, new_graph, node);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  f2ptr edges = f2__graph__edges(cause, this);
  {
    f2ptr iter = edges;
    while (iter) {
      f2ptr edge = f2__cons__car(cause, iter);
      {
	f2ptr label      = f2__graph_edge__label(     cause, edge);
	f2ptr left_node  = f2__graph_edge__left_node( cause, edge);
	f2ptr right_node = f2__graph_edge__right_node(cause, edge);
	raw__graph__add_edge(cause, new_graph, label, left_node, right_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return new_graph;
}

f2ptr f2__graph__copy(f2ptr cause, f2ptr this) {
  if (! raw__graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__graph__copy(cause, this);
}
def_pcfunk1(graph__copy, this, return f2__graph__copy(this_cause, this));


f2ptr raw__graph__part_not_contained_by(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr part_not_contained_graph = f2__graph__new(cause);
  {
    f2ptr this__nodes = f2__graph__nodes(cause, this);
    {
      f2ptr iter = this__nodes;
      while (iter) {
	f2ptr this__node = f2__cons__car(cause, iter);
	if (! raw__graph__contains_node(cause, that, this__node)) {
	  raw__graph__add_node(cause, part_not_contained_graph, this__node);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  {
    f2ptr this__edges = f2__graph__edges(cause, this);
    {
      f2ptr iter = this__edges;
      while (iter) {
	f2ptr this__edge = f2__cons__car(cause, iter);
	{
	  f2ptr this__edge__label      = f2__graph_edge__label(     cause, this__edge);
	  f2ptr this__edge__left_node  = f2__graph_edge__left_node( cause, this__edge);
	  f2ptr this__edge__right_node = f2__graph_edge__right_node(cause, this__edge);
	  if (! raw__graph__contains_edge(cause, that, this__edge__label, this__edge__left_node, this__edge__right_node)) {
	    raw__graph__add_edge(cause, part_not_contained_graph, this__edge__label, this__edge__left_node, this__edge__right_node);
	  }
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return part_not_contained_graph;
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

boolean_t raw__rooted_graph__is_type(f2ptr cause, f2ptr this) {
  if (raw__graph__is_type(  cause, this) &&
      raw__graph__is_rooted(cause, this)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__rooted_graph__is_type(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__rooted_graph__is_type(cause, this));
}

f2ptr raw__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  f2ptr frame     = f2__frame__new(cause);
  f2ptr root      = f2__graph__root(cause, this);
  f2ptr out_edges = f2__graph__node__outs(cause, this, root);
  {
    f2ptr iter = out_edges;
    while (iter) {
      f2ptr out_edge = f2__cons__car(cause, iter);
      {
	f2ptr label      = f2__graph_edge__label(     cause, out_edge);
	f2ptr right_node = f2__graph_edge__right_node(cause, out_edge);
	f2__frame__add_var_value(cause, frame, label, right_node);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return frame;
}

f2ptr f2__rooted_graph__as__frame(f2ptr cause, f2ptr this) {
  if (! raw__rooted_graph__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__rooted_graph__as__frame(cause, this);
}
def_pcfunk1(rooted_graph__as__frame, this, return f2__rooted_graph__as__frame(this_cause, this));

f2ptr f2trans__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2trans__primobject_type__new(cause);
  {char* slot_name = "equals";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.equals__funk);}
  {char* slot_name = "equals_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.equals_hash_value__funk);}
  {char* slot_name = "part_not_contained_by"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.part_not_contained_by__funk);}
  {char* slot_name = "as-frame";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_trans.as__frame__funk);}
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
  
  // graph_edge
  initialize_primobject_3_slot(graph_edge, label, left_node, right_node);
  
  // graph
  initialize_primobject_6_slot(graph, is_rooted, root, nodes, edges, edges_node_hash, edge_structure_hash_value);
  
  {char* symbol_str = "equals"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__equals, this, that, cfunk, 0, "checks for equality between two graphs."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals__funk = never_gc(cfunk);}
  {char* symbol_str = "equals_hash_value"; __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__equals_hash_value, this, cfunk, 0, "calculates the equals_hash_value for a graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.equals_hash_value__funk = never_gc(cfunk);}
  {char* symbol_str = "part_not_contained_by"; __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(graph__part_not_contained_by, this, that, cfunk, 0, "calculates the subgraph of this graph that is not contained in that graph."); __funk2.globalenv.object_type.primobject.primobject_type_graph.part_not_contained_by__funk = never_gc(cfunk);}
  {char* symbol_str = "as-frame"; __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(graph__as__frame, this, cfunk, 0, "returns a rooted graph as a frame."); __funk2.globalenv.object_type.primobject.primobject_type_graph.as__frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__2(graph__add_node,           this, node,                         "add a node to a graph by mutation.");
  f2__primcfunk__init__4(graph__add_edge,           this, label, left_node, right_node, "add an edge to a graph by mutation.");
  f2__primcfunk__init__2(graph__node__ins_and_outs, this, node,                         "get in and out edges of a node.");
  f2__primcfunk__init__2(graph__contains_node,      this, node,                         "returns boolean true if this graph contains node.");
  f2__primcfunk__init__2(graph__node__ins,          this, node,                         "returns node in edges.");
  f2__primcfunk__init__3(graph__node__ins__set,     this, node, ins,                    "sets node in edges.");
  f2__primcfunk__init__2(graph__node__outs,         this, node,                         "returns node out edges.");
  f2__primcfunk__init__3(graph__node__outs__set,    this, node, outs,                   "sets node out edges.");
  f2__primcfunk__init__4(graph__contains_edge,      this, label, left_node, right_node, "returns boolean true if this graph contains edge.");
  
  f2__primcfunk__init__1(graph__new_from_string,         string,                               "creates a graph of characters from a string.  (function used for debugging graph matching)");
  f2__primcfunk__init__1(graph__to_string,               this,                                 "creates a string from a graph made from a string.  (function used for debugging graph matching)");
  f2__primcfunk__init__3(graph__subgraphs_of_node_range, this, min_node_count, max_node_count, "returns all subgraphs with min_node_count to max_node_count nodes.");
  f2__primcfunk__init__1(graph__subgraphs,               this,                                 "returns all subgraphs of graph.");
  f2__primcfunk__init__2(graph__intersect,               this, that,                           "returns the intersection of two graphs.");
  f2__primcfunk__init__2(graph__union,                   this, that,                           "returns the union of two graphs.");
  f2__primcfunk__init__2(graph__subtract_node,           this, node,                           "subtract node from this graph.");
  f2__primcfunk__init__4(graph__subtract_edge,           this, label, left_node, right_node,   "subtract an edge from a perception graph.");
  f2__primcfunk__init__1(graph__copy,                    this,                                 "returns a copy of this graph.");
  f2__primcfunk__init__2(graph__part_not_contained_by,   this, that,                           "determines the maximal part of this graph that is not contained in that graph.");
  
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

